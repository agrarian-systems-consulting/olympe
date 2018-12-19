//---------------------------------------------------------------------------
#ifndef LBChoixH
#define LBChoixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <grids.hpp>
//---------------------------------------------------------------------------
class TLBChoixFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
protected: // Déclarations de l'utilisateur
	TStringGrid *LaGrille;
	TMemo *Memo;

	// ne pas modifier sans regarder AgriSaisie.h
	// cf       #include "AgriSaisieEnum.h"

public:// Déclarations de l'utilisateur
	int Origine;
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LBChoixFrm;

	__fastcall TLBChoixFrm(TComponent* Owner);
private:
	void __fastcall LBClickValeur(void);
	void __fastcall LBClickFormule(void);
	void __fastcall LBClickTvaImmo(void);
	void __fastcall LBClickTvaPetit(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixFrm *LBChoixFrm;
//---------------------------------------------------------------------------
#endif
