//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "QuelExcelCSV.h"
#include "Tableur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
extern CL_ES *ES;

////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Quantité
//
//-------------------------------------------------------------------------
void CL_Excel::Quantite(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	resultat = agri->Resultat;

	EcrireNomVC(agri);

	Titre(0, "QUANTITES PHYSIQUES");
	An(colDeb, agri->DefSim->An_0); //?
	if (resultat->V_Produit->Nbelt > 0)
		CategorieQ("Produits", V_CatProduit, resultat->V_Produit);
	if (resultat->V_Charge->Nbelt > 0)
		CategorieQ("Charges", V_CatCharge, resultat->V_Charge);
	FermerFichier();
}

//-------------------------------------------------------------------------
void CL_Excel::CategorieQ(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vQuanVal) {
	int i, j, l;
	CL_QuanVal *quanVal;
	CL_Item *item;
	CL_Categorie *categorie;
	AnsiString unite;
	Trait();
	Titre(0, titre);
	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

//        quanValTot=vCatTot->trouve(categorie->No);
		l = 0;
		Titre(1, categorie->Nom.c_str());

		for (j = 0; j < vQuanVal->Nbelt; j++) {
			quanVal = vQuanVal->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;

			if (Global == AGRI || Global == MOYENNE)
				unite = item->SysUnite->UTrans;
			else
				unite = item->SysUnite->UGlobal;

//		    if(Global==false) unite=item->SysUnite->UTrans;
//		    else              unite=item->SysUnite->UGlobal;

			l++;
			Resultat(2, item->Nom, unite, quanVal->Qte);
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
	AnsiString as;
	float solde[N_X];
	float valeur[N_X];
	int colDeb = 4;
	int i;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

/// colDeb debut des valeurs
	EcrireNomVC(agri);
	Titre(0, "RECETTES DEPENSES");
	Titre(0, " ");

	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre(0, as.c_str());

	resultat = agri->Resultat;

	An(colDeb, agri->DefSim->An_0); //An_0        //?

	CategorieV("Produits", V_CatProduit, resultat->V_Produit, resultat->Produit,
			resultat->V_CatProduitTot);
	CategorieV("Charges", V_CatCharge, resultat->V_Charge, resultat->Charge,
			resultat->V_CatChargeTot);

	Blanc();
	TitreEtValeur(1, "MARGE", colDeb, resultat->Marge);
	Blanc();

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
	Titre(1, "Immobilisation");
	for (int n = 0; n < N_X; n++)
		solde[n] = resultat->ImmoTotal->Achat[n]
				- resultat->ImmoTotal->Vente[n];
	TitreEtValeur(2, "Achat", colDeb, resultat->ImmoTotal->Achat);
	TitreEtValeur(2, "Vente", colDeb, resultat->ImmoTotal->Vente);
	TitreEtValeur(1, "Achat-Vente", colDeb, solde);

	Trait();
	Titre(1, "Emprunts");
	TitreEtValeur(2, "Emprunt", colDeb, resultat->EmpTotal->Capital);
	TitreEtValeur(2, "Remboursement", colDeb, resultat->EmpTotal->Remb);
	TitreEtValeur(2, "Interet", colDeb, resultat->EmpTotal->Interet);
	for (int n = 0; n < N_X; n++)
		solde[n] = resultat->EmpTotal->Capital[n] - resultat->EmpTotal->Remb[n]
				- resultat->EmpTotal->Interet[n];
	TitreEtValeur(1, "net", colDeb, solde);
	Blanc();

	TitreEtValeur(1, "SOLDE", colDeb, resultat->Solde);
	memset(valeur, 0, sizeof(float) * N_X);
	valeur[0] = resultat->TresoIni;
	for (i = 1; i < N_X; i++)
		valeur[i] = resultat->SoldeCumul[i - 1];
	TitreEtValeur(1, "Tresorerie Initiale", colDeb, valeur);
	TitreEtValeur(1, "SOLDE CUMULE", colDeb, resultat->SoldeCumul);
	Trait();
	FermerFichier();

}
//-------------------------------------------------------------------------
void CL_Excel::GrandsPostes(CL_Agriculteur *agri) {
	CL_AgriRes *resultat; //190905
	AnsiString as;
	float solde[N_X];
	float valeur[N_X];
	int colDeb = 4;
	int i;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

/// colDeb debut des valeurs
	EcrireNomVC(agri);
	Titre(0, "RECETTES DEPENSES Grands Postes"); //190905
	Titre(0, " ");

	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre(0, as.c_str());

	resultat = agri->Resultat;

	An(colDeb, agri->DefSim->An_0); //An_0        //?

	CategorieVTotal("Produits", V_CatProduit, resultat->V_Produit,
			resultat->Produit, resultat->V_CatProduitTot);
	CategorieVTotal("Charges", V_CatCharge, resultat->V_Charge,
			resultat->Charge, resultat->V_CatChargeTot);

	Blanc();
	TitreEtValeur(1, "MARGE", colDeb, resultat->Marge);
	Blanc();
	if (EstVide(resultat->ChStruct) == false)
		TitreEtValeur(1, "Charges de Structure", 4, resultat->ChStruct);
	if (EstVide(resultat->RecDiv) == false)
		TitreEtValeur(1, "Recettes Diverses", 4, resultat->RecDiv);
	if (EstVide(resultat->DepDiv) == false)
		TitreEtValeur(1, "D\'e9penses Diverses", 4, resultat->DepDiv);
	if (EstVide(resultat->RecFam) == false)
		TitreEtValeur(1, "Recettes Familiales", 4, resultat->RecFam);
	if (EstVide(resultat->DepFam) == false)
		TitreEtValeur(1, "D\'e9penses Familiales", 4, resultat->DepFam);
	Trait();
	Titre(1, "Immobilisation");
	for (int n = 0; n < N_X; n++)
		solde[n] = resultat->ImmoTotal->Achat[n]
				- resultat->ImmoTotal->Vente[n];
	TitreEtValeur(2, "Achat", colDeb, resultat->ImmoTotal->Achat);
	TitreEtValeur(2, "Vente", colDeb, resultat->ImmoTotal->Vente);
	TitreEtValeur(1, "Achat-Vente", colDeb, solde);

	Trait();
	Titre(1, "Emprunts");
	TitreEtValeur(2, "Emprunt", colDeb, resultat->EmpTotal->Capital);
	TitreEtValeur(2, "Remboursement", colDeb, resultat->EmpTotal->Remb);
	TitreEtValeur(2, "Interet", colDeb, resultat->EmpTotal->Interet);
	for (int n = 0; n < N_X; n++)
		solde[n] = resultat->EmpTotal->Capital[n] - resultat->EmpTotal->Remb[n]
				- resultat->EmpTotal->Interet[n];
	TitreEtValeur(1, "net", colDeb, solde);
	Blanc();

	TitreEtValeur(1, "SOLDE", colDeb, resultat->Solde);
	memset(valeur, 0, sizeof(float) * N_X);
	valeur[0] = resultat->TresoIni;
	for (i = 1; i < N_X; i++)
		valeur[i] = resultat->SoldeCumul[i - 1];
	TitreEtValeur(1, "Tresorerie Initiale", colDeb, valeur);
	TitreEtValeur(1, "SOLDE CUMULE", colDeb, resultat->SoldeCumul);
	Trait();
	FermerFichier();

}
//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Valeur
//
//-------------------------------------------------------------------------
void CL_Excel::Synthese(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	AnsiString as;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

/// colDeb debut des valeurs
	EcrireNomVC(agri);

	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre(0, as.c_str());

	resultat = agri->Resultat;

	An(colDeb, agri->DefSim->An_0); //An_0        //?

	TitreEtValeur(1, "MARGE", colDeb, resultat->Marge);
	TitreEtValeur(1, "SOLDE", colDeb, resultat->Solde);
	TitreEtValeur(1, "SOLDE CUMULE", colDeb, resultat->SoldeCumul);
	TitreEtValeur(1, "Résultat Ceg", colDeb, resultat->resExercice);
	TitreEtValeur(1, "EBE ", colDeb, resultat->Ebe);
	TitreEtValeur(1, "CAF ", colDeb, resultat->Caf);
	FermerFichier();

}
//------------------------------------------------------------------------------
// produits charges
//-------------------------------------------------------------------------
void CL_Excel::CategorieV(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vProduit, float *total,
		CL_Vecteur<CL_QuanVal> *vCatTot)

		{
	int i, j, l;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal, *quanValTot;
	int colDeb = 3;
	Trait();
	Titre(1, titre);

	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		quanValTot = vCatTot->trouve(categorie->No);
		l = 0;
		Titre(2, categorie->Nom.c_str());

		for (j = 0; j < vProduit->Nbelt; j++) {
			quanVal = vProduit->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;

			l++;
			Resultat(colDeb, item->Nom, quanVal->Val);
		}
		if (l > 1) {
			Resultat(colDeb, AnsiString("total"), quanValTot->Val);
		}
	}
	TitreEtValeur(1, "TOTAL", 4, total);

}
//-------------------------------------------------------------------------
void CL_Excel::CategorieVTotal(char *titre,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_QuanVal> *vProduit,
		float *total, CL_Vecteur<CL_QuanVal> *vCatTot)

		{
	int i;
	CL_Categorie *categorie;
	CL_QuanVal *quanValTot;
	int colDeb = 3;
	Trait();
	Titre(1, titre);

	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		quanValTot = vCatTot->trouve(categorie->No);
		Resultat(colDeb, AnsiString(categorie->Nom), quanValTot->Val);
	}
	TitreEtValeur(1, "TOTAL", 4, total);

}
//-------------------------------------------------------------------------

