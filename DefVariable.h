//---------------------------------------------------------------------------

#ifndef DefVariableH
#define DefVariableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DefItem.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TDefVariableFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall BtRepBasClick(TObject *Sender);void __fastcall BtBnUniteClick(TObject *Sender);void __fastcall BtRecopBasClick(TObject *Sender);void __fastcall BtBnNoteClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
//	void __fastcall BtBnUniteClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	AnsiString L_Titre;
//    AnsiString L_NonDef;
//    AnsiString L_PasDUnit;   

protected:
	virtual void __fastcall Personnaliser(void);virtual void __fastcall LireItem(CL_Item *item,int row);

	virtual void __fastcall AffItem(int row,CL_Item *item);virtual bool __fastcall VerifGrille(TStringGrid *grille);

public:
	// Déclarations de l'utilisateur
	void __fastcall RetourDeChoixUnite(CL_SystemeUnite *sysUnit);
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_VARIABLES;

	__fastcall TDefVariableFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefVariableFrm *DefVariableFrm;
//---------------------------------------------------------------------------
#endif
