#pragma inline 

#include"deftype.h" 

#include 
#include 
#include 
#include 
#include 
#include 

#include"scapture.h" 
#include"box.h" 
#include"popup.h" 
#include"pulldown.h" 
#include"editbox.h" 

CLASS_PULLDOWN pulldown( 0, 15,1, 15, 2 ); 

#include"mainfunc.h" 


void main(void) 
{ 
   char pmn,psn; 
   CLASS_EDITBOX temp1; 
   CLASS_BOX editbox; 
   PULLDOWN_unit_registerd(); 
   VIEW_mainscreen(); 
   VIEW_startingbox(); 
   if( pulldown.operation() == TRUE ) 
      pulldown.get_selectnums( &pmn,&psn ); 
      PULLDOWN_runcommand( pmn,psn ); 
   temp1.filename_set( "NOTITLE.ASM" ); 
   temp1.show_maximum(); 
   temp1.operation(); 
   return; 
} 


