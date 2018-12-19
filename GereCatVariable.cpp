//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"

#include "DefVariable.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCatVariable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCatVariableFrm *GereCatVariableFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereCatVariableFrm::TGereCatVariableFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatVariableFrm::Personnaliser(void)
{
	switch(Nature)
	{
		case EXTPOS:
		//Caption=    "Externalités";
		V_Item= V_Externalite;
		V_Categorie=V_CatExternalite;
		DefVariableFrm->HelpContext=400;
		break;
		case VARIABLE:
		//Caption="Variables";
		V_Item= V_Variable;
		V_Categorie=V_CatVar;
		DefVariableFrm->HelpContext=510;
		break;
		default:
		ShowMessage("TGereCatVariableFrm::Personnaliser Oubli");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatVariableFrm::LBClick(TObject *Sender)
{
	int n;
	bool rep;
	if(DefVariableFrm->Visible==true)
	{
		if(Categorie) DefVariableFrm->Close();
	}
	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	{
		rep=NouvelleCategorie();
		if(rep==false) return;
	}

	Categorie=(CL_Categorie*)LB->Items->Objects[n];
	DefVariableFrm->Categorie=Categorie;
	DefVariableFrm->Caption=Caption;
	DefVariableFrm->Origine=0;
	DefVariableFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TGereCatVariableFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int repMB;
	if(DefVariableFrm->Visible==true)
	{
		if(Categorie) DefVariableFrm->Close();
	}
	if(LabelModifie->Visible==true)
	{
		repMB=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(repMB==ID_YES)
		{
			if(OrdreModif==true) StockerOrdre(V_Categorie);

			ES->ecrireFichier();
			LabelModifie->Visible=false;
		}
	}
}

//--------------------------------------------
void TGereCatVariableFrm::IniCaption(void) {
	GereCatVariableFrm->Caption = LC_GereCatVariableFrm;

	BtClAlpha->Caption = T->LC_BtBnAlpha;
	BtClasser->Caption = T->LC_BtClasser;
	BtBnCopier->Caption = T->LC_BtBnCopier;
	BtBnCreer->Caption = T->LC_BtBnCreer;
	BtBnFermer->Caption = T->LC_BtBnFermer;
	GereCatItemFrm->Caption = LC_GereCatItemFrm;
	BtModifier->Caption = T->LC_BtModifier;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	BtSupprimer->Caption = T->LC_BtBnSupBesTrav;

}
//--------------------------------------------
void TGereCatVariableFrm::TexteCaption(void) {
	LC_GereCatVariableFrm = T->TrouveCaption("GereCatVariable",
			"LC_GereCatVariableFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereCatVariableFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

