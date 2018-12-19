//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "ErreurImmoSommaire.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TErreurImmoSommaireFrm *ErreurImmoSommaireFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TErreurImmoSommaireFrm::TErreurImmoSommaireFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TErreurImmoSommaireFrm::BtBnCalculerClick(TObject *Sender)
{
	int n;
	int col;
	AgriSaisieFrm->LabelModifie->Visible=true;
	switch(RG->ItemIndex)
	{
		case 0:
		for(n=0,col=4;n<N_X+1;n++,col++)
		{
			Resid[n+1]=Resid[n]-Amor[n]+Achat[n]-Revente[n]+ProdImmo[n];
			LaGrille->Cells[col][1]=Resid[n+1];
		}
		break;
		case 1:
		for(n=0,col=4;n<N_X+1;n++,col++)
		{
//	        	Resid[n+1]=Resid[n]-Amor[n]+Achat[n]-Revente[n]+ProdImmo[n];
			Amor[n]=Resid[n]-Resid[n+1]+Achat[n]-Revente[n]+ProdImmo[n];
			LaGrille->Cells[col][2]=Amor[n];
		}
		break;
		case 2:
		return;
	}
	Close();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TErreurImmoSommaireFrm::IniCaption(void) {
	RG->Caption = T->LC_RG;
	BtBnCalculer->Caption = T->LC_RG;
	GB->Caption = T->LC_ErreurFrm;
	ErreurImmoSommaireFrm->Caption = LC_ErreurImmoSommaireFrm;
}
//--------------------------------------------
void TErreurImmoSommaireFrm::TexteCaption(void) {
	LC_RG = T->TrouveCaption("CL_Trad", "LC_RG");
	LC_ErreurFrm = T->TrouveCaption("CL_Trad", "LC_ErreurFrm");
	LC_ErreurImmoSommaireFrm = T->TrouveCaption("ErreurImmoSommaire",
			"LC_ErreurImmoSommaireFrm");

	IniCaption();

}
//---------------------------------------------------------------------------
void TErreurImmoSommaireFrm::TexteChaine(void) {
	L_LaFormule = T->TrouveTexte("ErreurImmoSommaireFrm", "L_LaFormule");
	L_ValResid = T->TrouveTexte("ErreurImmoSommaireFrm", "L_ValResid");
	L_ValResidN = T->TrouveTexte("ErreurImmoSommaireFrm", "L_ValResidN");
	L_Amor = T->TrouveTexte("ErreurImmoSommaireFrm", "L_Amor");
	L_Achat = T->TrouveTexte("ErreurImmoSommaireFrm", "L_Achat");
	L_Revente = T->TrouveTexte("ErreurImmoSommaireFrm", "L_Revente");
	L_ProdImmo = T->TrouveTexte("ErreurImmoSommaireFrm", "L_ProdImmo");
	L_NonVerif = T->TrouveTexte("ErreurImmoSommaireFrm", "L_NonVerif");

	L_ValResiduelles = T->TrouveTexte("ErreurImmoSommaireFrm",
			"L_ValResiduelles");
	L_Amors = T->TrouveTexte("ErreurImmoSommaireFrm", "L_Amors");
	L_NeRienFaire = T->TrouveTexte("ErreurImmoSommaireFrm", "L_NeRienFaire");

	RE->Clear();
	RE->Lines->Add(L_LaFormule);
	RE->Lines->Add(L_ValResid);
	RE->Lines->Add(L_ValResidN);
	RE->Lines->Add(L_Amor);
	RE->Lines->Add(L_Achat);
	RE->Lines->Add(L_Revente);
	RE->Lines->Add(L_ProdImmo);
	RE->Lines->Add(L_NonVerif);

	RG->Items->Strings[0] = L_ValResiduelles;
	RG->Items->Strings[1] = L_Amors;
	RG->Items->Strings[2] = L_NeRienFaire;

}

