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
#include "TVChoixElt.h"

#include "Main.h"
#include "Atelier.h"

#include "GereComp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereEtat"
#pragma resource "*.dfm"
TGereCompFrm *GereCompFrm;
//---------------------------------------------------------------------------
__fastcall TGereCompFrm::TGereCompFrm(TComponent* Owner) :
		TGereEtatFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereCompFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
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
		DefEtatSortieFrm->Caption="Comparaison";
		DefEtatSortieFrm->LabelModifie->Visible=false;
		TVChoixEltFrm->EstInitialise=false;
		TVChoixEltFrm->Origine=COMPARAISON;

		Forme0Frm->CreeTVToutElt(TVChoixEltFrm->TV,NULL,true);

		CompleteComparaison();
	}
}
//---------------------------------------------------------------------------
// a 1 poil pres copie de void AgriSaisieCalcul CompleteEtatSortie(void)
//-------------------------------------------------------------------------
void __fastcall TGereCompFrm::CompleteComparaison(void)
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
void __fastcall TGereCompFrm::CreeTV(void)
{
	Forme0Frm->CreeTVEtat(TV,V_CatSerieComp,V_SerieComp);
}
