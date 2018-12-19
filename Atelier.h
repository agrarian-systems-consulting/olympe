//---------------------------------------------------------------------------

#ifndef AtelierH
#define AtelierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TAtelierFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnMarge;
	TBitBtn *BtBnReportDroit;
	TBitBtn *BtBnSupprimer;
	TBitBtn *BtBnReportBas;

	TLabel *LabUtilise;
	TLabel *LabAtelier;

	TBitBtn *BtBnProduit;
	TBitBtn *BtBnNotes;

	TBitBtn *BtBnRecopCal;
	TBitBtn *BtBnVideTout;

	TRadioGroup *RGDerobe;
	TPageControl *PC;

	TTabSheet *TSProduit;
	TStringGrid *GrilleProduits;

	TTabSheet *TSCharge;
	TStringGrid *GrilleCharges;

	TTabSheet *TSChargeVolume;
	TStringGrid *GrilleChargeVolume;

	TTabSheet *TSExternalite;
	TStringGrid *GrilleExternalite;

	TTabSheet *TSAvance;
	TLabel *LabAvance;
	TLabel *LabTotDep;
	TStringGrid *GrilleAvance;
	TStringGrid *SGAV;

	TTabSheet *TSProdImmo;
	TStringGrid *GrilleProdImmo;
	TStringGrid *SGPI;
	TPanel *PanProdImmo;
	TLabel *LabDurAmor;
	TLabel *LabDebAmor;
	TEdit *EdDurAmor;
	TEdit *EdDebAmor;

	TTabSheet *TSTravail;
	TStringGrid *GrilleTravail;
	TLabel *LabCalendrier;
	TLabel *LabBesoins;
	TBitBtn *BtBnSupBesTrav;
	TLabel *LabCalEnCours;
	TLabel *LabTotal;
	TEdit *EdTotalBesoins;
	TListBox *LBCalendrier;

//    TLabel      *Label1;
	TTabSheet *TSValInv;
	TStringGrid *GrilleValInv;
	TTabSheet *TSPiedHa;
	TStringGrid *GrillePiedHa;
	TTabSheet *TSProdPied;
	TTabSheet *TSChPied;
	TStringGrid *GrilleProdPied;
	TStringGrid *GrilleChPied;
	TBitBtn *BtBnDExcel;
	TBitBtn *BtBnVersExcel;
//    TLabel *LabAvance;
//    TLabel *Label3;
	void __fastcall PCChange(TObject *Sender);

	void __fastcall BtBnProduitClick(TObject *Sender);
	void __fastcall BtBnReportDroitClick(TObject *Sender);
	void __fastcall BtBnReportBasClick(TObject *Sender);
	void __fastcall BtBnMargeClick(TObject *Sender);
	void __fastcall BtBnSupprimerClick(TObject *Sender);

//    void __fastcall LBProductionClick(TObject *Sender);
	void __fastcall BtBnExcelClick(TObject *Sender);
	void __fastcall RGDerobeClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall BtBnSupBesTravClick(TObject *Sender);
	void __fastcall BtBnRecopCalendrierClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall PCChanging(TObject *Sender, bool &AllowChange);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall LBCalendrierClick(TObject *Sender);
	void __fastcall BtBnVersExcelClick(TObject *Sender);
	void __fastcall BtBnDExcelClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
//    void __fastcall BtReportBasClick(TObject *Sender);

//    void __fastcall BtBnReportDroitClick(TObject *Sender);
protected:
	TTabSheet* TS;
	//Atelier
	//Atelier1
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	virtual bool __fastcall ChargeVolumeExiste(int No);

	//Atelier3
	virtual void __fastcall SaisirCell(int col,int row);
	virtual bool __fastcall ControleCell(int col,int row);

