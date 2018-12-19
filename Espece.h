//---------------------------------------------------------------------------
#ifndef EspeceH
#define EspeceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SysUnite.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TEspeceFrm: public TSysUniteFrm {
	__published: // Composants gérés par l'EDI
TLabel	*LabPhase;
	TBitBtn *BtBn123;
	TBitBtn *BtBnMaz;
//	void __fastcall BtSupprimeClick(TObject *Sender);
//	void __fastcall BoutEditClick(TObject *Sender);
//	void __fastcall BtAnnuleClick(TObject *Sender);
	void __fastcall BoutImpEcranClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtBn123Click(TObject *Sender);
	void __fastcall BtBnMazClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:// Déclarations de l'utilisateur
	void __fastcall VersEspece(int row,CL_Espece *espece);
	void __fastcall BtReportDroitClick(TObject *Sender);

protected:
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);

	virtual void __fastcall VersGrille(TStringGrid *grille);
	virtual void __fastcall DeGrille(TStringGrid *grille);
	virtual bool __fastcall Stocker(void);

	virtual void __fastcall CellDebut(void);

	AnsiString L_Titre;
	AnsiString L_Util;
//	AnsiString L_SupQ;
//    AnsiString L_SupT;
	AnsiString L_PasEsp;
	AnsiString L_PasAm;
	AnsiString L_Dur100;
	AnsiString L_MisA1;
	AnsiString L_Incoherent;
	AnsiString L_Espece;
	AnsiString L_DebAmor;
	AnsiString L_Maxi;

public:// Déclarations de l'utilisateur
	AnsiString Notes;
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_EspeceFrm;
	AnsiString LC_LabForme;

	__fastcall TEspeceFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEspeceFrm *EspeceFrm;
//---------------------------------------------------------------------------
#endif
