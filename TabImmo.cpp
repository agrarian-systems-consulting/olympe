//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "QuelExcelCSV.h"

#include "Tableur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//----------------------------------------------------------------------------
void CL_Excel::Immo(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	resultat = agri->Resultat;

	EcrireNomVC(agri);

	Titre(0, "Immobilisations");
	AnPluUn(colDeb - 1, agri->DefSim->An_0); //?

	ImpImmo(resultat->Immo, "Immobilisations");

	ImpPetit(resultat->ImmoPetit, "Petit matériel");

	ImpImmo(resultat->ImmoSom, "Autres Immobilisations");

	ImpImmo(resultat->ImmoTotal, "RECAPITULATION");

	FermerFichier();

}
//----------------------------------------------------------------------------
void CL_Excel::ImpImmo(CL_TotImmo *totImmo, char *titre) {
	int colDeb = 2;
	if (totImmo->EstVide == true)
		return;
	Titre(0, titre);
	ResultatBilan(colDeb, "Achat", totImmo->Achat, N_X);
	ResultatBilan(colDeb, "Vente", totImmo->Vente, N_X);
	ResultatBilan(colDeb, "Valeur Résiduelle", totImmo->Resid, N_X + 1);
	ResultatBilan(colDeb, "Amortissement", totImmo->Amor, N_X);
	ResultatBilan(colDeb, "Production d'immobilisation", totImmo->ProdImmo,
			N_X + 1);
	ResultatBilan(colDeb, "Cession d'actif", totImmo->Vente, clNavy);
//    ResultatBilan(colDeb,"Plus Value",        totImmo->PlusVal,N_X);
//    ResultatBilan(colDeb,"Moins Value",       totImmo->MoinsVal,N_X);
}
//----------------------------------------------------------------------------
void CL_Excel::ImpPetit(CL_TotImmo *totImmo, char *titre) {
	int colDeb = 2;
	if (totImmo->EstVide == true)
		return;
	Titre(0, titre);
	ResultatBilan(colDeb, "Achat", totImmo->Achat, N_X);
	ResultatBilan(colDeb, "Amortissement", totImmo->Amor, N_X);
	Blanc(1);
}

