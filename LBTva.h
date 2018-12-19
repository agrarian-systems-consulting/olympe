//---------------------------------------------------------------------------

#ifndef LBTvaH
#define LBTvaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLBTvaFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBDblClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	AnsiString AppelePar;
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtBnTva;
	__fastcall TLBTvaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBTvaFrm *LBTvaFrm;
//---------------------------------------------------------------------------
#endif
