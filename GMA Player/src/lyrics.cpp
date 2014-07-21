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
#include <iconv.h>
#include <sdl.h>
#include <list>

#include "mp3engine.h"
#include "drawtext.h"
#include "filedialog.h"

using namespace std;

typedef struct
{
    int            contentsize;
    char           ldbid[16];
    unsigned long  basetick;
} LDBHeader;

typedef struct
{
    float  tick;
    char   text[256];
}Lyric;

int LyricsFound = 0;
int LyricsCallBackUseable = 0;
SDL_TimerID LyricsViewTimerID = 0;

int NumOfCurPlayingLyric = 0;
int NumOfCurPlayingLyricBegin = -1;
int NumOfCurPlayingLyricEnd = -1;
int NumOfLyrics = 0;

list<Lyric> Lyrics;
list<Lyric>::iterator CurrLyric;
list<Lyric>::iterator NextLyric;

unsigned char GetChar( FILE *fp )
{
    return fgetc(fp);
}

unsigned long GetLongAsBigEndian( FILE *fp )
{
    int v1 = fgetc(fp) << 24;
    int v2 = fgetc(fp) << 16;
    int v3 = fgetc(fp) << 8;
    int v4 = fgetc(fp);
    return v1 + v2 + v3 + v4;
}

unsigned long GetBaseTick( FILE *fp )
{
    int v1 = fgetc(fp);
    int v2 = fgetc(fp);
    int v3 = fgetc(fp);
    
    return (v1 & 0x0F) | (( ((v1 >> 4) & 0x01) | ((v2 >> 4) & 0x0E) ) << 4) |
		((v2 & 0x07) << 16) | ((v3 & 0x1f) << 11) | 0x80000;
}

unsigned long GetSyncTick( FILE *fp )
{
    int v1 = fgetc(fp);
    int v2 = fgetc(fp);
    int v3 = fgetc(fp);

    return (v2 & 0x7F) | ((v3 & 0x7F) << 7) | ((v1 & 0x7F) << 14);
}

unsigned short GetShortAsBigEndian( FILE *fp )
{
    int v1 = fgetc(fp) << 8;
    int v2 = fgetc(fp);
    return v1 + v2;
}

unsigned short GetShortAsLittleEndian( FILE *fp )
{
    int v1 = fgetc(fp);
    int v2 = fgetc(fp) << 8;
    return v1 + v2;
}

void AddLyric( float tick, char *text )
{
    Lyric reglyric;
    reglyric.tick = tick;
    strcpy( reglyric.text, text );
    Lyrics.push_back(reglyric);
    NumOfLyrics++;
}

// LDB
bool GetLDBHeader( FILE *fp, LDBHeader *pheader )
{
	char id3hdr[6];
	char id3frame[5];
	int id3size, size;
	unsigned short mark;

	fseek(fp, 0, SEEK_SET);
    fread(id3hdr, 6, 1, fp);
	if(strncmp(id3hdr, "ID3", 3) != 0) return false;
	id3size = GetLongAsBigEndian( fp );
	id3frame[4] = '\0';

	while(id3size > 0) {
		fread(id3frame, 4, 1, fp);
		if(strcmp(id3frame, "USLT") == 0) break;
		if(strcmp(id3frame, "WSLT") == 0) break;
		if(id3frame[0] == '\0') { id3size = -1; break; }
		size = GetLongAsBigEndian( fp );
		if(size > id3size) { id3size = -1; break; }
		fseek(fp, size + 2, SEEK_CUR);
		id3size -= size + 6;
	}

	if(id3size <= 0) return false;

    pheader->contentsize = GetLongAsBigEndian( fp );
	fseek(fp, 6, SEEK_CUR);

	mark = GetShortAsLittleEndian( fp );
	if(mark != 0x29) return false;
    fread( pheader->ldbid, 16, 1, fp );

	mark = GetShortAsLittleEndian( fp );
	if(mark != 0x02) return false;
    pheader->basetick = GetBaseTick( fp );

	fseek( fp, 43, SEEK_CUR);
	pheader->contentsize -= 70;

	return true;
}

