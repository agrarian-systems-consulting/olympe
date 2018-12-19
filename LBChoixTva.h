//---------------------------------------------------------------------------

#ifndef LBChoixTvaH
#define LBChoixTvaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLBChoixTvaFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TListBox	*LB;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // D�clarations utilisateur
protected:// D�clarations de l'utilisateur
	TStringGrid *LaGrille;
public:// D�clarations utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtBnTva;

	__fastcall TLBChoixTvaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBChoixTvaFrm *LBChoixTvaFrm;
//---------------------------------------------------------------------------
#endif
