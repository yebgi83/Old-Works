'안냐세요 이강용입니다. 
'샘틀지기님 덕분에 중고모로 다시 돌아올수 있게 되었습니다. 
'이건 BDIR(Basic DIR)이라고요 미니 도스쉘입니다. 
'아직 미완성입니다. 
'이거 보시고 많은 도움 되시길 

TYPE FileInfo 
    File AS STRING * 12 
    Attrib AS INTEGER 
    Size AS LONG 
END TYPE 
DECLARE FUNCTION FloopyDriveCheck (NumDrv)  '플로피 드라이브 체크 
DECLARE FUNCTION HIMEMCheck () 
DECLARE FUNCTION BooleanMsg$ (N, True$, False$) 
DECLARE FUNCTION MouseCheck () 
DECLARE FUNCTION File.FindFirst (WildCard$, Attrib, BUF AS FileInfo) 
DECLARE FUNCTION File.FindNext (BUF AS FileInfo) 

'Mouse 함수 
DECLARE SUB Mouse () 

'Example 함수 
DECLARE SUB Control () 
DECLARE SUB FileView (Page) 
DECLARE SUB LoadFiles () 
DECLARE SUB FileMsg (File$, C, Message$) 
DECLARE SUB ViewCursor (X, Y, R, SWITCH) 

'화면담당 함수 

DECLARE FUNCTION SaveScreen$ () 
DECLARE SUB ViewScreen (Scr$) 
REM $INCLUDE: 'QB.BI' 
'초기화 
DIM SHARED DTA AS STRING   'DTA 
DIM SHARED FIData(1024) AS FileInfo 
DIM SHARED TotalFile       '총화일수 담당 
DIM SHARED Page 
DIM SHARED Scr$ 
DIM SHARED Floopy$(4) 

FOR i = 0 TO 4 
   READ Floppy$(i) 
NEXT i 
CLS 
DATA "없음","5.25인치 360K 드라이브","5.25인치 1.2M 드라이브","3.5인치 720K 드라이브","3.5인치 1.44M 드라이브","확인불능" 

ADrive = FloopyDriveCheck(1) 
PRINT "-- 하드웨어 확인 --" 
PRINT "A드라이브:"; Floppy$(FloopyDriveCheck(1)) 
PRINT "B드라이브:"; Floppy$(FloopyDriveCheck(2)) 
PRINT "HIMEM.SYS상주:"; BooleanMsg$(HIMEMCheck, "있음", "없음") 
PRINT "Mouse유무:"; BooleanMsg$(MouseCheck, "있음", "없음") 
i$ = INPUT$(1) 
CLS 
Control 

FUNCTION BooleanMsg$ (N, True$, False$) 
   IF N >= 1 THEN 
      BooleanMsg$ = True$ 
   ELSE 
      BooleanMsg$ = False$ 
   END IF 
END FUNCTION 

SUB Control 
Mouse '마우스 가동 
LoadFiles 
COLOR 14, 0 
LOCATE 2, 1: PRINT STRING$(80, 196) 
LOCATE 21, 1: PRINT STRING$(80, 196) 
'파일의 출력 
FileView 1 
CR = 0 
ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 1 
COLOR 15, 0 
COLOR 15, 1 
LOCATE 22, 1: PRINT SPACE$(80) 
LOCATE 22, 1: PRINT "BDIR Version 1.0 [미완성] - Made by Lee Kang Yong" 
LOCATE 23, 1: PRINT SPACE$(80) 
LOCATE 23, 1: PRINT "F10 = MENU" 

