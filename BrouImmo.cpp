//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Brouillon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//----------------------------------------------------------------------------
void TFBrouillon::Immo(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	CL_TotImmo *totImmo;
	AnsiString caption, as;
	resultat = agri->Resultat;

	Demarre();
	caption = TexteCaption(agri);
	Titre1(caption.c_str());
	Titre1("Immobilisations");

	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre1(as.c_str());
	AnPluUn(agri->DefSim->An_0);

	ImpImmobilisation(resultat, "Immobilisations");

	ImpPetit(resultat->ImmoPetit, "Petit matériel");

	ImpImmo(resultat->ImmoSom, "Autres Immobilisations");

	ImpImmoTotal(resultat, "RECAPITULATION");

	Blanc(5);
	Show();

}
//----------------------------------------------------------------------------
void TFBrouillon::ImpImmobilisation(CL_AgriRes *resultat, char *titre) {
	if (resultat->Immo->EstVide == true)
		return;
	Titre2(titre);
	ResultatBilan("Achat", resultat->Immo->Achat, N_X, clNavy);
	ResultatBilan("Vente", resultat->Immo->Vente, N_X, clNavy);
	ResultatBilan("Valeur Résiduelle", resultat->Immo->Resid, N_X + 1, clNavy);
	ResultatBilan("Amortissement", resultat->Immo->Amor, N_X, clNavy);
	ResultatBilan("Production d'immobilisation", resultat->ProdImmo, N_X + 1,
			clNavy);
//    ResultatBilan("Plus Value",        totImmo->PlusVal,N_X,clNavy);
//    ResultatBilan("Moins Value",       totImmo->MoinsVal,N_X,clNavy);
	Blanc(1);
}
//----------------------------------------------------------------------------
void TFBrouillon::ImpImmoTotal(CL_AgriRes *resultat, char *titre) {
	if (resultat->Immo->EstVide == true)
		return;
	Titre2(titre);
	ResultatBilan("Achat", resultat->ImmoTotal->Achat, N_X, clNavy);
	ResultatBilan("Vente", resultat->ImmoTotal->Vente, N_X, clNavy);
	ResultatBilan("Valeur Résiduelle", resultat->ImmoTotal->Resid, N_X + 1,
			clNavy);
	ResultatBilan("Amortissement", resultat->ImmoTotal->Amor, N_X, clNavy);
	ResultatBilan("Production d'immobilisation", resultat->ProdImmo, N_X + 1,
			clNavy);
//    ResultatBilan("Plus Value",        totImmo->PlusVal,N_X,clNavy);
//    ResultatBilan("Moins Value",       totImmo->MoinsVal,N_X,clNavy);
	Blanc(1);
}
//----------------------------------------------------------------------------
void TFBrouillon::ImpImmo(CL_TotImmo *totImmo, char *titre) {
	if (totImmo->EstVide == true)
		return;
	Titre2(titre);
	ResultatBilan("Achat", totImmo->Achat, N_X, clNavy);
	ResultatBilan("Vente", totImmo->Vente, N_X, clNavy);
	ResultatBilan("Valeur Résiduelle", totImmo->Resid, N_X + 1, clNavy);
	ResultatBilan("Amortissement", totImmo->Amor, N_X, clNavy);
	Blanc(1);
}
//----------------------------------------------------------------------------
void TFBrouillon::ImpPetit(CL_TotImmo *totImmo, char *titre) {
	if (totImmo->EstVide == true)
		return;
	Titre2(titre);
	ResultatBilan("Achat", totImmo->Achat, N_X, clNavy);
	ResultatBilan("Amortissement", totImmo->Amor, N_X, clNavy);
	Blanc(1);
}

