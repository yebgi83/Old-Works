/* -*- C++ -*-
 * 
 *  MadWrapper.cpp - SMPEG compatible wrapper functions for MAD: Mpeg Audio Decoder
 *
 *  Copyright (c) 2001-2005 Ogapee. All rights reserved.
 *
 *  ogapee@aqua.dti2.ne.jp
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

#include "MadWrapper.h"
#include "mp3engine.h"

static inline unsigned short MadFixedToUshort( mad_fixed_t Fixed )
{
    if (Fixed >= MAD_F_ONE)
        Fixed = MAD_F_ONE - 1;
    else if (Fixed < -MAD_F_ONE)
        Fixed = -MAD_F_ONE;
    Fixed = Fixed >> (MAD_F_FRACBITS-15);
    return ((unsigned short)Fixed);
}

static MAD_WRAPPER* init( SDL_RWops *src )
{
    MAD_WRAPPER *mad = new MAD_WRAPPER;
	struct mad_header header;

    SDL_RWseek( src, 0, SEEK_END );
    mad->length = SDL_RWtell( src );
    SDL_RWseek( src, 0, SEEK_SET );

    mad->src = src;

	mad_stream_init( &mad->Stream );
	mad_frame_init( &mad->Frame );
	mad_synth_init( &mad->Synth );
    mad->volume = 64;
    
    mad->input_buf = new unsigned char[ INPUT_BUFFER_SIZE ];
    mad->output_buf = new unsigned char[ 1152*4*5 ]; /* 1152 because that's what mad has as a max; *4 because */
    mad->output_buf_index = 0;

    memset(bar_heights, 0, sizeof(bar_heights));

    mad->is_playing = true;
    MAD_WRAPPER_playAudio(mad, NULL, DEFAULT_AUDIOBUF);

	mad->bitrate = mad->Frame.header.bitrate;
	mad->freq = mad->Frame.header.samplerate;
	
	mad->bytepersec = mad->freq * 4;

	mad->is_playing = false;
    mad->output_buf_index = 0;
    mad->current_out = 0;

    return mad;
}

MAD_WRAPPER* MAD_WRAPPER_new( const char *file, void* info, int sdl_audio )
{
    SDL_RWops *src;

    src = SDL_RWFromFile( file, "rb" );
    if ( !src ) return NULL;

    return init( src );
}

MAD_WRAPPER* MAD_WRAPPER_new_rwops( SDL_RWops *src, void* info, int sdl_audio )
{
    return init( src );
}

int MAD_WRAPPER_playAudio( void *userdata, Uint8 *stream, int len )
{
    MAD_WRAPPER *mad = (MAD_WRAPPER*)userdata;

    if ( !mad->is_playing ) return -1; // pause
    
    size_t         ReadSize = 1, Remaining;
    unsigned char  *ReadStart;

    do{
        if( mad->Stream.buffer==NULL || mad->Stream.error==MAD_ERROR_BUFLEN ){
    
            if ( mad->Stream.next_frame != NULL ){
                Remaining = mad->Stream.bufend - mad->Stream.next_frame;
                memmove( mad->input_buf, mad->Stream.next_frame, Remaining);
                ReadStart = mad->input_buf + Remaining;
                ReadSize  = INPUT_BUFFER_SIZE - Remaining;
            }
            else{
                ReadSize  = INPUT_BUFFER_SIZE;
                ReadStart = mad->input_buf;
                Remaining = 0;
            }

            ReadSize = SDL_RWread( mad->src, ReadStart, 1, ReadSize );
            if ( ReadSize <= 0 ) break; // end of stream

            mad_stream_buffer( &mad->Stream, mad->input_buf, ReadSize + Remaining );
            mad->Stream.error = MAD_ERROR_NONE;
        }

        if ( mad_frame_decode( &mad->Frame,&mad->Stream ) ){
            if ( MAD_RECOVERABLE( mad->Stream.error ) ||
                 mad->Stream.error == MAD_ERROR_BUFLEN ){
                continue;
            }
            else{
                fprintf( stderr, "unrecoverable frame level error (%s).\n",
                         mad_stream_errorstr(&mad->Stream) );
                return 0; // error
            }
        }

		{
			unsigned int nch, ch, ns, s, sb;
			mad_fixed_t table[NUM_BANDS];
			static unsigned char const map[32] = {
				0, 1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
				8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
			};

			//nch = MAD_NCHANNELS(&mad->Frame.header);
			ns  = MAD_NSBSAMPLES(&mad->Frame.header);

			for (sb = 0; sb < NUM_BANDS; ++sb) {
				table[sb] = 0;
			}

			for (s = 0; s < ns; ++s) {
				for (sb = 0; sb < 32; ++sb) {
					if(table[map[sb]] < mad->Frame.sbsample[0][s][sb])
						table[map[sb]] = mad->Frame.sbsample[0][s][sb];
				}
			}

			for (sb = 0; sb < NUM_BANDS; ++sb) {
				unsigned short num = bar_height[MadFixedToUshort(table[sb]) >> 6];

				if(num > bar_heights[sb])
					bar_heights[sb] = num;
				else if(bar_heights[sb] > 1)
					bar_heights[sb] -= 1;
				else
					bar_heights[sb] = 0;
			}
		}

#if defined(PDA) && !defined(PSP)
        if ( mad->Frame.header.samplerate == 44100 )
            mad->Frame.options |= MAD_OPTION_HALFSAMPLERATE;
#endif
        mad_synth_frame( &mad->Synth, &mad->Frame );
    
        char *ptr = (char*)mad->output_buf + mad->output_buf_index;

        for ( int i=0 ; i<mad->Synth.pcm.length ; i++ ){
            unsigned short	Sample;

            /* Left channel */
            Sample=MadFixedToUshort( mad->Synth.pcm.samples[0][i] );
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            *(ptr++) = Sample & 0xff;
            *(ptr++) = Sample >> 8;
#else
            *(ptr++) = Sample >> 8;
            *(ptr++) = Sample & 0xff;
#endif

            /* Right channel, if exist. */
            if ( MAD_NCHANNELS(&mad->Frame.header)==2 )
                Sample=MadFixedToUshort( mad->Synth.pcm.samples[1][i] );
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
            *(ptr++) = Sample & 0xff;
            *(ptr++) = Sample >> 8;
#else
            *(ptr++) = Sample >> 8;
            *(ptr++) = Sample&0xff;
#endif
        }
        mad->output_buf_index += mad->Synth.pcm.length * 4;
    }
    while( mad->output_buf_index < len );

    if ( ReadSize <= 0 ) return 0; // end of stream
    
    if ( stream == NULL ) {
		// skip...
	} else if ( mad->output_buf_index > len ){
        //SDL_MixAudio( stream, mad->output_buf, len, mad->volume );
        memmove( stream, mad->output_buf, len);
        memmove( mad->output_buf, mad->output_buf + len, mad->output_buf_index - len );
        mad->output_buf_index -= len;
    } else {
        //SDL_MixAudio( stream, mad->output_buf, mad->output_buf_index, mad->volume );
        memmove( stream, mad->output_buf, mad->output_buf_index);
        len = mad->output_buf_index;
        mad->output_buf_index = 0;
    }

    mad->current_out += len;

    return len;
}

