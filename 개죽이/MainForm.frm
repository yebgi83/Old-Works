VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form MainForm 
   BorderStyle     =   1  '단일 고정
   Caption         =   "개죽이"
   ClientHeight    =   10890
   ClientLeft      =   2715
   ClientTop       =   3855
   ClientWidth     =   14730
   Icon            =   "MainForm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   10890
   ScaleWidth      =   14730
   StartUpPosition =   2  '화면 가운데
   Begin VB.Frame Frame3 
      Caption         =   "보너스"
      Height          =   1455
      Left            =   6360
      TabIndex        =   32
      Top             =   2520
      Width           =   2895
      Begin VB.CommandButton Cmd정지보너스 
         Caption         =   "정지보너스"
         Enabled         =   0   'False
         Height          =   495
         Left            =   120
         TabIndex        =   34
         Top             =   240
         Width           =   1335
      End
      Begin VB.CommandButton Cmd2차보너스 
         Caption         =   "2차보너스"
         Enabled         =   0   'False
         Height          =   495
         Left            =   120
         TabIndex        =   33
         Top             =   840
         Width           =   1335
      End
      Begin VB.Label Label2차보너스 
         AutoSize        =   -1  'True
         Caption         =   "없음"
         Height          =   300
         Left            =   1920
         TabIndex        =   36
         Top             =   1000
         Width           =   360
      End
      Begin VB.Label Label정지보너스 
         AutoSize        =   -1  'True
         Caption         =   "없음"
         Height          =   180
         Left            =   1920
         TabIndex        =   35
         Top             =   390
         Width           =   360
      End
   End
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  '아래 맞춤
      Height          =   375
      Left            =   0
      TabIndex        =   24
      Top             =   10515
      Width           =   14730
      _ExtentX        =   25982
      _ExtentY        =   661
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   1
            Object.Width           =   6112
            Text            =   "통신 환경"
            TextSave        =   "통신 환경"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Object.Width           =   12700
            MinWidth        =   12700
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Object.Width           =   7056
            MinWidth        =   7056
            Text            =   "통신 데이터 체크"
            TextSave        =   "통신 데이터 체크"
         EndProperty
      EndProperty
   End
   Begin VB.Frame Frame2 
      Caption         =   "주행"
      Height          =   1455
      Left            =   3240
      TabIndex        =   20
      Top             =   2520
      Width           =   3015
      Begin VB.CommandButton Cmd기록삭제 
         Caption         =   "기록삭제"
         Height          =   495
         Left            =   1560
         TabIndex        =   30
         Top             =   840
         Width           =   1335
      End
      Begin VB.CommandButton Cmd주행포기 
         Caption         =   "주행포기"
         Enabled         =   0   'False
         Height          =   495
         Left            =   120
         TabIndex        =   23
         Top             =   840
         Width           =   1335
      End
      Begin VB.CommandButton Cmd주행시작 
         Caption         =   "주행시작"
         Enabled         =   0   'False
         Height          =   495
         Left            =   120
         TabIndex        =   22
         Top             =   240
         Width           =   1335
      End
      Begin VB.CommandButton Cmd주행종료 
         Caption         =   "주행종료"
         Enabled         =   0   'False
         Height          =   495
         Left            =   1560
         TabIndex        =   21
         Top             =   240
         Width           =   1335
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "참가자 순서"
      Height          =   1455
      Left            =   120
      TabIndex        =   16
      Top             =   2520
      Width           =   3015
      Begin VB.CommandButton Cmd순서미루기 
         Caption         =   "순서미루기"
         Enabled         =   0   'False
         Height          =   495
         Left            =   1560
         TabIndex        =   29
         Top             =   840
         Width           =   1335
      End
      Begin VB.CommandButton Cmd차례정지 
         Caption         =   "차례정지"
         Enabled         =   0   'False
         Height          =   495
         Left            =   1560
         TabIndex        =   19
         Top             =   240
         Width           =   1335
      End
      Begin VB.CommandButton Cmd차례시작 
         Caption         =   "차례시작"
         Height          =   495
         Left            =   120
         TabIndex        =   18
         Top             =   240
         Width           =   1335
      End
      Begin VB.CommandButton Cmd다음차례 
         Caption         =   "다음차례"
         Height          =   495
         Left            =   120
         TabIndex        =   17
         Top             =   840
         Width           =   1335
      End
   End
   Begin VB.Frame Frame 
      Caption         =   "현재 순서"
      Height          =   7935
      Left            =   9360
      TabIndex        =   6
      Top             =   2520
      Width           =   5295
      Begin VB.CommandButton Cmd선택기록삭제 
         Caption         =   "선택한 기록 무효"
         Height          =   495
         Left            =   2520
         TabIndex        =   31
         Top             =   960
         Width           =   2655
      End
      Begin VB.TextBox TxtRank 
         Height          =   270
         Left            =   4440
         Locked          =   -1  'True
         TabIndex        =   28
         Top             =   195
         Width           =   735
      End
      Begin VB.TextBox TxtNum 
         Height          =   270
         Left            =   600
         Locked          =   -1  'True
         TabIndex        =   27
         Top             =   180
         Width           =   615
      End
      Begin VB.TextBox TxtNumOfRace 
         Height          =   270
         Left            =   1200
         Locked          =   -1  'True
         TabIndex        =   15
         Top             =   1000
         Width           =   855
      End
      Begin VB.TextBox TxtRobotName 
         Height          =   270
         Left            =   2040
         Locked          =   -1  'True
         TabIndex        =   13
         Top             =   200
         Width           =   1815
      End
      Begin VB.TextBox TxtName 
         Height          =   270
         Left            =   3240
         Locked          =   -1  'True
         TabIndex        =   12
         Top             =   620
         Width           =   1935
      End
      Begin VB.TextBox TxtUni 
         Height          =   270
         Left            =   600
         Locked          =   -1  'True
         TabIndex        =   11
         Top             =   600
         Width           =   2055
      End
      Begin MSComctlLib.ListView ListView2 
         Height          =   6255
         Left            =   120
         TabIndex        =   26
         Top             =   1560
         Width           =   5055
         _ExtentX        =   8916
         _ExtentY        =   11033
         View            =   3
         LabelEdit       =   1
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         FullRowSelect   =   -1  'True
         _Version        =   393217
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   5
         BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            Text            =   "주행횟수"
            Object.Width           =   1587
         EndProperty
         BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            Alignment       =   2
            SubItemIndex    =   1
            Text            =   "주행시간"
            Object.Width           =   1764
         EndProperty
         BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            Alignment       =   2
            SubItemIndex    =   2
            Text            =   "비고"
            Object.Width           =   2540
         EndProperty
         BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            Alignment       =   2
            SubItemIndex    =   3
            Text            =   "보너스"
            Object.Width           =   1270
         EndProperty
         BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
            SubItemIndex    =   4
            Text            =   "결과"
            Object.Width           =   2540
         EndProperty
      End
      Begin VB.Label Lab순위 
         Caption         =   "순위:"
         Height          =   255
         Index           =   4
         Left            =   3960
         TabIndex        =   25
         Top             =   255
         Width           =   615
      End
      Begin VB.Label Lab총주행횟수 
         Caption         =   "총주행횟수:"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   14
         Top             =   1080
         Width           =   975
      End
      Begin VB.Label Lab이름 
         Caption         =   "로봇명:"
         Height          =   255
         Index           =   3
         Left            =   1320
         TabIndex        =   10
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Lab이름 
         Caption         =   "학교:"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   9
         Top             =   645
         Width           =   975
      End
      Begin VB.Label Lab이름 
         Caption         =   "이름:"
         Height          =   255
         Index           =   1
         Left            =   2760
         TabIndex        =   8
         Top             =   645
         Width           =   975
      End
      Begin VB.Label Lab이름 
         Caption         =   "순번:"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   7
         Top             =   240
         Width           =   975
      End
   End
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   4200
      Top             =   720
   End
   Begin MSComctlLib.ListView ListView1 
      Height          =   6375
      Left            =   120
      TabIndex        =   0
      Top             =   4080
      Width           =   9135
      _ExtentX        =   16113
      _ExtentY        =   11245
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FullRowSelect   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   8
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "순번"
         Object.Width           =   1058
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "이름"
         Object.Width           =   1764
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "학교"
         Object.Width           =   3528
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "로봇명"
         Object.Width           =   3528
      EndProperty
      BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   4
         Text            =   "순위"
         Object.Width           =   1058
      EndProperty
      BeginProperty ColumnHeader(6) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   5
         Text            =   "최고기록"
         Object.Width           =   1764
      EndProperty
      BeginProperty ColumnHeader(7) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   6
         Text            =   "주행횟수"
         Object.Width           =   1058
      EndProperty
      BeginProperty ColumnHeader(8) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   7
         Text            =   "사용시간"
         Object.Width           =   1764
      EndProperty
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   4680
      Top             =   720
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Label LabMsg 
      Alignment       =   2  '가운데 맞춤
      Appearance      =   0  '평면
      BackColor       =   &H00C0FFFF&
      BorderStyle     =   1  '단일 고정
      Caption         =   "본 프로그램은 라인트레이서 경기 진행기 ""개죽이"" 입니다."
      BeginProperty Font 
         Name            =   "굴림체"
         Size            =   21.75
         Charset         =   129
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   615
      Left            =   120
      TabIndex        =   5
      Top             =   120
      Width           =   14535
   End
   Begin VB.Label Label2 
      BackStyle       =   0  '투명
      Caption         =   "남은시간"
      BeginProperty Font 
         Name            =   "굴림"
         Size            =   12
         Charset         =   129
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   1
      Left            =   5520
      TabIndex        =   4
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Label Lab사용시간 
      BackColor       =   &H00000000&
      Caption         =   "00:00.000"
      BeginProperty Font 
         Name            =   "HY나무L"
         Size            =   48
         Charset         =   129
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   960
      Left            =   5880
      TabIndex        =   3
      Top             =   1395
      Width           =   4050
   End
   Begin VB.Label Label1 
      BackStyle       =   0  '투명
      Caption         =   "주행시간"
      BeginProperty Font 
         Name            =   "굴림"
         Size            =   12
         Charset         =   129
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   2
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Label Lab경주시간 
      BackColor       =   &H00000000&
      Caption         =   "00:00.000"
      BeginProperty Font 
         Name            =   "HY나무L"
         Size            =   48
         Charset         =   129
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H0000FF00&
      Height          =   960
      Left            =   600
      TabIndex        =   1
      Top             =   1395
      Width           =   4050
   End
   Begin VB.Menu Menu기능 
      Caption         =   "기능"
      Begin VB.Menu Menu참가자등록 
         Caption         =   "참가자 등록"
      End
      Begin VB.Menu Menu초기화 
         Caption         =   "데이터 초기화"
      End
      Begin VB.Menu Cmd순위결과보기 
         Caption         =   "순위 결과 보기"
      End
      Begin VB.Menu Menu종료 
         Caption         =   "종료"
      End
   End
   Begin VB.Menu Menu설정 
      Caption         =   "설정"
      Begin VB.Menu MenuRS232 
         Caption         =   "RS232 설정"
      End
      Begin VB.Menu Menu규칙설정 
         Caption         =   "규칙 설정"
      End
   End
   Begin VB.Menu Menu개죽이 
      Caption         =   "개죽이"
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim 차례 As Integer
Dim 주행차례 As Integer

