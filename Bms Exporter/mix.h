#define MIX_CHANNELS 64 // 최대 채널 수  

typedef struct
{
    struct
    {
        bool isUsed;
        int nCur8;
        int nCur16;
        int nCur32;
        int nLen8;
        int nLen16;
        int nLen32;
        unsigned char *pData8;
        unsigned short *pData16;
        unsigned long  *pData32;
    }Channel[MIX_CHANNELS];
}MIXStatus;

typedef struct
{
    unsigned long  nCur8;
    unsigned long  nCur16;
    unsigned long  nCur32;
    unsigned long  nLen8;
    unsigned long  nLen16;
    unsigned long  nLen32;
    unsigned char  *pData8;
    unsigned short *pData16;
    unsigned long  *pData32;
}MIXOutput;

typedef struct tagMIX
{
    int wavBytes;
    int Channels;
    int nSampleRate;
    int nBytesAtOnce;
    MIXStatus Status;
    MIXOutput Output;
}MIX;

MIX InitMIX( void )
{
    MIX tmpmix;
    tmpmix.wavBytes        = 0;
    tmpmix.Channels        = 0;
    tmpmix.nSampleRate     = 0;
    tmpmix.nBytesAtOnce    = 0;
    tmpmix.Output.nCur8    = 0;
    tmpmix.Output.nCur16   = 0;
    tmpmix.Output.nCur32   = 0;
    tmpmix.Output.nLen8    = 0;
    tmpmix.Output.nLen16   = 0;
    tmpmix.Output.nLen32   = 0;
    for( int c = 0; c < MIX_CHANNELS; c++ )
    {
        tmpmix.Status.Channel[c].isUsed  = FALSE;
        tmpmix.Status.Channel[c].pData8  = NULL;
        tmpmix.Status.Channel[c].pData16 = NULL;
        tmpmix.Status.Channel[c].pData32 = NULL;
        tmpmix.Status.Channel[c].nLen8   = 0;
        tmpmix.Status.Channel[c].nLen16  = 0;
        tmpmix.Status.Channel[c].nLen32  = 0;
        tmpmix.Status.Channel[c].nCur8   = 0;
        tmpmix.Status.Channel[c].nCur16  = 0;
        tmpmix.Status.Channel[c].nCur32  = 0;
    }
    return tmpmix;
}

MIX OpenMIX( int samplerate, int channels, int nbytesatonce, int wavbytes, int nbufsize )
{
    MIX tmpmix;
    unsigned short bytes = channels * wavbytes;
    unsigned char *pdata = NULL;
    pdata = new unsigned char [nbufsize];
    memset( pdata, 0, nbufsize );
    
    if( pdata == NULL ) 
    {
        printf("Error : 메모리 할당에 실패했습니다.\n");
        return tmpmix;
    }         
    else
        printf("%d Allocated to mixing.\n", nbufsize);

    if( bytes == 1 )
    {
        tmpmix.Output.nLen8   = nbufsize;
        tmpmix.Output.nLen16  = nbufsize >> 1;   
        tmpmix.Output.nLen32  = nbufsize >> 2;   
    }
    if( bytes == 2 )
    {
        tmpmix.Output.nLen8  = nbufsize;
        tmpmix.Output.nLen16 = nbufsize >> 1;   
        tmpmix.Output.nLen32 = nbufsize >> 2;   
    }
    if( bytes == 4 )
    {
        tmpmix.Output.nLen8  = nbufsize;
        tmpmix.Output.nLen16 = nbufsize >> 1;   
        tmpmix.Output.nLen32 = nbufsize >> 2;
    }
    
    tmpmix.Output.nCur8    = 0;
    tmpmix.Output.nCur16   = 0;
    tmpmix.Output.pData8  = (unsigned char  *)pdata;
    tmpmix.Output.pData16 = (unsigned short *)pdata;
    tmpmix.Output.pData32 = (unsigned long  *)pdata;
    tmpmix.wavBytes        = wavbytes;
    tmpmix.Channels        = channels;
    tmpmix.nSampleRate     = samplerate;
    tmpmix.nBytesAtOnce    = nbytesatonce;
    for( int c = 0; c < MIX_CHANNELS; c++ )
    {
        tmpmix.Status.Channel[c].isUsed  = FALSE;
        tmpmix.Status.Channel[c].pData8  = NULL;
        tmpmix.Status.Channel[c].pData16 = NULL;
        tmpmix.Status.Channel[c].pData32 = NULL;
        tmpmix.Status.Channel[c].nLen8   = 0;
        tmpmix.Status.Channel[c].nLen16  = 0;
        tmpmix.Status.Channel[c].nLen32  = 0;
        tmpmix.Status.Channel[c].nCur8   = 0;
        tmpmix.Status.Channel[c].nCur16  = 0;
        tmpmix.Status.Channel[c].nCur32  = 0;
    }
    return tmpmix;
}

