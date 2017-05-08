#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "players.h"
#include "sdl_functions.h"
#include "game_functions.h"
#include "physics.h"

#define DEBUG_GAME false

char TEXTURE_TEST[] = "assets/platformerGraphicsDeluxe/Player/p3_spritesheet";
char TEXTURE_TEST2[] = "assets/platformerGraphicsDeluxe/Player/p1_spritesheet";

int threadReturnValue = 0;

void gameLoop(SDL_Renderer *ren)
{
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
      logSDLError("IMG_Init");
      SDL_Quit();
    }

  if (DEBUG_GAME)
    {
      SDL_Thread *thread = SDL_CreateThread(testThread, "Test Thread SDL 2 Shipwrecked", (void *)NULL);

      if (thread == NULL)
        {
          printf("thread creation failed: %s\n", SDL_GetError());
        }
      else
        {
          SDL_WaitThread(thread, &threadReturnValue);
          printf("Thread executed successfully and returned value : %d\n", threadReturnValue);
        }
    }

  PLAYER_C *test_player = new_player("baka", addString(TEXTURE_TEST, ".png"), addString(TEXTURE_TEST, ".txt"), 200, 300, 200, 200, 1, 16, ren);

  bool quit = false;
  SDL_Event event;
  while (!quit)
    {
      SDL_Thread *thread2 = SDL_CreateThread(testThread2, "Test Thread 2", test_player);

      eventLoopC(&event, &quit, test_player);

      SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
      SDL_RenderClear(ren);

      renderPlayerC(test_player, ren);

      SDL_RenderPresent(ren);
      SDL_WaitThread(thread2, &threadReturnValue);
      SDL_Delay(33);
    }

  free(test_player);
}



/*
 * THREAD 2 : Runs the auto movement of P2
 *
*/

int testThread2(void *data)
{
  PLAYER_C *p = (PLAYER_C *)data;

  if (p->pos.i == (1024 - p->dim.i))
    {
      p->pos.i = 0;
    }
  if (p->pos.j == (600 - p->dim.j))
    {
      p->pos.j = 0;
    }

  p->pos.i += 1;
  p->pos.j += 1;

  return 0;
}


/*
 * Bounds player to the screen
 */
void playerBound(PLAYER **players)
{
  if (players[0]->pcLoc->x + players[0]->pcLoc->w > 1024)
    {
      players[0]->pcLoc->x = 1024 - players[0]->pcLoc->w;
    }
  if (players[0]->pcLoc->x < 0)
    {
      players[0]->pcLoc->x = 0;
    }
  if (players[0]->pcLoc->y + players[0]->pcLoc->h > 600)
    {
      players[0]->pcLoc->y = 600 - players[0]->pcLoc->h;
    }
  if (players[0]->pcLoc->y < 0)
    {
      players[0]->pcLoc->y = 0;
    }

  if (players[1]->pcLoc->x + players[1]->pcLoc->w > 1024)
    {
      players[1]->pcLoc->x = 1024 - players[1]->pcLoc->w;
    }
  if (players[1]->pcLoc->x < 0)
    {
      players[1]->pcLoc->x = 0;
    }
  if (players[1]->pcLoc->y + players[1]->pcLoc->h > 600)
    {
      players[1]->pcLoc->y = 600 - players[1]->pcLoc->h;
    }
  if (players[1]->pcLoc->y < 0)
    {
      players[1]->pcLoc->y = 0;
    }
}


// Adds two strings and returns a string
char *addString(char *string_A, char *string_B)
{
  char *tmp = malloc(sizeof(char*) * (strlen(string_A) + strlen(string_B) + 1));
  strcpy(tmp, string_A);
  strcat(tmp, string_B);
  return tmp;
}


/*
 *  Loads sprite meta data into array
 */
FRAME *loadSprite(int f_count, char *metadata)
{
  if (DEBUG_GAME)
    {
      printf("METADATA : %s\n", metadata);
    }


  FRAME *sprite = malloc(f_count * sizeof(FRAME));
  FILE *fp = fopen(metadata, "r");
  if (fp == NULL)
    {
      printf("The meta data file not found\n");
      return NULL;
    }

  int i = 0;
  while (true)
    {
      fscanf(fp, "%s = %d %d %d %d", sprite[i].frame, &sprite[i].x, &sprite[i].y, &sprite[i].w, &sprite[i].h);
      if (DEBUG_GAME)
        {
          printf("Entered %d dataline : %s, %d, %d, %d, %d\n", i + 1, sprite[i].frame, sprite[i].x, sprite[i].y, sprite[i].w, sprite[i].h);
        }
      if (i++ == f_count) break;
    }

  if (DEBUG_GAME)
    {
      printf("Rechecking values of FRAMES before returning : \n");
      for (i = 0; i < f_count; i++)
        {
          printf("%s, %d, %d, %d, %d\n", sprite[i].frame, sprite[i].x, sprite[i].y, sprite[i].w, sprite[i].h);
        }
    }

  fclose(fp);
  return sprite;
}


void walkPlayer(PLAYER *p, int direction)
{
  p->walk = true;
  switch(direction)
    {
    case DIR_LEFT:
      p->pcLoc->x -= 10;
      break;
    case DIR_RIGHT:
      p->pcLoc->x += 10;
      break;
    case DIR_UP:
      p->pcLoc->y -= 10;
      break;
    case DIR_DOWN:
      p->pcLoc->y += 10;
      break;
    default:
      printf("Direction no defined\n");
    }
}

//void jumpPlayer(PLAYER *p, int direction)
//{
//  switch(direction)
//  {
//  case DIR_RIGHT:
//
//  }
//}

// THEAD 1 : Does a simple counting from 0 - 9 and returns 10 in the thread value
//int testThread(void *data)
//{
//  int cnt = 0;

//  while (cnt < 10)
//    {
//      printf("count : %d\n", cnt);
//      cnt++;
//    }

//  return cnt;
//}

