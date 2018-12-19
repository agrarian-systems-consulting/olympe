inherited GereComparaisonFrm: TGereComparaisonFrm
  Caption = 'Comparaison'
  PixelsPerInch = 96
  TextHeight = 13
  inherited GBEnsemble: TGroupBox
    inherited GBAtelier: TGroupBox
      Caption = 'Comparaisons'
    end
  end
  object BtBnAide: TBitBtn
    Left = 128
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
