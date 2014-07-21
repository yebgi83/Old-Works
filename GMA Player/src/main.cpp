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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iconv.h>
#include <SDL.h>
#ifdef GP2X
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>
#endif

#include "drawtext.h"
#include "filedialog.h"
#include "mp3engine.h"
#include "lyrics.h"
#include "player.h"

/* GP2X button mapping */
enum MAP_KEY
{
	VK_UP         , // 0
	VK_UP_LEFT    , // 1
	VK_LEFT       , // 2
	VK_DOWN_LEFT  , // 3
	VK_DOWN       , // 4
	VK_DOWN_RIGHT , // 5
	VK_RIGHT      , // 6
	VK_UP_RIGHT   , // 7
	VK_START      , // 8
	VK_SELECT     , // 9
	VK_FL         , // 10
	VK_FR         , // 11
	VK_FA         , // 12
	VK_FB         , // 13
	VK_FX         , // 14
	VK_FY         , // 15
	VK_VOL_UP     , // 16
	VK_VOL_DOWN   , // 17
	VK_TAT          // 18
};

#ifdef GP2X
#define MAX_PATH 1024
#endif

int volume = 70;

/* The screen surface */
SDL_Surface *screen = NULL;

void Terminate(void)
{
	MP3_Deinit();
	SDL_Quit();
#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}

bool SetVolume()
{
	if(volume < 0) volume = 0;
	if(volume > 100) volume = 100;
#ifdef GP2X
	int fd;
	if ((fd = open("/dev/sound/mixer", O_RDONLY)) >= 0)
	{
		int devs;
		if(ioctl(fd, SOUND_MIXER_READ_DEVMASK, &devs) != -1) {
			if (devs & (1 << SOUND_MIXER_PCM))
			{
				int vol = (int)(volume * 0.8);
				int v = (vol << 8) | vol;
				ioctl(fd, MIXER_WRITE(SOUND_MIXER_PCM), &v);
			}
		}
		close(fd);
	} else {
		return false;
	}
#endif
	return true;
}

void DrawSpectrum( void )
{
    static int coltable[35][3] = { {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 0, 0 },
                                   {31, 6, 0 },
                                   {31,12, 0 },
                                   {31,18, 0 },
                                   {31,24, 0 },
                                   {31,30, 0 },
                                   {31,36, 0 },
                                   {31,42, 0 },
                                   {31,48, 0 },
                                   {31,54, 0 },
                                   {31,63, 0 },
                                   {28,63, 0 },
                                   {24,63, 0 },
                                   {20,63, 0 },
                                   {16,63, 0 },
                                   {12,63, 0 },
                                   { 8,63, 0 },
                                   { 4,63, 0 },
                                   { 0,54, 0 },
                                   { 0,48, 0 },
                                   { 0,42, 4 },
                                   { 0,36, 8 },
                                   {31,30,12 },
                                   {31,24,16 },
                                   {31,18,20 },
                                   {31,12,24 },
                                   {31, 6,28 },
                                   {31, 0,31 } };

	int i, c, c2;
	int y;

    SDL_Rect rect = { 0, 30, 2, 5 };
	
	for(i = 0; i < NUM_BANDS; i++)
	{
		y = bar_heights[i];
	
        rect.x = 318;
        for( c2 = 0; c2 < y; c2++ )
        {
            int colidx;
            rect.x -= 3;
            rect.w = 2;
            rect.h = 5;
            if( c2 > 34 ) colidx = 34; else colidx = c2;
            SDL_FillRect( screen, &rect, coltable[colidx][0] << 11 | coltable[colidx][1] << 5 | coltable[colidx][2] );
        }
        rect.y += 9;
	}
}

bool ViewPlaying( char *filename )
{
    int done = 0;
    int before_current_time = -1;
    int viewstart = 0;
    SDL_Surface *title;
    SDL_Rect titlerect;
    SDL_Rect screenrect;
    unsigned int nowtick, eventtick, titletick, termtick;
    int count;
    bool titleupdate = true;
    bool statusupdate = true;
    int dir;
	int key, keydown;
    int joytokey[32];
	SDL_Event event;

#ifndef GP2X
	iconv_t iconvobj = iconv_open ( "utf-8", "uhc" );
	char convtext[1024];
	const char *ptext = strrchr(filename, '/');
	char *pconvtext = convtext;
	size_t textlen;
	size_t convlen = 1024;

	if(ptext == NULL)
		ptext = filename;
	else
		ptext++;
	textlen = strlen(ptext);

    iconv( iconvobj, &ptext, &textlen, &pconvtext, &convlen );
    pconvtext -= 4;
    *pconvtext = 0;

    title = CreateTrueTypeStringSurface( convtext );
    iconv_close (iconvobj);
#else
	char titletext[512];
	char *find = strrchr(filename, '/');
	if(find == NULL) {
		find = filename;
	} else {
		find++;
	}
	strcpy(titletext, find);
	find = strrchr(titletext, '.');
	if(find != NULL) *find = 0;
    title = CreateTrueTypeStringSurface( titletext );
#endif

	screenrect.x = 0;
	screenrect.y = 2;
	if(title && (title->w > 320)) {
		titlerect.x = -1;dir = 1;
		titlerect.y = 0;
		titlerect.w = 320;
		titlerect.h = title->h;
		titletick = SDL_GetTicks() - 50;
		DrawBlendRect( title, 0, 0, title->w, title->h, 4 );
	} else {
		titletick = 0;
	}

	eventtick = 0;	
	termtick = 0;

	keydown = 0;
    memset(joytokey, 0, sizeof(joytokey));

    joytokey[VK_LEFT] = SDLK_LEFT;
    joytokey[VK_RIGHT] = SDLK_RIGHT;
    joytokey[VK_UP] = SDLK_UP;
    joytokey[VK_DOWN] = SDLK_DOWN;
    joytokey[VK_FX] = SDLK_ESCAPE;
    joytokey[VK_VOL_UP] = SDLK_KP_PLUS;
    joytokey[VK_VOL_DOWN] = SDLK_KP_MINUS;

    SetVolume();

    while (!done)
  	{
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_JOYBUTTONDOWN:
					key = joytokey[event.jbutton.button];
					if(key == 0) break;
				case SDL_KEYDOWN:
					if(event.type == SDL_KEYDOWN)
	                    key = event.key.keysym.sym;
	                switch(key) {
						case SDLK_UP:
						case SDLK_DOWN:
                        case SDLK_LEFT:
                        case SDLK_RIGHT:
							keydown = key;
							count = 1;
							eventtick = SDL_GetTicks();
							break;
						case SDLK_KP_PLUS:
						case SDLK_KP_MINUS:
							volume += (key == SDLK_KP_PLUS) ? 5 : -5;
							statusupdate = SetVolume();
							break;
						case SDLK_ESCAPE:
							done = 1;
							break;
					}
					break;
				case SDL_JOYBUTTONUP:
					key = joytokey[event.jbutton.button];
	            case SDL_KEYUP:
					if(event.type == SDL_KEYUP)
	                    key = event.key.keysym.sym;
	                if(key == keydown) keydown = 0;
					break;
				case SDL_QUIT:
	                done = 1;
		       	    break;
		       	case EVENT_SONG_END:
					termtick = SDL_GetTicks() + 1000;
					break;
				default:
			        break;
			}
		}

		nowtick = SDL_GetTicks();
		if( (termtick != 0) && (termtick < nowtick) ) {
			done = -1;
			break;
		}

		if( (eventtick != 0) && (eventtick <= nowtick) ){
			switch(keydown) {
				case SDLK_UP:
					if( viewstart > 0 ) viewstart--;
					break;
				case SDLK_DOWN:
					if( viewstart + 14 + 1 < GetNumOfLyrics() ) viewstart++;
					break;
				case SDLK_LEFT:
                    MP3_PlayBack( 1 );
                    break;
                case SDLK_RIGHT:
                    MP3_PlayForward( 1 );
                    break;
				default:
					eventtick = 0;
					break;
			}
			if(count > 0) {
				eventtick += 150;
				count--;
			} else {
				eventtick += 70;
			}
		}

        if((titletick != 0) & (titletick <= nowtick)) {
			titlerect.x += dir;
			if((title->w - titlerect.x) < 320) {
				titlerect.x--;
				dir = -1;
			}
			if(titlerect.x < 0) {
				titlerect.x = 0;
				dir = 1;
			}
			titlerect.y = 0;
			titlerect.w = 320;
			titlerect.h = title->h;
			titletick += 50;

			SDL_Rect clear = {0, 0, 320, 14};
			SDL_FillRect(screen, &clear, 0);

			SDL_BlitSurface(title, &titlerect, screen, &screenrect);
			SDL_UpdateRect( screen, 0, 0, 320, 14 );
		} else if((titletick == 0) && titleupdate) {
			SDL_Rect clear = {0, 0, 320, 14};
			SDL_FillRect(screen, &clear, 0);

			SDL_BlitSurface(title, NULL, screen, &screenrect);
			DrawBlendRect( screen, 0, 0, 320, 14, 4 );
			SDL_UpdateRect( screen, 0, 0, 320, 14 );
			titleupdate = false;
		}

        int ctime = (int)MP3_GetCurrentTime();
        if( before_current_time != ctime )
        {
            before_current_time = ctime;
            statusupdate = true;
        }

        if(statusupdate) 
        {
            SDL_Rect clear = {0, 226, 320, 14};
   		    SDL_FillRect(screen, &clear, 0);
   		    
            int min = ctime / 60;
            int sec = ctime % 60;
            DrawText( screen, 80, 228, "%.2d:%.2d", min, sec );

            DrawText( screen, 3, 228, "Playing..." );
	        DrawText( screen, 260, 228, "Vol: %3d", volume );
			 
	   	    statusupdate = false;
            DrawBlendRect( screen, 0, 226, 320, 14, 2 );
            SDL_UpdateRect( screen, 0, 226, 320, 14 );
        }
    
	    SDL_Rect clear = {0, 14, 320, 212};
    	SDL_FillRect( screen, &clear, 0 );

		DrawSpectrum();

		if( IsLyricExist() == 0 ) {
			DrawText( screen, 95, 110, "Lyrics not found." );
		} else {
			viewstart = DrawEntireLyrics( screen, 0, 18, viewstart );
		}

		SDL_UpdateRect( screen, 0, 14, 320, 212 );
	}

	SDL_FreeSurface(title);
	return done != 1;
}

