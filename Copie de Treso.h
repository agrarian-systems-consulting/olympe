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
	TMenuItem *TypeValQuant;
	TMenuItem *Total;
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
	void __fastcall ProduitsClick(TObject *Sender);
	void __fastcall DefinitionClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall OperationnellesClick(TObject *Sender);
	void __fastcall StructureClick(TObject *Sender);
	void __fastcall DivRecettesClick(TObject *Sender);
	void __fastcall DivDepensesClick(TObject *Sender);
	void __fastcall PrivRecettesClick(TObject *Sender);
	void __fastcall PrivDepensesClick(TObject *Sender);
	void __fastcall TypeValQuantClick(TObject *Sender);
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
private: // Déclarations utilisateur
	CL_Vecteur<CL_QuanVal> *V_QuanVal;
	void __fastcall TTresoFrm::QuantOuVal(void);
	void __fastcall TTresoFrm::CompleteQuanVal(void);
	void __fastcall CompleteQuanVal1(CL_Vecteur<CL_QuanVal>*vecteur,int nature);
	CL_ItemRepart* __fastcall TrouveItemRepart(int noItem,int nature);
	CL_ItemRepart* __fastcall TTresoFrm::TrouveItemRepart(int famille);

	void __fastcall StockRepart(void);
	void __fastcall StockRepart1(CL_Vecteur<CL_QuanVal>*vecteur);

public:// Déclarations utilisateur
	int Origine;
//	int QouV;
	int Nature;//PRODUIT CHARGE
	bool IlYaModif;
	__fastcall TTresoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoFrm *TresoFrm;
//---------------------------------------------------------------------------
#endif
