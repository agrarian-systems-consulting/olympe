//-------------------------------- -------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
//#include "Brouillon.h"
//#include "ChoixCritere.h"
#include "AgriClasst.h"

//extern
#include "Olympe.hse"
#include "LesVecteurs.hse"

//------------------------------------------------------------------------------
bool CL_ES::ecrireFichier(void) {
	bool impFichier = false;
//StockagePermis=false;
	// on vient de modifier les données
	if (StockagePermis == false) {
		ShowMessage("ecrireFichier Supprimé");
		return true;
	}
/////////////!!!!!!!!!!!
//    ShowMessage("ecrireFichier");
	/// si on a ouvert olympe
	/// et pas lu de fichier
	/// et qu'on veut sortir alors ça planterait
	if (FEcriture.IsEmpty() == true)
		return false;

	fichier = fopen(FEcriture.c_str(), "wb");
	if (fichier == NULL) {
		MessageBox(0, "Verifier si le fichier n'est pas protégé en écriture",
				"IMPOSSIBLE", MB_ICONSTOP);
		return false;
	}

	fwrite(&Version, sizeof(int), 1, fichier);
	// SYSTEME UNITE///////////////////////
	EcrireSystemeUnite();
	EcrireTva();
	// produits charges
	EcrireCategorie(V_CatProduit);
	EcrireItem(V_Produit);

	EcrireCategorie(V_CatCharge);
	EcrireItem(V_Charge);

	// V_CatExternalite est standard cf main
	EcrireItem(V_Externalite);

	EcrireCategorie(V_CatBestiaux); //101201
	EcrireAnimaux(V_Bestiaux); //190802

	EcrireCategorie(V_CatCulture);
	EcrireCategorie(V_CatAnimaux);
	EcrireCategorie(V_CatVivrier);

	//nouveau 15 janvier 2001
	EcrireCategorie(V_CatChStruct);
	EcrireCategorie(V_CatRecDiv);
	EcrireCategorie(V_CatDepDiv);
	EcrireCategorie(V_CatRecFam);
	EcrireCategorie(V_CatDepFam);

	EcrireEspece();

	// Atelier
	EcrireAtelier(V_Culture);
	EcrireAtelier(V_Animaux);
	EcrireAtelier(V_Perenne);
	EcrireAtelier(V_Vivrier);

	// autres charges et recettes

	EcrireItem(V_ChStruct);
	EcrireItem(V_RecDiv);
	EcrireItem(V_DepDiv);
	EcrireItem(V_RecFam);
	EcrireItem(V_DepFam);

	// zone type exploitation
	EcrireCategorie(V_CatTypeZone);
	EcrireItem(V_TypeZone);
	EcrireLBCatCritere();

	// etatSortie  SerieComp indicateur variable

	EcrireCategorie(V_CatEtatSortie);
	EcrireEtatSortie(V_EtatSortie);

	EcrireCategorie(V_CatSerieComp);
	EcrireEtatSortie(V_SerieComp);

	EcrireCategorie(V_CatIndic);
	EcrireIndicateur();

	EcrireCategorie(V_CatVar);
	EcrireItem(V_Variable);

	EcrireCategorie(V_CatDico);
	EcrireItem(V_Dico);

	EcrireTendance(V_TendPrixProd); //prix
	EcrireTendance(V_TendPrixCharge);
	EcrireTendance(V_ScenPrixProd);
	EcrireTendance(V_ScenPrixCharge);

	//15 janvier 2001
	EcrireTendance(V_TendQProd);
	EcrireTendance(V_TendQCharge);
	EcrireTendance(V_ScenQProd);
	EcrireTendance(V_ScenQCharge);
	EcrireTendance(V_TendQExt);
	EcrireTendance(V_ScenQExt);

	//170801
	EcrireCalendrier();

	//180901
	EcrireConversion();
	//170903
	// TRESORERIE
	EcrireCategorie(V_CatRepart);
	EcrireRepart(V_Repart);

	// agriculteur
	EcrireAgriculteur();
	// Ensemble d'agriculteurs à simuler
	EcrireEnsemble();

	fwriteString(Notes);
//    EcrireLesDefSim();
	EcrireZero();
	fclose(fichier);

	// on vient de modifier les données

//    impFichier=true;
//    impFichier=false;
	if (impFichier == true) {
		ImpFichierAscii();
		//return 0;
	}

	LesAdresses();
	IniV_Elt();
	Supprimable();
//    V_Elt->purge();  c'est fait dans IniV_Elt
	return true;
}
//----------------------------------------------------------------------------
void CL_ES::EcrireSystemeUnite(void) {
	CL_SystemeUnite *sys;
	CL_Vecteur<CL_SystemeUnite> *vecteur;
	int nbelt, noX;
	int n;
	vecteur = V_SystemeUnite;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		sys = vecteur->Vecteur[i];
		sys->Flag = 'O';
		fwrite(&sys->No, sizeof(int), 1, fichier);
		fwriteString(sys->UUt);
		fwriteString(sys->UTrans);
		fwriteString(sys->UGlobal);
		fwrite(&sys->Ratio, sizeof(float), 1, fichier);
		fwrite(&sys->RatioG, sizeof(float), 1, fichier);
	}
//RUSTINE !!!!!!!!!
	if (SysMonnaie == NULL) {
		n = 0;
		fwrite(&n, sizeof(int), 1, fichier);
		return;
	}
	fwrite(&SysMonnaie->No, sizeof(int), 1, fichier);

}
//----------------------------------------------------------------------------
void CL_ES::EcrireTva(void) {
	CL_Tva *tva;
	CL_Vecteur<CL_Tva> *vecteur;
	int nbelt, noX;
	vecteur = V_Tva;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		tva = vecteur->Vecteur[i];
		tva->Flag = 'O';
		fwrite(&tva->No, sizeof(int), 1, fichier);
		fwriteString(tva->Nom);
		fwrite(&tva->Taux, sizeof(float), 1, fichier);
	}
