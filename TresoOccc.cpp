//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TresoOccc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TTresoOcccFrm *TresoOcccFrm;
//---------------------------------------------------------------------------
__fastcall TTresoOcccFrm::TTresoOcccFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoOcccFrm::FormActivate(TObject *Sender)
{
	LaGrille=Grille0;
	LaGrille->ColCount=11;
	LaGrille->RowCount=9;

	strcpy(TypeCol,"0NNNNNNNNNNNNN");

	LaGrille->ColWidths[0]=128;

	LaGrille->Cells[0][1]="Occc 1";
	LaGrille->Cells[0][2]="   Taux";
	LaGrille->Cells[0][3]="   Maxi";

	LaGrille->Cells[0][4]="Occc 2";
	LaGrille->Cells[0][5]="   Taux";
	LaGrille->Cells[0][6]="   Maxi";

	LaGrille->Cells[0][7]="Placement";
	LaGrille->Cells[0][8]="   Taux";
	LaGrille->Cells[0][9]="   Maxi";

	VersGrille(LaGrille);
}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TTresoOcccFrm::VersGrille(TStringGrid *grille)
{

	int n,c;
	int an;
	an=AgriEnCours->DefSim->An_0;
	for(n=0,c=1;n<N_X;n++,c++)
	LaGrille->Cells[c][0]=Aff(an);
	/*
	 grille->RowCount=vecteur->Nbelt+3;
	 for( r=0;r<vecteur->Nbelt;r++)
	 {
	 row=r+1;
	 tva=vecteur->Vecteur[r];
	 tva->Flag='O';
	 grille->Objects[0][row]=(TObject*)tva;
	 grille->Cells[0][row]=row;
	 if(tva->Supprimable==false) grille->Cells[1][row]='*';
	 grille->Cells[2][row]=tva->Nom;
	 if(tva->Taux==0)  grille->Cells[3][row]="     0";
	 else              grille->Cells[3][row]=Aff(tva->Taux,2);
	 }
	 IniCB();
	 CellInitiale(2,1);
	 */
}
//----------------------------------------------------------------------------

