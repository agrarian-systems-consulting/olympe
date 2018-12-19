//---------------------------------------------------------------------------

#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"
#include "Main.h"

#include "CreerLstNom.h"
extern CL_Trad *T;

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void DefinirNoms(void) {
	LstNom = new TStringList;
	//LstNom defini dans LesVecteurs
	TStringList *LstNomFinSom = new TStringList;
	TStringList *LstNomInvSom = new TStringList;
	TStringList *LstNomGrilleEmpLT = new TStringList;

	LstNom->AddObject("LstNomFinSom", LstNomFinSom);
	LstNom->AddObject("LstNomInvSom", LstNomInvSom);
	LstNom->AddObject("LstNomGrilleEmpLT", LstNomGrilleEmpLT);

	TexteChaine();

	NomFinSom(LstNomFinSom);
	NomInvSom(LstNomInvSom);
	NomGrilleEmpLT(LstNomGrilleEmpLT);
}
//---------------------------------------------------------------------------
void NomFinSom(TStringList *lst) {

	lst->Add(L_DetteLT); //"Dette LT");
	lst->Add(L_RembCapLT); //"Remb Capital LT");
	lst->Add(L_IntLT); //"Interet LT");
	lst->Add(L_NouvLT); //"Nouveaux LT");

	lst->Add(L_DetteCT); //"Dette CT");
	lst->Add(L_RembCapCT); //"Remb Capital CT");
	lst->Add(L_IntCT); //"Interet CT");
	lst->Add(L_NouvCT); //"Nouveaux CT");
}
//---------------------------------------------------------------------------
void NomInvSom(TStringList *lst) {
	lst->Add(L_V_Resid); //"V. Résiduelle");
	lst->Add(L_Amor); //"Amortissement");
	lst->Add(L_Achat); //"Achat");
	lst->Add(L_Revente); //"Revente");
	lst->Add(L_PlusVal); //"Plus Value");
	lst->Add(L_MoinsVal); //"Moins Value");
	lst->Add(L_ProdImmo); //"Production d'Immo");
}
//---------------------------------------------------------------------------
void NomGrilleEmpLT(TStringList *lst) {
	lst->Add(L_EMP); //"EMPRUNTS");
	lst->Add(L_Montant); //"Montant");
	lst->Add(L_Dur1); //"Durée 1");
	lst->Add(L_Taux1); //"Taux  1");
	lst->Add(L_Dur2); //"Durée 2");
	lst->Add(L_Taux2); //"Taux  2");
	lst->Add(L_Type); //"Type");
	lst->Add(L_Real); //"Réalisation");
	lst->Add(L_Remb); //"Remboursement");
	lst->Add(L_EouP); //"E/P");
}
//---------------------------------------------------------------------------
void TexteChaine(void) {
	L_DetteLT = T->TrouveTexte("MainForm", "L_DetteLT");
	L_RembCapLT = T->TrouveTexte("MainForm", "L_RembCapLT");
	L_IntLT = T->TrouveTexte("MainForm", "L_IntLT");
	L_NouvLT = T->TrouveTexte("MainForm", "L_NouvLT");

	L_DetteCT = T->TrouveTexte("MainForm", "L_DetteCT");
	L_RembCapCT = T->TrouveTexte("MainForm", "L_RembCapCT");
	L_IntCT = T->TrouveTexte("MainForm", "L_IntCT");
	L_NouvCT = T->TrouveTexte("MainForm", "L_NouvCT");
	L_V_Resid = T->TrouveTexte("MainForm", "L_V_Resid");
	L_Amor = T->TrouveTexte("MainForm", "L_Amor");
	L_Achat = T->TrouveTexte("MainForm", "L_Achat");
	L_Revente = T->TrouveTexte("MainForm", "L_Revente");
	L_PlusVal = T->TrouveTexte("MainForm", "L_PlusVal");
	L_MoinsVal = T->TrouveTexte("MainForm", "L_MoinsVal");
	L_ProdImmo = T->TrouveTexte("MainForm", "L_ProdImmo");

	L_EMP = T->TrouveTexte("MainForm", "L_EMP");
	L_Montant = T->TrouveTexte("MainForm", "L_Montant");
	L_Dur1 = T->TrouveTexte("MainForm", "L_Dur1");
	L_Taux1 = T->TrouveTexte("MainForm", "L_Taux1");
	L_Dur2 = T->TrouveTexte("MainForm", "L_Dur2");
	L_Taux2 = T->TrouveTexte("MainForm", "L_Taux2");
	L_Type = T->TrouveTexte("MainForm", "L_Type");
	L_Real = T->TrouveTexte("MainForm", "L_Real");
	L_Remb = T->TrouveTexte("MainForm", "L_Remb");
	L_EouP = T->TrouveTexte("MainForm", "L_EouP");

}

