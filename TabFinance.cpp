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
void CL_Excel::Finance(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	int colDeb = 4;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	EcrireNomVC(agri);

	resultat = agri->Resultat;

	Titre(0, "Finances");
	AnPluUn(colDeb - 1, agri->DefSim->An_0); //?

	ImpFinance(resultat->EmpLTE, "Emprunts Long terme");

	ImpFinance(resultat->EmpCTE, "Emprunts Court terme");

	for (int i = 0; i < N_X; i++) {
		if (resultat->FraisOccc[i] > 0) {
			Titre(0, "Occc");
			ResultatBilan(colDeb - 2, "Frais d'Occc", resultat->FraisOccc, N_X);
			Blanc(1);
			break;
		}
	}

	ImpFinance(resultat->EmpSomLT, "Autres Emprunts Long Terme ");
	ImpFinance(resultat->EmpSomCT, "Autres Emprunts Court Terme ");

//	FBrouillon->Titre1("RECAPITULATION");
	ImpFinance(resultat->EmpTotal, "RECAPITULATION");

	ImpPlacement(resultat->PlactE, "Placements");

	FermerFichier();

}
//----------------------------------------------------------------------------
void CL_Excel::ImpFinance(CL_TotEmp *totEmp, char *titre) {
	int colDeb = 2;
	float versement[N_X];

	if (totEmp->EstVide == true)
		return;
	for (int i = 0; i < N_X; i++)
		versement[i] = totEmp->Remb[i] + totEmp->Interet[i];
	Titre(0, titre);
	ResultatBilan(colDeb, "Capital", totEmp->Capital, N_X + 1);
	ResultatBilan(colDeb, "Versement", versement, N_X);
	ResultatBilan(colDeb, ". Remboursement", totEmp->Remb, N_X);
	ResultatBilan(colDeb, ". Intérêt", totEmp->Interet, N_X);
	ResultatBilan(colDeb, "Dette", totEmp->Dette, N_X + 1);
	Blanc(1);
}
//----------------------------------------------------------------------------
void CL_Excel::ImpPlacement(CL_TotEmp *totEmp, char *titre) {
	int colDeb = 2;
	if (totEmp->EstVide == true)
		return;
	Titre(0, titre);
	ResultatBilan(colDeb, "Placement", totEmp->Capital, N_X);
	ResultatBilan(colDeb, "Rentrée", totEmp->Remb, N_X);
	ResultatBilan(colDeb, "Intérêt", totEmp->Interet, N_X);
	ResultatBilan(colDeb, "Créance", totEmp->Dette, N_X + 1);
	Blanc(1);
}
//--------------------------------------------------------------------------

