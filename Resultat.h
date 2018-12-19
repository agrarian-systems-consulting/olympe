//---------------------------------------------------------------------------
#ifndef ResultatH
#define ResultatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include "PERFGRAP.h"

#include "RacDef.h"

//---------------------------------------------------------------------------
class TResultatFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LBSortie;
	TBitBtn *BtBnQuitter;
	TPanel *PanelBas;
	TOpenDialog *OpenDialog;

	TGroupBox *GBGraph;
	TLabel *LabGauche;
	TLabel *LabDroit;
	TRadioGroup *RGAxe;
	TRadioGroup *RGNatureG;
	TRadioGroup *RGNatureD;
	TListBox *LBGauche;
	TListBox *LBDroit;
	TButton *BtSup1G;
	TButton *BtSupToutG;
	TButton *BtAffiche;
	TButton *BtSup1D;
	TButton *BtSupToutD;
	TGroupBox *GBMonnaie;
	TEdit *EdMonnaie;
	TBitBtn *BtBnChgtMonnaie;
	TBitBtn *BtBnCourbe;
	TBitBtn *BtBnComparaison;
	TGroupBox *GBComparaison;
	TRadioGroup *RGUnOuEnsemble;
	TProgressBar *ProgressBar;
	TBitBtn *BtBnStandard;
	TBitBtn *BtBnTravail;
	TBitBtn *BtBnTableur;
	TPanel *PanBas;
	TRadioGroup *RGPrecision;
	TGroupBox *GBSortie;
	TImage *Image1;
	TImage *Image2;
	TRadioButton *RBQR;
	TRadioButton *RBExcel;
	TRadioButton *RBEcran;
	TBitBtn *BtBnDico;
	TRadioButton *RBLongueDuree;
	TBitBtn *BtBnAide;
	TListBox *LBRac;

	void __fastcall LBSortieDblClick(TObject *Sender);

	void __fastcall BtAfficheClick(TObject *Sender);
	void __fastcall BtSupToutGClick(TObject *Sender);
	void __fastcall BtSup1GClick(TObject *Sender);
	void __fastcall BtSup1DClick(TObject *Sender);
	void __fastcall BtSupToutDClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnMonnaieClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall LBGaucheClick(TObject *Sender);
	void __fastcall LBDroitClick(TObject *Sender);
	void __fastcall LBGaucheEnter(TObject *Sender);
	void __fastcall LBDroitEnter(TObject *Sender);
	void __fastcall BtBnCourbeClick(TObject *Sender);
	void __fastcall BtBnComparaisonClick(TObject *Sender);
	void __fastcall RGUnOuEnsembleClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtBnStandardClick(TObject *Sender);
	void __fastcall RBQRClick(TObject *Sender);
	void __fastcall RBExcelClick(TObject *Sender);
	void __fastcall RBEcranClick(TObject *Sender);
	void __fastcall BtBnTravailClick(TObject *Sender);
	void __fastcall GBComparaisonClick(TObject *Sender);
	void __fastcall BtBnTableurClick(TObject *Sender);
	void __fastcall RGPrecisionClick(TObject *Sender);
	void __fastcall BtBnDicoClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
	//void __fastcall BtBnRacClick(TObject *Sender);
	//void __fastcall LBRacClick(TObject *Sender);
private:// Déclarations de l'utilisateur
	void __fastcall NonVisible(void);
	void __fastcall TrouveValeurCourbe(int noFamille,int noCategorie,int noItem);
//    void CreeDico(void);
//    void __fastcall AjouteEtat(TTreeView *tv);  //070602
	CL_Agriculteur *AgriOrigine;
	CL_SystemeUnite *SysMonnaieOrigine;
	CL_Agriculteur *Converti;
	TList *LstValeur;
	TList *LstEltA;
	void __fastcall ViderLesLst(void);
//    void AffUneSortie(int n);//090920
	void TraiterEltRac(CL_EltRac *elt0);
	int TrouveLBNo(TListBox *lB,AnsiString as);
	TTreeNode* TrouveTVNo1(TTreeView *tV,AnsiString as0,AnsiString as1);
	TTreeNode* TrouveTVNo2(TTreeView *tV,CL_EltRac *eltRac);
	TTreeNode* TrouveTVNo3(TTreeView *tV,CL_EltRac *eltRac);

public:// Déclarations de l'utilisateur
	int Digits;
	CL_Agriculteur *Agri;
	CL_Ensemble *Ensemble;
	bool AConvertir;
	int Origine;
	void __fastcall PresenterResultat(void);
	void __fastcall RetourDeLBCompAgri(int noFamille,int noCategorie,int noItem);
	void __fastcall RetourDeTVChoixComp(CL_EtatSortie *serieComp);
	void AffUneSortie(int n);//090920
	void CreeDico(void);
	void __fastcall AjouteEtat(TTreeView *tv);//070602
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString L_Inconnu;

	AnsiString LC_BtAffiche;
	AnsiString LC_BtAutreAgri;
	AnsiString LC_RGAxe;
	AnsiString LC_GereComparaisonFrm;
	AnsiString LC_BtBnCourbe;
	AnsiString LC_BtDico;
	AnsiString LC_LabDroit;
	AnsiString LC_RBEcran;
	AnsiString LC_TabSheetG;
	AnsiString LC_GBGraph;
	AnsiString LC_GBMonnaie;
	AnsiString LC_RGNatureG;
	AnsiString LC_RGUnOuEnsemble;
	AnsiString LC_RGPrecision;
	AnsiString LC_BtBnResultat;
	AnsiString LC_GBSortie;
	AnsiString LC_BtBnStandard;
	AnsiString LC_BtSup1G;
	AnsiString LC_BtSupToutG;
	AnsiString LC_BtBnTableur;
	AnsiString LC_TSTravail;
	AnsiString LC_Courbe;
	AnsiString LC_Histo;
	AnsiString LC_Un;
	AnsiString LC_Serie;

	AnsiString LC_Synt;
	AnsiString LC_RecDep;
	AnsiString LC_RecDepGP;
	AnsiString LC_Quant;
	AnsiString LC_Ceg;
	AnsiString LC_Bilan;
	AnsiString LC_Prive;
	AnsiString LC_Marges;
	AnsiString LC_Exter;
	AnsiString LC_Etat;
	AnsiString LC_SyntFi;
	AnsiString LC_Immo;
	AnsiString LC_Tva;
	AnsiString LC_Surface;
	AnsiString LC_ComptaPer;
	AnsiString LC_Stocks;
	AnsiString LC_RecapLT;
	AnsiString LC_RecapImmo;
	AnsiString LC_LongueDuree;
	AnsiString LC_Raccourci;//181109

	__fastcall TResultatFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResultatFrm *ResultatFrm;
//---------------------------------------------------------------------------
#endif
