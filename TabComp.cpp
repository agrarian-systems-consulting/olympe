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
void CL_Excel::Comparaison(CL_EtatSortie *serieComp, TList *lstElt, int an_0) {
	CL_Elt *elt;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	EnTeteDate();
//    TexteCaption(agri);

	Titre(0, serieComp->Nom.c_str());
	An(colDeb, an_0);
	Trait();

	for (int n = 0; n < lstElt->Count; n++) {
		elt = (CL_Elt*) lstElt->Items[n];

		if (elt->NoFamille == FORME) {
			if (elt->NoItem == TRAIT)
				Trait();
			else if (elt->NoItem == BLANC)
				Blanc();
			else if (elt->NoItem == TITRE)
				Titre(1, elt->Nom);
		} else {
			Resultat(colDeb - 1, elt->Nom, elt->Valeur);
		}
	}
	FermerFichier();
	ShowMessage("Excel Ok");
}

