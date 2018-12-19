//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"

#include "QRGrille00.h"
#include "QRCatNom.h"
#include "QRCatNomTva.h"
#include "QRCatNomUnite.h"
#include "QRCatTout.h"
#include "DefCalendrier.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCalendrier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCalendrierFrm *GereCalendrierFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereCalendrierFrm::TGereCalendrierFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		PClasst->Visible=false; //panel pour classer
		LabelModifie->Visible=false;
		OrdreModif=false;
		No=0;//eviter reclassement si pas de sélection
		//Personnaliser();
		Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
		Categorie=NULL;
		Origine=1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::LBClick(TObject *Sender)
{
	int n;
	bool rep;
	if(DefCalendrierFrm->Visible==true)
	{
		DefCalendrierFrm->Close();
	}
	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	{
		rep=NouvelleCategorie();
		if(rep==false) return;
	}

	Calendrier=(CL_Calendrier*)LB->Items->Objects[n];

	DefCalendrierFrm->Calendrier=Calendrier;
	DefCalendrierFrm->Caption=Caption;
	DefCalendrierFrm->Origine=0;
	DefCalendrierFrm->Show();
}
//---------------------------------------------------------------------------
//Modifier le nom de la categorie
void __fastcall TGereCalendrierFrm::BtModifierNomClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;

	if(Calendrier==NULL)
	{
		MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}
	newNom=Calendrier->Nom;
	rep=ES->EntrerNom("Modification du Nom",newNom,newNom);
	if(rep==true)
	{
		//on a redonné le même nom
		if(newNom==Calendrier->Nom) return;
		//on a change le nom vérifier qu'il n'est pas vide et qu'il n'existe pas
		VerifNomCat(newNom,MODIFIER);
	}
}
//---------------------------------------------------------------------------
//NouvelleCategorie
//void __fastcall TGereCalFrm::NouvelleCategorie(void)
//---------------------------------------------------------------------------
// copie du Calendrier
//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::BtBnCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString titre;
	AnsiString newNom;

	if(Calendrier==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	// definir nom de la copie
	newNom=Calendrier->Nom;
	titre="Copie de  "+Calendrier->Nom;
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;

	//nom existe et pas de doublon + insertion dans V_Categorie
	// Categorie c(est ce qu'on vient de créer
	VerifNomCat(newNom,COPIER);

	DefCalendrierFrm->Calendrier=Calendrier;
//    DefCalendrierFrm->AffCalendrier();
	DefCalendrierFrm->Show();
}
//---------------------------------------------------------------------------
//VerifNomCat
// nom nouveau calendrier
//---------------------------------------------------------------------------
bool __fastcall TGereCalendrierFrm::VerifNomCat(AnsiString newNom,int action)
{
	int n;
	CL_Calendrier *ancCal=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return false;}

	// il n'y a pas de categorie avec ce nom
	ancCal=V_Calendrier->trouve(newNom);
	if(ancCal)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Calendrier->Nom= newNom;
		LabelModifie->Visible=true;
		n=LB->ItemIndex;
		Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
		LB->ItemIndex=n;
		return true;
	}

	//CREER
	else if(action==COPIER)
	{
		Calendrier=new CL_Calendrier(Calendrier);
		Calendrier->Nom=newNom;
		V_Calendrier->ins(Calendrier);

		LabelModifie->Visible=true;

		n=LB->ItemIndex;
		Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
		LB->ItemIndex=n;
	}

	else if(action==CREER)
	{
		Calendrier=new CL_Calendrier();
		Calendrier->Nom=newNom;
		V_Calendrier->ins(Calendrier);

		LabelModifie->Visible=true;

		n=LB->ItemIndex;
		Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
		LB->ItemIndex=n;
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::BtBnCreerClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;

	rep=ES->EntrerNom(L_NouvCal,"",newNom); //"Nouveau Calendrier"
	if(rep==false) return;
	newNom=newNom.Trim();
	if(newNom.IsEmpty()==true) return;

	VerifNomCat(newNom, CREER);
}
//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::BtSupprimerClick(TObject *Sender)
{
	int rep;
	char buf[100];
	if(Calendrier==NULL)return;

	if(Calendrier->Supprimable==false)
	{
		MessageBox(Handle,"Cette catégorie a des éléments!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	sprintf(buf," Je supprime %s \n Vous êtes sur ?",Calendrier->Nom.c_str() );
	rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Calendrier->sup(Calendrier);
		Calendrier=NULL;
		ES->ecrireFichier();
		LabelModifie->Visible=false;
		///actualiser LB TV
		Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
		//CategorieFrm->LabCatVar->Caption="";
		LB->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::StockerOrdreCalendrier(void)
{
	int i;
	for(i=0;i<LB->Items->Count;i++)
	V_Calendrier->Vecteur[i]=(CL_Calendrier*)LB->Items->Objects[i];
	OrdreModif=false;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Sortie avec Verif
//---------------------------------------------------------------------------
void __fastcall TGereCalendrierFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if(DefCalendrierFrm->Visible==true)DefCalendrierFrm->Close();
	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(rep==ID_YES)
		{
			if(OrdreModif==true) StockerOrdreCalendrier();

			ES->ecrireFichier();
			LabelModifie->Visible=false;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TGereCalendrierFrm::TexteChaine(void) {
	L_NouvCal = T->TrouveTexte("GereCalendrierFrm", "L_NouvCal");
}

//--------------------------------------------
void TGereCalendrierFrm::IniCaption(void) {
	GereCalendrierFrm->Caption = LC_GereCalendrierFrm;

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
void TGereCalendrierFrm::TexteCaption(void) {
	LC_GereCalendrierFrm = T->TrouveCaption("GereCalendrier",
			"LC_GereCalendrierFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereCalendrierFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

