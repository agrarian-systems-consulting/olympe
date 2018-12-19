//---------------------------------------------------------------------------

#ifndef GereEtatIndicH
#define GereEtatIndicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereAtelier.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereEtatIndicFrm: public TGereAtelierFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);void __fastcall BtBnCreeCatClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall BtBnFermerClick(TObject *Sender);void __fastcall BtBnCreeAtelierClick(TObject *Sender);void __fastcall BtCopierClick(TObject *Sender);void __fastcall BtSupprimerClick(TObject *Sender);void __fastcall BtChgtNomClick(TObject *Sender);
private:
	// Déclarations utilisateur
	CL_Indicateur *NouvIndic;
	CL_EtatSortie *NouvEtat;virtual void __fastcall InsererCategorie(AnsiString NewNom);virtual bool __fastcall CEstBon(void);bool __fastcall IndicateurBon(void);bool __fastcall EtatSortieBon(void);virtual bool __fastcall existeDeja(void);void __fastcall InsererIndic(void);void __fastcall InsererEtat(void);void __fastcall CopierIndic(void);void __fastcall CopierEtat(void);void __fastcall ChgtNomIndic(void);void __fastcall ChgtNomEtat(void);

public:
	// Déclarations utilisateur
	__fastcall TGereEtatIndicFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereEtatIndicFrm *GereEtatIndicFrm;
//---------------------------------------------------------------------------
#endif
