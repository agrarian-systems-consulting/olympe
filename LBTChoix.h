//---------------------------------------------------------------------------

#ifndef LBTChoixH
#define LBTChoixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoix.h"
//---------------------------------------------------------------------------
class TLBTChoixFrm: public TLBChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall LBClick(TObject *Sender);void __fastcall FormActivate(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// D�clarations utilisateur
	void __fastcall LBClickTendance(void);
public:
	// D�clarations utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LBTChoixFrm;

	__fastcall TLBTChoixFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBTChoixFrm *LBTChoixFrm;
//---------------------------------------------------------------------------
#endif
