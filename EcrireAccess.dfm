object EcrireAccessFrm: TEcrireAccessFrm
  Left = 823
  Top = 551
  Width = 310
  Height = 147
  Caption = 'Ecriture Access en cours...'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ProgressBar: TProgressBar
    Left = 72
    Top = 24
    Width = 150
    Height = 17
    Min = 0
    Max = 96
    TabOrder = 0
  end
  object ProgressBar1: TProgressBar
    Left = 72
    Top = 72
    Width = 150
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 1
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'mdb'
    Filter = '*.mdb'
    Left = 8
    Top = 64
  end
end
