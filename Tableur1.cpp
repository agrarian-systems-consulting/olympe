//---------------------------------------------------------------------------
#include <vcl.h>
//#include <vcl\printers.hpp>   //???
#include <utilcls.h>         // CBuilder5 : pour pouvoir utiliser "OlePropertySet" (seb).
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Tableur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

/////////////////////////////////////////////////////////////////////////////////
///////////////////////STANDARD cf Impression////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
void CL_Excel::EcrireNomVC(CL_Agriculteur *agri) {
	CL_Item *critere;
	int i, n;
	bool trouve;
	CL_Categorie *categorie;
	EnTeteDate();
	fprintf(fichier, "Agriculteur;%s;\n", agri->Nom.c_str());
	fprintf(fichier, "N° Variante;%d", agri->NoVariante);
	fprintf(fichier, "\n");

	fprintf(fichier, "Critères;");
	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		categorie = V_CatTypeZone->Vecteur[n];
		fprintf(fichier, "%s;", categorie->Nom.c_str());
	}
	fprintf(fichier, "\n");

	fprintf(fichier, " ;");
	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		categorie = V_CatTypeZone->Vecteur[n];
		trouve = true;
		for (i = 0; i < agri->LstCritere->Count; i++) {
			critere = (CL_Item*) agri->LstCritere->Items[i];
			if (critere->Categorie == categorie) {
				fprintf(fichier, "%s;", critere->Nom.c_str());
				trouve = true;
			}
		}
		if (trouve == false)
			fprintf(fichier, " ;");
	}
	fprintf(fichier, "\n");

	if (agri->DefSim->PrixProd)
		fprintf(fichier, "Alea Prix Produit;  %s;",
				agri->DefSim->PrixProd->Nom.c_str());
	if (agri->DefSim->PrixCharge)
		fprintf(fichier, "Alea Prix Charge;   %s;",
				agri->DefSim->PrixCharge->Nom.c_str());
	if (agri->DefSim->QProd)
		fprintf(fichier, "Alea Rendement;     %s;",
				agri->DefSim->QProd->Nom.c_str());
	if (agri->DefSim->QCharge)
		fprintf(fichier, "Alea Quant Charge;  %s;",
				agri->DefSim->QCharge->Nom.c_str());
	if (agri->DefSim->QExt)
		fprintf(fichier, "Alea Externalité;   %s;",
				agri->DefSim->QExt->Nom.c_str());

	fprintf(fichier, "\n\n");
}
//--------------------------------------------------------------------------
void CL_Excel::Titre(int col, char *titre) {
	CelluleVide(0, col);
	fprintf(fichier, "%s;\n", titre);
}
//--------------------------------------------------------------------------
void CL_Excel::CelluleVide(int colDeb, int colFin) {
	int c;
	for (c = colDeb; c < colFin; c++)
		fprintf(fichier, "   ;");
}
//--------------------------------------------------------------------------
void CL_Excel::An(int colDeb, int an0) {
	CelluleVide(0, colDeb);
	for (int i = 0; i < N_X; i++)
		fprintf(fichier, "%4d;", an0 + i);
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::AnPluUn(int colDeb, int an0) {
	CelluleVide(0, colDeb);
	an0--;
	for (int i = 0; i < N_X + 1; i++)
		fprintf(fichier, "%4d;", an0 + i);
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::Blanc(int nli) {
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::Trait(void) {
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::TitreEtValeur(int c0, AnsiString titre, int c1, float *valeur) {
	int i, c;
	/// blancs initiaux
	for (c = 0; c < c0; c++)
		fprintf(fichier, "   ;");

	if (titre.Length())
		fprintf(fichier, "%s;", titre.c_str());
	else
		fprintf(fichier, "  ;");
	for (c = c0 + 1; c < c1; c++)
		fprintf(fichier, "   ;");
	if (valeur) {
		for (i = 0; i < N_X; i++)
			fprintf(fichier, "%8.2f;", valeur[i]);
	}
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::Resultat(int colDeb, AnsiString titre, AnsiString unite,
		float *valeur) {
	CelluleVide(0, colDeb);

	if (titre.Length())
		fprintf(fichier, "%s;", titre.c_str());
	else
		fprintf(fichier, "  ;");

	if (unite.Length())
		fprintf(fichier, "%s;", unite.c_str());
	else
		fprintf(fichier, "  ;");

	if (valeur) {
		for (int i = 0; i < N_X; i++)
			fprintf(fichier, "%8.2f;", valeur[i]);
	}
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::Resultat(int colDeb, AnsiString titre, float *valeur) {
	CelluleVide(0, colDeb);

	if (titre.Length())
		fprintf(fichier, "%s;", titre.c_str());
	else
		fprintf(fichier, "  ;");

	if (valeur) {
		for (int i = 0; i < N_X; i++)
			fprintf(fichier, "%8.2f;", valeur[i]);
	}
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::ResultatBilan(int colDeb, AnsiString titre, float *valeur,
		int nX) {
	int i;
	CelluleVide(0, colDeb);

	if (titre.Length())
		fprintf(fichier, "%s;", titre.c_str());
	else
		fprintf(fichier, "  ;");

	if (valeur) {
		if (nX == N_X)
			CelluleVide(6, 7); //A VOIR
		else
			CelluleVide(6, 6);
		for (i = 0; i < nX; i++)
			fprintf(fichier, "%8.2f;", valeur[i]);
	}
	fprintf(fichier, "\n");

}
//--------------------------------------------------------------------------
void CL_Excel::RBilan(int colDeb, AnsiString titre, float *valeur, int nX) {
	CelluleVide(0, colDeb);

	if (titre.Length())
		fprintf(fichier, "%s;", titre.c_str());
	else
		fprintf(fichier, "  ;");

	if (valeur) {
		if (nX == N_X)
			CelluleVide(1, 2); //A VOIR
//        else        CelluleVide(1,1);
		for (int i = 0; i < nX; i++)
			fprintf(fichier, "%8.2f;", valeur[i]);
	}
	fprintf(fichier, "\n");

}

