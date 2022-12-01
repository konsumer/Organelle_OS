CXX = g++

CXXFLAGS += -std=c++11

objects =  \
	main.o \
	AppData.o \
	Timer.o \
	MainMenu.o \
	OledScreen.o \
	SLIPEncodedSerial.o \
	Serial.o Socket.o \
	UdpSocket.o \
	OSC/OSCData.o \
	OSC/OSCMatch.o \
	OSC/OSCMessage.o \
	OSC/OSCTiming.o \
	OSC/SimpleWriter.o

SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)

default :
	@echo "platform not specified"

# TODO: organize hardware control classes into pieces, so they can be combined:

#  SDLOled             ORGANELLE_HW_WIDTH, ORGANELLE_HW_HEIGHT
#  SDLLED              (SDLOled)
#  SDLInputKeys        (SDLOled)
#  SDLInputJoystick    (SDLOled)
#  PiI2cOled           I2C_OLED
#  PiI2cLED            I2C_LED
#  PiGPIOLED           GPIO_LED
#  PiI2cInputRotary    I2C_ROTARY
#  PiEventInputRotary  EVENT_ROTARY_DEVICE
#  SerialInput
#  SerialOled
#  SerialLED
#  CM3GPIOInput
#  CM3GPIOOled
#  CM3GPIOLED

# example combinations:

# SDLOled, SDLLED, SDLInputKeys                   - All is emulated on screen, use keys, need to set ORGANELLE_HW_WIDTH, ORGANELLE_HW_HEIGHT
# SDLOled, SDLLED, SDLInputJoystick               - All is emulated on screen, use joystick, need to set ORGANELLE_HW_WIDTH, ORGANELLE_HW_HEIGHT
# SDLOled, SDLLED, SDLInputKeys, SDLInputJoystick - All is emulated on screen, use keys & joystick, need to set ORGANELLE_HW_WIDTH, ORGANELLE_HW_HEIGHT
# SDLOled, PiI2cLED, PiI2cInputRotary             - Rotary & LED on i2c, use SDL screen, need to set ORGANELLE_HW_WIDTH, ORGANELLE_HW_HEIGHT, I2C_LED, I2C_ROTARY
# PiI2cOled, PiI2cLED, PiI2cInputRotary           - All on Pi i2c devices, need to set I2C_OLED, I2C_LED, I2C_ROTARY
# PiI2cOled, PiGPIOLED, PiI2cInputRotary          - All on Pi i2c devices except LED, need to set GPIO_LED, I2C_OLED, I2C_ROTARY

# TODO: set defaults for all defines that make sense

organelle : CXXFLAGS += -DSERIAL_HW
organelle : $(objects) hw_interfaces/SerialMCU.o
	$(CXX) -o fw_dir/mother $(objects) hw_interfaces/SerialMCU.o

organelle_m : CXXFLAGS += -DCM3GPIO_HW -DMICSEL_SWITCH -DPWR_SWITCH -DOLED_30FPS -DBATTERY_METER -DFIX_ABL_LINK
organelle_m : $(objects) hw_interfaces/CM3GPIO.o
	$(CXX) -l wiringPi -o fw_dir/mother $(objects) hw_interfaces/CM3GPIO.o

sdl : CXXFLAGS += $(SDL_CFLAGS) -DORGANELLE_SDL_UI_HW -DORGANELLE_HW_WIDTH=800 -DORGANELLE_HW_HEIGHT=600
sdl : $(objects) hw_interfaces/SDLUi.o
	$(CXX) $(SDL_LIBS) -o fw_dir/mother $(objects) hw_interfaces/SDLUi.o

sdl_pi_i2c_rotary : CXXFLAGS += $(SDL_CFLAGS) -DORGANELLE_SDL_UI_HW -DORGANELLE_I2C_ROTARY_HW -DORGANELLE_HW_WIDTH=800 -DORGANELLE_HW_HEIGHT=600 -DI2C_ROTARY=0x24u
sdl_pi_i2c_rotary : $(objects) hw_interfaces/SDLI2cRotary.o
	$(CXX) $(SDL_LIBS) -o fw_dir/mother $(objects) hw_interfaces/SDLI2cRotary.o

