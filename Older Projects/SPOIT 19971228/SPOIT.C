#include 
#include 

typedef unsigned char U8; 
typedef unsigned short U16; 
typedef unsigned int U32; 

U8 palbuf[768]; 

void LoadPcxToBuffer( U8 filename[13] , U8 *PCXbuffer ); 
void ViewPCXBuffer( U8 *PCXbuffer ); 
void InitGraph(); 
void CloseGraph(); 
// inline asm functions 
#pragma aux InitGraph = "MOV EAX,13h"\ 
                       "INT 10h"\   
                       parm; 
#pragma aux CloseGraph = "MOV EAX,3h"\ 
                        "INT 10h"\   
                        parm; 
void LoadPcxToBuffer( U8 filename[13] , U8 *PCXbuffer ) 
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
       return; 
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
                                  // DeCompress시켜야 할것이다. 
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
    memcpy ( 0xa0000 , PCXbuffer , 64000 ); // 버퍼 부름 찍어냄 
} 

void main()                                 
{                                           
    U8 *PCXbuffer; 
    PCXbuffer = (U8 *) malloc(64000); 
    InitGraph();                         
    LoadPcxToBuffer( "SAGA.PCX" , PCXbuffer ); 
    ViewPCXBuffer( PCXbuffer ); 
    getch(); 
    CloseGraph(); 
    free(PCXbuffer); 
} 

