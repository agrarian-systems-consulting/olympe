//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "Brouillon.h"

//extern
#include "LesVecteurs.hse"
#include "Olympe.hse"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void CL_ES::LesAdresses(void) {

	//ITEM produit charge irrigation variable
	// 3 categorie sysunite tva
	adresseItem3(V_Produit, V_CatProduit);
	adresseItem3(V_Charge, V_CatCharge);
	adresseItem3(V_Variable, V_CatVar);
	adresseItem3(V_Externalite, V_CatExternalite);
// autres recettes dépenses
	// 2 categorie tva
	adresseItem2(V_ChStruct, V_CatChStruct);
	adresseItem2(V_RecDiv, V_CatRecDiv);
	adresseItem2(V_DepDiv, V_CatDepDiv);
	adresseItem2(V_RecFam, V_CatRecFam);
	adresseItem2(V_DepFam, V_CatDepFam);
//type zone  dico
	adresseItem1(V_TypeZone, V_CatTypeZone);
	adresseItem1(V_Dico, V_CatDico);
// Atelier
	adresseAtelier(V_Culture, V_CatCulture);
	adresseAtelier(V_Animaux, V_CatAnimaux);
	adressePerenne(V_Perenne);
	adresseAtelier(V_Vivrier, V_CatVivrier);
//Agriculteur
	adresseAgri();
//EtatSortie
	adresseEtatSortie();
//Indicateur
	adresseIndicateur();
//Ensemble
	adresseEnsemble();

}
//------------------------------------------------------------------------------
void CL_ES::adresseItem3(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);
		item->Tva = V_Tva->trouve(item->NoTva);

	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseItem2(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->Tva = V_Tva->trouve(item->NoTva);
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseItem1(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void CL_ES::adresseAtelier(CL_Vecteur<CL_Atelier> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Atelier* atelier;
	int toto;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		if (atelier->No == 42)
			toto = 1;
		atelier->Categorie = vCategorie->trouve(atelier->NoCategorie);
		atelier->Espece = NULL;
		adresseAtelierItem(atelier->V_Produit, V_Produit);
		adresseAtelierItem(atelier->V_Charge, V_Charge);
		adresseAtelierItem(atelier->V_ChargeVolume, atelier->V_Produit,
				V_Charge);
		adresseAtelierItem(atelier->V_Externalite, V_Externalite);
	}
}
//------------------------------------------------------------------------
void CL_ES::adresseAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
		CL_Vecteur<CL_Item> *vecteur) {
	CL_ItemParAtelier* itemPA;

	for (int i = 0; i < vecteurIPA->Nbelt; i++) {
		itemPA = vecteurIPA->Vecteur[i];
		itemPA->Item = vecteur->trouve(itemPA->NoItem);
	}
}
//------------------------------------------------------------------------
void CL_ES::adresseAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
		CL_Vecteur<CL_ItemParAtelier> *vecteurP,
		CL_Vecteur<CL_Item> *vecteurC) {
	CL_ItemParAtelier* itemPA;

	for (int i = 0; i < vecteurIPA->Nbelt; i++) {
		itemPA = vecteurIPA->Vecteur[i];
		itemPA->ItemPA = vecteurP->trouve(itemPA->NoItemPA);
//        itemPA->ItemPA  =vecteurP->trouve(itemPA->NoItemPA);
		itemPA->Charge = vecteurC->trouve(itemPA->NoCharge);
	}
}
//-------------------------------------------------------------------------
void CL_ES::adressePerenne(CL_Vecteur<CL_Atelier> *vecteur) {
	CL_Atelier* atelier;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		atelier->Espece = V_Espece->trouve(atelier->NoEspece);
		atelier->Categorie = NULL;
		adresseAtelierItem(atelier->V_Produit, V_Produit);
		adresseAtelierItem(atelier->V_Charge, V_Charge);
		adresseAtelierItem(atelier->V_ChargeVolume, atelier->V_Produit,
				V_Charge);
		adresseAtelierItem(atelier->V_Externalite, V_Externalite);
	}
}

