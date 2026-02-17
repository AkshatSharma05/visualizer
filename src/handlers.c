#include "handlers.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event ev;

int frq_cmp[20] = {};
int frq_smooth[20] = {};

float smoothing = .5f;

void initSDL2(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("SDL2 init failed! \n");
	}
	if(!(window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS))){
		printf("Window creation failed!\n");
	}
	
	if(!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))){
		printf("Renderer creation failed! \n");
	}
}

void drawPlayer(){
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

	SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);

	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

	for (int i = 0; i < 20; i++) {
		if (frq_cmp[i] > frq_smooth[i])
			frq_smooth[i] += (frq_cmp[i]-frq_smooth[i]) * smoothing;
		else {
			frq_smooth[i] -= .5f;
			if (frq_smooth[i] < 0)
				frq_smooth[i] = 0;
		}
	}


    int bar_count = 20;
    int bar_width = WINDOW_WIDTH / bar_count;
    int gap = 10;

    for (int i = 0; i < bar_count; i++) {
        int x = i * bar_width + gap / 2;
        int val = frq_smooth[i];
        int bar_h = val * 10;
        SDL_Rect r = { x, WINDOW_HEIGHT/2 - bar_h, bar_width - gap, bar_h * 2 }; //x,y,w,h
        SDL_RenderFillRect(renderer, &r);
    }
	
	SDL_RenderPresent( renderer );
}

void deInitSDL2(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}