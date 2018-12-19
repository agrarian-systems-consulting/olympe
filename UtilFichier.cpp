//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdarg.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "Brouillon.h"
#include "ChoixCritere.h"

//extern
#include "LesVecteurs.hse"
#include "Olympe.hse"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//----------------------------------------------------------------------------
void CL_ES::Purge(void) {
	V_SystemeUnite->purge();
	V_Tva->purge();

	V_CatProduit->purge();
	V_CatCharge->purge();
//	V_CatExternalite

	V_CatCulture->purge();

	V_CatAnimaux->purge();

	V_CatVivrier->purge();

//	V_CatDepEnt->purge(); initialisé standard TMainForm

//	V_CatRecEnt->purge();      new CL_Vecteur<CL_Categorie>();

//	V_CatRecFam->purge();      new CL_Vecteur<CL_Categorie>();
//	V_CatDepFam->purge();      new CL_Vecteur<CL_Categorie>();

	V_CatTypeZone->purge();

	V_CatIndic->purge();
	V_CatEtatSortie->purge();

	V_Produit->purge();
	V_Charge->purge();

	V_Externalite->purge();

	V_Culture->purge();
	V_Animaux->purge();
	V_Vivrier->purge();

	V_Espece->purge();
	V_Perenne->purge();

	V_RecDiv->purge();
	V_DepDiv->purge();

	V_RecFam->purge();
	V_DepFam->purge();

	V_TypeZone->purge();

	V_CatVar->purge();
	V_Variable->purge();

	V_Agriculteur->purge(); //penser a purger agrires 

	V_Ensemble->purge();

	V_EtatSortie->purge();
	V_Indicateur->purge();

	//V_Poste->purge();
	V_Elt->purge();

	V_CatDico->purge();
	ChoixCritereFrm->LBCritere->Clear();
	AgriEnCours = NULL;
	EnsembleEnCours = NULL;
}
//----------------------------------------------------------------------------
void CL_ES::IniNouveau(void) {
	IniSysUnit("f", "f", "Kf", 1, 1000);
	IniSysUnit("q", "q", "T", 1, 10);
	IniSysUnit("T", "T", "T", 1, 1);
	SysMonnaie = V_SystemeUnite->Vecteur[0];

	IniTva("Sans", 0);
	TvaDefaut = V_Tva->Vecteur[0];
	TvaImmo = V_Tva->Vecteur[0];

//	SysMonnaie->Monnaie='*';
	IniCategorie(V_CatProduit, "Céréales");
	IniCategorie(V_CatProduit, "Oléagineux");
	IniCategorie(V_CatCharge, "Engrais");
	IniCategorie(V_CatCharge, "Semences");
	ecrireFichier();
}
//----------------------------------------------------------------------------
void CL_ES::IniSysUnit(char *uUt, char *uTrans, char *uGlobal, float ratio,
		float ratioG) {
	CL_SystemeUnite *sysUnite;

	sysUnite = new CL_SystemeUnite;

	sysUnite->UUt = uUt;
	sysUnite->UTrans = uTrans;
	sysUnite->UGlobal = uGlobal;
	sysUnite->Ratio = ratio;
	sysUnite->RatioG = ratioG;

	V_SystemeUnite->ins(sysUnite);

}
//----------------------------------------------------------------------------
void CL_ES::IniTva(char *nom, float taux) {
	CL_Tva *tva;

	tva = new CL_Tva;

	tva->Nom = nom;
	tva->Taux = taux;
	V_Tva->ins(tva);

}
//----------------------------------------------------------------------------
void CL_ES::IniCategorie(CL_Vecteur<CL_Categorie> *vecteur, char *nom) {
	CL_Categorie *categorie;
	categorie = new CL_Categorie;

	categorie->Nom = nom;

	vecteur->ins(categorie);
}
//---------------------------------------------------------------------------
void CL_ES::IniItem(CL_Vecteur<CL_Item>*vecteur, char*nom) {
	CL_Item *item;
	item = new CL_Item;

	item->Nom = nom;

	vecteur->ins(item);
}
//----------------------------------------------------------------------------
void CL_ES::IniType(CL_Vecteur<CL_Item> *vecteur, char*nom) {
	CL_Item *item;
	item = new CL_Item;

	item->Nom = nom;

	vecteur->ins(item);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void CL_ES::Supprimable(void) {
	int i;
// tout est supprimable

	V_SystemeUnite->SupMazTrue();
	V_Tva->SupMazTrue();

	V_CatProduit->SupMazTrue();
	V_CatCharge->SupMazTrue();

	V_CatExternalite->SupMazTrue();

	V_CatChStruct->SupMazTrue();

	V_CatRecDiv->SupMazTrue();
	V_CatDepDiv->SupMazTrue();

	V_CatRecFam->SupMazTrue();
	V_CatDepFam->SupMazTrue();

	V_CatTypeZone->SupMazTrue();

	V_Produit->SupMazTrue();
	V_Charge->SupMazTrue();

	V_Externalite->SupMazTrue();

	V_Culture->SupMazTrue();
	V_Animaux->SupMazTrue();
	V_Vivrier->SupMazTrue();

	V_Espece->SupMazTrue();
	V_Perenne->SupMazTrue();

	V_ChStruct->SupMazTrue();

	V_RecDiv->SupMazTrue();
	V_DepDiv->SupMazTrue();

	V_RecFam->SupMazTrue();
	V_DepFam->SupMazTrue();

	V_TypeZone->SupMazTrue();

	V_CatVar->SupMazTrue();
	V_Variable->SupMazTrue();

	V_Agriculteur->SupMazTrue();

	V_EtatSortie->SupMazTrue();
	V_Indicateur->SupMazTrue();

	//reperer les NON supprimables
	for (i = 0; i < V_Produit->Nbelt; i++) {
		V_Produit->Vecteur[i]->Categorie->Supprimable = false;
		V_Produit->Vecteur[i]->SysUnite->Supprimable = false;
		V_Produit->Vecteur[i]->Tva->Supprimable = false;
	}
	for (i = 0; i < V_Charge->Nbelt; i++) {
		V_Charge->Vecteur[i]->Categorie->Supprimable = false;
		V_Charge->Vecteur[i]->SysUnite->Supprimable = false;
		V_Charge->Vecteur[i]->Tva->Supprimable = false;
	}
	//met à false les item de V_Produit V_Charge V_ChargeVolume V_Externalite
	for (i = 0; i < V_Culture->Nbelt; i++)
		V_Culture->Vecteur[i]->SupMaFalse();
	for (i = 0; i < V_Animaux->Nbelt; i++)
		V_Animaux->Vecteur[i]->SupMaFalse();
	for (i = 0; i < V_Perenne->Nbelt; i++)
		V_Perenne->Vecteur[i]->SupMaFalse();
	for (i = 0; i < V_Vivrier->Nbelt; i++)
		V_Vivrier->Vecteur[i]->SupMaFalse(); //260101

	for (i = 0; i < V_Perenne->Nbelt; i++)
		V_Perenne->Vecteur[i]->Espece->Supprimable = false;

	for (i = 0; i < V_Agriculteur->Nbelt; i++)
		V_Agriculteur->Vecteur[i]->SupMaFalse();
	CL_Ensemble *ensemble;
	CL_AgriEff *agriEff;

	for (i = 0; i < V_Ensemble->Nbelt; i++) {
		ensemble = V_Ensemble->Vecteur[i];
		for (int j = 0; j < ensemble->V_AgriEff->Nbelt; j++) {
			agriEff = ensemble->V_AgriEff->Vecteur[j];
			agriEff->Agri->Supprimable = false;
		}
	}

	IndicateurSupMaFalse();

}
//---------------------------------------------------------------------------------
void CL_ES::IndicateurSupMaFalse(void) {
	int i, j, k;
	CL_Indicateur *indicateur;
	CL_Arbre *arbre;
	ST_Branche branche;
	CL_Elt *elt;
	for (i = 0; i < V_Indicateur->Nbelt; i++) {
		indicateur = V_Indicateur->Vecteur[i];
		arbre = indicateur->Prog->Arbre;
		if (arbre == NULL)
			continue;

		for (j = 0; j < arbre->BrancheX; j++) {
			branche = arbre->LesBranches[j];
			if (branche.code != IDENT)
				continue;
			for (k = 0; k < V_Elt->Nbelt; k++) {
				elt = V_Elt->Vecteur[k];
				if (elt->NoFamille == branche.arg[0]
						&& elt->NoCategorie == branche.arg[1]
						&& elt->NoItem == branche.arg[2]) {
					if (elt->Categorie)
						elt->Categorie->Supprimable = false;
					if (elt->Item)
						elt->Item->Supprimable = false;
					if (elt->Indic)
						elt->Indic->Supprimable = false;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------
void __fastcall CL_ES::NumeroteVarianteAgri(void)
{
	int i;
	CL_Agriculteur *agri;
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		agri->EstVariante=false;
	}
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->EstVariante==true) continue;

//		ancetre=agri;
		agri->Ancetre->Agri=agri;
		agri->Ancetre->No =agri->No;
		LesFilsDAgri( agri,agri->Ancetre,0);
	}

}

//---------------------------------------------------------------------------
void __fastcall CL_ES::LesFilsDAgri(CL_Agriculteur *agri,ST_NoAgri *ancetre,
		int nP)
{
	ST_NoAgri *variante;
	agri->Ancetre=ancetre;
	agri->NoVariante=nP;
	if(agri->LstVariante->Count==0) return;

	nP=nP*10;
	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i]; // Agri ou agri
		variante->Agri->EstVariante=true;
		nP++;
		LesFilsDAgri(variante->Agri,ancetre,nP);
	}
	return;
}
/*
 //.............
 V_CatCulture
 V_CatAnimaux
 V_CatVivrier
 V_CatDepEnt
 V_CatRecEnt
 V_CatRecFam
 V_CatDepFam
 V_CatTypeZone
 V_CatIndic
 V_CatEtatSortie
 V_Produit
 V_Charge
 V_Externalite
 V_Culture
 V_Animaux
 V_Vivrier

 V_Espece
 V_Perenne

 V_RecEnt
 V_DepEnt

 V_RecFam
 V_DepFam

 V_TypeZone

 V_CatVar
 V_Variable

 V_Agriculteur

 V_EtatSortie
 V_Indicateur

 V_Poste

 V_CatDico
 V_Dico
 */
