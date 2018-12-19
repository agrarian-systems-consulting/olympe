//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#pragma package(smart_init)
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"

#include "Tableur.h"
#include "TabCategorie.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//----------------------------------------------------------------------------
void CL_Excel::CatCulture(CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	int i, j;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	EnTeteDate();
//    fprintf(fichier,"\n");
//    fprintf(fichier,";");
	fprintf(fichier, "Nom;");
	fprintf(fichier, "Categorie;");
	fprintf(fichier, "\n");

	for (i = 0; i < V_Categorie->Nbelt; i++) {
		cat = V_Categorie->Vecteur[i];
		fprintf(fichier, "%s;", cat->Nom);
		fprintf(fichier, "\n");

		for (j = 0; j < V_Atelier->Nbelt; j++) {
			atelier = V_Atelier->Vecteur[j];
			if (atelier->NoCategorie == cat->No) {
				fprintf(fichier, "   ;");
				fprintf(fichier, "%s;", atelier->Nom);
				fprintf(fichier, "\n");
			}
		}
	}
}
//----------------------------------------------------------------------------
void CL_Excel::CatPerenne(CL_Vecteur<CL_Espece> *vEspece,
		CL_Vecteur<CL_Atelier> *vPerenne) {
	int i, j;
	CL_Atelier *atelier;
	CL_Espece *espece;
	EnTeteDate();
	fprintf(fichier, "Nom;");
	fprintf(fichier, "Categorie;");
	fprintf(fichier, "\n");

	for (i = 0; i < V_Espece->Nbelt; i++) {
		espece = V_Espece->Vecteur[i];
		fprintf(fichier, "%s;", espece->Nom);
		fprintf(fichier, "\n");

		for (j = 0; j < V_Atelier->Nbelt; j++) {
			atelier = V_Atelier->Vecteur[j];
			if (atelier->NoEspece == espece->No) {
				fprintf(fichier, "   ;");
				fprintf(fichier, "%s;", atelier->Nom);
				fprintf(fichier, "\n");
			}
		}
	}
}

