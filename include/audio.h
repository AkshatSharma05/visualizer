#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

extern SDL_AudioSpec wav_spec;
extern Uint8 *wav_buffer;
extern Uint32 wav_length;
extern SDL_AudioDeviceID deviceId;

extern Uint32 wav_position;

int audioInit();
void deInitAudio();

