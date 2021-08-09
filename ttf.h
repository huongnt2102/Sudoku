#ifndef TTF_H
#define TTF_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>


using namespace std;

void initTTF(SDL_Renderer *renderer);

void rendererTTF(SDL_Renderer* renderer, TTF_Font* font, string text, int left, int top, const SDL_Color RED);

void closeTTF(TTF_Font* font);

#endif
