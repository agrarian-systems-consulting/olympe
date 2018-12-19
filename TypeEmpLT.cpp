//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CL_Trad.h"
#include "AgriSaisie.h"
#include "TypeEmpLT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTypeEmpLTFrm *TypeEmpLTFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTypeEmpLTFrm::TTypeEmpLTFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTypeEmpLTFrm::BtBnOkClick(TObject *Sender)
{
	int r;
	char chaine[3],chaineEP[2];
	r=AgriSaisieFrm->LaGrille->Row;
	if(AgriSaisieFrm->LaGrille->Cells[2][r]=="") return; //300407

	AgriSaisieFrm->LabelModifie->Visible=true;
	chaine[2]=0;
	chaineEP[1]=0;
	switch(RGTypeRemb->ItemIndex)
	{
		case 0:chaine[0]='C';break;
		case 1:chaine[0]='V';break;
		case 2:chaine[0]='D';break;
	}
	switch(RGFrequence->ItemIndex)
	{
		case 0:chaine[1]='A';break;
		case 1:chaine[1]='S';break;
		case 2:chaine[1]='T';break;
		case 3:chaine[1]='M';break;
	}
	switch(RGEP->ItemIndex)
	{
		case 0:chaineEP[0]='E';break;
		case 1:chaineEP[0]='P';break;
	}
	if(chaine[0]=='D') chaine[1]='A';
	AgriSaisieFrm->LaGrille->Cells[8][r]=chaine;
	AgriSaisieFrm->LaGrille->Cells[11][r]=chaineEP;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTypeEmpLTFrm::IniCaption(void) {
	RGTypeRemb->Caption = LC_Remboursement;
	RGTypeRemb->Items->Strings[0] = LC_Constant;
	RGTypeRemb->Items->Strings[1] = LC_Variable;
	RGTypeRemb->Items->Strings[2] = LC_Differe;

	RGFrequence->Caption = LC_Frequence;
	RGFrequence->Items->Strings[0] = LC_Annuel;
	RGFrequence->Items->Strings[1] = LC_Semestriel;
	RGFrequence->Items->Strings[2] = LC_Trimestriel;
	RGFrequence->Items->Strings[3] = LC_Mensuel;

	RGEP->Caption = T->LC_EP;
	RGEP->Items->Strings[0] = T->LC_Entreprise;
	RGEP->Items->Strings[1] = T->LC_Prive;
}
//--------------------------------------------
void TTypeEmpLTFrm::TexteCaption(void) {
	LC_Constant = T->TrouveCaption("TypeEmpLT", "LC_Constant");
	LC_Remboursement = T->TrouveCaption("TypeEmpLT", "LC_Remboursement");
	LC_Variable = T->TrouveCaption("TypeEmpLT", "LC_Variable");
	LC_Differe = T->TrouveCaption("TypeEmpLT", "LC_Differe");

	LC_Annuel = T->TrouveCaption("TypeEmpLT", "LC_Annuel");
	LC_Semestriel = T->TrouveCaption("TypeEmpLT", "LC_Semestriel");
	LC_Trimestriel = T->TrouveCaption("TypeEmpLT", "LC_Trimestriel");
	LC_Mensuel = T->TrouveCaption("TypeEmpLT", "LC_Mensuel");

	LC_EP = T->TrouveCaption("CL_Trad", "LC_EP");
	LC_Entreprise = T->TrouveCaption("CL_Trad", "LC_Entreprise");
	LC_Prive = T->TrouveCaption("CL_Trad", "LC_Prive");
	IniCaption();
}

