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
//#include "TitreFrancais.h"

//#include "Brouillon.h"
#include "SortieEcran.h"

#include "Forme0.h"

//extern
#include "LesVecteurs.hse"
#include "Olympe.hse"

//extern char *LesTitresBilan[23];
extern CL_ES *ES;

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

	poste=new CL_Poste(LesTitresPoste[ 0],PRODUIT ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 1],CHARGE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 2],MARGE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 3],CHSTRUCT); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 4],RECDIV ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 5],DEPDIV ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 6],RECFAM ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 7],DEPFAM ); V_Poste->insSans(poste);

	poste=new CL_Poste(LesTitresPoste[ 8],POSTE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[ 9],BILAN ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[10],CEG ); V_Poste->insSans(poste);

	poste=new CL_Poste(LesTitresPoste[11],VARIABLE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[12],INDIC ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[13],EXTPOS ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[14],EXTNEG ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[15],QPRODUIT ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[16],QCHARGE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[17],PPRODUIT ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[18],PCHARGE ); V_Poste->insSans(poste);

	poste=new CL_Poste(LesTitresPoste[19],IMMO ); V_Poste->insSans(poste);

	poste=new CL_Poste(LesTitresPoste[20],EMP ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[21],EMPLT ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[22],EMPCT ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[23],EMPPRIVE ); V_Poste->insSans(poste);

	poste=new CL_Poste(LesTitresPoste[24],SUBVENTION ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[25],TVA ); V_Poste->insSans(poste);

	poste=new CL_Poste(LesTitresPoste[26],CULTURE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[27],PERENNE ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[28],VIVRIER ); V_Poste->insSans(poste);
	poste=new CL_Poste(LesTitresPoste[29],ANIMAUX ); V_Poste->insSans(poste);
	//030303
	poste=new CL_Poste(LesTitresPoste[30],MVT ); V_Poste->insSans(poste);

	poste=new CL_Poste("Calendrier", CALENDRIER); V_Poste->insSans(poste);//090306
	poste=new CL_Poste("Amor Détaillé", AMORDETAIL); V_Poste->insSans(poste);//090306
}
/*
 //                  Nom                   NoPoste
 poste=new CL_Poste("Recettes Produits",  PRODUIT ); V_Poste->insSans(poste);
 poste=new CL_Poste("Dépenses Appro",     CHARGE  ); V_Poste->insSans(poste);
 poste=new CL_Poste("Marge",              MARGE   ); V_Poste->insSans(poste);
 poste=new CL_Poste("Ch_structure",       CHSTRUCT); V_Poste->insSans(poste);
 poste=new CL_Poste("Recettes_Diverses",  RECDIV  ); V_Poste->insSans(poste);
 poste=new CL_Poste("Dépenses_Diverses",  DEPDIV  ); V_Poste->insSans(poste);
 poste=new CL_Poste("Recettes_Familiales",RECFAM  ); V_Poste->insSans(poste);
 poste=new CL_Poste("Dépenses_Familiales",DEPFAM  ); V_Poste->insSans(poste);

 poste=new CL_Poste("Poste",               POSTE ); V_Poste->insSans(poste);
 poste=new CL_Poste("Bilan",               BILAN ); V_Poste->insSans(poste);
 poste=new CL_Poste("Ceg",                 CEG   ); V_Poste->insSans(poste);

 poste=new CL_Poste("Variables",       VARIABLE ); V_Poste->insSans(poste);
 poste=new CL_Poste("Indicateurs",     INDIC    ); V_Poste->insSans(poste);
 poste=new CL_Poste("Ext. Positive",   EXTPOS   ); V_Poste->insSans(poste);
 poste=new CL_Poste("Ext. Négative",   EXTNEG   ); V_Poste->insSans(poste);
 poste=new CL_Poste("Quant Produit",   QPRODUIT ); V_Poste->insSans(poste);
 poste=new CL_Poste("Quant Charge",    QCHARGE  ); V_Poste->insSans(poste);
 poste=new CL_Poste("Prix Produit",    PPRODUIT ); V_Poste->insSans(poste);
 poste=new CL_Poste("Prix Charge",     PCHARGE  ); V_Poste->insSans(poste);


 poste=new CL_Poste("Immobilisation",  IMMO     ); V_Poste->insSans(poste);

 poste=new CL_Poste("Emprunt",         EMP      ); V_Poste->insSans(poste);
 poste=new CL_Poste("Emprunt LT",      EMPLT    ); V_Poste->insSans(poste);
 poste=new CL_Poste("Emprunt CT",      EMPCT    ); V_Poste->insSans(poste);
 poste=new CL_Poste("Emprunt Privé",   EMPPRIVE ); V_Poste->insSans(poste);

 poste=new CL_Poste("Subvention",      SUBVENTION ); V_Poste->insSans(poste);
 poste=new CL_Poste("Tva",             TVA );        V_Poste->insSans(poste);

 poste=new CL_Poste("Surf Cultures",       CULTURE   ); V_Poste->insSans(poste);
 poste=new CL_Poste("Surf Pérennes",       PERENNE   ); V_Poste->insSans(poste);
 poste=new CL_Poste("Surf PluriAnnuelle",  VIVRIER   ); V_Poste->insSans(poste);
 poste=new CL_Poste("Eff  Animaux",        ANIMAUX   ); V_Poste->insSans(poste);
 //030303
 poste=new CL_Poste("Mvt Animaux",    MVT       ); V_Poste->insSans(poste);
 */

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
	int i;
