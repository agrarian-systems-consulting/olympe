//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "NoteAgri.h"
#include "Ensemble.h"
#include "GereEnsemble.h"
#include "CL_Trad.h"
#include "Aide.h"

//#include "Erreur.h"
#include "Resultat.h"

#include "LBCompAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBCompAgriFrm *LBCompAgriFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBCompAgriFrm::TLBCompAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
// ChLB  a été créé dans Resultat Activate
//---------------------------------------------------------------------------
void __fastcall TLBCompAgriFrm::FormActivate(TObject *Sender)
{
	if(Screen->Width<1024) //241001
	{
		Top=ResultatFrm->Top;
		Left=ResultatFrm->Left;
	}
	else
	{
		Top=ResultatFrm->Top;
		Left=ResultatFrm->Left-Width;
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBCompAgriFrm::BtBnTousClick(TObject *Sender)
{
	int n;
	for( n=0;n<ChLB->Items->Count;n++)
	ChLB->Checked[n]=true;
}
//---------------------------------------------------------------------------
void __fastcall TLBCompAgriFrm::BtBnAucunClick(TObject *Sender)
{
	int n;
	for( n=0;n<ChLB->Items->Count;n++)
	ChLB->Checked[n]=false;
}
//---------------------------------------------------------------------------
void __fastcall TLBCompAgriFrm::BtBnFermerClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBCompAgriFrm::IniCaption(void) {
	BtBnAucun->Caption = T->LC_BtIndAucun;
	LBCompAgriFrm->Caption = T->LC_GereAgriFrm;
	BtBnTous->Caption = T->LC_BtIndTous;
}
//--------------------------------------------
void TLBCompAgriFrm::TexteCaption(void) {
	LC_BtIndAucun = T->TrouveCaption("CL_Trad", "LC_BtIndAucun");
	LC_GereAgriFrm = T->TrouveCaption("CL_Trad", "LC_GereAgriFrm");
	LC_BtIndTous = T->TrouveCaption("CL_Trad", "LC_BtIndTous");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBCompAgriFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

