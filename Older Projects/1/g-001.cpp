#include 
#include 
#include 
#include 
#include 
#include 
#include"graph.h" 
#include"font.h" 

void main(void) 
{ 
   T_PVS l_pvsBackGround; 

   InitializeEngFontBuf();         // initial english font system 
   LoadEngFont("ENGLISH.FNT"); 

   l_pvsBackGround=InitializeVS(); // initialize virtual background screen. 
   ClearVS(l_pvsBackGround);       // clear virtual background screen. 

   SetMode13h(); 
   SetPalette( "DEFAULT.PAL" ); 
   if( LoadPCX(l_pvsBackGround,"P001.PCX")==0 ) 
Printf( g_pVRAM,10,20,"Error" ); 
   else 
PutVS( g_pVRAM,l_pvsBackGround ); 
   Printf( g_pVRAM,10,20,"Lee kang-yong." ); 
   getch(); 
   SetTextMode(); 

   RemoveEngFontBuf();             // uninstall english font system 
   RemoveVS(l_pvsBackGround);      // remove virtual background screen. 
   return; 
} 
