//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "AgriSaisie.h"
#include "AgriAtelierMarge.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBMarge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBCompAgri"
#pragma resource "*.dfm"
TLBMargeFrm *LBMargeFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBMargeFrm::TLBMargeFrm(TComponent* Owner) :
		TLBCompAgriFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBMargeFrm::BtBnOkClick(TObject *Sender)
{
	AgriSaisieFrm->MargeAtelier(); //fait les calculs
	AgriAtelierMargeFrm->Arret=false;
}
//---------------------------------------------------------------------------
void TLBMargeFrm::IniCaption(void) {
	LBMargeFrm->Caption = LC_LBMargeFrm;
	BtBnAucun->Caption = T->LC_BtIndAucun;
	BtBnTous->Caption = T->LC_BtIndTous;
}
//--------------------------------------------
void TLBMargeFrm::TexteCaption(void) {
	LC_LBMargeFrm = T->TrouveCaption("LBMarge", "LC_LBMargeFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBMargeFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

