//---------------------------------------------------------------------------

#ifndef TVDonResH
#define TVDonResH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTVDonResFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanBas;
	TBitBtn *BtBnRafraichir;
	TGroupBox *GBDon;
	TTreeView *TVDon;
	TGroupBox *GBRes;
	TTreeView *TVRes;
private: // Déclarations de l'utilisateur
	void __fastcall CreeTVDon(void);
	void __fastcall CreeTVRes(void);
	void __fastcall BrancheValeur(TTreeView *tV,TTreeNode *tn,CL_Vecteur<CL_Valeur> *vecteur);
	void __fastcall BrancheQuanValValeur(TTreeView *tV,TTreeNode *tn0,CL_Vecteur<CL_QuanVal> *vecteur);
	void __fastcall BrancheQuanValPrix(TTreeView *tV,TTreeNode *tn0,CL_Vecteur<CL_QuanVal> *vecteur);

public:// Déclarations de l'utilisateur
	void __fastcall CreeTV(void);

	__fastcall TTVDonResFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVDonResFrm *TVDonResFrm;
//---------------------------------------------------------------------------
#endif
