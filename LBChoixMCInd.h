//---------------------------------------------------------------------------
#ifndef LBChoixMCIndH
#define LBChoixMCIndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoixMC.h"
//---------------------------------------------------------------------------
class TLBChoixMCIndFrm: public TLBChoixMCFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	bool EstInitialise;
	TRichEdit *Edit;
	TRadioGroup *RGModifiable;

public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtMotCle;

	__fastcall TLBChoixMCIndFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixMCIndFrm *LBChoixMCIndFrm;
//---------------------------------------------------------------------------
#endif
