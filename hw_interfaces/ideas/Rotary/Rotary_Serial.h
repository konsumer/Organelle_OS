// this describes the serial input of a rotary-encoder

#include "../Rotary.h"

#ifndef ROTARY_SERIAL_H
#define ROTARY_SERIAL_H

#include <stdint.h> 

class Rotary_Serial: public Rotary_Base
{
  public:
    Rotary_Serial();
    ~Rotary_Serial();
    void update();

    uint32_t encBut;
    uint32_t encButFlag;
    uint32_t encTurn;
    uint32_t encTurnFlag;
};

#endif