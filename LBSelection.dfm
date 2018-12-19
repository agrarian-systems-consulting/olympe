object LBSelectionFrm: TLBSelectionFrm
  Left = 207
  Top = 107
  Width = 131
  Height = 96
  Caption = 'Selection '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object LB: TListBox
    Left = 0
    Top = 0
    Width = 121
    Height = 49
    Color = clInfoBk
    ItemHeight = 13
    Items.Strings = (
      'Manuel'
      'Tri'
      'Addition')
    TabOrder = 0
    OnDblClick = LBDblClick
  end
  object BtBnOK: TBitBtn
    Left = -8
    Top = 48
    Width = 65
    Height = 20
    TabOrder = 1
    OnClick = BtBnOKClick
    Kind = bkOK
  end
  object BtBnPasOK: TBitBtn
    Left = 56
    Top = 48
    Width = 65
    Height = 20
    TabOrder = 2
    OnClick = BtBnPasOKClick
    Kind = bkAbort
  end
end
