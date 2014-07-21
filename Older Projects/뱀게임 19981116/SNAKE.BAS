DECLARE SUB PutChar (Y, X, C1, C2, D$) 
DECLARE SUB Queue.Push (px, py) 
DECLARE SUB Queue.Pop (gx, gy) 
DECLARE SUB Queue.GetDirect (position, gx, gy) 
DECLARE SUB InitailizeGameScreen () 
DECLARE SUB MainScreen () 
DECLARE SUB ViewBackGround (Round) 
DECLARE SUB SaveBackGround (Dest$) 
DECLARE SUB MakeItem () 
DECLARE SUB PlayPaletteChange () 
DECLARE SUB WaitBox (S$) 
DECLARE SUB PaletteEffect () 
DECLARE SUB ObjectView () 
DECLARE SUB DemoKeyRoutine () 
DECLARE SUB CreateCrashObjects (Stage) 
DECLARE SUB RecoverChar (Y, X) 
DECLARE SUB ViewStatus () 
DECLARE FUNCTION StageEvent (Stage) 
DECLARE FUNCTION Title$ () 
DECLARE FUNCTION ItemCrashCheck () 
DECLARE FUNCTION ObjectMove () 
DECLARE FUNCTION KeyRoutine () 
          
CONST CQUEUESIZE = 128 
CONST CPLAYERMARK$ = "?" 
DIM SHARED COBJECT$ 
DIM SHARED CITEMMARK$ 
CITEMMARK$ = CHR$(5) 
COBJECT$ = "@" 
' 큐를 이용한 프로그램입니다. 

DIM SHARED GLifes 
DIM SHARED GStage, GAllStage 
DIM SHARED GItems 
DIM SHARED GScore(2) 
DIM SHARED GSaveBackGroundBuf$ 
DIM SHARED GQueue(CQUEUESIZE, 2), GQHEAD, GQTAIL  '큐용 
DIM SHARED GCurPath$                              '현재 물체의 이동경로 
DIM SHARED GCX, GCY                               '현재 물체의 위치 
DIM SHARED GPC, GLength                           '찍기 카운터와 뱀길이 
DIM SHARED GCC                                    '화려한 칼라 목적 카운터 
DIM SHARED GDEMOID.X, GDEMOID.Y 
DIM SHARED CStageUValue1 
DIM SHARED CStageUValue2 
DIM SHARED CStageUValue3 
DIM SHARED CStageUValue4 
DIM SHARED CStageUValue5 
DIM SHARED CStageUValue6 
DIM SHARED CStageUValue7 
DIM SHARED CStageUValue8 

RANDOMIZE TIMER 

BeginCode: 

'Initialize 
GStage = 1: CScore(1) = 0: GLifes = 5 
GAllStage = 4 

SCREEN 12: SCREEN 0 
IK$ = Title$ 
IF IK$ = CHR$(27) THEN SCREEN 12: SCREEN 0: END 
IF IK$ = "D" THEN GStage = INT(RND * GAllStage) + 1 
BeginGame: 

LDELAYTIME = 2000 - (10 * GStage) 
GQHEAD = 0: GQTAIL = 0: GCurPath$ = "D": GCX = 5: GCY = 5 
GLength = 7: GPC = 0 

PlayPaletteChange 
InitailizeGameScreen 
ViewBackGround GStage 
CreateCrashObjects GStage 
SaveBackGround GSaveBackGroundBuf$ 
MakeItem 

IF IK$ = "D" THEN 
  LOCATE 1, 1: PRINT " Demonstlation. Press any key to mainmenu." 
ELSE 
  ViewStatus 
END IF 

