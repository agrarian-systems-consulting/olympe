//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Forme0.h"
//#include "Categorie.h"
#include "DefProduit.h"
#include "DefChStruct.h"
#include "DefBestiaux.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBTva.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBTvaFrm *LBTvaFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBTvaFrm::TLBTvaFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBTvaFrm::FormActivate(TObject *Sender)
{
	Forme0Frm->CreeLBTva(LB,V_Tva);
}
//---------------------------------------------------------------------------
void __fastcall TLBTvaFrm::LBDblClick(TObject *Sender)
{
	int n;
	CL_Tva *tva;
	n=LB->ItemIndex;
	tva=(CL_Tva*)LB->Items->Objects[n];
	if(tva==NULL)
	{
		Close();
		MainForm->BtTVAClick(this);
		return;
	}
//    if(AppelePar=="Categorie") CategorieFrm->RetourDeChoixTva(tva);
	if (AppelePar=="DefProduitFrm") DefProduitFrm->RetourDeChoixTva(tva);
	else if(AppelePar=="DefBestiauxFrm") DefBestiauxFrm->RetourDeChoixTva(tva);
	else if(AppelePar=="DefChStructFrm") DefChStructFrm->RetourDeChoixTva(tva);
	else
	ShowMessage("LBTva oubli");

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBTvaFrm::IniCaption(void) {
	LBTvaFrm->Caption = T->LC_BtBnTva;
}
//--------------------------------------------
void TLBTvaFrm::TexteCaption(void) {
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBTvaFrm::FormHelp(WORD Command, int Data, bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

