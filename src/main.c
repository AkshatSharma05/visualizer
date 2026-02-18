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

				case SDL_KEYDOWN:
					if(ev.key.keysym.sym == SDLK_LEFTBRACKET){
						current_track = abs(current_track - 1) % file_count;
						loadTrack(current_track);
						// printf("%d\n", current_track);
					}
					if(ev.key.keysym.sym == SDLK_RIGHTBRACKET){
						current_track = abs(current_track + 1) % file_count;
						loadTrack(current_track);
					}
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