DO 
  PlayPaletteChange 
  GPC = GPC + 1: IF GPC > GLength THEN GPC = GLength 
  GCC = GCC + 1: IF GCC > 12 THEN GCC = 1 
  IF IK$ = "1" THEN 
     IF KeyRoutine = 27 THEN GOTO BeginCode'키 루틴 담당 
  END IF 
  IF IK$ = "D" THEN 
     KC$ = INKEY$ 
     IF KC$ <> "" THEN GOTO BeginCode ELSE DemoKeyRoutine 
  END IF 
  IF StageEvent(GStage) = -1 OR ObjectMove = 1 THEN 
     WaitBox "Crashed!!!" 
     GLifes = GLifes - 1 
     IF IK$ = "D" THEN GOTO BeginCode 
     IF GLifes = 0 THEN WaitBox "Game Over": GOTO BeginCode 
     GOTO BeginGame 
  END IF 
  IF ItemCrashCheck = 1 THEN '출력전 확인 아이템 먹었나? 
     ' 아이템 먹었다면 
     ' 물체를 먹었을경우 길이의 기하급수적확장 방지 목적으로 
     GItems = GItems - 1 
     IF GItems = 0 THEN 
        WaitBox "Stage clear." 
        GStage = GStage + 1 
        IF IK$ = "1" THEN GOTO BeginGame ELSE GOTO BeginCode 
     END IF 
     GLength = GLength + 1 
     ' 먹을것의 위치 이동 
     MakeItem 
     GScore(1) = GScore(1) + 10 
     IF IK$ = "1" THEN ViewStatus 
     LDELAYTIME = LDELAYTIME - 40 
     IF LDELAYTIME < 0 THEN LDELAYTIME = 0 
  END IF 
  ObjectView '물체 출력 
  FOR T = 1 TO LDELAYTIME: NEXT T 
LOOP 
SCREEN 12: SCREEN 0: END 

SUB CreateCrashObjects (Stage) 
   SELECT CASE Stage 
      CASE 1 
        GItems = 10 
      CASE 2 
        GItems = 12 
        COBJECT$ = "*" 
        FOR T = 1 TO 3 
           FOR I = 20 TO 60 
              PutChar 5 + (4 * T), I, 7, 0, COBJECT$ 
           NEXT I 
        NEXT T 
      CASE 3 
        GItems = 15 
        COBJECT$ = "#" 
        FOR T = 1 TO 3 
           FOR I = 40 - (8 * T) TO 40 + (8 * T) 
              PutChar 5 + (4 * T) + ABS(INT(COS(I / 3.14) * 1)), I, 7, 0, COBJECT$ 
           NEXT I 
        NEXT T 
      CASE 4 
        COBJECT$ = "$" 
        GItems = 8 
   END SELECT 
END SUB 

