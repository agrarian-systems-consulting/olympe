//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "CL_Trad.h"

#include "NoteEnsemble.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NoteAgri"
#pragma resource "*.dfm"
TNoteEnsembleFrm *NoteEnsembleFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TNoteEnsembleFrm::TNoteEnsembleFrm(TComponent* Owner) :
		TNoteAgriFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TNoteEnsembleFrm::FormActivate(TObject *Sender)
{
	if(Ensemble==NULL) return;
	Memo->Text=Ensemble->Notes;
	Modif=false;
}
//---------------------------------------------------------------------------
void __fastcall TNoteEnsembleFrm::BtBnAnnuleClick(TObject *Sender)
{
	Modif=false;
}
//---------------------------------------------------------------------------
void __fastcall TNoteEnsembleFrm::MemoChange(TObject *Sender)
{
	Modif=true;
}
//---------------------------------------------------------------------------

void __fastcall TNoteEnsembleFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(Modif==false)return;
	Ensemble->Notes=Memo->Text;
	ES->ecrireFichier();

}
//---------------------------------------------------------------------------
void TNoteEnsembleFrm::IniCaption(void) {
	NoteEnsembleFrm->Caption = LC_NoteEnsembleFrm;
}
//--------------------------------------------
void TNoteEnsembleFrm::TexteCaption(void) {
	LC_NoteEnsembleFrm = T->TrouveCaption("NoteEnsemble", "LC_NoteEnsembleFrm");

	IniCaption();

}
//--------------------------------------------

