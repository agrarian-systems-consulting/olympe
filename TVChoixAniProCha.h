//---------------------------------------------------------------------------

#ifndef TVChoixAniProChaH
#define TVChoixAniProChaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixAniProChaFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall TVDblClick(TObject *Sender);void __fastcall FormActivate(TObject *Sender);
private:
	// Déclarations de l'utilisateur

public:
	// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);

//    AnsiString LC_[0]TLabel;

	__fastcall TTVChoixAniProChaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixAniProChaFrm *TVChoixAniProChaFrm;
//---------------------------------------------------------------------------
#endif
