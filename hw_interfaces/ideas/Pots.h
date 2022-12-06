// this is the base-class of the 4 analog pots

#ifndef POTS_BASE_H
#define POTS_BASE_H

#include <stdint.h> 

class Pots_Base
{
  public:
    Pots_Base();
    ~Pots_Base();
    void update();

    uint32_t knobFlag;
    uint32_t adcs[8];
};

#endif