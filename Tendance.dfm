inherited TendanceFrm: TTendanceFrm
  Left = 235
  Top = 178
  Width = 800
  Caption = 'Tendance'
  PixelsPerInch = 96
  TextHeight = 13
  inherited LabelModifie: TLabel
    Left = 624
    Visible = False
  end
  object LabTitre: TLabel [1]
    Left = 24
    Top = 0
    Width = 67
    Height = 20
    Caption = 'LabTitre'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsItalic]
    ParentFont = False
  end
  inherited Panell: TPanel
    Width = 792
    inherited BtClasser: TButton
      Left = 184
    end
    inherited PClasst: TPanel
      Left = 179
    end
    inherited BtBnImp: TBitBtn
      TabOrder = 10
    end
    inherited ChBRepTout: TCheckBox
      TabOrder = 11
    end
    inherited BtBnExcel: TBitBtn
      TabOrder = 12
    end
    object BtReportDroit: TBitBtn
      Left = 264
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie � droite'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
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
      Left = 304
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie En Bas'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
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
    object BtRecopBas: TBitBtn
      Left = 344
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie la Ligne'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
      OnClick = BtRecopBasClick
      Glyph.Data = {
        EE030000424DEE030000000000003600000028000000160000000E0000000100
        180000000000B8030000130B0000130B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000
        00000000FFFFFFFFFFFF000000000000FFFFFFFFFFFF000000000000FFFFFFFF
        FFFF000000000000FFFFFFFFFFFF000000000000FFFFFFFFFFFF000000000000
        0000000000000000FFFFFFFFFFFF000000000000FFFFFFFFFFFF000000000000
        FFFFFFFFFFFF000000000000FFFFFFFFFFFF000000000000FFFFFFFFFFFF0000
        000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000000FFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000000000000000000
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFF0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFF000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        0000000000000000000000000000000000000000000000000000000000000000
        000000000000000000000000000000000000}
    end
    object BtSup: TBitBtn
      Left = 72
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Supprimer Ligne'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
      OnClick = BtSupClick
      Glyph.Data = {
        26040000424D2604000000000000360000002800000010000000150000000100
        180000000000F0030000C40E0000C40E00000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0000000000000000000000000000000000000C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0
        C0C0808080808080808080000000000000C0C0C0C0C0C0C0C0C0C0C0C0000000
        000000FFFFFFC0C0C0C0C0C0000000C0C0C08080800000008080808080808080
        80000000000000C0C0C0C0C0C0000000FFFFFFFFFFFFC0C0C0C0C0C0000000C0
        C0C0808080000000808080808080808080808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
        C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
        C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0000000C0C0C08080800000008080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFF000000C0C0C0C0C0C0000000C0
        C0C0808080000000808080808080000000808080000000C0C0C0C0C0C0000000
        FFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C08080808080808080808080800000
        00808080000000C0C0C0C0C0C0000000FFFFFFFFFFFFC0C0C000000000000000
        0000000000000000808080808080808080808080000000C0C0C0C0C0C0000000
        000000000000000000C0C0C0C0C0C0C0C0C08080808080800000000000000000
        00000000000000C0C0C0C0C0C0000000C0C0C0C0C0C0C0C0C000000000000000
        0000000000000000808080808080808080808080000000C0C0C0000000C0C0C0
        000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C00000000000000000
        00000000808080000000000000000000FFFFFFFFFFFFC0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0000000000000C0C0C0C0C0C0C0C0C0C0C0C000000080808080
        8080808080000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000C0C0C0000000
        C0C0C0C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0000000C0C0C0C0C0C0C0C0C0000000000000000000C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0000000000000000000000000C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0000000000000000000000000000000C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0}
    end
  end
  inherited Grille0: TStringGrid
    Left = 8
    Top = 32
    Height = 369
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowMoving, goTabs, goThumbTracking]
  end
  object BtDonnees: TButton [4]
    Left = 544
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Donnees'
    TabOrder = 2
    Visible = False
    OnClick = BtDonneesClick
  end
  object EdNom: TEdit [5]
    Left = 288
    Top = 0
    Width = 121
    Height = 21
    TabOrder = 3
    Visible = False
  end
  object RGPcentVal: TRadioGroup [6]
    Left = 424
    Top = 0
    Width = 113
    Height = 35
    Color = clLime
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'pcent'
      'valeur')
    ParentColor = False
    TabOrder = 4
    OnClick = RGPcentValClick
  end
end
