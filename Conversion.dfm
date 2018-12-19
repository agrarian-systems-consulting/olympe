inherited ConversionFrm: TConversionFrm
  Left = 250
  Top = 316
  Width = 635
  Height = 300
  Caption = 'Table de Conversion'
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabDonnee: TLabel [0]
    Left = 16
    Top = 48
    Width = 107
    Height = 16
    Caption = 'Monnaie d'#39'origine'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabSortie: TLabel [1]
    Left = 16
    Top = 72
    Width = 84
    Height = 16
    Caption = 'A Convertir En'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object LabChoix: TLabel [2]
    Left = 512
    Top = 0
    Width = 115
    Height = 20
    Caption = 'R'#233'sultats En :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  inherited Panell: TPanel
    Top = 232
    Width = 627
    inherited BoutFermer: TBitBtn
      Left = 312
      Top = -8
      Visible = False
    end
    inherited BtBnQuitter: TBitBtn
      Left = 560
    end
    inherited BtClasser: TButton
      Left = 136
      Visible = False
    end
    inherited PClasst: TPanel
      Left = 211
    end
    inherited ChBRepTout: TCheckBox
      Left = 312
      Top = 8
      Checked = True
      State = cbChecked
    end
    object BtReportDroit: TBitBtn
      Left = 280
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie '#224' droite'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
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
    object BitBtn1: TBitBtn
      Left = 400
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 10
      OnClick = BtBnOkClick
      Kind = bkOK
    end
    object BtBnAbandon: TBitBtn
      Left = 480
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 9
      OnClick = BtBnAnnulClick
      Kind = bkAbort
    end
  end
  inherited Grille0: TStringGrid
    Left = 8
    Top = 96
    Width = 561
    Height = 97
    ColCount = 11
    DefaultColWidth = 48
    RowCount = 3
  end
  inherited PanHaut: TPanel
    Width = 627
    TabOrder = 7
    inherited LabelModifie: TLabel
      Left = 424
    end
    object LabTitre: TLabel
      Left = 8
      Top = 8
      Width = 207
      Height = 20
      Caption = 'Unit'#233' Mon'#233'taire de Sortie'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BtBnAide: TBitBtn
      Left = 232
      Top = 8
      Width = 25
      Height = 25
      Caption = '?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = BtBnAideClick
    end
  end
  object EdMonnaieBase: TEdit [6]
    Left = 160
    Top = 40
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'EdMonnaieBase'
  end
  object EdMonnaieSortie: TEdit [7]
    Left = 160
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'EdMonnaieSortie'
  end
  object RG: TRadioGroup [8]
    Left = 288
    Top = 40
    Width = 121
    Height = 57
    Caption = 'Conversion '#224' partir de'
    Color = clLime
    ItemIndex = 1
    Items.Strings = (
      'franc'
      'euro')
    ParentColor = False
    TabOrder = 4
    OnClick = RGClick
  end
  object CBFrancEuro: TComboBox [9]
    Left = 512
    Top = 8
    Width = 100
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ItemHeight = 20
    ParentFont = False
    TabOrder = 5
    Text = 'CBFrancEuro'
    OnKeyPress = CBFrancEuroKeyPress
  end
  object BtBnMonnaie: TBitBtn [10]
    Left = 520
    Top = 48
    Width = 81
    Height = 25
    Caption = 'Choix Monnaie'
    TabOrder = 6
    OnClick = BtBnMonnaieClick
  end
end
