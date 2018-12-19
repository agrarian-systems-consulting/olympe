#include <iostream>
#include <fstream>
#include <vcl.h>
#pragma hdrstop
using namespace std;
#include "LesClassesApp.h"

//---------------------------------------------------------------------------

#ifndef CL_MvtAnneeH
#define CL_MvtAnneeH
//---------------------------------------------------------------------------
class CL_MvtAnnee {
public:
	CL_MvtAnnee();
	void CopieVers(CL_MvtAnnee *vers);
	void Maz(void);
	void Lister(ofstream &outfile);
	void Nettoyer(AnsiString aFaire);
	CL_Bestiaux *Animal;
	int Debut, Fin;
	int Ne, Mort;

	int Vente[3], iVente, iRegul;
	float PrixVente[3];
	int TotVente;
	float ValVente;

	int Achat[3], iAchat, iAchatAuto;
	float PrixAchat[3];
	int TotAchat;
	float ValAchat;

	int Entree[3], Origine[3], iOr;
	int Sortie[3], Destin[3], iDest;
	bool EntreeTout[3];
	bool SortieTout[3]; //true on cliqué sur Tout je prends tous les animaux
	// de l'origine

	bool ADescendance;
	int DonneNo[4];
	float DonnePcent[4];

	//les fonctions
	void Solde(void); //doit remplacer EffFin
	int Dispo(int noDest);
	bool EstVide(void);
	int DonneiRegul(void);
	int DonneiAchatAuto(void);

};

#endif
