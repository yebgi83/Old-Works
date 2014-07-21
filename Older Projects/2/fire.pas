program fireversion; 

uses crt; 

var 
 FireBuf : array[1..100,1..200] of byte; 

function inportb( port : Integer ) : Byte; 
var 
  temp : Byte; 
begin { begin of function } 
  asm { asm } 
     mov dx,port; 
     in ax,dx; { get data from (port dx) } 
     mov temp,al; 
  end; 
  inportb := temp; 
end; 

procedure outportb( port : Integer; data : Byte ); 
assembler; 
asm 
  mov dx,port; 
  mov al,data; 
  out dx,al; 
end; 

procedure PaletteProcess; 
var 
  c : Byte; 
  c2 : Byte; 
begin 
  for c := 0 to 255 do 
  begin { for } 
     outportb( $3c8 , c ); 
     c2 := c div 4; 
     c2 := c2*2; 
     if ( c2>=63 ) then c2:=63; 
     outportb( $3c9 , c2 ); 
     c2 := (c div 6); 
     outportb( $3c9 , c2 ); 
     outportb( $3c9 , 0 ); 
  end; 
end; 

procedure SetMode( mode : Integer ); assembler; 
asm 
  mov ax,mode; 
  int 10h; { call video interrupt } 
end; 

procedure PutPixel ( x:Integer; y:Integer; col:Byte ); 
begin 
  { direct VRAM } 
  MemL[ $a000 : (320*y+x) ] := col; 
end; 
procedure ProcessTextBuf; 
var 
 c,c1,c2 : Integer; 
begin 
 gotoxy(1,1); 
 for c:=1 to 100 do 
 begin 
     for c1:=1 to 200 do 
     begin 
         if( c = 100 ) then 
         begin 
             FireBuf[c][c1] := random(255); 
         end else 
         begin 
             if(( c1>=2 ) and ( c1<=199)) then 
             begin 
                c2 := FireBuf[c+1][c1]; 
                c2 := c2 + FireBuf[c+1][c1-1]; 
                c2 := c2 + FireBuf[c+1][c1+1]; 
                c2 := c2 + FireBuf[c][c1]; 
                if( c2>=3 ) then c2 := c2 div 4; 
                if( c2<=3 ) and ( c2>=1 ) then dec(c2); 
                if( c2<=6 ) and ( c2>=3 ) then c2 := c2 - 2; 
                if( c2>=4 ) then c2 := c2 - 4; 
                FireBuf[c][c1] := c2; 
             end; 
         end; 
     end; 
 end; 
 for c:=1 to 99 do 
 begin 
     for c1:=1 to 200 do 
         putpixel(c1,c,FireBuf[c][c1]); 
 end; 
end; 

var 
 C,C1,C2 : Integer; 
begin 
 SetMode( $13 ); 
 PaletteProcess; 
 for c:=1 to 100 do 
 begin 
     for c1:=1 to 200 do 
         FireBuf[c][c1] := 0; 
 end; 
 while(true) do 
 begin 
     ProcessTextBuf; 
     if( KeyPressed ) then 
       if ( ReadKey = chr(27) ) then exit; 
 end; 
 SetMode( $3 ); 
end 
