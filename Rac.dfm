object RacFrm: TRacFrm
  Left = 1041
  Top = 98
  Width = 214
  Height = 500
  Caption = 'RacFrm'
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
  object PanH: TPanel
    Left = 0
    Top = 0
    Width = 206
    Height = 41
    Align = alTop
    TabOrder = 0
  end
  object PanB: TPanel
    Left = 0
    Top = 432
    Width = 206
    Height = 41
    Align = alBottom
    TabOrder = 1
  end
  object LBRac: TListBox
    Left = 0
    Top = 41
    Width = 206
    Height = 391
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 20
    ParentFont = False
    TabOrder = 2
    OnClick = LBRacClick
  end
end
