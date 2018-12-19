inherited TresoDefOcccFrm: TTresoDefOcccFrm
  Left = 86
  Top = 12
  Caption = 'TresoDefOcccFrm'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    inherited BtClasser: TButton
      Left = 432
      Visible = False
    end
    inherited PClasst: TPanel
      Left = 443
    end
    inherited ChBRepTout: TCheckBox
      Left = 272
      Checked = True
      State = cbChecked
    end
    object BtReportDroit: TBitBtn
      Left = 104
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
    object SansMaxi: TButton
      Left = 176
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Sans Maxi'
      TabOrder = 9
      OnClick = SansMaxiClick
    end
    object BtRepToutDroit: TBitBtn
      Left = 136
      Top = 8
      Width = 33
      Height = 25
      Hint = 'Recopie Tout a Droite'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
      OnClick = BtRepToutDroitClick
      Glyph.Data = {
        76000000424D76000000000000003E00000028000000160000000E0000000100
        010000000000380000000000000000000000020000000000000000000000FFFF
        FF00C0001800C0001800C0000000C0001800C0401800C0600000C7F01800C7F0
        1800C0600000C0401800C0001800C0000000C0001800C0001800}
    end
    object BtBnCalcul: TBitBtn
      Left = 376
      Top = 8
      Width = 75
      Height = 25
      Caption = 'R'#233'sultats'
      TabOrder = 11
      OnClick = BtBnCalculClick
    end
  end
  inherited Grille0: TStringGrid
    Width = 785
    ColCount = 3
  end
end
