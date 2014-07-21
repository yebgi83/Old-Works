typedef struct
{
    char id[4];
    unsigned long  wavFormatSize;
    unsigned short wavPCMFormatFlag;
    unsigned short wavChannels;
    unsigned long  wavSampleRate;
    unsigned long  wavSampleRatePerSec;
    unsigned short wavPerSecScale;
    unsigned short wavBits;
}FMTChunk;

typedef struct
{
    char id[4];
    unsigned long  wavDataSize;
}DATAChunk;

typedef struct
{
    char id[4];
    FMTChunk wavFMTChunk;
    DATAChunk wavDATAChunk;
}WAVEChunk;
        
typedef struct
{
    char id[4];
    unsigned long wavSize;
    WAVEChunk wavWAVEChunk;
}WAVEHdr;

typedef struct
{
    WAVEHdr Header;
    struct
    {
        unsigned long  nLen8;
        unsigned long  nLen16;
        unsigned long  nLen32;
        unsigned char  *pBuf8;
        unsigned short *pBuf16;
        unsigned long  *pBuf32;
    }Data;
}WAV;

unsigned char WAV_W2B( short value )
{ 
    // 음성 파일에서 0은 0x8000을 기준으로 한다.
    // 여기서 +되면 양
    // 여기서 -되면 될수록 음을 갖는다.          
    return 0x80 + (value / 256);
}

unsigned short WAV_B2W( unsigned char value )
{
    // 음성 파일에서 0은 0x80을 기준으로 한다.
    // 여기서 +되면 양
    // 여기서 -되면 될수록 음을 갖는다.          
    return (value - 0x80) << 8;
}

WAV OpenWAV( char *filename )
{
    FILE *fp = fopen( filename, "rb" );
    WAV loadwav;

    fread( &(loadwav.Header), sizeof(loadwav.Header), 1, fp );
    if( strncmp( loadwav.Header.id, "RIFF", 4 ) == 0 )
    {
        unsigned long datapos;
        unsigned long filelen;
        unsigned long datasize = loadwav.Header.wavWAVEChunk.wavDATAChunk.wavDataSize;
        unsigned char *pdata = NULL;
        datapos = ftell(fp);
        fseek( fp, 0, SEEK_END );
        filelen = ftell(fp);
        if( datasize > filelen ) datasize = filelen - 49;
        fseek( fp, datapos, SEEK_SET );
        pdata = new unsigned char [datasize];
        fread( pdata, datasize, 1, fp );

        loadwav.Data.pBuf8     = (unsigned char *) pdata;
        loadwav.Data.pBuf16    = (unsigned short *)(loadwav.Data.pBuf8);
        loadwav.Data.pBuf32    = (unsigned long  *)(loadwav.Data.pBuf8);
        loadwav.Data.nLen8     = datasize;
        loadwav.Data.nLen16    = datasize >> 1;
        loadwav.Data.nLen32    = datasize >> 2;
    }
    fclose(fp);        
    return loadwav;
}

void CloseWAV( WAV *pwav )
{
    delete (pwav->Data).pBuf8;
    memset( pwav, 0, sizeof( *pwav ) );
}

