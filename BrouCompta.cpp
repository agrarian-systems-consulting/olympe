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
//---------------------------------------------------------------------------
void TFBrouillon::Ceg(CL_Agriculteur *agri) {
	int n;
	AnsiString as, caption;
	CL_AgriRes *resultat;
	CL_Comptabilite *compta;

	LarTrait = 152;
	resultat = agri->Resultat;
	compta = resultat->Compta;
//c'est fait dans AgriSaisieCalcul
//    compta->FaireCompta(resultat);
	Demarre();

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	FBrouillon->Titre1("Compte de Résultat");

	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre1(as.c_str());
	An(agri->DefSim->An_0);
	/*
	 Trait(144);
	 Trait(146);
	 Trait(148);
	 Trait(150);
	 Trait(152);
	 Trait(154);
	 Trait(156);
	 */
	Trait();
//   a faire                //pour Excel cf BtBnExcelClick
	Resultat("Produits", compta->totProduit);
	Blanc(1);
	Resultat(".  Recettes", resultat->Produit, clNavy);
	Resultat(".  Recettes Diverses", resultat->RecDiv, clNavy);

	Resultat(".  Var. Stock", compta->deltaStock, clNavy);
	Resultat(".  Var. stock en terre", compta->deltaAvance, clNavy);
//    Resultat(".  Variation valeur plantation",   compta->deltaValPlant,clNavy);
	Resultat(".  Var. inventaire animal", compta->deltaVarInvAni, clNavy);

	Resultat(".  Produits financiers", resultat->PlactE->Interet, clNavy);
	Resultat(".  Production d'immo", resultat->ProdImmo, clNavy);
	Resultat(".  Cession d'actif", resultat->ImmoTotal->Vente, clNavy);

//    Resultat(".  Plus Value Cession",        resultat->ImmoTotal->PlusVal,clNavy);
//    Resultat(".  Moins Value Cession",       resultat->ImmoTotal->MoinsVal,clNavy);

	Resultat(".  Perte Exceptionnelle", resultat->PertePlant, clNavy);

	Resultat(".  Amortissemment Subvention", resultat->TotSub->Amor, clNavy);

	Blanc(2);
	// Charges
	Resultat("Charges", compta->totDepense);
	Blanc(1);
	Resultat(".  Dépenses Exploitation", resultat->Charge, clNavy);
	Resultat(".  Dépenses Diverses", resultat->DepDiv, clNavy);
	Resultat(".  Val comptable cession", resultat->ImmoTotal->ValCompta,
			clNavy);
	Blanc(1);

	Resultat("Charges de Structure", compta->totChStruct);
	Blanc(1);
	Resultat(".  Amortissement Immo", resultat->ImmoTotal->Amor, clNavy);
	Resultat(".  Amortissement Plantation", resultat->AmorPlant, clNavy);
	Resultat(".  Frais fin LT", resultat->EmpLTE->Interet, clNavy);
	Resultat(".  Frais fin CT", resultat->EmpCTE->Interet, clNavy);
	Resultat(".  Frais fin OCCC", resultat->FraisOccc, clNavy);
	Resultat(".  Autres Ch Struct", resultat->ChStruct, clNavy);
	Blanc(2);
	Resultat("Resultat", compta->resExercice, clRed);

	// fin
	FBrouillon->Blanc(5);
	FBrouillon->Show();

}
//---------------------------------------------------------------------------
void TFBrouillon::Bilan(CL_Agriculteur *agri) {
	int n;
	AnsiString as, caption;
	CL_AgriRes *resultat;
	CL_Comptabilite *compta;
	LarTrait = 166;
	resultat = agri->Resultat;

	compta = resultat->Compta;
//c'est fait dans AgriSaisieCalcul
//    compta->FaireCompta(resultat);

	Demarre();

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	FBrouillon->Titre1("Bilan");

	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre1(as.c_str());
	AnPluUn(agri->DefSim->An_0);

	Trait();
	Titre1("ACTIF");
	ResultatBilan("Immobilisations", compta->totImmo, N_X + 1, clBlack);
	FBrouillon->Blanc(1);
	ResultatBilan(".  Materiel Batiment", resultat->ImmoTotal->Resid, N_X + 1,
			clNavy);
	ResultatBilan(".  Animaux", resultat->InvAni, N_X + 1, clNavy);
	ResultatBilan(".  Plantations", resultat->ValPlant, N_X + 1, clNavy);

//    ResultatBilan(".  Stocks",                resultat->Stock,           N_X+1,clNavy);
	ResultatBilan(".  Stocks", resultat->Stock, N_X + 1, clNavy);
	ResultatBilan(".  Stocks en terre", resultat->Avance, N_X + 1, clNavy);
	//creance
	ResultatBilan("Placements", resultat->PlactE->Dette, N_X + 1);
	ResultatBilan("Creance Tva", compta->creanceTva, N_X + 1);
	ResultatBilan("Creances Diverses", resultat->Creance->CrDette, N_X + 1);
	ResultatBilan("Trésorerie", compta->tresorerie, N_X + 1);
	Blanc(1);
	ResultatBilan("Perte", compta->perte, N_X, clRed);
	ResultatBilan("Total Actif", compta->totActif, N_X + 1, clBlack);

	Trait();
	Titre1("PASSIF");
	ResultatBilan("Capital", compta->capital, N_X + 1, clBlack);
	ResultatBilan("Solde Privé", compta->soldePrive, N_X, clBlack);

	ResultatBilan("Subvention", resultat->TotSub->Resid, N_X + 1, clNavy);
	ResultatBilan("Dette LT", resultat->EmpLTE->Dette, N_X + 1, clNavy);
	ResultatBilan("Dette ct", resultat->EmpCTE->Dette, N_X + 1, clNavy);
	ResultatBilan("Dette Tva", compta->detteTva, N_X + 1, clNavy);
	ResultatBilan("Dettes Diverses", resultat->Dette->CrDette, N_X + 1);
	Blanc(1);
	ResultatBilan("Bénéfice", compta->benefice, N_X, clRed);
	ResultatBilan("Total Passif", compta->totPassif, N_X + 1, clBlack);
	// fin
	FBrouillon->Blanc(5);
	FBrouillon->Show();

}