Function 질문응답(질문 As String, 제목 As String) As Boolean
   Dim 선택 As Integer
   Dim 경주중 As Boolean
   Dim 사용중 As Boolean
   
   경주중 = Get경주중
   사용중 = Get사용중
   If 경주중 = True Then 경주시간정지
   If 사용중 = True Then 사용시간정지
   
   선택 = MsgBox(질문, vbApplicationModal Or vbYesNo, 제목)
   If 선택 = vbYes Then
      질문응답 = True
   Else
      질문응답 = False
      If 경주중 = True Then 경주시간시작
      If 사용중 = True Then 사용시간시작
   End If
End Function

Sub 상태표시(Msg As String)
   StatusBar1.Panels(2).Text = Msg
   StatusBar1.Refresh
End Sub

Sub 경기3초대기()
   On Error GoTo NotOpened
   '3초간 대기한다.
   MSComm1.PortOpen = False
   Timer1.Enabled = False
   사용시간정지
   WaitForm.Show 1
   사용시간시작
   Timer1.Enabled = True
   MSComm1.PortOpen = True
   Exit Sub

NotOpened:
   Timer1.Enabled = False
   사용시간정지
   WaitForm.Show 1
   사용시간시작
   Timer1.Enabled = True
End Sub

Sub 주행시작()
   If Get사용중 = False Then 사용시간시작
   
   Cmd차례정지.Enabled = False
   Cmd주행시작.Enabled = False
   Cmd기록삭제.Enabled = False
   Cmd주행종료.Enabled = True
   Cmd주행포기.Enabled = True
   Set플래그 0
   
   '주행기록 마지막것으로 자동선택
   LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "] 의 " + Str(Val(TxtNumOfRace.Text) + 1) + "번째 주행이 시작되었습니다."
      
   경주시간시작
   
   '연주
   PlaySound 출발신호사운드, 0, 1
