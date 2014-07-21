#include 
#include 
#include 
#include 
#include 
#include 

unsigned char *firebuffer,*viewbuffer; 

void SetMode13h(void) 
{ 
   asm mov ax,0013h; 
   asm int 10h; 
} 
void FireProcess(void) 
{ 
   register int c,c1; 
   int v; 
   for( c=0 ; c<=99 ; c++ ) 
   { 
      for( c1=0 ; c1<=319 ; c1++ ) 
      { 
 if( c == 99 ) 
   *(firebuffer+320*c+c1) = random(255); 
 else 
 { 
   if( c1>=1 && c1<=318 && c>=1) 
   { 
     v = *(firebuffer+320*(c+1)+c1); 
     v += *(firebuffer+320*(c+1)+c1-1); 
     v += *(firebuffer+320*(c+1)+c1+1); 
     v += *(firebuffer+320*(c)+c1); 
     v += (*(firebuffer+320*(c-1)+c1) / 20); 
     v /= 4; 
     *(firebuffer+320*c+c1) = v; 
   } 
   v = *(firebuffer+320*c+c1); 
   if( v<64 ) v-=32; 
   *(firebuffer+320*c+c1) = v; 
 } 
      } 
   } 
} 
void Scroll(int speed) 
{ 
   unsigned char *tempbuf = (unsigned char *)malloc(320); 
   register int c; 
   for( c=0 ; c<=99 ; c++) 
   { 
      memcpy( tempbuf , firebuffer+(320*c) , 320 ); 
      memcpy( firebuffer+(320*c) , tempbuf+speed , 320-speed ); 
      memcpy( firebuffer+(320*c)+320-speed , tempbuf , speed ); 
   } 
   free(tempbuf); 
} 
void PaletteProcess(void) 
{ 
   register int c; 
   for( c=1 ; c<=255 ; c++ ) 
   { 
      outportb( 0x3c8 , c ); 
      outportb( 0x3c9 , c/4 ); 
      outportb( 0x3c9 , c/32 ); 
      outportb( 0x3c9 , 0 ); 
   } 
   outportb( 0x3c8 , 255 ); 
   outportb( 0x3c9 , 63 ); 
   outportb( 0x3c9 , 63 ); 
   outportb( 0x3c9 , 63 ); 
} 
void main(void) 
{ 
   int speed = 0 , x=0 , y=0; 
   unsigned char ch; 
   SetMode13h(); 
   randomize(); 
   PaletteProcess(); 
   firebuffer = (unsigned char *) malloc(320*100); 
   viewbuffer = (unsigned char *) malloc(320*100); 
   memset( firebuffer , 0 , 320*100 ); 
   while( ch != 27 ) 
   { 
      if( kbhit() ) 
      { 
switch( ch = getch() ) 
{ 
    case '+': 
speed++; 
break; 
    case '-': 
if( speed>=1) speed--; 
break; 
} 
if( ch == 72 ) y-=10; 
if( ch == 80 ) y+=10; 
if( ch == 75 ) x-=10; 
if( ch == 77 ) x+=10; 
      } 
      FireProcess(); 
      memcpy( viewbuffer , firebuffer , 320*99 ); 
      *(viewbuffer+(320*y)+x)=255; 
      *(viewbuffer+(320*(y+1))+1+x)=255; 
      *(viewbuffer+(320*(y+2))+1+x)=255; 
      *(viewbuffer+(320*(y+0))+1+x)=255; 
      *(viewbuffer+(320*(y+1))+2+x)=255; 
      *(viewbuffer+(320*(y+2))+2+x)=255; 
      *(viewbuffer+(320*(y+0))+2+x)=255; 
      *(viewbuffer+(320*(y+1))+3+x)=255; 
      *(viewbuffer+(320*(y+2))+3+x)=255; 
      *(viewbuffer+(320*(y+0))+4+x)=255; 
      *(viewbuffer+(320*(y+1))+4+x)=255; 
      *(viewbuffer+(320*(y+2))+4+x)=255; 
      *(viewbuffer+(320*(y+0))+5+x)=255; 
      *(viewbuffer+(320*(y+1))+5+x)=255; 
      *(viewbuffer+(320*(y+2))+5+x)=255; 
      *(viewbuffer+(320*(y+0))+6+x)=255; 
      *(viewbuffer+(320*(y+1))+6+x)=255; 
      *(viewbuffer+(320*(y+2))+6+x)=255; 
      *(viewbuffer+(320*(y+0))+7+x)=255; 
      *(viewbuffer+(320*(y+1))+7+x)=255; 
      *(viewbuffer+(320*(y+2))+7+x)=255; 
      *(viewbuffer+(320*(y+0))+8+x)=255; 
      *(viewbuffer+(320*(y+1))+8+x)=255; 
      *(viewbuffer+(320*(y+2))+8+x)=255; 
      *(viewbuffer+(320*(y+0))+9+x)=255; 
      *(viewbuffer+(320*(y+1))+9+x)=255; 
      *(viewbuffer+(320*(y+2))+9+x)=255; 
      *(viewbuffer+(320*(y+1))+10+x)=255; 
      *(viewbuffer+(320*(y+2))+10+x)=255; 
      *(viewbuffer+(320*(y+2))+11+x)=255; 
      _fmemcpy( (void far *)(0xa0000000+32000) , (void far *)viewbuffer , 320*99); 
      Scroll(speed); 
   } 
   asm mov ax,0003; 
   asm int 10h; 
   free(firebuffer); 
   free(viewbuffer); 
   return; 

