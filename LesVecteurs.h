#ifndef LesVecteursH
#define LesVecteursH
class CL_Procedure;
// penser a mettre dans LesVecteurs.hse

// à initialiser dans main
CL_Vecteur<CL_SystemeUnite> *V_SystemeUnite;
CL_Vecteur<CL_Tva> *V_Tva;

CL_Vecteur<CL_Categorie> *V_Categorie; //représente un vecteur quelconque ci dessous
CL_Vecteur<CL_Categorie> *V_CatProduit;
CL_Vecteur<CL_Categorie> *V_CatCharge;
CL_Vecteur<CL_Categorie> *V_CatBestiaux; //101201
CL_Vecteur<CL_Categorie> *V_CatExternalite;

CL_Vecteur<CL_Categorie> *V_CatCulture;
CL_Vecteur<CL_Categorie> *V_CatAnimaux;
CL_Vecteur<CL_Categorie> *V_CatVivrier;

CL_Vecteur<CL_Categorie> *V_CatChStruct;
CL_Vecteur<CL_Categorie> *V_CatRecDiv;
CL_Vecteur<CL_Categorie> *V_CatDepDiv;
CL_Vecteur<CL_Categorie> *V_CatRecFam;
CL_Vecteur<CL_Categorie> *V_CatDepFam;

CL_Vecteur<CL_Categorie> *V_CatTypeZone;

CL_Vecteur<CL_Categorie> *V_CatIndic;
CL_Vecteur<CL_Categorie> *V_CatEtatSortie;
CL_Vecteur<CL_Categorie> *V_CatSerieComp;
CL_Vecteur<CL_Categorie> *V_CatProcedure;

CL_Vecteur<CL_Item> *V_Item; //représente un vecteur quelconque ci dessous
CL_Vecteur<CL_Item> *V_Charge;
CL_Vecteur<CL_Item> *V_Produit;
CL_Vecteur<CL_Bestiaux> *V_Bestiaux; //260903
CL_Vecteur<CL_Item> *V_Externalite;

CL_Vecteur<CL_Atelier> *V_Atelier; //représente un vecteur quelconque ci dessous
CL_Vecteur<CL_Atelier> *V_Culture;
CL_Vecteur<CL_Atelier> *V_Animaux;
CL_Vecteur<CL_Atelier> *V_Vivrier;
CL_Vecteur<CL_Atelier> *V_Perenne;

CL_Vecteur<CL_Espece> *V_Espece;

CL_Vecteur<CL_Item> *V_ChStruct;
CL_Vecteur<CL_Item> *V_RecDiv; //Recette Entreprise
CL_Vecteur<CL_Item> *V_DepDiv; //Depense

CL_Vecteur<CL_Item> *V_RecFam; //Recette Famille
CL_Vecteur<CL_Item> *V_DepFam; //Depense

CL_Vecteur<CL_Item> *V_TypeZone;

CL_Vecteur<CL_Categorie> *V_CatVar; //Categories de Variables
CL_Vecteur<CL_Item> *V_Variable; //Variables

CL_Vecteur<CL_Calendrier> *V_Calendrier;

CL_Vecteur<CL_Agriculteur> *V_Agriculteur;
CL_Vecteur<CL_Ensemble> *V_Ensemble;

CL_Vecteur<CL_Categorie> *V_CatRepart;
CL_Vecteur<CL_Repart> *V_Repart; //240203

CL_Vecteur<CL_EtatSortie> *V_EtatSortie;
CL_Vecteur<CL_EtatSortie> *V_SerieComp;
CL_Vecteur<CL_Procedure> *V_Procedure;

CL_Vecteur<CL_Indicateur> *V_Indicateur;

CL_Vecteur<CL_Elt> *V_Intitule;
CL_Vecteur<CL_Poste> *V_Poste;
CL_Vecteur<CL_Elt> *V_Elt;

CL_Elt *EltTrait;
CL_Elt *EltBlanc;
CL_Elt *EltTitre;

CL_Agriculteur *AgriEnCours;
CL_Ensemble *EnsembleEnCours;
CL_SystemeUnite *SysMonnaie;

CL_Vecteur<CL_Categorie> *V_CatDico;
CL_Vecteur<CL_Item> *V_Dico;

int Global; //AGRI 18 TOTAL 1 MOYENNE 2 ENSEMBLE 3
CL_Tva *TvaDefaut;
CL_Tva *TvaImmo;

CL_Vecteur<CL_Tendance> *V_TendPrixProd;
CL_Vecteur<CL_Tendance> *V_TendPrixCharge;
CL_Vecteur<CL_Tendance> *V_ScenPrixProd;
CL_Vecteur<CL_Tendance> *V_ScenPrixCharge;

CL_Vecteur<CL_Tendance> *V_TendQProd;
CL_Vecteur<CL_Tendance> *V_TendQCharge;
CL_Vecteur<CL_Tendance> *V_ScenQProd;
CL_Vecteur<CL_Tendance> *V_ScenQCharge;
CL_Vecteur<CL_Tendance> *V_TendQExt;
CL_Vecteur<CL_Tendance> *V_ScenQExt;

CL_Vecteur<CL_AgriDefSim> *V_DefSim;

AnsiString Notes;
CL_Conversion *Conversion;
CL_Vecteur<CL_Conversion> *V_Conversion;
AnsiString ExcelExe;

TStringList *LstNom;

char CarConst = 'C';
char CarVar = 'V';
char CarDif = 'D';

char CarMens = 'M';
char CarSem = 'S';
char CarTrim = 'T';
char CarAn = 'A';

char CarPreCompte = 'P';
char CarNonPrecompte = 'N';

char CarEnt = 'E';
char CarPrive = 'P';

char CarPlactFin = 'F';
char CarPlactAn = 'A';

char CarDeg = 'D';
char CarLin = 'L';
char CarSans = 'N';

// ESSAI !
// TStringGrid* LaGrille;
//.....
/*------->
 CL_Vecteur<CL_NomCibleAlea> *V_NomCibleAlea;

 CL_Vecteur<CL_TypeAlea>     *V_TypeAlea;
 CL_Vecteur<CL_FamilleAlea>  *V_FamilleAlea;
 CL_Vecteur<CL_Alea>         *V_Alea;

 CL_Vecteur<CL_Simu>         *V_Simu;
 ------->*/
#endif