End Sub

Sub 주행종료()
   Cmd차례정지.Enabled = True
   Cmd주행시작.Enabled = True
   Cmd기록삭제.Enabled = True
   Cmd주행종료.Enabled = False
   Cmd주행포기.Enabled = False
   
   If Get경주시간 > 0 Then
      경주시간정지
      기록추가 차례, Get경주시간, Get플래그
      참가자보기갱신
            
      '결과 표시
      LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "] 차례 " + Str(Val(TxtNumOfRace.Text)) + "번째 기록은 " + 시간형태로변환(Get경주시간) + " 입니다."
      경주시간초기화
            
      '연주
      PlaySound 박수소리사운드, 0, 1
      If Val(TxtNumOfRace.Text) = Get최대주행횟수 Then
         MsgBox "최대주행횟수인 " & Str(Get최대주행횟수) & "회를 채웠습니다.", vbApplicationModal And vbOKOnly
         Cmd차례정지_Click
      Else
         경기3초대기
      End If
    End If
End Sub

Sub 참가자보기갱신()
   상태표시 "참가자 정보를 갱신중입니다."
   참가자DB연결 ListView1
   
   If 차례 = 0 And ListView1.ListItems.Count > 0 Then 차례 = 1
   If 차례 > ListView1.ListItems.Count Then 차례 = ListView1.ListItems.Count
   If 차례 > 0 Then
      ListView1_ItemClick ListView1.ListItems.Item(차례)
   Else
      TxtNum.Text = ""
      TxtName.Text = ""
      TxtUni.Text = ""
      TxtRank.Text = ""
      TxtRobotName.Text = ""
      TxtNumOfRace.Text = ""
   End If
   
   주행기록보기 차례, ListView2
   상태표시 ""
