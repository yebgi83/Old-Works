typedef struct
{
    bool Writed;
    PAVIFILE pFile;
    struct
    {
       AVISTREAMINFO  Info;
       PAVISTREAM     pHandle;
       PAVISTREAM     pCompressed;
       int nFrame;
    }VideoStream;
/*  struct
    {
       AVISTREAMINFO  Info;
       PAVISTREAM     pHandle;
       int nSamp;
    }AudioStream; */
}AVI;

AVI CreateAVI( char *filename, int period )
{
    AVI avi;
    AVISTREAMINFO si;

    printf("Createing AVI.\n");
    memset( &avi, 0, sizeof(avi) );
    
    
    si.fccType         = streamtypeVIDEO;
    si.fccHandler      = (DWORD)( mmioFOURCC('D','I','B',' ') );
    si.dwFlags         = 0;
    si.dwCaps          = 0;
    si.wPriority       = 0;
    si.wLanguage       = 0;
    si.dwScale         = period;
    si.dwRate          = 1000;
    si.dwStart         = 0;
    si.dwLength        = si.dwRate * si.dwScale;
    si.dwInitialFrames = 0;
    si.dwSuggestedBufferSize = 0;
    si.dwQuality       = (DWORD)-1;
    si.dwSampleSize    = 0;
    si.rcFrame.left    = 0;
    si.rcFrame.top     = 0;
    si.rcFrame.right   = 256;
    si.rcFrame.bottom  = 256;
    si.dwEditCount     = 0;
    si.dwFormatChangeCount = 0;
    strcpy( si.szName, "" );
    memcpy( &(avi.VideoStream.Info), &si, sizeof(si) );

    AVIFileInit();    
    if( AVIFileOpen( &(avi.pFile), filename, OF_CREATE | OF_WRITE | OF_SHARE_DENY_NONE,NULL ) != 0 )
        printf("AVIFileOpen error.\n");
    if( AVIFileCreateStream( avi.pFile, &(avi.VideoStream.pHandle), &(avi.VideoStream.Info) ) != 0 )
        printf("AVIFileCreateStream error.\n");
    
    AVICOMPRESSOPTIONS opt;
    AVICOMPRESSOPTIONS *aopts[1];
    aopts[0] = &opt;
    memset( &opt, 0, sizeof(opt) );

    AVISaveOptions( NULL, 0, 1, &(avi.VideoStream.pHandle), aopts );
    if( AVIMakeCompressedStream( &(avi.VideoStream.pCompressed), avi.VideoStream.pHandle, aopts[0], NULL) != 0 )
        printf("AVIMakeCompressedStream error.\n");
    
    printf("Initialize OK.\n");
    return avi;
}

AVI CloseAVI( AVI *pavi )
{
    if( (pavi->VideoStream).pCompressed != NULL ) AVIStreamRelease( (pavi->VideoStream).pCompressed );    
    if( (pavi->VideoStream).pHandle != NULL ) AVIStreamRelease( (pavi->VideoStream).pHandle );    
//    if( (pavi->AudioStream).pHandle != NULL ) AVIStreamRelease( (pavi->AudioStream).pHandle );    
    AVIFileRelease( pavi->pFile );    
    AVIFileExit();    
}

void SkipFrame( AVI *pavi )
{
     printf("\r %d Frame : Skip.      ", (pavi->VideoStream).nFrame);
    (pavi->VideoStream).nFrame++;
}

void AddVideoFrame( AVI *pavi, IMG img )
{
    img.Info.Header.biWidth = (pavi->VideoStream).Info.rcFrame.right;
    img.Info.Header.biHeight = (pavi->VideoStream).Info.rcFrame.bottom;
    
    if( img.Loaded == TRUE )
    {
        printf("\r %d Frame : ");
        if( pavi->Writed == FALSE )
        {
            pavi->Writed = TRUE;
            AVIStreamSetFormat( (pavi->VideoStream).pCompressed, 0, &(img.Info.Header), img.Info.cbSize );
        }
        else
        {
            if( AVIStreamWrite( (pavi->VideoStream).pCompressed, (pavi->VideoStream).nFrame, 1, img.Data.pData, img.Data.cbSize, AVIIF_KEYFRAME, NULL, NULL ) != 0 )
                printf("Fail.     ");
            else
                printf("Completed.");
        }
    }
    else
    (pavi->VideoStream).nFrame++;
}
