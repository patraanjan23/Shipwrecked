#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "players.h"
#include "sdl_functions.h"
#include "game_functions.h"

int main(int argc, char *argv[])
{
  char title[] = "Shipwrecked";
  int posX = 100;
  int posY = 100;
  int width = 1024;
  int height = 600;

  WIN_REN *gameApp = gameInit(title, posX, posY, width, height);

  gameLoop(gameApp->ren);

  SDL_DestroyRenderer(gameApp->ren);
  SDL_DestroyWindow(gameApp->win);
  SDL_Quit();

  free(gameApp);
  return 0;
}
