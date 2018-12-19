//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DefAction.h"
#include "ActionRemplacer.h"

#include "LBChoixMCAction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoixMC"
#pragma resource "*.dfm"
TLBChoixMCActionFrm *LBChoixMCActionFrm;
//---------------------------------------------------------------------------
__fastcall TLBChoixMCActionFrm::TLBChoixMCActionFrm(TComponent* Owner) :
		TLBChoixMCFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixMCActionFrm::FormActivate(TObject *Sender)
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
void __fastcall TLBChoixMCActionFrm::LBClick(TObject *Sender)
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
		ActionRemplacerFrm->Show();
		break;
		default:
		nomAction+=AnsiString(" ")+AnsiString(noAction);
		ShowMessage(nomAction);

	}

}
//---------------------------------------------------------------------------
