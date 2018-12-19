//---------------------------------------------------------------------------

#ifndef LBChoixMCActionH
#define LBChoixMCActionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoixMC.h"
//---------------------------------------------------------------------------
class TLBChoixMCActionFrm: public TLBChoixMCFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	bool EstInitialise;
	TRichEdit *Edit;
public:
	// Déclarations de l'utilisateur
	__fastcall TLBChoixMCActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixMCActionFrm *LBChoixMCActionFrm;
//---------------------------------------------------------------------------
#endif
