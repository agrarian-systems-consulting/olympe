object ImpDeltaFrm: TImpDeltaFrm
  Left = 265
  Top = 189
  Width = 239
  Height = 177
  Align = alRight
  Caption = 'Import Delta'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GBFicCSV: TGroupBox
    Left = 0
    Top = 0
    Width = 224
    Height = 150
    Align = alLeft
    Caption = 'Fichier CSV *.csv'
    Color = clMoneyGreen
    ParentColor = False
    TabOrder = 0
    DesignSize = (
      224
      150)
    object EdFicCsv: TEdit
      Left = 16
      Top = 16
      Width = 200
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnClick = EdFicCsvClick
    end
  end
  object RGSeparateurCsv: TRadioGroup
    Left = 0
    Top = 56
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
    Left = 0
    Top = 96
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
  object BtBnOK: TBitBtn
    Left = 144
    Top = 88
    Width = 75
    Height = 25
    TabOrder = 3
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object BtBnPasOk: TBitBtn
    Left = 144
    Top = 112
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkAbort
  end
  object OpenDialogFicCsv: TOpenDialog
    DefaultExt = '*.csv'
    Filter = 'fichier *.csv|*.csv'
    Left = 144
    Top = 56
  end
end
