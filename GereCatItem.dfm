object GereCatItemFrm: TGereCatItemFrm
  Left = -1
  Top = 135
  Width = 335
  Height = 420
  Caption = 'GereCatItemFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnHelp = FormHelp
  DesignSize = (
    327
    393)
  PixelsPerInch = 96
  TextHeight = 13
  object LabelModifie: TLabel
    Left = 224
    Top = 0
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
  object LB: TListBox
    Left = 128
    Top = 32
    Width = 185
    Height = 313
    Anchors = [akLeft, akTop, akRight, akBottom]
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 16
    ParentFont = False
    TabOrder = 0
    OnClick = LBClick
  end
  object BtBnFermer: TBitBtn
    Left = 160
    Top = 347
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Fermer'
    TabOrder = 1
    Kind = bkClose
  end
  object BtBnQuitter: TBitBtn
    Left = 246
    Top = 347
    Width = 33
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Quitter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = BtBnQuitterClick
  end
  object GBEnsemble: TGroupBox
    Left = 8
    Top = 24
    Width = 105
    Height = 345
    TabOrder = 3
    object BtBnImp: TBitBtn
      Left = 8
      Top = 312
      Width = 25
      Height = 25
      Hint = 'Imprimer'
      TabOrder = 0
      OnClick = BtBnImpClick
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
    object GBCategorie: TGroupBox
      Left = 8
      Top = 24
      Width = 90
      Height = 257
      Color = clInactiveCaption
      ParentColor = False
      TabOrder = 1
      object BtBnCreer: TBitBtn
        Left = 8
        Top = 24
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
      object BtSupprimer: TButton
        Left = 8
        Top = 56
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
        OnClick = BtSupprimerClick
      end
      object BtModifier: TButton
        Left = 8
        Top = 120
        Width = 75
        Height = 25
        Caption = 'Modif. Nom'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = BtModifierNomClick
      end
      object BtBnCopier: TBitBtn
        Left = 8
        Top = 88
        Width = 75
        Height = 25
        Caption = 'Copier'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = BtBnCopierClick
      end
      object BtClasser: TButton
        Left = 8
        Top = 152
        Width = 75
        Height = 25
        Caption = 'Classer'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = BtClasserClick
      end
      object PClasst: TPanel
        Left = 0
        Top = 192
        Width = 90
        Height = 33
        TabOrder = 5
        Visible = False
        object BtClHaut: TBitBtn
          Left = 21
          Top = 5
          Width = 25
          Height = 24
          Hint = 'Report vers le haut'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 0
          OnClick = BtClHautClick
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
        object BtClBas: TBitBtn
          Left = 45
          Top = 5
          Width = 25
          Height = 24
          Hint = 'Report vers le Bas'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 1
          OnClick = BtClBasClick
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
        object BtBnFermClasst: TBitBtn
          Left = 69
          Top = 5
          Width = 25
          Height = 24
          Hint = 'Arreter les Reports'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 2
          OnClick = BtBnFermClasstClick
          Glyph.Data = {
            DE010000424DDE01000000000000760000002800000024000000120000000100
            0400000000006801000000000000000000001000000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            333333333333333333333333000033338833333333333333333F333333333333
            0000333911833333983333333388F333333F3333000033391118333911833333
            38F38F333F88F33300003339111183911118333338F338F3F8338F3300003333
            911118111118333338F3338F833338F3000033333911111111833333338F3338
            3333F8330000333333911111183333333338F333333F83330000333333311111
            8333333333338F3333383333000033333339111183333333333338F333833333
            00003333339111118333333333333833338F3333000033333911181118333333
            33338333338F333300003333911183911183333333383338F338F33300003333
            9118333911183333338F33838F338F33000033333913333391113333338FF833
            38F338F300003333333333333919333333388333338FFF830000333333333333
            3333333333333333333888330000333333333333333333333333333333333333
            0000}
          NumGlyphs = 2
        end
        object BtClAlpha: TButton
          Left = 0
          Top = 5
          Width = 25
          Height = 24
          Caption = 'A'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = BtClAlphaClick
        end
      end
    end
  end
  object BtBnAide: TBitBtn
    Left = 302
    Top = 0
    Width = 25
    Height = 25
    Caption = '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = BtBnAideClick
  end
end
