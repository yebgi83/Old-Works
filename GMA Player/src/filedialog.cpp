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

#include <stdlib.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_thread.h>
#ifdef GP2X
#include <sys/stat.h>
#endif
#include "drawtext.h"

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
	#include <dirent.h>
	char CurPath[MAX_PATH] = "/mnt/sd";
#else
	#include <dir.h>
	#include <iconv.h>
	char CurPath[MAX_PATH] = "c:";
#endif

#include<list>
using namespace std;

int ViewFilesIncGapY  = 12;
int ViewFilesInScreen = 16;

int NumOfDirs = 0;
int NumOfFiles = 0;
int NumOfAllFiles = 0;
int CurFile = 1;
int FirstViewFile = 1;

int FileSelRorateDelay = 0;
int FileSelRorateValue = 0;
int ViewSelLimit = 315;

char CurSelFileName[MAX_PATH];
SDL_Surface *SurfaceFileSel;

#ifdef GP2X
#define	_A_SUBDIR	0x00000010

struct _finddata_t
{
    unsigned	  attrib;		/* Attributes, see constants above. */
    char		  name[FILENAME_MAX];	/* may include spaces. */
}; 
#endif

list<_finddata_t> FileList;

class list_compare {
public:
    bool operator() (const struct _finddata_t &a, const struct _finddata_t &b) const {
		if( (a.attrib & _A_SUBDIR) != (b.attrib & _A_SUBDIR) )
			return (b.attrib & _A_SUBDIR) == 0;
        return strcmp(a.name, b.name) < 0;
    };
};

#ifdef GP2X
bool nandMount = false;

void NandMount()
{
	if(nandMount) return;
	bool mount = true;

	FILE *fp = fopen("/proc/mounts", "r");
	if(!fp) {
		system("mount /proc");
		fp = fopen("/proc/mounts", "r");
	}

	if(fp) {
		char line[100];
		while(!feof(fp)) {
			fgets(line, 100, fp);
			if(strncmp(line, "/dev/loop/7", 11) == 0) {
				nandMount = true;
				mount = false;
				break;
			}
		}
		fclose(fp);
	}

	if(mount) {
		char current_path[MAX_PATH];
		getcwd(current_path, sizeof(current_path));
		chdir("/usr/gp2x");
		system("/usr/gp2x/nandmount.sh");
		chdir(current_path);
	}
}

void GetFileList( char *path, char *findext )
{
    char text[MAX_PATH];
    _finddata_t fileinfo;

    NumOfDirs = 0;
    NumOfFiles = 0;
    FileList.clear();
    
    if( !nandMount && (strncmp(path, "/mnt/nand", 9) == 0) ) NandMount();

    if(strcmp(path, "/mnt") == 0) {
		fileinfo.attrib = _A_SUBDIR;
		strcpy(fileinfo.name, "sd");
		FileList.push_back(fileinfo);
		NumOfDirs++;
		strcpy(fileinfo.name, "nand");
		FileList.push_back(fileinfo);
		NumOfDirs++;
		strcpy(fileinfo.name, "ext");
		FileList.push_back(fileinfo);
		NumOfDirs++;
	} else {
	    // add directories to filelist.
	    strcpy( text, path );
	    strcat( text, "/" );
	
	    DIR *pdir = opendir( text );
	    struct dirent *currentindir = NULL;
	
	    if( pdir != NULL )
	    {
	        while(1)
	        {
	            currentindir = readdir( pdir );
	            if( currentindir == NULL ) break;
	            if( currentindir->d_type == DT_DIR ) 
	            {
					if(strcmp(currentindir->d_name, ".") != 0) {
		                fileinfo.attrib = _A_SUBDIR;
		                strcpy( fileinfo.name, currentindir->d_name );
		                FileList.push_back(fileinfo);
		                NumOfDirs++;
					}
	            } else {
					char *ext = strrchr(currentindir->d_name, '.');
					if( (ext != NULL) && (strcasecmp(ext, findext) == 0) ) {
		                fileinfo.attrib = 0;
		                strcpy( fileinfo.name, currentindir->d_name );
		                FileList.push_back(fileinfo);
		                NumOfFiles++;
					}
	            }
	        }
	        closedir( pdir );
	    }

	    FileList.sort(list_compare());
	}

    NumOfAllFiles = NumOfDirs + NumOfFiles;
}
#else
void GetFileList( char *path, char *findext )
{
    int flag;
    long handle;
    char text[MAX_PATH];
    _finddata_t fileinfo;

    NumOfDirs = 0;
    NumOfFiles = 0;
    FileList.clear();
    
    printf("Find: %s\n", path);
    
    // add directories to filelist.
    strcpy( text, path );
    strcat( text, "\\*." );
    handle = _findfirst(text, &fileinfo);
    flag = 0;
    do
    {
        if( ( fileinfo.attrib & _A_SUBDIR ) && strcmp(fileinfo.name, ".") )
        {
            FileList.push_back(fileinfo);
            NumOfDirs++;
        }
        flag = _findnext(handle, &fileinfo);
    }while(flag == 0);
    _findclose(handle);
    
    // add files to filelist.
    strcpy( text, path );
    strcat( text, "\\*" );
    strcat( text, findext);
    handle = _findfirst(text, &fileinfo);
    if( handle != -1 )
    {
        flag = 0;
        do
        {
            if( (fileinfo.attrib & _A_SUBDIR) == 0 )
            {
                FileList.push_back(fileinfo);
                NumOfFiles++;
            }
            flag = _findnext(handle, &fileinfo);
        }while(flag == 0);
        _findclose(handle);
    }

    FileList.sort(list_compare());
    NumOfAllFiles = NumOfDirs + NumOfFiles;
}
#endif

