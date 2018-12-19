object TVDonProcedureFrm: TTVDonProcedureFrm
  Left = 754
  Top = 102
  Width = 264
  Height = 525
  Anchors = [akTop, akRight]
  Caption = 'Donn'#233'es et R'#233'sultats'
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
  object PanBas: TPanel
    Left = 0
    Top = 448
    Width = 256
    Height = 50
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
    Top = 57
    Width = 256
    Height = 391
    Align = alClient
    Caption = 'Donn'#233'es A Calculer'
    TabOrder = 1
    object TVDon: TTreeView
      Left = 2
      Top = 15
      Width = 252
      Height = 374
      Align = alClient
      Anchors = [akLeft, akTop, akBottom]
      Color = clInfoBk
      Indent = 19
      ReadOnly = True
      TabOrder = 0
      OnClick = TVDonClick
    end
  end
  object GBRes: TGroupBox
    Left = 0
    Top = 57
    Width = 256
    Height = 391
    Align = alClient
    Caption = 'Resultats NON Modifiables'
    TabOrder = 2
    object TVRes: TTreeView
      Left = 2
      Top = 15
      Width = 252
      Height = 374
      Align = alClient
      Color = clInfoBk
      Indent = 19
      ReadOnly = True
      TabOrder = 0
      OnClick = TVResClick
    end
  end
  object PanHaut: TPanel
    Left = 0
    Top = 0
    Width = 256
    Height = 57
    Align = alTop
    Caption = 'PanHaut'
    TabOrder = 3
    object RG: TRadioGroup
      Left = 1
      Top = 1
      Width = 254
      Height = 55
      Align = alClient
      Caption = 'Donn'#233'es '#224' Utiliser'
      Color = clGradientActiveCaption
      ItemIndex = 0
      Items.Strings = (
        'Donn'#233'es A calculer'
        'R'#233'sultats NON Modifiables')
      ParentColor = False
      TabOrder = 0
      OnClick = RGClick
    end
  end
end
