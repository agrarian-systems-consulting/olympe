//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"

#include "DefChStruct.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCatChStruct.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCatChStructFrm *GereCatChStructFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereCatChStructFrm::TGereCatChStructFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatChStructFrm::Personnaliser(void)
{
//ShowMessage(AnsiString("TGereCatChStructFrm::Personnaliser  ")+Nature);

	switch(Nature)
	{
		case CHSTRUCT:
//            Caption=ES->LesTitresCeg[16];//"Charges de structure";//130206
		Caption=L_ChStruct;//"Charges de Structure";
		V_Item= V_ChStruct;
		V_Categorie=V_CatChStruct;
		DefChStructFrm->HelpContext=440;
		break;
		case DEPDIV:
//            Caption=ES->LesTitresCeg[14];//"Dépenses Diverses";
		Caption=L_DepDiv;//"Dépenses diverses";
		V_Item= V_DepDiv;
		V_Categorie=V_CatDepDiv;
		DefChStructFrm->HelpContext=450;
		break;
		case RECDIV:
//            Caption=ES->LesTitresCeg[2];//"Recettes Diverses";
		Caption=L_RecDiv;//"Recettes Diverses";
		V_Item= V_RecDiv;
		V_Categorie=V_CatRecDiv;
		DefChStructFrm->HelpContext=460;
		break;
		case RECFAM:
//            Caption=ES->LesTitresPoste[6];
		Caption=L_RecFam;//"Recettes Familiales";
		V_Item= V_RecFam;
		V_Categorie=V_CatRecFam;
		DefChStructFrm->HelpContext=480;
		break;
		case DEPFAM:
//            Caption=ES->LesTitresPoste[7];
		Caption=L_DepFam;//"Dépenses Familiales";
		V_Item= V_DepFam;
		V_Categorie=V_CatDepFam;
		DefChStructFrm->HelpContext=470;
		break;
		case EXTPOS:
		case EXTNEG:
		Caption=L_Exter;
		V_Item= V_Externalite;
		V_Categorie=V_CatExternalite;
		DefChStructFrm->HelpContext=470;
		break;

		default:
		ShowMessage("Oubli dans TGereCatChStructFrm::Personnaliser");
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatChStructFrm::LBClick(TObject *Sender)
{
	int n;
	bool rep;
	if(DefChStructFrm->Visible==true)
	{
		if(Categorie) DefChStructFrm->Close();
	}

	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	{
		rep=NouvelleCategorie();
		if(rep==false) return;
	}
	Categorie=(CL_Categorie*)LB->Items->Objects[n];
	DefChStructFrm->Categorie=Categorie;
	DefChStructFrm->Caption=Caption;
	DefChStructFrm->Origine=0;
	DefChStructFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereCatChStructFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int repMB;
	if(Categorie)
	DefChStructFrm->Close();

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
void TGereCatChStructFrm::IniCaption(void) {
	GereCatChStructFrm->Caption = LC_GereCatChStructFrm;

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
void TGereCatChStructFrm::TexteCaption(void) {
	LC_GereCatChStructFrm = T->TrouveCaption("GereCatChStruct",
			"LC_GereCatChStructFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereCatChStructFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=490;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