void SetFileSelect( char *filename )
{
    if( strcmp( CurSelFileName, filename ) != 0 )
    {
		if(SurfaceFileSel) {
	        SDL_FreeSurface( SurfaceFileSel );
	        SurfaceFileSel = NULL;
		}
#ifndef GP2X
		iconv_t iconvobj = iconv_open ( "utf-8", "uhc" );
		char convtext[1024];
		const char *ptext = filename;
		char *pconvtext = convtext;
		size_t textlen = strlen(ptext);
		size_t convlen = 1024;
		
        iconv( iconvobj, &ptext, &textlen,  &pconvtext, &convlen );
        *pconvtext = 0;

        SurfaceFileSel = CreateTrueTypeStringSurface( convtext );
        iconv_close (iconvobj);
#else
        SurfaceFileSel = CreateTrueTypeStringSurface( filename );
#endif
        strcpy( CurSelFileName, filename );
        FileSelRorateDelay = FileSelRorateValue = 0;
    }
}

void DrawBlendRect( SDL_Surface *surface, int x, int y, int w, int h, int type )
{
	SDL_LockSurface( surface );
	
	int cx, cy;
	char *pbdata = (char *)surface->pixels + surface->pitch * y + 2 * x;
	for( cy = y; cy < y + h; cy++ )
	{  
		for( cx = x; cx < x + w; cx++ )
		{
			unsigned short pixa, pixb;
			unsigned short r, g, b;
			pixa = *((unsigned short *)pbdata);
			if(pixa != 0xFFFF) {
				if(pixa != 0) {
					r = (pixa & 0xf800) >> 11;
					g = (pixa & 0x07e0) >> 5;
					b = (pixa & 0x001f);
				} else {
					r = g = b = 0;
				}
				if( type & 1 ) r += (12 * cx) / (x + w) + 19 - (19 * cy) / (y + h);
				if( type & 2 ) g += (63 * cx) / (x + w);
				if( type & 4 ) b += (31 * cy) / (y + h);
				if( r > 31 ) r = 31;
				if( g > 63 ) g = 63;
				if( b > 31 ) b = 31;
				pixb = (r << 11) | (g << 5) | b;
				*((unsigned short *)pbdata) = pixb;
			}
			pbdata += 2;
		}
		pbdata += (surface->pitch - (2 * w));
	}
	SDL_UnlockSurface( surface );
}

void DrawFileSel( SDL_Surface *surface, int dx, int dy )
{  
    if( SurfaceFileSel->w > ViewSelLimit )
    {
        SDL_Rect srcrect = { FileSelRorateValue, 0, ViewSelLimit, SurfaceFileSel->h };
        SDL_Rect destrect = { dx, dy, SurfaceFileSel->w, SurfaceFileSel->h };
        SDL_BlitSurface( SurfaceFileSel, &srcrect, surface, &destrect );
    }
    else
    {
        SDL_Rect destrect = { dx, dy, SurfaceFileSel->w, SurfaceFileSel->h };
        SDL_BlitSurface( SurfaceFileSel, 0, surface, &destrect );                           
    } 
    DrawBlendRect( surface, 0, dy - 1, 320, ViewFilesIncGapY + 1, 2 | 4 );
}

