//---------------------------------------------------------------------------

#ifndef CL_EltProcH
#define CL_EltProcH
#include "Olympedec.h"
#include "LesClassesApp.h"

//---------------------------------------------------------------------------
class CL_EltProc: public CL_0 {
public:
	friend bool operator <(const CL_EltProc&, const CL_EltProc&);
	CL_EltProc() {
		Agri = NULL;
		Nom = "";
		NomCategorie = "";
		NomFamille = "";
		NomNature = "";
		Valeur = NULL;
		Ensemble = NULL;
	}
	CL_EltProc(CL_EltProc* source) {
		Agri = source->Agri;
		Type = source->Type;
		Nom = source->Nom;
		NomCategorie = source->NomCategorie;
		NomFamille = source->NomFamille;
		NomNature = source->NomNature;
		Valeur = source->Valeur;
		Formule = source->Formule;
		Ensemble = source->Ensemble;
	}
	CL_EltProc(AnsiString nomNature, AnsiString nomFamille,
			AnsiString nomCategorie, AnsiString nomItem) {
		Agri = NULL;
		Nom = nomItem;
		NomCategorie = nomCategorie;
		NomFamille = nomFamille;
		NomNature = nomNature;
		Valeur = NULL;
		Ensemble = NULL;
	}
	int Cmp(CL_EltProc *ptr) {
		return 0;
	}
	; //non utilisé
	char Type; //F Formule  E Ensemble
	CL_Agriculteur *Agri;
	AnsiString Nom;
	AnsiString NomCategorie;
	AnsiString NomFamille;
	AnsiString NomNature;

	float *Valeur;
	CL_Formule *Formule;
	CL_Ensemble *Ensemble;

};

bool operator <(const CL_EltProc& eltP1, const CL_EltProc &eltP2) {
	if (eltP1.NomNature < eltP2.NomNature)
		return true;
	if (eltP1.NomNature > eltP2.NomNature)
		return false;

	if (eltP1.NomFamille < eltP2.NomFamille)
		return true;
	if (eltP1.NomFamille > eltP2.NomFamille)
		return false;

	if (eltP1.NomCategorie < eltP2.NomCategorie)
		return true;
	if (eltP1.NomCategorie > eltP2.NomCategorie)
		return false;

	if (eltP1.Nom < eltP2.Nom)
		return true;
	return false;
}

//---------------------------------------------------------------------------
#endif
