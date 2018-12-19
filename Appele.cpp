//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Appele.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAppeleFrm *AppeleFrm;
//---------------------------------------------------------------------------
__fastcall TAppeleFrm::TAppeleFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAppeleFrm::BtBnAnimationClick(TObject *Sender)
{
	AnimateWindow(Handle,5000, AW_HIDE |AW_SLIDE | AW_VER_POSITIVE);
	AnimateWindow(Handle,5000, AW_ACTIVATE |AW_SLIDE | AW_HOR_POSITIVE);
}
//---------------------------------------------------------------------------

void __fastcall TAppeleFrm::FormActivate(TObject *Sender)
{
	Logo1->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TAppeleFrm::Logo1Stop(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

