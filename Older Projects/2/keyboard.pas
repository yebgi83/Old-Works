{ Key Test 
 Made by Lee Kang-yong } 
program lowlevelunit; 

uses CRT; 

function Inportb( Port : Integer ) : Byte; 
var 
   t : Byte; 
begin 
   asm 
      mov dx,Port; 
      in ax,dx; 
      mov t,al; 
   end; 
   Inportb := t; 
end; 

VAR 
    ch : Char; 
BEGIN 
  while (TRUE) do 
  begin 
     if ( KeyPressed ) then { KeyPressed? } 
        if ( ReadKey = Chr(27) ) then Exit; 
     ch := Chr(Inportb($60)); 
     if ( (Ord(ch) and 128) = 0 ) then 
     begin 
        write( 'KeyPressed' ); 
     end else 
        write( 'Non-KeyPressed' ); 
     write( '   -   KeyData: ',Ord(ch),'(',ch,')'); 
     writeln( '  press ESC to exit... ' ); 
  end; 
  { 
    *** For Pascal *** 
    if ( KeyPressed ) then 
      if ( ReadKey = Chr(27) ) then Exit; 
    *** For C *** 
    if ( kbhit() ) 
      if ( getch() == 27 ) break; 
  } 
END 
