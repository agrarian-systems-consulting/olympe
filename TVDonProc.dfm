object TVDonProcFrm: TTVDonProcFrm
  Left = 198
  Top = 107
  Width = 180
  Height = 480
  Caption = 'Donnees Proc'#233'dure'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PanBas: TPanel
    Left = 0
    Top = 413
    Width = 172
    Height = 40
    Align = alBottom
    TabOrder = 0
    object BtBnRafraichir: TBitBtn
      Left = 16
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Rafraichir'
      TabOrder = 0
    end
  end
  object TV: TTreeView
    Left = 0
    Top = 0
    Width = 172
    Height = 413
    Align = alClient
    Color = clInfoBk
    Indent = 19
    ReadOnly = True
    TabOrder = 1
  end
end
