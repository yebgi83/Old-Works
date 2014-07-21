DECLARE SUB Viewb () 
DECLARE SUB Processb () 
CLEAR , , 30000 
DIM SHARED b(51, 51), c(51, 51) 
SCREEN 13 
FOR i = 1 TO 255 
   OUT &H3C8, i 
   OUT &H3C9, INT(i / 4) 
   OUT &H3C9, INT(i / 4) 
   OUT &H3C9, 0 
NEXT i 
FOR i = 1 TO 10 
   x = INT(RND * 50) + 1 
   y = INT(RND * 50) + 1 
   c = 450 
   b(x, y) = c 
   b(x, y - 1) = c 
   b(x, y + 1) = c 
   b(x - 1, y) = c 
   b(x + 1, y) = c 
   b(x - 1, y - 1) = c 
   b(x + 1, y + 1) = c 
   b(x - 1, y + 1) = c 
   b(x + 1, y - 1) = c 
NEXT i 
DO 
Viewb 
Processb 
LOOP 

SUB Processb 
   FOR i = 1 TO 50 
       FOR j = 1 TO 50 
             IF b(i, j) <= 0 THEN b(i, j) = 0 
             IF b(i, j) >= 255 THEN b(i, j) = b(i, j) - 10 
             IF c(i, j) = 0 AND b(i, j) >= 1 THEN 
                IF INT(RND * 2) + 1 = 1 AND c(i, j + 1) = 0 THEN c(i, j + 1) = 1: b(i, j + 1) = (b(i, j + 1) + b(i, j)) / 2 
                IF INT(RND * 2) + 1 = 1 AND c(i + 1, j) = 0 THEN c(i + 1, j) = 1: b(i + 1, j) = (b(i + 1, j) + b(i, j)) / 2 
                IF INT(RND * 2) + 1 = 1 AND c(i - 1, j) = 0 THEN c(i - 1, j) = 1: b(i - 1, j) = (b(i - 1, j) + b(i, j)) / 2 
                IF INT(RND * 2) + 1 = 1 AND c(i, j - 1) = 0 THEN c(i, j - 1) = 1: b(i, j - 1) = (b(i, j - 1) + b(i, j)) / 2 

             END IF 
   NEXT j, i 
END SUB 

SUB Viewb 
   FOR i = 1 TO 50 
   FOR j = 1 TO 50 
           c(j, i) = 0 
           IF b(j, i) >= 255 THEN c = 255 ELSE c = b(j, i) 
           PSET (j, i), c 
   NEXT j, i 
END SUB 

