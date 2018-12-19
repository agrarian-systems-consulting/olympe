object TVChoixRepartFrm: TTVChoixRepartFrm
  Left = 2
  Top = 113
  Width = 175
  Height = 294
  Caption = 'R'#233'partitions'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object TV: TTreeView
    Left = 0
    Top = 0
    Width = 167
    Height = 267
    Align = alClient
    Color = clInfoBk
    Indent = 19
    ReadOnly = True
    TabOrder = 0
    OnDblClick = TVDblClick
    OnExpanded = TVExpanded
  end
end
