#include<windows.h>

#define RGB16(r, g, b) ( ((r>>3)<<10) | ((g>>3)<<5) | (b>>3) )

typedef struct 
{
    bool Loaded;
    BITMAPFILEHEADER Header;
    struct
    {
       unsigned long    cbSize;     
       BITMAPINFOHEADER Header;
       RGBQUAD          Colors[256];
    }Info; 
    struct
    {
       unsigned long cbSize;
       unsigned char *pData;
    }Data;
}IMG;

IMG LoadIMG( char *filename )
{
    IMG img;
    FILE *fp;
   
    fp = fopen( filename, "rb" );
    fread( &img.Header, sizeof(img.Header), 1, fp );
    fread( &img.Info.Header, sizeof(img.Info.Header), 1, fp );
    
    if( img.Header.bfType != 0x4d42 ) 
    {
        img.Loaded = FALSE;
        printf("%s is Non-BMP File.\n", filename);
        fclose(fp);
        return img;
    }
    
    img.Loaded = TRUE;
    if( img.Info.Header.biClrUsed == 0 )    
    {
        switch( img.Info.Header.biBitCount ) 
        {    
            case 1:
                img.Info.cbSize = 8;
                break;
            case 4:
                img.Info.cbSize = 64;
                break;
            case 8:
                img.Info.cbSize = 1024;
                break;
            case 24:
                img.Info.cbSize = 0;
                break;
            case 16:    
            case 32:
                img.Info.cbSize += ( img.Info.Header.biCompression == BI_RGB ? 12 : 0 );
                break;    
        }     
    }
    else
        img.Info.cbSize = 4 * img.Info.Header.biClrUsed;
    
    memset( img.Info.Colors, 0, 1024 );
//    if( img.Info.Header.biClrUsed > 0 ) fread( img.Info.Colors, img.Info.cbSize, 1, fp );
    if( img.Info.cbSize > 0 ) fread( img.Info.Colors, img.Info.cbSize, 1, fp );
    img.Info.cbSize += sizeof(BITMAPINFOHEADER);

    img.Data.cbSize = img.Header.bfSize;
    img.Data.pData = new unsigned char [img.Data.cbSize];
    fread( img.Data.pData, img.Data.cbSize, 1, fp );
    fclose(fp);
    
    return img;
}

void MakeFixedIMG( IMG *pimg )
{
    // 사용 용도 탓에 어느 한 규격으로 통일을 시켜줘야 한다.  
    // 여기서는 16비트로 고정시켜준다. 
    DWORD pal[256][3];
    
    unsigned long  nsize8  = (pimg->Data).cbSize;
    unsigned long  nsize16 = nsize8 >> 1;
    unsigned short *pnewdata;
    
    switch( (pimg->Info).Header.biBitCount )
    {
        case 1:
            nsize8 *= 8;
            nsize8 *= 2;
            nsize16 = nsize8 >> 1;
            break;
        case 4:
            nsize8 *= 2;
            nsize8 *= 2;
            nsize16 = nsize8 >> 1;
            break;
        case 8:
            nsize8  *= 2;
            nsize16  = nsize8 >> 1;            
            break;
        case 16:
        case 32:
            return;
    }        
    pnewdata = new unsigned short [nsize16];
    memset( pnewdata, 0, nsize8 );
    
    for( int c = 0; c < (pimg->Info.cbSize - sizeof(BITMAPINFOHEADER)) / 4; c++ )
    {
        RGBQUAD paldata = pimg->Info.Colors[c];
        pal[c][0] = paldata.rgbRed;
        pal[c][1] = paldata.rgbGreen;
        pal[c][2] = paldata.rgbBlue;
    }
    
    int srcpos = 0;
    int destpos = 0;
    int c, idx1, idx2;
    for( srcpos = 0; srcpos < (pimg->Data).cbSize; srcpos++ )
    {
        switch( (pimg->Info).Header.biBitCount )
        {
            case 1:
                for( c = 1; c <= 128; c <<= 1 )
                {
                    idx1 = *((pimg->Data).pData + srcpos) & c;
                    if( idx1 != 0 ) 
                        *( pnewdata + destpos ) = 0xffff;
                    else
                        *( pnewdata + destpos ) = 0x0000;
                    destpos++;   
                }      
                break;
            case 4:
                idx1 = ( *((pimg->Data).pData + srcpos ) & 0xf0) >> 4;
                idx2 = *((pimg->Data).pData + srcpos ) & 0x0f;
                *( pnewdata + destpos++ ) = RGB16( pal[idx1][0], pal[idx1][1], pal[idx1][2] );
                *( pnewdata + destpos++ ) = RGB16( pal[idx1][0], pal[idx1][1], pal[idx1][2] );
                break;
            case 8:
                idx1 = *((pimg->Data).pData + srcpos);
                *( pnewdata + destpos++ ) = RGB16( pal[idx1][0], pal[idx1][1], pal[idx1][2] );
                break;
        }        
    }

    delete (pimg->Data).pData;
    (pimg->Data).cbSize = nsize8;
    (pimg->Data).pData  = (unsigned char *)pnewdata;

    (pimg->Info).cbSize = sizeof(BITMAPINFOHEADER);
    (pimg->Info).Header.biBitCount    = 16;
    (pimg->Info).Header.biClrUsed     = 0;
    (pimg->Info).Header.biCompression = 0;
}

void CloseIMG( IMG *pimg )
{
    if( (pimg->Data).cbSize > 0 ) delete (pimg->Data).pData;
    memset( pimg, 0, sizeof(IMG) );
}
