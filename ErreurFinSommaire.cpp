//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "ErreurFinSommaire.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ErreurImmoSommaire"
#pragma resource "*.dfm"
TErreurFinSommaireFrm *ErreurFinSommaireFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TErreurFinSommaireFrm::TErreurFinSommaireFrm(TComponent* Owner) :
		TErreurImmoSommaireFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TErreurFinSommaireFrm::BtBnCalculerClick(TObject *Sender)
{
	int n;
	int col;
	AgriSaisieFrm->LabelModifie->Visible=true;
	switch(RG->ItemIndex) //dette
	{
		case 0:
		for(n=0,col=4;n<N_X;n++,col++)
		{
			detteLT[n+1]=detteLT[n]-rembLT[n]+nouvLT[n];
			if(detteLT[n+1] <=0)
			{
				detteLT[n+1]=0;
				rembLT[n]=detteLT[n]+nouvLT[n];
				LaGrille->Cells[col][2]=rembLT[n];
			}
			LaGrille->Cells[col][1]=Forme00Frm->Aff(detteLT[n+1],0);
		}
		break;
		case 1: //remb
		for(n=0,col=4;n<N_X;n++,col++)
		{
			rembLT[n]=detteLT[n]-detteLT[n+1]+nouvLT[n];
			LaGrille->Cells[col][2]=Forme00Frm->Aff(rembLT[n],0);
		}
		break;
		case 2:
		return;
	}
	Close();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TErreurFinSommaireFrm::IniCaption(void) {
	ErreurFinSommaireFrm->Caption = LC_ErreurFinSommaireFrm;
}
//--------------------------------------------
void TErreurFinSommaireFrm::TexteCaption(void) {
	LC_ErreurFinSommaireFrm = T->TrouveCaption("ErreurFinSommaire",
			"LC_ErreurFinSommaireFrm");

	IniCaption();

}
//--------------------------------------------
//---------------------------------------------------------------------------
void TErreurFinSommaireFrm::TexteChaine(void) {
	L_LaFormule = T->TrouveTexte("ErreurFinSommaireFrm", "L_LaFormule");
	L_DetteN = T->TrouveTexte("ErreurFinSommaireFrm", "L_DetteN");
	L_DetteN1 = T->TrouveTexte("ErreurFinSommaireFrm", "L_DetteN1");
	L_RembourN = T->TrouveTexte("ErreurFinSommaireFrm", "L_RembourN");
	L_NouveauN = T->TrouveTexte("ErreurFinSommaireFrm", "L_NouveauN");
	L_NonVerif = T->TrouveTexte("ErreurFinSommaireFrm", "L_NonVerif");

	L_Dette = T->TrouveTexte("ErreurFinSommaireFrm", "L_Dette");
	L_Rembour = T->TrouveTexte("ErreurFinSommaireFrm", "L_Rembour");
	L_NeRienFaire = T->TrouveTexte("ErreurFinSommaireFrm", "L_NeRienFaire");

	RE->Clear();
	RE->Lines->Add(L_LaFormule);
	RE->Lines->Add(L_DetteN);
	RE->Lines->Add(L_DetteN1);
	RE->Lines->Add(L_RembourN);
	RE->Lines->Add(L_NouveauN);
	RE->Lines->Add(L_NonVerif);

	RG->Items->Strings[0] = L_Dette;
	RG->Items->Strings[1] = L_Rembour;
	RG->Items->Strings[2] = L_NeRienFaire;

}

