//---------------------------------------------------------------------------

#ifndef GereCatVariableH
#define GereCatVariableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCatVariableFrm: public TGereCatItemFrm {
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
	AnsiString LC_GereCatVariableFrm;

	__fastcall TGereCatVariableFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCatVariableFrm *GereCatVariableFrm;
//---------------------------------------------------------------------------
#endif
