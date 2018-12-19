//---------------------------------------------------------------------------
#ifndef ImpressionH
#define ImpressionH
//---------------------------------------------------------------------------
void ImprimerLesDonnees(void);
class CL_Imp {
public:
//	void ResultatAgriValeur(CL_Agriculteur *agri);
//	void ResultatAgriQuantite(CL_Agriculteur *agri);
//	void ResultatAgriExternalite(CL_Agriculteur *agri);
//    void Finance(CL_Agriculteur *agri);
//    void ImpFinance(CL_TotEmp *totEmp,char *titre);
//    void ImpPlacement(CL_TotEmp *totEmp,char *titre);

	void Immo(CL_Agriculteur *agri);
	void ImpImmo(CL_TotImmo *totImmo, char *titre);
	void ImpPetit(CL_TotImmo *totImmo, char *titre);

	/*
	 void Quantite(CL_Agriculteur *agri);
	 void CategorieQ(
	 char *titre,
	 CL_Vecteur<CL_Categorie>      *vCategorie,
	 CL_Vecteur<CL_QuanVal>        *vQuanVal);
	 void Valeur(CL_Agriculteur *agri);
	 void  CL_Imp::CategorieV(
	 char *titre,
	 CL_Vecteur<CL_Categorie>      *vCategorie,
	 CL_Vecteur<CL_Formule>        *vFormule,
	 float *total,
	 CL_Vecteur<CL_QuanVal>        *vCatTot);

	 void Externalite(CL_Agriculteur *agri);
	 */
	/*
	 void Val1(char *titre,
	 CL_Vecteur<CL_Categorie> *vCategorie,
	 CL_Vecteur<CL_QuanVal>   *vCatTot,
	 CL_Vecteur<CL_QuanVal>   *vQuanVal,
	 float *total);

	 void Val2(char *titre,CL_Vecteur<CL_Formule> *vecteur,float *total);
	 */

};

#endif
