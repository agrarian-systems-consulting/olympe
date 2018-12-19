//---------------------------------------------------------------------------

#ifndef EntreChaineH
#define EntreChaineH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TEntreChaineFrm: public TForm {
	__published: // Composants gérés par l'EDI
TEdit	*Edit1;
	TBitBtn *BtBnOk;
	TBitBtn *BtBnAnnul;
	TLabel *LabAAfficher;
	void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnOkClick(TObject *Sender);
	void __fastcall BtBnAnnulClick(TObject *Sender);
private: // Déclarations utilisateur
	int isalnumA(unsigned char c);
public:// Déclarations utilisateur
	bool __fastcall EntreChaine(AnsiString Titre,AnsiString AAfficher,AnsiString &Nom);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_EntreChaineFrm;
	AnsiString LC_LabAAfficher;

	__fastcall TEntreChaineFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEntreChaineFrm *EntreChaineFrm;
//---------------------------------------------------------------------------
#endif
