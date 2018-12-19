//---------------------------------------------------------------------------

#ifndef LBConversionH
#define LBConversionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TLBConversionFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	void __fastcall NouvelleConversion(CL_SystemeUnite *sysUnit);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_LBConversionFrm;

	__fastcall TLBConversionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBConversionFrm *LBConversionFrm;
//---------------------------------------------------------------------------
#endif
