object LectureDecisionFrm: TLectureDecisionFrm
  Left = 198
  Top = 107
  Width = 696
  Height = 480
  Caption = 'Lecture des Decisions'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RE: TRichEdit
    Left = 384
    Top = 80
    Width = 185
    Height = 257
    Color = clAqua
    Lines.Strings = (
      'RE')
    TabOrder = 0
  end
  object BtBnFichierDecision: TBitBtn
    Left = 48
    Top = 80
    Width = 75
    Height = 25
    Caption = 'Fichier Decision'
    TabOrder = 1
    OnClick = BtBnFichierDecisionClick
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Fichier D'#233'cision|*.csv'
    Left = 40
    Top = 16
  end
end
