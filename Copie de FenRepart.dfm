inherited FenRepartFrm: TFenRepartFrm
  Left = 205
  Top = 193
  Width = 399
  Height = 501
  Caption = 'Repartition'
  OnActivate = FormActivate
  OnCreate = nil
  PixelsPerInch = 96
  TextHeight = 13
  object LabPcent: TLabel [0]
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
  object LabVal: TLabel [1]
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
  object LabTotPcent: TLabel [2]
    Left = 56
    Top = 408
    Width = 50
    Height = 13
    Caption = 'Total en %'
  end
  object LabTotalVal: TLabel [3]
    Left = 224
    Top = 408
    Width = 24
    Height = 13
    Caption = 'Total'
  end
  inherited Panell: TPanel
    Top = 423
    Width = 391
    Height = 44
    inherited BoutFermer: TBitBtn
      Left = 232
    end
    inherited BtBnQuitter: TBitBtn
      Left = 312
    end
    object BtBnOk: TBitBtn
      Left = 16
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 2
      OnClick = BtBnOkClick
      Kind = bkOK
    end
  end
  object LaGrille: TStringGrid
    Left = 0
    Top = 56
    Width = 361
    Height = 345
    ColCount = 7
    FixedColor = 13693007
    RowCount = 13
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goAlwaysShowEditor]
    TabOrder = 1
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
  object GBCode: TGroupBox
    Left = 0
    Top = 0
    Width = 106
    Height = 41
    Caption = 'Code'
    TabOrder = 2
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
    Caption = 'Ann'#233'e'
    TabOrder = 3
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
    TabOrder = 4
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
    TabOrder = 5
    object EdProduit: TEdit
      Left = 0
      Top = 16
      Width = 145
      Height = 21
      TabOrder = 0
    end
  end
  object EdTotPcent: TEdit
    Left = 112
    Top = 400
    Width = 73
    Height = 21
    TabOrder = 6
  end
  object EdTotValeur: TEdit
    Left = 256
    Top = 400
    Width = 73
    Height = 21
    TabOrder = 7
  end
end
