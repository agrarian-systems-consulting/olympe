//---------------------------------------------------------------------------

#include <vcl.h>
#include<stdio.h>
#pragma hdrstop
#include "CL_Trad.h"
#include "Atelier.h"

#include "AtelierMDetailPerenne.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AtelierMDetail"
#pragma resource "*.dfm"
TAtelierMDetailPerenneFrm *AtelierMDetailPerenneFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TAtelierMDetailPerenneFrm::TAtelierMDetailPerenneFrm(
		TComponent* Owner) :
		TAtelierMDetailFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailPerenneFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int p,c;
	int col0,a0,a1;
	CL_Espece *espece;
	char chaine[20];
//                0  1  2  3   4
	int largeur[] = {64,64,32,64, 64};

	GrilleX=1;
	LaGrille=Grille0;
	LesGrilles[0]=Grille0;
	//LabTotal->Caption="Croisière";
	if(Atelier==NULL) return;
	espece=Atelier->Espece;

	grille->ColCount=6+Atelier->NbPhase*2;//2 colonnes par phase

	grille->FixedRows=1;
	grille->FixedCols=2;//0;//4; //5;  050208
	for(int c=0;c<4;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	for(int c=4;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[4];
		l+=largeur[4]; //100907
	}

	l=l+grille->Left+25; //25

	grille->Rows[0]->CommaText=L_TitreGrille.c_str();//"NOM,CATEGORIE,Unité,Prix,Quantite,Valeur";
	col0=6;//070102
	sprintf(chaine,L_AvtQuant.c_str());//" Avt Quant");
	grille->Cells[col0][0]=chaine;
	grille->Cells[col0+1][0]=L_Valeur;//"Valeur";
	for(p=0,c=col0+2;p<Atelier->NbPhase;p++,c+=2)
	{
		a0=espece->Phase[p];
		a1=espece->Phase[p+1];
		//if(a1==a0+1) sprintf(chaine,L_Quant.c_str(),a0);
		//else         sprintf(chaine,L_QuantEt.c_str(),a0);
		if(a1==a0+1) sprintf(chaine," %2d %s ",a0,L_Quant.c_str());
		else sprintf(chaine," %2d &+ %s ",a0,L_Quant.c_str());
		//if(a1==a0+1) sprintf(chaine,"%2d Quant",a0);
		//else         sprintf(chaine,"%2d et + Quant",a0);
		grille->Cells[c][0]=chaine;
		grille->Cells[c+1][0]=L_Valeur;//"Valeur";
	}

}
//***************************************************************************
//  VERSGRILLE
//------------------------------------------------------------------------------
void __fastcall TAtelierMDetailPerenneFrm::VersGrille(TStringGrid *grille)
{
	int n;
	int p;
	int row;
	float moyProd,moyCharge,moyChVol,moyMarge;
	float marge[N_PHASE+1],margeCumul[N_PHASE+1]; //300106  100907
	CL_ItemParAtelier *itemPA;
	CL_BesTrav *besTrav;
	float margeTot;
//CL_Item *item0,*item1;
//float *quantite0,*quantite1;
	int col0=4;
	TList *lstItemProd, *lstItemCha;//300407
	TList *lstQuantProd,*lstQuantCha;
	if(Atelier==NULL) return;
	if(Atelier->Flag==SUPPRIME )return;
	TitreGrille=Atelier->Nom;
	//    IniGrille(Grille0);
	VideLesGrilles();

	LabSais->Caption=Atelier->Nom;

	LaGrille=grille;
	LaGrille->RowCount=2;
	row=0;
	Titre=L_Titre.c_str();//"Titre";
	Total=T->L_Total.c_str();//"Total";
	Marge=T->L_Marge.c_str();//"Marge";

	//rechercher la prod maxi= année de croisiere
	itemPA=Atelier->V_Produit->Vecteur[0];
	if(itemPA==NULL)//pas de produit donc chercher dans les charges 030103
	itemPA=Atelier->V_Charge->Vecteur[0];

	/// mise à zero
	for(n=0;n<Atelier->NbPhase;n++)//210901
	{
		AtelierFrm->Produit[n] =0;
		AtelierFrm->Charge[n] =0;
		AtelierFrm->ChargeVol[n]=0;
	}
	//Duree de chaque phase
	for(p=0;p<Atelier->NbPhase;p++)
	{
		if(p==0) //annee avant
		DureePhase[p]=1;
		else if(p==Atelier->NbPhase-1)// // arrachage
		DureePhase[p]=1;
		else
		DureePhase[p]=Atelier->Espece->Phase[p]-Atelier->Espece->Phase[p-1];
	}
	// calculer quantité/ha
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
	// calcul valeur et affichage
	if(lstItemProd->Count >0)
	VersGrilleItem(row,PRODUIT,lstItemProd,lstQuantProd,moyProd);
	if(lstItemCha->Count >0)
	VersGrilleItem(row,CHARGE, lstItemCha, lstQuantCha, moyCharge);
	if(Atelier->V_ChargeVolume->Nbelt!=0)
	VersGrilleVolume(row,Atelier->V_ChargeVolume,lstItemProd,lstQuantProd,moyChVol);

	for(n=0;n<Atelier->NbPhase;n++)
	{
		marge[n]= AtelierFrm->Produit[n]
		- AtelierFrm->Charge[n]
		- AtelierFrm->ChargeVol[n];
	}
	LaGrille->Objects[1][row+1]=(TObject*)Marge;
	AffTotal(row,Atelier->NbPhase,marge,T->L_Marge.c_str()); //"Marge");

	moyMarge=moyProd-moyCharge-moyChVol;
	LaGrille->Cells[col0+1][row]=Aff(moyMarge,0);
	//pour afficher rapidement synthèse
	AtelierFrm->MoyProd=moyProd;
	AtelierFrm->MoyCharge=moyCharge;
	AtelierFrm->MoyChVol=moyChVol;

	//marge cumulée ->point mort                  //100907
	margeCumul[0]=marge[0]*DureePhase[0];
	for(n=1;n<Atelier->NbPhase;n++)
	margeCumul[n]=margeCumul[n-1]+marge[n]*DureePhase[n];
	AffTotal(row,Atelier->NbPhase,margeCumul,"Marge Cumulée");//T->L_Marge.c_str());//"Marge");

	// productivité travail
	TotHeure=0;
	if(Atelier->V_BesTrav->Nbelt!=0)
	{
		memset(TotHeureAn,0,sizeof(TotHeureAn));

		besTrav=Atelier->V_BesTrav->Vecteur[0]; //->trouve(0);
		besTrav->Totalise(TotHeure,TotHeureAn);
		TotHeure=0;
		for(p=0;p<Atelier->NbPhase;p++)
		{
			TotHeure+=TotHeureAn[p]*DureePhase[p];
		}
		if(TotHeure>0)
		{
			margeTot=0;
			for(p=0;p<Atelier->NbPhase;p++)margeTot+=marge[p]*DureePhase[p];
			AffTrav(row,Atelier,besTrav,marge,margeTot);
		}

	}

	// pour les charges prop c'est fait à chaque affichage de la grille
//    LaGrille->RowCount+=2;//+;???
//    LaGrille->FixedCols=6;

	Grille0->Visible=true;
	Libere(lstItemProd,lstQuantProd,lstItemCha,lstQuantCha);

}
//---------------------------------------------------------------------------
// Remplir les Grilles   produit charge
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailPerenneFrm::VersGrilleItem (int &row,int nature,
		TList *lstItem,TList *lstQuant, float &moyTotal)
{
	int r; //,nbelt;//row
	int p,col,col0;
	int eltDansCat,nbCat;
	AnsiString value;
	CL_Categorie *categorie,*cat0;
	CL_SystemeUnite *sysUnite;
//CL_ItemParAtelier *itemPA;
	CL_Item *item;
	float q,qTot,prix;
	char coutUnit[N_PHASE];
	float total[N_PHASE+1],ssTotal[N_PHASE+1];
	float moyQ,moySsTotal;//,moyTotal;
	int dureePhase,dureeVie;
	float *quantite;
	if(lstItem->Count==0) return;

	dureeVie=Atelier->Espece->Phase[Atelier->Espece->NbPhase-1];

	memset(total,0,sizeof(total));
	memset(ssTotal,0,sizeof(ssTotal));

	col0=4;

	row++;
	LaGrille->RowCount++;
	switch(nature)
	{
		case PRODUIT:LaGrille->Cells[0][row]=T->L_Produit;break; //"Produits";break;
		case CHARGE: LaGrille->Cells[0][row]=T->L_Charge;break;//"Charges";break;
	}
	LaGrille->Objects[1][row]=(TObject*)Titre;

	item=(CL_Item*)lstItem->Items[0];
	nbCat=0;
	cat0 =item->Categorie;
	eltDansCat=0;
	moyTotal=0;
	moySsTotal=0;

	for( r=0;r<lstItem->Count;r++)
	{
		item=(CL_Item*)lstItem->Items[r];
		quantite=(float*)lstQuant->Items[r];
		categorie=item->Categorie;
		sysUnite =item->SysUnite;
		if(categorie!=cat0)
		{
			if(eltDansCat >1)
			{
				AffTotal(row,Atelier->NbPhase,ssTotal,L_SousTot.c_str()); //"sous total");
				LaGrille->Cells[col0+1][row]=Aff(moySsTotal/(float)dureeVie,0);
			}
			nbCat++;
//            else
//            {
//                row++;
//                LaGrille->RowCount++;
//            }
			eltDansCat=0;
			memset(ssTotal,0,sizeof(ssTotal));
			moySsTotal=0;
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
		moyQ=0;
		// si espece a NbPhase  atelier a nbPhase +1  pour l'année avant
		// quant atelier est en phase p l'atelier est en phase p-1
		for(p=0,col=6;p<Atelier->NbPhase;p++,col+=2)
		{
			dureePhase=DureePhase[p]; //a trouver
			if(quantite[p]!=0)//itemPA->QtePhase[p]!=0) //!!
			{
				q=quantite[p];
				moyQ+=q*dureePhase;
				LaGrille->Cells[col][row]=Aff(q,2);
				LaGrille->Cells[col+1][row]=Aff(q*prix,0);
				qTot+=q;
				total[p] +=q*prix;
				ssTotal[p] +=q*prix;
				moySsTotal +=q*prix*dureePhase;
				moyTotal +=q*prix*dureePhase;
			}
		}
		LaGrille->Cells[col0][row]=Aff(moyQ/dureeVie,2);
		LaGrille->Cells[col0+1][row]=Aff(moyQ*prix/(float)dureeVie,0);
	}
	LaGrille->Objects[1][row+1]=(TObject*)Total;
	switch(nature)
	{
		case PRODUIT:
		if(nbCat>0)
		{
			AffTotal(row,Atelier->NbPhase,total,L_TotProd.c_str()); //"total Produits");
			LaGrille->Cells[col0+1][row]=Aff(moyTotal/(float)dureeVie,0);
		}
		for(p=0;p<Atelier->NbPhase;p++)
		AtelierFrm->Produit[p]=total[p];
		break;

		case CHARGE:
		if(nbCat>0)
		{
			AffTotal(row,Atelier->NbPhase,total,L_TotCharge.c_str()); //"total Charges");
			LaGrille->Cells[col0+1][row]=Aff(moyTotal/(float)dureeVie,0);
		}
		for(p=0;p<Atelier->NbPhase;p++)
		AtelierFrm->Charge[p]=total[p];
		break;
	}
	moyTotal/=dureeVie;
}

//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailPerenneFrm::VersGrilleVolume (int &row,
		CL_Vecteur<CL_ItemParAtelier> *vecteur,TList *lstItemProd,TList *lstQuantProd,float &moyTotal)
{
	int n,i;
	int p,col;
	int eltDansCat,nbCat;
	AnsiString value;
	CL_Categorie *categorie,*cat0;
	CL_SystemeUnite *sysUnite;
	CL_ItemParAtelier *itemPA,*produitA;
	CL_Item *chargeV,*item,*itemA;
	float *production;
	float q,qTot,prix,prod;
	float total[N_PHASE+1],ssTotal[N_PHASE+1];
	char coutUnit[N_PHASE+1];
	float moyQ,moySsTotal;
	int dureePhase,dureeVie;
	int col0=4;
	LaGrille->FixedCols=2; //0;   080207
	if(vecteur->Nbelt==0) return;

	memset(total,0,sizeof(total));
	moyTotal=0;
	moySsTotal=0;
	dureeVie=Atelier->Espece->Phase[Atelier->Espece->NbPhase-1];

	row++;
	LaGrille->RowCount++;
	LaGrille->Cells[0][row]=T->L_ChfProd;//"Charges f(Prod)";
	LaGrille->Objects[1][row]=(TObject*)Titre;

	memset(total,0,sizeof(total));
	memset(ssTotal,0,sizeof(ssTotal));

//    for(p=0;p<Atelier->NbPhase+1;p++)  total[p]=0;
//    for(p=0;p<Atelier->NbPhase+1;p++)ssTotal[p]=0;

	itemPA =vecteur->Vecteur[0];
	cat0 =itemPA->Charge->Categorie;
	eltDansCat=0;
	nbCat=0;
	//charge prop au volume  chargeV est fonction de la quantite de produitA
	for( n=0;n<vecteur->Nbelt;n++)
	{
		itemPA =vecteur->Vecteur[n];
		produitA =itemPA->ItemPA;
		itemA=produitA->Item;
		chargeV =itemPA->Charge;
		for(i=0;i<lstItemProd->Count;i++)
		{
			item=(CL_Item*)lstItemProd->Items[i];
			if(item==itemA)
			{
				production=(float*)lstQuantProd->Items[i];
				break;
			}
		}
		categorie= chargeV->Categorie;
		sysUnite =chargeV->SysUnite;
		if(categorie!=cat0)
		{
			if(eltDansCat >1)
			{
				AffTotal(row,Atelier->NbPhase,ssTotal,L_SousTot.c_str()); //"sous total");
				LaGrille->Cells[col0+1][row]=Aff(moySsTotal/(float)dureeVie,0);
			}
			nbCat++;
//            else
//            {
//                row++;
//                LaGrille->RowCount++;
//            }
			eltDansCat=0;
			moySsTotal=0;
			for(p=0;p<Atelier->NbPhase+1;p++)ssTotal[p]=0;
			cat0=categorie;
		}
		row++;
		LaGrille->RowCount++;
		eltDansCat++;
		LaGrille->Objects[1][row]=NULL;
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
		moyQ=0;
		for(p=0,col=6;p<Atelier->NbPhase;p++,col+=2)
		{
			dureePhase=DureePhase[p];

			if(production[p]!=0)
			{
				prod=production[p];
				q= itemPA->QtePhase[p];;
				LaGrille->Cells[col][row]=Aff(q*prod,0);
				LaGrille->Cells[col+1][row]=Aff(q*prod*prix,0);
				qTot +=q*prod;
				moyQ +=q*prod*dureePhase;
				total[p] +=q*prod*prix;
				ssTotal[p] +=q*prod*prix;
				moySsTotal +=q*prod*prix*dureePhase;
				moyTotal +=q*prod*prix*dureePhase;
			}
		}
		LaGrille->Cells[col0][row]=Aff(moyQ/dureeVie,2);
		LaGrille->Cells[col0+1][row]=Aff(moyQ*prix/(float)dureeVie,0);
	}
	if(nbCat>0)
	{
		AffTotal(row,Atelier->NbPhase,total,L_TotChvol.c_str()); //"total Charges(f vol)");
		LaGrille->Cells[col0+1][row]=Aff(moyTotal/(float)dureeVie,0);
	}
	LaGrille->Objects[1][row+1]=(TObject*)Total;
	for(p=0;p<Atelier->NbPhase;p++)
	AtelierFrm->ChargeVol[p]=total[p];
	moyTotal/=dureeVie;

}

