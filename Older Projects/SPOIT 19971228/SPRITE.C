// 안녕하세요 
// 이강용입니다. 심심해서 시간내어 만든 스프라이트 추출기입니다. 
// PCX화일을 불러서 일부분을 불러 스프라이트 화일로 바꾸어 줍니다. 
// 그럼 이만. ^^; 참고로 왓컴용입니다. 

#include 
#include 
#include 

typedef unsigned char U8; 
typedef unsigned short U16; 
typedef unsigned int U32; 

U8 pcxfile[13],sprfile[13]; 
U8 palbuf[768]; 

U8 *videomemory = (U8 *) 0xa0000; 
U8 *togglekeystatus = (U8 *) (0x400 + 0x0017); // 토글키 정보가 있는곳 

U8 *PCXbuffer; 
int sx=0,sy=0,ex=40,ey=40; // 오려낼 부분을 담당하고 있소이다. 

unsigned char LoadPcxToBuffer( U8 filename[13] , U8 *PCXbuffer ); 
void ViewPCXBuffer( U8 *PCXbuffer ); 
void XOR_linebox( U16 sx, U16 sy, U16 ex, U16 ey ); 
void Control(); 
void SaveSprite(); 
void InitGraph(); 
void CloseGraph(); 
// inline asm functions 
#pragma aux InitGraph = "MOV EAX,13h"\ 
                       "INT 10h"\   
                       parm; 
#pragma aux CloseGraph = "MOV EAX,3h"\ 
                        "INT 10h"\   
                        parm; 
