//---------------------------------------------------------------------------

#ifndef ConversionH
#define ConversionH
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
//---------------------------------------------------------------------------
class TConversionFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabDonnee;
	TLabel *LabSortie;
	TLabel *LabChoix;
	TEdit *EdMonnaieBase;
	TEdit *EdMonnaieSortie;
	TBitBtn *BtReportDroit;
	TRadioGroup *RG;
	TComboBox *CBFrancEuro;
	TBitBtn *BitBtn1;
	TBitBtn *BtBnAbandon;
	TBitBtn *BtBnMonnaie;
	TLabel *LabTitre;
	TBitBtn *BtBnAide;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall RGClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall Grille0KeyPress(TObject *Sender, char &Key);
	void __fastcall CBFrancEuroKeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnOkClick(TObject *Sender);
	void __fastcall BtBnAnnulClick(TObject *Sender);
	void __fastcall BtBnMonnaieClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations utilisateur
	void __fastcall Personnaliser(void);
	void __fastcall DefinirLesGrilles(void);
	void __fastcall IniGrille(TStringGrid *grille);
	void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall CellDebut(void);
	void __fastcall AffGrille(void);
	void __fastcall LireConversion(void);
	bool ModifTaux;

protected:
	virtual bool __fastcall Stocker(void);
	virtual void __fastcall SaisirCell(int col,int row);

public:// Déclarations utilisateur
	int Origine;
	void __fastcall RetourDeChoix(bool modif);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LabSortie;
	AnsiString LC_BtBnMonnaie;
	AnsiString LC_RG;
	AnsiString LC_LabDonnee;
	AnsiString LC_LabChoix;
	AnsiString LC_ConversionFrm;
	AnsiString LC_LabTitre;
	AnsiString LC_Abandon;

	__fastcall TConversionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConversionFrm *ConversionFrm;
//---------------------------------------------------------------------------
#endif
