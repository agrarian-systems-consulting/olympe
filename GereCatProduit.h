//---------------------------------------------------------------------------

#ifndef GereCatProduitH
#define GereCatProduitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCatProduitFrm: public TGereCatItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall LBClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);void __fastcall BtBnAideClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereCatProduitFrm;

	virtual void __fastcall Personnaliser(void);
protected:
//    virtual void __fastcall Personnaliser(void);
//	virtual void __fastcall Nouveau(void);

	__fastcall TGereCatProduitFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCatProduitFrm *GereCatProduitFrm;
//---------------------------------------------------------------------------
#endif
