DECLARE SUB EditModuleKeyControl () 
'기본 함수 
DECLARE SUB hxyprint (X%, Y%, c1%, c2%, s$)      '한글 내장 출력 함수 
DECLARE SUB XYPRINT (X%, Y%, s$)                 '한글 내장 출력 함수 

'커서 이동상의 함수 
DECLARE SUB Colortablecursor (tnum, Num) 
DECLARE SUB EditCursor (X, Y, l) 

'화면 구조상의 함수 
DECLARE SUB MainScreen () 

'키의 입력 컨트롤 담당 
DECLARE SUB EditModuleKeyControl () 

'기타 이용상의 함수 
DECLARE SUB Colortable (c1, c2) '칼라를 출력한다. 
DECLARE SUB linebox (X, Y, ex, ey, g, g2) 
DECLARE SUB Viewpalettedata () 
DECLARE SUB MiniViewputpixel (X, Y, c) 
DECLARE FUNCTION Textx (X) 
DECLARE FUNCTION Texty (Y) 
DECLARE FUNCTION MenuSelect (rec) 

'화일 로딩상의 함수 
DECLARE FUNCTION ExtPALfileload (Filename$) 
DECLARE FUNCTION ExtICOfileload (Filename$) 

'도움 
DECLARE SUB EditModuleHelp () 

'$INCLUDE: 'INT.BI' 
'$INCLUDE: 'SDAM.BI' 
                    
DIM SHARED UseFilename$ ' <-- 파일의 이름 
DIM SHARED HyunCommand$ ' <-- 현재상태 
DIM SHARED pixellarge   ' <-- 찍는 점의 크기 
DIM SHARED pal(15, 3)   ' <-- 현재 팔렛 RGB             
DIM SHARED hx, hy       ' <-- 현재 위치 
DIM SHARED Color1, Color2 
DIM SHARED Icondata(32, 32) 
'커서 디자인 
DIM SHARED Cursor(1 TO 20)  ' <-- 제작용 커서 1 
DIM SHARED Cursor2(1 TO 40) ' <-- 제작용 커서 2 
'메뉴 
DIM SHARED Menu$(20), Help$(20) 
FOR i = 1 TO 18 
   READ Menu$(i), Help$(i) 
NEXT i 
DATA "찍       기","찍는 작업을 한다." 
DATA "지   우  기","지우기 작업을 한다." 
DATA "선 그 리 기","지금은 사용불가능한 기능입니다." 
DATA "원 그 리 기","지금은 사용불가능한 기능입니다." 
DATA "새 로 하 기","새롭게 한다." 
DATA "ICO저장하기","ICO파일로 저장한다." 
DATA "ICO불러오기","작업창의 불러내기는 ICO파일을 지원한다." 
DATA "팔레트 편집","RGB 팔레트를 편집한다." 
DATA "회       전","Rotate기능을 한다." 
DATA "상하 바꾸기","상하를 뒤집어 놓는다." 
DATA "좌우 바꾸기","좌우를 뒤집어 놓는다." 
DATA "아 이 콘 창","아이콘창으로 이동한다." 
DATA "종       료","작업 종료" 
DATA "-----------","........." 
DATA "-----------","........." 
DATA "-----------","........." 
DATA "-----------","........." 
DATA "-----------","........." 
CLS 
'초기화 
HyunCommand$ = "찍기"       ' 기본 사용 
pixellarge = 1              ' 기본 점   크기 
UseFilename$ = "NONAME.ICB" ' 기본 파일 이름 
hx = 1: hy = 1: Color1 = 15: Color2 = 15 
COLOR 15, 1 
PRINT "          Icon Editor Version III   Made by dragonhi(Lee kang-yong)             " 
COLOR 7, 0 
PRINT "Default File load .............. "; 
IF ExtPALfileload("DEFAULT.PAL") THEN COLOR 15: PRINT "Succeed!" ELSE COLOR 15: PRINT "Fail!": BEEP: COLOR 7, 0: END 
i$ = INPUT$(1) 
'커서 저장 
SCREEN 12 
 LINE (1, 1)-(7, 7), 1, BF 
 LINE (2, 2)-(6, 6), 9, BF 
 LINE (3, 3)-(5, 5), 15, BF 
 GET (1, 1)-(7, 7), Cursor 
 LINE (1, 1)-(640, 480), 0, BF 
 CIRCLE (5, 7), 4, 8 
 CIRCLE (5, 7), 3, 7 
 PAINT (5, 7), 15, 7 
 LINE (5, 0)-(5, 13), 14 
 GET (1, 0)-(8, 13), Cursor2 
 CLS 
