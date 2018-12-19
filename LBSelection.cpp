//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "GereEnsemble.h"

#include "LBSelection.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBSelectionFrm *LBSelectionFrm;
//---------------------------------------------------------------------------
__fastcall TLBSelectionFrm::TLBSelectionFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBSelectionFrm::LBDblClick(TObject *Sender)
{
	int n;
	n=LB->ItemIndex;
	switch(n)
	{
		case 0: GereEnsembleFrm->SelectionManuelle();break;
		case 1: GereEnsembleFrm->SelectionTri(); break;
		case 2: GereEnsembleFrm->SelectionAddition();break;
		default: ShowMessage("LBSelection Oubli");
	}
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TLBSelectionFrm::BtBnOKClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TLBSelectionFrm::BtBnPasOKClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
