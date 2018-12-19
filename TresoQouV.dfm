object TresoQouVFrm: TTresoQouVFrm
  Left = 248
  Top = 152
  Width = 123
  Height = 133
  Caption = 'Type de Tr'#233'sorerie'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RGQouV: TRadioGroup
    Left = 0
    Top = 0
    Width = 81
    Height = 73
    Color = clHighlightText
    ItemIndex = 0
    Items.Strings = (
      'Valeur'
      'Quantit'#233)
    ParentColor = False
    TabOrder = 0
    OnClick = RGQouVClick
  end
  object BtOk: TBitBtn
    Left = 0
    Top = 72
    Width = 81
    Height = 25
    TabOrder = 1
    OnClick = BtOkClick
    Kind = bkOK
  end
end
