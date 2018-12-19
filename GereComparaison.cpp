//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
#include "Brouillon.h"
#include "Tableur.h"
#include "AgriSaisie.h"
#include "DefEtatSortie.h"
#include "TVDico.h"
#include "CL_Trad.h"

#include "Main.h"
#include "Atelier.h"
#include "Aide.h"

#include "GereComparaison.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereEtat"
#pragma resource "*.dfm"
TGereComparaisonFrm *GereComparaisonFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TGereComparaisonFrm::TGereComparaisonFrm(TComponent* Owner) :
		TGereEtatFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereComparaisonFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		GBAtelier->Caption="Comparaisons";

		PClasst->Visible=false;
		LabelModifie->Visible=false;
		OrdreModif=false; //151203
		Categorie=NULL;
		//comparaison travaille sur des états
		Etat=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
		Origine=1;
//                            Forme0Frm->CreeTVEtat(TV,V_CatSerieComp,V_SerieComp);

		V_Categorie=V_CatSerieComp;
		V_Etat =V_SerieComp;
		CreeTV();
		CalculDonnees();

		GereEtatFrm->Caption="Comparaisons";
		DefEtatSortieFrm->Caption="Comparaisons";
		DefEtatSortieFrm->LabelModifie->Visible=false;
		DefEtatSortieFrm->HelpContext=1830;
		TVDicoFrm->Origine=COMPARAISON;

		CompleteComparaison();
	}
}
//---------------------------------------------------------------------------
// a 1 poil pres copie de void AgriSaisieCalcul CompleteEtatSortie(void)
//-------------------------------------------------------------------------
void __fastcall TGereComparaisonFrm::CompleteComparaison(void)
{
	CL_EtatSortie *etat;
	CL_Elt *elt,*elt0;
	int i,j,k;
	for(i=0;i<V_SerieComp->Nbelt;i++)
	{
		etat=V_SerieComp->Vecteur[i];
		for(j=0;j<etat->V_Elt->Nbelt;j++)
		{
			elt=etat->V_Elt->Vecteur[j];
			if(elt->NoFamille==FORME) continue;

			for(k=0;k<V_Elt->Nbelt;k++)
			{
				elt0=V_Elt->Vecteur[k];
				if( elt0->NoFamille ==elt->NoFamille
						&& elt0->NoCategorie ==elt->NoCategorie
						&& elt0->NoItem ==elt->NoItem )
				{
					elt->Nom =elt0->Nom;
					elt->NomCat =elt0->NomCat;
					elt->NomFamille=elt0->NomFamille;
					break;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
// creeTV
//---------------------------------------------------------------------------
//cf GereEtat

//--------------------------------------------
void TGereComparaisonFrm::IniCaption(void) {
	GereComparaisonFrm->Caption = T->LC_GereComparaisonFrm;
	GBAtelier->Caption = T->LC_GereComparaisonFrm;

	BtBnAlpha->Caption = T->LC_BtBnAlpha;
	GBAtelier->Caption = T->LC_AtelierFrm;
	GBCategorie->Caption = T->LC_RGCat;
	GereAtelierFrm->Caption = LC_GereAtelierFrm;
	BtClasser->Caption = T->LC_BtClasser;
	BtCatCopier->Caption = T->LC_BtBnCopier;
	BtAtelierCopier->Caption = T->LC_BtBnCopier;
	BtCatCreer->Caption = T->LC_BtBnCreer;
	BtAtelierCreer->Caption = T->LC_BtBnCreer;
	BtCatModifNom->Caption = T->LC_BtModifier;
	BtAtelierModifNom->Caption = T->LC_BtModifier;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtCatNettoyer->Caption = T->LC_BtBnEffacer;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	BtCatSupprimer->Caption = T->LC_BtBnSupBesTrav;
	BtAtelierSupprimer->Caption = T->LC_BtBnSupBesTrav;

}
//--------------------------------------------
void TGereComparaisonFrm::TexteCaption(void) {
	LC_GereComparaisonFrm = T->TrouveCaption("CL_Trad",
			"LC_GereComparaisonFrm");

	IniCaption();
}
//--------------------------------------------

bool __fastcall TGereComparaisonFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1830;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TGereComparaisonFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1830;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
}
//---------------------------------------------------------------------------