void CL_Excel::Bilan(CL_Agriculteur *agri) {
	int colDeb = 4;
	CL_AgriRes *resultat;
	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;
	resultat = agri->Resultat;

	Titre(0, "BILAN"); //180905
	An(colDeb, agri->DefSim->An_0); //?

	Titre(2, "ACTIF");
//    blanc();
	TitreEtValeur(3, ES->LesTitresBilan[0], 4, resultat->totImmo);
	TitreEtValeur(3, ES->LesTitresBilan[1], 4, resultat->ImmoTotal->Resid);
	TitreEtValeur(3, ES->LesTitresBilan[2], 4, resultat->InvAniRepro); //260903
	TitreEtValeur(3, ES->LesTitresBilan[3], 4, resultat->ValPlant);

	TitreEtValeur(3, ES->LesTitresBilan[4], 4, resultat->Stock);
	TitreEtValeur(3, ES->LesTitresBilan[5], 4, resultat->Avance);
	TitreEtValeur(3, ES->LesTitresBilan[6], 4, resultat->InvAniAutre); //260903
	//creance
	TitreEtValeur(3, ES->LesTitresBilan[7], 4, resultat->PlactE->Dette);
	TitreEtValeur(3, ES->LesTitresBilan[8], 4, resultat->creanceTva);
	TitreEtValeur(3, ES->LesTitresBilan[9], 4, resultat->Creance->CrDette);
	TitreEtValeur(3, ES->LesTitresBilan[10], 4, resultat->tresorerie);
	TitreEtValeur(3, ES->LesTitresBilan[11], 4, resultat->perte);
	TitreEtValeur(3, ES->LesTitresBilan[12], 4, resultat->totActif);

//	PASSIF);
	Blanc();
	Titre(2, ES->LesTitresBilan[13]);
	TitreEtValeur(3, ES->LesTitresBilan[14], 4, resultat->capital);
	TitreEtValeur(3, ES->LesTitresBilan[15], 4, resultat->soldePrive);

	TitreEtValeur(3, ES->LesTitresBilan[16], 4, resultat->TotSub->Resid);
	TitreEtValeur(3, ES->LesTitresBilan[17], 4, resultat->EmpLTE->Dette);
	TitreEtValeur(3, ES->LesTitresBilan[18], 4, resultat->EmpCTE->Dette);
	TitreEtValeur(3, ES->LesTitresBilan[19], 4, resultat->detteTva);
	TitreEtValeur(3, ES->LesTitresBilan[20], 4, resultat->Dette->CrDette);
//    Blanc(1);
	TitreEtValeur(3, ES->LesTitresBilan[21], 4, resultat->benefice);
	TitreEtValeur(3, ES->LesTitresBilan[22], 4, resultat->totPassif);
}