'Main Module 
MainScreen                  ' 메인 화면을 부른다. 
EditModuleKeyControl        ' 편집 창의 키를 움직이게 하고 키의 명령을 수행하게 한다. 
i$ = INPUT$(1) 
SCREEN 0 

SUB Colortable (c1, c2) 
   '현재 색깔을 출력하는 함수 
   '베이직이 저속이라서 고속으로 찍게 할라고 이렇게 했음 
   DEF SEG = &HA000 
   OUT &H3CE, 5 
   OUT &H3CF, 0 
   o1 = c1: o2 = c2   'c1과 c2는 전역변수로 설정된 Color1와 Color2라는 변수가 
                      '대입 되어 있으므로 건드렸을경우 Color1와 Color2가 해를 미치게 된다. 
                      '한마디로 c1와 c2에는 Color1와 Color2변수의 번지가 들어가 있을것으로 
                      '생각한다. 
   LINE (Textx(25), Texty(23) + 4)-(Textx(29), Texty(25) + 4), 0, BF 
   linebox Textx(25) - 1, Texty(23) + 4 - 1, Textx(29) + 1, Texty(25) + 4 + 1, 0, 0 
   LINE (Textx(25), Texty(23) + 4)-(Textx(29), Texty(25) + 4), 15, B 
   FOR i = 1 TO 32 
      IF i MOD 2 = 0 THEN pr1 = 170: pr2 = 85 ELSE pr1 = 85: pr2 = 170 
      c1 = o1: c2 = o2 
      FOR J = 3 TO 0 STEP -1 
         OUT &H3C4, 2 
         OUT &H3C5, (2 ^ J) 
         p1 = 0: p2 = 0 
         IF c1 / (2 ^ J) >= 1 THEN p1 = pr1: c1 = c1 - (2 ^ J) 
         IF c2 / (2 ^ J) >= 1 THEN p2 = pr2: c2 = c2 - (2 ^ J) 
         pp = p1 OR p2 
         IF pp >= 1 THEN POKE (80 * (Texty(23) + 4)) + 25 + (80 * (i - 1)), pp 
         IF pp >= 1 THEN POKE (80 * (Texty(23) + 4)) + 26 + (80 * (i - 1)), pp 
         IF pp >= 1 THEN POKE (80 * (Texty(23) + 4)) + 27 + (80 * (i - 1)), pp 
         IF pp >= 1 THEN POKE (80 * (Texty(23) + 4)) + 28 + (80 * (i - 1)), pp 
   NEXT J, i 
   OUT &H3C5, 15 
   c1 = o1: c2 = o2  '원상 복귀 

END SUB 
                      

SUB Colortablecursor (tnum, Num) 
   IF tnum = 1 THEN PUT (16 + (10 * (Num - 1)), Texty(23) + 3), Cursor2 
   IF tnum = 2 THEN PUT (16 + (10 * (Num - 1)), Texty(24) + 7), Cursor2 
END SUB 

SUB EditCursor (X, Y, l) 
   FOR i = 1 - 1 TO l - 1 
     FOR J = 1 - 1 TO l - 1 
       PUT (296 + (8 * (X - 1 + J)), 71 + (8 * (Y - 1 + i))), Cursor 
   NEXT J, i 
END SUB 

SUB EditModuleHelp 
   hxyprint 21, 37, 15, 1, "             작   업   창              " 
   hxyprint 22, 37, 0, 7, " <+>,<-> - 찍는점크기 조절             " 
   hxyprint 23, 37, 0, 7, " Shift + <- or -> - 색깔 조절          " 
   hxyprint 24, 37, 0, 7, " Ctrl  + <- or -> - 색깔1조절          " 
   hxyprint 25, 37, 0, 7, " Shift + Ctrl + <- or -> - 색깔2조절   " 
   hxyprint 26, 37, 0, 7, " Space,Enter - 찍기지우기  F10 - 메뉴  " 
   hxyprint 27, 37, 0, 7, " Esc - 작업종료      Z , z - 랜덤찍기  " 
   linebox Textx(37), Texty(22), Textx(76) - 1, Texty(28), 0, 0 
