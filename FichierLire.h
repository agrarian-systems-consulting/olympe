//---------------------------------------------------------------------------
#ifndef FichierLireH
#define FichierLireH
#include <iostream>
#include <fstream>
#include <string>
#include <vcl.h>
#include <stdio.h>
using namespace std;

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "CL_BesTrav.h"

//---------------------------------------------------------------------------
class CL_ES {
public:
	CL_ES(void);
	~CL_ES(void);
	FILE *fichier;
	ofstream outfile;
	int Version; //Version En Cours
	int version; //version du fichier;
	int Verrou; //STANDARD MEDTER  interdit d'entrer des données
	AnsiString FLecture;
	AnsiString FEcriture;
	AnsiString FExcel;
	bool StockagePermis;

//    float ValZero[N_X];
	void IniNouveau(void);
	void Purge(void);
	void Supprimable(void);

	void V_CalendrierSupMazTrue(void); //060406
	void MaFalseBesTrav(CL_Atelier *atelier); //060406

	void IndicateurSupMaFalse(void);
	void IndicFormuleNonSup(CL_Vecteur<CL_Formule>*vecteur);

	void EtatSortieSupMaFalse(CL_Vecteur<CL_EtatSortie> *v_Etat);
//	void EtatSortieSupMaFalse(void);
	void TendanceMaFalse(CL_Vecteur<CL_Tendance> *v_Tendance);

	void IniSysUnit(char *uUt, char *uTrans, char *uGlobal, float ratio,
			float ratioG);
	void IniTva(char *nom, float taux);

//	void IniCategorie(CL_Vecteur<CL_Categorie> *vecteur,char *nom);
	void IniCategorie(CL_Vecteur<CL_Categorie> *vecteur, AnsiString nom);
	void IniItem(CL_Vecteur<CL_Item> *vecteur, char *nom);
	void IniType(CL_Vecteur<CL_Item> *vecteur, char *nom);
	void DefNoCategorie(CL_Vecteur<CL_Item> *vecteur);
	void DefNoCategorie108(CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Item> *vecteur);

	int lireFichier(bool tout);
	bool ecrireFichier(void);
	bool AStocker;
	void freadString(AnsiString &s);
	void fwriteString(AnsiString s);
	void BkpFic(void);
	void VerifNumeroAgri(void);

	void EcrireZero(void);

	void EcrireSystemeUnite(void);
	void LireSystemeUnite(int version);
	void LireSystemeUnite103(void);

	void EcrireTva(void);
	void LireTva(void);
	void LireTva103(void);

	void EcrireCategorie(CL_Vecteur<CL_Categorie> *vecteur);
	void LireCategorie(CL_Vecteur<CL_Categorie> *vecteur, int version); //020507

//    void LireCategorieT  (CL_Vecteur<CL_Categorie> *vecteur);//!!

	void EcrireItem(CL_Vecteur<CL_Item> *vecteur);
	void EcrireBestiaux(CL_Vecteur<CL_Bestiaux> *vecteur); //190802
	void LireItem(CL_Vecteur<CL_Item> *vecteur);
	void LireItem(CL_Vecteur<CL_Item> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);

	void LireBestiaux127(CL_Vecteur<CL_Bestiaux> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie); //190802
	void LireBestiaux(CL_Vecteur<CL_Bestiaux> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie); //190802
	void MajV_Bestiaux(CL_Vecteur<CL_Bestiaux> *vecteur);

