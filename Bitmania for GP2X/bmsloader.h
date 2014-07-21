#include<stdio.h>
#include<stdlib.h>

#include<SDL.h>
#include<SDL_audio.h>
#include<SDL_mixer.h>

//#define BMS_LOADER_DEBUG

#define BMS_SECTION_MAX           1024
#define BMS_NOTE_SECTION_SIZE     32

typedef unsigned char BMS_NormalNote[7][BMS_SECTION_MAX][BMS_NOTE_SECTION_SIZE];
typedef unsigned char BMS_ScNote       [BMS_SECTION_MAX][BMS_NOTE_SECTION_SIZE];
typedef unsigned char BMS_FrNote       [BMS_SECTION_MAX][BMS_NOTE_SECTION_SIZE];
typedef unsigned char BMS_BGANote      [BMS_SECTION_MAX][BMS_NOTE_SECTION_SIZE];
typedef unsigned char BMS_BGSNote  [32][BMS_SECTION_MAX][BMS_NOTE_SECTION_SIZE];

class BMS_Loader 
{
    private:
        int  IsLoadEnd;
        int  RecentNoteIdxProcessed;
        int  BgSound_Idx;
                    
        char Parser_Arg[10][512];
        char Parser_ColonArg[2][512];
//---------------------------------------------
        int  StringToNumber( char *str );
        int  HexToNumber( char upper, char lower );
        int  DecToNumber( char upper, char middle, char lower );
        void Parser( char *getline );
        void Interpret( void );
    protected:
        int  Player;
        char Genre[128];
        char Artist[128];
        char Title[256];
        int  BPM;
        int  PlayLevel;
        int  Rank;
        int  Total;
        char Email[128];
        char Url[128];
        int  PlaySections; 
     
        SDL_Surface *pStageBmp;
        
        Mix_Chunk *pWaveRes[255];
        SDL_Surface *pBmpRes[255];
//---------------------------------------------
        BMS_NormalNote Note_Normal;
        BMS_ScNote     Note_Sc;
        BMS_FrNote     Note_Fr;
        BMS_BGANote    Note_BGA;
        BMS_BGSNote    Note_BGS;
//---------------------------------------------
        int AllocatedSize;
    public:
        void Init( void );
        void LoadFromFile( char filename[256] );
        void AddExtNoteValue( int *p_sectionidx, int *p_subidx );
 
        Mix_Chunk *GetWaveResource( int index );
        SDL_Surface *GetBmpResource( int index );
        SDL_Surface *GetStageBmp( void );
      
        char *GetGenre( void );
        char *GetArtist( void );
        char *GetTitle( void );
        int   GetBPM( void );
        int   GetPlayLevel( void );
        int   GetRank( void );
        int   GetTotal( void );
        char *GetEmail( void );
        char *GetUrl( void );
        
        BMS_NormalNote *GetNormalNote();
        BMS_ScNote     *GetScNote();
        BMS_FrNote     *GetFrNote();
        BMS_BGANote    *GetBGANote();
        BMS_BGSNote    *GetBGSNote();

        int GetLoadEnd();
        int GetPlaySections();
        int GetAllocatedSize();
        double GetCaculatedOneBeatTick( void );

        int Util_Sync( int sectionidx, int subidx, int playstarttime );
};

int BMS_Loader::StringToNumber( char *str )
{
    int value = 1;
    int result = 0;
    for( int c = strlen(str) - 1; c >= 0; c-- )
    {
        int idx = 0;
        if( str[c] >= '0' && str[c] <= '9' ) 
        {
            idx = str[c] - '0';
            result += (value * idx);
        }
        value *= 10;
    }
    return result;
}

int BMS_Loader::HexToNumber( char upper, char lower )
{
    char *hexstr = "0123456789ABCDEF";
    int upper_idx = (int)(strchr( hexstr, upper ) - hexstr);
    int lower_idx = (int)(strchr( hexstr, lower ) - hexstr);
    if( upper_idx < 0 || lower_idx < 0 ) return -1; else return 0x10 * upper_idx + 0x01 * lower_idx;
}

int BMS_Loader::DecToNumber( char upper, char middle, char lower )
{
    return 100 * (upper - '0') + 10 * (middle - '0') + 1 * (lower - '0');
}

void BMS_Loader::Parser( char *getline )
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

