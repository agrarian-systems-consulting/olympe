//---------------------------------------------------------------------------

#ifndef FenRepartH
#define FenRepartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//---------------------------------------------------------------------------
class TFenRepartFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TStringGrid	*LaGrille;
	TGroupBox *GBCode;
	TEdit *EdCode;
	TGroupBox *GBAn;
	TEdit *EdAn;
	TGroupBox *GBValeur;
	TEdit *EdValeur;
	TGroupBox *GBProduit;
	TEdit *EdProduit;
	TLabel *LabPcent;
	TLabel *LabVal;
	TLabel *LabTotPcent;
	TEdit *EdTotPcent;
	TLabel *LabTotalVal;
	TEdit *EdTotValeur;
	TBitBtn *BtBnOk;
	TRadioGroup *RGPrecision;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnOkClick(TObject *Sender);
	void __fastcall RGPrecisionClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	void __fastcall EffaceGrille(void);
	void __fastcall Demarre(void);
	void __fastcall AffTotal(void);
	CL_QuanVal *LaQuanVal;

public:// Déclarations utilisateur
	int Traitement;//0 nouveau 1 emploi repart pour autre produit
	CL_Agriculteur *AgriEnCours;//010506
	CL_Repart *Repart;
	CL_Categorie *Categorie;
	float ValTot;
	TStringGrid *SG;
	void __fastcall Affiche(void);
	void __fastcall InformeSGTreso(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GBAn;
	AnsiString LC_GBCode;
	AnsiString LC_LabPcent;
	AnsiString LC_LabPProduit;
	AnsiString LC_FenRepartFrm;
	AnsiString LC_LabTotal;
	AnsiString LC_LabTotPcent;
	AnsiString LC_LabVal;

	__fastcall TFenRepartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFenRepartFrm *FenRepartFrm;
//---------------------------------------------------------------------------
#endif
