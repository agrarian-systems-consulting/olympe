//---------------------------------------------------------------------------

#ifndef LBToutAgriH
#define LBToutAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLBToutAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PBas;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnPasOK;
	TCheckListBox *ChLB;
	TBitBtn *BtBnTous;
	TBitBtn *BtBnAucun;
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall BtBnPasOKClick(TObject *Sender);
	void __fastcall ChLBClickCheck(TObject *Sender);
	void __fastcall BtBnTousClick(TObject *Sender);
	void __fastcall BtBnAucunClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	void __fastcall MontrerErreurAn_0(void);

public:// Déclarations utilisateur
	AnsiString VientDe;
	void __fastcall Decoche(CL_Agriculteur *agri0);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtIndAucun;
	AnsiString LC_GereAgriFrm;
	AnsiString LC_BtIndTous;

	__fastcall TLBToutAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBToutAgriFrm *LBToutAgriFrm;
//---------------------------------------------------------------------------
#endif
