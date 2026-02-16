#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH  	640.0
#define WINDOW_HEIGHT 	480.0
#define FPS			  	30.0

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event ev;

void initSDL2();
void updateAudio(int frq_cmp[]);
void deInitSDL2();