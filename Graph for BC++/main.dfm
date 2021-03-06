object Form1: TForm1
  Left = 253
  Top = 157
  BorderStyle = bsSingle
  Caption = 'Form1'
  ClientHeight = 594
  ClientWidth = 816
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Chart1: TChart
    Left = 8
    Top = 40
    Width = 400
    Height = 250
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.AdjustFrame = False
    Title.Text.Strings = (
      'Sensor 1')
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.ExactDateTime = False
    LeftAxis.Maximum = 5
    LeftAxis.MinorGrid.Style = psDashDotDot
    LeftAxis.MinorGrid.SmallDots = True
    LeftAxis.MinorGrid.Visible = True
    LeftAxis.MinorTickCount = 4
    LeftAxis.TickLength = 3
    LeftAxis.TickOnLabelsOnly = False
    TopAxis.Automatic = False
    TopAxis.AutomaticMaximum = False
    TopAxis.AutomaticMinimum = False
    TopAxis.Maximum = 100
    View3D = False
    BevelInner = bvRaised
    BevelOuter = bvNone
    TabOrder = 0
    object Series1: TFastLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      LinePen.Color = clRed
      LinePen.Width = 3
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Chart2: TChart
    Left = 416
    Top = 40
    Width = 400
    Height = 249
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.AdjustFrame = False
    Title.Text.Strings = (
      'Sensor 2')
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 5
    LeftAxis.MinorGrid.Visible = True
    LeftAxis.MinorTickCount = 4
    View3D = False
    TabOrder = 1
    object Series2: TFastLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      LinePen.Color = clRed
      LinePen.Width = 3
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Chart3: TChart
    Left = 8
    Top = 296
    Width = 400
    Height = 250
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.AdjustFrame = False
    Title.Text.Strings = (
      'Sensor 3')
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 5
    LeftAxis.MinorGrid.SmallDots = True
    LeftAxis.MinorGrid.Visible = True
    LeftAxis.MinorTickCount = 4
    View3D = False
    TabOrder = 2
    object Series3: TFastLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      LinePen.Color = clRed
      LinePen.Width = 3
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Chart4: TChart
    Left = 416
    Top = 296
    Width = 400
    Height = 250
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.AdjustFrame = False
    Title.Text.Strings = (
      'Sensor 4')
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 5
    LeftAxis.MinorGrid.Style = psDashDotDot
    LeftAxis.MinorGrid.SmallDots = True
    LeftAxis.MinorGrid.Visible = True
    LeftAxis.MinorTickCount = 4
    View3D = False
    TabOrder = 3
    object Series4: TFastLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      LinePen.Color = clRed
      LinePen.Width = 3
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object TestOnBtn: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Test On'
    TabOrder = 4
    OnClick = TestOnBtnClick
  end
  object TestOffBtn: TButton
    Left = 88
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Test Off'
    TabOrder = 5
    OnClick = TestOffBtnClick
  end
  object SerialOnBtn: TButton
    Left = 168
    Top = 8
    Width = 75
    Height = 25
    Caption = 'RS232 On'
    TabOrder = 6
    OnClick = SerialOnBtnClick
  end
  object MSComm1: TMSComm
    Left = 744
    Top = 8
    Width = 32
    Height = 32
    OnComm = MSComm1Comm
    ControlData = {
      2143341208000000ED030000ED03000001568A64000006000000010000040500
      0002000000C201000000080000000000000000003F00000001000000}
  end
  object StatusPanel: TPanel
    Left = 0
    Top = 568
    Width = 816
    Height = 26
    Align = alBottom
    BorderStyle = bsSingle
    Caption = 'Serial Not Opened'
    TabOrder = 8
  end
  object SerialOffBtn: TButton
    Left = 248
    Top = 8
    Width = 75
    Height = 25
    Caption = 'RS232 Off'
    TabOrder = 9
    OnClick = SerialOffBtnClick
  end
  object TestTimer: TTimer
    Enabled = False
    Interval = 50
    OnTimer = TestTimerTimer
    Left = 784
    Top = 8
  end
end
