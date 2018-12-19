//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Erreur.h"

#include "TendanceEnum.h"
#include "AleaPrix.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//bool __fastcall TAgriSaisieFrm::ControleCell(int col,int row)
/* appel direct de VerifGrilleNom
 //-----------------------------------------------------------------------------
 //VerifGrille
 //-----------------------------------------------------------------------------
 bool __fastcall TAleaPrixFrm::VerifGrille(void)
 {
 bool correct;
 switch(LaGrille->Tag)
 {
 case GTProd:
 case GTCharge:
 case GSProd:
 case GSCharge:
 case GSExter:
 case GTExter:

 correct=VerifGrilleNom( );break;

 default: ShowMessage("VerifGrille Oubli");
 }
 return correct;
 }
 */

/*
 //-----------------------------------------------------------------------------
 // existence de nom
 //    il y en a toujours un par construction
 //-----------------------------------------------------------------------------
 bool __fastcall TAleaPrixFrm::VerifGrilleNom(void)
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
 */
//----------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::DesGrilles(void)
{
	int i,row;
	CL_Delta* delta;
	int c,col;
	float base,prix;
	CL_Vecteur<CL_Delta> *vecteur=Tendance->V_Delta;
	if(Tendance==NULL) return; //230502

	if(LabelModifie->Visible==false) return;

	if(OrdreModif==true)
	{
		for(row=1;row<LaGrille->RowCount;row++)
		{
			if(RowVide(row)==true) continue;
			delta=(CL_Delta*)LaGrille->Objects[0][row];
			if(delta->Flag=='N')
			{
				delta->Flag='M';
				vecteur->ins(delta);
			}
		}
		i=0;
		for(row=1;row<LaGrille->RowCount;row++)
		{
			if(RowVide(row)==true) continue;
			delta=(CL_Delta*)LaGrille->Objects[0][row];
			vecteur->Vecteur[i]=delta;
			i++;
		}
	}
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		delta=(CL_Delta*)LaGrille->Objects[0][row];
		if (delta==NULL) continue;

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
		for(c=0,col=5;c<delta->NMax;c++,col++)
		{
			switch(GrilleALire)
			{
				case 0: //saisie en pcent
				delta->Pcent[c]=GrilleFloat(col,row);
				break;
				case 1://saisie en valeur
				prix =GrilleFloat(col,row);
				if(base==0) delta->Pcent[c]=100;
				else delta->Pcent[c]=(prix*100)/base;
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
