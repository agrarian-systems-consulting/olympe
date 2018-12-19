//---------------------------------------------------------------------------

#ifndef TresoOcccH
#define TresoOcccH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TTresoOcccFrm: public TForme00Frm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormActivate(TObject *Sender);
private:
	// D�clarations de l'utilisateur
	void __fastcall VersGrille(TStringGrid *grille);

public:
	// D�clarations de l'utilisateur
	__fastcall TTresoOcccFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoOcccFrm *TresoOcccFrm;
//---------------------------------------------------------------------------
#endif
