//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Brouillon.h"
#include "Atelier.h"
#include "ResAtelier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TResAtelierFrm *ResAtelierFrm;
//---------------------------------------------------------------------------
__fastcall TResAtelierFrm::TResAtelierFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TResAtelierFrm::FormActivate(TObject *Sender)
{
	int c,n,r,cTot;
	int largeur;
	CL_Atelier *atelier=AtelierFrm->Atelier;

	if (atelier==NULL) return; // Pourquoi il est NULL ?? Bonne question... (seb)
	LaGrille=Grille0;
	LesGrilles[0]=Grille0;
	Grille0->Cells[0][1]="Produits";
	Grille0->Cells[0][2]="Charges";
	Grille0->Cells[0][3]="Charges Volume";
	Grille0->Cells[0][4]="Marge";

	Grille0->ColCount=AtelierFrm->Atelier->NbPhase+2;
	Grille0->RowCount=5;

	Grille0->Width=128;
	Grille0->ColWidths[0]=128;
	largeur=Grille0->ColWidths[0];
	for(c=1;c<Grille0->ColCount;c++)
	{
		Grille0->ColWidths[c]=64;
		largeur+=Grille0->ColWidths[c];
	}
	if(largeur<ResAtelierFrm->Width+Grille0->Left)
	Grille0->Width=largeur;
	else
	Grille0->Width=ResAtelierFrm->Width-Grille0->Left-20;
//    ResAtelierFrm->Width=Grille0->Width+30;
	AtelierFrm->MetAnnee(Grille0,1);
	cTot=AtelierFrm->Atelier->NbPhase+1;
	Grille0->Cells[cTot][0]="Total";

	r=1;
	Grille0->Cells[0][r]="Produits";
	for(n=0;n<atelier->NbPhase+1;n++)
	Grille0->Cells[n+1][r]=Aff(AtelierFrm->Produit[n],0);
	r=2;
	Grille0->Cells[0][r]="Charges";
	for(n=0;n<atelier->NbPhase+1;n++)
	Grille0->Cells[n+1][r]=Aff(AtelierFrm->Charge[n],0);

	r=3;
	Grille0->Cells[0][r]="Charges Volume";
	for(n=0;n<atelier->NbPhase+1;n++)
	Grille0->Cells[n+1][r]=Aff(AtelierFrm->ChargeVol[n],0);

	r=4;
	Grille0->Cells[0][r]="Marge";
	for(n=0;n<atelier->NbPhase+1;n++)
	Grille0->Cells[n+1][r]=Aff(AtelierFrm->Marge[n],0);
}

//---------------------------------------------------------------------------
void __fastcall TResAtelierFrm::BtBnStockerClick(TObject *Sender)
{
	//BtStockerClick->Visible=false
	ShowMessage("Stocker a faire");
}
//---------------------------------------------------------------------------
void __fastcall TResAtelierFrm::BtBnImpClick(TObject *Sender)
{
	ShowMessage("A faire");
}
//---------------------------------------------------------------------------