void MAD_WRAPPER_restart( MAD_WRAPPER *mad )
{
    SDL_RWseek( mad->src, 0, SEEK_SET );
    mad->current_out = 0;
}

void MAD_WRAPPER_play( MAD_WRAPPER *mad )
{
    mad->is_playing = true;
}

void MAD_WRAPPER_stop( MAD_WRAPPER *mad )
{
    mad->is_playing = false;
}

void MAD_WRAPPER_delete( MAD_WRAPPER *mad )
{
	mad_synth_finish( &mad->Synth );
	mad_frame_finish( &mad->Frame );
	mad_stream_finish( &mad->Stream );

    delete[] mad->input_buf;
    delete[] mad->output_buf;
    SDL_FreeRW( mad->src );
    delete mad;
}

void MAD_WRAPPER_setvolume( MAD_WRAPPER *mad, int volume )
{
    if ( (volume >= 0) && (volume <= 100) ) {
        mad->volume = (volume*SDL_MIX_MAXVOLUME) / 100;
    }
}

const char* MAD_WRAPPER_error( MAD_WRAPPER *mad )
{
    if ( mad ) return NULL;
    return "Mad open error";
}

void MAD_WRAPPER_Back( MAD_WRAPPER *mad, int level )
{
    SDL_RWseek( mad->src, INPUT_BUFFER_SIZE * level * -1, SEEK_CUR );
}

void MAD_WRAPPER_Forward( MAD_WRAPPER *mad, int level )
{
    SDL_RWseek( mad->src, INPUT_BUFFER_SIZE * level, SEEK_CUR );
}

#if defined(DEBUG_MAD)
void mp3callback( void *userdata, Uint8 *stream, int len )
{
    if ( MAD_WRAPPER_playAudio( userdata, stream, len ) == 0 ){
        printf("end of file\n");
        exit(0);
    }
}

int main(void)
{
	if ( SDL_Init( SDL_INIT_TIMER | SDL_INIT_AUDIO ) < 0 ){
		fprintf(stderr,
			"Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

    SDL_AudioSpec audio_format;

    MAD_WRAPPER *mad = MAD_WRAPPER_new( "travel.mp3", NULL, 0 );
    
    MAD_WRAPPER_play( mad );
    Mix_HookMusic( mp3callback, mad );

    if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, DEFAULT_AUDIOBUF ) < 0 ){
        fprintf(stderr, "Couldn't open audio device!\n"
                "  reason: [%s].\n", SDL_GetError());
        exit(-1);
    }
    else{
        int freq;
        Uint16 format;
        int channels;

        Mix_QuerySpec( &freq, &format, &channels);
        printf("Audio: %d Hz %d bit %s\n", freq,
               (format&0xFF),
               (channels > 1) ? "stereo" : "mono");
        audio_format.format = format;
        audio_format.freq = freq;
        audio_format.channels = channels;
    }

    getchar();
    MAD_WRAPPER_stop( mad );
    MAD_WRAPPER_delete( mad );
}
#endif 
