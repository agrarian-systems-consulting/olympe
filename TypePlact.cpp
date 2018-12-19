//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "AgriSaisie.h"
#include "CL_Trad.h"

#include "TypePlact.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTypePlactFrm *TypePlactFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTypePlactFrm::TTypePlactFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTypePlactFrm::BtBnOkClick(TObject *Sender)
{
	int r;
	char chaine[3],chaineEP[2];
	AgriSaisieFrm->LabelModifie->Visible=true;
	r=AgriSaisieFrm->LaGrille->Row;
	chaine[1]=0;
	chaineEP[1]=0;
	switch(RGInteret->ItemIndex)
	{
		case 0:chaine[0]='A';break;
		case 1:chaine[0]='F';break;
	}
	switch(RGEP->ItemIndex)
	{
		case 0:chaineEP[0]='E';break;
		case 1:chaineEP[0]='P';break;
	}
	AgriSaisieFrm->LaGrille->Cells[5][r]=chaine;
	AgriSaisieFrm->LaGrille->Cells[8][r]=chaineEP;

}
//--------------------------------------------
void TTypePlactFrm::IniCaption(void) {
	RGInteret->Caption = T->LC_Interet;
	RGInteret->Items->Strings[0] = LC_Annuel;
	RGInteret->Items->Strings[1] = LC_AlaFin;

	RGEP->Caption = T->LC_EP;
	RGEP->Items->Strings[0] = T->LC_Entreprise;
	RGEP->Items->Strings[1] = T->LC_Prive;
}
//--------------------------------------------
void TTypePlactFrm::TexteCaption(void) {
	LC_Interet = T->TrouveCaption("CL_Trad", "LC_Interet");
	LC_Annuel = T->TrouveCaption("TypePlact", "LC_Annuel");
	LC_AlaFin = T->TrouveCaption("TypePlact", "LC_AlaFin");

	LC_EP = T->TrouveCaption("CL_Trad", "LC_EP");
	LC_Entreprise = T->TrouveCaption("CL_Trad", "LC_Entreprise");
	LC_Prive = T->TrouveCaption("CL_Trad", "LC_Prive");
	IniCaption();
}
//---------------------------------------------------------------------------

