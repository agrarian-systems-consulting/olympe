object TypeEmpLTFrm: TTypeEmpLTFrm
  Left = 901
  Top = 97
  Width = 123
  Height = 290
  Caption = 'Type d'#39'Emprunt LT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RGTypeRemb: TRadioGroup
    Left = 0
    Top = 0
    Width = 89
    Height = 73
    Caption = 'RemboursementType Emprunt'
    Color = clInfoBk
    ItemIndex = 0
    Items.Strings = (
      'Constant'
      'Variable'
      'Diff'#233'r'#233)
    ParentColor = False
    TabOrder = 0
  end
  object RGFrequence: TRadioGroup
    Left = 0
    Top = 72
    Width = 89
    Height = 105
    Caption = 'Fr'#233'qence'
    Color = clInfoBk
    ItemIndex = 0
    Items.Strings = (
      'Annuel'
      'Semestriel'
      'Trimestriel'
      'Mensuel')
    ParentColor = False
    TabOrder = 1
  end
  object BtBnOk: TBitBtn
    Left = 0
    Top = 224
    Width = 75
    Height = 25
    TabOrder = 2
    OnClick = BtBnOkClick
    Kind = bkOK
  end
  object RGEP: TRadioGroup
    Left = 0
    Top = 176
    Width = 89
    Height = 50
    Caption = 'E/P'
    Color = clInfoBk
    ItemIndex = 0
    Items.Strings = (
      'Entreprise'
      'Priv'#233)
    ParentColor = False
    TabOrder = 3
  end
end
