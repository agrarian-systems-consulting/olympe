object GereAleaPrixFrm: TGereAleaPrixFrm
  Left = 3
  Top = 108
  Width = 327
  Height = 461
  HelpContext = 91
  Caption = 'Aleas Prix'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  HelpFile = 'Olympe.hlp'
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnHelp = FormHelp
  DesignSize = (
    319
    434)
  PixelsPerInch = 96
  TextHeight = 13
  object LabelModifie: TLabel
    Left = 240
    Top = 8
    Width = 59
    Height = 20
    Caption = 'Modifie'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object BtBnFermer: TBitBtn
    Left = 160
    Top = 395
    Width = 75
    Height = 25
    Caption = 'Fermer'
    TabOrder = 0
    Kind = bkClose
  end
  object BtBnQuitter: TBitBtn
    Left = 246
    Top = 395
    Width = 33
    Height = 25
    Caption = 'Quitter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = BtBnQuitterClick
  end
  object BtBnImp: TBitBtn
    Left = 32
    Top = 376
    Width = 25
    Height = 25
    Hint = 'Imprimer'
    TabOrder = 2
    Glyph.Data = {
      36030000424D3603000000000000360000002800000010000000100000000100
      18000000000000030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000000000000000000000000000000000
      0000000000000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0
      C0000000C0C0C0C0C0C000000000000000000000000000000000000000000000
      0000000000000000000000000000000000C0C0C0000000C0C0C0000000C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000FFFF00FFFF00FFFFC0C0C0C0C0C00000
      00000000000000C0C0C0000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C080
      8080808080808080C0C0C0C0C0C0000000C0C0C0000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000C0C0C0000000C0C0C0000000
      000000000000000000000000000000000000000000000000000000C0C0C00000
      00C0C0C0000000000000C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFF000000C0C0C0000000C0C0C0000000C0C0C0C0C0C0
      C0C0C0000000FFFFFF000000000000000000000000000000FFFFFF0000000000
      00000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0000000FFFFFF000000000000000000000000000000FFFFFF0000
      00C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C00000000000000000000000000000000000000000000000
      00000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
      C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
  end
  object TV: TTreeView
    Left = 120
    Top = 40
    Width = 185
    Height = 345
    Anchors = [akLeft, akTop, akRight, akBottom]
    AutoExpand = True
    Color = clInfoBk
    Indent = 19
    ReadOnly = True
    TabOrder = 3
    OnDblClick = TVDblClick
  end
  object Panel2: TPanel
    Left = 0
    Top = 24
    Width = 113
    Height = 297
    TabOrder = 4
    object GBCategorie: TGroupBox
      Left = 8
      Top = 16
      Width = 97
      Height = 153
      Color = clInfoBk
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      object BtBnCreer: TBitBtn
        Left = 8
        Top = 16
        Width = 75
        Height = 25
        Caption = 'Cr'#233'er'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = BtBnCreerClick
      end
      object Btsupprimer: TButton
        Left = 8
        Top = 48
        Width = 75
        Height = 25
        Caption = 'Supprimer'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = BtsupprimerClick
      end
      object BtCopier: TBitBtn
        Left = 8
        Top = 80
        Width = 75
        Height = 25
        Caption = 'Copier'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = BtCopierClick
      end
      object BtModifier: TButton
        Left = 8
        Top = 112
        Width = 75
        Height = 25
        Caption = 'Modif. Nom'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = BtModifierClick
      end
    end
    object GBReclasser: TGroupBox
      Left = 16
      Top = 176
      Width = 75
      Height = 49
      Caption = 'Reclasser'
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
      object BtHaut: TBitBtn
        Left = 2
        Top = 17
        Width = 30
        Height = 25
        TabOrder = 0
        Glyph.Data = {
          72010000424D7201000000000000760000002800000011000000150000000100
          040000000000FC000000C40E0000C40E00001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
          7777700000007777777777777777700000007777700000007777700000007777
          7000000077777000000077777000000077777000000077777000000077777000
          0000777770000000777770000000777770000000777770000000777770000000
          7777700000007777700000007777700000007000000000000000700000007700
          0000000000077000000077700000000000777000000077770000000007777000
          0000777770000000777770000000777777000007777770000000777777700077
          7777700000007777777707777777700000007777777777777777700000007777
          77777777777770000000777777777777777770000000}
      end
      object BtBas: TBitBtn
        Left = 42
        Top = 17
        Width = 30
        Height = 25
        TabOrder = 1
        Glyph.Data = {
          72010000424D7201000000000000760000002800000011000000150000000100
          040000000000FC000000C40E0000C40E00001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
          7777700000007777777777777777700000007777777777777777700000007777
          7777077777777000000077777770007777777000000077777700000777777000
          0000777770000000777770000000777700000000077770000000777000000000
          0077700000007700000000000007700000007000000000000000700000007777
          7000000077777000000077777000000077777000000077777000000077777000
          0000777770000000777770000000777770000000777770000000777770000000
          7777700000007777700000007777700000007777700000007777700000007777
          77777777777770000000777777777777777770000000}
      end
    end
  end
end
