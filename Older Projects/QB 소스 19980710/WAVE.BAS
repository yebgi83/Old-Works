DIM a(320) 
SCREEN 13 
FOR I = 1 TO 320 
   IF INT(RND * 2) + 1 = 1 AND INT(RND * 2) + 1 = 1 THEN 
      IF STE = 1 THEN STE = -1: a(I) = STE ELSE STE = 1: a(I) = STE 
   END IF 
   IF C >= 31 THEN STE = -1: a(I) = STE 
   IF C <= 20 THEN STE = 1: a(I) = STE 
   C = C + STE 
NEXT I 
C = 21 
FOR I = 1 TO 16 
   FOR J = 1 TO 16 
       CC = CC + 1 
       OUT &H3C8, CC 
       OUT &H3C9, 4 * J 
       OUT &H3C9, 4 * J 
       OUT &H3C9, 4 * J 
NEXT J, I 

STE2 = 1 
DO 
   K = K + STE2 
   IF K <= -5 THEN STE2 = 1 
   IF K > 5 THEN STE2 = -1 
FOR I = 1 TO 50 
   C = 18 + COS(90 - (90 * (I / 360))) * K 
   STE = 1 
   FOR J = 1 TO 25 
      PSET (J, I), C 
      C = C + STE 
      IF C < 0 THEN STE = 1 
      IF C >= 255 THEN STE = -1 
   NEXT J 
NEXT I 
LOOP 
