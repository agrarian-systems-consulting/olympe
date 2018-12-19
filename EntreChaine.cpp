//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Util.h"
#include "CL_Trad.h"

#include "EntreChaine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEntreChaineFrm *EntreChaineFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TEntreChaineFrm::TEntreChaineFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
bool __fastcall TEntreChaineFrm::EntreChaine(AnsiString Titre,
		AnsiString AAfficher,AnsiString &Nom)
{
	Caption=Titre;
	Edit1->Text=Nom;
	LabAAfficher->Caption=AAfficher;
	return true; //aew
}
//---------------------------------------------------------------------------
void __fastcall TEntreChaineFrm::Edit1KeyPress(TObject *Sender, char &Key)
{
	if(IsalnumA(Key)==1) return;
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TEntreChaineFrm::BtBnOkClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TEntreChaineFrm::BtBnAnnulClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void TEntreChaineFrm::IniCaption(void) {
	EntreChaineFrm->Caption = LC_EntreChaineFrm;
	LabAAfficher->Caption = LC_LabAAfficher;
}
//--------------------------------------------
void TEntreChaineFrm::TexteCaption(void) {
	LC_EntreChaineFrm = T->TrouveCaption("EntreChaine", "LC_EntreChaineFrm");
	LC_LabAAfficher = T->TrouveCaption("EntreChaine", "LC_LabAAfficher");

	IniCaption();

}
//--------------------------------------------

