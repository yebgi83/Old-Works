void PULLDOWN_unit_registerd( void ); 
void PULLDOWN_runcommand( int mainnum , int subnum ); 

void VIEW_mainscreen( void ); 
void VIEW_freememory( void ); 
void VIEW_startingbox( void ); 

void PULLDOWN_unit_registerd( void ) 
{ 
   pulldown.unit_append(1," @File "); 
      pulldown.unit_subappend(" @New        "); 
      pulldown.unit_subappend(" @Open...    "); 
      pulldown.unit_subappend(" @Save       "); 
      pulldown.unit_subappend(" Save @as... "); 
      pulldown.unit_subappend(" @Dos shell  "); 
      pulldown.unit_subappend(" @Quit       "); 
   return; 
} 

void VIEW_freememory( void ) 
{ 
    gotoxy(1,25); 
    textattr( 7 << 4 ); 
    cprintf("  Free memory : %lu Bytes  " , farcoreleft() ); 
} 

void VIEW_mainscreen( void ) 
{ 
    register int c; 
    clrscr(); 
    textattr( (1 << 4) | 15 ); 
    for( c=0 ; c<=4096 ; c+=2 ) 
    { 
*( (unsigned char far *) (0xb8000000lu+c))=176; 
*( (unsigned char far *) (0xb8000000lu+c+1))=7; 
    } 
    gotoxy(1,1); 
    textattr( (1 << 4) | 15 ); 
    cprintf("                                                                                "); 
    for( c=0 ; c<=160 ; c+=2 ) 
    { 
*( (unsigned char far *) (0xb8000000lu+160*24+c))=' '; 
*( (unsigned char far *) (0xb8000000lu+160*24+c+1))=(7<<4) | 0; 
    } 
    VIEW_freememory(); 
    return; 
} 

void VIEW_startingbox( void ) 
{ 
    CLASS_BOX t001; 
    t001.draw(15,1,19,5,40,13,16); 
    gotoxy(21,7); 
    cprintf(" MINZ technologies 1998 (C) 컴컴컴컴?n"); 
    gotoxy(25,10); 
    cprintf(" POWER ASM IDE Version 0.14 "); 
    textcolor(14); 
    gotoxy(21,13); 
    cprintf(" Auto-finding plug-in...... completed"); 
    gotoxy(21,14); 
    cprintf(" Execute program ready..... completed"); 
    return; 
} 

void RUNCOMMAND_osshell( void ) 
{ 
/*     CLASS_SCREENCAPTURE savescreen; 
    savescreen.getregion(0,0,80,25); 
    clrscr(); 
    system("COMMAND\0"); 
    savescreen.putregion(0,0); */ 
} 
void PULLDOWN_runcommand( int mainnum , int subnum ) 
{ 
    if( mainnum==1 && subnum==5 ) RUNCOMMAND_osshell(); // OS Shell 
    return; 
} 
