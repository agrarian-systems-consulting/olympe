//---------------------------------------------------------------------------
#ifndef LbChoixExterH
#define LbChoixExterH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBChoix.h"
//---------------------------------------------------------------------------
class TLBChoixExterFrm: public TLBChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall LBClick(TObject *Sender);
private:
	// D�clarations de l'utilisateur
public:
	// D�clarations de l'utilisateur
	__fastcall TLBChoixExterFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixExterFrm *LBChoixExterFrm;
//---------------------------------------------------------------------------
#endif
