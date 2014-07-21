VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form RegDialog 
   BorderStyle     =   3  '크기 고정 대화 상자
   Caption         =   "참가자 등록"
   ClientHeight    =   6090
   ClientLeft      =   6120
   ClientTop       =   5550
   ClientWidth     =   8805
   Icon            =   "RegDialog.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   6090
   ScaleWidth      =   8805
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '소유자 가운데
   Begin VB.CommandButton EditBtn 
      Caption         =   "편집"
      Height          =   375
      Left            =   6120
      TabIndex        =   10
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton MoveFirstBtn 
      Caption         =   "맨 위로 이동"
      Height          =   375
      Left            =   7440
      TabIndex        =   9
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton DeleteBtn 
      Caption         =   "삭제"
      Height          =   375
      Left            =   7440
      TabIndex        =   1
      Top             =   120
      Width           =   1215
   End
   Begin VB.TextBox TxtRobotName 
      Height          =   315
      Left            =   3720
      TabIndex        =   3
      Top             =   200
      Width           =   2295
   End
   Begin VB.TextBox TxtName 
      Height          =   315
      Left            =   600
      TabIndex        =   2
      Top             =   200
      Width           =   2295
   End
   Begin VB.TextBox TxtUni 
      Height          =   315
      Left            =   600
      TabIndex        =   4
      Top             =   600
      Width           =   5415
   End
   Begin VB.CommandButton RegisterBtn 
      Caption         =   "등록"
      Height          =   375
      Left            =   6120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin MSComctlLib.ListView ListView1 
      Height          =   4935
      Left            =   120
      TabIndex        =   8
      Top             =   1080
      Width           =   8535
      _ExtentX        =   15055
      _ExtentY        =   8705
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
         Object.Width           =   1411
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "학교"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "로봇명"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   4
         Text            =   "순위"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(6) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   5
         Text            =   "최고기록"
         Object.Width           =   2170
      EndProperty
      BeginProperty ColumnHeader(7) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   6
         Text            =   "주행횟수"
         Object.Width           =   5292
      EndProperty
      BeginProperty ColumnHeader(8) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   7
         Text            =   "사용시간"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.Label Label1 
      Caption         =   "로봇명"
      Height          =   255
      Index           =   2
      Left            =   3120
      TabIndex        =   7
      Top             =   240
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "이름"
      Height          =   255
      Index           =   3
      Left            =   120
      TabIndex        =   6
      Top             =   240
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "학교"
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   5
      Top             =   645
      Width           =   615
   End
End
Attribute VB_Name = "RegDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim 첨자 As Integer
Dim 순번 As Integer

Sub 참가자보기갱신()
    참가자DB연결 ListView1
    
    If 첨자 > 0 And ListView1.ListItems.Count > 0 Then
       ListView1_ItemClick ListView1.ListItems.Item(첨자)
       스크롤위치변경 ListView1.hwnd, 첨자
    Else
       TxtName.Text = ""
       TxtUni.Text = ""
       TxtRobotName.Text = ""
    End If
End Sub

Private Sub DeleteBtn_Click()
    Dim 이름 As String
    Dim 로봇명 As String
    Dim 경고문구 As String
    
    If (ListView1.ListItems.Count = 0) Then Exit Sub
    
    이름 = TxtName.Text
    로봇명 = TxtRobotName.Text
    
    If 첨자 > 0 Then
       경고문구 = "선택된 [" & 순번 & "번 " & 이름 & "] 참가자를 삭제하시겠습니까?"
       If MsgBox(경고문구, vbOKCancel, "경고") = vbOK Then
          참가자삭제 첨자
          MsgBox "삭제하였습니다.", vbOKOnly, "메세지"
          
          참가자파일저장 참가자보관파일
          참가자보기갱신
       End If
    End If
End Sub

Private Sub EditBtn_Click()
    If (ListView1.ListItems.Count = 0) Then Exit Sub
        
    If 첨자 > 0 Then
       참가자배열수정 첨자, TxtName.Text, TxtRobotName.Text, TxtUni.Text
       
       MsgBox 순번 & "번 참가자의 편집을 완료했습니다.", vbOKOnly, "메세지"
       
       참가자파일저장 참가자보관파일
       참가자보기갱신
    End If
End Sub

Private Sub Form_Load()
    참가자파일부르기 참가자보관파일
    참가자DB연결 ListView1
End Sub
Private Sub ListView1_ItemClick(ByVal Item As MSComctlLib.ListItem)
    TxtName.Text = Item.SubItems(1)
    TxtUni.Text = Item.SubItems(2)
    TxtRobotName.Text = Item.SubItems(3)
    순번 = Item.Text
    첨자 = Item.Index
End Sub

Private Sub MoveFirstBtn_Click()
    Dim 이름 As String
    Dim 로봇명 As String
    Dim 경고문구 As String
    
    If (ListView1.ListItems.Count = 0) Then Exit Sub
    
    이름 = TxtName.Text
    로봇명 = TxtRobotName.Text
    
    If 첨자 > 0 Then
       경고문구 = "선택된 [" & 순번 & "번 " & 이름 & "] 참가자를 맨 위로 옮기겠습니까?"
       If MsgBox(경고문구, vbOKCancel, "경고") = vbOK Then
          맨위로이동 첨자
          MsgBox "이동을 완료했습니다.", vbOKOnly, "메세지"
          
          참가자파일저장 참가자보관파일
          참가자보기갱신
       End If
    End If
End Sub

Private Sub RegisterBtn_Click()
    Dim 이름 As String
    Dim 로봇명 As String
    Dim 학교 As String
    
    이름 = TxtName.Text
    로봇명 = TxtRobotName.Text
    학교 = TxtUni.Text
    참가자등록 이름, 로봇명, 학교
    
    참가자파일저장 참가자보관파일
    참가자보기갱신
End Sub

Private Sub TxtName_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
       TxtRobotName.SetFocus
    End If
End Sub

Private Sub TxtRobotName_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
       TxtUni.SetFocus
    End If
End Sub

Private Sub TxtUni_KeyPress(KeyAscii As Integer)
    If KeyAscii = 13 Then
       RegisterBtn_Click
       TxtName.SetFocus
    End If
End Sub