	void EcrireAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void LireAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteur);

	void EcrireAtelier(CL_Vecteur<CL_Atelier> *vecteur);
	void LireAtelier119(CL_Vecteur<CL_Atelier> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie); //250901
	void LireAtelier119(CL_Vecteur<CL_Atelier> *vecteur,
			CL_Vecteur<CL_Espece> *vCategorie); //250901
	void LireAtelier122(CL_Vecteur<CL_Atelier> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie); //300111
	void LireAtelier122(CL_Vecteur<CL_Atelier> *vecteur,
			CL_Vecteur<CL_Espece> *vCategorie); //300111
	void MajAtelierItem122(CL_Vecteur<CL_ItemParAtelier> *vecteur, int nbPhase);
	void LireAtelier(CL_Vecteur<CL_Atelier> *vecteur, int nature,
			CL_Vecteur<CL_Categorie> *vCategorie, int version); ///030604
	void LireAtelier(CL_Vecteur<CL_Atelier> *vecteur, int nature,
			CL_Vecteur<CL_Espece> *vCategorie, int version); ///030604

	void EcrireAtelierAvance(CL_Vecteur<CL_EEF> *vecteur); //190802
	void LireAtelierAvance(CL_Vecteur<CL_EEF> *vecteur);

	void EcrireAtelierBesTrav(CL_Vecteur<CL_BesTrav> *vecteur);
	void LireAtelierBesTrav(CL_Vecteur<CL_BesTrav> *vecteur);

	void EcrireAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteur, int nbPhase);
	void LireAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteur, int nbPhase);

	void AdresseAtelier(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
			CL_Vecteur<CL_Item> *vecteur);
	void AdresseAtelier(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
			CL_Vecteur<CL_ItemParAtelier> *vecteurP,
			CL_Vecteur<CL_Item> *vecteurC);

	void EcrireEspece(void);
	void LireEspece(int version);

	void EcrireType(CL_Vecteur<CL_Item> *vecteur);
	void LireType(CL_Vecteur<CL_Item> *vecteur);

	void EcrireCalendrier(void);
	void LireCalendrier(int version);
	void EcrirePeriode(CL_Periode *periode);
	void LirePeriode(CL_Periode *periode);

	void LireConversion119(void);
	void LireConversion(void);
	void EcrireConversion(void);

	// Agriculteurs
	void EcrireAgriculteur(void);
	void LireAgriculteur(void);

	void EcrireAgriDefSim(CL_AgriDefSim *defSim);
	void LireAgriDefSim(CL_AgriDefSim *defSim);
	void LireAgriDefSim110(CL_AgriDefSim *defSim);

	void TrouveTendScen(CL_AgriDefSim *defSim);

	void EcrireLesDefSim(void);
	void LireLesDefSim(void);

	void CreeAgriDefSim(CL_AgriDefSim *defSim);

	void EcrireAgriValeur(CL_Vecteur<CL_Valeur> *vecteur);
	void EcrireAgriInvAni(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni); //11 06 00
	void LireAgriInvAni126(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni); //091002
	void LireAgriInvAni129(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni); //091002
	void LireAgriInvAni(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni); //091002

	void EcrireAgriFormule(CL_Vecteur<CL_Formule> *vecteur);
	void EcrireFormule(char **LesChaines);

	void LireAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur);
	void LireAgriFormule104(CL_Vecteur<CL_Formule> *vecteur, int noFamille);
	void LireAgriFormule105(CL_Vecteur<CL_Formule> *vecteur);
	void LireAgriFormule114(CL_Vecteur<CL_Formule> *vecteur);
	void LireAgriFormule(CL_Vecteur<CL_Formule> *vecteur);
	void LireFormule100(CL_Formule *formule);
	void trouveItemFormule(CL_Formule *formule);

	void LireFormule(char **LesChaines);

	void LireAgriValeurItem(CL_Vecteur<CL_Valeur> *vecteur);

	void EcrireAgriTroupeau(TList *lst);
	void LireAgriTroupeau(TList *lst);

	void EcrireAgriVerger(CL_Vecteur<CL_Verger> *vecteur);
	void LireAgriValeurVerger(CL_Vecteur<CL_Verger> *vecteur);

	void EcrireAgriEmpLT(CL_Vecteur<CL_EmpLT> *vecteur);
	void EcrireAgriEmpCT(CL_Vecteur<CL_EmpCT> *vecteur);
	//void EcrireAgriSub        (CL_Vecteur<CL_Sub>   *vecteur);        //190412
	bool EcrireAgriSub(CL_Vecteur<CL_Sub> *vecteur);
	void EcrireAgriPlact(CL_Vecteur<CL_Plact> *vecteur);
	void EcrireAgriOccc(CL_Vecteur<CL_Occc> *vecteur);

	void EcrireAgriImmo(CL_Vecteur<CL_Immo> *vecteur);
	void EcrireAgriPetit(CL_Agriculteur *agri, CL_Vecteur<CL_Petit> *vecteur);
	void EcrireAgriFN_Xp1(CL_Vecteur<CL_FN_Xp1>*vecteur);

	void LireAgriEmpLT(CL_Vecteur<CL_EmpLT> *vecteur);
	void LireAgriEmpCT(CL_Vecteur<CL_EmpCT> *vecteur);
	//void LireAgriSub        (CL_Vecteur<CL_Sub>   *vecteur);            //190412
	bool LireAgriSub(CL_Vecteur<CL_Sub> *vecteur);
	void LireAgriPlact(CL_Vecteur<CL_Plact> *vecteur);
	void LireAgriOccc(CL_Vecteur<CL_Occc> *vecteur);

	void LireAgriImmo103(CL_Vecteur<CL_Immo> *vecteur);
	void LireAgriImmo(CL_Vecteur<CL_Immo> *vecteur);
	void LireAgriPetit(CL_Agriculteur *agri, CL_Vecteur<CL_Petit> *vecteur);
	void LireAgriFN_Xp1(CL_Vecteur<CL_FN_Xp1>*vecteur);

	void LireAgriCreanceDette(CL_Vecteur<CL_EnCours> *vecteur);
	void EcrireAgriCreanceDette(CL_Vecteur<CL_EnCours> *vecteur);

	void EcrireAgriStockIni(CL_Vecteur<CL_StockIni> *vecteur);
	void LireAgriStockIni(CL_Vecteur<CL_StockIni> *vecteur);
	void LireAgriStockIni123(CL_Vecteur<CL_StockIni> *vecteur);

	void EcrireAgriPolStock(CL_Vecteur<CL_PolStock> *vecteur);
	void LireAgriPolStock(CL_Vecteur<CL_PolStock> *vecteur);

