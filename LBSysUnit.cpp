//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Forme0.h"
#include "Conversion.h"

#include "LBConversion.h"
//#include "DefItem.h"
#include "DefProduit.h"
#include "DefVariable.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBSysUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBSysUnitFrm *LBSysUnitFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBSysUnitFrm::TLBSysUnitFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBSysUnitFrm::FormActivate(TObject *Sender)
{
	Forme0Frm->CreeLBUnite(LB,V_SystemeUnite);
}
//---------------------------------------------------------------------------
void __fastcall TLBSysUnitFrm::LBDblClick(TObject *Sender)
{
	int n;
	CL_SystemeUnite *sysUnit;
	n=LB->ItemIndex;
	sysUnit=(CL_SystemeUnite*)LB->Items->Objects[n];
	if(sysUnit==NULL)
	{
		Close();
		MainForm->BtUniteClick(this);
		return;
	}
	if(AppelePar=="LBConversion")
	{
		LBConversionFrm->NouvelleConversion(sysUnit);
		Close();
		return;
	}
//    else if(AppelePar=="Categorie")     DefItemFrm->RetourDeChoixUnite(sysUnit);
	else if(AppelePar=="DefProduitFrm") DefProduitFrm->RetourDeChoixUnite(sysUnit);
	else if(AppelePar=="DefVariableFrm") DefVariableFrm->RetourDeChoixUnite(sysUnit);
}

//--------------------------------------------
void TLBSysUnitFrm::IniCaption(void) {
	Label1->Caption = LC_Label1;
	LBSysUnitFrm->Caption = T->LC_LBSysUnitFrm;
}
//--------------------------------------------
void TLBSysUnitFrm::TexteCaption(void) {
	LC_Label1 = T->TrouveCaption("LBSysUnit", "LC_Label1");
	LC_LBSysUnitFrm = T->TrouveCaption("CL_Trad", "LC_LBSysUnitFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBSysUnitFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

