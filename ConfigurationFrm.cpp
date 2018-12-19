#include "ConfigurationFrm.h"
#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfigFrm *Config;
//---------------------------------------------------------------------------
__fastcall TConfigFrm::TConfigFrm() :
		TForm(Owner) //(TComponent* Owner) : TForm(Owner)
{
	ok = false;
}
//---------------------------------------------------------------------------

void __fastcall TConfigFrm::OKClick(TObject *Sender)
{
	ok = true;
	Close ();
}
//---------------------------------------------------------------------------

void __fastcall TConfigFrm::AnnulerClick(TObject *Sender)
{
	ok = false;
	Close ();
}
//---------------------------------------------------------------------------

