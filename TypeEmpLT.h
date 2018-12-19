//---------------------------------------------------------------------------

#ifndef TypeEmpLTH
#define TypeEmpLTH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTypeEmpLTFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGTypeRemb;
	TRadioGroup *RGFrequence;
	TBitBtn *BtBnOk;
	TRadioGroup *RGEP;
	void __fastcall BtBnOkClick(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Remboursement;
	AnsiString LC_Constant;
	AnsiString LC_Variable;
	AnsiString LC_Differe;

	AnsiString LC_Frequence;
	AnsiString LC_Annuel;
	AnsiString LC_Semestriel;
	AnsiString LC_Trimestriel;
	AnsiString LC_Mensuel;

	AnsiString LC_EP;
	AnsiString LC_Entreprise;
	AnsiString LC_Prive;

	__fastcall TTypeEmpLTFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTypeEmpLTFrm *TypeEmpLTFrm;
//---------------------------------------------------------------------------
#endif
