#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <dirent.h>

//DEFINITIONS
#define CHUNK_SIZE 65536    

#define MAX_FILES 100
#define MAX_FILENAME 512

//SDL AUDIO
extern SDL_AudioSpec        wav_spec;
extern Uint8                *wav_buffer;
extern Uint32               wav_length;
extern SDL_AudioDeviceID    deviceId;

extern Uint32               wav_position;

//FILE IO
extern struct dirent        *de; 
extern DIR                  *dr;

//FUCTIONS
int audioInit();

int loadTrack(int currentTrack);

void updateAudio(int frq_cmp[]);

void deInitAudio();

