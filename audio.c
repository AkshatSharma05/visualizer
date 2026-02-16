#include "audio.h"

#define CHUNK_SIZE 65536    

SDL_AudioSpec wav_spec;
Uint8 *wav_buffer;
Uint32 wav_length;

SDL_AudioDeviceID deviceId;

Uint32 wav_position = 0;

int audioInit(){
    if (SDL_LoadWAV("music/techno.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
        printf("Failed to load WAV\n");
        return 1;
    } 
    
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    // SDL_QueueAudio(deviceId, wav_buffer, wav_length);
    SDL_PauseAudioDevice(deviceId, 0);

    return 0;
}

void updateAudio(int frq_cmp[]){
    if (wav_position < wav_length) {
        if (SDL_GetQueuedAudioSize(deviceId) < CHUNK_SIZE * 4) {

            Uint32 remaining = wav_length - wav_position;
            Uint32 chunk = remaining > CHUNK_SIZE ? CHUNK_SIZE : remaining;

            SDL_QueueAudio(deviceId, wav_buffer + wav_position, chunk);

            int16_t *samples = (int16_t*)(wav_buffer + wav_position);
            int sample_count = chunk / sizeof(int16_t);

            for (int i = 0; i < 20; i++)
                frq_cmp[i] = 0;

            for (int i = 0; i < sample_count && i < 20; i++)
                frq_cmp[i] = abs(samples[i]) / 1000; 

            wav_position += chunk;
        }
    }
}

void deInitAudio(){
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wav_buffer);
}