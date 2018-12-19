object SorRapFrm: TSorRapFrm
  Left = 256
  Top = 138
  Width = 870
  Height = 500
  Caption = 'SorRapFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PanH: TPanel
    Left = 0
    Top = 0
    Width = 862
    Height = 41
    Align = alTop
    TabOrder = 0
  end
  object PanB: TPanel
    Left = 0
    Top = 432
    Width = 862
    Height = 41
    Align = alBottom
    TabOrder = 1
  end
  object SG: TStringGrid
    Left = 0
    Top = 41
    Width = 862
    Height = 391
    Align = alClient
    FixedColor = clMoneyGreen
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing, goAlwaysShowEditor, goThumbTracking]
    TabOrder = 2
    RowHeights = (
      24
      24
      24
      24
      24)
  end
end
