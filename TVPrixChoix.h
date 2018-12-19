//---------------------------------------------------------------------------

#ifndef TVPrixChoixH
#define TVPrixChoixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"//
//---------------------------------------------------------------------------
class TTVPrixChoixFrm: public TTVChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);
private:
	// D�clarations utilisateur
	void __fastcall TVDblClickProduit(void);bool __fastcall Doublon(CL_Item *item);

public:
	// D�clarations utilisateur
	int Digits, DigitsPrix;
	__fastcall TTVPrixChoixFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVPrixChoixFrm *TVPrixChoixFrm;
//---------------------------------------------------------------------------
#endif
