//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AgriSaisie.h"

#include "LbChoixExter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoix"
#pragma resource "*.dfm"
TLBChoixExterFrm *LBChoixExterFrm;
// entrer nouvelle externalité
//---------------------------------------------------------------------------
__fastcall TLBChoixExterFrm::TLBChoixExterFrm(TComponent* Owner) :
		TLBChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixExterFrm::LBClick(TObject *Sender)
{
	int n;
	int rep;
	CL_Item *item;
	int r=LaGrille->Row;
	int col=LaGrille->Col;
	if(col!=2) return;
	if(AgriSaisieFrm->RGModifiable->ItemIndex==0)return;

	n=LB->ItemIndex;
	item=(CL_Item*)LB->Items->Objects[n];

	if(LaGrille->Cells[2][r]=="")
	LaGrille->Cells[2][r]=item->Nom;
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_YES)
		LaGrille->Cells[2][r]=item->Nom;
	}
	Forme00Frm->AjouterRow();

}

