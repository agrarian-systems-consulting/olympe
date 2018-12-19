//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Indicateur.h"
#include "CL_Trad.h"

#include "LBChoixMCInd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoixMC"
#pragma resource "*.dfm"
TLBChoixMCIndFrm *LBChoixMCIndFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBChoixMCIndFrm::TLBChoixMCIndFrm(TComponent* Owner) :
		TLBChoixMCFrm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TLBChoixMCIndFrm::FormActivate(TObject *Sender)
{
	if(EstInitialise==false)
	{
		Edit=IndicateurFrm->Edit;
		RGModifiable=IndicateurFrm->RGModifiable;
		Left=IndicateurFrm->Left+Edit->Left+Edit->Width-Width-50;
		Top =IndicateurFrm->Top+Edit->Top+20;
		EstInitialise=true;
	}

}
//---------------------------------------------------------------------------
void __fastcall TLBChoixMCIndFrm::LBClick(TObject *Sender)
{
	int n;
	AnsiString motCle;
	AnsiString as;
	int startPos=Edit->SelStart+1;
	if(startPos==1) startPos=Edit->Text.Length();
	if(RGModifiable->ItemIndex==0)return;

	n=LB->ItemIndex;
	motCle=LB->Items->Strings[n];

	as=Edit->Text;
	as.Insert(motCle+"  ",startPos);
	Edit->Text=as;
	Edit->Modified=true;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBChoixMCIndFrm::IniCaption(void) {
	LBChoixMCIndFrm->Caption = T->LC_BtMotCle;
}
//--------------------------------------------
void TLBChoixMCIndFrm::TexteCaption(void) {
	LC_BtMotCle = T->TrouveCaption("CL_Trad", "LC_BtMotCle");

	IniCaption();

}
//--------------------------------------------