END SUB 

SUB EditModuleKeyControl 
   large = pixellarge 
   'Alt키가 먹게 할려면 스캔 코드를 불러 오는 방법을 써야 한다. 
   hxyprint 5, 72, 15, 0, LTRIM$(STR$(hx)) 
   hxyprint 5, 77, 15, 0, LTRIM$(STR$(hy)) 
   DO 
      DEF SEG = &H40          ' 토글키 알기     
      KeyStatus = PEEK(&H17)  ' 토글키 알기     
      k$ = INKEY$ 
      IF k$ <> "" THEN '키가 입력 되었을 경우 
         '토글키 상황 알기 
         IF KeyStatus AND 2 THEN k$ = "" + k$ 
         IF KeyStatus AND 4 THEN k$ = "" + k$ 
         IF KeyStatus AND 8 THEN k$ = "" + k$ 
      END IF 
      SELECT CASE k$ 
         CASE "" 
         CASE CHR$(27) 
            SCREEN 0 
            END 
         CASE "" + CHR$(0) + CHR$(75), "4" 
            Colortablecursor 1, Color1 
            Colortablecursor 2, Color2 
            Color1 = Color1 - 1 
            IF Color1 = -1 THEN Color1 = 15 
            Color2 = Color1 
            Colortablecursor 1, Color1 
            Colortablecursor 2, Color2 
            Colortable Color1, Color2 
         CASE "" + CHR$(0) + CHR$(77), "6" 
            Colortablecursor 1, Color1 
            Colortablecursor 2, Color2 
            Color1 = Color1 + 1 
            IF Color1 = 16 THEN Color1 = 0 
            Color2 = Color1 
            Colortablecursor 1, Color1 
            Colortablecursor 2, Color2 
            Colortable Color1, Color2 
         CASE "" + CHR$(0) + "s" 
            Colortablecursor 1, Color1 
            Color1 = Color1 - 1 
            IF Color1 = -1 THEN Color1 = 15 
            Colortablecursor 1, Color1 
            Colortable Color1, Color2 
         CASE "" + CHR$(0) + "t" 
            Colortablecursor 1, Color1 
            Color1 = Color1 + 1 
            IF Color1 = 16 THEN Color1 = 0 
            Colortablecursor 1, Color1 
            Colortable Color1, Color2 
         CASE "" + CHR$(0) + "s", "" + CHR$(0) + "s" 
            Colortablecursor 2, Color2 
            Color2 = Color2 - 1 
            IF Color2 = -1 THEN Color2 = 15 
            Colortablecursor 2, Color2 
            Colortable Color1, Color2 
         CASE "" + CHR$(0) + "t", "" + CHR$(0) + "t" 
            Colortablecursor 2, Color2 
            Color2 = Color2 + 1 
            IF Color2 = 16 THEN Color2 = 0 
            Colortablecursor 2, Color2 
            Colortable Color1, Color2 
         CASE "+" 
            EditCursor hy, hx, large 
            pixellarge = pixellarge + 1 
            IF hx + pixellarge - 1 > 32 THEN pixellarge = pixellarge - 1: BEEP 
            IF hy + pixellarge - 1 > 32 THEN pixellarge = pixellarge - 1: BEEP 
            IF pixellarge > 10 THEN pixellarge = 10: BEEP 
            large = pixellarge 
            EditCursor hy, hx, large 
            hxyprint 21, 2, 0, 7, " 찍는 점 크기       :     " 
            hxyprint 21, 2, 0, 7, " 찍는 점 크기       :  " + LTRIM$(STR$(pixellarge)) 
         CASE "-" 
            EditCursor hy, hx, large 
            pixellarge = pixellarge - 1 
            IF pixellarge <= 0 THEN pixellarge = 1: BEEP 
            large = pixellarge 
            EditCursor hy, hx, large 
            hxyprint 21, 2, 0, 7, " 찍는 점 크기       :     " 
            hxyprint 21, 2, 0, 7, " 찍는 점 크기       :  " + LTRIM$(STR$(pixellarge)) 
         CASE CHR$(0) + CHR$(72) 
            EditCursor hy, hx, large 
            hx = hx - 1 
            IF hx = 0 THEN hx = 33 - pixellarge 
            hxyprint 5, 72, 15, 0, "  " 
            hxyprint 5, 72, 15, 0, LTRIM$(STR$(hx)) 
            hxyprint 5, 77, 15, 0, "  " 
            hxyprint 5, 77, 15, 0, LTRIM$(STR$(hy)) 
            EditCursor hy, hx, large 
         CASE CHR$(0) + CHR$(80) 
            EditCursor hy, hx, large 
            hx = hx + 1 
            IF hx = 34 - large THEN hx = 1 
            hxyprint 5, 72, 15, 0, "  " 
            hxyprint 5, 72, 15, 0, LTRIM$(STR$(hx)) 
            hxyprint 5, 77, 15, 0, "  " 
            hxyprint 5, 77, 15, 0, LTRIM$(STR$(hy)) 
            EditCursor hy, hx, large 
         CASE CHR$(0) + CHR$(75) 
            EditCursor hy, hx, large 
            hy = hy - 1 
            IF hy = 0 THEN hy = 33 - large 
            hxyprint 5, 72, 15, 0, "  " 
            hxyprint 5, 72, 15, 0, LTRIM$(STR$(hx)) 
            hxyprint 5, 77, 15, 0, "  " 
            hxyprint 5, 77, 15, 0, LTRIM$(STR$(hy)) 
            EditCursor hy, hx, large 
         CASE CHR$(0) + CHR$(77) 
            EditCursor hy, hx, large 
            hy = hy + 1 
            IF hy = 34 - large THEN hy = 1 
            hxyprint 5, 72, 15, 0, "  " 
            hxyprint 5, 72, 15, 0, LTRIM$(STR$(hx)) 
            hxyprint 5, 77, 15, 0, "  " 
            hxyprint 5, 77, 15, 0, LTRIM$(STR$(hy)) 
            EditCursor hy, hx, large 
         CASE CHR$(13), " " 
            EditCursor hy, hx, large 
            SELECT CASE HyunCommand$ 
               CASE "찍기" 
                    Cswitch = hx - (2 * INT(hx / 2)) 
                    IF Cswitch = 0 THEN Cswitch = 1 ELSE Cswitch = 0 
                    IF hy - (2 * INT(hy / 2)) >= 1 THEN 
                       IF Cswitch = 0 THEN Cswitch = 1 ELSE Cswitch = 0 
                    END IF 
                    FOR i = hx TO hx + large - 1 
                        IF large MOD 2 = 0 THEN 
                           '점의 크기가 짝수일땐 이를 적용 
                           IF Cswitch = 0 THEN Cswitch = 1 ELSE Cswitch = 0 
                        END IF 
                        FOR J = hy TO hy + large - 1 
                            IF Cswitch = 0 THEN Cswitch = 1 ELSE Cswitch = 0 
                            IF Cswitch = 1 THEN 
                               LINE (296 + (8 * (X - 1 + J)), 71 + (8 * (Y - 1 + i)))-(296 + (8 * (X - 1 + J)) + 6, 71 + (8 * (Y - 1 + i)) + 6), Color1, BF 
                               MiniViewputpixel J, i, Color1 
                            END IF 
                            IF Cswitch = 0 THEN 
                               LINE (296 + (8 * (X - 1 + J)), 71 + (8 * (Y - 1 + i)))-(296 + (8 * (X - 1 + J)) + 6, 71 + (8 * (Y - 1 + i)) + 6), Color2, BF 
                               MiniViewputpixel J, i, Color2 
                            END IF 
                    NEXT J, i 
               CASE "지우기" 
                    FOR i = hx TO hx + large - 1 
                        FOR J = hy TO hy + large - 1 
                            LINE (296 + (8 * (X - 1 + J)), 71 + (8 * (Y - 1 + i)))-(296 + (8 * (X - 1 + J)) + 6, 71 + (8 * (Y - 1 + i)) + 6), 0, BF 
                            MiniViewputpixel J, i, 0 
                    NEXT J, i 
            END SELECT 
            EditCursor hy, hx, pixellarge 
         CASE CHR$(0) + CHR$(68) 
            Num = MenuSelect(1)  'MenuSelect(1) <-- 작업창에서의 메뉴 
            EditCursor hy, hx, pixellarge 
            IF Num = 1 THEN HyunCommand$ = "찍기" 
            IF Num = 2 THEN HyunCommand$ = "지우기" 
            IF Num = 5 THEN 
               R = ExtPALfileload("DEFAULT.PAL") 
               Viewpalettedata 
               LINE (Textx(37), Texty(1))-(Textx(41) - 1, Texty(3) - 1), 0, BF 
               FOR i = 1 TO 32 
                   FOR J = 1 TO 32 
                        Icondata(J, i) = 0 
                        LINE (295 + (8 * (J - 1)), 70 + (8 * (i - 1)))-(295 + (8 * J), 70 + (8 * i)), 7, B 
                        LINE (295 + (8 * (J - 1) + 1), 70 + (8 * (i - 1)) + 1)-(295 + (8 * J) - 1, 70 + (8 * i) - 1), 0, BF 
               NEXT J, i 
            END IF 
            IF Num = 7 THEN 
               R = ExtICOfileload("M0171I.ICO") 
            END IF 
            hxyprint 26, 2, 0, 7, " 현재상태 :               " 
            hxyprint 26, 2, 0, 7, " 현재상태 :  [" + HyunCommand$ + "]" 
            EditModuleHelp 
            EditCursor hy, hx, pixellarge 
      END SELECT 
   LOOP 
