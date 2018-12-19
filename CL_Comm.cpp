#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "CL_Comm.h"
#include "Commercialisation.h"

//---------------------------------------------------------------------------
CL_Comm::CL_Comm() {
	NoItem = -1;
	memset(Production, 0, sizeof(Production));
	memset(PrixRevient, 0, sizeof(PrixRevient));
	memset(Reste, 0, sizeof(Reste));
}
//---------------------------------------------------------------------------
CL_Comm::CL_Comm(int noItem) {
	NoItem = noItem;
	memset(Production, 0, sizeof(Production));
	memset(PrixRevient, 0, sizeof(PrixRevient));
	memset(Reste, 0, sizeof(Reste));
}
//---------------------------------------------------------------------------
void CL_Comm::InsereProdAvant(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++) {
		Production[i] = quantite[i];
		Reste[i] = quantite[i];
	}
}

//---------------------------------------------------------------------------
void CL_Comm::InsereProdApres(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++) {
		Production[i + N_X] = quantite[i];
		Reste[i + N_X] = quantite[i];
	}
}
//---------------------------------------------------------------------------
void CL_Comm::InserePrixRevientAvant(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++)
		PrixRevient[i] = quantite[i];
}

//---------------------------------------------------------------------------
void CL_Comm::InserePrixRevientApres(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++)
		PrixRevient[i + N_X] = quantite[i];
}
//---------------------------------------------------------------------------
void CL_Comm::CalculVenteQ(float *vente) {
	int i;
	int n;
	int an_0 = AgriEnCours->DefSim->An_0;
	CL_QuantPrix *quantPrix;
	memset(vente, 0, sizeof(vente));
	for (i = 0; i < CommercialisationFrm->Agri->LstQuantPrix->Count; i++) {
		quantPrix =
				(CL_QuantPrix*) CommercialisationFrm->Agri->LstQuantPrix->Items[i];
		if (quantPrix->Item->No != NoItem)
			continue;

		n = quantPrix->AnComm - an_0;
		vente[n] += quantPrix->Quant;
	}

}
//---------------------------------------------------------------------------
void CL_Comm::CalculVenteV(float *vente) {
	int i;
	int n;
	int an_0 = AgriEnCours->DefSim->An_0;
	CL_QuantPrix *quantPrix;
	float vVente[N_X];
	memset(vVente, 0, sizeof(vVente));
	for (i = 0; i < CommercialisationFrm->Agri->LstQuantPrix->Count; i++) {
		quantPrix =
				(CL_QuantPrix*) CommercialisationFrm->Agri->LstQuantPrix->Items[i];
		if (quantPrix->Item->No != NoItem)
			continue;

		n = quantPrix->AnComm - an_0;
		if (n >= N_X)
			continue;
		vente[n] += quantPrix->Quant * quantPrix->Prix;
		vVente[n] += quantPrix->Quant * quantPrix->Prix;
	}

}
//---------------------------------------------------------------------------
void CL_Comm::CalculStockQ(float *stock) {
	int i, j;
	int n;
	int an_0 = AgriEnCours->DefSim->An_0;
	CL_QuantPrix *quantPrix;
	stock[0] = Production[0];
	for (i = 1; i < N_X * 2; i++)
		stock[i] = stock[i - 1] + Production[i];
	for (i = 0; i < CommercialisationFrm->Agri->LstQuantPrix->Count; i++) {
		quantPrix =
				(CL_QuantPrix*) CommercialisationFrm->Agri->LstQuantPrix->Items[i];
		if (quantPrix->Item->No != NoItem)
			continue;

		n = quantPrix->AnComm - an_0 + N_X;
		for (j = n; j < N_X * 2; j++)
			stock[j] -= quantPrix->Quant;
	}

}
//---------------------------------------------------------------------------
void CL_Comm::CalculStockV(float *stock) {
	int i, j;
	int n;
	int nProd;
	int an_0 = AgriEnCours->DefSim->An_0;
	CL_QuantPrix *quantPrix;

	stock[0] = Production[0] * PrixRevient[0];
	for (i = 1; i < N_X * 2; i++)
		stock[i] = stock[i - 1] + Production[i] * PrixRevient[i];
	for (i = 0; i < CommercialisationFrm->Agri->LstQuantPrix->Count; i++) {
		quantPrix =
				(CL_QuantPrix*) CommercialisationFrm->Agri->LstQuantPrix->Items[i];
		if (quantPrix->Item->No != NoItem)
			continue;

		n = quantPrix->AnComm - an_0 + N_X;
		nProd = quantPrix->AnProd - an_0 + N_X;
//        prixRevient[nProd]=
		for (j = n; j < N_X * 2; j++)
			stock[j] -= quantPrix->Quant * PrixRevient[nProd];
	}
	// affichage et saisie tiennent compte de float tronqués
	//(ie sans chiffre aprés virgule)
	// les stocks sont des float
	// tolérance pour un écart de 1 entre total vendu et produit
	// toute valeur de stock  < valeur d'une unité correspond a un arrondi
	for (j = 0; j < N_X * 2; j++) {
		if (stock[j] < PrixRevient[j])
			stock[j] = 0;
	}
}

