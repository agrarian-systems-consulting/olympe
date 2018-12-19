//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Classe2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClasse2Frm *Classe2Frm;
//---------------------------------------------------------------------------
__fastcall TClasse2Frm::TClasse2Frm(TComponent* Owner) :
		TFrame(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TClasse2Frm::BtHautClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
	TObject *object;
	TGridRect selection;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row<=1) return;

	object=LaGrille->Objects[0][row];
	LaGrille->Objects[0][row]=LaGrille->Objects[0][row-1];
	LaGrille->Objects[0][row-1]=object;

	for(c=0;c<cX;c++)
	{
		s=LaGrille->Cells[c][row];
		LaGrille->Cells[c][row]=LaGrille->Cells[c][row-1];
		LaGrille->Cells[c][row-1]=s;
	}
	selection.Left=1;
	selection.Right=cX-1;
	selection.Top=row-1;
	selection.Bottom=row-1;
	LaGrille->Selection=selection;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TClasse2Frm::BtBasClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
	TObject *object;
	TGridRect selection;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row>=LaGrille->RowCount-1) return;

	object=LaGrille->Objects[0][row];
	LaGrille->Objects[0][row]=LaGrille->Objects[0][row-1];
	LaGrille->Objects[0][row+1]=object;

	for(c=0;c<cX;c++)
	{
		s=LaGrille->Cells[c][row];
		LaGrille->Cells[c][row]=LaGrille->Cells[c][row+1];
		LaGrille->Cells[c][row+1]=s;
	}
	selection.Left=1;
	selection.Right=cX-1;
	selection.Top=row+1;
	selection.Bottom=row+1;
	LaGrille->Selection=selection;
}
//---------------------------------------------------------------------------

