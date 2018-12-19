object CalTravFrm: TCalTravFrm
  Left = 247
  Top = 107
  Width = 696
  Height = 480
  Caption = 'CalTravFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object LabCalendrier: TLabel
    Left = 8
    Top = 8
    Width = 80
    Height = 20
    Caption = 'Calendriers'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object RecMotif: TShape
    Left = 288
    Top = 408
    Width = 40
    Height = 20
    Brush.Style = bsBDiagonal
    Enabled = False
    OnMouseDown = RecMotifMouseDown
  end
  object LB: TListBox
    Left = 8
    Top = 32
    Width = 121
    Height = 97
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 0
    OnClick = LBClick
  end
  object BtBnFermer: TBitBtn
    Left = 592
    Top = 408
    Width = 75
    Height = 25
    TabOrder = 1
    Kind = bkClose
  end
  object BtBnLegende: TBitBtn
    Left = 24
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Légende'
    TabOrder = 2
    OnClick = BtBnLegendeClick
  end
  object GB: TGroupBox
    Left = 384
    Top = 8
    Width = 289
    Height = 393
    Caption = 'Couleurs et Motifs'
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 3
  end
  object BtBnQuitter: TBitBtn
    Left = 536
    Top = 408
    Width = 50
    Height = 25
    Hint = 'Sortie IMMEDIATE SANS stocker'
    Caption = 'Quitter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = BtBnQuitterClick
  end
  object BtBnGraphe: TBitBtn
    Left = 24
    Top = 208
    Width = 75
    Height = 25
    Caption = 'Graphe'
    TabOrder = 5
    OnClick = BtBnGrapheClick
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    Left = 16
    Top = 384
  end
end
