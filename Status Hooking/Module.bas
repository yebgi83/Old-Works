Attribute VB_Name = "Module1"
Private Const WH_CALLWNDPROC = 4
Private Const WH_CALLWNDPROCRET = 12
Private Const WH_CBT = 5
Private Const WH_FOREGROUNDIDLE = 12
Private Const WH_GETMESSAGE = 3
Private Const WH_JOURNALPLAYBACK = 1
Private Const WH_JOURNALRECORD = 0
Private Const WH_KEYBOARD = 2
Private Const WH_KEYBOARD_LL = 13
Private Const WH_MOUSE = 7
Private Const WH_MOUSE_LL = 14
Private Const WH_MSGFILTER = -1
Private Const WH_SHELL = 10
Private Const WH_SYSMSGFILTER = 6

Private Declare Function SetWindowsHookEx Lib "user32" Alias "SetWindowsHookExA" (ByVal idHook As Long, ByVal lpfn As Long, ByVal hmod As Long, ByVal dwThreadId As Long) As Long
Private Declare Function UnhookWindowsHookEx Lib "user32" (ByVal hHook As Long) As Long
Private Declare Function CallNextHookEx Lib "user32" (ByVal hHook As Long, ByVal ncode As Long, ByVal wParam As Long, lParam As Any) As Long
Private Declare Function GetModuleHandle Lib "kernel32" Alias "GetModuleHandleA" (ByVal lpModuleName As String) As Long

Public g_hHook As Long
Public g_Code As Integer
Public g_wParam As Long
Public g_lParam As Long

Public Sub HookStart()
    g_hHook = SetWindowsHookEx(WH_CALLWNDPROCRET, AddressOf GetMsgProc, App.hInstance, 0)
End Sub

Public Sub HookEnd()
    UnhookWindowsHookEx g_hHook
End Sub

Public Function GetMsgProc(ByVal Code As Long, ByVal wParam As Long, lParam As Long) As Long
    '첫번째, 두번째에 ByVal이 없을 때 오류 발생, 왜 파라미터에 ByVal을 넣어야만 정상적으로 작동이 되는지 모르겠음. (생각해 봐야함)

    'Add code here
    g_Code = Code
    g_wParam = wParam
    g_lParam = lParam
    
    'GetMsgProc = 1
    GetMsgProc = CallNextHookEx(g_hHook, Code, wParam, lParam)
End Function


