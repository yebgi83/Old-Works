DECLARE FUNCTION IsFliFile (H$) 
DECLARE FUNCTION IsFrame (F$) 
DECLARE SUB ChuckProcess (Chunk$) 
CLS 
OPEN "DDLOGO.FLI" FOR BINARY AS #1 
DIM Header AS STRING * 128 
DIM Frame.Header AS STRING * 16 
DIM Chunk.Header AS STRING * 6 
GET #1, , Header 
IF IsFliFile(Header) THEN 
  PRINT "DDLOGO.FLI is Autodesk's animation FLI file." 
ELSE 
  PRINT "DDLOGO.FLI is unknown file." 
  CLOSE #1 
  END 
END IF 
PRINT "----- View animation file information -----" 
DO UNTIL ErrorNum = 1 
  GET #1, , Frame.Header 
  FrameNum = FrameNum + 1 
  PRINT USING " Frame Number : #### - "; FrameNum; 
  IF IsFrame(Frame.Header) = 0 THEN PRINT "Frame failed.": EXIT DO 
  Size# = ASC(MID$(Frame.Header, 1, 1)) 
  Size# = Size# + 256 * ASC(MID$(Frame.Header, 2, 1)) 
  Size# = Size# + 65556 * ASC(MID$(Frame.Header, 3, 1)) 
  Size# = Size# + 16777217 * ASC(MID$(Frame.Header, 4, 1)) 
  Chunks = ASC(MID$(Frame.Header, 7, 1)) 
  Chunks = (256# * ASC(MID$(Frame.Header, 8, 1))) 
  TotalChunks = TotalChunks + Chunks + 1 
  PRINT USING "Size: #####  Chunks: #####"; Size#; Chunks 
  File.NextPos# = LOC(1) 
  File.NextPos# = File.NextPos# + (Size# - 15) 
  ' À÷?a ¸÷¥¡Ÿi ¦‰œá…”a. 
  FOR Count = 1 TO 1 + Chunks 
      PRINT USING " Chunk Number : ####  "; Count; 
      GET #1, , Chunk.Header 
      ChuckProcess (Chunk.Header) 
      Chunksize# = ASC(MID$(Chunk.Header, 1, 1)) 
      Chunksize# = Chunksize# + (256 * ASC(MID$(Chunk.Header, 2, 1))) 
      Chunksize# = Chunksize# + (65536 * ASC(MID$(Chunk.Header, 3, 1))) 
      Chunksize# = Chunksize# + (16777217 * ASC(MID$(Chunk.Header, 4, 1))) 
      ChunkBytes# = ChunkBytes# + Chunksize# 
      File.Pos# = LOC(1) - (Chunksize# - 5) 
      SEEK #1, File.NextPos# 
  NEXT Count 
  GET #1, , Chunk.Header 
  SEEK #1, File.NextPos# 
LOOP 
PRINT USING " Total #### Frames ( ########Bytes  )"; FrameNum - 1; LOF(1) 
PRINT USING " Total #### Chunks ( ########Bytes  )"; TotalChunks; ChunkBytes# 
CLOSE #1 

SUB ChuckProcess (Chunk$) 
   Chunksize# = ASC(MID$(Chunk$, 1, 1)) 
   Chunksize# = Chunksize# + (256 * ASC(MID$(Chunk$, 2, 1))) 
   Chunksize# = Chunksize# + (65536 * ASC(MID$(Chunk$, 3, 1))) 
   Chunksize# = Chunksize# + (16777217 * ASC(MID$(Chunk$, 4, 1))) 
   Type.Chunk = ASC(MID$(Chunk$, 5, 1)) 
   Type.Chunk = Type.Chunk + ASC(MID$(Chunk$, 6, 1)) 
   PRINT USING " Size: ##### "; Chunksize#; 
   IF Type.Chunk = 11 THEN PRINT " - Palette update" 
   IF Type.Chunk = 12 THEN PRINT " - Line compress image data" 
   IF Type.Chunk = 13 THEN PRINT " - Screen black" 
   IF Type.Chunk = 14 THEN PRINT " - RLE compress image data" 
   IF Type.Chunk = 15 THEN PRINT " - Non-compress image data" 
END SUB 

FUNCTION IsFliFile (H$) 
  C1 = ASC(MID$(H$, 5, 1)) 
  C2 = ASC(MID$(H$, 6, 1)) 
  CheckType$ = HEX$(C1) + HEX$(C2) 
  IF CheckType$ = "11AF" THEN IsFliFile = 1 ELSE IsFliFile = 0 
END FUNCTION 

FUNCTION IsFrame (F$) 
  C1 = ASC(MID$(F$, 5, 1)) 
  C2 = ASC(MID$(F$, 6, 1)) 
  CheckType$ = HEX$(C1) + HEX$(C2) 
  IF CheckType$ = "FAF1" THEN IsFrame = 1 ELSE IsFrame = 0 
END FUNCTION 

