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

#ifndef __FILEDIALOG_H__
#define __FILEDIALOG_H__

bool MovePath(char *path);
int OpenFileDialog( SDL_Surface *surface, char *path, char *filename, char *result );
void DrawBlendRect( SDL_Surface *surface, int x, int y, int w, int h, int type );
void GetNextFile( char *result );

#endif
