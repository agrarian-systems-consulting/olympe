//---------------------------------------------------------------------------

#include <vcl.h>
#include <systdate.h>
#include <vcl\dstring.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Brouillon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//----------------------------------------------------------------------------
void TFBrouillon::ResultatAgriQuantite(CL_Agriculteur *agri) {
	Demarre();
	Quantite(agri);
	Blanc(5);
	Show();
}
//-------------------------------------------------------------------------
void TFBrouillon::ResultatAgriValeur(CL_Agriculteur *agri) {
	Demarre();
	Valeur(agri);
	Blanc(5);
	Show();
}
//----------------------------------------------------------------------------
void TFBrouillon::ResultatAgriExternalite(CL_Agriculteur *agri) {
	Demarre();
	Externalite(agri);
	Blanc(5);
	Show();
}
//-------------------------------------------------------------------------
void TFBrouillon::ResultatAgriTva(CL_Agriculteur *agri) {
	Demarre();
	Tva(agri);
	Blanc(5);
	Show();
}
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Quantité
//
//-------------------------------------------------------------------------
void TFBrouillon::Quantite(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	AnsiString caption;
	CL_InvAni *invAni;
	/*
	 Trait(156);
	 Trait(154);
	 Trait(152);
	 Trait(150);
	 */

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	resultat = agri->Resultat;

	Titre1("Quantites Physiques");
	An(agri->DefSim->An_0);
	if (resultat->V_Produit->Nbelt > 0)
		CategorieQ("Produits", V_CatProduit, resultat->V_Produit);
	if (Agri->V_InvAni->Nbelt) {
		Titre2("Animaux Vendus");
		for (int i = 0; i < Agri->V_InvAni->Nbelt; i++) {
			invAni = Agri->V_InvAni->Vecteur[i];
			if (EstVide(invAni->Vente) == false)
				Resultat(invAni->Animal->Nom, invAni->Vente, clNavy);
		}
		Titre2("Animaux Achetés");
		for (int i = 0; i < Agri->V_InvAni->Nbelt; i++) {
			invAni = Agri->V_InvAni->Vecteur[i];
			if (EstVide(invAni->Achat) == false)
				Resultat(invAni->Animal->Nom, invAni->Achat, clNavy);
		}
	}
	if (resultat->V_Charge->Nbelt > 0)
		CategorieQ("Charges", V_CatCharge, resultat->V_Charge);

}
//-------------------------------------------------------------------------
void TFBrouillon::CategorieQ(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vQuanVal) {
	int i, j, l;
	CL_QuanVal *quanVal;
	CL_Item *item;
	CL_Categorie *categorie;
	AnsiString unite;
	LarTrait = 152;
	Trait();
	Titre2(titre);
	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		//quanValTot=vCatTot->trouve(categorie->No);
		l = 0;
		Titre3(categorie->Nom.c_str(), clNavy);

		for (j = 0; j < vQuanVal->Nbelt; j++) {
			quanVal = vQuanVal->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;

			if (Global == false)
				unite = item->SysUnite->UTrans;
			else
				unite = item->SysUnite->UGlobal;

			l++;
			Resultat(item->Nom, unite, quanVal->Qte, clNavy);
		}
	}
}
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Valeur
//
//-------------------------------------------------------------------------
void TFBrouillon::Valeur(CL_Agriculteur *agri) {
	int n;
	CL_AgriRes *resultat;
	AnsiString as;
	float solde[N_X];
	float valeur[N_X];
	AnsiString caption;
	CL_InvAni *invAni;
	LarTrait = 152;
	caption = TexteCaption(agri);
	/*
	 Trait(156);
	 Trait(154);
	 Trait(152);
	 Trait(150);
	 */

	Titre1(caption.c_str());

	resultat = agri->Resultat;
	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre1(as.c_str());
	An(agri->DefSim->An_0);

	CategorieV("Produits", V_CatProduit, resultat->V_Produit, resultat->Produit,
			resultat->V_CatProduitTot);

	if (Agri->V_InvAni->Nbelt) {
		Titre2("Animaux Vendus");
		for (int i = 0; i < Agri->V_InvAni->Nbelt; i++) {
			invAni = Agri->V_InvAni->Vecteur[i];
			if (EstVide(invAni->ValVente) == false)
				Resultat(invAni->Animal->Nom, invAni->ValVente, clNavy);
		}
		Titre2("Animaux Achetés");
		for (int i = 0; i < Agri->V_InvAni->Nbelt; i++) {
			invAni = Agri->V_InvAni->Vecteur[i];
			if (EstVide(invAni->ValAchat) == false)
				Resultat(invAni->Animal->Nom, invAni->ValAchat, clNavy);
		}
	}
	CategorieV("Charges", V_CatCharge, resultat->V_Charge, resultat->Charge,
			resultat->V_CatChargeTot);

	Total("MARGE", resultat->Marge);
//	Blanc();

	CategorieV("Charges de Structure", V_CatChStruct, resultat->V_ChStruct,
			resultat->ChStruct, resultat->V_CatChStructTot);
	CategorieV("Recettes Diverses", V_CatRecDiv, resultat->V_RecDiv,
			resultat->RecDiv, resultat->V_CatRecDivTot);
	CategorieV("Dépenses Diverses", V_CatDepDiv, resultat->V_DepDiv,
			resultat->DepDiv, resultat->V_CatDepDivTot);
	CategorieV("Recettes Familiales", V_CatRecFam, resultat->V_RecFam,
			resultat->RecFam, resultat->V_CatRecFamTot);
	CategorieV("Dépenses Familiales", V_CatDepFam, resultat->V_DepFam,
			resultat->DepFam, resultat->V_CatDepFamTot);
	Trait();
	Titre2("Immobilisation");
	for (n = 0; n < N_X; n++)
		solde[n] = resultat->ImmoTotal->Achat[n]
				- resultat->ImmoTotal->Vente[n];
	Resultat("Achat", resultat->ImmoTotal->Achat, clNavy);
	Resultat("Vente", resultat->ImmoTotal->Vente, clNavy);
	Resultat("Achat-Vente", solde);

	Trait();
	Titre2("Emprunts");
	Resultat("Emprunt", resultat->EmpTotal->Capital, clNavy);
	Resultat("Remboursement", resultat->EmpTotal->Remb, clNavy);
	Resultat("Interet", resultat->EmpTotal->Interet, clNavy);
	for (n = 0; n < N_X; n++)
		solde[n] = resultat->EmpTotal->Capital[n] - resultat->EmpTotal->Remb[n]
				- resultat->EmpTotal->Interet[n];
	Resultat("net", solde);

	Trait();
	Titre2("Placements");
	Resultat("Placé", resultat->PlactE->Capital, clNavy);
	Resultat("Disponible", resultat->PlactE->Remb, clNavy);
//    Resultat("Interet",      resultat->PlactE->Interet,clNavy);
	for (int n = 0; n < N_X; n++)
		solde[n] = -resultat->PlactE->Capital[n] + resultat->PlactE->Remb[n];
//                  +resultat->PlactE->Interet[n];
	Resultat("net", solde);

	Trait();
	Titre2("Subventions");
	Resultat("Subventions", resultat->TotSub->Valeur, clNavy);
	Blanc();

	Trait();
	Titre2("Créances et Dettes");
	Resultat("Créances", resultat->Creance->Flux, clNavy);
	for (n = 0; n < N_X; n++)
		valeur[n] = -resultat->Dette->Flux[n];
	Resultat("Dettes", valeur, clNavy);
	Blanc();

	Trait();
	Titre2("Tva");
	Resultat("Solde Tva", resultat->Tva->Solde, clNavy);
	Blanc();

//    Trait(132);  Total trace un trait
	Total("SOLDE", resultat->Solde);
//	Trait(132);

//    Trait(132);
	memset(valeur, 0, sizeof(float) * N_X);
	valeur[0] = resultat->TresoIni;
	Resultat("Trésorerie Initiale", valeur);
	Resultat("SOLDE CUMULE", resultat->SoldeCumul);
	Trait();
}
//-------------------------------------------------------------------------
void TFBrouillon::CategorieV(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vProduit, float *total,
		CL_Vecteur<CL_QuanVal> *vCatTot) {
	int i, j, l;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal, *quanValTot;
	LarTrait = 152;
	if (vProduit->Nbelt == 0)
		return;

	Trait();
	Titre2(titre);

	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		quanValTot = vCatTot->trouve(categorie->No);
		l = 0;
		Titre3(categorie->Nom.c_str(), clNavy);

		for (j = 0; j < vProduit->Nbelt; j++) {
			quanVal = vProduit->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;
			l++;
			Resultat(item->Nom, quanVal->Val, clNavy);
		}
		if (l > 1) {
			Resultat(AnsiString("total"), quanValTot->Val);
		}
	}
	Total("TOTAL", total);

}
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Externalité
//
//-------------------------------------------------------------------------
void TFBrouillon::Externalite(CL_Agriculteur *agri) {
	int i;
	CL_AgriRes *resultat;
	CL_QuanVal *quanVal;
	CL_Item *item;
	CL_Vecteur<CL_QuanVal> *vQuanVal;
	AnsiString caption;
	AnsiString unite;
//    /*
	Trait(156);
	Trait(154);
	Trait(152);
	Trait(150);
//    */

	resultat = agri->Resultat;

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	Titre1("Externalités");
	An(agri->DefSim->An_0);
	if (resultat->V_ExtNeg->Nbelt > 0) {
		vQuanVal = resultat->V_ExtNeg;
		Trait(136);
		Titre2("Négatives");
		for (i = 0; i < vQuanVal->Nbelt; i++) {
			quanVal = vQuanVal->Vecteur[i];
			item = quanVal->Item;

			if (Global == false)
				unite = item->SysUnite->UTrans;
			else
				unite = item->SysUnite->UGlobal;

			Resultat(item->Nom, unite, quanVal->Qte, clNavy);
		}
	}

	if (resultat->V_ExtPos->Nbelt > 0) {
		vQuanVal = resultat->V_ExtPos;
		Trait(136);
		Titre2("Positives");
		for (i = 0; i < vQuanVal->Nbelt; i++) {
			quanVal = vQuanVal->Vecteur[i];
			item = quanVal->Item;

			if (Global == false)
				unite = item->SysUnite->UTrans;
			else
				unite = item->SysUnite->UGlobal;

			Resultat(item->Nom, unite, quanVal->Qte, clNavy);
		}
	}
}
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Tva
//
//-------------------------------------------------------------------------
void TFBrouillon::Tva(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	AnsiString caption, as;
	LarTrait = 152;

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	resultat = agri->Resultat;
	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre1(as.c_str());

	An(agri->DefSim->An_0);
	Trait();
	Resultat("Encaissé", resultat->Tva->Recu, clNavy);
	Resultat("Versé", resultat->Tva->Verse, clNavy);
	Blanc(1);
	Resultat("Acompte Fevrier", resultat->Tva->AcompteFev, clNavy);
	Resultat("Régularisation ", resultat->Tva->Regul, clNavy);
	Resultat("Remboursement", resultat->Tva->RembTva, clNavy);
	Blanc(1);
	Resultat("Acompte Mai", resultat->Tva->AcompteMai, clNavy);
	Resultat("Acompte Aout", resultat->Tva->AcompteAout, clNavy);
	Resultat("Acompte Novembre", resultat->Tva->AcompteNov, clNavy);

	Trait();
	Resultat("Solde", resultat->Tva->Solde, clNavy);
	Trait();

}
