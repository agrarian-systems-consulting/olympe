//---------------------------------------------------------------------------

#ifndef TVChoixCalendrierH
#define TVChoixCalendrierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixCalendrierFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall TVDblClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
public:
	// Déclarations de l'utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GBAtelier;

	__fastcall TTVChoixCalendrierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixCalendrierFrm *TVChoixCalendrierFrm;
//---------------------------------------------------------------------------
#endif
