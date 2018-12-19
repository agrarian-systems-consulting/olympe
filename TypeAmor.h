//---------------------------------------------------------------------------

#ifndef TypeAmorH
#define TypeAmorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTypeAmorFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGAmor;
	TBitBtn *BtBnOk;
	void __fastcall BtBnOkClick(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Amor;
	AnsiString LC_Degressif;
	AnsiString LC_Lineaire;
	AnsiString LC_Sans;
	__fastcall TTypeAmorFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTypeAmorFrm *TypeAmorFrm;
//---------------------------------------------------------------------------
#endif
