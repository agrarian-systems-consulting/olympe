//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "AleaPrix.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
/*
 //---------------------------------------------------------------------------
 //SAISIE
 //---------------------------------------------------------------------------
 void  __fastcall TAleaPrixFrm::CellDebut(void)
 {
 int g=LaGrille->Tag;

 CellAVerifier=false;

 CellModifiable(false);
 LaGrille->Col=2;
 LaGrille->Row=1;//1;
 Grille0Click(this);
 ColM[g]=LaGrille->Col;
 RowM[g]=LaGrille->Row;

 CellAVerifier=true;
 ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
 }
 */
/*
 //---------------------------------------------------------------------------
 void __fastcall TAleaPrixFrm::SaisirCell(int col,int row)
 {
 if (col<5)
 CellModifiable(false);
 else
 CellModifiable(true);
 }
 */
//reporte à droite une cellule
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtReportDroitClick(TObject *Sender)
{
	int c,c0,colQ=5;
	int r0;
	AnsiString as;
	int g;
	if(LaGrille->Col <colQ )return;
	g=LaGrille->Tag;
	GrilleModif[g]=true;
	LabelModifie->Visible=true;

	c0=LaGrille->Col;
	r0=LaGrille->Row;
	ReAffFloat(c0,r0,DigitsPrix);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(ChBRepTout->Checked==false)
		{
			if(CellVide(c,r0)==false) continue;
		}
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
}
//recopie colonne
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtReportBasClick(TObject *Sender)
{
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	int r,rMax;
	AnsiString as;
	AnsiString s=LaGrille->Cells[col][row];
	if(s.IsEmpty()) return;
	if(col<5) return;
	rMax=LaGrille->RowCount-2;
	for(r=row+1;r<rMax;r++)
	{
		if(ChBRepTout->Checked==false)
		{
			if(CellVide(col,r)==false) continue;
		}
		LaGrille->Cells[col][r]=s;
		LabelModifie->Visible=true;
	}
}
//Recopie ligne entière
//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::BtRecopBasClick(TObject *Sender)
{
	int row=LaGrille->Row;
	int r,rMax;
	AnsiString as;
//int l;
	rMax=LaGrille->RowCount-2;

	for(int c=5;c<LaGrille->ColCount;c++)
	{
		if(LaGrille->Cells[c][row].IsEmpty() )continue;
		for(r=row+1;r<rMax;r++)
		{
			if(ChBRepTout->Checked==false)
			{
				if(CellVide(c,r)==false) continue;
			}
			LaGrille->Cells[c][r]=LaGrille->Cells[c][row];
			LabelModifie->Visible=true;
		}
	}
}

