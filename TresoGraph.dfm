inherited TresoGraphFrm: TTresoGraphFrm
  Left = 208
  Top = 107
  Width = 712
  Height = 548
  Caption = 'TresoGraphFrm'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 14
  inherited PCGaucheDroit: TPageControl
    Top = 0
    Height = 241
    inherited TabSheetG: TTabSheet
      inherited SpBtCourbeG: TSpeedButton
        Top = 176
      end
      inherited SpBtHistoG: TSpeedButton
        Top = 176
      end
    end
  end
  inherited GBBas: TGroupBox
    Left = 592
    Top = 432
    Width = 97
  end
  object GBAff: TGroupBox
    Left = 592
    Top = 248
    Width = 97
    Height = 169
    Caption = 'Affichage'
    TabOrder = 2
    object LabMois: TLabel
      Left = 0
      Top = 104
      Width = 68
      Height = 14
      Caption = 'Mois de D'#233'but'
    end
    object LabAn: TLabel
      Left = 0
      Top = 64
      Width = 32
      Height = 14
      Caption = 'Ann'#233'e'
    end
    object RGNbAnnee: TRadioGroup
      Left = 0
      Top = 16
      Width = 89
      Height = 49
      Caption = 'Nombre d'#39'ann'#233'es'
      ItemIndex = 1
      Items.Strings = (
        'Une Ann'#233'e'
        'Toutes')
      TabOrder = 0
      OnClick = RGNbAnneeClick
    end
    object CBMois: TComboBox
      Left = 0
      Top = 120
      Width = 89
      Height = 22
      ItemHeight = 14
      ItemIndex = 0
      TabOrder = 1
      Text = 'Janv'
      OnClick = CBMoisClick
      Items.Strings = (
        'Janv'
        'F'#233'v'
        'Mars'
        'Avril'
        'Mai'
        'Juin'
        'Juillet'
        'Aout'
        'Sept'
        'Oct'
        'Nov'
        'D'#233'c')
    end
    object CBAn: TComboBox
      Left = 0
      Top = 80
      Width = 89
      Height = 22
      ItemHeight = 14
      TabOrder = 2
      OnClick = CBAnClick
    end
    object BtBnOK: TBitBtn
      Left = 8
      Top = 144
      Width = 75
      Height = 18
      TabOrder = 3
      OnClick = BtBnOKClick
      Kind = bkOK
    end
  end
end