END SUB 

FUNCTION ExtICOfileload (Filename$) 
   OPEN Filename$ FOR RANDOM AS #1 LEN = 1 
      FIELD #1, 1 AS Char$ 
      'PALETTE화일이 아닐 경우 실패 
         IF LOF(1) = 0 THEN CLOSE : KILL Filename$: ExtICOfileload = 0: EXIT FUNCTION 
         IF LOF(1) <> 766 THEN CLOSE : ExtICOfileload = 0: EXIT FUNCTION 
      '------- 
      Record = 126: Y = 1 
      Jin16$ = "0123456789ABCDEF" 
      DO UNTIL Record > 127 + 512 
         Record = Record + 1 
         GET #1, Record 
         HexC$ = HEX$(ASC(Char$)) 
         IF LEN(HexC$) = 1 THEN HexC$ = "0" + HexC$ 
         Icondata(Y, 32 - X) = INSTR(1, Jin16$, MID$(HexC$, 1, 1)) - 1 
         Y = Y + 1 
         Icondata(Y, 32 - X) = INSTR(1, Jin16$, MID$(HexC$, 2, 1)) - 1 
         Y = Y + 1 
         IF Y >= 33 THEN Y = 1: X = X + 1 
      LOOP 
      FOR i = 63 TO 126 STEP 4 '팔렛트 로드 
         GET #1, i 
         pal(c, 1) = INT(ASC(Char$) / 4) 
         GET #1, i + 1 
         pal(c, 2) = INT(ASC(Char$) / 4) 
         GET #1, i + 2 
         pal(c, 3) = INT(ASC(Char$) / 4) 
         OUT &H3C8, c 
         OUT &H3C9, pal(c, 1) 
         OUT &H3C9, pal(c, 2) 
         OUT &H3C9, pal(c, 3) 
         c = c + 1 
      NEXT i 
   CLOSE 
   Viewpalettedata 
   FOR i = 1 TO 32     '찍어내기 
      FOR J = 1 TO 32 
         LINE (295 + (8 * (J - 1) + 1), 70 + (8 * (i - 1)) + 1)-(295 + (8 * J) - 1, 70 + (8 * i) - 1), Icondata(J, i), BF 
         MiniViewputpixel J, i, Icondata(J, i) 
   NEXT J, i 
   ExtICOfileload = 1 '성공 
