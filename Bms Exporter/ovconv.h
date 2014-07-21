#include<vorbis/vorbisenc.h>

void SaveOGG( char *filename, MIX mix )
{
    FILE *fp; 
    fp = fopen( filename, "wb" );
    
    ogg_stream_state os;
    ogg_packet op;
    ogg_page   og;

    vorbis_info    vi;
    vorbis_comment vc;
    
    vorbis_dsp_state vd;
    vorbis_block     vb;

    int eos = 0;
    
    srand(time(NULL));
    ogg_stream_init( &os, rand() );
      
    printf("Initializing OGG Vorbis Encoder.... ");
    vorbis_info_init( &vi );
   
    vorbis_encode_setup_init( &vi );    
    vorbis_encode_init_vbr( &vi, 2 , 44100, .5 );

    vorbis_comment_init( &vc );
    vorbis_comment_add_tag( &vc, "ENCODER", "OGG file from bitmania" );    

    vorbis_analysis_init( &vd, &vi );
    vorbis_block_init( &vd, &vb );
    
    printf("OK.\n");

    {
        ogg_packet header;
        ogg_packet header_comm;
        ogg_packet header_code;

        vorbis_analysis_headerout( &vd, &vc, &header, &header_comm, &header_code);
    
        ogg_stream_packetin(&os, &header); 
        ogg_stream_packetin(&os, &header_comm);
        ogg_stream_packetin(&os, &header_code);

        printf("Pushing OGG Vorbis header.\n");
   	    while(1)
        {
	        int result = ogg_stream_flush( &os, &og );
		    if( result == 0 ) break;
		    fwrite(og.header , og.header_len , 1, fp);
		    fwrite(og.body   , og.body_len   , 1, fp);
        }
	}
    
    long curbytes = 0;
    long packet_len = 0;
    long inc = 64000;
    long encodedbytes = 0;
    
    printf("Pushing packet compressed.\n");
    while( !eos )
    {
        if( mix.Output.nLen8 - curbytes < inc )
            packet_len = mix.Output.nLen8 - curbytes;
        else
            packet_len = inc;

        if( curbytes == mix.Output.nLen8 )
        {
            vorbis_analysis_wrote( &vd, 0);
            break;
        }

        int i;
        float **buffer = vorbis_analysis_buffer( &vd, packet_len );
      
        for( i = 0 ; i < packet_len / 4 ; i++ )
        {
/*             signed short ch1 = *( (signed short *)( mix.Output.pData8 + curbytes + i * 4 + 1 ) );
             signed short ch2 = *( (signed short *)( mix.Output.pData8 + curbytes + i * 4 + 3 ) );
             
         	 buffer[0][i]  = (float)(ch1);
             buffer[0][i] /= 32768.0f;
         	 buffer[1][i]  = (float)(ch2);
             buffer[1][i] /= 32768.0f;*/
             
             signed char *readbuffer = (signed char *)(mix.Output.pData8 + curbytes);
             
             buffer[0][i]=( (readbuffer[i*4+1]<<8) | (0x00ff&(int)readbuffer[i*4]) ) / 32768.f;
          	 buffer[1][i]=( (readbuffer[i*4+3]<<8) | (0x00ff&(int)readbuffer[i*4+2]) ) / 32768.f;
        }
        curbytes += packet_len;
        vorbis_analysis_wrote( &vd, i );
        
        while( vorbis_analysis_blockout( &vd, &vb ) == 1 )
        {
            // analysis, assume we want to use bitrate management 
            vorbis_analysis(&vb,NULL);
            vorbis_bitrate_addblock(&vb);

            while( vorbis_bitrate_flushpacket(&vd,&op) )
            {
	
         	    // weld the packet into the bitstream 
         	    ogg_stream_packetin(&os,&op);
	
    	        // write out pages (if any) 
    	        while( !eos )
                {
    	            int result = ogg_stream_pageout(&os,&og);
    	            if( result == 0 )break;

             	    fwrite( og.header, 1, og.header_len, fp);
    	            fwrite( og.body, 1, og.body_len, fp);
	  
    	            encodedbytes += ( og.header_len + og.body_len );
    	            printf("%d encoded bytes.\r", encodedbytes );
      	            // this could be set above, but for illustrative purposes, I do
    	            // it here (to show that vorbis does know where the stream ends) 
    	            if( ogg_page_eos( &og ) ) eos = 1;
                }
         	}
        }
    }

    printf("\nComplete.\n");
    printf("Writing compressed data.\n");
    
    printf("\n");
    
    ogg_stream_clear( &os );
    vorbis_block_clear( &vb );
    vorbis_dsp_clear( &vd );
    vorbis_comment_clear(&vc );
    vorbis_info_clear( &vi );
    fclose(fp);
}


