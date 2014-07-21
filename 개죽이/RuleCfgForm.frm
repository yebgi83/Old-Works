VERSION 5.00
Begin VB.Form RuleCfgForm 
   BorderStyle     =   1  '단일 고정
   Caption         =   "규칙 설정"
   ClientHeight    =   4815
   ClientLeft      =   7830
   ClientTop       =   5880
   ClientWidth     =   3600
   Icon            =   "RuleCfgForm.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   4815
   ScaleWidth      =   3600
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  '소유자 가운데
   Begin VB.Frame Frame4 
      Caption         =   "사용시간 차감"
      Height          =   735
      Left            =   120
      TabIndex        =   20
      Top             =   3360
      Width           =   3375
      Begin VB.TextBox Txt주행포기 
         Height          =   270
         Left            =   1440
         TabIndex        =   21
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "(밀리초)"
         Height          =   180
         Index           =   5
         Left            =   2520
         TabIndex        =   23
         Top             =   285
         Width           =   690
      End
      Begin VB.Label Label2 
         Caption         =   "손접촉반칙"
         Height          =   255
         Index           =   5
         Left            =   120
         TabIndex        =   22
         Top             =   285
         Width           =   1215
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "벌점"
      Height          =   735
      Left            =   120
      TabIndex        =   16
      Top             =   2520
      Width           =   3375
      Begin VB.TextBox Txt순서미루기 
         Height          =   270
         Left            =   1440
         TabIndex        =   17
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Label2 
         Caption         =   "순서미루기"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   19
         Top             =   285
         Width           =   1215
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "(밀리초)"
         Height          =   180
         Index           =   4
         Left            =   2520
         TabIndex        =   18
         Top             =   285
         Width           =   690
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "보너스"
      Height          =   1095
      Left            =   120
      TabIndex        =   9
      Top             =   1320
      Width           =   3375
      Begin VB.TextBox Txt2차보너스 
         Height          =   270
         Left            =   1440
         TabIndex        =   13
         Top             =   675
         Width           =   975
      End
      Begin VB.TextBox Txt정지보너스 
         Height          =   270
         Left            =   1440
         TabIndex        =   10
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Label2 
         Caption         =   "2차보너스"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   15
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "(밀리초)"
         Height          =   180
         Index           =   3
         Left            =   2520
         TabIndex        =   14
         Top             =   720
         Width           =   690
      End
      Begin VB.Label Label2 
         Caption         =   "정지보너스"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   12
         Top             =   285
         Width           =   1215
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "(밀리초)"
         Height          =   180
         Index           =   2
         Left            =   2520
         TabIndex        =   11
         Top             =   285
         Width           =   690
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "기본 규칙"
      Height          =   1095
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   3375
      Begin VB.TextBox Txt제한시간 
         Height          =   270
         Left            =   1440
         TabIndex        =   6
         Top             =   240
         Width           =   1215
      End
      Begin VB.TextBox Txt최대주행횟수 
         Height          =   270
         Left            =   1440
         TabIndex        =   3
         Top             =   675
         Width           =   1215
      End
      Begin VB.Label Label2 
         Caption         =   "제한시간"
         Height          =   255
         Index           =   4
         Left            =   120
         TabIndex        =   8
         Top             =   285
         Width           =   1215
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "(초)"
         Height          =   180
         Index           =   0
         Left            =   2760
         TabIndex        =   7
         Top             =   285
         Width           =   330
      End
      Begin VB.Label Label2 
         Caption         =   "최대주행횟수"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   5
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "(회)"
         Height          =   180
         Index           =   1
         Left            =   2760
         TabIndex        =   4
         Top             =   720
         Width           =   330
      End
   End
   Begin VB.CommandButton Cmd취소 
      Caption         =   "취소"
      Height          =   495
      Left            =   1920
      TabIndex        =   1
      Top             =   4200
      Width           =   1215
   End
   Begin VB.CommandButton Cmd적용 
      Caption         =   "적용"
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   4200
      Width           =   1215
   End
End
Attribute VB_Name = "RuleCfgForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Cmd적용_Click()
   Set제한시간 Val(Txt제한시간.Text)
   Set최대주행횟수 Val(Txt최대주행횟수.Text)
   Set정지보너스가중치 Val(Txt정지보너스.Text)
   Set2차보너스가중치 Val(Txt2차보너스.Text)
   Set주행포기가중치 Val(Txt주행포기.Text)
   Set순서미루기가중치 Val(Txt순서미루기.Text)
   Unload Me
End Sub

Private Sub Cmd취소_Click()
   Unload Me
End Sub

Private Sub Form_Load()
   Txt제한시간.Text = Get제한시간
   Txt최대주행횟수.Text = Get최대주행횟수
   Txt정지보너스.Text = Get정지보너스가중치
   Txt2차보너스.Text = Get2차보너스가중치
   Txt주행포기.Text = Get주행포기가중치
   Txt순서미루기.Text = Get순서미루기가중치
End Sub

Sub 숫자유지(Text As String, 부호 As Integer)
   If Text <> "0" And Text <> "" Then
      Text = Val(Text)
   End If
   If 부호 = -1 Then
      If Val(Text) > 0 Then
         Text = RTrim$(Str(Val(Text) * -1))
      End If
   End If
End Sub

Private Sub Txt2차보너스_Change()
   숫자유지 Txt2차보너스, -1
End Sub

Private Sub Txt주행포기_Change()
   숫자유지 Txt주행포기, 1
End Sub

Private Sub Txt순서미루기_Change()
   숫자유지 Txt순서미루기, 1
End Sub

Private Sub Txt정지보너스_Change()
   숫자유지 Txt정지보너스, -1
End Sub

Private Sub Txt제한시간_Change()
   숫자유지 Txt제한시간, 1
End Sub

Private Sub Txt최대주행횟수_Change()
   숫자유지 Txt최대주행횟수, 1
End Sub