//test
	CL_Categorie *categorie;
	for(int c=0;c<V_CatProduit->Nbelt;c++)
	{
		categorie=V_CatProduit->Vecteur[c];
	}
//....
	// pour les prix des produits et des charges j'ai alloué de la place
	//cf Forme0  CompleteElt
	// d'abord je delete les valeurs si je les ai allouées

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

	IniV_EltPoste();
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

	//Emprunt
	IniV_EltEmp (EMP);
	IniV_EltEmp (EMPLT);
	IniV_EltEmp (EMPCT);
	IniV_EltEmp (EMPPRIVE);//020205
	//Subvention
	IniV_EltSubvention();
	//Tva
	IniV_EltTva();

	//190102
	//surface
	IniV_EltSurface();//y compris animaux sauf mouvement
	//animaux
	IniV_EltAnimaux ( );// seulement mouvement

	IniV_EltCalendrier();//090306
	//IniV_EltAmorDetail();  //240406  ne sert à rien 211006
	V_Elt->Flag=true;
//   TEST
//   ImpV_Elt();    //IMPRESSION pour Test
}
//Bilan
/*
 CompleteV_Elt a besoin de NoFamille=BILAN
 NoItem
 */
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltPoste(void)
{
	CL_Poste *poste;
	CL_Elt *elt;
	poste=V_Poste->trouve(POSTE);
	elt=new CL_Elt(poste,LesTitresTreso[ 0],PRODUIT); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 1],CHARGE); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 2],MARGE); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 3],CHSTRUCT); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 4],RECDIV); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 5],DEPDIV); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 6],RECFAM); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 7],DEPFAM); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 8],SOLDE); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[ 9],SOLDECUMUL); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[10],RESULTAT); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[11],EBE); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTreso[12],CAF); V_Elt->ins(elt);
	/*
	 elt=new CL_Elt(poste,"Recettes Produits",  PRODUIT);   V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Dépenses Appro",     CHARGE);    V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Marge",              MARGE);     V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Ch_structure",       CHSTRUCT);  V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Recettes_Diverses",  RECDIV);    V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Dépenses_Diverses",  DEPDIV);    V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Recettes_Familiales",RECFAM);    V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Dépenses_Familiales",DEPFAM);    V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Solde",              SOLDE);     V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Solde Cumul",    	   SOLDECUMUL); V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Résultat",           RESULTAT);  V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Ebe",                EBE);       V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Caf",                CAF);       V_Elt->ins(elt);
	 */
}
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

	elt=new CL_Elt(poste,LesTitresCeg[ 0], 0);V_Elt->ins(elt);

	elt=new CL_Elt(poste,LesTitresCeg[ 1], 1);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 2], 2);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 3], 3);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 4], 4);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 5], 5);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 6], 6);V_Elt->ins(elt);

	elt=new CL_Elt(poste,LesTitresCeg[ 7], 7);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 8], 8);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[ 9], 9);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[10],10);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[11],11);V_Elt->ins(elt);

	elt=new CL_Elt(poste,LesTitresCeg[12],12);V_Elt->ins(elt);

	elt=new CL_Elt(poste,LesTitresCeg[13],13);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[14],14);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[15],15);V_Elt->ins(elt);

	elt=new CL_Elt(poste,LesTitresCeg[16],16);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[17],17);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[18],18);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[19],19);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[20],20);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[21],21);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[22],22);V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresCeg[23],23);V_Elt->ins(elt);
	/*

	 elt=new CL_Elt(poste,"Produits",                 0);V_Elt->ins(elt);

	 elt=new CL_Elt(poste,"Recettes",                 1);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Recettes Diverses",        2);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Var. Stock",               3);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Var. stock en terre",      4);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Var. inv animal Repro",    5);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Var. inv animal Autre",    6);V_Elt->ins(elt);

	 elt=new CL_Elt(poste,"Produits financiers",      7);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Production d'immo",        8);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Cession d'actif",          9);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Perte Exceptionnelle",     10);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Amortissement Subvention", 11);V_Elt->ins(elt);


	 elt=new CL_Elt(poste,"Charges",                  12);V_Elt->ins(elt);

	 elt=new CL_Elt(poste,"Dépenses Exploitation",    13);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Dépenses Diverses",        14);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Val comptable cession",    15);V_Elt->ins(elt);

	 elt=new CL_Elt(poste,"Charges de Structure",     16);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Amortissement Immo",       17);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Amortissement Plantation", 18);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Frais fin LT",             19);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Frais fin CT",             20);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Frais fin OCCC",           21);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Autres Ch Struct",         22);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Résultat",                 23);V_Elt->ins(elt);
	 */
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
	if(poste==NULL)
	ShowMessage("IniV_EltItem poste=NULL");
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
	elt=new CL_Elt(poste,LesTitresImmo[0], AMOR); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresImmo[1], VALRESID); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresImmo[2], VALACHAT); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresImmo[3], VALBRUT); V_Elt->ins(elt);

	/*

	 elt=new CL_Elt(poste,"Amortissement",  AMOR);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Val Résiduelle", VALRESID);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Achat",          VALACHAT);V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Val Brute",      VALBRUT);V_Elt->ins(elt);
	 */
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltSubvention(void)
{
	CL_Poste *poste;
	CL_Elt *elt;

	poste=V_Poste->trouve(SUBVENTION);
	elt=new CL_Elt(poste,LesTitresSub[0], VALACHAT); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresSub[1], AMOR); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresSub[2], VALRESID); V_Elt->ins(elt);
	/*
	 elt=new CL_Elt(poste,"Valeur",         VALACHAT);  V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Amortissement",  AMOR);      V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Val Résiduelle", VALRESID);  V_Elt->ins(elt);
	 */
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltTva(void)
{
	CL_Poste *poste;
	CL_Elt *elt;

	poste=V_Poste->trouve(TVA);

	elt=new CL_Elt(poste,LesTitresTva[0],1); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTva[1],2); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTva[2],3); V_Elt->ins(elt);
	elt=new CL_Elt(poste,LesTitresTva[3],4); V_Elt->ins(elt);

	/*
	 elt=new CL_Elt(poste,"Encaissé",       1);  V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Versé",          2);  V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Régularisation", 3);  V_Elt->ins(elt);
	 elt=new CL_Elt(poste,"Solde",          4);  V_Elt->ins(elt);
	 */
}

