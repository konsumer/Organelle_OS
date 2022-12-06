// this is the baseclass for RGB LED

#ifndef LED_BASE_H
#define LED_BASE_H

class LED_Base
{
  public:
    LED_Base();
    ~LED_Base();
    void update(unsigned c);
};

#endif