void LoadLyricsInLDBFormat( char *filename )
{
    int size;
    char addlyric[1024];
    FILE *fp = fopen( filename, "rb" );
    
    LDBHeader header;

	if( GetLDBHeader( fp, &header) ) {
		size = header.contentsize;
	} else {
		return;
	}

    int loadedlen = 0;
    iconv_t iconvobj = iconv_open ( "utf-8", "unicodelittle" );
    float lasttick = -1;

    while( loadedlen < size )
    {
        unsigned short wtext[256];
        char           convtext[1024];

        unsigned char symbol      = GetShortAsLittleEndian( fp );
        unsigned long synctick    = GetSyncTick( fp ) - header.basetick;

        size_t        wtextlen    = GetChar( fp );
        size_t        convtextlen = 1024;
        
        int tick;
        
        if(( symbol != 8 ) && ( symbol != 7 ))break;

        fread(wtext, wtextlen, 1, fp);

        loadedlen += wtextlen + 6;

        char *pwtext = (char *)wtext;
        char *pconvtext = convtext;
#ifdef GP2X
        iconv( iconvobj, (char **)&pwtext, &wtextlen,  &pconvtext, &convtextlen );
#else
        iconv( iconvobj, (const char **)&pwtext, &wtextlen,  &pconvtext, &convtextlen );
#endif
		*pconvtext = 0;
		
		if(symbol == 8) {
			if(lasttick != -1)
				AddLyric( lasttick / 100, addlyric );
			strcpy(addlyric, convtext);
			lasttick = synctick;
		} else {
			strcat(addlyric, convtext);
		}
    }    
	if(lasttick != -1)
		AddLyric( lasttick / 100, addlyric );
    iconv_close( iconvobj );
    LyricsFound = 1;
    LyricsCallBackUseable = 1;
}
 
// lrc
void LoadLyricsFromLrcFile( char *filename )
{
    int extfound = 0;
    char lrcfilename[256];
  
    strcpy( lrcfilename, filename );
    for( int c = strlen(lrcfilename) - 1; c >= 0; c-- )
    {
        if( lrcfilename[c] == '.' ) 
        {
            if( c + 4 < 256 )
            {
                lrcfilename[c+1] = 'l';
                lrcfilename[c+2] = 'r';
                lrcfilename[c+3] = 'c';
                lrcfilename[c+4] = '\0';
                extfound = 1;
                break;
            }
        }
    }
    if( extfound == 0 ) return;
    
    iconv_t iconvobj = iconv_open ( "utf-8", "uhc" );
    FILE *fp = fopen( lrcfilename, "rb" );
    char loadtext[512];
    char lyrictext[512];
    char convtext[1024];
    float lyrictick = 0;

    if( fp == NULL ) return;
    do
    {
        int c = 0;
        while(1)
        {
            char ch = fgetc(fp);
            if( feof(fp) ) break;
            if( ch == 13 ) 
            {
                fgetc(fp);
                break;
            }
            else
                loadtext[ c++ ] = ch;
        } 
        loadtext[c] = 0;

        int min = 0;
        float sec = 0;
        int lyricstart = 0;
        int failed = 1;        

        for( c = 0; c < strlen(loadtext); c++ )
        {
            if( loadtext[c] == '[' )
            {
				char tmp[10];
				int n;
                c++;n = 0;
                while((loadtext[c] >= '0') && (loadtext[c] <= '9')) {
					tmp[n] = loadtext[c];
					c++;n++;
				}
				if( (n == 0) || (loadtext[c] != ':') ) break;
				tmp[n] = 0;
				min = atoi(tmp);

                c++;n = 0;
                while( ((loadtext[c] >= '0') && (loadtext[c] <= '9')) || (loadtext[c] == '.') ) {
					tmp[n] = loadtext[c];
					c++;n++;
				}
				if( (n == 0) || (loadtext[c] != ']') ) break;
				tmp[n] = 0;
				sec = atof(tmp);

                failed = 0;
                lyricstart = c + 1;
                break;
            }
        }

        if( failed == 0 ) {
            lyrictext[ strlen(loadtext) - lyricstart ] = '\0';
            strncpy( lyrictext, &(loadtext[lyricstart]), strlen(loadtext) - lyricstart );
            lyrictick = 60 * min + sec;
            LyricsCallBackUseable = 1;
        } else {
			lyrictick = 0;
			strcpy(lyrictext, loadtext);
		}
		
        char *plyrictext = lyrictext;
        char *pconvtext = convtext;
        size_t lyriclen = strlen(lyrictext);
        size_t convtextlen = 1024;
#ifdef GP2X
        iconv( iconvobj, (char **)&plyrictext, &lyriclen,  &pconvtext, &convtextlen );
#else
        iconv( iconvobj, (const char **)&plyrictext, &lyriclen,  &pconvtext, &convtextlen );
#endif
		*pconvtext = 0;
		
        AddLyric( lyrictick, convtext );
    }while(!feof(fp));

    iconv_close( iconvobj );
    fclose(fp);
    LyricsFound = 1;
}