END FUNCTION 

FUNCTION ExtPALfileload (Filename$) 
   OPEN Filename$ FOR RANDOM AS #1 LEN = 1 
      FIELD #1, 1 AS Char$ 
      'PALETTE화일이 아닐 경우 실패 
         IF LOF(1) = 0 THEN CLOSE : KILL Filename$: ExtPALfileload = 0: EXIT FUNCTION 
         IF LOF(1) <> 48 THEN CLOSE : ExtPALfileload = 0: EXIT FUNCTION 
      '------- 
      col = 0: Trec = 0 
      DO UNTIL col >= 16 
          Trec = Trec + 1: GET #1, Trec: pal(col, 1) = ASC(Char$) 
          Trec = Trec + 1: GET #1, Trec: pal(col, 2) = ASC(Char$) 
          Trec = Trec + 1: GET #1, Trec: pal(col, 3) = ASC(Char$) 
          '팔렛트 변화 
          OUT &H3C8, col 
          OUT &H3C9, pal(col, 1) 
          OUT &H3C9, pal(col, 2) 
          OUT &H3C9, pal(col, 3) 
          col = col + 1 
      LOOP 
   CLOSE 
   ExtPALfileload = 1 '성공 
END FUNCTION 

SUB hxyprint (X%, Y%, c1%, c2%, s$) 
   HCOLOR c1%, c2% 
   XYPRINT X%, Y%, s$ 
