object CopierDansFrm: TCopierDansFrm
  Left = 198
  Top = 114
  Width = 246
  Height = 535
  Caption = 'Copier Dans'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object LabAncNom: TLabel
    Left = 16
    Top = 8
    Width = 67
    Height = 13
    Caption = 'A Copier Sous'
  end
  object LabCategorie: TLabel
    Left = 16
    Top = 120
    Width = 73
    Height = 13
    Caption = 'Dans Categorie'
  end
  object EdNom: TEdit
    Left = 16
    Top = 24
    Width = 201
    Height = 21
    TabOrder = 0
  end
  object ChLB: TCheckListBox
    Left = 16
    Top = 144
    Width = 201
    Height = 305
    ItemHeight = 13
    TabOrder = 1
  end
  object PanBas: TPanel
    Left = 0
    Top = 460
    Width = 238
    Height = 41
    Align = alBottom
    TabOrder = 2
    object BtOk: TBitBtn
      Left = 8
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      OnClick = BtOkClick
      Kind = bkOK
    end
    object BtAnnuler: TBitBtn
      Left = 128
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      OnClick = BtAnnulerClick
      Kind = bkCancel
    end
  end
  object RGCat: TRadioGroup
    Left = 16
    Top = 56
    Width = 201
    Height = 57
    Caption = 'Categorie'
    ItemIndex = 0
    Items.Strings = (
      'M'#234'me'
      'Autres')
    TabOrder = 3
    OnClick = RGCatClick
  end
end
