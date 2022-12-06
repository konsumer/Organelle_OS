// this describes a rotary-encoder using Linux event-interface (/dev/input/*) for keyboard, joystick, and pi GPIO rotary-encoder

#include "../Rotary.h"

#ifndef ROTARY_EVENT_KEYBOARDJOYSTICKGPIO_H
#define ROTARY_EVENT_KEYBOARDJOYSTICKGPIO_H

#include <stdint.h> 

class Rotary_Event_KeyboardJoystickGPIO: public Rotary_Base
{
  public:
    Rotary_Event_KeyboardJoystickGPIO();
    ~Rotary_Event_KeyboardJoystickGPIO();
    void update();

    uint32_t encBut;
    uint32_t encButFlag;
    uint32_t encTurn;
    uint32_t encTurnFlag;
};

#endif
