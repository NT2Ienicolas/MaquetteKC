object FMain: TFMain
  Left = 0
  Top = 0
  Caption = 'Main'
  ClientHeight = 986
  ClientWidth = 1008
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label6: TLabel
    Left = 914
    Top = 119
    Width = 27
    Height = 13
    Caption = 'Angle'
  end
  object Label7: TLabel
    Left = 918
    Top = 147
    Width = 6
    Height = 13
    Caption = 'X'
  end
  object Label8: TLabel
    Left = 918
    Top = 175
    Width = 6
    Height = 13
    Caption = 'Y'
  end
  object Label1: TLabel
    Left = 918
    Top = 251
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Label2: TLabel
    Left = 918
    Top = 278
    Width = 6
    Height = 13
    Caption = '1'
  end
  object Label3: TLabel
    Left = 918
    Top = 305
    Width = 6
    Height = 13
    Caption = '2'
  end
  object Label4: TLabel
    Left = 918
    Top = 332
    Width = 6
    Height = 13
    Caption = '3'
  end
  object Label5: TLabel
    Left = 920
    Top = 359
    Width = 6
    Height = 13
    Caption = '4'
  end
  object lblDeltaCassette: TLabel
    Left = 970
    Top = 470
    Width = 30
    Height = 13
    AutoSize = False
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBtnText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object bCarousel: TButton
    Left = 906
    Top = 8
    Width = 94
    Height = 25
    Caption = 'Carousel'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = bCarouselClick
  end
  object bInitRotation: TButton
    Left = 906
    Top = 39
    Width = 94
    Height = 25
    Caption = 'Init Rotation'
    TabOrder = 1
    OnClick = bInitRotationClick
  end
  object bDoRotation: TButton
    Left = 906
    Top = 70
    Width = 94
    Height = 25
    Caption = 'Do Rotation'
    TabOrder = 2
    OnClick = bDoRotationClick
  end
  object seAngleRotation: TSpinEdit
    Left = 951
    Top = 116
    Width = 49
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 90
  end
  object seRotationX: TSpinEdit
    Left = 951
    Top = 144
    Width = 49
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 4
    Value = 30
  end
  object seRotationY: TSpinEdit
    Left = 951
    Top = 172
    Width = 49
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 5
    Value = 50
  end
  object pInfoBulle: TPanel
    Left = 0
    Top = 0
    Width = 169
    Height = 113
    BevelOuter = bvNone
    Caption = 'pInfoBulle'
    Color = clYellow
    ParentBackground = False
    TabOrder = 6
    Visible = False
    object mBulleInfo: TMemo
      Left = 2
      Top = 76
      Width = 164
      Height = 34
      Lines.Strings = (
        'mBulleInfo')
      TabOrder = 0
    end
  end
  object cbNumObj: TCheckBox
    Left = 920
    Top = 216
    Width = 82
    Height = 17
    Caption = 'Visu n'#176' objet'
    TabOrder = 7
  end
  object cbCass0: TComboBox
    Left = 930
    Top = 248
    Width = 70
    Height = 21
    ItemIndex = 0
    TabOrder = 8
    Text = 'Absent'
    Items.Strings = (
      'Absent'
      'Reactif'
      'Conso')
  end
  object cbCass1: TComboBox
    Left = 930
    Top = 275
    Width = 70
    Height = 21
    ItemIndex = 0
    TabOrder = 9
    Text = 'Absent'
    Items.Strings = (
      'Absent'
      'Reactif'
      'Conso')
  end
  object cbCass2: TComboBox
    Left = 930
    Top = 302
    Width = 70
    Height = 21
    ItemIndex = 0
    TabOrder = 10
    Text = 'Absent'
    Items.Strings = (
      'Absent'
      'Reactif'
      'Conso')
  end
  object cbCass3: TComboBox
    Left = 930
    Top = 329
    Width = 70
    Height = 21
    ItemIndex = 0
    TabOrder = 11
    Text = 'Absent'
    Items.Strings = (
      'Absent'
      'Reactif'
      'Conso')
  end
  object cbCass4: TComboBox
    Left = 930
    Top = 356
    Width = 70
    Height = 21
    ItemIndex = 0
    TabOrder = 12
    Text = 'Absent'
    Items.Strings = (
      'Absent'
      'Reactif'
      'Conso')
  end
  object bInitScan: TButton
    Left = 906
    Top = 383
    Width = 94
    Height = 25
    Caption = 'Scan K7'
    TabOrder = 13
    OnClick = bInitScanClick
  end
  object bPrevCassette: TButton
    Left = 906
    Top = 414
    Width = 94
    Height = 22
    Caption = '<< Cassette'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    OnClick = bPrevCassetteClick
  end
  object bNextCassette: TButton
    Left = 906
    Top = 442
    Width = 94
    Height = 22
    Caption = 'Cassette >>'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 15
    OnClick = bNextCassetteClick
  end
  object mTodo: TMemo
    Left = 906
    Top = 560
    Width = 94
    Height = 145
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      'Todo :'
      'SetInfoBulle')
    ParentFont = False
    TabOrder = 16
  end
  object bColor: TButton
    Left = 906
    Top = 711
    Width = 94
    Height = 22
    Caption = 'Couleur'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 17
  end
  object tInfoBulle: TTimer
    Enabled = False
    Interval = 10000
    OnTimer = tInfoBulleTimer
    Left = 8
  end
end
