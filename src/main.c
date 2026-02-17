#include <math.h>
#include "handlers.h"
#include "audio.h"

bool running = true;

int main ( ) {
	initSDL2();
	audioInit();

	while( running ){
		while( SDL_PollEvent(&ev) != 0 ){
			switch( ev.type ){
				case SDL_QUIT:
				running = false;
				break;
			}
		}

		updateAudio(frq_cmp);

		drawPlayer();
				
		SDL_Delay( 1000.0/FPS );
	}

	deInitAudio();
	deInitSDL2();
	
	return 0;
}