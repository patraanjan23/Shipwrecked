#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_functions.h"

typedef struct _sdl_win_ren
{
    SDL_Window *win;
    SDL_Renderer *ren;
} WIN_REN;

void logSDLError(char *msg);
WIN_REN *gameInit(char *title, int posX, int posY, int width, int height);
SDL_Texture *loadImage(const char *img, SDL_Renderer *renderer);
void renderFrame(SDL_Renderer *ren, SDL_Texture *spritesheet, FRAME *metadata, int f_number, SDL_Rect *dst);
void renderPlayer(SDL_Renderer *ren, PLAYER *p, int f_number);

#endif // SDL_FUNCTIONS_H
