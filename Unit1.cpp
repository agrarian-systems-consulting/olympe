//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
for(c=Col0;c<GrilleMvt->ColCount;c++)
{
	//mvt mouvement d'une catégorie à une autre et naissance
	// vieillissement:mouvement d'une catégorie à une autre
	for(r=1;r<GrilleMvt->RowCount;r++)// -1 a supprimer
	{
		if(GrilleMvt->Objects[0][r]==NULL) continue;

		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
		noOr=mvt->Animal->NoOrigine;
		if(noOr==-1) continue; // veaux

		mvtOr=(CL_MvtAnnee*)GrilleMvt->Objects[c][noOr];
		iE=trouveColOrigine(noOr,mvtOr);
		iD=trouveColDestin(noOr,mvt);

		mvt->Entree[iD]=mvtOr->Dispo(0);// Dispo(n ) n non utilisé
		mvtOr->Sortie[iE]=mvt->Entree[iE];
	}
	// décision utilisateur
	for(i=0;i<3;i++)
	{
	}

	int trouveColOrigine(int no,CL_MvtAnnee *mvtOr)
	{
		int i;

		if(mvtOr->iOr==0)
		{
			mvtOr->Origine[0]==no;
			mvtOr->iOr=1;
			return 0;
		}
		for(i=0;i<mvtOr->iOr;i++)
		{
			if(mvtOr->Origine[i]==no)
			return i;
		}
		i=mvtOr->iOr;
		mvtOr->Origine[i]==no;
		mvtOr->iOr++;
		return i;
	}

	int trouveColDest(int no,CL_MvtAnnee *mvtDest)
	{
		int i;

		if(mvtDest->iDest==0)
		{
			mvtDest->Destin[0]==no;
			mvtDest->iDest=1;
			return 0;
		}
		for(i=0;i<mvtDest->iDest;i++)
		{
			if(mvtDest->Destin[i]==no)
			return i;
		}
		i=mvtDest->iDest;
		mvtDest->Destin[i]==no;
		mvtDest->iDest++;
		return i;
	}
