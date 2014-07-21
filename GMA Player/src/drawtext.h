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

#ifndef __DRAWTEXT_H__
#define __DRAWTEXT_H__

#include <sdl.h>

#define FT_COLOR_BLACK  0
#define FT_COLOR_WHITE  1
#define FT_COLOR_YELLOW 2

void SetFontColor( int color );
void DrawText( SDL_Surface *surface, int x, int y, char *fmt, ... );
SDL_Surface *CreateTrueTypeStringSurface( char *fmt, ... );

#endif
