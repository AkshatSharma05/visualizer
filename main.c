#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#include "handlers.h"

bool running = true;

int main ( ) {
	initSDL2();
	while( running ){
		while( SDL_PollEvent(&ev) != 0 ){
			switch( ev.type ){
				case SDL_QUIT:
				running = false;
				break;
			}
		}

		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
		SDL_SetRenderTarget( renderer, NULL );
		SDL_RenderPresent( renderer );		
		SDL_Delay( 1000.0/FPS );
	}

	deInitSDL2();
	return 0;
}