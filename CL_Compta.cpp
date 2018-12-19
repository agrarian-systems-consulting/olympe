//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Forme00.h"
#include "Erreur.h"
//#include "CL_Compta.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void CL_Comptabilite::FaireCompta(CL_AgriRes *resultat) {
	int n, i;
	CL_QuanVal *quanVal;
//calculs TVA créances dettes
	resultat->creanceTva[0] = 0;
	resultat->detteTva[0] = resultat->Tva->AcompteFev[0]
			+ resultat->Tva->Regul[0];
	if (resultat->detteTva[0] < 0) {
		resultat->creanceTva[0] = -resultat->detteTva[0];
		resultat->detteTva[n] = 0;
	}
	for (n = 1; n < N_X + 1; n++)
		resultat->detteTva[n] = resultat->Tva->Recu[n - 1]
				- resultat->Tva->Verse[n - 1] - resultat->Tva->AcompteMai[n - 1]
				- resultat->Tva->AcompteAout[n - 1]
				- resultat->Tva->AcompteNov[n - 1];

	for (n = 1; n < N_X + 1; n++) {
		resultat->creanceTva[n] = 0;
		if (resultat->detteTva[n] < 0) {
			resultat->creanceTva[n] = -resultat->detteTva[n];
			resultat->detteTva[n] = 0;
		}
	}
//stocks produits + inventaire animaux non reproducteurs
	memset(resultat->StockIni, 0, sizeof(float) * (N_X + 1));

	// 1 stocks produits

	memset(resultat->Stock, 0, sizeof(float) * (N_X + 1));
	for (n = 0; n < resultat->V_Produit->Nbelt; n++) {
		quanVal = resultat->V_Produit->Vecteur[n];
		for (i = 0; i < N_X + 1; i++)
			resultat->Stock[i] += quanVal->Stock[i];
	}
	// stock comporte stock + stockIni
	// variation de stock
	for (n = 0; n < N_X; n++) {
		resultat->deltaStock[n] = resultat->Stock[n + 1] - resultat->Stock[n];
		resultat->deltaAvance[n] = resultat->Avance[n + 1]
				- resultat->Avance[n];
		resultat->deltaVarInvAniRepro[n] = resultat->InvAniRepro[n + 1]
				- resultat->InvAniRepro[n]; //260903
		resultat->deltaVarInvAniAutre[n] = resultat->InvAniAutre[n + 1]
				- resultat->InvAniAutre[n]; //260903
	}

	//.................
//Ceg
	//Total Produits
	for (n = 0; n < N_X; n++)
		resultat->totProduit[n] = resultat->Produit[n] //tient compte des ventes et achats d'animaux
		+ resultat->RecDiv[n] + resultat->deltaStock[n]
				+ resultat->deltaAvance[n]
				+ resultat->deltaVarInvAniRepro[n] //260903
				+ resultat->deltaVarInvAniAutre[n] //260903
				+ resultat->PlactE->Interet[n] + resultat->ProdImmo[n]
				+ resultat->ImmoTotal->Vente[n] - resultat->PertePlant[n]
				+ resultat->TotSub->Amor[n];
	//Total Dépenses
	for (n = 0; n < N_X; n++)
		resultat->totDepense[n] = resultat->Charge[n] + resultat->DepDiv[n]
				+ resultat->ImmoTotal->ValCompta[n];
	//Total Charges de structure
	for (n = 0; n < N_X; n++)
		resultat->totChStruct[n] = resultat->ImmoTotal->Amor[n]
				+ resultat->AmorPlant[n] + resultat->EmpTotal->Interet[n] //050402
//                        + resultat->EmpLTE->Interet[n]
//                        + resultat->EmpCTE->Interet[n]
//                        + resultat->FraisOccc[n]  130303
				+ resultat->ChStruct[n];
	for (n = 0; n < N_X; n++)
		resultat->resExercice[n] = resultat->totProduit[n]
				- resultat->totDepense[n] - resultat->totChStruct[n];
//Prive
	for (n = 0; n < N_X; n++)
		resultat->soldePrive[n] = resultat->RecFam[n] - resultat->DepFam[n]
				+ resultat->ProdImmoFam[n] + resultat->PlactP->Interet[n]
				- resultat->EmpLTP->Remb[n] - resultat->EmpCTP->Remb[n]
				- resultat->EmpLTP->Interet[n] - resultat->EmpCTP->Interet[n]
				- resultat->PlactP->Capital[n];
//Bilan
	for (n = 0; n < N_X + 1; n++)
		resultat->totImmo[n] = resultat->ImmoTotal->Resid[n]
				+ resultat->InvAniRepro[n] //260903
				+ resultat->InvAniAutre[n] //260903
				+ resultat->ValPlant[n];
	resultat->tresorerie[0] = resultat->TresoIni;
	for (n = 1; n < N_X + 1; n++)
		resultat->tresorerie[n] = resultat->SoldeCumul[n - 1];

	//bilan d'ouverture
	resultat->totActif[0] = resultat->totImmo[0]
//                +resultat->StockIni[0]
			+ resultat->Stock[0] + resultat->Avance[0]
			//creance
			+ resultat->Creance->CrDette[0] + resultat->PlactE->Dette[0]
			+ resultat->creanceTva[0] + resultat->tresorerie[0];

	resultat->totPassif[0] = resultat->TotSub->Resid[0]
			+ resultat->Dette->CrDette[0] + resultat->EmpLTE->Dette[0]
			+ resultat->EmpCTE->Dette[0] + resultat->detteTva[0];

	resultat->capital[0] = resultat->totActif[0] - resultat->totPassif[0];

	resultat->totPassif[0] = resultat->totActif[0];
	resultat->capital[1] = resultat->capital[0];
	// calcul bilan
	for (n = 1; n < N_X + 1; n++) {
		resultat->totActif[n] = resultat->totImmo[n] + resultat->Stock[n]
				+ resultat->Avance[n]
				//creance
				+ resultat->Creance->CrDette[n] + resultat->PlactE->Dette[n]
				+ resultat->creanceTva[n] + resultat->tresorerie[n];

		resultat->totPassif[n] = resultat->capital[n]
				+ resultat->soldePrive[n - 1] + resultat->Dette->CrDette[n]
				+ resultat->TotSub->Resid[n] + resultat->EmpLTE->Dette[n]
				+ resultat->EmpCTE->Dette[n] + resultat->detteTva[n];

		resultat->benefice[n - 1] = resultat->totActif[n]
				- resultat->totPassif[n];
		if (benefice[n - 1] > 0) {
			perte[n - 1] = 0;
			totPassif[n] += benefice[n - 1];
		} else {
			perte[n - 1] = -benefice[n - 1];
			benefice[n - 1] = 0;
			totActif[n] += perte[n - 1];
		}
		if (n + 1 >= N_X + 1)
			continue;

		capital[n + 1] = capital[n] + benefice[n - 1] - perte[n - 1]
				+ soldePrive[n - 1];
	}

}
