Attribute VB_Name = "Module2"
Public Declare Function GetTickCount Lib "kernel32" () As Long

Public Const 사용중 = 1
Public Const 경주중 = 2
Public Const 경주포기 = 250000000#

Dim 처음사용시간 As Long
Dim 처음경주시간 As Long

Dim 사용시간 As Long
Dim 경주시간 As Long

Dim 시간상태 As Integer

Sub 사용시간시작()
   시간상태 = 시간상태 Or 사용중
   처음사용시간 = GetTickCount - 사용시간
End Sub

Sub 경주시간시작()
   If ((시간상태 And 사용중) = 0) Then Exit Sub
   시간상태 = 시간상태 Or 경주중
   처음경주시간 = GetTickCount - 경주시간
End Sub

Sub 경주시간초기화()
   경주시간 = 0
End Sub

Sub 시간측정초기화()
   사용시간 = 0
   경주시간 = 0
End Sub

Sub 사용시간추가(추가시간 As Long)
   처음사용시간 = GetTickCount - (사용시간 + 추가시간)
   사용시간 = GetTickCount - 처음사용시간
   If (Get제한시간 * 1000# - 사용시간 = 0) Then
      사용시간 = Get제한시간 * 1000#
   End If
End Sub

Sub 사용시간지정(시간 As Long)
   If ((시간상태 And 사용중) = 0) Then Exit Sub
   처음사용시간 = GetTickCount - 시간
   사용시간 = 시간
End Sub

Sub 사용시간정지()
   시간상태 = 0
End Sub

Sub 경주시간정지()
   시간상태 = 시간상태 And 사용중
End Sub

Sub 경주포기지정()
   경주시간 = 경주포기
End Sub

Sub Set사용시간(시간 As Long)
   사용시간 = 시간
End Sub

Sub 시간콜백함수()
   If (시간상태 And 사용중) <> 0 Then 사용시간 = GetTickCount - 처음사용시간
   If (시간상태 And 경주중) <> 0 Then 경주시간 = GetTickCount - 처음경주시간
End Sub

Function Get경주포기() As Boolean
   If 사용시간 = 경주포기 Then
      Get경주포기 = True
   Else
      Get경주포기 = False
   End If
End Function

Function Get사용시간() As Long
   Get사용시간 = 사용시간
End Function

Function Get경주시간() As Long
   Get경주시간 = 경주시간
End Function

Function Get사용중() As Boolean
   If (시간상태 And 사용중) > 0 Then
      Get사용중 = True
   Else
      Get사용중 = False
   End If
End Function

Function Get경주중() As Boolean
   If (시간상태 And 경주중) > 0 Then
      Get경주중 = True
   Else
      Get경주중 = False
   End If
End Function

