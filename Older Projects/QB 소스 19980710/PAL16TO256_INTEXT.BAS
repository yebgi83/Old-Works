' 안냐세요 이강용입니다. 
' sopepos님의 SOP파일 제작기 NOTEW에 
' 몇개의 스크린 세이버 같은게 들어있는데 
' 그중에 16칼라 텍스트MODE에서 256칼라가 그려지지 않습니까? 
' 그것은 팔렛트 전환을 한 일종의 속임수입니다. 이 소스를 보시길 
DECLARE SUB CHECK1 () 
CLS 
COLOR 15, 1 
LOCATE 1, 1: PRINT SPACE$(80) 
LOCATE 1, 1: PRINT "  ScreenSaver  -  Made by Lee Kang-yong" 
DO 
I$ = INKEY$: IF I$ <> "" THEN GOTO A 
FOR I = 1 TO 64 
   FOR J = 1 TO 15: CHECK1: NEXT 
   OUT &H3C8, 0 
   OUT &H3C9, 0 
   OUT &H3C9, 0 
   OUT &H3C9, 0 
NEXT I 
CHECK1 
DO 
FOR J = 50 TO 64 
I$ = INKEY$: IF I$ <> "" THEN GOTO A 
FOR I = J TO 31 STEP -1 
   OUT &H3C8, 0 
   OUT &H3C9, I 
   OUT &H3C9, 0 
   OUT &H3C9, 0 
   CHECK1 
NEXT I 
FOR I = J TO 31 STEP -1 
   OUT &H3C8, 0 
   OUT &H3C9, I 
   OUT &H3C9, I 
   OUT &H3C9, 0 
   CHECK1 
NEXT I 
FOR I = J TO 31 STEP -1 
   OUT &H3C8, 0 
   OUT &H3C9, 0 
   OUT &H3C9, I 
   OUT &H3C9, 0 
   CHECK1 
NEXT I 
FOR I = 31 TO J 
   OUT &H3C8, 0 
   OUT &H3C9, 0 
   OUT &H3C9, 0 
   OUT &H3C9, I 
   CHECK1 
NEXT I 
FOR K = 1 TO 20: CHECK1: NEXT K 
J = 50 
NEXT J 
LOOP 
LOOP 
A: 
SCREEN 9 
SCREEN 0 
END 

SUB CHECK1 
DO 
 B = 64 
 IF (INP(&H3DA) AND B) = 0 THEN EXIT DO 
 IF (INP(&H3DA) AND B) = 0 THEN EXIT DO 
LOOP 
END SUB 

