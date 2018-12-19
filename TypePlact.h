//---------------------------------------------------------------------------

#ifndef TypePlactH
#define TypePlactH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTypePlactFrm: public TForm {
	__published: // Composants g�r�s par l'EDI
TRadioGroup	*RGInteret;
	TRadioGroup *RGEP;
	TBitBtn *BtBnOk;
	void __fastcall BtBnOkClick(TObject *Sender);
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Interet;
	AnsiString LC_Annuel;
	AnsiString LC_AlaFin;

	AnsiString LC_EP;
	AnsiString LC_Entreprise;
	AnsiString LC_Prive;

	__fastcall TTypePlactFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTypePlactFrm *TypePlactFrm;
//---------------------------------------------------------------------------
#endif
