//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "AgriSaisie.h"

#include "TypeEmpCT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTypeEmpCTFrm *TypeEmpCTFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTypeEmpCTFrm::TTypeEmpCTFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTypeEmpCTFrm::BtBnOkClick(TObject *Sender)
{
	int r;
	char chaine[3],chaineEP[2];
	r=AgriSaisieFrm->LaGrille->Row;
	if(AgriSaisieFrm->LaGrille->Cells[2][r]=="") return; //300407

	AgriSaisieFrm->LabelModifie->Visible=true;
	chaine[1]=0;
	chaineEP[1]=0;
	switch(RGInteret->ItemIndex)
	{
		case 0:chaine[0]='N';break;
		case 1:chaine[0]='P';break;
	}
	switch(RGEP->ItemIndex)
	{
		case 0:chaineEP[0]='E';break;
		case 1:chaineEP[0]='P';break;
	}
	AgriSaisieFrm->LaGrille->Cells[5][r]=chaine;
	AgriSaisieFrm->LaGrille->Cells[8][r]=chaineEP;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTypeEmpCTFrm::IniCaption(void) {
	RGInteret->Caption = T->LC_Interet;
	RGInteret->Items->Strings[0] = LC_Normal;
	RGInteret->Items->Strings[1] = LC_PreCompte;

	RGEP->Caption = T->LC_EP;
	RGEP->Items->Strings[0] = T->LC_Entreprise;
	RGEP->Items->Strings[1] = T->LC_Prive;
}
//--------------------------------------------
void TTypeEmpCTFrm::TexteCaption(void) {
	LC_Interet = T->TrouveCaption("CL_Trad", "LC_Interet");
	LC_Normal = T->TrouveCaption("TypeEmpCT", "LC_Normal");
	LC_PreCompte = T->TrouveCaption("TypeEmpCT", "LC_PreCompte");

	LC_EP = T->TrouveCaption("CL_Trad", "LC_EP");
	LC_Entreprise = T->TrouveCaption("CL_Trad", "LC_Entreprise");
	LC_Prive = T->TrouveCaption("CL_Trad", "LC_Prive");
	IniCaption();

}
