Attribute VB_Name = "Module1"
Const 최대참가자 = 1000
Const NOTTHING = 0
Const MINIMUM = 200000000#
Const 문자열길이 = 64
Const 주행기록길이 = 1000
Const 기록데이터크기 = 5

Type 참가자서식
    순번     As Integer
    이름     As String * 문자열길이
    로봇명   As String * 문자열길이
    학교     As String * 문자열길이
    순위     As Integer
    주행횟수 As Integer
    최고기록 As Long
    주행기록 As String * 주행기록길이
    사용시간 As Long
End Type

Dim 참가자(최대참가자) As 참가자서식
Dim 누적순번           As Integer
Dim 참가인원           As Integer

Sub 참가자배열수정(첨자 As Integer, 이름 As String, 로봇명 As String, 학교 As String)
    n = 첨자
    참가자(n).이름 = 이름
    참가자(n).로봇명 = 로봇명
    참가자(n).학교 = 학교
End Sub

'참가자를 특정 배열 첨자에 입력한다
Sub 참가자배열입력(첨자 As Integer, 순번 As Integer, 이름 As String, 로봇명 As String, 학교 As String, 순위 As Integer, 주행횟수 As Integer, 최고기록 As Integer, 주행기록 As String, 사용시간 As Long)
    n = 첨자
    참가자(n).순번 = 순번
    참가자(n).이름 = 이름
    참가자(n).로봇명 = 로봇명
    참가자(n).학교 = 학교
    참가자(n).순위 = 순위
    참가자(n).주행횟수 = 주행횟수
    참가자(n).최고기록 = 최고기록
    참가자(n).주행기록 = 주행기록
    참가자(n).사용시간 = 사용시간
End Sub

'참가자DB를 초기화한다.
Sub 참가자DB초기화()
    Dim i As Integer
    
    참가인원 = 0
    For i = 1 To 최대참가자
        참가자배열입력 i, i, "", "", "", 0, 0, 0, "", 0
    Next i
End Sub

'참가자를 참가자DB에 추가한다.
Sub 참가자등록(이름 As String, 로봇명 As String, 학교 As String)
    누적순번 = 누적순번 + 1
    참가인원 = 참가인원 + 1 '참가인원 한명 추가
    
    '참가자 등록
    참가자배열입력 참가인원, 누적순번, 이름, 로봇명, 학교, 0, 0, 0, "", 0
End Sub

Sub 참가자삭제(첨자 As Integer)
    Dim i As Integer
    
    Dim 순번     As Integer
    Dim 이름     As String * 문자열길이
    Dim 로봇명   As String * 문자열길이
    Dim 학교     As String * 문자열길이
    Dim 순위     As Integer
    Dim 주행횟수 As Integer
    Dim 최고기록 As Integer
    Dim 주행기록 As String * 주행기록길이
    Dim 사용시간 As Long
    
    For i = 첨자 To 참가인원 - 1
        순번 = 참가자(i + 1).순번
        이름 = 참가자(i + 1).이름
        로봇명 = 참가자(i + 1).로봇명
        학교 = 참가자(i + 1).학교
        순위 = 참가자(i + 1).순위
        주행횟수 = 참가자(i + 1).주행횟수
        최고기록 = 참가자(i + 1).최고기록
        주행기록 = 참가자(i + 1).주행기록
        사용시간 = 참가자(i + 1).사용시간
        참가자배열입력 i, 순번, 이름, 로봇명, 학교, 순위, 주행횟수, 최고기록, 주행기록, 사용시간
    Next i
    
    참가자배열입력 참가인원, 0, "", "", "", 0, 0, 0, "", 0
    참가인원 = 참가인원 - 1
    
    '순위 갱신
    For i = 1 To 참가인원
        순위계산 i
    Next i
End Sub

Sub 참가자파일저장(파일명 As String)
    '파일 초기화
    Open 파일명 For Output As #1: Close #1
    
    '파일 저장
    Open 파일명 For Binary As #1
        Put #1, , 누적순번
        For i = 1 To 참가인원
            Put #1, , 참가자(i)
        Next i
    Close #1
End Sub

Sub 참가자파일부르기(파일명 As String)
    On Error GoTo FileNotFound
    
    '참가자 명단 초기화
    참가자DB초기화
    
    
    '파일 부른다.
    Open 파일명 For Binary As #1
    Get #1, , 누적순번
    Do
        If LOF(1) <= Loc(1) Then Exit Do
        참가인원 = 참가인원 + 1
        Get #1, , 참가자(참가인원)
    Loop
    Close #1
