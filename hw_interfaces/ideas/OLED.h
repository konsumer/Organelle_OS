// This is the base-class of a 128x64 display

#ifndef OLED_BASE_H
#define OLED_BASE_H

#include "../../OledScreen.h"

class OLED_Base
{
  public:
    OLED_Base();
    ~OLED_Base();
    void update(OledScreen &s);
};

#endif
