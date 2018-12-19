//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "Main.h"
#include "CL_Trad.h"

#include "APropos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAProposFrm *AProposFrm;
// voir c++ 14 jours p 201

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TAProposFrm::TAProposFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAProposFrm::FormActivate(TObject *Sender)
{
	char buf[50];
	float version=(float)ES->Version/100.;

	if(ES->Verrou==MEDTER) return;

	sprintf(buf,MainForm->L_DateLim.c_str(),MainForm->MoisLimite,MainForm->AnLimite);
//    sprintf(buf,"date limite %2d %2d",MainForm->MoisLimite,MainForm->AnLimite);

	LabVersion->Caption=AnsiString("Version ")+FloatToStrF(version,ffNumber,7,2);
	LabLimite->Caption=AnsiString(buf);
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TAProposFrm::TexteCaption(void) {
	LC_APropos = T->TrouveCaption("AProposFrm", "LC_APropos");
	Caption = LC_APropos;
}
//---------------------------------------------------------------------------

