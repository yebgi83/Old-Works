#ifndef _SDL_H
#include <sdl.h>
#endif

#include <stdarg.h>

#define  BMS_INTERFACE_SPRITE_MAX  8

typedef struct
{
   SDL_Surface *pBaseSurface;
   int          NumOfImgs;
   int          Delay;
   SDL_Rect     Rect[BMS_INTERFACE_SPRITE_MAX];
   
   int          IsViewing;
   int          IsRepeat;
   int          IsEnd;
         
   int          CurDrawIdx;
   int          WaitForSkip;
}BMSSprite;

typedef struct
{
   SDL_Surface *pBaseSurface;
   SDL_Rect    CharImgRect[255];
}BMSImgFont;

SDL_Rect NewRect( int x, int y, int w, int h )
{
   SDL_Rect temprect;
   temprect.x = x;
   temprect.y = y;
   temprect.w = w;
   temprect.h = h;
   return temprect;
}

void SetBMSSprite( BMSSprite *pSpr, SDL_Surface *pBaseSurface, int NumOfImgs, int Delay, int IsRepeat, ... )
{
   pSpr->pBaseSurface  = pBaseSurface;
   pSpr->NumOfImgs     = NumOfImgs;
   pSpr->Delay         = Delay;
   pSpr->IsRepeat      = IsRepeat;
   pSpr->CurDrawIdx    = 0;
   pSpr->WaitForSkip   = Delay;
   
   va_list valist;
   va_start( valist, IsRepeat );    
   
   for( int c = 0; c < NumOfImgs; c++ )
   {
       SDL_Rect temp = va_arg( valist, SDL_Rect );
       pSpr->Rect[c].x = temp.x;
       pSpr->Rect[c].y = temp.y;
       pSpr->Rect[c].w = temp.w;
       pSpr->Rect[c].h = temp.h;
   }
   va_end(valist);
}

class BMS_Interface
{
    private:
       SDL_Surface *pPrimarySurface;

       SDL_Surface *pBaseImgSurface;
       BMSSprite   Img_SynthKeyBase;
       BMSSprite   Img_KeyOn;
       BMSSprite   Img_ScOn;
       BMSSprite   Img_IronStick;
       BMSSprite   Img_BlueStick;
       BMSSprite   Img_RedStick;
       BMSSprite   Img_Pang[6];
       BMSSprite   Img_Poor;
       BMSSprite   Img_Bad;
       BMSSprite   Img_Good;
       BMSSprite   Img_Great;
       BMSSprite   Img_RedBlendBar;
       BMSSprite   Img_BlueBlendBar;
       BMSSprite   Img_BigRedBlendBar;
       BMSSprite   Img_BigBlueBlendBar;
       BMSImgFont  Img_Font;
       BMSImgFont  Img_ScoreFont;
//-------------------------------------------------------
       int         Sw_ProcessedWhenOn[7];
//-------------------------------------------------------
       int         PangOperation[7];
       int         Cur_Contained_Idx[7];
//-------------------------------------------------------
       int         Judge_Target[7][2];
       int         Judge[7];
       int         Judge_RecentResult;
       int         Judge_RecentResult_RestTimeToView;
//-------------------------------------------------------
       int         Recent_ProcessedStick[7][2];
//-------------------------------------------------------
       int         Sw_Key[7];
       int         Sw_Sc;
//-------------------------------------------------------
       double      Sync_OneBeatTime;
       int         Sync_StartTime;
//-------------------------------------------------------
       SDL_TimerID AnimateCallBack_TimerID;
       SDL_TimerID NoteProcessCallBack_TimerID;
//-------------------------------------------------------
       int   Status_MaxCombo;
       int   Status_Combo;
       int   Status_Life;
       int   Status_Score;
       int   Status_NumOfPoor;
       int   Status_NumOfBad;
       int   Status_NumOfGood;
       int   Status_NumOfGreat;
//-------------------------------------------------------
       int   Status_Success;
       int   Status_End;
//-------------------------------------------------------
       void FrameProcessBMSSprite( BMSSprite *pspr );
       void DrawBMSSprite( BMSSprite *pspr, int x, int y );
//-------------------------------------------------------
       void SetBaseSurfaceToFont( BMSImgFont *pimgfont, SDL_Surface *pSurface );
       void RegImgToFont( BMSImgFont *pimgfont, unsigned char idx, SDL_Rect rect );       
       void DrawText( BMSImgFont *pimgfont, int x, int y, char *fmt, ... );
//-------------------------------------------------------
       void  Sync_Init( void );
       int   Sync( void );
       float Sync_Percentage( void );
//-------------------------------------------------------
       void  Update_Contained_Idx( int channel, int section, int idx );
//-------------------------------------------------------
       void  Set_Judge_Result( int status );
       void  View_Judge_Result( void );
    protected:
       int         Total;
       int         BPM;     
       int         PlaySections;
//-------------------------------------------------------
       Mix_Chunk   *pWaveRes[255];
       SDL_Surface *pBmpRes[255];
//-------------------------------------------------------
       BMS_NormalNote *pNote_Normal;
       BMS_ScNote     *pNote_Sc;
       BMS_FrNote     *pNote_Fr;
       BMS_BGANote    *pNote_BGA;
       BMS_BGSNote    *pNote_BGS;
//-------------------------------------------------------
       int Cur_Note_Section;
       int Cur_Note_Idx;
    public:
       void Init();
       void SetPrimarySurface( SDL_Surface *pSurface );
       void Draw();
       void DrawNote();
       
