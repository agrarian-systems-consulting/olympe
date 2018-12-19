object ConfigFrm: TConfigFrm
  Left = 390
  Top = 458
  Width = 520
  Height = 135
  Caption = 'Configuration d'#39'Olympe'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object OK: TBitBtn
    Left = 216
    Top = 80
    Width = 65
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = OKClick
  end
  object Annuler: TBitBtn
    Left = 288
    Top = 80
    Width = 57
    Height = 25
    Caption = 'Annuler'
    TabOrder = 1
    OnClick = AnnulerClick
  end
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 497
    Height = 65
    TabOrder = 2
    object Data_path: TLabel
      Left = 8
      Top = 8
      Width = 127
      Height = 16
      Caption = 'Chemin des données'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object exec_path: TLabel
      Left = 8
      Top = 32
      Width = 139
      Height = 16
      Caption = 'Chemin de l'#39'exécutable'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object data_path_edit: TEdit
      Left = 160
      Top = 8
      Width = 329
      Height = 21
      TabOrder = 0
    end
    object exec_path_edit: TEdit
      Left = 160
      Top = 32
      Width = 329
      Height = 21
      TabOrder = 1
    end
  end
end
