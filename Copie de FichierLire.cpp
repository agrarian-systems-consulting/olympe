/*
 modif fichier
 indicateur unite
 atelier Coul Motif Ordre
 */
//---------------------------------------------------------------------------
#include <vcl.h>
#include <dir.h>
#include <stdio.h>
#include <values.h>
#pragma hdrstop
/*
 #include "Olympedec.h"
 #include "LesClassesApp.h"
 #include "CL_BesTrav.h"
 */
#include "FichierLire.h"
//#include "Brouillon.h"
//#include "ChoixCritere.h"
#include "AgriClasst.h"

#include "Main.h"
//extern
#include "LesVecteurs.hse"
#include "TriAgri.h"
#include "CL_PossibOcPlact.h"

#include "Olympe.hse"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// pour &CatProduitX,etc voir Olympe.h et hse
//-----------------------------------------------------------

//------------------------------------------------------------------------------
CL_ES::CL_ES(void) {
	FLecture = "";
	FEcriture = "";

}
//---------------------------------------------------------------------------
CL_ES::~CL_ES(void) {
}
/// return 0   OK
///        1  N'existe Pas MAIS Créer Nouveau
///        2               Abandon
//---------------------------------------------------------------------------
int CL_ES::lireFichier(void) {
	int rep;
	char bufEnCours[100], bufAncien[100];
	CL_Categorie *cat;
	AnsiString bidon;
//long pos;
//bool impFichier=true;
	bool impFichier = false; //Modifier ImpFichier1 pour avoir ce qu'on veut
	bool mettreAJour = false;

	fichier = fopen(FEcriture.c_str(), "rb");
	if (fichier == NULL) {
		sprintf(bufAncien, "Le Fichier %s n'existe pas\n Le créer ?",
				FEcriture.c_str());
		rep = MessageBox(MainForm->Handle, bufAncien, "PROBLEME SUR FICHIER",
				MB_YESNO | MB_ICONEXCLAMATION);
		if (rep == ID_YES)
			return 1;
		else
			return 2;
	}
	fread(&version, sizeof(int), 1, fichier);
	if (version != Version) {
		if (version > 100 && version < Version) {
			sprintf(bufEnCours, "Actuellement Version= %4.2f", Version / 100.);
			sprintf(bufAncien, "Je mets à jour Version= %4.2f  ?",
					version / 100.);
			rep = MessageBox(MainForm->Handle, bufAncien, bufEnCours,
					MB_YESNO | MB_ICONSTOP);
			if (rep == IDNO)
				return 2;
			mettreAJour = true;
		} else {
			sprintf(bufEnCours, "Version= %4.2f   Inconnue", version / 100.);
			MessageBox(MainForm->Handle, bufEnCours, "Problème sur Fichier",
					MB_OK | MB_ICONSTOP);
			return 2;
		}
	}
	//SYSTEME UNITE///////////////////////
	if (version <= 103) {
		LireSystemeUnite103();
		LireTva103();
	} else {
		LireSystemeUnite();
		LireTva();

	}

	//produits charges externalités
//	LireCategorieP(V_CatProduit);
	LireCategorie(V_CatProduit);
	LireItem(V_Produit, V_CatProduit);

	LireCategorie(V_CatCharge);
	LireItem(V_Charge, V_CatCharge);

	// V_CatExternalite est standard cf main
	LireItem(V_Externalite);

	if (version >= 123) {
		LireCategorie(V_CatBestiaux); //101201
		if (version <= 126)
			LireItem(V_Bestiaux); //101201
		else if (version == 127)
			LireAnimaux127(V_Bestiaux); //101201
		else
			LireAnimaux(V_Bestiaux); //101201
	}
	if (version < 130)
		MajV_Bestiaux(V_Bestiaux);
	LireCategorie(V_CatCulture);
	LireCategorie(V_CatAnimaux);
	LireCategorie(V_CatVivrier);
	if (version >= 108) {
		LireCategorie(V_CatChStruct);
		LireCategorie(V_CatRecDiv);
		LireCategorie(V_CatDepDiv);
		LireCategorie(V_CatRecFam);
		LireCategorie(V_CatDepFam);

	} else {
		cat = new CL_Categorie("Structure", 0);
		V_CatChStruct->ins(cat);
		cat = new CL_Categorie("D. Diverses", 0);
		V_CatDepDiv->ins(cat);
		cat = new CL_Categorie("Recettes Diverses", 0);
		V_CatRecDiv->ins(cat);
		cat = new CL_Categorie("Recettes Familiales", 0);
		V_CatRecFam->ins(cat);
		cat = new CL_Categorie("Dépenses Familiales", 0);
		V_CatDepFam->ins(cat);
	}

	LireEspece();

	//Atelier
	if (version <= 119) {
		LireAtelier119(V_Culture);
		LireAtelier119(V_Animaux);
		LireAtelier119(V_Perenne);
		LireAtelier119(V_Vivrier);
	} else if (version <= 122) {
		LireAtelier122(V_Culture);
		LireAtelier122(V_Animaux);
		LireAtelier122(V_Perenne);
		LireAtelier122(V_Vivrier);
	} else {
		LireAtelier(V_Culture, CULTURE);
		LireAtelier(V_Animaux, ANIMAUX);
		LireAtelier(V_Perenne, PERENNE);
		LireAtelier(V_Vivrier, VIVRIER);
	}
	//V_Vivrier->purge();//  !!!!
	// autres recettes dépenses entreprise famille
	if (version >= 109)
		LireItem(V_ChStruct);

	LireItem(V_RecDiv);
	LireItem(V_DepDiv);
	LireItem(V_RecFam);
	LireItem(V_DepFam);

	if (version < 108) {
		DefNoCategorie(V_RecDiv);
		DefNoCategorie(V_DepDiv);
		DefNoCategorie(V_RecFam);
		DefNoCategorie(V_DepFam);
	}
	if (version < 110) {
		DefNoCategorie108(V_CatChStruct, V_ChStruct);
		DefNoCategorie108(V_CatRecDiv, V_RecDiv);
		DefNoCategorie108(V_CatDepDiv, V_DepDiv);
		DefNoCategorie108(V_CatRecFam, V_RecFam);
		DefNoCategorie108(V_CatDepFam, V_DepFam);
	}
	// types zone
	LireCategorie(V_CatTypeZone);
	LireItem(V_TypeZone);
	if (version <= 113)
		LireCreeLBCritere113();
	else
		LireCreeLBCatCritere();
	//oblige TriAgri à initialiser
	TriAgriFrm->EstInitialise = false;
	// etat sortie indicateur variable

	if (version <= 120) {
		LireCategorie(V_CatEtatSortie);
		LireEtatSortie(V_EtatSortie);
	} else {
		// etatSortie
		LireCategorie(V_CatEtatSortie);
		LireEtatSortie(V_EtatSortie);
		// comparaison utilise les mêmes objets
		LireCategorie(V_CatSerieComp);
		LireEtatSortie(V_SerieComp);
	}

	LireCategorie(V_CatIndic);
	if (version <= 106)
		LireIndicateur106();
	else
		LireIndicateur();

	LireCategorie(V_CatVar);
	LireItem(V_Variable);

	LireCategorie(V_CatDico);
	LireItem(V_Dico);
	if (version >= 106) {
		LireTendance(V_TendPrixProd, V_Produit);
		LireTendance(V_TendPrixCharge, V_Charge);
		LireTendance(V_ScenPrixProd, V_Produit);
		LireTendance(V_ScenPrixCharge, V_Charge);
	} else {
		V_TendPrixProd->purge();
		V_TendPrixCharge->purge();
		V_ScenPrixProd->purge();
		V_ScenPrixCharge->purge();
	}

	if (version >= 108) {
		LireTendance(V_TendQProd, V_Produit);
		LireTendance(V_TendQCharge, V_Charge);
		LireTendance(V_ScenQProd, V_Produit);
		LireTendance(V_ScenQCharge, V_Charge);
		LireTendance(V_TendQExt, V_Externalite);
		LireTendance(V_ScenQExt, V_Externalite);
	} else {
		V_TendQProd->purge();
		V_TendQCharge->purge();
		V_ScenQProd->purge();
		V_ScenQCharge->purge();
		V_TendQExt->purge();
		V_ScenQExt->purge();
	}

	if (version >= 118)
		LireCalendrier();

	Conversion = NULL;
	if (version == 119)
		LireConversion119();
	if (version >= 120)
		LireConversion();
	if (version >= 129) {
		LireCategorie(V_CatRepart);
		LireRepart(V_Repart);
	}

	//!!!!!!!!!!!!
	//...
	if (impFichier == true) {
		ImpFichierAscii();
		//return 0;
	}

	//21 mars 2001
	if (version >= 111 && version <= 115)
		//lirelesDefSim ne lit plus rien depui 100801
		LireLesDefSim();
	//correct
	//for(i=0;i<V_SystemeUnite->Nbelt;i++)
	//sysUnite=V_SystemeUnite->Vecteur[i];

	// agriculteur
	LireAgriculteur();

	// Ensemble d'agriculteurs à simuler
	LireEnsemble();

	if (version >= 111)
		freadString(Notes);
	fclose(fichier);

	if (version < 123)
		MajInvAni();

	BkpFic(); //!!!!!!!

	LesAdresses();

	IniV_Elt(); //pour que les indicateurs marquent les elements utilises

	Supprimable();

	NumeroteVarianteAgri();

	if (mettreAJour == true)
		ecrireFichier();
	if (AgriEnCours != NULL) //010403
		Mois_0 = AgriEnCours->DefSim->MDeb;
	else
		Mois_0 = 1;
	return 0;

}