//RUSTINE!!!!    
	if (TvaDefaut == NULL) {
		nbelt = 0;
		fwrite(&nbelt, sizeof(int), 1, fichier);
		fwrite(&nbelt, sizeof(int), 1, fichier);
		return;
	}
	fwrite(&TvaDefaut->No, sizeof(int), 1, fichier);
	fwrite(&TvaImmo->No, sizeof(int), 1, fichier);

}
//----------------------------------------------------------------------------
void CL_ES::EcrireCategorie(CL_Vecteur<CL_Categorie> *vecteur) {
	CL_Categorie *categorie;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		categorie = vecteur->Vecteur[i];
		categorie->Flag = 'O';
		fwrite(&categorie->No, sizeof(int), 1, fichier);
		fwriteString(categorie->Nom);
	}
}
//-------------------------------------------------------------------
void CL_ES::EcrireLBCatCritere(void) {
	int n, nX;
	TCheckListBox *lB;
	CL_Categorie *categorie;

	lB = AgriClasstFrm->ChLBCatTypeZone;
	nX = 0;
	for (n = 0; n < lB->Items->Count; n++) {
		if (lB->Checked[n] == true)
			nX++;
	}

	fwrite(&nX, sizeof(int), 1, fichier);
	for (n = 0; n < nX; n++) {
		if (lB->Checked[n] == false)
			continue;

		categorie = (CL_Categorie*) lB->Items->Objects[n];
		fwrite(&categorie->No, sizeof(int), 1, fichier);
	}
}
//-------------------------------------------------------------------
void CL_ES::EcrireItem(CL_Vecteur<CL_Item> *vecteur) {
	CL_Item *item;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Flag = 'O';
		fwrite(&item->No, sizeof(int), 1, fichier);
		fwriteString(item->Nom);
		fwrite(&item->NoCategorie, sizeof(int), 1, fichier);
		fwrite(&item->NoSysteme, sizeof(int), 1, fichier);
		fwrite(&item->NoTva, sizeof(int), 1, fichier);
		fwrite(&item->Prix, sizeof(float), 1, fichier);
	}

}
//-------------------------------------------------------------------
void CL_ES::EcrireAnimaux(CL_Vecteur<CL_Item> *vecteur) {
	CL_Item *item;
	int nbelt, noX;
	int i, n;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Flag = 'O';
		fwrite(&item->No, sizeof(int), 1, fichier);
		fwriteString(item->Nom);
		fwrite(&item->NoCategorie, sizeof(int), 1, fichier);
		fwrite(&item->NoOrigine, sizeof(int), 1, fichier); //190802

		fwrite(&item->NoTva, sizeof(int), 1, fichier);
		fwrite(&item->Prix, sizeof(float), 1, fichier);
		fwrite(&item->ValInv, sizeof(float), 1, fichier); //081003
		for (n = 0; n < 4; n++)
			fwrite(&item->DonneNo[n], sizeof(int), 1, fichier);
		for (int n = 0; n < 4; n++)
			fwrite(&item->DonnePcent[n], sizeof(float), 1, fichier);
	}

}
//-------------------------------------------------------------------------
void CL_ES::EcrireAtelier(CL_Vecteur<CL_Atelier> *vecteur) {
	CL_Atelier* atelier;
	int nbelt, noX;
	int derobe;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		atelier->Flag = 'O';
		fwrite(&atelier->No, sizeof(int), 1, fichier);
		fwriteString(atelier->Nom);
		fwrite(&atelier->Nature, sizeof(int), 1, fichier); //PERENNE CULTURE ANIMAUX VIVRIER
		fwrite(&atelier->NoEspece, sizeof(int), 1, fichier);
		fwrite(&atelier->NbPhase, sizeof(int), 1, fichier);
		fwrite(&atelier->NoCategorie, sizeof(int), 1, fichier);
		if (atelier->Derobe == true)
			derobe = 1; //250901
		else
			derobe = 0;
		fwrite(&derobe, sizeof(int), 1, fichier);
		fwriteString(atelier->Notes); //281101
		// produit
		EcrireAtelierItem(atelier->V_Produit, atelier->NbPhase);
		EcrireAtelierItem(atelier->V_Charge, atelier->NbPhase);
		EcrireAtelierItem(atelier->V_ChargeVolume, atelier->NbPhase);
		EcrireAtelierItem(atelier->V_Externalite, atelier->NbPhase);

		//avance
		EcrireAtelierAvance(atelier->V_Avance);

		//besoins en travail
		EcrireAtelierBesTrav(atelier->V_BesTrav); //280802

		//EcrireAtelierAvanceStock(atelier->V_Stock);//190802

		// debut et durée d'amortissement
		fwrite(&atelier->DebAmor, sizeof(int), 1, fichier);
		fwrite(&atelier->DurAmor, sizeof(int), 1, fichier);

		// production d'immo pour les pérennes et les autres si besoin
		fwrite(&atelier->PImmoExiste, sizeof(bool), 1, fichier);
		if (atelier->PImmoExiste == true)
			fwrite(atelier->ProdImmo, sizeof(float) * atelier->NbPhase, 1,
					fichier);
		fwrite(&atelier->PImmoFamExiste, sizeof(bool), 1, fichier);
		if (atelier->PImmoFamExiste == true)
			fwrite(atelier->ProdImmoFam, sizeof(float) * atelier->NbPhase, 1,
					fichier);
		// Valeur Inventaire      //220903
		fwrite(&atelier->ValInvRepro, sizeof(float), 1, fichier);
		fwrite(&atelier->ValInvAutre, sizeof(float), 1, fichier);

	}
}
//--------------------------------------------------------------------------
void CL_ES::EcrireAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteur,
		int nbPhase) {
	CL_ItemParAtelier* itemPA;
	int nbelt, noX;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		itemPA = vecteur->Vecteur[i];
		fwrite(&itemPA->No, sizeof(int), 1, fichier);
		fwrite(&itemPA->NoItem, sizeof(int), 1, fichier);
		fwrite(&itemPA->NoCharge, sizeof(int), 1, fichier);
		fwrite(&itemPA->NoItemPA, sizeof(int), 1, fichier);
		fwrite(itemPA->QtePhase, sizeof(float) * nbPhase, 1, fichier);
	}
}
//--------------------------------------------------------------------------
void CL_ES::EcrireAtelierAvance(CL_Vecteur<CL_EEF> *vecteur) {
	CL_EEF* eEF;
	int nbelt, noX;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		eEF = vecteur->Vecteur[i];
		fwrite(&eEF->Deb, sizeof(int), 1, fichier);
		fwrite(&eEF->Fin, sizeof(int), 1, fichier);
		fwrite(&eEF->Val, sizeof(float), 1, fichier);
	}
}
//--------------------------------------------------------------------------
void CL_ES::EcrireAtelierBesTrav(CL_Vecteur<CL_BesTrav> *vecteur) {
	CL_BesTrav* besTrav;
	int nbelt, noX;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		besTrav = vecteur->Vecteur[i];
		besTrav->ecrireFichier(fichier);
	}
}

