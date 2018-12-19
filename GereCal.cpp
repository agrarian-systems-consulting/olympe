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
//#include "CalendrierAncien.h"
#include "DefCalendrier.h"

#include "GereCal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCalFrm *GereCalFrm;
extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TGereCalFrm::TGereCalFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCalFrm::FormActivate(TObject *Sender)
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
void __fastcall TGereCalFrm::LBClick(TObject *Sender)
{
	int n;
	if(DefCalendrierFrm->Visible==true)
	{
		DefCalendrierFrm->Close();
	}
	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	NouvelleCategorie();
	Calendrier=(CL_Calendrier*)LB->Items->Objects[n];

	DefCalendrierFrm->Calendrier=Calendrier;
	DefCalendrierFrm->Caption=Caption;
	DefCalendrierFrm->Origine=0;
	DefCalendrierFrm->Show();
}
//---------------------------------------------------------------------------
//Modifier le nom de la categorie
void __fastcall TGereCalFrm::BtModifierNomClick(TObject *Sender)
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
void __fastcall TGereCalFrm::BtBnCopierClick(TObject *Sender)
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
void __fastcall TGereCalFrm::VerifNomCat(AnsiString newNom,int action)
{
	int n;
	CL_Calendrier *ancCal=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return;}

	// il n'y a pas de categorie avec ce nom
	ancCal=V_Calendrier->trouve(newNom);
	if(ancCal)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Calendrier->Nom= newNom;
		LabelModifie->Visible=true;
		n=LB->ItemIndex;
		Forme0Frm->CreeLBCalendrier(LB,V_Calendrier);
		LB->ItemIndex=n;
		return;
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
}

//---------------------------------------------------------------------------
void __fastcall TGereCalFrm::BtBnCreerClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;

	rep=ES->EntrerNom("Nouveau Calendrier","",newNom);
	if(rep==false) return;
	newNom=newNom.Trim();
	if(newNom.IsEmpty()==true) return;

	VerifNomCat(newNom, CREER);
}
//---------------------------------------------------------------------------
void __fastcall TGereCalFrm::BtSupprimerClick(TObject *Sender)
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
void __fastcall TGereCalFrm::StockerOrdreCalendrier(void)
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
void __fastcall TGereCalFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if(DefCalendrierFrm->Visible==true)DefCalendrierFrm->Close();
	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle," Modifié\nVoulez vous conserver","MODIFICATION",
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

