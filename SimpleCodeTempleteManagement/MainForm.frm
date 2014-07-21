VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form MainForm 
   Caption         =   "Templete Code Manager"
   ClientHeight    =   13500
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   21585
   Icon            =   "MainForm.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   13500
   ScaleWidth      =   21585
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command6 
      Caption         =   "Send to Notepad"
      Height          =   495
      Left            =   13800
      TabIndex        =   13
      Top             =   120
      Width           =   1695
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Copy to Clipboard"
      Height          =   495
      Left            =   12000
      TabIndex        =   9
      Top             =   120
      Width           =   1695
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Save"
      Height          =   495
      Left            =   10200
      TabIndex        =   8
      Top             =   120
      Width           =   1695
   End
   Begin VB.Frame Frame2 
      Caption         =   "Selected Tempelte Code"
      Height          =   12735
      Left            =   10200
      TabIndex        =   6
      Top             =   720
      Width           =   11295
      Begin VB.TextBox TitleText 
         Height          =   375
         Left            =   600
         TabIndex        =   10
         Top             =   240
         Width           =   10575
      End
      Begin VB.TextBox TempleteText 
         Height          =   11655
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   7
         Top             =   960
         Width           =   11055
      End
      Begin VB.Label Label2 
         Caption         =   "Content"
         Height          =   495
         Left            =   120
         TabIndex        =   12
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "Title"
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   240
         Width           =   375
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Templete Code List "
      Height          =   12735
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   9975
      Begin VB.CommandButton Command4 
         Cancel          =   -1  'True
         Caption         =   "Find "
         Height          =   375
         Left            =   8640
         TabIndex        =   4
         Top             =   240
         Width           =   1215
      End
      Begin VB.TextBox FindText 
         Height          =   375
         Left            =   120
         TabIndex        =   3
         Top             =   240
         Width           =   8415
      End
      Begin ComctlLib.ListView TempleteListView 
         Height          =   11895
         Left            =   120
         TabIndex        =   5
         Top             =   720
         Width           =   9735
         _ExtentX        =   17171
         _ExtentY        =   20981
         View            =   3
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         _Version        =   327682
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   1
         BeginProperty ColumnHeader(1) {0713E8C7-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Text            =   "Templete Name"
            Object.Width           =   25400
         EndProperty
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Remove selected templete"
      Height          =   495
      Left            =   1920
      TabIndex        =   1
      Top             =   120
      Width           =   1695
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Create new templete"
      Height          =   495
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1695
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Clicked_TempleteIdx As Integer
    
Private Sub Command1_Click()
    CreateNewTemplete TempleteListView
End Sub

Private Sub Command2_Click()
    If TempleteListView.ListItems.Count > 0 Then
       RemoveCodeTemplete TempleteListView.SelectedItem.Index, TempleteListView
       Clicked_TempleteIdx = 0
    End If
End Sub

Private Sub Command3_Click()
    Clipboard.Clear
    Clipboard.SetText (RTrim$(TempleteText.Text))
End Sub

Private Sub Command4_Click()
    Dim Idx As Integer
    
    If TempleteListView.SelectedItem Is Nothing Then
        IdxStart% = 1
    Else
        IdxStart% = TempleteListView.SelectedItem.Index + 1
    End If
    
    For Idx = IdxStart% To TempleteListView.ListItems.Count
        If InStr(TempleteListView.ListItems(Idx).Text, FindText.Text) > 0 Then
           Exit For
        End If
    Next Idx
    
    If Idx = TempleteListView.ListItems.Count + 1 Then
        MsgBox "Data is not found"
    Else
        TempleteListView.ListItems(Idx).Selected = True
    End If
End Sub

Private Sub Command5_Click()
    If Not (TempleteListView.SelectedItem Is Nothing) Then
       SaveCodeTemplete TempleteListView.SelectedItem.Index, TitleText.Text, TempleteText.Text
       TempleteListView.ListItems(TempleteListView.SelectedItem.Index).Text = TitleText.Text
    End If
End Sub

Private Sub Command6_Click()
    If Not (TempleteListView.SelectedItem Is Nothing) Then
       OpenTempleteWithNotepad TempleteListView.SelectedItem.Index
    End If
End Sub

Private Sub Form_Load()
    GetCodeTempletesList
    CodeTempletesIntoListView TempleteListView
    MainForm.Caption = App.Title + " " + Trim$(Str$(App.Major)) + "." + Trim$(Str$(App.Minor)) + "." + Trim$(Str$(App.Revision))
End Sub

Private Sub TempleteListView_ItemClick(ByVal Item As ComctlLib.ListItem)
    Dim Title As String
    Dim Templete As String
    
    GetCodeTemplete Item.Index, Title, Templete
    TitleText.Text = Title
    TempleteText.Text = Templete
End Sub
