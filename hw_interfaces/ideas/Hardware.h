// this is the central Hardware Interface

#ifndef HARDWARE_H
#define HARDWARE_H

#include "./Footswitch.h"

#include "./LED.h"
#include "./LED/LED_CM3_GPIO.h"
#include "./LED/LED_Pi_GPIO.h"
#include "./LED/LED_Pi_i2c.h"
#include "./LED/LED_SDL.h"
#include "./LED/LED_Serial.h"

#include "./NoteKeys.h"
#include "./Pots.h"

#include "./Rotary.h"
#include "./Rotary/Rotary_CM3_GPIO.h"
#include "./Rotary/Rotary_Event_KeyboardJoystickGPIO.h"
#include "./Rotary/Rotary_SDL_KeyboardJoystick.h"
#include "./Rotary/Rotary_Serial.h"

#include "./OLED.h"
#include "./OLED/OLED_CM3_GPIO.h"
#include "./OLED/OLED_Pi_i2c.h"
#include "./OLED/OLED_SDL.h"
#include "./OLED/OLED_Serial.h"

class HardwareInterface
{
  public:
    HardwareInterface() {
      #if HW_LED =="SDL"
        led = new LED_SDL();
      #endif

      #if HW_OLED == "SDL"
        oled = new OLED_SDL();
      #endif

      #if HW_ROTARY == "SDL"
        rotary = new Rotary_SDL_KeyboardJoystick();
      #endif
    }

    ~HardwareInterface() {
      delete footswitch;
      delete led;
      delete noteKeys;
      delete oled;
      delete pots;
      delete rotary;
    }

    void update(OledScreen &s) {
      if (led) {
        led.update();
      }
      
      if (oled) {
        oled.update(OledScreen &s);
      }

      if (rotary) {
        rotary.update();
      }
    }

  private:
    Footswitch_Base footswitch;
    LED_Base led;
    NoteKeys_Base noteKeys;
    OLED_Base oled;
    Pots_Base pots;
    Rotary_Base rotary;
};


#endif