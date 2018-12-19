inherited FenRepartDefFrm: TFenRepartDefFrm
  Left = 580
  Top = 140
  Width = 265
  Height = 552
  Caption = 'R'#233'partition D'#233'finition'
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabelModifie: TLabel [0]
    Left = 216
    Top = 32
    Width = 13
    Height = 16
    Caption = 'M'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object LabTotPcent: TLabel [1]
    Left = 56
    Top = 384
    Width = 50
    Height = 13
    Caption = 'Total en %'
  end
  inherited Panell: TPanel
    Top = 403
    Width = 257
    Height = 115
    inherited BoutFermer: TBitBtn
      Left = 184
      Top = 56
      Width = 50
    end
    inherited BtBnQuitter: TBitBtn
      Left = 184
    end
    object BtBn100: TBitBtn
      Left = 8
      Top = 8
      Width = 25
      Height = 21
      Caption = '100'
      TabOrder = 2
      OnClick = BtBn100Click
    end
    object BtBnEgal: TBitBtn
      Left = 40
      Top = 8
      Width = 41
      Height = 21
      Caption = '100/12'
      TabOrder = 3
      OnClick = BtBnEgalClick
    end
    object BtBn0: TBitBtn
      Left = 88
      Top = 8
      Width = 33
      Height = 21
      Caption = '0'
      TabOrder = 4
      OnClick = BtBn0Click
    end
    object BtBnMaz: TBitBtn
      Left = 128
      Top = 8
      Width = 49
      Height = 21
      Caption = '0 partout'
      TabOrder = 5
      OnClick = BtBnMazClick
    end
    object BtBnACopier: TBitBtn
      Left = 8
      Top = 32
      Width = 49
      Height = 25
      Caption = 'A Copier'
      TabOrder = 6
      OnClick = BtBnACopierClick
    end
    object BtBnReste: TBitBtn
      Left = 128
      Top = 30
      Width = 49
      Height = 25
      Caption = 'Le Reste'
      TabOrder = 7
      OnClick = BtBnResteClick
    end
    object BtBnCopier: TBitBtn
      Left = 68
      Top = 30
      Width = 49
      Height = 25
      Caption = 'Copier'
      TabOrder = 8
      OnClick = BtBnCopierClick
    end
    object BtBnCopieRepart: TBitBtn
      Left = 8
      Top = 56
      Width = 169
      Height = 25
      Caption = 'Copier Autre Repartition'
      TabOrder = 9
      OnClick = BtBnCopieRepartClick
    end
    object BtBnSup: TBitBtn
      Left = 8
      Top = 88
      Width = 75
      Height = 25
      Caption = 'Supprimer'
      Enabled = False
      TabOrder = 10
    end
  end
  object GBCode: TGroupBox
    Left = 104
    Top = 8
    Width = 106
    Height = 41
    Caption = 'Code'
    TabOrder = 1
    object EdCode: TEdit
      Left = 0
      Top = 16
      Width = 100
      Height = 21
      TabOrder = 0
      OnKeyPress = EdCodeKeyPress
    end
  end
  object LaGrille: TStringGrid
    Left = 0
    Top = 48
    Width = 201
    Height = 329
    ColCount = 4
    FixedColor = 13693007
    RowCount = 13
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goAlwaysShowEditor]
    TabOrder = 2
    OnKeyPress = LaGrilleKeyPress
    OnSelectCell = LaGrilleSelectCell
    OnSetEditText = LaGrilleSetEditText
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
    Top = 376
    Width = 73
    Height = 21
    TabOrder = 3
  end
  object GBCategorie: TGroupBox
    Left = 0
    Top = 8
    Width = 106
    Height = 41
    Caption = 'Categorie'
    TabOrder = 4
    object EdCategorie: TEdit
      Left = 0
      Top = 16
      Width = 100
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
  end
end
