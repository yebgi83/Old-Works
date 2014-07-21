#define BMS_DOC_SIZE      1296

#define BMS_SECTION_MAX   500lu
#define BMS_SECTION_SIZE  96u
#define BMS_CHANNELS      48lu
#define BMS_NOTESIZE_MAX  (BMS_SECTION_MAX * BMS_SECTION_SIZE)

#define BMS_NOTE( pbms, c, n ) *((pbms->Note).pNote[c - 1] + (n - 1))
#define BMS_IMG_NOTE( pbms, n ) (pbms->Note).pBgNote[n] 

static char Parser_Arg[10][512];
static char Parser_ColonArg[2][512];

typedef struct
{
    WAV *pWav;
    IMG *pImg;
}BMSDoc;

typedef struct
{
    char  lpszTitle[100];
    char  lpszArtist[100];
    char  lpszGenre[100];
    char  lpszEmail[100];
    char  lpszUrl[100];
    short nPlayer;
    short nBPM;
    short nPlayLevel;
    short nRank;
    short nTotal;
}BMSInfo;

typedef struct
{
    unsigned short nDatas;
    unsigned short nBgsChans[BMS_SECTION_MAX];
    unsigned short *pNote[BMS_CHANNELS];
    unsigned short *pBgNote;
}BMSNote;

typedef struct
{
    bool Loaded;
    BMSInfo Info;
    BMSDoc  Doc;
    BMSNote Note;
}BMS;

#include "bmsbnk.h"

void BMSParser( char *getline )
{
    int argnum_writing = 0;
    int colonargnum_writing = 0;
    char *startpos = getline;
    
    strcpy( Parser_Arg[0], "" );
    strcpy( Parser_Arg[1], "" );
    strcpy( Parser_Arg[2], "" );
    strcpy( Parser_ColonArg[0], "" );
    strcpy( Parser_ColonArg[1], "" );
    
    int flag_recent_searched_space = 0;
    int flag_recent_searched_colon = 1;
    
    while(1)
    {
        char *result_searching_space = strchr( startpos, ' ' );
        char *result_searching_colon = strchr( startpos, ':' );
        
        if( result_searching_space == NULL && result_searching_colon == NULL ) 
        {
            if( flag_recent_searched_space == 0 && flag_recent_searched_colon == 0 ) strcpy( Parser_Arg[ argnum_writing ], getline );
            if( flag_recent_searched_space == 1 )
            {
                strncpy( Parser_Arg[ argnum_writing ], startpos, strlen(getline) - (size_t)(startpos - getline) );
                Parser_Arg[ argnum_writing++ ][ strlen(getline) - (size_t)(startpos - getline) ] = '\0';
            }
            if( flag_recent_searched_colon == 1 )
            {
                strncpy( Parser_ColonArg[ colonargnum_writing ], startpos, strlen(getline) - (size_t)(startpos - getline) );
                Parser_ColonArg[ colonargnum_writing++ ][ strlen(getline) - (size_t)(startpos - getline) ] = '\0';
            }
            break;
        }
        
        if( result_searching_space == NULL ) result_searching_space = (char *)0xfffffffflu;
        if( result_searching_colon == NULL ) result_searching_colon = (char *)0xfffffffflu;

        if( result_searching_space < result_searching_colon ) 
        {
            strncpy( Parser_Arg[ argnum_writing ], startpos, (size_t)(result_searching_space - startpos) );
            Parser_Arg[ argnum_writing++ ][ (size_t)(result_searching_space - startpos) ] = '\0';
            startpos = result_searching_space + 1;
            flag_recent_searched_colon = 0;
            flag_recent_searched_space = 1;
        }
        if( result_searching_colon < result_searching_space ) 
        {
            strncpy( Parser_ColonArg[ colonargnum_writing ], startpos, (size_t)(result_searching_colon - startpos) );
            Parser_ColonArg[ colonargnum_writing++ ][ (size_t)(result_searching_colon - startpos) ] = '\0';
            startpos = result_searching_colon + 1;
            flag_recent_searched_colon = 1;
            flag_recent_searched_space = 0;
        }
        if( argnum_writing > 10 ) break;
        if( colonargnum_writing > 2 ) break;
    }
}