End Sub

Private Sub Cmd기록삭제_Click()
   If 차례 = 0 Then
      MsgBox "선택된 참가자가 없습니다.", vbApplicationModal Or vbOKOnly
      Exit Sub
   Else
      If 질문응답("선택된 [" & TxtNum.Text & "번 " & TxtName.Text & "] 참가자의 기록을 모두 삭제합니다. 부득이한 상황에서 사용하는 기능입니다. 그래도 하시겠습니까?", "재확인") = True Then
         기록삭제 차례
         
         상태표시 "참가자 정보를 저장중입니다."
         참가자파일저장 참가자보관파일
         상태표시 ""

         참가자보기갱신
         
         '메시지 출력으로 마무리
         MsgBox "기록삭제가 완료되었습니다.", vbApplicationModal Or vbOKOnly
      End If
   End If
End Sub

Private Sub Cmd다음차례_Click()
   If (차례 < ListView1.ListItems.Count) Then
       ListView1_ItemClick ListView1.ListItems.Item(차례 + 1)
   Else
       LabMsg.Caption = "모든 차례가 끝났습니다. 수고하셨습니다."
   End If
End Sub

Private Sub Cmd선택기록삭제_Click()
   Dim 첨자 As Integer
   Dim 선택 As Integer
            
   첨자 = Val(TxtNum.Text)
   If ListView2.ListItems.Count = 0 Then
      MsgBox "주행 기록이 없습니다", vbApplicationModal Or vbOKOnly
      Exit Sub
   End If
   If ListView2.SelectedItem <> 0 Then
      선택 = MsgBox("선택된" & ListView2.SelectedItem & "번 주행기록이 삭제됩니다. 그래도 하시겠습니까?", vbApplicationModal Or vbYesNo, "경고")
      If 선택 = vbYes Then
         선택기록삭제 차례, Val(ListView2.SelectedItem)
         참가자보기갱신
      End If
   Else
      MsgBox "선택한 기록이 없습니다", vbSystemModal
   End If
