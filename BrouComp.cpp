//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Brouillon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//----------------------------------------------------------------------------
void TFBrouillon::Comparaison(CL_EtatSortie *serieComp, TList *lstElt,
		int an_0) {
	CL_Elt *elt;
	AnsiString caption;
	CL_Agriculteur *agri;
	TypeImp("Courier", size2, clNavy, 'M');

	FBrouillon->Demarre();
	/*
	 Trait(156);
	 Trait(154);
	 Trait(152);
	 Trait(150);
	 */
	LarTrait = 136;
	FBrouillon->Titre1(serieComp->Nom.c_str());
	FBrouillon->An(an_0); //An_0
	FBrouillon->Trait(132);
	//pour Excel cf BtBnExcelClick
	EtatSortie = serieComp;
	LstElt = lstElt;
	An_0 = an_0;

	for (int n = 0; n < lstElt->Count; n++) {
		elt = (CL_Elt*) lstElt->Items[n];

		if (elt->NoFamille == FORME) {
//          if     (elt->NoItem==TRAIT)  FBrouillon->Trait(132);
			if (elt->NoItem == TRAIT)
				FBrouillon->Trait();
			else if (elt->NoItem == BLANC)
				FBrouillon->Blanc();
			else if (elt->NoItem == TITRE)
				FBrouillon->Titre2(elt->Nom, clNavy);
		} else {
			FBrouillon->Resultat(elt->Nom, elt->Valeur, clNavy);
		}
	}
	FBrouillon->Blanc(5);
	FBrouillon->Show();
}

