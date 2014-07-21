// (한글타입 => 수열대로 맞추기) 테이블 
int t_chotable[31]  = { 0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0,}; 
int t_jungtable[31] = { 0,0,0,1,2,3,4,5,0,0,6,7,8,9,10,11,0,0,12,13,14,15,16,17,0,0,18,19,20,21,0,}; 
int t_jongtable[31] = { 0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,0,17,18,19,20,21,22,23,24,25,26,27,0,}; 
// 한글타입 - 찍기에 알맞게 한다. 
int t_cho_htype1[] = { 0,0,0,0,0,0,0,0,0,1,3,3,3,1,2,4,4,4,2,1,3,0}; 
int t_cho_htype2[] = { 5,5,5,5,5,5,5,5,5,6,7,7,7,6,6,7,7,7,6,6,7,5}; 
int t_jong_htype[] = { 0,0,2,0,2,1,2,1,2,3,0,2,1,3,3,1,2,1,3,3,1,1}; 

void _gethancode( unsigned char hanchar[2] , char *image ); 

unsigned char *videomemory = (unsigned char *) 0xa0000000; 
unsigned char _eng[4096]; 
unsigned char _cho[640*8]; 
unsigned char _jung[704*4]; 
unsigned char _jong[896*4]; 
unsigned char _image[32]; 

void _gethancode( unsigned char hanchar[2] , char *image ) 
{ 
    register unsigned int hancode = ( ((unsigned int)(hanchar[0]) << 8) | hanchar[1] ); 
    unsigned char count; 
    unsigned char tempimage[32]; 
    unsigned char cho = t_chotable[ ( (hancode >> 10) & 31 ) ]; 
    unsigned char jung = t_jungtable[ ( (hancode >> 5) & 31 ) ]; 
    unsigned char jong = t_jongtable[ ( hancode & 31 ) ]; 
    unsigned char chotype  = ( jong ? t_cho_htype2[jung] : t_cho_htype1[jung] ); 
    unsigned char jungtype = ( (cho == 1 || cho == 15) ? 0 : 1 ) + ( jong ? 2 : 0 ); 
    unsigned char jongtype = t_jong_htype[jung]; 
    memset( image , 0 , 32 ); 
    memcpy( image , _cho+(640*chotype+32*cho) , 32 ); 
    memcpy( tempimage , _jung+(704*jungtype+32*jung) , 32 ); 
    for(count=0;count<=31;count++) 
   *(image+count) |= tempimage[count]; // 문자 이미지 결합 
    memcpy( tempimage , _jong+(896*jongtype+32*jong) , 32 ); 
    for(count=0;count<=31;count++) 
   *(image+count) |= tempimage[count]; // 문자 이미지 결합 */ 
    return; 
} 
void hputc( int y , int x , char hchar[2] ) 
{ 
    unsigned char c; 
    _gethancode( hchar , _image ); 
    for( c=0 ; c<=31 ; c++) 
    { 
   *(videomemory+screeninfo.sizex*y+x) = *(_image+(c++)); 
   *(videomemory+screeninfo.sizex*y+x+1) = *(_image+c); 
   y++; 
    } 
} 
void eputc( int y, int x, char ch ) 
{ 
    unsigned char c; 
    memcpy( _image , _eng+(16*ch) , 16 ); 
    for( c=0 ; c<=15 ; c++) 
    { 
   *(videomemory+screeninfo.sizex*y+x) = *(_image+c); 
   y++; 
    } 
} 
void hanfileload( unsigned char filename[32] ) 
{ 
    FILE *fp; 
    if ( !(fp = fopen(filename,"rb")) ) 
    { 
   printf("File not found.\n"); 
   return; 
    } 
    fread( _cho , 640*8 , 1 , fp ); 
    fread( _jung , 704*4 , 1 , fp ); 
    fread( _jong , 896*4 , 1 , fp ); 
    fclose(fp); 
} 
void engfileload( unsigned char filename[32] ) 
{ 
    FILE *fp; 
    if ( !(fp = fopen(filename,"rb")) ) 
    { 
   printf("File not found.\n"); 
   return; 
    } 
    fread( _eng , 4096 , 1 , fp ); 
    fclose(fp); 
} 
void hprintf( int y, int x, unsigned char *string , ... ) 
{ 
    int count,cx=x; 
    unsigned char fmtstr[255],hchar[2]={0,0}; 
    sprintf( fmtstr , string , ... ); 
    for( count = 0 ; count <= strlen(fmtstr) ; count++ ) 
    { 
   if ( hchar[0]==0 && ((*string) & 128) ) 
      hchar[0] = *string; 
   else 
   { 
      if( hchar[0] ) 
      { 
         hchar[1] = *string; 
         hputc( y, cx , hchar ); 
         cx+=2; 
         hchar[0] = 0; 
      } 
      else 
      { 
         eputc( y, cx, *string ); 
         cx++; 
      } 
   } 
   string++; 
    } 
} 