End Sub

Private Sub Cmd순서미루기_Click()
   If 차례 = 0 Then
      MsgBox "선택된 참가자가 없습니다.", vbApplicationModal Or vbOKOnly
      Exit Sub
   Else
      If 질문응답("선택된 [" & TxtNum.Text & "번 " & TxtName.Text & "] 참가자의 순서가 가장 뒤로 미뤄집니다. 그리고 사용시간이 차감되는 불이익이 작용합니다. 그래도 하시겠습니까?", "재확인") = True Then
         '가중치 부여한다음 차례를 종료하면, 기록이 된다.
         경주시간초기화
         사용시간추가 Get순서미루기가중치
         Cmd차례정지_Click
         
         '기록한 정보의 위치를 뒤로 미루고, 그 상태를 보여준다.
         순서미루기 차례
         참가자보기갱신
         
         '메시지 출력으로 마무리
         MsgBox "순서미루기 작업이 완료되었습니다.", vbApplicationModal Or vbOKOnly
      End If
   End If
End Sub

Private Sub Cmd순위결과보기_Click()
   결과파일만들기 결과보관파일
   Call Shell("C:\Windows\NOTEPAD.EXE " & 결과보관파일, vbMaximizedFocus)
End Sub

Private Sub Cmd정지보너스_Click()
   Dim 플래그 As Integer
   플래그 = 기록에서플래그얻기(차례, 주행차례)
   
   If ((플래그 And 정지보너스) <> 0) Then
      플래그 = 플래그 And (255 Xor 정지보너스)
   Else
      플래그 = 플래그 Or 정지보너스
   End If
   기록에플래그덮어씌우기 차례, 주행차례, 플래그
   
   '화면에 보이는 데이터 갱신
   참가자DB연결 ListView1
   주행기록보기 차례, ListView2
   
   'ListView1, 즉 참가자 선수 명단을 갱신하면 자동으로 현재 선택된 선수의 주행기록 현황(오른쪽부분)도 변경되게 해놨다.
   ListView1_ItemClick ListView1.ListItems.Item(차례)
End Sub

