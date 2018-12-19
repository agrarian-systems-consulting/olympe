//---------------------------------------------------------------------------

#ifndef LBMargeH
#define LBMargeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LBCompAgri.h"
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLBMargeFrm: public TLBCompAgriFrm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnOk;
	void __fastcall BtBnOkClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LBMargeFrm;

	__fastcall TLBMargeFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBMargeFrm *LBMargeFrm;
//---------------------------------------------------------------------------
#endif
