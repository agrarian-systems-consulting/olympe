//---------------------------------------------------------------------------

#ifndef LBSysUnitH
#define LBSysUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLBSysUnitFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	TPanel *PanUnite;
	TLabel *Label1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBDblClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	AnsiString AppelePar;
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_Label1;
	AnsiString LC_LBSysUnitFrm;

	__fastcall TLBSysUnitFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBSysUnitFrm *LBSysUnitFrm;
//---------------------------------------------------------------------------
#endif
