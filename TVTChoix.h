//---------------------------------------------------------------------------

#ifndef TVTChoixH
#define TVTChoixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVTChoixFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);
private:
	// Déclarations utilisateur
	int Digits;void __fastcall TVDblClickProduit(void);bool __fastcall Doublon(CL_Item *item);

public:
	// Déclarations utilisateur
	__fastcall TTVTChoixFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVTChoixFrm *TVTChoixFrm;
//---------------------------------------------------------------------------
#endif
