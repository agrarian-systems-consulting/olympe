//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Forme00.h"
#include "Classer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClasserFrm *ClasserFrm;
//---------------------------------------------------------------------------
__fastcall TClasserFrm::TClasserFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TClasserFrm::BtClHautClick(TObject *Sender)
{
	Forme00Frm->BtHaut();
}
//---------------------------------------------------------------------------
void __fastcall TClasserFrm::BtClBasClick(TObject *Sender)
{
	Forme00Frm->BtBas();
}

/*
 //---------------------------------------------------------------------------
 void TClasserFrm::Demarrer(void)
 {
 TGridRect selection;
 int row;
 LaGrille=Forme00Frm->Grille0;
 row=LaGrille->Row;
 if(row==0) Close();
 if(!LaGrille->Options.Contains(goRowSelect))
 {
 LaGrille->Options >> goEditing;
 LaGrille->Options << goRowSelect;
 if( LaGrille->Row >0 && LaGrille->Col >0)
 MarquerLigne(row);
 }
 else
 {
 LaGrille->Options << goEditing;
 LaGrille->Options >> goRowSelect;
 MarquerLigne(row);
 }

 Show();
 }
 //---------------------------------------------------------------------------
 void __fastcall TClasserFrm::BtHautClick(TObject *Sender)
 {
 int row;
 int c,cX;
 AnsiString s;
 TObject    *object;
 Forme00Frm->LabelModifie->Visible=true;
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
 MarquerLigne(row-1);
 }
 //---------------------------------------------------------------------------
 void __fastcall TClasserFrm::BtBasClick(TObject *Sender)
 {
 int row;
 int c,cX;
 AnsiString s;
 TObject    *object;
 TGridRect selection;
 Forme00Frm->LabelModifie->Visible=true;
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
 MarquerLigne(row+1);
 }
 //---------------------------------------------------------------------------
 void __fastcall TClasserFrm::MarquerLigne(int row)
 {
 TGridRect selection;
 int cX=LaGrille->ColCount;
 selection.Left=1;
 selection.Right=cX-1;
 selection.Top=row;
 selection.Bottom=row;
 LaGrille->Selection=selection;
 }
 */

