//---------------------------------------------------------------------------

#ifndef TVChoixMargeH
#define TVChoixMargeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoixEtat.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixMargeFrm: public TTVChoixEtatFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall TVDblClick(TObject *Sender);void __fastcall FormActivate(TObject *Sender);void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
	// Déclarations utilisateur
public:
	// Déclarations utilisateur
	__fastcall TTVChoixMargeFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixMargeFrm *TVChoixMargeFrm;
//---------------------------------------------------------------------------
#endif
