#include "BladeMP3EncDLL.h"

static BEINITSTREAM		beInitStream     = NULL;
static BEENCODECHUNK	beEncodeChunk    = NULL;
static BEDEINITSTREAM	beDeinitStream   = NULL;
static BECLOSESTREAM	beCloseStream    = NULL;
static BEVERSION		beVersion        = NULL;
static BEWRITEVBRHEADER	beWriteVBRHeader = NULL;
static BEWRITEINFOTAG	beWriteInfoTag   = NULL;
static BE_VERSION	    Version			 = {0,};
static BE_CONFIG	    beConfig		 = {0,};

static HINSTANCE hDLL;

void InitMP3Converter( void )
{
    printf ("Loading lame_enc.dll\n");
    hDLL = LoadLibrary("lame_enc.dll");
  	if( NULL == hDLL ) 
    {
        hDLL = LoadLibrary("lame_enc.dll");
   	    if( NULL == hDLL )
 	    {
	   	    printf("Error loading lame_enc.DLL");
		    return;
	    }
   	
      	beInitStream	= (BEINITSTREAM) GetProcAddress(hDLL, TEXT_BEINITSTREAM);
	    beEncodeChunk	= (BEENCODECHUNK) GetProcAddress(hDLL, TEXT_BEENCODECHUNK);
	    beDeinitStream	= (BEDEINITSTREAM) GetProcAddress(hDLL, TEXT_BEDEINITSTREAM);
	    beCloseStream	= (BECLOSESTREAM) GetProcAddress(hDLL, TEXT_BECLOSESTREAM);
	    beVersion		= (BEVERSION) GetProcAddress(hDLL, TEXT_BEVERSION);
	    beWriteVBRHeader= (BEWRITEVBRHEADER) GetProcAddress(hDLL,TEXT_BEWRITEVBRHEADER);
	    beWriteInfoTag  = (BEWRITEINFOTAG) GetProcAddress(hDLL,TEXT_BEWRITEINFOTAG);

	    if(!beInitStream || !beEncodeChunk || !beDeinitStream || !beCloseStream || !beVersion || !beWriteVBRHeader)
	    {
	  	    printf("Unable to get LAME interfaces");
		    return;
	    } 
    }
    
    beVersion( &Version );
    printf("Lame encoder interface initialized. Version = %d\n", Version);
}

void SaveMP3( MIX *pmix )
{
    FILE       *pFileOut;
    
    DWORD		dwSamples	= 0;
	DWORD		dwMP3Buffer	= 0;
	HBE_STREAM	hbeStream	= 0;
	BE_ERR		err			= 0; 
	
    PBYTE       pmp3buf     = NULL;
    PSHORT      pwavbuf     = NULL;
    
	memset(&beConfig,0,sizeof(beConfig));					// clear all fields

	// use the LAME config structure
	beConfig.dwConfig = BE_CONFIG_LAME;

	// this are the default settings for testcase.wav
	beConfig.format.LHV1.dwStructVersion	= 1;
	beConfig.format.LHV1.dwStructSize		= sizeof(beConfig);		
	beConfig.format.LHV1.dwSampleRate		= 44100;				// INPUT FREQUENCY
	beConfig.format.LHV1.dwReSampleRate		= 0;					// DON"T RESAMPLE
	beConfig.format.LHV1.nMode				= BE_MP3_MODE_JSTEREO;	// OUTPUT IN STREO
	beConfig.format.LHV1.dwBitrate			= 128;					// MINIMUM BIT RATE
	beConfig.format.LHV1.nPreset			= LQP_R3MIX;		// QUALITY PRESET SETTING
	beConfig.format.LHV1.dwMpegVersion		= MPEG1;				// MPEG VERSION (I or II)
	beConfig.format.LHV1.dwPsyModel			= 0;					// USE DEFAULT PSYCHOACOUSTIC MODEL 
	beConfig.format.LHV1.dwEmphasis			= 0;					// NO EMPHASIS TURNED ON
	beConfig.format.LHV1.bOriginal			= TRUE;					// SET ORIGINAL FLAG
	beConfig.format.LHV1.bWriteVBRHeader	= TRUE;					// Write INFO tag

//	beConfig.format.LHV1.dwMaxBitrate		= 320;					// MAXIMUM BIT RATE
//	beConfig.format.LHV1.bCRC				= TRUE;					// INSERT CRC
//	beConfig.format.LHV1.bCopyright			= TRUE;					// SET COPYRIGHT FLAG	
//	beConfig.format.LHV1.bPrivate			= TRUE;					// SET PRIVATE FLAG
//	beConfig.format.LHV1.bWriteVBRHeader	= TRUE;					// YES, WRITE THE XING VBR HEADER
//	beConfig.format.LHV1.bEnableVBR			= TRUE;					// USE VBR
//	beConfig.format.LHV1.nVBRQuality		= 5;					// SET VBR QUALITY
	beConfig.format.LHV1.bNoRes				= TRUE;					// No Bit resorvoir

// Preset Test
//	beConfig.format.LHV1.nPreset			= LQP_PHONE;

	// Init the MP3 Stream
	err = beInitStream(&beConfig, &dwSamples, &dwMP3Buffer, &hbeStream);

	// Check result
	if(err != BE_ERR_SUCCESSFUL)
	{
		printf("Error opening encoding stream (%lu)", err);
		return;
	}     
	
	// Open MP3 file
	pFileOut= fopen("test.mp3","wb+");

	// Check file open result
	if(pFileOut == NULL)
	{
		printf("Error creating file.");
		return;
	}

	// Allocate MP3 buffer
	pmp3buf = new BYTE [dwMP3Buffer];

	// Allocate WAV buffer
	pwavbuf = (SHORT *)(pmix->Output).pData16;

	// Check if Buffer are allocated properly
	if(!pmp3buf || !pwavbuf)
	{
		printf("Out of memory");
		return;
	}
	
	DWORD dwRead       = 0;
	DWORD dwWrite      = 0;
	DWORD dwDone       = 0; 
	DWORD dwSize       = (pmix->Output).nLen16;
	DWORD dwPacketSize = sizeof(short) * dwSamples;
    
	// Convert All PCM samples
	while (1)
	{
        if( dwRead + dwPacketSize > dwSize )
            dwRead = dwSize - dwPacketSize;
        else
            dwRead = dwPacketSize;
          
		// Encode samples
		err = beEncodeChunk( hbeStream, dwRead, pwavbuf, pmp3buf, &dwWrite);

		// Check result
		if(err != BE_ERR_SUCCESSFUL)
		{
			beCloseStream(hbeStream);
			fprintf(stderr,"beEncodeChunk() failed (%lu)", err);
			return;
		}
		
		// write dwWrite bytes that are returned in tehe pMP3Buffer to disk
		if(fwrite(pmp3buf,1,dwWrite,pFileOut) != dwWrite)
		{
			fprintf(stderr,"Output file write error");
			return;
		}

		dwDone += dwRead / sizeof(SHORT);
        pwavbuf += (dwRead / 2);
		printf("Done: %0.2f%%     \r", 100 * (float)dwDone/(float)(dwSize));
	}

    fclose( pFileOut );
}
