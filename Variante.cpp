//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Variante.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVVarianteFrm *TVVarianteFrm;
//---------------------------------------------------------------------------
__fastcall TTVVarianteFrm::TTVVarianteFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVVarianteFrm::FormResize(TObject *Sender)
{
	TV->Height=ClientHeight;
	TV->Width=ClientWidth;
	TV->FullExpand();
}
//---------------------------------------------------------------------------
