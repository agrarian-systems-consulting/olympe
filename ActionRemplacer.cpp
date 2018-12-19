//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CL_Trad.h"
#include "ActionRemplacer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TActionRemplacerFrm *ActionRemplacerFrm;

extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TActionRemplacerFrm::TActionRemplacerFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TActionRemplacerFrm::FormActivate(TObject *Sender)
{
	CL_Atelier *culture0,*culture1;

	culture0=V_Culture->trouve(action->LesInt[0]);
	culture1=V_Culture->trouve(action->LesInt[1]);
	Edit1->Text=culture0->Nom;
	Edit2->Text=culture1->Nom;
	Edit3->Text=AnsiString(action->LesFloat[0]);

}
//---------------------------------------------------------------------------
void TActionRemplacerFrm::IniCaption(void) {
	Label1->Caption = LC_Label1;
	LabPar->Caption = LC_LabPar;
//    ActionRemplacerFrm->Caption=T->LC_ActionRemplacerFrm;
	ActionRemplacerFrm->Caption = LC_ActionRemplacerFrm;
	LabNomAction->Caption = LC_ActionRemplacerFrm;
	LabSur->Caption = LC_LabSur;
}
//--------------------------------------------
void TActionRemplacerFrm::TexteCaption(void) {
	AnsiString as;
	as = T->TrouveCaption("ActionRemplacer", "LC_Label1");
	LC_Label1 = as;
//??     LC_Label1 =T->TrouveCaption("ActionRemplacer" ,"LC_Label1");
	LC_LabPar = T->TrouveCaption("ActionRemplacer", "LC_LabPar");
	LC_ActionRemplacerFrm = T->TrouveCaption("CL_Trad",
			"LC_ActionRemplacerFrm");
	LC_LabSur = T->TrouveCaption("ActionRemplacer", "LC_LabSur");
}

