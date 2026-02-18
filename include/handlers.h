#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH  	640.0
#define WINDOW_HEIGHT 	480.0
#define FPS			  	30.0
#define PLAYER_FONT "./fonts/pixel.ttf"

extern SDL_Window*          window;
extern SDL_Renderer*        renderer;
extern SDL_Event            ev;

extern SDL_Surface *textSurface;
extern SDL_Texture *textTexture;
extern TTF_Font *font;

extern SDL_Color textColor;

extern int frq_cmp[20];
extern int frq_smooth[20];
extern float smoothing;


void initSDL2();
void updateAudio(int frq_cmp[]);
void drawPlayer();
void deInitSDL2();