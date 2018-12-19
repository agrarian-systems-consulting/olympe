//---------------------------------------------------------------------------

#ifndef Motif2H
#define Motif2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TMotif2Frm: public TForm {
	__published: // Composants gérés par l'EDI
TGroupBox	*GroupBox1;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private: // Déclarations de l'utilisateur
	void __fastcall LegendeAtelier(void);
	int LesMotifs[10];
	int MotifX;

public:// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GroupBox1;
	AnsiString LC_Motif2Frm;

	__fastcall TMotif2Frm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMotif2Frm *Motif2Frm;
//---------------------------------------------------------------------------
#endif
