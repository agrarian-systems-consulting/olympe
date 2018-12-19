object TypePlactFrm: TTypePlactFrm
  Left = 901
  Top = 110
  Width = 123
  Height = 183
  Caption = 'TypePlactFrm'
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
  object RGInteret: TRadioGroup
    Left = 0
    Top = 0
    Width = 89
    Height = 73
    Caption = 'Interet'
    Color = clInfoBk
    ItemIndex = 0
    Items.Strings = (
      'Annuel'
      'A la Fin')
    ParentColor = False
    TabOrder = 0
  end
  object RGEP: TRadioGroup
    Left = 0
    Top = 72
    Width = 89
    Height = 50
    Caption = 'E/P'
    Color = clInfoBk
    ItemIndex = 0
    Items.Strings = (
      'Entreprise'
      'Priv'#233)
    ParentColor = False
    TabOrder = 1
  end
  object BtBnOk: TBitBtn
    Left = 0
    Top = 120
    Width = 75
    Height = 25
    TabOrder = 2
    OnClick = BtBnOkClick
    Kind = bkOK
  end
end
