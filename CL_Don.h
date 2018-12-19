//---------------------------------------------------------------------------

#ifndef CL_DonH
#define CL_DonH
#include <vector.h>
#include <algorithm>

using namespace std;
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_EltProc.h"

//---------------------------------------------------------------------------
class CL_Don {
public:
	CL_Don(void);

	void CreeV(vector<CL_EltProc*> v, CL_Agriculteur *agri = NULL);void __fastcall EcrireDonnees(vector<CL_EltProc*> v,AnsiString AsFichier);
private:
	vector<CL_EltProc*> V0;
	vector<CL_EltProc*> V1;

	void __fastcall CreeVAtelier(vector<CL_EltProc*> &v,
			AnsiString nomNature,AnsiString nomFamille,
			CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCat,
			CL_Agriculteur *agri);

	void __fastcall CreeVItem(vector<CL_EltProc*> &v,
			AnsiString nomNature,AnsiString nomFamille,
			CL_Vecteur<CL_Item> *vecteur,CL_Vecteur<CL_Categorie> *vCat,
			CL_Agriculteur *agri);

	void __fastcall CreeVTendance(vector<CL_EltProc*> &v,
			AnsiString nomNature,AnsiString nomFamille,
			CL_Vecteur<CL_Tendance> *vecteur,CL_Vecteur<CL_Categorie> *vCat,
			CL_Agriculteur *agri);

	void __fastcall TriVector(vector<CL_EltProc*> &v);

	int __fastcall Comp(const CL_EltProc& eltP1,const CL_EltProc &eltP2);

	CL_EltProc* __fastcall cherche(vector<CL_EltProc*> &v,const CL_EltProc &eltP);

};
#endif
