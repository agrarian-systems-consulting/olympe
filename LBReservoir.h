//---------------------------------------------------------------------------

#ifndef LBReservoirH
#define LBReservoirH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBLexique.h"
//---------------------------------------------------------------------------
class TLBReservoirFrm: public TLBLexiqueFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormCreate(TObject *Sender);void __fastcall LBClick(TObject *Sender);
private:
	// D�clarations utilisateur
public:
	// D�clarations utilisateur
	__fastcall TLBReservoirFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBReservoirFrm *LBReservoirFrm;
//---------------------------------------------------------------------------
#endif
