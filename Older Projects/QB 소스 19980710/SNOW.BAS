DECLARE SUB SetRGB (C, R, G, B) 
'¾Æ ¶ï¶ïÇØ ÀÌ¹ø¿£ ´«³»¸®±â ^^; 
SCREEN 13 
SnowPaths = 100 
'´« °æ·ÎÀÇ »ý¼º 
MaxCol = 37 
FOR Count = 1 TO SnowPaths 
   X = INT(RND * 320) + 1 
   Y = INT(RND * 5) + 1 
   PlusY = INT(RND * 2) + 1 
   Col = INT(RND * MaxCol) + 1 
   DO 
     Y = Y + PlusY 
     PSET (X - INT(RND * 8) - 2, Y), Col 
     IF Y >= 220 THEN EXIT DO 
     PlusY = PlusY + INT(RND * 2) 
     Col = Col + 1 
     IF Col > MaxCol THEN Col = 1 
   LOOP 
NEXT Count 
FOR Count = 1 TO MaxCol 
   SetRGB Count, 0, 0, 0 
NEXT Count 
P = 0 
DO 
  P = P + 1 
  IF P - 3 >= 1 THEN SetRGB P - 3, 10, 10, 10 
  IF P - 2 >= 1 THEN SetRGB P - 2, 20, 20, 20 
  IF P - 1 >= 1 THEN SetRGB P - 1, 40, 40, 40 
  SetRGB P, 63, 63, 63 
  FOR Delay = 1 TO 20000: NEXT Delay 
  IF P - 3 >= 1 THEN SetRGB P - 3, 0, 0, 0 
  IF P - 2 >= 1 THEN SetRGB P - 2, 0, 0, 0 
  IF P - 1 >= 1 THEN SetRGB P - 1, 0, 0, 0 
  SetRGB P, 0, 0, 0 
  IF P = MaxCol THEN P = 0 
LOOP 


SUB SetRGB (C, R, G, B) 
   OUT &H3C8, C 
   OUT &H3C9, R 
   OUT &H3C9, G 
   OUT &H3C9, B 
END SUB 

