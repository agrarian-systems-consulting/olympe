//---------------------------------------------------------------------------

#ifndef ModCaptionH
#define ModCaptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <stdio.h>

//---------------------------------------------------------------------------
class TModCaptionFrm: public TForm {
	__published: // Composants gérés par l'EDI
TButton	*Button1;
	void __fastcall Button1Click(TObject *Sender);
private: // Déclarations de l'utilisateur
	void __fastcall ModCaption(void);
	void __fastcall NomProgramme(void);

public:// Déclarations de l'utilisateur
	__fastcall TModCaptionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModCaptionFrm *ModCaptionFrm;
//---------------------------------------------------------------------------
#endif
