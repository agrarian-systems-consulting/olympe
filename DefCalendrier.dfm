inherited DefCalendrierFrm: TDefCalendrierFrm
  Left = 150
  Top = 197
  Caption = 'Calendrier'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 385
    Height = 88
    inherited BtClasser: TButton
      Left = 448
      Top = 16
    end
    inherited PClasst: TPanel
      Left = 443
      Top = 40
    end
    inherited BtBnNote: TBitBtn
      Enabled = True
    end
    inherited BtBnVersExcel: TBitBtn
      TabOrder = 15
    end
    object RGDef: TRadioGroup
      Left = 248
      Top = 8
      Width = 105
      Height = 73
      Caption = 'P'#233'riodes D'#233'finies'
      ItemIndex = 0
      Items.Strings = (
        'Par l'#39'utilisateur'
        'Mois'
        'Quinzaine')
      TabOrder = 13
      OnClick = RGDefClick
    end
  end
  inherited Grille0: TStringGrid
    Height = 344
  end
  inherited PanHaut: TPanel
    object BtBnAide: TBitBtn
      Left = 664
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
      TabOrder = 2
      OnClick = BtBnAideClick
    end
  end
end