END SUB 

SUB linebox (X, Y, ex, ey, g, g2) 
  IF g = 1 THEN LINE (X + 1 + 10, Y + 1 + 10)-(ex - 1 + 10, ey - 1 + 10), 8, BF 
  LINE (X, Y)-(ex - 1, Y), 8 
  LINE (X, Y)-(X, ey - 1), 8 
  LINE (ex, Y + 1)-(ex, ey), 15 
  LINE (X + 1, ey)-(ex, ey), 15 
  IF g2 = 1 THEN LINE (X + 1, Y + 1)-(ex - 1, ey - 1), 7, BF 
END SUB 

SUB MainScreen 
     SCREEN 12 
     HSCREEN 1 
     HFONT 1, 1 
     hxyprint 0, 0, 15, 1, "           아이콘창             " 
     linebox 0, Texty(1), Textx(32) - 1, Texty(11), 1, 1 
     LINE (Textx(1), Texty(2))-(Textx(31), Texty(10)), 0, BF 
     linebox Textx(1) - 1, Texty(2) - 1, Textx(31) + 1, Texty(10) + 1, 0, 0 
     hxyprint 12, 0, 15, 1, "           정 보 창             " 
     linebox 0, Texty(13), Textx(32) - 1, Texty(18), 1, 1 
     hxyprint 14, 2, 0, 7, " 편집 파일 : " + UseFilename$ 
     hxyprint 15, 2, 0, 7, " 현재편집아이콘번호 :#### " 
     hxyprint 16, 2, 0, 7, " 총 아이콘 갯수     :#### " 
     hxyprint 19, 0, 15, 1, "           상 태 창             " 
     linebox 0, Texty(20), Textx(32) - 1, Texty(28), 1, 1 
     hxyprint 21, 2, 0, 7, " 찍는 점 크기       :  " + LTRIM$(STR$(pixellarge)) 
     hxyprint 22, 2, 0, 7, " 색깔                     " 
     FOR i = 0 TO 15 
       LINE (15 + (10 * (i - 1)), Texty(23) + 5)-(15 + (10 * i), Texty(23) + 15), 15, B 
       LINE (15 + (10 * (i - 1)) + 1, Texty(23) + 5 + 1)-(15 + (10 * i), Texty(23) + 15 - 1), i, BF 
       LINE (15 + (10 * (i - 1)), Texty(24) + 9)-(15 + (10 * i), Texty(24) + 19), 15, B 
       LINE (15 + (10 * (i - 1)) + 1, Texty(24) + 9 + 1)-(15 + (10 * i), Texty(24) + 19 - 1), i, BF 
     NEXT i 
     hxyprint 26, 2, 0, 7, " 현재상태 :  [" + HyunCommand$ + "]" 
     LINE (Textx(37) - 1, Texty(1) - 1)-(Textx(41), Texty(3)), 15, B 
     linebox Textx(37) - 2, Texty(1) - 2, Textx(41), Texty(3), 0, 0 
     FOR i = 1 TO 32 
         FOR J = 1 TO 32 
            LINE (295 + (8 * (J - 1)), 70 + (8 * (i - 1)))-(295 + (8 * J), 70 + (8 * i)), 7, B 
     NEXT J, i 
     hxyprint 0, 43, 15, 1, " RGB 팔렛트창                      " 
     hxyprint 0, 56, 15, 1, "(" + UseFilename$ + ":1)" 
     linebox Textx(43) - 1, Texty(1) - 1, Textx(78) + 1, Texty(4) + 1, 0, 1 
     hxyprint 1, 44, 4, 7, "R" 
     hxyprint 2, 44, 2, 7, "G" 
     hxyprint 3, 44, 1, 7, "B" 
     Colortablecursor 1, Color1 
     Colortablecursor 2, Color2 
     Colortable Color1, Color2 
     EditCursor hy, hx, pixellarge 
     Viewpalettedata 
     hxyprint 5, 70, 15, 0, "X:   Y:  " 
     EditModuleHelp 
