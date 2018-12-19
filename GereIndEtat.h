//---------------------------------------------------------------------------
#ifndef GereIndEtatH
#define GereIndEtatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCat.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGereIndEtatFrm: public TGereCatFrm {
	__published: // Composants gérés par l'EDI
TButton	*BtCopier;
	TTreeView *TV;
	TLabel *LabCat;
	TEdit *EdCategorie;
	TButton *BtSup;
	void __fastcall FormActivate(TObject *Sender);
//	void __fastcall BtNouveauClick(TObject *Sender);
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall BtPasOkClick(TObject *Sender);
	void __fastcall BtCopierClick(TObject *Sender);
//	void __fastcall BtSupprimerClick(TObject *Sender);
//	void __fastcall LBClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnFermerClick(TObject *Sender);
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
private:// Déclarations de l'utilisateur
	CL_Indicateur *NouvInd;
	CL_EtatSortie *NouvEtat;
	CL_Categorie *Categorie;
	bool AjoutCategorie;
	virtual bool __fastcall CEstBon(void);

	bool __fastcall IndicateurBon(void);
	bool __fastcall EtatSortieBon(void);
	void __fastcall nouveau(void);
	void __fastcall ajoutCategorie(void);

public:// Déclarations de l'utilisateur
	__fastcall TGereIndEtatFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereIndEtatFrm *GereIndEtatFrm;
//---------------------------------------------------------------------------
#endif