void CloseMIX( MIX *pmix )
{
    delete (pmix->Output).pData8;
    (pmix->Output).pData8   = NULL;  
    (pmix->Output).pData16  = NULL;  
    (pmix->Output).pData32  = NULL;  
    (pmix->Output).nCur8    = 0;
    (pmix->Output).nCur16   = 0;
    (pmix->Output).nCur32   = 0;
    (pmix->Output).nLen8    = 0;
    (pmix->Output).nLen16   = 0;
    (pmix->Output).nLen32   = 0;
    pmix->wavBytes          = 0;
    pmix->Channels          = 0;
    pmix->nSampleRate       = 0;
    pmix->nBytesAtOnce      = 0;
    for( int c = 0; c < MIX_CHANNELS; c++ )
    {
        (pmix->Status).Channel[c].isUsed  = FALSE;
        (pmix->Status).Channel[c].pData8  = NULL;
        (pmix->Status).Channel[c].pData16 = NULL;
        (pmix->Status).Channel[c].pData32 = NULL;
        (pmix->Status).Channel[c].nLen8   = 0;
        (pmix->Status).Channel[c].nLen16  = 0;
        (pmix->Status).Channel[c].nLen32  = 0;
        (pmix->Status).Channel[c].nCur8   = 0;
        (pmix->Status).Channel[c].nCur16  = 0;
        (pmix->Status).Channel[c].nCur32  = 0;
    }
}

void AddChannel( MIX *pmix, WAV wav )
{
    for( int idx = 0; idx < MIX_CHANNELS; idx++ )
    {
         if( (pmix->Status).Channel[idx].isUsed == FALSE )
         {
             (pmix->Status).Channel[idx].isUsed  = TRUE;
             (pmix->Status).Channel[idx].pData8  = wav.Data.pBuf8;
             (pmix->Status).Channel[idx].pData16 = wav.Data.pBuf16;
             (pmix->Status).Channel[idx].pData32 = wav.Data.pBuf32;
             (pmix->Status).Channel[idx].nLen8   = wav.Data.nLen8;
             (pmix->Status).Channel[idx].nLen16  = wav.Data.nLen16;
             (pmix->Status).Channel[idx].nLen32  = wav.Data.nLen32;
             (pmix->Status).Channel[idx].nCur8   = 0;
             (pmix->Status).Channel[idx].nCur16  = 0;
             (pmix->Status).Channel[idx].nCur32  = 0;
             break;
         }
    }
}

