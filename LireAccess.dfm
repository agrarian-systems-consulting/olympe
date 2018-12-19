object LireAccessFrm: TLireAccessFrm
  Left = 439
  Top = 536
  Width = 326
  Height = 150
  Caption = 'Lecture en cours ....'
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
    Left = 80
    Top = 16
    Width = 150
    Height = 17
    Min = 0
    Max = 96
    TabOrder = 0
  end
  object ProgressBar1: TProgressBar
    Left = 80
    Top = 72
    Width = 150
    Height = 17
    Min = 0
    Max = 96
    TabOrder = 1
  end
  object OpenDialog: TOpenDialog
    DefaultExt = '*.mdb'
    Filter = 'fichier Access|*.mdb'
    Left = 32
    Top = 32
  end
end