//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
void CL_ES::LireSystemeUnite103(void) {
	int nbelt;
	float f;
	char c;
	CL_SystemeUnite *item;
	CL_Vecteur<CL_SystemeUnite> *vecteur;
	vecteur = V_SystemeUnite;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = new CL_SystemeUnite();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->UUt);
		freadString(item->UTrans);
		freadString(item->UGlobal);
		fread(&f, sizeof(float), 1, fichier);
		item->Ratio = f;
		fread(&f, sizeof(float), 1, fichier);
		item->RatioG = f;
		fread(&c, sizeof(char), 1, fichier);
		item->Monnaie = c;
		if (c == '*')
			SysMonnaie = item;
		vecteur->insSans(item);
	}
}
//----------------------------------------------------------------------------
void CL_ES::LireTva103(void) {
	int nbelt;
	CL_Tva *tva;
	CL_Vecteur<CL_Tva> *vecteur;
	vecteur = V_Tva;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		tva = new CL_Tva();
		fread(&tva->No, sizeof(int), 1, fichier);
		freadString(tva->Nom);
		fread(&tva->Taux, sizeof(float), 1, fichier);
		fread(&tva->Defaut, sizeof(int), 1, fichier);
		if (tva->Defaut == 1)
			TvaDefaut = tva;
		vecteur->insSans(tva);
	}
	TvaImmo = TvaDefaut;
}
//----------------------------------------------------------------------------
void CL_ES::LireSystemeUnite(void) {
	int nbelt;
	float f;
	int noMonnaie;
	CL_SystemeUnite *item;
	CL_Vecteur<CL_SystemeUnite> *vecteur;
	vecteur = V_SystemeUnite;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = new CL_SystemeUnite();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->UUt);
		freadString(item->UTrans);
		freadString(item->UGlobal);
		fread(&f, sizeof(float), 1, fichier);
		item->Ratio = f;
		fread(&f, sizeof(float), 1, fichier);
		item->RatioG = f;
		item->Monnaie = 'N';
		vecteur->insSans(item);
	}
	fread(&noMonnaie, sizeof(int), 1, fichier);
	SysMonnaie = vecteur->trouve(noMonnaie);
	if (SysMonnaie == NULL)
		SysMonnaie = vecteur->Vecteur[0];
	SysMonnaie->Monnaie = 'O';
	/*
	 for(int r=0;r<vecteur->Nbelt;r++)
	 {
	 item=vecteur->Vecteur[r];
	 }
	 */
}
//----------------------------------------------------------------------------
void CL_ES::LireTva(void) {
	int nbelt;
	CL_Tva *tva;
	CL_Vecteur<CL_Tva> *vecteur;
	int noDefaut, noImmo;
	vecteur = V_Tva;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		tva = new CL_Tva();
		fread(&tva->No, sizeof(int), 1, fichier);
		freadString(tva->Nom);
		fread(&tva->Taux, sizeof(float), 1, fichier);
		vecteur->insSans(tva);
	}
	fread(&noDefaut, sizeof(int), 1, fichier);
	TvaDefaut = vecteur->trouve(noDefaut);
	fread(&noImmo, sizeof(int), 1, fichier);
	TvaImmo = vecteur->trouve(noImmo);
}
//----------------------------------------------------------------------------
void CL_ES::LireCategorie(CL_Vecteur<CL_Categorie> *vecteur) {
	int nbelt;
	CL_Categorie *categorie;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);

	for (int i = 0; i < nbelt; i++) {
		categorie = new CL_Categorie();
		fread(&categorie->No, sizeof(int), 1, fichier);
		freadString(categorie->Nom);
		vecteur->insSans(categorie);
	}
}
//palliatif toutes les catégories de zone sont retenues
//-------------------------------------------------------------------
void CL_ES::LireCreeLBCritere113(void) {
	int n, nX;
	int noCat;
	TCheckListBox *lB;
	CL_Categorie *categorie;

	lB = AgriClasstFrm->ChLBCatTypeZone;

	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		categorie = V_CatTypeZone->Vecteur[n];
		lB->Items->AddObject(categorie->Nom, (TObject*) categorie);
	}
//ne sert à rien
	fread(&nX, sizeof(int), 1, fichier);
	for (n = 0; n < nX; n++)
		fread(&noCat, sizeof(int), 1, fichier);
}
//-------------------------------------------------------------------
void CL_ES::LireCreeLBCatCritere(void) {
	int n, nX;
	int i;
	int noCat;
	TCheckListBox *chLB;
	CL_Categorie *categorie;

	V_CatTypeZone->FlagMisA(false);

	chLB = AgriClasstFrm->ChLBCatTypeZone;
	chLB->Clear(); //141101
	fread(&nX, sizeof(int), 1, fichier);

	//seuls les n° des criteres Retenus sont stockés
	// on
	i = 0;
	for (n = 0; n < nX; n++) {
		fread(&noCat, sizeof(int), 1, fichier);
		categorie = V_CatTypeZone->trouve(noCat);
		if (categorie == NULL)
			continue; //060602??

		if (categorie->Flag == true)
			continue; //il y a 1 bug et je sais pas ou
		categorie->Flag = true;
		chLB->Items->AddObject(categorie->Nom, (TObject*) categorie);
		chLB->Checked[i] = true;
		i++;
	}
	//criteres Non Retenus
	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		categorie = V_CatTypeZone->Vecteur[n];
		if (categorie->Flag == false) {
			chLB->Items->AddObject(categorie->Nom, (TObject*) categorie);
			chLB->Checked[i] = false;
			i++;
		}
	}
}
/*
 //-------------------------------------------------------------------
 void CL_ES::LireCreeLBCatCritere(void)
 {
 int n,nX;
 int noCat;
 TListBox *lB;
 CL_Categorie *categorie;

 V_CatTypeZone->FlagMisA(false);

 lB=ChoixCritereFrm->LBCritere;
 lB->Clear();                                  //141101
 fread(&nX,sizeof(int),1,fichier);

 //criteres Retenus
 for(n=0;n<nX;n++)
 {
 fread(&noCat,sizeof(int),1,fichier);
 categorie=V_CatTypeZone->trouve(noCat);
 if(categorie==NULL)
 continue;                                //060602
 if(categorie->Flag==true) continue;  //il y a 1 bug et je sais pas ou
 categorie->Flag=true;
 lB->Items->AddObject(categorie->Nom,(TObject*)categorie);
 }
 //criteres Non Retenus
 lB=ChoixCritereFrm->LBCritereNR;
 lB->Clear();                                 //141101
 for(n=0;n<V_CatTypeZone->Nbelt;n++)
 {
 categorie=V_CatTypeZone->Vecteur[n];
 if(categorie->Flag==false)
 lB->Items->AddObject(categorie->Nom,(TObject*)categorie);
 }
 }
 */
//-------------------------------------------------------------------
void CL_ES::LireItem(CL_Vecteur<CL_Item> *vecteur) {
	int nbelt;
	CL_Item *item;

	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = new CL_Item();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->Nom);
		//correspond à famille taxes NE Plus les stocker ni les lire
		fread(&item->NoCategorie, sizeof(int), 1, fichier);
		fread(&item->NoSysteme, sizeof(int), 1, fichier);
		fread(&item->NoTva, sizeof(int), 1, fichier);
		fread(&item->Prix, sizeof(float), 1, fichier);
		vecteur->insSans(item);
	}
}
//-------------------------------------------------------------------
void CL_ES::LireAnimaux127(CL_Vecteur<CL_Item> *vecteur) {
	int i;
	int nbelt;
	CL_Item *item;

	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		item = new CL_Item();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->Nom);
		//correspond à famille taxes NE Plus les stocker ni les lire
		fread(&item->NoCategorie, sizeof(int), 1, fichier);
		fread(&item->NoOrigine, sizeof(int), 1, fichier); //190802
		fread(&item->NoTva, sizeof(int), 1, fichier);
		fread(&item->Prix, sizeof(float), 1, fichier);
		vecteur->insSans(item);
	}
}
//-------------------------------------------------------------------
void CL_ES::LireAnimaux(CL_Vecteur<CL_Item> *vecteur) {
	int i, n;
	int nbelt;
	CL_Item *item;

	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		item = new CL_Item();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->Nom);
		//correspond à famille taxes NE Plus les stocker ni les lire
		fread(&item->NoCategorie, sizeof(int), 1, fichier);
		fread(&item->NoOrigine, sizeof(int), 1, fichier); //190802
		fread(&item->NoTva, sizeof(int), 1, fichier);
		fread(&item->Prix, sizeof(float), 1, fichier); //081003
		if (version >= 130)
			fread(&item->ValInv, sizeof(float), 1, fichier); //091003

		for (n = 0; n < 4; n++) //160103
			fread(&item->DonneNo[n], sizeof(int), 1, fichier);
		for (int n = 0; n < 4; n++)
			fread(&item->DonnePcent[n], sizeof(float), 1, fichier);
		vecteur->insSans(item);
	}
}
//------------------------------------------------------------------------------
void CL_ES::MajV_Bestiaux(CL_Vecteur<CL_Item> *vecteur) {
	int i;
	CL_Item *item;
	for (i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->ValInv = item->Prix;
	}
}
//------------------------------------------------------------------------------
void CL_ES::LireItem(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	int nbelt;
	CL_Item *item;

	vecteur->purge();
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = new CL_Item();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->Nom);

		fread(&item->NoCategorie, sizeof(int), 1, fichier);
		fread(&item->NoSysteme, sizeof(int), 1, fichier);
		fread(&item->NoTva, sizeof(int), 1, fichier);

		fread(&item->Prix, sizeof(float), 1, fichier);
		vecteur->insSans(item);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAtelier119(CL_Vecteur<CL_Atelier> *vecteur) {
	int nbelt;
	CL_Atelier *atelier;
	CL_Espece *espece;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		atelier = new CL_Atelier();
		fread(&atelier->No, sizeof(int), 1, fichier);
		freadString(atelier->Nom);
		//PERENNE CULTURE ANIMAUX VIVRIER
		fread(&atelier->Nature, sizeof(int), 1, fichier);
		fread(&atelier->NoEspece, sizeof(int), 1, fichier);
		fread(&atelier->NbPhase, sizeof(int), 1, fichier);
		fread(&atelier->NoCategorie, sizeof(int), 1, fichier);
		atelier->Derobe = false; //250901
		// produit  ..
		LireAtelierItem(atelier->V_Produit, atelier->NbPhase);
		LireAtelierItem(atelier->V_Charge, atelier->NbPhase);
		LireAtelierItem(atelier->V_ChargeVolume, atelier->NbPhase);
		LireAtelierItem(atelier->V_Externalite, atelier->NbPhase);
		vecteur->insSans(atelier);

		// mise à jour pour tenir compte de l'année -1   301101
		if (atelier->Nature == PERENNE) {
			MajAtelierItem122(atelier->V_Produit, atelier->NbPhase);
			MajAtelierItem122(atelier->V_Charge, atelier->NbPhase);
			MajAtelierItem122(atelier->V_ChargeVolume, atelier->NbPhase);
			MajAtelierItem122(atelier->V_Externalite, atelier->NbPhase);
			atelier->NbPhase++;
			// maj pour tenir compte des prodImmo et amortissements
			espece = V_Espece->trouve(atelier->NoEspece);
			atelier->DebAmor = espece->DebAmor;
			atelier->DurAmor = espece->DurAmor;
		}
		// c'est déjà dans le constructeur
		atelier->PImmoExiste = false;
		atelier->PImmoFamExiste = false;
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAtelier122(CL_Vecteur<CL_Atelier> *vecteur) {
	int nbelt;
	CL_Atelier* atelier;
	CL_Espece *espece;
	int derobe;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		atelier = new CL_Atelier();
		fread(&atelier->No, sizeof(int), 1, fichier);
		freadString(atelier->Nom);
		//PERENNE CULTURE ANIMAUX VIVRIER
		fread(&atelier->Nature, sizeof(int), 1, fichier);
		fread(&atelier->NoEspece, sizeof(int), 1, fichier);
		fread(&atelier->NbPhase, sizeof(int), 1, fichier);
		fread(&atelier->NoCategorie, sizeof(int), 1, fichier);
		fread(&derobe, sizeof(int), 1, fichier);
		if (derobe == 1)
			atelier->Derobe = true; //250901
		else
			atelier->Derobe = false;
		if (version >= 122) //281101
			freadString(atelier->Notes);

		// produit  ..
		LireAtelierItem(atelier->V_Produit, atelier->NbPhase);
		LireAtelierItem(atelier->V_Charge, atelier->NbPhase);
		LireAtelierItem(atelier->V_ChargeVolume, atelier->NbPhase);
		LireAtelierItem(atelier->V_Externalite, atelier->NbPhase);
		vecteur->insSans(atelier);
		//301101
		// mise à jour pour tenir compte de l'année -1
		if (atelier->Nature == PERENNE) {
			MajAtelierItem122(atelier->V_Produit, atelier->NbPhase);
			MajAtelierItem122(atelier->V_Charge, atelier->NbPhase);
			MajAtelierItem122(atelier->V_ChargeVolume, atelier->NbPhase);
			MajAtelierItem122(atelier->V_Externalite, atelier->NbPhase);
			atelier->NbPhase++;
			espece = V_Espece->trouve(atelier->NoEspece);
			atelier->DebAmor = espece->DebAmor;
			atelier->DurAmor = espece->DurAmor;

		}
		atelier->PImmoExiste = false;
		atelier->PImmoFamExiste = false;
	}
}
/// ajoute 1 année dans qtePhase pour tenir compte de l'année -1
//--------------------------------------------------------------------------
void CL_ES::MajAtelierItem122(CL_Vecteur<CL_ItemParAtelier> *vecteur,
		int nbPhase) {
	int i, j;
	CL_ItemParAtelier* itemPA;
	float *qtePhase;
	for (i = 0; i < vecteur->Nbelt; i++) {
		itemPA = vecteur->Vecteur[i];
		qtePhase = itemPA->QtePhase;
		itemPA->QtePhase = new float[nbPhase + 1];
		itemPA->QtePhase[0] = 0;
		for (j = 0; j < nbPhase; j++)
			itemPA->QtePhase[j + 1] = qtePhase[j];
		delete[] qtePhase;
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAtelier(CL_Vecteur<CL_Atelier> *vecteur, int nature) {
	int nbelt;
	CL_Atelier* atelier;
	int derobe;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		atelier = new CL_Atelier();
		fread(&atelier->No, sizeof(int), 1, fichier);
		freadString(atelier->Nom);
		//PERENNE CULTURE ANIMAUX VIVRIER
		fread(&atelier->Nature, sizeof(int), 1, fichier);
		//correction oubli de définir nature dans certains cas mal élucidés 030604
		atelier->Nature = nature;
		fread(&atelier->NoEspece, sizeof(int), 1, fichier);
		fread(&atelier->NbPhase, sizeof(int), 1, fichier);
		fread(&atelier->NoCategorie, sizeof(int), 1, fichier);
		if (vecteur == V_Perenne) //250404 correction erreur sans conséquences 
			atelier->NoCategorie = 0;
		fread(&derobe, sizeof(int), 1, fichier);
		if (derobe == 1)
			atelier->Derobe = true; //250901
		else
			atelier->Derobe = false;
		freadString(atelier->Notes);

		// produit  ..
		LireAtelierItem(atelier->V_Produit, atelier->NbPhase);
		LireAtelierItem(atelier->V_Charge, atelier->NbPhase);
		LireAtelierItem(atelier->V_ChargeVolume, atelier->NbPhase);
		LireAtelierItem(atelier->V_Externalite, atelier->NbPhase);

		//avance
		LireAtelierAvance(atelier->V_Avance);
		//LireAtelierAvanceStock(atelier->V_Stock);
		//..........
		if (version < 126) {
			int nbelt, n;
			float f;
			fread(&nbelt, sizeof(int), 1, fichier);
			fread(&n, sizeof(int), 1, fichier); //fread(&vecteur->NoX,sizeof(int),1,fichier);
			for (int i = 0; i < nbelt; i++) {
				//eEF=new CL_EEF;
				fread(&n, sizeof(int), 1, fichier); //fread(&eEF->Deb,sizeof(int),1,fichier);
				fread(&n, sizeof(int), 1, fichier); //fread(&eEF->Fin,sizeof(int),1,fichier);
				fread(&f, sizeof(float), 1, fichier); //fread(&eEF->Val,sizeof(float),1,fichier);
				//vecteur->ins(eEF);
			}
		}
		//..........
		if (version >= 126)
			LireAtelierBesTrav(atelier->V_BesTrav);
		// debut et durée d'amortissement
		fread(&atelier->DebAmor, sizeof(int), 1, fichier);
		fread(&atelier->DurAmor, sizeof(int), 1, fichier);

		// production d'immo pour les pérennes et les autres si besoin
		fread(&atelier->PImmoExiste, sizeof(bool), 1, fichier);
		if (atelier->PImmoExiste == true) //030403 regarder le +2
				{
			atelier->ProdImmo = new float[atelier->NbPhase + 2];
			fread(atelier->ProdImmo, sizeof(float) * (atelier->NbPhase), 1,
					fichier);
		}
		fread(&atelier->PImmoFamExiste, sizeof(bool), 1, fichier);
		if (atelier->PImmoFamExiste == true) {
			atelier->ProdImmoFam = new float[atelier->NbPhase + 2];
			fread(atelier->ProdImmoFam, sizeof(float) * (atelier->NbPhase), 1,
					fichier);
		}
		// Valeur Inventaire      //220903
		if (version >= 129) {
			fread(&atelier->ValInvRepro, sizeof(float), 1, fichier);
			fread(&atelier->ValInvAutre, sizeof(float), 1, fichier);
		}

		vecteur->insSans(atelier);
	}
}
//--------------------------------------------------------------------------
void CL_ES::LireAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteur,
		int nbPhase) {
	CL_ItemParAtelier* itemPA;
	int nbelt;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		itemPA = new CL_ItemParAtelier();
		itemPA->QtePhase = new float[nbPhase];
		fread(&itemPA->No, sizeof(int), 1, fichier);
		fread(&itemPA->NoItem, sizeof(int), 1, fichier);

		fread(&itemPA->NoCharge, sizeof(int), 1, fichier);
		fread(&itemPA->NoItemPA, sizeof(int), 1, fichier); //nouveau
		fread(itemPA->QtePhase, sizeof(float) * nbPhase, 1, fichier);
		vecteur->insSans(itemPA);
	}
}
//--------------------------------------------------------------------------
void CL_ES::LireAtelierAvance(CL_Vecteur<CL_EEF> *vecteur) {
	CL_EEF* eEF;
	int nbelt;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		eEF = new CL_EEF();
		fread(&eEF->Deb, sizeof(int), 1, fichier);
		fread(&eEF->Fin, sizeof(int), 1, fichier);
		fread(&eEF->Val, sizeof(float), 1, fichier);
		vecteur->ins(eEF);
	}
}
//--------------------------------------------------------------------------
void CL_ES::LireAtelierBesTrav(CL_Vecteur<CL_BesTrav> *vecteur) {
	CL_BesTrav* besTrav;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		besTrav = new CL_BesTrav();
		besTrav->lireFichier(fichier);
		vecteur->insSans(besTrav);
	}
}

