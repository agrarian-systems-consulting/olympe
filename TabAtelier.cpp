#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"

#include "Tableur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//----------------------------------------------------------------------------
void CL_Excel::Atelier(CL_Atelier *atelier) {
//    QuelExcelCSVFrm->ShowModal();
//    if(QuelExcelCSVFrm->Renonce==true) return;

	EnTeteDate();

	Titre(0, atelier->Nom.c_str());
	if (atelier->Nature != PERENNE)
		AtelierEnTete();
	else
		PerenneEnTete(atelier);
	Atelier1("Produits", atelier->V_Produit, atelier->NbPhase);
	Atelier1("Charges", atelier->V_Charge, atelier->NbPhase);
	AtelierVolume("Charges f(volume)", atelier->V_ChargeVolume,
			atelier->NbPhase);
	Atelier1("Externalités", atelier->V_Externalite, atelier->NbPhase);
	FermerFichier();
}
//----------------------------------------------------------------------------
void CL_Excel::AtelierEnTete(void) {
	fprintf(fichier, "\n");
	fprintf(fichier, ";");
	fprintf(fichier, "Nom;");
	fprintf(fichier, "Categorie;");
	fprintf(fichier, "Unité Atelier;");
	fprintf(fichier, ";");
	fprintf(fichier, "Avant 1;");
	fprintf(fichier, "1;");
	fprintf(fichier, "2;");
	fprintf(fichier, "\n");
}
//----------------------------------------------------------------------------
void CL_Excel::PerenneEnTete(CL_Atelier *atelier) {
	int p;
	int a0, a1;
	CL_Espece *espece = atelier->Espece;
	fprintf(fichier, "\n");
	fprintf(fichier, ";");
	fprintf(fichier, "Nom;");
	fprintf(fichier, "Categorie;");
	fprintf(fichier, "Unité Atelier;");
	fprintf(fichier, ";");
	fprintf(fichier, "Avant 1;");
	for (p = 0; p < atelier->NbPhase; p++) {
		a0 = espece->Phase[p];
		a1 = espece->Phase[p + 1];
		if (a1 == a0 + 1)
			fprintf(fichier, "  %2d;", a0);
		else
			fprintf(fichier, "  %2d et +;", a0);
	}
	fprintf(fichier, "\n");
}
//----------------------------------------------------------------------------
void CL_Excel::Atelier1(char *titre, CL_Vecteur<CL_ItemParAtelier>*vecteur,
		int nbPhase) {
	int i, j;
	CL_ItemParAtelier *itemPA;
	if (vecteur->Nbelt == 0)
		return;

	fprintf(fichier, "%s\n", titre);
	for (i = 0; i < vecteur->Nbelt; i++) {
		fprintf(fichier, " ;");
		itemPA = vecteur->Vecteur[i];
		fprintf(fichier, "%s;", itemPA->Item->Nom);
		fprintf(fichier, "%s;", itemPA->Item->Categorie->Nom);
		fprintf(fichier, "%s;", itemPA->Item->SysUnite->UUt);
		fprintf(fichier, ";");

		for (j = 0; j < nbPhase; j++)
			fprintf(fichier, "%8.2f;", itemPA->QtePhase[j]);
		fprintf(fichier, "\n");
	}
}
//----------------------------------------------------------------------------
void CL_Excel::AtelierVolume(char *titre, CL_Vecteur<CL_ItemParAtelier>*vecteur,
		int nbPhase) {
	int i, j;
	CL_ItemParAtelier *itemPA, *produitA;
	CL_Item *produit, *charge;
	if (vecteur->Nbelt == 0)
		return;

	fprintf(fichier, "%s\n", titre);
	for (i = 0; i < vecteur->Nbelt; i++) {
		fprintf(fichier, " ;");
		itemPA = vecteur->Vecteur[i];
		produitA = itemPA->ItemPA;
		produit = produitA->Item;
		charge = itemPA->Charge;
		fprintf(fichier, "%s;", produit->Nom);
		fprintf(fichier, "%s;", produit->SysUnite->UUt);
		if (charge == NULL)
			fprintf(fichier, " ; ;");
		else {
			fprintf(fichier, "%s;", charge->Nom);
			fprintf(fichier, "%s;", charge->SysUnite->UUt);
		}
		for (j = 0; j < nbPhase; j++)
			fprintf(fichier, "%8.2f;", itemPA->QtePhase[j]);
		fprintf(fichier, "\n");
	}
}
