//---------------------------------------------------------------------------

#ifndef GereCompH
#define GereCompH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereEtat.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCompFrm: public TGereEtatFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormActivate(TObject *Sender);
private:
	// D�clarations de l'utilisateur
protected:
	virtual void __fastcall CreeTV(void);

public:
	// D�clarations de l'utilisateur
	void __fastcall CompleteComparaison(void); //agriSaisieCalcul
	__fastcall TGereCompFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCompFrm *GereCompFrm;
//---------------------------------------------------------------------------
#endif
