VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "IMEClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Attribute VB_Ext_KEY = "Member0" ,"LanguageInformationCollection"
'********************************************************************************
' APIs
'********************************************************************************

'활성화 되어있는 키보드 레이아웃을 확인하는 API
Private Declare Function GetKeyboardLayout Lib "user32" (ByVal dwLayout As Long) As Long

'지윈가능한 키보드 레이아웃을 가져오는 API
Private Declare Function GetKeyboardLayoutList Lib "user32" (ByVal nBuff As Long, lpList As Long) As Long

'키보드 레이아웃을 활성화 하는 API
Private Declare Function ActivateKeyboardLayout Lib "user32" (ByVal HKL As Long, ByVal flags As Long) As Long

'********************************************************************************
' Fields
'********************************************************************************
Private m_Languages As LanguageInformationCollection '모든 국가 코드
Private m_Layouts() As Long

'********************************************************************************
' Methods
'********************************************************************************
Private Sub Class_Initialize()
    '초기화
    Set m_Languages = New LanguageInformationCollection
    
    '국가 등록 (출처 : http://msdn.microsoft.com/en-us/library/aa912040.aspx)
    m_Languages.Add &H3C01, "Arabic", "Bahrain", 1256, "ARH"
    m_Languages.Add &HC01, "Arabic", "Egypt", 1256, "ARE"
    m_Languages.Add &H801, "Arabic", "Iraq", 1256, "ARI"
    m_Languages.Add &H2C01, "Arabic", "Jordan", 1256, "ARJ"
    m_Languages.Add &H3401, "Arabic", "Kuwait", 1256, "ARK"
    m_Languages.Add &H3001, "Arabic", "Lebanon", 1256, "ARB"
    m_Languages.Add &H1001, "Arabic", "Libya", 1256, "ARL"
    m_Languages.Add &H1801, "Arabic", "Morocco", 1256, "ARM"
    m_Languages.Add &H2001, "Arabic", "Oman", 1256, "ARO"
    m_Languages.Add &H4001, "Arabic", "Qatar", 1256, "ARQ"
    m_Languages.Add &H401, "Arabic", "Saudi Arabia", 1256, "ARA"
    m_Languages.Add &H2801, "Arabic", "Syria", 1256, "ARS"
    m_Languages.Add &H1C01, "Arabic", "Tunisia", 1256, "ART"
    m_Languages.Add &H3801, "Arabic", "U.A.E.", 1256, "ARU"
    m_Languages.Add &H2401, "Arabic", "Yemen", 1256, "ARY"
    m_Languages.Add &H42B, "Armenian", "Armenia", 0, "HYE"
    m_Languages.Add &H82C, "Azeri", "Azerbaijan (Cyrillic)", 1251, "AZE"
    m_Languages.Add &H42C, "Azeri", "Azerbaijan (Latin)", 1254, "AZE"
    m_Languages.Add &H42D, "Basque", "Spain", 1252, "EUQ"
    m_Languages.Add &H423, "Belarusian", "Belarus", 1251, "BEL"
    m_Languages.Add &H402, "Bulgarian", "Bulgaria", 1251, "BGR"
    m_Languages.Add &H403, "Catalan", "Spain", 1252, "CAT"
    m_Languages.Add &HC04, "Chinese", "Hong Kong SAR", 950, "ZHH"
    m_Languages.Add &H1404, "Chinese", "Macao SAR", 950, "ZHM"
    m_Languages.Add &H804, "Chinese", "PRC", 936, "CHS"
    m_Languages.Add &H1004, "Chinese", "Singapore", 936, "ZHI"
    m_Languages.Add &H404, "Chinese", "Taiwan", 950, "TWN" '"CHT"
    m_Languages.Add &H41A, "Croatian", "Croatia", 1250, "HRV"
    m_Languages.Add &H405, "Czech", "Czech Republic", 1250, "CSY"
    m_Languages.Add &H406, "Danish", "Denmark", 1252, "DAN"
    m_Languages.Add &H465, "Divehi", "Maldives", 0, "DIV"
    m_Languages.Add &H813, "Dutch", "Belgium", 1252, "NLB"
    m_Languages.Add &H413, "Dutch", "Netherlands", 1252, "NLD"
    m_Languages.Add &HC09, "English", "Australia", 1252, "ENA"
    m_Languages.Add &H2809, "English", "Belize", 1252, "ENL"
    m_Languages.Add &H1009, "English", "Canada", 1252, "ENC"
    m_Languages.Add &H2409, "English", "Caribbean", 1252, "ENB"
    m_Languages.Add &H1809, "English", "Ireland", 1252, "ENI"
    m_Languages.Add &H2009, "English", "Jamaica", 1252, "ENJ"
    m_Languages.Add &H1409, "English", "New Zealand", 1252, "ENZ"
    m_Languages.Add &H3409, "English", "Philippines", 1252, "ENP"
    m_Languages.Add &H1C09, "English", "South Africa", 1252, "ENS"
    m_Languages.Add &H2C09, "English", "Trinidad", 1252, "ENT"
    m_Languages.Add &H809, "English", "United Kingdom", 1252, "ENG"
    m_Languages.Add &H409, "English", "United States", 1252, "USA"
    m_Languages.Add &H3009, "English", "Zimbabwe", 1252, "ENW"
    m_Languages.Add &H425, "Estonian", "Estonia", 1257, "ETI"
    m_Languages.Add &H438, "Faroese", "Faroe Islands", 1252, "FOS"
    m_Languages.Add &H429, "Farsi", "Iran", 1256, "FAR"
    m_Languages.Add &H40B, "Finnish", "Finland", 1252, "FIN"
    m_Languages.Add &H80C, "French", "Belgium", 1252, "FRB"
    m_Languages.Add &HC0C, "French", "Canada", 1252, "FRC"
    m_Languages.Add &H40C, "French", "France", 1252, "FRA"
    m_Languages.Add &H140C, "French", "Luxembourg", 1252, "FRL"
    m_Languages.Add &H180C, "French", "Monaco", 1252, "FRM"
    m_Languages.Add &H100C, "French", "Switzerland", 1252, "FRS"
    m_Languages.Add &H42F, "F.Y.R.O.Macedonia", "F.Y.R.O.Macedonia", 1251, "MKI"
    m_Languages.Add &H456, "Galician", "Spain", 1252, "GLC"
    m_Languages.Add &H437, "Georgian", "Georgia", 0, "KAT"
    m_Languages.Add &HC07, "German", "Austria", 1252, "DEA"
    m_Languages.Add &H407, "German", "Germany", 1252, "DEU"
    m_Languages.Add &H1407, "German", "Liechtenstein", 1252, "DEC"
    m_Languages.Add &H1007, "German", "Luxembourg", 1252, "DEL"
    m_Languages.Add &H807, "German", "Switzerland", 1252, "DES"
    m_Languages.Add &H408, "Greek", "Greece", 1253, "ELL"
    m_Languages.Add &H447, "Gujarati", "India", 0, "GUJ"
    m_Languages.Add &H40D, "Hebrew", "Israel", 1255, "HEB"
    m_Languages.Add &H439, "Hindi", "India", 0, "HIN"
    m_Languages.Add &H40E, "Hungarian", "Hungary", 1250, "HUN"
    m_Languages.Add &H40F, "Icelandic", "Iceland", 1252, "ISL"
    m_Languages.Add &H421, "Indonesian", "Indonesia (Bahasa)", 1252, "IND"
    m_Languages.Add &H410, "Italian", "Italy", 1252, "ITA"
    m_Languages.Add &H810, "Italian", "Switzerland", 1252, "ITS"
    m_Languages.Add &H411, "Japanese", "Japan", 932, "JPN"
    m_Languages.Add &H44B, "Kannada", "India (Kannada script)", 0, "KAN"
    m_Languages.Add &H43F, "Kazakh", "Kazakstan", 1251, "KKZ"
    m_Languages.Add &H457, "Konkani", "India", 0, "KNK"
    m_Languages.Add &H412, "Korean", "Korea", 949, "KOR"
    m_Languages.Add &H440, "Kyrgyz", "Kyrgyzstan", 1251, "KYR"
    m_Languages.Add &H426, "Latvian", "Latvia", 1257, "LVI"
    m_Languages.Add &H427, "Lithuanian", "Lithuania", 1257, "LTH"
    m_Languages.Add &H83E, "Malay", "Brunei Darussalam", 1252, "MSB"
    m_Languages.Add &H43E, "Malay", "Malaysia", 1252, "MSL"
    m_Languages.Add &H44E, "Marathi", "India", 0, "MAR"
    m_Languages.Add &H450, "Mongolian (Cyrillic)", "Mongolia", 1251, "MON"
    m_Languages.Add &H414, "Norwegian", "Norway (Bokmal)", 1252, "NOR"
    m_Languages.Add &H814, "Norwegian", "Norway (Nynorsk)", 1252, "NON"
    m_Languages.Add &H415, "Polish", "Poland", 1250, "PLK"
    m_Languages.Add &H416, "Portuguese", "Brazil", 1252, "PTB"
    m_Languages.Add &H816, "Portuguese", "Portugal", 1252, "PTG"
    m_Languages.Add &H446, "Punjabi", "India (Gurmukhi script)", 0, "PAN"
    m_Languages.Add &H418, "Romanian", "Romania", 1250, "ROM"
    m_Languages.Add &H419, "Russian", "Russia", 1251, "RUS"
    m_Languages.Add &H44F, "Sanskrit", "India", 0, "SAN"
    m_Languages.Add &HC1A, "Serbian", "Serbia (Cyrillic)", 1251, "SRB"
    m_Languages.Add &H81A, "Serbian", "Serbia (Latin)", 1250, "SRL"
    m_Languages.Add &H41B, "Slovak", "Slovakia", 1250, "SKY"
    m_Languages.Add &H424, "Slovenian", "Slovenia", 1250, "SLV"
    m_Languages.Add &H2C0A, "Spanish", "Argentina", 1252, "ESS"
    m_Languages.Add &H400A, "Spanish", "Bolivia", 1252, "ESB"
    m_Languages.Add &H340A, "Spanish", "Chile", 1252, "ESL"
    m_Languages.Add &H240A, "Spanish", "Colombia", 1252, "ESO"
    m_Languages.Add &H140A, "Spanish", "Costa Rica", 1252, "ESC"
    m_Languages.Add &H1C0A, "Spanish", "Dominican Republic", 1252, "ESD"
    m_Languages.Add &H300A, "Spanish", "Ecuador", 1252, "ESF"
    m_Languages.Add &H440A, "Spanish", "El Salvador", 1252, "ESE"
    m_Languages.Add &H100A, "Spanish", "Guatemala", 1252, "ESG"
    m_Languages.Add &H480A, "Spanish", "Honduras", 1252, "ESH"
    m_Languages.Add &H80A, "Spanish", "Mexico", 1252, "ESM"
    m_Languages.Add &H4C0A, "Spanish", "Nicaragua", 1252, "ESI"
    m_Languages.Add &H180A, "Spanish", "Panama", 1252, "ESA"
    m_Languages.Add &H3C0A, "Spanish", "Paraguay", 1252, "ESZ"
    m_Languages.Add &H280A, "Spanish", "Peru", 1252, "ESR"
    m_Languages.Add &H500A, "Spanish", "Puerto Rico", 1252, "ESU"
    m_Languages.Add &H40A, "Spanish", "Spain (Traditional sort)", 1252, "ESP"
    m_Languages.Add &HC0A, "Spanish", "Spain (International sort)", 1252, "ESN"
    m_Languages.Add &H380A, "Spanish", "Uruguay", 1252, "ESY"
    m_Languages.Add &H200A, "Spanish", "Venezuela", 1252, "ESV"
    m_Languages.Add &H441, "Swahili", "Kenya", 1252, "SWK"
    m_Languages.Add &H81D, "Swedish", "Finland", 1252, "SVF"
    m_Languages.Add &H41D, "Swedish", "Sweden", 1252, "SVE"
    m_Languages.Add &H45A, "Syriac", "Syria", 0, "SYR"
    m_Languages.Add &H449, "Tamil", "India", 0, "TAM"
    m_Languages.Add &H444, "Tatar", "Tatarstan", 1251, "TTT"
    m_Languages.Add &H44A, "Telugu", "India (Telugu script)", 0, "TEL"
    m_Languages.Add &H41E, "Thai", "Thailand", 874, "THA"
    m_Languages.Add &H41F, "Turkish", "Turkey", 1254, "TRK"
    m_Languages.Add &H422, "Ukrainian", "Ukraine", 1251, "UKR"
    m_Languages.Add &H420, "Urdu", "Pakistan", 1256, "URP"
    m_Languages.Add &H843, "Uzbek", "Uzbekistan (Cyrillic)", 1251, "UZB"
    m_Languages.Add &H443, "Uzbek", "Uzbekistan (Latin)", 1254, "UZB"
    m_Languages.Add &H42A, "Vietnamese", "Viet Nam", 1258, "VIT"
    
    '설치된 키보드 레이아웃의 개수를 구한다.
    Dim LayoutCount As Long
    LayoutCount = GetKeyboardLayoutList(0, ByVal 0&)
    
    '설치된 키보드 레이아웃을 불러낸다.
    ReDim m_Layouts(LayoutCount - 1)
    GetKeyboardLayoutList LayoutCount, m_Layouts(0)
End Sub
