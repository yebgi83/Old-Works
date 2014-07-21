#include"xms.cpp" 
#include 
void main() 
{ 
   MEMORY_Information t1; 
   printf("\nBrightieng Soft Team ---------------------------- Lee Kang Yong\n" 
  "Sens for Dos prepare version XMS Memory manager Example program\n" ); 
   if ( t1.InitXMS() )  /* XMS»Æ¿Œ */ 
   { 
      printf("XMS Check................ XMS found.\n"); 
      printf("XMS Version Check ....... %d.%d\n",t1.XMSmajor,t1.XMSminor); 
      printf("XMS Free Memory Check ... %d KB\n",t1.maxfreeXMS); 
   } 
   else 
      printf("XMS not found........\n"); 

   printf("---------------------------------------------------------------\n"); 
