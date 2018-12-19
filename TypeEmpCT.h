//---------------------------------------------------------------------------

#ifndef TypeEmpCTH
#define TypeEmpCTH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTypeEmpCTFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TRadioGroup	*RGEP;
	TRadioGroup *RGInteret;
	TBitBtn *BtBnOk;
	void __fastcall BtBnOkClick(TObject *Sender);
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Interet;
	AnsiString LC_Normal;
	AnsiString LC_PreCompte;

	AnsiString LC_EP;
	AnsiString LC_Entreprise;
	AnsiString LC_Prive;
	__fastcall TTypeEmpCTFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTypeEmpCTFrm *TypeEmpCTFrm;
//---------------------------------------------------------------------------
#endif
