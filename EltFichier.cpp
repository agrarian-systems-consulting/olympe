//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdarg.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "Brouillon.h"

//extern
#include "LesVecteurs.hse"
#include "Olympe.hse"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
 class CL_Elt
 {
 public:
 CL_Elt(void){};
 CL_Elt(CL_Poste *poste);
 CL_Elt(CL_Poste *poste,CL_Categorie *categorie,CL_Item *item);
 CL_Elt(CL_Poste *poste,CL_Categorie *categorie,CL_Indicateur *indic);
 CL_Elt(CL_Poste *poste,CL_Item *item);
 CL_Elt(int type);    //pour mise en forme :trait blanc
 ~CL_Elt(void){};
 //....
 int           No;
 int           Cmp(CL_Elt *ptr){ return 0;};//non utilisé
 char          Flag;
 int           NoFamille;      //PRODUIT CHARGE RECDIV...
 int           NoCategorie;    //seult pour produit charge irrigation
 int           NoItem;
 int           NoIndic;
 CL_Poste      *Poste;
 CL_Item       *Item;
 CL_Indicateur *Indic;
 CL_Categorie  *Categorie;
 char          *Nom;
 char          *NomCat;
 char          *NomFamille;
 float        *Valeur;
 float         VMin,VMax;
 };
 */