DO 
  i$ = INKEY$ 
  SELECT CASE i$ 
     CASE CHR$(27) 
      SCREEN 0, 0, 0 
      END 
     CASE CHR$(13) 
      IF (FIData(CR + 1).Attrib AND 16) > 0 THEN 
         SHELL "CD " + FIData(CR + 1).File 
         LoadFiles 
         FileView 1 
         CR = 0 
         ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 1 
      ELSE 
         IF RIGHT$(RTRIM$(FIData(CR + 1).File), 4) = ".EXE" THEN 
        BufScr$ = SaveScreen$ 
        COLOR 7, 0: CLS 
        SHELL FIData(CR + 1).File 
        i$ = INPUT$(1) 
        ViewScreen (BufScr$) 
         END IF 
         IF RIGHT$(RTRIM$(FIData(CR + 1).File), 4) = ".COM" THEN 
        BufScr$ = SaveScreen$ 
        COLOR 7, 0: CLS 
        SHELL FIData(CR + 1).File 
        i$ = INPUT$(1) 
        ViewScreen (BufScr$) 
         END IF 
         IF RIGHT$(RTRIM$(FIData(CR + 1).File), 4) = ".BAT" THEN 
        BufScr$ = SaveScreen$ 
        COLOR 7, 0: CLS 
        SHELL FIData(CR + 1).File 
        i$ = INPUT$(1) 
        ViewScreen (BufScr$) 
         END IF 
      END IF 
     CASE CHR$(0) + CHR$(72) 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 0 
      CR = CR - 3 
      IF CR + 1 < 1 THEN CR = CR + 3 
      IF INT((CR + 3) / 54) <> INT(CR / 54) THEN Page = INT(CR / 54) + 1: FileView Page 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 1 
     CASE CHR$(0) + CHR$(80) 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 0 
      CR = CR + 3 
      IF CR + 1 > TotalFile THEN CR = CR - 3 
      IF INT((CR - 3) / 54) <> INT(CR / 54) THEN Page = INT(CR / 54) + 1: FileView Page 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 1 
     CASE CHR$(0) + CHR$(75) 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 0 
      CR = CR - 1 
      IF CR + 1 < 1 THEN CR = CR + 1 
      IF INT((CR + 3) / 54) <> INT(CR / 54) THEN Page = INT(CR / 54) + 1: FileView Page 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 1 
     CASE CHR$(0) + CHR$(77) 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 0 
      CR = CR + 1 
      IF CR + 1 > TotalFile THEN CR = CR - 1 
      IF INT((CR - 3) / 54) <> INT(CR / 54) THEN Page = INT(CR / 54) + 1: FileView Page 
      ViewCursor 3 + INT(CR / 3), 5 + (25 * (CR MOD 3)), CR + 1, 1 
  END SELECT 
LOOP 
END SUB 

