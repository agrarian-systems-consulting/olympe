//---------------------------------------------------------------------------

#ifndef LBProduitH
#define LBProduitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLBProduitFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	void __fastcall LBClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtBnProduit;

	__fastcall TLBProduitFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBProduitFrm *LBProduitFrm;
//---------------------------------------------------------------------------
#endif
