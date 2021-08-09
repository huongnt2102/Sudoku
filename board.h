#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>

struct tile
{
    int value;
    int isActive; // was it clicked?
    bool changed; // change flag for updating the number texture
    bool isError; //
    int result; // correct value

//    SDL_Texure* numTexture;
};

#endif // BOARD_H