FileNotFound:
End Sub

Function 시간형태로변환(Count As Long) As String
    Dim Min As Integer
    Dim Sec As Integer
    Dim MSec As Integer
    Dim TempCount As Long
    
    'Call by reference효과를 방지
    TempCount = Count
    
    If TempCount = 경주포기 Then
       시간형태로변환 = "---------"
       Exit Function
    End If
    
    '초.시.밀리세컨으로 분리
    Min = Int(TempCount / 60000#)
    TempCount = TempCount Mod (60000#)
    
    Sec = Int(TempCount / 1000)
    TempCount = TempCount Mod 1000
    
    MSec = TempCount
    
    '문자열로 변환 합체
    StrMin$ = LTrim$(Min)
    If Len(StrMin$) < 2 Then StrMin$ = "0" + StrMin$
    
    StrSec$ = LTrim$(Sec)
    If Len(StrSec$) < 2 Then StrSec$ = "0" + StrSec$
    
    StrMSec$ = LTrim$(MSec)
    If Len(StrMSec$) < 3 Then StrMSec$ = String$(3 - Len(StrMSec$), "0") + StrMSec$
    
    '결과값을 돌려줌
    시간형태로변환 = StrMin$ + ":" + StrSec$ + "." + StrMSec$
End Function

Sub 참가자DB연결(lv As ListView)
    '리스트뷰 내용 삭제
    lv.ListItems.Clear
    '리스트뷰에 삽입
    For i = 1 To 참가인원
        Set ItmX = lv.ListItems.Add(, , 참가자(i).순번)
        ItmX.SubItems(1) = RTrim$(참가자(i).이름)
        ItmX.SubItems(2) = RTrim$(참가자(i).학교)
        ItmX.SubItems(3) = RTrim$(참가자(i).로봇명)
        
        If 참가자(i).순위 = 0 Then
           ItmX.SubItems(4) = "---"
        Else
           ItmX.SubItems(4) = Str(참가자(i).순위)
        End If
        
        If 참가자(i).최고기록 = 0 Then
           ItmX.SubItems(5) = "--------"
        Else
           ItmX.SubItems(5) = 시간형태로변환(참가자(i).최고기록)
        End If
        
        ItmX.SubItems(6) = Str(참가자(i).주행횟수)
        ItmX.SubItems(7) = 시간형태로변환(참가자(i).사용시간)
    Next i
    lv.Refresh
End Sub

Sub 숫자를4바이트로분해(숫자 As Long, Ch1 As Integer, Ch2 As Integer, Ch3 As Integer, Ch4 As Integer)
    
End Sub

Sub 주행기록보기(첨자 As Integer, lv As ListView)
    '주행기록을 리스트뷰에 보여줌
    Dim TempCount As Long
    Dim Bonus As Long
    Dim Record As String
    
    '리스트뷰 내용 삭제
    lv.ListItems.Clear
    
    '리스트뷰에 삽입
    Record = 참가자(첨자).주행기록
    For i = 1 To 참가자(첨자).주행횟수
        HighOffset = 기록데이터크기 * (i - 1) + 1 ' 상위바이트
        MidOffset1 = 기록데이터크기 * (i - 1) + 2 ' 중앙바이트1
        MidOffset2 = 기록데이터크기 * (i - 1) + 3 ' 중앙바이트2
        LowOffset = 기록데이터크기 * (i - 1) + 4 ' 하위바이트
        FlagOffset = 기록데이터크기 * (i - 1) + 5     '플래그
        
        H# = Asc(Mid$(Record, HighOffset, 1))
        M1# = Asc(Mid$(Record, MidOffset1, 1))
        M2# = Asc(Mid$(Record, MidOffset2, 1))
        L# = Asc(Mid$(Record, LowOffset, 1))
        Flag% = Asc(Mid$(Record, FlagOffset, 1))
        TempCount = H# * 2091752# + M1# * 16384# + M2# * 128# + L#
        
        Set ItmX = lv.ListItems.Add(, , Str(i))
        ItmX.SubItems(1) = 시간형태로변환(TempCount)
        
        ItmX.SubItems(2) = ""
        
        If TempCount <> 경주포기 Then
           If (Flag And 정지보너스) <> 0 Then ItmX.SubItems(2) = ItmX.SubItems(2) & "정지 "
           If (Flag And 이차보너스) <> 0 Then ItmX.SubItems(2) = ItmX.SubItems(2) & "2차 "
           If (Flag And 연기) <> 0 Then ItmX.SubItems(2) = ItmX.SubItems(2) & "연기 "
           If (Flag And 손접촉반칙) <> 0 Then ItmX.SubItems(2) = ItmX.SubItems(2) & "접촉 "
        
           Bonus = 플래그에따른가중치(Flag%)
           TempCount = TempCount + Bonus
           If TempCount < 1 Then TempCount = 1
                 
           If Bonus > 0 Then
              ItmX.SubItems(3) = "+" & Format(Bonus / 1000, "##.####")
           Else
              ItmX.SubItems(3) = Format(Bonus / 1000, "##.####")
           End If
           
           ItmX.SubItems(4) = 시간형태로변환(TempCount)
        End If
        
        Select Case TempCount
           Case 경주포기
              ItmX.SubItems(2) = "주행포기"
           Case 참가자(첨자).최고기록
              ItmX.SubItems(2) = "최고기록"
        End Select
        
        If ItmX.SubItems(2) = "" Then ItmX.SubItems(2) = "."
    Next i
    
    lv.Refresh
End Sub

Sub 순서미루기(첨자 As Integer)
    Dim c As Integer
        
    '임시보관
    Dim 순번     As Integer
    Dim 이름     As String * 문자열길이
    Dim 로봇명   As String * 문자열길이
    Dim 학교     As String * 문자열길이
    Dim 순위     As Integer
    Dim 주행횟수 As Integer
    Dim 최고기록 As Integer
    Dim 주행기록 As String * 주행기록길이
    Dim 사용시간 As Long
    
    순번 = 참가자(첨자).순번
    이름 = 참가자(첨자).이름
    로봇명 = 참가자(첨자).로봇명
    학교 = 참가자(첨자).학교
    순위 = 참가자(첨자).순위
    주행횟수 = 참가자(첨자).주행횟수
    최고기록 = 참가자(첨자).최고기록
    주행기록 = 참가자(첨자).주행기록
    사용시간 = 참가자(첨자).사용시간
    
    '첨자에 대응되는 참가자
    참가자삭제 첨자
    참가인원 = 참가인원 + 1
    참가자배열입력 참가인원, 순번, 이름, 로봇명, 학교, 순위, 주행횟수, 최고기록, 주행기록, 사용시간
    
    '순위계산을 통해 순위 부분 갱신
    For c = 1 To 참가인원
        순위계산 c
    Next c
    
    '순서바꾸기 완료
End Sub

Sub 기록삭제(첨자 As Integer)
    Dim c As Integer
    
    참가자(첨자).순위 = 0
    참가자(첨자).최고기록 = 0
    참가자(첨자).주행횟수 = 0
    참가자(첨자).주행기록 = ""
    참가자(첨자).사용시간 = 0
    
    For c = 1 To 참가인원
        순위계산 c
    Next c
End Sub

Sub 순위계산(첨자 As Integer)
    Dim 최하순위 As Integer
    최하순위 = 참가인원
    For i = 1 To 참가인원
       If 참가자(i).최고기록 = 0 Then 최하순위 = 최하순위 - 1
    Next i
    For i = 1 To 참가인원
       Do
          If 참가자(i).최고기록 <> 0 Then
             참가자(i).순위 = 최하순위
             Exit Do
          Else
             참가자(i).순위 = 0
             i = i + 1
             If i > 참가인원 Then Exit For
          End If
       Loop
       For j = 1 To 참가인원
           If i <> j And 참가자(j).최고기록 <> 0 Then
              If 참가자(i).최고기록 <= 참가자(j).최고기록 Then 참가자(i).순위 = 참가자(i).순위 - 1
           End If
       Next j
    Next i
End Sub

Sub 기록에서사용시간변환(첨자 As Integer, 사용시간 As Long)
    참가자(첨자).사용시간 = 사용시간
End Sub
Sub 기록추가(첨자 As Integer, 기록 As Long, 플래그 As Integer)
    Dim Temp기록 As Long
    Dim c As Integer
    
    Temp기록 = 기록
    
    n = 참가자(첨자).주행횟수
    
    HighOffset = 기록데이터크기 * n + 1  ' 상위바이트
    MidOffset1 = 기록데이터크기 * n + 2  ' 중간바이트
    MidOffset2 = 기록데이터크기 * n + 3  ' 중간바이트
    LowOffset = 기록데이터크기 * n + 4   ' 하위바이트
    FlagOffset = 기록데이터크기 * n + 5  ' 플래그바이트
    
    '비베 아스키 코드 대응 방법때문에 환장할 노릇, 한 바이트당 저장 가능한 범위를 0 ~ 127로 설정
    H# = Int(Temp기록 / 2091752#)
    Temp기록 = Temp기록 Mod 2091752#
    M1# = Int(Temp기록 / 16384#)
    Temp기록 = Temp기록 Mod 16384#
    M2# = Int(Temp기록 / 128#)
    L# = Temp기록 Mod 128#
    
    '기록을 주행기록에 추가
    Mid$(참가자(첨자).주행기록, HighOffset, 1) = Chr$(H#)
    Mid$(참가자(첨자).주행기록, MidOffset1, 1) = Chr$(M1#)
    Mid$(참가자(첨자).주행기록, MidOffset2, 1) = Chr$(M2#)
    Mid$(참가자(첨자).주행기록, LowOffset, 1) = Chr$(L#)
    Mid$(참가자(첨자).주행기록, FlagOffset, 1) = Chr$(플래그)
    
    참가자(첨자).주행횟수 = 참가자(첨자).주행횟수 + 1
    참가자(첨자).사용시간 = Get사용시간
    
    '기록에 보너스나 벌점에 따른 가중치 부여( 실제 기록은 주행기록에 저장됨 )
    기록 = 기록 + 플래그에따른가중치(플래그)
    
    '최고기록보다 빠르면 최고기록 갱신( 경주포기는 기록 인정 안함 )
    If (참가자(첨자).최고기록 > 기록 Or 참가자(첨자).최고기록 = 0) And 기록 <> 경주포기 Then 참가자(첨자).최고기록 = 기록
    
    '순위계산을 통해 순위 부분 갱신
    For c = 1 To 참가인원
        순위계산 c
    Next c
End Sub

Sub 참가자최고기록및순위갱신(첨자 As Integer)
    Dim Record As String
    Dim c As Integer
    Dim TempCount As Long
    
    Record = 참가자(첨자).주행기록
    If 참가자(첨자).최고기록 <> 0 Then
       참가자(첨자).최고기록 = MINIMUM
       For c = 1 To 참가자(첨자).주행횟수
           HighOffset = 기록데이터크기 * (c - 1) + 1 ' 상위바이트
           MidOffset1 = 기록데이터크기 * (c - 1) + 2 ' 중앙바이트1
           MidOffset2 = 기록데이터크기 * (c - 1) + 3 ' 중앙바이트2
           LowOffset = 기록데이터크기 * (c - 1) + 4  ' 하위바이트
           FlagOffset = 기록데이터크기 * (c - 1) + 5 ' 플래그바이트
           
           H# = Asc(Mid$(Record, HighOffset, 1))
           M1# = Asc(Mid$(Record, MidOffset1, 1))
           M2# = Asc(Mid$(Record, MidOffset2, 1))
           L# = Asc(Mid$(Record, LowOffset, 1))
           f% = Asc(Mid$(Record, FlagOffset, 1))
           TempCount = H# * 2091752# + M1# * 16384# + M2# * 128# + L#
        
           'TempCount는 기록 데이터를 가지고 있다. 일단 TempCount에 규정에 따라서 발생되는 가중치를 부여.
           TempCount = TempCount + 플래그에따른가중치(f%)
           
           '가중치 부여한 기록으로 최고기록과 비교
           If TempCount < 0 Then TempCount = 1
           If 참가자(첨자).최고기록 > TempCount Then 참가자(첨자).최고기록 = TempCount
       Next c
       If 참가자(첨자).최고기록 = MINIMUM Then 참가자(첨자).최고기록 = 0
       
       '순위계산을 통해 순위 부분 갱신
       For c = 1 To 참가인원
           순위계산 c
       Next c
    End If
End Sub
Sub 선택기록삭제(첨자 As Integer, 기록번호 As Integer)
    Temp$ = 참가자(첨자).주행기록
    If 기록번호 = 1 Then
       Result$ = ""
    Else
       Result$ = Left$(Temp$, 기록데이터크기 * (기록번호 - 1))
    End If
    
    HighOffset = 기록데이터크기 * (기록번호 - 1) + 1 ' 상위바이트
    MidOffset1 = 기록데이터크기 * (기록번호 - 1) + 2 ' 중앙바이트1
    MidOffset2 = 기록데이터크기 * (기록번호 - 1) + 3 ' 중앙바이트2
    LowOffset = 기록데이터크기 * (기록번호 - 1) + 4  ' 하위바이트
    FlagOffset = 기록데이터크기 * (기록번호 - 1) + 5 ' 플래그바이트
        
    H# = Asc(Mid$(Temp$, HighOffset, 1))
    M1# = Asc(Mid$(Temp$, MidOffset1, 1))
    M2# = Asc(Mid$(Temp$, MidOffset2, 1))
    L# = Asc(Mid$(Temp$, LowOffset, 1))
    f% = Asc(Mid$(Temp$, FlagOffset, 1))
    TempCount = H# * 2091752# + M1# * 16384# + M2# * 128# + L#
    
    If TempCount <> 경주포기 Then
       참가자(첨자).사용시간 = 참가자(첨자).사용시간 - TempCount
    End If
        
    '필요없는 부분을 발라낸다.
    Result$ = Result$ + Mid$(Temp$, 1 + (기록데이터크기 * 기록번호), Len(Temp$) - (1 + (기록데이터크기 * 기록번호)))
    
    '필요없는 부분을 없애고 생긴 공백을 아스키코드 0인 문자로 채운다.
    Result$ = Result$ + String(주행기록길이 - Len(Result$), Chr$(0))
        
    참가자(첨자).주행기록 = Result$
    참가자(첨자).주행횟수 = 참가자(첨자).주행횟수 - 1
    
    '최고기록 갱신
    참가자최고기록및순위갱신 첨자
End Sub

Sub 맨위로이동(첨자 As Integer)
    Dim 옮길참가자 As 참가자서식
    Dim 임시공간(최대참가자) As 참가자서식
    Dim SwapRec As 참가자서식
    Dim i As Integer, j As Integer
    Dim OutStr As String
    
    옮길참가자.순번 = 참가자(첨자).순번
    옮길참가자.이름 = 참가자(첨자).이름
    옮길참가자.로봇명 = 참가자(첨자).로봇명
    옮길참가자.학교 = 참가자(첨자).학교
    옮길참가자.순위 = 참가자(첨자).순위
    옮길참가자.주행횟수 = 참가자(첨자).주행횟수
    옮길참가자.최고기록 = 참가자(첨자).최고기록
    옮길참가자.주행기록 = 참가자(첨자).주행기록
    옮길참가자.사용시간 = 참가자(첨자).사용시간
    
    For i = 첨자 To 2 Step -1
       참가자(i).순번 = 참가자(i - 1).순번
       참가자(i).이름 = 참가자(i - 1).이름
       참가자(i).로봇명 = 참가자(i - 1).로봇명
       참가자(i).학교 = 참가자(i - 1).학교
       참가자(i).순위 = 참가자(i - 1).순위
       참가자(i).주행횟수 = 참가자(i - 1).주행횟수
       참가자(i).최고기록 = 참가자(i - 1).최고기록
       참가자(i).주행기록 = 참가자(i - 1).주행기록
       참가자(i).사용시간 = 참가자(i - 1).사용시간
    Next i
        
    참가자(1).순번 = 옮길참가자.순번
    참가자(1).이름 = 옮길참가자.이름
    참가자(1).로봇명 = 옮길참가자.로봇명
    참가자(1).학교 = 옮길참가자.학교
    참가자(1).순위 = 옮길참가자.순위
    참가자(1).주행횟수 = 옮길참가자.주행횟수
    참가자(1).최고기록 = 옮길참가자.최고기록
    참가자(1).주행기록 = 옮길참가자.주행기록
    참가자(1).사용시간 = 옮길참가자.사용시간
End Sub
Sub 결과파일만들기(파일명 As String)
    Dim 임시공간(최대참가자) As 참가자서식
    Dim SwapRec As 참가자서식
    Dim i As Integer, j As Integer
    Dim OutStr As String
    
    For i = 1 To 참가인원
       임시공간(i).로봇명 = 참가자(i).로봇명
       임시공간(i).사용시간 = 참가자(i).사용시간
       임시공간(i).순번 = 참가자(i).순번
       임시공간(i).순위 = 참가자(i).순위
       임시공간(i).이름 = 참가자(i).이름
       임시공간(i).최고기록 = 참가자(i).최고기록
       임시공간(i).학교 = 참가자(i).학교
       
       If 임시공간(i).순위 = 0 Then 임시공간(i).순위 = 32767
    Next i
        
    For i = 1 To 참가인원
       For j = 1 To 참가인원
          If 임시공간(i).순위 < 임시공간(j).순위 Then
             'Swap
             SwapRec.로봇명 = 임시공간(i).로봇명
             SwapRec.사용시간 = 임시공간(i).사용시간
             SwapRec.순번 = 임시공간(i).순번
             SwapRec.순위 = 임시공간(i).순위
             SwapRec.이름 = 임시공간(i).이름
             SwapRec.최고기록 = 임시공간(i).최고기록
             SwapRec.학교 = 임시공간(i).학교
                
             임시공간(i).로봇명 = 임시공간(j).로봇명
             임시공간(i).사용시간 = 임시공간(j).사용시간
             임시공간(i).순번 = 임시공간(j).순번
             임시공간(i).순위 = 임시공간(j).순위
             임시공간(i).이름 = 임시공간(j).이름
             임시공간(i).최고기록 = 임시공간(j).최고기록
             임시공간(i).학교 = 임시공간(j).학교
                
             임시공간(j).로봇명 = SwapRec.로봇명
             임시공간(j).사용시간 = SwapRec.사용시간
             임시공간(j).순번 = SwapRec.순번
             임시공간(j).순위 = SwapRec.순위
             임시공간(j).이름 = SwapRec.이름
             임시공간(j).최고기록 = SwapRec.최고기록
             임시공간(j).학교 = SwapRec.학교
          End If
       Next j
    Next i
    
    Open 파일명 For Output As #1
       LineStr$ = String$(6 + 32 + 32 + 32 + 15, "-")
       Print #1, LineStr$
       OutStr = "| 순위 |          학교 및 소속          |              이름              |              로봇명            |최고기록 |"
       Print #1, OutStr
       Print #1, String$(6 + 32 + 32 + 32 + 15, "-")
       For i = 1 To 참가인원
          If (임시공간(i).순위 < 32767) Then
             s$ = LTrim$(Str$(임시공간(i).순위))
             s$ = Space$(6 - Len(s$)) + s$
             OutStr = "|" & s$ & "|"
          Else
             OutStr = "|------|"
          End If
          s$ = ""
          n학교$ = LeftB$(RTrim$(임시공간(i).학교), 32)
          n학교$ = n학교$ + Space$(32 - LenB(StrConv(n학교$, vbFromUnicode)))
          OutStr = OutStr & n학교$ & "|"
          n이름$ = LeftB$(RTrim$(임시공간(i).이름), 32)
          n이름$ = n이름$ + Space$(32 - LenB(StrConv(n이름$, vbFromUnicode)))
          OutStr = OutStr & n이름$ & "|"
          n로봇명$ = LeftB$(RTrim$(임시공간(i).로봇명), 32)
          n로봇명$ = n로봇명$ + Space$(32 - LenB(StrConv(n로봇명$, vbFromUnicode)))
          OutStr = OutStr & n로봇명$ & "|"
          
          If (임시공간(i).최고기록 > 0) Then
             OutStr = OutStr & 시간형태로변환(임시공간(i).최고기록) & "|"
          Else
             OutStr = OutStr & "---------" & "|"
          End If
          Print #1, OutStr
       Next i
       Print #1, LineStr$
    Close #1
End Sub

Function 기록에서플래그얻기(첨자 As Integer, 회수 As Integer) As Integer
    기록에서플래그얻기 = Asc(Mid$(참가자(첨자).주행기록, 기록데이터크기 * (회수 - 1) + 5))
End Function

Sub 기록에플래그덮어씌우기(첨자 As Integer, 회수 As Integer, 플래그 As Integer)
    Mid$(참가자(첨자).주행기록, 기록데이터크기 * (회수 - 1) + 5) = Chr$(플래그)
    참가자최고기록및순위갱신 첨자
End Sub

Function Set참가자사용시간(첨자 As Integer, 사용시간 As Long)
    참가자(첨자).사용시간 = 사용시간
End Function

Function Get참가자사용시간(첨자 As Integer) As Long
    Get참가자사용시간 = 참가자(첨자).사용시간
End Function

Function Get참가인원() As Integer
    Get참가인원 = 참가인원
End Function
