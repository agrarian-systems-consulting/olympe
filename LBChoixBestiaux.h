//---------------------------------------------------------------------------

#ifndef LBChoixBestiauxH
#define LBChoixBestiauxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoix.h"
#include "Troupeau.h"

//---------------------------------------------------------------------------
class TLBChoixBestiauxFrm: public TLBChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall LBClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// D�clarations de l'utilisateur
	CL_Agriculteur *Agri;

public:
	// D�clarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LBChoixBestiauxFrm;

	__fastcall TLBChoixBestiauxFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixBestiauxFrm *LBChoixBestiauxFrm;
//---------------------------------------------------------------------------
#endif
