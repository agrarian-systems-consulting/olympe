//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Tableur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Quantité
//
//-------------------------------------------------------------------------
void CL_Excel::Quantite(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	resultat = agri->Resultat;

	Titre1("Quantites Physiques");
	An(agri->DefSim->An_0);
	if (resultat->V_Produit->Nbelt > 0) {
		Trait();
		Titre2("Produits");
		CategorieQ(V_CatProduit, resultat->V_CatProduitTot,
				resultat->V_Produit);
	}

	if (resultat->V_Charge->Nbelt > 0) {
		Trait();
		Titre2("Charges");
		CategorieQ(V_CatCharge, resultat->V_CatChargeTot, resultat->V_Charge);
	}

//    Show();
}

//-------------------------------------------------------------------------
void CL_Excel::CategorieQ(CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vCatTot, CL_Vecteur<CL_QuanVal> *vQuanVal) {
	int i, j, l;
	CL_QuanVal *quanVal;
	CL_Item *item;
	CL_Categorie *categorie;
	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

//        quanValTot=vCatTot->trouve(categorie->No);
		l = 0;
		Titre3(categorie->Nom.c_str(), clNavy);

		for (j = 0; j < vQuanVal->Nbelt; j++) {
			quanVal = vQuanVal->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;

			l++;
			Resultat(item->Nom, item->SysUnite->UTrans, quanVal->Qte, clNavy);
		}
	}
}
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Valeur
//
//-------------------------------------------------------------------------
void CL_Excel::Valeur(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	resultat = agri->Resultat;

	Titre1("Valeurs");
	An(agri->DefSim->An_0); //An_0
	if (resultat->V_Produit->Nbelt > 0) {
		Trait();
		Titre2("Produits");
		CategorieV(V_CatProduit, resultat->V_CatProduitTot, agri->V_Produits);
	}

	if (resultat->V_Charge->Nbelt > 0) {
		Trait();
		Titre2("Charges");
		CategorieV(V_CatCharge, resultat->V_CatChargeTot, agri->V_Charges);
	}

//    Val2("Produits",agri->V_Produits, resultat->Produit);
//	Val2("Charges", agri->V_Charges,  resultat->Charge);
	Trait();
	Total(AnsiString("MARGE"), resultat->Marge);
	Trait();
//	Blanc();

	/*	Val2("Charges de Structure",agri->V_ChStruct, resultat->ChStruct);
	 Val2("Recettes Diverses",   agri->V_RecDiv,   resultat->RecDiv);
	 Val2("Depenses Diverses",   agri->V_DepDiv,   resultat->DepDiv);
	 Val2("Recettes Familiales", agri->V_RecFam,   resultat->RecFam);
	 */
	Trait();
//	Blanc();
	Total(AnsiString("Autres Recettes"), resultat->AutreRecette);
	Total(AnsiString("Autres Depenses"), resultat->AutreDepense);
	Total(AnsiString("SOLDE"), resultat->Solde);
	Trait();

}
//------------------------------------------------------------------------------
// produits charges
//-------------------------------------------------------------------------
void CL_Excel::CategorieV(CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vCatTot, CL_Vecteur<CL_Formule> *vFormule) {
	int i, j, l;
	CL_QuanVal *quanVal, *quanValTot;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_Formule *formule;

	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		quanValTot = vCatTot->trouve(categorie->No);
		l = 0;
		Titre3(categorie->Nom.c_str(), clNavy);

		for (j = 0; j < vFormule->Nbelt; j++) {
			formule = vFormule->Vecteur[j];
			item = formule->Item;
			if (item->Categorie != categorie)
				continue;

			l++;
			Resultat(item->Nom, formule->Valeur, clNavy);
		}
		if (l > 1) {
			Resultat(AnsiString("..."), quanValTot->Qte, clNavy);
		}
	}
}

//------------------------------------------------------------------------------
// structure divers..
//------------------------------------------------------------------------------
void CL_Excel::Val1(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vCatTot, CL_Vecteur<CL_QuanVal> *vQuanVal,
		float *total) {
	if (vQuanVal->Nbelt > 0) {
		Trait();
		Titre2(titre);
//        CategorieV(vCategorie,vCatTot,vQuanVal);//??? V ou Q
		Blanc();
		Total(AnsiString(" TOTAL"), total);
	}
}
//------------------------------------------------------------------------------
void CL_Excel::Val2(char *titre, CL_Vecteur<CL_Formule> *vecteur,
		float *total) {
	int i;
//CL_Valeur *valeur;
	CL_Formule *formule;

	if (vecteur->Nbelt > 0) {
//        ImpTrait(132);
		Titre2(titre);
		for (i = 0; i < vecteur->Nbelt; i++) {
			formule = vecteur->Vecteur[i];
			//valeur=vecteur->Vecteur[i];
			//item=valeur->Item;
			Resultat(formule->Item->Nom, formule->Valeur, clNavy);
		}
		if (vecteur->Nbelt > 1)
			Resultat(AnsiString(" total"), total, clNavy);
	}
}

