//---------------------------------------------------------------------------
#ifndef Forme0H
#define Forme0H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <checklst.hpp>

#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//---------------------------------------------------------------------------
class TForme0Frm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panell;
	TBitBtn *BoutFermer;
	TBitBtn *BtBnQuitter;

	void __fastcall BoutImpEcranClick(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);

	void __fastcall FormCreate(TObject *Sender);
private: // Déclarations de l'utilisateur
public:
	int Origine;
	float __fastcall ValeurDe(AnsiString s);
	AnsiString __fastcall NomMois(int n,int nbCar=0);

	// LB
	virtual void __fastcall CreeLBCat(TListBox *LB,CL_Vecteur<CL_Categorie> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBUnite(TListBox *LB,CL_Vecteur<CL_SystemeUnite> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBTva(TListBox *LB,CL_Vecteur<CL_Tva> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBAtelier(TListBox *LB,CL_Vecteur<CL_Atelier> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBItem(TListBox *LB,CL_Vecteur<CL_Item> *vecteur, int noCat,bool avec=true);
	virtual void __fastcall CreeLBValeur(TListBox *LB,CL_Vecteur<CL_Valeur> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBVerger(TListBox *LB,CL_Vecteur<CL_Verger> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBTendance(TListBox *LB,CL_Vecteur<CL_Tendance> *vecteur);

	// a supprimer modifier resultat
	virtual void __fastcall CreeTVEtat(TTreeView *TV,CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_EtatSortie> *vEtat);
	void __fastcall CreeTVProcedure(TTreeView *TV,CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Procedure> *vProcedure);

	void __fastcall CreeTVMarge(TTreeView *TV,CL_Agriculteur *agri);
	void __fastcall CreeLBMarge( TCheckListBox *ChLB,CL_Agriculteur *agri);

	virtual void __fastcall CreeLBEtatSortie(TListBox *LB,CL_Vecteur<CL_EtatSortie> *vecteur);
	virtual void __fastcall CreeLBElt(TListBox *LB,CL_Vecteur<CL_Elt> *vecteur,bool avec=true);
	virtual void __fastcall CreeLBVariable(TListBox *LB,CL_Categorie *cat,CL_Vecteur<CL_Item> *vecteur);
	virtual void __fastcall CreeLBCalendrier(TListBox *LB,CL_Vecteur<CL_Calendrier> *vecteur);
	void __fastcall CreeLBConversion(TListBox *LB,CL_Vecteur<CL_Conversion> *vecteur);
	//CLB
	virtual void __fastcall CreeCLBCat(TCheckListBox *CLB,CL_Vecteur<CL_Categorie> *vecteur);
	//CB
	virtual void __fastcall CreeCBEspece(TComboBox *CB,CL_Vecteur<CL_Espece> *vecteur);
	virtual void __fastcall CreeCBCategorie(TComboBox *CB,CL_Vecteur<CL_Categorie> *vecteur);
	virtual void __fastcall CreeCBType(TComboBox *CB,CL_Vecteur<CL_Item> *vecteur, int noCat);
	//CheckListBox
	void __fastcall CreeLBToutAgri( TCheckListBox *ChLB);
	void __fastcall CreeLBToutAgriA(TCheckListBox *ChLB,CL_Agriculteur *agri);
	void __fastcall CreeLBToutAgriB(TCheckListBox *ChLB,AnsiString nomAieul,int nF,CL_Agriculteur *fils);

	void __fastcall CreeLBToutEnsemble( TCheckListBox *ChLB);
	void __fastcall CreeLBToutEnsembleA(TCheckListBox *ChLB,CL_Ensemble *ensemble);
	void __fastcall CreeLBToutEnsembleB(TCheckListBox *ChLB,AnsiString nomAieul,int nF,CL_Ensemble *fils);

	//TV
//	void __fastcall CreeTVCulture(	TTreeView *TV,int type);
	void __fastcall CreeTVAtelier(TTreeView *TV,CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Atelier> *vAtelier);
	void __fastcall CreeTVPerenne(TTreeView *TV,CL_Vecteur<CL_Espece> *vEsp,
			CL_Vecteur<CL_Atelier> *vPer);
	void __fastcall CreeTVItem( TTreeView *TV,
			CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Item> *vElt);
	void __fastcall CreeTVBestiaux( TTreeView *TV,
			CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Bestiaux> *vElt);
	void __fastcall CreeTVCreance( TTreeView *TV);
	void __fastcall CreeTVDette ( TTreeView *TV);

	void __fastcall CreeTVVariable( TTreeView *TV,
			CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Valeur> *vValeur);
	void __fastcall CreeTVToutAgri( TTreeView *TV);
	void __fastcall CreeTVVarianteAgri( TTreeView *TV,CL_Agriculteur *agri);
	void __fastcall CreeTVVarianteAgriSuite(TTreeView *TV,CL_Agriculteur *agri,TTreeNode *tNFils);
	void __fastcall CreeTVVarianteEnsemble( TTreeView *TV,CL_Ensemble *ens);
	void __fastcall CreeTVVarianteEnsembleSuite(TTreeView *TV,int nF,CL_Ensemble *ens,TTreeNode *tNFils);
	void __fastcall CreeTVAleaPrix( TTreeView *TV);
	void __fastcall CreeTVAleaRdt ( TTreeView *TV);
	void __fastcall CreeTVRepart (TTreeView *TV);
	void __fastcall CreeTVProduitComm(TTreeView *TV,CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Formule> *vFormule,CL_Vecteur<CL_StockIni> *vStockIni);

	void __fastcall CreeTVIndicateur(TTreeView *TV);
//	void __fastcall CreeTVEtatSortie(TTreeView *TV);

	void __fastcall CreeTVToutElt(TTreeView *tVChoix,CL_Agriculteur *agri,bool complet);

//	bool __fastcall CompleteElt( CL_Elt *elt,CL_Agriculteur *agri);
	void __fastcall CompleteV_Elt( CL_Agriculteur *agri);
	bool __fastcall CompleteElt( CL_Elt *elt,CL_Agriculteur *agri);
	float* __fastcall trouveDelta(CL_Item *item,CL_Tendance *tend);

	int Nature;
//    float ValZero[N_X];
//    CL_Agriculteur *Agri;
	CL_Tendance *PProd,*PCharge;

//    private:		// Déclarations de l'utilisateur
//    CL_Agriculteur *Agri;
//    float ValZero[N_X];

public:
	float ValZero[N_X];
	void TexteChaine(void);
	AnsiString L_RecDiv;
//        AnsiString L_Tendance;
//        AnsiString L_Scenario;
	AnsiString L_Externalite;
	AnsiString L_OubliImmo;
	AnsiString L_OubliSubvention;
	AnsiString L_OubliTva;

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtBnQuitter;

	__fastcall TForme0Frm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForme0Frm *Forme0Frm;
//---------------------------------------------------------------------------
#endif
