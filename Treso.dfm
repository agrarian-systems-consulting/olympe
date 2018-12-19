inherited TresoFrm: TTresoFrm
  Left = 359
  Top = 169
  Width = 698
  Height = 573
  Caption = 'Tresorerie'
  Menu = MainMenu
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panell: TPanel
    Top = 486
    Width = 690
  end
  object MainMenu: TMainMenu
    object Definition: TMenuItem
      Caption = 'R'#233'partitions'
      OnClick = DefinitionClick
    end
    object Produits1: TMenuItem
      Caption = 'Produits'
      OnClick = ProduitsClick
    end
    object Charges: TMenuItem
      Caption = 'Charges'
      object Oprationnelles1: TMenuItem
        Caption = 'Op'#233'rationnelles'
        OnClick = OperationnellesClick
      end
      object Structure1: TMenuItem
        Caption = 'Structure'
        OnClick = StructureClick
      end
    end
    object Troupeaux: TMenuItem
      Caption = 'Troupeaux'
      OnClick = TroupeauxClick
      object BestiauxVente: TMenuItem
        Caption = 'Vente'
        OnClick = BestiauxVenteClick
      end
      object BestiauxAchat: TMenuItem
        Caption = 'Achat'
        OnClick = BestiauxAchatClick
      end
    end
    object Divers1: TMenuItem
      Caption = 'Divers'
      object Recettes: TMenuItem
        Caption = 'Recettes'
        OnClick = DivRecettesClick
      end
      object Depenses: TMenuItem
        Caption = 'D'#233'penses'
        OnClick = DivDepensesClick
      end
    end
    object Externalites: TMenuItem
      Caption = 'Externalit'#233's'
      OnClick = ExternalitesClick
    end
    object Immo: TMenuItem
      Caption = 'Immo'
      object Investissement: TMenuItem
        Caption = 'Investissement'
        OnClick = InvestissementClick
      end
      object PetitMatriel: TMenuItem
        Caption = 'Petit Mat'#233'riel'
        OnClick = PetitMatrielClick
      end
    end
    object Finance: TMenuItem
      Caption = 'Finance'
      OnClick = FinanceClick
    end
    object Prive: TMenuItem
      Caption = 'Priv'#233
      object PrivRecettes: TMenuItem
        Caption = 'Recettes'
        OnClick = PrivRecettesClick
      end
      object PrivDepenses: TMenuItem
        Caption = 'D'#233'penses'
        OnClick = PrivDepensesClick
      end
    end
    object EnCours: TMenuItem
      Caption = 'EnCours'
      OnClick = EnCoursClick
    end
    object Occc: TMenuItem
      Caption = 'Occc'
      OnClick = OcccClick
    end
    object Resultat: TMenuItem
      Caption = 'RESULTAT'
      object TresoDetail: TMenuItem
        Caption = 'D'#233'taill'#233'e'
        OnClick = TresoDetailClick
      end
      object TresoSemiDetail: TMenuItem
        Caption = 'SemiD'#233'taill'#233'e'
        OnClick = TresoSemiDetailClick
      end
      object TresoSynthese: TMenuItem
        Caption = 'Synth'#232'se'
        OnClick = TresoSyntheseClick
      end
      object Quantite: TMenuItem
        Caption = 'Quantit'#233's'
        OnClick = QuantiteClick
      end
    end
  end
end
