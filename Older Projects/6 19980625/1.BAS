DECLARE SUB rrgbpalette (C, r) 
DIM rgbpalette(16, 3) 
FIGHT = 15 
AIREC = 2' AI -- 999 - All 
FOR I = 1 TO 16 
  FOR j = 1 TO 3 
      READ rgbpalette(I, j) 
NEXT j, I 
DATA 0,0,0 
DATA 0,0,42 
DATA 0,42,0 
DATA 0,42,42 
DATA 42,0,0 
DATA 42,0,42 
DATA 42,21,0 
DATA 42,42,42 
DATA 21,21,21 
DATA 21,21,63 
DATA 21,63,21 
DATA 21,63,63 
DATA 63,21,21 
DATA 63,21,63 
DATA 63,63,21 
DATA 63,63,63 
SCREEN 0, , 0 
0 CLS 
WIDTH 80, 50 
'FOR i = 1 TO 16 
'    rrgbpalette i, i 
'NEXT i 
RANDOMIZE TIMER 
DO UNTIL INKEY$ = " " 
  CCC = INT(RND * FIGHT) + 1 
  COLOR CCC 
  a = INT(RND * 80) + 1 
  b = INT(RND * 42) + 1 
  LOCATE b, a: PRINT CHR$(219) 
LOOP 
DIM xp(FIGHT), yp(FIGHT), top(FIGHT) 
FOR I = 1 TO FIGHT 
xp(I) = INT(RND * 48) + 1 
yp(I) = INT(RND * 80) + 1 
NEXT I 
b = 4 
message$ = "LeeKangYongGenius" 
DO UNTIL INKEY$ = " " 
 FOR I = 1 TO FIGHT 
  C = 0 
  'IF I = 4 THEN C = 1 
  'IF I = 2 THEN C = 1 
  IF I <> 2 AND I < 5 THEN C = 1 
  IF C = 0 THEN C = I 
  COLOR C: LOCATE xp(I), yp(I): PRINT CHR$(219) 
  IF INT(RND * 2) + 1 = 1 THEN b = INT(RND * 4) + 1 
  Try = 0 
Loop1: 
  IF b = 1 THEN xp(I) = xp(I) - 1: IF xp(I) = 0 THEN xp(I) = 1 
  IF b = 2 THEN xp(I) = xp(I) + 1: IF xp(I) = 49 THEN xp(I) = 48 
  IF b = 3 THEN yp(I) = yp(I) - 1: IF yp(I) = 0 THEN yp(I) = 1 
  IF b = 4 THEN yp(I) = yp(I) + 1: IF yp(I) = 81 THEN yp(I) = 80 
  IF I = AIREC OR AIREC = 999 THEN 
     curc = SCREEN(xp(I), yp(I), 1) 
     IF curc = I THEN 
        Try = Try + 1 
        IF Try < 4 THEN GOTO Loop1 
     END IF 
   END IF 

 NEXT I 
LOOP 
DIM SCORE(15) 
FOR I = 1 TO 48 
 FOR j = 1 TO 80 
    SCORE(SCREEN(I, j, 1)) = SCORE(SCREEN(I, j, 1)) + 1 
 NEXT j 
NEXT I 
SCREEN 0, , 1 
LOCATE 1, 1: PRINT "Last Score" 
DIM ccol(15) 
FOR I = 1 TO FIGHT 
  COLOR I: LOCATE I + 1, 1: PRINT "?" 
  COLOR 8: LOCATE I + 1, 10: PRINT STRING$(40, "?"); 
  COLOR 14: LOCATE I + 1, 10: PRINT STRING$(40 * (SCORE(I) / 3840), "?"); 
  COLOR 15: LOCATE I + 1, 60: PRINT "Score "; SCORE(I) 
  COLOR 15: LOCATE I + 1, 72: PRINT USING "###.##"; (SCORE(I) / 3840) * 100 
  TOTAL = TOTAL + SCORE(I) 
  ccol(I) = I 
NEXT I 
  COLOR 15: LOCATE 17, 1: PRINT "Blank" 
  COLOR 8: LOCATE 17, 10: PRINT STRING$(40, "?"); 
  COLOR 14: LOCATE 17, 10: PRINT STRING$(40 * ((3840 - TOTAL) / 3840), "?"); 
  COLOR 15: LOCATE 17, 60: PRINT "Score "; 3840 - TOTAL 
FOR I = 1 TO FIGHT 
 FOR j = I TO FIGHT 
    IF SCORE(I) < SCORE(j) THEN 
       SWAP SCORE(I), SCORE(j) 
       SWAP ccol(I), ccol(j) 
    END IF 
 NEXT j 
NEXT I 
I$ = INPUT$(1) 
FOR I = 1 TO FIGHT 
  LOCATE I + 1, 1: PRINT SPACE$(80) 
  COLOR ccol(I): LOCATE I + 1, 1: PRINT "?" 
  COLOR 8: LOCATE I + 1, 10: PRINT STRING$(40, "?"); 
  COLOR 14: LOCATE I + 1, 10: PRINT STRING$(40 * (SCORE(I) / 3840), "?"); 
  COLOR 15: LOCATE I + 1, 60: PRINT "Score "; SCORE(I) 
  COLOR 15: LOCATE I + 1, 72: PRINT USING "###.##"; (SCORE(I) / 3840) * 100 
NEXT I 
I$ = INPUT$(1) 
SCREEN 0, , 0 
FOR I = 1 TO FIGHT 
   DO UNTIL INKEY$ = " " 
      rrgbpalette ccol(I), 20 
      rrgbpalette ccol(I), 35 
   LOOP 
   rrgbpalette ccol(I), I + 1 
NEXT I 

SUB rrgbpalette (C, r) 
PALETTE C, r 
END SUB 
