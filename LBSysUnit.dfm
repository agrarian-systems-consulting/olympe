object LBSysUnitFrm: TLBSysUnitFrm
  Left = 795
  Top = 133
  Width = 181
  Height = 327
  Caption = 'Syst'#232'mes d'#39'Unit'#233
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnActivate = FormActivate
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LB: TListBox
    Left = 0
    Top = 25
    Width = 173
    Height = 275
    Align = alClient
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 0
    OnDblClick = LBDblClick
  end
  object PanUnite: TPanel
    Left = 0
    Top = 0
    Width = 173
    Height = 25
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 0
      Top = 8
      Width = 161
      Height = 13
      Caption = 'Atelier        Entreprise         R'#233'gion'
    end
  end
end
