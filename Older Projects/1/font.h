char *g_pFontBuf; 
char InitializeEngFontBuf( void ); 
void RemoveEngFontBuf( void ); 
char LoadEngFont( char l_pfilename[14] ); 

char InitializeEngFontBuf( void ) 
{ 
   g_pFontBuf = (char *) new char [4096]; 
   if( !g_pFontBuf ) return 0; else return 1; 
} 

void RemoveEngFontBuf( void ) 
{ 
   delete g_pFontBuf; 
} 

char LoadEngFont( char l_pFileName[14] ) 
{ 
   FILE *l_pFileStruct; 
   if( !(l_pFileStruct=fopen( l_pFileName,"rb" )) ) // not exist check 
return 0;       // send signal 
   fread( g_pFontBuf,1,4096,l_pFileStruct ); 
   fclose(l_pFileStruct); 
   return 1;     // load success. 
} 

void PutChar( T_PVS l_pvs,int l_x,int l_y,char l_code ) 
{ 
   unsigned char l_pBitMaskTable[]={128,64,32,16,8,4,2,1}; 
   unsigned char *l_pDestPutPos; 
   unsigned char *l_pSrcPutPos; 
   register int  l_counter1=0;     // counter for y 
   register int  l_counter2;       // counter for x 
   l_pDestPutPos=l_pvs+(320*l_y)+l_x; 
   l_pSrcPutPos =g_pFontBuf+(16*l_code); 
   do 
   { 
for( l_counter2=0;l_counter2<=7;l_counter2++ ) 
   *(l_pDestPutPos++)=((*l_pSrcPutPos) & l_pBitMaskTable[l_counter2]) 
      ? 15:0; 
l_pSrcPutPos++; 
l_pDestPutPos+=312; 
   }while( (l_counter1++)<16 ); 
} 

void Printf( T_PVS l_pvs,int l_x,int l_y,char l_pstr[255],... ) 
{ 
   va_list l_vlist; 
   char l_pfmtstr[255]; 
   char *l_pPos=l_pfmtstr; 
   // get va_list 
   va_start(l_vlist,l_pstr);           // l_vlist is arguments after l_pstr. 
// (?) 
   vsprintf(l_pfmtstr,l_pstr,l_vlist );// vsprintf 
// =(sprintf for using argument list) 
   while( *l_pPos ) 
   { 
PutChar( l_pvs,l_x,l_y,*l_pPos ); 
l_x+=8; 
l_pPos++; 
   } 
   return; 

