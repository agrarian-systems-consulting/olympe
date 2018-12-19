//---------------------------------------------------------------------------

#ifndef FichierEcrireXmlH
#define FichierEcrireXmlH
#include <iostream>
#include <fstream>
#include<string>
#include <stdio.h>
using namespace std;

class CL_Xml {
private:
//ofstream outfile;
	void LesProduits(ofstream &outfile);
	void LesTvaDefaut(ofstream &outfile);
	void EcrireFamilleItem(ofstream &fichier, CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Item> *vItem, char *nomFamille, int type = 3);
	//les bestiaux
	void EcrireFamilleBestiaux(ofstream &fichier,
			CL_Vecteur<CL_Categorie> *vCat, CL_Vecteur<CL_Bestiaux> *vItem,
			char *nomFamille);
	//culture animaux vivrier
	void EcrireFamilleAtelier(ofstream &fichier, CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Atelier> *vAtelier, char *nomFamille, char *nomType);

	//perenne
	void EcrireFamillePerenne(ofstream &fichier, CL_Vecteur<CL_Espece> *vCat,
			CL_Vecteur<CL_Atelier> *vAtelier, char *nomFamille, char *nomType);

	//indicateur
	void EcrireFamilleIndicateur(ofstream &fichier, char *nomFamille);

	//aleas
	void EcrireLesAleas(ofstream &fichier, char *nomFamille);

	//Agriculteur

public:
	CL_Xml(void) {
		An_0 = 0;
	}
	;
	char *NomFichier;
	int An_0;
//    ~CL_Xml(void);

	void EcrireLesTroupeaux(ofstream &outfile, TList *lst);

	void EcrireAgriPetit(ofstream &fichier, CL_Vecteur<CL_Petit>*vPetit);
	void EcrireV_InvSom(ofstream &fichier, CL_Vecteur<CL_FN_Xp1>*vecteur);
	void EcrireV_FinSom(ofstream &fichier, CL_Vecteur<CL_FN_Xp1>*vecteur);

	bool EstVide(float *valeur, int nMax);

	void baliseDebut(ofstream &fichier, char *nomBalise);
	void baliseDebut(ofstream &fichier, char *nomBalise, char *nomAttribut);
	void baliseDebut(ofstream &fichier, char *nomBalise, char *nomAttribut,
			AnsiString attribut);
	void baliseFin(ofstream &fichier, char *nomE);
	void baliseDebutFin(ofstream &fichier, char *nomBalise, char *nomAttribut,
			AnsiString nom);

	void finBalise(ofstream &fichier);
	// nom= valeur
	void ecrire(ofstream &fichier, char *nom, char *valeur);
	void ecrire(ofstream &fichier, char *nom, char valeur);
	void ecrire(ofstream &fichier, char *nom, AnsiString valeur);
	void ecrire(ofstream &fichier, char *nom, float valeur);
	void ecrire(ofstream &fichier, char *nom, int valeur);
	void ecrire(ofstream &fichier, char *nom, int val1, int val2);
	void ecrire(ofstream &fichier, char *nom, float *valeur, int nx);
	void ecrire(ofstream &fichier, char *nom, int *valeur, int nx);
	void ecrire(ofstream &fichier, char *nom, char *valeur, int nx);

	void ecrireTxt(ofstream &fichier, char *nom, AnsiString txt);

	// <nom> valeur </nom> endl
	void ecrireBalVal(ofstream &fichier, char *nom, float *valeur, int nx);

	void EcrireFichier(void);
	void LireFichier(void);

};
//---------------------------------------------------------------------------
#endif
