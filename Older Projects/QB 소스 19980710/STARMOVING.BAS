DECLARE SUB putpixel (x, y, col) 
DECLARE SUB Starchogihua () 
DECLARE SUB Starmove () 
SCREEN 13 
CONST TOTALSTARS = 100 
DIM SHARED starx(TOTALSTARS) 
DIM SHARED stary(TOTALSTARS) 
DIM SHARED starcolor(TOTALSTARS) 
DIM SHARED STARSPEED(TOTALSTARS) 

Starchogihua 
DO UNTIL INKEY$ <> "" 
  Starmove 
LOOP 

WIDTH 80 
PRINT "Star move Source" 
PRINT "Made by Lee Kang yong" 

SUB putpixel (x, y, col) 
   DEF SEG = &HA000   ' Video segment 
   POKE 320 * y + x, col 
END SUB 

SUB Starchogihua 
  FOR i = 1 TO TOTALSTARS 
     starx(i) = INT(RND * 320) + 1 
     stary(i) = INT(RND * 200) + 1 
     starcolor(i) = INT(RND * 255) + 1 
     STARSPEED(i) = RND * 2 
     putpixel starx(i), stary(i), starcolor(i) 
  NEXT i 
END SUB 

SUB Starmove 
   FOR i = 1 TO TOTALSTARS 
     putpixel starx(i), stary(i), 0 
     starx(i) = starx(i) - STARSPEED(i) 
     IF starx(i) < 1 THEN 
         starx(i) = 319 
         stary(i) = INT(RND * 200) + 1 
         starcolor(i) = INT(RND * 255) + 1 
         STARSPEED(i) = RND * 2 
     END IF 
     putpixel starx(i), stary(i), starcolor(i) 
   NEXT i 
END SUB 