       void SetWaveResource( int idx, Mix_Chunk *pWaveChunk );
       void SetBmpResource( int idx, SDL_Surface *pSurface );
       
       void SetTotal( int total );
       void SetBPM( int BPM );
       void SetPlaySections( int playsections );
       
       void SetNormalNote( BMS_NormalNote *pnote );
       void SetScNote( BMS_ScNote *pnote );
       void SetFrNote( BMS_FrNote *pnote );
       void SetBGANote( BMS_BGANote *pnote );
       void SetBGSNote( BMS_BGSNote *pnote );
       
       void SetKeySwitch( int idx, int sw );
       void SetScSwitch( int sw );
       
       int  GetKeySwitch( int idx );
       int  GetScSwitch( void );
       
       int  IsPlaying( void );
       void End( int playsuccess );
       void ViewResult( void );
       
       friend Uint32 AnimateCallBack( Uint32 interval, void *param );
       friend Uint32 NoteProcessCallBack( Uint32 interval, void *param );
};

Uint32 AnimateCallBack( Uint32 interval, void *param )
{
    BMS_Interface *tempobj = (BMS_Interface *)param;
    tempobj->FrameProcessBMSSprite( &(tempobj->Img_IronStick) );
    tempobj->FrameProcessBMSSprite( &(tempobj->Img_BlueStick) );
    tempobj->FrameProcessBMSSprite( &(tempobj->Img_RedStick) );
    for( int c = 0; c < 6; c++ )
        tempobj->FrameProcessBMSSprite( &(tempobj->Img_Pang[c]) );
    return interval;
}

