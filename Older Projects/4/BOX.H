class CLASS_BOX : private CLASS_SCREENCAPTURE 
{ 
  protected: 
     char config_position_x;                      // x 
     char config_position_y;                      // y 
  public: 
     // functions 
     void draw( char fc, char bc, char x , char y 
              , char sx , char sy , char type );  // draw window 
     void activebox( char fc, char bc ,char x, char y 
                   , char sx, char sy , char type ); 
     void recoverbackground(void);                // recover bgr 
}; 

void CLASS_BOX::draw( char fc, char bc, char x , char y 
                   , char sx , char sy , char type ) 
{ 
  register int count,count2; 
  unsigned char draw_symbol1,draw_symbol2; 
  unsigned char draw_symbol3,draw_symbol4; 
  unsigned char draw_symbol5,draw_symbol6; 

  // for background protect 
  if( (type & 32) == 0 ) 
  { 
    if( (type & 16) == 16 ) // shadow effect ok? 
       CLASS_SCREENCAPTURE::getregion(x,y,sx+2,sy+1); 
    else 
CLASS_SCREENCAPTURE::getregion(x,y,sx,sy); 
  } 

  // draw symbol set 
  switch( type & 3 ) 
  { 
     case 0: // single line 
        draw_symbol1 = '?'; draw_symbol2 = '?'; 
        draw_symbol3 = '?'; draw_symbol4 = '?'; 
        draw_symbol5 = '?'; draw_symbol6 = '?'; 
        break; 
     case 1: // two line 
draw_symbol1 = '?'; draw_symbol2 = '?'; 
draw_symbol3 = '?'; draw_symbol4 = '?'; 
draw_symbol5 = '?'; draw_symbol6 = '?'; 
break; 
  } 

  // color set 
  textattr( (bc<<4) | fc ); 

  // draw box - 1. head 
  gotoxy( x+1,y+1 ); 
  cprintf("%c",draw_symbol1); 
  for( count=1 ; count<=sx-2 ; count ++ ) 
     cprintf("%c",draw_symbol5); 
  cprintf("%c",draw_symbol2); 

  // 2. middle 
  for( count2=1 ; count2<=sy-2 ; count2++ ) 
  { 
     gotoxy( x+1,y+1+(count2-1)+1 ); 
     cprintf("%c",draw_symbol6); 
     for( count=1 ; count<=sx-2 ; count ++ ) 
cprintf(" "); 
     cprintf("%c",draw_symbol6); 
  } 

  // draw box - 3. bottom 
  gotoxy( x+1,y+1+(count2-1)+1 ); 
  cprintf("%c",draw_symbol3); 

  for( count=1 ; count<=sx-2 ; count ++ ) 
     cprintf("%c",draw_symbol5); 

  cprintf("%c",draw_symbol4); 

  // shadow effect 
  if( sx>=1 && sy>=1 && (type & 16) ) 
  { 
     // side shadow 
     for( count=1 ; count<=sy ; count++ ) 
     { 
*( (unsigned char far *)(0xb8000000lu)+(160*(y+count)+(2*(sx+x))+1 )) = 8; 
*( (unsigned char far *)(0xb8000000lu)+(160*(y+count)+(2*(sx+x+1))+1 )) = 8; 
     } 

     // bottom shadow 
     for( count=x ; count<=x+sx-1 ; count++ ) 
     { 
*( (unsigned char far *)(0xb8000000lu)+(160*(y+sy)+(2*count))+1+4 ) = 8; 
     } 
  } 

  // position set 
  CLASS_BOX::config_position_x = x; 
  CLASS_BOX::config_position_y = y; 

  return; 
} 

void CLASS_BOX::activebox( char fc, char bc ,char x, char y 
, char sx, char sy , char type ) 
{ 
  // active box draw 
  float increase_x = sx / 8.0; 
  float increase_y = sy / 8.0; 
  float temp_sx = 0.0; 
  float temp_sy = 0.0; 
  register int count; 

  // get screen 
  if( (type & 16) == 16 ) // shadow effect ok? 
     CLASS_SCREENCAPTURE::getregion(x,y,sx+2,sy+1); 
  else 
     CLASS_SCREENCAPTURE::getregion(x,y,sx,sy); 

  // active 
  for( count=1; count<=8 ; count++ ) 
  { 
     temp_sx += increase_x; 
     temp_sy += increase_y; 
     CLASS_BOX::draw( fc, bc, x , y , (char)temp_sx , (char)temp_sy 
    , type | 32); 
     delay(20); 
  } 

  // complete draw box 
  CLASS_BOX::draw( fc, bc, x , y , sx , sy 
    , type|32); 
  return; 
} 

void CLASS_BOX::recoverbackground(void) 
{ 
  // background recover 
  CLASS_SCREENCAPTURE::putregion( CLASS_BOX::config_position_x 
, CLASS_BOX::config_position_y ); 
  return; 
} 

