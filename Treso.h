//---------------------------------------------------------------------------

#ifndef TresoH
#define TresoH
//---------------------------------------------------------------------------
#include <dir.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TTresoFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TMainMenu	*MainMenu;
	TMenuItem *Produits1;
	TMenuItem *Charges;
	TMenuItem *Definition;
	TMenuItem *Oprationnelles1;
	TMenuItem *Structure1;
	TMenuItem *Divers1;
	TMenuItem *Recettes;
	TMenuItem *Depenses;
	TMenuItem *Prive;
	TMenuItem *PrivRecettes;
	TMenuItem *PrivDepenses;
	TMenuItem *Resultat;
	TMenuItem *TresoDetail;
	TMenuItem *TresoSemiDetail;
	TMenuItem *TresoSynthese;
	TMenuItem *Externalites;
	TMenuItem *Immo;
	TMenuItem *Finance;
	TMenuItem *EnCours;
	TMenuItem *Occc;
	TMenuItem *Investissement;
	TMenuItem *PetitMatriel;
	TMenuItem *Quantite;
	void __fastcall ProduitsClick(TObject *Sender);
	void __fastcall DefinitionClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall OperationnellesClick(TObject *Sender);
	void __fastcall StructureClick(TObject *Sender);
	void __fastcall DivRecettesClick(TObject *Sender);
	void __fastcall DivDepensesClick(TObject *Sender);
	void __fastcall PrivRecettesClick(TObject *Sender);
	void __fastcall PrivDepensesClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TresoDetailClick(TObject *Sender);
	void __fastcall TresoSemiDetailClick(TObject *Sender);
	void __fastcall TresoSyntheseClick(TObject *Sender);
	void __fastcall FinanceClick(TObject *Sender);
	void __fastcall EnCoursClick(TObject *Sender);
	void __fastcall OcccClick(TObject *Sender);
	void __fastcall ExternalitesClick(TObject *Sender);
	void __fastcall InvestissementClick(TObject *Sender);
	void __fastcall PetitMatrielClick(TObject *Sender);
//    void __fastcall RGValOuQClick(TObject *Sender);
	void __fastcall BestiauxVenteClick(TObject *Sender);
	void __fastcall BestiauxAchatClick(TObject *Sender);
	void __fastcall QuantiteClick(TObject *Sender);
	void __fastcall TroupeauxClick(TObject *Sender);
private:// Déclarations utilisateur
	CL_Vecteur<CL_QuanVal> *V_QuanVal;
	void __fastcall TTresoFrm::QuantOuVal(void);
	void __fastcall TTresoFrm::CompleteQuanVal(void);
	void __fastcall CompleteQuanVal1(CL_Vecteur<CL_QuanVal>*vecteur,int nature);
	CL_ItemRepart* __fastcall TrouveItemRepart(int noItem,int nature);
	CL_ItemRepart* __fastcall TTresoFrm::TrouveItemRepart(int famille);
	void __fastcall CreeQuanValTroupeaux(void);
	void __fastcall StockRepart(void);
	void __fastcall StockRepart1(CL_Vecteur<CL_QuanVal>*vecteur);
	bool EstVide(float *valeur);

public:// Déclarations utilisateur
	int Origine;
//	int QouV;
	int Nature;//PRODUIT CHARGE
	bool IlYaModif;
//    CL_Agriculteur *AgriEnCours;//010506
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString L_ChoixAgri;
	AnsiString L_TresoVal;//"Tresorerie en Valeur";break;
	AnsiString L_TresoQuant;//"Tresorerie en Quantité";break;
	AnsiString L_TresoAutre;//"Tresorerie Autre";break;  // a voir
	AnsiString L_Standard;
	AnsiString L_Definir;
	AnsiString L_Aucun;

	AnsiString LC_LabPCharge;
	AnsiString LC_ChargesDivers;
	AnsiString LC_TresoDetail;
	AnsiString LC_DIVERS1;
	AnsiString LC_BtEnsEnCours;
	AnsiString LC_TSExternalite;
	AnsiString LC_Finance;
	AnsiString LC_Immo;
	AnsiString LC_Investissement;
	AnsiString LC_Occc;
	AnsiString LC_Oprationnelles1;
	AnsiString LC_PetitMatriel;
	AnsiString LC_Prive;
	AnsiString LC_BtBnProduit;
	AnsiString LC_Produits1;
	AnsiString LC_Definition;
	AnsiString LC_RESULTATS;
	AnsiString LC_TresoSemiDetail;
	AnsiString LC_Structure1;
	AnsiString LC_BtSyntDetail;
	AnsiString LC_LabTotal;
	AnsiString LC_Tresorerie;
	AnsiString LC_TypeValQuant;
	AnsiString LC_Troupeau;
	__fastcall TTresoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoFrm *TresoFrm;
//---------------------------------------------------------------------------
#endif
