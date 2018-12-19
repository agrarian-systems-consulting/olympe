object EffacerFrm: TEffacerFrm
  Left = 229
  Top = 140
  Width = 696
  Height = 480
  Caption = 'Effacer les donn'#233'es inutilis'#233'es'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabInd: TLabel
    Left = 0
    Top = 8
    Width = 286
    Height = 16
    Caption = 'Cocher les familles d'#39#233'l'#233'ments '#224' nettoyer'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object PanUnite: TPanel
    Left = 17
    Top = 136
    Width = 140
    Height = 73
    Color = clInfoBk
    TabOrder = 0
    object ChLBUnite: TCheckListBox
      Left = 8
      Top = 16
      Width = 130
      Height = 40
      ItemHeight = 13
      Items.Strings = (
        'Unit'#233's'
        'Tva')
      TabOrder = 0
    end
  end
  object PanIndic: TPanel
    Left = 416
    Top = 344
    Width = 140
    Height = 89
    Color = clInfoBk
    TabOrder = 1
    object ChLBIndEtat: TCheckListBox
      Left = 8
      Top = 8
      Width = 95
      Height = 49
      ItemHeight = 13
      Items.Strings = (
        'Indicateur'
        'Etat de Sortie'
        'Comparaison')
      TabOrder = 0
    end
    object BtIndAucun: TBitBtn
      Left = 8
      Top = 64
      Width = 57
      Height = 26
      Caption = 'Aucun'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = BtIndAucunClick
    end
    object BtIndTous: TBitBtn
      Left = 80
      Top = 64
      Width = 57
      Height = 25
      Caption = 'Tous'
      TabOrder = 2
      OnClick = BtIndTousClick
    end
  end
  object GBAgri: TGroupBox
    Left = 352
    Top = 232
    Width = 140
    Height = 49
    Caption = 'Agriculteurs'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 2
    object ChBAgri: TCheckBox
      Left = 8
      Top = 24
      Width = 90
      Height = 17
      Caption = 'Agriculteurs'
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
  end
  object GBEnsemble: TGroupBox
    Left = 504
    Top = 232
    Width = 140
    Height = 49
    Caption = 'Ensembles'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 3
    object ChBEnsemble: TCheckBox
      Left = 11
      Top = 24
      Width = 90
      Height = 17
      Caption = 'Ensemble'
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
  end
  object BtBnFermer: TBitBtn
    Left = 600
    Top = 424
    Width = 75
    Height = 25
    TabOrder = 4
    OnClick = BtBnFermerClick
    Kind = bkClose
  end
  object BtBnEffacer: TBitBtn
    Left = 552
    Top = 312
    Width = 75
    Height = 25
    Caption = 'Nettoyer'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = BtBnOKClick
    Glyph.Data = {
      26040000424D2604000000000000360000002800000010000000150000000100
      180000000000F0030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0000000000000000000000000000000000000C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0
      C0C0808080808080808080000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000
      000000FFFFFFC0C0C0C0C0C0000000C0C0C08080800000008080808080808080
      80000000000000C0C0C0C0C0C0000000FFFFFFFFFFFFC0C0C0C0C0C0000000C0
      C0C0808080000000808080808080808080808080000000C0C0C0C0C0C0000000
      FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
      00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
      C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
      FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
      00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
      C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
      FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
      00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
      C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
      FFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C08080808080808080808080800000
      00808080000000C0C0C0C0C0C0000000FFFFFFFFFFFFC0C0C000000000000000
      0000000000000000808080808080808080808080000000C0C0C0C0C0C0000000
      000000000000000000C0C0C0C0C0C0C0C0C08080808080800000000000000000
      00000000000000C0C0C0C0C0C0000000C0C0C0C0C0C0C0C0C000000000000000
      0000000000000000808080808080808080808080000000C0C0C0000000C0C0C0
      000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000000000000000
      00000000808080000000000000000000FFFFFFFFFFFFC0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0C0C0C0C0C000000080808080
      8080808080000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000
      C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0000000C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0000000000000000000000000000000C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0}
  end
  object GBAlea: TGroupBox
    Left = 504
    Top = 24
    Width = 140
    Height = 65
    Caption = 'Aleas'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 6
    object ChLBAlea: TCheckListBox
      Left = 8
      Top = 16
      Width = 90
      Height = 41
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 16
      Items.Strings = (
        'Prix'
        'Quantit'#233)
      ParentFont = False
      TabOrder = 0
    end
  end
  object GBProduction: TGroupBox
    Left = 344
    Top = 64
    Width = 140
    Height = 145
    Caption = 'Productions'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 7
    object ChLBAtelier: TCheckListBox
      Left = 8
      Top = 16
      Width = 130
      Height = 89
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      Items.Strings = (
        'Cultures'
        'Animaux'
        'Phases de production'
        'Perennes'
        'Vivriers')
      ParentFont = False
      TabOrder = 0
    end
    object BtProAucun: TBitBtn
      Left = 8
      Top = 112
      Width = 57
      Height = 25
      Caption = 'Aucun'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = BtProAucunClick
    end
    object BtProTous: TBitBtn
      Left = 80
      Top = 112
      Width = 57
      Height = 25
      Caption = 'Tous'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = BtProTousClick
    end
  end
  object GBDefinition: TGroupBox
    Left = 176
    Top = 64
    Width = 140
    Height = 257
    Caption = 'D'#233'finitions'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 8
    object ChLBDef: TCheckListBox
      Left = 8
      Top = 16
      Width = 130
      Height = 193
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemHeight = 13
      Items.Strings = (
        'Produits'
        'Charges Ope'
        'Externalit'#233's'
        'Troupeaux'
        'P'#233'riodes de Travail'
        ''
        'Charges Structure'
        'D'#233'penses Diverses'
        'Recettes Diverses'
        ''
        'Recette Famille'
        'D'#233'penses Famille'
        ''
        'Variables')
      ParentFont = False
      TabOrder = 0
    end
    object BtDefAucun: TBitBtn
      Left = 8
      Top = 224
      Width = 57
      Height = 25
      Caption = 'Aucun'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = BtDefAucunClick
    end
    object BtDefTous: TBitBtn
      Left = 80
      Top = 224
      Width = 57
      Height = 25
      Caption = 'Tous'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = BtDefTousClick
    end
  end
  object GBTypologie: TGroupBox
    Left = 352
    Top = 288
    Width = 145
    Height = 57
    Caption = 'Typologie'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 9
    object ChBClassif: TCheckBox
      Left = 8
      Top = 16
      Width = 90
      Height = 17
      Caption = 'Classification'
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
    object ChBTypoAgri: TCheckBox
      Left = 8
      Top = 32
      Width = 97
      Height = 17
      Caption = 'Typo Agriculteurs'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
  end
  object Button1: TButton
    Left = 8
    Top = 32
    Width = 25
    Height = 25
    Caption = ' ?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
    OnClick = Button1Click
  end
end
