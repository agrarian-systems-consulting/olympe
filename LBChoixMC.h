//---------------------------------------------------------------------------
#ifndef LBChoixMCH
#define LBChoixMCH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoix.h"
//---------------------------------------------------------------------------
class TLBChoixMCFrm: public TLBChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall LBClick(TObject *Sender);

private:
	// D�clarations de l'utilisateur

public:
	// D�clarations de l'utilisateur
	void TraduireMotCle(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtMotCle;

	__fastcall TLBChoixMCFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixMCFrm *LBChoixMCFrm;
//---------------------------------------------------------------------------
#endif
