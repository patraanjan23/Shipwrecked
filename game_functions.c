
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "game_functions.h"
#include "sdl_functions.h"
#include "physics.h"

#define DEBUG false

char TEXTURE_TEST[] = "../assets/platformerGraphicsDeluxe/Player/p3_spritesheet";
char TEXTURE_TEST2[] = "../assets/platformerGraphicsDeluxe/Player/p1_spritesheet";

void gameLoop(SDL_Renderer *ren)
{
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError("IMG_Init");
        SDL_Quit();
    }

    FRAME *playerSprite = loadSprite(16, addString(TEXTURE_TEST, ".txt"));
    SDL_Texture *P1_SHEET = loadImage(addString(TEXTURE_TEST, ".png"), ren);

    POS_V p1_pos = newVector(0, 0);

//    POS_V currentPos = p1_pos;
//    DSP_V currentDsp = zeroVector();
//    VEL_V currentVel = zeroVector();
//    ACC_V currentAcc = zeroVector();


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

    PLAYER p2;
    p2.pcFrames = player2Sprite;
    p2.pcImg = P2_SHEET;
    p2.pcLoc = &player2;


    int t = 5;
    int u = 5;
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        bool walking = false;
        bool walking2 = false;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_RIGHT:
                    walking = true;
                    player.x += 10;
                    if (DEBUG) printf("t = %d\n", t);
                    break;
                case SDLK_LEFT:
                    walking = true;
                    player.x -= 10;
                    if (DEBUG) printf("t = %d\n", t);
                    break;
                case SDLK_DOWN:
                    walking = true;
                    player.y += 10;
                    if (DEBUG) printf("t = %d\n", t);
                    break;
                case SDLK_UP:
                    walking = true;
                    player.y -= 10;
                    if (DEBUG) printf("t = %d\n", t);
                    break;
                case SDLK_w:
                    walking2 = true;
                    player2.y -= 10;
                    break;
                case SDLK_s:
                    walking2 = true;
                    player2.y += 10;
                    break;
                case SDLK_a:
                    walking2 = true;
                    player2.x -= 10;
                    break;
                case SDLK_d:
                    walking2 = true;
                    player2.x += 10;
                    break;
                default:
                    break;
                }
            }
        }
        if (player.x + player.w > 1024)
        {
            player.x = 1024 - player.w;
        }
        if (player.x < 0)
        {
            player.x = 0;
        }
        if (player.y + player.h > 600)
        {
            player.y = 600 - player.h;
        }
        if (player.y < 0)
        {
            player.y = 0;
        }

        if (player2.x + player2.w > 1024)
        {
            player2.x = 1024 - player2.w;
        }
        if (player2.x < 0)
        {
            player2.x = 0;
        }
        if (player2.y + player2.h > 600)
        {
            player2.y = 600 - player2.h;
        }
        if (player2.y < 0)
        {
            player2.y = 0;
        }
        SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
        SDL_RenderClear(ren);
//        renderFrame(ren, P1_SHEET, playerSprite, t, &player);
        renderPlayer(ren, &p1, t);
//        renderFrame(ren, P2_SHEET, player2Sprite, u, &player2);
        renderPlayer(ren, &p2, u);

        if (walking)
        {
            if (t++ == 15) t = 5;
        }
        if (walking2)
        {
            if (u++ == 15) u = 5;
        }

        SDL_RenderPresent(ren);
        SDL_Delay(33);
    }
    free(playerSprite);
    free(player2Sprite);
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
 *  Loads sprite metadata into array
 */

FRAME *loadSprite(int f_count, char *metadata)
{
    if (DEBUG)
    {
        printf("METADATA : %s\n", metadata);
    }


    FRAME *sprite = malloc(f_count * sizeof(FRAME));
    FILE *fp = fopen(metadata, "r");
    if (fp == NULL)
    {
        printf("The metadata file not found\n");
        return NULL;
    }

    int i = 0;
    while (true)
    {
        fscanf(fp, "%s = %d %d %d %d", sprite[i].frame, &sprite[i].x, &sprite[i].y, &sprite[i].w, &sprite[i].h);
        if (DEBUG)
        {
            printf("Entered %d dataline : %s, %d, %d, %d, %d\n", i + 1, sprite[i].frame, sprite[i].x, sprite[i].y, sprite[i].w, sprite[i].h);
        }
        if (i++ == f_count) break;
    }

    if (DEBUG)
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
