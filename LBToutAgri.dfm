object LBToutAgriFrm: TLBToutAgriFrm
  Left = 2
  Top = 107
  Width = 171
  Height = 519
  Caption = 'Les Agriculteurs'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object PBas: TPanel
    Left = 0
    Top = 422
    Width = 163
    Height = 70
    Align = alBottom
    TabOrder = 0
    object BtBnOK: TBitBtn
      Left = 8
      Top = 40
      Width = 72
      Height = 25
      TabOrder = 0
      OnClick = BtBnOKClick
      Kind = bkOK
    end
    object BtBnPasOK: TBitBtn
      Left = 88
      Top = 40
      Width = 72
      Height = 25
      TabOrder = 1
      OnClick = BtBnPasOKClick
      Kind = bkAbort
    end
    object BtBnTous: TBitBtn
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Tous'
      TabOrder = 2
      OnClick = BtBnTousClick
    end
    object BtBnAucun: TBitBtn
      Left = 88
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Aucun'
      TabOrder = 3
      OnClick = BtBnAucunClick
    end
  end
  object ChLB: TCheckListBox
    Left = 0
    Top = 0
    Width = 163
    Height = 422
    OnClickCheck = ChLBClickCheck
    Align = alClient
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 1
  end
end
