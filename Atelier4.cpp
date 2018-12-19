//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#pragma hdrstop

#include "Atelier.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::Calcul(void)
{
	int row;
	int n,nTot;
	int c,colQ;
	float coutUnit;
	float qtePhase[20]; //[N_PHASE];
	float val;
	CL_ItemParAtelier *itemPA,*produitA;
	CL_Item *item,*chargeV;;
	float qteProduite[20];//[N_PHASE];
	int g=LaGrille->Tag;
//float Produit[20],Charge[20],ChargeVol[20],Marge[20];

	memset(Produit, 0,sizeof(float)*20);
	memset(Charge, 0,sizeof(float)*20);
	memset(ChargeVol, 0,sizeof(float)*20);
	memset(Marge, 0,sizeof(float)*20);

//Produits
	LaGrille=LesGrilles[0];
	colQ=5;
	for( row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];
		for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
		{
			if(LaGrille->Cells[c][row].IsEmpty() )
			qtePhase[n]=0;
			else
			qtePhase[n]=GrilleFloat(c,row);
		}
		item=itemPA->Item;
		coutUnit=item->Prix/item->SysUnite->Ratio;
		for(n=0;n<Atelier->NbPhase;n++)
		{
			val=qtePhase[n]*coutUnit;
			Produit[n]+=val;
		}
	}
	//Charges
	colQ=5;
	LaGrille=LesGrilles[1];
	for( row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];
		for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
		{
			if(LaGrille->Cells[c][row].IsEmpty() )
			qtePhase[n]=0;
			else
			qtePhase[n]=GrilleFloat(c,row);
		}
		item=itemPA->Item;
		coutUnit=item->Prix/item->SysUnite->Ratio;
		for(n=0;n<Atelier->NbPhase;n++)
		{
			val=qtePhase[n]*coutUnit;
			Charge[n]+=val;
		}
	}
	// Charges prop au volume
	colQ=6;
	LaGrille=LesGrilles[2];
	for( row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];
		produitA =itemPA->ItemPA;
		chargeV =itemPA->Charge;
		for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
		{
			if(LaGrille->Cells[c][row].IsEmpty() )
			qtePhase[n]=0;
			else
			qtePhase[n]=GrilleFloat(c,row);
		}
		trouveProduit(produitA,qteProduite);
		coutUnit=chargeV->Prix/chargeV->SysUnite->Ratio;

		for(n=0;n<Atelier->NbPhase;n++)
		{
			val=qtePhase[n]*coutUnit*qteProduite[n];
//            val=coutUnit*qteProduite[n];
			ChargeVol[n]+=val;
		}
	}

	for(n=0;n<Atelier->NbPhase;n++)
	Marge[n]=Produit[n]-Charge[n]-ChargeVol[n];

	//Total
	nTot=Atelier->NbPhase;
	for(n=0;n<Atelier->NbPhase;n++)
	{
		Produit[nTot]+= Produit[n];
		Charge[nTot]+= Charge[n];
		ChargeVol[nTot]+= ChargeVol[n];
		Marge[nTot]+= Marge[n];
	}

	LaGrille=LesGrilles[g];
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::trouveProduit(CL_ItemParAtelier* produitA,float* qteProduite)
{
	int row;
	int n;
	int c,colQ=5;
	CL_ItemParAtelier *itemPA;
	memset(qteProduite,0,sizeof(float)*N_PHASE);
	LaGrille=LesGrilles[0];
	for( row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];
		if(itemPA!=produitA) continue;

		for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
		{
			if(LaGrille->Cells[c][row].IsEmpty() )
			qteProduite[n]=0;
			else
			qteProduite[n]=GrilleFloat(c,row);
		}
	}
	LaGrille=LesGrilles[2];
}

