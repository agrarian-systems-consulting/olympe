//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "AgriData.h"

#include "ImpDelta.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImpDeltaFrm *ImpDeltaFrm;
//---------------------------------------------------------------------------
__fastcall TImpDeltaFrm::TImpDeltaFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TImpDeltaFrm::EdFicCsvClick(TObject *Sender)
{
	bool rep;
	AnsiString as;
	rep=OpenDialogFicCsv->Execute();
	if(rep)
	{
		EdFicCsv->Text=OpenDialogFicCsv->FileName;
	}

}
//---------------------------------------------------------------------------
void __fastcall TImpDeltaFrm::BtBnOKClick(TObject *Sender)
{
	if(EdFicCsv->Text=="")
	{
		ShowMessage("Pas de Fichier");
		return;
	}
	AgriDataFrm->ImportDelta();
}
//---------------------------------------------------------------------------
