//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "QuelExcelCSV.h"

#include "Tableur.h"
#include "AgriSaisie.h"
#include "TabCompta.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void CL_Excel::Ceg(CL_Agriculteur *agri) {
	int colDeb = 1;
	AnsiString as;
	CL_AgriRes *resultat;
//  !!CL_Comptabilite *compta;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	resultat = agri->Resultat;
//c'est fait dans AgriSaisieCalcul
	for (int an = 0; an < N_X; an++)
		AgriSaisieFrm->FaireCompta(resultat, an);

	EcrireNomVC(agri);

	Titre(0, "Compte de Résultat");

	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre(0, as.c_str());
	An(colDeb, agri->DefSim->An_0);
	Trait();
//   a faire                //pour Excel cf BtBnExcelClick
	Resultat(0, "Produits", resultat->totProduit);
	Blanc();
	Resultat(0, ".  Recettes", resultat->Produit);
	Resultat(0, ".  Recettes Diverses", resultat->RecDiv);

	Resultat(0, ".  Var. Stock", resultat->deltaStock);
	Resultat(0, ".  Var. Stock en terre", resultat->deltaAvance);
//    Resultat(0,".  Variation valeur plantation",   resultat->deltaValPlant);
	Resultat(0, ".  Var.inv animal Repro", resultat->deltaVarInvAniRepro); //260903
	Resultat(0, ".                 Autre", resultat->deltaVarInvAniAutre); //260903

	Resultat(0, ".  Produits financiers", resultat->PlactE->Interet);
	Resultat(0, ".  Production d'immo", resultat->ProdImmo);
//    Resultat(0,".  Plus Value Cession",        resultat->ImmoTotal->PlusVal);
//    Resultat(0,".  Moins Value Cession",       resultat->ImmoTotal->MoinsVal);
	Resultat(0, ".  Cession d'actif", resultat->ImmoTotal->Vente);

	Resultat(0, ".  Perte Exceptionnelle", resultat->PertePlant);

	Resultat(0, ".  Amortissemment Subvention", resultat->TotSub->Amor);

	Blanc();
	// Charges
	Resultat(0, "Charges", resultat->totDepense);
	Blanc(0);
	Resultat(0, ".  Dépenses Exploitation", resultat->Charge);
	Resultat(0, ".  Dépenses Diverses", resultat->DepDiv);
	Resultat(0, ".  Val comptable cession", resultat->ImmoTotal->ValCompta);

	Blanc();

	Resultat(0, "Charges de Structure", resultat->totChStruct);
	Blanc();
	Resultat(0, ".  Amortissement Immo", resultat->ImmoTotal->Amor);
	Resultat(0, ".  Amortissement Plantation", resultat->AmorPlant);
	Resultat(0, ".  Frais fin LT", resultat->EmpLTE->Interet);
	Resultat(0, ".  Frais fin CT", resultat->EmpCTE->Interet);
	Resultat(0, ".  Frais fin OCCC", resultat->FraisOccc);
	Resultat(0, ".  Autres Ch Struct", resultat->ChStruct);
	Blanc(0);
	Resultat(0, "Resultat", resultat->resExercice);

	// fin
	FermerFichier();
}
//---------------------------------------------------------------------------
void CL_Excel::Bilan(CL_Agriculteur *agri) {
	AnsiString as, caption;
	CL_AgriRes *resultat;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	resultat = agri->Resultat;
	for (int an = 0; an < N_X; an++)
		AgriSaisieFrm->FaireCompta(resultat, an);

	EcrireNomVC(agri);

	Titre(0, "Bilan");

	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre(0, as.c_str());
	AnPluUn(1, agri->DefSim->An_0);

	Trait();
	Titre(0, "ACTIF");
	RBilan(0, "Immobilisations", resultat->totImmo, N_X + 1);
	Blanc();
	RBilan(0, ".  Materiel Batiment", resultat->ImmoTotal->Resid, N_X + 1);
	RBilan(0, ".  Animaux Repro", resultat->InvAniRepro, N_X + 1); //260903
	RBilan(0, ".  Plantations", resultat->ValPlant, N_X + 1);

	RBilan(0, ".  Stocks", resultat->Stock, N_X + 1);
	RBilan(0, ".  Stocks en terre", resultat->Avance, N_X + 1);
	RBilan(0, ".  Animaux ", resultat->InvAniAutre, N_X + 1); //260903

	RBilan(0, "Placements", resultat->PlactE->Capital, N_X + 1);
	RBilan(0, "Creance Tva", resultat->creanceTva, N_X + 1);
	RBilan(0, "Creances Diverses", resultat->Creance->CrDette, N_X + 1);
	RBilan(0, "Trésorerie", resultat->tresorerie, N_X + 1);
	// a faire
	RBilan(0, "Perte", resultat->perte, N_X);
	RBilan(0, "Total Actif", resultat->totActif, N_X + 1);

	Trait();
	Titre(0, "PASSIF");
	RBilan(0, "Capital", resultat->capital, N_X + 1);
	RBilan(0, "Solde Privé", resultat->soldePrive, N_X);

	RBilan(0, "Subvention", resultat->TotSub->Resid, N_X + 1);
	RBilan(0, "Dette LT", resultat->EmpLTE->Dette, N_X + 1);
	RBilan(0, "Dette ct", resultat->EmpCTE->Dette, N_X + 1);
	RBilan(0, "Dette Tva", resultat->detteTva, N_X + 1);
	RBilan(0, "Dettes Diverses", resultat->Dette->CrDette, N_X + 1);

	RBilan(0, "Bénéfice", resultat->benefice, N_X);
	RBilan(0, "Total Passif", resultat->totPassif, N_X + 1);
	// fin
	FermerFichier();
}

//---------------------------------------------------------------------------
void CL_Excel::Famille(CL_Agriculteur *agri) {
	AnsiString as, caption;
	CL_AgriRes *resultat;
//CL_Comptabilite *compta;
	int colDeb = 1;

	QuelExcelCSVFrm->ShowModal();
	if (QuelExcelCSVFrm->Renonce == true)
		return;

	resultat = agri->Resultat;
//c'est fait dans AgriSaisieCalcul
	for (int an = 0; an < N_X; an++)
		AgriSaisieFrm->FaireCompta(resultat, an);

	EcrireNomVC(agri);

	Titre(0, "Privé");
	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre(0, as.c_str());
	An(colDeb, agri->DefSim->An_0);

	Trait();
	Resultat(0, "  + Apports ", resultat->RecFam);
	Resultat(0, "  - Prélevements", resultat->DepFam);
	Resultat(0, "  + Production d'immo", resultat->ProdImmoFam);
	Resultat(0, "  + Produits financiers", resultat->PlactP->Interet);
	Resultat(0, "  - Remboursement LT", resultat->EmpLTP->Remb);
	Resultat(0, "  - Remboursement CT", resultat->EmpCTP->Remb);
	Resultat(0, "  - Frais fin LT", resultat->EmpLTP->Interet);
	Resultat(0, "  - Frais fin CT", resultat->EmpCTP->Interet);
	Resultat(0, "  - Placements", resultat->PlactP->Capital);
	Resultat(0, "Solde Privé", resultat->soldePrive);

	// fin
	FermerFichier();
}

