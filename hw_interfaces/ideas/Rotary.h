// this is the base-class for a rotary-encoder input

#ifndef ROTARY_BASE_H
#define ROTARY_BASE_H

#include <stdint.h> 

class Rotary_Base
{
  public:
    Rotary_Base();
    ~Rotary_Base();
    void update();

    uint32_t encBut;
    uint32_t encButFlag;
    uint32_t encTurn;
    uint32_t encTurnFlag;
};

#endif