object EntreChaineFrm: TEntreChaineFrm
  Left = 192
  Top = 107
  Width = 271
  Height = 105
  Caption = 'EntreChaineFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object LabAAfficher: TLabel
    Left = 8
    Top = 8
    Width = 61
    Height = 13
    Caption = 'LabAAfficher'
  end
  object Edit1: TEdit
    Left = 8
    Top = 24
    Width = 249
    Height = 21
    TabOrder = 0
    Text = 'EdNom'
    OnKeyPress = Edit1KeyPress
  end
  object BtBnOk: TBitBtn
    Left = 8
    Top = 48
    Width = 75
    Height = 25
    TabOrder = 1
    OnClick = BtBnOkClick
    Kind = bkOK
  end
  object BtBnAnnul: TBitBtn
    Left = 88
    Top = 48
    Width = 75
    Height = 25
    TabOrder = 2
    OnClick = BtBnAnnulClick
    Kind = bkCancel
  end
end
