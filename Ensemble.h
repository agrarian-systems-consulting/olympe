//---------------------------------------------------------------------------
#ifndef EnsembleH
#define EnsembleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TEnsembleFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TButton	*BtAutre;
	TBitBtn *BtReportDroit;
	TBitBtn *BtBnSup;
	TLabel *LabEnsemble;
	TBitBtn *BtBnSomme;
	TBitBtn *BtReportBas;
	TBitBtn *BtRecopBas;
	TBitBtn *BtRepToutDroit;
	TBitBtn *BtBnVersExcel;
	TBitBtn *BtBnDExcel;
	TBitBtn *BtBnNotes;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall BtAutreClick(TObject *Sender);
	void __fastcall BtBnSupClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtBnSommeClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtReportBasClick(TObject *Sender);
	void __fastcall BtReportLigne(TObject *Sender);
	void __fastcall BtReportTout(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtBnVersExcelClick(TObject *Sender);
	void __fastcall BtBnDExcelClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
protected:
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall SaisirCell(int col,int row);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	virtual void __fastcall DeGrille(TStringGrid *grille);
	virtual bool __fastcall Stocker(void);

private: // Déclarations de l'utilisateur
	int LarColAgri;
	void __fastcall CreeGrille(void);
	int __fastcall AffLesVariantes(CL_Agriculteur *agri,int r);
	bool __fastcall StockerNouveau(void);
	int EffTotal[N_X];
	void __fastcall TotalAgri(void);
	void __fastcall TotalAgriDeGrille(void);

	AnsiString L_NbType;
//    AnsiString L_Total;
//    AnsiString L_Agri;
	AnsiString L_NVar;
	AnsiString L_EffQ;
	AnsiString L_Abandon;
	AnsiString L_Vide;
	AnsiString L_SupQ;
	AnsiString L_SupQ2;
//    AnsiString L_Tot;     

public:// Déclarations de l'utilisateur
	CL_Ensemble *Ensemble;
	int AFaire;
	int ColAn0;
	bool GrilleEstVide;
	void __fastcall AffGrilleVide(void);
	void __fastcall VoirEnsemble(void);
	void __fastcall EffaceEnsemble(void);
	int __fastcall EstAffiche(CL_Agriculteur *agri);
	void __fastcall AffAgriEff(int r,CL_AgriEff *agriEff);
	void __fastcall SupLigne(int r0);
//	CL_AgriEff* __fastcall	TrouveAgriEff(CL_Agriculteur *agri);

	void __fastcall SelectionManuelle(void);
	void __fastcall SelectionTri(void);
	void __fastcall SelectionAddition(void);
	void __fastcall Extraction(void);
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtAutre;
	AnsiString LC_ChBEnsemble;
	AnsiString LC_BtBnSomme;

	__fastcall TEnsembleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEnsembleFrm *EnsembleFrm;
//---------------------------------------------------------------------------
#endif