int DoMix( MIX *pmix )
{
    int c1, c2;
    for( c1 = 0; c1 < pmix->nBytesAtOnce / pmix->wavBytes; c1++ )
    {
        int nmulti = 0, sum = 0;

        /* 채널 처리 */ 
        for( c2 = 0; c2 < MIX_CHANNELS; c2++ )
        {
            if( (pmix->Status).Channel[c2].isUsed == TRUE && (pmix->Status).Channel[c2].nLen8 == 0 )  
                (pmix->Status).Channel[c2].isUsed = FALSE;
                
            if( (pmix->Status).Channel[c2].isUsed == TRUE && (pmix->Status).Channel[c2].nLen8 > 0 )  
            {
                if( pmix->wavBytes == 1 )
                {
                    char datum = *((pmix->Status).Channel[c2].pData8 + (pmix->Status).Channel[c2].nCur8);
                    sum += datum;
                    (pmix->Status).Channel[c2].nCur8++;
                    if( datum != 0 ) nmulti++;
                    if( (pmix->Status).Channel[c2].nCur8 >= (pmix->Status).Channel[c2].nLen8 - 1 )
                    {
                        (pmix->Status).Channel[c2].isUsed = FALSE;
                        (pmix->Status).Channel[c2].nCur8  = 0;
                        (pmix->Status).Channel[c2].nCur16 = 0;
                        (pmix->Status).Channel[c2].nCur32 = 0;
                    }
                    else
                    {
                        (pmix->Status).Channel[c2].nCur16 = (pmix->Status).Channel[c2].nCur8  >> 1;
                        (pmix->Status).Channel[c2].nCur32 = (pmix->Status).Channel[c2].nCur16 >> 1;
                    }
                }
                if( pmix->wavBytes == 2 )
                {
                    short datum = *((pmix->Status).Channel[c2].pData16 + (pmix->Status).Channel[c2].nCur16);
                    sum += datum;
                    (pmix->Status).Channel[c2].nCur16++;
                    if( datum != 0 ) nmulti++;
                    if( (pmix->Status).Channel[c2].nCur16 >= (pmix->Status).Channel[c2].nLen16 - 1 )
                    {
                        (pmix->Status).Channel[c2].isUsed = FALSE;
                        (pmix->Status).Channel[c2].nCur8  = 0;
                        (pmix->Status).Channel[c2].nCur16 = 0;
                        (pmix->Status).Channel[c2].nCur32 = 0;
                    }
                    else
                    {
                        (pmix->Status).Channel[c2].nCur8  = (pmix->Status).Channel[c2].nCur16 << 1;
                        (pmix->Status).Channel[c2].nCur32 = (pmix->Status).Channel[c2].nCur16 >> 1;
                    }
                }
            }
        }

        /* 처리 후 */ 
        if( pmix->wavBytes == 1 )
        {
            if( sum > 255 ) sum = 255;
            if( sum < -255 ) sum = -255;
            
            if( nmulti == 0 )
                *((pmix->Output).pData8 + (pmix->Output).nCur8) = 0;
            else
                *((pmix->Output).pData8 + (pmix->Output).nCur8) = sum;
                
            (pmix->Output).nCur8++;
            (pmix->Output).nCur16 = (pmix->Output).nCur8  >> 1;
            (pmix->Output).nCur32 = (pmix->Output).nCur16 >> 1;
        }
        
        if( pmix->wavBytes == 2 )
        {
            if( sum > 32767 ) sum = 32767;
            if( sum < -32767 ) sum = -32767;
                    
            if( nmulti == 0 )
                *((pmix->Output).pData16 + (pmix->Output).nCur16) = 0;
            else
                *((pmix->Output).pData16 + (pmix->Output).nCur16) = sum;
                
            (pmix->Output).nCur16++;
            (pmix->Output).nCur8  = (pmix->Output).nCur16 << 1;
            (pmix->Output).nCur32 = (pmix->Output).nCur16 >> 1;
        }
    }
    return (pmix->Output).nCur8;
}

void SaveWAV( MIX *pmix, char *filename )
{
    WAV tmpwav;
    
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavFormatSize       = sizeof(FMTChunk) - 8;
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavPCMFormatFlag    = 1;
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavChannels         = pmix->Channels;
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavSampleRate       = pmix->nSampleRate;
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavSampleRatePerSec = pmix->nSampleRate * pmix->Channels;
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavPerSecScale      = pmix->wavBytes;
    tmpwav.Header.wavWAVEChunk.wavFMTChunk.wavBits             = pmix->wavBytes * 8;
    
    tmpwav.Data.pBuf8  = (pmix->Output).pData8;
    tmpwav.Data.pBuf16 = (pmix->Output).pData16;
    tmpwav.Data.pBuf32 = (pmix->Output).pData32;
    tmpwav.Data.nLen8  = (pmix->Output).nLen8;
    tmpwav.Data.nLen16 = (pmix->Output).nLen16;
    tmpwav.Data.nLen32 = (pmix->Output).nLen32;

    strncpy( tmpwav.Header.id, "RIFF", 4 );
    strncpy( tmpwav.Header.wavWAVEChunk.id, "WAVE", 4 );
    strncpy( tmpwav.Header.wavWAVEChunk.wavFMTChunk.id, "fmt ", 4 );
    strncpy( tmpwav.Header.wavWAVEChunk.wavDATAChunk.id, "data", 4 );
    tmpwav.Header.wavSize = tmpwav.Data.nLen8 - sizeof(WAVEChunk);
    tmpwav.Header.wavWAVEChunk.wavDATAChunk.wavDataSize = tmpwav.Data.nLen8;
    
/*    FILE *fp = fopen( filename, "wb" );
    printf( "Saving %s\n", filename ); 
    fwrite( &(tmpwav.Header), sizeof(tmpwav.Header), 1, fp );
    fwrite( tmpwav.Data.pBuf8, tmpwav.Data.nLen8, 1, fp );*/
    PlayWAV( tmpwav );
//    fclose(fp);
}

// #include "mp3conv.h"
