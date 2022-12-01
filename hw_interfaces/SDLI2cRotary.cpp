#include "SDLI2cRotary.h"

SDLI2cRotary::SDLI2cRotary() {
}

void SDLI2cRotary::init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Organelle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ORGANELLE_HW_WIDTH, ORGANELLE_HW_HEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    SDL_RenderSetLogicalSize(renderer, 128, 64);

    // keys
    keyStatesLast = 0;
    clearFlags();
}

void SDLI2cRotary::clearFlags() {
    encButFlag = 0;
    encTurnFlag = 0;
    knobFlag = 0;
    keyFlag = 0;
    footswitchFlag = 0;
}

// this polll uses keys for buttons and arrows for 2 menu knobs
// eventually it will use stuff attached to GPIO
void SDLI2cRotary::poll(){
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            shutdown();
        }
        // TODO: poll i2c rotary state
    }
}

void SDLI2cRotary::pollKnobs(){
}

void SDLI2cRotary::updateOLED(OledScreen &s){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int x, y;
    for (y = 0; y < 64; y++) {
        for (x = 0; x < 128; x++) {
            if (s.get_pixel(x, y)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void SDLI2cRotary::ping(){
}

void SDLI2cRotary::shutdown() {
    printf("sending shutdown...\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

void SDLI2cRotary::setLED(unsigned stat) {
    // TODO: add indicator on screen
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