//---------------------------------------------------------------------------

#ifndef GereCatBestiauxH
#define GereCatBestiauxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereCatItem.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCatBestiauxFrm: public TGereCatItemFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall LBClick(TObject *Sender);void __fastcall BtSupprimerClick(TObject *Sender);void __fastcall BtBnCopierClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
	void __fastcall MajV_Bestiaux(CL_Categorie *cat);

protected:
	virtual void __fastcall Personnaliser(void);

public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereCatBestiauxFrm;

	__fastcall TGereCatBestiauxFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCatBestiauxFrm *GereCatBestiauxFrm;
//---------------------------------------------------------------------------
#endif
