object TravCalFrm: TTravCalFrm
  Left = 198
  Top = 262
  Width = 1027
  Height = 480
  Caption = 'TravCalFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnHelp = FormHelp
  DesignSize = (
    1002
    446)
  PixelsPerInch = 96
  TextHeight = 13
  object BtBnFermer: TBitBtn
    Left = 923
    Top = 408
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    TabOrder = 0
    Kind = bkClose
  end
  object GB: TGroupBox
    Left = 368
    Top = 24
    Width = 601
    Height = 377
    Hint = 'Cliquer pour choisir couleur et motif'
    Caption = 'Couleurs'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    object LabCoulMotif: TLabel
      Left = 8
      Top = 32
      Width = 36
      Height = 13
      Caption = 'Couleur'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object BtBnQuitter: TBitBtn
    Left = 867
    Top = 408
    Width = 50
    Height = 25
    Hint = 'Sortie IMMEDIATE SANS stocker'
    Anchors = [akRight, akBottom]
    Caption = 'Quitter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = BtBnQuitterClick
  end
  object GBOrdre: TGroupBox
    Left = 168
    Top = 192
    Width = 185
    Height = 241
    Caption = 'Ordre d'#39'affichage'
    TabOrder = 3
    object LBAtelier: TListBox
      Left = 16
      Top = 16
      Width = 153
      Height = 177
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 0
      OnClick = LBAtelierClick
    end
    object PClasst: TPanel
      Left = 16
      Top = 200
      Width = 153
      Height = 33
      TabOrder = 1
      object BtClHaut: TBitBtn
        Left = 37
        Top = 5
        Width = 25
        Height = 24
        Hint = 'Report vers le haut'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        OnClick = BtClHautClick
        Glyph.Data = {
          72010000424D7201000000000000760000002800000011000000150000000100
          040000000000FC000000C40E0000C40E00001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
          7777700000007777777777777777700000007777700000007777700000007777
          7000000077777000000077777000000077777000000077777000000077777000
          0000777770000000777770000000777770000000777770000000777770000000
          7777700000007777700000007777700000007000000000000000700000007700
          0000000000077000000077700000000000777000000077770000000007777000
          0000777770000000777770000000777777000007777770000000777777700077
          7777700000007777777707777777700000007777777777777777700000007777
          77777777777770000000777777777777777770000000}
      end
      object BtClBas: TBitBtn
        Left = 93
        Top = 5
        Width = 25
        Height = 24
        Hint = 'Report vers le Bas'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 1
        OnClick = BtClBasClick
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
    end
  end
  object GBGeneral: TGroupBox
    Left = 8
    Top = 8
    Width = 345
    Height = 161
    TabOrder = 4
    object LabCalendrier: TLabel
      Left = 8
      Top = 8
      Width = 69
      Height = 16
      Caption = 'Calendriers'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabAn: TLabel
      Left = 168
      Top = 8
      Width = 39
      Height = 16
      Caption = 'Ann'#233'e'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabNbOuv: TLabel
      Left = 168
      Top = 65
      Width = 86
      Height = 16
      Caption = 'Nb travailleurs'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object LabCal: TLabel
      Left = 16
      Top = 136
      Width = 5
      Height = 16
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LBCalendrier: TListBox
      Left = 8
      Top = 32
      Width = 121
      Height = 97
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 0
      OnClick = LBCalendrierClick
    end
    object CBAn: TComboBox
      Left = 168
      Top = 32
      Width = 81
      Height = 21
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 1
      OnClick = CBAnClick
    end
    object EdNbOuv: TEdit
      Left = 168
      Top = 89
      Width = 81
      Height = 24
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Text = '0'
      OnExit = EdNbOuvExit
      OnKeyPress = EdNbOuvKeyPress
    end
    object BtBnCalculer: TBitBtn
      Left = 216
      Top = 120
      Width = 75
      Height = 25
      Caption = 'Calculer'
      TabOrder = 3
      Visible = False
      OnClick = BtBnCalculerClick
    end
  end
  object GBResultat: TGroupBox
    Left = 8
    Top = 192
    Width = 121
    Height = 129
    Caption = 'Resultats'
    TabOrder = 5
    object BtBnGraphe: TBitBtn
      Left = 22
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Graphe'
      TabOrder = 0
      OnClick = BtBnGrapheClick
    end
    object BtBnCalcul: TBitBtn
      Left = 22
      Top = 48
      Width = 75
      Height = 25
      Caption = 'Valeurs'
      TabOrder = 1
      OnClick = BtBnCalculClick
    end
    object BtBnTotalBesoins: TBitBtn
      Left = 24
      Top = 80
      Width = 75
      Height = 25
      Caption = 'Total Besoins'
      TabOrder = 2
      OnClick = BtBnTotalBesoinsClick
    end
  end
  object GBPresentation: TGroupBox
    Left = 8
    Top = 328
    Width = 121
    Height = 105
    Caption = 'Modif Presentation'
    TabOrder = 6
    object BtBnLegende: TBitBtn
      Left = 22
      Top = 24
      Width = 75
      Height = 25
      Caption = 'L'#233'gende'
      TabOrder = 0
      OnClick = BtBnLegendeClick
    end
    object BtBnOrdre: TBitBtn
      Left = 22
      Top = 56
      Width = 75
      Height = 25
      Caption = 'Ordre Affichage'
      TabOrder = 1
      OnClick = BtBnOrdreClick
    end
  end
  object BtBnAide: TBitBtn
    Left = 136
    Top = 424
    Width = 25
    Height = 25
    Caption = '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    OnClick = BtBnAideClick
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    Left = 400
    Top = 408
  end
end
