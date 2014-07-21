' Made in Korea 
' 제작 : 이강용 ( SUB팀 소속 ) 
' 본 프로그램은 QOP라고 하여 
' 재혁님의 NOP방식을 고대로 써먹은 프로그램이옵니다 -_-; 
' 제작날짜 1998.03.?? 


DECLARE SUB Title () 
DECLARE SUB InitMainHeaders () 
DECLARE SUB SortMainHeaders () 
DECLARE SUB SortMainHeaders.QuickSort (L, R) 

'-------------------------------------------------------- 
' **** 타입 declare한 부분을 보실까엽? 
' **** declare - 선어ㄴ하다. 젠장 완성형의 한계다 -_-; 
 TYPE Header 
    Char AS STRING * 1  '문자 
    Count AS INTEGER    '빈도수 
 END TYPE 

 CONST NONE = 0 
 CONST TRUE = 1 
 CONST FALSE = -1 
 CONST COMMAND.NOPUT = 0 
 CONST COMMAND.PUT = 1 
' **** 주 프로그램 시작 
 OPTION BASE 0 
 DIM SHARED QOPMainHeader(255) AS Header   ' 주헤더 
 DIM SHARED QOPTempHeader(255) AS Header   ' 임시헤더 
 DIM SHARED CompressPossibleCharTable$(7) 
 DIM SHARED MaxCount 
 DIM BitMask(8) 

 FOR i = 1 TO 8 
   READ BitMask(i) 
 NEXT i 
 DATA 1,2,4,8,16,32,64,128 

 DestFileName$ = "GRPDATA.DAT" 
 CreateCompressFilename$ = "COMPRESS.QOP" 

 InitMainHeaders 
 OPEN DestFileName$ FOR BINARY AS #1 ' Compress할 화일 열기 
      IF LOF(1) = 0 THEN ' 파일 존재 없음 
         PRINT " Can" + CHR$(39) + "t File Write... " 
         CLOSE 
         END   ' 프로그램 끝냄 
      END IF 
      OPEN CreateCompressFilename$ FOR BINARY AS #2 
         IF LOF(1) <> 0 THEN 
            CLOSE #2: KILL CreateCompressFilename$ 
            OPEN CreateCompressFilename$ FOR BINARY AS #2 
         END IF 
         '문자의 빈도수를 집어넣음 
         MaxCount = 0 
         PRINT "Now Loading..." 
         DO WHILE NOT EOF(1) '파일 끝이 아닐때까지 반복한다. 
            LoadChar$ = SPACE$(1) 
            GET #1, , LoadChar$ 
            QOPMainHeader(ASC(LoadChar$)).Count = QOPMainHeader(ASC(LoadChar$)).Count + 1 
            IF QOPMainHeader(ASC(LoadChar$)).Count > MaxCount THEN 
               MaxCount = QOPMainHeader(ASC(LoadChar$)).Count 
            END IF 
         LOOP 
         PRINT "Now Sorting..." 
         SortMainHeaders 
         PRINT "Now Progressing..." 
         SEEK #1, 1 
        
         Header$ = "QOP" 
         PUT #2, , Header$ 
         FOR i = 1 TO 7 
             PUT #2, , CompressPossibleCharTable$(i) 
         NEXT i 
        
         PRINT DestFileName$; "  -->  "; CreateCompressFilename$ 

         DO WHILE NOT EOF(1) 
            LoadChar$ = SPACE$(1) 
            GET #1, , LoadChar$ '한문자를 받음 
            '빈도수에 맞게 적당히 처리함 
            EP = 0 
            FOR FindCount = 1 TO 7 
                IF CompressPossibleCharTable$(FindCount) = LoadChar$ THEN 
                   EP = FindCount: EXIT FOR 
                END IF 
            NEXT FindCount 
            IF EP <> 0 THEN 
               PutBitRouTine.Command = COMMAND.PUT '비트를 찍어라 
               GOSUB SUB.PutBitRouTine 
               FOR i = 1 TO EP - 1 
                   GOSUB SUB.PutBitRouTine 
               NEXT i 
            ELSE 
               PutBitRouTine.Command = COMMAND.NOPUT '비트를 찍지마라 
               GOSUB SUB.PutBitRouTine 
               FOR i = 1 TO 8 
                   IF (ASC(LoadChar$) AND BitMask(i)) THEN 
                      PutBitRouTine.Command = COMMAND.PUT '비트를 찍어라 
                   ELSE 
                      PutBitRouTine.Command = COMMAND.NOPUT '비트를 찍지마라 
                   END IF 
                   GOSUB SUB.PutBitRouTine 
               NEXT i 
            END IF 
         LOOP 
 CLOSE         ' 파일 다 닫음 
