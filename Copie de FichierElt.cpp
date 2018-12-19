//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "TitreFrancais.h"

//#include "Brouillon.h"
#include "SortieEcran.h"

#include "Forme0.h"

//extern
#include "LesVecteurs.hse"
#include "Olympe.hse"

//extern char *LesTitresBilan[23];

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
 //---------------------------------------------------------------------------
 class CL_Elt
 {
 public:
 CL_Elt(void);
 CL_Elt(CL_Elt *elt);
 CL_Elt(CL_Poste *poste);
 CL_Elt(CL_Poste *poste,CL_Categorie *categorie,CL_Item *item);
 CL_Elt(CL_Poste *poste,int noType,CL_Categorie *categorie,CL_Item *item);
 CL_Elt(CL_Poste *poste,CL_Categorie *categorie,CL_Indicateur *indic);
 CL_Elt(CL_Poste *poste,CL_Categorie *categorie,CL_Atelier *atelier);
 CL_Elt(CL_Poste *poste,CL_Espece    *espece,   CL_Atelier *atelier);
 CL_Elt(CL_Poste *poste,char *nom, int no);

 CL_Elt(CL_Poste *poste,CL_Item *item);
 CL_Elt(CL_Poste *poste,CL_Categorie *categorie);
 CL_Elt(int type);    //pour mise en forme :trait blanc
 ~CL_Elt(void);
 AnsiString Donne_Nom();
 //    AnsiString Donne_Unite();
 char* Donne_Unite();
 AnsiString NomTypeMvtAni(int noType);
 //....
 int            No;
 int            Cmp(CL_Elt *ptr){ return 0;};//non utilisé
 char           Flag;
 int            NoFamille;      //PRODUIT CHARGE RECDIV...INDIC  cf olympedec.h
 int            NoCategorie;    //seult pour produit charge
 int            NoType;         //seult pour animaux EFF EFFV EFFA VALV VALA VALINV
 int            NoItem;
 int            NoEspece;
 int            NoEtat;
 CL_Poste       *Poste;
 CL_Item        *Item;
 CL_EtatSortie  *Etat;
 CL_Categorie   *Categorie;
 CL_Espece      *Espece;
 char           *Nom;
 char           *NomCat;
 char           *NomFamille;
 char           *Unite;
 float          *Valeur;
 float          *Pcent;
 float          VMin,VMax;
 float          *Passe;
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
	//                  Nom                   NoPoste
	poste=new CL_Poste("Recettes Produits", PRODUIT, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Dépenses Appro", CHARGE, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Marge", MARGE, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Ch_structure", CHSTRUCT,true); V_Poste->insSans(poste);
	poste=new CL_Poste("Recettes_Diverses", RECDIV, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Dépenses_Diverses", DEPDIV, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Recettes_Familiales",RECFAM, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Dépenses_Familiales",DEPFAM, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Solde", SOLDE, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Solde Cumul", SOLDECUMUL, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Résultat", RESULTAT, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Ebe", EBE, true); V_Poste->insSans(poste);
	poste=new CL_Poste("Caf", CAF, true); V_Poste->insSans(poste);

	poste=new CL_Poste("Bilan", BILAN, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Ceg", CEG, false); V_Poste->insSans(poste);

	poste=new CL_Poste("Variables", VARIABLE, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Indicateurs", INDIC, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Ext. Positive", EXTPOS, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Ext. Négative", EXTNEG, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Quant Produit", QPRODUIT, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Quant Charge", QCHARGE, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Prix Produit", PPRODUIT, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Prix Charge", PCHARGE, false); V_Poste->insSans(poste);

	poste=new CL_Poste("Immobilisation", IMMO, false); V_Poste->insSans(poste);

	poste=new CL_Poste("Emprunt", EMP, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Emprunt LT", EMPLT, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Emprunt CT", EMPCT, false); V_Poste->insSans(poste);

	poste=new CL_Poste("Cultures", CULTURE, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Pérennes", PERENNE, false); V_Poste->insSans(poste);
	poste=new CL_Poste("PluriAnnuelle", VIVRIER, false); V_Poste->insSans(poste);
	poste=new CL_Poste("Animaux", ANIMAUX, false); V_Poste->insSans(poste);
	//030303
	poste=new CL_Poste("Mvt Animaux", MVT, false); V_Poste->insSans(poste);
}

//---------------------------------------------------------------------------
// appelé par Main
//
// à chaque mise à jour de fichier V_Elt->purge
// je cree des elt et je les range dans V_Elt
// mais elt->Valeur n'est pas défini
// il le sera dans  Forme0->CreeTVToutElt
//  ou directement par appel à CompleteElt(CL_Elt *elt) cf Forme0
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_Elt(void)
{
	CL_Elt *elt;
	CL_Poste *poste;
	int i;
	// pour les prix des produits et des charges j'ai alloué de la place
	//cf Forme0  CompleteElt
	// d'abord je delete les valeurs si je les ai alloués

	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		if( elt->NoFamille== PPRODUIT
				|| elt->NoFamille== PCHARGE
				||elt->NoFamille== CULTURE
				||elt->NoFamille== PERENNE
				||elt->NoFamille== VIVRIER
				||elt->NoFamille== ANIMAUX) //030303

		{
			if(elt->Valeur)
			{
				if(elt->Valeur!=Forme0Frm->ValZero)
				{
					delete []elt->Valeur;
					elt->Valeur=NULL;
				}
			}
		}
	}
	//puis je delete tous les elt
	V_Elt->purge();

	for(i=0;i<V_Poste->Nbelt;i++)
	{
		poste=V_Poste->Vecteur[i];
		if(poste->Aff==false) continue;

		elt=new CL_Elt(poste);
		elt->NomFamille="Poste";
		elt->NomCat="";
		V_Elt->ins(elt);
	}
	IniV_EltBilan();
	IniV_EltCeg();
	IniV_EltItem (PRODUIT, V_Produit, V_CatProduit);
	IniV_EltItem (CHARGE, V_Charge, V_CatCharge);

	IniV_EltExter (EXTPOS, V_Externalite,V_CatExternalite);
	IniV_EltExter (EXTNEG, V_Externalite,V_CatExternalite);

	IniV_EltItem (CHSTRUCT, V_ChStruct, V_CatChStruct);
	IniV_EltItem (DEPDIV, V_DepDiv, V_CatDepDiv);
	IniV_EltItem (RECDIV, V_RecDiv, V_CatRecDiv);

	IniV_EltItem (RECFAM, V_RecFam, V_CatRecFam);
	IniV_EltItem (DEPFAM, V_DepFam, V_CatDepFam);

	IniV_EltItem (VARIABLE, V_Variable, V_CatVar);
	IniV_EltIndicateur (INDIC, V_Indicateur, V_CatIndic);
	//Quantites
	IniV_EltItem (QPRODUIT, V_Produit, V_CatProduit);
	IniV_EltItem (QCHARGE, V_Charge, V_CatCharge);
	//Prix
	IniV_EltItem (PPRODUIT, V_Produit, V_CatProduit);
	IniV_EltItem (PCHARGE, V_Charge, V_CatCharge);
	//160102
	//Immo
	IniV_EltImmo();

	IniV_EltEmp (EMP);
	IniV_EltEmp (EMPLT);
	IniV_EltEmp (EMPCT);
	//190102
	//surface
	IniV_EltSurface();//y compris animaux sauf mouvement
	//animaux
	IniV_EltAnimaux ( );// seulement mouvement
	V_Elt->Flag=true;
//   TEST
//ImpV_Elt();    //IMPRESSION pour Test
}
//Bilan
/*
 CompleteV_Elt a besoin de NoFamille=BILAN
 NoItem
 */
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltBilan(void)
{
	CL_Poste *poste;
	CL_Elt *elt;
	poste=V_Poste->trouve(BILAN);

	elt=new CL_Elt(poste, LesTitresBilan[0], 0); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[1], 1); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[2], 2); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[3], 3); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[4], 4); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[5], 5); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[6], 6); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[7], 7); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[8], 8); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[9], 9); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[10],10); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[11],11); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[12],12); V_Elt->ins(elt);
	//PASSIF 13
	elt=new CL_Elt(poste, LesTitresBilan[14],14); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[15],15); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[16],16); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[17],17); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[18],18); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[19],19); V_Elt->ins(elt);

	elt=new CL_Elt(poste, LesTitresBilan[20],20); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[21],21); V_Elt->ins(elt);
	elt=new CL_Elt(poste, LesTitresBilan[22],22); V_Elt->ins(elt);

}
//Ceg
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltCeg(void)
{
	CL_Poste *poste;
	CL_Elt *elt;
	poste=V_Poste->trouve(CEG);
	elt=new CL_Elt(poste,"Produits", 0);V_Elt->ins(elt);

	elt=new CL_Elt(poste,"Recettes", 1);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Recettes Diverses", 2);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Var. Stock", 3);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Var. stock en terre", 4);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Var. inv animal Repro", 5);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Var. inv animal Autre", 6);V_Elt->ins(elt);

	elt=new CL_Elt(poste,"Produits financiers", 7);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Production d'immo", 8);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Cession d'actif", 9);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Perte Exceptionnelle", 10);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Amortissement Subvention", 11);V_Elt->ins(elt);

	elt=new CL_Elt(poste,"Charges", 12);V_Elt->ins(elt);

	elt=new CL_Elt(poste,"Dépenses Exploitation", 13);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Dépenses Diverses", 14);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Val comptable cession", 15);V_Elt->ins(elt);

	elt=new CL_Elt(poste,"Charges de Structure", 16);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Amortissement Immo", 17);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Amortissement Plantation", 18);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Frais fin LT", 19);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Frais fin CT", 20);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Frais fin OCCC", 21);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Autres Ch Struct", 22);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Résultat", 23);V_Elt->ins(elt);
	/*

	 elt=new CL_Elt(poste,"Produits",                 resultat->totProduit);

	 elt=new CL_Elt(poste,"Recettes",                 resultat->Produit);
	 elt=new CL_Elt(poste,"Recettes Diverses",        resultat->RecDiv);
	 elt=new CL_Elt(poste,"Var. Stock",               resultat->deltaStock);
	 elt=new CL_Elt(poste,"Var. stock en terre",      resultat->deltaAvance);
	 elt=new CL_Elt(poste,"Var. inv animal Repro",    resultat->deltaVarInvAniRepro);
	 elt=new CL_Elt(poste,"                Autre",    resultat->deltaVarInvAniAutre);

	 elt=new CL_Elt(poste,"Produits financiers",       resultat->PlactE->Interet);
	 elt=new CL_Elt(poste,"Production d'immo",         resultat->ProdImmo);
	 elt=new CL_Elt(poste,"Cession d'actif",           resultat->ImmoTotal->Vente);
	 elt=new CL_Elt(poste,"Perte Exceptionnelle",      resultat->PertePlant);
	 elt=new CL_Elt(poste,"Amortissement Subvention",  resultat->TotSub->Amor);


	 elt=new CL_Elt(poste,"Charges",                resultat->totDepense);

	 elt=new CL_Elt(poste,"Dépenses Exploitation",    resultat->Charge);
	 elt=new CL_Elt(poste,"Dépenses Diverses",        resultat->DepDiv);
	 elt=new CL_Elt(poste,"Val comptable cession",    resultat->ImmoTotal->ValCompta);

	 elt=new CL_Elt(poste,"Charges de Structure",   resultat->totChStruct);
	 elt=new CL_Elt(poste,"Amortissement Immo",       resultat->ImmoTotal->Amor);
	 elt=new CL_Elt(poste,"Amortissement Plantation", resultat->AmorPlant);
	 elt=new CL_Elt(poste,"Frais fin LT",             resultat->EmpLTE->Interet);
	 elt=new CL_Elt(poste,"Frais fin CT",             resultat->EmpCTE->Interet);
	 elt=new CL_Elt(poste,"Frais fin OCCC",           resultat->FraisOccc);
	 elt=new CL_Elt(poste,"Autres Ch Struct",         resultat->ChStruct);
	 elt=new CL_Elt(poste,"Résultat",                 resultat->resExercice,clRed);

	 */
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
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltAnimaux(void)
{
	CL_Poste *poste;
	CL_Elt *elt;
	CL_Item *item;
	CL_Categorie *categorie;
	int noType;
	int i,c;
	poste=V_Poste->trouve(MVT);
	for(c=0;c<V_CatBestiaux->Nbelt;c++)
	{
		categorie=V_CatBestiaux->Vecteur[c];
		for(noType=EFF;noType<=VALINV;noType++)
		{
			for(i=0;i<V_Bestiaux->Nbelt;i++)
			{
				item=V_Bestiaux->Vecteur[i];
				if(item->NoCategorie != categorie->No)continue;
				{
					elt=new CL_Elt(poste,noType,categorie,item);
					V_Elt->ins(elt);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltExter(int noPoste,CL_Vecteur<CL_Item>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)

{
	CL_Poste *poste;
	CL_Elt *elt;
	CL_Item *item;
	CL_Categorie *categorie;
	poste=V_Poste->trouve(noPoste);
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
void __fastcall CL_ES::IniV_EltIndicateur(int noPoste,CL_Vecteur<CL_Indicateur>*vecteur,
		CL_Vecteur<CL_Categorie>*vCat)

{
	CL_Poste *poste;
	CL_Elt *elt;
	CL_Indicateur *indic;
	CL_Categorie *categorie;
	poste=V_Poste->trouve(noPoste);
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
void __fastcall CL_ES::IniV_EltImmo(void)
{
	CL_Poste *poste;
	CL_Elt *elt;

	poste=V_Poste->trouve(IMMO);
	elt=new CL_Elt(poste,"Amortissement", AMOR);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Val Résiduelle", VALRESID);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Achat", VALACHAT);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Val Brute", VALBRUT);V_Elt->ins(elt);
	/*
	 elt->Poste=poste;
	 elt->NomFamille=poste->Nom.c_str();
	 elt->NomCat="";
	 elt->Nom="Amortissement";

	 elt->NoFamille=poste->No;
	 elt->Categorie=NULL;
	 elt->NoItem=1;    //AMOR
	 V_Elt->ins(elt);
	 */
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltEmp(int nature)
{
	CL_Poste *poste;
	CL_Elt *elt;

	poste=V_Poste->trouve(nature);
	elt=new CL_Elt(poste,"Annuités", ANNUITE);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Cap Remboursé", REMB); V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Interet", INTERET);V_Elt->ins(elt);
	elt=new CL_Elt(poste,"Nouveaux", NOUVEMP);V_Elt->ins(elt);
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltSurface(void)
{
	CL_Poste *poste;

	poste=V_Poste->trouve(CULTURE); //principal:derobe=false puis derobe=true 
	IniV_EltSurface2(poste, V_CatCulture,V_Culture,false);
	IniV_EltSurface2(poste, V_CatCulture,V_Culture,true);

	poste=V_Poste->trouve(PERENNE);
	IniV_EltSurfacePerenne(poste,false);
	IniV_EltSurfacePerenne(poste,true);

	poste=V_Poste->trouve(VIVRIER);
	IniV_EltSurface2(poste, V_CatVivrier,V_Vivrier,false);
	IniV_EltSurface2(poste, V_CatVivrier,V_Vivrier,true);

	poste=V_Poste->trouve(ANIMAUX);
	IniV_EltSurface2(poste, V_CatAnimaux,V_Animaux,false);
	IniV_EltSurface2(poste, V_CatAnimaux,V_Animaux,true);
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltSurface2(
		CL_Poste *poste,
		CL_Vecteur<CL_Categorie> *vCat,
		CL_Vecteur<CL_Atelier> *vAtelier,
		bool derobe)
{
	CL_Categorie *categorie;
	CL_Atelier *atelier;
	CL_Elt *elt;

	for(int c=0;c<vCat->Nbelt;c++)
	{
		categorie=vCat->Vecteur[c];
		for(int i=0;i<vAtelier->Nbelt;i++)
		{
			atelier=vAtelier->Vecteur[i];
			if(atelier->Derobe!=derobe) continue;
			if(atelier->NoCategorie != categorie->No)continue;
			elt=new CL_Elt(poste,categorie,atelier);
			elt->Valeur=new float[N_X]; //
			V_Elt->ins(elt);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltSurfacePerenne(CL_Poste *poste,bool derobe)
{
	CL_Espece *espece;
	CL_Atelier *atelier;
	CL_Elt *elt;

	for(int c=0;c<V_Espece->Nbelt;c++)
	{
		espece=V_Espece->Vecteur[c];
		for(int i=0;i<V_Perenne->Nbelt;i++)
		{
			atelier=V_Perenne->Vecteur[i];
			if(atelier->Derobe!=derobe) continue;
			if(atelier->NoEspece!= espece->No)continue;
			elt=new CL_Elt(poste,espece,atelier);
			elt->Valeur=new float[N_X]; //
			memset(elt->Valeur,0,sizeof(float)*N_X);
			V_Elt->ins(elt);
		}
	}
}
//---------------------------------------------------------------------------
void CL_ES::ImpV_Elt(void) {
	int i;
	CL_Elt *elt;
	AnsiString date;
	TDateTime time;

	ofstream outfile("LesElt.txt");
	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();

	outfile << date.c_str() << endl;

	outfile << "    N°Famille" << endl;
	outfile << "          N°Categorie" << endl;
	outfile << "            N°Type" << endl;
	outfile << "              N°Item" << endl;

	for (i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		outfile << i << "  " << elt->NoFamille << "  " << elt->NoCategorie
				<< "  " << elt->NoType << "  " << elt->NoItem << "  "
				<< elt->Nom << "  " << elt->NomCat << "  " << elt->NomFamille
				<< endl;
	}
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