Private Sub Cmd2차보너스_Click()
   Dim 플래그 As Integer
   플래그 = 기록에서플래그얻기(차례, 주행차례)
   
   If ((플래그 And 이차보너스) <> 0) Then
      플래그 = 플래그 And (255 Xor 이차보너스)
   Else
      플래그 = 플래그 Or 이차보너스
   End If
   기록에플래그덮어씌우기 차례, 주행차례, 플래그
   
   '화면에 보이는 데이터 갱신
   참가자DB연결 ListView1
   주행기록보기 차례, ListView2
   
   'ListView1, 즉 참가자 선수 명단을 갱신하면 자동으로 현재 선택된 선수의 주행기록 현황(오른쪽부분)도 변경되게 해놨다.
   ListView1_ItemClick ListView1.ListItems.Item(차례)
End Sub

Private Sub Cmd주행시작_Click()
   주행시작
End Sub

Private Sub Cmd주행종료_Click()
   주행종료
End Sub

Private Sub Cmd주행포기_Click()
   경주시간정지
   
   Cmd차례정지.Enabled = True
   Cmd주행시작.Enabled = True
   Cmd기록삭제.Enabled = True
   Cmd주행종료.Enabled = False
   Cmd주행포기.Enabled = False
      
   경주포기지정
      
   사용시간추가 Get주행포기가중치
   
   기록추가 차례, Get경주시간, 0
   참가자보기갱신
   
   LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "] 차례 " + Str(Val(TxtNumOfRace.Text)) + "번째 주행을 포기하셨습니다."
   
   경주시간초기화
   Timer1_Timer
   
   If Val(TxtNumOfRace.Text) = Get최대주행횟수 Then
      MsgBox "최대주행횟수인 " & Str(Get최대주행횟수) & "회를 채웠습니다.", vbApplicationModal Or vbOKOnly
      Cmd차례정지_Click
   Else
      경기3초대기
   End If
End Sub

Private Sub Cmd차례시작_Click()
   If 차례 = 0 Then
      MsgBox "준비할 참가자를 선택하세요"
   Else
      주행횟수 = Val(TxtNumOfRace.Text)
      If 주행횟수 >= Get최대주행횟수 Then
         MsgBox "이미 최대주행횟수인 " & Str(Get최대주행횟수) & "회를 채웠습니다.", vbApplicationModal Or vbOKOnly
      Else
         ListView1.Enabled = False
         Cmd차례시작.Enabled = False
         Cmd차례정지.Enabled = True
         Cmd다음차례.Enabled = False
         Cmd주행시작.Enabled = True
         Cmd순서미루기.Enabled = True
         
         LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "] 출발함과 동시에 차례가 시작됩니다."
         사용시간시작
         사용시간정지
      End If
   End If
End Sub

Private Sub Cmd차례정지_Click()
   LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "] " & TxtRank.Text & "위로 차례가 끝났습니다."
   Set참가자사용시간 차례, Get사용시간
   
   ListView1.Enabled = True
   
   Cmd차례시작.Enabled = True
   Cmd차례정지.Enabled = False
   Cmd다음차례.Enabled = True
   Cmd기록삭제.Enabled = True
   Cmd주행시작.Enabled = False
   Cmd주행종료.Enabled = False
   Cmd주행포기.Enabled = False
   Cmd순서미루기.Enabled = False
   
   사용시간정지
   
   상태표시 "참가자 정보를 저장중입니다."
   참가자파일저장 참가자보관파일
   상태표시 ""
   
   참가자보기갱신
End Sub

Private Sub Form_Load()
   MainForm.Caption = MainForm.Caption & " " & App.Major & "." & App.Minor & "." & App.Revision
   
   규칙파일부르기 규칙보관파일
   통신환경부르기 통신환경보관파일
   통신설정적용 MSComm1
   
   If MSComm1.PortOpen = True Then
      StatusBar1.Panels(3).Text = "통신연결 성공"
   Else
      StatusBar1.Panels(3).Text = "통신연결 안됨"
   End If
   
   On Error GoTo LabelFileNotFound
   참가자파일부르기 참가자보관파일
   참가자보기갱신
   
   Exit Sub
LabelFileNotFound:
End Sub

