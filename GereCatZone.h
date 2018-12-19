//---------------------------------------------------------------------------

#ifndef GereCatZoneH
#define GereCatZoneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCatZoneFrm: public TGereCatItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall LBClick(TObject *Sender);void __fastcall BtSupprimerClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
	void __fastcall MajLBCatCritere(void);
protected:
	virtual void __fastcall Personnaliser(void);
public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_DefZoneFrm;
	__fastcall TGereCatZoneFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCatZoneFrm *GereCatZoneFrm;
//---------------------------------------------------------------------------
#endif
