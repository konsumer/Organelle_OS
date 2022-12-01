# Organelle OS Program

Provides menu interface for operating the Organelle, interfaces with hardware, launches patches, provides settings for midi, wifi, etc...

## file locations

Mother assumes some things are in particular locations.

```
USB_PATCHES="/usbdrive/Patches"
SD_PATCHES="/sdcard/Patches"
DEFAULT_PATCHES="/usbdrive/Patches"

USB_USERDIR="/usbdrive"
SD_USERDIR="/sdcard"
DEFAULT_USERDIR="/usbdrive"

DEFAULT_FW="/root/fw_dir"
```

## make targets

There are several hardware make-targets available. See the [Makefile](./Makefile) for customization options. They all result in different `fw_dir/mother` builds.

### `make organelle`

This is the original [Organelle S](https://www.critterandguitari.com/organelle) hardware. It has a 128x64 OLED screen, and a primary rotary-encoder.


### `make organelle_m`

This is the original [Organelle M](https://www.critterandguitari.com/organelle) hardware. It has a 128x64 OLED screen, and a primary rotary-encoder.


### `make sdl`

This is a SDL-based UI. This allows keys (up/down/ENTER) & joystick (up/down/A) input for primary rotary-encoder. This is a good choice if you have a regular SDL-supported screen (not 128x64 OLED) and keys/joystick, and should work on framebuffer or in X on pi, for example. It's also a good choice if you are developing new Organelle features on desktop. YOu can customize `ORGANELLE_HW_WIDTH` and `ORGANELLE_HW_HEIGHT` to set the screen-dimensions of the SDL window.

### `make pi_sdl_i2c_rotary`

This is same as `sdl` above, but uses i2c drivers for primary rotary-encoder attached to [GPIO 2/3](https://pinout.xyz/pinout/i2c), and does not support joystick/keys. Double-check `I2C_ROTARY` in [Makefile](./Makefile) matches the i2c address of your rotary-encoder.

### `make pi_i2c_rotary_oled`

This uses an i2c OLED attached to [GPIO 2/3](https://pinout.xyz/pinout/i2c). Double-check `I2C_ROTARY` in [Makefile](./Makefile) matches the i2c address of your rotary-encoder, and `I2C_OLED` matches the i2c address of your i2c OLED.

