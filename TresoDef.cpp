//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Treso.h"
#include "TresoRepart.h"

#include "TresoDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TTresoDefFrm *TresoDefFrm;
//---------------------------------------------------------------------------
__fastcall TTresoDefFrm::TTresoDefFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefFrm::FormCreate(TObject *Sender)
{
	QouV=VALEUR;
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefFrm::FormActivate(TObject *Sender)
{
	int i,r;
	Top=TresoFrm->Top+50;
	Left=TresoFrm->Left;
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefFrm::RGQouVClick(TObject *Sender)
{
	if(RGQouV->ItemIndex==0) QouV=VALEUR;
	else QouV=QUANTITE;
	// mal placé a voir !!!!!!
	TresoRepartFrm->Origine=0;

	// id pour TresoCharges
}
//---------------------------------------------------------------------------

