//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Brouillon.h"
#include "Impression.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
 //-------------------------------------------------------------------------
 //
 //                 IMPRESSION
 //                     Quantité
 //
 //-------------------------------------------------------------------------
 void  CL_Imp::Quantite(CL_Agriculteur *agri)
 {
 CL_AgriRes *resultat;
 resultat=agri->Resultat;
 //    FBrouillon->Nom("");   //!!

 FBrouillon->Titre1("Quantites Physiques");
 FBrouillon->An(agri->DefSim->An_0);
 if(resultat->V_Produit->Nbelt>0)
 CategorieQ("Produits",V_CatProduit,resultat->V_Produit);

 if(resultat->V_Charge->Nbelt>0)
 CategorieQ("Charges",V_CatCharge ,resultat->V_Charge);

 }
 //-------------------------------------------------------------------------
 void  CL_Imp::CategorieQ(
 char *titre,
 CL_Vecteur<CL_Categorie>      *vCategorie,
 CL_Vecteur<CL_QuanVal>        *vQuanVal)
 {
 int i,j,l;
 CL_QuanVal   *quanVal;
 CL_Item      *item;
 CL_Categorie *categorie;
 AnsiString    unite;
 FBrouillon->Trait(132);
 FBrouillon->Titre2(titre);
 for(i=0;i<vCategorie->Nbelt;i++)
 {
 categorie=vCategorie->Vecteur[i];
 if(categorie->Flag=='N') continue;

 //quanValTot=vCatTot->trouve(categorie->No);
 l=0;
 FBrouillon->Titre3(categorie->Nom.c_str(),clNavy);

 for(j=0;j<vQuanVal->Nbelt;j++)
 {
 quanVal=vQuanVal->Vecteur[j];
 item=quanVal->Item;
 if(item->Categorie!=categorie ) continue;

 if(Global==false) unite=item->SysUnite->UTrans;
 else              unite=item->SysUnite->UGlobal;

 l++;
 FBrouillon->Resultat(item->Nom,unite,quanVal->Qte,clNavy);
 }
 }
 }
 //-------------------------------------------------------------------------
 //
 //                 IMPRESSION
 //                     Valeur
 //
 //-------------------------------------------------------------------------
 void  CL_Imp::Valeur(CL_Agriculteur *agri)
 {
 CL_AgriRes *resultat;
 AnsiString as;
 resultat=agri->Resultat;
 as="Valeurs en ";
 if(Global==false) as+=SysMonnaie->UTrans;
 else              as+=SysMonnaie->UGlobal;
 FBrouillon->Titre1(as.c_str());
 FBrouillon->An(agri->DefSim->An_0);

 CategorieV("Produits",      V_CatProduit,agri->V_Produits,
 resultat->Produit,resultat->V_CatProduitTot);
 CategorieV("Charges",       V_CatCharge ,agri->V_Charges,
 resultat->Charge,resultat->V_CatChargeTot);

 FBrouillon->Total("MARGE",resultat->Marge);
 FBrouillon->Blanc();

 CategorieV("Charges de Structure",     V_CatChStruct,agri->V_ChStruct,
 resultat->ChStruct,resultat->V_CatChStructTot);
 CategorieV("Recettes Diverses",        V_CatRecDiv,agri->V_RecDiv,
 resultat->RecDiv,resultat->V_CatRecDivTot);
 CategorieV("Dépenses Diverses",        V_CatDepDiv,agri->V_DepDiv,
 resultat->DepDiv,resultat->V_CatDepDivTot);
 CategorieV("Recettes Familiales",      V_CatRecFam,agri->V_RecFam,
 resultat->RecFam,resultat->V_CatRecFamTot);
 CategorieV("Dépenses Familiales",      V_CatDepFam,agri->V_DepFam,
 resultat->DepFam,resultat->V_CatDepFamTot);
 FBrouillon->Titre2("Immobilisation");
 FBrouillon->Resultat("Achat", resultat->ImmoTotal->Achat,clNavy);
 FBrouillon->Resultat("Vente", resultat->ImmoTotal->Vente,clNavy);

 FBrouillon->Titre2("Emprunts");
 FBrouillon->Resultat("Emprunt",      resultat->EmpTotal->Capital,clNavy);
 FBrouillon->Resultat("Remboursement",resultat->EmpTotal->Remb,clNavy);
 FBrouillon->Resultat("Interet",      resultat->EmpTotal->Interet,clNavy);
 FBrouillon->Blanc();

 FBrouillon->Total("SOLDE",          resultat->Solde);
 FBrouillon->Trait(132);

 }
 //-------------------------------------------------------------------------
 void  CL_Imp::CategorieV(
 char *titre,
 CL_Vecteur<CL_Categorie>      *vCategorie,
 CL_Vecteur<CL_Formule>        *vFormule,
 float *total,
 CL_Vecteur<CL_QuanVal>        *vCatTot)
 {
 int i,j,l;
 CL_QuanVal   *quanVal;
 CL_Item      *item;
 CL_Categorie *categorie;
 CL_QuanVal   *quanValTot;
 CL_Formule   *formule;
 AnsiString    unite;

 if(vFormule->Nbelt==0) return;

 FBrouillon->Trait(132);
 FBrouillon->Titre2(titre);

 for(i=0;i<vCategorie->Nbelt;i++)
 {
 categorie=vCategorie->Vecteur[i];
 if(categorie->Flag=='N') continue;

 quanValTot=vCatTot->trouve(categorie->No);
 l=0;
 FBrouillon->Titre3(categorie->Nom.c_str(),clNavy);

 for(j=0;j<vFormule->Nbelt;j++)
 {
 formule=vFormule->Vecteur[j];
 item=formule->Item;
 if(item->Categorie!=categorie ) continue;

 l++;
 FBrouillon->Resultat(item->Nom,formule->Valeur,clNavy);
 }
 if(l >1)
 {
 FBrouillon->Resultat(AnsiString("total"),quanValTot->Qte);
 }
 }
 FBrouillon->Total("TOTAL",total);

 }
 //-------------------------------------------------------------------------
 //
 //                 IMPRESSION
 //                     Externalité
 //
 //-------------------------------------------------------------------------
 void  CL_Imp::Externalite(CL_Agriculteur *agri)
 {
 int i;
 CL_AgriRes   *resultat;
 CL_QuanVal   *quanVal;
 CL_Item      *item;
 CL_Vecteur<CL_QuanVal> *vQuanVal;

 resultat=agri->Resultat;

 FBrouillon->Titre1("Externalités");
 FBrouillon->An(agri->DefSim->An_0);
 if(resultat->V_ExtNeg->Nbelt>0)
 {
 vQuanVal=resultat->V_ExtNeg;
 FBrouillon->Trait(132);
 FBrouillon->Titre2("Négatives");
 for(i=0;i<vQuanVal->Nbelt;i++)
 {
 quanVal=vQuanVal->Vecteur[i];
 item=quanVal->Item;
 FBrouillon->Resultat(item->Nom,item->SysUnite->UTrans,quanVal->Qte,clNavy);
 }
 }

 if(resultat->V_ExtPos->Nbelt>0)
 {
 vQuanVal=resultat->V_ExtPos;
 FBrouillon->Trait(132);
 FBrouillon->Titre2("Positives");
 for(i=0;i<vQuanVal->Nbelt;i++)
 {
 quanVal=vQuanVal->Vecteur[i];
 item=quanVal->Item;
 FBrouillon->Resultat(item->Nom,item->SysUnite->UTrans,quanVal->Qte,clNavy);
 }
 }
 }
 */
