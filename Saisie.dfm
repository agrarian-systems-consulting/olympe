object SaisieFrm: TSaisieFrm
  Left = 204
  Top = 132
  Width = 696
  Height = 480
  Caption = 'Copie de Fichiers'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object LabAPartirde: TLabel
    Left = 16
    Top = 8
    Width = 49
    Height = 13
    Caption = 'A Partir de'
  end
  object Label1: TLabel
    Left = 16
    Top = 40
    Width = 91
    Height = 13
    Caption = 'Repertoire d'#39'origine'
  end
  object Label2: TLabel
    Left = 16
    Top = 64
    Width = 102
    Height = 13
    Caption = 'RepertoireDestination'
  end
  object LabNbCopie: TLabel
    Left = 424
    Top = 336
    Width = 94
    Height = 13
    Caption = 'Nombre de Fichiers '
  end
  object LabDate: TLabel
    Left = 568
    Top = 16
    Width = 42
    Height = 13
    Caption = '22 11 04'
  end
  object EdAPartirDe: TEdit
    Left = 88
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '24/09/2004'
  end
  object EdOrigine: TEdit
    Left = 128
    Top = 32
    Width = 537
    Height = 21
    TabOrder = 1
    Text = 'c:\Olympe En Cours'
  end
  object EdDestination: TEdit
    Left = 128
    Top = 64
    Width = 537
    Height = 21
    TabOrder = 2
    Text = 'c:\Olympe En Cours\AMettreAjour'
  end
  object GBExtension: TGroupBox
    Left = 8
    Top = 88
    Width = 345
    Height = 353
    Caption = 'LesExtensions'
    TabOrder = 3
    object GBCpp: TGroupBox
      Left = 8
      Top = 16
      Width = 97
      Height = 233
      Caption = 'C++'
      TabOrder = 0
      object ChLbCpp: TCheckListBox
        Left = 6
        Top = 16
        Width = 65
        Height = 121
        Color = clInfoBk
        ItemHeight = 13
        Items.Strings = (
          'cpp'
          'h'
          'hse'
          'dfm'
          'ddp'
          'bmp'
          'bpr')
        TabOrder = 0
      end
      object BtTousCpp: TBitBtn
        Left = 6
        Top = 176
        Width = 65
        Height = 25
        Caption = 'Tous'
        TabOrder = 1
        OnClick = BtTousClick
      end
      object BtAucunCpp: TBitBtn
        Left = 6
        Top = 200
        Width = 65
        Height = 25
        Caption = 'Aucun'
        TabOrder = 2
        OnClick = BtAucunClick
      end
      object BtModifCpp: TBitBtn
        Left = 8
        Top = 144
        Width = 65
        Height = 25
        Caption = 'Modifier'
        TabOrder = 3
        OnClick = BtModifChLBClick
      end
    end
    object GBStandard: TGroupBox
      Left = 120
      Top = 16
      Width = 97
      Height = 233
      Caption = 'Standard'
      TabOrder = 1
      object ChLbStandard: TCheckListBox
        Left = 8
        Top = 16
        Width = 65
        Height = 120
        Color = clInfoBk
        ItemHeight = 13
        Items.Strings = (
          'doc'
          'txt'
          'xls'
          'csv')
        TabOrder = 0
      end
      object BtTousStandard: TBitBtn
        Left = 6
        Top = 176
        Width = 65
        Height = 25
        Caption = 'Tous'
        TabOrder = 1
        OnClick = BtTousClick
      end
      object BtAucunStandard: TBitBtn
        Left = 6
        Top = 200
        Width = 65
        Height = 25
        Caption = 'Aucun'
        TabOrder = 2
        OnClick = BtAucunClick
      end
      object BtModifStandard: TBitBtn
        Left = 8
        Top = 144
        Width = 65
        Height = 25
        Caption = 'Modifier'
        TabOrder = 3
        OnClick = BtModifChLBClick
      end
    end
    object GBAutre: TGroupBox
      Left = 224
      Top = 16
      Width = 97
      Height = 233
      Caption = 'Autre'
      TabOrder = 2
      object ChLbAutre: TCheckListBox
        Left = 8
        Top = 16
        Width = 65
        Height = 120
        Color = clInfoBk
        ItemHeight = 13
        Items.Strings = (
          'oly')
        TabOrder = 0
      end
      object BtTousAutre: TBitBtn
        Left = 6
        Top = 176
        Width = 65
        Height = 25
        Caption = 'Tous'
        TabOrder = 1
        OnClick = BtTousClick
      end
      object BtAucunAutre: TBitBtn
        Left = 6
        Top = 200
        Width = 65
        Height = 25
        Caption = 'Aucun'
        TabOrder = 2
        OnClick = BtAucunClick
      end
      object BtModifAutre: TBitBtn
        Left = 8
        Top = 144
        Width = 65
        Height = 25
        Caption = 'Modifier'
        TabOrder = 3
        OnClick = BtModifChLBClick
      end
    end
    object GBAutreExtension: TGroupBox
      Left = 0
      Top = 256
      Width = 337
      Height = 57
      Caption = 'A modifier'
      TabOrder = 3
      object EdAModifier: TEdit
        Left = 8
        Top = 15
        Width = 265
        Height = 21
        TabOrder = 0
      end
      object BtAModifierOK: TBitBtn
        Left = 280
        Top = 16
        Width = 49
        Height = 25
        TabOrder = 1
        OnClick = BtAModifierOKClick
        Kind = bkOK
      end
    end
  end
  object BtQuitter: TBitBtn
    Left = 592
    Top = 400
    Width = 75
    Height = 25
    TabOrder = 4
    Kind = bkClose
  end
  object EdNbCopie: TEdit
    Left = 536
    Top = 328
    Width = 49
    Height = 21
    TabOrder = 5
  end
  object RGAvecCopie: TRadioGroup
    Left = 576
    Top = 136
    Width = 97
    Height = 65
    Caption = 'Avec Copie'
    ItemIndex = 0
    Items.Strings = (
      'faux'
      'vrai')
    TabOrder = 6
    OnClick = RGAvecCopieClick
  end
  object BtEcrire: TBitBtn
    Left = 416
    Top = 232
    Width = 75
    Height = 25
    Caption = 'BtEcrire'
    TabOrder = 7
    Visible = False
    OnClick = BtEcrireClick
  end
  object BtLire: TBitBtn
    Left = 416
    Top = 256
    Width = 153
    Height = 25
    Caption = 'lire fichier des modif'
    TabOrder = 8
    OnClick = BtLireClick
  end
  object BtOk: TBitBtn
    Left = 398
    Top = 400
    Width = 75
    Height = 25
    Caption = 'Executer'
    TabOrder = 9
    OnClick = BtOkClick
    Kind = bkOK
  end
end
