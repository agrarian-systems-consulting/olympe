inherited InvAniFrm: TInvAniFrm
  Left = 236
  Top = 223
  Width = 765
  Height = 499
  Caption = 'Inventaire des Animaux'
  FormStyle = fsStayOnTop
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 364
    Width = 757
    Height = 101
    object LabEffectif: TLabel [0]
      Left = 408
      Top = 8
      Width = 33
      Height = 13
      Caption = 'Effectif'
    end
    object LabValeur: TLabel [1]
      Left = 472
      Top = 8
      Width = 30
      Height = 13
      Caption = 'Valeur'
    end
    object LabCatAnimaux: TLabel [2]
      Left = 56
      Top = 16
      Width = 50
      Height = 13
      Caption = 'Categories'
    end
    inherited BoutFermer: TBitBtn
      Top = 72
    end
    inherited BtBnQuitter: TBitBtn
      Top = 72
    end
    inherited BtClasser: TButton
      Left = 680
      Top = 56
      Visible = False
    end
    inherited BtBnStocker: TBitBtn
      Top = 72
    end
    inherited PClasst: TPanel
      Left = 715
    end
    inherited BtBnImp: TBitBtn
      Top = 72
    end
    inherited ChBRepTout: TCheckBox
      Left = 680
      Top = 48
      Visible = False
    end
    inherited BtBnExcel: TBitBtn
      Top = 72
    end
    object BtBnEAchat: TBitBtn
      Left = 408
      Top = 24
      Width = 55
      Height = 25
      Caption = 'Achat'
      TabOrder = 8
      OnClick = BtBnEAchatClick
    end
    object BtBnEVente: TBitBtn
      Left = 408
      Top = 48
      Width = 55
      Height = 25
      Caption = 'Vente'
      TabOrder = 9
      OnClick = BtBnEVenteClick
    end
    object BtBnVAchat: TBitBtn
      Left = 472
      Top = 24
      Width = 55
      Height = 25
      Caption = 'Achat'
      TabOrder = 10
      OnClick = BtBnVAchatClick
    end
    object BtBnVVente: TBitBtn
      Left = 472
      Top = 48
      Width = 55
      Height = 25
      Caption = 'Vente'
      TabOrder = 11
      OnClick = BtBnVVenteClick
    end
    object BtBnInventaire: TBitBtn
      Left = 472
      Top = 72
      Width = 55
      Height = 25
      Caption = 'Inventaire'
      TabOrder = 12
      OnClick = BtBnInventaireClick
    end
    object RGCouS: TRadioGroup
      Left = 184
      Top = 8
      Width = 113
      Height = 80
      Caption = 'Effectifs'
      ItemIndex = 0
      Items.Strings = (
        'Avec Mouvement'
        'Constant')
      TabOrder = 13
      OnClick = RGCouSClick
    end
    object BtBnDemarrer: TBitBtn
      Left = 304
      Top = 40
      Width = 75
      Height = 25
      Caption = 'D'#233'marrer'
      TabOrder = 14
      OnClick = BtBnDemarrerClick
    end
    object CBCatAnimaux: TComboBox
      Left = 16
      Top = 32
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 15
      OnClick = CBCatAnimauxClick
    end
    object BtBnRecommencer: TBitBtn
      Left = 304
      Top = 64
      Width = 75
      Height = 25
      Caption = 'Recommencer'
      TabOrder = 16
      OnClick = BtBnRecommencerClick
    end
    object BtBnMax: TBitBtn
      Left = 304
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Eff Max'
      TabOrder = 17
      OnClick = BtBnMaxClick
    end
    object BtBnProCha: TBitBtn
      Left = 560
      Top = 32
      Width = 89
      Height = 25
      Caption = 'Produits Charges'
      TabOrder = 18
      OnClick = BtBnProChaClick
    end
  end
  inherited Grille0: TStringGrid
    Top = 41
    Width = 757
    Height = 323
    Align = alClient
  end
  inherited PanHaut: TPanel
    Width = 757
    object LabEffFin: TLabel
      Left = 200
      Top = 24
      Width = 47
      Height = 13
      Caption = 'Effectif fin'
    end
  end
  inherited ActionList1: TActionList
    Left = 672
    Top = 364
  end
end
