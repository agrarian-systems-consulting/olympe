//---------------------------------------------------------------------------
#ifndef NoteEnsembleH
#define NoteEnsembleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "NoteAgri.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TNoteEnsembleFrm: public TNoteAgriFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall BtBnAnnuleClick(TObject *Sender);void __fastcall MemoChange(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:
	// D�clarations de l'utilisateur
public:
	// D�clarations de l'utilisateur
	CL_Ensemble *Ensemble;
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_NoteEnsembleFrm;

	__fastcall TNoteEnsembleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNoteEnsembleFrm *NoteEnsembleFrm;
//---------------------------------------------------------------------------
#endif