void ConvertChannels( int desire_channels, WAV *pwav )
{
    int channels = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels;
    int wavbytes = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits / 8;
    
    if( channels == desire_channels ) return;
    if( wavbytes == 1 )
    {
        if( channels == 1 && desire_channels == 2 )
        {
            unsigned char *polddata = (pwav->Data).pBuf8;
            unsigned char *pnewdata = NULL;
            unsigned long oldlen   = (pwav->Data).nLen8;
            unsigned long newlen   = oldlen << 1;
            pnewdata = new unsigned char [newlen];
            for( int c = 0; c < oldlen; c++ )
            {
                *(pnewdata + 2 * c + 0) = *(polddata + c);
                *(pnewdata + 2 * c + 1) = *(polddata + c);
            }
            (pwav->Data).pBuf8  = pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen;
            (pwav->Data).nLen16 = newlen >> 1;
            (pwav->Data).nLen32 = newlen >> 2;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels = 2;
            delete polddata;
        }
        if( channels == 2 && desire_channels == 1 )
        {
            unsigned char *polddata  = (pwav->Data).pBuf8;
            unsigned char *pnewdata  = NULL;
            unsigned long oldlen   = (pwav->Data).nLen8;
            unsigned long newlen   = oldlen >> 1;
            pnewdata = new unsigned char [newlen];
            for( int c = 0; c < newlen; c++ )
                *(pnewdata + c) = (*(polddata + 2 * c + 0) + *(polddata + 2 * c + 1)) / 2;
            (pwav->Data).pBuf8  = pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen;
            (pwav->Data).nLen16 = newlen >> 1;
            (pwav->Data).nLen32 = newlen >> 2;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels = 1;
            delete polddata;
        }
    }
    if( wavbytes == 2 )
    {
        if( channels == 1 && desire_channels == 2 )
        {
            unsigned short *polddata = (pwav->Data).pBuf16;
            unsigned short *pnewdata = NULL;
            unsigned long  oldlen   = (pwav->Data).nLen16;
            unsigned long  newlen   = oldlen << 1;
            pnewdata = new unsigned short [newlen];
            for( int c = 0; c < oldlen; c++ )
            {
                *(pnewdata + 2 * c + 0) = *(polddata + c);
                *(pnewdata + 2 * c + 1) = *(polddata + c);
            }
            (pwav->Data).pBuf32 = (unsigned long *)pnewdata;
            (pwav->Data).pBuf16 = pnewdata;
            (pwav->Data).pBuf8  = (unsigned char *)pnewdata;
            (pwav->Data).nLen32 = newlen >> 1;
            (pwav->Data).nLen16 = newlen;
            (pwav->Data).nLen8  = newlen << 1;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels = 2;
            delete polddata;
        }
        if( channels == 2 && desire_channels == 1 )
        {
            unsigned short *polddata = (pwav->Data).pBuf16;
            unsigned short *pnewdata = NULL;
            unsigned long oldlen   = (pwav->Data).nLen16;
            unsigned long newlen   = oldlen >> 1;
            pnewdata = new unsigned short [newlen];
            for( int c = 0; c < newlen; c++ )
                *(pnewdata + c) = (*(polddata + 2 * c + 0) + *(polddata + 2 * c + 1)) / 2;
            (pwav->Data).pBuf32 = (unsigned long *)pnewdata;
            (pwav->Data).pBuf16 = pnewdata;
            (pwav->Data).pBuf8  = (unsigned char *)pnewdata;
            (pwav->Data).nLen32 = newlen << 1;
            (pwav->Data).nLen16 = newlen;
            (pwav->Data).nLen8  = newlen >> 1;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels = 1;
            delete polddata;
        }
    }
}

