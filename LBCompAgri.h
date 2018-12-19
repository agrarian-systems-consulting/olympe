//---------------------------------------------------------------------------

#ifndef LBCompAgriH
#define LBCompAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLBCompAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TCheckListBox	*ChLB;
	TPanel *PBas;
	TBitBtn *BtBnFermer;
	TBitBtn *BtBnTous;
	TBitBtn *BtBnAucun;
	void __fastcall BtBnTousClick(TObject *Sender);
	void __fastcall BtBnAucunClick(TObject *Sender);
	void __fastcall BtBnFermerClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtIndAucun;
	AnsiString LC_GereAgriFrm;
	AnsiString LC_BtIndTous;

	__fastcall TLBCompAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBCompAgriFrm *LBCompAgriFrm;
//---------------------------------------------------------------------------
#endif
