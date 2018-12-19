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
void CL_Comptabilite::FaireCompta(CL_Agriculteur *agri) {
	int n, i;
	float val;
	CL_AgriRes *resultat;
	CL_StockIni *stockIni;
	CL_QuanVal *quanVal;
	resultat = agri->Resultat;
	//calculs
	creanceTva[0] = 0;
	detteTva[0] = resultat->Tva->AcompteFev[0] + resultat->Tva->Regul[0];
	if (detteTva[0] < 0) {
		creanceTva[0] = -detteTva[0];
		detteTva[n] = 0;
	}
	for (n = 1; n < N_X + 1; n++)
		detteTva[n] = resultat->Tva->Recu[n - 1] - resultat->Tva->Verse[n - 1]
//                    - resultat->Tva->AcompteFev[n-1]
				- resultat->Tva->AcompteMai[n - 1]
				- resultat->Tva->AcompteAout[n - 1]
				- resultat->Tva->AcompteNov[n - 1];

	for (n = 1; n < N_X + 1; n++) {
		creanceTva[n] = 0;
		if (detteTva[n] < 0) {
			creanceTva[n] = -detteTva[n];
			detteTva[n] = 0;
		}
	}
	memset(resultat->StockIni, 0, sizeof(float) * (N_X + 1));
	//stocks initiaux introduits par l'utilisateur
	// seront traités par Commercialisation
	//pour le moment ils sont présents jusqu'à la fin
	for (n = 0; n < agri->V_StockIni->Nbelt; n++) {
		stockIni = agri->V_StockIni->Vecteur[n];
		for (i = 0; i < N_X; i++) //corespond aux 10 années précédentes
				{
			val = stockIni->Quantite[i] * stockIni->PrixRevient[i];
			resultat->StockIni[0] += val;
		}
	}
	// à supprimer quand commercialisation sera faite !!!!!!!!!!!!!!
	for (i = 1; i < N_X + 1; i++) //corespond aux 10 années précédentes
		resultat->StockIni[i] = resultat->StockIni[0];
	//stocks %age introduit dans les ateliers
	//quanVal->Stock[i]  stocks qui sont faits l'année i
	memset(resultat->Stock, 0, sizeof(float) * (N_X + 1));
	for (n = 0; n < resultat->V_Produit->Nbelt; n++) {
		quanVal = resultat->V_Produit->Vecteur[n];
		for (i = 0; i < N_X; i++)
			resultat->Stock[i + 1] += quanVal->Stock[i];
	}
	// stock comporte stock + stockIni
	for (n = 0; n < N_X + 1; n++)
		resultat->Stock[n] += resultat->StockIni[n]; //010302
	//sera modifie quand commercialisation sera terminée
	/// variation de stock
	for (n = 0; n < N_X; n++) {
		deltaStock[n] = resultat->Stock[n + 1] - resultat->Stock[n];
		deltaAvance[n] = resultat->Avance[n + 1] - resultat->Avance[n];
//        deltaValPlant[n]=  resultat->ValPlant[n+1]-resultat->ValPlant[n];
		deltaVarInvAni[n] = resultat->InvAni[n + 1] - resultat->InvAni[n];
	}

	//.................
//Ceg
	//Total Produits
	for (n = 0; n < N_X; n++)
		totProduit[n] = resultat->Produit[n] + resultat->RecDiv[n]
				+ deltaStock[n] + deltaAvance[n] + deltaVarInvAni[n]
				+ resultat->PlactE->Interet[n] + resultat->ProdImmo[n]
				+ resultat->ImmoTotal->Vente[n] - resultat->PertePlant[n]
				+ resultat->TotSub->Amor[n];
	//Total Dépenses
	for (n = 0; n < N_X; n++)
		totDepense[n] = resultat->Charge[n] + resultat->DepDiv[n]
				+ resultat->ImmoTotal->ValCompta[n];
	//Total Charges de structure
	for (n = 0; n < N_X; n++)
		totChStruct[n] = resultat->ImmoTotal->Amor[n] + resultat->AmorPlant[n]
				+ resultat->EmpLTE->Interet[n] + resultat->EmpCTE->Interet[n]
				+ resultat->FraisOccc[n] + resultat->ChStruct[n];
	for (n = 0; n < N_X; n++)
		resExercice[n] = totProduit[n] - totDepense[n] - totChStruct[n];
//Prive
	for (n = 0; n < N_X; n++)
		soldePrive[n] = resultat->RecFam[n] - resultat->DepFam[n]
				+ resultat->ProdImmoFam[n] + resultat->PlactP->Interet[n]
				- resultat->EmpLTP->Remb[n] - resultat->EmpCTP->Remb[n]
				- resultat->EmpLTP->Interet[n] - resultat->EmpCTP->Interet[n]
				- resultat->PlactP->Capital[n];
//Bilan
	for (n = 0; n < N_X + 1; n++)
		totImmo[n] = resultat->ImmoTotal->Resid[n] + resultat->InvAni[n]
				+ resultat->ValPlant[n];
	tresorerie[0] = resultat->TresoIni;
	for (n = 1; n < N_X + 1; n++)
		tresorerie[n] = resultat->SoldeCumul[n - 1];

	//bilan d'ouverture
	totActif[0] = totImmo[0]
//                +resultat->StockIni[0]
			+ resultat->Stock[0] + resultat->Avance[0]
			//creance
			+ resultat->Creance->CrDette[0] + resultat->PlactE->Dette[0]
			+ creanceTva[0] + tresorerie[0];

	totPassif[0] = resultat->TotSub->Resid[0] + resultat->Dette->CrDette[0]
			+ resultat->EmpLTE->Dette[0] + resultat->EmpCTE->Dette[0]
			+ detteTva[0];

	capital[0] = totActif[0] - totPassif[0];

	totPassif[0] = totActif[0];
	capital[1] = capital[0];
	// calcul bilan
	for (n = 1; n < N_X + 1; n++) {
		totActif[n] = totImmo[n] + resultat->Stock[n] + resultat->Avance[n]
				//creance
				+ resultat->Creance->CrDette[n] + resultat->PlactE->Dette[n]
				+ creanceTva[n] + tresorerie[n];

		totPassif[n] = capital[n] + soldePrive[n - 1]
				+ resultat->Dette->CrDette[n] + resultat->TotSub->Resid[n]
				+ resultat->EmpLTE->Dette[n] + resultat->EmpCTE->Dette[n]
				+ detteTva[n];

		benefice[n - 1] = totActif[n] - totPassif[n];
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
