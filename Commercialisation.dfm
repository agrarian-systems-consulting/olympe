object CommercialisationFrm: TCommercialisationFrm
  Left = 201
  Top = 137
  Width = 757
  Height = 537
  Caption = 'Commercialisation'
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
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabProduit: TLabel
    Left = 0
    Top = 0
    Width = 76
    Height = 16
    Caption = 'LabProduit'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelModifie: TLabel
    Left = 632
    Top = 0
    Width = 52
    Height = 16
    Caption = 'Modifi'#233
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    Visible = False
  end
  object LabAnnee: TLabel
    Left = 304
    Top = 2
    Width = 125
    Height = 16
    Caption = 'Ann'#233'e de Production'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object GrilleProd: TStringGrid
    Left = 0
    Top = 24
    Width = 745
    Height = 121
    ColCount = 21
    FixedColor = 13693007
    RowCount = 4
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 0
    OnEnter = GrilleProdEnter
    OnKeyPress = GrilleKeyPress
    OnSelectCell = GrilleProdSelectCell
  end
  object GrilleComm: TStringGrid
    Left = 0
    Top = 152
    Width = 745
    Height = 281
    ColCount = 11
    FixedColor = 13693007
    RowCount = 26
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing, goAlwaysShowEditor]
    TabOrder = 1
    OnEnter = GrilleCommEnter
    OnKeyPress = GrilleKeyPress
    OnSelectCell = GrilleCommSelectCell
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
      24
      24)
  end
  object BtBnProduit: TBitBtn
    Left = 496
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Produits'
    TabOrder = 2
    OnClick = BtBnProduitClick
  end
  object CBAn: TComboBox
    Left = 432
    Top = 0
    Width = 64
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    Text = 'Ann'#233'e'
    OnClick = CBAnClick
  end
  object PanBas: TPanel
    Left = 0
    Top = 443
    Width = 749
    Height = 67
    Align = alBottom
    TabOrder = 4
    object LabQuant: TLabel
      Left = 344
      Top = 1
      Width = 49
      Height = 13
      Caption = 'Quantit'#233
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabVal: TLabel
      Left = 416
      Top = 1
      Width = 37
      Height = 13
      Caption = 'Valeur'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BtBnQuitter: TBitBtn
      Left = 688
      Top = 33
      Width = 50
      Height = 25
      Hint = 'Sortie IMMEDIATE SANS stocker'
      Caption = 'Quitter'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = BtBnQuitterClick
    end
    object BoutFermer: TBitBtn
      Left = 616
      Top = 33
      Width = 75
      Height = 25
      Hint = 'Fermer'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Kind = bkClose
    end
    object ChBRepTout: TCheckBox
      Left = 104
      Top = 25
      Width = 81
      Height = 17
      Hint = 'Report tout ou seult si Vide'
      Caption = 'Report Tout'
      Color = clInfoBk
      ParentColor = False
      TabOrder = 2
    end
    object BtBnReportDroit: TBitBtn
      Left = 72
      Top = 17
      Width = 33
      Height = 25
      Hint = 'Report A Droite'
      TabOrder = 3
      OnClick = BtBnReportDroitClick
      Glyph.Data = {
        42010000424D4201000000000000760000002800000015000000110000000100
        040000000000CC000000C40E0000C40E00001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
        7777777770007777777777077777777770007777777777007777777770007777
        7777770007777777700077777777770000777777700077000000000000077777
        7000770000000000000077777000770000000000000007777000770000000000
        0000007770007700000000000000077770007700000000000000777770007700
        0000000000077777700077777777770000777777700077777777770007777777
        7000777777777700777777777000777777777707777777777000777777777777
        777777777000}
    end
    object CBAnCopie: TComboBox
      Left = 272
      Top = 17
      Width = 57
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      Text = 'CBAn'
      OnClick = CBAnCopieClick
    end
    object BtBnCopier: TBitBtn
      Left = 200
      Top = 17
      Width = 75
      Height = 21
      Caption = 'Copier Vers'
      TabOrder = 5
      OnClick = BtBnCopierClick
    end
    object BtBnCopieTout: TBitBtn
      Left = 200
      Top = 41
      Width = 129
      Height = 21
      Caption = 'Copie Vers Tout'
      TabOrder = 6
      OnClick = BtBnCopieToutClick
    end
    object BtBnVenteQ: TBitBtn
      Left = 336
      Top = 17
      Width = 75
      Height = 21
      Caption = 'Vente'
      TabOrder = 7
      OnClick = BtBnVenteQClick
    end
    object BtBnStockQ: TBitBtn
      Left = 336
      Top = 41
      Width = 75
      Height = 21
      Caption = 'Stock'
      TabOrder = 8
      OnClick = BtBnStockQClick
    end
    object BtBnVenteVal: TBitBtn
      Left = 416
      Top = 17
      Width = 75
      Height = 21
      Caption = 'Vente'
      TabOrder = 9
      OnClick = BtBnVenteValClick
    end
    object BtBnStockVal: TBitBtn
      Left = 416
      Top = 41
      Width = 75
      Height = 21
      Caption = 'Stock'
      TabOrder = 10
      OnClick = BtBnStockValClick
    end
    object BtBnReste: TBitBtn
      Left = 8
      Top = 8
      Width = 49
      Height = 25
      Caption = 'Reste'
      TabOrder = 11
      OnClick = BtBnResteClick
    end
    object RgSupprime: TRadioGroup
      Left = 496
      Top = 8
      Width = 113
      Height = 50
      Caption = 'Supprimer'
      Items.Strings = (
        'Produit En Cours'
        'Tous')
      TabOrder = 12
      OnClick = RgSupprimeClick
    end
  end
end
