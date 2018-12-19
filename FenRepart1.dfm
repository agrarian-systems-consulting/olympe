object FenRepartFrm1: TFenRepartFrm1
  Left = 192
  Top = 114
  Width = 389
  Height = 480
  Caption = 'FenRepartFrm1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabPcent: TLabel
    Left = 8
    Top = 40
    Width = 53
    Height = 16
    Caption = 'Pourcent'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabVal: TLabel
    Left = 184
    Top = 40
    Width = 39
    Height = 16
    Caption = 'Valeur'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabTotPcent: TLabel
    Left = 56
    Top = 392
    Width = 50
    Height = 13
    Caption = 'Total en %'
  end
  object LabTotalVal: TLabel
    Left = 224
    Top = 392
    Width = 24
    Height = 13
    Caption = 'Total'
  end
  object LabelModifie: TLabel
    Left = 320
    Top = 40
    Width = 52
    Height = 16
    Caption = 'Modifie'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Panell: TPanel
    Left = 0
    Top = 405
    Width = 381
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BoutFermer: TBitBtn
      Left = 248
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkClose
    end
    object BtBnQuitter: TBitBtn
      Left = 328
      Top = 8
      Width = 50
      Height = 25
      Caption = 'Quitter'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BtBnQuitterClick
    end
    object BtRepBas: TBitBtn
      Left = 29
      Top = 5
      Width = 25
      Height = 24
      Hint = 'Report vers le Bas'
      ParentShowHint = False
      ShowHint = False
      TabOrder = 2
      OnClick = BtRepBasClick
      Glyph.Data = {
        72010000424D7201000000000000760000002800000011000000150000000100
        040000000000FC000000C40E0000C40E00001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
        7777700000007777777777777777700000007777777777777777700000007777
        7777077777777000000077777770007777777000000077777700000777777000
        0000777770000000777770000000777700000000077770000000777000000000
        0077700000007700000000000007700000007000000000000000700000007777
        7000000077777000000077777000000077777000000077777000000077777000
        0000777770000000777770000000777770000000777770000000777770000000
        7777700000007777700000007777700000007777700000007777700000007777
        77777777777770000000777777777777777770000000}
    end
    object BtBn100: TBitBtn
      Left = 56
      Top = 5
      Width = 25
      Height = 25
      Caption = '100'
      TabOrder = 3
      OnClick = BtBn100Click
    end
    object BtBnEgal: TBitBtn
      Left = 80
      Top = 5
      Width = 41
      Height = 25
      Caption = '100/12'
      TabOrder = 4
      OnClick = BtBnEgalClick
    end
  end
  object LaGrille: TStringGrid
    Left = 0
    Top = 56
    Width = 361
    Height = 329
    ColCount = 7
    FixedColor = 13693007
    RowCount = 13
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goAlwaysShowEditor]
    TabOrder = 1
    OnKeyPress = SGKeyPress
    OnSelectCell = SGSelectCell
    RowHeights = (
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24
      24)
  end
  object EdTotPcent: TEdit
    Left = 112
    Top = 384
    Width = 73
    Height = 21
    TabOrder = 2
  end
  object EdTotValeur: TEdit
    Left = 256
    Top = 384
    Width = 73
    Height = 21
    TabOrder = 3
  end
  object GBCode: TGroupBox
    Left = 0
    Top = 0
    Width = 106
    Height = 41
    Caption = 'Code'
    TabOrder = 4
    object EdCode: TEdit
      Left = 0
      Top = 16
      Width = 100
      Height = 21
      TabOrder = 0
    end
  end
  object GBAn: TGroupBox
    Left = 112
    Top = 0
    Width = 49
    Height = 41
    Caption = 'Année'
    TabOrder = 5
    object EdAn: TEdit
      Left = 0
      Top = 16
      Width = 41
      Height = 21
      TabOrder = 0
      Text = '2002'
    end
  end
  object GBValeur: TGroupBox
    Left = 320
    Top = 0
    Width = 57
    Height = 41
    Caption = 'Valeur'
    TabOrder = 6
    object EdValeur: TEdit
      Left = 0
      Top = 16
      Width = 80
      Height = 21
      TabOrder = 0
    end
  end
  object GBProduit: TGroupBox
    Left = 168
    Top = 0
    Width = 145
    Height = 41
    Caption = 'Produit'
    TabOrder = 7
    object EdProduit: TEdit
      Left = 0
      Top = 16
      Width = 145
      Height = 21
      TabOrder = 0
    end
  end
end
