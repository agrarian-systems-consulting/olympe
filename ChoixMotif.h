//---------------------------------------------------------------------------

#ifndef ChoixMotifH
#define ChoixMotifH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TChoixMotifFrm: public TForm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnQuitter;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
private: // Déclarations de l'utilisateur
	int X0,Y0;
	int Hauteur;
	int Largeur;
public:// Déclarations de l'utilisateur
	CL_Atelier *Atelier;
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_ChoixMotifFrm;

	__fastcall TChoixMotifFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChoixMotifFrm *ChoixMotifFrm;
//---------------------------------------------------------------------------
#endif
