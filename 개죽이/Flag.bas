Attribute VB_Name = "Module6"
Public Const 정지보너스 = 1
Public Const 이차보너스 = 2
Public Const 연기 = 4
Public Const 손접촉반칙 = 8

Dim 플래그 As Integer
Sub Set플래그(Flag As Integer)
   플래그 = Flag
End Sub

Sub Set정지보너스플래그(Bit As Boolean)
   If (Bit = True) Then
      플래그 = 플래그 Or 정지보너스
   Else
      플래그 = 플래그 And (255 Xor 정지보너스)
   End If
End Sub

Sub Set2차보너스플래그(Bit As Boolean)
   If (Bit = True) Then
      플래그 = 플래그 Or 이차보너스
   Else
      플래그 = 플래그 And (255 Xor 이차보너스)
   End If
End Sub

Sub Set연기플래그(Bit As Boolean)
   If (Bit = True) Then
      플래그 = 플래그 Or 연기
   Else
      플래그 = 플래그 And (255 Xor 연기)
   End If
End Sub

Sub Set손접촉반칙플래그(Bit As Boolean)
   If (Bit = True) Then
      플래그 = 플래그 Or 손접촉반칙
   Else
      플래그 = 플래그 And (255 Xor 손접촉반칙)
   End If
End Sub

Function Get플래그() As Integer
   Get플래그 = 플래그
End Function

Function Get정지보너스플래그() As Boolean
   If (플래그 And 정지보너스) <> 0 Then
      Get정지보너스플래그 = True
   Else
      Get정지보너스플래그 = False
   End If
End Function

Function Get2차보너스플래그() As Boolean
   If (플래그 And 이차보너스) <> 0 Then
      Get이차보너스플래그 = True
   Else
      Get이차보너스플래그 = False
   End If
End Function
