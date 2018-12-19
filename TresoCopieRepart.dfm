object TresoCopieRepartFrm: TTresoCopieRepartFrm
  Left = 198
  Top = 107
  Width = 696
  Height = 480
  Caption = 'Copie de Repartition'
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
  object PanB: TPanel
    Left = 0
    Top = 412
    Width = 688
    Height = 41
    Align = alBottom
    TabOrder = 0
    object BtBnFermer: TBitBtn
      Left = 520
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkClose
    end
    object BtBnQuitter: TBitBtn
      Left = 602
      Top = 8
      Width = 33
      Height = 25
      Caption = 'Quitter'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = BtBnQuitterClick
    end
  end
  object GrilleAgri: TStringGrid
    Left = 0
    Top = 0
    Width = 688
    Height = 412
    Align = alClient
    Color = clInfoBk
    FixedColor = 13693007
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect, goThumbTracking]
    TabOrder = 1
    OnDblClick = GrilleAgriDblClick
  end
end
