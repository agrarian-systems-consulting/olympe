//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FenResPlan.h"

#include "LBReservoir.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBLexique"
#pragma resource "*.dfm"
TLBReservoirFrm *LBReservoirFrm;
//---------------------------------------------------------------------------
__fastcall TLBReservoirFrm::TLBReservoirFrm(TComponent* Owner) :
		TLBLexiqueFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBReservoirFrm::FormCreate(TObject *Sender)
{

	LB->Items->Add("Date");
	LB->Items->Add("PrixKw");
	LB->Items->Add("Niveau(...)");
	LB->Items->Add("Volume");
	LB->Items->Add("Volume(...)");
	LB->Items->Add("PomperDans(...)");
	LB->Items->Add("PomperVers(...)");
	LB->Items->Add("<");
	LB->Items->Add(">");
	LB->Items->Add("ET");
	LB->Items->Add("OU");

}
//---------------------------------------------------------------------------
void __fastcall TLBReservoirFrm::LBClick(TObject *Sender)
{
	int n;
	TRichEdit *re;
	AnsiString motCle;
	AnsiString as;
	int startPos;
	re=FenResPlanFrm->REActif;
	startPos=re->SelStart+1;
	if(startPos==1) startPos=re->Text.Length();

	n=LB->ItemIndex;
	motCle=LB->Items->Strings[n];

	as=re->Text;
	as.Insert(motCle+"  ",startPos);
	re->Text=as;

	re->Modified=true;

}
//---------------------------------------------------------------------------
