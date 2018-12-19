object QuelExcelCSVFrm: TQuelExcelCSVFrm
  Left = 318
  Top = 446
  Width = 421
  Height = 146
  Caption = 'Envoi sur Tableur CSV'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnActivate = FormActivate
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object EdNomExcel: TEdit
    Left = 0
    Top = 0
    Width = 393
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Text = 'EdNomExcel'
  end
  object BtBnParcourir: TBitBtn
    Left = 320
    Top = 24
    Width = 73
    Height = 25
    Caption = 'Parcourir'
    TabOrder = 1
    OnClick = BtBnParcourirClick
  end
  object BtBnAnnuler: TBitBtn
    Left = 320
    Top = 56
    Width = 75
    Height = 25
    TabOrder = 2
    OnClick = BtBnAnnulerClick
    Kind = bkAbort
  end
  object RG: TRadioGroup
    Left = 8
    Top = 24
    Width = 97
    Height = 65
    Caption = 'A Ecrire'
    ItemIndex = 0
    Items.Strings = (
      'A la suite'
      'Mettre '#224' zero'
      'Autre Fichier')
    TabOrder = 3
  end
  object BtBnOK: TBitBtn
    Left = 240
    Top = 56
    Width = 75
    Height = 25
    TabOrder = 4
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object BtBnAide: TBitBtn
    Left = 184
    Top = 72
    Width = 25
    Height = 25
    Caption = '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = BtBnAideClick
  end
  object ODExcel: TOpenDialog
    DefaultExt = 'csv'
    Filter = 'tableur stocke en CSV|*.csv'
    Left = 216
    Top = 24
  end
end
