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
#include "AleaRdt.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void __fastcall TAleaRdtFrm::DesGrilles(void)
{
	int i,row;
	CL_Delta* delta;
	int c,col; //,g;
	float base,rdt;
	CL_Vecteur<CL_Delta> *vecteur;
	if(LabelModifie->Visible==false)
	return;
	LabelModifie->Visible=false;

	if(Tendance==NULL) return;//230502

	vecteur=Tendance->V_Delta;
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

	// le stockage se fait sur LabelModifie
	//évite des erreurs d'arrondi sur pcent
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
		base=GrilleFloat(4,row); //?
		for(c=0,col=5;c<delta->NMax;c++,col++)//240907
		{
			switch(GrilleALire)
			{
				case 0: //saisie en pcent
				delta->Pcent[c]=GrilleFloat(col,row);
				break;
				case 1://saisie en valeur
				rdt =GrilleFloat(col,row);
				delta->Pcent[c]=(rdt*100)/base;
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