Private Sub Form_Paint()
   StatusBar1.Panels(1).Text = 통신상태
   참가자보기갱신
End Sub

Private Sub Form_Unload(Cancel As Integer)
   상태표시 "종료전에 참가자 정보를 저장중입니다. (1/3)"
   참가자파일저장 참가자보관파일
   상태표시 "종료전에 통신환경설정을 저장중입니다. (2/3)"
   통신환경저장 통신환경보관파일
   상태표시 "종료전에 규칙환경설정을 저장중입니다. (3/3)"
   규칙파일저장 규칙보관파일
End Sub


Private Sub ListView1_ItemClick(ByVal Item As MSComctlLib.ListItem)
   TxtNum.Text = Val(Item.Text)
   TxtName.Text = Item.SubItems(1)
   TxtUni.Text = Item.SubItems(2)
   TxtRobotName.Text = Item.SubItems(3)
   TxtNumOfRace.Text = Item.SubItems(6)
      
   If (Val(Item.SubItems(4)) = 0) Then '순위가 없다면
      TxtRank.Text = "---"
   Else
      TxtRank.Text = Item.SubItems(4)
   End If
  
   '기존 차례 표시 제거
   ListView1.ListItems.Item(차례).ForeColor = &H0
   ListView1.ListItems.Item(차례).Bold = False
   
   차례 = Item.Index
   스크롤위치변경 ListView1.hwnd, 차례

   '표시
   ListView1.ListItems.Item(차례).ForeColor = &HFF
   ListView1.ListItems.Item(차례).Bold = True
   
   Set사용시간 Get참가자사용시간(차례)
   
   주행기록보기 차례, ListView2
   
   If (ListView2.ListItems.Count > 0) Then
      주행차례 = ListView2.ListItems.Count
   Else
      주행차례 = 0
      Frame3.Caption = "보너스"
      Label정지보너스.ForeColor = 0
      Label정지보너스.Caption = "없음"
      Label2차보너스.ForeColor = 0
      Label2차보너스.Caption = "없음"
   End If
      
   If 주행차례 > 0 Then ListView2_ItemClick ListView2.ListItems.Item(주행차례)
      
   If (Val(TxtNumOfRace.Text) > 0) Then
      Cmd정지보너스.Enabled = True
      Cmd2차보너스.Enabled = True
   Else
      Cmd정지보너스.Enabled = False
      Cmd2차보너스.Enabled = False
   End If
   
   '메시지 알림
   LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "] 차례입니다. 준비해주십시오."
End Sub

Private Sub ListView2_ItemClick(ByVal Item As MSComctlLib.ListItem)
   Dim 플래그 As Integer
   
   If Item.SubItems(2) <> "주행포기" Then
      Cmd2차보너스.Enabled = True
      Cmd정지보너스.Enabled = True
      Frame3.Caption = 주행차례 & "번째 주행 보너스 "
   Else
      Cmd2차보너스.Enabled = False
      Cmd정지보너스.Enabled = False
      Label정지보너스.ForeColor = 0
      Label정지보너스.Caption = "없음"
      Label2차보너스.ForeColor = 0
      Label2차보너스.Caption = "없음"
      Frame3.Caption = 주행차례 & "번째 보너스 없음"
   End If
   
   '표시
   ListView2.ListItems.Item(주행차례).ForeColor = &H0
   ListView2.ListItems.Item(주행차례).Bold = False
   
   주행차례 = Val(Item.Index)
   
   '표시
   ListView2.ListItems.Item(주행차례).ForeColor = &HFF0000
   ListView2.ListItems.Item(주행차례).Bold = True
   If Item.SubItems(2) = "주행포기" Then Exit Sub
         
   플래그 = 기록에서플래그얻기(차례, Item.Index)
   
   If (플래그 And 정지보너스) <> 0 Then
      Label정지보너스.ForeColor = &HFF0000
      Label정지보너스.Caption = "획득"
   Else
      Label정지보너스.ForeColor = 0
      Label정지보너스.Caption = "없음"
   End If
   
   If (플래그 And 이차보너스) <> 0 Then
      Label2차보너스.ForeColor = &HFF0000
      Label2차보너스.Caption = "획득"
   Else
      Label2차보너스.ForeColor = 0
      Label2차보너스.Caption = "없음"
   End If