void DrawFileDialog( SDL_Surface *surface, bool redraw = false )
{
    int c = 1;
    int dx = 5, dy = 16;
    list<_finddata_t>::iterator u = FileList.begin();
    
#ifndef GP2X
	char convtext[1024];
	const char *ptext;
	char *pconvtext;
	size_t textlen;
	size_t convlen;
	iconv_t iconvobj = iconv_open ( "utf-8", "uhc" );
#endif

    if(redraw) {
	    SDL_FillRect( surface, NULL, 0 );
	  
#ifndef GP2X
		ptext = CurPath;
		pconvtext = convtext;
		textlen = strlen(ptext);
		convlen = 1024;
		
	    iconv( iconvobj, &ptext, &textlen,  &pconvtext, &convlen );
	    *pconvtext = 0;
	
	    DrawText( surface, 5, 0, "Folder: %s, %d File(s) existed.", convtext, NumOfAllFiles );
#else
	    DrawText( surface, 5, 0, "Folder: %s, %d File(s) existed.", CurPath, NumOfAllFiles );
#endif
	    DrawBlendRect( surface, 0, 0, 320, 14, 1 );
	} else {
		SDL_Rect clear = {0, 14, 320, 226};
	    SDL_FillRect( surface, &clear, 0 );
	}
	
    while( c <= FirstViewFile - 1 ) 
    {
        c++;
        u++;
    }

    for( c = 1; c <= ViewFilesInScreen && FirstViewFile + c - 1 <= NumOfAllFiles ; c++ )
    {
		if( u->attrib & _A_SUBDIR) {
			SetFontColor(FT_COLOR_YELLOW);
		} else {
			SetFontColor(FT_COLOR_WHITE);
		}
        if( CurFile == c ) 
        {
            SetFileSelect( u->name );
            DrawFileSel( surface, dx, dy ); 
        }
        else
        {
#ifndef GP2X
			ptext = u->name;
			pconvtext = convtext;
			textlen = strlen(ptext);
			convlen = 1024;
			
	        iconv( iconvobj, &ptext, &textlen,  &pconvtext, &convlen );
	        *pconvtext = 0;
	
	        SDL_Surface *tempsurface = CreateTrueTypeStringSurface( convtext );
#else
			SDL_Surface *tempsurface = CreateTrueTypeStringSurface( u->name );
#endif

            SDL_Rect destrect = { dx, dy, 320, tempsurface->h };
            SDL_Rect srcrect = { 0, 0, ViewSelLimit, tempsurface->h };
            SDL_BlitSurface( tempsurface, &srcrect, surface, &destrect );
            SDL_FreeSurface( tempsurface );
        }
        u++;
        dy += (ViewFilesIncGapY + 2);
    }
#ifndef GP2X
    iconv_close (iconvobj);
#endif
	SetFontColor(FT_COLOR_WHITE);
    if( NumOfAllFiles == 0 ) DrawText( surface, dx, dy, "There's nothing in directory." );
    SDL_UpdateRect( surface, 0, 0, surface->w, surface->h );
}

void DecCurFile( void )
{
    CurFile--;  
    if( CurFile == 0 ) 
    {
        CurFile = 1;
        if( FirstViewFile > 1 ) FirstViewFile--;
    }        
}

void IncCurFile( void )
{
    CurFile++;
    if( FirstViewFile + CurFile - 1 > NumOfAllFiles ) CurFile--;
    if( CurFile > ViewFilesInScreen )
    {
        CurFile = ViewFilesInScreen;
        if( FirstViewFile < (1 + NumOfAllFiles - ViewFilesInScreen) ) FirstViewFile++;
    }
}

void PageUpCurFile( void )
{
    if(FirstViewFile == 1) {
		CurFile = 1;
		return;
	}

	FirstViewFile -= ViewFilesInScreen;
	if(FirstViewFile < 1) FirstViewFile = 1;
}

void PageDownCurFile( void )
{
    if( (FirstViewFile + ViewFilesInScreen) > NumOfAllFiles ) {
		CurFile = ViewFilesInScreen;
		if(CurFile > NumOfAllFiles)
			CurFile = NumOfAllFiles;
		return;
	}

    FirstViewFile += ViewFilesInScreen;
    if( (FirstViewFile + ViewFilesInScreen) > NumOfAllFiles ) {
		FirstViewFile = NumOfAllFiles - ViewFilesInScreen + 1;
	}
	if(FirstViewFile < 0) FirstViewFile = 0;
}

int OperateCurFile( char *restext )
{
    int c = 0;
    list<_finddata_t>::iterator u = FileList.begin();
    
    while( c < ((FirstViewFile - 1) + (CurFile - 1)) ) 
    {
       c++;
       u++;
    } 
    if( u->attrib & _A_SUBDIR )
    {
        CurFile = 1;
        FirstViewFile = 1;
        if( strcmp( u->name, ".." ) == 0 )
        {
            int c2;
            for( c2 = strlen(CurPath) - 1; c2 >= 0; c2-- ) 
            {
                if( CurPath[c2] == '/' ) 
                {
                    CurPath[c2] = '\0';
                    break;
                }
            }
            return 0;
        }
        if( strcmp( u->name, "." ) != 0 )
        {
            strcat( CurPath, "/" );
            strcat( CurPath, u->name );
            return 0;
        }
        else
            return 0;
    }
    strcpy( restext, CurPath );
    strcat( restext, "/" );
    strcat( restext, u->name );
    return 1;
}