int GetLyricsFromFile( char *filename ) 
{
    FILE *fp;

    fp = fopen( filename, "rb" );
    if( !fp ) return 0;
    
    NumOfLyrics = 0;
    Lyrics.clear();
    
    int lyricsize = 0;
    
    LyricsFound = 0;
    LyricsCallBackUseable = 0;
    if( LyricsFound == 0 ) LoadLyricsInLDBFormat( filename );
    if( LyricsFound == 0 ) LoadLyricsFromLrcFile( filename );

    fclose(fp);
    return LyricsFound;
}

Uint32 LyricsCallBack(Uint32 interval, void *param )
{
    float curplayingtick = MP3_GetCurrentTime() + 0.05;
    while(curplayingtick > NextLyric->tick)
    {
		if(CurrLyric == NULL) {
			NumOfCurPlayingLyric = 0;
		} else if(NextLyric != Lyrics.end()){
			NumOfCurPlayingLyric++;
		}

		if( (CurrLyric == NULL) || (NextLyric->tick > CurrLyric->tick) ) {
	        NumOfCurPlayingLyricBegin = NumOfCurPlayingLyricEnd = NumOfCurPlayingLyric;
	        CurrLyric = NextLyric;
		} else if(strlen(NextLyric->text) != 0) {
			NumOfCurPlayingLyricEnd = NumOfCurPlayingLyric;
		}

        if(NextLyric == Lyrics.end()) break;
        NextLyric++;
    }
    return interval;
}

void LyricsTimerStart( void )
{
    if( LyricsCallBackUseable == 0 ) return;
    CurrLyric = NULL;
    NextLyric = Lyrics.begin();

    if( LyricsViewTimerID == 0 ) LyricsViewTimerID = SDL_AddTimer( 100, LyricsCallBack, NULL );
}

void LyricsTimerStop( void )
{
    SDL_RemoveTimer( LyricsViewTimerID );
    LyricsViewTimerID = 0;
    LyricsCallBackUseable = 0;
    NumOfCurPlayingLyric = 0;
    NumOfCurPlayingLyricBegin = NumOfCurPlayingLyricEnd = -1;
    CurrLyric = NULL;
}

int GetNumOfLyrics( void )
{
    return NumOfLyrics;
}

int IsLyricExist( void )
{
    return LyricsFound;
}

int DrawEntireLyrics( SDL_Surface *surface, int x, int y, int start )
{
    int dx = x, dy = y, c;
    list<Lyric>::iterator templyric = Lyrics.begin();
    
    if (NumOfCurPlayingLyricEnd > start + 12)
	    start = NumOfCurPlayingLyricEnd - 12;

    if (NumOfCurPlayingLyricBegin < start + 2)
	    start = NumOfCurPlayingLyricBegin - 2;

	if (start + 15 > NumOfLyrics) start = NumOfLyrics - 15;
	if (start < 0) start = 0;

    for( c = 1; c <= start && templyric != Lyrics.end(); c++ ) templyric++;
    if( templyric == Lyrics.end() ) return start;

    for( c = 0; c < 15 && templyric != Lyrics.end() ; templyric++, c++ )
    {
        if( LyricsCallBackUseable == 1 )
        {
            if( ( NumOfCurPlayingLyricBegin <= c + start ) && ( NumOfCurPlayingLyricEnd >= c + start ) )
            {
                SetFontColor( FT_COLOR_YELLOW );
            }
            else
            {
                SetFontColor( FT_COLOR_WHITE );
            }
            DrawText( surface, dx, dy, templyric->text );
            if( NumOfCurPlayingLyricBegin == c + start )
                DrawBlendRect( surface, 0, dy, 320, 12, 1 );
        }
        else
        {
            SetFontColor( FT_COLOR_WHITE );
            DrawText( surface, dx, dy, templyric->text );
        }
        dy += 14;
    }
    SetFontColor( FT_COLOR_WHITE );
    
    return start;
}
