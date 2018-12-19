inherited InvAniMaxFrm: TInvAniMaxFrm
  Left = 247
  Top = 205
  Width = 797
  Height = 485
  Caption = 'InvAniMaxFrm'
  FormStyle = fsStayOnTop
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 410
    Width = 789
    inherited BtClasser: TButton
      Left = 96
      Visible = False
    end
    inherited PClasst: TPanel
      Left = 467
    end
    inherited ChBRepTout: TCheckBox
      Left = 208
    end
    object BtReportDroit: TBitBtn
      Left = 176
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
    object BtBnSansBorne: TBitBtn
      Left = 304
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Sans Borne'
      TabOrder = 9
      OnClick = BtBnSansBorneClick
    end
  end
  inherited Grille0: TStringGrid
    Top = 41
    Width = 777
    Height = 344
  end
  inherited PanHaut: TPanel
    Width = 789
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
