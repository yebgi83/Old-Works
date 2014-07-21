Attribute VB_Name = "Module4"
Dim 제한시간 As Long
Dim 최대주행횟수 As Integer
Dim 정지보너스가중치 As Integer
Dim 이차보너스가중치 As Integer
Dim 순서미루기가중치 As Integer
Dim 주행포기가중치 As Integer

Sub Set제한시간(시간 As Long)
   제한시간 = 시간
End Sub

Sub Set최대주행횟수(주행횟수 As Integer)
   최대주행횟수 = 주행횟수
End Sub

Sub Set정지보너스가중치(가중치 As Integer)
   정지보너스가중치 = 가중치
End Sub

Sub Set2차보너스가중치(가중치 As Integer)
   이차보너스가중치 = 가중치
End Sub

Sub Set순서미루기가중치(가중치 As Integer)
   순서미루기가중치 = 가중치
End Sub

Sub Set주행포기가중치(가중치 As Integer)
   주행포기가중치 = 가중치
End Sub

Function Get제한시간() As Long
   Get제한시간 = 제한시간
End Function

Function Get최대주행횟수() As Integer
   Get최대주행횟수 = 최대주행횟수
End Function

Function Get정지보너스가중치() As Integer
   Get정지보너스가중치 = 정지보너스가중치
End Function

Function Get2차보너스가중치() As Integer
   Get2차보너스가중치 = 이차보너스가중치
End Function

Function Get순서미루기가중치() As Integer
   Get순서미루기가중치 = 순서미루기가중치
End Function

Function Get주행포기가중치() As Integer
   Get주행포기가중치 = 주행포기가중치
End Function

Sub 기본규칙지정()
   제한시간 = 60 * 20
   최대주행횟수 = 10
   정지보너스가중치 = -10
   이차보너스가중치 = -10
   순서미루기가중치 = 30
   주행포기가중치 = 30
End Sub

Sub 규칙파일저장(파일명 As String)
   Open 파일명 For Output As #1
      Print #1, 제한시간
      Print #1, 최대주행횟수
      Print #1, 정지보너스가중치
      Print #1, 이차보너스가중치
      Print #1, 순서미루기가중치
      Print #1, 주행포기가중치
   Close #1
End Sub

Sub 규칙파일부르기(파일명 As String)
   Open 파일명 For Input As #1
      Input #1, 제한시간
      Input #1, 최대주행횟수
      Input #1, 정지보너스가중치
      Input #1, 이차보너스가중치
      Input #1, 순서미루기가중치
      Input #1, 주행포기가중치
   Close #1
End Sub

Function 플래그에따른가중치(플래그 As Integer)
   Dim 보너스 As Integer
   If (플래그 And 정지보너스) <> 0 Then 보너스 = 보너스 + 정지보너스가중치
   If (플래그 And 이차보너스) <> 0 Then 보너스 = 보너스 + 이차보너스가중치
   플래그에따른가중치 = 보너스
End Function


