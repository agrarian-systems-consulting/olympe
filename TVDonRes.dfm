object TVDonResFrm: TTVDonResFrm
  Left = 198
  Top = 107
  Width = 460
  Height = 497
  Caption = 'Donn'#233'es et R'#233'sultats'
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
    Top = 430
    Width = 452
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
  object GBDon: TGroupBox
    Left = 0
    Top = 0
    Width = 220
    Height = 430
    Align = alLeft
    Caption = 'Donn'#233'es Modifiables'
    TabOrder = 1
    object TVDon: TTreeView
      Left = 2
      Top = 15
      Width = 216
      Height = 413
      Align = alClient
      Anchors = [akLeft, akTop, akBottom]
      Color = clInfoBk
      Indent = 19
      ReadOnly = True
      TabOrder = 0
    end
  end
  object GBRes: TGroupBox
    Left = 229
    Top = 0
    Width = 223
    Height = 430
    Align = alRight
    Caption = 'R'#233'sultats NON Modifiables'
    TabOrder = 2
    object TVRes: TTreeView
      Left = 2
      Top = 15
      Width = 219
      Height = 413
      Align = alClient
      Anchors = [akTop, akRight, akBottom]
      Color = clInfoBk
      Indent = 19
      ReadOnly = True
      TabOrder = 0
    end
  end
end
