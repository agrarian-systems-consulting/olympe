object LBSelectionAgriFrm: TLBSelectionAgriFrm
  Left = 207
  Top = 107
  Width = 135
  Height = 128
  Caption = 'Selection '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LB: TListBox
    Left = 0
    Top = 0
    Width = 121
    Height = 65
    Color = clInfoBk
    ItemHeight = 13
    Items.Strings = (
      'Manuel'
      'Tri'
      'Addition'
      'Extraire')
    TabOrder = 0
  end
  object BtBnOK: TBitBtn
    Left = -8
    Top = 64
    Width = 65
    Height = 25
    TabOrder = 1
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object BtBnPasOK: TBitBtn
    Left = 56
    Top = 64
    Width = 65
    Height = 25
    TabOrder = 2
    OnClick = BtBnPasOKClick
    Kind = bkAbort
  end
end