//---------------------------------------------------------------------------
void TFBrouillon::Famille(CL_Agriculteur *agri) {
	int n;
	AnsiString as, caption;
	CL_AgriRes *resultat;
	CL_Comptabilite *compta;
	LarTrait = 152;
	resultat = agri->Resultat;
	compta = resultat->Compta;
//c'est fait dans AgriSaisieCalcul
//    compta->FaireCompta(resultat);

	Demarre();

	caption = TexteCaption(agri);
	Titre1(caption.c_str());

	FBrouillon->Titre1("Privé");
	as = "Valeurs en ";
	if (Global == false)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;

	Titre1(as.c_str());
	An(agri->DefSim->An_0);

	Trait();
	Resultat("+ Apports ", resultat->RecFam, clNavy);
	Resultat("- Prélevements", resultat->DepFam, clNavy);
	Resultat("+ Production d'immo", resultat->ProdImmoFam, clNavy);
	Resultat("+ Produits financiers", resultat->PlactP->Interet, clNavy);
	Resultat("- Remboursement LT", resultat->EmpLTP->Remb, clNavy);
	Resultat("- Remboursement CT", resultat->EmpCTP->Remb, clNavy);
	Resultat("- Frais fin LT", resultat->EmpLTP->Interet, clNavy);
	Resultat("- Frais fin CT", resultat->EmpCTP->Interet, clNavy);
	Resultat("- Placements", resultat->PlactP->Capital, clNavy);
	Resultat("Solde Privé", compta->soldePrive);

	// fin
	FBrouillon->Blanc(5);
	FBrouillon->Show();
}