//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltEmp(int nature)
{
	CL_Poste *poste;
	CL_Elt *elt;
	poste=V_Poste->trouve(nature);
	switch(nature)
	{
		case EMP:
		elt=new CL_Elt(poste,LesTitresEmp[ 0], ANNUITE);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[ 1], REMB); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[ 2], INTERET);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[ 3], NOUVEMP);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[ 4], DETTE); V_Elt->ins(elt);
		break;
		/*
		 elt=new CL_Elt(poste,"Annuités      Tot Ent", ANNUITE);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Cap Remboursé Tot Ent", REMB);   V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Interet       Tot Ent", INTERET);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Nouveaux Emp  Tot Ent", NOUVEMP);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Dettes        Tot Ent", DETTE);  V_Elt->ins(elt);
		 */

		case EMPLT:
		elt=new CL_Elt(poste,LesTitresEmp[5], ANNUITE);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[6], REMB); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[7], INTERET);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[8], NOUVEMP);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[9], DETTE); V_Elt->ins(elt);
		break;
		/*
		 elt=new CL_Elt(poste,"Annuités      LT Ent", ANNUITE);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Cap Remboursé LT Ent", REMB);   V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Interet       LT Ent", INTERET);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Nouveaux Emp  LT Ent", NOUVEMP);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Dettes        LT Ent", DETTE); V_Elt->ins(elt);
		 */

		case EMPCT:
		elt=new CL_Elt(poste,LesTitresEmp[10], ANNUITE);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[11], REMB); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[12], INTERET);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[13], NOUVEMP);V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[14], DETTE);V_Elt->ins(elt);
		break;
		/*
		 elt=new CL_Elt(poste,"Annuités      CT Ent", ANNUITE);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Cap Remboursé CT Ent", REMB);   V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Interet       CT Ent", INTERET);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Nouveaux  Emp CT Ent", NOUVEMP);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Dettes        CT Ent", DETTE);V_Elt->ins(elt);
		 */

		case EMPPRIVE:
		elt=new CL_Elt(poste,LesTitresEmp[15], ANNUITE); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[16], REMB); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[17], INTERET); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[18], NOUVEMP); V_Elt->ins(elt);
		elt=new CL_Elt(poste,LesTitresEmp[19], DETTE); V_Elt->ins(elt);
		break;
		/*
		 elt=new CL_Elt(poste,"Annuités      Privé", ANNUITE);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Cap Remboursé Privé", REMB);   V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Interet       Privé", INTERET);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Nouveaux Emp  Privé", NOUVEMP);V_Elt->ins(elt);
		 elt=new CL_Elt(poste,"Dettes        Privé", DETTE);V_Elt->ins(elt);
		 */
	}
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
void __fastcall CL_ES::IniV_EltCalendrier(void)//090306
{
	CL_Calendrier *calendrier;
	CL_Poste *poste;
	CL_Elt *elt;
//ShowMessage("FichierElt");
	poste=V_Poste->trouve(CALENDRIER);
	for(int c=0;c<V_Calendrier->Nbelt;c++)
	{
		calendrier=V_Calendrier->Vecteur[c];
		elt=new CL_Elt(poste,calendrier);
		//elt->Valeur=new float[N_X];
		//memset(elt->Valeur,0,sizeof(float)*N_X);
		V_Elt->ins(elt);
	}
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::IniV_EltAmorDetail(void)//240406
{
	CL_Immo *immo;
	CL_Poste *poste;
	CL_Elt *elt;
	int n,nbelt;
//ShowMessage("IniV_EltAmorDetail");
	if(AgriEnCours==NULL) return;
	poste=V_Poste->trouve(AMORDETAIL);

	CL_Vecteur<CL_Immo> *vecteur=AgriEnCours->V_Immo;
	if(vecteur==NULL) return;

	nbelt=vecteur->Nbelt;

	for( n=0;n<nbelt;n++)
	{
		immo=vecteur->Vecteur[n];
//        elt=new CL_Elt(poste,calendrier);
//        V_Elt->ins(elt);
	}

}
//---------------------------------------------------------------------------
void CL_ES::ImpV_Elt(void) {
	int i;
	CL_Elt *elt;
	AnsiString date;
	TDateTime time;
	char chaine[100];

	ofstream outfile("voir LesElt.txt de ImpV_Elt");
	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();

	outfile << date.c_str() << endl;
	outfile << ES->FLecture.c_str() << endl;

	outfile << "    N°" << endl;
	outfile << "      N°Famille" << endl;
	outfile << "          N°Categorie" << endl;
	outfile << "               N°Type" << endl;
	outfile << "                   N°Item" << endl;

	for (i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		sprintf(chaine, " %3d %3d %3d %3d %3d %-20.20s %-20.20s %-20.20s",
				elt->No, elt->NoFamille, elt->NoCategorie, elt->NoType,
				elt->NoItem, elt->Nom, elt->NomCat, elt->NomFamille);
		outfile << chaine << endl;
	}
	outfile.close();
	ShowMessage("Voir  LesElt.txt");
}

/*

 */
