//---------------------------------------------------------------------------

#ifndef TresoRepartH
#define TresoRepartH
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
class TTresoRepartFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TStringGrid	*SG;
	TBitBtn *BtBnCalcul;
	TBitBtn *BtRepBas;
	TBitBtn *BtReportDroit;
	TCheckBox *ChBRepTout;
	TBitBtn *BtRepToutDroit;
	TPanel *PanHaut;
	TBitBtn *BtBnRepart;
	TLabel *LabelModifie;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);
	void __fastcall BtBnCalculClick(TObject *Sender);
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall SGDblClick(TObject *Sender);
	void __fastcall BtRepToutDroitClick(TObject *Sender);
	void __fastcall BtBnRepartClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
//	void __fastcall BtBnExtraireClick(TObject *Sender);
private:// Déclarations utilisateur
	CL_Vecteur<CL_QuanVal> *V_QuanVal;
	CL_Vecteur<CL_Categorie> *V_Categorie;
	CL_Item *Item;
	int *LesNoRepart;
	CL_Repart **LesRepart;
	void __fastcall TrouveLesRepart(int r);

public:// Déclarations utilisateur
	int Origine;
	char VouQ;
	int CalculEn;
	bool __fastcall AffRepartitions(void);
	bool __fastcall AffRepartitionsExter(void);
	bool __fastcall AffRepartitionsPetitMat(void);

	__fastcall TTresoRepartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoRepartFrm *TresoRepartFrm;
//---------------------------------------------------------------------------
#endif