//---------------------------------------------------------------------------------
// IniV_Poste appelé par Main
// postes calculés ce sont des totaux
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_Poste(void)
{
	CL_Poste *poste;
	V_Poste->purge();
	//                  Nom                   No
	poste=new CL_Poste("Produits", PRODUIT); V_Poste->insSans(poste);
	poste=new CL_Poste("Charges Ope", CHARGE); V_Poste->insSans(poste);
	poste=new CL_Poste("Marge", MARGE); V_Poste->insSans(poste);
	poste=new CL_Poste("Ch_structure", CHSTRUCT); V_Poste->insSans(poste);
	poste=new CL_Poste("Recettes_Diverses", RECDIV); V_Poste->insSans(poste);
	poste=new CL_Poste("Dépenses_Diverses", DEPDIV); V_Poste->insSans(poste);
	poste=new CL_Poste("Recettes_Familiales",RECFAM); V_Poste->insSans(poste);
	poste=new CL_Poste("Dépenses_Familiales",DEPFAM); V_Poste->insSans(poste);
//	poste=new CL_Poste("Primes",             PRIME);     V_Poste->insSans(poste);
//	poste=new CL_Poste("Taxes",              TAXE);      V_Poste->insSans(poste);
}
//---------------------------------------------------------------------------
// appelé par Main
//            Forme0->CreeTVToutElt
// à chaque mise à jour de fichier V_Elt->purge
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_Elt(void)
{
	static bool estInitialise=false;
	static CL_Poste *PVariable,*PIndic,*PExtPos,*PExtNeg;
	static CL_Poste *PQProduit,*PQCharge; //Quantite
	static CL_Poste *PPProduit,*PPCharge;//Prix

	CL_Elt *elt;
	CL_Poste *poste;
	int i;
//char chaine[120];
	//si modif voir AgriSaisie
	if(estInitialise==false)
	{
		estInitialise=true;
		PVariable= new CL_Poste("Variables", VARIABLE);
		PIndic= new CL_Poste("Indicateurs", INDIC);
		PExtPos= new CL_Poste("Ext_Pos", EXTPOS);
		PExtNeg= new CL_Poste("Ext_Neg", EXTNEG);
		PQProduit= new CL_Poste("Q_Produit", QPRODUIT);
		PQCharge= new CL_Poste("Q_Charge", QCHARGE);
		PPProduit= new CL_Poste("P_Produit", PPRODUIT);
		PPCharge= new CL_Poste("P_Charge", PCHARGE);
	}
	V_Elt->purge();
	for(i=0;i<V_Poste->Nbelt;i++)
	{
		poste=V_Poste->Vecteur[i];
		elt=new CL_Elt(poste);
		elt->NomFamille="Poste";
		elt->NomCat="";
		V_Elt->ins(elt);
	}
	IniV_EltItem(PRODUIT, V_Produit, V_CatProduit);
	IniV_EltItem(CHARGE , V_Charge, V_CatCharge);
	//Externalite
	IniV_EltExter(PExtPos,V_Externalite,V_CatExternalite);
	IniV_EltExter(PExtNeg,V_Externalite,V_CatExternalite);

	IniV_EltItem(CHSTRUCT,CHSTRUCT,V_DepDiv, V_CatDepEnt);
	IniV_EltItem(DEPDIV, DEPDIV, V_DepDiv, V_CatDepEnt);
//    IniV_EltItem(TAXE,    TAXE,    V_DepEnt,    V_CatDepEnt);

	IniV_EltItem(RECDIV, RECDIV, V_RecDiv, V_CatRecEnt);
//    IniV_EltItem(PRIME,   PRIME,   V_RecEnt,    V_CatRecEnt);

	IniV_EltItem(RECFAM, RECFAM, V_RecFam, V_CatRecFam);
	IniV_EltItem(DEPFAM, DEPFAM, V_DepFam, V_CatDepFam);

	IniV_EltItem(PVariable, V_Variable, V_CatVar);
	IniV_EltIndicateur (PIndic, V_Indicateur,V_CatIndic);
	//Quantites
	IniV_EltItem(PQProduit, V_Produit, V_CatProduit);
	IniV_EltItem(PQCharge, V_Charge, V_CatCharge);
	//Prix
	IniV_EltItem(PPProduit, V_Produit, V_CatProduit);
	IniV_EltItem(PPCharge, V_Charge, V_CatCharge);

	V_Elt->Flag=true;
//   ImpV_Elt();
}
// V_Produit V_Charge V_Variable
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltItem(int noPoste,CL_Vecteur<CL_Item>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)
{
	CL_Poste *poste;
	CL_Elt *elt;
	CL_Item *item;
	CL_Categorie *categorie;
	int i,c;
	poste=V_Poste->trouve(noPoste);
	for(c=0;c<vCat->Nbelt;c++)
	{
		categorie=vCat->Vecteur[c];
		for(i=0;i<vecteur->Nbelt;i++)
		{
			item=vecteur->Vecteur[i];
			if(item->NoCategorie != categorie->No)continue;
			elt=new CL_Elt(poste,categorie,item);
			V_Elt->ins(elt);
		}
	}
}
//V_DepEnt V_RecEnt V_RecFam V_DepFam
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltItem(int noPoste,int noCat,CL_Vecteur<CL_Item>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)
{
	CL_Poste *poste;
	CL_Elt *elt;
	CL_Item *item;
	CL_Categorie *categorie;
	int i;
	poste=V_Poste->trouve(noPoste);
	categorie=vCat->trouve(noCat);
	for(i=0;i<vecteur->Nbelt;i++)
	{
		item=vecteur->Vecteur[i];
		if(item->NoCategorie != categorie->No)continue;
		elt=new CL_Elt(poste,categorie,item);
		V_Elt->ins(elt);
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltItem(CL_Poste *poste,CL_Vecteur<CL_Item>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)

{
	CL_Elt *elt;
	CL_Item *item;
	CL_Categorie *categorie;
	for(int c=0;c<vCat->Nbelt;c++)
	{
		categorie=vCat->Vecteur[c];
		for(int i=0;i<vecteur->Nbelt;i++)
		{
			item=vecteur->Vecteur[i];
			if(item->NoCategorie != categorie->No)continue;
			elt=new CL_Elt(poste,categorie,item);
			V_Elt->ins(elt);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltExter(CL_Poste *poste,CL_Vecteur<CL_Item>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)

{
	CL_Elt *elt;
	CL_Item *item;
	CL_Categorie *categorie;
	for(int c=0;c<vCat->Nbelt;c++)
	{
		categorie=vCat->Vecteur[c];
		if(categorie->No!=poste->No)continue;
		for(int i=0;i<vecteur->Nbelt;i++)
		{
			item=vecteur->Vecteur[i];
			if(item->NoCategorie != categorie->No)continue;
			elt=new CL_Elt(poste,categorie,item);
			V_Elt->ins(elt);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltIndicateur(CL_Poste *poste,CL_Vecteur<CL_Indicateur>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)

{
	CL_Elt *elt;
	CL_Indicateur *indic;
	CL_Categorie *categorie;
	for(int c=0;c<vCat->Nbelt;c++)
	{
		categorie=vCat->Vecteur[c];
		for(int i=0;i<vecteur->Nbelt;i++)
		{
			indic=vecteur->Vecteur[i];
			if(indic->NoCategorie != categorie->No)continue;
			elt=new CL_Elt(poste,categorie,indic);
			V_Elt->ins(elt);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::ImpV_Elt(void)
{
	int i;
	CL_Elt *elt;
	char chaine[100];
	FBrouillon->Demarre();
	FBrouillon->Memo1->Lines->Add("    N°Famille");
	FBrouillon->Memo1->Lines->Add("          N°Categorie");
	FBrouillon->Memo1->Lines->Add("              N°Item");

	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		sprintf(chaine,"%3d %3d %3d %3d %-10.10s %-20.20s %-20.20s",
				i,
				elt->NoFamille,
				elt->NoCategorie,
				elt->NoItem,
				elt->Nom,
				elt->NomCat,
				elt->NomFamille);
		FBrouillon->Memo1->Lines->Add(chaine);
	}
	/*
	 FBrouillon->Memo1->Lines->Add("V_SystemeUnite     "+AnsiString(V_SystemeUnite->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Tva              "+AnsiString(V_Tva         ->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatProduit       "+AnsiString(V_CatProduit->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatExternalite   "+AnsiString(V_CatExternalite->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatCulture       "+AnsiString(V_CatCulture->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatAnimaux       "+AnsiString(V_CatAnimaux->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatVivrier       "+AnsiString(V_CatVivrier->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatDepEnt        "+AnsiString(V_CatDepEnt->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatRecEnt        "+AnsiString(V_CatRecEnt->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatDepFam        "+AnsiString(V_CatDepFam->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatRecFam        "+AnsiString(V_CatRecFam->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatTypeZone      "+AnsiString(V_CatTypeZone->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatIndic         "+AnsiString(V_CatIndic->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_CatEtatSortie    "+AnsiString(V_CatEtatSortie->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Produit          "+AnsiString(V_Produit->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Charge           "+AnsiString(V_Charge->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Externalite      "+AnsiString(V_Externalite->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Culture          "+AnsiString(V_Culture->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Animaux          "+AnsiString(V_Animaux->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Vivrier          "+AnsiString(V_Vivrier->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Espece           "+AnsiString(V_Espece->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_Perenne          "+AnsiString(V_Perenne->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_RecEnt           "+AnsiString(V_RecEnt->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_DepEnt           "+AnsiString(V_DepEnt->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_RecFam           "+AnsiString(V_RecFam->NoX ));
	 FBrouillon->Memo1->Lines->Add("V_DepFam           "+AnsiString(V_DepFam->NoX ));
	 //    /*
	 FBrouillon->Memo1->Lines->Add("                   "+AnsiString(              ->NoX ));
	 FBrouillon->Memo1->Lines->Add("                   "+AnsiString(              ->NoX ));
	 FBrouillon->Memo1->Lines->Add("                   "+AnsiString(              ->NoX ));
	 */
	FBrouillon->Show();
}

