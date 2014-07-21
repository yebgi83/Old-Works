class CLASS_SCREENCAPTURE 
{ 
   protected: 
     // for screen region save 
     unsigned char config_size_x; // sizex 
     unsigned char config_size_y; // sizey 
     unsigned char buffer[4000];  // buffer 
   public: 
     // functions 
     void getregion( char x, char y, char sx, char sy ); 
     void putregion( char x, char y ); 
}; 

void CLASS_SCREENCAPTURE::getregion( char x, char y, char sx, char sy ) 
{ 
   int count1,count2; 

   unsigned char *tempbuffer = &CLASS_SCREENCAPTURE::buffer[0]; 

   for( count1=y ; count1<=(y+sy-1) ; count1++) 
   { 
      // line get 
      for( count2=x ; count2<=(x+sx-1) ; count2++) 
      { 
 *(tempbuffer++) 
 = *( (unsigned char far *)(0xb8000000lu)+( 160u*count1+(2u*count2) ) ); 
 *(tempbuffer++) 
 = *( (unsigned char far *)(0xb8000000lu)+( 160u*count1+(2u*count2)+1 ) ); 
      } 
   } 
   config_size_x = sx; 
   config_size_y = sy; 
} 
void CLASS_SCREENCAPTURE::putregion( char x, char y ) 
{ 
   register int count1,count2; 
   unsigned char *tempbuffer = CLASS_SCREENCAPTURE::buffer; 
   for( count1=y ; count1<=(y+config_size_y-1) ; count1++) 
   { 
      // line put 
      for( count2=x ; count2<=(x+config_size_x-1) ; count2++) 
      { 
 *( (unsigned char far *)(0xb8000000lu)+( 160*count1+(2*count2) ) ) 
 = *(tempbuffer++); 
 *( (unsigned char far *)(0xb8000000lu)+( 160*count1+(2*count2)+1 ) ) 
 = *(tempbuffer++); 
      } 
   } 
   return; 
} 
