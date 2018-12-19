object TypeAmorFrm: TTypeAmorFrm
  Left = 901
  Top = 429
  Width = 123
  Height = 155
  Caption = 'TypeAmorFrm'
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
  object RGAmor: TRadioGroup
    Left = 8
    Top = 8
    Width = 90
    Height = 89
    Caption = 'Amortissement'
    Color = clInfoBk
    ItemIndex = 0
    Items.Strings = (
      'D'#233'gressif'
      'Lin'#233'aire'
      'Sans')
    ParentColor = False
    TabOrder = 0
  end
  object BtBnOk: TBitBtn
    Left = 8
    Top = 96
    Width = 75
    Height = 25
    TabOrder = 1
    OnClick = BtBnOkClick
    Kind = bkOK
  end
end
