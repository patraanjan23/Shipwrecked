#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "players.h"
#include "game_functions.h"
#include "sdl_functions.h"
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

  FRAME *playerSprite = loadSprite(16, addString(TEXTURE_TEST, ".txt"));
  SDL_Texture *P1_SHEET = loadImage(addString(TEXTURE_TEST, ".png"), ren);

  POS_V p1_pos = newVector(0, 0);

//  POS_V currentPos = p1_pos;
//  DSP_V currentDsp = zeroVector();
//  VEL_V currentVel = zeroVector();
//  ACC_V currentAcc = zeroVector();


  SDL_Rect player;
  player.x = p1_pos.i;
  player.y = p1_pos.j;
  player.w = 72 / 2;
  player.h = 97 / 2;

  FRAME *player2Sprite = loadSprite(16, addString(TEXTURE_TEST2, ".txt"));
  SDL_Texture *P2_SHEET = loadImage(addString(TEXTURE_TEST2, ".png"), ren);

  SDL_Rect player2;
  player2.x = 0;
  player2.y = 0;
  player2.w = 72 / 2;
  player2.h = 97 / 2;

  PLAYER p1;
  p1.pcFrames = playerSprite;
  p1.pcImg = P1_SHEET;
  p1.pcLoc = &player;
  p1.walk = false;

  PLAYER p2;
  p2.pcFrames = player2Sprite;
  p2.pcImg = P2_SHEET;
  p2.pcLoc = &player2;
  p2.walk = false;

//    SDL_Rect **playersArray = malloc(sizeof(SDL_Rect *) * 2);
//    playersArray[0] = &player2;
//    playersArray[1] = &player;

  PLAYER **players = malloc(sizeof(PLAYER) * 2);
  players[0] = &p1;
  players[1] = &p2;

  PLAYER_C *test_player = new_player("baka", addString(TEXTURE_TEST, ".png"), addString(TEXTURE_TEST, ".txt"), 200, 300, 200, 200, 16, ren);

  int t = 5;
  int u = 5;
  bool quit = false;
  SDL_Event event;
  while (!quit)
    {
      players[0]->walk = false;
      players[1]->walk = false;

      SDL_Thread *thread2 = SDL_CreateThread(testThread2, "Test Thread 2", &p1);

//      eventLoop(&event, &quit, players);
      eventLoopC(&event, &quit, test_player);
      playerBound(players);

      SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
      SDL_RenderClear(ren);
//        renderFrame(ren, P1_SHEET, playerSprite, t, &player);
      renderPlayer(ren, &p1, t);
//        renderFrame(ren, P2_SHEET, player2Sprite, u, &player2);
      renderPlayer(ren, &p2, u);

      renderPlayerC(test_player, ren);

      if (p1.walk)
        {
          if (t++ == 15) t = 5;
        }
      if (p2.walk)
        {
          if (u++ == 15) u = 5;
        }

      SDL_RenderPresent(ren);
      SDL_WaitThread(thread2, &threadReturnValue);
      SDL_Delay(33);
    }
  free(playerSprite);
  free(player2Sprite);
//    free(playersArray);
  free(players);
  free(test_player);
}

// THEAD 1 : Does a simple counting from 0 - 9 and returns 10 in the thread value
int testThread(void *data)
{
  int cnt = 0;

  while (cnt < 10)
    {
      printf("count : %d\n", cnt);
      cnt++;
    }

  return cnt;
}

// THREAD 2 : Runs the auto movement of P2
int testThread2(void *data)
{
  PLAYER *p = (PLAYER *)data;

  if (p->pcLoc->x == (1024 - p->pcLoc->w))
    {
      p->pcLoc->x = 0;
    }
  if (p->pcLoc->y == (600 - p->pcLoc->h))
    {
      p->pcLoc->y = 0;
    }

  p->pcLoc->x += 1;
  p->pcLoc->y += 1;
  p->walk = true;

  return 0;
}


/*
 * Event Handling : Key input
 */
void eventLoop(SDL_Event *event, bool *quit, PLAYER **players)
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
//            case SDLK_RIGHT:
//              walkPlayer(players[0], DIR_RIGHT);
////              walkPlayerC(test_p, DIR_RIGHT);
//              break;
//            case SDLK_LEFT:
//              walkPlayer(players[0], DIR_LEFT);
////              walkPlayerC(test_p, DIR_LEFT);
//              break;
//            case SDLK_DOWN:
//              walkPlayer(players[0], DIR_DOWN);
////              walkPlayerC(test_p, DIR_DOWN);
//              break;
//            case SDLK_UP:
//              walkPlayer(players[0], DIR_UP);
////              walkPlayerC(test_p, DIR_UP);
//              break;
            case SDLK_w:
              walkPlayer(players[1], DIR_UP);
              break;
            case SDLK_s:
              walkPlayer(players[1], DIR_DOWN);
              break;
            case SDLK_a:
              walkPlayer(players[1], DIR_LEFT);
              break;
            case SDLK_d:
              walkPlayer(players[1], DIR_RIGHT);
              break;
            default:
              break;
            }
        }
    }
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
