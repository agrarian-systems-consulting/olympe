object LBProduitFrm: TLBProduitFrm
  Left = 192
  Top = 107
  Width = 175
  Height = 114
  Caption = 'Produits'
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
    Width = 167
    Height = 87
    Align = alClient
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 0
    OnClick = LBClick
  end
end
