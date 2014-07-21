Attribute VB_Name = "Module3"
Type 통신환경구조체
   포트 As Integer
   속도 As Long
   데이터비트 As Integer
   정지비트 As Integer
   패리티 As Integer
   흐름제어 As Integer
   환경설정문자열 As String
End Type

Dim 통신환경 As 통신환경구조체
Function Get포트() As Integer
   Get포트 = 통신환경.포트 - 1
End Function
Function Get속도() As Long
   Select Case 통신환경.속도
      Case 4800
        Get속도 = 0
      Case 7200
        Get속도 = 1
      Case 9600
        Get속도 = 2
      Case 14400
        Get속도 = 3
      Case 19200
        Get속도 = 4
      Case 38400
        Get속도 = 5
      Case 57600
        Get속도 = 6
      Case 115200
        Get속도 = 7
      Case 128000
        Get속도 = 8
   End Select
End Function
Function Get정지비트() As Integer
   Select Case 통신환경.정지비트
      Case 1
         Get정지비트 = 0
      Case 1.5
         Get정지비트 = 1
      Case 2
         Get정지비트 = 2
   End Select
End Function
Function Get패리티() As Integer
   Get패리티 = 통신환경.패리티
End Function
Function Get데이터비트() As Integer
   Select Case 통신환경.데이터비트
      Case 7
        Get데이터비트 = 0
      Case 8
        Get데이터비트 = 1
   End Select
End Function
Function Get흐름제어() As Integer
   Get흐름제어 = 통신환경.흐름제어
End Function
Sub Set포트(포트숫자 As Integer)
   통신환경.포트 = 포트숫자 + 1
End Sub
Sub Set속도(속도 As Integer)
   Select Case 속도
      Case 0
        통신환경.속도 = 4800
      Case 1
        통신환경.속도 = 7200
      Case 2
        통신환경.속도 = 9600
      Case 3
        통신환경.속도 = 14400
      Case 4
        통신환경.속도 = 19200
      Case 5
        통신환경.속도 = 38400
      Case 6
        통신환경.속도 = 57600
      Case 7
        통신환경.속도 = 115200
      Case 8
        통신환경.속도 = 128000
   End Select
End Sub
Sub Set정지비트(정지비트 As Integer)
   Select Case 정지비트
      Case 1
        통신환경.정지비트 = 0
      Case 1.5
        통신환경.정지비트 = 1
      Case 2
        통신환경.정지비트 = 2
   End Select
End Sub
Sub Set패리티(패리티 As Integer)
   통신환경.패리티 = 패리티
End Sub
Sub Set데이터비트(데이터비트 As Integer)
    Select Case 데이터비트
      Case 0
        통신환경.데이터비트 = 7
      Case 1
        통신환경.데이터비트 = 8
   End Select
End Sub
Sub Set흐름제어(흐름제어 As Integer)
   통신환경.흐름제어 = 흐름제어
End Sub
Sub 통신기본환경(통신객체 As MSComm)
   통신환경.포트 = 3
   통신환경.속도 = 57600
   통신환경.데이터비트 = 8
   통신환경.정지비트 = 1
   통신환경.패리티 = 0
   통신환경.환경설정문자열 = "57600,n,8"
   통신환경.흐름제어 = 0
   통신설정적용 통신객체
End Sub
Sub 통신설정적용(통신객체 As MSComm)
   If (통신객체.PortOpen = True) Then
      통신객체.PortOpen = False
      For c = 1 To 1000: Next c
   End If
   
   통신객체.CommPort = 통신환경.포트
   통신객체.Handshaking = 통신환경.흐름제어
   통신객체.RThreshold = 1
   통신객체.RTSEnable = True
   
   통신환경.환경설정문자열 = LTrim$(Str$(통신환경.속도)) & ","
   Select Case 통신환경.패리티
      Case 0 'None
         통신환경.환경설정문자열 = 통신환경.환경설정문자열 & "n"
      Case 1 'Odd
         통신환경.환경설정문자열 = 통신환경.환경설정문자열 & "o"
      Case 2 'Even
         통신환경.환경설정문자열 = 통신환경.환경설정문자열 & "e"
   End Select
   
   통신환경.환경설정문자열 = 통신환경.환경설정문자열 & "," & LTrim$(Str$(통신환경.데이터비트))
   통신환경.환경설정문자열 = 통신환경.환경설정문자열 & "," & LTrim$(Str$(통신환경.정지비트))
      
   통신객체.Settings = 통신환경.환경설정문자열
   통신객체.SThreshold = 1
   통신객체.InputLen = 1
   
   On Error GoTo ErrorOpenPort
   통신객체.PortOpen = True
ErrorOpenPort:
End Sub

Function 통신상태() As String
   통신상태 = "COM" & LTrim$(통신환경.포트) & ":" & 통신환경.환경설정문자열
End Function

Sub 통신환경저장(파일명 As String)
   Open 파일명 For Output As #1
      Print #1, 통신환경.포트
      Print #1, 통신환경.속도
      Print #1, 통신환경.데이터비트
      Print #1, 통신환경.정지비트
      Print #1, 통신환경.패리티
      Print #1, 통신환경.흐름제어
   Close #1
End Sub
Sub 통신환경부르기(파일명 As String)
   Open 파일명 For Input As #1
      Input #1, 통신환경.포트
      Input #1, 통신환경.속도
      Input #1, 통신환경.데이터비트
      Input #1, 통신환경.정지비트
      Input #1, 통신환경.패리티
      Input #1, 통신환경.흐름제어
   Close #1
End Sub

