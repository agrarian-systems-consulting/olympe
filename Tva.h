//---------------------------------------------------------------------------
#ifndef TvaH
#define TvaH
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
class TTvaFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtSup;
	TGroupBox *GBDefaut;
	TLabel *LabTva;
	TLabel *LabImmo;
	TComboBox *CBDefaut;
	TComboBox *CBImmo;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnNotes;
//	void __fastcall BtClasserClick(TObject *Sender);
//	void __fastcall BoutAnnulClick(TObject *Sender);
//	void __fastcall BtSupprimeClick(TObject *Sender);
//	void __fastcall BoutEditClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall CBDefautClick(TObject *Sender);
	void __fastcall CBImmoClick(TObject *Sender);
	void __fastcall GBDefautEnter(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

private:// Déclarations de l'utilisateur
	void __fastcall IniCB(void);
	void __fastcall StockerOrdre(CL_Vecteur<CL_Tva> *vecteur);
protected:
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);
	virtual bool __fastcall Stocker(void);

public:// Déclarations de l'utilisateur
	virtual void __fastcall VersGrille (TStringGrid *grille);
	void __fastcall ImpTva(void);
	AnsiString Notes;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Immo;
	AnsiString LC_GBDefaut;
	AnsiString LC_BtBnTva;

	AnsiString LC_Jefface;
	AnsiString LC_Nettoyer;
	AnsiString LC_PasNom;
	AnsiString LC_PasTaux;
	AnsiString LC_PasTvaDefaut;
	AnsiString LC_PasTvaImmo;

	AnsiString LC_Nom;
	AnsiString LC_Taux;
	AnsiString LC_Utilise;

	__fastcall TTvaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTvaFrm *TvaFrm;
//---------------------------------------------------------------------------
#endif
