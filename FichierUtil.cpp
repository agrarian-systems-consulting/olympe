//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdarg.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
//#include "ChoixCritere.h"
#include "AgriClasst.h"

#include "LesVecteurs.hse"
#include "Olympe.hse"
#include "CL_Trad.h"
#include "CL_Matrice.h"
#include "FichierLire.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
extern CL_Trad *T;

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
	V_CatBestiaux->purge();

	V_CatChStruct->purge();
	V_CatDepDiv->purge();
	V_CatRecDiv->purge();
	V_CatRecFam->purge();
	V_CatDepFam->purge();

	V_CatTypeZone->purge();

	V_CatIndic->purge();
	V_CatEtatSortie->purge();
	V_CatSerieComp->purge();
	V_CatProcedure->purge(); //proc

	V_Charge->purge();
	V_Produit->purge();
	V_Externalite->purge();
	V_Bestiaux->purge();
	V_Calendrier->purge();

	V_Culture->purge();
	V_Animaux->purge();
	V_Vivrier->purge();

	V_Espece->purge();
	V_Perenne->purge();

	V_ChStruct->purge();
	V_RecDiv->purge();
	V_DepDiv->purge();

	V_RecFam->purge();
	V_DepFam->purge();

	V_TypeZone->purge();

	V_CatVar->purge();
	V_Variable->purge();

	V_Calendrier->purge();
	V_Ensemble->purge();

	V_EtatSortie->purge();
	V_SerieComp->purge();
	V_Indicateur->purge();

	//V_Poste->purge();
	V_Elt->purge();

	V_CatDico->purge();
	V_Dico->purge();

	V_TendPrixProd->purge();
	V_TendPrixCharge->purge();
	V_ScenPrixProd->purge();
	V_ScenPrixCharge->purge();

	V_TendQProd->purge();
	V_TendQCharge->purge();
	V_ScenQProd->purge();
	V_ScenQCharge->purge();
	V_TendQExt->purge();
	V_ScenQExt->purge();

	V_CatRepart->purge(); //170604
	V_Repart->purge();

//    ChoixCritereFrm->LBCritere->Clear();

	AgriClasstFrm->ChLBCatTypeZone->Clear();

	V_Conversion->purge();
	V_Agriculteur->purge();