//----------------------------------------------------------------------------
void CL_ES::LireEspece(void) {
	int nbelt;
	CL_Espece *espece;
	CL_Vecteur<CL_Espece> *vecteur;

	vecteur = V_Espece;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		espece = new CL_Espece();
		fread(&espece->No, sizeof(int), 1, fichier);
		freadString(espece->Nom);
		fread(&espece->DebAmor, sizeof(int), 1, fichier);
		fread(&espece->DurAmor, sizeof(int), 1, fichier);
		fread(&espece->NbPhase, sizeof(int), 1, fichier);
		fread(espece->Phase, sizeof(int) * N_PHASE, 1, fichier);
		vecteur->insSans(espece);
	}
}
// provisoire servira pour lire rec dep autre ds nouveau lire item
//-------------------------------------------------------------------------
void CL_ES::LireType(CL_Vecteur<CL_Item> *vecteur) {
	int nbelt;
	CL_Item *item;

	vecteur->purge();
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = new CL_Item();
		fread(&item->No, sizeof(int), 1, fichier);
		freadString(item->Nom);
		vecteur->insSans(item);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireBidon(void) {
	int nbelt, noX;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&noX, sizeof(int), 1, fichier);
}
//-------------------------------------------------------------------------
void CL_ES::LireCalendrier(void) {
	int i, j;
	int nbelt, nbPeriode;
	CL_Vecteur<CL_Calendrier> *vecteur = V_Calendrier;
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		calendrier = new CL_Calendrier();

		fread(&calendrier->No, sizeof(int), 1, fichier);
		freadString(calendrier->Nom);

		fread(&nbPeriode, sizeof(int), 1, fichier);
		fread(&calendrier->V_Periode->NoX, sizeof(int), 1, fichier);

		for (j = 0; j < nbPeriode; j++) {
			periode = new CL_Periode();
			LirePeriode(periode);
			calendrier->V_Periode->insSans(periode);
		}
		vecteur->insSans(calendrier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LirePeriode(CL_Periode *periode) {
	fread(&periode->No, sizeof(int), 1, fichier);
	freadString(periode->Nom);
	fread(&periode->JDeb, sizeof(int), 1, fichier);
	fread(&periode->MDeb, sizeof(int), 1, fichier);
	fread(&periode->JFin, sizeof(int), 1, fichier);
	fread(&periode->MFin, sizeof(int), 1, fichier);
	fread(&periode->PcentDispo, sizeof(int), 1, fichier);
	fread(&periode->HpJ, sizeof(float), 1, fichier);
	periode->CalculDuree();
	periode->CalculDispo();
}
//-------------------------------------------------------------------------
void CL_ES::LireConversion119(void) {
	int i;
	int nbelt;
	CL_Vecteur<CL_Conversion> *vecteur = V_Conversion;
	CL_Conversion *conversion;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		conversion = new CL_Conversion();

		fread(&conversion->No, sizeof(int), 1, fichier);
		freadString(conversion->Nom);

		fread(&conversion->NoBase, sizeof(int), 1, fichier);
		fread(&conversion->NoSortie, sizeof(int), 1, fichier);
		fread(&conversion->APartirDe, sizeof(int), 1, fichier);
		conversion->Base = V_SystemeUnite->trouve(conversion->NoBase);
		conversion->Sortie = V_SystemeUnite->trouve(conversion->NoSortie);
		fread(conversion->TauxConvFrancVersEuro, sizeof(float) * N_X, 1,
				fichier);
		fread(conversion->TauxConvEuroVersFranc, sizeof(float) * N_X, 1,
				fichier);

		vecteur->insSans(conversion);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireConversion(void) {
	int i, n;
	int nbelt;
	CL_Vecteur<CL_Conversion> *vecteur = V_Conversion;
	CL_Conversion *conversion;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		conversion = new CL_Conversion();

		fread(&conversion->No, sizeof(int), 1, fichier);
		freadString(conversion->Nom);

		fread(&conversion->NoBase, sizeof(int), 1, fichier);
		fread(&conversion->NoSortie, sizeof(int), 1, fichier);
		fread(&conversion->APartirDe, sizeof(int), 1, fichier);
		conversion->Base = V_SystemeUnite->trouve(conversion->NoBase);
		conversion->Sortie = V_SystemeUnite->trouve(conversion->NoSortie);
		fread(conversion->TauxConvFrancVersEuro, sizeof(float) * N_X, 1,
				fichier);
		fread(conversion->TauxConvEuroVersFranc, sizeof(float) * N_X, 1,
				fichier);

		vecteur->insSans(conversion);
	}
	fread(&n, sizeof(int), 1, fichier);
	if (n == -1)
		Conversion = NULL; //250901
	else
		Conversion = vecteur->trouve(n);
}
//---------------------------------------------------------------------------
void CL_ES::LireRepart(CL_Vecteur<CL_Repart> *vecteur) {
	int i;
	CL_Repart *repart;
	int nbelt;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		repart = new CL_Repart();
		repart->FichierLire(fichier);
		vecteur->insSans(repart);
	}
}

//-------------------------------------------------------------------------
void CL_ES::LireAgriculteur(void) {
	int i, n, no;
	int nbelt;
	int nCritere, nVariante;
	ST_NoAgri *variante;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_Agriculteur> *vecteur;

	CL_Item* critere;
	CL_Troupeau *troupeau;
	int noCatBestiaux;
	vecteur = V_Agriculteur;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		agri = new CL_Agriculteur();
		fread(&agri->No, sizeof(int), 1, fichier);
		fread(&nCritere, sizeof(int), 1, fichier);
		//classif
		// correction d'erreur d'origine inconnue A TROUVER
		V_TypeZone->FlagMisA('N');
		critere = new CL_Item();
		for (int j = 0; j < nCritere; j++) {
			fread(&no, sizeof(int), 1, fichier);
			critere = V_TypeZone->trouve(no);
			if (critere->Flag == 'N') {
				critere->Flag = 'O';
				agri->LstCritere->Add(critere);
			}
		}
		freadString(agri->Nom);
		if (version < 110)
			CreeAgriDefSim(agri->DefSim);
		else if (version == 110)
			LireAgriDefSim110(agri->DefSim);
		else
			LireAgriDefSim(agri->DefSim);

		freadString(agri->Notes);
		// a quoi ça sert car EstVariante est établi dans NumeroteVariante ??
		fread(&agri->EstVariante, sizeof(bool), 1, fichier);

		LireAgriValeurAtelier(agri->V_Culture);
		LireAgriValeurAtelier(agri->V_Animaux);
		// a partir de 126  mvt des animaux
		// a partir de 130 plusieurs troupeaux
		if (version >= 126 && version < 130) {
			fread(&noCatBestiaux, sizeof(int), 1, fichier);
			if (noCatBestiaux != -1) {
				troupeau = new CL_Troupeau();
				troupeau->NoCatBestiaux = noCatBestiaux;
				troupeau->CatBestiaux = V_CatBestiaux->trouve(noCatBestiaux);
				agri->LstTroupeaux->Add(troupeau);
				if (version < 127)
					LireAgriInvAni126(troupeau->V_InvAni, troupeau->LstMvtAni); //11 06 00
				else
					//128 129)
					LireAgriInvAni129(troupeau->V_InvAni, troupeau->LstMvtAni); //06 10 03
			} else {
				// pb dans les exploitation TOTAL et MOY
				troupeau = new CL_Troupeau();
				// pas d'animaux mais j'ai stocké les nbelt et nox
				if (version < 127)
					LireAgriInvAni126(troupeau->V_InvAni, troupeau->LstMvtAni); //11 06 00
				else
					//128 129)
					LireAgriInvAni129(troupeau->V_InvAni, troupeau->LstMvtAni); //06 10 03
				if (troupeau->V_InvAni->Nbelt == 0)
					delete troupeau;
				else {
					troupeau->CatBestiaux = V_CatBestiaux->Vecteur[0];
					troupeau->NoCatBestiaux = troupeau->CatBestiaux->No;
					agri->LstTroupeaux->Add(troupeau);
				}

			}
		} else
			LireAgriTroupeau(agri->LstTroupeaux); //06 10 03
		LireAgriValeurVerger(agri->V_Verger);
		if (version >= 113)
			LireAgriValeurVerger(agri->V_Vivrier);
		LireAgriValeurItem(agri->V_Variable);
		if (version <= 104) {
			LireAgriFormule104(agri->V_Produits, PRODUIT);
			LireAgriFormule104(agri->V_Charges, CHARGE);
			LireAgriFormule104(agri->V_ChStruct, CHSTRUCT);
			LireAgriFormule104(agri->V_RecDiv, RECDIV);
			LireAgriFormule104(agri->V_DepDiv, DEPDIV);
			LireAgriFormule104(agri->V_RecFam, RECFAM);
			LireAgriFormule104(agri->V_DepFam, DEPFAM);
			int bidon;
			for (int n = 0; n < 4; n++)
				fread(&bidon, sizeof(int), 1, fichier);
		} else if (version <= 106) {
			LireAgriFormule105(agri->V_Produits);
			LireAgriFormule105(agri->V_Charges);
			LireAgriFormule105(agri->V_ChStruct);
			LireAgriFormule105(agri->V_RecDiv);
			LireAgriFormule105(agri->V_DepDiv);
			LireAgriFormule105(agri->V_RecFam);
			LireAgriFormule105(agri->V_DepFam);
			int bidon;
			for (int n = 0; n < 4; n++)
				fread(&bidon, sizeof(int), 1, fichier);
		} else if (version <= 114) {
			LireAgriFormule114(agri->V_Produits);
			LireAgriFormule114(agri->V_Charges);
			LireAgriFormule114(agri->V_ChStruct);
			LireAgriFormule114(agri->V_RecDiv);
			LireAgriFormule114(agri->V_DepDiv);
			LireAgriFormule114(agri->V_RecFam);
			LireAgriFormule114(agri->V_DepFam);
		} else {
			LireAgriFormule(agri->V_Produits);
			LireAgriFormule(agri->V_Charges);
			LireAgriFormule(agri->V_ChStruct);
			LireAgriFormule(agri->V_RecDiv);
			LireAgriFormule(agri->V_DepDiv);
			LireAgriFormule(agri->V_RecFam);
			LireAgriFormule(agri->V_DepFam);
		}
		if (version >= 102) {
			if (version <= 104) {
				LireAgriFormule104(agri->V_ExtPos, EXTPOS);
				LireAgriFormule104(agri->V_ExtNeg, EXTPOS);
			}
			if (version <= 106) {
				LireAgriFormule105(agri->V_ExtPos);
				LireAgriFormule105(agri->V_ExtNeg);
			} else {
				LireAgriFormule(agri->V_ExtPos);
				LireAgriFormule(agri->V_ExtNeg);
			}
		}
		if (version >= 103) {
			LireAgriEmpLT(agri->V_EmpLT);
			LireAgriEmpCT(agri->V_EmpCT);
			LireAgriSub(agri->V_Sub);
			LireAgriPlact(agri->V_Plact);
			LireAgriOccc(agri->V_Occc);
			if (version == 103)
				LireAgriImmo103(agri->V_Immo);
			else
				LireAgriImmo(agri->V_Immo);
			LireAgriPetit(agri, agri->V_Petit);
			if (agri->V_Petit->Nbelt > N_X)
				agri->V_Petit->Nbelt = N_X; //bug grignon_0 corrigé
			LireAgriFN_Xp1(agri->V_FinSom);
			LireAgriFN_Xp1(agri->V_InvSom);
			if (version >= 124) {
				LireAgriCreanceDette(agri->V_Creance);
				LireAgriCreanceDette(agri->V_Dette);
			}
			if (version >= 126)
				LireAgriPolStock(agri->V_PolStock);
			if (version == 123)
				LireAgriStockIni123(agri->V_StockIni); //121201

			if (version >= 124)
				LireAgriStockIni(agri->V_StockIni); //121201
			if (version >= 126)
				LireAgriVente(agri->LstQuantPrix); //210802
			if (version >= 129)
				LireAgriItemRepart(agri); //170604

			agri->TvaEntIni = new CL_TvaEntIni();
			if (version >= 117) {
				LireAgriTvaEntIni(agri->TvaEntIni); //130802
				fread(&agri->TresoIni, sizeof(float), 1, fichier); //130802
//                agri->TresoIni=0.;                   // 171002 depanne LeGrusse
//                if(agri->TresoIni<MINFLOAT)
//                    agri->TresoIni=0.;
			} else {
				agri->TresoIni = 0;
			}
		}

		fread(&nVariante, sizeof(int), 1, fichier);
		for (int j = 0; j < nVariante; j++) {
			variante = new (ST_NoAgri);
			fread(&variante->No, sizeof(int), 1, fichier);
			agri->LstVariante->Add(variante);
		}
		vecteur->insSans(agri);
	}
	fread(&n, sizeof(int), 1, fichier);
	if (n == -1)
		AgriEnCours = NULL;
	else
		AgriEnCours = V_Agriculteur->trouve(n);

}
//-------------------------------------------------------------------------
void CL_ES::LireAgriDefSim(CL_AgriDefSim *defSim) {
	fread(&defSim->An_0, sizeof(int), 1, fichier);
	fread(&defSim->NbAnSim, sizeof(int), 1, fichier);
	fread(&defSim->MDeb, sizeof(int), 1, fichier);
	fread(&defSim->AnCalage, sizeof(int), 1, fichier);
	fread(&defSim->TypeAlea, sizeof(int), 1, fichier);

	fread(&defSim->NoPrixProd, sizeof(int), 1, fichier);
	fread(&defSim->NoPrixCharge, sizeof(int), 1, fichier);
	fread(&defSim->NoQProd, sizeof(int), 1, fichier);
	fread(&defSim->NoQCharge, sizeof(int), 1, fichier);
	fread(&defSim->NoQExt, sizeof(int), 1, fichier);

	fread(&defSim->TouSPrixProd, sizeof(int), 1, fichier);
	fread(&defSim->TouSPrixCharge, sizeof(int), 1, fichier);
	fread(&defSim->TouSQProd, sizeof(int), 1, fichier);
	fread(&defSim->TouSQCharge, sizeof(int), 1, fichier);
	fread(&defSim->TouSQExt, sizeof(int), 1, fichier);

	fread(&defSim->Enchainement, sizeof(char) * (N_X + 1), 1, fichier);

	TrouveTendScen(defSim);
	V_DefSim->ins(defSim);
}
//-------------------------------------------------------------------------
void CL_ES::TrouveTendScen(CL_AgriDefSim *defSim) {
	int no;
	no = defSim->NoPrixProd;
	switch (defSim->TouSPrixProd) {
	case 0:
		defSim->PrixProd = NULL;
		break;
	case 1:
		defSim->PrixProd = V_TendPrixProd->trouve(no);
		break;
	case 2:
		defSim->PrixProd = V_ScenPrixProd->trouve(no);
		break;
	}

	no = defSim->NoPrixCharge;
	switch (defSim->TouSPrixCharge) {
	case 0:
		defSim->PrixCharge = NULL;
		break;
	case 1:
		defSim->PrixCharge = V_TendPrixCharge->trouve(no);
		break;
	case 2:
		defSim->PrixCharge = V_ScenPrixCharge->trouve(no);
		break;
	}

	no = defSim->NoQProd;
	switch (defSim->TouSQProd) {
	case 0:
		defSim->QProd = NULL;
		break;
	case 1:
		defSim->QProd = V_TendQProd->trouve(no);
		break;
	case 2:
		defSim->QProd = V_ScenQProd->trouve(no);
		break;
	}

	no = defSim->NoQCharge;
	switch (defSim->TouSQCharge) {
	case 0:
		defSim->QCharge = NULL;
		break;
	case 1:
		defSim->QCharge = V_TendQCharge->trouve(no);
		break;
	case 2:
		defSim->QCharge = V_ScenQCharge->trouve(no);
		break;
	}

	no = defSim->NoQExt;
	switch (defSim->TouSQExt) {
	case 0:
		defSim->QExt = NULL;
		break;
	case 1:
		defSim->QExt = V_TendQExt->trouve(no);
		break;
	case 2:
		defSim->QExt = V_ScenQExt->trouve(no);
		break;
	}

}
// 110 n'a jamais été utilisé en dehors de grignon ->je mets à zero
//-------------------------------------------------------------------------
void CL_ES::LireAgriDefSim110(CL_AgriDefSim *defSim) {
	fread(&defSim->An_0, sizeof(int), 1, fichier);
	fread(&defSim->NbAnSim, sizeof(int), 1, fichier);
	fread(&defSim->MDeb, sizeof(int), 1, fichier);
	fread(&defSim->AnCalage, sizeof(int), 1, fichier);
	fread(&defSim->TypeAlea, sizeof(int), 1, fichier);

	fread(&defSim->NoPrixProd, sizeof(int), 1, fichier);
	fread(&defSim->NoPrixCharge, sizeof(int), 1, fichier);
	fread(&defSim->NoQProd, sizeof(int), 1, fichier);
	fread(&defSim->NoQCharge, sizeof(int), 1, fichier);
	fread(&defSim->NoQExt, sizeof(int), 1, fichier);

	fread(&defSim->Enchainement, sizeof(char) * (N_X + 1), 1, fichier);

	defSim->NoPrixProd = -1;
	defSim->NoPrixCharge = -1;
	defSim->NoQProd = -1;
	defSim->NoQCharge = -1;
	defSim->NoQExt = -1;

	defSim->TouSPrixProd = 0;
	defSim->TouSPrixCharge = 0;
	defSim->TouSQProd = 0;
	defSim->TouSQCharge = 0;
	defSim->TouSQExt = 0;

	defSim->TypeAlea = 0;

	V_DefSim->ins(defSim);

}
//-------------------------------------------------------------------------
void CL_ES::CreeAgriDefSim(CL_AgriDefSim *defSim) {
//	defSim->An_0      =2000;
	defSim->NbAnSim = 10;
	defSim->MDeb = 1;
	defSim->AnCalage = 0;
	defSim->TypeAlea = SANS;
}
// lire le type pour V_Culture ou V_Vivrier
//-------------------------------------------------------------------------
void CL_ES::LireAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur) {
	int nbelt;
	CL_Valeur* valeur;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		valeur = new CL_Valeur();
		fread(&valeur->No, sizeof(int), 1, fichier);
		fread(&valeur->NoAtelier, sizeof(int), 1, fichier);
		fread(&valeur->NoItem, sizeof(int), 1, fichier);
		fread(valeur->Valeur, sizeof(float) * N_X, 1, fichier);

		vecteur->insSans(valeur);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriTroupeau(TList *lstTroupeaux) {
	int n, nTroupeau;
	CL_Troupeau *troupeau;

	fread(&nTroupeau, sizeof(int), 1, fichier);

	for (n = 0; n < nTroupeau; n++) {
		troupeau = new CL_Troupeau();
		fread(&troupeau->NoCatBestiaux, sizeof(int), 1, fichier);
		troupeau->CatBestiaux = V_CatBestiaux->trouve(troupeau->NoCatBestiaux);
		LireAgriInvAni(troupeau->V_InvAni, troupeau->LstMvtAni); //11 06 00
		lstTroupeaux->Add(troupeau);
	}
}

//-------------------------------------------------------------------------
void CL_ES::LireAgriInvAni(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni) //061003
		{
	int i, n;
	int nbelt, nbListe;
	CL_InvAni *invAni;
	CL_MvtAni *mvtAni;
	int noAnimal, date, type, eff;
	float info;
//float valInv;
	vecteur->purge();
	lstMvtAni->Count = 0;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);

	for (i = 0; i < nbelt; i++) {
		invAni = new CL_InvAni();
		fread(&invAni->No, sizeof(int), 1, fichier);
		fread(&invAni->NoAnimal, sizeof(int), 1, fichier);
		fread(&invAni->Reproducteur, sizeof(char), 1, fichier); //031003
		fread(invAni->PrixVenteMoy, sizeof(invAni->PrixVenteMoy), 1, fichier);
		fread(invAni->ValInvMoy, sizeof(invAni->ValInvMoy), 1, fichier);
		fread(invAni->Effectif, sizeof(float) * N_X, 1, fichier);
		fread(invAni->Valeur, sizeof(float) * (N_X + 1), 1, fichier);
		fread(invAni->Vente, sizeof(float) * N_X, 1, fichier);
		fread(invAni->Achat, sizeof(float) * N_X, 1, fichier);
		fread(invAni->ValVente, sizeof(float) * N_X, 1, fichier);
		fread(invAni->ValAchat, sizeof(float) * N_X, 1, fichier);
		if (version >= 129) {
			fread(invAni->EffMax, sizeof(float) * N_X, 1, fichier); //180903
			fread(invAni->NoAtelier, sizeof(invAni->NoAtelier), 1, fichier); //190903
			for (n = 0; n < N_X; n++)
				invAni->Atelier[n] = V_Animaux->trouve(invAni->NoAtelier[n]);

		}
		invAni->Animal = V_Bestiaux->trouve(invAni->NoAnimal);
		vecteur->insSans(invAni);
	}
	if (nbelt == 0)
		return;

	fread(&nbListe, sizeof(int), 1, fichier);
	for (i = 0; i < nbListe; i++) {
		fread(&noAnimal, sizeof(int), 1, fichier);
		fread(&date, sizeof(int), 1, fichier);
		fread(&type, sizeof(int), 1, fichier);
		fread(&eff, sizeof(int), 1, fichier);
		fread(&info, sizeof(float), 1, fichier);
		mvtAni = new CL_MvtAni(noAnimal, date, type, eff, info);

		lstMvtAni->Add(mvtAni);
	}

}
//-------------------------------------------------------------------------
void CL_ES::LireAgriInvAni129(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni) //061003
		{
	int i, n;
	int nbelt, nbListe;
	CL_InvAni *invAni;
	CL_MvtAni *mvtAni;
	int noAnimal, date, type, eff;
	float info;
	float valInv;
	vecteur->purge();
	lstMvtAni->Count = 0;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);

	for (i = 0; i < nbelt; i++) {
		invAni = new CL_InvAni();
		fread(&invAni->No, sizeof(int), 1, fichier);
		fread(&invAni->NoAnimal, sizeof(int), 1, fichier);
		invAni->Animal = V_Bestiaux->trouve(invAni->NoAnimal);

		fread(&valInv, sizeof(float), 1, fichier); //260903
		for (n = 0; n < N_X + 1; n++)
			invAni->ValInvMoy[n] = valInv;

		fread(invAni->Effectif, sizeof(float) * N_X, 1, fichier);
		if (version < 129)
			fread(invAni->Valeur, sizeof(float) * N_X, 1, fichier);
		else
			fread(invAni->Valeur, sizeof(float) * (N_X + 1), 1, fichier);

		fread(invAni->Vente, sizeof(float) * N_X, 1, fichier);
		fread(invAni->Achat, sizeof(float) * N_X, 1, fichier);
		fread(invAni->ValVente, sizeof(float) * N_X, 1, fichier);
		fread(invAni->ValAchat, sizeof(float) * N_X, 1, fichier);
		if (version >= 129) {
			fread(invAni->EffMax, sizeof(float) * N_X, 1, fichier); //180903
			fread(invAni->NoAtelier, sizeof(invAni->NoAtelier), 1, fichier); //190903
			for (n = 0; n < N_X; n++)
				invAni->Atelier[n] = V_Animaux->trouve(invAni->NoAtelier[n]);

		}
		for (n = 0; n < N_X; n++)
			invAni->PrixVenteMoy[n] = invAni->Animal->Prix;
		vecteur->insSans(invAni);
	}
	if (nbelt == 0)
		return;
	fread(&nbListe, sizeof(int), 1, fichier);
	for (i = 0; i < nbListe; i++) {
		fread(&noAnimal, sizeof(int), 1, fichier);
		fread(&date, sizeof(int), 1, fichier);
		fread(&type, sizeof(int), 1, fichier);
		fread(&eff, sizeof(int), 1, fichier);
		fread(&info, sizeof(float), 1, fichier);
		mvtAni = new CL_MvtAni(noAnimal, date, type, eff, info);

		lstMvtAni->Add(mvtAni);
	}
}

