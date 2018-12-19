//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#pragma hdrstop
#include "CL_Trad.h"
#include "Main.h"

#include "LBChoixMC.h"
#include "Indicateur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoix"
#pragma resource "*.dfm"
TLBChoixMCFrm *LBChoixMCFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBChoixMCFrm::TLBChoixMCFrm(TComponent* Owner) :
		TLBChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLBChoixMCFrm::LBClick(TObject *Sender)
{
	int n;
	AnsiString motCle;
	AnsiString as;
	int startPos=IndicateurFrm->Edit->SelStart+1;
//	if(startPos==1) startPos=Memo->Text.Length();
	if(startPos==1) startPos=IndicateurFrm->Edit->Text.Length();

	n=LB->ItemIndex;
	motCle=LB->Items->Strings[n];

//    as=Memo->Text;
	as=IndicateurFrm->Edit->Text;
	as.Insert(motCle+"  ",startPos);
	IndicateurFrm->Edit->Text=as;
//    Memo->Text=as;

//    Memo->Modified=true;
	IndicateurFrm->Edit->Modified=true;
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TLBChoixMCFrm::IniCaption(void) {
	LBChoixMCFrm->Caption = T->LC_BtMotCle;
}
//--------------------------------------------
void TLBChoixMCFrm::TexteCaption(void) {
	LC_BtMotCle = T->TrouveCaption("CL_Trad", "LC_BtMotCle");

	IniCaption();

}
//--------------------------------------------
//---------------------------------------------------------------------------
void TLBChoixMCFrm::TraduireMotCle(void) {
	switch (MainForm->Langue) {
	case 'F': //Français
		LB->Items->Strings[12] = "AN";
		LB->Items->Strings[18] = "SI( )";
		LB->Items->Strings[19] = "SINONSI( )";
		LB->Items->Strings[20] = "SINON";
		LB->Items->Strings[22] = "ET";
		LB->Items->Strings[23] = "OU";
		break;
	case 'E': //english
		LB->Items->Strings[12] = "YEAR";
		LB->Items->Strings[18] = "IF( )";
		LB->Items->Strings[19] = "ELSEIF( )";
		LB->Items->Strings[20] = "ELSE";
		LB->Items->Strings[22] = "AND";
		LB->Items->Strings[23] = "OR";
		break;
	}
}

