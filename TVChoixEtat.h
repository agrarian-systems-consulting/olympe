//---------------------------------------------------------------------------

#ifndef TVChoixEtatH
#define TVChoixEtatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixEtatFrm: public TTVChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall TVDblClick(TObject *Sender);void __fastcall FormActivate(TObject *Sender);
private:
	// D�clarations utilisateur
public:
	// D�clarations utilisateur
	__fastcall TTVChoixEtatFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixEtatFrm *TVChoixEtatFrm;
//---------------------------------------------------------------------------
#endif
