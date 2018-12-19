//---------------------------------------------------------------------------
#ifndef ErreurH
#define ErreurH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TErreurFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRichEdit	*Edit;
	TPanel *Panel1;
	TButton *BtImprimer;
	TBitBtn *BtBnFermer;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtImprimerClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
//	void MonPrintf(char *format, ...);

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_ErreurFrm;
	AnsiString LC_BtBnFermer;
	AnsiString LC_BtImprimer;

	__fastcall TErreurFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TErreurFrm *ErreurFrm;
//---------------------------------------------------------------------------
#endif
