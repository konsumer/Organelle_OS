#ifndef HW_OLED_Rotary_H
#define HW_OLED_Rotary_H


#include <stdint.h>
#include <SDL2/SDL.h>
#include "../OledScreen.h"
#include "../OSC/OSCMessage.h"
#include "../OSC/SimpleWriter.h"
#include "../Serial.h"

// definition for SDL + pi i2c rotary-encoder
class SDLI2cRotary
{
    public:
        SDLI2cRotary();
        void init();
        void poll();
        void pollKnobs();
        void updateOLED(OledScreen &s);
        void ping();
        void shutdown();
        void setLED(unsigned c);
        void clearFlags();

        uint32_t encBut;
        uint32_t encButFlag;
        uint32_t encTurn;
        uint32_t encTurnFlag;
        uint32_t knobFlag;
        uint32_t adcs[8];
        uint32_t footswitch;
        uint32_t footswitchFlag;
        uint32_t keyStates;
        uint32_t keyStatesLast;
        uint32_t keyFlag;

        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Joystick *joystick;
};


#endif