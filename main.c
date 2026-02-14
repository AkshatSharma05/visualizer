#include <math.h>
#include "handlers.h"

bool running = true;

int frq_cmp[] = {1,2,1,10,11,2,15,21,1,4,5,8,0,0,1,4,1,1,4,10};

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


		SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);

		for(int i = 1; i <= 20; i++){
			SDL_RenderDrawLine(renderer, (WINDOW_WIDTH / 20) * i, WINDOW_HEIGHT/2, (WINDOW_WIDTH / 20) * i, WINDOW_HEIGHT/2 - 10 * frq_cmp[i-1]);
		}
		
		SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
		SDL_SetRenderTarget( renderer, NULL );
		SDL_RenderPresent( renderer );		
		SDL_Delay( 1000.0/FPS );
	}

	deInitSDL2();
	return 0;
}