//    V_DefSim->purge();//10 08 01
	V_DefSim->Nbelt = 0;
	V_DefSim->NoX = 0; //110105 déjà mis a NULL 

	AgriEnCours = NULL;
	EnsembleEnCours = NULL;
}
//----------------------------------------------------------------------------
void CL_ES::IniNouveau(void) {
	CL_SystemeUnite *sys;
	sys = new CL_SystemeUnite("€", "€", "K€", 1, 1000);
	V_SystemeUnite->ins(sys);
	SysMonnaie = sys;

	sys = new CL_SystemeUnite("f", "f", "Kf", 1, 1000);
	V_SystemeUnite->ins(sys);
	sys = new CL_SystemeUnite("q", "q", "T", 1, 10);
	V_SystemeUnite->ins(sys);
	sys = new CL_SystemeUnite("T", "T", "T", 1, 1);
	V_SystemeUnite->ins(sys);
	sys = new CL_SystemeUnite("ha", "ha", "ha", 1, 1);
	V_SystemeUnite->ins(sys);
	sys = new CL_SystemeUnite("L", "1000L", "1000L", 1000, 1);
	V_SystemeUnite->ins(sys);

	//SysMonnaie=NULL;                 //O60104
	//310306
	IniTva(L_Sans.c_str(), 0); //"Sans",0);
	IniTva(L_Reduit.c_str(), 5.5); //"Réduit",5.5);
	IniTva(L_Normal.c_str(), 19.6); //"Normal",19.6);
	TvaDefaut = V_Tva->Vecteur[0];
	TvaImmo = V_Tva->Vecteur[0];

//	SysMonnaie->Monnaie='*';
	IniCategorie(V_CatProduit, L_Cereale); //"Céréales");
	IniCategorie(V_CatProduit, L_Oleagineux); //"Oléagineux");
	IniCategorie(V_CatProduit, L_Proteagineux); //"Protéagineux");

	IniCategorie(V_CatCharge, L_ChGlob); //"Charge Globale");
	IniCategorie(V_CatCharge, L_Engrais); //"Engrais");
	IniCategorie(V_CatCharge, L_Semence); //"Semences");
	IniCategorie(V_CatCharge, L_Phyto); //"Phytosanitaires");

	IniCategorie(V_CatCulture, L_Cereale); //"Céréales");
	IniCategorie(V_CatCulture, L_Oleagineux); //"Oléagineux");
	IniCategorie(V_CatCulture, L_Proteagineux); //"Protéagineux");

	ecrireFichier();
}
//----------------------------------------------------------------------------
void CL_ES::IniSysUnit(char *uUt, char *uTrans, char *uGlobal, float ratio,
		float ratioG) {
	CL_SystemeUnite *sysUnite;

	sysUnite = new CL_SystemeUnite();

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

	tva = new CL_Tva();

	tva->Nom = nom;
	tva->Taux = taux;
	V_Tva->ins(tva);

}
//----------------------------------------------------------------------------
//void CL_ES::IniCategorie(CL_Vecteur<CL_Categorie> *vecteur,char *nom)
void CL_ES::IniCategorie(CL_Vecteur<CL_Categorie> *vecteur, AnsiString nom) {
	CL_Categorie *categorie;
	categorie = new CL_Categorie();

	categorie->Nom = nom;

	vecteur->ins(categorie);
}
//---------------------------------------------------------------------------
void CL_ES::IniItem(CL_Vecteur<CL_Item>*vecteur, char*nom) {
	CL_Item *item;
	item = new CL_Item();

	item->Nom = nom;

	vecteur->ins(item);
}
//----------------------------------------------------------------------------
void CL_ES::IniType(CL_Vecteur<CL_Item> *vecteur, char*nom) {
	CL_Item *item;
	item = new CL_Item();

	item->Nom = nom;

	vecteur->ins(item);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void CL_ES::Supprimable(void) {
	int i;
	CL_Ensemble *ensemble;
	CL_AgriEff *agriEff;
	CL_AgriDefSim *defSim;
	CL_Categorie *categorie;
// tout est supprimable

	V_SystemeUnite->SupMazTrue();
	V_Tva->SupMazTrue();

	V_CatProduit->SupMazTrue();
	V_CatCharge->SupMazTrue();
	V_CatBestiaux->SupMazTrue();

	V_CatExternalite->SupMazTrue();

	V_CatCulture->SupMazTrue();
	V_CatAnimaux->SupMazTrue();
	V_CatVivrier->SupMazTrue();

	V_CatChStruct->SupMazTrue();
	V_CatRecDiv->SupMazTrue();
	V_CatDepDiv->SupMazTrue();
	V_CatRecFam->SupMazTrue();
	V_CatDepFam->SupMazTrue();

	V_CatTypeZone->SupMazTrue();
	V_CatIndic->SupMazTrue();

	V_Charge->SupMazTrue();
	V_Produit->SupMazTrue();
	V_Bestiaux->SupMazTrue();
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
	//V_Ensemble->SupMazTrue();  n'est jamais utilisé ailleurs

	V_EtatSortie->SupMazTrue();
	V_SerieComp->SupMazTrue();
	V_Indicateur->SupMazTrue();

	V_TendPrixProd->SupMazTrue();
	V_TendPrixCharge->SupMazTrue();
	V_ScenPrixProd->SupMazTrue();
	V_ScenPrixCharge->SupMazTrue();

	V_TendQProd->SupMazTrue();
	V_TendQCharge->SupMazTrue();
	V_TendQExt->SupMazTrue();
	V_ScenQProd->SupMazTrue();
	V_ScenQCharge->SupMazTrue();
	V_ScenQExt->SupMazTrue();
	//fonction spécifique !!
	V_CalendrierSupMazTrue();

	//......................................................................
	///reperer les NON supprimables
	for (i = 0; i < V_Produit->Nbelt; i++) {
		categorie = V_Produit->Vecteur[i]->Categorie;
		if (categorie)
			categorie->Supprimable = false;
		V_Produit->Vecteur[i]->Categorie->Supprimable = false;
		V_Produit->Vecteur[i]->SysUnite->Supprimable = false;
		V_Produit->Vecteur[i]->Tva->Supprimable = false;
	}
	for (i = 0; i < V_Charge->Nbelt; i++) {
		V_Charge->Vecteur[i]->Categorie->Supprimable = false;
		V_Charge->Vecteur[i]->SysUnite->Supprimable = false;
		if (V_Charge->Vecteur[i]->Tva == NULL) //rustine 150107
			V_Charge->Vecteur[i]->Tva = V_Tva->Vecteur[0];
		V_Charge->Vecteur[i]->Tva->Supprimable = false;
	}

	for (i = 0; i < V_Bestiaux->Nbelt; i++) {
		V_Bestiaux->Vecteur[i]->Categorie->Supprimable = false;
		V_Bestiaux->Vecteur[i]->Tva->Supprimable = false;
	}
	for (i = 0; i < V_Externalite->Nbelt; i++) {
		V_Externalite->Vecteur[i]->Categorie->Supprimable = false;
//290908		V_Externalite->Vecteur[i]->SysUnite->Supprimable=false;
	}
	for (i = 0; i < V_Variable->Nbelt; i++) {
		V_Variable->Vecteur[i]->SysUnite->Supprimable = false;
	}
	for (i = 0; i < V_Indicateur->Nbelt; i++) {
		categorie = V_Indicateur->Vecteur[i]->Categorie; //091208
		if (categorie)
			categorie->Supprimable = false;
		//V_Indicateur->Vecteur[i]->Categorie->Supprimable=false;
	}
	//SupMaFalse
	//pour chaque atelier produits charges externalités

	for (i = 0; i < V_Culture->Nbelt; i++)
		V_Culture->Vecteur[i]->SupMaFalse();
	for (i = 0; i < V_Animaux->Nbelt; i++)
		V_Animaux->Vecteur[i]->SupMaFalse();
	for (i = 0; i < V_Perenne->Nbelt; i++)
		V_Perenne->Vecteur[i]->SupMaFalse();
	for (i = 0; i < V_Vivrier->Nbelt; i++)
		V_Vivrier->Vecteur[i]->SupMaFalse(); //260101
	// pour pérenne ne pas oublier l'espèce
	for (i = 0; i < V_Perenne->Nbelt; i++)
		V_Perenne->Vecteur[i]->Espece->Supprimable = false;
	//calendrier

	for (i = 0; i < V_Culture->Nbelt; i++)
		MaFalseBesTrav(V_Culture->Vecteur[i]);
	for (i = 0; i < V_Animaux->Nbelt; i++)
		MaFalseBesTrav(V_Animaux->Vecteur[i]);
	for (i = 0; i < V_Perenne->Nbelt; i++)
		MaFalseBesTrav(V_Perenne->Vecteur[i]);
	for (i = 0; i < V_Vivrier->Nbelt; i++)
		MaFalseBesTrav(V_Vivrier->Vecteur[i]);

	//les ateliers
	//       culture animaux verger vivrier animaux (V_invani)
	//       formules
	for (i = 0; i < V_Agriculteur->Nbelt; i++)
		V_Agriculteur->Vecteur[i]->SupMaFalse();

	for (i = 0; i < V_Ensemble->Nbelt; i++) {
		ensemble = V_Ensemble->Vecteur[i];
		for (int j = 0; j < ensemble->V_AgriEff->Nbelt; j++) {
			agriEff = ensemble->V_AgriEff->Vecteur[j];
			//rustine 110203
			if (agriEff->Agri)
				agriEff->Agri->Supprimable = false;
		}
	}

	IndicateurSupMaFalse();

	EtatSortieSupMaFalse(V_EtatSortie);

	EtatSortieSupMaFalse(V_SerieComp);

	TendanceMaFalse(V_TendPrixProd);
	TendanceMaFalse(V_TendPrixCharge);
	TendanceMaFalse(V_ScenPrixProd);
	TendanceMaFalse(V_ScenPrixCharge);

	TendanceMaFalse(V_TendQProd);
	TendanceMaFalse(V_TendQCharge);
	TendanceMaFalse(V_ScenQProd);
	TendanceMaFalse(V_ScenQCharge);
	TendanceMaFalse(V_TendQExt);
	TendanceMaFalse(V_ScenQExt);
	for (i = 0; i < V_Agriculteur->Nbelt; i++) {
		//agri=V_Agriculteur->Vecteur[i];
		defSim = V_Agriculteur->Vecteur[i]->DefSim;
		defSim->SupMaFalse();
	}
	/*        080302
	 for(i=0;i<V_DefSim->Nbelt;i++)
	 {
	 defSim=V_DefSim->Vecteur[i];
	 defSim->SupMaFalse();
	 }
	 */
	if (SysMonnaie)
		SysMonnaie->Supprimable = false;
	if (TvaDefaut)
		TvaDefaut->Supprimable = false;
	if (TvaImmo)
		TvaImmo->Supprimable = false;
}
//---------------------------------------------------------------------------------
void CL_ES::V_CalendrierSupMazTrue(void) {
	int n, i;
	int periodeX;

	CL_Calendrier *calendrier;
	CL_Periode *periode;

	//supprimable=true
	for (n = 0; n < V_Calendrier->Nbelt; n++) {
		calendrier = V_Calendrier->Vecteur[n];
		calendrier->Supprimable = true;
		periodeX = calendrier->V_Periode->Nbelt;
		for (i = 0; i < periodeX; i++) {
			periode = calendrier->V_Periode->Vecteur[i];
			periode->Supprimable = true;
		}
	}
}
//---------------------------------------------------------------------------------
void CL_ES::MaFalseBesTrav(CL_Atelier *atelier) //060406
		{
//2 pour chaque culture ou perenne
//	j'interdis de supprimer
	int n, i, j;
	int periodeX;
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	CL_BesTrav *besTrav;
	for (n = 0; n < atelier->V_BesTrav->Nbelt; n++) {
		besTrav = atelier->V_BesTrav->Vecteur[n];
		calendrier = besTrav->Calendrier;
		if (calendrier == NULL) {
			continue; //210706
		}
		calendrier->Supprimable = false;

		periodeX = calendrier->V_Periode->Nbelt;
		for (i = 0; i < periodeX; i++) {
			periode = calendrier->V_Periode->Vecteur[i];
			for (j = 0; j < atelier->NbPhase; j++) {
				if (besTrav->Besoins->val(i, j) != 0) {
					periode->Supprimable = false;
					break;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------------
void CL_ES::IndicateurSupMaFalse(void) {
	int i, j, k, n;
	CL_Indicateur *indicateur, *autreIndic;
	CL_Arbre *arbre;
	ST_Branche branche;
	CL_Elt *elt;
	CL_Agriculteur *agri;
	CL_EtatSortie *etat;
	CL_Atelier *atelier; //070305
	//les indicateurs  utilisés par d'autres Indic
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
					if (elt->NoFamille == CULTURE) {
						atelier = V_Culture->trouve(elt->NoItem);
						atelier->Supprimable = false;
					}
					if (elt->NoFamille == ANIMAUX) {
						atelier = V_Animaux->trouve(elt->NoItem);
						atelier->Supprimable = false;
					}
					if (elt->NoFamille == INDIC) {
						autreIndic = V_Indicateur->trouve(elt->NoItem);
						if (autreIndic)
							autreIndic->Supprimable = false;
					}
				}
			}
		}
	}

	//les indicateurs dans des formules
	for (n = 0; n < V_Agriculteur->Nbelt; n++) {
		agri = V_Agriculteur->Vecteur[n];
		IndicFormuleNonSup(agri->V_Produits);
		IndicFormuleNonSup(agri->V_Charges);
		IndicFormuleNonSup(agri->V_ExtNeg);
		IndicFormuleNonSup(agri->V_ExtPos);
		IndicFormuleNonSup(agri->V_ChStruct);
		IndicFormuleNonSup(agri->V_RecDiv);
		IndicFormuleNonSup(agri->V_DepDiv);
		IndicFormuleNonSup(agri->V_RecFam);
		IndicFormuleNonSup(agri->V_DepFam);
	}
	//les indicateurs dans les etats
	for (n = 0; n < V_EtatSortie->Nbelt; n++) {
		etat = V_EtatSortie->Vecteur[n];
		for (i = 0; i < etat->V_Elt->Nbelt; i++) {
			elt = etat->V_Elt->Vecteur[i];
			if (elt->NoFamille == INDIC) {
				indicateur = V_Indicateur->trouve(elt->NoItem);
				if (indicateur == NULL)
					continue; //171007
				indicateur->Supprimable = false;
			}
		}

	}
}
//---------------------------------------------------------------------------
void CL_ES::IndicFormuleNonSup(CL_Vecteur<CL_Formule>*vecteur) {
	int n, i;
	CL_Formule *formule;
	CL_Prog *prog, *prog0;
	for (i = 0; i < vecteur->Nbelt; i++) {
		formule = vecteur->Vecteur[i];
		prog0 = NULL;
		for (n = 0; n < N_X; n++) {
			prog = formule->LesProg[n];
			if (prog == prog0)
				continue;

			prog0 = prog;
			if (prog == NULL)
				continue;
			if (prog->Arbre == NULL)
				continue; //220603
			prog->Arbre->MetIndicNonSupprimable();
		}
	}
}
//---------------------------------------------------------------------------------
void CL_ES::EtatSortieSupMaFalse(CL_Vecteur<CL_EtatSortie> *v_Etat) {
	int i, j;
	CL_EtatSortie *etat;
	CL_Elt *elt;
	CL_Indicateur *indic;
	for (i = 0; i < v_Etat->Nbelt; i++) {
		etat = v_Etat->Vecteur[i];

		for (j = 0; j < etat->V_Elt->Nbelt; j++) {
			elt = etat->V_Elt->Vecteur[j];
			if (elt->NoFamille == FORME)
				continue;
			if (elt->NoFamille == POSTE)
				continue;
			if (elt->Categorie)
				elt->Categorie->Supprimable = false;
			if (elt->Item)
				elt->Item->Supprimable = false;
			if (elt->NoFamille == INDIC) {
				indic = V_Indicateur->trouve(elt->NoItem);
				if (indic)
					indic->Supprimable = false;
			}
		}
	}
}
//---------------------------------------------------------------------------------
void CL_ES::TendanceMaFalse(CL_Vecteur<CL_Tendance> *v_Tendance)
//void CL_ES::TendanceMaFalse(CL_Vecteur<CL_Tendance> *vecteur)
		{
	int i, j;
	CL_Tendance *tendance;
	CL_Delta *delta;

	for (i = 0; i < v_Tendance->Nbelt; i++) {
		tendance = v_Tendance->Vecteur[i];
		for (j = 0; j < tendance->V_Delta->Nbelt; j++) {
			delta = tendance->V_Delta->Vecteur[j];
			delta->Item->Supprimable = false;
			if (delta->Atelier)
				delta->Atelier->Supprimable = false;
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
		agri->Pere=NULL;
		agri->NbVariante=LesFilsDAgri(agri,1)-1;
	}

}

//---------------------------------------------------------------------------
int __fastcall CL_ES::LesFilsDAgri(CL_Agriculteur *agri,int nP)
{
	int i;
	int n=1;
	int k;
	ST_NoAgri *variante;
	agri->NoVariante=nP;
	if(agri->LstVariante->Count==0)
	return 1;

	nP=nP*10;
	for( i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i]; // Agri ou agri
		if(variante->Agri==NULL)
		{
			agri->LstVariante->Delete(i);
			continue;
		}
		// correction d'erreur possible avec version <124    //290502
		variante->Agri->EstVariante=true;
		variante->Agri->Pere=agri;
		nP++;
		k=LesFilsDAgri(variante->Agri,nP);
		variante->Agri->NbVariante=k-1;
		n+=k;
	}
	return n;
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::trouveNom(void)
{
	ShowMessage("trouveNom à revoir");
	return;
}
//---------------------------------------------------------------------------
void __fastcall CL_ES::trouveNom2(char car)
{
	ShowMessage("trouveNom à revoir");
	return;
	/*
	 AnsiString nom;
	 long int pos;
	 char buf[200];
	 nom=car;
	 pos=ftell(fichier);
	 pos--;

	 while(1)
	 {
	 fread(&car,sizeof(char),1,fichier);
	 if(isalpha(car) )
	 nom+=car;
	 else if(car==' ')
	 nom+=car;
	 else if(car==0)
	 {
	 nom+=car;
	 sprintf(buf,"%ld   %s",pos,nom.c_str());
	 FBrouillon->Memo1->Lines->Add(buf);
	 return;
	 }
	 else
	 return;
	 }
	 */
}
//---------------------------------------------------------------------------
// remplit une chaine de 3 caractères dont /0 final
// pour une valeur n
// n'est valable que si n< 90*90  ('z'-' '=90)
//---------------------------------------------------------------------------
void __fastcall CL_ES::CleCree(char *cle,int n)
{
	static taille='z'-' '; //90
	int n1,n2;

	if(n<taille)
	{
		cle[0]=' ';
		cle[1]=' '+n;
	}
	else
	{
		n1=n/taille;
		cle[0]=' '+n1;
		n2=n-n1*taille;
		cle[1]=' '+n2;
	}
	cle[2]=0;
}
//---------------------------------------------------------------------------
int __fastcall CL_ES::CleVal(char *cle)
{
	int n;
	n=cle[1]-' ' + cle[0]*('z'-' ');
	return n;
}
//---------------------------------------------------------------------------
bool CL_ES::EntrerNom(const AnsiString Titre, AnsiString AAfficher,
		AnsiString &Nom) {
	int n;
	bool rep;
	bool correct;
	char buf[100];
	while (1) {
		correct = true;
		rep = InputQuery(Titre, AAfficher, Nom);
		if (rep == false)
			return false;
		Nom = Nom.Trim();
		if (Nom.Length() == 0) {
			correct = false;
			MessageBox(Application->Handle, Nom.c_str(), L_NomVide.c_str(),
					MB_OK | MB_ICONEXCLAMATION);
			//MessageBox(Application->Handle,Nom.c_str(),"Le nom est vide",MB_OK|MB_ICONEXCLAMATION);
			continue;
		}
		if (isalpha(Nom[1]) == false) {
			correct = false;
			MessageBox(Application->Handle, Nom.c_str(), L_NomAlpha.c_str(),
					MB_OK | MB_ICONEXCLAMATION);
			//MessageBox(Application->Handle,Nom.c_str(),"Doit commencer par caractère alpha",MB_OK|MB_ICONEXCLAMATION);
			continue;
		}
		for (n = 1; n <= Nom.Length(); n++) {
			if (isalnumA(Nom[n]) > 0)
				continue;
			if (Nom[n] == ' ')
				continue;

			correct = false;
			sprintf(buf, L_CarInvalide.c_str(), Nom[n]);
			//sprintf(buf,"  %c Est un Caractère Invalide",Nom[n]);
			MessageBox(Application->Handle, Nom.c_str(), buf,
					MB_OK | MB_ICONEXCLAMATION);
			break;
		}
		if (correct == true)
			return true;
	}
}
//---------------------------------------------------------------------------
int CL_ES::isalnumA(unsigned char c) {
// prise en compte de é à etc
	if (isalnum(c))
		return 1;
	if (c == '_')
		return 1;
	if (c == '.')
		return 1;
	if (c == 27)
		return 1; //  '
	if (c >= 128 && c <= 176)
		return 1;
	if (c >= 224 && c <= 244)
		return 1;

	return 0;
}
//---------------------------------------------------------------------------
void CL_ES::TexteChaine(void) {

	L_Sans = T->TrouveTexte("CL_ES", "L_Sans");
	L_Reduit = T->TrouveTexte("CL_ES", "L_Reduit");
	L_Normal = T->TrouveTexte("CL_ES", "L_Normal");

	L_Cereale = T->TrouveTexte("CL_ES", "L_Cereale");
	L_Oleagineux = T->TrouveTexte("CL_ES", "L_Oleagineux");
	L_Proteagineux = T->TrouveTexte("CL_ES", "L_Proteagineux");

	L_ChGlob = T->TrouveTexte("CL_ES", "L_ChGlob");
	L_Engrais = T->TrouveTexte("CL_ES", "L_Engrais");
	L_Semence = T->TrouveTexte("CL_ES", "L_Semence");
	L_Phyto = T->TrouveTexte("CL_ES", "L_Phyto");
	L_NomVide = T->TrouveTexte("CL_ES", "L_NomVide");
	L_NomAlpha = T->TrouveTexte("CL_ES", "L_NomAlpha");
	L_CarInvalide = T->TrouveTexte("CL_ES", "L_CarInvalide");

	//LesTitresBilan
	LesTitresBilan[0] = T->TrouveChaine("CL_ES", "LesTitresBilan[0]");
	LesTitresBilan[1] = T->TrouveChaine("CL_ES", "LesTitresBilan[1]");
	LesTitresBilan[2] = T->TrouveChaine("CL_ES", "LesTitresBilan[2]");
	LesTitresBilan[3] = T->TrouveChaine("CL_ES", "LesTitresBilan[3]");

	LesTitresBilan[4] = T->TrouveChaine("CL_ES", "LesTitresBilan[4]");
	LesTitresBilan[5] = T->TrouveChaine("CL_ES", "LesTitresBilan[5]");
	LesTitresBilan[6] = T->TrouveChaine("CL_ES", "LesTitresBilan[6]");

	LesTitresBilan[7] = T->TrouveChaine("CL_ES", "LesTitresBilan[7]");
	LesTitresBilan[8] = T->TrouveChaine("CL_ES", "LesTitresBilan[8]");
	LesTitresBilan[9] = T->TrouveChaine("CL_ES", "LesTitresBilan[9]");
	LesTitresBilan[10] = T->TrouveChaine("CL_ES", "LesTitresBilan[10]");
	LesTitresBilan[11] = T->TrouveChaine("CL_ES", "LesTitresBilan[11]");
	LesTitresBilan[12] = T->TrouveChaine("CL_ES", "LesTitresBilan[12]");

	LesTitresBilan[13] = T->TrouveChaine("CL_ES", "LesTitresBilan[13]");
	LesTitresBilan[14] = T->TrouveChaine("CL_ES", "LesTitresBilan[14]");
	LesTitresBilan[15] = T->TrouveChaine("CL_ES", "LesTitresBilan[15]");

	LesTitresBilan[16] = T->TrouveChaine("CL_ES", "LesTitresBilan[16]");
	LesTitresBilan[17] = T->TrouveChaine("CL_ES", "LesTitresBilan[17]");
	LesTitresBilan[18] = T->TrouveChaine("CL_ES", "LesTitresBilan[18]");
	LesTitresBilan[19] = T->TrouveChaine("CL_ES", "LesTitresBilan[19]");
	LesTitresBilan[20] = T->TrouveChaine("CL_ES", "LesTitresBilan[20]");
	LesTitresBilan[21] = T->TrouveChaine("CL_ES", "LesTitresBilan[21]");
	LesTitresBilan[22] = T->TrouveChaine("CL_ES", "LesTitresBilan[22]");

	//LesTitresCeg
	LesTitresCeg[0] = T->TrouveChaine("CL_ES", "LesTitresCeg[0]");
	LesTitresCeg[1] = T->TrouveChaine("CL_ES", "LesTitresCeg[1]");
	LesTitresCeg[2] = T->TrouveChaine("CL_ES", "LesTitresCeg[2]");
	LesTitresCeg[3] = T->TrouveChaine("CL_ES", "LesTitresCeg[3]");
	LesTitresCeg[4] = T->TrouveChaine("CL_ES", "LesTitresCeg[4]");
	LesTitresCeg[5] = T->TrouveChaine("CL_ES", "LesTitresCeg[5]");
	LesTitresCeg[6] = T->TrouveChaine("CL_ES", "LesTitresCeg[6]");

	LesTitresCeg[7] = T->TrouveChaine("CL_ES", "LesTitresCeg[7]");
	LesTitresCeg[8] = T->TrouveChaine("CL_ES", "LesTitresCeg[8]");
	LesTitresCeg[9] = T->TrouveChaine("CL_ES", "LesTitresCeg[9]");
	LesTitresCeg[10] = T->TrouveChaine("CL_ES", "LesTitresCeg[10]");
	LesTitresCeg[11] = T->TrouveChaine("CL_ES", "LesTitresCeg[11]");

	LesTitresCeg[12] = T->TrouveChaine("CL_ES", "LesTitresCeg[12]");

	LesTitresCeg[13] = T->TrouveChaine("CL_ES", "LesTitresCeg[13]");
	LesTitresCeg[14] = T->TrouveChaine("CL_ES", "LesTitresCeg[14]");
	LesTitresCeg[15] = T->TrouveChaine("CL_ES", "LesTitresCeg[15]");

	LesTitresCeg[16] = T->TrouveChaine("CL_ES", "LesTitresCeg[16]");
	LesTitresCeg[17] = T->TrouveChaine("CL_ES", "LesTitresCeg[17]");
	LesTitresCeg[18] = T->TrouveChaine("CL_ES", "LesTitresCeg[18]");
	LesTitresCeg[19] = T->TrouveChaine("CL_ES", "LesTitresCeg[19]");
	LesTitresCeg[20] = T->TrouveChaine("CL_ES", "LesTitresCeg[20]");
	LesTitresCeg[21] = T->TrouveChaine("CL_ES", "LesTitresCeg[21]");
	LesTitresCeg[22] = T->TrouveChaine("CL_ES", "LesTitresCeg[22]");
	LesTitresCeg[23] = T->TrouveChaine("CL_ES", "LesTitresCeg[23]");

	//LesTitresPoste[31]={
	LesTitresPoste[0] = T->TrouveChaine("CL_ES", "LesTitresPoste[0]");
	LesTitresPoste[1] = T->TrouveChaine("CL_ES", "LesTitresPoste[1]");
	LesTitresPoste[2] = T->TrouveChaine("CL_ES", "LesTitresPoste[2]");
	LesTitresPoste[3] = T->TrouveChaine("CL_ES", "LesTitresPoste[3]");
	LesTitresPoste[4] = T->TrouveChaine("CL_ES", "LesTitresPoste[4]");
	LesTitresPoste[5] = T->TrouveChaine("CL_ES", "LesTitresPoste[5]");
	LesTitresPoste[6] = T->TrouveChaine("CL_ES", "LesTitresPoste[6]");
	LesTitresPoste[7] = T->TrouveChaine("CL_ES", "LesTitresPoste[7]");

	LesTitresPoste[8] = T->TrouveChaine("CL_ES", "LesTitresPoste[8]");
	LesTitresPoste[9] = T->TrouveChaine("CL_ES", "LesTitresPoste[9]");
	LesTitresPoste[10] = T->TrouveChaine("CL_ES", "LesTitresPoste[10]");

	LesTitresPoste[11] = T->TrouveChaine("CL_ES", "LesTitresPoste[11]");
	LesTitresPoste[12] = T->TrouveChaine("CL_ES", "LesTitresPoste[12]");
	LesTitresPoste[13] = T->TrouveChaine("CL_ES", "LesTitresPoste[13]");
	LesTitresPoste[14] = T->TrouveChaine("CL_ES", "LesTitresPoste[14]");
	LesTitresPoste[15] = T->TrouveChaine("CL_ES", "LesTitresPoste[15]");
	LesTitresPoste[16] = T->TrouveChaine("CL_ES", "LesTitresPoste[16]");
	LesTitresPoste[17] = T->TrouveChaine("CL_ES", "LesTitresPoste[17]");
	LesTitresPoste[18] = T->TrouveChaine("CL_ES", "LesTitresPoste[18]");

	LesTitresPoste[19] = T->TrouveChaine("CL_ES", "LesTitresPoste[19]");

	LesTitresPoste[20] = T->TrouveChaine("CL_ES", "LesTitresPoste[20]");
	LesTitresPoste[21] = T->TrouveChaine("CL_ES", "LesTitresPoste[21]");
	LesTitresPoste[22] = T->TrouveChaine("CL_ES", "LesTitresPoste[22]");
	LesTitresPoste[23] = T->TrouveChaine("CL_ES", "LesTitresPoste[23]");

	LesTitresPoste[24] = T->TrouveChaine("CL_ES", "LesTitresPoste[24]");
	LesTitresPoste[25] = T->TrouveChaine("CL_ES", "LesTitresPoste[25]");

	LesTitresPoste[26] = T->TrouveChaine("CL_ES", "LesTitresPoste[26]");
	LesTitresPoste[27] = T->TrouveChaine("CL_ES", "LesTitresPoste[27]");
	LesTitresPoste[28] = T->TrouveChaine("CL_ES", "LesTitresPoste[28]");
	LesTitresPoste[29] = T->TrouveChaine("CL_ES", "LesTitresPoste[29]");

	LesTitresPoste[30] = T->TrouveChaine("CL_ES", "LesTitresPoste[30]");
	//char *LesTitresTreso[13]={

	LesTitresTreso[0] = T->TrouveChaine("CL_ES", "LesTitresTreso[0]");
	LesTitresTreso[1] = T->TrouveChaine("CL_ES", "LesTitresTreso[1]");
	LesTitresTreso[2] = T->TrouveChaine("CL_ES", "LesTitresTreso[2]");
	LesTitresTreso[3] = T->TrouveChaine("CL_ES", "LesTitresTreso[3]");
	LesTitresTreso[4] = T->TrouveChaine("CL_ES", "LesTitresTreso[4]");
	LesTitresTreso[5] = T->TrouveChaine("CL_ES", "LesTitresTreso[5]");
	LesTitresTreso[6] = T->TrouveChaine("CL_ES", "LesTitresTreso[6]");
	LesTitresTreso[7] = T->TrouveChaine("CL_ES", "LesTitresTreso[7]");
	LesTitresTreso[8] = T->TrouveChaine("CL_ES", "LesTitresTreso[8]");
	LesTitresTreso[9] = T->TrouveChaine("CL_ES", "LesTitresTreso[9]");
	LesTitresTreso[10] = T->TrouveChaine("CL_ES", "LesTitresTreso[10]");
	LesTitresTreso[11] = T->TrouveChaine("CL_ES", "LesTitresTreso[11]");
	LesTitresTreso[12] = T->TrouveChaine("CL_ES", "LesTitresTreso[12]");

	//char *LesTitresImmo[4]={
	LesTitresImmo[0] = T->TrouveChaine("CL_ES", "LesTitresImmo[0]");
	LesTitresImmo[1] = T->TrouveChaine("CL_ES", "LesTitresImmo[1]");
	LesTitresImmo[2] = T->TrouveChaine("CL_ES", "LesTitresImmo[2]");
	LesTitresImmo[3] = T->TrouveChaine("CL_ES", "LesTitresImmo[3]");

	//char *LesTitresSub[3]={
	LesTitresSub[0] = T->TrouveChaine("CL_ES", "LesTitresSub[0]");
	LesTitresSub[1] = T->TrouveChaine("CL_ES", "LesTitresSub[1]");
	LesTitresSub[2] = T->TrouveChaine("CL_ES", "LesTitresSub[2]");

	//char *LesTitresTva[4]={
	LesTitresTva[0] = T->TrouveChaine("CL_ES", "LesTitresTva[0]");
	LesTitresTva[1] = T->TrouveChaine("CL_ES", "LesTitresTva[1]");
	LesTitresTva[2] = T->TrouveChaine("CL_ES", "LesTitresTva[2]");
	LesTitresTva[3] = T->TrouveChaine("CL_ES", "LesTitresTva[3]");

	//char *LesTitresEmp[20]={
	LesTitresEmp[0] = T->TrouveChaine("CL_ES", "LesTitresEmp[0]");
	LesTitresEmp[1] = T->TrouveChaine("CL_ES", "LesTitresEmp[1]");
	LesTitresEmp[2] = T->TrouveChaine("CL_ES", "LesTitresEmp[2]");
	LesTitresEmp[3] = T->TrouveChaine("CL_ES", "LesTitresEmp[3]");
	LesTitresEmp[4] = T->TrouveChaine("CL_ES", "LesTitresEmp[4]");

	LesTitresEmp[5] = T->TrouveChaine("CL_ES", "LesTitresEmp[5]");
	LesTitresEmp[6] = T->TrouveChaine("CL_ES", "LesTitresEmp[6]");
	LesTitresEmp[7] = T->TrouveChaine("CL_ES", "LesTitresEmp[7]");
	LesTitresEmp[8] = T->TrouveChaine("CL_ES", "LesTitresEmp[8]");
	LesTitresEmp[9] = T->TrouveChaine("CL_ES", "LesTitresEmp[9]");

	LesTitresEmp[10] = T->TrouveChaine("CL_ES", "LesTitresEmp[10]");
	LesTitresEmp[11] = T->TrouveChaine("CL_ES", "LesTitresEmp[11]");
	LesTitresEmp[12] = T->TrouveChaine("CL_ES", "LesTitresEmp[12]");
	LesTitresEmp[13] = T->TrouveChaine("CL_ES", "LesTitresEmp[13]");
	LesTitresEmp[14] = T->TrouveChaine("CL_ES", "LesTitresEmp[14]");

	LesTitresEmp[15] = T->TrouveChaine("CL_ES", "LesTitresEmp[15]");
	LesTitresEmp[16] = T->TrouveChaine("CL_ES", "LesTitresEmp[16]");
	LesTitresEmp[17] = T->TrouveChaine("CL_ES", "LesTitresEmp[17]");
	LesTitresEmp[18] = T->TrouveChaine("CL_ES", "LesTitresEmp[18]");
	LesTitresEmp[19] = T->TrouveChaine("CL_ES", "LesTitresEmp[19]");

	L_ExistePas = T->TrouveChaine("CL_ES", "L_ExistePas");
	L_ProbSurFichier = T->TrouveChaine("CL_ES", "L_ProbSurFichier");
	L_VerActuelle = T->TrouveChaine("CL_ES", "L_VerActuelle");
	L_JmetAJour = T->TrouveChaine("CL_ES", "L_JmetAJour");
	L_VerInco = T->TrouveChaine("CL_ES", "L_VerInco");

	/*
	 L_Cereale=          "Céréales";
	 L_Oleagineux=       "Oléagineux";
	 L_Proteagineux=     "Protéagineux";

	 L_ChGlob=           "Charge Globale";
	 L_Engrais=          "Engrais";
	 L_Semence=          "Semences";
	 L_Phyto=            "Phytosanitaires";
	 L_NomVide=          "Le nom est vide";
	 L_NomAlpha=         "Doit commencer par caractère alpha";
	 L_CarInvalide=      "  %c Est un Caractère Invalide";

	 //LesTitresBilan
	 LesTitresBilan[0]="Immobilisation";          //0
	 LesTitresBilan[1]="Materiel Batiment";       //1
	 LesTitresBilan[2]="Animaux Reproducteurs";   //2
	 LesTitresBilan[3]="Plantations";             //3

	 LesTitresBilan[4]="Stocks";                  //4
	 LesTitresBilan[5]="Stocks en terre";         //5
	 LesTitresBilan[6]="Animaux ";                //6

	 LesTitresBilan[7]="Placements";              //7
	 LesTitresBilan[8]="Creance Tva";             //8
	 LesTitresBilan[9]="Creances Diverses";       //9
	 LesTitresBilan[10]="Trésorerie";              //10
	 LesTitresBilan[11]="Perte";                   //11
	 LesTitresBilan[12]="Total Actif";             //12

	 LesTitresBilan[13]="PASSIF";                  //13
	 LesTitresBilan[14]="Capital";                 //14
	 LesTitresBilan[15]="Solde Privé";             //15

	 LesTitresBilan[16]="Subvention";              //16
	 LesTitresBilan[17]="Dette LT";                //17
	 LesTitresBilan[18]="Dette ct";                //18
	 LesTitresBilan[19]="Dette Tva";               //19
	 LesTitresBilan[20]="Dettes Diverses";         //20
	 LesTitresBilan[21]="Bénéfice";                //21
	 LesTitresBilan[22]="Total Passif";            //22

	 //LesTitresCeg
	 LesTitresCeg[0]="Produits";                     //0
	 LesTitresCeg[1]="Recettes";                     //1
	 LesTitresCeg[2]="Recettes Diverses";            //2
	 LesTitresCeg[3]="Var. Stock";                   //3
	 LesTitresCeg[4]="Var. stock en terre";          //4
	 LesTitresCeg[5]="Var. inv animal Repro";        //5
	 LesTitresCeg[6]="Var. inv animal Autre";        //6

	 LesTitresCeg[7]="Produits financiers";          //7
	 LesTitresCeg[8]="Production d'immo";            //8
	 LesTitresCeg[9]="Cession d'actif";              //9
	 LesTitresCeg[10]="Perte Exceptionnelle";         //10
	 LesTitresCeg[11]="Amortissement Subvention";     //11


	 LesTitresCeg[12]="Charges";                      //12

	 LesTitresCeg[13]="Dépenses Exploitation";        //13
	 LesTitresCeg[14]="Dépenses Diverses";            //14
	 LesTitresCeg[15]="Val comptable cession";        //15

	 LesTitresCeg[16]="Charges de Structure";         //16
	 LesTitresCeg[17]="Amortissement Immo";           //17
	 LesTitresCeg[18]="Amortissement Plantation";     //18
	 LesTitresCeg[19]="Frais fin LT";                 //19
	 LesTitresCeg[20]="Frais fin CT";                 //20
	 LesTitresCeg[21]="Frais fin OCCC";               //21
	 LesTitresCeg[22]="Autres Ch Struct";             //22
	 LesTitresCeg[23]="Résultat";                     //23

	 //LesTitresPoste[31]={
	 LesTitresPoste[0]="Recettes Produits";           //0
	 LesTitresPoste[1]="Dépenses Appro";              //1
	 LesTitresPoste[2]="Marge";                       //2
	 LesTitresPoste[3]="Ch_structure",                 //3
	 LesTitresPoste[4]="Recettes_Diverses";            //4
	 LesTitresPoste[5]="Dépenses_Diverses";            //5
	 LesTitresPoste[6]="Recettes_Familiales";          //6
	 LesTitresPoste[7]="Dépenses_Familiales";          //7

	 LesTitresPoste[8]="Poste";                        //8
	 LesTitresPoste[9]="Bilan";                        //9
	 LesTitresPoste[10]="Ceg";                          //10

	 LesTitresPoste[11]="Variables";                    //11
	 LesTitresPoste[12]="Indicateurs";                  //12
	 LesTitresPoste[13]="Ext. Positive";                //13
	 LesTitresPoste[14]="Ext. Négative";                //14
	 LesTitresPoste[15]="Quant Produit";                //15
	 LesTitresPoste[16]="Quant Charge";                 //16
	 LesTitresPoste[17]="Prix Produit";                 //17
	 LesTitresPoste[18]="Prix Charge";                  //18


	 LesTitresPoste[19]="Immobilisation";               //19

	 LesTitresPoste[20]="Emprunt";                      //20
	 LesTitresPoste[21]="Emprunt LT";                   //21
	 LesTitresPoste[22]="Emprunt CT";                   //22
	 LesTitresPoste[23]="Emprunt Privé";                //23

	 LesTitresPoste[24]="Subvention";                   //24
	 LesTitresPoste[25]="Tva";                          //25

	 LesTitresPoste[26]="Surf Cultures";                //26
	 LesTitresPoste[27]="Surf Pérennes";                //27
	 LesTitresPoste[28]="Surf PluriAnnuelle";           //28
	 LesTitresPoste[29]="Eff  Animaux";                 //29

	 LesTitresPoste[30]="Mvt Animaux";                  //30
	 //char *LesTitresTreso[13]={

	 LesTitresTreso[0]="Recettes Produits";            //0
	 LesTitresTreso[1]="Dépenses Appro";               //1
	 LesTitresTreso[2]="Marge";                        //2
	 LesTitresTreso[3]="Ch_structure";                 //3
	 LesTitresTreso[4]="Recettes_Diverses";            //4
	 LesTitresTreso[5]="Dépenses_Diverses";            //5
	 LesTitresTreso[6]="Recettes_Familiales";          //6
	 LesTitresTreso[7]="Dépenses_Familiales";          //7
	 LesTitresTreso[8]="Solde";                        //8
	 LesTitresTreso[9]="Solde Cumul";                  //9
	 LesTitresTreso[10]="Résultat";                     //10
	 LesTitresTreso[11]="Ebe";                          //11
	 LesTitresTreso[12]="Caf";                          //12


	 //char *LesTitresImmo[4]={
	 LesTitresImmo[0]="Amortissement";        //0
	 LesTitresImmo[1]="Val Résiduelle";       //1
	 LesTitresImmo[2]="Achat";                //2
	 LesTitresImmo[3]="Val Brute";            //3

	 //char *LesTitresSub[3]={
	 LesTitresSub[0]="Valeur";              //0
	 LesTitresSub[1]="Amortissement";       //1
	 LesTitresSub[2]="Val Résiduelle";       //2

	 //char *LesTitresTva[4]={
	 LesTitresTva[0]="Encaissé";            //0
	 LesTitresTva[1]="Versé";               //1
	 LesTitresTva[2]="Régularisation";      //2
	 LesTitresTva[3]="Solde";                //3

	 //char *LesTitresEmp[20]={
	 LesTitresEmp[0]="Annuités      Tot Ent"; //0
	 LesTitresEmp[1]="Cap Remboursé Tot Ent"; //1
	 LesTitresEmp[2]="Interet       Tot Ent"; //2
	 LesTitresEmp[3]="Nouveaux Emp  Tot Ent"; //3
	 LesTitresEmp[4]="Dettes        Tot Ent"; //4

	 LesTitresEmp[5]="Annuités      LT Ent"; //5
	 LesTitresEmp[6]="Cap Remboursé LT Ent"; //6
	 LesTitresEmp[7]="Interet       LT Ent"; //7
	 LesTitresEmp[8]="Nouveaux Emp  LT Ent"; //8
	 LesTitresEmp[9]="Dettes        LT Ent"; //9

	 LesTitresEmp[10]="Annuités      CT Ent"; //10
	 LesTitresEmp[11]="Cap Remboursé CT Ent"; //11
	 LesTitresEmp[12]="Interet       CT Ent"; //12
	 LesTitresEmp[13]="Nouveaux  Emp CT Ent"; //13
	 LesTitresEmp[14]="Dettes        CT Ent"; //14

	 LesTitresEmp[15]="Annuités      Privé"; //15
	 LesTitresEmp[16]="Cap Remboursé Privé"; //16
	 LesTitresEmp[17]="Interet       Privé"; //17
	 LesTitresEmp[18]="Nouveaux Emp  Privé"; //18
	 LesTitresEmp[19]="Dettes        Privé"; //19
	 */
}
/*
 //---------------------------------------------------------------------------
 void CL_ES::Anglais(void)
 {
 L_Cereale=          "Cereals";
 L_Oleagineux=       "Oleaginous plants";
 L_Proteagineux=     "Proteaginous plants";

 L_ChGlob=           "Global Expenses";
 L_Engrais=          "Fertilizers";
 L_Semence=          "Seeds";
 L_Phyto=            "Phytosanitary";
 L_NomVide=          "No name";
 L_NomAlpha=         "Must start with an alpha character";
 L_CarInvalide=      "  %c is an invalid Character";
 //LesTitresBilan
 LesTitresBilan[0]="Immobilisation";          //0
 LesTitresBilan[1]="Materiel Batiment";       //1
 LesTitresBilan[2]="Animaux Reproducteurs";   //2
 LesTitresBilan[3]="Plantations";             //3

 LesTitresBilan[4]=        "Stocks";                  //4
 LesTitresBilan[5]=        "Stocks en terre";         //5
 LesTitresBilan[6]=        "Animaux ";                //6

 LesTitresBilan[7]=        "Placements";              //7
 LesTitresBilan[8]=        "Creance Tva";             //8
 LesTitresBilan[9]=        "Creances Diverses";       //9
 LesTitresBilan[10]=        "Trésorerie";              //10
 LesTitresBilan[11]=        "Perte";                   //11
 LesTitresBilan[12]=        "Total Actif";             //12

 LesTitresBilan[13]=        "PASSIF";                  //13
 LesTitresBilan[14]=        "Capital";                 //14
 LesTitresBilan[15]=        "Solde Privé";             //15

 LesTitresBilan[16]=        "Subvention";              //16
 LesTitresBilan[17]=        "Dette LT";                //17
 LesTitresBilan[18]=        "Dette ct";                //18
 LesTitresBilan[19]=        "Dette Tva";               //19
 LesTitresBilan[20]=        "Dettes Diverses";         //20
 LesTitresBilan[21]=        "Bénéfice";                //21
 LesTitresBilan[22]=        "Total Passif";            //22


 //LesTitresCeg
 LesTitresCeg[0]= "Products";                     //0
 LesTitresCeg[1]="Incomes";                      //1
 LesTitresCeg[2]="Misc. Incomes";                //2
 LesTitresCeg[3]="Stock Var.";                   //3
 LesTitresCeg[4]="Land Stock Var.";              //4
 LesTitresCeg[5]="Var. inv animal Repro";        //5
 LesTitresCeg[6]="Var. inv animal Other";        //6

 LesTitresCeg[7]="Financial Products";           //7
 LesTitresCeg[8]="Fixed Assets Production";      //8
 LesTitresCeg[9]="Transfer of assets";           //9
 LesTitresCeg[10]="Extraordinary losses";         //10
 LesTitresCeg[11]="Subvention for depreciation";  //11


 LesTitresCeg[12]="Expenses";                     //12

 LesTitresCeg[13]="Farm Expenses";                //13
 LesTitresCeg[14]="Misc. Expenses";               //14
 LesTitresCeg[15]="Accounting Val of transfer";   //15

 LesTitresCeg[16]="Fixed assets costs";           //16
 LesTitresCeg[17]="Fixed assets depreciation";    //17
 LesTitresCeg[18]="Land depreciation";            //18
 LesTitresCeg[19]="LT Fin. costs";                //19
 LesTitresCeg[20]="ST Fin. costs";                //20
 LesTitresCeg[21]="OCCC Fin. costs";              //21
 LesTitresCeg[22]="Other costs";                  //22
 LesTitresCeg[23]="Results";                      //23

 //LesTitresPoste[31]={
 LesTitresPoste[0]="Incomes Products";           //0
 LesTitresPoste[1]="Expenses Supplies";              //1
 LesTitresPoste[2]="Margin";                       //2
 LesTitresPoste[3]="Fix_Ass_Costs",                //3
 LesTitresPoste[4]="Misc_Incomes";                //4
 LesTitresPoste[5]="Misc_Expenses";                //5
 LesTitresPoste[6]="Family_Incomes";              //6
 LesTitresPoste[7]="Family_Expenses";              //7

 LesTitresPoste[8]="Item";                         //8
 LesTitresPoste[9]="Balance";                      //9
 LesTitresPoste[10]="Ceg";                          //10

 LesTitresPoste[11]="Variables";                    //11
 LesTitresPoste[12]="Indicators";                   //12
 LesTitresPoste[13]="Positive Ext.";                //13
 LesTitresPoste[14]="Negative Ext.";                //14
 LesTitresPoste[15]="Amount Product";               //15
 LesTitresPoste[16]="Amount Expense";               //16
 LesTitresPoste[17]="Price Product";                //17
 LesTitresPoste[18]="Price Expense";                //18


 LesTitresPoste[19]="Fixed Assets";               //19

 LesTitresPoste[20]="Loan";                      //20
 LesTitresPoste[21]="LT Loan";                   //21
 LesTitresPoste[22]="ST Loan";                   //22
 LesTitresPoste[23]="Private Loan";              //23

 LesTitresPoste[24]="Grant";                   //24
 LesTitresPoste[25]="Vat";                          //25

 LesTitresPoste[26]="Crops area";                //26
 LesTitresPoste[27]="Tree crops area";           //27
 LesTitresPoste[28]="Perennials area";           //28
 LesTitresPoste[29]="Animals No";                //29

 LesTitresPoste[30]="Animals Mvt";                  //30
 //char *LesTitresTreso[13]={

 LesTitresTreso[0]="Incomes Products";           //0
 LesTitresTreso[1]="Expenses Supplies";               //1
 LesTitresTreso[2]="Margin";                         //2
 LesTitresTreso[3]="Fix_Ass_Costs";                  //3
 LesTitresTreso[4]="Misc_Incomes";                  //4
 LesTitresTreso[5]="Misc_Expenses";                  //5
 LesTitresTreso[6]="Family_Income";                 //6
 LesTitresTreso[7]="Family_Expenses";                //7
 LesTitresTreso[8]="Balance";                        //8
 LesTitresTreso[9]="Total Balance";                  //9
 LesTitresTreso[10]="Results";                        //10
 LesTitresTreso[11]="Ebe";                          //11
 LesTitresTreso[12]="Caf";                          //12


 //char *LesTitresImmo[4]={
 LesTitresImmo[0]="Depreciation";        //0
 LesTitresImmo[1]="Residual Value";        //1
 LesTitresImmo[2]="Buying";              //2
 LesTitresImmo[3]="Gross Value";         //3

 //char *LesTitresSub[3]={
 LesTitresSub[0]="Value";              //0
 LesTitresSub[1]="Depreciation";       //1
 LesTitresSub[2]="Residual Value";       //2

 //char *LesTitresTva[4]={
 LesTitresTva[0]="Received";            //0
 LesTitresTva[1]="Paid";               //1
 LesTitresTva[2]="Adjustment";      //2
 LesTitresTva[3]="Balance";                //3

 //char *LesTitresEmp[20]={
 LesTitresEmp[0]="Annuities       Tot Farm"; //0
 LesTitresEmp[1]="Cap Reimbursed  Tot Farm"; //1
 LesTitresEmp[2]="Interest        Tot Farm"; //2
 LesTitresEmp[3]="New Loan        Tot Farm"; //3
 LesTitresEmp[4]="Debts           Tot Farm"; //4

 LesTitresEmp[5]="Annuities       LT Farm"; //5
 LesTitresEmp[6]="Cap Reimbursed  LT Ent"; //6
 LesTitresEmp[7]="Interest        LT Ent"; //7
 LesTitresEmp[8]="New Loan        LT Ent"; //8
 LesTitresEmp[9]="Debts           LT Ent"; //9

 LesTitresEmp[10]="Annuities       ST Ent"; //10
 LesTitresEmp[11]="Cap Reimbursed  ST Ent"; //11
 LesTitresEmp[12]="Interest        ST Ent"; //12
 LesTitresEmp[13]="New Loan        ST Ent"; //13
 LesTitresEmp[14]="Debts           ST Ent"; //14

 LesTitresEmp[15]="Annuities       Private"; //15
 LesTitresEmp[16]="Cap Reimbursed  Private"; //16
 LesTitresEmp[17]="Interest        Private"; //17
 LesTitresEmp[18]="New Loan        Private"; //18
 LesTitresEmp[19]="Debts           Private"; //19
 }
 */

/*
 //pour une culture
 for(n=0;n<V_BesTrav->Nbelt;n++)
 {
 besTrav=V_BesTrav->Vecteur[n];
 calendrier=besTrav->Calendrier;
 periodeX=calendrier->V_Periode->Nbelt;
 for(i=0;i<periodeX;i++)
 {
 periode=calendrier->V_Periode->Vecteur[i];
 for(j=0;j<NbPhase;j++)
 {
 if(besTrav->Besoins[i][j]!=0)
 periode->Supprimable=false;
 }
 }
 }
 //supprimable=true
 for(n=0;n<V_Calendrier->Nbelt;n++)
 {
 calendrier=V_Calendrier->Vecteur[n];
 periodeX=calendrier->V_Periode->Nbelt;
 for(i=0;i<periodeX;i++)
 {
 periode=calendrier->V_Periode->Vecteur[i];
 periode->Supprimable=true;
 }

 }
 ne pas oublier si suppression de modifier pour chaque culture besTrav
 */
