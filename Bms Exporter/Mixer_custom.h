#include<SDL.h>
#include<SDL_audio.h>
#include<SDL_mixer.h>

#define MIXER_MAX_CHANNELS 128

void InitMixer( void )
{
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    Mix_AllocateChannels(MIXER_MAX_CHANNELS);
}

void RemoveMixer( void )
{
    Mix_CloseAudio();
}

void Mixer_Play( Mix_Chunk *pMixChunk )
{
    int result;
    result = Mix_PlayChannel( -1, pMixChunk, 0);
    Mix_Volume( result, 100 );
}

void Mixer_PlayEx( Mix_Chunk *pMixChunk, int volume, int groupnum )
{
    int result;
    result = Mix_PlayChannel( -1, pMixChunk, groupnum );
    Mix_Volume( result, volume ); 
    Mix_GroupChannel( result, groupnum );
}