void BMSInterpret( BMS *pbms )
{
    if( Parser_Arg[0][0] == '*' ) return;
    if( Parser_Arg[0][0] != '#' && Parser_Arg[0][0] != '%' && Parser_ColonArg[0][0] == '\0' ) return;
   
    if( Parser_Arg[0][0] == '%' )
    {
        char *name = &Parser_Arg[0][1];
        if( strcmp( name, "EMAIL" ) == 0 ) strcmp( (pbms->Info).lpszEmail, Parser_Arg[1] );
        if( strcmp( name, "URL" )   == 0 ) strcmp( (pbms->Info).lpszUrl, Parser_Arg[1] );
    }

    if( Parser_Arg[0][0] == '#' && strncmp( &Parser_Arg[0][1], "WAV", 3 ) != 0 && strncmp( &Parser_Arg[0][1], "BMP", 3 ) != 0 )
    {
        char *name = &Parser_Arg[0][1];
        if( strcmp( name, "PLAYER" ) == 0 ) (pbms->Info).nPlayer = StringToNumber( Parser_Arg[1] ); 
        if( strcmp( name, "GENRE" )  == 0 ) strcpy( (pbms->Info).lpszGenre, Parser_Arg[1] );
        if( strcmp( name, "TITLE" )  == 0 ) 
        {
            for( int c = 1; c < 10; c++ )
            {
                if( c == 1 ) 
                    strcpy( (pbms->Info).lpszTitle, Parser_Arg[c] ); 
                else
                {
                    if( Parser_Arg[c][0] != '\0' )
                    {
                        strcat( (pbms->Info).lpszTitle, " " );
                        strcat( (pbms->Info).lpszTitle, Parser_Arg[c] );
                    }
                }
            }
        }
        if( strcmp( name, "ARTIST" )    == 0 ) strcpy( (pbms->Info).lpszArtist, Parser_Arg[1] );
        if( strcmp( name, "BPM" )       == 0 ) (pbms->Info).nBPM = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "PLAYLEVEL" ) == 0 ) (pbms->Info).nPlayLevel = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "RANK" )      == 0 ) (pbms->Info).nRank = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "TOTAL" )     == 0 ) (pbms->Info).nTotal = StringToNumber( Parser_Arg[1] );
//        if( strcmp( name, "STAGEFILE" ) == 0 ) pStageBmp = SDL_LoadBMP( Parser_Arg[1] );
    }
    
    if( Parser_Arg[0][0] == '#' && strncmp( &Parser_Arg[0][1], "WAV", 3 ) == 0 ) 
    {
        int idx = HexToNumber( Parser_Arg[0][4], Parser_Arg[0][5] );
        if( idx == -1 ) return;
        
        (pbms->Doc).pWav[idx] = OpenWAV( Parser_Arg[1] );
         printf("Loading WAV[%d] %s Length = %d\n", idx, Parser_Arg[1], (pbms->Doc).pWav[idx].Data.nLen8 );
         MakeFixedWAV( &((pbms->Doc).pWav[idx]) );
            
         // 게임에 연주될 악기를 추려내기 위해 일단 명단을 보관한다. 
         RegisterWAVUnit( idx, Parser_Arg[1], (pbms->Doc).pWav[idx].Data.nLen8 );
    }

    if( Parser_Arg[0][0] == '#' && strncmp( &Parser_Arg[0][1], "BMP", 3 ) == 0 ) 
    {
        int idx = HexToNumber( Parser_Arg[0][4], Parser_Arg[0][5] );
        if( idx == -1 ) return;

        (pbms->Doc).pImg[idx] = LoadIMG( Parser_Arg[1] );
        if( (pbms->Doc).pImg[idx].Loaded == TRUE )
        {
            printf("Loading BMP[%d] %s Size = %d x %d \n", idx, Parser_Arg[1], (pbms->Doc).pImg[idx].Info.Header.biWidth, (pbms->Doc).pImg[idx].Info.Header.biHeight );
            MakeFixedIMG( &((pbms->Doc).pImg[idx]) );
        }
    }
    
    if( Parser_ColonArg[0][0] == '#' )
    {
        int note_section_idx = DecToNumber( Parser_ColonArg[0][1], Parser_ColonArg[0][2], Parser_ColonArg[0][3] );
        int note_channel_idx = DecToNumber(                   '0', Parser_ColonArg[0][4], Parser_ColonArg[0][5] );
        int note_idx         = 0;
        int inc;
        
        inc = BMS_SECTION_SIZE / ( strlen( Parser_ColonArg[1] ) / 2 );
        for( int c = 0; c < strlen( Parser_ColonArg[1] ); c += 2 )
        {
            unsigned short data = HexToNumber( Parser_ColonArg[1][c], Parser_ColonArg[1][c+1] );
            unsigned long  pos  = BMS_SECTION_SIZE * note_section_idx + note_idx;

            switch( note_channel_idx )
            {
                case 1:             
                    BMS_NOTE( pbms, (pbms->Note).nBgsChans[note_section_idx] + 11, pos ) = data;
                    break;
                case 4:
                    BMS_IMG_NOTE( pbms, pos ) = data;
                    break;
                case 11:                     
                case 12:                     
                case 13:                     
                case 14: 
                case 15:                     
                case 16:                     
                case 17:                     
                case 18:                     
                case 19:         
                    BMS_NOTE( pbms, note_channel_idx - 10, pos ) = data;
                    break;                    
//                    SetUsedForGame( data );
//                    break;
                    
            }
            if( (pbms->Note).nDatas < pos ) (pbms->Note).nDatas = pos;
            note_idx += inc;
        }        
        if( (pbms->Note).nBgsChans[note_section_idx] + 11 < BMS_CHANNELS ) (pbms->Note).nBgsChans[note_section_idx]++;  
    }
}

