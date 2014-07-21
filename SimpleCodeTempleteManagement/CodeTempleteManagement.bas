Attribute VB_Name = "Module1"
Public Const MAX_TEMPLETE_NUMBER = 10000

Type CodeTemplete
    Title As String
End Type

Public NumOfCodeTemplete As Integer
Public CodeTempleteArray(MAX_TEMPLETE_NUMBER) As CodeTemplete

Function IndexToCustomizeFileString(Idx As Integer) As String
    IndexToCustomizeFileString = String$(Len(Trim$(Str$(MAX_TEMPLETE_NUMBER))) - Len(Trim$(Str$(Idx))), "0") & Trim$(Str$(Idx))
End Function

Sub GetCodeTempletesList()
    Dim Idx As Integer
    Dim LoadFileName As String
    Dim LoadLine As String
    
    For Idx = 1 To MAX_TEMPLETE_NUMBER
        LoadFileName = IndexToCustomizeFileString(Idx)
        
        'Is file found?
        Open ProgramDirectory + LoadFileName + ".txt" For Binary As #1
        If LOF(1) = 0 Then
           Close #1
           Kill ProgramDirectory + LoadFileName + ".txt"
           Exit For
        Else
           Close #1
           Open ProgramDirectory + LoadFileName + ".txt" For Input As #1
                Line Input #1, LoadLine
                If Left$(LoadLine, 7) = "[Title]" Then
                   CodeTempleteArray(Idx).Title = Right$(LoadLine, Len(LoadLine) - 7)
                End If
           Close #1
        End If
    Next Idx
    NumOfCodeTemplete = Idx - 1
End Sub

Sub CodeTempletesIntoListView(Target As ListView)
    Dim Idx As Integer
    Dim NewRecord As ListItem
    
    Target.ListItems.Clear
    For Idx = 1 To NumOfCodeTemplete
        Set NewRecord = Target.ListItems.Add(Idx, , CodeTempleteArray(Idx).Title, 0, 0)
    Next Idx
    Target.Refresh
End Sub

Sub SaveCodeTemplete(Idx As Integer, Title As String, Buffer As String)
    Open ProgramDirectory + IndexToCustomizeFileString(Idx) + ".txt" For Output As #1
        Print #1, "[Title]" + Title
        Print #1, Buffer
    Close #1
    CodeTempleteArray(Idx).Title = Title
End Sub

Sub GetCodeTemplete(Idx As Integer, ByRef TitleForGetting As String, ByRef BufferForGetting As String)
    Dim LoadLine As String
    
    TitleForGetting = ""
    BufferForGetting = ""
    Open ProgramDirectory + IndexToCustomizeFileString(Idx) + ".txt" For Input As #1
        Do Until EOF(1)
            Line Input #1, LoadLine
            If Left$(LoadLine, 7) = "[Title]" Then
               TitleForGetting = Right$(LoadLine, Len(LoadLine) - 7)
            Else
               BufferForGetting = BufferForGetting + LoadLine + Chr$(13) + Chr$(10)
            End If
        Loop
    Close #1
End Sub

Sub CreateNewTemplete(Target As ListView)
    Dim CreateFileName As String

    NumOfCodeTemplete = NumOfCodeTemplete + 1
    CreateFileName = ProgramDirectory + IndexToCustomizeFileString(NumOfCodeTemplete) + ".txt"
    
    Open CreateFileName For Binary As #1
    If LOF(1) = 0 Then
       Close #1
    Else
       Close #1
       Kill CreateFileName
    End If
    
    With CodeTempleteArray(NumOfCodeTemplete)
        .Title = "<" + Date$ + " / " + Time$ + "> No Title"
        Open CreateFileName For Output As #1: Print #1, "[Title]" + .Title: Close #1
    End With
    
    Dim NewRecord As ListItem
    Set NewRecord = Target.ListItems.Add(NumOfCodeTemplete, , CodeTempleteArray(NumOfCodeTemplete).Title, 0, 0)
End Sub


Sub RemoveCodeTemplete(Idx As Integer, Target As ListView)
    Kill ProgramDirectory + IndexToCustomizeFileString(Idx) + ".txt"
      
    For Count% = Idx + 1 To NumOfCodeTemplete
        Name ProgramDirectory + IndexToCustomizeFileString(Count%) + ".txt" As ProgramDirectory + IndexToCustomizeFileString(Count% - 1) + ".txt"
        CodeTempleteArray(Count% - 1) = CodeTempleteArray(Count%)
    Next Count%
    CodeTempleteArray(NumOfCodeTemplete).Title = ""
    NumOfCodeTemplete = NumOfCodeTemplete - 1
    
    Target.ListItems.Remove Idx
End Sub

Sub OpenTempleteWithNotepad(Idx As Integer)
    LoadFileName$ = ProgramDirectory + IndexToCustomizeFileString(Idx) + ".txt"
    Shell "Notepad " + LoadFileName$, vbNormalFocus
End Sub
    
    
    
 