//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Externalité
//
//-------------------------------------------------------------------------
void CL_Excel::Externalite(CL_Agriculteur *agri) {
	int i;
	CL_AgriRes *resultat;
	CL_QuanVal *quanVal;
	CL_Item *item;
	CL_Vecteur<CL_QuanVal> *vQuanVal;
//AnsiString caption;
	AnsiString unite;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	resultat = agri->Resultat;

	EcrireNomVC(agri);

	Titre(0, "Externalités");
	An(colDeb, agri->DefSim->An_0);
	if (resultat->V_ExtNeg->Nbelt > 0) {
		vQuanVal = resultat->V_ExtNeg;
		Trait();
		Titre(1, "Négatives");
		for (i = 0; i < vQuanVal->Nbelt; i++) {
			quanVal = vQuanVal->Vecteur[i];
			item = quanVal->Item;

			if (Global == AGRI || Global == MOYENNE)
				unite = item->SysUnite->UTrans;
			else
				unite = item->SysUnite->UGlobal;

			Resultat(colDeb - 2, item->Nom, unite, quanVal->Qte);
		}
	}

	if (resultat->V_ExtPos->Nbelt > 0) {
		vQuanVal = resultat->V_ExtPos;
		Trait();
		Titre(1, "Positives");
		for (i = 0; i < vQuanVal->Nbelt; i++) {
			quanVal = vQuanVal->Vecteur[i];
			item = quanVal->Item;

			if (Global == AGRI || Global == MOYENNE)
				unite = item->SysUnite->UTrans;
			else
				unite = item->SysUnite->UGlobal;

			Resultat(colDeb - 2, item->Nom, unite, quanVal->Qte);
		}
	}
	FermerFichier();
}

//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Tva
//
//-------------------------------------------------------------------------
void CL_Excel::Tva(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	AnsiString caption;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	EcrireNomVC(agri);

	resultat = agri->Resultat;

	Titre(0, "Calcul Tva");
	An(colDeb, agri->DefSim->An_0); //?

	colDeb--;
	Resultat(colDeb, "Encaissé", resultat->Tva->Recu);
	Resultat(colDeb, "Versé", resultat->Tva->Verse);
	Blanc();
	Resultat(colDeb, "Acompte Fevrier", resultat->Tva->AcompteFev);
	Resultat(colDeb, "Remboursement", resultat->Tva->RembTva);
	Resultat(colDeb, "Régularisation", resultat->Tva->Regul);
	Blanc();
	Resultat(colDeb, "Acompte Mai", resultat->Tva->AcompteMai);
	Resultat(colDeb, "Acompte Aout", resultat->Tva->AcompteAout);
	Resultat(colDeb, "Acompte Novembre", resultat->Tva->AcompteNov);
	Resultat(colDeb, "Solde", resultat->Tva->Solde);

	FermerFichier();
}