End Sub

Private Sub Menu개죽이_Click()
   frmAbout.Show 1
End Sub

Private Sub Menu규칙설정_Click()
   RuleCfgForm.Show 1
   규칙파일저장 규칙보관파일
End Sub

Private Sub Menu종료_Click()
   Unload Me
End Sub

Private Sub Menu참가자등록_Click()
   사용시간정지
   RegDialog.Show 1
   MainForm.Refresh
   참가자보기갱신
End Sub

Private Sub Menu초기화_Click()
   Dim 선택 As Integer
   선택 = MsgBox("참가자에 대한 모든 데이터가 삭제됩니다. 그래도 하시겠습니까?", vbYesNo, "경고")
      
   If 선택 = vbYes Then
      '파일내용 초기화
      Open 참가자보관파일 For Output As #1: Close #1
      차례 = 0
      참가자DB초기화
      사용시간정지
      MsgBox "모든 데이터가 삭제되었습니다.", vbApplicationModal And vbOKOnly, "메세지"
      ListView1.ListItems.Clear
      ListView2.ListItems.Clear
   End If
End Sub

Private Sub MenuRS232_Click()
   RS232CfgForm.Show 1
   
   통신설정적용 MSComm1
   If MSComm1.PortOpen = True Then
      StatusBar1.Panels(3).Text = "통신연결 성공"
   Else
      StatusBar1.Panels(3).Text = "통신연결 안됨"
   End If
   
   통신환경저장 통신환경보관파일
   MainForm.Refresh
End Sub

Private Sub MSComm1_OnComm()
   Dim RvChar As String * 1
   Select Case MSComm1.CommEvent
      '받았을 경우
      Case comEvReceive
         RvChar = MSComm1.Input
         
         '센서값 Status Bar에 표시 (디버깅)
         StatusBar1.Panels(3).Text = "받은 데이터 : " & RvChar & " (" & Hex$(Asc(RvChar)) & ")"
         
         If Asc(RvChar) = 출발신호 Then
            StatusBar1.Panels(3).Text = StatusBar1.Panels(3).Text & " ← 출발신호확인"
            If Cmd차례시작.Enabled = False And Get경주중 = False Then
               주행시작
            End If
         End If
         If Asc(RvChar) = 도착신호 Then
            StatusBar1.Panels(3).Text = StatusBar1.Panels(3).Text & " ← 도착신호확인"
            If Get경주중 = True Then
               주행종료
            End If
         End If
   End Select
End Sub

Private Sub Timer1_Timer()
   시간콜백함수
   'StatusBar1.Panels(2) = 차례 & "   " & Get사용시간
   
   StatusBar1.Panels(2) = DateTime.Now
   If (Get제한시간 * 1000# - Get사용시간 > 0) Then
      'Get제한시간은 기본단위가 초단위, Get사용시간은 1MilliSec가 기본단위라서 제한시간에 100을 곱함
      Lab사용시간.Caption = 시간형태로변환(Get제한시간 * 1000# - Get사용시간)
      Lab경주시간.Caption = 시간형태로변환(Get경주시간)
   Else
      Lab사용시간.Caption = 시간형태로변환(0)
      Lab경주시간.Caption = 시간형태로변환(0)
      If (Get사용중 = True) Then
         If (Get경주중 = True) Then
            경주시간정지
            경주시간초기화
         End If
         
         사용시간지정 Get제한시간 * 1000#
         Cmd차례정지_Click
         LabMsg.Caption = TxtNum.Text & "번 [" & TxtRobotName.Text & "]의 사용시간이 다 되었습니다."
      End If
   End If
End Sub