//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailPerenneFrm::AffTotal(int &row,int nbPhase,float *total,char *titre)
{
	int p;
	int col;
	row++;
	LaGrille->RowCount++;
	//la myenne est affichée par ailleurs à améliorer!!!
	LaGrille->Cells[0][row]=titre;
	for(p=0,col=6;p<nbPhase;p++,col+=2)
	LaGrille->Cells[col+1][row]=Aff(total[p],0);
}
//---------------------------------------------------------------------------
float TAtelierMDetailPerenneFrm::TotalHeure(CL_Espece *espece,
		float *totHeureAn) {
//int dureePhase[20];
	int i, duree, age;
	float tot;
	tot = totHeureAn[0];
	age = 0;
	for (i = 0; i < espece->NbPhase - 1; i++) {
		duree = espece->Phase[i + 1] - espece->Phase[i];
		age += duree;
		tot += totHeureAn[i + 1] * duree;
	}
	duree = espece->DurAmor - age;
	if (duree > 0) {
		i = espece->NbPhase;
		tot += totHeureAn[i] * duree;
	}
	return tot;
}
//---------------------------------------------------------------------------
void __fastcall TAtelierMDetailPerenneFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	CanClose=true;
}
//---------------------------------------------------------------------------
void TAtelierMDetailPerenneFrm::TexteChaine(void) {
	L_TitreGrille = T->TrouveTexte("AtelierMDetailFrm", "L_TitreGrille");
	L_AvtQuant = T->TrouveTexte("AtelierMDetailFrm", "L_AvtQuant");
	L_Valeur = T->TrouveTexte("AtelierMDetailFrm", "L_Valeur");
	L_Quant = T->TrouveTexte("AtelierMDetailFrm", "L_Quant");
	L_QuantEt = T->TrouveTexte("AtelierMDetailFrm", "L_QuantEt");

	L_TotProd = T->TrouveTexte("AtelierMDetailFrm", "L_TotProd");
	L_TotCharge = T->TrouveTexte("AtelierMDetailFrm", "L_TotCharge");
	L_TotChvol = T->TrouveTexte("AtelierMDetailFrm", "L_TotChvol");

}
//---------------------------------------------------------------------------
void TAtelierMDetailPerenneFrm::IniCaption(void) {
	AtelierMDetailPerenneFrm->Caption = LC_AtelierMDetailPerenneFrm;
	LabTotal->Caption = LC_LabTotal;
}
//--------------------------------------------
void TAtelierMDetailPerenneFrm::TexteCaption(void) {
	LC_AtelierMDetailPerenneFrm = T->TrouveCaption("AtelierMDetailPerenne",
			"LC_AtelierMDetailPerenneFrm");
	LC_LabTotal = T->TrouveCaption("AtelierMDetailPerenne", "LC_LabTotal");

	IniCaption();

}

