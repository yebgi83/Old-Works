#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#ifdef GP2X
#include <unistd.h>
#endif

#include "freetype2_custom.h"

#include "mixer_custom.h"
#include "bmsloader.h"
#include "bmsinterface.h"

BMS_Loader BL;
BMS_Interface BI;

/* The screen surface */
SDL_Surface *screen = NULL;

void Terminate(void)
{
	SDL_Quit();
#ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}

Uint32 OpenBMSCallBack(Uint32 interval, void *param )
{
    if( BL.GetStageBmp()     ) 
        SDL_BlitSurface( BL.GetStageBmp(), NULL, screen, NULL ); 
    else
        SDL_FillRect( screen, NULL, 0 );
    DrawText( screen, 110, 5, "%-7d바이트 할당됨", BL.GetAllocatedSize() );
    SDL_UpdateRect( screen, 0, 0, 320, 240 );
    return interval;
}

void OpenBMS( char *filename )
{
    SDL_TimerID OpenBMSCallBack_TimerID;

    OpenBMSCallBack_TimerID = SDL_AddTimer( 100, &OpenBMSCallBack, &BL );
    BL.LoadFromFile( filename );
    while( BL.GetLoadEnd() == 0 );
    
    for( int c = 0; c < 255; c++ ) 
    {
         BI.SetWaveResource( c, BL.GetWaveResource(c) );
         BI.SetBmpResource( c, BL.GetBmpResource(c) );
    }
    
    BI.Init();
    BI.SetPrimarySurface( screen );
    BI.SetPlaySections( BL.GetPlaySections() );
    BI.SetNormalNote( BL.GetNormalNote() );
    BI.SetBGANote( BL.GetBGANote() );
    BI.SetBGSNote( BL.GetBGSNote() );
    BI.SetScNote( BL.GetScNote() );
    BI.SetFrNote( BL.GetFrNote() );
    BI.SetTotal( BL.GetTotal() );
    BI.SetBPM( BL.GetBPM() );
    
    SDL_RemoveTimer( OpenBMSCallBack_TimerID );
}

void BMPlay( void )
{
    int done = 0;
    
    while (!done)
	{
		Uint8 *keystate = SDL_GetKeyState(NULL);

		SDL_PumpEvents();
        if ( keystate[SDLK_ESCAPE] ) done = 1;
        if ( keystate[SDLK_z] ) BI.SetKeySwitch( 0, 1 ); else BI.SetKeySwitch( 0, 0 );
        if ( keystate[SDLK_s] ) BI.SetKeySwitch( 1, 1 ); else BI.SetKeySwitch( 1, 0 );
        if ( keystate[SDLK_x] ) BI.SetKeySwitch( 2, 1 ); else BI.SetKeySwitch( 2, 0 );
        if ( keystate[SDLK_d] ) BI.SetKeySwitch( 3, 1 ); else BI.SetKeySwitch( 3, 0 );
        if ( keystate[SDLK_c] ) BI.SetKeySwitch( 4, 1 ); else BI.SetKeySwitch( 4, 0 );
        if ( keystate[SDLK_SPACE] ) BI.SetScSwitch( 1 ); else BI.SetScSwitch( 0 );

		/* Processing */
        BI.Draw();
        
        if( done == 0 && BI.IsPlaying() == 0 ) 
        {
            BI.ViewResult();
            done = 1;
        }
        SDL_UpdateRect( screen, 0, 0, 320, 240 );
	}
}

int main (int argc, char *argv[])
{
	int done;

	/* Initialize SDL */
	if (SDL_Init (SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
		exit (1);
	}
	SDL_JoystickOpen(0);
	atexit (Terminate);

	SDL_ShowCursor(SDL_DISABLE);

	/* Set 320x240 16-bits video mode */
	screen = SDL_SetVideoMode (320, 240, 16, SDL_SWSURFACE );
	if (screen == NULL) {
		fprintf (stderr, "Couldn't set 320x240x16 video mode: %s\n", SDL_GetError ());
		exit (2);
	}
  
    InitMixer();
    InitFreeType2();
    
//    OpenBMS( "rozen_01_5n.bms" );
//   OpenBMS( "invisible_stream_overflow.bms" );
//    OpenBMS( "lamellibrachia7n.bme" );
    OpenBMS( "breeze_normal.bms" );
    BMPlay();
    return 0;
}