Uint32 FileDialogEffectCallBack(Uint32 interval, void *param )
{
    if( FileSelRorateDelay > 0 )
    {
        FileSelRorateDelay--;
        if( FileSelRorateDelay == 0 ) FileSelRorateValue = 0;
    }
    else
    {
        FileSelRorateValue++;
        if( FileSelRorateValue > SurfaceFileSel->w - ViewSelLimit ) FileSelRorateDelay = 50;
    }
    return interval;
}

bool MovePath(char *path)
{
#ifdef GP2X
	struct stat statbuf;
    if( !nandMount && (strncmp(path, "/mnt/nand", 9) == 0) ) NandMount();
	lstat(path, &statbuf);
	if(S_ISDIR(statbuf.st_mode)) {
		strcpy(CurPath, path);
		return true;
	}
#endif
	return false;
}

int OpenFileDialog( SDL_Surface *surface, char *path, char *filename, char *result )
{
    int done;
    SDL_TimerID timerid;
    int key, keydown;
    int joytokey[32];
    unsigned int nowtick, eventtick, titletick;
    int count;
    bool update = true;
    bool redraw = true;

    char temptext[MAX_PATH];
    if( path != NULL ) 
    {
        strcpy( temptext, path );
        strcpy( CurPath, path );
        CurFile = 1;
        FirstViewFile = 1;
    }
    if( path == NULL ) strcpy( temptext, CurPath );

    GetFileList( temptext, filename );
    list<_finddata_t>::iterator u = FileList.begin();
    SetFileSelect( u->name );

    timerid = SDL_AddTimer( 50, FileDialogEffectCallBack, (void *)surface );

    done = 0;
    eventtick = 0;
    memset(joytokey, 0, sizeof(joytokey));

    joytokey[VK_LEFT] = SDLK_LEFT;
    joytokey[VK_RIGHT] = SDLK_RIGHT;
    joytokey[VK_UP] = SDLK_UP;
    joytokey[VK_DOWN] = SDLK_DOWN;
    joytokey[VK_FB] = SDLK_RETURN;
    joytokey[VK_TAT] = SDLK_RETURN;
    joytokey[VK_START] = SDLK_ESCAPE;

    while (!done)
	{
		SDL_Event event;

		/* Check for events */
		while (SDL_PollEvent(&event))
		{
            switch (event.type)
			{
				case SDL_JOYBUTTONDOWN:
					key = joytokey[event.jbutton.button];
					if(key == 0) break;
				case SDL_KEYDOWN:
					if(event.type == SDL_KEYDOWN)
	                    key = event.key.keysym.sym;
                    switch (key)
                    {
						case SDLK_LEFT:
						case SDLK_RIGHT:
						case SDLK_UP:
						case SDLK_DOWN:
							keydown = key;
							count = 1;
							eventtick = SDL_GetTicks();
							break;
						case SDLK_RETURN:
	                        if( OperateCurFile(result) == 0 ) {
	                            GetFileList( CurPath, filename );
								update = true;
								redraw = true;
	                        } else
	                            done = 1;
							break;
						case SDLK_ESCAPE:
	                        done = -1;
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
                    done = -1;
					break;
				default:
					break;
			}
		}
		
		nowtick = SDL_GetTicks();

		if( (eventtick != 0) && (eventtick <= nowtick) ){
			switch(keydown) {
				case SDLK_LEFT:
					PageUpCurFile();
					break;
				case SDLK_RIGHT:
					PageDownCurFile();
					break;
				case SDLK_UP:
					DecCurFile();
					break;
				case SDLK_DOWN:
					IncCurFile();
					break;
				default:
					eventtick = 0;
					break;
			}
			if(count > 0) {
				eventtick += 300;
				count--;
			} else {
				eventtick += 70;
			}
			update = true;
		}

		/* Processing */
		if(update) {
	        DrawFileDialog( surface, redraw );
	        update = false;
	        redraw = false;
		}
    }
    SDL_RemoveTimer( timerid );

    SDL_FreeSurface( SurfaceFileSel );
    SurfaceFileSel = NULL;
    CurSelFileName[0] = 0;

    if(done == 1)
		return 1;
	else
		return 0;
}

void GetNextFile(char *result)
{
    int c = 0;
    list<_finddata_t>::iterator u = FileList.begin();
    
    if( FirstViewFile + CurFile - 1 >= NumOfAllFiles ) {
		FirstViewFile = 1;
		CurFile = 1;
	} else {
		IncCurFile();
	}

    while( c < ((FirstViewFile - 1) + (CurFile - 1)) ) {
       c++;
       u++;
    } 
    while( u->attrib & _A_SUBDIR ) {
		IncCurFile();
		u++;
	}

    strcpy( result, CurPath );
    strcat( result, "/" );
    strcat( result, u->name );
}
