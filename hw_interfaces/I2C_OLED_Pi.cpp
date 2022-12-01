#include "I2C_OLED_Pi.h"

I2cOledRotary::I2cOledRotary() {
}

void I2cOledRotary::init(){
    // keys
    keyStatesLast = 0;
    clearFlags();
}

void I2cOledRotary::clearFlags() {
    encButFlag = 0;
    encTurnFlag = 0;
    knobFlag = 0;
    keyFlag = 0;
    footswitchFlag = 0;
}

// this polll uses keys for buttons and arrows for 2 menu knobs
// eventually it will use stuff attached to GPIO
void I2cOledRotary::poll(){
    // TODO: poll i2c rotary state
}

void I2cOledRotary::pollKnobs(){
}

void I2cOledRotary::updateOLED(OledScreen &s){
    // TODO: update OLED
}

void I2cOledRotary::ping(){
}

void I2cOledRotary::shutdown() {
    printf("sending shutdown...\n");
    exit(0);
}

void I2cOledRotary::setLED(unsigned stat) {
    stat %= 8;

    if (stat == 0) {
        printf("LED: 0 0 0\n");
    } else if (stat == 1) {
        printf("LED: 1 0 0\n");
    } else if (stat == 2) {
        printf("LED: 1 1 0\n");
    } else if (stat == 3) {
        printf("LED: 0 1 0\n");
    } else if (stat == 4) {
        printf("LED: 0 1 1\n");
    } else if (stat == 5) {
        printf("LED: 0 0 1\n");
    } else if (stat == 6) {
        printf("LED: 1 0 1\n");
    } else if (stat == 7) {
        printf("LED: 1 1 1\n");
    }
}