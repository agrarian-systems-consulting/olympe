//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"

#include "DefBestiaux.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCatBestiaux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereCatItem"
#pragma resource "*.dfm"
TGereCatBestiauxFrm *GereCatBestiauxFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereCatBestiauxFrm::TGereCatBestiauxFrm(TComponent* Owner) :
		TGereCatItemFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereCatBestiauxFrm::Personnaliser(void)
{
//    Caption=" Mouvement des Animaux";
//    V_Item=                        V_Bestiaux;
	V_Categorie= V_CatBestiaux;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatBestiauxFrm::LBClick(TObject *Sender)
{
	int n;
	bool rep;
	if(DefBestiauxFrm->Visible==true)
	{
		if(Categorie) DefBestiauxFrm->Close();
	}
	n=LB->ItemIndex;
	No=n; // pour Reclasser
	if(LB->Items->Strings[n]=="[...]")
	{
		rep=NouvelleCategorie();
		if(rep==false) return;
	}

	Categorie=(CL_Categorie*)LB->Items->Objects[n];
	DefBestiauxFrm->Categorie=Categorie;
	DefBestiauxFrm->Caption=Caption;
	DefBestiauxFrm->Origine=0;
	DefBestiauxFrm->Show();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatBestiauxFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int repMB;
	if(DefBestiauxFrm->Visible==true)
	{
		if(Categorie) DefBestiauxFrm->Close();
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
//---------------------------------------------------------------------------
void __fastcall TGereCatBestiauxFrm::BtSupprimerClick(TObject *Sender)
{
	int rep;
	char buf[100];
	if(Categorie==NULL)return;

	if(Categorie->Supprimable==false)
	{
		MessageBox(Handle,"Ce Troupeau est utilisé!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	sprintf(buf," Je supprime %s \n Vous êtes sur ?",Categorie->Nom.c_str() );
	rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Categorie->sup(Categorie);
		MajV_Bestiaux(Categorie);
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
//---------------------------------------------------------------------------
// eliminer dans V_Bestiaux tous les animaux de la categorie supprimée
//---------------------------------------------------------------------------
void __fastcall TGereCatBestiauxFrm::MajV_Bestiaux(CL_Categorie *cat)
{
	int i;
	CL_Bestiaux *animal;
	for(i=0;i<V_Bestiaux->Nbelt;i++)
	{
		animal=V_Bestiaux->Vecteur[i];
		if(animal->Categorie==cat)
		V_Bestiaux->sup(animal);
	}

}
//-------------------------------------------------------------------------------
void __fastcall TGereCatBestiauxFrm::BtBnCopierClick(TObject *Sender)
{
	bool rep;
	int n;
	AnsiString titre;
	AnsiString newNom;
	CL_Categorie *cat;
	CL_Bestiaux *bestiaux,*nouvBestiaux;

	if(Categorie==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	cat=Categorie;

	// definir nom de la copie
	newNom=Categorie->Nom;
	titre="Copie de  "+Categorie->Nom;
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;

	//nom existe et pas de doublon + insertion dans V_Categorie
	// Categorie c(est ce qu'on vient de créer
	VerifNomCat(newNom,CREER);

	//trouver les bestiaux de la categorie et les inserer dans V_bestiaux
	for(n=0;n<V_Bestiaux->Nbelt;n++)
	{
		bestiaux=V_Bestiaux->Vecteur[n];
		if(bestiaux->Categorie!= cat) continue;

		nouvBestiaux=new CL_Bestiaux (bestiaux);
		nouvBestiaux->Categorie=Categorie;
		nouvBestiaux->NoCategorie=Categorie->No;
		V_Bestiaux->ins(nouvBestiaux);
	}
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TGereCatBestiauxFrm::IniCaption(void) {
	GereCatBestiauxFrm->Caption = LC_GereCatBestiauxFrm;

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
void TGereCatBestiauxFrm::TexteCaption(void) {
	LC_GereCatBestiauxFrm = T->TrouveCaption("GereCatBestiaux",
			"LC_GereCatBestiauxFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereCatBestiauxFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