void BMS_Loader::Interpret( void )
{
    if( Parser_Arg[0][0] == '*' ) return;
    if( Parser_Arg[0][0] != '#' && Parser_Arg[0][0] != '%' && Parser_ColonArg[0][0] == '\0' ) return;
   
    if( Parser_Arg[0][0] == '%' )
    {
        char *name = &Parser_Arg[0][1];
        if( strcmp( name, "EMAIL" )     == 0 ) strcmp( Email, Parser_Arg[1] );
        if( strcmp( name, "URL" )     == 0 ) strcmp( Url, Parser_Arg[1] );
    }

    if( Parser_Arg[0][0] == '#' && strncmp( &Parser_Arg[0][1], "WAV", 3 ) != 0 && strncmp( &Parser_Arg[0][1], "BMP", 3 ) != 0 )
    {
        char *name = &Parser_Arg[0][1];
        if( strcmp( name, "PLAYER" )    == 0 ) Player = StringToNumber( Parser_Arg[1] ); 
        if( strcmp( name, "GENRE" )     == 0 ) strcpy( Genre, Parser_Arg[1] );
        if( strcmp( name, "TITLE" )     == 0 ) 
        {
            for( int c = 1; c < 10; c++ )
            {
                if( c == 1 ) 
                    strcpy( Title, Parser_Arg[c] ); 
                else
                {
                    if( Parser_Arg[c][0] != '\0' )
                    {
                        strcat( Title, " " );
                        strcat( Title, Parser_Arg[c] );
                    }
                }
            }
        }
        if( strcmp( name, "ARTIST" )    == 0 ) strcpy( Artist, Parser_Arg[1] );
        if( strcmp( name, "BPM" )       == 0 ) BPM = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "PLAYLEVEL" ) == 0 ) PlayLevel = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "RANK" )      == 0 ) Rank = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "TOTAL" )     == 0 ) Total = StringToNumber( Parser_Arg[1] );
        if( strcmp( name, "STAGEFILE" ) == 0 ) pStageBmp = SDL_LoadBMP( Parser_Arg[1] );
    }
    
    if( Parser_Arg[0][0] == '#' && strncmp( &Parser_Arg[0][1], "WAV", 3 ) == 0 ) 
    {
        int idx = HexToNumber( Parser_Arg[0][4], Parser_Arg[0][5] );
        if( idx == -1 ) return;

        pWaveRes[idx] = Mix_LoadWAV( Parser_Arg[1] );
#ifdef BMS_LOADER_DEBUG
        if( pWaveRes[idx] == NULL ) 
            fprintf( stderr, "Error: %s is not loaded that because %s\n", Parser_Arg[1], Mix_GetError() );
        else
            AllocatedSize += pWaveRes[idx]->alen;
#else
        if( pWaveRes[idx] != NULL ) AllocatedSize += pWaveRes[idx]->alen;
#endif
    }

    if( Parser_Arg[0][0] == '#' && strncmp( &Parser_Arg[0][1], "BMP", 3 ) == 0 ) 
    {
        int idx = HexToNumber( Parser_Arg[0][4], Parser_Arg[0][5] );
        if( idx == -1 ) return;

        pBmpRes[idx] = SDL_LoadBMP( Parser_Arg[1] );
#ifdef BMS_LOADER_DEBUG
        if( pBmpRes[idx] == NULL ) 
            fprintf( stderr, "Error: %s is not loaded that because %s\n", Parser_Arg[1], SDL_GetError() );
        else
            AllocatedSize += (pBmpRes[idx]->pitch * pBmpRes[idx]->h);
#else
        if( pBmpRes[idx] != NULL) AllocatedSize += (pBmpRes[idx]->pitch * pBmpRes[idx]->h);
#endif
    }
    
    if( Parser_ColonArg[0][0] == '#' )
    {
        int note_data_idx    = 0;
        int note_section_idx = DecToNumber( Parser_ColonArg[0][1], Parser_ColonArg[0][2], Parser_ColonArg[0][3] );
        int note_channel_idx = DecToNumber(                   '0', Parser_ColonArg[0][4], Parser_ColonArg[0][5] );
        int inc;

        if( PlaySections < note_section_idx ) PlaySections = note_section_idx;

        if( RecentNoteIdxProcessed != note_section_idx ) 
        {
            BgSound_Idx = 0;
            RecentNoteIdxProcessed = note_section_idx;
        }
            
        inc = 32 / ( strlen( Parser_ColonArg[1] ) / 2 );
        for( int c = 0; c < strlen( Parser_ColonArg[1] ); c += 2 )
        {
            unsigned char data = HexToNumber( Parser_ColonArg[1][c], Parser_ColonArg[1][c+1] );
            
            if( note_channel_idx == 1 )  Note_BGS[ BgSound_Idx ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 4 )  Note_BGA[ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 11 ) Note_Normal[ 0 ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 12 ) Note_Normal[ 1 ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 13 ) Note_Normal[ 2 ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 14 ) Note_Normal[ 3 ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 15 ) Note_Normal[ 4 ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 16 ) Note_Sc[ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 17 ) Note_Fr[ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 18 ) Note_Normal[ 5 ][ note_section_idx ][ note_data_idx ] = data;
            if( note_channel_idx == 19 ) Note_Normal[ 6 ][ note_section_idx ][ note_data_idx ] = data;
            
            note_data_idx += inc;
            if( note_data_idx >= 32 ) break;
        }        

        if( note_channel_idx == 1 ) BgSound_Idx++;
    }
}
 
