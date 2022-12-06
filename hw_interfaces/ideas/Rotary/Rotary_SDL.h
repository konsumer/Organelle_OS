// this describes a Rotary-decoder emulator in SDL using Keyboard & Joystick (if connected)
// It must be used with OLED_SDL

#include "../Rotary.h"

#ifndef ROTARY_SDL_H
#define ROTARY_SDL_H

#include <stdint.h> 

#ifndef HW_ROTARY_UP
  #define HW_ROTARY_UP "Up"
#endif

#ifndef HW_ROTARY_DOWN
  #define HW_ROTARY_DOWN "Down"
#endif

#ifndef HW_ROTARY_OK
  #define HW_ROTARY_OK "Return"
#endif

class Rotary_SDL: public Rotary_Base
{
  public:
    Rotary_SDL_KeyboardJoystick();
    ~Rotary_SDL_KeyboardJoystick();
    void update();

    uint32_t encBut;
    uint32_t encButFlag;
    uint32_t encTurn;
    uint32_t encTurnFlag;
};

#endif

