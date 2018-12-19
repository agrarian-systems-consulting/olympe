//---------------------------------------------------------------------------

#ifndef DefProcedureH
#define DefProcedureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <iostream>
#include <vector.h>
using namespace std;

#include "LesClassesApp.h"

//---------------------------------------------------------------------------
class TDefProcedureFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TPanel	*PanB2;
	TPanel *PanH1;

	TBitBtn *BtBnDico;
	TBitBtn *BtBnSup;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnExecuter;

	TOpenDialog *OpenDialogExe;
	TOpenDialog *OpenDialogFichier;
	TLabel *LabExecutable;
	TLabel *LabFichierTransfert;
	TLabel *LabProcedure;
	TEdit *EdProcedure;
	TRadioGroup *RGModifiable;
	TEdit *EdExe;
	TEdit *EdFichier;
	TButton *BtExe;
	TButton *BtFichier;
	TRadioGroup *RGTraitement;

	void __fastcall BtBnDicoClick(TObject *Sender);
	void __fastcall BtBnExecuterClick(TObject *Sender);
	void __fastcall RGModifiableClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnSupClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtExeClick(TObject *Sender);
	void __fastcall BtFichierClick(TObject *Sender);
	void __fastcall EdExeKeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnSelectionClick(TObject *Sender);
	void __fastcall RGTraitementClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

private: // Déclarations de l'utilisateur
	void __fastcall AffEnTete(void);
	bool __fastcall Verifier(void);
	AnsiString L_LancerQ;
	AnsiString L_Procedure;
//	AnsiString L_Nom;
//	AnsiString L_Cat;
//	AnsiString L_Fam;
//	AnsiString L_Nat;
//	AnsiString L_SupToutQ;
//    AnsiString L_Sup;
	AnsiString L_EffQ;
	AnsiString L_PasDExe;
	AnsiString L_PasFTrf;
	AnsiString L_JStockPas;

public:// Déclarations de l'utilisateur
	CL_Procedure *Procedure;
	CL_Categorie *Categorie;
	CL_Agriculteur *Agri;
	vector<CL_Agriculteur*> VAgri;

	void __fastcall CreerMapNomFamNat(void);
	void __fastcall AffProcedure(void);

	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
//    virtual bool  __fastcall Stocker(void);

	void __fastcall PossibleModifier(bool modifiable);
	void __fastcall SelectionManuelle(void);
	void __fastcall SelectionTri(void);
	void ExecuterProcedure(AnsiString nomCatProc,AnsiString nomProc,CL_Agriculteur *agri);

	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtExe;
	AnsiString LC_DefProcedureFrm;
	AnsiString LC_BtDico;
	AnsiString LC_LabExecutable;
	AnsiString LC_LabFichierTransfert;
	AnsiString LC_BtBnExecuter;
	AnsiString LC_RGModifiable;
	AnsiString LC_LabProcedure;

	__fastcall TDefProcedureFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefProcedureFrm *DefProcedureFrm;
//---------------------------------------------------------------------------
#endif
