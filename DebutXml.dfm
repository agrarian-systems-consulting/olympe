object DebutXmlFrm: TDebutXmlFrm
  Left = 198
  Top = 114
  Width = 696
  Height = 480
  Caption = 'DebutXmlFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabDuree: TLabel
    Left = 368
    Top = 48
    Width = 37
    Height = 16
    Caption = 'Dur'#233'e'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object BitBtn1: TBitBtn
    Left = 256
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Animation'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 256
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Lire'
    TabOrder = 1
    OnClick = BitBtn2Click
  end
  object EdDuree: TEdit
    Left = 408
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'EdDuree'
  end
  object OpenDialog: TOpenDialog
    DefaultExt = '*.xml'
    Filter = 'xml|*.xml'
    Left = 88
    Top = 48
  end
end
