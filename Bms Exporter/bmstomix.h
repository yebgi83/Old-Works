MIX BindBMS( BMS *pbms )
{
   MIX tmpmix;
   
   unsigned long samplerate = 44100;
   unsigned long channels = 2;
   unsigned long bytesatonce;
   unsigned long wavbytes = 2;
   unsigned long nbufsize;
   
   float playtime = (float)((pbms->Note).nDatas) / (float)((pbms->Info).nBPM) * 2.5f;
   nbufsize = (unsigned long)((float)samplerate * playtime);
   nbufsize += (unsigned long)((float)samplerate * 5.0); // 5초의 끝시간을 준다.  
   nbufsize *= channels * wavbytes;
   bytesatonce = (unsigned long)( (float)samplerate * (playtime / (float)((pbms->Note).nDatas)) );
   bytesatonce *= channels * wavbytes;
   tmpmix = OpenMIX( samplerate, channels, bytesatonce, wavbytes, nbufsize );
   return tmpmix;       
}

void AudioScheduler( MIX *pmix, BMS *pbms )
{
    int c1, c2, next;

    printf("Audio Scheduler Opearation.\n");

    for( c1 = 1; c1 <= (pbms->Note).nDatas ; c1++ )
    {
        for( c2 = 1; c2 <= BMS_CHANNELS; c2++ ) 
        {
            int ndatum = BMS_NOTE( pbms, c2, c1 );
            if( ndatum > 0 ) AddChannel( pmix, (pbms->Doc).pWav[ndatum] );
        }
        next = DoMix( pmix );  

        if( c1 % 128 == 0 ) 
        {
            printf("                                                             \r");
            printf("%d bytes completed( %d %% ).\r", next, 100 * c1 / (pbms->Note).nDatas );     
        }
    }
    printf("                                                             \r");
    printf("\nMixing completed.\n");
}
