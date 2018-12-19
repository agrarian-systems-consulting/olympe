object LBCompAgriFrm: TLBCompAgriFrm
  Left = 242
  Top = 87
  Width = 170
  Height = 480
  Caption = 'Les Agriculteurs'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object ChLB: TCheckListBox
    Left = 0
    Top = 0
    Width = 162
    Height = 373
    Align = alClient
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 0
  end
  object PBas: TPanel
    Left = 0
    Top = 373
    Width = 162
    Height = 80
    Align = alBottom
    TabOrder = 1
    object BtBnFermer: TBitBtn
      Left = 88
      Top = 40
      Width = 75
      Height = 25
      TabOrder = 0
      OnClick = BtBnFermerClick
      Kind = bkClose
    end
    object BtBnTous: TBitBtn
      Left = 88
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Tous'
      TabOrder = 1
      OnClick = BtBnTousClick
    end
    object BtBnAucun: TBitBtn
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Aucun'
      TabOrder = 2
      OnClick = BtBnAucunClick
    end
  end
end
