//---------------------------------------------------------------------------

#ifndef AgriDefSimH
#define AgriDefSimH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAgriDefSimFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGAlea;

	TGroupBox *GBPrix;
	TGroupBox *GBQuantite;
	TGroupBox *GBEnch;

	TComboBox *CBSTPProduit;
	TComboBox *CBSTPCharge;
	TComboBox *CBSTQProduit;
	TComboBox *CBSTQCharge;
	TComboBox *CBSTQExt;

	TComboBox *CBPProduit;
	TComboBox *CBPCharge;
	TComboBox *CBQProduit;
	TComboBox *CBQCharge;
	TComboBox *CBQExt;

	TLabel *LabPProduit;
	TLabel *LabPCharge;
	TLabel *LabQProduit;
	TLabel *LabQCharge;
	TLabel *LabQExt;
	TPanel *Panel1;

	TLabel *LabNom;
	TLabel *LabVariante;
	TLabel *LabAn0;
	TLabel *LabMoisOuv;

	TEdit *EdNom;
	TEdit *EdVariante;
	TEdit *EdAn0;

	TBitBtn *BoutFermer;
	TBitBtn *BtBnQuitter;

	TStringGrid *GrilleEnch;

	TGroupBox *GBCas;
	TComboBox *CBOuv;
	TBitBtn *BtBnNotes;
	TBitBtn *BtReportDroit;
	TLabel *LabAnMax;
	TCheckBox *ChBRepTout;
	TLabel *LabelModifie;
	TBitBtn *BtBnStocker;
	TStringGrid *GrilleCritere;
	TLabel *LabZone;
	TGroupBox *GBSerie;
	TListBox *LBResultatPour;
	TComboBox *CBNbAnnee;

	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall GrilleEnchKeyPress(TObject *Sender, char &Key);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall CBPProduitClick(TObject *Sender);
	void __fastcall CBPChargeClick(TObject *Sender);
	void __fastcall CBQProduitClick(TObject *Sender);
	void __fastcall CBQChargeClick(TObject *Sender);
	void __fastcall CBQExtClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall RGAleaClick(TObject *Sender);
	void __fastcall CBSTPProduitClick(TObject *Sender);
	void __fastcall CBSTPChargeClick(TObject *Sender);
	void __fastcall CBSTQProduitClick(TObject *Sender);
	void __fastcall CBSTQChargeClick(TObject *Sender);
	void __fastcall CBSTQExtClick(TObject *Sender);
	void __fastcall BtBnReprendreClick(TObject *Sender);
	void __fastcall BtBnConserverClick(TObject *Sender);
	void __fastcall EdAn0KeyPress(TObject *Sender, char &Key);
	void __fastcall EdAn0Exit(TObject *Sender);
	void __fastcall GrilleCritereClick(TObject *Sender);
	void __fastcall CBOuvChange(TObject *Sender);
	void __fastcall CBNbAnneeClick(TObject *Sender);
	void __fastcall LBResultatPourClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	CL_Agriculteur *Agri;
	int NoSerie;
	bool AnAAfficher;
	bool AnEstAffiche;
	bool DansIniEcran;
	TList *LstCritereTemp;
	void __fastcall AffTitreCritere(void);
	void __fastcall AffCritere(void);

	void __fastcall IniCB( TComboBox *CB,CL_Vecteur<CL_Tendance> *V_Tend);
	void __fastcall IniCBST(TComboBox *CBST,CL_Vecteur<CL_Tendance> *V_Tend,
			CL_Vecteur<CL_Tendance> *V_Scen);

	int __fastcall trouve(CL_Vecteur<CL_Tendance>*v_Tend,CL_Tendance *tend0);
	bool __fastcall Verif(void);
	void __fastcall AffAn(void);
	void __fastcall AffTend(int TouS,CL_Tendance *tend,
			TComboBox *CBST,TComboBox *CB,
			CL_Vecteur<CL_Tendance> *vTend,CL_Vecteur<CL_Tendance> *vScen);
	bool __fastcall DefSimExiste(void);
	bool __fastcall EstIdentique(CL_AgriDefSim *defSim);

	void CreeLBResultatPour(int nSerie);

	AnsiString L_Aucun;
//    AnsiString L_Tendance;
//    AnsiString L_Scenario;
//	AnsiString L_QuitQ;
//    AnsiString L_QuitM;
	AnsiString L_LimDate;
	AnsiString L_LimDateM;
	AnsiString L_ErrTend;
//    AnsiString L_ErrM;
	AnsiString L_ErrScen;
	AnsiString L_Res1;
	AnsiString L_Res2;
	AnsiString L_SimSur;
	AnsiString L_CestSur;
	AnsiString L_An;

	AnsiString LC_RGAlea;
	AnsiString LC_LabAn0;
	AnsiString LC_LabCalage;
	AnsiString LC_AgriDefSimFrm;
	AnsiString LC_LabPCharge;
	AnsiString LC_LabZone;
	AnsiString LC_GBEnch;
	AnsiString LC_LabQExt;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_LabMoisOuv;
	AnsiString LC_LabAnMax;
	AnsiString LC_LabNom;
	AnsiString LC_BtBnNotes;
	AnsiString LC_GBPrix;
	AnsiString LC_LabPProduit;
	AnsiString LC_GBQuantite;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_ChBRepTout;
	AnsiString LC_GBSerie;
	AnsiString LC_LabVariante;

	AnsiString LC_Sans;
	AnsiString LC_Avec;

	//.........
//    CL_AgriDefSim   *DefSim;//provisire
public:// Déclarations utilisateur
	void IniCaption(void);
	void TexteCaption(void);

//    CL_Agriculteur  *Agri;
	CL_AgriDefSim *DefSim;
	int Origine;
	void __fastcall IniEcran(void);
	void TexteChaine(void);

	void __fastcall Aff(void);
	__fastcall TAgriDefSimFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAgriDefSimFrm *AgriDefSimFrm;
//---------------------------------------------------------------------------
#endif