pi_i2c_rotary_oled : CXXFLAGS += -DORGANELLE_I2C_OLED_HW -DORGANELLE_I2C_ROTARY_HW -DI2C_ROTARY=0x24u -DI2C_OLED=0x56u
pi_i2c_rotary_oled :  $(objects) hw_interfaces/I2cOledRotary.o
	$(CXX) -o fw_dir/mother $(objects) hw_interfaces/I2cOledRotary.o

.PHONY : clean

clean :
	rm -f main $(objects) fw_dir/mother hw_interfaces/SDLUi.o hw_interfaces/SerialMCU.o hw_interfaces/CM3GPIO.o hw_interfaces/I2C_Rotary_Pi.o hw_interfaces/I2C_OLED_Pi.o

IMAGE_BUILD_VERSION = $(shell cat fw_dir/version)
IMAGE_BUILD_TAG = $(shell cat fw_dir/buildtag)
IMAGE_VERSION = $(IMAGE_BUILD_VERSION)$(IMAGE_BUILD_TAG)
IMAGE_DIR = UpdateOS-$(IMAGE_VERSION)

organelle_deploy : organelle
	@echo "Updating OS to $(IMAGE_VERSION)"
	fw_dir/scripts/remount-rw.sh
	@echo "copying fw files to /root"
	rm -fr /root/fw_dir
	mkdir /root/fw_dir
	cp -fr fw_dir/* /root/fw_dir
	@echo "copying version file to root for backwards compatiblility"
	cp -fr fw_dir/version /root
	@echo "copying system files"
	cp -fr platforms/organelle/rootfs/* /
	sync

organelle_m_deploy : organelle_m
	@echo "Updating OS to $(IMAGE_VERSION)"
	@echo "copying common fw files"
	rm -fr /home/music/fw_dir
	mkdir /home/music/fw_dir
	cp -fr fw_dir/* /home/music/fw_dir
	@echo "copying platform fw files"
	cp -fr platforms/organelle_m/fw_dir/* /home/music/fw_dir
	chown -R music:music /home/music/fw_dir
	@echo "copying version file to root for backwards compatiblility"
	cp -fr fw_dir/version /root
	@echo "copying systems files"
	mkdir tmp
	cp -r platforms/organelle_m/rootfs tmp/
	chown -R root:root tmp/rootfs
	chown -R music:music tmp/rootfs/home/music
	cp -fr --preserve=mode,ownership tmp/rootfs/* /
	rm -fr tmp
	sync

# Generate with g++ -MM *.c* OSC/*.* 
AppData.o: AppData.cpp AppData.h OledScreen.h
MainMenu.o: MainMenu.cpp MainMenu.h AppData.h OledScreen.h
OledScreen.o: OledScreen.cpp OledScreen.h fonts.h simple_svg_1.0.0.hpp
SLIPEncodedSerial.o: SLIPEncodedSerial.cpp SLIPEncodedSerial.h Serial.h \
  UdpSocket.h Socket.h
Serial.o: Serial.cpp Serial.h
Socket.o: Socket.cpp Socket.h
Timer.o: Timer.cpp Timer.h
UdpSocket.o: UdpSocket.cpp UdpSocket.h Socket.h
main.o: main.cpp OSC/OSCMessage.h OSC/OSCData.h OSC/OSCTiming.h \
  OSC/SimpleWriter.h Serial.h UdpSocket.h Socket.h SLIPEncodedSerial.h \
  OledScreen.h MainMenu.h AppData.h Timer.h
serialdump.o: serialdump.c
test.o: test.cpp
OSCData.o: OSC/OSCData.cpp OSC/OSCData.h OSC/OSCTiming.h
OSCMatch.o: OSC/OSCMatch.c OSC/OSCMatch.h
OSCMessage.o: OSC/OSCMessage.cpp OSC/OSCMessage.h OSC/OSCData.h \
  OSC/OSCTiming.h OSC/SimpleWriter.h OSC/OSCMatch.h
OSCTiming.o: OSC/OSCTiming.cpp OSC/OSCTiming.h
SimpleWriter.o: OSC/SimpleWriter.cpp OSC/SimpleWriter.h

