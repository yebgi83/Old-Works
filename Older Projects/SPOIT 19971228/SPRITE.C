// �ȳ��ϼ��� 
// �̰����Դϴ�. �ɽ��ؼ� �ð����� ���� ��������Ʈ ������Դϴ�. 
// PCXȭ���� �ҷ��� �Ϻκ��� �ҷ� ��������Ʈ ȭ�Ϸ� �ٲپ� �ݴϴ�. 
// �׷� �̸�. ^^; ������ ���Ŀ��Դϴ�. 

#include 
#include 
#include 

typedef unsigned char U8; 
typedef unsigned short U16; 
typedef unsigned int U32; 

U8 pcxfile[13],sprfile[13]; 
U8 palbuf[768]; 

U8 *videomemory = (U8 *) 0xa0000; 
U8 *togglekeystatus = (U8 *) (0x400 + 0x0017); // ���Ű ������ �ִ°� 

U8 *PCXbuffer; 
int sx=0,sy=0,ex=40,ey=40; // ������ �κ��� ����ϰ� �ּ��̴�. 

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
    // ���� ���۸��� �̿��Ѱ��̴�. 
    // ���� ȭ�鿡 PCX�׸��� �׷����´�. 
    // �׷��� ȭ������ PCXȭ���� ��Ÿ���� �ʴ´�. 
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
    // ���� ��۸��������� �����ϱ� ��ƴ�. �ѱ����� ����� ũũũ 
    // * �ȷ�Ʈ �κ� �ε� 
    // * �ȷ�Ʈ �κ��� PCXȭ���� ���� �ڲ������� 768����Ʈ�̴� �����ϵ��� 
    fseek( filehandle , -768 , SEEK_END ); // �޲������� -768����Ʈ �޺κ����� 
                                           // �̵� 
    fread( &palbuf , 768 , 1 , filehandle ); // �ȷ�Ʈ �ε� 
    for( count=0 ; count<768 ; count++ ) 
       palbuf[count] >>= 2;                // �ȷ�Ʈ�� ������ 0~64�̹Ƿ� �ƽ�Ű 
                                           // �ڵ忡�� �ȷ�Ʈ ���� ������ �ٲ۴�. 
    // �׷����� �����ϴ� ���� 129��° ��ġ ���ʹ�. 
    fseek( filehandle , 128 , SEEK_SET );  // �������� ������ ���ۺκ��� 0�̹Ƿ� 
                                           // 129�� �ƴ϶� 128�� ����� �Ѵ�. 
    count = 0; 
    for( ;; ) // ���� �������� 
    {             
       ch = fgetc(filehandle);   
       if ( (ch & 192) == 192 )   // �� �κ���? ���� ���ӵǴ� Ƚ���� ������ ���ΰ�? Ȯ���Ѵ�. 
                                  // PCX�� RLE Compress����� �Ἥ �����߱⶧���� �̰��� 
                                  // decoding���Ѿ� �Ұ��̴�. 
       {                          // �ֻ��� ��Ʈ �� ��Ʈ�� 1�̶�� �̰��� ���ӵ� ��ġ��� ���̴�. 
           b = ch & 63;  // ���ӵ� ���� ������ �θ���. 
           ch = fgetc(filehandle); // ���ڸ� �θ���. �̰� �Ⱥ��� �����̶�°� �˼��ִ�. 
           for ( count2 = 0 ; count2 < b; count2++ ) 
           { 
               PCXbuffer[count++] = ch; 
               if( count == 64000 ) break; // �� �Լ��� 320*200�� �׸��� �̴´�. 
           } 
           if( count == 64000 ) break; // �� �Լ��� 320*200�� �׸��� �̴´�. 
       } 
       else 
       { 
           PCXbuffer[count++] = ch; 
           if( count == 64000 ) break; // �� �Լ��� 320*200�� �׸��� �̴´�. 
       }           
       if( count >= 64000 ) break; // �� �Լ��� 320*200�� �׸��� �̴´�. 
    }   
    fclose( filehandle ); // FILE���ݴ´�. 
    return 1; 
}                                           
void ViewPCXBuffer( U8 *PCXbuffer ) 
{ 
    // ȭ���� ��Ÿ����. 
    U16 c; 
    outp(0x3c8 , 0); // �ȷ�Ʈ ���� 
    for( c=0 ; c<768 ; c++ ) 
         outp(0x3c9 , palbuf[c] ); 
    // Video Memory�� ���� ���� 
    // WC���� 0xa0000 
    // TC���� 0xa0000000���� �Ѵ�. 
    memcpy ( videomemory , PCXbuffer , 64000 ); // ���� �θ� �� 
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
    // XOR���� �Ἥ ȭ�� ���� ������ �簢�� ���� 
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
    // ũ�⸦ ���Ѵ�. 
    xl = eex - ssx; 
    yl = eey - ssy; 
    fp = fopen(sprfile,"wb"); 
    fputc(xl/256,fp); 
    fputc(xl%256,fp); 
    fputc(yl/256,fp); 
    fputc(yl%256,fp); 
    // �׸� ������ ����. 
    for ( c1 = ssy ; c1 <= eey ; c1++ ) 
    {   
        for ( c2 = ssx ; c2 <= eex ; c2++ ) 
            fputc( PCXbuffer[320*c1+c2] , fp ); // �׳� ���� ȭ���� ���� �����Ѵ�. 
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
       ch = getch(); // Ű�� �Է¹޴´�. 
       tkey_info = *togglekeystatus; 
       if ( ch == 0 ) // Ȯ�� �ƽ�Ű �ڵ����� �˾ƺ���. 
       { 
          // ���� Ȯ�� �ƽ�Ű �ڵ� ����. 
          XOR_linebox( sx, sy , ex, ey ); 
          ch = getch(); // � Ȯ�� �ƽ�Ű �ڵ�����? 
          switch( ch ) 
          { 
             /* ��ġ �̵��̾߿� */ 
             case 75: 
                  // ���� 
                  if ( tkey_info & 2 ) sx=sx-1; // ����ƮŰģ ���¿��� �׷����� 
                  ex=ex-1; // ����ƮŰģ ���°� �ƴϸ� �̰͸� �ϴ°� �翬 
                  if ( sx == -1 ) sx=0; 
                  if ( ex == -1 ) ex=0; 
                  break; 
             case 77: 
                  // ������ 
                  if ( tkey_info & 2 ) sx=sx+1; // ����ƮŰģ ���¿��� �׷����� 
                  ex=ex+1; // ����ƮŰģ ���°� �ƴϸ� �̰͸� �ϴ°� �翬 
                  if ( sx == 320 ) sx=319; 
                  if ( ex == 320 ) ex=319; 
                  break; 
             case 72: 
                  // ���� 
                  if ( tkey_info & 2 ) sy=sy-1; // ����ƮŰģ ���¿��� �׷����� 
                  ey=ey-1; // ����ƮŰģ ���°� �ƴϸ� �̰͸� �ϴ°� �翬 
                  if ( sy == -1 ) sy=0; 
                  if ( ey == -1 ) ey=0; 
                  break; 
             case 80: 
                  // ���� 
                  if ( tkey_info & 2 ) sy=sy+1; // ����ƮŰģ ���¿��� �׷����� 
                  ey=ey+1; // ����ƮŰģ ���°� �ƴϸ� �̰͸� �ϴ°� �翬 
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
             break; // ESC�� Ű�� �����ٿ�. 
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
