//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Brouillon.h"
#include "SysUnite.h"
//#include "Agriculteur.h"

#include "Impression.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//----------------------------------------------------------------------------
void ImprimerLesDonnees(void) {
	FBrouillon->Demarre();

	FBrouillon->Titre1("LES SYSTEMES D'UNITES");
//	SysUniteFrm->ImpSysUnite();
	/*
	 FBrouillon->Titre1("LES CATEGORIES");
	 CategoriesFrm->ImpCategorie("PRODUITS",  V_CatProduit);
	 CategoriesFrm->ImpCategorie("CHARGES",   V_CatCharge);
	 CategoriesFrm->ImpCategorie("IRRIGATION",V_CatEau);

	 FBrouillon->Titre1("LES PRODUITS");
	 ProduitFrm->ImpProduit("LES PRODUITS",V_Produit);

	 FBrouillon->Titre1("LES CHARGES OPERATIONNELLES");
	 ChargeFrm->ImpProduit("LES CHARGES",V_Charge);

	 FBrouillon->Titre1("IRRIGATION");
	 EauFrm->ImpProduit("IRRIGATION",V_Irrigation);

	 FBrouillon->Titre1("AUTRES RECETTES ET DEPENSES");
	 //    RecDepAutreFrm->ImpRecDepAutre("RECETTES",V_RecDiv);
	 //    RecDepAutreFrm->ImpRecDepAutre("DEPENSES",V_DepDiv);

	 FBrouillon->Titre1("LES CHARGES DE STRUCTURE");
	 //    StructureFrm->ImpRecDepAutre("CHARGES",V_ChStruct);


	 FBrouillon->Titre1("FAMILLE");
	 //    FamilleFrm->ImpRecDepAutre("RECETTES",  V_RecFam);
	 //    FamilleFrm->ImpRecDepAutre("DEPENSES",  V_DepFam);

	 FBrouillon->Titre1("TYPOLOGIE");
	 //    TypeFrm->ImpRecDepAutre("TYPES",  V_Type);
	 //    TypeFrm->ImpRecDepAutre("ZONES",  V_Zone);
	 */
	FBrouillon->Show();
}
////////////////////////////////////////////////////////////////////////////
/*
 //----------------------------------------------------------------------------
 void CL_Imp::ResultatAgriQuantite(CL_Agriculteur *agri)
 {
 FBrouillon->Demarre();
 Quantite(agri);
 FBrouillon->Blanc(5);
 FBrouillon->Show();
 }
 //-------------------------------------------------------------------------
 void CL_Imp::ResultatAgriValeur(CL_Agriculteur *agri)
 {
 FBrouillon->Demarre();
 Valeur(agri);
 FBrouillon->Blanc(5);
 FBrouillon->Show();
 }
 //----------------------------------------------------------------------------
 void CL_Imp::ResultatAgriExternalite(CL_Agriculteur *agri)
 {
 FBrouillon->Demarre();
 Externalite(agri);
 FBrouillon->Blanc(5);
 FBrouillon->Show();
 }
 */
/*
 //----------------------------------------------------------------------------
 void CL_Imp::Finance(CL_Agriculteur *agri)
 {
 CL_AgriRes *resultat;
 CL_TotEmp *totEmp;
 resultat=agri->Resultat;

 FBrouillon->Demarre();
 FBrouillon->Titre1("Finances");
 FBrouillon->AnPluUn(agri->DefSim->An_0);

 ImpFinance(resultat->EmpLTE,"Emprunts Long terme");

 ImpFinance(resultat->EmpCTE,"Emprunts Court terme");
 for(int i=0;i<N_X;i++)
 {
 if(resultat->FraisOccc[i]>0)
 {
 FBrouillon->Titre2("Occc");
 FBrouillon->ResultatBilan("Frais d'Occc",resultat->FraisOccc, N_X,clNavy);
 FBrouillon->Blanc(1);
 break;
 }
 }
 ImpFinance(resultat->EmpSomLT,"Autres Emprunts Long Terme ");
 ImpFinance(resultat->EmpSomCT,"Autres Emprunts Court Terme ");

 //	FBrouillon->Titre1("RECAPITULATION");
 ImpFinance(resultat->EmpTotal,"RECAPITULATION");

 ImpPlacement(resultat->PlactE,"Placements");

 FBrouillon->Blanc(5);
 FBrouillon->Show();

 }
 //----------------------------------------------------------------------------
 void CL_Imp::ImpFinance(CL_TotEmp *totEmp,char *titre)
 {
 if(totEmp->EstVide==true) return;
 FBrouillon->Titre2(titre);
 FBrouillon->ResultatBilan("Capital",      totEmp->Capital, N_X,clNavy);
 FBrouillon->ResultatBilan("Remboursement",totEmp->Remb,    N_X,clNavy);
 FBrouillon->ResultatBilan("Intérêt",      totEmp->Interet, N_X,clNavy);
 FBrouillon->ResultatBilan("Dette",        totEmp->Dette,   N_X+1,clNavy);
 FBrouillon->Blanc(1);
 }
 //----------------------------------------------------------------------------
 void CL_Imp::ImpPlacement(CL_TotEmp *totEmp,char *titre)
 {
 if(totEmp->EstVide==true) return;
 FBrouillon->Titre2(titre);
 FBrouillon->ResultatBilan("Placement",      totEmp->Capital, N_X,clNavy);
 FBrouillon->ResultatBilan("Rentrée",totEmp->Remb,    N_X,clNavy);
 FBrouillon->ResultatBilan("Intérêt",      totEmp->Interet, N_X,clNavy);
 FBrouillon->ResultatBilan("Créance",        totEmp->Dette,   N_X+1,clNavy);
 FBrouillon->Blanc(1);
 }
 */
