//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
//#include "Forme0.h"

#pragma hdrstop

#include "Atelier.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------
//****************************************************************************
// FONCTIONS A PERSONNALISER
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::DefinirLesGrilles(void)
{

	AjoutRow=true;
	Grille0->Visible=false;
	GrilleX=11; //280307
	//         0        1      2       3     4       5      6        7
	//enum { GProduit,GCharge,GChProp,GExter,GAvance,GPImmo,GTravail,GValInv}; //220903

	LesGrilles[0]=GrilleProduits;//produits
	LesGrilles[1]=GrilleCharges;//charges
	LesGrilles[2]=GrilleChargeVolume;//charges prop
	LesGrilles[3]=GrilleExternalite;//externalite
	LesGrilles[4]=GrilleAvance;//avance aux cultures
	LesGrilles[5]=GrilleProdImmo;//Production d'immobilisation
								 // seult pour les pérennes
	LesGrilles[6]=GrilleTravail;//travail  200802
	LesGrilles[7]=GrilleValInv;//220903
	LesGrilles[8]=GrillePiedHa;//280307
	LesGrilles[9]=GrilleProdPied;//280307
	LesGrilles[10]=GrilleChPied;//280307

	for(int g=0;g<GrilleX;g++)
	{
		LesGrilles[g]->Tag=g; // cf enum dans Atelier.h
		LesGrilles[g]->ColCount=30;//??
		ColM[g]=2;
		RowM[g]=1;
	}
	VideLesGrilles(); ///291101

	switch(Nature)
	{
		case ANIMAUX:
		TSValInv->TabVisible =true;
		TSAvance->TabVisible =false;
		TSProdImmo->TabVisible =false;
		break;
		default:
		TSValInv->TabVisible =false;
		TSAvance->TabVisible =true;
		TSProdImmo->TabVisible =true;
	}

	//je commence par les produits
	PC->ActivePage=TSProduit;
	LaGrille=GrilleProduits;
	CreeLBTravail();
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::CreeLBTravail(void)
{
	CL_Calendrier *calendrier;
	CL_BesTrav *besTrav;
	AnsiString as;
	int i,n;
	LBCalendrier->Clear();
	for(i=0;i<V_Calendrier->Nbelt;i++)
	{
		calendrier=V_Calendrier->Vecteur[i];
		as=AnsiString("  ")+calendrier->Nom;
		LBCalendrier->Items->AddObject(as,(TObject*)calendrier);
	}
	LBCalendrier->Items->AddObject("[...]",NULL);
	if(Atelier->V_BesTrav->Nbelt==0)
	LBCalendrier->ItemIndex=0;
	else
	{
		LBCalendrier->ItemIndex=-1;
		for(n=0;n<Atelier->V_BesTrav->Nbelt;n++)
		{
			besTrav=Atelier->V_BesTrav->Vecteur[n];
			if(besTrav->Calendrier==NULL)
			{
				Atelier->V_BesTrav->sup(besTrav);
				LBCalendrier->ItemIndex=0;
				ShowMessage("Revoir Calendrier de Travail");
				//260705
				continue;
			}
			for(i=0;i<LBCalendrier->Items->Count;i++)
			{
				calendrier=(CL_Calendrier*)LBCalendrier->Items->Objects[i];
				if(besTrav->Calendrier==calendrier)
				{
					if(LBCalendrier->ItemIndex==-1)LBCalendrier->ItemIndex=i;
					as=LBCalendrier->Items->Strings[i];
					as[1]='*';
					LBCalendrier->Items->Strings[i]=as;
					break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
//IniGrille
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrille(TStringGrid *grille)
{
	switch(grille->Tag)
	{
		case GProduit:
		case GCharge:
		case GExter:
		case GProdPied:
		case GChPied:
		IniGrilleProduit(grille);break;
		case GChProp: IniGrilleVolume(grille);break;
		case GAvance: IniGrilleAvance(grille);break;
		case GPImmo: IniGrilleProdImmo(grille);break;
		case GTravail: IniGrilleTravail(grille);break;
		case GValInv: IniGrilleValInv(grille);break;
		case GPiedHa: IniGrillePiedHa(grille);break;
	}
}
//---------------------------------------------------------------------------
//Produit Charge externalite
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrilleProduit(TStringGrid *grille)
{
	int l=0;
	int nbPhase;
	//14 phases
//                     |     | 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
	int largeur[] = {20,10,64,64, 64};
	nbPhase=Atelier->NbPhase;

	grille->ColCount=2+3+nbPhase;
	grille->FixedRows=1;
	grille->FixedCols=2; //5;
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

	grille->Rows[0]->CommaText=L_TitreProduit;//".,.,NOM,CATEGORIE,Unité_Atelier";

	MetAnnee(grille,5);
}
//---------------------------------------------------------------------------
// Charges fonction de la quantité
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrilleVolume(TStringGrid *grille)
{
	int l=0;
	int nbPhase;
	//14 phases
//                     |     | 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
	int largeur[] = {20,10,64,64, 64};
	nbPhase=Atelier->NbPhase;

	grille->ColCount=2+3+nbPhase+1;

	grille->FixedRows=1;
	grille->FixedCols=2; //5;
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

	grille->Rows[0]->CommaText=L_TitreVol;//".,.,PRODUIT,Unité,APPRO,Unité";

	MetAnnee(grille,5);

}
//---------------------------------------------------------------------------
//Avance
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrilleAvance(TStringGrid *grille)
{
	int r;
	int l=0;
	int nbPhase;
	int largeur=64;
	nbPhase=Atelier->NbPhase;

	grille->ColCount=1+nbPhase;
	grille->RowCount=13;
	grille->FixedRows=1;
	grille->FixedCols=1; //5;
	for(int c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur;
		l+=largeur;
	}
	l=l+grille->Left+25; //25

	grille->Cells[0][0]=L_Ouverture;//"Ouverture";
	for(r=1;r<13;r++)
	{
		grille->Cells[0][r]=AnsiString("  ")+AnsiString(r);
	}
	MetAnnee(grille,1);

}
//---------------------------------------------------------------------------
// Production d'immo
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrilleProdImmo(TStringGrid *grille)
{
	int l=0;
	int largeur=64;

	grille->ColCount=1+Atelier->NbPhase;
	grille->RowCount=3;
	grille->FixedRows=1;
	grille->FixedCols=1; //5;

	grille->ColWidths[0]=largeur*2;

	for(int c=1;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur;
		l+=largeur;
	}
	l=l+grille->Left+25; //25

	grille->Cells[0][1]=L_Ent;//" Par l'entreprise";
	grille->Cells[0][2]=L_Fam;//" Par la famille";

	MetAnnee(grille,1);
}
//---------------------------------------------------------------------------
//Travail
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrilleTravail(TStringGrid *grille)
{
	int i;
	int largeur=128;

	grille->ColCount=1+Atelier->NbPhase; //Atelier->Espece->NbPhase ???
	grille->RowCount=30;//12
	grille->FixedRows=1;
	grille->FixedCols=1;//5;

	grille->ColWidths[0]=largeur;
	for(i=1;i<grille->ColCount;i++ )
	grille->ColWidths[i]=largeur/2;

	grille->Cells[0][0]=L_Periode;//"Périodes";
//    grille->Cells[1][0]="Avant 1";
//    grille->Cells[2][0]="  1";
//    grille->Cells[3][0]="  2";

	MetAnnee(grille,1);
}
//------------------------------------------------------------------------------
//valeurs d'inventaire
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrilleValInv(TStringGrid *grille)
{
	ColM[grille->Tag]=1;
	RowM[grille->Tag]=1;
	grille->ColCount=2;
	grille->RowCount=2;
	grille->FixedRows=0;
	grille->FixedCols=1;
	grille->ColWidths[0]=128;
	grille->ColWidths[1]=64;
	grille->Cells[0][0]=L_Repro; //"Reproducteur";
	grille->Cells[0][1]=L_Autre;//"Autre";

}
//---------------------------------------------------------------------------
//PiedHa
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::IniGrillePiedHa(TStringGrid *grille)
{
	int l=0;
	int nbPhase;
	int largeur=64;
	nbPhase=Atelier->NbPhase;

	grille->ColCount=1+nbPhase;
	grille->RowCount=2;
	grille->FixedRows=1;
	grille->FixedCols=1; //5;
	for(int c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur;
		l+=largeur;
	}
	l=l+grille->Left+25; //25

	grille->Cells[0][0]=L_Ouverture;//"Ouverture";
	grille->Cells[0][1]=L_PiedParHa;//AnsiString("  Pied/ha");

	MetAnnee(grille,1);

}
//------------------------------------------------------------------------------
// affiche les années
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::MetAnnee(TStringGrid *grille,int col0)
{
	int c,p,a0,a1;
	char chaine[20];
	if(grille==GrilleChargeVolume) col0++;

	switch(Nature)
	{
		case PERENNE:
		grille->Cells[col0][0]=L_Avant1; //"Avant 1";
		for(p=0,c=col0+1;p<Atelier->NbPhase;p++,c++)
		{
			a0=Espece->Phase[p];
			a1=Espece->Phase[p+1];
			if(a1==a0+1) sprintf(chaine,"  %2d",a0);
			else if(a1==0) sprintf(chaine,"  %2d ...",a0);
			else sprintf(chaine,"  %2d - %2d",a0,a1-1);
			grille->Cells[c][0]=chaine;
			if(a1==0)break; //180108
		}
		break;
		case ANIMAUX:
		case CULTURE:
		c=col0;
		grille->Cells[c++][0]=L_Avant1; //"Avant 1";
		grille->Cells[c++][0]="  1";
		grille->Cells[c][0]= "  2";
		break;
		case VIVRIER:
		c=col0;
		grille->Cells[c++][0]=L_Avant1;//"Avant 1";
		grille->Cells[c++][0]="  1";
		grille->Cells[c++][0]="  2";
		grille->Cells[c++][0]="  3";
		grille->Cells[c][0]= "  4";
		break;
	}
}
//***************************************************************************
//  VERSGRILLE
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrille(TStringGrid *grille)
{
	int g=grille->Tag;
//	if(EstInitialise==false) return;
	if(Atelier==NULL) return;
	if(Atelier->Flag==SUPPRIME )return;

	LaGrille=grille;
	if ( grille==GrilleProduits) VersGrilleItem(Atelier->V_Produit);
	else if( grille==GrilleCharges) VersGrilleItem(Atelier->V_Charge);
	else if( grille==GrilleChargeVolume) VersGrilleVolume(Atelier->V_ChargeVolume);
	else if( grille==GrilleExternalite) VersGrilleItem(Atelier->V_Externalite);
	else if( grille==GrilleAvance) VersGrilleAvance(Atelier->V_Avance);
	else if( grille==GrilleProdImmo) VersGrilleProdImmo(Atelier->ProdImmo,Atelier->ProdImmoFam);
	else if( grille==GrilleValInv) VersGrilleValInv();

	else if( grille==GrillePiedHa)
	VersGrillePiedHa(Atelier->PiedHa);//PiedHa
	else if( grille==GrilleProdPied)
	VersGrilleItem(Atelier->V_ProdPied);
	else if( grille==GrilleChPied)
	VersGrilleItem(Atelier->V_ChPied);
	GrilleModif[g] =false;

}
//---------------------------------------------------------------------------
//  produit charge irrigation
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrilleItem (CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int row,r,nbelt;
	int p,col;
	AnsiString value;
	CL_Categorie *categorie;
	CL_SystemeUnite *sysUnite;
	CL_ItemParAtelier *itemPA;
	CL_Item *item;
//float q,p,ra;
	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;
	VideGrille(LaGrille);//180108

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		itemPA =vecteur->Vecteur[r];
		item=itemPA->Item;
		categorie=item->Categorie;
		sysUnite =item->SysUnite;

		LaGrille->Objects[0][row]=(TObject*)itemPA;
		itemPA->Flag='O';
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=item->Nom;
		LaGrille->Cells[3][row]=categorie->Nom;
		LaGrille->Cells[4][row]=sysUnite->UUt;
		for(p=0,col=5;p<Atelier->NbPhase;p++,col++)
		{
			if(Espece && Espece->Phase[p-1]==0) break; //240108

			if(itemPA->QtePhase[p]!=0)
			LaGrille->Cells[col][row]=Aff(itemPA->QtePhase[p],2);
		}
	}
}
//---------------------------------------------------------------------------
// Remplir la Grille charges prop au volume
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrilleVolume(CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int row,r,nbelt;
	AnsiString value;
	CL_SystemeUnite *sysUniteC;
	CL_ItemParAtelier *itemPA, *produitA;
	CL_Item *produit,*charge;
	int p,col;
//float q,p,ra;
	VideGrille(LaGrille);

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;
//reprendre données précédentes
	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		itemPA =vecteur->Vecteur[r];
		produitA=itemPA->ItemPA;
		if(produitA==NULL)
		{
			vecteur->sup(itemPA);
			r--;
			nbelt--;
			continue;
		}
		produit =produitA->Item;

		if(itemPA->Charge!=NULL)
		{
			charge=itemPA->Charge;
			sysUniteC=charge->SysUnite;
		}

		LaGrille->Objects[0][row]=(TObject*)itemPA;

		itemPA->Flag='O';
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=produit->Nom;
		LaGrille->Cells[3][row]=produit->SysUnite->UUt;

		if(itemPA->Charge==NULL) continue;

		LaGrille->Cells[4][row]=charge->Nom;
		LaGrille->Cells[5][row]=sysUniteC->UUt;
		for(p=0,col=6;p<Atelier->NbPhase;p++,col++)
		{
			if(itemPA->QtePhase[p]!=0)
			LaGrille->Cells[col][row]=Aff(itemPA->QtePhase[p],2);
		}
	}
}
//---------------------------------------------------------------------------
bool __fastcall TAtelierFrm::ChargeVolumeExiste(int No)
{
	CL_ItemParAtelier *itemPA;
	for( int r=0;r<Atelier->V_ChargeVolume->Nbelt;r++)
	{
		itemPA =Atelier->V_ChargeVolume->Vecteur[r];
		if(itemPA->No==No) return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrilleAvance(CL_Vecteur<CL_EEF> *vecteur)
{
	int i;
	int r,r0,r1;
	int col;
	int nbelt;
	CL_EEF *eEF;
	nbelt=vecteur->Nbelt;

	for( i=0;i<nbelt;i++)
	{
		eEF=vecteur->Vecteur[i];
		eEF->Coordonnee(col,r0,r1);
		for(r=r0;r<=r1;r++)
		LaGrille->Cells[col][r]=Aff(eEF->Val,0);
	}
}
//---------------------------------------------------------------------------
// Remplir la Grille Production d'immo
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrilleProdImmo(float *prodImmo,float *prodImmoFam)
{
	int p;
	int col, row;
	EdDurAmor->Text=" ";
	EdDebAmor->Text=" ";
	if(Atelier->DurAmor) EdDurAmor->Text=AnsiString(Atelier->DurAmor);
	if(Atelier->DebAmor) EdDebAmor->Text=AnsiString(Atelier->DebAmor);
	if(Atelier->DurAmor>0 && Atelier->DebAmor==0) EdDebAmor->Text="0";

	if(Atelier->PImmoExiste==true)
	{
		row=1;
		for(p=0,col=1;p<Atelier->NbPhase;p++,col++)
		{
			if(prodImmo!=NULL && prodImmo[p]!=0)
			LaGrille->Cells[col][row]=Aff(prodImmo[p],0);
		}
	}
	if(Atelier->PImmoFamExiste==true)
	{
		row=2;
		for(p=0,col=1;p<Atelier->NbPhase;p++,col++)
		{
			if(prodImmoFam!=NULL && prodImmoFam[p]!=0)
			LaGrille->Cells[col][row]=Aff(prodImmoFam[p],0);
		}
	}
}
//---------------------------------------------------------------------------
// Remplir la Grille Production d'immo
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrilleValInv(void)
{

	LaGrille->Cells[1][0]=Aff(Atelier->ValInvRepro);
	LaGrille->Cells[1][1]=Aff(Atelier->ValInvAutre);
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::VersGrillePiedHa(float *piedHa)
{
	int i;
	int col,row;
	row=1;
	for(col=1,i=0;col<LaGrille->ColCount; col++,i++)
	{
		LaGrille->Cells[col][row]=Aff(piedHa[i],0);
	}
}

//total des charges pour faciliter saisie des avances aux cultures
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::AffTotalCharge(TStringGrid *grille)
{
	int n;
	int p;
	int r,a0,a1;
	float prix,q;
	CL_Item *item;
	CL_ItemParAtelier *itemPA;
	float total[N_PHASE];
	char chaine[50];
	memset(total,0,sizeof(float)*N_PHASE); //230902
	grille->RowCount=Atelier->NbPhase;
	grille->Cells[0][0]=L_Avant1;//Avant 1";
	if(Atelier->Nature==PERENNE)
	{
		for(p=0,r=1;p<Atelier->NbPhase;p++,r++)
		{
			a0=Espece->Phase[p];
			a1=Espece->Phase[p+1];
			if(a1==a0+1) sprintf(chaine,"  %2d",a0);
			else if(a1==0) sprintf(chaine,"  %2d ...",a0);
			else sprintf(chaine,"  %2d - %2d",a0,a1-1);

			grille->Cells[0][r]=chaine;
		}
	}
	else
	{
		grille->Cells[0][1]="   1";
		grille->Cells[0][2]="   2";

	}

	for( n=0;n<Atelier->V_Charge->Nbelt;n++)
	{
		itemPA =Atelier->V_Charge->Vecteur[n];
		item=itemPA->Item;
		if(item->SysUnite->Ratio==1)
		prix=item->Prix;
		else
		prix=item->Prix/item->SysUnite->Ratio;
		for(p=0;p<Atelier->NbPhase;p++)
		{
			if(itemPA->QtePhase[p]!=0)
			{
				q=itemPA->QtePhase[p];
				total[p] +=q*prix;
			}
		}
	}
	for(p=0;p<Atelier->NbPhase;p++)
	{
		grille->Cells[1][p]=FloatToStrF(total[p],ffNumber,7,0);
	}
}

/*
 L_TitreProduit=             ".,.,NOM,CATEGORIE,Unité_Atelier";
 L_TitreVol=                 ".,.,PRODUIT,Unité,APPRO,Unité";
 L_Ouverture=                "Ouverture";
 L_Ent=                      " Par l'entreprise";
 L_Fam=                      " Par la famille";
 L_Periode=                  "Périodes";
 L_Repro=                    "Reproducteur";
 L_Autre=                    "Autre";
 L_Avant1=                   "Avant 1";


 */
