//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "DefAction.h"

//#include "ActionRemplacer.h"

#include "LBChoixAction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoixMC"
#pragma resource "*.dfm"
TLBChoixActionFrm *LBChoixActionFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBChoixActionFrm::TLBChoixActionFrm(TComponent* Owner) :
		TLBChoixMCFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixActionFrm::FormActivate(TObject *Sender)
{
	int n;
	if(EstInitialise==false)
	{
		Edit=DefActionFrm->REdit;
		Left=DefActionFrm->Left+Edit->Left+Edit->Width-Width-50;
		Top =DefActionFrm->Top+Edit->Top+20;

		LB->Clear();
		n=0;LB->Items->AddObject("Remplacer",(TObject*)n);

		n=1;LB->Items->AddObject("Planter",(TObject*)n);
		n=2;LB->Items->AddObject("Arracher",(TObject*)n);

		n=3;LB->Items->AddObject("Investir",(TObject*)n);
		n=4;LB->Items->AddObject("Emprunter",(TObject*)n);

		EstInitialise=true;
	}

}
//---------------------------------------------------------------------------
void __fastcall TLBChoixActionFrm::LBClick(TObject *Sender)
{
	int n;
	AnsiString nomAction;
	int noAction;
	n=LB->ItemIndex;
	nomAction=LB->Items->Strings[n];
	noAction=(int)LB->Items->Objects[n];
	switch(noAction)
	{
		case 0:
		//ActionRemplacerFrm->Show();
		break;
		default:
		nomAction+=AnsiString(" ")+AnsiString(noAction);
		ShowMessage(nomAction);

	}

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBChoixActionFrm::IniCaption(void) {
	LBChoixActionFrm->Caption = LC_LBChoixActionFrm;
}
//--------------------------------------------
void TLBChoixActionFrm::TexteCaption(void) {
	LC_LBChoixActionFrm = T->TrouveCaption("LBChoixAction",
			"LC_LBChoixActionFrm");

	IniCaption();

}
//--------------------------------------------

