//---------------------------------------------------------------------------

#ifndef RendementH
#define RendementH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Tendance.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "AleaPrix.h"
//---------------------------------------------------------------------------
class TRendementFrm: public TAleaPrixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall BtDonneesClick(TObject *Sender);
private:
	// D�clarations utilisateur
public:
	// D�clarations utilisateur
	void __fastcall Produit(int *nature);
protected:
	virtual void __fastcall IniGrille0(void);

	__fastcall TRendementFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRendementFrm *RendementFrm;
//---------------------------------------------------------------------------
#endif