SUB DemoKeyRoutine 
   ' 함수명 : DemoKeyRoutine 
   ' 역할 : 컴퓨터가 알아서 이동 함. 
   ' 1. 충돌을 확인하며 알아서 이동 
   CrashPossible = 0 
   LC = 0 
   ' 0. 물체를 향해 접근 
   IF GDEMOID.X - GCX > 0 AND GCurPath$ <> "L" THEN GCurPath$ = "R"'오른쪽으로 가까움 
   IF GDEMOID.X - GCX < 0 AND GCurPath$ <> "R" THEN GCurPath$ = "L"'왼쪽으로 가까움 
   IF GDEMOID.Y - GCY > 0 AND GCurPath$ <> "U" THEN GCurPath$ = "D"'밑으로 가까움 
   IF GDEMOID.Y - GCY < 0 AND GCurPath$ <> "D" THEN GCurPath$ = "U"'밑으로 가까움 
   DO 
     LC = LC + 1 
     IF LC > 10 THEN EXIT DO 
     IF GCurPath$ = "L" AND GCX - 1 > 0 AND SCREEN(GCY, GCX - 1, 0) = ASC(COBJECT$) THEN GCurPath$ = "U": CrashPossible = 1 
     IF GCurPath$ = "U" AND GCY - 1 > 2 AND SCREEN(GCY - 1, GCX, 0) = ASC(COBJECT$) THEN GCurPath$ = "R": CrashPossible = 1 
     IF GCurPath$ = "R" AND GCX + 1 < 81 AND SCREEN(GCY, GCX + 1, 0) = ASC(COBJECT$) THEN GCurPath$ = "D": CrashPossible = 1 
     IF GCurPath$ = "D" AND GCY + 1 < 26 AND SCREEN(GCY + 1, GCX, 0) = ASC(COBJECT$) THEN GCurPath$ = "L": CrashPossible = 1 ELSE EXIT DO 
   LOOP 
   IF CrashPossible = 1 THEN EXIT SUB 
   CrashPossible = 0 
   LC = 0 
   DO 
     LC = LC + 1 
     IF LC > 10 THEN EXIT DO 
     IF GCurPath$ = "L" AND GCX - 1 > 0 AND SCREEN(GCY, GCX - 1, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "U": CrashPossible = 1 
     IF GCurPath$ = "U" AND GCY - 1 > 2 AND SCREEN(GCY - 1, GCX, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "R": CrashPossible = 1 
     IF GCurPath$ = "R" AND GCX + 1 < 81 AND SCREEN(GCY, GCX + 1, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "D": CrashPossible = 1 
     IF GCurPath$ = "D" AND GCY + 1 < 26 AND SCREEN(GCY + 1, GCX, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "L": CrashPossible = 1 ELSE EXIT DO 
   LOOP 
   IF CrashPossible = 1 THEN EXIT SUB 
   ' 2. 테두리 충돌 체크 
   CrashPossible = 0 
   LC = 0 
   DO 
     LC = LC + 1 
     IF LC > 10 THEN EXIT DO 
     IF GCY - 1 = 1 AND GCurPath$ = "U" THEN GCurPath$ = "L" 
     IF GCY + 1 = 25 AND GCurPath$ = "D" THEN GCurPath$ = "R" 
     IF GCX - 1 = 1 AND GCurPath$ = "L" THEN GCurPath$ = "D" 
     IF GCX + 1 = 80 AND GCurPath$ = "R" THEN GCurPath$ = "U" 
   LOOP 
   IF CrashPossible = 1 THEN EXIT SUB 
   ' 3. 재확인 
   IF INT(RND * 1) = 1 THEN 
      CrashPossible = 0 
      LC = 0 
      DO 
         LC = LC + 1 
         IF LC > 10 THEN EXIT DO 
         IF GCurPath$ = "L" AND GCX - 1 > 0 AND SCREEN(GCY, GCX - 1, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "U" 
         IF GCurPath$ = "U" AND GCY - 1 > 2 AND SCREEN(GCY - 1, GCX, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "R" 
         IF GCurPath$ = "R" AND GCX + 1 < 81 AND SCREEN(GCY, GCX + 1, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "D" 
         IF GCurPath$ = "D" AND GCY + 1 < 26 AND SCREEN(GCY + 1, GCX, 0) = ASC(CPLAYERMARK$) THEN GCurPath$ = "L" 
      LOOP 
      LC = 0 
      DO 
         LC = LC + 1 
         IF LC > 10 THEN EXIT DO 
         IF GCurPath$ = "L" AND GCX - 1 > 0 AND SCREEN(GCY, GCX - 1, 0) = ASC(COBJECT$) THEN GCurPath$ = "U": CrashPossible = 1 
         IF GCurPath$ = "U" AND GCY - 1 > 2 AND SCREEN(GCY - 1, GCX, 0) = ASC(COBJECT$) THEN GCurPath$ = "R": CrashPossible = 1 
         IF GCurPath$ = "R" AND GCX + 1 < 81 AND SCREEN(GCY, GCX + 1, 0) = ASC(COBJECT$) THEN GCurPath$ = "D": CrashPossible = 1 
         IF GCurPath$ = "D" AND GCY + 1 < 26 AND SCREEN(GCY + 1, GCX, 0) = ASC(COBJECT$) THEN GCurPath$ = "L": CrashPossible = 1 ELSE EXIT DO 
      LOOP 
    END IF 
   ' 4. 물체를 향해 접근 
   IF GDEMOID.X - GCX > 0 AND GCurPath$ <> "L" THEN GCurPath$ = "R"'오른쪽으로 가까움 
   IF GDEMOID.X - GCX < 0 AND GCurPath$ <> "R" THEN GCurPath$ = "L"'왼쪽으로 가까움 
   IF GDEMOID.Y - GCY > 0 AND GCurPath$ <> "U" THEN GCurPath$ = "D"'밑으로 가까움 
   IF GDEMOID.Y - GCY < 0 AND GCurPath$ <> "D" THEN GCurPath$ = "U"'밑으로 가까움 
END SUB 

SUB InitailizeGameScreen 
   ' 메인 화면 
   ' 초기에 나타나는 화면을 뜻함. 
   OUT &H3C6, 15 ' Palette Mask Register 
   OUT &H3C8, 15 ' Setting 
   OUT &H3C9, 63 
   OUT &H3C9, 63 
   OUT &H3C9, 63 
   COLOR 15, 1 
   CLS 
   LOCATE 2, 1: PRINT STRING$(80, 219) 
   FOR C = 2 TO 24 
       PutChar C, 1, 15, 1, CHR$(219) 
       PutChar C, 80, 15, 1, CHR$(219) 
   NEXT C 
   FOR C = 1 TO 80 
       PutChar 25, C, 15, 1, CHR$(219) 
   NEXT C 
END SUB 

FUNCTION ItemCrashCheck 
   ' 다른 충돌의 결정 
   ' 1. 테두리에 충돌 
   ' 2. 물체에 충돌 
   IF CHR$(SCREEN(GCY, GCX, 0)) = CITEMMARK$ THEN 
      PLAY "l64CEG" 
      ItemCrashCheck = 1 
   END IF 
END FUNCTION 

FUNCTION KeyRoutine 
   ' 함수명 : KeyRoutine 
   ' 역할 : 물체의 경로변화를 주로 담당함 
   '        ESC를 눌렀을경우 -1이 리턴 됨. 
   '        그 외의 경우 눌러진 키가 리턴됨 
   K$ = INKEY$ 
   SELECT CASE K$ 
      CASE CHR$(0) + CHR$(72) 
        IF GCurPath$ <> "D" THEN GCurPath$ = "U" 
      CASE CHR$(0) + CHR$(80) 
        IF GCurPath$ <> "U" THEN GCurPath$ = "D" 
      CASE CHR$(0) + CHR$(75) 
        IF GCurPath$ <> "R" THEN GCurPath$ = "L" 
      CASE CHR$(0) + CHR$(77) 
        IF GCurPath$ <> "L" THEN GCurPath$ = "R" 
   END SELECT 
   IF K$ = "" THEN KeyRoutine = 0 ELSE KeyRoutine = ASC(K$) 
END FUNCTION 

SUB MakeItem 
   DO 
     GDEMOID.X = INT(RND * 78) + 2: GDEMOID.Y = INT(RND * 22) + 3 
     IF SCREEN(GDEMOID.Y, GDEMOID.X, 0) <> ASC(CPLAYERMARK$) AND SCREEN(GDEMOID.Y, GDEMOID.X, 0) <> ASC(COBJECT$) THEN 
        T1 = ASC(MID$(GSaveBackGroundBuf$, 160 * (GDEMOID.Y - 1) + (2 * (GDEMOID.X - 1)) + 2, 1)) 
        DEF SEG = &HB800 
        POKE 160 * (GDEMOID.Y - 1) + (2 * (GDEMOID.X - 1)), ASC(CITEMMARK$) 
        POKE 160 * (GDEMOID.Y - 1) + (2 * (GDEMOID.X - 1)) + 1, (T1 AND 240) + 14 
        EXIT DO 
     END IF 
   LOOP 
END SUB 

FUNCTION ObjectMove 
   '함수명 : ObjectMove 
   '역할 : 정해진 경로에 따라 물체를 움직이고 충돌검사까지 하는 부분 
   IsCrash = 0' 충돌 확인 스위치 
   SELECT CASE GCurPath$ 
      CASE "U" 
        GCY = GCY - 1 
        IF GCY = 2 THEN IsCrash = 1: GCY = 3 
      CASE "D" 
        GCY = GCY + 1 
        IF GCY = 25 THEN IsCrash = 1: GCY = 24 
      CASE "L" 
        GCX = GCX - 1 
        IF GCX = 1 THEN IsCrash = 1: GCX = 2 
      CASE "R" 
        GCX = GCX + 1 
        IF GCX = 80 THEN IsCrash = 1: GCX = 79 
   END SELECT 
   IF IsCrash = 0 THEN 
      IF CHR$(SCREEN(GCY, GCX, 0)) = CPLAYERMARK$ OR CHR$(SCREEN(GCY, GCX, 0)) = COBJECT$ THEN IsCrash = 1 ELSE Queue.Push GCX, GCY 
   END IF 
   ObjectMove = IsCrash 
END FUNCTION 

SUB ObjectView 
   '오브젝트 찍음 
   PutChar GCY, GCX, 10 + (GCC MOD 4), 1, CPLAYERMARK$ 
   IF GPC = GLength THEN 
      Queue.Pop CX, CY 
      RecoverChar CY, CX 
   END IF 
END SUB 

SUB PlayPaletteChange 
   SELECT CASE GCC MOD 4 
      CASE 0 
        L01 = 10: L02 = 10: L03 = 0 
        L11 = 20: L12 = 20: L13 = 0 
        L21 = 40: L22 = 40: L23 = 0 
        L31 = 60: L32 = 60: L33 = 0 
      CASE 1 
        L01 = 60: L02 = 60: L03 = 0 
        L11 = 10: L12 = 10: L13 = 0 
        L21 = 20: L22 = 20: L23 = 0 
        L31 = 40: L32 = 40: L33 = 0 
      CASE 2 
        L01 = 40: L02 = 40: L03 = 0 
        L11 = 60: L12 = 60: L13 = 0 
        L21 = 10: L22 = 10: L23 = 0 
        L31 = 20: L32 = 20: L33 = 0 
      CASE 3 
        L01 = 20: L02 = 20: L03 = 0 
        L11 = 40: L12 = 40: L13 = 0 
        L21 = 60: L22 = 60: L23 = 0 
        L31 = 10: L32 = 10: L33 = 0 
   END SELECT 
   ' Palette setting 
   OUT &H3C6, 15      ' Palette Mask Register Setting 
   OUT &H3C8, 10 
   OUT &H3C9, L01 
   OUT &H3C9, L02 
   OUT &H3C9, L03 
   OUT &H3C8, 11 
   OUT &H3C9, L11 
   OUT &H3C9, L12 
   OUT &H3C9, L13 
   OUT &H3C8, 12 
   OUT &H3C9, L21 
   OUT &H3C9, L22 
   OUT &H3C9, L23 
   OUT &H3C8, 13 
   OUT &H3C9, L31 
   OUT &H3C9, L32 
   OUT &H3C9, L33 
END SUB 

SUB PutChar (Y, X, C1, C2, D$) 
   DEF SEG = &HB800 
   POKE 160 * (Y - 1) + (2 * (X - 1)), ASC(D$) 
   POKE 160 * (Y - 1) + (2 * (X - 1)) + 1, C2 * 16 + C1 
END SUB 

SUB Queue.GetDirect (position, gx, gy) 
   position = position MOD QUEUESIZE 
   '큐크기보다 작은 위치로 구함. 
   gx = GQueue(position, 1) 
   gy = GQueue(position, 2) 
END SUB 

SUB Queue.Pop (gx, gy) STATIC 
   GQHEAD = GQHEAD + 1 
   IF GQHEAD > CQUEUESIZE THEN GQHEAD = 1 
   gx = GQueue(GQHEAD, 1) 
   gy = GQueue(GQHEAD, 2) 
END SUB 

SUB Queue.Push (px, py) 
   GQTAIL = GQTAIL + 1 
   IF GQTAIL > CQUEUESIZE THEN GQTAIL = 1 
   GQueue(GQTAIL, 1) = px 
   GQueue(GQTAIL, 2) = py 
END SUB 

SUB RecoverChar (Y, X) 
   T1 = ASC(MID$(GSaveBackGroundBuf$, 160 * (Y - 1) + (2 * (X - 1)) + 1, 1)) 
   T2 = ASC(MID$(GSaveBackGroundBuf$, 160 * (Y - 1) + (2 * (X - 1)) + 2, 1)) 
   POKE 160 * (Y - 1) + (2 * (X - 1)), T1 
   POKE 160 * (Y - 1) + (2 * (X - 1)) + 1, T2 
END SUB 

SUB SaveBackGround (Dest$) 
   DEF SEG = &HB800 
   Dest$ = "" 
   FOR I = 0 TO 160 * 25 
       Dest$ = Dest$ + CHR$(PEEK(I)) 
   NEXT I 
END SUB 

FUNCTION StageEvent (Stage) 
   StageEvent = 0 
   SELECT CASE Stage 
      CASE 4 
        COLOR 6 
        LOCATE 4, 10: PRINT STRING$(61, COBJECT$) 
        LOCATE 21, 10: PRINT STRING$(61, COBJECT$) 
        IF CStageUValue1 <= 4 THEN CStageUValue1 = 20 
        IF CStageUValue2 <= 4 THEN CStageUValue2 = 20 
        IF CStageUValue3 <= 4 THEN CStageUValue3 = 20 
        IF SCREEN(CStageUValue1, 10, 0) <> ASC(CPLAYERMARK$) THEN RecoverChar INT(CStageUValue1), 10 ELSE StageEvent = -1 
        IF SCREEN(CStageUValue2, 40, 0) <> ASC(CPLAYERMARK$) THEN RecoverChar INT(CStageUValue2), 40 ELSE StageEvent = -1 
        IF SCREEN(CStageUValue3, 70, 0) <> ASC(CPLAYERMARK$) THEN RecoverChar INT(CStageUValue3), 70 ELSE StageEvent = -1 
        CStageUValue1 = CStageUValue1 - .4 
        CStageUValue2 = CStageUValue2 - .4 
        CStageUValue3 = CStageUValue3 - .4 
        IF CStageUValue1 <= 4 THEN CStageUValue1 = 20 
        IF CStageUValue2 <= 4 THEN CStageUValue2 = 20 
        IF CStageUValue3 <= 4 THEN CStageUValue3 = 20 
        IF SCREEN(CStageUValue1, 10, 0) <> ASC(CPLAYERMARK$) THEN PutChar INT(CStageUValue1), 10, 15, 1, COBJECT$ 
        IF SCREEN(CStageUValue2, 40, 0) <> ASC(CPLAYERMARK$) THEN PutChar INT(CStageUValue2), 40, 15, 1, COBJECT$ 
        IF SCREEN(CStageUValue3, 70, 0) <> ASC(CPLAYERMARK$) THEN PutChar INT(CStageUValue3), 70, 15, 1, COBJECT$ 
   END SELECT 
END FUNCTION 

FUNCTION Title$ 
   CLS 
   LOCATE 5, 10: PRINT "Super NIBBLES --------------------------------------------" 
   LOCATE 6, 10: PRINT "Made by Lee Kang-yong 1998.11.15" 
   LOCATE 7, 10: PRINT "1 - Game start one player." 
   LOCATE 8, 10: PRINT "D - Game demo." 
   LOCATE 9, 10: PRINT "Esc - End." 
   DO 
      K$ = INPUT$(1) 
      IF K$ = "1" OR UCASE$(K$) = "D" OR K$ = CHR$(27) THEN Title$ = K$: EXIT DO 
   LOOP 
END FUNCTION 

SUB ViewBackGround (Round) 
   SELECT CASE Round 
      CASE 1, 2, 3 
        FOR I = 3 TO 24 
            FOR J = 2 TO 79 
                PutChar I, J, 7, 0, " " 
        NEXT J, I 
        FOR C = 1 TO 20 
            X = INT(RND * 78) + 2: Y = INT(RND * 22) + 3 
            PutChar Y, X, 10, 0, "." 
        NEXT C 
        FOR C = 1 TO 20 
            X = INT(RND * 78) + 2: Y = INT(RND * 22) + 3 
            PutChar Y, X, 11, 0, "." 
        NEXT C 
        FOR C = 1 TO 20 
            X = INT(RND * 78) + 2: Y = INT(RND * 22) + 3 
            PutChar Y, X, 12, 0, "." 
        NEXT C 
        FOR C = 1 TO 20 
            X = INT(RND * 78) + 2: Y = INT(RND * 22) + 3 
            PutChar Y, X, 13, 0, "." 
        NEXT C 
     END SELECT 
END SUB 

SUB ViewStatus 
   COLOR 15: LOCATE 1, 40: PRINT USING " Stage: ###"; GStage 
   LOCATE 1, 2: PRINT USING " Score : ###,###"; GScore(1) 
   LOCATE 1, 22: PRINT USING " Items : ###"; GItems 
   LOCATE 1, 60: PRINT "Lifes:"; STRING$(GLifes, 3) 
END SUB 

SUB WaitBox (S$) 
   COLOR 15 
   LOCATE 11, 28: PRINT "栢栢栢栢栢栢栢栢栢栢栢栢" 
   LOCATE 12, 28: PRINT "?                      ?" 
   LOCATE 13, 28: PRINT "栢栢栢栢栢栢栢栢栢栢栢栢" 
   COLOR 14 
   LOCATE 12, 30: PRINT S$ 
   I$ = INPUT$(1) 
   'Recover 
   FOR I = 11 TO 13 
       FOR J = 28 TO 51 
           DEF SEG = &HB800 
           RecoverChar I, J 
   NEXT J, I 
END SUB 

