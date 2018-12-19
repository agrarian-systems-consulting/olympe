//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "AgriSaisie.h"
#include "TypeAmor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTypeAmorFrm *TypeAmorFrm;

extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TTypeAmorFrm::TTypeAmorFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTypeAmorFrm::BtBnOkClick(TObject *Sender)
{
	int r;
	char chaine[4];
	r=AgriSaisieFrm->LaGrille->Row;
	if(AgriSaisieFrm->LaGrille->Cells[2][r]=="") return; //300407
	AgriSaisieFrm->LabelModifie->Visible=true;
	chaine[1]=0;
	switch(RGAmor->ItemIndex)
	{
		case 0:chaine[0]='D';break;
		case 1:chaine[0]='L';break;
		case 2:chaine[0]='N';break;
	}
	AgriSaisieFrm->LaGrille->Cells[5][r]=chaine;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTypeAmorFrm::IniCaption(void) {
	RGAmor->Caption = LC_Amor;
	RGAmor->Items->Strings[0] = LC_Degressif;
	RGAmor->Items->Strings[1] = LC_Lineaire;
	RGAmor->Items->Strings[2] = LC_Sans;
}
//--------------------------------------------
void TTypeAmorFrm::TexteCaption(void) {
	LC_Amor = T->TrouveCaption("TypeAmor", "LC_Amor");
	LC_Degressif = T->TrouveCaption("TypeAmor", "LC_Degressif");
	LC_Lineaire = T->TrouveCaption("TypeAmor", "LC_Lineaire");
	LC_Sans = T->TrouveCaption("TypeAmor", "LC_Sans");
	IniCaption();

}