/*
 //----------------------------------------------------------------------------
 void CL_Imp::Immo(CL_Agriculteur *agri)
 {
 CL_AgriRes *resultat;
 CL_TotImmo *totImmo;
 resultat=agri->Resultat;

 FBrouillon->Demarre();
 FBrouillon->Titre1("Immobilisations");
 FBrouillon->AnPluUn(agri->DefSim->An_0);

 ImpImmo(resultat->Immo,"Immobilisations");

 ImpPetit(resultat->ImmoPetit,"Petit matériel");

 ImpImmo(resultat->ImmoSom,"Autres Immobilisations");

 ImpImmo(resultat->ImmoTotal,"RECAPITULATION");

 FBrouillon->Blanc(5);
 FBrouillon->Show();

 }
 //----------------------------------------------------------------------------
 void CL_Imp::ImpImmo(CL_TotImmo *totImmo,char *titre)
 {
 if(totImmo->EstVide==true) return;
 FBrouillon->Titre2(titre);
 FBrouillon->ResultatBilan("Achat",             totImmo->Achat, N_X,clNavy);
 FBrouillon->ResultatBilan("Vente",             totImmo->Vente, N_X,clNavy);
 FBrouillon->ResultatBilan("Valeur Résiduelle", totImmo->Resid, N_X+1,clNavy);
 FBrouillon->ResultatBilan("Amortissement",     totImmo->Amor,  N_X,clNavy);
 FBrouillon->ResultatBilan("Production d'immobilisation",totImmo->ProdImmo,   N_X+1,clNavy);
 FBrouillon->ResultatBilan("Plus Value",        totImmo->PlusVal,N_X,clNavy);
 FBrouillon->ResultatBilan("Moins Value",       totImmo->MoinsVal,N_X,clNavy);
 FBrouillon->Blanc(1);
 }
 //----------------------------------------------------------------------------
 void CL_Imp::ImpPetit(CL_TotImmo *totImmo,char *titre)
 {
 if(totImmo->EstVide==true) return;
 FBrouillon->Titre2(titre);
 FBrouillon->ResultatBilan("Achat",             totImmo->Achat, N_X,clNavy);
 //    FBrouillon->ResultatBilan("Vente",             totImmo->Vente, N_X,clNavy);
 //    FBrouillon->ResultatBilan("Valeur Résiduelle", totImmo->Resid, N_X+1,clNavy);
 FBrouillon->ResultatBilan("Amortissement",     totImmo->Amor,  N_X,clNavy);
 //    FBrouillon->ResultatBilan("Production d'immobilisation",totImmo->ProdImmo,   N_X+1,clNavy);
 //    FBrouillon->ResultatBilan("Plus Value",        totImmo->PlusVal,N_X,clNavy);
 //    FBrouillon->ResultatBilan("Moins Value",       totImmo->MoinsVal,N_X,clNavy);
 FBrouillon->Blanc(1);
 }
 /*
 /*
 //----------------------------------------------------------------------------
 void CL_Imp::ImpPlacement(CL_TotEmp *totEmp,char *titre)
 {
 if(totEmp->EstVide==true) return;
 FBrouillon->Titre2(titre);
 FBrouillon->ResultatBilan("Placement",      totEmp->Capital, N_X,clNavy);
 FBrouillon->ResultatBilan("Rentrée",totEmp->Remb,    N_X,clNavy);
 FBrouillon->ResultatBilan("Intérêt",      totEmp->Interet, N_X,clNavy);
 FBrouillon->ResultatBilan("Créance",        totEmp->Dette,   N_X+1,clNavy);
 FBrouillon->Blanc(1);
 }
 */
/*
 //------------------------------------------------------------------------------
 // structure divers..
 //------------------------------------------------------------------------------
 void  CL_Imp::Val2(char *titre,
 CL_Vecteur<CL_Valeur> *vecteur,
 float *total)
 {
 int i;
 CL_Valeur *valeur;
 CL_Item   *item;
 if(vecteur->Nbelt>0)
 {
 //        FBrouillon->ImpTrait(132);
 FBrouillon->Titre2(titre);
 for(i=0;i<vecteur->Nbelt;i++)
 {
 valeur=vecteur->Vecteur[i];
 item=valeur->Item;
 FBrouillon->Resultat(item->Nom,valeur->Valeur,clNavy);
 }
 if(vecteur->Nbelt>1)
 FBrouillon->Resultat(AnsiString(" total"),total,clNavy);
 }
 }
 */
