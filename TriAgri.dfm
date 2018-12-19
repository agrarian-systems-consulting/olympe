object TriAgriFrm: TTriAgriFrm
  Left = 187
  Top = 251
  Width = 722
  Height = 334
  Caption = 'Cl'#233's de Tri'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PanBas: TPanel
    Left = 0
    Top = 266
    Width = 714
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BtBnOk: TBitBtn
      Left = 8
      Top = 8
      Width = 49
      Height = 25
      TabOrder = 0
      OnClick = BtBnOkClick
      Kind = bkOK
    end
    object BtBnPasOK: TBitBtn
      Left = 64
      Top = 8
      Width = 49
      Height = 25
      TabOrder = 1
      OnClick = BtBnPasOKClick
      Kind = bkCancel
    end
    object BtBnCritere: TBitBtn
      Left = 296
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Crit'#232'res'
      TabOrder = 2
      OnClick = BtBnCritereClick
    end
  end
  object Pan1: TPanel
    Left = 0
    Top = 8
    Width = 129
    Height = 241
    Caption = 'Pan1'
    TabOrder = 1
    object Lab1: TLabel
      Left = 0
      Top = 0
      Width = 30
      Height = 16
      Caption = 'Lab1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object BtBnAucun1: TBitBtn
      Left = 0
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Aucun'
      TabOrder = 0
      OnClick = BtBnAucunClick
    end
    object BtBnTous1: TBitBtn
      Left = 78
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Tous'
      TabOrder = 1
      OnClick = BtBnTousClick
    end
    object ChLB1: TCheckListBox
      Left = 1
      Top = 32
      Width = 127
      Height = 185
      OnClickCheck = ChLBClickCheck
      Color = clInfoBk
      Flat = False
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object Pan2: TPanel
    Left = 140
    Top = 8
    Width = 129
    Height = 241
    Caption = 'Pan2'
    TabOrder = 2
    object Lab2: TLabel
      Left = 0
      Top = 0
      Width = 30
      Height = 16
      Caption = 'Lab2'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object BtBnAucun2: TBitBtn
      Left = 0
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Aucun'
      TabOrder = 0
      OnClick = BtBnAucunClick
    end
    object BtBnTous2: TBitBtn
      Left = 78
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Tous'
      TabOrder = 1
      OnClick = BtBnTousClick
    end
    object ChLB2: TCheckListBox
      Left = 0
      Top = 32
      Width = 129
      Height = 185
      OnClickCheck = ChLBClickCheck
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object Pan3: TPanel
    Left = 277
    Top = 8
    Width = 129
    Height = 241
    Caption = 'Pan3'
    TabOrder = 3
    object Lab3: TLabel
      Left = 0
      Top = 0
      Width = 30
      Height = 16
      Caption = 'Lab3'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object BtBnAucun3: TBitBtn
      Left = 0
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Aucun'
      TabOrder = 0
      OnClick = BtBnAucunClick
    end
    object BtBnTous3: TBitBtn
      Left = 78
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Tous'
      TabOrder = 1
      OnClick = BtBnTousClick
    end
    object ChLB3: TCheckListBox
      Left = 1
      Top = 32
      Width = 135
      Height = 185
      OnClickCheck = ChLBClickCheck
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object Pan4: TPanel
    Left = 415
    Top = 8
    Width = 129
    Height = 241
    Caption = 'Pan4'
    TabOrder = 4
    object Lab4: TLabel
      Left = 0
      Top = 0
      Width = 30
      Height = 16
      Caption = 'Lab4'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object BtBnAucun4: TBitBtn
      Left = 0
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Aucun'
      TabOrder = 0
      OnClick = BtBnAucunClick
    end
    object BtBnTous4: TBitBtn
      Left = 78
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Tous'
      TabOrder = 1
      OnClick = BtBnTousClick
    end
    object ChLB4: TCheckListBox
      Left = 1
      Top = 32
      Width = 135
      Height = 185
      OnClickCheck = ChLBClickCheck
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 2
    end
  end
  object Pan5: TPanel
    Left = 552
    Top = 8
    Width = 129
    Height = 241
    Caption = 'Pan5'
    TabOrder = 5
    object Lab5: TLabel
      Left = 0
      Top = 0
      Width = 30
      Height = 16
      Caption = 'Lab5'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object BtBnAucun5: TBitBtn
      Left = 0
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Aucun'
      TabOrder = 0
      OnClick = BtBnAucunClick
    end
    object BtBnTous5: TBitBtn
      Left = 78
      Top = 216
      Width = 51
      Height = 25
      Caption = 'Tous'
      TabOrder = 1
      OnClick = BtBnTousClick
    end
    object ChLB5: TCheckListBox
      Left = 1
      Top = 32
      Width = 135
      Height = 185
      OnClickCheck = ChLBClickCheck
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 2
    end
  end
end
