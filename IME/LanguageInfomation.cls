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
Private m_ID As Integer             '��� �ĺ���
Private m_LanguageName As String    '��� ��Ī
Private m_Country As String         '���� �̸�
Private m_CodePage As Integer       '���� �ڵ� ��ȣ
Private m_CountryCode As String     '���� ����� ��Ī

'********************************************************************************
' Properties
'********************************************************************************
'Ű ���� �����´�. ( Ű = ��� �ĺ��� )
Public Property Get Key() As String
    Key = Hex(ID)
End Property

'��� �ĺ��ڸ� �����´�.
Public Property Get ID() As Integer
    ID = m_ID
End Property

'��� �ĺ��ڸ� �����Ѵ�.
Public Property Let ID(Value As Integer)
    m_ID = Value
End Property

'��� ��Ī�� �����´�.
Public Property Get LanguageName() As String
    LanguageName = m_LanguageName
End Property

'��� ��Ī�� �����Ѵ�.
Public Property Let LanguageName(Value As String)
    m_LanguageName = Value
End Property

'���� �̸��� �����´�.
Public Property Get Country() As String
    Country = m_Country
End Property

'���� �̸��� �����Ѵ�.
Public Property Let Country(Value As String)
    m_Country = Value
End Property

'���� �ڵ� ��ȣ�� �����´�.
Public Property Get CodePage() As Integer
    CodePage = m_CodePage
End Property

'���� �ڵ� ��ȣ�� �����Ѵ�.
Public Property Let CodePage(Value As Integer)
    m_CodePage = Value
End Property

'���� �ڵ带 �����´�.
Public Property Get CountryCode() As String
    CountryCode = m_CountryCode
End Property

'���� �ڵ带 �����Ѵ�.
Public Property Let CountryCode(Value As String)
    m_CountryCode = Value
End Property