//-------------------------------------------------------------------------
void CL_ES::LireAgriInvAni126(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni) //11 06 00
		{
	int i, n;
	int nbelt, nbListe;
	CL_InvAni *invAni;
	CL_MvtAni *mvtAni;
	int noAnimal, date, type, eff;
	float info;
	float valInv;
	vecteur->purge();
	lstMvtAni->Count = 0;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);

	for (i = 0; i < nbelt; i++) {
		invAni = new CL_InvAni();
		fread(&invAni->No, sizeof(int), 1, fichier);
		fread(&invAni->NoAnimal, sizeof(int), 1, fichier);
		fread(&valInv, sizeof(float), 1, fichier); //260903
		for (n = 0; n < N_X; n++)
			invAni->ValInvMoy[n] = valInv; //061003
		fread(invAni->Effectif, sizeof(int) * N_X, 1, fichier);
		fread(invAni->Valeur, sizeof(float) * N_X, 1, fichier);

		fread(invAni->Vente, sizeof(int) * N_X, 1, fichier);
		fread(invAni->Achat, sizeof(int) * N_X, 1, fichier);
		fread(invAni->ValVente, sizeof(float) * N_X, 1, fichier);
		fread(invAni->ValAchat, sizeof(float) * N_X, 1, fichier);
		invAni->Animal = V_Bestiaux->trouve(invAni->NoAnimal);
		vecteur->insSans(invAni);
	}
	if (nbelt == 0)
		return;

	fread(&nbListe, sizeof(int), 1, fichier);
	for (i = 0; i < nbListe; i++) {
		fread(&noAnimal, sizeof(int), 1, fichier);
		fread(&date, sizeof(int), 1, fichier);
		fread(&type, sizeof(int), 1, fichier);
		fread(&eff, sizeof(int), 1, fichier);
		fread(&info, sizeof(float), 1, fichier);
		mvtAni = new CL_MvtAni(noAnimal, date, type, eff, info);

		lstMvtAni->Add(mvtAni);
	}

}
//-------------------------------------------------------------------------
void CL_ES::LireAgriFormule104(CL_Vecteur<CL_Formule> *vecteur, int noFamille) {
	int nbelt;
	CL_Formule *formule;
	CL_Prog *prog;
	int leProgDe[N_X];
	AnsiString as;
	bool estLu[N_X];
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		formule = new CL_Formule();
		formule->NoFamille = noFamille;
		fread(&formule->No, sizeof(int), 1, fichier);
		trouveItemFormule(formule);
//		freadString(formule->Nom);
		freadString(as);
		fread(formule->Valeur, sizeof(float) * N_X, 1, fichier);
		fread(&formule->Origine, sizeof(char), 1, fichier);
		prog = NULL;
		if (version == 100) {
			LireFormule100(formule);
			if (formule->Item)
				vecteur->insSans(formule);
			continue;
		}
		for (int n = 0; n < N_X; n++)
			estLu[n] = false;

		for (int n = 0; n < N_X; n++) {
			if (estLu[n] == true)
				continue;

			fread(leProgDe, sizeof(int) * N_X, 1, fichier);
			if (leProgDe[0] == -1)
				break;

			prog = new CL_Prog();
			freadString(as);
//            prog->Chaine=strdup(as.c_str());
			prog->Arbre = lireArbre();
			prog->Reseau = lireReseau();
			for (int j = 0; j < N_X; j++) {
				if (leProgDe[j] == 1) {
					formule->LesProg[j] = prog;
					estLu[j] = true;
				}
			}
		}
		if (formule->Item)
			vecteur->insSans(formule);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriFormule105(CL_Vecteur<CL_Formule> *vecteur) {
	int nbelt;
	CL_Formule *formule;
	CL_Prog *prog;
	int leProgDe[N_X];
	AnsiString as;
	bool estLu[N_X];
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		formule = new CL_Formule();
		fread(&formule->No, sizeof(int), 1, fichier); //c'est le n° de l'item
		fread(&formule->NoFamille, sizeof(int), 1, fichier);
//		fread(&formule->NoItem,sizeof(int),1,fichier);
		trouveItemFormule(formule);
//		freadString(formule->Nom);
		fread(formule->Valeur, sizeof(float) * N_X, 1, fichier);
		fread(&formule->Origine, sizeof(char), 1, fichier);
		prog = NULL;
//        if(version==100)
//        {
//            LireFormule100(formule);
//  	      vecteur->insSans(formule);
//            continue;
//        }
		for (int n = 0; n < N_X; n++)
			estLu[n] = false;

		for (int n = 0; n < N_X; n++) {
			if (estLu[n] == true)
				continue;

			fread(leProgDe, sizeof(int) * N_X, 1, fichier);
			if (leProgDe[0] == -1)
				break;

			prog = new CL_Prog();
			freadString(as);
//            prog->Chaine=strdup(as.c_str());
			prog->Arbre = lireArbre();
			prog->Reseau = lireReseau();
			for (int j = 0; j < N_X; j++) {
				if (leProgDe[j] == 1) {
					formule->LesProg[j] = prog;
					estLu[j] = true;
				}
			}
		}
		vecteur->insSans(formule);
	}
//    vecteur->purge();// A RETIRER PB MAYNADIER
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriFormule114(CL_Vecteur<CL_Formule> *vecteur) {
	int i, j, n;
	int nbelt;
	CL_Formule *formule;
	CL_Prog *prog;
	int leProgDe[N_X];
	AnsiString as;
	bool estLu[N_X];
	bool existe;
	vecteur->purge();
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		existe = true;
		formule = new CL_Formule();
		fread(&formule->No, sizeof(int), 1, fichier); //c'est le n° de l'item
		fread(&formule->NoFamille, sizeof(int), 1, fichier);
		trouveItemFormule(formule);
		fread(formule->Valeur, sizeof(float) * N_X, 1, fichier);
		fread(&formule->Origine, sizeof(char), 1, fichier);
		prog = NULL;
		for (n = 0; n < N_X; n++)
			estLu[n] = false;

		for (n = 0; n < N_X; n++) {
			if (estLu[n] == true)
				continue;

			fread(leProgDe, sizeof(int) * N_X, 1, fichier);
			if (leProgDe[0] == -1) // break;
					{
				for (j = n; j < N_X; j++) {
					if (leProgDe[j] == -1) {
						formule->LesProg[j] = NULL;
						estLu[j] = true;
					}
				}
				//....
				if (n == 0) //correction d'erreur jusqu'à 114 inclus
						{
					existe = false;
					for (j = 0; j < N_X; j++) {
						if (leProgDe[j] != -1) {
							existe = true;
							break;
						}
					}
				}
				continue;
			}
			prog = new CL_Prog();
			prog->Arbre = lireArbre();
			prog->Reseau = lireReseau();
			for (j = 0; j < N_X; j++) {
				if (leProgDe[j] == 1) {
					formule->LesProg[j] = prog;
					estLu[j] = true;
				}
			}
		}
		if (formule->Item == NULL)
			continue; //190501
		vecteur->insSans(formule);

		if (existe == false) //correction d'erreur jusqu'à 114 inclus
			fread(leProgDe, sizeof(int) * N_X, 1, fichier);
	}
}
/// ceci est la copie de ce qui existe dans FichierEcrire
///formule->LesProg[n] est un pointeur sur CL_Prog qui contient pointeur sur
///    CL_Arbre CL_Reseau qui peuvent etre nuls
/// si les prog pour différentes années sont les mêmes
/// ne pas stocker plusieurs fois la même information
///
/// pour formule->LesProg[j]
//  regarder si on rencontre pour d'autres années la meme formule
/// si oui mettre des 1 dans leProgDe[N_X] pour ces années leProgDe[j]=1
///        dire qu'il est ecrit( estEcrit[j]=true
/// stocker l'arbre et le reseau
/// stocker leProgDe qui contient des 0 et des 1
/// mécanisme inverse à la lecture
/// ATTENTION
/// si pas de formule leProgDe[j]=-1
///

