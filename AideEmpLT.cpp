//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AideEmpLT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAideEmpLTFrm *AideEmpLTFrm;
//---------------------------------------------------------------------------
__fastcall TAideEmpLTFrm::TAideEmpLTFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAideEmpLTFrm::Memo1Click(TObject *Sender)
{
	AideEmpLTFrm->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAideEmpLTFrm::RichEdit1ContextPopup(TObject *Sender,
		TPoint &MousePos, bool &Handled)
{
	Handled=true;
}
//---------------------------------------------------------------------------
void __fastcall TAideEmpLTFrm::RichEdit1Enter(TObject *Sender)
{
	AideEmpLTFrm->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TAideEmpLTFrm::RichEdit1SelectionChange(TObject *Sender)
{
	AideEmpLTFrm->SetFocus();

}
//---------------------------------------------------------------------------
