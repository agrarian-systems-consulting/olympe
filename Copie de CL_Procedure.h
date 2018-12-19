//---------------------------------------------------------------------------

#ifndef CL_ProcedureH
#define CL_ProcedureH

#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <sysvari.h>
#include <vector.h>
using namespace std;

#include "DefProcedure.h"
#include "GereProcedure.h"

//---------------------------------------------------------------------------
class CL_EltProc: public CL_0 {
public:
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class CL_Procedure: public CL_0 {
public:
	CL_Procedure();
	CL_Procedure(AnsiString Nom);
	CL_Procedure(CL_Procedure *source);
	CL_Categorie *Categorie;
	int Cmp(CL_Procedure *ptr) {
		return 0;
	}
	; //non utilisé

	AnsiString AsExe;
	AnsiString AsFichier;
	AnsiString Note;
	CL_Vecteur<CL_EltProc> *V_EltP;

	void LireXml(_di_IXMLNode brancheProc);
//    void LireXml(void);
	void Afficher(TEdit *EdProc, TEdit *EdExe, TEdit* EdFich,
			TStringGrid *grille);
	void LireGrille(TEdit *EdProc, TEdit *EdExe, TEdit* EdFichier,
			TStringGrid *grille);
	void LireValeur(FILE *fichier, float *valeur);
	void LireFormule(FILE *fichier, CL_Formule *formule);
	void LireEnsemble(FILE *fichier, CL_Ensemble *ensemble);

	int TrouveValeur(CL_Agriculteur *agri, vector<CL_EltProc*> &vEltProc);
	int TrValAtelier(CL_Agriculteur *agri, CL_Vecteur<CL_Valeur>*vecteur,
			CL_EltProc *elt);
	int TrValItem(CL_Agriculteur *agri, CL_Vecteur<CL_Valeur>*vecteur,
			CL_EltProc *elt);
	int TrValFormule(CL_Agriculteur *agri, CL_Vecteur<CL_Formule>*vecteur,
			CL_EltProc *elt);
	bool FormuleModifiable(CL_Formule *formule);
	int TrValGlobal(CL_Agriculteur *agri, AnsiString NomDeLaListe,
			CL_EltProc *elt);
	int TrEffAssol(CL_EltProc *eltP);
	CL_Formule* TrouveFormule(AnsiString s, CL_EltProc *eltP);
	void MajFormule(CL_Formule *formule, int n, float val);

	void EcrireXml(_di_IXMLNode brancheCat, int p);
	void EcrireXmlTxt(ofstream &fichier);

	void Executer(vector<CL_Agriculteur*> vAgri);
	//données à traiter
	bool EcrireDonnees(vector<CL_EltProc*>);
	void LireDonnees(vector<CL_EltProc*> vEltProc);
//    void LireDonnees(void);

	void EcrireEnTete(FILE *fichier, CL_EltProc *eltP);
	void EcrireNom(AnsiString as, FILE *fichier);
	void EcrireEnsemble(CL_Ensemble *ensemble, FILE *fichier);

};
#endif
