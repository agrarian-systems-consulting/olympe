inherited SituDepartFrm: TSituDepartFrm
  Left = 439
  Top = 172
  Width = 348
  Height = 356
  Caption = 'Situation de D'#233'part'
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnHelp = FormHelp
  PixelsPerInch = 96
  TextHeight = 13
  object LabTresoIni: TLabel [0]
    Left = 24
    Top = 24
    Width = 141
    Height = 20
    Caption = 'Tr'#233'sorerie Initiale'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabTva: TLabel [1]
    Left = 24
    Top = 64
    Width = 29
    Height = 20
    Caption = 'Tva'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabAcompteAout: TLabel [2]
    Left = 40
    Top = 203
    Width = 67
    Height = 13
    Caption = 'Acompte Aout'
  end
  object LabAcompteNov: TLabel [3]
    Left = 40
    Top = 232
    Width = 94
    Height = 13
    Caption = 'Acompte Novembre'
  end
  object LabAcompteMai: TLabel [4]
    Left = 40
    Top = 174
    Width = 62
    Height = 13
    Caption = 'Acompte Mai'
  end
  object LabAcompteFevrier: TLabel [5]
    Left = 40
    Top = 261
    Width = 77
    Height = 13
    Caption = 'Acompte F'#233'vrier'
  end
  object LabTvaEncaissee: TLabel [6]
    Left = 40
    Top = 96
    Width = 71
    Height = 13
    Caption = 'Tva Encaissee'
  end
  object LabTvaVersee: TLabel [7]
    Left = 40
    Top = 120
    Width = 55
    Height = 13
    Caption = 'Tva Vers'#233'e'
  end
  object LabelModifie: TLabel [8]
    Left = 263
    Top = 0
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
  inherited Panell: TPanel
    Top = 288
    Width = 340
    inherited BoutFermer: TBitBtn
      Left = 200
    end
    inherited BtBnQuitter: TBitBtn
      Left = 280
    end
  end
  object EdTresoIni: TEdit
    Left = 192
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'EdTresoIni'
    OnExit = EdTresoIniExit
    OnKeyPress = EdKeyPress
  end
  object EdAcompteAout: TEdit
    Left = 184
    Top = 197
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'EdAcompteAout'
    OnExit = EdAcompteAoutExit
  end
  object EdAcompteNov: TEdit
    Left = 184
    Top = 226
    Width = 121
    Height = 21
    TabOrder = 3
    Text = 'EdAcompteNov'
    OnExit = EdAcompteNovExit
  end
  object EdAcompteFev: TEdit
    Left = 184
    Top = 255
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'EdAcompteFev'
    OnExit = EdAcompteFevExit
  end
  object EdAcompteMai: TEdit
    Left = 184
    Top = 168
    Width = 121
    Height = 21
    TabOrder = 5
    Text = 'EdAcompteMai'
    OnExit = EdAcompteMaiExit
  end
  object EdTvaRecue: TEdit
    Left = 184
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 6
    Text = 'EdTvaRecue'
    OnExit = EdTvaRecueExit
    OnKeyPress = EdKeyPress
  end
  object EdTvaVersee: TEdit
    Left = 184
    Top = 112
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'EdTvaVersee'
    OnExit = EdTvaVerseeExit
  end
  object BtClBas: TBitBtn
    Left = 309
    Top = 169
    Width = 25
    Height = 24
    Hint = 'Report vers le Bas'
    ParentShowHint = False
    ShowHint = False
    TabOrder = 8
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
end