END SUB 




                    

FUNCTION MenuSelect (rec) 
   SELECT CASE rec 
      CASE 1 
           hxyprint 21, 37, 15, 1, "             메        뉴              " 
           hxyprint 22, 37, 0, 7, "                                       " 
           hxyprint 23, 37, 0, 7, "                                       " 
           hxyprint 24, 37, 0, 7, "                                       " 
           hxyprint 25, 37, 0, 7, "                                       " 
           hxyprint 26, 37, 0, 7, "                                       " 
           hxyprint 27, 37, 0, 7, "                                       " 
           X% = 22 
           FOR i = 1 TO 18 STEP 3 
              hxyprint X%, 38, 0, 7, Menu$(i) 
              hxyprint X%, 51, 0, 7, Menu$(i + 1) 
              hxyprint X%, 64, 0, 7, Menu$(i + 2) 
              X% = X% + 1 
           NEXT i 
           menurec% = 0 
           hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 14, 7, Menu$(menurec% + 1) 
           DO 
              k$ = INKEY$ 
              SELECT CASE k$ 
                  CASE CHR$(0) + CHR$(75) 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 0, 7, Menu$(menurec% + 1) 
                       menurec% = menurec% - 1 
                       IF menurec% = -1 THEN menurec% = 0 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 14, 7, Menu$(menurec% + 1) 
                  CASE CHR$(0) + CHR$(77) 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 0, 7, Menu$(menurec% + 1) 
                       menurec% = menurec% + 1 
                       IF menurec% = 18 THEN menurec% = 17 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 14, 7, Menu$(menurec% + 1) 
                  CASE CHR$(0) + CHR$(72) 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 0, 7, Menu$(menurec% + 1) 
                       menurec% = menurec% - 3 
                       IF menurec% < 0 THEN menurec% = menurec% + 3 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 14, 7, Menu$(menurec% + 1) 
                  CASE CHR$(0) + CHR$(80) 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 0, 7, Menu$(menurec% + 1) 
                       menurec% = menurec% + 3 
                       IF menurec% > 17 THEN menurec% = menurec% - 3 
                       hxyprint 22 + INT(menurec% / 3), 38 + (13 * (menurec% - 3 * INT(menurec% / 3))), 14, 7, Menu$(menurec% + 1) 
                  CASE CHR$(13) 
                       MenuSelect = menurec% + 1 
                       EXIT FUNCTION 
              END SELECT 
           LOOP 
   END SELECT 
END FUNCTION 

SUB MiniViewputpixel (X, Y, c) 
  PSET (Textx(37) + X - 1, Texty(1) + Y - 1), c 
  Icondata(X, Y) = c 
END SUB 

FUNCTION Textx (X) 
 Textx = X * 8 
END FUNCTION 

FUNCTION Texty (Y) 
  Texty = 16 * Y 
END FUNCTION 

SUB Viewpalettedata 
FOR i = 0 TO 15 
  IF i = 0 THEN c% = 7 ELSE c% = i 
  hxyprint 1, 46 + (2 * i), 0, c%, "  " 
  hxyprint 2, 46 + (2 * i), 0, c%, "  " 
  hxyprint 3, 46 + (2 * i), 0, c%, "  " 
  hxyprint 1, 46 + (2 * i), 0, c%, LTRIM$(STR$(pal(i, 1))) 
  hxyprint 2, 46 + (2 * i), 0, c%, LTRIM$(STR$(pal(i, 2))) 
  hxyprint 3, 46 + (2 * i), 0, c%, LTRIM$(STR$(pal(i, 3))) 
NEXT i 
END SUB 

SUB XYPRINT (X%, Y%, s$) 
   HLOCATE X%, Y% 
   HPRINT s$ 
END SUB 

