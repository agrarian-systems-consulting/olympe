//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"

#include "DefProduit.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCatProduit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCatProduitFrm *GereCatProduitFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereCatProduitFrm::TGereCatProduitFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatProduitFrm::Personnaliser(void)
{
	switch(Nature)
	{
		case PRODUIT:
		//Caption=                   "Produits";//130206
		V_Item= V_Produit;
		V_Categorie= V_CatProduit;
		DefProduitFrm->HelpContext= 380;
		break;
		case CHARGE:
		//Caption=                       "Charges Opérationnelles";
		V_Item= V_Charge;
		V_Categorie= V_CatCharge;
		DefProduitFrm->HelpContext= 390;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatProduitFrm::LBClick(TObject *Sender)
{
	int n;
	int rep;
	AnsiString as;
	as=GereCatItemFrm->L_Impo;
	if(DefProduitFrm->Visible==true)
	{
		if(Categorie) DefProduitFrm->Close();
	}
	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	{
		rep=NouvelleCategorie();
		if(rep==false) return;
	}
	Categorie=(CL_Categorie*)LB->Items->Objects[n];
	DefProduitFrm->Categorie=Categorie;
	DefProduitFrm->Caption=Caption;
	DefProduitFrm->Origine=0;
	DefProduitFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TGereCatProduitFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int repMB;
	if(DefProduitFrm->Visible==true)
	{
		if(Categorie) DefProduitFrm->Close();
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
void TGereCatProduitFrm::IniCaption(void) {
	GereCatProduitFrm->Caption = LC_GereCatProduitFrm;

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
void TGereCatProduitFrm::TexteCaption(void) {
	LC_GereCatProduitFrm = T->TrouveCaption("GereCatProduit",
			"LC_GereCatProduitFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereCatProduitFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TGereCatProduitFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=295;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

