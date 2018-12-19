//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "QuelExcelCSV.h"

#include "Tableur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//----------------------------------------------------------------------------
void CL_Excel::Etat(CL_Agriculteur *agri, CL_EtatSortie *etat) {
	CL_Elt *elt;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	EcrireNomVC(agri);

	Titre(0, etat->Nom.c_str());
	An(colDeb, agri->DefSim->An_0);
	Trait();

	for (int n = 0; n < etat->V_Elt->Nbelt; n++) {
		elt = etat->V_Elt->Vecteur[n];

		if (elt->NoFamille == FORME) {
			if (elt->NoItem == TRAIT)
				Trait();
			else if (elt->NoItem == BLANC)
				Blanc();
			else if (elt->NoItem == TITRE)
				Titre(0, elt->Nom);
		} else {
			Forme0Frm->CompleteElt(elt, agri);
			Resultat(colDeb - 1, elt->Nom, elt->Valeur);
		}
	}
	FermerFichier();
}

