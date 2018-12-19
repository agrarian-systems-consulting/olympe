//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "AgriSaisie.h"
#include "Forme0.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBChoixTva.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBChoixTvaFrm *LBChoixTvaFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLBChoixTvaFrm::TLBChoixTvaFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixTvaFrm::FormActivate(TObject *Sender)
{
	LaGrille= AgriSaisieFrm->LaGrille;
	Top= LaGrille->Top+40;
	Forme0Frm->CreeLBTva(LB,V_Tva,true);
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixTvaFrm::LBClick(TObject *Sender)
{
	int n;
	CL_EnCours *enCours;
	CL_Tva *tva;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	AnsiString s;
	int colTva=4;
	if(c!=colTva) return;

	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		MainForm->BtTVAClick(this);
		return;
	}
	enCours=(CL_EnCours*)LaGrille->Objects[0][r];

	if(enCours==NULL)return;

	if(enCours->Flag!='N')enCours->Flag='M';

	tva=(CL_Tva*)LB->Items->Objects[n];
//    enCours->NoTva=  tva->No;
//    enCours->Tva=    tva;
	LaGrille->Cells[colTva][r]=tva->Nom;
	AgriSaisieFrm->LabelModifie->Visible=true;
	LaGrille->SetFocus();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBChoixTvaFrm::IniCaption(void) {
	LBChoixTvaFrm->Caption = T->LC_BtBnTva;
}
//--------------------------------------------
void TLBChoixTvaFrm::TexteCaption(void) {
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBChoixTvaFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

