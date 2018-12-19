//---------------------------------------------------------------------------
#ifndef TableurH
#define TableurH
#include <vcl.h>
//------------------------------------------------------------------------------
class CL_Excel {
public:

	CL_Excel(void);
	~CL_Excel(void);
	/// ouvert dans QuelExcelCSV
	FILE *fichier;
	void EnTeteDate(void);

	void EcritGrille(TStringGrid *grille);
//        void LitGrille(TStringGrid *grille);

	bool RowVide(TStringGrid *grille, int row);

	void EcritGrilleFichier(TStringGrid *grille, AnsiString TitreGrille);
	void FermerFichier(void);

	void EcrireNomVC(CL_Agriculteur *agri);
	void Titre(int col, char *titre);
	void CelluleVide(int colDeb, int colFin);

	void Nom(char *titre, TColor = clBlack);
	void An(int colDeb, int an0);
	void AnPluUn(int colDeb, int an0);

	void Blanc(int nli = 1);
	void Trait(void);
	void TitreEtValeur(int c0, AnsiString titre, int c1, float *valeur);
	void Resultat(int colDeb, AnsiString nom, AnsiString unite, float *valeur);
	void Resultat(int colDeb, AnsiString nom, float *valeur);
	void ResultatBilan(int colDeb, AnsiString titre, float *valeur, int nX);
	void RBilan(int colDeb, AnsiString titre, float *valeur, int nX);

	//TabResultat
	void Quantite(CL_Agriculteur *agri);
	void Valeur(CL_Agriculteur *agri);
	void GrandsPostes(CL_Agriculteur *agri);
	void Synthese(CL_Agriculteur *agri);
	void CategorieQ(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vQuanVal);
	void CategorieV(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit, float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);

	void CategorieVTotal(char *titre, CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit, float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);

	void Tva(CL_Agriculteur *agri);
	void Externalite(CL_Agriculteur *agri);

	//TabEtat
	void Etat(CL_Agriculteur *agri, CL_EtatSortie *etat);
	// TabComparaison
	void Comparaison(CL_EtatSortie *serieComp, TList *lstElt, int an_0);

	//TabFinance
	void Finance(CL_Agriculteur *agri);
	void ImpFinance(CL_TotEmp *totEmp, char *titre);
	void ImpPlacement(CL_TotEmp *totEmp, char *titre);

	//TabImmo
	void Immo(CL_Agriculteur *agri);
	void ImpImmo(CL_TotImmo *totImmo, char *titre);
	void ImpPetit(CL_TotImmo *totImmo, char *titre);

	//TabAtelier
	void Atelier(CL_Atelier *atelier);
	void AtelierEnTete(void);
	void PerenneEnTete(CL_Atelier *atelier);

	void Atelier1(char *titre, CL_Vecteur<CL_ItemParAtelier>*vecteur,
			int nbPhase);
	void AtelierVolume(char *titre, CL_Vecteur<CL_ItemParAtelier>*vecteur,
			int nbPhase);
	//TabCompta
	void Ceg(CL_Agriculteur *agri);
	void Bilan(CL_Agriculteur *agri);
	void Famille(CL_Agriculteur *agri);

	void ResAgri(CL_Agriculteur *agri);
	void CreerIdentifiantAgri(CL_Agriculteur *agri, char *identifiant);
	void EnTete(void);
	//TabCategorie
	void CatCulture(CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_Atelier> *vCulture);
	void CatPerenne(CL_Vecteur<CL_Espece> *vEspece,
			CL_Vecteur<CL_Atelier> *vPerenne);

	bool EstVide(float *valeur);
};

//---------------------------------------------------------------------------
#endif
