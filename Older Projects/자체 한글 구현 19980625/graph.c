#include"graph.h" 

// graph.c 
void setgraph( char mode ) 
{ 
    if ( mode == M_640X480 ) 
    { 
screeninfo.sizex = 80; 
screeninfo.sizey = 480; 
asm mov ax,0x0012; 
    } 
    else 
    { 
screeninfo.sizex = 100; 
screeninfo.sizey = 600; 
asm mov ax,0x006a; 
    } 
    asm int 10h; // Call video interrupt 
} 
void settextmode(void) 
{ 
    asm mov ax,0x0003; 
    asm int 10h; 
} 
