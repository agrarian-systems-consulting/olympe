#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "QuelExcelCSV.h"
#include "AgriSaisie.h"
#include "Tableur.h"
#include "Aide.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------
void CL_Excel::ResAgri(CL_Agriculteur *agri) {
	int i, n, nMax;
	CL_Elt *elt;
	char identifiant[200];

//	EnTete();
	CreerIdentifiantAgri(agri, identifiant);

	for (i = 0; i < V_Elt->Nbelt; i++) {
		fprintf(fichier, "%s", identifiant);
		elt = V_Elt->Vecteur[i];
		fprintf(fichier, "%4d;", elt->NoFamille);
		fprintf(fichier, "%4d;", elt->NoCategorie);
		fprintf(fichier, "%4d;", elt->NoType);
		fprintf(fichier, "%4d;", elt->NoItem);
		fprintf(fichier, "%s;", elt->Nom);
		fprintf(fichier, "%s;", elt->NomCat);
		fprintf(fichier, "%s;", elt->NomFamille);
		if (elt->Valeur) {
			if (elt->NoFamille == BILAN)
				nMax = N_X + 1;
			else
				nMax = N_X;
			for (n = 0; n < nMax; n++)
				fprintf(fichier, "%6.2f;", elt->Valeur[n]);
		}
		fprintf(fichier, "\n");

	}

}
//----------------------------------------------------------------------------
void CL_Excel::CreerIdentifiantAgri(CL_Agriculteur *agri, char *identifiant) {
	int i, n;
	char chaine[200];
	CL_Item *critere;
	CL_Categorie *cat;
	bool trouve;

	sprintf(identifiant, "%d;  %s;", agri->No, agri->Nom.c_str());

	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		trouve = false;
		cat = V_CatTypeZone->Vecteur[n];
		for (i = 0; i < agri->LstCritere->Count; i++) {
			critere = (CL_Item*) agri->LstCritere->Items[i];
			if (critere->Categorie == cat) {
				sprintf(chaine, "%s; %4d; ", critere->Nom, critere->No);
				i = agri->LstCritere->Count;
				trouve = true;
			}
		}
		if (trouve == false)
			sprintf(chaine, " ; ;");
		strcat(identifiant, chaine);
	}
	sprintf(chaine, "%2d;  %2d; %2d;", agri->NoVariante, agri->NbVariante,
			(int) agri->EstVariante);
	strcat(identifiant, chaine);
}
//----------------------------------------------------------------------------
void CL_Excel::EnTete(void) {
	int n;
	CL_Categorie *cat;
	if (fichier == NULL)
		return; // 100512
	fprintf(fichier, "NoAgri;");
	fprintf(fichier, "NomAgri;");
	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		cat = V_CatTypeZone->Vecteur[n];
		fprintf(fichier, " %s; N°Critere; ", cat->Nom.c_str());
	}
	fprintf(fichier, "N°Variante;");
	fprintf(fichier, "NbVariante;");
	fprintf(fichier, "EstVariante;");

	fprintf(fichier,
			"N°Famille;N°Categorie;N°Type;N°Item;Nom;NomCat;NomFamille");
	fprintf(fichier, "\n");
}

