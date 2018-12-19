//---------------------------------------------------------------------------

#ifndef DefZoneH
#define DefZoneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DefChProduit.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "DefItem.h"
#include "DefItem.h"
//---------------------------------------------------------------------------
class TDefZoneFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnNotes;
	void __fastcall BtBnNotesClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations de l'utilisateur
	AnsiString L_Titre;

protected:
	virtual void __fastcall Personnaliser(void);
	void __fastcall AffItem(int row,CL_Item *item);
	bool __fastcall VerifGrille(TStringGrid *grille);
	virtual void __fastcall LireItem(CL_Item *item,int row);

public:// Déclarations de l'utilisateur
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_DefZoneFrm;

	__fastcall TDefZoneFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefZoneFrm *DefZoneFrm;
//---------------------------------------------------------------------------
#endif