Uint32 NoteProcessCallBack( Uint32 interval, void *param )
{
    BMS_Interface *tempobj = (BMS_Interface *)param;
    
    // 게임 전개와 관련된 처리
    // 노트를 무시했는가 여부 확인
    for( int c = 0; c < 7; c++ ) 
    {
        unsigned char value;
        value = (*(tempobj->pNote_Normal))[c][tempobj->Cur_Note_Section][tempobj->Cur_Note_Idx];
        if( value != 0 && ( tempobj->Recent_ProcessedStick[c][0] != tempobj->Cur_Note_Section || tempobj->Recent_ProcessedStick[c][1] != tempobj->Cur_Note_Idx )) 
        {
            // 스틱이 내려오고 있어도 전혀 치지 못한 상황이기 때문에.
            tempobj->Set_Judge_Result( 1 );
            // 일단 처리된 스틱으로 간주해놓고 중복 처리를 피한다.
            tempobj->Recent_ProcessedStick[c][0] = tempobj->Cur_Note_Section;
            tempobj->Recent_ProcessedStick[c][1] = tempobj->Cur_Note_Idx;
        }
    }
    
    // 백그라운드 연주 
    for( int c = 0; c < 32; c++ )
    {
        unsigned char value;
        value = (*(tempobj->pNote_BGS))[c][tempobj->Cur_Note_Section][tempobj->Cur_Note_Idx];
        if( value != 0 ) Mixer_Play( tempobj->pWaveRes[value] );
    } 
    
    if( tempobj->Sync() )
    {
        // 노트 위치 변화후
        tempobj->Cur_Note_Idx++;
        
        // 다음섹션으로 넘겨질때 연주될 악기를 미리 알아낸다.  
        if( tempobj->Cur_Note_Idx == 32 )
        {
            tempobj->Cur_Note_Idx = 0;
            tempobj->Cur_Note_Section++;
            if( tempobj->Cur_Note_Section > tempobj->PlaySections + 1 ) tempobj->End(1);
            for( int c = 0; c < 6; c++ ) tempobj->Update_Contained_Idx( c, tempobj->Cur_Note_Section, 0 );
        }
        else
        {
            if( tempobj->Cur_Note_Idx > 0 )
            {
                unsigned char b_value;
                int tempsec = tempobj->Cur_Note_Section;
                int tempidx = tempobj->Cur_Note_Idx;
                for( int c = 0; c < 6; c++ )
                {
                    if( c >= 0 & c <= 4 ) b_value = (*tempobj->pNote_Normal)[c][tempsec][tempidx-1];
                    if( c == 5 ) b_value = (*tempobj->pNote_Sc)[tempsec][tempidx-1];
                    if( b_value != 0 ) tempobj->Update_Contained_Idx( c, tempsec, tempidx );
                }
            }
        }
    }

    // 효과 관련 변수 조정
    if( tempobj->Judge_RecentResult_RestTimeToView > 0 ) 
    {
        tempobj->Judge_RecentResult_RestTimeToView--;
        if( tempobj->Judge_RecentResult_RestTimeToView == 0 ) tempobj->Judge_RecentResult = 0;           
    }
 
    return interval;
}

void BMS_Interface::FrameProcessBMSSprite( BMSSprite *pspr )
{
    if( !pspr->IsViewing ) return;
    if( pspr->IsEnd ) return;
    pspr->WaitForSkip--;
    if( pspr->WaitForSkip == 0 )
    {
        pspr->WaitForSkip = pspr->Delay;
        if( pspr->CurDrawIdx + 1 == pspr->NumOfImgs ) 
        {
            if( pspr->IsRepeat ) 
                pspr->CurDrawIdx = 0;
            else
                pspr->IsEnd = 1;
        }
        else
            pspr->CurDrawIdx++;
    }
}

void BMS_Interface::DrawBMSSprite( BMSSprite *pspr, int x, int y )
{
    SDL_Rect dstrect;
    pspr->IsViewing = 1;
    dstrect = NewRect( x, y, x + pspr->Rect[ pspr->CurDrawIdx ].w - 1, y + pspr->Rect[ pspr->CurDrawIdx ].h - 1 );
    SDL_BlitSurface( pspr->pBaseSurface, &(pspr->Rect[pspr->CurDrawIdx]), pPrimarySurface, &dstrect );
}

void BMS_Interface::SetBaseSurfaceToFont( BMSImgFont *pimgfont, SDL_Surface *pSurface )
{
    pimgfont->pBaseSurface = pSurface;
}

void BMS_Interface::RegImgToFont( BMSImgFont *pimgfont, unsigned char idx, SDL_Rect rect )
{
    memcpy( &(pimgfont->CharImgRect[idx]), &rect, sizeof(SDL_Rect) );
}

void BMS_Interface::DrawText( BMSImgFont *pimgfont, int x, int y, char *fmt, ... )
{
    char text[256];

    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);

    int drawx = x;
    for( int n = 0 ; n < strlen(text); n++ )
    {
        char ch = text[n];
        SDL_Rect dstrect;
        dstrect = NewRect( drawx, y, drawx + pimgfont->CharImgRect[ch].w - 1, y + pimgfont->CharImgRect[ch].h - 1 );
        SDL_BlitSurface( pimgfont->pBaseSurface, &(pimgfont->CharImgRect[ch]), pPrimarySurface, &dstrect );
        drawx += (pimgfont->CharImgRect[ch].w + 1);
    }
}

