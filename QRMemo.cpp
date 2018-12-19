//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "QRMemo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQRMemoFrm *QRMemoFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRMemoFrm::TQRMemoFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TQRMemoFrm::IniCaption(void) {
	NomAgri->Caption = T->LC_NomAgri_A;
	QRMemoFrm->Caption = LC_QRMemoFrm;
	TitreEtat->Caption = T->LC_TitreEtat;
}
//--------------------------------------------
void TQRMemoFrm::TexteCaption(void) {
	LC_NomAgri_A = T->TrouveCaption("CL_Trad", "LC_NomAgri_A");
	LC_QRMemoFrm = T->TrouveCaption("QRMemo", "LC_QRMemoFrm");
	LC_TitreEtat = T->TrouveCaption("CL_Trad", "LC_TitreEtat");

	IniCaption();

}
//--------------------------------------------

