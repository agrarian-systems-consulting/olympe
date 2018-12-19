//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Brouillon.h"
#include "Atelier.h"
#include "AtelierMDetail.h"
#include "CL_Trad.h"

#include "AtelierMDetailPerenne.h"
#include "AtelierMarge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAtelierMargeFrm *AtelierMargeFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TAtelierMargeFrm::TAtelierMargeFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMargeFrm::FormActivate(TObject *Sender)
{
	int c,n,r,c0;
	int largeur;
	CL_Atelier *atelier=AtelierFrm->Atelier;
	float totProd,totCharge,totChargeVol,totMarge;
	float margeHeure[N_PHASE]; //040408
	float somme,margeCumul[N_PHASE];
	if (atelier==NULL) return;// Pourquoi il est NULL ?? Bonne question... (seb)

	Caption=T->L_Marge+"  "+atelier->Nom;
	//Caption="Marge   "+atelier->Nom;
	LaGrille=Grille0;
	LesGrilles[0]=Grille0;
	TitreGrille=atelier->Nom;
	strcpy(TypeCol,"TNNNNNNNNNNNNNNNNNNN");

	totProd =0;
	totCharge =0;
	totChargeVol =0;
	totMarge =0;

	for(n=0;n<atelier->NbPhase;n++)
	{
		AtelierFrm->Marge[n]= AtelierFrm->Produit[n]
		- AtelierFrm->Charge[n]
		- AtelierFrm->ChargeVol[n];
	}

	switch(atelier->Nature)
	{
		case PERENNE:
		totProd =AtelierFrm->MoyProd;
		totCharge =AtelierFrm->MoyCharge;
		totChargeVol =AtelierFrm->MoyChVol;
		totMarge =totProd-totCharge-totChargeVol;
		Grille0->Cells[1][0]=L_Moy; //"Moyenne";
		Grille0->RowCount=7;
		c0=2;
		break;
		default:
		for(n=0;n<atelier->NbPhase;n++)
		{
			totProd +=AtelierFrm->Produit[n];
			totCharge +=AtelierFrm->Charge[n];
			totChargeVol +=AtelierFrm->ChargeVol[n];
			totMarge +=AtelierFrm->Marge[n];

		}
		c0=2;
		Grille0->Cells[1][0]=T->L_Total; //"Total";
		Grille0->RowCount=6;
	}

	Grille0->Cells[0][1]=T->L_Produit; //"Produits";
	Grille0->Cells[0][2]=T->L_Charge;//"Charges";
	Grille0->Cells[0][3]=L_ChVol;//"Charges Volume";
	Grille0->Cells[0][4]=T->L_Marge;//"Marge";

	Grille0->ColCount=AtelierFrm->Atelier->NbPhase+2;

	Grille0->Width=128;
	Grille0->ColWidths[0]=128;
	largeur=Grille0->ColWidths[0];
	for(c=1;c<Grille0->ColCount;c++)
	{
		Grille0->ColWidths[c]=64;
		largeur+=Grille0->ColWidths[c];
	}
	//test
	Grille0->Width=largeur;
	AtelierFrm->MetAnnee(Grille0,c0);

	r=1;
	Grille0->Cells[0][r]=T->L_Produit;//"Produits";
	Grille0->Cells[1][r]=Aff(totProd,0);
	for(n=0,c=c0;n<atelier->NbPhase;n++,c++)
	Grille0->Cells[c][r]=Aff(AtelierFrm->Produit[n],0);
	r=2;
	Grille0->Cells[0][r]=T->L_Charge;//"Charges";
	Grille0->Cells[1][r]=Aff(totCharge,0);
	for(n=0,c=c0;n<atelier->NbPhase;n++,c++)
	Grille0->Cells[c][r]=Aff(AtelierFrm->Charge[n],0);

	r=3;
	Grille0->Cells[0][r]=L_ChVol;//"Charges Volume";
	Grille0->Cells[1][r]=Aff(totChargeVol,0);
	for(n=0,c=c0;n<atelier->NbPhase;n++,c++)
	Grille0->Cells[c][r]=Aff(AtelierFrm->ChargeVol[n],0);

	r=4;
	Grille0->Cells[0][r]=T->L_Marge;//"Marge";
	Grille0->Cells[1][r]=Aff(totMarge,0);
	for(n=0,c=c0;n<atelier->NbPhase;n++,c++)
	Grille0->Cells[c][r]=Aff(AtelierFrm->Marge[n],0);

	if(atelier->Nature== PERENNE)
	{
		somme=0;
		for(n=0;n<atelier->NbPhase;n++)
		{
			somme+=AtelierFrm->Marge[n]*AtelierMDetailPerenneFrm->DureePhase[n];
			margeCumul[n]=somme;
			margeHeure[n]=0;
			if(AtelierMDetailPerenneFrm->TotHeureAn[n]>0)
			margeHeure[n]=AtelierFrm->Marge[n]/AtelierMDetailPerenneFrm->TotHeureAn[n];
		}
		r=5;
		Grille0->Cells[0][r]=L_MargeCum; //"Marge Cumulée";
		for(n=0,c=c0;n<atelier->NbPhase;n++,c++)
		Grille0->Cells[c][r]=Aff(margeCumul[n],0);
	}

	if(atelier->Nature!= PERENNE)
	{
		r=5;
		if(AtelierMDetailFrm->TotHeure==0)
		{
			Grille0->Cells[0][r]=" ";
			Grille0->Cells[1][r]="  ";
		}
		else
		{
			Grille0->Cells[0][r]=T->L_MargeHeure; //"Marge/heure";
			Grille0->Cells[1][r]=Aff(totMarge/AtelierMDetailFrm->TotHeure,2);
		}
	}

	else //PERENNE
	{
		r=6;
		if(AtelierMDetailPerenneFrm->TotHeure==0)
		{
			Grille0->Cells[0][r]=" ";
			Grille0->Cells[1][r]="  ";
		}
		else
		{
			Grille0->Cells[0][r]=T->L_MargeHeure; //"Marge/heure";
			for(n=0,c=c0;n<atelier->NbPhase;n++,c++)
			Grille0->Cells[c][r]=Aff(margeHeure[n],2);
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TAtelierMargeFrm::BtBnStockerClick(TObject *Sender)
{
	//BtStockerClick->Visible=false
	ShowMessage("Stocker a faire");
}

//---------------------------------------------------------------------------
void __fastcall TAtelierMargeFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	CanClose=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TAtelierMargeFrm::TexteChaine(void) {
	L_Moy = T->TrouveTexte("AtelierMargeFrm", "L_Moy");
	L_ChVol = T->TrouveTexte("AtelierMargeFrm", "L_ChVol");
	L_MargeCum = T->TrouveTexte("AtelierMargeFrm", "L_MargeCum");
}
//---------------------------------------------------------------------------
void TAtelierMargeFrm::TexteCaption(void) {
	AtelierMargeFrm->Caption = T->LC_BtBnMarge;
}
//---------------------------------------------------------------------------
void TAtelierMargeFrm::IniCaption(void) {
	LC_BtBnMarge = T->TrouveCaption("CL_Trad", "LC_BtBnMarge");
}

