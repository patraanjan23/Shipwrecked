
#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include <SDL2/SDL.h>

typedef enum {false, true} bool;
typedef struct _sprite_frame
{
    char frame[20];
    int x;
    int y;
    int w;
    int h;
} FRAME;

typedef struct _player
{
    FRAME *pcFrames;
    SDL_Texture *pcImg;
    SDL_Rect *pcLoc;
} PLAYER;

typedef struct _sprite_animation
{
    int walk;
    PLAYER *p;
} WALK_ANIM;

void gameLoop(SDL_Renderer *ren);
FRAME *loadSprite(int f_count, char *metadata);
char *addString(char *string_A, char *string_B);

#endif // GAME_FUNCTIONS_H
