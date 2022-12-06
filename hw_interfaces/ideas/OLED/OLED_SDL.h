#ifndef OLED_BASE_H
#define OLED_BASE_H

#include "../../OledScreen.h"

#define HW_SDL_WIDTH 800
#define HW_SDL_HEIGHT 600

class OLED_SDL
{
  public:
    OLED_SDL(int width = HW_SDL_WIDTH, int height = HW_SDL_HEIGHT);
    ~OLED_SDL();
    void update(OledScreen &s);
};

#endif