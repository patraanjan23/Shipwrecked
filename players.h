#ifndef PLAYERS_H
#define PLAYERS_H

#define DIR_LEFT 100
#define DIR_RIGHT 200
#define DIR_UP 300
#define DIR_DOWN 400

#include <SDL2/SDL.h>
#include "sdl_functions.h"
#include "physics.h"

typedef enum{STAND, WALK, JUMP} MOV;

typedef struct _sprite_frame_c
{
  char frame[20];
  int x;
  int y;
  int w;
  int h;
} FRAME_C;


typedef struct _player
{
  char        *name;
  POS_V        pos;
  SDL_Texture *pTexture;
  FRAME       *frames;
  MOV         *movement;
} PLAYER_C;

PLAYER_C *new_player(char *player_name, char *player_spritesheet, char *player_metadata, float player_pos_x, float player_pos_y, float player_size_w, float player_size_h, int player_frames, SDL_Renderer *ren);
void renderPlayerC(PLAYER_C *p, SDL_Renderer *ren);
void walkPlayerC(PLAYER_C *p, int direction);
void eventLoopC(SDL_Event *event, bool *quit, PLAYER_C *test_p);

#endif // PLAYERS_H
