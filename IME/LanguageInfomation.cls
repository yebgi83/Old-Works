VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "LanguageInformation"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"No"
'********************************************************************************
' Fields
'********************************************************************************
Private m_ID As Integer             '언어 식별자
Private m_LanguageName As String    '언어 명칭
Private m_Country As String         '국가 이름
Private m_CodePage As Integer       '문자 코드 번호
Private m_CountryCode As String     '국가 축약형 명칭

'********************************************************************************
' Properties
'********************************************************************************
'키 값을 가져온다. ( 키 = 언어 식별자 )
Public Property Get Key() As String
    Key = Hex(ID)
End Property

'언어 식별자를 가져온다.
Public Property Get ID() As Integer
    ID = m_ID
End Property

'언어 식별자를 설정한다.
Public Property Let ID(Value As Integer)
    m_ID = Value
End Property

'언어 명칭을 가져온다.
Public Property Get LanguageName() As String
    LanguageName = m_LanguageName
End Property

'언어 명칭을 설정한다.
Public Property Let LanguageName(Value As String)
    m_LanguageName = Value
End Property

'국가 이름을 가져온다.
Public Property Get Country() As String
    Country = m_Country
End Property

'국가 이름을 설정한다.
Public Property Let Country(Value As String)
    m_Country = Value
End Property

'문자 코드 번호를 가져온다.
Public Property Get CodePage() As Integer
    CodePage = m_CodePage
End Property

'문자 코드 번호를 설정한다.
Public Property Let CodePage(Value As Integer)
    m_CodePage = Value
End Property

'국가 코드를 가져온다.
Public Property Get CountryCode() As String
    CountryCode = m_CountryCode
End Property

'국가 코드를 지정한다.
Public Property Let CountryCode(Value As String)
    m_CountryCode = Value
End Property