END 

SUB.PutBitRouTine: 
 PutBitRouTine.BitCount = PutBitRouTine.BitCount + 1 
 IF PutBitRouTine.BitCount = 9 THEN 
    PutBitRouTine.BitCount = 1 
    PutLoadChar$ = CHR$(PutBitRouTine.Char) 
    PUT #2, , PutLoadChar$ 
    PutBitRouTine.Char = NONE 
 END IF 
 IF PutBitRouTine.Command = COMMAND.PUT THEN 
    PutBitRouTine.Char = PutBitRouTine.Char OR BitMask(PutBitRouTine.BitCount) 
 END IF 
RETURN 

SUB InitMainHeaders 
   FOR Counter = 0 TO 255 
       QOPMainHeader(Counter).Char = CHR$(Counter) 
       QOPMainHeader(Counter).Count = 0 
   NEXT Counter 
END SUB 

SUB SortMainHeaders 
   '정렬한다. 
   'TempHeader로 정렬이 되어 진다. 
   FOR Counter = 0 TO 255 
       QOPTempHeader(Counter).Char = QOPMainHeader(Counter).Char 
       QOPTempHeader(Counter).Count = QOPMainHeader(Counter).Count 
   NEXT Counter 
   SortMainHeaders.QuickSort 0, 255  '퀵 소트로 끝장을 봄 
   FOR Counter = 1 TO 7 
       CompressPossibleCharTable$(Counter) = QOPTempHeader(Counter - 1).Char 
   NEXT Counter 
END SUB 

SUB SortMainHeaders.QuickSort (L, R) 
   IF L >= R THEN EXIT SUB 
   Split = INT((L + R) / 2)' 중간값 
   SplitValue = QOPTempHeader(Split - 1).Count 
   '중간값을 기준으로 하여 
   '큰 값 작은 값으로 나눔 
   CurL = L: CurR = R 
   DO 
      '중간값보다 작은 값을 찾아낸다. 
      DO WHILE QOPTempHeader(CurL).Count >= SplitValue 
         IF CurL = Split THEN EXIT DO 
         CurL = CurL + 1 
      LOOP 
      '중간값보다 큰 값을 찾아낸다. 
      DO WHILE QOPTempHeader(CurR).Count <= SplitValue 
         IF CurR = Split THEN EXIT DO 
         CurR = CurR - 1 
      LOOP 
      SWAP QOPTempHeader(CurL).Count, QOPTempHeader(CurR).Count 
      SWAP QOPTempHeader(CurL).Char, QOPTempHeader(CurR).Char 
      IF CurL = CurR THEN EXIT DO 
      '어느 한쪽이라도 중간 위치에 갔으면 
      IF CurL = Split OR CurR = Split THEN 
         CurL = L: CurR = R 
         '재 정렬 시작 
         SplitValue = QOPTempHeader(Split).Count 
      ELSE 
         CurL = CurL + 1 
         CurR = CurR - 1 
      END IF 
   LOOP 
   SortMainHeaders.QuickSort L, Split - 1 
   SortMainHeaders.QuickSort Split + 1, R 
END SUB 

SUB Title 
   PRINT " QOP Version 1.0  Made by Lee Kang-yong " 
END SUB 

