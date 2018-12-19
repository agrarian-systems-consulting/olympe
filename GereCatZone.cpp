//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
//#include "ChoixCritere.h"
#include "AgriClasst.h"

#include "DefZone.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCatZone.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCatZoneFrm *GereCatZoneFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereCatZoneFrm::TGereCatZoneFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereCatZoneFrm::Personnaliser(void)
{
//	Caption="Typologie";
	V_Item= V_TypeZone;
	V_Categorie=V_CatTypeZone;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatZoneFrm::LBClick(TObject *Sender)
{
	int n;
	bool rep;
	if( PClasst->Visible==true) {No=LB->ItemIndex; return;}

	if(DefZoneFrm->Visible==true)
	{
		if(Categorie) DefZoneFrm->Close();
	}
	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	{
		rep=NouvelleCategorie();
		if(rep==false) return;
	}

	Categorie=(CL_Categorie*)LB->Items->Objects[n];
	DefZoneFrm->Categorie=Categorie;
	DefZoneFrm->Caption=Caption;
	DefZoneFrm->Origine=0;
	DefZoneFrm->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatZoneFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int repMB;
	if(DefZoneFrm->Visible==true)
	{
		if(Categorie) DefZoneFrm->Close();
	}
	if(LabelModifie->Visible==true)
	{
		repMB=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(repMB==ID_YES)
		{
			if(OrdreModif==true) StockerOrdre(V_Categorie);
			MajLBCatCritere(); //200705
			ES->ecrireFichier();
			LabelModifie->Visible=false;
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TGereCatZoneFrm::BtSupprimerClick(TObject *Sender)
{
	int rep;
	char buf[100];
	if(Categorie==NULL)return;

	if(Categorie->Supprimable==false)
	{
		//MessageBox(Handle,"Cette catégorie a des éléments!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		MessageBox(Handle,T->L_CatAElt.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);

		return;
	}

	//sprintf(buf," Je supprime %s \n Vous êtes sur ?",Categorie->Nom.c_str() );
	sprintf(buf,L_JSup.c_str(),Categorie->Nom.c_str() );

	//rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	rep=MessageBox(Handle,buf,T->L_SupT.c_str(),MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDNO) return;

	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Categorie->sup(Categorie);
		Categorie=NULL;

		ES->ecrireFichier();
		LabelModifie->Visible=false;
		///actualiser LB TV
		Forme0Frm->CreeLBCat(LB,V_Categorie);
		//CategorieFrm->LabCatVar->Caption="";
		LB->SetFocus();
	}

}
//---------------------------------------------------------------------------
// quand on fait un ensemble
// on peut utiliser tout ou partie des categories de critéres
//ils sont dans 2 ListBox
// je recree ces 2 LB en fonction de categorie->Flag
// true retenu false inutilisé
//---------------------------------------------------------------------------
void __fastcall TGereCatZoneFrm::MajLBCatCritere(void)
{
	int n;
	TCheckListBox *chLB;
	CL_Categorie *categorie;

	chLB=AgriClasstFrm->ChLBCatTypeZone;
	chLB->Clear();
	for(n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		categorie=V_CatTypeZone->Vecteur[n];
		chLB->Items->AddObject(categorie->Nom,(TObject*)categorie);
		chLB->Checked[n]=categorie->Flag;
	}

	/*
	 //criteres Retenus
	 lB=ChoixCritereFrm->LBCritere;
	 lB->Clear();
	 for(n=0;n<V_CatTypeZone->Nbelt;n++)
	 {
	 categorie=V_CatTypeZone->Vecteur[n];
	 if(categorie->Flag==true)
	 lB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	 }

	 //criteres Non Retenus
	 lB=ChoixCritereFrm->LBCritereNR;
	 lB->Clear();                                 //141101
	 for(n=0;n<V_CatTypeZone->Nbelt;n++)
	 {
	 categorie=V_CatTypeZone->Vecteur[n];
	 if(categorie->Flag==false)
	 lB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	 }
	 */
}
//--------------------------------------------
void TGereCatZoneFrm::TexteCaption(void) {
	GereCatZoneFrm->Caption = T->LC_DefZoneFrm;

	BtBnCreer->Caption = T->LC_BtBnCreer;
	BtBnCopier->Caption = T->LC_BtBnCopier;
	BtModifier->Caption = T->LC_BtModifier;
	BtClasser->Caption = T->LC_BtClasser;
	BtSupprimer->Caption = T->LC_BtBnSupBesTrav;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	//inutile
	//    IniCaption();

}
//--------------------------------------------
void TGereCatZoneFrm::IniCaption(void) {
	LC_DefZoneFrm = T->TrouveCaption("CL_Trad", "LC_DefZoneFrm");
}
//--------------------------------------------

bool __fastcall TGereCatZoneFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

