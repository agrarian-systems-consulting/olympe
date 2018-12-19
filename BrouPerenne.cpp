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
void TFBrouillon::ComptaPerenne(CL_Agriculteur *agri) {
	CL_AgriRes *resultat;
	CL_TotEmp *totEmp;
	AnsiString caption;
	AnsiString as;
	LarTrait = 166;
	Demarre();

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	resultat = agri->Resultat;
	Titre1("Pérennes Elements comptables");

	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre1(as.c_str());
	AnPluUn(agri->DefSim->An_0);
	Trait();
	ResultatBilan("Valeur Plantations", resultat->ValPlant, N_X + 1, clNavy);
	ResultatBilan("Amortissement Plantation", resultat->AmorPlant, N_X, clNavy);
	ResultatBilan("Prod Immo", resultat->ProdImmo, N_X, clNavy);
	ResultatBilan("Prod Immo famille", resultat->ProdImmoFam, N_X, clNavy);
	ResultatBilan("Perte Exceptionnelle", resultat->PertePlant, N_X, clNavy);
	Trait();
//    ResultatBilan("Avance aux cultures",      resultat->Avance,     N_X+1,clNavy);
//    ResultatBilan("Stocks ",                  resultat->Stock,      N_X+1,clNavy);

	FBrouillon->Blanc(5);
	FBrouillon->Show();

}
