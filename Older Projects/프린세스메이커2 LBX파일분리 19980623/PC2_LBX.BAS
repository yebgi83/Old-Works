DECLARE SUB EncordingLBX (Filename$) 
DECLARE SUB BottomPrint (X, S$) 
DECLARE SUB DeleteALLPT1File () 
DECLARE SUB ClearScreen () 
DECLARE SUB Usage () 
CLEAR , , 16384 
TYPE LBXFileDataHeader 
    Fname AS STRING * 12 
    StartPos AS LONG 
    Length AS LONG 
END TYPE 
VIEW PRINT 1 TO 25 
Options$ = COMMAND$ 
Filename$ = Options$ 
COLOR 7, 0 
CLS 
COLOR 15, 1 
PRINT "                   Princess Maker 2 - LBX File Load Program                     " 
COLOR 15, 0 
PRINT " Made by Lee Kang-yong" 
PRINT " Esc - Exit" 
IF Options$ = "" THEN 
  COLOR 7, 0 
  Usage 
ELSE 
  PRINT " Loading "; Filename$; "....." 
  BottomPrint 1, " LBX File Load Program .... Programmed by Lee kang-yong                         " 
  EncordingLBX (Filename$) 
END IF 

SUB BottomPrint (X, S$) 
   DEF SEG = &HB800 
   FOR i = 1 TO LEN(S$) 
       POKE 160 * 24 + (2 * (i - 1 + X - 1)) + 1, 16 * 1 + 15 
       POKE 160 * 24 + (2 * (i - 1 + X - 1)), ASC(MID$(S$, i, 1)) 
   NEXT i 
END SUB 

SUB ClearScreen 
   DEF SEG = &HB800 
   FOR i = 1 TO 24 
       LOCATE i, 1: PRINT SPACE$(80) 
   NEXT i 
END SUB 

SUB DeleteALLPT1File 
   SHELL "CD TEMP" 
   SHELL "ECHO Y | DEL *.* " 
   SHELL "CD.." 
END SUB 

SUB EncordingLBX (Filename$) 
   ' Encording LBX 
   DIM FilenamePlace.StartPos AS LONG ' Filename Place 
   DIM FileData AS LBXFileDataHeader 
   DIM FileCount AS INTEGER 
   DIM char AS STRING * 1 
   DIM OneLargeBlock AS STRING * 8192 
   DIM OneMiddleBlock AS STRING * 1024 
   DIM OneSmallBlock AS STRING * 128 
   LargeBlockLength = 8192 
   MiddleBlockLength = 1024 
   SmallBlockLength = 128 
   OPEN Filename$ FOR BINARY AS #1 
        IF LOF(1) = 0 THEN 
           PRINT " File not found...": PLAY "L64GCACA" 
           CLOSE #1: KILL Filename$ 
           EXIT SUB 
        END IF 
        SEEK #1, LOF(1) - 5 
        GET #1, , char 
        FileCount = ASC(char$) 
        GET #1, , char 
        FileCount = FileCount + ASC(char$) * 256# 
        PRINT " Total "; FileCount; " File(s)" 
        GET #1, , char 
        FilenamePlace.StartPos = ASC(char) 
        GET #1, , char 
        FilenamePlace.StartPos = FilenamePlace.StartPos + 256# * ASC(char) 
        GET #1, , char 
        FilenamePlace.StartPos = FilenamePlace.StartPos + 65536# * ASC(char) 
        FOR i = 1 TO FileCount 
            SEEK #1, FilenamePlace.StartPos + (20 * (i - 1)) + 1 
            GET #1, , FileData 
            PRINT i; ". Created "; RTRIM$(FileData.Fname$); " File. - "; FileData.Length; "Bytes  "; 
            y = CSRLIN: X = POS(1) 
            SEEK #1, FileData.StartPos + 1 
            Length# = FileData.Length 
            OPEN RTRIM$(FileData.Fname$) FOR BINARY AS #2 
                 SEEK #2, 1 
                 FOR b = 1 TO INT(FileData.Length / LargeBlockLength) 
                     LOCATE y, X: PRINT USING "(###.## Percent Completed)"; 100 * (LOF(2) / Length#) 
                     GET #1, , OneLargeBlock 
                     PUT #2, , OneLargeBlock 
                 NEXT b 
                 FileData.Length = FileData.Length MOD LargeBlockLength 
                 FOR b = 1 TO INT(FileData.Length / MiddleBlockLength) 
                     LOCATE y, X: PRINT USING "(###.## Percent Completed)"; 100 * (LOF(2) / Length#) 
                     GET #1, , OneMiddleBlock 
                     PUT #2, , OneMiddleBlock 
                 NEXT b 
                 FileData.Length = FileData.Length MOD MiddleBlockLength 
                 FOR b = 1 TO INT(FileData.Length / SmallBlockLength) 
                     LOCATE y, X: PRINT USING "(###.## Percent Completed)"; 100 * (LOF(2) / Length#) 
                     GET #1, , OneSmallBlock 
                     PUT #2, , OneSmallBlock 
                 NEXT b 
                 FileData.Length = FileData.Length MOD SmallBlockLength 
                 FOR b = 1 TO FileData.Length 
                     LOCATE y, X: PRINT USING "(###.## Percent Completed)"; 100 * (LOF(2) / Length#) 
                     GET #1, , char 
                     PUT #2, , char 
                 NEXT b 
                 IF (100 * (LOF(2) / Length#)) >= 100 THEN LOCATE y, X: PRINT "Completed.......          " 
            CLOSE #2 
            TotalLength# = TotalLength# + Length# 
            TotalPercentString$ = "(" + STR$(INT(100 * ((TotalLength# / FilenamePlace.StartPos)))) + "%)" 
            BottomPrint 61, TotalPercentString$ 
            IF y = 24 THEN ClearScreen: LOCATE 1, 1 
            K$ = INKEY$ 
            IF K$ = CHR$(27) THEN PRINT " Canceld....": EXIT FOR 
        NEXT i 
   CLOSE #1 
   PLAY "L64CEGCEGCEG" 
   COLOR 7, 0 
END SUB 

SUB Usage 
   PRINT " Usage : VIEWLBX [LBX File name] " 
END SUB 

