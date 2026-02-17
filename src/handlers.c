#include "handlers.h"
#include "audio.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event ev;

SDL_Surface *textSurface = NULL;
SDL_Texture *textTexture = NULL;
TTF_Font *font = NULL;

SDL_Color textColor = {255, 255, 255, 255};

int frq_cmp[20] = {};
int frq_smooth[20] = {};

float smoothing = .5f;

int text_x = 0;

void initSDL2(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("SDL2 init failed! \n");
	}

	if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
    }

	if(!(window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS))){
		printf("Window creation failed!\n");
	}
	
	if(!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))){
		printf("Renderer creation failed! \n");
	}

	font = TTF_OpenFont(PLAYER_FONT, 26);
	if (!font){
		printf("Failed to load font: %s\n", TTF_GetError());
	}


	char *text = (strlen(files[current_track]) > 0) ? files[current_track] : " ";
	// printf("%d\n ", sizeof(files[current_track])/sizeof(char));
	textSurface = TTF_RenderText_Solid(font, text, textColor);

	if (!textSurface) {
		printf("Failed to create text surface: %s\n", TTF_GetError());
	}

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (!textTexture){
		printf("Failed to create text texture: %s\n", SDL_GetError());
	}

}

void drawPlayer(){
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

	SDL_RenderClear(renderer);

	
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
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

	SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2);

	char *text = (strlen(files[current_track]) > 0) ? files[current_track] : " ";
	// printf("%d\n ", sizeof(files[current_track])/sizeof(char));
	textSurface = TTF_RenderText_Solid(font, text, textColor);

	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	text_x += 5;

	SDL_Rect textRect = {(int)text_x % (int)(WINDOW_WIDTH+textSurface->w) - textSurface->w, WINDOW_HEIGHT*5/6, textSurface->w, textSurface->h}; // rectangle where the text is drawn 
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	
	SDL_RenderPresent( renderer );
}

void deInitSDL2(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}