void ConvertWavBytes( int desire_wavbytes, WAV *pwav )
{
    int channels = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels;
    int wavbytes = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits / 8;

    if( wavbytes == desire_wavbytes ) return;
    if( channels == 1 )
    {
        if( wavbytes == 1 && desire_wavbytes == 2 )
        {
            unsigned char *polddata    = (pwav->Data).pBuf8;
            unsigned short *pnewdata   = NULL;
            unsigned long  oldlen    = (pwav->Data).nLen8;
            unsigned long  newlen    = oldlen;
            pnewdata = new unsigned short [newlen];
            for( int c = 0; c < newlen; c++ )
            {
                unsigned char unsigndatum = *(polddata + c);
                signed  short signdatum;
                signdatum = unsigndatum - 128;
                *(pnewdata + c) = (unsigned short)(signdatum * 256);
            }
            (pwav->Data).pBuf8  = (unsigned char *)pnewdata;
            (pwav->Data).pBuf16 = pnewdata;
            (pwav->Data).pBuf32 = (unsigned long *)pnewdata;
            (pwav->Data).nLen8  = newlen >> 1;
            (pwav->Data).nLen16 = newlen;
            (pwav->Data).nLen32 = newlen << 1;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits = 16;
            delete polddata;
        }
        else
        if( wavbytes == 2 && desire_wavbytes == 1 )
        {
            unsigned   short *polddata = (pwav->Data).pBuf16;
            unsigned   char  *pnewdata = NULL;
            unsigned long  oldlen    = (pwav->Data).nLen16;
            unsigned long  newlen    = oldlen;
            pnewdata = new unsigned char [newlen];
            for( int c = 0; c < newlen; c++ )
            {
                signed short signdatum = (unsigned short)*(polddata + c);
                signdatum /= 256;
                *(pnewdata + c) = (unsigned char)signdatum;
            }
            (pwav->Data).pBuf8  = pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen;
            (pwav->Data).nLen16 = newlen >> 1;
            (pwav->Data).nLen32 = newlen >> 2;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits = 8;
            delete polddata;
        }
    }
    if( channels == 2 )
    {
        if( wavbytes == 1 && desire_wavbytes == 2 )
        {
            unsigned short *polddata = (unsigned short *)(pwav->Data).pBuf16;
            unsigned long  *pnewdata = NULL;
            unsigned long oldlen    = (pwav->Data).nLen16;
            unsigned long newlen    = oldlen;
            pnewdata = new unsigned long [newlen];
            for( int c = 0; c < newlen; c++ )
            {
                unsigned short n;
                unsigned long  res;
                unsigned char  nl, nr;
                n    = *(polddata + c);
                nr   = (n & 0x00ff);
                nl   = ((n & 0xff00) >> 8);
                res  = (WAV_B2W(nl) << 16) | WAV_B2W(nr);
                *(pnewdata + c) = res;
            }
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen << 2;
            (pwav->Data).nLen16 = newlen << 1;
            (pwav->Data).nLen32 = newlen;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits = 16;
            delete polddata;
        }
        else
        if( wavbytes == 2 && desire_wavbytes == 1 )
        {
            unsigned long  *polddata = (unsigned long *)(pwav->Data).pBuf32;
            unsigned short *pnewdata = NULL;
            unsigned long  oldlen  = (pwav->Data).nLen32;
            unsigned long  newlen  = oldlen;
            pnewdata = new unsigned short [newlen];
            for( int c = 0; c < newlen; c++ )
            {
                unsigned long  n;
                unsigned short res;
                unsigned short nl, nr;
                n   = *(polddata + c);
                nr  = (n & 0x0000ff00);
                nl  = (n & 0xff000000) >> 16;
                res = (WAV_W2B(nl) << 8) | WAV_W2B(nr);
                *(pnewdata + c) = res;
            }
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen >> 1;
            (pwav->Data).nLen16 = newlen;
            (pwav->Data).nLen32 = newlen << 1;
            (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits = 8;
            delete polddata;
        }
    }
}

void ConvertSampleRate( int desire_samplerate, WAV *pwav )
{
    int samplerate = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavSampleRate;
    int channels = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavChannels;
    int wavbytes = (pwav->Header).wavWAVEChunk.wavFMTChunk.wavBits / 8;
    int bytes = channels * wavbytes;

    if( samplerate == desire_samplerate ) return;
    if( bytes == 1 )
    {
        if( desire_samplerate > samplerate )
        {
            int padding = (int)((float)desire_samplerate / samplerate + 0.5f);
            int memidx  = 0;
            unsigned char *polddata = (pwav->Data).pBuf8;
            unsigned char *pnewdata = NULL;
            unsigned long oldlen    = (pwav->Data).nLen8;
            unsigned long newlen    = oldlen * padding;
            pnewdata = new unsigned char [newlen];
            for( int c1 = 0; c1 < oldlen; c1++ )
                for( int c2 = 0; c2 < padding; c2++ )
                   *(pnewdata + memidx++) = *(polddata + c1);
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen;
            (pwav->Data).nLen16 = newlen >> 1;
            (pwav->Data).nLen32 = newlen >> 2;
            delete polddata;
        }        
        if( desire_samplerate < samplerate )
        {
            int invpadding = (int)((float)samplerate / desire_samplerate + 0.5f);
            unsigned char *polddata = (pwav->Data).pBuf8;
            unsigned char *pnewdata = NULL;
            unsigned long oldlen    = (pwav->Data).nLen8;
            unsigned long newlen    = oldlen / invpadding;
            pnewdata = new unsigned char [newlen];
            for( int c = 0; c < newlen; c++ )
                *(pnewdata + c) = *(polddata + invpadding * c);
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen;
            (pwav->Data).nLen16 = newlen >> 1;
            (pwav->Data).nLen32 = newlen >> 2;
            delete polddata;
        }        
    }

    if( bytes == 2 )
    {
        if( desire_samplerate > samplerate )
        {
            int padding = (int)((float)desire_samplerate / samplerate + 0.5f);
            int memidx  = 0;
            unsigned short *polddata = (pwav->Data).pBuf16;
            unsigned short *pnewdata = NULL;
            unsigned long  oldlen    = (pwav->Data).nLen16;
            unsigned long  newlen    = oldlen * padding;
            pnewdata = new unsigned short [newlen];
            for( int c1 = 0; c1 < oldlen; c1++ )
                for( int c2 = 0; c2 < padding; c2++ )
                   *(pnewdata + memidx++) = *(polddata + c1);
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen << 1;
            (pwav->Data).nLen16 = newlen;
            (pwav->Data).nLen32 = newlen >> 1;
            delete polddata;
        }        
        if( desire_samplerate < samplerate )
        {
            int invpadding = (int)((float)samplerate / desire_samplerate + 0.5f);
            unsigned short *polddata = (pwav->Data).pBuf16;
            unsigned short *pnewdata = NULL;
            unsigned long  oldlen    = (pwav->Data).nLen16;
            unsigned long  newlen    = oldlen / invpadding;
            pnewdata = new unsigned short [newlen];
            for( int c = 0; c < newlen; c++ )
                *(pnewdata + c) = *(polddata + invpadding * c);
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen << 1;
            (pwav->Data).nLen16 = newlen;
            (pwav->Data).nLen32 = newlen >> 1;
            delete polddata;
        }        
    }
    
    if( bytes == 4 )
    {
        if( desire_samplerate > samplerate )
        {
            int padding = (int)((float)desire_samplerate / samplerate + 0.5f);
            int memidx  = 0;
            unsigned long *polddata = (pwav->Data).pBuf32;
            unsigned long *pnewdata = NULL;
            unsigned long oldlen    = (pwav->Data).nLen32;
            unsigned long newlen    = oldlen * padding;
            pnewdata = new unsigned long [newlen];
            for( int c1 = 0; c1 < oldlen; c1++ )
                for( int c2 = 0; c2 < padding; c2++ )
                   *(pnewdata + memidx++) = *(polddata + c1);
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen << 2;
            (pwav->Data).nLen16 = newlen << 1;
            (pwav->Data).nLen32 = newlen;
            delete polddata;
        }        
        if( desire_samplerate < samplerate )
        {
            int invpadding = (int)((float)samplerate / desire_samplerate + 0.5f);
            unsigned long *polddata = (pwav->Data).pBuf32;
            unsigned long *pnewdata = NULL;
            unsigned long oldlen    = (pwav->Data).nLen32;
            unsigned long newlen    = oldlen / invpadding;
            pnewdata = new unsigned long [newlen];
            for( int c = 0; c < newlen; c++ )
                *(pnewdata + c) = *(polddata + invpadding * c);
            (pwav->Data).pBuf8  = (unsigned char  *)pnewdata;
            (pwav->Data).pBuf16 = (unsigned short *)pnewdata;
            (pwav->Data).pBuf32 = (unsigned long  *)pnewdata;
            (pwav->Data).nLen8  = newlen << 2;
            (pwav->Data).nLen16 = newlen << 1;
            (pwav->Data).nLen32 = newlen;
            delete polddata;
        }        
    }
    
    (pwav->Header).wavWAVEChunk.wavFMTChunk.wavSampleRate = desire_samplerate;
}

void MakeFixedWAV( WAV *pwav )
{ 
    int desire_samplerate = 44100;
    int desire_channels   = 2;
    int desire_bytes      = 2;
    
    ConvertChannels( desire_channels, pwav );
    ConvertWavBytes( desire_bytes, pwav );
    ConvertSampleRate( desire_samplerate, pwav );
    return;
}

void PlayWAV( WAV wav )
{
    HWAVEOUT hwo;
    WAVEFORMATEX wfex;

    wfex.wFormatTag = wav.Header.wavWAVEChunk.wavFMTChunk.wavPCMFormatFlag;
    wfex.nChannels  = wav.Header.wavWAVEChunk.wavFMTChunk.wavChannels;
    wfex.nSamplesPerSec = wav.Header.wavWAVEChunk.wavFMTChunk.wavSampleRate;
    wfex.nAvgBytesPerSec = wav.Header.wavWAVEChunk.wavFMTChunk.wavSampleRatePerSec;
    wfex.nBlockAlign = wav.Header.wavWAVEChunk.wavFMTChunk.wavPerSecScale;
    wfex.wBitsPerSample = wav.Header.wavWAVEChunk.wavFMTChunk.wavBits; 
    wfex.cbSize = sizeof(wfex);

    waveOutOpen( &hwo, 
                 WAVE_MAPPER, 
                 &wfex,
                 0,
                 0,
                 CALLBACK_NULL );
                 
    WAVEHDR wavehdr;
    wavehdr.lpData = (char *)wav.Data.pBuf8;
    wavehdr.dwBufferLength = wav.Data.nLen8;
    wavehdr.dwBytesRecorded = 0;
    wavehdr.dwUser = 0;
    wavehdr.dwFlags = WHDR_DONE;
    wavehdr.dwLoops = 1;
    wavehdr.lpNext = NULL;
    wavehdr.reserved = 0;

    waveOutPrepareHeader ( hwo, &wavehdr, sizeof(WAVEHDR) ) ;
    waveOutWrite( hwo, &wavehdr, sizeof(WAVEHDR) );
    printf("%d bits, %s, %dKhz  Length = %lu\n", wfex.wBitsPerSample
                                               , ( wfex.nChannels == 1 ? "mono" : "stereo" )
                                               , wfex.nSamplesPerSec
                                               , wavehdr.dwBufferLength );
    printf("Playing WAV. Press any key to stop playing..\n"); 
    getch();
    waveOutReset( hwo );
    waveOutClose( hwo );
}
