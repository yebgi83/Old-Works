#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <mem.h>

#include <cstdlib>
#include <iostream>

#include <windows.h>
#include <vfw.h>  

#include "common.h"
#include "bms.h"
#include "bmstomix.h"
#include "ovconv.h"
#include "avi.h"

#define WIN32_LEAN_AND_MEAN

using namespace std;

void ExportFromBMS( char *avifilename, char *oggfilename, BMS bms )
{
    int period = 2500 / bms.Info.nBPM;
    
    AVI avi = CreateAVI( avifilename, period );
    MIX mix = BindBMS( &bms );
    
    AudioScheduler( &mix, &bms );
    for( int c = 0; c < bms.Note.nDatas; c++ )
    {
        if( bms.Note.pBgNote[c] != 0 )
            if( bms.Doc.pImg[ bms.Note.pBgNote[c] ].Loaded == true ) AddVideoFrame( &avi, bms.Doc.pImg[ bms.Note.pBgNote[c] ] );
        else            
            SkipFrame( &avi );
    } 
    printf("\n"); 
//    SaveOGG( oggfilename, mix ); 
    CloseAVI( &avi ); 
//    ViewWAVList();

//    NoteOptimize( &bms );
//    getch();
SaveWAV( &mix, "" );
    CloseBMS( &bms );        
}

int main(int argc, char *argv[])
{
 /*   if( argc == 1 )
    {
        printf("BMS Exporter Version 0.6\n");
        printf("[Usage] BMSEXPORT [bmsfilename] [avifilename(for export)] [oggfilename(for export)]\n");
        printf("This program is set as 44100Hz, Stereo, 16 bits.\n");
    }
        
    if( argc == 4 ) 
    {
        BMS bms = OpenBMS( argv[1] );
        if( bms.Loaded == TRUE )
        {
            ExportFromBMS( argv[2], argv[3], bms );
            printf("Press any key to terminate.\n");
            getch();
        }
    }*/

    BMS bms = OpenBMS( ".\\ex\\invisible_stream_overflow_7NM.bms" );
    ExportFromBMS( "r.avi", "r.ogg", bms );
    
    if( argc != 4 ) printf( "Error! There are less or more arguments.\n");

    return EXIT_SUCCESS;
}
 
