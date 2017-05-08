#include "players.h"
#include "sdl_functions.h"
#include "physics.h"

#define DEBUG_PLAYER 0

PLAYER_C *new_player(char *player_name, char *player_spritesheet, char *player_metadata, float player_pos_x, float player_pos_y, float player_size_w, float player_size_h, int player_frames, SDL_Renderer *ren)
{

  // TODO (natsu#1#): Add player_name length handling
  PLAYER_C *p = malloc(sizeof(char) * 20 + sizeof(POS_V) + sizeof(SDL_Texture *) + sizeof(FRAME *) + sizeof(MOV));

  SDL_Texture *tmp_tex = loadImage(player_spritesheet, ren);
//  POS_V tmp_pos = newVector(player_pos_x, player_pos_y);
  FRAME *tmp_sprite = loadSprite(player_frames, player_metadata);
  MOV tmp_mov = STAND;

  p->name = player_name;
  p->pos.i = player_pos_x;
  p->pos.j = player_pos_y;
  p->pTexture = tmp_tex;
  p->frames = tmp_sprite;
  p->movement = &tmp_mov;

  printf("Successfully created  player : %s", player_name);
  return p;

  //TODO (natsu#9#): Complete the new player structure using vectors
}

void renderPlayerC(PLAYER_C *p, SDL_Renderer *ren)
{
  SDL_Rect clip;
  SDL_Rect dest;

  int f = 2;

  clip.x = p->frames[f].x;
  clip.y = p->frames[f].y;
  clip.w = p->frames[f].w;
  clip.h = p->frames[f].h;

  dest.x = p->pos.i;
  dest.y = p->pos.j;
  dest.w = p->frames[f].w;
  dest.h = p->frames[f].h;

  SDL_RenderCopy(ren, p->pTexture, &clip, &dest);
}

void walkPlayerC(PLAYER_C *p, int direction)
{
  switch(direction)
  {
  case DIR_LEFT:
    if (DEBUG_PLAYER) printf("case left reached\n");
    addVectorPointer(&p->pos, newVector(-10, 0));
    break;
  case DIR_RIGHT:
    if (DEBUG_PLAYER) printf("case right reached\n");
    addVectorPointer(&p->pos, newVector(10, 0));
    break;
  case DIR_UP:
    if (DEBUG_PLAYER) printf("case up reached\n");
    addVectorPointer(&p->pos, newVector(0, -10));
    break;
  case DIR_DOWN:
    if (DEBUG_PLAYER) printf("case down reached\n");
    addVectorPointer(&p->pos, newVector(0, 10));
    break;
  default:
    printf("Direction no defined\n");
  }
}

void eventLoopC(SDL_Event *event, bool *quit, PLAYER_C *test_p)
{
while (SDL_PollEvent(event))
    {
      if (event->type == SDL_QUIT)
        {
          *quit = true;
          break;
        }
      if (event->type == SDL_KEYDOWN)
        {
          switch(event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
              *quit = true;
              break;
            case SDLK_RIGHT:
              walkPlayerC(test_p, DIR_RIGHT);
              break;
            case SDLK_LEFT:
              walkPlayerC(test_p, DIR_LEFT);
              break;
            case SDLK_DOWN:
              walkPlayerC(test_p, DIR_DOWN);
              break;
            case SDLK_UP:
              walkPlayerC(test_p, DIR_UP);
              break;
            default:
              break;
            }
        }
    }
}


/* TODO (Natsu#1#05/05/17):
 * 1. Properly implement POS_V inside PLAYER_C.
 *    Currently the player structure tries to access
 *    a POS_V pointer. Either include POS_V directly
 *    inside PLAYER_C or change newPlayer() function
 *    to set the POS_V which is defined previously
 *    before fn call.
 *
 * 2. Clean up all headers. Implement all player
 *    related stuff inside players.h and players.c/
 *    rewrite the main game functions to incorporate
 *    both old/new PLAYER/PLAYER_C structures.
*/