//	void EcrireAgriItemRepart (CL_Vecteur<CL_ItemRepart> *vecteur);
	void EcrireAgriItemRepart(CL_Agriculteur *agri); //170604
//	void LireAgriItemRepart (CL_Vecteur<CL_ItemRepart> *vecteur);
	void LireAgriItemRepart(CL_Agriculteur *agri); //170604

	void EcrireAgriVente(TList *lstQuantPrix);
	void LireAgriVente(TList *lstQuantPrix);

	void EcrireAgriTvaEntIni(CL_TvaEntIni *tvaIni);
	void LireAgriTvaEntIni(CL_TvaEntIni *tvaIni);

	void EcrireEnsemble(void);
	void LireEnsemble(int version);
	void adresseEnsemble(void);

	void EcrireAgriEff(CL_AgriEff *agriEff);
	void LireAgriEff(CL_AgriEff *agriEff);

	void LireEtatSortie(void); //conservé pour vesion <121
//    void EcrireEtatSortie(void);
	void EcrireEtatSortie(CL_Vecteur<CL_EtatSortie> *v_Etat);
//030908    
	void EcrireEtatSortie130(CL_Vecteur<CL_EtatSortie> *v_Etat);
	void EcrireEtatSortie134(CL_Vecteur<CL_EtatSortie> *v_Etat);
	void LireEtatSortie(CL_Vecteur<CL_EtatSortie> *v_Etat,
			CL_Vecteur<CL_Categorie> *vCategorie, int version);

	void LireIndicateur106(CL_Vecteur<CL_Categorie> *vCategorie);
	void LireIndicateur(CL_Vecteur<CL_Categorie> *vCategorie, int version);

	void ecrireArbre(CL_Indicateur *indicateur);
	void ecrireArbre(CL_Arbre *Arbre);

	void ecrireReseau(CL_Reseau *Reseau);
	void EcrireIndicateur(void);
	CL_Arbre* lireArbre(void);
	CL_Reseau* lireReseau(void);
	void LireCreeLBCritere113(void);
	void LireCreeLBCatCritere(void);
	void EcrireLBCatCritere(void);

	//treso  170903
	void LireRepart(CL_Vecteur<CL_Repart> *vecteur);
	void EcrireRepart(CL_Vecteur<CL_Repart> *vecteur);

	void LesAdresses(void);
	void adresseItem3(CL_Vecteur<CL_Item> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);
	void adresseItem2(CL_Vecteur<CL_Item> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);
	void adresseItem1(CL_Vecteur<CL_Item> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);
	void adresseItem4(CL_Vecteur<CL_Item> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);
	void adresseItem5(CL_Vecteur<CL_Item> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);

	void adresseAgriInvAni(CL_Vecteur<CL_InvAni> *vecteur); //131201
	void adresseAtelier(CL_Vecteur<CL_Atelier> *vecteur,
			CL_Vecteur<CL_Categorie> *vCategorie);
	void adresseAtelierItem(CL_Atelier *atelier, int nature);
	void adresseAgriCreanceDette(CL_Vecteur<CL_EnCours> *vecteur);

	/*
	 void adresseAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
	 CL_Vecteur<CL_Item> *vecteur);
	 void adresseAtelierItem( CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
	 CL_Vecteur<CL_ItemParAtelier> *vecteurP,
	 CL_Vecteur<CL_Item> *vecteurC );
	 */
	void adressePerenne(CL_Vecteur<CL_Atelier> *vecteur);
	void adresseAgri(void);
	void adresseAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur,
			CL_Vecteur<CL_Atelier> *vAtelier);
	void adresseAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur,
			CL_Vecteur<CL_Atelier> *vAtelier, int nature);

	void adresseAgriValeurItem(CL_Vecteur<CL_Valeur> *vecteur,
			CL_Vecteur<CL_Item>*vItem);
	void adresseAgriValeurVerger(CL_Vecteur<CL_Verger> *vecteur,
			CL_Vecteur<CL_Atelier> *vAtelier);
	void adresseEtatSortie(CL_Vecteur<CL_EtatSortie> *vEtat,
			CL_Vecteur<CL_Categorie> *vCategorie);
	void adresseIndicateur(void);
	void adresseAgriStockIni(CL_Vecteur<CL_StockIni> *vecteur);
	void messageErreur(char *nomAtelier, char *famille);

	void __fastcall IniV_Poste(void);

	void __fastcall IniV_EltPoste(void);void __fastcall IniV_EltBilan(void);void __fastcall IniV_EltCeg(void);

	void __fastcall IniV_Elt(void);void __fastcall IniV_EltItem(int noPoste,CL_Vecteur<CL_Item>*vecteur,
			CL_Vecteur<CL_Categorie>*vCat);void __fastcall IniV_EltAnimaux(void);

	void __fastcall IniV_EltExter(int noPoste,CL_Vecteur<CL_Item>*vecteur,
			CL_Vecteur<CL_Categorie>*vCat);

	void __fastcall IniV_EltIndicateur(int noPoste,CL_Vecteur<CL_Indicateur>*vecteur,
			CL_Vecteur<CL_Categorie>*vCat);

	void __fastcall IniV_EltImmo(void);void __fastcall IniV_EltSubvention(void);void __fastcall IniV_EltTva(void);void __fastcall IniV_EltEmp (int nature);

	void __fastcall IniV_EltSurface(void);void __fastcall IniV_EltSurface2(
			CL_Poste *poste,
			CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Atelier> *vAtelier,
			bool derobe);void __fastcall IniV_EltSurfacePerenne(CL_Poste *poste,bool derobe);

	void __fastcall IniV_EltCalendrier(void); //090306
	void __fastcall IniV_EltAmorDetail(void); //240406

	void __fastcall CompleteV_Elt(CL_Agriculteur *agri);
