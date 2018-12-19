//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Classe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClasseFrm *ClasseFrm;
//---------------------------------------------------------------------------
__fastcall TClasseFrm::TClasseFrm(TComponent* Owner) :
		TFrame(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TClasseFrm::BtHautClick(TObject *Sender)
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
