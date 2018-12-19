//---------------------------------------------------------------------------
#ifndef TVChoixDicoH
#define TVChoixDicoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixDicoFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall TVDblClick(TObject *Sender);

private:
	// Déclarations de l'utilisateur
public:
	// Déclarations de l'utilisateur
	__fastcall TTVChoixDicoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixDicoFrm *TVChoixDicoFrm;
//---------------------------------------------------------------------------
#endif
