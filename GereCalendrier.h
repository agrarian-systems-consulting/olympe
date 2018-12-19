//---------------------------------------------------------------------------

#ifndef GereCalendrierH
#define GereCalendrierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCalendrierFrm: public TGereCatItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);void __fastcall BtBnCopierClick(TObject *Sender);void __fastcall BtBnCreerClick(TObject *Sender);void __fastcall BtSupprimerClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall BtModifierNomClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
	CL_Calendrier *Calendrier;
//    virtual void __fastcall VerifNomCat(AnsiString newNom,int action);
	virtual bool __fastcall VerifNomCat(AnsiString newNom,int action);virtual void __fastcall StockerOrdreCalendrier(void);

public:
	// Déclarations de l'utilisateur
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GereCalendrierFrm;
	AnsiString L_NouvCal;
	__fastcall TGereCalendrierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCalendrierFrm *GereCalendrierFrm;
//---------------------------------------------------------------------------
#endif
