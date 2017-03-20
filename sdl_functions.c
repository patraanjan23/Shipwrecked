
#include "sdl_functions.h"
#include "game_functions.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

/*
*	A function that prints formatted Error msg with SDL_GetError.
*	Argument is an additional msg to be shown with SDL_GetError.
*	Example use: log("SDL_CreateWindow");
*/
void logSDLError(char *msg)
{
    printf("Error: %s: %s\n", msg, SDL_GetError());
}

// game window and renderer setup
WIN_REN *gameInit(char *title, int posX, int posY, int width, int height)
{
    // SDL Initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError("SDL_Init");
        return NULL;
    }

    // Window and Renderer
    WIN_REN *tmp = malloc(sizeof(WIN_REN));
    tmp->win = SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_SHOWN);
    if (tmp->win == NULL)
    {
        logSDLError("SDL_CreateWindow");
        SDL_Quit();
        return NULL;
    }
    tmp->ren = SDL_CreateRenderer(tmp->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (tmp->ren == NULL)
    {
        logSDLError("SDL_CreateRenderer");
        SDL_DestroyWindow(tmp->win);
        SDL_Quit();
        return NULL;
    }
    return tmp;
}

SDL_Texture *loadImage(const char *img, SDL_Renderer *renderer)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, img);
    if (texture == NULL)
    {
        logSDLError("loadImage");
    }
    return texture;
}

void drawPlayer(SDL_Texture *player, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip)
{
    SDL_RenderCopy(ren, player, clip, &dst);
}

void renderFrame(SDL_Renderer *ren, SDL_Texture *spritesheet, FRAME *metadata, int f_number, SDL_Rect *dst)
{
    SDL_Rect clip;
    clip.x = metadata[f_number].x;
    clip.y = metadata[f_number].y;
    clip.w = metadata[f_number].w;
    clip.h = metadata[f_number].h;

    SDL_RenderCopy(ren, spritesheet, &clip, dst);
}

void renderPlayer(SDL_Renderer *ren, PLAYER *p, int f_number)
{
    renderFrame(ren, p->pcImg, p->pcFrames, f_number, p->pcLoc);
}
