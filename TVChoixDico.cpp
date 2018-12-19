//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"

#include "LireFichier.h"
#include "Forme00.h"
#include "AgriSaisie.h"
#include "TVChoixDico.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVChoixDicoFrm *TVChoixDicoFrm;
//---------------------------------------------------------------------------
__fastcall TTVChoixDicoFrm::TTVChoixDicoFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixDicoFrm::TVDblClick(TObject *Sender)
{
	int rep;
	TTreeNode *choix;
	CL_Item *item;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	if(RGModifiable->ItemIndex==0)return;

	if(c!=2) return;

	choix=TV->Selected;
	if(choix->Level==0) return;

	item=(CL_Item*)choix->Data;

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
//---------------------------------------------------------------------------

