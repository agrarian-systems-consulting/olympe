//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Forme00.h"
#include "ReclasseG.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReclasseGFrm *ReclasseGFrm;
//---------------------------------------------------------------------------
__fastcall TReclasseGFrm::TReclasseGFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TReclasseGFrm::FormActivate(TObject *Sender)
{
	TGridRect selection;

	Forme00Frm->Grille0->Options<<goRowSelect;

	selection.Top = selection.Bottom = Forme00Frm->Grille0->Row;
	selection.Left = 0;
	selection.Right = Forme00Frm->Grille0->ColCount - 1;
	Forme00Frm->Grille0->Selection = selection;

}
//---------------------------------------------------------------------------
void __fastcall TReclasseGFrm::BtHautClick(TObject *Sender)
{
	int col;
	int r;
	AnsiString swap;
	r=Forme00Frm->Grille0->Row;
	if(r==1) return;
	for (col=0;col<Forme00Frm->Grille0->ColCount;col++)
	{
		swap=Forme00Frm->Grille0->Cells[col][r-1];
		Forme00Frm->Grille0->Cells[col][r-1]=Forme00Frm->Grille0->Cells[col][r];
		Forme00Frm->Grille0->Cells[col][r]=swap;
	}
	Forme00Frm->Grille0->Row--;

}
//---------------------------------------------------------------------------
void __fastcall TReclasseGFrm::BtBasClick(TObject *Sender)
{
	int r;
	int col;
	AnsiString swap;
	TObject *objectSwap;
	r=Forme00Frm->Grille0->Row;
	if(r>=Forme00Frm->Grille0->RowCount-1) return;
	objectSwap=Forme00Frm->Grille0->Objects[0][r+1];
	Forme00Frm->Grille0->Objects[0][r+1]=Forme00Frm->Grille0->Objects[0][r];
	Forme00Frm->Grille0->Objects[0][r]= objectSwap;
	for (col=0;col<Forme00Frm->Grille0->ColCount;col++)
	{
		swap=Forme00Frm->Grille0->Cells[col][r+1];
		Forme00Frm->Grille0->Cells[col][r+1]=Forme00Frm->Grille0->Cells[col][r];
		Forme00Frm->Grille0->Cells[col][r]=swap;
	}
	Forme00Frm->Grille0->Row++;
}
//---------------------------------------------------------------------------
void __fastcall TReclasseGFrm::BtOKClick(TObject *Sender)
{
	Forme00Frm->Grille0->Options>>goRowSelect;
	Close();
}
//---------------------------------------------------------------------------

