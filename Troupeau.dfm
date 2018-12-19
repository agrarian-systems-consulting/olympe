inherited TroupeauFrm: TTroupeauFrm
  Left = 171
  Top = 99
  Width = 837
  Height = 558
  Caption = 'Troupeau'
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 490
    Width = 829
    inherited BtClasser: TButton
      Left = 472
      Top = 0
      Visible = False
    end
    inherited PClasst: TPanel
      Left = 475
      inherited BtClBas: TBitBtn
        Top = 8
        Height = 21
      end
    end
    inherited ChBRepTout: TCheckBox
      Left = 280
      Top = 8
      Checked = True
      State = cbChecked
    end
    object BtReportDroit: TBitBtn
      Left = 208
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie '#224' droite'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
      OnClick = BtReportDroitClick
      Glyph.Data = {
        42010000424D4201000000000000760000002800000015000000110000000100
        040000000000CC000000C40E0000C40E00001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
        7777777770007777777777077777777770007777777777007777777770007777
        7777770007777777700077777777770000777777700077000000000000077777
        7000770000000000000077777000770000000000000007777000770000000000
        0000007770007700000000000000077770007700000000000000777770007700
        0000000000077777700077777777770000777777700077777777770007777777
        7000777777777700777777777000777777777707777777777000777777777777
        777777777000}
    end
    object BtReportBas: TBitBtn
      Left = 240
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie En Bas'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
      OnClick = BtReportBasClick
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
    object BtBnSansBorne: TBitBtn
      Left = 368
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Sans Borne'
      TabOrder = 10
      OnClick = BtBnSansBorneClick
    end
    object BtBnAide: TBitBtn
      Left = 128
      Top = 8
      Width = 25
      Height = 25
      Caption = '?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
      OnClick = BtBnAideClick
    end
  end
  inherited PanHaut: TPanel
    Width = 829
    object LabNomTroupeau: TLabel
      Left = 16
      Top = 8
      Width = 143
      Height = 20
      Caption = 'Nom du Troupeau'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object PC: TPageControl [3]
    Left = 0
    Top = 41
    Width = 829
    Height = 449
    ActivePage = TSMouvement
    Align = alClient
    TabIndex = 6
    TabOrder = 3
    OnChange = PCChange
    OnChanging = PCChanging
    object TSNature: TTabSheet
      Caption = 'Nature'
      ImageIndex = 4
      object PanNature: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 0
        object LabNature: TLabel
          Left = 8
          Top = 8
          Width = 150
          Height = 20
          Caption = 'Type de Troupeau:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GBTroupeau: TGroupBox
        Left = 8
        Top = 56
        Width = 369
        Height = 209
        Caption = 'Les Troupeaux'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object LBTroupeau: TListBox
          Left = 8
          Top = 24
          Width = 361
          Height = 145
          BevelKind = bkTile
          Color = clInfoBk
          ItemHeight = 16
          TabOrder = 0
          OnClick = LBTroupeauClick
        end
        object BtBnSup: TBitBtn
          Left = 8
          Top = 176
          Width = 75
          Height = 25
          Caption = 'Supprimer'
          TabOrder = 1
          OnClick = BtBnSupClick
          Kind = bkCancel
        end
      end
    end
    object TSMaxi: TTabSheet
      Caption = 'Maxi'
      ImageIndex = 2
      object GrilleMaxi: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 380
        Align = alClient
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
        OnMouseDown = GrilleMaxiMouseDown
        OnMouseMove = GrilleMaxiMouseMove
        OnMouseUp = GrilleMaxiMouseUp
      end
      object PanMaxi: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 1
        object LabEffMax: TLabel
          Left = 8
          Top = 8
          Width = 240
          Height = 20
          Caption = 'Effectif maximal par cat'#233'gorie'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
    end
    object TSPrix: TTabSheet
      Caption = 'Prix Vente'
      ImageIndex = 1
      object TLabel
        Left = 8
        Top = 8
        Width = 160
        Height = 20
        Caption = 'Produits et Charges'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object PanPrix: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 0
        object LabPrix: TLabel
          Left = 8
          Top = 8
          Width = 145
          Height = 20
          Caption = ' Prix Vente Moyen'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GrillePrix: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 380
        Align = alClient
        ColCount = 3
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
        OnMouseDown = GrilleMaxiMouseDown
        OnMouseMove = GrilleMaxiMouseMove
        OnMouseUp = GrilleMaxiMouseUp
      end
    end
    object TSValInv: TTabSheet
      Caption = 'Val. Inventaire'
      ImageIndex = 5
      object GrilleValInv: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 380
        Hint = 'Repro O/N'
        Align = alClient
        ColCount = 3
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
        OnMouseDown = GrilleMaxiMouseDown
        OnMouseMove = GrilleMaxiMouseMove
        OnMouseUp = GrilleMaxiMouseUp
      end
      object PanValInv: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 1
        object LabValInv: TLabel
          Left = 8
          Top = 8
          Width = 159
          Height = 20
          Caption = 'Valeurs d'#39'inventaire'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
    end
    object TSAchat: TTabSheet
      Caption = 'Achat'
      ImageIndex = 7
      object PanAchat: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 0
        object LabAchat: TLabel
          Left = 8
          Top = 8
          Width = 81
          Height = 20
          Caption = 'A Acheter'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GrilleAchat: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 380
        Align = alClient
        ColCount = 3
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
        OnMouseDown = GrilleMaxiMouseDown
        OnMouseMove = GrilleMaxiMouseMove
        OnMouseUp = GrilleMaxiMouseUp
      end
    end
    object TSPrixAchat: TTabSheet
      Caption = 'Prix Achat'
      ImageIndex = 8
      object PanPrixAchat: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 0
        object LabPrixAchat: TLabel
          Left = 8
          Top = 8
          Width = 96
          Height = 20
          Caption = 'Prix d'#39'Achat'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GrillePrixAchat: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 380
        Align = alClient
        ColCount = 3
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
        OnMouseDown = GrilleMaxiMouseDown
        OnMouseMove = GrilleMaxiMouseMove
        OnMouseUp = GrilleMaxiMouseUp
      end
    end
    object TSMouvement: TTabSheet
      Caption = 'Mouvement'
      object PanMvtBas: TPanel
        Left = 0
        Top = 316
        Width = 821
        Height = 105
        Align = alBottom
        TabOrder = 0
        object RGCouS: TRadioGroup
          Left = 8
          Top = 24
          Width = 113
          Height = 49
          Caption = 'Effectifs'
          ItemIndex = 0
          Items.Strings = (
            'Avec Mouvement'
            'Constant')
          TabOrder = 0
          OnClick = RGCouSClick
        end
        object BtBnSimuler: TBitBtn
          Left = 152
          Top = 8
          Width = 89
          Height = 27
          Caption = 'Simuler'
          TabOrder = 1
          OnClick = BtBnSimulerClick
        end
        object GBResultat: TGroupBox
          Left = 272
          Top = 2
          Width = 369
          Height = 97
          Caption = 'R'#233'sultats'
          TabOrder = 2
          object TVMvtEffectif: TTreeView
            Left = 8
            Top = 16
            Width = 169
            Height = 73
            Color = clInfoBk
            Indent = 19
            ReadOnly = True
            TabOrder = 0
            OnClick = TVResultatClick
            Items.Data = {
              01000000210000000000000000000000FFFFFFFFFFFFFFFF0000000002000000
              0845666665637469661E0000000000000000000000FFFFFFFFFFFFFFFF000000
              00000000000541636861741E0000000000000000000000FFFFFFFFFFFFFFFF00
              000000000000000556656E7465}
          end
          object TVMvtValeur: TTreeView
            Left = 184
            Top = 16
            Width = 169
            Height = 73
            Color = clInfoBk
            Indent = 19
            ReadOnly = True
            TabOrder = 1
            OnClick = TVResultatClick
            Items.Data = {
              010000001F0000000000000000000000FFFFFFFFFFFFFFFF0000000003000000
              0656616C6575721E0000000000000000000000FFFFFFFFFFFFFFFF0000000000
              0000000541636861741E0000000000000000000000FFFFFFFFFFFFFFFF000000
              00000000000556656E7465230000000000000000000000FFFFFFFFFFFFFFFF00
              000000000000000A496E76656E7461697265}
          end
        end
        object BtBnMazVenteAchat: TBitBtn
          Left = 152
          Top = 40
          Width = 89
          Height = 25
          Caption = 'Maz VenteAchat'
          TabOrder = 3
          OnClick = BtBnMazVenteAchatClick
        end
        object BtBnMazMvt: TBitBtn
          Left = 152
          Top = 72
          Width = 89
          Height = 25
          Caption = 'Maz Mvt d'#233'cid'#233's'
          TabOrder = 4
          OnClick = BtBnMazMvtClick
        end
      end
      object GrilleMvt: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 275
        Align = alClient
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
        OnMouseDown = GrilleMaxiMouseDown
        OnMouseMove = GrilleMaxiMouseMove
        OnMouseUp = GrilleMaxiMouseUp
        RowHeights = (
          24
          24
          24
          24
          24)
      end
      object PanMvtHaut: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 2
        object LabMvt: TLabel
          Left = 8
          Top = 8
          Width = 198
          Height = 20
          Caption = 'Mouvement des animaux'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object LabFinAnnee: TLabel
          Left = 384
          Top = 24
          Width = 109
          Height = 13
          Caption = 'Effectifs En fin d'#39'ann'#233'e'
        end
      end
    end
    object TSProCha: TTabSheet
      Caption = 'Produits/Charges'
      ImageIndex = 3
      object PanChaPro: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 0
        object LabProCha: TLabel
          Left = 8
          Top = 8
          Width = 160
          Height = 20
          Caption = 'Produits et Charges'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object BtBnProcha: TBitBtn
          Left = 352
          Top = 8
          Width = 97
          Height = 25
          Caption = 'Produits Charges'
          TabOrder = 0
          OnClick = BtBnProchaClick
        end
        object BtBnRien: TBitBtn
          Left = 464
          Top = 8
          Width = 75
          Height = 25
          Caption = 'Rien'
          TabOrder = 1
          OnClick = BtBnRienClick
        end
      end
      object GrilleProCha: TStringGrid
        Left = 0
        Top = 41
        Width = 821
        Height = 380
        Align = alClient
        FixedColor = 13693007
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goTabs, goAlwaysShowEditor, goThumbTracking]
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Grille0Click
        OnKeyPress = Grille0KeyPress
      end
    end
    object RSResultat: TTabSheet
      Caption = 'Resultats'
      ImageIndex = 6
      object GBSortie: TGroupBox
        Left = 736
        Top = 336
        Width = 73
        Height = 73
        Caption = 'Sortie sur'
        TabOrder = 0
        object Image1: TImage
          Left = 8
          Top = 32
          Width = 17
          Height = 20
          Picture.Data = {
            07544269746D617036030000424D360300000000000036000000280000001000
            000010000000010018000000000000030000C40E0000C40E0000000000000000
            0000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000000000000000
            00000000000000000000000000000000000000000000000000C0C0C0C0C0C0C0
            C0C0C0C0C0000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0000000C0C0C0000000C0C0C0C0C0C00000000000000000000000000000
            00000000000000000000000000000000000000000000000000C0C0C0000000C0
            C0C0000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000FFFF00FFFF00FFFF
            C0C0C0C0C0C0000000000000000000C0C0C0000000C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0808080808080808080C0C0C0C0C0C0000000C0C0C000000000
            0000000000000000000000000000000000000000000000000000000000000000
            000000000000000000C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000C0C0C000
            0000C0C0C0000000000000000000000000000000000000000000000000000000
            000000C0C0C0000000C0C0C0000000000000C0C0C0C0C0C0000000FFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0000000C0C0C000
            0000C0C0C0C0C0C0C0C0C0000000FFFFFF000000000000000000000000000000
            FFFFFF000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFF000000000000000000000000
            000000FFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000
            00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000000000000000
            000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0}
        end
        object Image2: TImage
          Left = 8
          Top = 48
          Width = 17
          Height = 20
          Picture.Data = {
            07544269746D61706E040000424D6E0400000000000036000000280000001300
            000012000000010018000000000038040000C40E0000C40E0000000000000000
            0000DFDFDFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDF
            DFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0000000000000000000000000000000C0C0C0000000DFDFDFC0C0C000000000
            0000000000000000000000000000000000000000000000000000000000808000
            808000808000808000000000C0C0C0000000DFDFDFC0C0C00000008080808080
            80808080808080808080808080808080808080000000808000FFFF00FFFF00FF
            FFFF000000C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0000000FFFF00808000
            808000808000808000808000000000808000FFFF00FFFF00FFFFFF000000C0C0
            C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0C0C0000000FFFF0080800080
            8000808000000000808000FFFF00FFFF00FFFFFF000000808000000000C0C0C0
            C0C0C0000000DFDFDFC0C0C0C0C0C0C0C0C0C0C0C0000000FFFF008080000000
            00808000FFFF00FFFF00FFFFFF000000000000000000000000C0C0C0C0C0C000
            0000DFDFDFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000808000FFFF00
            FFFF00FFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDF
            DFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000808000FFFF00FFFF00FFFFFF00
            0000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0
            C0C0C0C0C0C0C0C0C0000000808000FFFF00FFFF00FFFFFF0000008080008080
            80000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C0C0
            C0C0000000808000FFFF00FFFF00FFFFFF000000FFFF00808000808000808080
            000000C0C0C0C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0C0C0C00000008080
            00FFFF00FFFF00FFFFFF000000C0C0C0000000FFFF0080800080800080808000
            0000C0C0C0C0C0C0C0C0C0000000DFDFDFC0C0C0000000FFFFFFFFFFFFFFFFFF
            FFFFFF000000C0C0C0C0C0C0C0C0C0000000FFFF00FFFF00FFFF00FFFF000000
            00C0C0C0C0C0C0000000DFDFDFC0C0C0000000000000000000000000000000C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000000000000000C0C0C0
            C0C0C0000000DFDFDFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000
            0000DFDFDFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000DFDF
            DFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000}
        end
        object RBQR: TRadioButton
          Left = 48
          Top = 32
          Width = 17
          Height = 17
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RBExcel: TRadioButton
          Left = 48
          Top = 48
          Width = 17
          Height = 17
          TabOrder = 1
        end
        object RBEcran: TRadioButton
          Left = 8
          Top = 16
          Width = 53
          Height = 17
          Alignment = taLeftJustify
          Caption = 'Ecran'
          TabOrder = 2
        end
      end
      object PanResTroup: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 41
        Align = alTop
        TabOrder = 1
        object LabResTroup: TLabel
          Left = 8
          Top = 8
          Width = 222
          Height = 20
          Caption = 'R'#233'sultats du/des troupeaux'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GBResultats: TGroupBox
        Left = 208
        Top = 56
        Width = 233
        Height = 209
        Caption = 'R'#233'sultats'
        TabOrder = 2
        object TVResultat: TTreeView
          Left = 16
          Top = 24
          Width = 169
          Height = 169
          Color = clInfoBk
          Indent = 19
          ReadOnly = True
          TabOrder = 0
          OnClick = TVResultatClick
          Items.Data = {
            03000000210000000000000000000000FFFFFFFFFFFFFFFF0000000002000000
            0845666665637469661E0000000000000000000000FFFFFFFFFFFFFFFF000000
            00000000000541636861741E0000000000000000000000FFFFFFFFFFFFFFFF00
            000000000000000556656E74651F0000000000000000000000FFFFFFFFFFFFFF
            FF00000000030000000656616C6575721E0000000000000000000000FFFFFFFF
            FFFFFFFF00000000000000000541636861741E0000000000000000000000FFFF
            FFFFFFFFFFFF00000000000000000556656E7465230000000000000000000000
            FFFFFFFFFFFFFFFF00000000000000000A496E76656E74616972652900000000
            00000000000000FFFFFFFFFFFFFFFF00000000020000001050726F6475697473
            2F43686172676573210000000000000000000000FFFFFFFFFFFFFFFF00000000
            00000000085175616E746974E91F0000000000000000000000FFFFFFFFFFFFFF
            FF00000000000000000656616C657572}
        end
      end
      object GBTrARetenir: TGroupBox
        Left = 24
        Top = 56
        Width = 153
        Height = 137
        Caption = 'Troupeaux '#224' Retenir'
        TabOrder = 3
        object ChLBTroupeau: TCheckListBox
          Left = 16
          Top = 16
          Width = 121
          Height = 97
          Color = clInfoBk
          ItemHeight = 13
          TabOrder = 0
        end
      end
    end
  end
end
