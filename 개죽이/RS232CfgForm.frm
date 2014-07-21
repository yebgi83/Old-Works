VERSION 5.00
Begin VB.Form RS232CfgForm 
   BorderStyle     =   1  '단일 고정
   Caption         =   "통신 환경 설정"
   ClientHeight    =   3195
   ClientLeft      =   7830
   ClientTop       =   7050
   ClientWidth     =   3450
   Icon            =   "RS232CfgForm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Moveable        =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   3450
   StartUpPosition =   1  '소유자 가운데
   Begin VB.CommandButton Cmd취소 
      Caption         =   "취소"
      Height          =   495
      Left            =   1800
      TabIndex        =   13
      Top             =   2520
      Width           =   1215
   End
   Begin VB.CommandButton Cmd적용 
      Caption         =   "적용"
      Height          =   495
      Left            =   360
      TabIndex        =   12
      Top             =   2520
      Width           =   1215
   End
   Begin VB.ComboBox Combo흐름제어 
      Height          =   300
      Left            =   1560
      TabIndex        =   11
      Top             =   1980
      Width           =   1575
   End
   Begin VB.ComboBox Combo패리티비트 
      Height          =   300
      Left            =   1560
      TabIndex        =   10
      Top             =   1620
      Width           =   1575
   End
   Begin VB.ComboBox Combo정지비트 
      Height          =   300
      Left            =   1560
      TabIndex        =   9
      Top             =   1260
      Width           =   1575
   End
   Begin VB.ComboBox Combo데이터비트 
      Height          =   300
      Left            =   1560
      TabIndex        =   8
      Top             =   900
      Width           =   1575
   End
   Begin VB.ComboBox Combo통신속도 
      Height          =   300
      Left            =   1560
      TabIndex        =   7
      Top             =   540
      Width           =   1575
   End
   Begin VB.ComboBox Combo포트번호 
      Height          =   300
      Left            =   1560
      TabIndex        =   6
      Top             =   200
      Width           =   1575
   End
   Begin VB.Label Label1 
      Caption         =   "흐름 제어"
      Height          =   255
      Index           =   5
      Left            =   360
      TabIndex        =   5
      Top             =   2040
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "패리티 비트"
      Height          =   255
      Index           =   4
      Left            =   360
      TabIndex        =   4
      Top             =   1680
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "정지 비트"
      Height          =   255
      Index           =   3
      Left            =   360
      TabIndex        =   3
      Top             =   1320
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "데이터 비트"
      Height          =   255
      Index           =   2
      Left            =   360
      TabIndex        =   2
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "통신 속도"
      Height          =   255
      Index           =   1
      Left            =   360
      TabIndex        =   1
      Top             =   600
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "포트 번호"
      Height          =   255
      Index           =   0
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "RS232CfgForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Cmd적용_Click()
   Set포트 Combo포트번호.ListIndex
   Set속도 Combo통신속도.ListIndex
   Set데이터비트 Combo데이터비트.ListIndex
   Set정지비트 Combo정지비트.ListIndex
   Set패리티 Combo패리티비트.ListIndex
   Set흐름제어 Combo흐름제어.ListIndex
   Unload Me
End Sub

Private Sub Cmd취소_Click()
   Unload Me
End Sub

Private Sub Form_Load()
   Combo포트번호.AddItem "COM1"
   Combo포트번호.AddItem "COM2"
   Combo포트번호.AddItem "COM3"
   Combo포트번호.AddItem "COM4"
   Combo포트번호.AddItem "COM5"
   Combo포트번호.AddItem "COM6"
   Combo포트번호.AddItem "COM7"
   Combo포트번호.AddItem "COM8"
   Combo포트번호.AddItem "COM9"
   Combo포트번호.AddItem "COM10"
   
   Combo통신속도.AddItem "4800"
   Combo통신속도.AddItem "7200"
   Combo통신속도.AddItem "9600"
   Combo통신속도.AddItem "14400"
   Combo통신속도.AddItem "19200"
   Combo통신속도.AddItem "38400"
   Combo통신속도.AddItem "57600"
   Combo통신속도.AddItem "115200"
   Combo통신속도.AddItem "128000"
   
   Combo데이터비트.AddItem "7"
   Combo데이터비트.AddItem "8"
   
   Combo정지비트.AddItem "1"
   Combo정지비트.AddItem "1.5"
   Combo정지비트.AddItem "2"
   
   Combo패리티비트.AddItem "없음"
   Combo패리티비트.AddItem "홀수"
   Combo패리티비트.AddItem "짝수"
   
   Combo흐름제어.AddItem "Xon / Xoff"
   Combo흐름제어.AddItem "하드웨어"
   Combo흐름제어.AddItem "없음"
   
   Combo포트번호.ListIndex = Get포트
   Combo통신속도.ListIndex = Get속도
   Combo데이터비트.ListIndex = Get데이터비트
   Combo정지비트.ListIndex = Get정지비트
   Combo패리티비트.ListIndex = Get패리티
   Combo흐름제어.ListIndex = Get흐름제어
End Sub
