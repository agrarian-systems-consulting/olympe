//---------------------------------------------------------------------------

#ifndef TresoProduitsH
#define TresoProduitsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TTresoProduitsFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TStringGrid	*SG;
	TBitBtn *BtBnCalcul;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);
	void __fastcall SGClick(TObject *Sender);
	void __fastcall BtBnCalculClick(TObject *Sender);
private: // Déclarations utilisateur
//    CL_Vecteur<CL_Formule>    *V_Formule;
	CL_Vecteur<CL_QuanVal> *V_QuanVal;
	CL_Vecteur<CL_Categorie> *V_Categorie;
	CL_Item *Item;
public:// Déclarations utilisateur
	int Origine;
	char VouQ;
	void __fastcall AffValeur(void);

	__fastcall TTresoProduitsFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoProduitsFrm *TresoProduitsFrm;
//---------------------------------------------------------------------------
#endif
