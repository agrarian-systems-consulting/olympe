//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Forme0.h"
#include "LBSysUnit.h"
#include "Conversion.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBConversion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBConversionFrm *LBConversionFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLBConversionFrm::TLBConversionFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBConversionFrm::FormActivate(TObject *Sender)
{
	Forme0Frm->CreeLBConversion(LB,V_Conversion);
}
//---------------------------------------------------------------------------
void __fastcall TLBConversionFrm::LBClick(TObject *Sender)
{
	int n;
	AnsiString s;
	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		LBSysUnitFrm->AppelePar="LBConversion";
		LBSysUnitFrm->Show();
	}
	else
	{
		Conversion=(CL_Conversion*)LB->Items->Objects[n];
		// il est global
		ConversionFrm->RetourDeChoix(true);
		Close();
	}

}
// est appelé par LBSysUnit
//---------------------------------------------------------------------------
void __fastcall TLBConversionFrm::NouvelleConversion(CL_SystemeUnite *sysUnit)
{
	bool rep;
	AnsiString nom=sysUnit->UUt;

	rep=InputQuery("Nouvelle Conversion","Donner son Nom",nom);
	if(rep==false) return;

	Conversion=new CL_Conversion(SysMonnaie,sysUnit);
	Conversion->Nom=nom;
	V_Conversion->ins(Conversion);
	// ajouter
	Forme0Frm->CreeLBConversion(LB,V_Conversion);
//    ConversionFrm->Show();
	ConversionFrm->RetourDeChoix(true);
	Close();
}
//--------------------------------------------
void TLBConversionFrm::IniCaption(void) {
	LBConversionFrm->Caption = LC_LBConversionFrm;
}
//--------------------------------------------
void TLBConversionFrm::TexteCaption(void) {
	LC_LBConversionFrm = T->TrouveCaption("LBConversion", "LC_LBConversionFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBConversionFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

