//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "CL_Trad.h"

#include "Aide.h"

#include "GereEnsemble.h"
#include "Ensemble.h"
#include "DefProcedure.h"

#include "LBSelectionAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBSelectionAgriFrm *LBSelectionAgriFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLBSelectionAgriFrm::TLBSelectionAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBSelectionAgriFrm::FormActivate(TObject *Sender)
{
	LB->Items->Clear();
	if(VientDe=="DefProcedure")
	{
		LB->Items->Add(L_Manuel); //"Manuel");
		LB->Items->Add(L_Tri);//"Tri");
	}
	else
	{
		LB->Items->Add(L_Manuel); //("Manuel");
		LB->Items->Add(L_Tri);//("Tri");
		LB->Items->Add(L_Addition);//"Addition");
		LB->Items->Add(L_Extraire);//"Extraire");
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLBSelectionAgriFrm::BtBnOKClick(TObject *Sender)
{
	int n;
	n=LB->ItemIndex;
	if(VientDe=="GereEnsemble")
	{
		switch(n)
		{
			case 0: GereEnsembleFrm->SelectionManuelle();break;
			case 1: GereEnsembleFrm->SelectionTri(); break;
			case 2: GereEnsembleFrm->SelectionAddition();break;
			case 3: GereEnsembleFrm->Extraction(); break;
			default: ShowMessage("LBSelection Oubli");
		}
	}
	else if(VientDe=="Ensemble")
	{
		switch(n)
		{
			case 0: EnsembleFrm->SelectionManuelle();break;
			case 1: EnsembleFrm->SelectionTri(); break;
			case 2: EnsembleFrm->SelectionAddition();break;
			case 3: EnsembleFrm->Extraction(); break;
			default: ShowMessage("LBSelection Oubli");
		}
	}
	else if(VientDe=="DefProcedure")
	{
		switch(n)
		{
			case 0: DefProcedureFrm->SelectionManuelle();break;
			case 1: DefProcedureFrm->SelectionTri(); break;
			default: ShowMessage("LBSelection Oubli");
		}
	}
	else
	{
		ShowMessage("LBSelection Oubli");
	}

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TLBSelectionAgriFrm::BtBnPasOKClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLBSelectionAgriFrm::TexteChaine(void) {

	L_Manuel = T->TrouveTexte("LBSelectionAgriFrm", "L_Manuel");
	L_Tri = T->TrouveTexte("LBSelectionAgriFrm", "L_Tri");
	L_Addition = T->TrouveTexte("LBSelectionAgriFrm", "L_Addition");
	L_Extraire = T->TrouveTexte("LBSelectionAgriFrm", "L_Extraire");
}
//--------------------------------------------
void TLBSelectionAgriFrm::IniCaption(void) {
	LBSelectionAgriFrm->Caption = LC_LBSelectionAgriFrm;
}
//--------------------------------------------
void TLBSelectionAgriFrm::TexteCaption(void) {
	LC_LBSelectionAgriFrm = T->TrouveCaption("LBSelectionAgri",
			"LC_LBSelectionAgriFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBSelectionAgriFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

