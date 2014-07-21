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

#ifndef _SDL_H
#include <sdl.h>
#endif

#include <UnicodeFont.h>
#include <stdarg.h>

static char *DefErrMsgSection = "[FreeType2 Custom]";
#ifndef DECLARE_ERRMSG
   #define ERRMSG( condition, msg ) if( condition ){ fprintf( stderr, "%s %s\n", DefErrMsgSection, msg); exit(3); }
   #define DECLARE_ERRMSG
#endif

#define FT_COLOR_BLACK  0
#define FT_COLOR_WHITE  1
#define FT_COLOR_YELLOW 2
#define FT_CREATE_COLOR_TABLE( count, tr, tg, tb ) for( count = 1; count < 256; i ++ ) { FontColor[count].r = tr; FontColor[count].g = tg; FontColor[count].b = tb; }

const short FontSize = 12;
unsigned short fontcolor = 0xFFFF;

void SetFontColor( int color )
{
    switch( color )
    {
        case FT_COLOR_BLACK:
			fontcolor = 0x0000;
			break;
        case FT_COLOR_WHITE:
			fontcolor = 0xFFFF;
			break;
        case FT_COLOR_YELLOW:
			fontcolor = 0xFFE0;
			break;
    }
}

unsigned short getCode(unsigned char **str)
{
	int i, j;
	unsigned short ch;
	unsigned char *s = *str;

	ch = *s++;
	if ( ch >= 0xF0 ) {
		ch  =  (ch & 0x07) << 18;
		ch |=  (*s++ & 0x3F) << 12;
		ch |=  (*s++ & 0x3F) << 6;
		ch |=  (*s++ & 0x3F);
	} else if ( ch >= 0xE0 ) {
		ch  =  (ch & 0x0F) << 12;
		ch |=  (*s++ & 0x3F) << 6;
		ch |=  (*s++ & 0x3F);
	} else if ( ch >= 0xC0 ) {
		ch  =  (ch & 0x1F) << 6;
		ch |=  *s++ & 0x3F;
	}
	
	*str = s;
	return ch;
}

void DrawText( SDL_Surface *surface, int x, int y, char *fmt, ... )
{
    int n, error;
    char text[256];
    unsigned char *pt;
    unsigned short font[16];
    int w, h;
    unsigned short c;
    unsigned short *buf;
    int pitch;

    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);
    
    pt = (unsigned char*)text;
    buf = (unsigned short*)surface->pixels;
    pitch = surface->pitch >> 1;
    buf += (y * pitch) + x;
    while(*pt != 0)
    {
		c = getCode(&pt);
		GetFont(c, font, &h, &w);
		if((x + w) >= surface->w) break;

		for(int cy=0; cy<h; cy++)
		{
			unsigned short *scr = buf + (cy * pitch);
			for(int cx=0; cx<w; cx++)
			{
				if(font[cy] & (0x8000 >> cx))
				{
					scr[cx] = fontcolor;
				}
			}
		}

		buf += w;
		x += w;
    }
}

void _GetTrueTypeStringSize( int *w, int *h, char *fmt, ... )
{
    int n, error;
    char text[256];
    unsigned char *pt = (unsigned char*)text;
    unsigned short font[16];
    unsigned short c;
    *w = *h = 0;
    
    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);

    int fw, fh;
    while(*pt != 0)
    {
		c = getCode(&pt);
		GetFont(c, font, &fh, &fw);
		*w += fw;
		if(*h < fh) *h = fh;
    }
}
 
SDL_Surface *CreateTrueTypeStringSurface( char *fmt, ... )
{
    int w, h;
    char text[256];
    SDL_Surface *ttsurface;

    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);
    
    _GetTrueTypeStringSize( &w, &h, text );
    
    // 16bit mask
    // 1111 1000 0000 0000
    // 0000 0111 1110 0000
    // 0000 0000 0001 1111

    w += 2;
    h = FontSize + 2;
    ttsurface = SDL_CreateRGBSurface( SDL_SWSURFACE, 
                                      w, h, 16,
                                      0xf800,
                                      0x07e0,
                                      0x001f,
                                      0x0000 );

    DrawText( ttsurface, 0, 0, text );
    return( ttsurface );                                      
}            
