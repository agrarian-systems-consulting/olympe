//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Tableur.h"
#include "SysUnite.h"
#include "AgriSaisie.h"
#include "Tendance.h"
#include "Ensemble.h"

#include "CreeLBTV.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
// ligne
//////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// INI ListBox
//---------------------------------------------------------------------------

void __fastcall CreeLBTV::CreeLBCat(TListBox *LB,CL_Vecteur<CL_Categorie> *vecteur,
		bool avec)
{
	CL_Categorie *categorie;
	int i;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		categorie=vecteur->Vecteur[i];
		LB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	if( vecteur== V_CatProduit
			|| vecteur== V_CatCharge
			|| vecteur== V_CatTypeZone
			|| vecteur== V_CatVar
			|| vecteur== V_CatDico)
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBUnite(TListBox *LB,CL_Vecteur<CL_SystemeUnite> *vecteur,bool avec)
{
	CL_SystemeUnite *systeme;
	int i;
	char buf[100];
	LB->Clear();
	LB->Font->Name="Courier";
	for(i=0;i<vecteur->Nbelt;i++)
	{
		systeme=vecteur->Vecteur[i];
		sprintf(buf,"%-6.6s %-6.6s %-6.6s",
				systeme->UUt.c_str(),systeme->UTrans.c_str(),systeme->UGlobal.c_str());
		LB->Items->AddObject(buf,(TObject*)systeme);
	}
	if(avec==true)
	LB->Items->AddObject("[...]",NULL);

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBTva(TListBox *LB,CL_Vecteur<CL_Tva> *vecteur,bool avec)
{
	CL_Tva *tva;
	int i;

	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		tva=vecteur->Vecteur[i];
		LB->Items->AddObject(tva->Nom,(TObject*)tva);
	}
	if(avec==true)
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBAtelier(TListBox *LB,CL_Vecteur<CL_Atelier> *vecteur,bool avec)
{
	CL_Atelier *atelier;
	int i;

	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		atelier=vecteur->Vecteur[i];
		LB->Items->AddObject(atelier->Nom,(TObject*)atelier);
	}
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBItem(TListBox *LB,CL_Vecteur<CL_Item> *vecteur, int noCat,bool avec)
{
	int i;
	CL_Item *item;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		item=vecteur->Vecteur[i];
		if(item->NoCategorie!=noCat) continue;
		LB->Items->AddObject(item->Nom,(TObject*)item);
	}
	LB->Items->AddObject("[...]",NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBEtatSortie(TListBox *LB,CL_Vecteur<CL_EtatSortie> *vecteur)
{
	CL_EtatSortie *etat;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		etat=vecteur->Vecteur[i];
		LB->Items->AddObject(etat->Nom,(TObject *)etat);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBElt(TListBox *LB,CL_Vecteur<CL_Elt> *vecteur,bool avec)
{
	CL_Elt *elt;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		elt=vecteur->Vecteur[i];
		LB->Items->AddObject(elt->Nom,(TObject *)elt);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBVariable(TListBox *LB,CL_Categorie *cat,CL_Vecteur<CL_Item> *vecteur)
{
	CL_Item *variable;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		variable=vecteur->Vecteur[i];
		if(variable->NoCategorie!=cat->No) continue;
		LB->Items->AddObject(variable->Nom,(TObject *)variable);
	}
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBValeur(TListBox *LB,CL_Vecteur<CL_Valeur> *vecteur,bool avec)
{
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		valeur=vecteur->Vecteur[i];
		atelier=valeur->Atelier;
		LB->Items->AddObject(atelier->Nom,(TObject *)valeur);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBVerger(TListBox *LB,CL_Vecteur<CL_Verger> *vecteur,bool avec)
{
	CL_Verger *verger;
	CL_Atelier *atelier;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		verger=vecteur->Vecteur[i];
		atelier=verger->Atelier;
		LB->Items->AddObject(atelier->Nom,(TObject *)verger);
	}
}
//Tendance
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBTendance(TListBox *LB,CL_Vecteur<CL_Tendance> *vecteur)
{
	CL_Tendance *tendance;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		tendance=vecteur->Vecteur[i];
		LB->Items->AddObject(tendance->Nom,(TObject *)tendance);
	}
	LB->Items->AddObject("[...]",NULL);

}
//Calendrier
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBCalendrier(TListBox *LB,CL_Vecteur<CL_Calendrier> *vecteur)
{
	CL_Calendrier *calendrier;
	int i;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		calendrier=vecteur->Vecteur[i];
		LB->Items->AddObject(calendrier->Nom,(TObject *)calendrier);
	}
	LB->Items->AddObject("[...]",NULL);

}
//Conversion
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBConversion(TListBox *LB,CL_Vecteur<CL_Conversion> *vecteur)
{
	CL_Conversion *conversion;
	int i;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		conversion=vecteur->Vecteur[i];
		LB->Items->AddObject(conversion->Nom,(TObject *)conversion);
	}
	LB->Items->AddObject("[...]",NULL);

}
//---------------------------------------------------------------------------
// INI CheckListBox
//---------------------------------------------------------------------------

void __fastcall TForme0Frm::CreeCLBCat(TCheckListBox *CLB,CL_Vecteur<CL_Categorie> *vecteur)
{
	CL_Categorie *categorie;
	int i;
	CLB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		categorie=vecteur->Vecteur[i];
		CLB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	/*
	 if(    vecteur== V_CatProduit
	 || vecteur== V_CatCharge
	 || vecteur== V_CatTypeZone
	 || vecteur== V_CatVar
	 || vecteur== V_CatDico)
	 LB->Items->AddObject("[...]",NULL);
	 */
}
//-----------------------------------------------------------------------------
// ControlBox
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeCBType(TComboBox *CB,CL_Vecteur<CL_Item> *vecteur,int noCat)
{
	CL_Item *type;
	int i;
	CB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		type=vecteur->Vecteur[i];
		if(type->NoCategorie!=noCat) continue;
		CB->Items->AddObject(type->Nom,(TObject*)type);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeCBEspece(TComboBox *CB,CL_Vecteur<CL_Espece> *vecteur)
{
	CL_Espece *espece;
	int i;
	CB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		espece=vecteur->Vecteur[i];
		CB->Items->AddObject(espece->Nom,(TObject *)espece);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeCBCategorie(TComboBox *CB,CL_Vecteur<CL_Categorie> *vecteur)
{
	CL_Categorie *categorie;
	int i;
	CB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		categorie=vecteur->Vecteur[i];
		CB->Items->AddObject(categorie->Nom,(TObject *)categorie);
	}
}
//-----------------------------------------------------------------------------
//   TREENODE
//              TVPerenne  TVCulture=Culture+Vivrier
//              TV V_Produit V_Charge  V_Irrigation
//-----------------------------------------------------------------------------
// AgriSaisie
//-----------------------------------------------------------------------------
// AgriSaisie
// GereAtelier
void __fastcall TForme0Frm::CreeTVAtelier( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Atelier> *vAtelier)
{
	TTreeNode *tNCat,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	int nature;
	if (vAtelier==V_Culture) nature=CULTURE; //c'est un entier
	else if(vAtelier==V_Animaux) nature=ANIMAUX;//c'est un entier
	else if(vAtelier==V_Vivrier) nature=VIVRIER;//c'est un entier

	TV->Items->Clear();

	tNCat=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCat,cat->Nom,cat);
		for(j=0;j<vAtelier->Nbelt;j++)
		{
			atelier=vAtelier->Vecteur[j];
			if(atelier->NoCategorie==cat->No)
			{
				TV->Items->AddChildObject(tNElt,atelier->Nom,atelier);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",(TObject*)nature);
	}
	TV->Items->AddObject(tNCat,"[...]",(TObject*)nature);

}
//-----------------------------------------------------------------------------
// AgriSaisie
// GereAtelier
void __fastcall TForme0Frm::CreeTVPerenne( TTreeView *TV,
		CL_Vecteur<CL_Espece> *vEsp,CL_Vecteur<CL_Atelier> *vPer)
{
	TTreeNode *tNEspece,*tNElt;
	AnsiString s;
	int i,j;
	CL_Espece *espece;
	CL_Atelier *perenne;

	TV->Items->Clear();

	tNEspece=new TTreeNode(TV->Items);
	for(i=0;i<vEsp->Nbelt;i++)
	{
		espece=vEsp->Vecteur[i];
		tNElt=TV->Items->AddObject(tNEspece,espece->Nom,espece);
		for(j=0;j<vPer->Nbelt;j++)
		{
			perenne=vPer->Vecteur[j];
			if(perenne->NoEspece==espece->No)
			{
				TV->Items->AddChildObject(tNElt,perenne->Nom,perenne);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",perenne);
	}
	TV->Items->AddObject(tNEspece,"[...]",NULL);

}
//-----------------------------------------------------------------------------
// Categorie
// AgriSaisie
// GereAtelier
void __fastcall TForme0Frm::CreeTVItem( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Item> *vElt)
{
	TTreeNode *tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *categorie;
	CL_Item *item;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vElt->Nbelt;j++)
		{
			item=vElt->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,item->Nom,item);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",item);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVIndicateur(TTreeView *TV)
{
	TTreeNode *tNCategorie,*tNElt;
	CL_Indicateur *indic;
	CL_Categorie *categorie;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(int i=0;i<V_CatIndic->Nbelt;i++)
	{
		categorie=V_CatIndic->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(int j=0;j<V_Indicateur->Nbelt;j++)
		{
			indic=V_Indicateur->Vecteur[j];
			if(indic->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,indic->Nom,indic);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",NULL);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVEtat(TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_EtatSortie> *vEtat)

{
	TTreeNode *tNCategorie,*tNElt;
	CL_EtatSortie *etat;
	CL_Categorie *categorie;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(int i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(int j=0;j<vEtat->Nbelt;j++)
		{
			etat=vEtat->Vecteur[j];
			if(etat->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,etat->Nom,etat);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",NULL);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);
}

//-----------------------------------------------------------------------------
//  utilisé pour construire des formules
// ne comporte que les variables utilisées par l'agriculteur
// pas d'ajout possible
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVariable( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Valeur> *vValeur)
{
	TTreeNode *tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *categorie;
	CL_Valeur *valeur;
	CL_Item *item;
	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vValeur->Nbelt;j++)
		{
			valeur=vValeur->Vecteur[j];
			item=valeur->Item;
			if(item->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,item->Nom,item);
			}
		}
	}
}
/*
 test avec nombre
 //-----------------------------------------------------------------------------
 void __fastcall TForme0Frm::CreeTVVariante(	TTreeView *TV,CL_Agriculteur *agri)
 {
 TTreeNode *tNPere,*tNFils,*tNPetitFils;
 CL_Agriculteur *agriFils;
 AnsiString s;
 int i,j,nF,nPf;
 ST_NoAgri    *noAgri;
 TV->Items->Clear();

 tNPere=new TTreeNode(TV->Items);
 tNFils=TV->Items->AddObject(tNPere,agri->Nom,agri);
 for(i=0;i<4;i++)
 {
 nF=i+1;
 tNPetitFils=TV->Items->AddChildObject(tNFils,nF,agri);
 for(j=0;j<5;j++)
 {
 nPf=nF*10+j+1;
 CreeTVVarianteSuite(TV,nPf,tNPetitFils);
 }
 }
 TV->Items->AddChildObject(tNFils,"[...]",NULL);
 }
 //-----------------------------------------------------------------------------
 void __fastcall TForme0Frm::CreeTVVarianteSuite(TTreeView *TV,int nF,TTreeNode *tNFils)
 {
 TTreeNode *tNPetitFils;
 int j,nPf;
 if (nF>1000)return;
 tNPetitFils=TV->Items->AddChildObject(tNFils,nF,NULL);//agri);
 for(j=0;j<4;j++)
 {
 nPf=nF*10+j+1;
 CreeTVVarianteSuite(TV,nPf,tNPetitFils);
 }

 }
 */
// Variante Agri
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteAgri( TTreeView *TV,CL_Agriculteur *agri)
{
	TTreeNode *tNPere,*tNFils,*tNPetitFils;
	CL_Agriculteur *pere,*fils,*petitFils;
	AnsiString s;
	int i,j,nF,nPf;
	ST_NoAgri *variante;
	TV->Items->Clear();

	pere=agri;
	agri->NoVariante=0;
	tNPere=new TTreeNode(TV->Items);
	tNFils=TV->Items->AddObject(tNPere,pere->Nom,agri);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		nF=i+1;
		variante=(ST_NoAgri*)pere->LstVariante->Items[i];
		fils=variante->Agri;
		fils->NoVariante=nF;
		tNPetitFils=TV->Items->AddChildObject(tNFils,nF,fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			nPf=nF*10+j+1;
			variante=(ST_NoAgri*)fils->LstVariante->Items[j];
			petitFils=variante->Agri;
			petitFils->NoVariante=nPf;
			CreeTVVarianteAgriSuite(TV,nPf,petitFils,tNPetitFils);
		}
		//if(fils->LstVariante->Count==0)
		TV->Items->AddChildObject(tNPetitFils,"[...]",fils);
	}
	TV->Items->AddChildObject(tNFils,"[...]",pere);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteAgriSuite(TTreeView *TV,int nF,
		CL_Agriculteur *fils,TTreeNode *tNFils)
{
	int j,nPf;
	ST_NoAgri *variante;
	CL_Agriculteur *petitFils;
	TTreeNode *tNPetitFils;
// utilisation de nF ?? il est dans agri->NoVariante
	tNPetitFils=TV->Items->AddChildObject(tNFils,nF,fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoAgri*)fils->LstVariante->Items[j];
		petitFils=variante->Agri;
		petitFils->NoVariante=nPf;
		CreeTVVarianteAgriSuite(TV,nPf,petitFils,tNPetitFils);
	}
	TV->Items->AddChildObject(tNPetitFils,"[...]",fils);
}
//-----------------------------------------------------------------------------
// GereAlea
/*
 CL_Vecteur<CL_Tendance>      *V_TendProd;
 CL_Vecteur<CL_Tendance>      *V_TendCharge;
 CL_Vecteur<CL_Tendance>      *V_ScenProd;
 CL_Vecteur<CL_Tendance>      *V_ScenCharge;
 PRIX
 Produits
 Tendance
 Scénario
 Charges
 Tendance
 Scénario
 QUANTITE
 Produits
 Tendance
 Scénario
 Charges
 Tendance
 Scénario
 Externalités
 Tendance
 Scénario

 */
void __fastcall TForme0Frm::CreeTVAleaPrix( TTreeView *TV)
{
	TTreeNode *tN0,*tN1,*tN2;
	AnsiString s;
	int i,j;
	CL_Tendance *tendance;
	int *nature;
	static int* lesNatures[4];
	static bool debut=true;
	if(debut==true)
	{
		nature=new int[4];
		lesNatures[0]=nature;
		nature[0]=PRIX;nature[1]=PRODUIT; nature[2]=TENDANCE;nature[3]=0;
		nature=new int[4];
		lesNatures[1]=nature;
		nature[0]=PRIX;nature[1]=PRODUIT; nature[2]=SCENARIO;nature[3]=0;
		nature=new int[4];
		lesNatures[2]=nature;
		nature[0]=PRIX;nature[1]=CHARGE; nature[2]=TENDANCE;nature[3]=0;
		nature=new int[4];
		lesNatures[3]=nature;
		nature[0]=PRIX;nature[1]=CHARGE; nature[2]=SCENARIO;nature[3]=0;
		debut =false;
	}
	TV->Visible=false;
	TV->Items->Clear();

	tN0=new TTreeNode(TV->Items);
//....Produits
	tN1=TV->Items->AddChild(tN0,"Produits");
	nature=lesNatures[0];
//    nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;
	tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendPrixProd->Nbelt;i++)
	{
		tendance=V_TendPrixProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
	if(nature[3]>0) tN2->Expand(false);

	nature=lesNatures[1];
	//nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=SCENARIO;
	tN2=TV->Items->AddChildObject(tN1,"Scénario",nature);
	for(i=0;i<V_ScenPrixProd->Nbelt;i++)
	{
		tendance=V_ScenPrixProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
	if(nature[3]>0) tN2->Expand(false);

	tN1->Expand(false);

//....Charges
	tN1=TV->Items->AddChild(tN0,"Charges");
	nature=lesNatures[2];
	//nature[0]=PRIX;nature[1]=CHARGE;nature[2]=TENDANCE;
	tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendPrixCharge->Nbelt;i++)
	{
		tendance=V_TendPrixCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
	if(nature[3]>0) tN2->Expand(false);

	nature=lesNatures[3];
	nature[0]=PRIX;nature[1]=CHARGE;nature[2]=SCENARIO;
	tN2=TV->Items->AddChildObject(tN1,"Scenario",nature);
	for(i=0;i<V_ScenPrixCharge->Nbelt;i++)
	{
		tendance=V_ScenPrixCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
	if(nature[3]>0) tN2->Expand(false);

	tN1->Expand(false);
//    tN2->Expand(false);

	TV->Visible=true;

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVAleaRdt( TTreeView *TV)
{
	TTreeNode *tN0,*tN1,*tN2;
	AnsiString s;
	int i,j;
	CL_Tendance *tendance;
	int *nature;
	static int* lesNatures[6];
	static bool debut=true;
	if(debut==true)
	{
		nature=new int[4];
		lesNatures[0]=nature;
		nature[0]=QUANTITE;nature[1]=PRODUIT; nature[2]=TENDANCE;nature[3]=0;

		nature=new int[4];
		lesNatures[1]=nature;
		nature[0]=QUANTITE;nature[1]=PRODUIT; nature[2]=SCENARIO;nature[3]=0;

		nature=new int[4];
		lesNatures[2]=nature;
		nature[0]=QUANTITE;nature[1]=CHARGE; nature[2]=TENDANCE;nature[3]=0;

		nature=new int[4];
		lesNatures[3]=nature;
		nature[0]=QUANTITE;nature[1]=CHARGE; nature[2]=SCENARIO;nature[3]=0;

		nature=new int[4];
		lesNatures[4]=nature;
		nature[0]=QUANTITE;nature[1]=EXTER; nature[2]=TENDANCE;nature[3]=0;

		nature=new int[4];
		lesNatures[5]=nature;
		nature[0]=QUANTITE;nature[1]=EXTER; nature[2]=SCENARIO;nature[3]=0;

		debut =false;
	}

	TV->Visible=false;
	TV->Items->Clear();

	tN0=new TTreeNode(TV->Items);
//QUANTITE
//....Produits
	tN1=TV->Items->AddChild(tN0,"Produits");
	nature=lesNatures[0];
	tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendQProd->Nbelt;i++)
	{
		tendance=V_TendQProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	nature=lesNatures[1];
	tN2=TV->Items->AddChildObject(tN1,"Scénario",nature);
	for(i=0;i<V_ScenQProd->Nbelt;i++)
	{
		tendance=V_ScenQProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
	tN1->Expand(false);

//....Charges
	tN1=TV->Items->AddChild(tN0,"Charges");
	nature=lesNatures[2];
	tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendQCharge->Nbelt;i++)
	{
		tendance=V_TendQCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	nature=lesNatures[3];
	tN2=TV->Items->AddChildObject(tN1,"Scenario",nature);
	for(i=0;i<V_ScenQCharge->Nbelt;i++)
	{
		tendance=V_ScenQCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	tN1->Expand(false);

//....Externalités
	tN1=TV->Items->AddChild(tN0,"Externalités");
	nature=lesNatures[4];

	tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendQExt->Nbelt;i++)
	{
		tendance=V_TendQExt->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	nature=lesNatures[5];
	tN2=TV->Items->AddChildObject(tN1,"Scenario",nature);
	for(i=0;i<V_ScenQExt->Nbelt;i++)
	{
		tendance=V_ScenQExt->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	tN1->Expand(false);

	TV->Visible=true;

}
//-----------------------------------------------------------------------------
// CheckListBox pour choisir les agri
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutAgri( TCheckListBox *ChLB)
{
	int n;
	CL_Agriculteur *agri;
	ChLB->Clear();
	for(n=0;n<V_Agriculteur->Nbelt;n++)
	{
		agri=V_Agriculteur->Vecteur[n];
		if(agri->EstVariante==true) continue;
		CreeLBToutAgriA(ChLB,agri);
	}
	for(n=0;n<ChLB->Items->Count;n++)
	{
		agri=(CL_Agriculteur*)ChLB->Items->Objects[n];
		if(EnsembleFrm->EstAffiche(agri)>0)
		ChLB->Checked[n]=true;
	}
}

// Variante Agri
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutAgriA(TCheckListBox *ChLB,CL_Agriculteur *agri)
{
	CL_Agriculteur *pere,*fils,*petitFils;
	AnsiString s;
	AnsiString nomAieul;
	char blanc[]="      ";
	int i,j,nF,nPf;
	ST_NoAgri *variante;

	pere=agri;
	nomAieul=pere->Nom;
	agri->NoVariante=0;
	ChLB->Items->AddObject(nomAieul,(TObject*)agri);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		nF=i+1;
		variante=(ST_NoAgri*)pere->LstVariante->Items[i];
		fils=variante->Agri;
		fils->NoVariante=nF;
		s=nomAieul + AnsiString(blanc)+AnsiString(nF); //200801
		ChLB->Items->AddObject(s,(TObject*)fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			nPf=nF*10+j+1;
			variante=(ST_NoAgri*)fils->LstVariante->Items[j];
			petitFils=variante->Agri;
			petitFils->NoVariante=nPf;
			CreeLBToutAgriB(ChLB,nomAieul,nPf,petitFils);
		}
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutAgriB(TCheckListBox *ChLB,AnsiString nomAieul,
		int nF,CL_Agriculteur *fils)
{
	int j,nPf;
	ST_NoAgri *variante;
	CL_Agriculteur *petitFils;
	AnsiString s,code;
	char blanc[]="      ";
	code=AnsiString(nF);
	s=nomAieul;
	for(int i=0;i<code.Length();i++)s=s+AnsiString(blanc);
	s=s+AnsiString(nF);
	ChLB->Items->AddObject(s,(TObject*)fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoAgri*)fils->LstVariante->Items[j];
		petitFils=variante->Agri;
		petitFils->NoVariante=nPf;
		CreeLBToutAgriB(ChLB,nomAieul,nPf,petitFils);
	}

}

///........
//-----------------------------------------------------------------------------
// CheckListBox pour choisir les ensembles
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutEnsemble( TCheckListBox *ChLB)
{
	int n;
	CL_Ensemble *ensemble;
	ChLB->Clear();
	for(n=0;n<V_Ensemble->Nbelt;n++)
	{
		ensemble=V_Ensemble->Vecteur[n];
		if(ensemble->EstVariante==true) continue;
		CreeLBToutEnsembleA(ChLB,ensemble);
	}
}

// Variante Ensemble
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutEnsembleA(TCheckListBox *ChLB,CL_Ensemble *ensemble)
{
	CL_Ensemble *pere,*fils,*petitFils;
	AnsiString s;
	AnsiString nomAieul;
	char blanc[]="      ";
	int i,j,nF,nPf;
	ST_NoEnsemble *variante;

	pere=ensemble;
	nomAieul=pere->Nom;
	ensemble->NoVariante=0;
	ChLB->Items->AddObject(nomAieul,(TObject*)ensemble);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		nF=i+1;
		variante=(ST_NoEnsemble*)pere->LstVariante->Items[i];
		fils=variante->Ensemble;
		fils->NoVariante=nF;
		s=nomAieul + AnsiString(blanc)+AnsiString(nF); //200801
		ChLB->Items->AddObject(s,(TObject*)fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			nPf=nF*10+j+1;
			variante=(ST_NoEnsemble*)fils->LstVariante->Items[j];
			petitFils=variante->Ensemble;
			petitFils->NoVariante=nPf;
			CreeLBToutEnsembleB(ChLB,nomAieul,nPf,petitFils);
		}
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutEnsembleB(TCheckListBox *ChLB,AnsiString nomAieul,
		int nF,CL_Ensemble *fils)
{
	int j,nPf;
	ST_NoAgri *variante;
	CL_Agriculteur *petitFils;
	AnsiString s,code;
	char blanc[]="      ";
	code=AnsiString(nF);
	s=nomAieul;
	for(int i=0;i<code.Length();i++)s=s+AnsiString(blanc);
	s=s+AnsiString(nF);
	ChLB->Items->AddObject(s,(TObject*)fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoAgri*)fils->LstVariante->Items[j];
		petitFils=variante->Agri;
		petitFils->NoVariante=nPf;
		CreeLBToutAgriB(ChLB,nomAieul,nPf,petitFils);
	}

}
///...
//-----------------------------------------------------------------------------
// Variante Ensemble
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteEnsemble( TTreeView *TV,CL_Ensemble *ens)
{
	TTreeNode *tNPere,*tNFils,*tNPetitFils;
	CL_Ensemble *pere,*fils,*petitFils;
	AnsiString s;
	int i,j,nF,nPf;
	ST_NoEnsemble *variante;
	TV->Items->Clear();

	pere=ens;
	ens->NoVariante=0;
	tNPere=new TTreeNode(TV->Items);
	tNFils=TV->Items->AddObject(tNPere,pere->Nom,ens);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		nF=i+1;
		variante=(ST_NoEnsemble*)pere->LstVariante->Items[i];
		fils=variante->Ensemble;
		fils->NoVariante=nF;
		tNPetitFils=TV->Items->AddChildObject(tNFils,nF,fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			nPf=nF*10+j+1;
			variante=(ST_NoEnsemble*)fils->LstVariante->Items[j];
			petitFils=variante->Ensemble;
			petitFils->NoVariante=nPf;
			CreeTVVarianteEnsembleSuite(TV,nPf,petitFils,tNPetitFils);
		}
		//if(fils->LstVariante->Count==0)
		TV->Items->AddChildObject(tNPetitFils,"[...]",fils);
	}
	TV->Items->AddChildObject(tNFils,"[...]",pere);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteEnsembleSuite(TTreeView *TV,int nF,
		CL_Ensemble *fils,TTreeNode *tNFils)
{
	int j,nPf;
	ST_NoEnsemble *variante;
	CL_Ensemble *petitFils;
	TTreeNode *tNPetitFils;
// utilisation de nF ?? il est dans ens->NoVariante
	tNPetitFils=TV->Items->AddChildObject(tNFils,nF,fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoEnsemble*)fils->LstVariante->Items[j];
		petitFils=variante->Ensemble;
		petitFils->NoVariante=nPf;
		CreeTVVarianteEnsembleSuite(TV,nPf,petitFils,tNPetitFils);
	}
	TV->Items->AddChildObject(tNPetitFils,"[...]",fils);

}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////////////////// GENERAL////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//complet  =false ne contient que les élements qui ont une valeur
//complet  =true  contient tout
//tVChoix->Tag=1  ne pas recréer tVChoix
//
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVToutElt(TTreeView *tVChoix,CL_Agriculteur *agri,
		bool complet)
{
//static bool debut=true;
	int i;
	TTreeNode *tnTout;
	TTreeNode *tnFamille,*tnCategorie,*tnItem;
	TTreeView *tTV;
	/** Initialisation : les premiers Elt sont des POSTE */
	int noFamille=POSTE;
	CL_Elt *elt;
	CL_Categorie *categorie=NULL;
	bool eltExiste;
//int n;
	/*
	 if(debut==true)
	 {
	 tnTout=new TTreeNode(tVChoix->Items);
	 debut=false;
	 }
	 */
	/*
	 // à chaque mise à jour de fichier purge de V_Elt
	 if(V_Elt->Nbelt==0)ES->IniV_Elt();
	 else if(tVChoix->Tag==1) return;

	 // a voir pour éviter de faire n fois les memes calculs
	 //if(AgriEnCours) AgriSaisieFrm->Calcul(AgriEnCours);
	 */
	//ES->IniV_Elt(); doit etre appele avant d'utilise CreeTVToutElt
	Agri=agri;
	if(Agri)
	{
		PProd= Agri->DefSim->TPProd;
		PCharge= Agri->DefSim->TPCharge;
	}

	tVChoix->Items->Clear();

	tnTout=new TTreeNode(tVChoix->Items);
	tnItem=tVChoix->Items->Add(tnTout,"Postes");

	/** On balaye le V_Elt */
	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		/** Cet éléments est présent chez notre agriculteur ? */
		eltExiste=CompleteElt(elt);

		/** Si on ne veut pas une liste exhaustive des Elt
		 et l'Elt n'est pas présent chez l'agriculteur,
		 on passe au suivant */
		if(complet==false && eltExiste==false) continue;

		/** Si notre Elt a une catégorie -- y-a-t-il des Elt sans cat ? */
		if(elt->Categorie)
		{
			/** On a changé de famille */
			if(elt->NoFamille!=noFamille)
			{
				/** On crée un nouveau noeud de famille à la racine
				 qui a le nom du Poste */
				tnFamille=tVChoix->Items->AddChild(tnTout,elt->Poste->Nom);
				/** Pointeur courant sur famille actualisé */
				noFamille=elt->NoFamille;
			}
			/** On a changé de catégorie */
			if(elt->Categorie!=categorie)
			{
				/** Nouveau noeud de catégorie sous la famille courante */
				tnCategorie=tVChoix->Items->AddChild(tnFamille,elt->Categorie->Nom);
				categorie=elt->Categorie;
			}
			/** On accroche un noeud pour un Elt sous sa catégorie */
			tVChoix->Items->AddChildObject(tnCategorie,elt->Nom,elt);
		}
		else
		/** Pas de catégorie !!!
		 cas probable : Externalités
		 à terme : à supprimer */
		{
			if(elt->NoFamille!=noFamille)
			{
				/** On accroche le noeud Famille à la racine */
				tnItem=tVChoix->Items->AddChild(tnTout,elt->Poste->Nom);
				noFamille=elt->NoFamille;
			}
			tVChoix->Items->AddChildObject(tnItem,elt->Nom,elt);
		}
	}
	/*
	 //test                          261101
	 int j,k;
	 AnsiString asF,asC,asI;
	 for(i=0;i<tVChoix->Items->Count;i++)
	 {
	 tnFamille=tVChoix->Items->Item[i];//ok
	 asF=tnFamille->Text;
	 for(j=0;j<tnFamille->Count;j++)
	 {
	 tnCategorie=tnFamille->Item[j];
	 asC=tnCategorie->Text;
	 for(k=0;k<tnCategorie->Count;k++)
	 {
	 tnItem=tnCategorie->Item[k];
	 asI=tnItem->Text;
	 elt=(CL_Elt*)tnItem->Data;
	 }
	 }
	 }
	 //fin test
	 */
	V_Elt->Flag=true;
	tVChoix->Tag=1; //les adresses ont été mises
	delete tnTout;
}
//---------------------------------------------------------------------------
/** Accroche aux Elt de V_Elt les Valeurs éparpillées dans :
 Agri, AgriRes
 */
bool __fastcall TForme0Frm::CompleteElt( CL_Elt *elt)
{
	bool enValeur;
	CL_Vecteur<CL_QuanVal> *vQuanVal;
//CL_Vecteur<CL_Formule> *vFormule;
	CL_Vecteur<CL_Item> *vItem;
	CL_QuanVal *quanVal;
	CL_Valeur *valeur;
	CL_Formule *formule;
	CL_Indicateur *indic;
	CL_Item *item;
	CL_Agriculteur *agriTest;
	// mystère Agri a été initialisé dans CreeTVToutElt
	// cette affectation ne devrait pas etre nécessaire!!!
	// elle est idiote!
	Agri=Forme0Frm->Agri;

	if(Agri==NULL) return false;

	if(elt->NoFamille==FORME) return false;

	if(elt->NoFamille==POSTE)
	{
		switch(elt->NoItem)
		{
			case PRODUIT: elt->Valeur=Agri->Resultat->Produit;break;
			case CHARGE: elt->Valeur=Agri->Resultat->Charge;break;
			case MARGE: elt->Valeur=Agri->Resultat->Marge;break;
			case CHSTRUCT: elt->Valeur=Agri->Resultat->ChStruct;break;
			case RECDIV: elt->Valeur=Agri->Resultat->RecDiv;break;
			case DEPDIV: elt->Valeur=Agri->Resultat->DepDiv;break;
			case RECFAM: elt->Valeur=Agri->Resultat->RecFam;break;
			case DEPFAM: elt->Valeur=Agri->Resultat->DepFam;break;
			case SOLDE: elt->Valeur=Agri->Resultat->Solde;break;
			case SOLDECUMUL: elt->Valeur=Agri->Resultat->SoldeCumul;break;
			default:
			ShowMessage("CompleteElt 1 Oubli");
			elt->Valeur=ValZero;
		}
		return true;
	}
	if(elt->NoFamille==VARIABLE)
	{
		for(int i=0;i<Agri->V_Variable->Nbelt;i++)
		{
			valeur=Agri->V_Variable->Vecteur[i];
			item=valeur->Item;
			if(item->No==elt->NoItem && item->NoCategorie==elt->NoCategorie)
			{
				elt->Valeur=valeur->Valeur;
				return true;
			}
		}
		elt->Valeur=ValZero; return false;
	}
	// a ce stade les indicateurs doivent avoir été calculés
	if(elt->NoFamille==INDIC)
	{
		for(int i=0;i<V_Indicateur->Nbelt;i++)
		{
			indic=V_Indicateur->Vecteur[i];
			if(indic->No==elt->NoItem && indic->NoCategorie==elt->NoCategorie)
			{
				elt->Valeur=indic->Valeur;
				return true;
			}
		}
		elt->Valeur=ValZero; return false;
	}
	if(elt->NoFamille==PPRODUIT)
	{
		item=V_Produit->trouve(elt->NoItem);
		if(item==NULL) {elt->Valeur=ValZero; return false;}
		else
		{
			if(elt->Valeur==NULL)
			elt->Valeur=new float[N_X];
			elt->Pcent=trouveDelta(item,PProd);
			if(elt->Pcent==NULL)
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix;
			else
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix*elt->Pcent[i];
			return true;
		}
	}

	if(elt->NoFamille==PCHARGE)
	{
		item=V_Charge->trouve(elt->NoItem);
		if(item==NULL) {elt->Valeur=ValZero; return false;}
		else
		{
			if(elt->Valeur==NULL)
			elt->Valeur=new float[N_X];
			elt->Pcent=trouveDelta(item,PCharge);
			if(elt->Pcent==NULL)
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix;
			else
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix*elt->Pcent[i];
			return true;
		}
	}

	vQuanVal=NULL;
	switch (elt->NoFamille)
	{
		//valeur
		case PRODUIT: vQuanVal=Agri->Resultat->V_Produit; enValeur=true;break;
		case CHARGE: vQuanVal=Agri->Resultat->V_Charge; enValeur=true;break;

		case CHSTRUCT: vQuanVal=Agri->Resultat->V_ChStruct; enValeur=true;break;
		case RECDIV: vQuanVal=Agri->Resultat->V_RecDiv; enValeur=true;break;
		case DEPDIV: vQuanVal=Agri->Resultat->V_DepDiv; enValeur=true;break;
		case RECFAM: vQuanVal=Agri->Resultat->V_RecFam; enValeur=true;break;
		case DEPFAM: vQuanVal=Agri->Resultat->V_DepFam; enValeur=true;break;

		//quantité
		case EXTPOS: vQuanVal=Agri->Resultat->V_ExtPos; enValeur=false;break;
		case EXTNEG: vQuanVal=Agri->Resultat->V_ExtNeg; enValeur=false;break;
		case QPRODUIT: vQuanVal=Agri->Resultat->V_Produit; enValeur=false;break;
		case QCHARGE: vQuanVal=Agri->Resultat->V_Charge; enValeur=false;break;

		default:ShowMessage("CompleteElt 2 Oubli");
	}
	if(vQuanVal)
	{
		quanVal=vQuanVal->trouve(elt->NoItem);
		if(quanVal==NULL) {elt->Valeur=ValZero; return false;}
		else
		{
			if(enValeur==true)
			{
				elt->Valeur=quanVal->Val;
				return true;
			}
			else
			{
				elt->Valeur=quanVal->Qte;
				return true;
			}
		}
	}
	return false; //aew
}
//---------------------------------------------------------------------------
float* __fastcall TForme0Frm:: trouveDelta(CL_Item *item,CL_Tendance *tendance)
{
	int i;
	CL_Delta *delta;

	if ( tendance==NULL) return NULL;

	for(i=0;i<tendance->V_Delta->Nbelt;i++)
	{
		delta=tendance->V_Delta->Vecteur[i];
		if(delta->Item==item)
		{
			return delta->Pcent;
		}
	}
	return NULL;
}

//---------------------------------------------------------------------------
/*
 Forme0
 Forme00
 SysUnite
 Espece
 Produit
 Charge
 Eau
 Fruit
 Categories
 RecDepAutre
 Structure
 Etat
 Famille
 Zone
 Externalite
 Forme000
 Animal
 Cultures
 Agriculteur

 */