void BMS_Interface::Sync_Init( void )
{
    Sync_OneBeatTime = 60000.0f / BPM / 8.0f;
    Sync_StartTime = SDL_GetTicks();
}

int BMS_Interface::Sync( void )
{
    int virtualplayingtime;
    virtualplayingtime = (int)((float)Cur_Note_Section * Sync_OneBeatTime * 32.0f);
    virtualplayingtime += (int)((float)Cur_Note_Idx * Sync_OneBeatTime );
    
    int realplayingtime = SDL_GetTicks() - Sync_StartTime;

    return(virtualplayingtime < realplayingtime);
}

float BMS_Interface::Sync_Percentage( void )
{
    int virtualplayingtime;
    virtualplayingtime = (int)(Cur_Note_Section * Sync_OneBeatTime * 32.0f);
    virtualplayingtime += (int)(Cur_Note_Idx * Sync_OneBeatTime );
    
    int realplayingtime = SDL_GetTicks() - Sync_StartTime;
    float result = (float)(realplayingtime - virtualplayingtime);

    return(result / Sync_OneBeatTime);
}

void BMS_Interface::Update_Contained_Idx( int channel, int section, int idx )
{
    while( idx < 32 )
    {
        idx++;
        unsigned char value;
        if( channel >= 0 && channel <= 4 ) value = (*pNote_Normal)[channel][section][idx];
        if( channel == 5 ) value = (*pNote_Sc)[section][idx];
        
        if( value ) Cur_Contained_Idx[channel] = value;
    } 
}

void BMS_Interface::View_Judge_Result( void )
{
    if( Judge_RecentResult_RestTimeToView % 2 ) // 홀수일때만 출력해서 깜빡거리게
    {
        if( Judge_RecentResult == 1 ) DrawBMSSprite( &Img_Poor, 10, 80 );
        if( Judge_RecentResult == 2 ) DrawBMSSprite( &Img_Bad, 10, 80 );
        if( Judge_RecentResult == 3 ) DrawBMSSprite( &Img_Good, 10, 80 );
        if( Judge_RecentResult == 4 ) DrawBMSSprite( &Img_Great, 10, 80 );
        if( Judge_RecentResult >= 2 ) DrawText( &Img_Font, 39, 110, "%3d", Status_Combo );
    } 
}

void BMS_Interface::Set_Judge_Result( int status )
{
    Judge_RecentResult = status;
    Judge_RecentResult_RestTimeToView = 100;

    // 판정 결과에 따른 처리. 
    if( status == 1 ) Status_NumOfPoor++;
    if( status == 2 ) Status_NumOfBad++;
    if( status == 3 ) Status_NumOfGood++;
    if( status == 4 ) Status_NumOfGreat++;
    
    if( status == 1 ) 
    {
        Status_Combo = 0;
        if( Status_Life > 0 ) Status_Life -= 2;
        if( Status_Life <= 0 ) End(0);
    }
    if( status >= 2 ) 
    {
        if( Status_Life < 100 ) Status_Life += (2 + (Status_Combo / 5));
        Status_Score += ((status - 1) * 50) + Status_Combo * 10;
        Status_Combo++;
        if( Status_Combo > Status_MaxCombo ) Status_MaxCombo = Status_Combo;
    }
}

