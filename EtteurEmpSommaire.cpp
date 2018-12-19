//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "EtteurEmpSommaire.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ErreurImmoSommaire"
#pragma resource "*.dfm"
TErreurEmpSommaireFrm *ErreurEmpSommaireFrm;
//---------------------------------------------------------------------------
__fastcall TErreurEmpSommaireFrm::TErreurEmpSommaireFrm(TComponent* Owner) :
		TErreurImmoSommaireFrm(Owner) {
}
//---------------------------------------------------------------------------
