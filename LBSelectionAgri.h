//---------------------------------------------------------------------------

#ifndef LBSelectionAgriH
#define LBSelectionAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TLBSelectionAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnPasOK;
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall BtBnPasOKClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	AnsiString VientDe;
	void TexteCaption(void);
	void IniCaption(void);
	void TexteChaine(void);

	AnsiString LC_LBSelectionAgriFrm;

	AnsiString L_Manuel;
	AnsiString L_Tri;
	AnsiString L_Addition;
	AnsiString L_Extraire;

	__fastcall TLBSelectionAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBSelectionAgriFrm *LBSelectionAgriFrm;
//---------------------------------------------------------------------------
#endif
