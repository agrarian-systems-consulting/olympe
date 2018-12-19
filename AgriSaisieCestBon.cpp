//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "Compilateur.h"
#include "Erreur.h"
#include "AgriSaisieEnum.h"
#include "FichierLire.h"
//#include "TVChoixElt.h"
//#include "TVChoixElt.h"
#include "MvtAnnee.h"

#include "ErreurImmoSommaire.h"
#include "ErreurFinSommaire.h"

#include "AgriSaisie.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
extern CL_ES *ES;

//---------------------------------------------------------------------------
//8
// Verifier et calculer avant de passer à la saisie suivante
// LaGrille->Tag correspond à la grille d'où on sort
//si on a modifié produit et charge(on sort de GAssol GPerenne GAni )
//        il faut comleter et calculer les formules
//on doit écraser Grille->Tag pour utiliser CompleteFormule
//Grille->Tag  sera mis à jour au retour dans la fonction qui a appelé CEstBon
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::CEstBon(void)
{
	bool rep;
	int laGrilleTag=LaGrille->Tag;
	//on n'est passé que dans AgriSaisie
//CL_Formule *formule;
//	formule=Agri->V_ChStruct->Vecteur[0];

	if(LaGrille==NULL) return true;
	if(LaGrille->Tag==GResul) return true;
	if(LaGrille->Tag==GClose) return true;

	if(LaGrille->Tag==GBestiaux) MvtAnneeFrm->Close();

	if(LaGrille->Tag==GNotes)
	{
		if(ValueAvant==AnsiString(L_Modifie="modifié"))
		{
			Stocker();
			Agri->Notes=Memo->Text;
			Memo->Height=HauteurMemo;
		}
		return true;
	}

	DerniereCell();

	if(LabelModifie->Visible==false) return true;
	rep=VerifGrille();

	if(rep==false)
	{
		if(LaGrille->Tag==GInvSom)
		{
			ErreurImmoSommaireFrm->LaGrille=LaGrille;
			ErreurImmoSommaireFrm->Show();
		}
		else if(LaGrille->Tag==GFinSom)
		{
			ErreurFinSommaireFrm->LaGrille=LaGrille;
			ErreurFinSommaireFrm->Show();
		}
		else
		{
			ErreurFrm->Show();
		}
		return false;
	}

	DesGrilles();

	if(OrdreModif) StockerOrdre();
	Calcul0(Agri);

	Stocker();

	LaGrille->Tag=laGrilleTag;

	return true;
}
/*
 L_Modifie=          "modifié";
 */
