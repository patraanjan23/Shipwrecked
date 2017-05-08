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

typedef struct _player_s
{
  FRAME *pcFrames;
  SDL_Texture *pcImg;
  SDL_Rect *pcLoc;
  bool walk;
} PLAYER;

// Threads
int testThread(void *data);
int testThread2(void *data);

// Functions
void gameLoop(SDL_Renderer *ren);
FRAME *loadSprite(int f_count, char *metadata);
char *addString(char *string_A, char *string_B);
void eventLoop(SDL_Event *event, bool *quit, PLAYER **players);
void playerBound(PLAYER **players);
void walkPlayer(PLAYER* p, int direction);

#endif // GAME_FUNCTIONS_H
