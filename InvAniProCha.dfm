inherited InvAniProChaFrm: TInvAniProChaFrm
  Left = 177
  Width = 824
  Caption = 'InvAniProChaFrm'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Width = 816
    inherited BtBnSansBorne: TBitBtn
      Visible = False
    end
  end
  inherited Grille0: TStringGrid
    Width = 816
    Align = alTop
  end
  inherited PanHaut: TPanel
    Width = 816
    inherited LabelModifie: TLabel
      Left = 632
    end
    inherited LabEffMax: TLabel
      Width = 160
      Caption = 'Produits et Charges'
    end
    object BtBnProcha: TBitBtn
      Left = 352
      Top = 8
      Width = 97
      Height = 25
      Caption = 'Produits Charges'
      TabOrder = 0
      OnClick = BtBnProchaClick
    end
  end
end
