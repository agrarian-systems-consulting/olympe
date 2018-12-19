//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "Tendance.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
//SAISIE
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::CellDebut(void)
{
	int g=LaGrille->Tag;

	CellAVerifier=false;

	CellModifiable(false);
	LaGrille->Col=2;
	LaGrille->Row=1; //1;
	Grille0Click(this);
	ColM[g]=LaGrille->Col;
	RowM[g]=LaGrille->Row;

	CellAVerifier=true;
	ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::SaisirCell(int col,int row)
{
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		SaisirCellTend(col,row);break;

		default:ShowMessage("SaisirCell Oubli");
	}
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::SaisirCellTend(int col,int row)
{
	if (col<5)
	CellModifiable(false);
	else
	CellModifiable(true);

}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::BtReportDroitClick(TObject *Sender)
{
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		RepDroit(); break;
		default:ShowMessage("RepDroit Oubli");break;
	}
}
//reporte à droite une cellule
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::RepDroit(void)
{
	int c,c0,colQ=5;
	int r0;
	AnsiString as;
	if(LaGrille->Col <colQ )return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	ReAffFloat(c0,r0,Digits);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(CellVide(c,r0)==false) continue;

		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::BtReportBasClick(TObject *Sender)
{
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	int r,rMax;
	AnsiString s=LaGrille->Cells[col][row];
	if(s.IsEmpty()) return;
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:

		RepBas(col,row);break;
		default:ShowMessage("ReportBas Oubli");break;
	}
}
//recopie colonne
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::RepBas(int col,int row)
{
	int r,rMax;
	AnsiString s=LaGrille->Cells[col][row];
	AnsiString as;
	if(col<5) return;
	rMax=LaGrille->RowCount-2;
	for(r=row+1;r<rMax;r++)
	{
		if(CellVide(col,r)==false) continue;

		LaGrille->Cells[col][r]=s;
		LabelModifie->Visible=true;
	}
}
//Recopie ligne entière
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::BtRecopBasClick(TObject *Sender)
{
	int row=LaGrille->Row;
	int r,c,rMax;
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:

		RecopBas(row);break;
		default:ShowMessage("RecopBas Oubli");break;
	}
}
//Recopie ligne entière
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::RecopBas(int row)
{
	int r,rMax;
	CL_Delta *delta1,*delta2;
	AnsiString as;
//int l;
	rMax=LaGrille->RowCount-2;

	for(int c=5;c<LaGrille->ColCount;c++)
	{
		if(LaGrille->Cells[c][row].IsEmpty() )continue;
		for(r=row+1;r<rMax;r++)
		{
			if(CellVide(c,r)==false) continue;
			LaGrille->Cells[c][r]=LaGrille->Cells[c][row];
			LabelModifie->Visible=true;
		}
	}
}

