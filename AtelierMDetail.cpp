//---------------------------------------------------------------------------

#include <vcl.h>
#include<stdio.h>
#pragma hdrstop
#include "Atelier.h"
#include "AtelierMarge.h"
#include "CL_Matrice.h"
#include <iostream.h>
using namespace std;

#include "QRGrille00.h"
#include "AtelierMDetailPerenne.h"
#include "CL_Trad.h"

#include "Outil.h"

#include "AtelierMDetail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAtelierMDetailFrm *AtelierMDetailFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TAtelierMDetailFrm::TAtelierMDetailFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::Personnaliser(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::DefinirLesGrilles(void)
{
	AjoutRow=true;
	Grille0->Visible=false;
	GrilleX=1;

	LesGrilles[0]=Grille0;

	LaGrille=Grille0;
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int a0;
	int p,c,col0;
	AnsiString as;
//                              1     2      3     Total
	int largeur[] = {64,64,32,64, 64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64};
	//081001   pourquoi va t il ici de temps en temps à l'initialisation
	if(Atelier==NULL) return;
	TitreGrille=Atelier->Nom;
	strcpy(TypeCol,"TTTNNNNNNNNNNNN");
	grille->ColCount=6+Atelier->NbPhase*2;

	grille->FixedRows=1;
	grille->FixedCols=0;//4; //5;
	for(int c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	l=l+grille->Left+25; //25

	grille->Rows[0]->CommaText=L_TitreGrille;//"NOM,CATEGORIE,Unité,Prix,Quantite,Valeur";
	grille->Cells[3][0]=AnsiString("Prix  ")+SysMonnaie->UTrans;
	a0=0;
	col0=6;
	for(p=0,c=col0;p<Atelier->NbPhase;p++,c+=2)
	{
		if(p==0)as=AnsiString(L_AvtQuant); //"Avant Quant");
		else as=AnsiString(a0)+L_Quant;//"  Quant";
		grille->Cells[c][0]=as;
		grille->Cells[c+1][0]=L_Valeur;//"Valeur";
		a0++;
	}

}
//***************************************************************************
//  VERSGRILLE
//------------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::VersGrille(TStringGrid *grille)
{
	int row;
	int n;
	float marge[N_PHASE];
	CL_BesTrav *besTrav;
	float margeTot;
	TList *lstItemProd, *lstItemCha; //300407
	TList *lstQuantProd,*lstQuantCha;
	if(Atelier==NULL) return;
	if(Atelier->Flag==SUPPRIME )return;
	VideLesGrilles();

	LabSais->Caption=Atelier->Nom;
	Caption=L_MargeDet + Atelier->Nom;
	//    Caption="Marge Détaillée  " + Atelier->Nom;170206
	LaGrille=grille;
	LaGrille->RowCount=2;
	LaGrille->ColCount=grille->ColCount;// pourquoi
	row=0;
	Titre=L_Titre.c_str();//"Titre";
	Total=T->L_Total.c_str();//"Total";
	Marge=T->L_Marge.c_str();//"Marge";
	/// mise à zero
	for(n=0;n<Atelier->NbPhase;n++)//210901
	{
		AtelierFrm->Produit[n] =0;
		AtelierFrm->Charge[n] =0;
		AtelierFrm->ChargeVol[n]=0;
	}
	// calculer quantité/ha  //300407
	//   quantite/ha et quantite/pied *pied/ha
	lstItemProd=new TList;
	lstQuantProd=new TList;
	//production
	TotaliserProdCha(Atelier->NbPhase,Atelier->V_Produit,Atelier->PiedHa,Atelier->V_ProdPied,
			lstItemProd,lstQuantProd);

	//Charges
	lstItemCha=new TList;
	lstQuantCha=new TList;
	TotaliserProdCha(Atelier->NbPhase,Atelier->V_Charge,Atelier->PiedHa,Atelier->V_ChPied,
			lstItemCha,lstQuantCha);

	/// fait calcul et affiche à ligne row cf &row
	if(lstItemProd->Count>0)
	VersGrilleItem(row,PRODUIT,lstItemProd,lstQuantProd);//Atelier->V_Produit);
	if(lstItemCha->Count>0)
	VersGrilleItem(row,CHARGE, lstItemCha,lstQuantCha);//Atelier->V_Charge );
//!!    VersGrilleVolume(row,Atelier->V_ChargeVolume );

	/// calcul marge
	for(n=0;n<Atelier->NbPhase;n++)
	{
		marge[n]= AtelierFrm->Produit[n]
		- AtelierFrm->Charge[n]
		- AtelierFrm->ChargeVol[n];
	}
	LaGrille->Objects[1][row+1]=(TObject*)Marge;
	AffTotal(row,Atelier->NbPhase,marge,L_MargeUnit.c_str()); //"Marge unitaire");

	// productivité travail
	for(n=0;n<Atelier->V_BesTrav->Nbelt;n++)
	{
		TotHeure=0;
		memset(TotHeureAn,0,sizeof(TotHeureAn));
		besTrav=Atelier->V_BesTrav->Vecteur[n];
		besTrav->Totalise(TotHeure,TotHeureAn);
		if(TotHeure>0)
		{
			margeTot=0;
			for(int p=0;p<Atelier->NbPhase;p++)margeTot+=marge[p];
			AffTrav(row,Atelier,besTrav,marge,margeTot);
		}
	}
	/*
	 // productivité travail
	 TotHeure=0;
	 if(Atelier->V_BesTrav->Nbelt!=0)
	 {
	 memset(TotHeureAn,0,sizeof(TotHeureAn));
	 n=Atelier->V_BesTrav->Nbelt;         //!!!!!!!!!!!
	 besTrav=Atelier->V_BesTrav->Vecteur[0];//->trouve(0);
	 besTrav->Totalise(TotHeure,TotHeureAn);
	 if(TotHeure>0)
	 {
	 margeTot=0;
	 for(int p=0;p<Atelier->NbPhase;p++)margeTot+=marge[p];
	 AffTrav(row,Atelier,marge,margeTot);
	 }
	 }

	 */
	Grille0->Visible=true;
	Libere(lstItemProd,lstQuantProd,lstItemCha,lstQuantCha);

}
//---------------------------------------------------------------------------
void TAtelierMDetailFrm::TotaliserProdCha(int nbPhase,
		CL_Vecteur<CL_ItemParAtelier>*vItemPA, float* piedHa,
		CL_Vecteur<CL_ItemParAtelier>*vQParPied, TList *lstItem,
		TList *lstQuantite) {
	int i, j, n;
	float *quantite;
	CL_ItemParAtelier *itemPA;
	CL_Item *item, *itemA;
	bool existe;
	//quantités introduites
	for (i = 0; i < vItemPA->Nbelt; i++) {
		itemPA = vItemPA->Vecteur[i];
		item = itemPA->Item;
		existe = false;
		for (j = 0; j < lstItem->Count; j++) {
			itemA = (CL_Item*) lstItem->Items[j];
			if (item == itemA) {
				quantite = (float*) lstQuantite->Items[j];
				existe = true;
				break;
			}
		}
		if (existe == false) {
			lstItem->Add(item);
			quantite = new float[nbPhase];
			memset(quantite, 0, sizeof(float) * nbPhase);
			lstQuantite->Add(quantite);
		}
		for (n = 0; n < nbPhase; n++)
			quantite[n] = +itemPA->QtePhase[n];
	}
	//quantitésPied* PiedHa
	for (i = 0; i < vQParPied->Nbelt; i++) {
		itemPA = vQParPied->Vecteur[i];
		item = itemPA->Item;
		existe = false;
		for (j = 0; j < lstItem->Count; j++) {
			itemA = (CL_Item*) lstItem->Items[j];
			if (item == itemA) {
				quantite = (float*) lstQuantite->Items[j];
				existe = true;
				break;
			}
		}
		if (existe == false) {
			lstItem->Add(item);
			quantite = new float[nbPhase];
			memset(quantite, 0, sizeof(float) * nbPhase);
			lstQuantite->Add(quantite);
		}
		for (n = 0; n < nbPhase; n++)
			quantite[n] = itemPA->QtePhase[n] * piedHa[n];
	}
}

//---------------------------------------------------------------------------
// Remplir les Grilles   produit charge irrigation
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::VersGrilleItem (int &row,int nature,
		TList *lstItem,TList *lstQuant)
//        CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int n;
	int p,col;
	int eltDansCat;
	AnsiString value;
	CL_Categorie *categorie,*cat0;
	CL_SystemeUnite *sysUnite;
	CL_Item *item;
	float q,qTot,prix;
	float *quantite;
	float total[N_PHASE], ssTotal[N_PHASE]; //mettre a N_PHASE cf Atelier.h
	char coutUnit[N_PHASE];
	AnsiString as;
//ShowMessage("VersGrilleItem");

	memset(total, 0,sizeof(total));
	memset(ssTotal,0,sizeof(total));
	row++;
	LaGrille->RowCount++;
	switch(nature)
	{
		case PRODUIT:LaGrille->Cells[0][row]=T->L_Produit;break;
		case CHARGE: LaGrille->Cells[0][row]=T->L_Charge;break;
	}
	LaGrille->Objects[1][row]=(TObject*)Titre;

	item=(CL_Item*)lstItem->Items[0];
	cat0 =item->Categorie;
	eltDansCat=0;

	for( n=0;n<lstItem->Count;n++)
	{
		item=(CL_Item*)lstItem->Items[n];
		quantite=(float*)lstQuant->Items[n];
		categorie=item->Categorie;
		sysUnite =item->SysUnite;
		if(categorie!=cat0)
		{
			if(eltDansCat >1)
			AffTotal(row,Atelier->NbPhase,ssTotal,L_SousTot.c_str()); //"sous total");
//            else
//            {
//                row++;
//                LaGrille->RowCount++;
//            }
			eltDansCat=0;
			memset(ssTotal,0,sizeof(total));
			cat0=categorie;
		}
		row++;
		LaGrille->RowCount++;
		eltDansCat++;
		LaGrille->Objects[1][row]=NULL;
		LaGrille->Cells[0][row]=item->Nom;
		LaGrille->Cells[1][row]=categorie->Nom;
		LaGrille->Cells[2][row]=sysUnite->UUt;
		if(sysUnite->Ratio==1)
		{
			sprintf(coutUnit,"%6.2f",item->Prix);
			prix=item->Prix;
		}
		else
		{
			sprintf(coutUnit,"%6.2f /%s",item->Prix,sysUnite->UTrans);
			prix=item->Prix/sysUnite->Ratio;
		}
		LaGrille->Cells[3][row]=coutUnit;
		qTot=0;
		for(p=0,col=6;p<Atelier->NbPhase;p++,col+=2)
		{
			if(quantite[p]!=0)
			{
				q=quantite[p];
				LaGrille->Cells[col][row]=Aff(q,2);
				LaGrille->Cells[col+1][row]=Aff(q*prix,0);
				qTot+=q;
				total[p] +=q*prix;
				ssTotal[p] +=q*prix;
			}
		}
		col=4;
		LaGrille->Cells[col][row]=Aff(qTot,2);
		LaGrille->Cells[col+1][row]=Aff(qTot*prix,0);
	}
	LaGrille->Objects[1][row+1]=(TObject*)Total;
	switch(nature)
	{
		case PRODUIT:
		AffTotal(row,Atelier->NbPhase,total,L_TotProd.c_str()); //"total Produits");
		for(p=0;p<Atelier->NbPhase;p++)
		AtelierFrm->Produit[p]=total[p];
		break;

		case CHARGE:
		AffTotal(row,Atelier->NbPhase,total,L_TotCharge.c_str());//"total Charges");
		for(p=0;p<Atelier->NbPhase;p++)
		AtelierFrm->Charge[p]=total[p];
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::VersGrilleVolume (int &row,
		CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int r,nbelt; //row
	int p,col;
	int eltDansCat;
	AnsiString value;
	CL_Categorie *categorie,*cat0;
	CL_SystemeUnite *sysUnite;
	CL_ItemParAtelier *itemPA,*produitA,*production;
	CL_Item *chargeV;
	float q,qTot,prix,prod;
	float total[20],ssTotal[20];
	char coutUnit[20];
	if(vecteur->Nbelt==0) return;

	memset(total,0,sizeof(float)*20);
	memset(ssTotal,0,sizeof(total));

	row++;
	LaGrille->RowCount++;
	LaGrille->Cells[0][row]=T->L_ChfProd;//"Charges f(Prod)";
	LaGrille->Objects[1][row]=(TObject*)Titre;

	for(p=0;p<Atelier->NbPhase+1;p++) total[p]=0;
	for(p=0;p<Atelier->NbPhase+1;p++)ssTotal[p]=0;

	itemPA =vecteur->Vecteur[0];
	cat0 =itemPA->Charge->Categorie;
	eltDansCat=0;

	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		itemPA =vecteur->Vecteur[r];
//        item=    itemPA->Item;
		produitA=itemPA->ItemPA;
		chargeV= itemPA->Charge;
		for(int i=0;i<Atelier->V_Produit->Nbelt;i++)
		{
			production=Atelier->V_Produit->Vecteur[i];
			if(production==produitA) break;
		}
		categorie= chargeV->Categorie;
		sysUnite =chargeV->SysUnite;
		if(categorie!=cat0)
		{
			if(eltDansCat >1)
			AffTotal(row,Atelier->NbPhase,ssTotal,L_SousTot.c_str()); //"sous total");
			else
			{
				row++;
				LaGrille->RowCount++;
			}
			eltDansCat=0;
			for(p=0;p<Atelier->NbPhase+1;p++)ssTotal[p]=0;
			cat0=categorie;
		}
		row++;
		LaGrille->RowCount++;
		eltDansCat++;
		LaGrille->Cells[0][row]=chargeV->Nom;
		LaGrille->Cells[1][row]=categorie->Nom;
		LaGrille->Cells[2][row]=sysUnite->UUt;
		if(sysUnite->Ratio==1)
		{
			sprintf(coutUnit,"%6.2f",chargeV->Prix);
			prix=chargeV->Prix;
		}
		else
		{
			sprintf(coutUnit,"%6.2f /%s",chargeV->Prix,sysUnite->UTrans);
			prix=chargeV->Prix/sysUnite->Ratio;
		}
		LaGrille->Cells[3][row]=coutUnit;
		qTot=0;
		for(p=0,col=6;p<Atelier->NbPhase;p++,col+=2)
		{
			if(production->QtePhase[p]!=0)
			{
				prod=production->QtePhase[p];
				q= itemPA->QtePhase[p];;
				LaGrille->Cells[col][row]=Aff(q*prod,0);
				LaGrille->Cells[col+1][row]=Aff(q*prod*prix,0);
				qTot+=q*prod;
				total[p] +=q*prod*prix;
				ssTotal[p] +=q*prod*prix;
			}
		}
		col=4;
		LaGrille->Cells[col][row]=Aff(qTot,2);
		LaGrille->Cells[col+1][row]=Aff(qTot*prix,0);
	}

	LaGrille->Objects[1][row+1]=(TObject*)Total;
	AffTotal(row,Atelier->NbPhase,total,L_TotChvol.c_str()); //"total chf(vol)");
	for(p=0;p<Atelier->NbPhase;p++)
	AtelierFrm->ChargeVol[p]=total[p];

}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::AffTotal(int &row,int nbPhase,float *total,char *titre)
{
	float sigma;
	int p;
	int col;
	row++;
	LaGrille->RowCount++;

	sigma=0;
	LaGrille->Cells[0][row]=titre;
	for(p=0;p<nbPhase;p++)sigma+=total[p];
	for(p=0,col=6;p<nbPhase;p++,col+=2)
	LaGrille->Cells[col+1][row]=Aff(total[p],0);
	col=4;
	LaGrille->Cells[col+1][row]=Aff(sigma,0);
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::AffTrav(int row,CL_Atelier *atelier,
		CL_BesTrav *besTrav, float *marge,float margeTot)
{
	int col,p;
	int nbPhase=atelier->NbPhase;
	row=LaGrille->RowCount+1;
	LaGrille->RowCount+=5;
//    row+=2;
	LaGrille->Cells[0][row++]=L_Travail;//"Travail";
	LaGrille->Cells[0][row++]=besTrav->Calendrier->Nom;

	LaGrille->Cells[0][row]=L_Besoins;//"Besoin travail";////"Besoins";
	LaGrille->Cells[2][row]=L_Heure;//"heure";
	if(atelier->Espece)
	TotHeure=AtelierMDetailPerenneFrm->TotalHeure(atelier->Espece,TotHeureAn);
	LaGrille->Cells[4][row]=Aff(TotHeure,0);
	for(p=0,col=6;p<nbPhase;p++,col+=2)
	LaGrille->Cells[col][row]=Aff(TotHeureAn[p],0);
	row++;

	LaGrille->Cells[0][row]=T->L_MargeHeure;//"Marge/heure";
	LaGrille->Cells[2][row]=SysMonnaie->UTrans;
	LaGrille->Cells[5][row]=Aff(margeTot/TotHeure,2);

	if(atelier->Nature==PERENNE ||atelier->Nature==VIVRIER)
	{
		for(p=0,col=6;p<nbPhase;p++,col+=2)
		{
			if(TotHeureAn[p])
			LaGrille->Cells[col][row]=Aff(marge[p]/TotHeureAn[p],2);
			else
			LaGrille->Cells[col][row]="";
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailFrm::BtBnSyntheseClick(TObject *Sender)
{
	AtelierMargeFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TAtelierMDetailFrm::BtBnImpClick(TObject *Sender)
{

	QRGrille00Frm->LaGrille=LaGrille;
	QRGrille00Frm->TitreEtat->Caption=L_MargeDe+LabSais->Caption; //Forme00Frm->Caption;
	//QRGrille00Frm->TitreEtat->Caption=AnsiString("Marge de ")+LabSais->Caption;//Forme00Frm->Caption;
	QRGrille00Frm->TypeCol=TypeCol;
	QRGrille00Frm->Initialise();
	QRGrille00Frm->QR->Preview();

}
//---------------------------------------------------------------------------
void TAtelierMDetailFrm::Libere(TList *lstItemProd, TList *lstQuantProd,
		TList *lstItemCha, TList *lstQuantCha) {
	int n;
	float *quantite;
	delete lstItemProd;
	delete lstItemCha;
	for (n = 0; n < lstQuantProd->Count; n++) {
		quantite = (float*) lstQuantProd->Items[n];
		delete[] quantite;
	}
	delete lstQuantProd;
	for (n = 0; n < lstQuantCha->Count; n++) {
		quantite = (float*) lstQuantCha->Items[n];
		delete[] quantite;
	}
	delete lstQuantCha;
}
//---------------------------------------------------------------------------

void __fastcall TAtelierMDetailFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	CanClose=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TAtelierMDetailFrm::TexteChaine(void) {
	L_TitreGrille = T->TrouveTexte("AtelierMDetailFrm", "L_TitreGrille");
	L_AvtQuant = T->TrouveTexte("AtelierMDetailFrm", "L_AvtQuant");
	L_Quant = T->TrouveTexte("AtelierMDetailFrm", "L_Quant");
	L_QuantV = T->TrouveTexte("AtelierMDetailFrm", "L_QuantV");
	L_QuantEt = T->TrouveTexte("AtelierMDetailFrm", "L_QuantEt");
	L_Valeur = T->TrouveTexte("AtelierMDetailFrm", "L_Valeur");
	L_MargeDet = T->TrouveTexte("AtelierMDetailFrm", "L_MargeDet");
	L_Titre = T->TrouveTexte("AtelierMDetailFrm", "L_Titre");
	L_MargeUnit = T->TrouveTexte("AtelierMDetailFrm", "L_MargeUnit");
	L_SousTot = T->TrouveTexte("AtelierMDetailFrm", "L_SousTot");
	L_TotProd = T->TrouveTexte("AtelierMDetailFrm", "L_TotProd");
	L_TotCharge = T->TrouveTexte("AtelierMDetailFrm", "L_TotCharge");
	L_TotChvol = T->TrouveTexte("AtelierMDetailFrm", "L_TotChvol");
	L_Travail = T->TrouveTexte("AtelierMDetailFrm", "L_Travail");
	L_Besoins = T->TrouveTexte("AtelierMDetailFrm", "L_Besoins");
	L_Heure = T->TrouveTexte("AtelierMDetailFrm", "L_Heure");
	L_MargeDe = T->TrouveTexte("AtelierMDetailFrm", "L_MargeDe");

}
//--------------------------------------------
void TAtelierMDetailFrm::IniCaption(void) {
	LabSais->Caption = T->LC_LabSais;
	AtelierMDetailFrm->Caption = LC_AtelierMDetailFrm;
	BtBnSynthese->Caption = T->LC_BtSyntDetail;
	LabTotal->Caption = T->LC_LabTotal;
}
//--------------------------------------------
void TAtelierMDetailFrm::TexteCaption(void) {
	LC_LabSais = T->TrouveCaption("CL_Trad", "LC_LabSais");
	LC_AtelierMDetailFrm = T->TrouveCaption("AtelierMDetail",
			"LC_AtelierMDetailFrm");
	LC_BtSyntDetail = T->TrouveCaption("CL_Trad", "LC_BtSyntDetail");
	LC_LabTotal = T->TrouveCaption("CL_Trad", "LC_LabTotal");

	IniCaption();

}

void __fastcall TAtelierMDetailFrm::BtBnVersExcelClick(TObject *Sender)
{
//
	OutilFrm->VersExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);

}
//---------------------------------------------------------------------------

