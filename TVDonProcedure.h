//---------------------------------------------------------------------------

#ifndef TVDonProcedureH
#define TVDonProcedureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include <iostream>
#include <map.h>
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
class TTVDonProcedureFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanBas;
	TBitBtn *BtBnRafraichir;
	TGroupBox *GBDon;
	TTreeView *TVDon;
	TGroupBox *GBRes;
	TTreeView *TVRes;
	TPanel *PanHaut;
	TRadioGroup *RG;
	void __fastcall TVResClick(TObject *Sender);
	void __fastcall TVDonClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall RGClick(TObject *Sender);
private: // Déclarations de l'utilisateur

	TRadioGroup *RGModifiable;
	TStringGrid *LaGrille;
	void __fastcall CreeTVDon(void);

	void __fastcall ArbreAtelier(TTreeView *tV,TTreeNode *tn,
			char* nomNature,char* nomFamille,
			int code,CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCat);

	void __fastcall BrancheAtelier(TTreeView *tV,TTreeNode *tn,
			char* nomNature,char* nomFamille,
			int code, CL_Vecteur<CL_Atelier> *vecteur,CL_Vecteur<CL_Categorie> *vCat);

	void __fastcall ArbreItem(TTreeView *tV,TTreeNode *tn,
			char* nomNature,char* nomFamille,
			int code,CL_Vecteur<CL_Item> *vecteur,CL_Vecteur<CL_Categorie> *vCat);

	void __fastcall BrancheItem(TTreeView *tV,TTreeNode *tn,
			char* nomNature,char* nomFamille,
			int code, CL_Vecteur<CL_Item> *vecteur,CL_Vecteur<CL_Categorie> *vCat);

	void __fastcall ArbreTendance(TTreeView *tV,TTreeNode *tn,
			char* nomNature,int code,
			CL_Vecteur<CL_Tendance> *v_Prix,CL_Vecteur<CL_Tendance> *v_Quant);

	void __fastcall BrancheTendance(TTreeView *tV,TTreeNode *tn,
			char* nomNature,char* nomFamille,
			int code,CL_Vecteur<CL_Tendance> *v_Tendance);

	void __fastcall ArbreQuanVal(TTreeView *tV,TTreeNode *tn,AnsiString nom,
			CL_Vecteur<CL_QuanVal> *vecteur,CL_Vecteur<CL_Categorie> *vCat);
	void __fastcall BrancheQuanValValeur(TTreeView *tV,TTreeNode *tn0,
			CL_Vecteur<CL_QuanVal> *vecteur,CL_Vecteur<CL_Categorie> *vCat);
	void __fastcall BrancheQuanValPrix(TTreeView *tV,TTreeNode *tn0,
			CL_Vecteur<CL_QuanVal> *vecteur,CL_Vecteur<CL_Categorie> *vCat);
	void __fastcall ArbreFormule(TTreeView *tV,TTreeNode *tn,
			char *nomNature,char *nomFamille,
			int code,CL_Vecteur<CL_Formule> *vecteur,CL_Vecteur<CL_Categorie> *vCat);
	void __fastcall ArbreEnsemble(TTreeView *tV,TTreeNode *tn);

	void __fastcall BrancheGlobal(TTreeView *tV,TTreeNode *tn,
			char *nomNature,char *nomFamille,
			int code,CL_Vecteur<CL_FN_Xp1> *vecteur,AnsiString AFaire);
//        int code,CL_Vecteur<CL_FN_Xp1> *vecteur,char *NomDeLaListe);

	void __fastcall EcrireGrille(TTreeNode *choix);

public:// Déclarations de l'utilisateur
	void __fastcall CreeTV(void);
	void __fastcall CreerMapNomFamNat(void);

	__fastcall TTVDonProcedureFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVDonProcedureFrm *TVDonProcedureFrm;
//---------------------------------------------------------------------------
#endif
