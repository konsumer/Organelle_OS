// this describes a rotary-encoder connected to GPIO on CM3

#include "../Rotary.h"

#ifndef ROTARY_CM3_GPIO_H
#define ROTARY_CM3_GPIO_H

#include <stdint.h> 

class Rotary_CM3_GPIO: public Rotary_Base
{
  public:
    Rotary_CM3_GPIO();
    ~Rotary_CM3_GPIO();
    void update();

    uint32_t encBut;
    uint32_t encButFlag;
    uint32_t encTurn;
    uint32_t encTurnFlag;
};

#endif