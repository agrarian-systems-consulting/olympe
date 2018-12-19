//---------------------------------------------------------------------------

#ifndef LBChoixActionH
#define LBChoixActionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoixMC.h"
//---------------------------------------------------------------------------
class TLBChoixActionFrm: public TLBChoixMCFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	bool EstInitialise;
	TRichEdit *Edit;
public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LBChoixActionFrm;

	__fastcall TLBChoixActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixActionFrm *LBChoixActionFrm;
//---------------------------------------------------------------------------
#endif
