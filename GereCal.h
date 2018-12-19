//---------------------------------------------------------------------------

#ifndef GereCalH
#define GereCalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCalFrm: public TGereCatItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);void __fastcall BtBnCopierClick(TObject *Sender);void __fastcall BtBnCreerClick(TObject *Sender);void __fastcall BtSupprimerClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall BtModifierNomClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	CL_Calendrier *Calendrier;virtual void __fastcall VerifNomCat(AnsiString newNom,int action);virtual void __fastcall StockerOrdreCalendrier(void);

public:
	// Déclarations de l'utilisateur
	__fastcall TGereCalFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCalFrm *GereCalFrm;
//---------------------------------------------------------------------------
#endif
