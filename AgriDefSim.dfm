object AgriDefSimFrm: TAgriDefSimFrm
  Left = 246
  Top = 106
  Width = 714
  Height = 594
  HelpContext = 910
  Caption = 'Caract'#233'ristiques de la Simulation'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabelModifie: TLabel
    Left = 616
    Top = 160
    Width = 69
    Height = 20
    Caption = 'Modifi'#233' !'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object RGAlea: TRadioGroup
    Tag = 1
    Left = 0
    Top = 160
    Width = 145
    Height = 81
    Caption = 'Alea'
    Color = 13693007
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    Items.Strings = (
      'Sans'
      'Avec')
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    OnClick = RGAleaClick
  end
  object GBPrix: TGroupBox
    Left = 152
    Top = 152
    Width = 457
    Height = 73
    Caption = 'PRIX'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 1
    Visible = False
    object LabPProduit: TLabel
      Left = 24
      Top = 24
      Width = 42
      Height = 16
      Caption = 'Produit'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabPCharge: TLabel
      Left = 24
      Top = 48
      Width = 44
      Height = 16
      Caption = 'Charge'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object CBPProduit: TComboBox
      Left = 200
      Top = 16
      Width = 240
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 16
      ParentFont = False
      TabOrder = 0
      Text = 'CBPProduit'
      OnClick = CBPProduitClick
    end
    object CBPCharge: TComboBox
      Left = 200
      Top = 48
      Width = 240
      Height = 24
      ItemHeight = 16
      TabOrder = 1
      Text = 'CBPCharge'
      OnClick = CBPChargeClick
    end
    object CBSTPProduit: TComboBox
      Left = 88
      Top = 16
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 2
      Text = 'CBSTPProduit'
      OnClick = CBSTPProduitClick
      Items.Strings = (
        'Aucun'
        'Tendance'
        'Sc'#233'nario')
    end
    object CBSTPCharge: TComboBox
      Left = 88
      Top = 48
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 3
      Text = 'CBSTPCharge'
      OnClick = CBSTPChargeClick
      Items.Strings = (
        'Aucun'
        'Tendance'
        'Sc'#233'nario')
    end
  end
  object GBQuantite: TGroupBox
    Left = 152
    Top = 224
    Width = 457
    Height = 113
    Caption = 'QUANTITE'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 2
    Visible = False
    object LabQProduit: TLabel
      Left = 23
      Top = 21
      Width = 42
      Height = 16
      Caption = 'Produit'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabQCharge: TLabel
      Left = 21
      Top = 53
      Width = 44
      Height = 16
      Caption = 'Charge'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabQExt: TLabel
      Left = 22
      Top = 85
      Width = 62
      Height = 16
      Caption = 'Externalit'#233
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object CBQProduit: TComboBox
      Left = 200
      Top = 17
      Width = 240
      Height = 24
      ItemHeight = 16
      TabOrder = 0
      Text = 'CBQProduit'
      OnClick = CBQProduitClick
    end
    object CBQCharge: TComboBox
      Left = 200
      Top = 49
      Width = 240
      Height = 24
      ItemHeight = 16
      TabOrder = 1
      Text = 'CBQCharge'
      OnClick = CBQChargeClick
    end
    object CBQExt: TComboBox
      Left = 200
      Top = 81
      Width = 240
      Height = 24
      ItemHeight = 16
      TabOrder = 2
      Text = 'CBQExt'
      OnClick = CBQExtClick
    end
    object CBSTQProduit: TComboBox
      Left = 88
      Top = 16
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 3
      Text = 'CBSTQProduit'
      OnClick = CBSTQProduitClick
      Items.Strings = (
        'Aucun'
        'Tendance'
        'Sc'#233'nario')
    end
    object CBSTQCharge: TComboBox
      Left = 88
      Top = 48
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 4
      Text = 'CBSTQCharge'
      OnClick = CBSTQChargeClick
      Items.Strings = (
        'Aucun'
        'Tendance'
        'Sc'#233'nario')
    end
    object CBSTQExt: TComboBox
      Left = 88
      Top = 80
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 5
      Text = 'CBSTQExt'
      OnClick = CBSTQExtClick
      Items.Strings = (
        'Aucun'
        'Tendance'
        'Sc'#233'nario')
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 526
    Width = 706
    Height = 41
    Align = alBottom
    TabOrder = 3
    object BoutFermer: TBitBtn
      Left = 552
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkClose
    end
    object BtBnQuitter: TBitBtn
      Left = 632
      Top = 8
      Width = 33
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
    object BtBnStocker: TBitBtn
      Left = 8
      Top = 8
      Width = 25
      Height = 25
      Hint = 'Stocker'
      TabOrder = 2
      Glyph.Data = {
        36030000424D3603000000000000360000002800000010000000100000000100
        18000000000000030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000000000000000000000000000000000
        0000000000000000000000000000000000000000000000C0C0C0C0C0C0000000
        008080008080000000000000000000000000000000000000C0C0C0C0C0C00000
        00008080000000C0C0C0C0C0C000000000808000808000000000000000000000
        0000000000000000C0C0C0C0C0C0000000008080000000C0C0C0C0C0C0000000
        008080008080000000000000000000000000000000000000C0C0C0C0C0C00000
        00008080000000C0C0C0C0C0C000000000808000808000000000000000000000
        0000000000000000000000000000000000008080000000C0C0C0C0C0C0000000
        0080800080800080800080800080800080800080800080800080800080800080
        80008080000000C0C0C0C0C0C000000000808000808000000000000000000000
        0000000000000000000000000000008080008080000000C0C0C0C0C0C0000000
        008080000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000
        00008080000000C0C0C0C0C0C0000000008080000000C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000008080000000C0C0C0C0C0C0000000
        008080000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000
        00008080000000C0C0C0C0C0C0000000008080000000C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000008080000000C0C0C0C0C0C0000000
        008080000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000
        00000000000000C0C0C0C0C0C0000000008080000000C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000C0C0C0C0C0C0000000
        0000000000000000000000000000000000000000000000000000000000000000
        00000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
    end
  end
  object GBEnch: TGroupBox
    Left = 152
    Top = 336
    Width = 457
    Height = 73
    Caption = 'ENCHAINEMENT'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 4
    Visible = False
    object GrilleEnch: TStringGrid
      Left = 8
      Top = 16
      Width = 345
      Height = 120
      ColCount = 10
      DefaultColWidth = 32
      FixedColor = 13693007
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
      TabOrder = 0
      OnKeyPress = GrilleEnchKeyPress
      ColWidths = (
        32
        32
        32
        32
        32
        32
        32
        32
        32
        32)
    end
    object BtReportDroit: TBitBtn
      Left = 376
      Top = 16
      Width = 33
      Height = 25
      Hint = 'Recopie '#224' droite'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = BtReportDroitClick
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
    object ChBRepTout: TCheckBox
      Left = 352
      Top = 48
      Width = 97
      Height = 17
      Hint = 'Report tout ou seult si Vide'
      Caption = 'ReportTout'
      TabOrder = 2
    end
  end
  object GBCas: TGroupBox
    Left = 0
    Top = 0
    Width = 706
    Height = 153
    Align = alTop
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 5
    object LabNom: TLabel
      Left = 24
      Top = 24
      Width = 32
      Height = 16
      Caption = 'Nom '
    end
    object LabVariante: TLabel
      Left = 24
      Top = 48
      Width = 53
      Height = 16
      Caption = 'Variante '
    end
    object LabAn0: TLabel
      Left = 264
      Top = 40
      Width = 79
      Height = 16
      Caption = 'Ann'#233'e d'#233'but '
    end
    object LabMoisOuv: TLabel
      Left = 264
      Top = 64
      Width = 93
      Height = 16
      Caption = 'Mois Ouverture '
    end
    object LabAnMax: TLabel
      Left = 520
      Top = 64
      Width = 67
      Height = 16
      Caption = 'Nb Ann'#233'es'
    end
    object LabZone: TLabel
      Left = 24
      Top = 96
      Width = 79
      Height = 16
      Caption = 'Classification'
    end
    object EdNom: TEdit
      Left = 120
      Top = 16
      Width = 553
      Height = 24
      TabOrder = 0
      Text = 'EdNom'
    end
    object EdVariante: TEdit
      Left = 120
      Top = 48
      Width = 121
      Height = 24
      TabOrder = 1
      Text = 'EdVariante'
    end
    object EdAn0: TEdit
      Left = 384
      Top = 40
      Width = 50
      Height = 24
      TabOrder = 2
      Text = 'EdAn0'
      OnExit = EdAn0Exit
      OnKeyPress = EdAn0KeyPress
    end
    object CBOuv: TComboBox
      Left = 384
      Top = 60
      Width = 121
      Height = 24
      DropDownCount = 12
      ItemHeight = 16
      TabOrder = 3
      Text = 'CBOuv'
      OnChange = CBOuvChange
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12')
    end
    object GrilleCritere: TStringGrid
      Left = 112
      Top = 88
      Width = 529
      Height = 57
      ColCount = 8
      FixedColor = 13693007
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goThumbTracking]
      TabOrder = 4
      OnClick = GrilleCritereClick
      ColWidths = (
        64
        64
        65
        64
        64
        64
        64
        64)
      RowHeights = (
        24
        24)
    end
    object CBNbAnnee: TComboBox
      Left = 592
      Top = 56
      Width = 65
      Height = 24
      ItemHeight = 16
      TabOrder = 5
      Text = '  10'
      OnClick = CBNbAnneeClick
      Items.Strings = (
        '  10'
        '  20'
        '  30'
        '  40'
        '  50'
        '  60'
        '  70'
        '  80'
        '  90'
        '100 ')
    end
  end
  object BtBnNotes: TBitBtn
    Left = 0
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Notes'
    TabOrder = 6
    OnClick = BtBnNotesClick
    Glyph.Data = {
      22050000424D2205000000000000360000002800000014000000150000000100
      180000000000EC04000000000000000000000000000000000000C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C08D492E8F4423873E1D8B3C189D451BB34F1FCF5B24DC6126C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0D2B8A1DBE1AFDECA9DD1AF84BD8D64A367438C492C823B1D873A18A1471CDB
      6127C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0CDC3B4
      CFFFDAC5F6C9D7EAB0BFE491C7EB9DDCE3A3D8D498D8B27D753519D35C25C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0CCC0AEC9F7D0D4
      EDC1E2B062C99D49D1AB57DBBC6DDBCE7BD4D67F9361328345218D421CA4481C
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0CDC0B0D1FBDAD7DFA3D8A2
      51BD9142BB8E41C68D48C58D44CA8A41D58A52DBA070DDA56D85532DC0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0CDC1B0C9FAD2E1CE86DCA54BC7A042
      CA9D46CD9B4AC89649C28C40C37D49CB8D6AE8A87397552BC0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0CCC1B1D2F7CFE6BF6BE2AE4BD3AA45CFA643D6
      A44AD5A24ACD9840D0894ADC9E6BDAA267A64C1FC0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0CCC3B5D1EBB2EBBB58EDBB53DAB443DCB044E3AF4DDBAB
      48D5A13FDB944AF1B271B77F4CC65521C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0CCC4B7E0DF9EF0C15FEDC45FE2BD4CE4BA48EAB84CE7B547E1AB40
      E69D49FEC0759A582FDA5C24C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0CCC1B2E3D585ECCC75F1CC74E2C45EE1C156ECC057EEBE50E7B441F4AC4AF1
      B76EA0481FC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0D2B79F
      EDD384EDD890EED386E0CC71E4CA6BEFC96CEBC660E7BC4EFEB753BE8852C552
      20C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0DAAB85EDDF93E7
      DF9FECDC96E2D584E4D37FE7D07CE6CE72EAC665FEBB6596552DC0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0E0AD8BF2E4B8FAEEC3F4E6
      B8E8E2A1E8DC94F3DF98F6DD8FF3D27DE9A65A9C451DC0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0DD998A97A1A9DFCDBA9FB7BBDCCBBA
      A0A9A8E7CCABBDC0B6F4D5AA96856BA3441BC0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0AB847664A4B7888B92699DAA8B89916795A796
      8C92729CABBB9A9C61757FBA4D1FC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0}
  end
  object GBSerie: TGroupBox
    Left = 616
    Top = 208
    Width = 81
    Height = 145
    Caption = 'Donn'#233'es pour'
    TabOrder = 7
    Visible = False
    object LBResultatPour: TListBox
      Left = 2
      Top = 15
      Width = 77
      Height = 128
      Align = alClient
      Color = clInfoBk
      ItemHeight = 13
      Items.Strings = (
        ' 1-10'
        '11-20'
        '21-30'
        '31-40')
      TabOrder = 0
      Visible = False
      OnClick = LBResultatPourClick
    end
  end
end