unsigned char LoadPcxToBuffer( U8 filename[13] , U8 *PCXbuffer ) 
{ 
    // 더블 버퍼링을 이용한것이다. 
    // 가상 화면에 PCX그림을 그려놓는다. 
    // 그래서 화면으론 PCX화면이 나타나지 않는다. 
    U8 ch,b,count2; 
    U16 count; 
    FILE *filehandle; 
    filehandle = fopen( filename , "rb" ); 
    if ( !filehandle ) // File Not Found? 
    { 
       printf("%s File Not Found\n",filename); // Yes, File Not Found. 
       getch(); 
       return 0; 
    } 
    // No, File Found. 
    // 젠장 콩글리쉬가지고 설명하기 어렵다. 한국말을 써야지 크크크 
    // * 팔렛트 부분 로드 
    // * 팔렛트 부분은 PCX화일의 제일 뒤꼬랑지의 768바이트이다 명심하도록 
    fseek( filehandle , -768 , SEEK_END ); // 뒷꼬랑지의 -768바이트 뒷부분으로 
                                           // 이동 
    fread( &palbuf , 768 , 1 , filehandle ); // 팔렛트 로드 
    for( count=0 ; count<768 ; count++ ) 
       palbuf[count] >>= 2;                // 팔렛트의 범위는 0~64이므로 아스키 
                                           // 코드에서 팔렛트 한정 범위로 바꾼다. 
    // 그래픽이 시작하는 곳은 129번째 위치 부터다. 
    fseek( filehandle , 128 , SEEK_SET );  // 씨에서는 파일의 시작부분이 0이므로 
                                           // 129가 아니라 128로 적어야 한다. 
    count = 0; 
    for( ;; ) // 무한 루프가동 
    {             
       ch = fgetc(filehandle);   
       if ( (ch & 192) == 192 )   // 이 부분이? 과연 연속되는 횟수를 저장한 곳인가? 확인한다. 
                                  // PCX는 RLE Compress방법을 써서 저장했기때문에 이것을 
                                  // decoding시켜야 할것이다. 
       {                          // 최상위 비트 두 비트가 1이라면 이것은 연속된 위치라는 것이다. 
           b = ch & 63;  // 연속된 점의 갯수를 부른다. 
           ch = fgetc(filehandle); // 글자를 부른다. 이건 안봐도 색깔이라는걸 알수있다. 
           for ( count2 = 0 ; count2 < b; count2++ ) 
           { 
               PCXbuffer[count++] = ch; 
               if( count == 64000 ) break; // 본 함수는 320*200의 그림만 뽑는다. 
           } 
           if( count == 64000 ) break; // 본 함수는 320*200의 그림만 뽑는다. 
       } 
       else 
       { 
           PCXbuffer[count++] = ch; 
           if( count == 64000 ) break; // 본 함수는 320*200의 그림만 뽑는다. 
       }           
       if( count >= 64000 ) break; // 본 함수는 320*200의 그림만 뽑는다. 
    }   
    fclose( filehandle ); // FILE을닫는다. 
    return 1; 
}                                           
void ViewPCXBuffer( U8 *PCXbuffer ) 
{ 
    // 화면을 나타낸다. 
    U16 c; 
    outp(0x3c8 , 0); // 팔렛트 지정 
    for( c=0 ; c<768 ; c++ ) 
         outp(0x3c9 , palbuf[c] ); 
    // Video Memory에 직접 접근 
    // WC에선 0xa0000 
    // TC에선 0xa0000000으로 한다. 
    memcpy ( videomemory , PCXbuffer , 64000 ); // 버퍼 부름 찍어냄 
} 
void XOR_linebox( U16 sx, U16 sy, U16 ex, U16 ey ) 
{ 
    U16 c1; 
    U16 ssx,ssy,eex,eey; 
    if ( sx <= ex ) 
    { 
       ssx = sx; 
       eex = ex; 
    } 
    else 
    { 
       ssx = ex; 
       eex = sx; 
    } 
    if ( sy <= ey ) 
    { 
       ssy = sy; 
       eey = ey; 
    } 
    else 
    { 
       ssy = ey; 
       eey = sy; 
    } 
    // XOR연산 써서 화면 복구 가능한 사각형 만듬 
    for ( c1 = ssx ; c1 <= eex ; c1++ ) 
    {   
        videomemory[320*ssy+c1] ^= 0xa0; 
        videomemory[320*eey+c1] ^= 0xa0; 
    } 
    for ( c1 = ssy+1 ; c1 < eey ; c1++ ) 
    {   
        videomemory[320*c1+ssx] ^= 0xa0; 
        videomemory[320*c1+eex] ^= 0xa0; 
    } 
} 
void SaveSprite() 
{ 
    U16 xl,yl; 
    U16 ssx,ssy,eex,eey; 
    U16 c1,c2; 
    FILE *fp; 
    if ( sx <= ex ) 
    { 
       ssx = sx; 
       eex = ex; 
    } 
    else 
    { 
       ssx = ex; 
       eex = sx; 
    } 
    if ( sy <= ey ) 
    { 
       ssy = sy; 
       eey = ey; 
    } 
    else 
    { 
       ssy = ey; 
       eey = sy; 
    } 
    printf("Save Sprite.....\n"); 
    printf("Sprite Filename: TEST.SPR\n"); 
    printf("Save Region: (%d,%d)-(%d,%d)\n",ssx,ssy,eex,eey); 
    printf("Save Palette............"); 
    // 크기를 정한다. 
    xl = eex - ssx; 
    yl = eey - ssy; 
    fp = fopen(sprfile,"wb"); 
    fputc(xl/256,fp); 
    fputc(xl%256,fp); 
    fputc(yl/256,fp); 
    fputc(yl%256,fp); 
    // 그림 내용의 저장. 
    for ( c1 = ssy ; c1 <= eey ; c1++ ) 
    {   
        for ( c2 = ssx ; c2 <= eex ; c2++ ) 
            fputc( PCXbuffer[320*c1+c2] , fp ); // 그냥 가상 화면을 통해 접근한다. 
    } 
    for ( c1 = 0 ; c1 <= 767 ; c1++ ) 
    { 
        fputc(palbuf[c1],fp); 
    } 
    fclose(fp); 
}               
void main(int argc , char *argv[])                                 
{                                           
    if ( argc != 3 ) 
    { 
        printf(" Sprite Save Program.... \n"); 
        printf(" Program by Lee Kang-yong( BrightSoftTeam )\n"); 
        printf(" Usage: MAKESPR [PCXFILENAME] [SAVESPRFILENAME]\n"); 
        return; 
    } 
    strcpy( pcxfile , argv[1] ); 
    strcpy( sprfile , argv[2] ); 
    PCXbuffer = (U8 *) malloc(64000); 
    if ( LoadPcxToBuffer( pcxfile , PCXbuffer ) ) 
    { 
         InitGraph();                         
         ViewPCXBuffer( PCXbuffer ); 
         Control(); 
    } 
    free(PCXbuffer); 
} 
void Control() 
{ 
    U8 ch,tkey_info; 
    XOR_linebox( sx, sy , ex, ey ); 
    for(;;) 
    { 
       ch = getch(); // 키를 입력받는다. 
       tkey_info = *togglekeystatus; 
       if ( ch == 0 ) // 확장 아스키 코드인지 알아본다. 
       { 
          // 오오 확장 아스키 코드 구려. 
          XOR_linebox( sx, sy , ex, ey ); 
          ch = getch(); // 어떤 확장 아스키 코드일지? 
          switch( ch ) 
          { 
             /* 위치 이동이야요 */ 
             case 75: 
                  // 왼쪽 
                  if ( tkey_info & 2 ) sx=sx-1; // 쉬프트키친 상태에서 그랬으면 
                  ex=ex-1; // 쉬프트키친 상태가 아니면 이것만 하는건 당연 
                  if ( sx == -1 ) sx=0; 
                  if ( ex == -1 ) ex=0; 
                  break; 
             case 77: 
                  // 오른쪽 
                  if ( tkey_info & 2 ) sx=sx+1; // 쉬프트키친 상태에서 그랬으면 
                  ex=ex+1; // 쉬프트키친 상태가 아니면 이것만 하는건 당연 
                  if ( sx == 320 ) sx=319; 
                  if ( ex == 320 ) ex=319; 
                  break; 
             case 72: 
                  // 위로 
                  if ( tkey_info & 2 ) sy=sy-1; // 쉬프트키친 상태에서 그랬으면 
                  ey=ey-1; // 쉬프트키친 상태가 아니면 이것만 하는건 당연 
                  if ( sy == -1 ) sy=0; 
                  if ( ey == -1 ) ey=0; 
                  break; 
             case 80: 
                  // 왼쪽 
                  if ( tkey_info & 2 ) sy=sy+1; // 쉬프트키친 상태에서 그랬으면 
                  ey=ey+1; // 쉬프트키친 상태가 아니면 이것만 하는건 당연 
                  if ( sy == 200 ) sy=199; 
                  if ( ey == 200 ) ey=199; 
                  break; 
          } 
          XOR_linebox( sx, sy , ex, ey ); 
       } 
       else 
       { 
          if ( ch == 27 ) 
          { 
             CloseGraph(); 
             break; // ESC를 키면 나간다요. 
          } 
          if ( ch == 13 ) 
          { 
             CloseGraph(); 
             // SAVE SPRITE 
             SaveSprite(); 
             break; 
          } 
       } 
    } 
} 

