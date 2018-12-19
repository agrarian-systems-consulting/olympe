//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Treso.h"
#include "TresoRepart.h"
#include "FenRepartDef.h"
#include "TVChoixRepart.h"
#include "Treso.h"

#include "TresoQouV.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTresoQouVFrm *TresoQouVFrm;
//---------------------------------------------------------------------------
__fastcall TTresoQouVFrm::TTresoQouVFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoQouVFrm::RGQouVClick(TObject *Sender)
{
	switch(TresoQouVFrm->RGQouV->ItemIndex)
	{
		case 0:
		TresoFrm->Caption ="Tresorerie en Valeur";
		break;
		case 1:
		TresoFrm->Caption ="Tresorerie en Quantité";
		break;
		case 2:
		TresoFrm->Caption ="Tresorerie Autre";
		ShowMessage("A discuter");
		//TresoFrm->QouV=3; //A definir
		break;
	}

	// mal placé a voir !!!!!!
	TresoRepartFrm->Origine=0;

}
//---------------------------------------------------------------------------

void __fastcall TTresoQouVFrm::BtOkClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