void BMS_Interface::Init()
{
    pPrimarySurface = NULL;
    pBaseImgSurface = SDL_LoadBMP( "bm98play.bmp" );
    SDL_SetColorKey( pBaseImgSurface, SDL_SRCCOLORKEY, 0 );    
    
    SetBMSSprite( &Img_SynthKeyBase, pBaseImgSurface, 1,  1, 0, NewRect(  2,  3, 99, 49 ) );
    SetBMSSprite( &Img_KeyOn       , pBaseImgSurface, 1,  1, 0, NewRect(  1,178, 17, 22 ) );
    SetBMSSprite( &Img_ScOn        , pBaseImgSurface, 1,  1, 0, NewRect( 66, 93, 32, 42 ) );
    SetBMSSprite( &Img_IronStick   , pBaseImgSurface, 4, 20, 1, NewRect( 37,178, 25,  9 ),
                                                                NewRect( 37,188, 25,  9 ),
                                                                NewRect( 37,198, 25,  9 ),
                                                                NewRect( 37,208, 25,  9 ) );
    SetBMSSprite( &Img_BlueStick   , pBaseImgSurface, 4, 20, 1, NewRect( 63,178, 25,  9 ),
                                                                NewRect( 63,188, 25,  9 ),
                                                                NewRect( 63,198, 25,  9 ),
                                                                NewRect( 63,208, 25,  9 ) );
    SetBMSSprite( &Img_RedStick    , pBaseImgSurface, 4, 20, 1, NewRect( 37,239, 36,  9 ),
                                                                NewRect( 74,239, 36,  9 ),
                                                                NewRect(111,239, 36,  9 ),
                                                                NewRect( 37,249, 36,  9 ) );
    for( int c = 0; c < 6; c++ )
    SetBMSSprite( &Img_Pang[c]     , pBaseImgSurface, 3,  5, 0, NewRect(137, 60, 58, 58 ),
                                                                NewRect(137,119, 58, 58 ),
                                                                NewRect(137,178, 58, 58 ) );

    SetBMSSprite( &Img_Poor        , pBaseImgSurface, 1,  1, 0, NewRect(196,  1, 75, 22 ) );
    SetBMSSprite( &Img_Bad         , pBaseImgSurface, 1,  1, 0, NewRect(196, 24, 75, 22 ) );
    SetBMSSprite( &Img_Good        , pBaseImgSurface, 1,  1, 0, NewRect(196, 47, 75, 22 ) );
    SetBMSSprite( &Img_Great       , pBaseImgSurface, 1,  1, 0, NewRect(196, 70, 75, 22 ) );
    SetBMSSprite( &Img_RedBlendBar , pBaseImgSurface, 1,  1, 0, NewRect(565,322, 21,195 ) );
    SetBMSSprite( &Img_BlueBlendBar, pBaseImgSurface, 1,  1, 0, NewRect(565,  1, 21,195 ) );
    SetBMSSprite( &Img_BigRedBlendBar , pBaseImgSurface, 1,  1, 0, NewRect(587,322, 37,195 ) );
    SetBMSSprite( &Img_BigBlueBlendBar, pBaseImgSurface, 1,  1, 0, NewRect(587,  1, 37,195 ) );

    SetBaseSurfaceToFont( &Img_Font, pBaseImgSurface );
    RegImgToFont( &Img_Font, '0', NewRect( 273, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '1', NewRect( 289, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '2', NewRect( 305, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '3', NewRect( 321, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '4', NewRect( 337, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '5', NewRect( 353, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '6', NewRect( 369, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '7', NewRect( 385, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '8', NewRect( 401, 526, 15, 22 ));
    RegImgToFont( &Img_Font, '9', NewRect( 417, 526, 15, 22 ));

    SetBaseSurfaceToFont( &Img_ScoreFont, pBaseImgSurface );
    RegImgToFont( &Img_ScoreFont, '0', NewRect( 361, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '1', NewRect( 369, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '2', NewRect( 377, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '3', NewRect( 385, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '4', NewRect( 393, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '5', NewRect( 401, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '6', NewRect( 409, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '7', NewRect( 417, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '8', NewRect( 425, 549, 7, 15 ));
    RegImgToFont( &Img_ScoreFont, '9', NewRect( 433, 549, 7, 15 ));

    memset( Sw_ProcessedWhenOn, 0, sizeof( Sw_ProcessedWhenOn ) );
    
    memset( Sw_Key, 0, sizeof( Sw_Key ) );
    Sw_Sc = 0;
    
    Cur_Note_Section = 0;
    Cur_Note_Idx = 0;
    
    Status_Combo = 0;
    Status_Life = 100;
    
    AnimateCallBack_TimerID = SDL_AddTimer( 10, &AnimateCallBack, this );
    NoteProcessCallBack_TimerID = SDL_AddTimer( 1, &NoteProcessCallBack, this );
}

void BMS_Interface::SetPrimarySurface( SDL_Surface *pSurface )
{
    pPrimarySurface = pSurface;
}
 
void BMS_Interface::Draw()
{
    SDL_Rect dstrect = NewRect( 0, 0, 100, 240 );
    SDL_FillRect( pPrimarySurface, &dstrect, 0 );
    
    int temp_x[6] = { 1, 12, 22, 32, 42, 62 };
    for( int c = 0; c < 6; c++ )
    {
        if( c >= 0 && c <= 4 ) if( Sw_Key[c] ) DrawBMSSprite( &Img_BlueBlendBar, temp_x[c], 0 );
        if( c == 5 )           if( Sw_Sc )     DrawBMSSprite( &Img_BigBlueBlendBar , temp_x[c], 0 );
    }
 
    DrawNote();
    
    DrawBMSSprite( &Img_SynthKeyBase, 0, 192 );

    if( Sw_Key[0] ) DrawBMSSprite( &Img_KeyOn,  2, 217 );
    if( Sw_Key[1] ) DrawBMSSprite( &Img_KeyOn, 12, 197 );
    if( Sw_Key[2] ) DrawBMSSprite( &Img_KeyOn, 23, 217 );
    if( Sw_Key[3] ) DrawBMSSprite( &Img_KeyOn, 33, 197 );
    if( Sw_Key[4] ) DrawBMSSprite( &Img_KeyOn, 44, 217 );
    if( Sw_Sc     ) DrawBMSSprite( &Img_ScOn , 64, 198 );

    if( Judge_RecentResult != 0 ) View_Judge_Result();

    // 반짝하며 터지는 이미지 나타냄( 노트 악보를 맞췄을 경우 ) 
    int temp2_x[7] = { 1, 10, 20, 30, 40, 60, 60 };
    for( int c = 0; c < 6; c++ )
    {
        if( PangOperation[c] ) 
        {
            DrawBMSSprite( &Img_Pang[c], temp2_x[c] - 16, 162 );
            if( Img_Pang[c].IsEnd == 1 )
            {
                PangOperation[c] = 0;
                Img_Pang[c].IsEnd = 0;
                Img_Pang[c].IsViewing = 0;
                Img_Pang[c].CurDrawIdx = 0;
            }
        }
    }
    
    // 에너지 게이지 
    for( int c = 0; c < 100; c++ )
    {
        SDL_Rect rect = NewRect( 110 + 2 * c, 210, 1, 5 );
        if( c > Status_Life )
            SDL_FillRect( pPrimarySurface, &rect, 0xf800 );
        else
            SDL_FillRect( pPrimarySurface, &rect, 0x7c0 );
    }
    dstrect = NewRect( 110, 220, 64, 17 );
    SDL_FillRect( pPrimarySurface, &dstrect, 0x1e );
    DrawText( &Img_ScoreFont, 111, 222, "%d", Status_Score );
    
    SDL_UpdateRect( pPrimarySurface, pPrimarySurface->clip_rect.x, pPrimarySurface->clip_rect.y, pPrimarySurface->clip_rect.w, pPrimarySurface->clip_rect.h );
}

void BMS_Interface::DrawNote()
{
    int temp_section = Cur_Note_Section;
    int temp_idx = Cur_Note_Idx;
    
    int judge_ok[7] = { 0, };
    
    int gap_row = 5;
    int drawx[7] = { 1, 10, 20, 30, 40, 60, 60 };
    int drawy = 193 + (int)(Sync_Percentage() * gap_row);

    // 세로선을 그린다. 
    for( int chan = 0; chan < 5; chan++ )
    {
        SDL_Rect rect = NewRect( drawx[chan] + 13, 0, 1, 189 );
        SDL_FillRect( pPrimarySurface, &rect, 0xffff );
    }

    // 판정영역 그린다 하도 궁금해서
    while( drawy > -gap_row )
    {
        for( int chan = 0; chan < 7; chan++ )
        {
            int tempy;
            unsigned char value;
            
            if( drawy > 189 ) tempy = 189; else tempy = drawy;
            
            if( chan >= 0 && chan <= 4 ) value = (*pNote_Normal)[chan][ temp_section ][ temp_idx ];
            if( chan == 5 ) value = (*pNote_Sc)[ temp_section ][ temp_idx ];
            if( chan == 6 ) value = (*pNote_Fr)[ temp_section ][ temp_idx ];

            // 판정 구함
            if( judge_ok[chan] == 0 )
            {
                int jt = 189 - gap_row * 5;
                int jb = 194;
                
                int top = tempy + 2;
                int bottom = tempy + 2 + 4;
                
                if( bottom >= jt && bottom <= jb ) 
                {
                    // (jb - jt) - (jb - bottom) = bottom - jt
                    Judge[chan] = ( value ? (bottom - jt) * 100 / (jb - jt) : 0 );
                    if( Judge[chan] > 100 ) Judge[chan] = 100 - (Judge[chan] - 100);
                    if( value ) judge_ok[chan] = 1;
                }
                Judge_Target[chan][0] = temp_section;
                Judge_Target[chan][1] = temp_idx;
            }

            if( value != 0 )
            {
                if( chan == 0 ) DrawBMSSprite( &Img_IronStick , drawx[chan], tempy );
                if( chan == 1 ) DrawBMSSprite( &Img_BlueStick , drawx[chan], tempy );
                if( chan == 2 ) DrawBMSSprite( &Img_IronStick , drawx[chan], tempy );
                if( chan == 3 ) DrawBMSSprite( &Img_BlueStick , drawx[chan], tempy );
                if( chan == 4 ) DrawBMSSprite( &Img_IronStick , drawx[chan], tempy );
                if( chan == 5 ) DrawBMSSprite( &Img_RedStick  , drawx[chan], tempy );
                if( chan == 6 ) DrawBMSSprite( &Img_RedStick  , drawx[chan], tempy );
            }
        }
        drawy -= gap_row;         
        temp_idx++;
        if( temp_idx == 32 ) 
        {
            // 가로선을 그린다. 
            drawy--;
            SDL_Rect rect = NewRect( 0, drawy - 9, 99, 1 );
            SDL_FillRect( pPrimarySurface, &rect, 0xffff );
            drawy--;
            temp_section++;
            temp_idx = 0;
        }
    }

    // BMP그리기
    unsigned char value = (*pNote_BGA)[ Cur_Note_Section ][ Cur_Note_Idx ];
    if( value != 0 )
    {
        SDL_Rect dstrect = NewRect( 100,  0, 220, 240 );
        SDL_Rect srcrect = NewRect(   0,  0, 220, 240 );
        SDL_FillRect( pPrimarySurface, &dstrect, 0 );
        SDL_BlitSurface( pBmpRes[value], &srcrect, pPrimarySurface, &dstrect );
    }
    
    ::DrawText( pPrimarySurface, 300, 50, "%d", Status_NumOfPoor );
}

void BMS_Interface::SetTotal( int total )
{
    Total = total;
}

void BMS_Interface::SetBPM( int BPM )
{
    this->BPM = BPM;
    Sync_Init();
}

void BMS_Interface::SetPlaySections( int playsections )
{
    PlaySections = playsections;
}

void BMS_Interface::SetWaveResource( int idx, Mix_Chunk *pWaveChunk )
{
    pWaveRes[idx] = pWaveChunk;
}

void BMS_Interface::SetBmpResource( int idx, SDL_Surface *pSurface )
{
    pBmpRes[idx] = pSurface;
}

void BMS_Interface::SetNormalNote( BMS_NormalNote *pnote )
{
    pNote_Normal = pnote;
}

void BMS_Interface::SetScNote( BMS_ScNote *pnote )
{
    pNote_Sc = pnote;
}

void BMS_Interface::SetFrNote( BMS_FrNote *pnote )
{
    pNote_Fr = pnote;
}

void BMS_Interface::SetBGANote( BMS_BGANote *pnote )
{
    pNote_BGA = pnote;
}

void BMS_Interface::SetBGSNote( BMS_BGSNote *pnote )
{
    pNote_BGS = pnote;
}

void BMS_Interface::SetKeySwitch( int idx, int sw )
{
    Sw_Key[idx] = sw;
    if( sw == 1 && Sw_ProcessedWhenOn[idx] == 0 ) 
    {
        // 키를 누른 직후 상황에 판독을 한다. 이 부분에서 함. 
        Sw_ProcessedWhenOn[idx] = 1;
        if( Recent_ProcessedStick[idx][0] != Judge_Target[idx][0] || Recent_ProcessedStick[idx][1] != Judge_Target[idx][1] )
        {
            if( Judge[idx] > 85 ) 
            {
                Set_Judge_Result(  4 );
                PangOperation[idx] = 1; // Great는 터지는 효과 발생
            }
            if( Judge[idx] <= 85 && Judge[idx] > 25 ) Set_Judge_Result( 3 );
            if( Judge[idx] <= 25 && Judge[idx] > 0  ) Set_Judge_Result( 2 );
            if( Judge[idx] == 0 ) Set_Judge_Result( 1 );
        
            // 연주
            Mixer_Play( pWaveRes[ Cur_Contained_Idx[idx] ] );
       
            Recent_ProcessedStick[idx][0] = Judge_Target[idx][0];
            Recent_ProcessedStick[idx][1] = Judge_Target[idx][1];
        }
        else
            Set_Judge_Result( 1 );
    }
    if( sw == 0 ) Sw_ProcessedWhenOn[idx] = 0;
}

void BMS_Interface::SetScSwitch( int sw )
{
    Sw_Sc = sw;
    if( sw == 1 && Sw_ProcessedWhenOn[5] == 0 )
    {
        Sw_ProcessedWhenOn[5] = 1;
        if( Recent_ProcessedStick[5][0] != Judge_Target[5][0] || Recent_ProcessedStick[5][1] != Judge_Target[5][1] )
        {
            if( Judge[5] > 85 )
            {
                Set_Judge_Result( 4 );
                PangOperation[5] = 1; // Great는 터지는 효과 발생
            }
            if( Judge[5] <= 85 && Judge[5] > 25 ) Set_Judge_Result( 3 );
            if( Judge[5] <= 25 && Judge[5] > 0  ) Set_Judge_Result( 2 );
            if( Judge[5] == 0 ) Set_Judge_Result( 1 );
        
            Mixer_Play( pWaveRes[ Cur_Contained_Idx[5] ] );
       
            Recent_ProcessedStick[5][0] = Judge_Target[5][0];
            Recent_ProcessedStick[5][1] = Judge_Target[5][1];
        }
        else
            Set_Judge_Result( 1 );
    }
    if( sw == 0 ) Sw_ProcessedWhenOn[5] = 0;
}

int BMS_Interface::GetKeySwitch( int idx )
{
    return Sw_Key[idx];
}

int BMS_Interface::GetScSwitch( void )
{
    return Sw_Sc;
}

int BMS_Interface::IsPlaying( void )
{
    return( !Status_End );
}

void BMS_Interface::End( int playsuccess )
{
    SDL_RemoveTimer( AnimateCallBack_TimerID );
    SDL_RemoveTimer( NoteProcessCallBack_TimerID );
    Status_End = 1;
    Status_Success = playsuccess;
    return;
}

void BMS_Interface::ViewResult( void )
{
    SDL_FillRect( pPrimarySurface, NULL, 0 );
    SetFontSize(15);
    if( Status_Success ) 
        ::DrawText( pPrimarySurface, 10, 10, "축하합니다! 본 스테이지를 클리어 하셨습니다." );
    else
        ::DrawText( pPrimarySurface, 10, 10, "실패했습니다." );
    ::DrawText( pPrimarySurface, 10, 30, "Poor    : %d", Status_NumOfPoor  );
    ::DrawText( pPrimarySurface, 10, 50, "Bad     : %d", Status_NumOfBad   );
    ::DrawText( pPrimarySurface, 10, 70, "Good    : %d", Status_NumOfGood  );
    ::DrawText( pPrimarySurface, 10, 90, "Great   : %d", Status_NumOfGreat );
    ::DrawText( pPrimarySurface, 10, 110, "MaxCombo: %d", Status_MaxCombo   );
    ::DrawText( pPrimarySurface, 10, 130, "Score   : %d", Status_Score      );
    SDL_UpdateRect( pPrimarySurface, pPrimarySurface->clip_rect.x, pPrimarySurface->clip_rect.y, pPrimarySurface->clip_rect.w, pPrimarySurface->clip_rect.h );
    SDL_Delay( 10000 );
}

