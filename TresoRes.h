//---------------------------------------------------------------------------

#ifndef TresoResH
#define TresoResH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TTresoResFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TStringGrid	*SG;
	TBitBtn *BtBnPlus12;
	TBitBtn *BtBnMoin12;
	TRadioGroup *RGPrecision;
	TBitBtn *BtBnGraphique;
	TBitBtn *BtBnExcel;
	TBitBtn *BtBnImp;
	TBitBtn *BtBnEffSelection;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnPlus12Click(TObject *Sender);
	void __fastcall BtBnMoin12Click(TObject *Sender);
	void __fastcall RGPrecisionClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall SGClick(TObject *Sender);
	void __fastcall BtBnGraphiqueClick(TObject *Sender);
	void __fastcall BtBnExcelClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
	void __fastcall BtBnEffSelectionClick(TObject *Sender);
private: // Déclarations utilisateur
	TList *LstTresoMens;
	float Solde[120];
	float TotalLambda[120];
	float SoldeCumule[120];
	float TotalRecette[120];
	float TotalDepense[120];
	float TvaEncaissee[120];
	float TvaVersee[120];
	float TvaAcompte[120];
	float TvaRegularisation[120];
	float TvaRemboursement[120];
	float FinancePlus[120];
	float FinanceMoins[120];
	float SoldeApresOccc[120];
	float SoldeApresPlact[120];

	bool __fastcall ilYaValeur(float *valeur);

	void __fastcall AffMoisAn(int col0);
	void __fastcall CreeLstTresoMens(CL_Vecteur<CL_Categorie> *v_Categorie,
			CL_Vecteur<CL_QuanVal> *v_QuanVal,
			char *famille,int recette);
	void TTresoResFrm::CreeTresoVenteNetteAni(void);

	void TotCategorie(CL_Vecteur<CL_QuanVal> *v_QuanVal,CL_Categorie *cat,float *totalCat);//061206

	void __fastcall CreeLstTresoMensEnCours(CL_Vecteur<CL_EnCours> *vecteur,int proOUcha);

	void __fastcall CreeLesTresoMens(void);
	void __fastcall CreeLstTresoMensProduit(void);
	void __fastcall CreeLstTresoMensImmo(void);
	void __fastcall CreeLstTresoMensPetit(void);
	void __fastcall CreeLstTresoMensEmpruntLT(void);
	void __fastcall CreeLstTresoMensEmpruntCT(void);
	void __fastcall CreeLstTresoMensSubvention(void);
	void __fastcall CreeLstTresoMensPlact(void);
	void __fastcall Ajoute(float *total,float *valeur);

	//    void __fastcall CalculLesTresoMens(void);
	void __fastcall AffLesTresoMensValeurDetail(int digits);
	void __fastcall AffLesTresoMensValeurSemiDetail(int digits);
	void __fastcall AffLesTresoMensValeurSynthese(int digits);
	void __fastcall AffLesTresoMensOccc(int digits);
	void __fastcall AffLesTresoMensQuantite(int digits);

	void __fastcall CalculTva(void);
	void __fastcall CalculSolde(void);
	void __fastcall CalculOccc(void);

public:// Déclarations utilisateur
	int Origine;
	int An_0;
	int Nature;//CATEGORIE 110  TOTAL 1
	int TypeSortie;//DETAIL SEMIDETAIL GLOBAL
	CL_Vecteur<CL_QuanVal> *V_QuanVal;
	CL_Vecteur<CL_Categorie> *V_Categorie;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBnPlus12;
	AnsiString LC_BtBnMoin12;
	AnsiString LC_BtBnGraphique;
	AnsiString LC_RGPrecision;
	AnsiString LC_TresoResFrm;

	AnsiString LC_ProVal;
	AnsiString LC_ProQuant;
	AnsiString LC_ChaVal;
	AnsiString LC_ChaQuant;
	AnsiString LC_ChStructVal;
	AnsiString LC_AniVal;
	AnsiString LC_AniEff;
	AnsiString LC_RecDiv;
	AnsiString LC_DepDiv;
	AnsiString LC_Ext;
	AnsiString LC_ExtNeg;
	AnsiString LC_ExtPos;
	AnsiString LC_RecFam;
	AnsiString LC_DepFam;
	AnsiString LC_Immo;
	AnsiString LC_PetitMat;
	AnsiString LC_Finance;
	AnsiString LC_CreanDette;

	AnsiString LC_VenteAni;
	AnsiString LC_AchatAni;
	AnsiString LC_Troupeau;
	AnsiString LC_Creances;
	AnsiString LC_Dettes;
	AnsiString LC_Charges;

	AnsiString LC_TotRecu;
	AnsiString LC_TotSorti;
	AnsiString LC_CreanceEtDette;
	AnsiString LC_TotCreanceEtDette;
	AnsiString LC_TotEmprunt;
	AnsiString LC_TotRembEmpr;
	AnsiString LC_TotalAchat;
	AnsiString LC_TotalVente;
	AnsiString LC_InvNet;
	AnsiString LC_EmpLT;
	AnsiString LC_TotNouvEmp;
	AnsiString LC_TotRemb;
	AnsiString LC_EmpCT;
	AnsiString LC_TotNouvCT;
	AnsiString LC_TotRembCT;
	AnsiString LC_Subvention;
	AnsiString LC_SubTot;
	AnsiString LC_Plact;
	AnsiString LC_PlactTot;
	AnsiString LC_PlactRes;
	AnsiString LC_Tva;
	AnsiString LC_TvaEnc;
	AnsiString LC_TvaVer;
	AnsiString LC_TvaAc;
	AnsiString LC_TvaReg;
	AnsiString LC_TvaRemb;
	AnsiString LC_TvaSolde;

	AnsiString LC_TotRec;
	AnsiString LC_TotDep;
	AnsiString LC_Solde;
	AnsiString LC_SoldeCumul;
	AnsiString LC_Oc1;
	AnsiString LC_Oc1Int;
	AnsiString LC_Oc2;
	AnsiString LC_Oc2Int;

	AnsiString LC_Occc;
	AnsiString LC_OcccInt;
	AnsiString LC_SolApOccc;

	AnsiString LC_PlactInt;
	AnsiString LC_SoldeApPlact;

	__fastcall TTresoResFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoResFrm *TresoResFrm;
//---------------------------------------------------------------------------
#endif