//-------------------------------------------------------------------------
void CL_ES::adresseAgri(void) {
	CL_Agriculteur *agri;
	ST_NoItem *critere;
	ST_NoAgri *variante;
	for (int i = 0; i < V_Agriculteur->Nbelt; i++) {
		agri = V_Agriculteur->Vecteur[i];
		for (int j = 0; j < agri->LstCritere->Count; j++) {
			critere = (ST_NoItem*) agri->LstCritere->Items[j];
			critere->Item = V_TypeZone->trouve(critere->No);
		}
		for (int j = 0; j < agri->LstVariante->Count; j++) {
			variante = (ST_NoAgri*) agri->LstVariante->Items[j];
			variante->Agri = V_Agriculteur->trouve(variante->No);
		}
		adresseAgriValeurAtelier(agri->V_Culture, V_Culture);
		adresseAgriValeurAtelier(agri->V_Animaux, V_Animaux);
		adresseAgriValeurVerger(agri->V_Verger, V_Perenne);

		adresseAgriValeurItem(agri->V_Variable, V_Variable);

		/*        adresseAgriValeurItem(agri->V_ChStruct, V_DepEnt);
		 adresseAgriValeurItem(agri->V_RecDiv,   V_RecEnt);
		 adresseAgriValeurItem(agri->V_DepDiv,   V_DepEnt);
		 adresseAgriValeurItem(agri->V_RecFam,   V_RecFam);
		 adresseAgriValeurItem(agri->V_DepFam,   V_DepFam);
		 */
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	CL_Valeur* valeur;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		valeur->Atelier = vAtelier->trouve(valeur->NoAtelier);
//        if(valeur->Atelier==NULL){ vecteur->Nbelt=0;return;} //bidouille
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurItem(CL_Vecteur<CL_Valeur> *vecteur,
		CL_Vecteur<CL_Item>*vItem) {
	CL_Valeur* valeur;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		valeur->Item = vItem->trouve(valeur->NoItem);
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurVerger(CL_Vecteur<CL_Verger> *vecteur,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	CL_Verger* verger;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		verger = vecteur->Vecteur[i];
		verger->Atelier = vAtelier->trouve(verger->NoAtelier);
		verger->Espece = verger->Atelier->Espece;
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseEtatSortie(void) {
	CL_EtatSortie *etat;

	for (int i = 0; i < V_EtatSortie->Nbelt; i++) {
		etat = V_EtatSortie->Vecteur[i];
		etat->Categorie = V_CatEtatSortie->trouve(etat->NoCategorie);
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseIndicateur(void) {
	CL_Indicateur *indic;

	for (int i = 0; i < V_Indicateur->Nbelt; i++) {
		indic = V_Indicateur->Vecteur[i];
		indic->Categorie = V_CatIndic->trouve(indic->NoCategorie);
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseEnsemble(void) {
	int i, j;
	int noAgri;
	CL_Ensemble *ensemble;
	CL_AgriEff *agriEff;
	ST_NoEnsemble *variante;
	for (i = 0; i < V_Ensemble->Nbelt; i++) {
		ensemble = V_Ensemble->Vecteur[i];
		for (j = 0; j < ensemble->V_AgriEff->Nbelt; j++) {
			agriEff = ensemble->V_AgriEff->Vecteur[j];
			noAgri = agriEff->NoAgri;
			agriEff->Agri = V_Agriculteur->trouve(noAgri);
			agriEff->Nom = agriEff->Agri->Nom;
		}
		for (j = 0; j < ensemble->LstVariante->Count; j++) {
			variante = (ST_NoEnsemble*) ensemble->LstVariante->Items[j];
			variante->Ensemble = V_Ensemble->trouve(variante->No);
		}
	}
}
