#include <vcl.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//---------------------------------------------------------------------------
#ifndef CompilateurH
#define CompilateurH

//---------------------------------------------------------------------------
#define VIDE 0

// 2 fevrier 2000

/* ======================== Les Codes des Mots Clés =======================*/

class CL_Compil {
private:
	bool EstInitialise;
	bool TestCompil;
	TStringList *Lexique;
	int Annee;

	CL_Agriculteur *Agri;

	unsigned char *Flot;
	int Pos;
	int LeMot;
	float Valeur;
	int NoFamille, NoCategorie, NoItem, NoType;
	AnsiString TxtArbre;
	AnsiString TxtReseau;
	void impLeMot(char *ouJeSuis, ofstream &outfile);
	void instruction(ofstream &outfile);

	void casSimple(void);

	int expressionAdd(ofstream &outfile);
	int expressionMul(ofstream &outfile);
	int expressionNum(ofstream &outfile);
	int unIdent(ofstream &outfile);
	int unTotal(ofstream &outfile);

	int uneAnnee(ofstream &outfile);
	//extression conditionnelle
	int blocSI(int reseau, ofstream &outfile);
	int suiteSI(int reseau, ofstream &outfile);

	int conditionOU(ofstream &outfile);
	int conditionET(ofstream &outfile);
	int expressionComp(ofstream &outfile);

	int stockBranche(int code, int a0, int a1, int a2, int type, int date = 0);
	void reallouerArbre(void);
	void reallouerReseau(void);

	void ecrireReseau(ofstream &outfile);

//    int   stockReseau( int code, int numero,int arbre, int avant);
	int stockMaille(int code, int arbre, int avant);
	int stockMailleSI(int branche, int avant);
	int stockMaillePont(int reseau_g, int reseau_d);

	char* nomSymbole(int n);

	float operande(void);

	//analex
	int analex(void);
	int anaTexte(void);
	bool estSeparateur(int pos);
	int estMotCle(void);
	int lireNombre(void);

	int lireIdent(char *mot);
	int trouveTypeAnimaux(AnsiString nomType);

	int lireTotal(void);

	void lireNom(AnsiString nom);
	AnsiString lireNom(char *mot, int &pos);
	bool lire2Points(void);

	int erreur(char *message);

	int trouveElt(AnsiString nomItem);
	int trouveElt(AnsiString nomFamille, AnsiString nomItem);
	int trouveElt(AnsiString nomFamille, AnsiString nomCategorie,
			AnsiString nomItem);
	int trouveElt(int noFamille, AnsiString nomCategorie, int type,
			AnsiString nomItem);
	int trouveEltFamCat(AnsiString nomFamille, AnsiString nomCategorie);
//    CL_Elt *trouveElt(int noFam,int noCat,int noItem);

//calcul
	bool traiterArbre(CL_Arbre *arbre, int n, int i, float &res); //101002
	float Sigma(int i, int noFam, int noCat);
	float CL_Compil::TotalSurface(int ex);
	void traiterReseau(CL_Reseau *reseau, CL_Arbre *arbre, int m, int an,
			float &resultat); //121102
	int traiterMaille(CL_Reseau *reseau, CL_Arbre *arbre, int m, int an,
			float &resultat); //121102

//??	float* trouveValElt(int noFam,int noCat,int noItem);

	//EtablitFormule
	int LongTxtMax;
	bool deLArbre(int i, int opPrec);
	bool parenthese(int opPrec);

	void ecritElt(int noFam, int noCat, int noItem);
	void ecritSigma(int noFam, int noCat);
	void reEcritReseau(int i, int prec);
	void reEcritArbre(int n);
	void Decoupe(char op, int n0, int nMax);
	void trouveParFermante(int &n0);

	/*
	 TRichEdit *RE;
	 void deLArbreRE      (int i,int opPrec);
	 void ecritEltRE      (int noFam,int noCat,int noItem);
	 void ecritSigmaRE    (int noFam,int noCat);
	 void reEcritReseauRE (int i, int prec);
	 void reEcritArbreRE  (int n);
	 */

public:
	CL_Arbre *Arbre;
	CL_Reseau *Reseau;
	AnsiString JeTraite;

	CL_Compil() {
		EstInitialise = false;
	}
	bool Erreur;
	void IniLexique(void);
	CL_Prog *CreeProg(int noFamille, CL_Item *item);
	CL_Prog *CreeProgQuantPrix(int QXX, int PXX, CL_Item *item);
	CL_Prog *CreeProgVal(int QXX, CL_Item *item);