private:// Déclarations utilisateur
	int LBCalendrierItemIndex;

	enum {GProduit,GCharge,GChProp,GExter,GAvance,GPImmo,GTravail,GValInv,
		GPiedHa,GProdPied,GChPied}; //220903
	void __fastcall IniGrilleProduit(TStringGrid *grille);
	void __fastcall IniGrilleVolume(TStringGrid *grille);
	void __fastcall IniGrilleAvance(TStringGrid *grille);//190802
	void __fastcall IniGrilleProdImmo(TStringGrid *grille);
	void __fastcall IniGrilleTravail(TStringGrid *grille);
	void __fastcall IniGrilleValInv(TStringGrid *grille);
	void __fastcall IniGrillePiedHa(TStringGrid *grille);//290307

	void __fastcall ChoixProduit(void);
	void __fastcall StockerOrdre (void);
	void __fastcall StockerOrdre1(CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall AffExcel(char *titre,TStringGrid *grille);

	void __fastcall TAtelierFrm::AffTotalCharge(TStringGrid *grille);//230902
	void __fastcall CreeLBTravail(void);

	//Atelier1
	void __fastcall VersGrilleItem (CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall VersGrilleVolume(CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall VersGrilleAvance(CL_Vecteur<CL_EEF> *vecteur);//190802
	void __fastcall VersGrilleProdImmo(float *prodImmo,float *prodImmoFam);
	void __fastcall VersGrilleValInv(void);
	void __fastcall VersGrillePiedHa(float *piedHa);

	//Atelier2
	bool __fastcall VerifGrille(void);
	bool __fastcall VerifLaGrille(void);
	bool __fastcall IlYaQuantite(int row);
	bool __fastcall VerifProdImmo(void);
	bool __fastcall ControleCellItem(int col,int row);
	bool __fastcall ControleCellVolume(int col,int row);
	void __fastcall DeGrilleItem (CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall DeGrilleVolume(CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall DeGrilleAvanceStock(CL_Vecteur<CL_EEF> *vecteur);
	void __fastcall DeGrilleProdImmo(void);
	void __fastcall DeGrillePiedHa(float *piedHa);

	void __fastcall TotaliseTravail(void);

	//Atelier3
//	virtual void __fastcall  SaisirCellItem(int col,int row);
	virtual void __fastcall SaisirCellVolume(int col,int row);
//	virtual void __fastcall  SaisirCellValInv(int col,int row);

	//Atelier4
	void __fastcall trouveProduit(CL_ItemParAtelier* produitA,float* qteProduite);

	virtual bool __fastcall VerifLesGrilles(void);
	virtual void __fastcall DesGrilles(void);
	virtual void __fastcall DeLaGrille(void);
	void __fastcall DeGrilleInvAni(void);

//    AnsiString L_Produit;
	AnsiString L_Derobe;
//    AnsiString L_Charge;
//    AnsiString L_Exter;
	AnsiString L_SupQ;
	AnsiString L_SupT;
//    AnsiString L_SupToutQ;
//    AnsiString L_Atelier;

	AnsiString L_TitreProduit;
	AnsiString L_TitreVol;
	AnsiString L_Ouverture;
	AnsiString L_Ent;
	AnsiString L_Fam;
	AnsiString L_Periode;
	AnsiString L_Repro;
	AnsiString L_Autre;
	AnsiString L_Avant1;

	AnsiString L_ErrPasQant;
	AnsiString L_ErrPasNom;
	AnsiString L_ProdImmo;
	AnsiString L_ErrPasDebAmor;
	AnsiString L_ErrPasDurAmor;
	AnsiString L_ErrPasProd;
	AnsiString L_Err;

	AnsiString L_Production;
	AnsiString L_ErrCal;
	AnsiString L_TotAn;
	//180507
	AnsiString L_PiedParHa;
	AnsiString LC_PiedParHa;
	AnsiString LC_ProdParPied;
	AnsiString LC_ChargeParPied;

	//AnsiString L_SupQ;
	//AnsiString L_SupT;

public:// Déclarations utilisateur
	int Origine;
	int Nature;
	CL_Espece *Espece;
	CL_Categorie *Categorie;
	CL_Vecteur<CL_Atelier> *V_Atelier;
	CL_Atelier *Atelier;
	CL_BesTrav *BesTrav;
//    void __fastcall Demarrer(void);
	void __fastcall AffAtelier(void);
	bool __fastcall VerifPage(void);
	void __fastcall MetAnnee(TStringGrid *grille,int col0);
	bool __fastcall Stocker(void);

//	bool __fastcall Stocker(void);
	float Produit[N_PHASE];//pour perenne ça va jusqu'à N_PHASE=14 =40
	float Charge [N_PHASE];
	float ChargeVol[N_PHASE];
	float Marge[N_PHASE];
	float MoyProd,MoyCharge,MoyChVol;

	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LabAvance;
	AnsiString LC_AtelierFrm;
	AnsiString LC_TSAvance;
	AnsiString LC_LabBesoins;
	AnsiString LC_LabCalEnCours;
	AnsiString LC_LabPCharge;
	AnsiString LC_TSChargeVolume;
	AnsiString LC_LabDebAmor;
	AnsiString LC_RGDerobe;
	AnsiString LC_LabDurAmor;
//    AnsiString LC_[0]TLabel [0];
	AnsiString LC_TSExternalite;
	AnsiString LC_LabCalendrier;
	AnsiString LC_BtBnMarge;
	AnsiString LC_TSProdImmo;
	AnsiString LC_BtBnProduit;
	AnsiString LC_BtBnRecopCal;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_LabTotal;
	AnsiString LC_LabTotDep;
	AnsiString LC_TSTravail;
	AnsiString LC_LabUtilise;
	AnsiString LC_Panell;
	AnsiString LC_TSValInv;
	AnsiString LC_Vrai;
	AnsiString LC_Faux;

	__fastcall TAtelierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAtelierFrm *AtelierFrm;
//---------------------------------------------------------------------------
#endif
