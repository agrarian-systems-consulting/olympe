//---------------------------------------------------------------------------

#ifndef GereComparaisonH
#define GereComparaisonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereEtat.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereComparaisonFrm: public TGereEtatFrm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnAide;
	void __fastcall FormActivate(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations de l'utilisateur
protected:

public:// Déclarations de l'utilisateur
	void __fastcall CompleteComparaison(void);//agriSaisieCalcul
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereComparaisonFrm;

	__fastcall TGereComparaisonFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereComparaisonFrm *GereComparaisonFrm;
//---------------------------------------------------------------------------
#endif