	float DepouilleFormule(CL_Agriculteur *agri, int an, char *flot);
	void Compiler(char *flot);
	bool Calculer(CL_Reseau *Reseau, CL_Arbre *Arbre, int iDeb, int iFin,
			float *valeur);

//	void  Calculer(CL_Reseau *Reseau,CL_Arbre *Arbre,int iDeb,int iFin);
	void ecrireArbre(ofstream &outfile);
	int isalnumA(unsigned char c);
	void ReEcritFormule(CL_Prog *prog);
//    void  ReEcritFormuleRE(CL_Prog *prog,TRichEdit *RE);//RE
	CL_Elt *trouveElt(int noFam, int noCat, int noItem); //utilisé dans AgriSaisieCalcul
														 //AgriSaisieFormule

};
enum {
	ERREUR = 300, NOMBRE, NUM, BOOLEEN, FIN, INFEG, SUPEG, MUNAIRE, PONT,
//      IDENT=310 cf olympedec.h
	ET = 320,
	OU,
	SI,
	SINON,
	SINONSI,
	SIGMA,
	AN,
	LOG,
	EXP,
	TOTSUR
};
/*
 enum { OPERATEUR = 300, ET, OU, SAUF, PARMI, INFEG, SUPEG, MUNAIRE,
 SI, SINON, SINONSI,
 PONT, NUM, DDATE, LISTE,ARBRE,RESEAU,BBOOL,
 PHASE,S_PHASE,OPERATION,GRAPHIQUE,PROP,
 FONCTION = 400, MAX,MIN,MOY,                //max(x,y)
 VALMIN,VALMAX,VALMOY,      // max(amor(n1,n2))
 TENDANCE,HAUSSE,BAISSE,STABLE,
 VRAI,FAUX,INCO,_OUI,_NON,    //OUI,NON,d‚j… d‚fini dans les grignon's
 I_NET_O,I_NET_P,
 B_MIN,B_MAX,
 D_INV,EMPR_E,EMPR_P,EMPR_EX,EMPR_PX,
 PLACER_E,PLACER_P,PLACER_EX,PLACER_PX,
 TEL_QUE,
 R_INV_O,R_INV,
 CT,MT,LT,
 //Postes
 // 1    2       3       4       5        6      7
 ACHAT=500,   AMOR,V_RESID,REVENTE,CAPITAL,DETTE_LT,DETTE_CT,CAP_REMB,
 //8       9          10               11     12
 INTERET,CHARGE_OPE,AUTRE_CHARGE_STR,PRIVE_APP,
 //13         14           15       16        17
 PRIVE_PREL,TRESORERIE,TRESORERIE_Q,RESULTAT,CHARGE_STR,
 //18
 RUBRIQUE_X,
 //19          20          21          22
 PLACT_VAL_P,PLACT_INT_P,PLACT_NOUV_P,PLACT_REMB_P,
 //23          24          25         26
 PLACT_VAL_E,PLACT_INT_E,PLACT_NOUV_E,PLACT_REMB_E,
 // 27  28     29     30     31     32
 T_E_CT,T_E_MT,T_E_LT,T_P_CT,T_P_MT,T_P_LT,
 //Tableaux de saisie   33  34      35       36    37     38      39      40
 T_PROD,T_CH_OP,T_CH_STR,T_APP,T_PREL,T_AUTRE,T_EVENT,T_VAR,
 //                  41
 TABLEAU,
 //Inventaire       51      52      53
 INV_ANI=550,INV_PRO,INV_CHA,INV_TOT,
 //                  54        55        56        57
 D_INV_ANI,D_INV_PRO,D_INV_CHA,D_INV_TOT,
 //                  58        59        60        61        62        63
 T_INV_ANI,T_INV_PRO,T_INV_CHA,T_VAR_ANI,T_VAR_PRO,T_VAR_CHA,
 //                  64
 SUB_RECUE,SUB_AMOR,SUB_RESID,
 //                  66
 T_INV_ANI_E,T_INV_ANI_A,T_INV_ANI_V,
 IDENT=600,ID_INDIC_NUM,ID_INDIC_BOOL,ID_OPER,ID_PHASE,
 ID_S_PHASE,ID_GRAPHIQUE,ID_PROP,ID_ELT,ID_TBORD,ID_ETAT,
 ACTION,ID_TEXTE,ID_QUEST,ID_COMP,ID_FONC,
 UNITE    = 700, FRANC,KFRANC,MFRANC,
 TILT     = 800, OK,
 // complements emprunts
 CAP_LT   =900,CAP_CT ,DETTE ,CAP_R_LT  ,CAP_R_CT,INT_LT     ,INT_CT,
 CAP_E  ,CAP_LT_E  ,CAP_CT_E  ,DETTE_E ,DETTE_LT_E ,DETTE_CT_E,
 CAP_R_E,CAP_R_LT_E,CAP_R_CT_E,INT_E   ,INT_LT_E   ,INT_CT_E,
 CAP_P  ,CAP_LT_P  ,CAP_CT_P  ,DETTE_P ,DETTE_LT_P ,DETTE_CT_P,
 CAP_R_P,CAP_R_LT_P,CAP_R_CT_P,INT_P   ,INT_LT_P   ,INT_CT_P,
 PLACT_VAL ,PLACT_INT ,PLACT_NOUV ,PLACT_REMB,
 SOLDE_P ,PLUS_VAL,OCCC,
 AMOR_V,V_RESID_V,P_IMMO_V,PERTE_V
 };
 */

#endif