//-------------------------------------------------------------------------
void CL_ES::LireAgriFormule(CL_Vecteur<CL_Formule> *vecteur) {
	int i, j, n;
	int nbelt;
	CL_Formule *formule;
	CL_Prog *prog;
	int leProgDe[N_X];
	AnsiString as;
	bool estLu[N_X];
	vecteur->purge();
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		formule = new CL_Formule();
		fread(&formule->No, sizeof(int), 1, fichier); //c'est le n° de l'item
		fread(&formule->NoFamille, sizeof(int), 1, fichier);
		trouveItemFormule(formule);
		fread(formule->Valeur, sizeof(float) * N_X, 1, fichier);
		fread(&formule->Origine, sizeof(char), 1, fichier);
		prog = NULL;
		for (n = 0; n < N_X; n++)
			estLu[n] = false;

		for (n = 0; n < N_X; n++) {
			if (estLu[n] == true)
				continue;

			fread(leProgDe, sizeof(int) * N_X, 1, fichier);
			if (leProgDe[0] == -1) // break;
					{
				for (j = n; j < N_X; j++) {
					if (leProgDe[j] == -1) {
						formule->LesProg[j] = NULL;
						estLu[j] = true;
					}
				}
				continue;
			}
			prog = new CL_Prog();
			prog->Arbre = lireArbre();
			prog->Reseau = lireReseau();
			for (j = 0; j < N_X; j++) {
				if (leProgDe[j] == 1) {
					formule->LesProg[j] = prog;
					estLu[j] = true;
				}
			}
		}
		if (formule->Item == NULL)
			continue; //190501
		vecteur->insSans(formule);
	}
}
//-------------------------------------------------------------------------
void CL_ES::trouveItemFormule(CL_Formule *formule) {
	CL_Vecteur<CL_Item> *vecteur;
	switch (formule->NoFamille) {
	case PRODUIT:
		vecteur = V_Produit;
		break;
	case CHARGE:
		vecteur = V_Charge;
		break;
	case EXTPOS:
		vecteur = V_Externalite;
		break;
	case EXTNEG:
		vecteur = V_Externalite;
		break;
	case CHSTRUCT:
		vecteur = V_ChStruct;
		break;
	case RECDIV:
		vecteur = V_RecDiv;
		break;
	case DEPDIV:
		vecteur = V_DepDiv;
		break;
	case RECFAM:
		vecteur = V_RecFam;
		break;
	case DEPFAM:
		vecteur = V_DepFam;
		break;
	default:
		ShowMessage("Oubli dans trouveItemFormule");
		formule->Item = NULL;
		return;
	}
	formule->Item = vecteur->trouve(formule->No);
}
//-------------------------------------------------------------------------
void CL_ES::LireFormule100(CL_Formule *formule) {
	int existe;
	CL_Prog *prog;
	AnsiString as;
	prog = NULL;
	for (int n = 0; n < N_X; n++) {
		fread(&existe, sizeof(int), 1, fichier);

		if (existe == 0) {
			formule->LesProg[n] = prog;
			continue;
		}
		prog = new CL_Prog();
		freadString(as);
//        prog->Chaine=strdup(as.c_str());
		prog->Arbre = lireArbre();
		prog->Reseau = lireReseau();
		formule->LesProg[n] = prog;
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriValeurItem(CL_Vecteur<CL_Valeur> *vecteur) {
	int nbelt;
	CL_Valeur* valeur;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		valeur = new CL_Valeur();
		fread(&valeur->No, sizeof(int), 1, fichier);
		fread(&valeur->NoAtelier, sizeof(int), 1, fichier);
		fread(&valeur->NoItem, sizeof(int), 1, fichier);
		fread(valeur->Valeur, sizeof(float) * N_X, 1, fichier);

		vecteur->insSans(valeur);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriValeurVerger(CL_Vecteur<CL_Verger> *vecteur) {
	int nbelt;
	CL_Verger* verger;
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		verger = new CL_Verger();
		fread(&verger->No, sizeof(int), 1, fichier);
		fread(&verger->NoAtelier, sizeof(int), 1, fichier);
		fread(&verger->NoEspece, sizeof(int), 1, fichier);
		fread(&verger->AnPlant, sizeof(int), 1, fichier);
		fread(&verger->AnArr, sizeof(int), 1, fichier);
		fread(&verger->Surface, sizeof(float), 1, fichier);

		vecteur->insSans(verger);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriEmpLT(CL_Vecteur<CL_EmpLT> *vecteur) {
	CL_EmpLT* empLT;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		empLT = new CL_EmpLT();
		fread(&empLT->No, sizeof(int), 1, fichier);
		freadString(empLT->Nom);
		fread(&empLT->Montant, sizeof(float), 1, fichier);
		fread(&empLT->Duree, sizeof(int), 1, fichier);
		fread(&empLT->Duree2, sizeof(int), 1, fichier);
		fread(&empLT->Taux, sizeof(float), 1, fichier);
		fread(&empLT->Taux2, sizeof(float), 1, fichier);
		freadString(empLT->Type);
		fread(&empLT->AReal, sizeof(int), 1, fichier);
		fread(&empLT->MReal, sizeof(int), 1, fichier);
		fread(&empLT->ARemb, sizeof(int), 1, fichier);
		fread(&empLT->MRemb, sizeof(int), 1, fichier);
		fread(&empLT->Pour, sizeof(char), 1, fichier);
		vecteur->insSans(empLT);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriEmpCT(CL_Vecteur<CL_EmpCT> *vecteur) {
	CL_EmpCT* empCT;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		empCT = new CL_EmpCT();
		fread(&empCT->No, sizeof(int), 1, fichier);
		freadString(empCT->Nom);
		fread(&empCT->Montant, sizeof(float), 1, fichier);
		fread(&empCT->Taux, sizeof(float), 1, fichier);
		freadString(empCT->Type);
		fread(&empCT->AReal, sizeof(int), 1, fichier);
		fread(&empCT->MReal, sizeof(int), 1, fichier);
		fread(&empCT->ARemb, sizeof(int), 1, fichier);
		fread(&empCT->MRemb, sizeof(int), 1, fichier);
		fread(&empCT->Pour, sizeof(char), 1, fichier);

		vecteur->insSans(empCT);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriSub(CL_Vecteur<CL_Sub> *vecteur) {
	CL_Sub* sub;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		sub = new CL_Sub();
		fread(&sub->No, sizeof(int), 1, fichier);
		freadString(sub->Nom);
		fread(&sub->Montant, sizeof(float), 1, fichier);
		fread(&sub->AReal, sizeof(int), 1, fichier);
		fread(&sub->MReal, sizeof(int), 1, fichier);
		fread(&sub->Duree, sizeof(int), 1, fichier);

		vecteur->insSans(sub);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriPlact(CL_Vecteur<CL_Plact> *vecteur) {
	CL_Plact* plact;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		plact = new CL_Plact();
		fread(&plact->No, sizeof(int), 1, fichier);
		freadString(plact->Nom);
		fread(&plact->Montant, sizeof(float), 1, fichier);
		fread(&plact->Taux, sizeof(float), 1, fichier);
		fread(&plact->Type, sizeof(char), 1, fichier);
		fread(&plact->AReal, sizeof(int), 1, fichier);
		fread(&plact->MReal, sizeof(int), 1, fichier);
		fread(&plact->ATerme, sizeof(int), 1, fichier);
		fread(&plact->MTerme, sizeof(int), 1, fichier);
		fread(&plact->Pour, sizeof(char), 1, fichier);

		vecteur->insSans(plact);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriOccc(CL_Vecteur<CL_Occc> *vecteur) {
	CL_Occc* occc;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		occc = new CL_Occc();
		fread(&occc->No, sizeof(int), 1, fichier);
		fread(&occc->Ex, sizeof(int), 1, fichier);
		fread(&occc->Montant, sizeof(float), 1, fichier);
		fread(&occc->Taux, sizeof(float), 1, fichier);
		fread(&occc->Pcent, sizeof(float), 1, fichier);
		fread(&occc->Frais, sizeof(float), 1, fichier);

		vecteur->insSans(occc);

	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriImmo103(CL_Vecteur<CL_Immo> *vecteur) {
	CL_Immo* immo;
	int nbelt;
	int bidon;
	bool bidbool;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		immo = new CL_Immo();
		fread(&immo->No, sizeof(int), 1, fichier);
		freadString(immo->Nom);
		fread(&immo->ValAchat, sizeof(float), 1, fichier);
		fread(&immo->AAchat, sizeof(int), 1, fichier);
		fread(&immo->MAchat, sizeof(int), 1, fichier);
		fread(&immo->AVente, sizeof(int), 1, fichier);
		fread(&immo->MVente, sizeof(int), 1, fichier);
		fread(&immo->TypeAmor, sizeof(char), 1, fichier);
		fread(&immo->Duree, sizeof(int), 1, fichier);
//		fread(&immo->Present,   sizeof(bool),1,fichier);
		fread(&bidbool, sizeof(bool), 1, fichier);
//		fread(&immo->Groupe,    sizeof(int),1,fichier);
		fread(&bidon, sizeof(int), 1, fichier);

		fread(&immo->NoTva, sizeof(int), 1, fichier);

		immo->Tva = V_Tva->trouve(immo->NoTva);
		vecteur->insSans(immo);

	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriImmo(CL_Vecteur<CL_Immo> *vecteur) {
	CL_Immo* immo;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		immo = new CL_Immo();
		fread(&immo->No, sizeof(int), 1, fichier);
		freadString(immo->Nom);
		fread(&immo->ValAchat, sizeof(float), 1, fichier);
		fread(&immo->AAchat, sizeof(int), 1, fichier);
		fread(&immo->MAchat, sizeof(int), 1, fichier);
		fread(&immo->AVente, sizeof(int), 1, fichier);
		fread(&immo->MVente, sizeof(int), 1, fichier);
		fread(&immo->TypeAmor, sizeof(char), 1, fichier);
		fread(&immo->Duree, sizeof(int), 1, fichier);
		fread(&immo->ValVente, sizeof(float), 1, fichier);
		fread(&immo->NoTva, sizeof(int), 1, fichier);

		immo->Tva = V_Tva->trouve(immo->NoTva);
		vecteur->insSans(immo);

	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriPetit(CL_Agriculteur *agri, CL_Vecteur<CL_Petit> *vecteur) {
	CL_Petit * petit;
	int i, nbelt;

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	// auparavant le nombre de petit materiel n'etait pas limité
	//il y a maintenant N_X petit
	for (i = 0; i < nbelt; i++) {
		petit = new CL_Petit();
		fread(&petit->No, sizeof(int), 1, fichier);
		fread(&petit->NoRepart, sizeof(int), 1, fichier); //non informé ne sert pas
		fread(&petit->ValAchat, sizeof(float), 1, fichier);
		fread(&petit->NoTva, sizeof(int), 1, fichier);

		petit->Tva = V_Tva->trouve(petit->NoTva);
		vecteur->insSans(petit);
	}
	if (nbelt == 0)
		return;
}
// FN_Xp1 est une classe qu contient un vecteur de float de N_X+1
//-------------------------------------------------------------------------
void CL_ES::LireAgriFN_Xp1(CL_Vecteur<CL_FN_Xp1> *vecteur) {
	CL_FN_Xp1 *fN_Xp1;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		fN_Xp1 = new CL_FN_Xp1();
		fread(&fN_Xp1->No, sizeof(int), 1, fichier);
		fread(&fN_Xp1->Valeur, sizeof(float) * (N_X + 1), 1, fichier);
		vecteur->insSans(fN_Xp1);

	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriCreanceDette(CL_Vecteur<CL_EnCours> *vecteur) {
	CL_EnCours *enCours;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		enCours = new CL_EnCours();
		fread(&enCours->No, sizeof(int), 1, fichier);
		fread(&enCours->NoFamille, sizeof(int), 1, fichier);
		fread(&enCours->NoItem, sizeof(int), 1, fichier);
		fread(&enCours->EnStock, sizeof(char), 1, fichier);
		fread(&enCours->Valeur, sizeof(float), 1, fichier);
		fread(&enCours->APaie, sizeof(int), 1, fichier);
		fread(&enCours->MPaie, sizeof(int), 1, fichier);
		vecteur->insSans(enCours);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriPolStock(CL_Vecteur<CL_PolStock> *vecteur) {
	CL_PolStock *polStock;
	int nbelt;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		polStock = new CL_PolStock();
		polStock->LireFichier(fichier);
		vecteur->insSans(polStock);
	}
}
//-------------------------------------------------------------------------
//void CL_ES::LireAgriItemRepart (CL_Vecteur<CL_ItemRepart> *vecteur)
void CL_ES::LireAgriItemRepart(CL_Agriculteur *agri) //170604
		{
	CL_Vecteur<CL_ItemRepart> *vecteur = agri->V_ItemRepart;
	CL_ItemRepart *itemRepart, *itemRepartPetit;
	int nbelt;
	int possibOcPlactExiste;
	int noRepartDefaut; //a mettre dans CL_Agri

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) //les repart par produits ont ete créés automatiquement
									// mais peuvent etre vides
									// c'est le cas si V_Repart->Nbelt==0
			{
		itemRepart = new CL_ItemRepart();
		itemRepart->LireFichier(fichier);
		if (itemRepart->Famille == PETITMAT)
			itemRepartPetit = itemRepart;
		vecteur->ins(itemRepart);
	}
	if (V_Repart->Nbelt == 0) //fichier .oly ou treso non utilisée
		return;

	fread(&noRepartDefaut, sizeof(int), 1, fichier);
	fread(&possibOcPlactExiste, sizeof(int), 1, fichier);

	if (possibOcPlactExiste != 0) {
		agri->PossibOcPlact = new CL_PossibOcPlact();
		agri->PossibOcPlact->LireFichier(fichier);
	}
	if (agri->V_Petit->Nbelt == 0)
		return;
	agri->QuanValPetit->ItemRepart = itemRepartPetit;
}

//version 123 n'a sans dout pas été utilisée
//-------------------------------------------------------------------------
void CL_ES::LireAgriStockIni123(CL_Vecteur<CL_StockIni> *vecteur) {
	int nbelt;
	int no, noItem;
	float valStock, taux;
	int pcentAn[N_X];
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		fread(&no, sizeof(int), 1, fichier);
		fread(&noItem, sizeof(int), 1, fichier);
		fread(&valStock, sizeof(float), 1, fichier);
		fread(&taux, sizeof(float), 1, fichier);
		fread(pcentAn, sizeof(int) * N_X, 1, fichier);
	}
}

//-------------------------------------------------------------------------
void CL_ES::LireAgriStockIni(CL_Vecteur<CL_StockIni> *vecteur) {
	int nbelt;
	CL_StockIni *stock;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		stock = new CL_StockIni();
		fread(&stock->No, sizeof(int), 1, fichier);
		fread(&stock->NoItem, sizeof(int), 1, fichier);
		fread(stock->Quantite, sizeof(float) * N_X, 1, fichier);
		fread(stock->PrixRevient, sizeof(float) * N_X, 1, fichier);
		vecteur->insSans(stock);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriVente(TList *lstQuantPrix) {
	int n, nX;
	CL_QuantPrix *quantPrix;
	lstQuantPrix->Clear();
	fread(&nX, sizeof(int), 1, fichier);
	for (n = 0; n < nX; n++) {
		quantPrix = new CL_QuantPrix();
		quantPrix->LireFichier(fichier);
		//rustine
		if (quantPrix->Item == NULL)
			continue;

		lstQuantPrix->Add(quantPrix);
	}
}
//-------------------------------------------------------------------------
void CL_ES::LireAgriTvaEntIni(CL_TvaEntIni *tvaIni) {
	fread(&tvaIni->Recu, sizeof(float), 1, fichier);
	fread(&tvaIni->Verse, sizeof(float), 1, fichier);
	fread(&tvaIni->AcompteAout, sizeof(float), 1, fichier);
	fread(&tvaIni->AcompteNov, sizeof(float), 1, fichier);
	fread(&tvaIni->AcompteFev, sizeof(float), 1, fichier);
	fread(&tvaIni->AcompteMai, sizeof(float), 1, fichier);
}
//-------------------------------------------------------------------------
void CL_ES::LireEnsemble(void) {
	int i, j, n;
	int nbelt;
	int nbAgriEff;
	CL_Ensemble *ensemble;
	CL_AgriEff *agriEff;
	CL_Vecteur<CL_Ensemble> *vecteur;
	int nVariante;
	ST_NoEnsemble *variante;

//CL_Vecteur<CL_AgriEff>  *vAgriEff;
	vecteur = V_Ensemble;
	vecteur->purge();
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		ensemble = new CL_Ensemble();
		fread(&ensemble->No, sizeof(int), 1, fichier);
		freadString(ensemble->Nom);
		freadString(ensemble->Notes);

		fread(&nbAgriEff, sizeof(int), 1, fichier);

		fread(&ensemble->V_AgriEff->NoX, sizeof(int), 1, fichier);
		for (j = 0; j < nbAgriEff; j++) {
			agriEff = new CL_AgriEff();
			LireAgriEff(agriEff);
			ensemble->V_AgriEff->ins(agriEff);
		}
		// Total n'est pas écrit -> à recalculer à chaque fois !!!
		vecteur->insSans(ensemble);
		/*
		 if(vecteur->trouve(ensemble->Nom)==NULL)
		 {
		 vecteur->insSans( ensemble);
		 }
		 */
		if (version > 103) {
			fread(&nVariante, sizeof(int), 1, fichier);
			for (int j = 0; j < nVariante; j++) {
				variante = new (ST_NoEnsemble);
				fread(&variante->No, sizeof(int), 1, fichier);
				ensemble->LstVariante->Add(variante);
			}
		}
	}
	EnsembleEnCours = NULL; //130801
	if (version >= 117) {
		fread(&n, sizeof(int), 1, fichier);
		if (n >= 0)
			EnsembleEnCours = V_Ensemble->trouve(n);
	}

}
//-------------------------------------------------------------------------
void CL_ES::LireAgriEff(CL_AgriEff *agriEff) {
	fread(&agriEff->NoAgri, sizeof(int), 1, fichier);
	fread(agriEff->Effectif, sizeof(int) * N_X, 1, fichier);

}

//-------------------------------------------------------------------------
void CL_ES::LireEtatSortie(CL_Vecteur<CL_EtatSortie> *v_Etat) {
	int l;
	char *chaine;
	CL_EtatSortie *etat;
	CL_Elt *elt;
	int nbelt;
	int nbeltV;
	CL_Vecteur<CL_Elt> *vecteur;
//AnsiString nom;//!!
	int i, j;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&v_Etat->NoX, sizeof(int), 1, fichier);
	v_Etat->purge();

	for (i = 0; i < nbelt; i++) {
		etat = new CL_EtatSortie();
		freadString(etat->Nom);
		fread(&etat->No, sizeof(int), 1, fichier);
		fread(&etat->NoCategorie, sizeof(int), 1, fichier);
		vecteur = etat->V_Elt;
		fread(&nbeltV, sizeof(int), 1, fichier);
		fread(&vecteur->NoX, sizeof(int), 1, fichier);
		for (j = 0; j < nbeltV; j++) {
			elt = new CL_Elt();
			fread(&elt->No, sizeof(int), 1, fichier);
			fread(&elt->NoFamille, sizeof(int), 1, fichier);
			fread(&elt->NoCategorie, sizeof(int), 1, fichier);
			fread(&elt->NoItem, sizeof(int), 1, fichier);
			if (elt->NoItem == TITRE) {
				fread(&l, sizeof(int), 1, fichier);
				chaine = new char[l];
				fread(chaine, sizeof(char) * (l), 1, fichier);
				elt->Nom = chaine;
			}
			vecteur->insSans(elt);
		}
		v_Etat->insSans(etat);
	}
}
//----------------------------------------------------------------------------
void CL_ES::LireIndicateur106(void) {
	int nbelt;
	CL_Indicateur *indicateur;
	V_Indicateur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&V_Indicateur->NoX, sizeof(int), 1, fichier);

	for (int i = 0; i < nbelt; i++) {
		indicateur = new CL_Indicateur();
		freadString(indicateur->Nom);
		fread(&indicateur->No, sizeof(int), 1, fichier);
		fread(&indicateur->NoCategorie, sizeof(int), 1, fichier);
		fread(&indicateur->type, sizeof(int), 1, fichier);

		if (version >= 130) //101003
				{
			fread(&indicateur->NoSysteme, sizeof(int), 1, fichier); //101003
			indicateur->SysUnite = V_SystemeUnite->trouve(
					indicateur->NoSysteme);
		}

		freadString(indicateur->Prog->Source); //a supprimer
		indicateur->Prog->Arbre = lireArbre();
		indicateur->Prog->Reseau = lireReseau();
		//indicateur->Arbre=   lireArbre( );
		//indicateur->Reseau=  lireReseau( );
		//if(indicateur->Arbre)   indicateur->Compile=true;
		//else                    indicateur->Compile=false;
		indicateur->Compile = true;
		V_Indicateur->insSans(indicateur);
	}
}
//----------------------------------------------------------------------------
void CL_ES::LireIndicateur(void) {
	int nbelt;
	CL_Indicateur *indicateur;
	V_Indicateur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&V_Indicateur->NoX, sizeof(int), 1, fichier);

	for (int i = 0; i < nbelt; i++) {
		indicateur = new CL_Indicateur();
		freadString(indicateur->Nom);
		fread(&indicateur->No, sizeof(int), 1, fichier);
		fread(&indicateur->NoCategorie, sizeof(int), 1, fichier);
		fread(&indicateur->type, sizeof(int), 1, fichier);

		if (version >= 130) //101004
				{
			fread(&indicateur->NoSysteme, sizeof(int), 1, fichier);
			indicateur->SysUnite = V_SystemeUnite->trouve(
					indicateur->NoSysteme);
		}

		indicateur->Prog->Arbre = lireArbre();
		indicateur->Prog->Reseau = lireReseau();
		indicateur->Compile = true;
		V_Indicateur->insSans(indicateur);
	}
}
//----------------------------------------------------------------------------
CL_Arbre* CL_ES::lireArbre(void) {
	int n, nX;
	CL_Arbre *Arbre;
	fread(&nX, sizeof(int), 1, fichier);
	if (nX == 0) {
		Arbre = NULL;
		return Arbre;
	}
	Arbre = new CL_Arbre(nX, 10);
	Arbre->BrancheX = nX;
	for (n = 0; n < nX; n++) {
		fread(&Arbre->LesBranches[n], sizeof(ST_Branche), 1, fichier);
//        branche=Arbre->LesBranches[n];
//		if(branche.arg[0]==INDIC)                 //270902
//        	ShowMessage("INDIC");
	}
	return Arbre;
//return NULL;
}
//----------------------------------------------------------------------------
CL_Reseau *CL_ES::lireReseau(void) {
	int n, nX;
	CL_Reseau *Reseau;
	fread(&nX, sizeof(int), 1, fichier);
	if (nX == 0) {
		Reseau = NULL;
		return Reseau;
	}

	Reseau = new CL_Reseau(nX, 10);
	Reseau->MailleX = nX;
	for (n = 0; n < Reseau->MailleX; n++) {
//        fread(&Reseau->LesMailles[n],sizeof(ST_Maille),1,fichier);
		fread(&Reseau->LesMailles[n].code, sizeof(int), 1, fichier);
		fread(&Reseau->LesMailles[n].branche, sizeof(int), 1, fichier);
		fread(&Reseau->LesMailles[n].apG, sizeof(int), 1, fichier);
		fread(&Reseau->LesMailles[n].apD, sizeof(int), 1, fichier);

	}
	return Reseau;
}
//----------------------------------------------------------------------------
void CL_ES::LireTendance(CL_Vecteur<CL_Tendance> *vecteur,
		CL_Vecteur<CL_Item> *vItem) {
	int nbelt, nbDelta;
	CL_Tendance* tendance;
	CL_Delta* delta;
	CL_Vecteur<CL_Delta> *vDelta;
	bool erreur; //si pb fichier Impossible !!??
	vecteur->purge();

	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		tendance = new CL_Tendance();
		fread(&tendance->No, sizeof(int), 1, fichier);
		freadString(tendance->Nom);

		vDelta = tendance->V_Delta;
		fread(&nbDelta, sizeof(int), 1, fichier);
		fread(&vDelta->NoX, sizeof(int), 1, fichier);
		for (int j = 0; j < nbDelta; j++) {
			delta = new CL_Delta();
			erreur = false;
			fread(&delta->No, sizeof(int), 1, fichier);
			fread(&delta->NoItem, sizeof(int), 1, fichier);
			fread(&delta->NoAtelier, sizeof(int), 1, fichier);
			fread(&delta->Nature, sizeof(int), 1, fichier);

			delta->Item = vItem->trouve(delta->NoItem);
			if (delta->Item == NULL)
				erreur = true;
			//ça ne devrait pas arriver Verifier Supprimable
			//Nature=0 par defaut ne sert que pour rdt et quantité de charges
			switch (delta->Nature) {
			case ANIMAUX:
				delta->Atelier = V_Animaux->trouve(delta->NoAtelier);
				break;
			case CULTURE:
				delta->Atelier = V_Culture->trouve(delta->NoAtelier);
				break;
			case VIVRIER:
				delta->Atelier = V_Vivrier->trouve(delta->NoAtelier);
				break;
			case PERENNE:
				delta->Atelier = V_Perenne->trouve(delta->NoAtelier);
				break;
			}
			for (int k = 0; k < N_X; k++)
				fread(&delta->Pcent[k], sizeof(float), 1, fichier);
			if (erreur == false)
				vDelta->insSans(delta);

		}
		vecteur->insSans(tendance);
	}
}
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------
//------------------------------------------------------------------------------
void CL_ES::freadString(AnsiString &s) {
	int l;
	char chaine[100];
	char *grand = NULL;
	fread(&l, sizeof(int), 1, fichier);
	if (l < 100) {
		fread(chaine, sizeof(char) * (l + 1), 1, fichier);
		s = AnsiString(chaine);
	} else {
		grand = new char[l + 1];
		fread(grand, sizeof(char) * (l + 1), 1, fichier);
		s = AnsiString(grand);
	}
	s = s.Trim();
	if (grand)
		delete grand;
}
//------------------------------------------------------------------------------
void CL_ES::fwriteString(AnsiString s) {
	int l;
	s = s.Trim();
	l = s.Length();
	fwrite(&l, sizeof(int), 1, fichier);
	fwrite(s.c_str(), sizeof(char) * (l + 1), 1, fichier);
}
//------------------------------------------------------------------------------
void CL_ES::DefNoCategorie(CL_Vecteur<CL_Item> *vecteur) {
	CL_Item *item;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->NoCategorie = 0;
	}

}
//------------------------------------------------------------------------------
void CL_ES::DefNoCategorie108(CL_Vecteur<CL_Categorie> *vCat,
		CL_Vecteur<CL_Item> *vecteur) {
	int i, no, catNo;
	CL_Item *item;
	CL_Categorie *cat;
	int numero[100];
	vCat->NoX++;

	for (i = 0; i < 100; i++)
		numero[i] = -1;

	for (i = 0; i < vCat->Nbelt; i++) {
		cat = vCat->Vecteur[i];
		no = cat->No;
		numero[no] = i;
		cat->No = i;
	}

	for (i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		catNo = item->NoCategorie;
		if (numero[catNo] == -1)
			item->NoCategorie = 0;
		else
			item->NoCategorie = numero[catNo];
	}

}

/* ------------------------------------------------------------------------ */
/* bkp_fic()                                                       */
/* ------------------------------------------------------------------------ */
void CL_ES::BkpFic(void) {
	char nomFichier[MAXPATH];
	char bkpNom[MAXPATH];
	char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT];

	bool existe = false;
	strncpy(nomFichier, FEcriture.c_str(), MAXPATH);
// Construire le nom du fichier.BAK */
	fnsplit(nomFichier, drive, dir, name, ext);
	fnmerge(bkpNom, drive, dir, name, ".bak");

	if (FileExists(bkpNom))
		DeleteFile(bkpNom);
	CopyFile(nomFichier, bkpNom, existe);
}
//-------------------------------------------------------------------------
void CL_ES::LireLesDefSim(void) {
	int i;
	int nbelt;
	CL_Vecteur<CL_AgriDefSim> *vecteur;
	CL_AgriDefSim *defSim;

	vecteur = V_DefSim;
	fread(&nbelt, sizeof(int), 1, fichier);
	fread(&vecteur->NoX, sizeof(int), 1, fichier);
	//correction d'un bug  pour les versions jusqu'à 115 inclus
	//LireLesDefSim(void) ne sera plus utilisé après ???
	vecteur->Nbelt = 0;
	vecteur->NoX = 0;
	for (i = 0; i < nbelt; i++) {
		defSim = new CL_AgriDefSim();
		fread(&defSim->No, sizeof(int), 1, fichier);
		LireAgriDefSim(defSim);
//        vecteur->insSans(defSim);
	}
}
//-------------------------------------------------------------------------
void CL_ES::MajInvAni(void) {
	int i;
	int noX;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	CL_Item *item;
	///maj
	///V_InvAni contient des CL_InvAni
	/// CL_InvAni avait un pointeur sur CL_Atelier
	/// maintenant                  sur CL_Item NomAnimaux
	/// V_NomAnimaux n'existait pas
	/// je le cree en creant catgorie divers
	/// et en reprenant tous les noms de V_Animaux

	if (V_Animaux->Nbelt == 0)
		return;

	cat = new CL_Categorie();
	cat->No = 0;
	cat->Nom = "divers";
	V_CatBestiaux->insSans(cat);
	V_CatBestiaux->NoX = 1;

	noX = 0;
	for (i = 0; i < V_Animaux->Nbelt; i++) {
		atelier = V_Animaux->Vecteur[i];
		item = new CL_Item();
		item->No = atelier->No;
		item->Nom = atelier->Nom;
		item->NoCategorie = cat->No;
		item->Categorie = cat;
		item->Tva = TvaDefaut;
		item->NoTva = TvaDefaut->No;
		if (item->No > noX)
			noX = item->No;
		V_Bestiaux->insSans(item);
	}
	V_Bestiaux->NoX = noX + 1;
}

