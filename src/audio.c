#include "audio.h"

//SDL AUDIO
SDL_AudioSpec       wav_spec;
Uint8               *wav_buffer;
Uint32              wav_length;

SDL_AudioDeviceID   deviceId;

Uint32              wav_position = 0;

//FILE IO
struct dirent       *de;  
DIR *dr = NULL;

char files[MAX_FILES][MAX_FILENAME] = {};
int file_count = 0;
    
int current_track = 0;


//Load a music file
int loadTrack(int current_track){
    if (deviceId) {
        SDL_CloseAudioDevice(deviceId);
        deviceId = 0;
    }
    if (wav_buffer) {
        SDL_FreeWAV(wav_buffer);
        wav_buffer = NULL;
        wav_length = 0;
        wav_position = 0;
    }

    char fullpath[1024];

    snprintf(fullpath, sizeof(fullpath), "music/%s", files[current_track]);

    if (SDL_LoadWAV(fullpath, &wav_spec, &wav_buffer, &wav_length) == NULL) {
        printf("Failed to load WAV\n");
        return 1;
    } 
    
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
    SDL_PauseAudioDevice(deviceId, 0);
    return 0;
}

// initialize audio
int audioInit(){
    dr = opendir("music");

    if (dr == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }

    while ((de = readdir(dr)) != NULL){
        if (strcmp(de->d_name, ".") != 0 &&
            strcmp(de->d_name, "..") != 0 && (file_count < MAX_FILES))
        {
            printf("%s\n", de->d_name);

            strncpy(files[file_count], de->d_name, MAX_FILENAME - 1);
            files[file_count][MAX_FILENAME - 1] = '\0'; 
            file_count++;
        }
    }

    loadTrack(current_track);
    
    return 0;
}
    
//audio loop
void updateAudio(int frq_cmp[]){
    if (wav_position < wav_length) {
        if (SDL_GetQueuedAudioSize(deviceId) < CHUNK_SIZE * 2) {
            
            Uint32 remaining = wav_length - wav_position;
            Uint32 chunk = remaining > CHUNK_SIZE ? CHUNK_SIZE : remaining;
            
            SDL_QueueAudio(deviceId, wav_buffer + wav_position, chunk);
            
            int16_t *samples = (int16_t*)(wav_buffer + wav_position);
            int sample_count = chunk / sizeof(int16_t);
            
            for (int i = 0; i < 20; i++){
                int sum = 0;
                for (int j = i*sample_count/20; j < i * (sample_count/20) + (sample_count/20); j++){
                    sum += abs(samples[j]);
                }
                frq_cmp[i] = (sum/sample_count/20) * 0.5;
            }
            
            wav_position += chunk;
        }
    }
}
    
// deinitialize audio
void deInitAudio(){
    closedir(dr);
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wav_buffer);
}