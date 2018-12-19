//---------------------------------------------------------------------------
#include <vcl.h>
#include <systdate.h>
#include <vcl\dstring.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Brouillon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//----------------------------------------------------------------------------
void TFBrouillon::Finance(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	CL_TotEmp *totEmp;
	AnsiString caption;
	AnsiString as;
	Demarre();

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	resultat = agri->Resultat;
	Titre1("Finances");

	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre1(as.c_str());
	AnPluUn(agri->DefSim->An_0);

	ImpFinance(resultat->EmpLTE, "Emprunts Long terme");

	ImpFinance(resultat->EmpCTE, "Emprunts Court terme");
	for (int i = 0; i < N_X; i++) {
		if (resultat->FraisOccc[i] > 0) {
			Titre2("Occc");
			ResultatBilan("Frais d'Occc", resultat->FraisOccc, N_X, clNavy);
			Blanc(1);
			break;
		}
	}
//  les emprunts "sommaires" sont integrés dans resultat->EmpLTE et CTE
//    ImpFinance(resultat->EmpSomLT,"Autres Emprunts Long Terme ");
//    ImpFinance(resultat->EmpSomCT,"Autres Emprunts Court Terme ");

//	FBrouillon->Titre1("RECAPITULATION");
	ImpFinance(resultat->EmpTotal, "RECAPITULATION");
	ImpSubvention(agri);

	ImpPlacement(resultat->PlactE, "Placements");

	FBrouillon->Blanc(5);
	FBrouillon->Show();

}
//----------------------------------------------------------------------------
void TFBrouillon::ImpFinance(CL_TotEmp *totEmp, char *titre) {
	float versement[N_X];

	if (totEmp->EstVide == true)
		return;
	for (int i = 0; i < N_X; i++)
		versement[i] = totEmp->Remb[i] + totEmp->Interet[i];
	Titre2(titre);
	ResultatBilan("Capital", totEmp->Capital, N_X, clNavy);
	ResultatBilan("Versement", versement, N_X, clNavy);
	ResultatBilan(".  Remboursement", totEmp->Remb, N_X, clNavy);
	ResultatBilan(".  Intérêt", totEmp->Interet, N_X, clNavy);
	ResultatBilan("Dette", totEmp->Dette, N_X + 1, clNavy);
	Blanc(1);
}
//----------------------------------------------------------------------------
void TFBrouillon::ImpPlacement(CL_TotEmp *totEmp, char *titre) {
	if (totEmp->EstVide == true)
		return;
	Titre2(titre);
	ResultatBilan("Placement", totEmp->Capital, N_X, clNavy);
	ResultatBilan("Rentrée", totEmp->Remb, N_X, clNavy);
	ResultatBilan("Intérêt", totEmp->Interet, N_X, clNavy);
	ResultatBilan("Créance", totEmp->Dette, N_X + 1, clNavy);
	Blanc(1);
}
//--------------------------------------------------------------------------
void TFBrouillon::ImpSubvention(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	CL_TotSub *totSub;
	resultat = agri->Resultat;
	totSub = resultat->TotSub;
	Titre2("Subvention");
	ResultatBilan("Subvention", totSub->Valeur, N_X, clNavy);
	ResultatBilan("Amortissement", totSub->Amor, N_X, clNavy);
	ResultatBilan("à amortir", totSub->Resid, N_X + 1, clNavy);
	Blanc(1);
}

