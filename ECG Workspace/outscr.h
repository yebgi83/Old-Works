char ScrBuf[80][22];
char Chars[2][4] = {' ','-','_','=',' ','*','*','*'};

void Draw( short x, short y, short opt )
{
   if( y < 0 || y >= 44 ) return;
   ScrBuf[x][y / 2] |= (opt << 4);
   if( (y % 2) == 0 )
      ScrBuf[x][y / 2] |= 0x02;
   else
      ScrBuf[x][y / 2] |= 0x01;
}

void RowClr( short x ) 
{
   short c;
   for( c = 0; c < 22; c++ )
      ScrBuf[x][c] = 0;
}

void Clear( short x, short y )
{
   if( y < 0 || y >= 44 ) return;

   ScrBuf[x][y / 2] &= 0xf0;
   if( (y % 2) == 0 )
      ScrBuf[x][y / 2] &= 0x01;
   else
      ScrBuf[x][y / 2] &= 0x02;
}

void View( void )
{
   short x, y;
   for( y = 0; y < 22; y++ )
       for( x = 0; x < 80; x++ )
           printf("%c", Chars[ (ScrBuf[x][y] & 0xf0) >> 4 ][ ScrBuf[x][y] & 0x03 ] );
}

