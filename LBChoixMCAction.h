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
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);
private:
	// D�clarations de l'utilisateur
	bool EstInitialise;
	TRichEdit *Edit;
public:
	// D�clarations de l'utilisateur
	__fastcall TLBChoixMCActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixMCActionFrm *LBChoixMCActionFrm;
//---------------------------------------------------------------------------
#endif
