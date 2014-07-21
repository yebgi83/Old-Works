'안냐세요 이강용입니다. 
'이소스는 차라리 QBASIC으로 보세요 
'속도가 더 느려서 더욱 좋게 보실수 있습니다. 
'그럼. 
DECLARE SUB PutStar (x, y, c) 
DECLARE SUB SetPalette (c, r, g, b) 
DIM LightLevel(15) 
DIM CLevel(15), Switch(15) 
FOR i = 1 TO 15 
   READ LightLevel(i) 
NEXT i 
DATA 0,1,5,10,15,20,25,30,35,40,45,50,55,60,63 
SCREEN 12 
stars = 1000 
FOR i = 1 TO stars 
   x = INT(RND * 640) + 1 
   y = INT(RND * 480) + 1 
   c = INT(RND * 15) + 1 
   PutStar x, y, c 
NEXT i 
FOR i = 1 TO 15 
   CLevel(i) = i 
   SetPalette i, LightLevel(CLevel(i)), LightLevel(CLevel(i)), LightLevel(CLevel(i)) 
   'IF INT(RND * 2) + 1 = 1 THEN Switch(i) = -1 ELSE Switch(i) = 1 
   Switch(i) = 1 
NEXT i 
DO UNTIL INKEY$ <> "" 
   FOR i = 1 TO 15 
       CLevel(i) = CLevel(i) + Switch(i) 
       IF CLevel(i) >= 15 AND Switch(i) = 1 THEN CLevel(i) = 14: Switch(i) = -1 
       IF CLevel(i) = 0 AND Switch(i) = -1 THEN CLevel(i) = 1: Switch(i) = 1 
       SetPalette i, LightLevel(CLevel(i)), LightLevel(CLevel(i)), LightLevel(CLevel(i)) 
       FOR t = 1 TO 100: NEXT t 
   NEXT i 
LOOP 

SUB PutStar (x, y, c) 
   PSET (x, y), c 
   IF INT(RND * 2) + 1 = 1 THEN 
      PSET (x - 1, y), c - 1 
      PSET (x + 1, y), c - 1 
      PSET (x, y - 1), c - 1 
      PSET (x, y + 1), c - 1 
   ELSE 
      PSET (x - 1, y - 1), c - 1 
      PSET (x + 1, y + 1), c - 1 
      PSET (x + 1, y - 1), c - 1 
      PSET (x - 1, y + 1), c - 1 
   END IF 
END SUB 

SUB SetPalette (c, r, g, b) 
   OUT &H3C8, c 
   OUT &H3C9, r 
   OUT &H3C9, g 
   OUT &H3C9, b 
END SUB 

