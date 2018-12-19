object TVChoixCompFrm: TTVChoixCompFrm
  Left = 823
  Top = 225
  Width = 170
  Height = 320
  Caption = 'S'#233'rie Comparaison'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object TV: TTreeView
    Left = 0
    Top = 0
    Width = 162
    Height = 286
    Align = alClient
    Color = clInfoBk
    Indent = 19
    ReadOnly = True
    TabOrder = 0
    OnClick = TVClick
    OnDblClick = TVDblClick
  end
end
