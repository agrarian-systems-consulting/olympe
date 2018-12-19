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
	__published: // Composants gérés par l'EDI
	void __fastcall FormCreate(TObject *Sender);void __fastcall LBClick(TObject *Sender);
private:
	// Déclarations utilisateur
public:
	// Déclarations utilisateur
	__fastcall TLBReservoirFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBReservoirFrm *LBReservoirFrm;
//---------------------------------------------------------------------------
#endif
