//---------------------------------------------------------------------------

#ifndef DefChStructH
#define DefChStructH
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
class TDefChStructFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall BtRepBasClick(TObject *Sender);void __fastcall BtBnTvaClick(TObject *Sender);void __fastcall BtBnNoteClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
protected:
	virtual void __fastcall Personnaliser(void);void __fastcall AffItem(int row,CL_Item *item);bool __fastcall VerifGrille(TStringGrid *grille);virtual void __fastcall LireItem(CL_Item *item,int row);
	AnsiString L_Titre;
//    AnsiString L_EltNonDef;

public:
	// Déclarations de l'utilisateur
	void __fastcall RetourDeChoixTva (CL_Tva *tva);
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_DefChStructFrm;

	__fastcall TDefChStructFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefChStructFrm *DefChStructFrm;
//---------------------------------------------------------------------------
#endif
