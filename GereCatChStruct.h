//---------------------------------------------------------------------------

#ifndef GereCatChStructH
#define GereCatChStructH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCatChStructFrm: public TGereCatItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall LBClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
protected:
	virtual void __fastcall Personnaliser(void);

public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereCatChStructFrm;

	__fastcall TGereCatChStructFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCatChStructFrm *GereCatChStructFrm;
//---------------------------------------------------------------------------
#endif