FUNCTION File.FindFirst (WildCard$, Attrib, BUF AS FileInfo) 
  
   '이 함수의 기능 
   '파일을 받아낸다. 
   'WildCard$, Attrib - 받아낼 조건 
   'WildCard$ - 와일드 카드 
   'Attrib    - 불러낼 조건 속성 
   'BUFFile$,BUFAttrib - 이쪽으로 보내준다. 
   'BUFFile$  - 이쪽으로 파일이름을 보내준다 
   'BUFAttrib - 이쪽으로 그 파일의 속성을 보내준다. 
   DIM IN AS RegTypeX 
   DIM OT AS RegTypeX 
    
   'DTA의 주소를 넣어준다. 
   DTA = SPACE$(256) 
   IN.ax = &H1A00 
   IN.ds = VARSEG(DTA) 
   IN.dx = SADD(DTA) 
   INTERRUPTX &H21, IN, OT 
  
   '인터럽트 써서 파일 찾음 파일은 DTA로 들어옴 
   WildCard$ = WildCard$ + CHR$(0) 
   IN.ax = &H4E00 
   IN.cx = Attrib 
   IN.ds = VARSEG(WildCard$) 
   IN.dx = SADD(WildCard$) 
   INTERRUPTX &H21, IN, OT 
   BUF.Size = ASC(MID$(DTA, 27, 1)) + (256# * ASC(MID$(DTA, 28, 1))) + (65536# * ASC(MID$(DTA, 29, 1))) + (16777216# * ASC(MID$(DTA, 30, 1))) 
   BUF.File = MID$(DTA, 31, 12) 
   BUF.Attrib = ASC(MID$(DTA, 22, 1)) 
   IF INSTR(1, BUF.File, " ") >= 1 THEN BUF.File = LEFT$(BUF.File, INSTR(1, BUF.File, " ") - 1) 
   IF INSTR(1, BUF.File, CHR$(0)) >= 1 THEN BUF.File = LEFT$(BUF.File, INSTR(1, BUF.File, CHR$(0)) - 1) 
   IF OT.ax = 0 THEN File.FindFirst = 1'파일을 못 부를땐 0이고 불렀다면 1이다. 
END FUNCTION 

FUNCTION File.FindNext (BUF AS FileInfo) 
   DIM IN AS RegTypeX 
   DIM OT AS RegTypeX 
   IN.ax = &H4F00 
   INTERRUPTX &H21, IN, OT 
   BUF.File = MID$(DTA, 31, 12) 
   BUF.Attrib = ASC(MID$(DTA, 22, 1)) 
   BUF.Size = ASC(MID$(DTA, 27, 1)) + (256# * ASC(MID$(DTA, 28, 1))) + (65536# * ASC(MID$(DTA, 29, 1))) + (16777216# * ASC(MID$(DTA, 30, 1))) 
   IF INSTR(1, BUF.File, " ") >= 1 THEN BUF.File = LEFT$(BUF.File, INSTR(1, BUF.File, " ") - 1) 
   IF INSTR(1, BUF.File, CHR$(0)) >= 1 THEN BUF.File = LEFT$(BUF.File, INSTR(1, BUF.File, CHR$(0)) - 1) 
   IF OT.ax = 0 THEN File.FindNext = 1 '파일을 못 부를땐 0이고 불렀다면 1이다. 
END FUNCTION 

SUB FileMsg (File$, C, Message$) 
   '화일의 형태에 따라 찍을 색깔과 메세지가 달라진다. 
   Ext$ = RIGHT$(RTRIM$(File$), 4) 
   C = 15 
   IF Ext$ = ".BMP" THEN C = 2 
   IF Ext$ = ".BAT" THEN C = 14 
   IF Ext$ = ".BAS" THEN C = 3 
   IF Ext$ = ".EXE" THEN C = 11 
   IF Ext$ = ".COM" THEN C = 11 
   IF Ext$ = ".BAK" THEN C = 4 
   IF Ext$ = ".LIB" THEN C = 13 
   IF Ext$ = ".CAP" THEN C = 3 
   IF Ext$ = ".DLL" THEN C = 11 
END SUB 

SUB FileView (Page) 
VFrec = 0: PX = 0 
COLOR 15, 0 
IF INT(TotalFile / 54) = 0 THEN VP = 1 ELSE VP = INT(TotalFile / 54) + 1 
LOCATE 21, 66: PRINT USING "[###/###]"; Page; VP 
LOCATE 1, 1: PRINT SPACE$(80) 
LOCATE 1, 1: PRINT "Current Directory: "; : COLOR 14: SHELL "CD" 
COLOR 15 
LOCATE 1, 63: PRINT USING "Total #### File(s)"; TotalFile 
COLOR 15, 1 
FOR i = 3 TO 20 
   LOCATE i, 1: PRINT "?"; SPACE$(78); "?" 
NEXT i 
VFrec = (Page - 1) * 54 
Prec = Prec + 1 
DO 
   VFrec = VFrec + 1 
   Prec = Prec + 1 
   IF VFrec > TotalFile THEN EXIT DO 
   FileMsg FIData(VFrec).File, C, M$ 
   IF (FIData(VFrec).Attrib AND 16) > 0 THEN COLOR 12 ELSE COLOR C 
   LOCATE 3 + PX, 5 + (25 * Linen): PRINT FIData(VFrec).File 
   IF (FIData(VFrec).Attrib AND 16) > 0 THEN 
      LOCATE 3 + PX, 5 + (25 * Linen) + 14: PRINT " [DIR]" 
   ELSE 
      COLOR 14: LOCATE 3 + PX, 5 + (25 * Linen) + 14: PRINT FIData(VFrec).Size 
   END IF 
   Linen = Linen + 1 
   IF Prec = 55 THEN EXIT DO 
   IF Linen = 3 THEN Linen = 0: PX = PX + 1 
LOOP 
END SUB 

FUNCTION FloopyDriveCheck (NumDrv) 
   '&H70H ( CMOS RAM ) 으로 플로피 드라이브를 확인함 
   'NumDrv = 1이면 A드라이브 2이면 B드라이브 
   OUT &H70, &H10 
   Drive = INP(&H71) 
   IF NumDrv = 1 THEN Drive = (Drive AND 240) / 16 
   IF NumDrv = 2 THEN Drive = Drive AND 15 
   FloopyDriveCheck = Drive 
END FUNCTION 

FUNCTION HIMEMCheck 
   'HIMEM이 상주해 있는지 확인한다. 
   DIM IN AS RegType 
   DIM OT AS RegType 
   IN.ax = &H4300 
   INTERRUPT &H2F, IN, OT 
   IF OT.ax AND 128 = 128 THEN HIMEMCheck = 1 
END FUNCTION 

SUB LoadFiles 
DIM Fi AS FileInfo 
'먼저 디렉토리를 부른다. 
Start = 0 
Filen = 0 
DO 
  IF Start = 0 THEN 
     Start = 1 
     B = File.FindFirst("*.", 16, Fi) 
     IF B = 1 THEN 
    IF (Fi.Attrib AND 16) > 0 THEN 
       Filen = Filen + 1 
       FIData(Filen).File = Fi.File 
       FIData(Filen).Attrib = Fi.Attrib 
       FIData(Filen).Size = Fi.Size 
    END IF 
     ELSE 
    EXIT DO 
     END IF 
  END IF 
  IF Start = 1 THEN 
     B = File.FindNext(Fi) 
     IF B = 1 THEN 
    IF (Fi.Attrib AND 16) > 0 THEN 
       Filen = Filen + 1 
       FIData(Filen).File = Fi.File 
       FIData(Filen).Attrib = Fi.Attrib 
       FIData(Filen).Size = Fi.Size 
    END IF 
     ELSE 
    EXIT DO 
     END IF 
  END IF 
LOOP 
Start = 0 
DO 
  IF Start = 0 THEN 
     Start = 1 
     B = File.FindFirst("*.*", 15, Fi) 
     IF B = 1 THEN 
    Filen = Filen + 1 
    FIData(Filen).File = Fi.File 
    FIData(Filen).Attrib = Fi.Attrib 
    FIData(Filen).Size = Fi.Size 
     ELSE 
    EXIT DO 
     END IF 
  END IF 
  IF Start = 1 THEN 
     B = File.FindNext(Fi) 
     IF B = 1 THEN 
    Filen = Filen + 1 
    FIData(Filen).File = Fi.File 
    FIData(Filen).Attrib = Fi.Attrib 
    FIData(Filen).Size = Fi.Size 
     ELSE 
    EXIT DO 
     END IF 
  END IF 
LOOP 
TotalFile = Filen 
END SUB 

SUB Mouse 
   '마우스 작동 
   DIM IN AS RegType 
   DIM OT AS RegType 
   IN.ax = 1 
   INTERRUPT &H33, IN, OT 
END SUB 

FUNCTION MouseCheck 
   '마우스 생존 확인 
   DIM IN AS RegType 
   DIM OT AS RegType 
   IN.ax = 0 
   INTERRUPT &H33, IN, OT 
   IF OT.ax = -1 THEN MouseCheck = 1 
END FUNCTION 

FUNCTION SaveScreen$ 
   DEF SEG = &HB800 
   Scr$ = "" 
   FOR i = 1 TO 25 
   FOR J = 1 TO 80 
       Scr$ = Scr$ + CHR$(PEEK(160 * (i - 1) + (2 * (J - 1)))) 
       Scr$ = Scr$ + CHR$(PEEK(160 * (i - 1) + (2 * (J - 1)) + 1)) 
   NEXT J, i 
   SaveScreen$ = Scr$ 
END FUNCTION 

SUB ViewCursor (X, Y, R, SWITCH) 
   X = X - (18 * INT((X - 3) / 18)) 
   FileMsg FIData(R).File, C, M$ 
   IF (FIData(R).Attrib AND 16) > 0 THEN C = 12 
   IF SWITCH = 1 THEN COLOR 15 - C, 7 ELSE COLOR C, 1 
   LOCATE X, Y - 2: PRINT "  " 
   LOCATE X, Y: PRINT FIData(R).File + "   " 
   LOCATE X, Y + 14: PRINT "        " 
   IF (FIData(R).Attrib AND 16) > 0 THEN 
      LOCATE X, Y + 14: PRINT " [DIR]" 
   ELSE 
      COLOR 14: LOCATE X, Y + 14: PRINT FIData(R).Size 
   END IF 
END SUB 

SUB ViewScreen (Scr$) 
   DEF SEG = &HB800 
   FOR i = 1 TO 25 
   FOR J = 1 TO 80 
       Length = Length + 1 
       POKE 160 * (i - 1) + (2 * (J - 1)), ASC(MID$(Scr$, Length, 1)) 
       Length = Length + 1 
       POKE 160 * (i - 1) + (2 * (J - 1)) + 1, ASC(MID$(Scr$, Length, 1)) 
   NEXT J, i 
END SUB 