//	void __fastcall CompleteEltValeur(CL_Elt *elt, CL_Vecteur<CL_Valeur>*vecteur);
//	void __fastcall CompleteEltFormule(CL_Elt *elt, CL_Vecteur<CL_Formule>*vecteur);

	CL_Elt* __fastcall V_EltTrouve(int noFamille,int noElt);
	void LireBidon(void);

	void __fastcall NumeroteVarianteAgri(void);
//    void __fastcall LesFilsDAgri(CL_Agriculteur *agri,ST_NoAgri *ancetre,int nP);
	int __fastcall LesFilsDAgri(CL_Agriculteur *agri,int nP);

	void EcrireTendance(CL_Vecteur<CL_Tendance> *vecteur);
	void LireTendance(CL_Vecteur<CL_Tendance> *vecteur,
			CL_Vecteur<CL_Item> *vItem, int variante);

	void __fastcall trouveNom(void);void __fastcall trouveNom2(char car);

	void __fastcall CleCree(char *cle,int n);int __fastcall CleVal(char *cle);

	void ImpFichierAscii(void);

	void ImpSysUnit(ofstream &outfile);
	void ImpTva(ofstream &outfile);
	void ImpCategorie(ofstream &outfile, CL_Vecteur<CL_Categorie> *vecteur,
			char *titre);

	void ImpItem(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur, char *titre);
	void ImpItem2(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur, char *titre);
	void ImpItem3(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur, char *titre);
	void ImpItem4(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur, char *titre);

	void ImpCalendrier(ofstream &outfile, CL_Vecteur<CL_Calendrier> *vecteur,
			char *titre);

	void ImpAtelier(ofstream &outfile, CL_Vecteur<CL_Atelier> *vecteur,
			char *titre);
	void ImpLesAteliers(ofstream &outfile, CL_Vecteur<CL_Atelier> *vecteur);
	void ImpAtelierItem(ofstream &outfile, CL_Atelier *atelier,
			CL_Vecteur<CL_ItemParAtelier> *vecteur, char *titre);
	void ImpAtelierBesTrav(ofstream &outfile, CL_Atelier *atelier,
			CL_Vecteur<CL_BesTrav> *vecteur, char *titre);
	void ImpV_Elt(void);

	void ImpEspece(ofstream &outfile);

	void ImpLesIndicateurs(ofstream &outfile);
	void ImpIndic(ofstream &outfile, CL_Indicateur *indic);
	void ImpArbre(ofstream &outfile, CL_Arbre *arbre);
	void ImpReseau(ofstream &outfile, CL_Reseau *reseau);
	char* nomSymbole(int n);
	void ImpLesEtatSortie(ofstream &outfile);
	void ImpTendance(ofstream &outfile, CL_Vecteur<CL_Tendance> *vecteur,
			CL_Vecteur<CL_Item> *vItem, char *titre);
	bool EntrerNom(const AnsiString Titre, const AnsiString AAfficher,
			AnsiString &Nom);
	int isalnumA(unsigned char c);
	// mis à jour
	void MajInvAni(void);

	void ImpLesAgri(ofstream &outfile);
	void ImpListeAgri(ofstream &outfile, int n, CL_Agriculteur *agri);
	//test
	void AffLstMvtAniCount(void);

	void TexteChaine(void);

	char *LesTitresBilan[23];
	char *LesTitresCeg[24];
	char *LesTitresPoste[31];
	char *LesTitresTreso[13];

	char *LesTitresImmo[4];
	char *LesTitresSub[3];
	char *LesTitresTva[4];
	char *LesTitresEmp[20];

	AnsiString L_Sans;
	AnsiString L_Reduit;
	AnsiString L_Normal;

	AnsiString L_Cereale;
	AnsiString L_Oleagineux;
	AnsiString L_Proteagineux;

	AnsiString L_ChGlob;
	AnsiString L_Engrais;
	AnsiString L_Semence;
	AnsiString L_Phyto;
	AnsiString L_NomVide;
	AnsiString L_NomAlpha;
	AnsiString L_CarInvalide;

	AnsiString L_ExistePas;
	AnsiString L_ProbSurFichier;
	AnsiString L_VerActuelle;
	AnsiString L_JmetAJour;
	AnsiString L_VerInco;

	bool ErreurSub;
	//pour les amor détaillés
//??    CL_Agriculteur *AgriEnCours;
//    void ImpAgri(CL_Agriculteur *agri);
};
//void Printf(char *format, ...)

#endif
