VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7245
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11595
   LinkTopic       =   "Form1"
   ScaleHeight     =   7245
   ScaleWidth      =   11595
   StartUpPosition =   3  'Windows �⺻��
   Begin VB.CommandButton Command3 
      Caption         =   "Ʈ���� ����"
      Height          =   495
      Left            =   2760
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "�ؽ�Ʈ ����"
      Height          =   495
      Left            =   1440
      TabIndex        =   2
      Top             =   120
      Width           =   1215
   End
   Begin ComctlLib.ListView ListView1 
      Height          =   6495
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   11415
      _ExtentX        =   20135
      _ExtentY        =   11456
      View            =   3
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "�ڵ�"
         Object.Width           =   1764
      EndProperty
      BeginProperty ColumnHeader(2) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   1
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "������ �̸�"
         Object.Width           =   3528
      EndProperty
      BeginProperty ColumnHeader(3) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   2
         Key             =   ""
         Object.Tag             =   ""
         Text            =   "����"
         Object.Width           =   17639
      EndProperty
      BeginProperty ColumnHeader(4) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
         SubItemIndex    =   3
         Key             =   ""
         Object.Tag             =   ""
         Text            =   ""
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.CommandButton Command1 
      Caption         =   "�ҷ�����"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
   LoadW3T "C:\����.w3t"
   SendItemToListBox ListView1
   Form1.Caption = Str$(ListView1.ListItems.Count) + "���� �����Ͱ� �ֽ��ϴ�."
End Sub

Private Sub Command2_Click()
   SaveItemList "C:\����Ʈ.txt"
End Sub

Private Sub Command3_Click()
   MakeCombiList "C:\����.txt"
End Sub

Private Sub Form_Load()
   
   InitializeW3TIdentifier
End Sub

