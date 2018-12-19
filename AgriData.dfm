object AgriDataFrm: TAgriDataFrm
  Left = -825
  Top = -180
  Width = 246
  Height = 392
  Align = alRight
  Caption = 'AgriDataFrm'
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
  DesignSize = (
    238
    365)
  PixelsPerInch = 96
  TextHeight = 13
  object ImFlecheBas: TImage
    Left = 112
    Top = 120
    Width = 17
    Height = 17
    Picture.Data = {
      07544269746D617072010000424D720100000000000076000000280000001100
      0000150000000100040000000000FC000000C40E0000C40E0000100000000000
      000000000000000080000080000000808000800000008000800080800000C0C0
      C000808080000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFF
      FF00777777777777777770000000777777777777777770000000777777777777
      7777700000007777777707777777700000007777777000777777700000007777
      7700000777777000000077777000000077777000000077770000000007777000
      0000777000000000007770000000770000000000000770000000700000000000
      0000700000007777700000007777700000007777700000007777700000007777
      7000000077777000000077777000000077777000000077777000000077777000
      0000777770000000777770000000777770000000777770000000777770000000
      777770000000777777777777777770000000777777777777777770000000}
  end
  object GBLangue: TGroupBox
    Left = 8
    Top = 216
    Width = 129
    Height = 49
    Caption = 'Langue'
    Color = clSkyBlue
    ParentColor = False
    TabOrder = 0
    object CBLangue: TComboBox
      Left = 16
      Top = 16
      Width = 80
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      Text = 'Fran'#231'ais'
      Items.Strings = (
        'Fran'#231'ais'
        'English'
        'Espanol'
        'Nederlands'
        'Portugues'
        'xxx')
    end
  end
  object RGSeparateurCsv: TRadioGroup
    Left = 8
    Top = 272
    Width = 129
    Height = 41
    Caption = 'S'#233'parateur CSV'
    Color = clSkyBlue
    Columns = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ItemIndex = 0
    Items.Strings = (
      ';'
      ',')
    ParentColor = False
    ParentFont = False
    TabOrder = 1
  end
  object RGSeparateurDecimal: TRadioGroup
    Left = 8
    Top = 312
    Width = 129
    Height = 41
    Caption = 'S'#233'parateur Decimal'
    Color = clSkyBlue
    Columns = 2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ItemIndex = 0
    Items.Strings = (
      '.'
      ',')
    ParentColor = False
    ParentFont = False
    TabOrder = 2
  end
  object GBFicOlympe: TGroupBox
    Left = 8
    Top = 8
    Width = 225
    Height = 57
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Fichier Base  Olympe *.oly'
    Color = clMoneyGreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 3
    DesignSize = (
      225
      57)
    object EdFicOlympe: TEdit
      Left = 16
      Top = 24
      Width = 201
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnClick = EdFicOlympeClick
    end
  end
  object GBFicCSV: TGroupBox
    Left = 8
    Top = 64
    Width = 225
    Height = 57
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Fichier CSV *.csv'
    Color = clMoneyGreen
    ParentColor = False
    TabOrder = 4
    DesignSize = (
      225
      57)
    object EdFicCsv: TEdit
      Left = 16
      Top = 16
      Width = 201
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnClick = EdFicCsvClick
    end
  end
  object BtBnOK: TBitBtn
    Left = 144
    Top = 296
    Width = 75
    Height = 25
    TabOrder = 5
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object BtBnPasOk: TBitBtn
    Left = 144
    Top = 320
    Width = 75
    Height = 25
    TabOrder = 6
    OnClick = BtBnPasOkClick
    Kind = bkAbort
  end
  object GBFicResultat: TGroupBox
    Left = 8
    Top = 144
    Width = 225
    Height = 57
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Fichier R'#233'sultat  *.oly'
    Color = 4259584
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 7
    DesignSize = (
      225
      57)
    object EdFicResultat: TEdit
      Left = 8
      Top = 16
      Width = 209
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnClick = EdFicResultatClick
    end
  end
  object BtBnAide: TBitBtn
    Left = 197
    Top = 224
    Width = 25
    Height = 25
    Caption = '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
    OnClick = BtBnAideClick
  end
  object OpenDialogFicCsv: TOpenDialog
    DefaultExt = '*.csv'
    Filter = 'fichier *.csv|*.csv'
    Left = 152
    Top = 232
  end
  object OpenDialogFicOlympe: TOpenDialog
    DefaultExt = '*.oly'
    Filter = 'Fichier Olympe|*.oly'
    Left = 184
    Top = 232
  end
  object SaveDialogFicResultat: TSaveDialog
    DefaultExt = '*.oly'
    Filter = 'Fichier Olympe|*.oly'
    Left = 152
    Top = 264
  end
end
