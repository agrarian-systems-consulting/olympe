//---------------------------------------------------------------------------

#ifndef ActionRemplacerH
#define ActionRemplacerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "DefAction.h"

//---------------------------------------------------------------------------
class TActionRemplacerFrm: public TForm {
	__published: // Composants gérés par l'EDI
TLabel	*LabNomAction;
	TLabel *LabPar;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *LabSur;
	TEdit *Edit3;
	TLabel *Label1;
	void __fastcall FormActivate(TObject *Sender);
private: // Déclarations de l'utilisateur
	AnsiString LC_Label1;
	AnsiString LC_LabPar;
	AnsiString LC_ActionRemplacerFrm;
	AnsiString LC_LabSur;
	void IniCaption(void);
public:// Déclarations de l'utilisateur
	/*
	 AnsiString LC_Label1;
	 AnsiString LC_LabPar;
	 AnsiString LC_ActionRemplacerFrm;
	 AnsiString LC_LabSur;
	 */
//??    void IniCaption(void);
	void TexteCaption(void);

	CL_Action *action;
	__fastcall TActionRemplacerFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TActionRemplacerFrm *ActionRemplacerFrm;
//---------------------------------------------------------------------------
#endif