//-------------------------------------------------------------------------
void CL_ES::EcrireEspece(void) {
	CL_Espece *espece;
	CL_Vecteur<CL_Espece> *vecteur;
	int nbelt, noX;

	vecteur = V_Espece;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		espece = vecteur->Vecteur[i];
		espece->Flag = 'O';
		fwrite(&espece->No, sizeof(int), 1, fichier);
		fwriteString(espece->Nom);
		fwrite(&espece->DebAmor, sizeof(int), 1, fichier);
		fwrite(&espece->DurAmor, sizeof(int), 1, fichier);
		fwrite(&espece->NbPhase, sizeof(int), 1, fichier);
		fwrite(espece->Phase, sizeof(int) * N_PHASE, 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireType(CL_Vecteur<CL_Item> *vecteur) {
	CL_Item *item;
	int nbelt, noX;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Flag = 'O';
		fwrite(&item->No, sizeof(int), 1, fichier);
		fwriteString(item->Nom);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireCalendrier(void) {
	int j;
	CL_Vecteur<CL_Calendrier> *vecteur = V_Calendrier;
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	int nbelt, noX;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		calendrier = vecteur->Vecteur[i];

		fwrite(&calendrier->No, sizeof(int), 1, fichier);
		fwriteString(calendrier->Nom);

		fwrite(&calendrier->V_Periode->Nbelt, sizeof(int), 1, fichier);
		fwrite(&calendrier->V_Periode->NoX, sizeof(int), 1, fichier);

		for (j = 0; j < calendrier->V_Periode->Nbelt; j++) {
			periode = calendrier->V_Periode->Vecteur[j];
			EcrirePeriode(periode);
		}
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrirePeriode(CL_Periode *periode) {
	fwrite(&periode->No, sizeof(int), 1, fichier);
	fwriteString(periode->Nom);
	fwrite(&periode->JDeb, sizeof(int), 1, fichier);
	fwrite(&periode->MDeb, sizeof(int), 1, fichier);
	fwrite(&periode->JFin, sizeof(int), 1, fichier);
	fwrite(&periode->MFin, sizeof(int), 1, fichier);
	fwrite(&periode->PcentDispo, sizeof(int), 1, fichier);
	fwrite(&periode->HpJ, sizeof(float), 1, fichier);
}
//-------------------------------------------------------------------------
void CL_ES::EcrireConversion(void) {
	int moinsUn = -1;
	CL_Vecteur<CL_Conversion> *vecteur = V_Conversion;
	CL_Conversion *conversion;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		conversion = vecteur->Vecteur[i];

		fwrite(&conversion->No, sizeof(int), 1, fichier);
		fwriteString(conversion->Nom);

		fwrite(&conversion->NoBase, sizeof(int), 1, fichier);
		fwrite(&conversion->NoSortie, sizeof(int), 1, fichier);
		fwrite(&conversion->APartirDe, sizeof(int), 1, fichier);

		fwrite(conversion->TauxConvFrancVersEuro, sizeof(float) * N_X, 1,
				fichier);
		fwrite(conversion->TauxConvEuroVersFranc, sizeof(float) * N_X, 1,
				fichier);
	}
	if (Conversion)
		fwrite(&Conversion->No, sizeof(int), 1, fichier);
	else
		fwrite(&moinsUn, sizeof(int), 1, fichier);

}
//---------------------------------------------------------------------------
void CL_ES::EcrireRepart(CL_Vecteur<CL_Repart> *vecteur) {
	int i;
	CL_Repart *repart;
	int nbelt, noX;

	vecteur = V_Repart;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (i = 0; i < nbelt; i++) {
		repart = vecteur->Vecteur[i];
		repart->FichierEcrire(fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriculteur(void) {
	int nCritere, nVariante;
	int moinsUn = -1;
	CL_Item *critere;
	ST_NoAgri *variante;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_Agriculteur> *vecteur;
	int nbelt, noX;
	vecteur = V_Agriculteur;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		agri = vecteur->Vecteur[i];

		fwrite(&agri->No, sizeof(int), 1, fichier);
		nCritere = agri->LstCritere->Count;
		fwrite(&nCritere, sizeof(int), 1, fichier);
		for (int n = 0; n < nCritere; n++) {
			critere = (CL_Item*) agri->LstCritere->Items[n];
			fwrite(&critere->No, sizeof(int), 1, fichier);
		}
		fwriteString(agri->Nom);

		EcrireAgriDefSim(agri->DefSim);

		fwriteString(agri->Notes);
		fwrite(&agri->EstVariante, sizeof(bool), 1, fichier);

		EcrireAgriValeur(agri->V_Culture);
		EcrireAgriValeur(agri->V_Animaux);

//        EcrireAgriInvAni(agri->V_InvAni,agri->LstMvtAni);  //11 06 00
		EcrireAgriTroupeau(agri->LstTroupeaux);

		EcrireAgriVerger(agri->V_Verger);
		EcrireAgriVerger(agri->V_Vivrier); //28 04 01
		EcrireAgriValeur(agri->V_Variable);

		EcrireAgriFormule(agri->V_Produits);
		EcrireAgriFormule(agri->V_Charges);
		EcrireAgriFormule(agri->V_ChStruct);

		EcrireAgriFormule(agri->V_RecDiv);
		EcrireAgriFormule(agri->V_DepDiv);
		EcrireAgriFormule(agri->V_RecFam);
		EcrireAgriFormule(agri->V_DepFam);

		EcrireAgriFormule(agri->V_ExtPos);
		EcrireAgriFormule(agri->V_ExtNeg);

		EcrireAgriEmpLT(agri->V_EmpLT);
		EcrireAgriEmpCT(agri->V_EmpCT);
		EcrireAgriSub(agri->V_Sub);
		EcrireAgriPlact(agri->V_Plact);
		EcrireAgriOccc(agri->V_Occc);

		EcrireAgriImmo(agri->V_Immo);
		EcrireAgriPetit(agri, agri->V_Petit);

		EcrireAgriFN_Xp1(agri->V_FinSom);
		EcrireAgriFN_Xp1(agri->V_InvSom);

		EcrireAgriCreanceDette(agri->V_Creance); //180102
		EcrireAgriCreanceDette(agri->V_Dette); //180102

		EcrireAgriPolStock(agri->V_PolStock); //190802
		EcrireAgriStockIni(agri->V_StockIni); //121201
		EcrireAgriVente(agri->LstQuantPrix); //210802

//		EcrireAgriItemRepart (agri->V_ItemRepart);            //180903
		EcrireAgriItemRepart(agri); //170604

		EcrireAgriTvaEntIni(agri->TvaEntIni); //130801
		fwrite(&agri->TresoIni, sizeof(float), 1, fichier); //130801

		nVariante = agri->LstVariante->Count;
		fwrite(&nVariante, sizeof(int), 1, fichier);
		for (int n = 0; n < nVariante; n++) {
			variante = (ST_NoAgri*) agri->LstVariante->Items[n];
			fwrite(&variante->No, sizeof(int), 1, fichier);
		}

	}
	if (AgriEnCours)
		fwrite(&AgriEnCours->No, sizeof(int), 1, fichier);
	else
		fwrite(&moinsUn, sizeof(int), 1, fichier);
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriDefSim(CL_AgriDefSim *defSim) {
	fwrite(&defSim->An_0, sizeof(int), 1, fichier);
	fwrite(&defSim->NbAnSim, sizeof(int), 1, fichier);
	fwrite(&defSim->MDeb, sizeof(int), 1, fichier);
	fwrite(&defSim->AnCalage, sizeof(int), 1, fichier);
	fwrite(&defSim->TypeAlea, sizeof(int), 1, fichier);

	fwrite(&defSim->NoPrixProd, sizeof(int), 1, fichier);
	fwrite(&defSim->NoPrixCharge, sizeof(int), 1, fichier);
	fwrite(&defSim->NoQProd, sizeof(int), 1, fichier);
	fwrite(&defSim->NoQCharge, sizeof(int), 1, fichier);
	fwrite(&defSim->NoQExt, sizeof(int), 1, fichier);

	fwrite(&defSim->TouSPrixProd, sizeof(int), 1, fichier);
	fwrite(&defSim->TouSPrixCharge, sizeof(int), 1, fichier);
	fwrite(&defSim->TouSQProd, sizeof(int), 1, fichier);
	fwrite(&defSim->TouSQCharge, sizeof(int), 1, fichier);
	fwrite(&defSim->TouSQExt, sizeof(int), 1, fichier);

	fwrite(&defSim->Enchainement, sizeof(char) * (N_X + 1), 1, fichier);
//ShowMessage(defSim->Enchainement);

}

//-------------------------------------------------------------------------
void CL_ES::EcrireAgriValeur(CL_Vecteur<CL_Valeur> *vecteur) {
	CL_Valeur* valeur;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		fwrite(&valeur->No, sizeof(int), 1, fichier);
		fwrite(&valeur->NoAtelier, sizeof(int), 1, fichier);
		fwrite(&valeur->NoItem, sizeof(int), 1, fichier);
		fwrite(valeur->Valeur, sizeof(float) * N_X, 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriInvAni(CL_Vecteur<CL_InvAni> *vecteur, TList *lstMvtAni) //11 06 00
		{
	int i, nbListe;
	CL_InvAni *invAni;
	CL_MvtAni *mvtAni;
	int nbelt, noX;

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		invAni = vecteur->Vecteur[i];
		fwrite(&invAni->No, sizeof(int), 1, fichier);
		fwrite(&invAni->NoAnimal, sizeof(int), 1, fichier);
		fwrite(&invAni->Reproducteur, sizeof(char), 1, fichier); //260903

		fwrite(&invAni->PrixVenteMoy, sizeof(invAni->PrixVenteMoy), 1, fichier); //260903
		fwrite(&invAni->ValInvMoy, sizeof(invAni->ValInvMoy), 1, fichier); //260903
//		fwrite(&invAni->ValInv, sizeof(float),1,fichier);   //260903  supprime 0031003
		fwrite(invAni->Effectif, sizeof(float) * N_X, 1, fichier); //091002
		fwrite(invAni->Valeur, sizeof(float) * (N_X + 1), 1, fichier); //180903
		fwrite(invAni->Vente, sizeof(float) * N_X, 1, fichier); //091002
		fwrite(invAni->Achat, sizeof(float) * N_X, 1, fichier); //091002
		fwrite(invAni->ValVente, sizeof(float) * N_X, 1, fichier);
		fwrite(invAni->ValAchat, sizeof(float) * N_X, 1, fichier);
		fwrite(invAni->EffMax, sizeof(float) * N_X, 1, fichier); //180903
		fwrite(invAni->NoAtelier, sizeof(invAni->NoAtelier), 1, fichier); //190903

	}
	if (vecteur->Nbelt == 0)
		return;

	nbListe = lstMvtAni->Count;
	fwrite(&nbListe, sizeof(int), 1, fichier);
	for (i = 0; i < lstMvtAni->Count; i++) {
		mvtAni = (CL_MvtAni*) lstMvtAni->Items[i];
		fwrite(&mvtAni->NoAnimal, sizeof(int), 1, fichier);
		fwrite(&mvtAni->Date, sizeof(int), 1, fichier);
		fwrite(&mvtAni->Type, sizeof(int), 1, fichier);
		fwrite(&mvtAni->Eff, sizeof(int), 1, fichier);
		fwrite(&mvtAni->Info, sizeof(float), 1, fichier);
	}

}
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
void CL_ES::EcrireAgriFormule(CL_Vecteur<CL_Formule> *vecteur) {
	CL_Formule *formule;
	CL_Prog *prog, *progN;
	int leProgDe[N_X];
	bool estEcrit[N_X];
	int n, j;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		formule = vecteur->Vecteur[i];
		fwrite(&formule->No, sizeof(int), 1, fichier); //c'est le n° de l'item
		fwrite(&formule->NoFamille, sizeof(int), 1, fichier);
		fwrite(formule->Valeur, sizeof(float) * N_X, 1, fichier);
		fwrite(&formule->Origine, sizeof(char), 1, fichier);

		for (n = 0; n < N_X; n++)
			estEcrit[n] = false;

		for (n = 0; n < N_X; n++) {
			if (estEcrit[n] == true)
				continue;

			prog = formule->LesProg[n];
			if (prog == NULL) //continue;
					{
				for (j = 0; j < N_X; j++)
					leProgDe[j] = 0;

				leProgDe[0] = -1;
				for (j = n; j < N_X; j++) {
					if (formule->LesProg[j] == NULL) {
						leProgDe[j] = -1;
						estEcrit[j] = true;
					}
				}
				fwrite(leProgDe, sizeof(int) * N_X, 1, fichier);
				continue;
			}

			for (j = 0; j < N_X; j++)
				leProgDe[j] = 0;
			for (j = n; j < N_X; j++) {
				progN = formule->LesProg[j];
				if (prog == progN)
				//if(formule->LesProg[j]==prog)
						{
					leProgDe[j] = 1;
					estEcrit[j] = true;
				}
			}
			fwrite(leProgDe, sizeof(int) * N_X, 1, fichier);
			ecrireArbre(prog->Arbre);
			ecrireReseau(prog->Reseau);
		}
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriTroupeau(TList *lstTroupeaux) {
	int n;
	CL_Troupeau *troupeau;
	n = lstTroupeaux->Count;
	fwrite(&n, sizeof(int), 1, fichier);
	for (n = 0; n < lstTroupeaux->Count; n++) {
		troupeau = (CL_Troupeau*) lstTroupeaux->Items[n];
		fwrite(&troupeau->NoCatBestiaux, sizeof(int), 1, fichier);
		EcrireAgriInvAni(troupeau->V_InvAni, troupeau->LstMvtAni); //11 06 00
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriVerger(CL_Vecteur<CL_Verger> *vecteur) {
	CL_Verger* verger;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		verger = vecteur->Vecteur[i];
		fwrite(&verger->No, sizeof(int), 1, fichier);
		fwrite(&verger->NoAtelier, sizeof(int), 1, fichier);
		fwrite(&verger->NoEspece, sizeof(int), 1, fichier);
		fwrite(&verger->AnPlant, sizeof(int), 1, fichier);
		fwrite(&verger->AnArr, sizeof(int), 1, fichier);
		fwrite(&verger->Surface, sizeof(float), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriEmpLT(CL_Vecteur<CL_EmpLT> *vecteur) {
	CL_EmpLT* empLT;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		empLT = vecteur->Vecteur[i];
		fwrite(&empLT->No, sizeof(int), 1, fichier);
		fwriteString(empLT->Nom);
		fwrite(&empLT->Montant, sizeof(float), 1, fichier);
		fwrite(&empLT->Duree, sizeof(int), 1, fichier);
		fwrite(&empLT->Duree2, sizeof(int), 1, fichier);
		fwrite(&empLT->Taux, sizeof(float), 1, fichier);
		fwrite(&empLT->Taux2, sizeof(float), 1, fichier);
		fwriteString(empLT->Type);
		fwrite(&empLT->AReal, sizeof(int), 1, fichier);
		fwrite(&empLT->MReal, sizeof(int), 1, fichier);
		fwrite(&empLT->ARemb, sizeof(int), 1, fichier);
		fwrite(&empLT->MRemb, sizeof(int), 1, fichier);
		fwrite(&empLT->Pour, sizeof(char), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriEmpCT(CL_Vecteur<CL_EmpCT> *vecteur) {
	CL_EmpCT* empCT;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		empCT = vecteur->Vecteur[i];
		fwrite(&empCT->No, sizeof(int), 1, fichier);
		fwriteString(empCT->Nom);
		fwrite(&empCT->Montant, sizeof(float), 1, fichier);
		fwrite(&empCT->Taux, sizeof(float), 1, fichier);
		fwriteString(empCT->Type);
		fwrite(&empCT->AReal, sizeof(int), 1, fichier);
		fwrite(&empCT->MReal, sizeof(int), 1, fichier);
		fwrite(&empCT->ARemb, sizeof(int), 1, fichier);
		fwrite(&empCT->MRemb, sizeof(int), 1, fichier);
		fwrite(&empCT->Pour, sizeof(char), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriSub(CL_Vecteur<CL_Sub> *vecteur) {
	CL_Sub* sub;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		sub = vecteur->Vecteur[i];
		fwrite(&sub->No, sizeof(int), 1, fichier);
		fwriteString(sub->Nom);
		fwrite(&sub->Montant, sizeof(float), 1, fichier);
		fwrite(&sub->AReal, sizeof(int), 1, fichier);
		fwrite(&sub->MReal, sizeof(int), 1, fichier);
		fwrite(&sub->Duree, sizeof(int), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriPlact(CL_Vecteur<CL_Plact> *vecteur) {
	CL_Plact* plact;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		plact = vecteur->Vecteur[i];
		fwrite(&plact->No, sizeof(int), 1, fichier);
		fwriteString(plact->Nom);
		fwrite(&plact->Montant, sizeof(float), 1, fichier);
		fwrite(&plact->Taux, sizeof(float), 1, fichier);
		fwrite(&plact->Type, sizeof(char), 1, fichier);
		fwrite(&plact->AReal, sizeof(int), 1, fichier);
		fwrite(&plact->MReal, sizeof(int), 1, fichier);
		fwrite(&plact->ATerme, sizeof(int), 1, fichier);
		fwrite(&plact->MTerme, sizeof(int), 1, fichier);
		fwrite(&plact->Pour, sizeof(char), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriOccc(CL_Vecteur<CL_Occc> *vecteur) {
	CL_Occc* occc;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		occc = vecteur->Vecteur[i];
		fwrite(&occc->No, sizeof(int), 1, fichier);
		fwrite(&occc->Ex, sizeof(int), 1, fichier);
		fwrite(&occc->Montant, sizeof(float), 1, fichier);
		fwrite(&occc->Taux, sizeof(float), 1, fichier);
		fwrite(&occc->Pcent, sizeof(float), 1, fichier);
		fwrite(&occc->Frais, sizeof(float), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriImmo(CL_Vecteur<CL_Immo> *vecteur) {
	CL_Immo* immo;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		immo = vecteur->Vecteur[i];
		fwrite(&immo->No, sizeof(int), 1, fichier);
		fwriteString(immo->Nom);
		fwrite(&immo->ValAchat, sizeof(float), 1, fichier);
		fwrite(&immo->AAchat, sizeof(int), 1, fichier);
		fwrite(&immo->MAchat, sizeof(int), 1, fichier);
		fwrite(&immo->AVente, sizeof(int), 1, fichier);
		fwrite(&immo->MVente, sizeof(int), 1, fichier);
		fwrite(&immo->TypeAmor, sizeof(char), 1, fichier);
		fwrite(&immo->Duree, sizeof(int), 1, fichier);
		fwrite(&immo->ValVente, sizeof(float), 1, fichier);
		fwrite(&immo->NoTva, sizeof(int), 1, fichier);
		// lecture trouver Tva
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriPetit(CL_Agriculteur *agri,
		CL_Vecteur<CL_Petit> *vecteur) {
	CL_Petit * petit;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		petit = vecteur->Vecteur[i];
		fwrite(&petit->No, sizeof(int), 1, fichier);
		fwrite(&petit->NoRepart, sizeof(int), 1, fichier);
		fwrite(&petit->ValAchat, sizeof(float), 1, fichier);
		fwrite(&petit->NoTva, sizeof(int), 1, fichier);
		// lecture trouver Tva
	}
}
// FN_Xp1 est une classe qu contient un vecteur de float de N_X+1
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriFN_Xp1(CL_Vecteur<CL_FN_Xp1> *vecteur) {
	CL_FN_Xp1 *fN_Xp1;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		fN_Xp1 = vecteur->Vecteur[i];
		fwrite(&fN_Xp1->No, sizeof(int), 1, fichier);
		fwrite(&fN_Xp1->Valeur, sizeof(float) * (N_X + 1), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriCreanceDette(CL_Vecteur<CL_EnCours> *vecteur) {
	CL_EnCours *enCours;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		enCours = vecteur->Vecteur[i];
		fwrite(&enCours->No, sizeof(int), 1, fichier);
		fwrite(&enCours->NoFamille, sizeof(int), 1, fichier);
		fwrite(&enCours->NoItem, sizeof(int), 1, fichier);
		fwrite(&enCours->EnStock, sizeof(char), 1, fichier);
		fwrite(&enCours->Valeur, sizeof(float), 1, fichier);
		fwrite(&enCours->APaie, sizeof(int), 1, fichier);
		fwrite(&enCours->MPaie, sizeof(int), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriPolStock(CL_Vecteur<CL_PolStock> *vecteur) {
	CL_PolStock *polStock;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		polStock = vecteur->Vecteur[i];
		polStock->EcrireFichier(fichier);
	}
}
//-------------------------------------------------------------------------
//void CL_ES::EcrireAgriItemRepart (CL_Vecteur<CL_ItemRepart> *vecteur)
void CL_ES::EcrireAgriItemRepart(CL_Agriculteur *agri) //170604
		{
	CL_Vecteur<CL_ItemRepart> *vecteur = agri->V_ItemRepart;
	CL_ItemRepart *itemRepart;
	int nbelt, noX;
	int possibOcPlactExiste;
	int noRepartDefaut; //a mettre dans CL_Agri

	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		itemRepart = vecteur->Vecteur[i];
		itemRepart->EcrireFichier(fichier);
	}
	if (V_Repart->Nbelt == 0) //treso non utilisée
		return;

	noRepartDefaut = 5; //!!!!!!!!
	fwrite(&noRepartDefaut, sizeof(int), 1, fichier);

	if (agri->PossibOcPlact) {
		possibOcPlactExiste = 1;
		fwrite(&possibOcPlactExiste, sizeof(int), 1, fichier);
		agri->PossibOcPlact->EcrireFichier(fichier);
	} else {
		possibOcPlactExiste = 0;
		fwrite(&possibOcPlactExiste, sizeof(int), 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriStockIni(CL_Vecteur<CL_StockIni> *vecteur) {
	CL_StockIni *stock;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		stock = vecteur->Vecteur[i];
		fwrite(&stock->No, sizeof(int), 1, fichier);
		fwrite(&stock->NoItem, sizeof(int), 1, fichier);
		fwrite(stock->Quantite, sizeof(float) * N_X, 1, fichier);
		fwrite(stock->PrixRevient, sizeof(float) * N_X, 1, fichier);
	}
}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriVente(TList *lstQuantPrix) {
	int n;
	CL_QuantPrix *quantPrix;
	n = lstQuantPrix->Count;
	fwrite(&n, sizeof(int), 1, fichier);
	for (n = 0; n < lstQuantPrix->Count; n++) {
		quantPrix = (CL_QuantPrix *) lstQuantPrix->Items[n];
		quantPrix->EcrireFichier(fichier);
	}
}

//-------------------------------------------------------------------------
void CL_ES::EcrireAgriTvaEntIni(CL_TvaEntIni *tvaIni) {
	fwrite(&tvaIni->Recu, sizeof(float), 1, fichier);
	fwrite(&tvaIni->Verse, sizeof(float), 1, fichier);
	fwrite(&tvaIni->AcompteAout, sizeof(float), 1, fichier);
	fwrite(&tvaIni->AcompteNov, sizeof(float), 1, fichier);
	fwrite(&tvaIni->AcompteFev, sizeof(float), 1, fichier);
	fwrite(&tvaIni->AcompteMai, sizeof(float), 1, fichier);
}
//-------------------------------------------------------------------------
void CL_ES::EcrireEnsemble(void) {
	int j;
	int moinsUn = -1;
	CL_Ensemble *ensemble;
	CL_AgriEff *agriEff;
	CL_Vecteur<CL_Ensemble> *vecteur;
	int nVariante;
	ST_NoEnsemble *variante;
	int nbelt, noX;
//CL_Vecteur<CL_AgriEff>  *vAgriEff;
	vecteur = V_Ensemble;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		ensemble = vecteur->Vecteur[i];
		fwrite(&ensemble->No, sizeof(int), 1, fichier);
		fwriteString(ensemble->Nom);
		fwriteString(ensemble->Notes);

		fwrite(&ensemble->V_AgriEff->Nbelt, sizeof(int), 1, fichier);
		fwrite(&ensemble->V_AgriEff->NoX, sizeof(int), 1, fichier);
		for (j = 0; j < ensemble->V_AgriEff->Nbelt; j++) {
			agriEff = ensemble->V_AgriEff->Vecteur[j];
			EcrireAgriEff(agriEff);
		}
		nVariante = ensemble->LstVariante->Count;
		fwrite(&nVariante, sizeof(int), 1, fichier);
		for (int n = 0; n < nVariante; n++) {
			variante = (ST_NoEnsemble*) ensemble->LstVariante->Items[n];
			fwrite(&variante->No, sizeof(int), 1, fichier);
		}
	}
	if (EnsembleEnCours)
		fwrite(&EnsembleEnCours->No, sizeof(int), 1, fichier);
	else
		fwrite(&moinsUn, sizeof(int), 1, fichier);

}
//-------------------------------------------------------------------------
void CL_ES::EcrireAgriEff(CL_AgriEff *agriEff) {
	CL_Agriculteur *agri;
	agri = agriEff->Agri;
	fwrite(&agri->No, sizeof(int), 1, fichier);
	fwrite(agriEff->Effectif, sizeof(int) * N_X, 1, fichier);

}
//-------------------------------------------------------------------------
void CL_ES::EcrireEtatSortie(CL_Vecteur<CL_EtatSortie> *v_Etat) {
	int l;
	CL_EtatSortie *etat;
	CL_Elt *elt;
	CL_Vecteur<CL_Elt> *vecteur;
	int nbelt, noX;
	nbelt = v_Etat->Nbelt;
	noX = v_Etat->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		etat = v_Etat->Vecteur[i];
		fwriteString(etat->Nom);
		fwrite(&etat->No, sizeof(int), 1, fichier);
		fwrite(&etat->NoCategorie, sizeof(int), 1, fichier);

		vecteur = etat->V_Elt;
		fwrite(&vecteur->Nbelt, sizeof(int), 1, fichier);
		fwrite(&vecteur->NoX, sizeof(int), 1, fichier);

		for (int j = 0; j < vecteur->Nbelt; j++) {
			elt = vecteur->Vecteur[j];
			fwrite(&elt->No, sizeof(int), 1, fichier);
			fwrite(&elt->NoFamille, sizeof(int), 1, fichier);
			fwrite(&elt->NoCategorie, sizeof(int), 1, fichier);
			fwrite(&elt->NoItem, sizeof(int), 1, fichier);
			if (elt->NoItem == TITRE) {
				l = strlen(elt->Nom) + 1;
				fwrite(&l, sizeof(int), 1, fichier);
				fwrite(elt->Nom, sizeof(char) * (l), 1, fichier);
			}
		}
	}
}
//----------------------------------------------------------------------------
void CL_ES::EcrireIndicateur(void) {
	CL_Indicateur *indicateur;
	int nbelt, noX;
	nbelt = V_Indicateur->Nbelt;
	noX = V_Indicateur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		indicateur = V_Indicateur->Vecteur[i];
		fwriteString(indicateur->Nom);
		fwrite(&indicateur->No, sizeof(int), 1, fichier);
		fwrite(&indicateur->NoCategorie, sizeof(int), 1, fichier);
		fwrite(&indicateur->type, sizeof(int), 1, fichier);
		fwrite(&indicateur->NoSysteme, sizeof(int), 1, fichier); //101003
		ecrireArbre(indicateur->Prog->Arbre);
		ecrireReseau(indicateur->Prog->Reseau);
	}
}
//----------------------------------------------------------------------------
void CL_ES::ecrireArbre(CL_Arbre *Arbre) {
	int n;
	int zero = 0;
	if (Arbre == NULL) {
		fwrite(&zero, sizeof(int), 1, fichier);
		return;
	}

	fwrite(&Arbre->BrancheX, sizeof(int), 1, fichier);
	for (n = 0; n < Arbre->BrancheX; n++)
		fwrite(&Arbre->LesBranches[n], sizeof(ST_Branche), 1, fichier);
}
//----------------------------------------------------------------------------
void CL_ES::ecrireReseau(CL_Reseau *Reseau) {
	int n;
	int zero = 0;
	if (Reseau == NULL) {
		fwrite(&zero, sizeof(int), 1, fichier);
		return;
	}

	fwrite(&Reseau->MailleX, sizeof(int), 1, fichier);
	for (n = 0; n < Reseau->MailleX; n++)
		fwrite(&Reseau->LesMailles[n], sizeof(ST_Maille), 1, fichier);
}
//----------------------------------------------------------------------------
void CL_ES::EcrireZero(void) {
// pour preparer lecture des nouveautés
	int n = 0;
	fwrite(&n, sizeof(int), 1, fichier);
}
//----------------------------------------------------------------------------
void CL_ES::EcrireTendance(CL_Vecteur<CL_Tendance> *vecteur) {
	CL_Tendance* tendance;
	CL_Delta* delta;
	CL_Vecteur<CL_Delta> *vDelta;
	int nbelt, noX;
	nbelt = vecteur->Nbelt;
	noX = vecteur->NoX;
	fwrite(&nbelt, sizeof(int), 1, fichier);
	fwrite(&noX, sizeof(int), 1, fichier);
	for (int i = 0; i < nbelt; i++) {
		tendance = vecteur->Vecteur[i];
		fwrite(&tendance->No, sizeof(int), 1, fichier);
		fwriteString(tendance->Nom);

		vDelta = tendance->V_Delta;
		fwrite(&vDelta->Nbelt, sizeof(int), 1, fichier);
		fwrite(&vDelta->NoX, sizeof(int), 1, fichier);
		for (int j = 0; j < vDelta->Nbelt; j++) {
			delta = vDelta->Vecteur[j];
			fwrite(&delta->No, sizeof(int), 1, fichier);
			fwrite(&delta->NoItem, sizeof(int), 1, fichier);
			fwrite(&delta->NoAtelier, sizeof(int), 1, fichier);
			fwrite(&delta->Nature, sizeof(int), 1, fichier);
			for (int k = 0; k < N_X; k++)
				fwrite(&delta->Pcent[k], sizeof(float), 1, fichier);
		}
	}
}
/*
 //-------------------------------------------------------------------------
 void CL_ES::EcrireLesDefSim(void)
 {
 int i;
 CL_Vecteur<CL_AgriDefSim> *vecteur;
 CL_AgriDefSim *defSim;
 int nbelt,noX;

 vecteur=V_DefSim;
 nbelt=vecteur->Nbelt;
 noX=vecteur->NoX;
 fwrite(&nbelt,sizeof(int),1,fichier);
 fwrite(&noX,sizeof(int),1,fichier);
 for(int i=0;i<nbelt;i++)
 {
 defSim=vecteur->Vecteur[i];
 fwrite(&defSim->No,sizeof(int),1,fichier);
 EcrireAgriDefSim(defSim);
 }
 }
 */