BMS OpenBMS( char *filename )
{
    FILE *fp;
    BMS loadbms;
    memset( &loadbms, 0, sizeof(BMS) );
    loadbms.Loaded = FALSE;
    
    // 게임에 연주되는 악기만 추려내기 위해  
    InitWAVList();
    
    fp = fopen( filename, "rb" );
    if( fp == NULL ) 
    {
        printf( "File is not found.\n" );
        return loadbms;
    }
    
    loadbms.Loaded = TRUE;
    loadbms.Doc.pWav = new WAV [BMS_DOC_SIZE];
    loadbms.Doc.pImg = new IMG [BMS_DOC_SIZE];

    for( int c = 0; c < BMS_DOC_SIZE; c++ )
    {
        memset( &(loadbms.Doc.pImg[c]), 0, sizeof(IMG) );
        memset( &(loadbms.Doc.pWav[c]), 0, sizeof(WAV) );
    }
    
    for( int c = 0; c < BMS_CHANNELS; c++ )
    {
        loadbms.Note.pNote[c] = new unsigned short [BMS_NOTESIZE_MAX];
        memset( loadbms.Note.pNote[c], 0, 2 * BMS_NOTESIZE_MAX );
    }
    loadbms.Note.pBgNote = new unsigned short [BMS_NOTESIZE_MAX];
    memset( loadbms.Note.pBgNote, 0, 2 * BMS_NOTESIZE_MAX );
    
    char ch;
    char getline[512];
    int  getline_curpos = 0;
    while( !feof(fp) )
    {
        char ch = fgetc(fp);
        if( ch == 0x0d ) 
        {
            ch = fgetc(fp);
            if( ch == 0x0a ) 
            {
                getline[ getline_curpos ] = 0;
                BMSParser( getline ); 
                BMSInterpret( &loadbms );
                getline_curpos = 0;
            }
        }
        else
            getline[ getline_curpos++ ] = ch;
    }
    fclose(fp); 
    printf("\n");
    return loadbms;
}

void CloseBMS( BMS *pbms )
{
    RemoveWAVList();
    
    for( int c = 0; c < BMS_CHANNELS; c++ )
    {
        if( (pbms->Note).pNote[c] != NULL )
        {
            delete (pbms->Note).pNote[c];
            (pbms->Note).pNote[c] = NULL;
        }
    }
    delete (pbms->Note).pBgNote;
    for( int c = 0; c < BMS_DOC_SIZE; c++ ) CloseWAV( &((pbms->Doc).pWav[c]) );
    for( int c = 0; c < BMS_DOC_SIZE; c++ ) CloseIMG( &((pbms->Doc).pImg[c]) );
    delete (pbms->Doc).pWav;
    delete (pbms->Doc).pImg;
}
