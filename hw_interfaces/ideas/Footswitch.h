// this is the base-class of the analog footswitch

#ifndef FOOTSWITCH_BASE_H
#define FOOTSWITCH_BASE_H

#include <stdint.h> 

class Footswitch_Base
{
  public:
    Footswitch_Base();
    ~Footswitch_Base();
    void update(unsigned c);
    
    uint32_t footswitch;
    uint32_t footswitchFlag;
};

#endif