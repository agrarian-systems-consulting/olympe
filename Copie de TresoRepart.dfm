inherited TresoRepartFrm: TTresoRepartFrm
  Left = 214
  Top = 137
  Width = 792
  Caption = 'Treso  Produits '
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Width = 784
    inherited BoutFermer: TBitBtn
      OnClick = BoutFermerClick
    end
    object BtBnCalcul: TBitBtn
      Left = 224
      Top = 8
      Width = 75
      Height = 25
      Caption = 'R'#233'sultats'
      TabOrder = 2
      OnClick = BtBnCalculClick
    end
    object BtRepBas: TBitBtn
      Left = 13
      Top = 8
      Width = 25
      Height = 24
      Hint = 'Report vers le Bas'
      ParentShowHint = False
      ShowHint = False
      TabOrder = 3
      OnClick = BtRepBasClick
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
    object BtReportDroit: TBitBtn
      Left = 40
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Report '#224' droite'
      TabOrder = 4
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
    object ChBRepTout: TCheckBox
      Left = 112
      Top = 8
      Width = 81
      Height = 17
      Hint = 'Report tout ou seult si Vide'
      Caption = 'Report Tout'
      Checked = True
      Color = clInfoBk
      ParentColor = False
      State = cbChecked
      TabOrder = 5
    end
    object BtRepToutDroit: TBitBtn
      Left = 72
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie Tout a Droite'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      OnClick = BtRepToutDroitClick
      Glyph.Data = {
        76000000424D76000000000000003E00000028000000160000000E0000000100
        010000000000380000000000000000000000020000000000000000000000FFFF
        FF00C0001800C0001800C0000000C0001800C0401800C0600000C7F01800C7F0
        1800C0600000C0401800C0001800C0000000C0001800C0001800}
    end
  end
  object SG: TStringGrid
    Left = 0
    Top = 41
    Width = 784
    Height = 452
    Align = alClient
    ColCount = 11
    FixedColor = 13693007
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing]
    TabOrder = 1
    OnDblClick = SGDblClick
  end
  object PanHaut: TPanel
    Left = 0
    Top = 0
    Width = 784
    Height = 41
    Align = alTop
    TabOrder = 2
    object LabelModifie: TLabel
      Left = 440
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
    end
    object BtBnRepart: TBitBtn
      Left = 288
      Top = 8
      Width = 75
      Height = 25
      Caption = 'R'#233'partitions'
      TabOrder = 0
      OnClick = BtBnRepartClick
    end
  end
end
