//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "LesVecteurs.hse"

#include "Erreur.h"

#include "TendanceEnum.h"
#include "Tendance.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//bool __fastcall TAgriSaisieFrm::ControleCell(int col,int row)
//-----------------------------------------------------------------------------
//VerifGrille
//-----------------------------------------------------------------------------
bool __fastcall TTendanceFrm::VerifGrille(void)
{
	bool correct;
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		correct=VerifGrilleNom( );break;

		default: ShowMessage("VerifGrille Oubli");
	}
	return correct;
}
//-----------------------------------------------------------------------------
// existence de nom
//-----------------------------------------------------------------------------
bool __fastcall TTendanceFrm::VerifGrilleNom(void)
{
	int row;
	bool correct=true;
	char buf[100];

	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(LaGrille->Cells[2][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	return correct;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void __fastcall TTendanceFrm::DesGrilles(void)
{
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		DeGrilleTendance(Tendance->V_Delta);break;
		default: ShowMessage("AgriSaisie DesGrilles Oubli");
	}
}
//---------------------------------------------------------------------------
// DeGrille  Tendance
//------------------------------------------------------------------------------
void __fastcall TTendanceFrm::DeGrilleTendance(CL_Vecteur<CL_Delta> *vecteur)
{
	int row;
	CL_Delta* delta;
	int c,col,g;
	float base,prix;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		delta=(CL_Delta*)LaGrille->Objects[0][row];
		if (delta==NULL) ///???????????
		return;
		switch(delta->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(delta);
			break;
			case 'O'://origine
			case 'M'://modifié
			break;
		}
		base=delta->Item->Prix;
		for(c=0,col=5;c<10;c++,col++)
		{
			switch(RGPcentVal->ItemIndex)
			{
				case 0: //saisie en pcent
				delta->Pcent[c]=GrilleFloat(col,row);
				break;
				case 1://saisie en valeur
				prix =GrilleFloat(col,row);
				delta->Pcent[c]=(prix*100)/base;
				break;
			}
		}
		delta->Flag='O';
	}
	if(vecteur->Nbelt==0) return;
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		delta=vecteur->Vecteur[i];
		if(delta->Flag=='S') {vecteur->sup(delta);i--;}
	}
	return;
}
