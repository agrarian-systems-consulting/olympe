object LBConversionFrm: TLBConversionFrm
  Left = 603
  Top = 103
  Width = 174
  Height = 215
  Caption = 'Conversion'
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
  object LB: TListBox
    Left = 0
    Top = 0
    Width = 166
    Height = 188
    Align = alClient
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 0
    OnClick = LBClick
  end
end
