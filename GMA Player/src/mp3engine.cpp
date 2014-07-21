/*
 *  GMA Player - Lyric supported MP3 player
 *
 *  Copyright (c) 2006 gma, nightknight. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <SDL.h>
#include <math.h>
#include "player.h"
#include "mp3engine.h"
#include "MadWrapper.h"

MAD_WRAPPER *pMadObj = NULL;
short bar_heights[NUM_BANDS];

int MP3_IsUsed = 0;
int MP3_IsLoop = 0;
int MP3_IsPlay = 0;

int bar_height[1024];
static bool state = false;

SDL_AudioSpec audio_spec;
SDL_mutex *sound_mutex;
#define EnterSound() SDL_LockMutex(sound_mutex)
#define LeaveSound() SDL_UnlockMutex(sound_mutex)

float MP3_GetEndTime( void )
{
    if( MP3_IsUsed  )
		return pMadObj->length / pMadObj->bytepersec;

	return -1;
}

float MP3_GetCurrentTime( void )
{
    if( MP3_IsUsed && MP3_IsPlay )
		return pMadObj->current_out / pMadObj->bytepersec;

	return -1;
}

void MP3_CallBack( void *parg, Uint8 *stream, int len )
{
	EnterSound();
	if( (MP3_IsPlay) && (pMadObj) ){
	    if ( MAD_WRAPPER_playAudio( pMadObj, stream, len ) == 0 ) {
			SDL_Event event;
		    event.type = EVENT_SONG_END;
		    SDL_PushEvent(&event);
		    MP3_IsPlay = 0;
		}
	}
    LeaveSound();
}

void MP3_Init( void )
{
	if(!state) {
		int i;
		double scale = 34 / log(512);
		state = true;
		bar_height[0] = 0;
		for(i=1;i<1024;i++) {
			bar_height[i] = (int)(log(i) * scale);
			if(bar_height[i] > 34)
				bar_height[i] = 34;
		}

		MP3_IsPlay = 0;
		sound_mutex = SDL_CreateMutex();

		audio_spec.format = AUDIO_S16;
		audio_spec.channels = 2;
		audio_spec.freq = 44100;
		audio_spec.samples = DEFAULT_AUDIOBUF;

		audio_spec.callback = MP3_CallBack;
		audio_spec.userdata = NULL;
	
		if (SDL_OpenAudio(&audio_spec, NULL) < 0) {
			fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		} else {
			SDL_PauseAudio(1);
		}
	}
}

void MP3_OpenMediaFile( char *filename )
{
	if(pMadObj) MP3_CloseMediaFile();
    pMadObj = MAD_WRAPPER_new( filename, NULL, 0 );
    
    if(pMadObj->freq != audio_spec.freq) {
		SDL_CloseAudio();

		audio_spec.format = AUDIO_S16;
		audio_spec.channels = 2;
		audio_spec.freq = pMadObj->freq;
		audio_spec.samples = DEFAULT_AUDIOBUF;
		if(audio_spec.freq < 30000)
			audio_spec.samples >>= 1;

		audio_spec.callback = MP3_CallBack;
		audio_spec.userdata = NULL;
		
		printf("freq: %d, channels: %d\n", audio_spec.freq, audio_spec.channels);
		
		if (SDL_OpenAudio(&audio_spec, NULL) < 0) {
			fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		} else {
			SDL_PauseAudio(1);
		}
	}

    MP3_IsUsed = 1;
	LeaveSound();
}

void MP3_MediaPlayStart( void )
{
	if( (!MP3_IsPlay) && (pMadObj) ){
		EnterSound();
	    MP3_IsPlay = 1;
	    MAD_WRAPPER_play( pMadObj );
		SDL_PauseAudio(0);
		LeaveSound();
	}
}
 
void MP3_MediaPlayStop( void )
{
	EnterSound();
    if( pMadObj ) MAD_WRAPPER_stop( pMadObj );
    MP3_IsPlay = 0;
    SDL_PauseAudio(1);
    LeaveSound();
}
 
void MP3_SetMediaRepeatMode( int sw )
{
    MP3_IsLoop = sw;
}

void MP3_CloseMediaFile()
{
	MP3_MediaPlayStop();
	EnterSound();
    if( pMadObj != NULL ) MAD_WRAPPER_delete( pMadObj );
    pMadObj = NULL;
    MP3_IsUsed = 0;
    LeaveSound();
}

void MP3_Deinit()
{
	MP3_CloseMediaFile();
	SDL_DestroyMutex(sound_mutex);
	SDL_CloseAudio();
}

void MP3_PlayBack( int level )
{
    if( MP3_IsUsed ) MAD_WRAPPER_Back( pMadObj, level );
}

void MP3_PlayForward( int level )
{
    if( MP3_IsUsed ) MAD_WRAPPER_Forward( pMadObj, level );
}
