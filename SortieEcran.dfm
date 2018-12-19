object SortieEcranFrm: TSortieEcranFrm
  Left = 192
  Top = 107
  Width = 696
  Height = 480
  Caption = 'SortieEcranFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TRichEdit
    Left = 0
    Top = 0
    Width = 688
    Height = 405
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Fixedsys'
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 405
    Width = 688
    Height = 41
    Align = alBottom
    TabOrder = 1
    object BitBtn1: TBitBtn
      Left = 584
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      Kind = bkClose
    end
  end
end
