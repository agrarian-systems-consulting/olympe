object AgriClasstFrm: TAgriClasstFrm
  Left = 190
  Top = 200
  Width = 694
  Height = 486
  Caption = 'Classement des agriculteurs'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnHelp = FormHelp
  DesignSize = (
    686
    459)
  PixelsPerInch = 96
  TextHeight = 13
  object LabelModifie: TLabel
    Left = 600
    Top = 5
    Width = 69
    Height = 20
    Caption = 'Modifi'#233' !'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object CleDeClassif: TGroupBox
    Left = 16
    Top = 24
    Width = 153
    Height = 385
    Anchors = [akLeft, akTop, akBottom]
    Caption = 'Cles de Classification'
    TabOrder = 0
    object ChLBCatTypeZone: TCheckListBox
      Left = 16
      Top = 24
      Width = 121
      Height = 177
      OnClickCheck = ChLBCatTypeZoneClickCheck
      Color = clInfoBk
      ItemHeight = 13
      TabOrder = 0
    end
    object PCleDeClassif: TPanel
      Left = 2
      Top = 342
      Width = 149
      Height = 41
      Align = alBottom
      TabOrder = 1
      object BtClHautLB: TBitBtn
        Left = 5
        Top = 5
        Width = 25
        Height = 24
        Hint = 'Report vers le haut'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        OnClick = BtClLBClick
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
      object BtClBasLB: TBitBtn
        Left = 37
        Top = 5
        Width = 25
        Height = 24
        Hint = 'Report vers le Bas'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 1
        OnClick = BtClLBClick
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
  object GBOrdreTri: TGroupBox
    Left = 192
    Top = 24
    Width = 489
    Height = 385
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Ordre de Tri'
    TabOrder = 1
    object LaGrille: TStringGrid
      Left = 16
      Top = 15
      Width = 471
      Height = 327
      Align = alRight
      Anchors = [akLeft, akTop, akRight, akBottom]
      DefaultColWidth = 90
      FixedColor = 13693007
      FixedCols = 0
      TabOrder = 0
    end
    object Panel1: TPanel
      Left = 2
      Top = 342
      Width = 485
      Height = 41
      Align = alBottom
      TabOrder = 1
      object BtBnClHautLaGrille: TBitBtn
        Left = 21
        Top = 5
        Width = 25
        Height = 24
        Hint = 'Report vers le haut'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        OnClick = BtBnClLaGrilleClick
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
      object BtBnClBasLaGrille: TBitBtn
        Left = 53
        Top = 5
        Width = 25
        Height = 24
        Hint = 'Report vers le Bas'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 1
        OnClick = BtBnClLaGrilleClick
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
  object PBas: TPanel
    Left = 0
    Top = 418
    Width = 686
    Height = 41
    Align = alBottom
    TabOrder = 2
    object BtOK: TBitBtn
      Left = 560
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 0
      OnClick = BtOKClick
      Kind = bkOK
    end
    object BtIgnore: TBitBtn
      Left = 472
      Top = 8
      Width = 75
      Height = 25
      TabOrder = 1
      OnClick = BtIgnoreClick
      Kind = bkIgnore
    end
  end
end