int main (int argc, char *argv[])
{
	/* Initialize SDL */
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0) {
		fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
		exit (1);
	}
	atexit (Terminate);

#ifdef GP2X
	SDL_ShowCursor(SDL_DISABLE);
#else
	SDL_WM_SetCaption("gmaplayer", NULL);
#endif

	/* Set 320x240 16-bits video mode */
	screen = SDL_SetVideoMode (320, 240, 16, SDL_SWSURFACE );
	if (screen == NULL) {
		fprintf (stderr, "Couldn't set 320x240x16 video mode: %s\n", SDL_GetError ());
		exit (2);
	}
	
	/* Check and open joystick device */
	if (SDL_NumJoysticks() > 0) {
		SDL_JoystickOpen(0);
	}

    MP3_Init();
    bool next = false;
	char filename[MAX_PATH];

#ifdef GP2X
	bool moved = MovePath("/mnt/sd/Music");
	if(!moved) moved = MovePath("/mnt/sd/music");
	if(!moved) moved = MovePath("/mnt/sd/MUSIC");
	if(!moved) moved = MovePath("/mnt/sd/mp3");
	if(!moved) moved = MovePath("/mnt/sd/MP3");
#endif

    while(1)
    {
		if(next) {
			GetNextFile( filename );
		} else if(!OpenFileDialog( screen, NULL, ".mp3", filename ) ) {
			break;
		}

        GetLyricsFromFile( filename );
        MP3_OpenMediaFile( filename );
        MP3_SetMediaRepeatMode( true );
        MP3_MediaPlayStart();
		LyricsTimerStart();
        next = ViewPlaying( filename );
        MP3_CloseMediaFile();
        LyricsTimerStop();
    }        
	return 0;
}