void BMS_Loader::Init( void )
{
    BgSound_Idx = 0;
    AllocatedSize = 0;
    PlaySections = 0;
    pStageBmp = NULL;
    memset( pWaveRes              , 0 , sizeof( Mix_Chunk * )* 255 );
    memset( pBmpRes               , 0 , sizeof( SDL_Surface * ) * 255 );
    memset( Note_Normal           , 0 , sizeof( Note_Normal ));
    memset( Note_Sc               , 0 , sizeof( Note_Sc ));
    memset( Note_Fr               , 0 , sizeof( Note_Fr ));
    memset( Note_BGA              , 0 , sizeof( Note_BGA ));
    memset( Note_BGS              , 0 , sizeof( Note_BGS ));
} 

void BMS_Loader::LoadFromFile( char filename[256] )
{
    Init();
    
    FILE *fp;
    fp = fopen( filename, "rb" );
    if( fp == NULL ) 
    {
        fprintf( stderr, "File is not found.\n" );
        return;
    }
    
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
#ifdef BMS_LOADER_DEBUG
    fprintf( stderr, "%s\n", getline );
#endif
                Parser( getline ); 
                Interpret();
                getline_curpos = 0;
            }
        }
        else
            getline[ getline_curpos++ ] = ch;
    }
    fclose(fp);
    IsLoadEnd = 1;

    return;
}

void BMS_Loader::AddExtNoteValue( int *p_sectionidx, int *p_subidx )
{
    if( *p_sectionidx > Total ) return;
    (*p_subidx)++;
    if( *p_subidx > BMS_NOTE_SECTION_SIZE )
    {
        (*p_sectionidx)++;
        *p_subidx = 0;
    }
}

int BMS_Loader::GetLoadEnd()
{
    return IsLoadEnd;
}

int BMS_Loader::GetPlaySections()
{
    return PlaySections;
}

int BMS_Loader::GetAllocatedSize()
{
    return AllocatedSize;
}

Mix_Chunk *BMS_Loader::GetWaveResource( int index )
{
    return pWaveRes[index];
}

SDL_Surface *BMS_Loader::GetBmpResource( int index )
{
    return pBmpRes[index];
}

SDL_Surface *BMS_Loader::GetStageBmp( void )
{
    return pStageBmp;
}

inline double BMS_Loader::GetCaculatedOneBeatTick( void )
{
    return (60000.0f / BPM / 8.0f);
}

inline char *BMS_Loader::GetArtist( void )
{
    return Artist;
}

inline char *BMS_Loader::GetTitle( void )
{
    return Title;
}

inline int BMS_Loader::GetBPM( void )
{
    return BPM;
}

inline int BMS_Loader::GetPlayLevel( void )
{
    return PlayLevel;
}

inline int BMS_Loader::GetRank( void )
{
    return Rank;
}

inline int BMS_Loader::GetTotal( void )
{
    return Total;
}

inline char *BMS_Loader::GetEmail( void )
{
    return Email;
}

inline char *BMS_Loader::GetUrl( void )
{
    return Url;
}

inline BMS_NormalNote *BMS_Loader::GetNormalNote( void )
{
    return &Note_Normal;
}

inline BMS_ScNote *BMS_Loader::GetScNote( void )
{
    return &Note_Sc;
}

inline BMS_FrNote *BMS_Loader::GetFrNote( void )
{
    return &Note_Fr;
}

inline BMS_BGANote *BMS_Loader::GetBGANote( void )
{
    return &Note_BGA;
}

inline BMS_BGSNote *BMS_Loader::GetBGSNote( void )
{
    return &Note_BGS;
}

int BMS_Loader::Util_Sync( int sectionidx, int subidx, int playstarttime )
{
    double onebeattime = GetCaculatedOneBeatTick();

    int virtualplayingtime;
    virtualplayingtime = (int)(sectionidx * onebeattime * 32.0f);
    virtualplayingtime += (int)(subidx * onebeattime);
    
    int realplayingtime = SDL_GetTicks() - playstarttime;

    return(virtualplayingtime < realplayingtime);
}
