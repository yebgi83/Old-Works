VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6000
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8670
   LinkTopic       =   "Form1"
   ScaleHeight     =   6000
   ScaleWidth      =   8670
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   120
      Top             =   120
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    HookStart
    If g_hHook = 0 Then
        MsgBox "Making handle to hook is failed."
        End
    Else
        MsgBox "Hooking handle is maked."
    End If
End Sub

Private Sub Form_Terminate()
    HookEnd
End Sub

Private Sub Timer1_Timer()
    Form1.Caption = "ID: " & g_hHook & "    "
    Form1.Caption = Form1.Caption & "Code: " & g_Code & "    "
    Form1.Caption = Form1.Caption & "Code: " & g_wParam & "    "
    Form1.Caption = Form1.Caption & "Code: " & g_lParam & "    "
End Sub
