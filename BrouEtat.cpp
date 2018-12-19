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
void TFBrouillon::Etat(CL_Agriculteur *agri, CL_EtatSortie *etat) {
	CL_Elt *elt;
	AnsiString caption;

	Demarre();
	FBrouillon->BtBnExcel->Visible = true;
//    /*
	Trait(156);
	Trait(154);
	Trait(152);
	Trait(150);
//    */

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	FBrouillon->Titre1(etat->Nom.c_str());
	FBrouillon->An(agri->DefSim->An_0); //An_0
	FBrouillon->Trait(132);
	EtatSortie = etat; //pour Excel cf BtBnExcelClick
	for (int n = 0; n < etat->V_Elt->Nbelt; n++) {
		elt = etat->V_Elt->Vecteur[n];

		if (elt->NoFamille == FORME) {
			if (elt->NoItem == TRAIT)
				FBrouillon->Trait(132);
			else if (elt->NoItem == BLANC)
				FBrouillon->Blanc();
			else if (elt->NoItem == TITRE)
				FBrouillon->Titre2(elt->Nom, clNavy);
		} else {
			Forme0Frm->CompleteElt(elt, agri);
			FBrouillon->Resultat(elt->Nom, elt->Valeur, clNavy);
		}
	}
	FBrouillon->Blanc(5);
	FBrouillon->Show();
}

