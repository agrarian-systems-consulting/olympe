//----------------------  -----------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <Grids.hpp>

#include <vcl\dstring.h>
#pragma hdrstop

#include "Olympedec.h"

#include "LesClassesApp.h"
#include "Cl_PossibOcPlact.h"

#include "LesVecteurs.hse"
//#include "Brouillon.h"
#include "FichierLire.h"
#include "Compilateur.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//      dcnnees.cpp
//
//extern CL_ES *ES;
extern CL_Compil *Compil;

//-----------------------------------------------------------
CL_SystemeUnite::CL_SystemeUnite(char *uUt, char *uTrans, char *uGlobal,
		float ratio, float ratioG) {
	UUt = uUt;
	UTrans = uTrans;
	UGlobal = uGlobal;
	Ratio = ratio;
	RatioG = ratioG;

}
//-----------------------------------------------------------
CL_TvaEnt::CL_TvaEnt() {
	MaZ();
}
void CL_TvaEnt::MaZ(void) {
	memset(Recu, 0, sizeof(float) * N_X);
	memset(Verse, 0, sizeof(float) * N_X);
	memset(AcompteAout, 0, sizeof(float) * N_X);
	memset(AcompteNov, 0, sizeof(float) * N_X);
	memset(AcompteFev, 0, sizeof(float) * N_X);
	memset(AcompteMai, 0, sizeof(float) * N_X);
	memset(RembTva, 0, sizeof(float) * N_X);
	memset(Regul, 0, sizeof(float) * N_X);
	memset(Solde, 0, sizeof(float) * N_X);
}

CL_TvaEnt::CL_TvaEnt(CL_TvaEnt *source) {
	memcpy(Recu, source->Recu, sizeof(float) * N_X);
	memcpy(Verse, source->Verse, sizeof(float) * N_X);
	memcpy(AcompteAout, source->AcompteAout, sizeof(float) * N_X);
	memcpy(AcompteNov, source->AcompteNov, sizeof(float) * N_X);
	memcpy(AcompteFev, source->AcompteFev, sizeof(float) * N_X);
	memcpy(AcompteMai, source->AcompteMai, sizeof(float) * N_X);
	memcpy(RembTva, source->RembTva, sizeof(float) * N_X);
	memcpy(Regul, source->Regul, sizeof(float) * N_X);
	memcpy(Solde, source->Solde, sizeof(float) * N_X);
}

CL_TvaEntIni::CL_TvaEntIni() {
	Recu = 0;
	Verse = 0;
	AcompteAout = 0;
	AcompteNov = 0;
	AcompteFev = 0;
	AcompteMai = 0;
	Regul = 0;
}
//-----------------------------------------------------------
CL_TvaEntIni::CL_TvaEntIni(CL_TvaEntIni* ptr) {
	Recu = ptr->Recu;
	Verse = ptr->Verse;
	AcompteAout = ptr->AcompteAout;
	AcompteNov = ptr->AcompteNov;
	AcompteFev = ptr->AcompteFev;
	AcompteMai = ptr->AcompteMai;
	Regul = ptr->Regul;
}
//-----------------------------------------------------------
CL_ItemRepart::CL_ItemRepart() {
	No = 0;
	NoItem = 0;
	Famille = 0;
	memset(LesNoRepartQ, -1, sizeof(LesNoRepartQ));
	for (int i = 0; i < N_X; i++)
		LesRepartQ[i] = NULL;
	memset(LesNoRepartV, -1, sizeof(LesNoRepartV));
	for (int i = 0; i < N_X; i++)
		LesRepartV[i] = NULL;
	Flag = ' ';
}
//-----------------------------------------------------------
CL_ItemRepart::CL_ItemRepart(int noItem, int famille) {
	No = 0;
	NoItem = noItem; //le n° de l'item
	Famille = famille;
	memset(LesNoRepartQ, -1, sizeof(LesNoRepartQ));
	for (int i = 0; i < N_X; i++)
		LesRepartQ[i] = NULL;
	memset(LesNoRepartV, -1, sizeof(LesNoRepartV));
	for (int i = 0; i < N_X; i++)
		LesRepartV[i] = NULL;
	Flag = ' ';
}
//-----------------------------------------------------------
CL_ItemRepart::CL_ItemRepart(CL_ItemRepart *source) {
	No = 0;
	NoItem = source->NoItem; //le n° de l'item
	Famille = source->Famille;
	memcpy(LesNoRepartQ, source->LesNoRepartQ, sizeof(LesNoRepartQ));
	memcpy(LesRepartQ, source->LesRepartQ, sizeof(LesRepartQ));
	memcpy(LesNoRepartV, source->LesNoRepartV, sizeof(LesNoRepartV));
	memcpy(LesRepartV, source->LesRepartV, sizeof(LesRepartV));
	Flag = ' ';
}
//---------------------------------------------------------------------------
void CL_ItemRepart::EcrireFichier(FILE *fichier) {
	fwrite(&NoItem, sizeof(int), 1, fichier);
	fwrite(&Famille, sizeof(int), 1, fichier);
	fwrite(LesNoRepartQ, sizeof(LesNoRepartQ), 1, fichier);
	fwrite(LesNoRepartV, sizeof(LesNoRepartV), 1, fichier);
}
//---------------------------------------------------------------------------
void CL_ItemRepart::LireFichier(FILE *fichier) {
	int i;
	fread(&NoItem, sizeof(int), 1, fichier);
	fread(&Famille, sizeof(int), 1, fichier);
	fread(LesNoRepartQ, sizeof(LesNoRepartQ), 1, fichier);
	fread(LesNoRepartV, sizeof(LesNoRepartV), 1, fichier);
	for (i = 0; i < N_X; i++) {
		if (LesNoRepartQ[i] != -1)
			LesRepartQ[i] = V_Repart->trouve(LesNoRepartQ[i]);
		if (LesNoRepartV[i] != -1)
			LesRepartV[i] = V_Repart->trouve(LesNoRepartV[i]);
	}
}

//-----------------------------------------------------------
CL_QuanVal::CL_QuanVal() {
	No = 0; //le n° de l'item
	Item = NULL;
	Categorie = NULL; //100401
	memset(Qte, 0, sizeof(float) * N_X);
	memset(Val, 0, sizeof(float) * N_X);
	memset(Stock, 0, sizeof(float) * (N_X + 1));
	ItemRepart = NULL;
	Flag = ' ';
}
//-----------------------------------------------------------
CL_QuanVal::CL_QuanVal(int nature) {
	No = 0; //le n° de l'item
	Item = NULL;
	Categorie = NULL; //100401
	memset(Qte, 0, sizeof(float) * N_X);
	memset(Val, 0, sizeof(float) * N_X);
	memset(Stock, 0, sizeof(float) * (N_X + 1));
	Flag = ' ';
	ItemRepart = new CL_ItemRepart();
	Item = new CL_Item();
	if (nature == PETITMAT) {
		Item->Nom = "Petit Matériel";
		Item->Tva = TvaImmo;
	}
}
//-----------------------------------------------------------
CL_QuanVal::CL_QuanVal(CL_QuanVal *source) {
	No = source->No; //le n° de l'item
	Item = source->Item;
	Categorie = source->Categorie;
	memcpy(Qte, source->Qte, sizeof(float) * N_X);
	memcpy(Val, source->Val, sizeof(float) * N_X);
	memcpy(Stock, source->Stock, sizeof(float) * (N_X + 1));
	ItemRepart = source->ItemRepart;
	Flag = ' ';
}
//-----------------------------------------------------------
CL_Categorie::CL_Categorie(AnsiString nom, int no) {
	Nom = nom;
	No = no;
	Supprimable = false;
	Notes = "";
}
//--------------------------------------------------------------------------
int CL_Categorie::Cmp(CL_Categorie *cat) {
	return (Nom.AnsiCompare(cat->Nom));
}
//---------------------------------------------------------------------------
int CL_SystemeUnite::Cmp(CL_SystemeUnite *ptr) {
	int n;
	n = UUt.AnsiCompare(ptr->UUt);
	if (n != 0)
		return n;

	else
		return (UTrans.AnsiCompare(ptr->UTrans));

}
//---------------------------------------------------------------------------
CL_Item::CL_Item() {
	int n;
	Categorie = NULL;
	SysUnite = NULL;
	Tva = NULL;
	Supprimable = true;
	Prix = 0;
	NoCategorie = -1;
	NoSysteme = -1;
	NoTva = -1;
	NoOrigine = -1;
	for (n = 0; n < 4; n++) {
		DonneNo[n] = 0; //                  060103
		DonnePcent[n] = 0;
	}
	ValInv = 0;
}
//---------------------------------------------------------------------------
CL_Item::CL_Item(CL_Item *anc) {
	int n;
	Nom = anc->Nom;
	Categorie = anc->Categorie;
	SysUnite = anc->SysUnite;
	Tva = anc->Tva;
	Supprimable = true;
	Prix = anc->Prix;
	NoCategorie = anc->NoCategorie;
	NoSysteme = anc->NoSysteme;
	NoTva = anc->NoTva;
	NoOrigine = anc->NoOrigine;
	for (n = 0; n < 4; n++) {
		DonneNo[n] = anc->DonneNo[n]; //                  060103
		DonnePcent[n] = anc->DonnePcent[n];
	}
	ValInv = anc->ValInv;
}
//---------------------------------------------------------------------------
int CL_Item::Cmp(CL_Item *ptr) {
	int n;
	CL_Categorie *cat0, *cat1;
	cat0 = V_Categorie->trouve(NoCategorie);
	cat1 = V_Categorie->trouve(ptr->NoCategorie);
	n = cat0->Nom.AnsiCompare(cat1->Nom);
	if (n != 0)
		return n;
	return Nom.AnsiCompare(ptr->Nom);

}
//---------------------------------------------------------------------------
CL_ItemParAtelier::CL_ItemParAtelier() {
	Item = NULL;
	ItemPA = NULL; //pour les charges proportionnelles au volume   no_produit!=-1
	Charge = NULL;
	No = 0;
	NoItem = 0;
	NoCharge = 0;
	NoItemPA = 0; //pour les charges proportionnelles au volume
	Qte = 0;
	QtePhase = NULL;
}
//---------------------------------------------------------------------------
CL_ItemParAtelier::~CL_ItemParAtelier(void) {
	if (QtePhase) {
		delete QtePhase;
		QtePhase = NULL;
	}
}
//---------------------------------------------------------------------------
CL_Espece::CL_Espece() {
	No = 0;
	Nom = "";
	memset(Phase, 0, sizeof(Phase));
	DebAmor = 0;
	DurAmor = 0;
	NbPhase = 0;
	Supprimable = true;
}
// entier entier flottant
//-------------------------------------------------------------
CL_EEF::CL_EEF() {
	Deb = 0;
	Fin = 0;
	Val = 0;
}
/*
 //-------------------------------------------------------------
 CL_EEF::CL_EEF(int deb,int fin, float val )
 {
 Deb=deb;
 Fin=fin;
 Val=val;
 }
 */
//-------------------------------------------------------------
CL_EEF::CL_EEF(CL_EEF *eef) {
	Deb = eef->Deb;
	Fin = eef->Fin;
	Val = eef->Val;
}
//-------------------------------------------------------------
CL_EEF::CL_EEF(int col, int r0, int r1, float val) {
//    col=1 r0=2 r1=4  -> Deb=2   Fin=4
//    col=2 r0=2 r1=4  -> Deb=14  Fin=16
	col--;
	Deb = col * 12 + r0;
	Fin = col * 12 + r1;
	Val = val;
}
//-------------------------------------------------------------
void CL_EEF::Coordonnee(int &col, int &r0, int &r1) {
// Deb=14 Fin=16  ->col=1 r0=2 r1=4 col=2
	col = (Deb - 1) / 12;
	r0 = Deb - col * 12;
	r1 = Fin - col * 12;
	col++;
}

//-------------------------------------------------------------
//-------------------------------------------------------------
CL_Atelier::CL_Atelier() {
	Nom = "";
	NbPhase = 0;
	Supprimable = true;
	Categorie = NULL;
	NoCategorie = 0;
	Nature = 0;
	Espece = NULL;
	NoEspece = 0;
	Derobe = false;
	DebAmor = 0;
	DurAmor = 0;
	Notes = "";
	Couleur = -1;
	Motif = -1;
	V_Charge = new CL_Vecteur<CL_ItemParAtelier>();
	V_ChargeVolume = new CL_Vecteur<CL_ItemParAtelier>();
	V_Produit = new CL_Vecteur<CL_ItemParAtelier>();
	V_Externalite = new CL_Vecteur<CL_ItemParAtelier>();

	V_Avance = new CL_Vecteur<CL_EEF>();
	//V_Stock       =new	CL_Vecteur<CL_EEF>();//190802
	V_BesTrav = new CL_Vecteur<CL_BesTrav>();

	PImmoExiste = false;
	PImmoFamExiste = false;
	ProdImmo = NULL;
	ProdImmoFam = NULL;
	ValInvRepro = 0.;
	ValInvAutre = 0.;
	Ordre = 0;
}
//-------------------------------------------------------------------------
CL_Atelier::CL_Atelier(const CL_Atelier *atelier) {
	CL_ItemParAtelier *itemPA;
	CL_BesTrav *besTravOr, *besTrav;
	Nom = atelier->Nom;
	No = atelier->No;
	NoCategorie = atelier->NoCategorie;
	Categorie = atelier->Categorie;
	NoEspece = atelier->NoEspece;
	Espece = atelier->Espece;
	NbPhase = atelier->NbPhase;
	Nature = atelier->Nature;
	Derobe = atelier->Derobe;
	Notes = atelier->Notes;
	DebAmor = atelier->DebAmor;
	DurAmor = atelier->DurAmor;
	Couleur = -1;
	Motif = -1;
	Supprimable = true;
	V_Produit = new CL_Vecteur<CL_ItemParAtelier>(atelier->V_Produit);
	V_Charge = new CL_Vecteur<CL_ItemParAtelier>(atelier->V_Charge);
	V_ChargeVolume = new CL_Vecteur<CL_ItemParAtelier>(atelier->V_ChargeVolume);
	V_Externalite = new CL_Vecteur<CL_ItemParAtelier>(atelier->V_Externalite);

	V_Avance = new CL_Vecteur<CL_EEF>(atelier->V_Avance);
	//V_Stock       =new	CL_Vecteur<CL_EEF>(atelier->V_Stock);//190802
	V_BesTrav = new CL_Vecteur<CL_BesTrav>(); //atelier->V_BesTrav);

	for (int i = 0; i < atelier->V_BesTrav->Nbelt; i++) {
		besTravOr = atelier->V_BesTrav->Vecteur[i];
		besTrav = new CL_BesTrav(besTravOr);
		V_BesTrav->insSans(besTrav);
	}

	if (NbPhase > 0) {
		RecopieQuantite(V_Produit, atelier->V_Produit);
		RecopieQuantite(V_Charge, atelier->V_Charge);
		RecopieQuantite(V_ChargeVolume, atelier->V_ChargeVolume);
		RecopieQuantite(V_Externalite, atelier->V_Externalite);
	}
	for (int i = 0; i < atelier->V_ChargeVolume->Nbelt; i++) {
		itemPA = V_ChargeVolume->Vecteur[i];
		itemPA->ItemPA = V_Produit->trouve(itemPA->NoItemPA);
	}
	ProdImmo = NULL;
	if (atelier->PImmoExiste == true) {
		ProdImmo = new float(atelier->NbPhase);
		memcpy(ProdImmo, atelier->ProdImmo, sizeof(ProdImmo));
	}
	ProdImmoFam = NULL;
	if (atelier->PImmoFamExiste == true) {
		ProdImmoFam = new float(atelier->NbPhase);
		memcpy(ProdImmoFam, atelier->ProdImmoFam, sizeof(ProdImmoFam));
	}
	ValInvRepro = atelier->ValInvRepro;
	ValInvAutre = atelier->ValInvAutre;
	Ordre = atelier->Ordre;
}
//----------------------------------------------------------------------------
void CL_Atelier::RecopieQuantite(CL_Vecteur<CL_ItemParAtelier> *vecteur,
		CL_Vecteur<CL_ItemParAtelier> *vecteurOr) {
	int i, n;
	CL_ItemParAtelier* itemPA;
	CL_ItemParAtelier* itemPAOr;
	for (n = 0; n < vecteur->Nbelt; n++) {
		itemPA = vecteur->Vecteur[n];
		itemPAOr = vecteurOr->Vecteur[n];
		itemPA->QtePhase = new float[NbPhase];
		for (i = 0; i < NbPhase; i++)
			itemPA->QtePhase[i] = itemPAOr->QtePhase[i];
	}
}
//---------------------------------------------------------------------------
CL_Atelier::~CL_Atelier(void) {
	Deletevecteur(V_Charge);
	Deletevecteur(V_ChargeVolume);
	Deletevecteur(V_Produit);
	Deletevecteur(V_Externalite);
	Notes = "";
	delete V_Charge;
	V_Charge = NULL;
	delete V_ChargeVolume;
	V_ChargeVolume = NULL;
	delete V_Produit;
	V_Produit = NULL;
	delete V_Externalite;
	V_Externalite = NULL;

}
//---------------------------------------------------------------------------
void CL_Atelier::Deletevecteur(CL_Vecteur<CL_ItemParAtelier> *vecteur) {
	CL_ItemParAtelier* itemPA;
	for (int n = 0; n < vecteur->Nbelt; n++) {
		itemPA = vecteur->Vecteur[n];
		delete itemPA;
		itemPA = NULL;
	}
}
//----------------------------------------------------------------------------
void CL_Atelier::SupMaFalse(void) {
	int i;
	if (Categorie)
		Categorie->Supprimable = false;
	if (Espece)
		Espece->Supprimable = false;
	for (i = 0; i < V_Produit->Nbelt; i++)
		V_Produit->Vecteur[i]->Item->Supprimable = false;
	for (i = 0; i < V_Charge->Nbelt; i++)
		V_Charge->Vecteur[i]->Item->Supprimable = false;
	for (i = 0; i < V_ChargeVolume->Nbelt; i++)
		V_ChargeVolume->Vecteur[i]->Charge->Supprimable = false;
	for (i = 0; i < V_Externalite->Nbelt; i++)
		V_Externalite->Vecteur[i]->Item->Supprimable = false;
}
//-----------------------------------------------------------

//-----------------------------------------------------------
CL_Valeur::CL_Valeur(const CL_Valeur *valeur) {
	Type = valeur->Type;
	No = valeur->No;
	NoAtelier = valeur->NoAtelier;
	NoItem = valeur->NoItem;
	Atelier = valeur->Atelier;
	Item = valeur->Item;
	memcpy(Valeur, valeur->Valeur, sizeof(float) * N_X);
}

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
CL_Verger::CL_Verger(const CL_Verger *verger) {
	No = verger->No;
	Surface = verger->Surface;
	memcpy(SurfaceAn, verger->SurfaceAn, sizeof(float) * N_X);
	AnPlant = verger->AnPlant;
	AnArr = verger->AnArr;
	NoAtelier = verger->NoAtelier;
	NoEspece = verger->NoEspece;
	memcpy(Phase, verger->Phase, sizeof(float) * N_X);
	Atelier = verger->Atelier;
	Espece = verger->Espece;
}

//-----------------------------------------------------------
CL_InvAni::CL_InvAni() {
	int n;
	No = 0;
	NoAnimal = 0;
	Animal = NULL;

//    ValInv=0;         //260903
	Reproducteur = 'O'; //260903

	for (n = 0; n < N_X + 1; n++) {
		Effectif[n] = 0.;
		Valeur[n] = 0.;
	}
	for (n = 0; n < N_X; n++) {
		Vente[n] = 0.;
		Achat[n] = 0.;
		ValVente[n] = 0.;
		ValAchat[n] = 0.;
		EffMax[n] = SANSBORNE;
		Atelier[n] = NULL;
		NoAtelier[n] = -1;
		PrixVenteMoy[n] = 0; //300903  Non Stocké
		ValInvMoy[n] = 0; //300903  Non Stocké
	}
	ValInvMoy[N_X] = 0;
	// pour les EffMax  1000 signifie pas de contrainte

}
//-----------------------------------------------------------
CL_InvAni::CL_InvAni(const CL_InvAni *invAni) {
	No = 0;
	NoAnimal = 0;
	Animal = NULL;

//    ValInv= invAni->ValInv; //260309
	Reproducteur = invAni->Reproducteur; //260309

	memcpy(Effectif, invAni->Effectif, sizeof(float) * (N_X + 1)); //091002
	memcpy(Valeur, invAni->Valeur, sizeof(float) * (N_X + 1)); //091002

	memcpy(Vente, invAni->Vente, sizeof(float) * N_X); //091002
	memcpy(Achat, invAni->Achat, sizeof(float) * N_X); //091002

	memcpy(ValVente, invAni->ValVente, sizeof(float) * N_X);
	memcpy(ValAchat, invAni->ValAchat, sizeof(float) * N_X);

	memcpy(Atelier, invAni->Atelier, sizeof(Atelier));
	memcpy(NoAtelier, invAni->NoAtelier, sizeof(NoAtelier));

	memcpy(PrixVenteMoy, invAni->PrixVenteMoy, sizeof(PrixVenteMoy));
	memcpy(ValInvMoy, invAni->ValInvMoy, sizeof(ValInvMoy));

}
//-----------------------------------------------------------
CL_Troupeau::CL_Troupeau() {
	NoCatBestiaux = -1;
	CatBestiaux = NULL;
	V_InvAni = new CL_Vecteur<CL_InvAni>();
	LstMvtAni = new TList;

}
//-----------------------------------------------------------
CL_Troupeau::CL_Troupeau(CL_Categorie *catBestiaux) {
	int i, n;
	CL_Item *animal;
	CL_InvAni *invAni;
	CatBestiaux = catBestiaux;
	NoCatBestiaux = CatBestiaux->No;
	V_InvAni = new CL_Vecteur<CL_InvAni>();
	for (i = 0; i < V_Bestiaux->Nbelt; i++) {
		animal = V_Bestiaux->Vecteur[i];
		if (animal->Categorie != catBestiaux)
			continue;

		invAni = new CL_InvAni();
		invAni->Animal = animal;
		invAni->NoAnimal = animal->No;
		if (animal->DonnePcent[0] != 0)
			invAni->Reproducteur = 'O';
		else
			invAni->Reproducteur = 'N';
		for (n = 0; n < N_X; n++) {
			invAni->PrixVenteMoy[n] = animal->Prix;
			invAni->ValInvMoy[n] = animal->ValInv;
		}
		invAni->ValInvMoy[N_X] = animal->ValInv;
		V_InvAni->ins(invAni);
	}

	LstMvtAni = new TList;

}
//-----------------------------------------------------------
CL_Troupeau::CL_Troupeau(CL_Troupeau *troupeau) {
	int i;
	CL_MvtAni *mvtAni, *mvtAni0;
	CatBestiaux = troupeau->CatBestiaux;
	NoCatBestiaux = CatBestiaux->No;
	V_InvAni = new CL_Vecteur<CL_InvAni>(troupeau->V_InvAni);

	LstMvtAni = new TList;
	for (i = 0; i < troupeau->LstMvtAni->Count; i++) {
		mvtAni0 = (CL_MvtAni *) troupeau->LstMvtAni->Items[i];
		mvtAni = new CL_MvtAni(mvtAni0);
		LstMvtAni->Add(mvtAni);

	}
}
//-----------------------------------------------------------
CL_Troupeau::~CL_Troupeau() {
	V_InvAni->purge();
	VideLstMvtAni();
	delete LstMvtAni;

}
//-----------------------------------------------------------
void CL_Troupeau::VideLstMvtAni(void) {
	int i;
	CL_MvtAni *mvtAni;
	for (i = 0; i < LstMvtAni->Count; i++) {
		mvtAni = (CL_MvtAni *) LstMvtAni->Items[i];
		delete mvtAni;
	}
	LstMvtAni->Count = 0;
}

//-----------------------------------------------------------
//CL_EmpLT
//-----------------------------------------------------------
CL_EmpLT::CL_EmpLT() {
	Duree = Duree2 = 0;
	Taux = Taux2 = 0;
	Type = ""; //ca s t m va...
	AReal = MReal = ARemb = MRemb = 0;
//    memset(Dette,  0,sizeof(float)*N_X);
//    memset(CapRemb,0,sizeof(float)*N_X);
//    memset(Interet,0,sizeof(float)*N_X);
	Pour = 'E'; //E ou Prive
}
CL_EmpLT::~CL_EmpLT() {
}
//-----------------------------------------------------------
//CL_EmpCT
//-----------------------------------------------------------
CL_EmpCT::CL_EmpCT() {
	Taux = 0;
	Type = "N"; //ca s t m va...
	AReal = MReal = ARemb = MRemb = 0;
	Pour = 'E'; //E ou Prive
}
//-----------------------------------------------------------
//CL_Sub   Subvention
//-----------------------------------------------------------
CL_Sub::CL_Sub() {
	Montant = 0;
	AReal = MReal = 0;
	Duree = 0;
}
//-----------------------------------------------------------
CL_Sub::CL_Sub(CL_Sub *source) {
	No = source->No;
	Nom = source->Nom;
	Montant = source->Montant;
	AReal = source->AReal;
	MReal = source->MReal;
	ExReal = source->ExReal;
	Duree = source->Duree;
}
//-----------------------------------------------------------

//-----------------------------------------------------------
CL_Plact::CL_Plact() {
	Montant = 0;
	Taux = 0;
	AReal = MReal = ATerme = MTerme = 0;
	Type = 'F';
	Pour = 'E';
}
//-----------------------------------------------------------
CL_Occc::CL_Occc() {
	Ex = 0;
	Montant = 0;
	Taux = 0;
	Pcent = 0;
	Frais = 0;
}
//-----------------------------------------------------------
CL_FN_Xp1::CL_FN_Xp1() {
	memset(Valeur, 0, sizeof(float) * (N_X + 1));
}
//-----------------------------------------------------------
CL_Immo::CL_Immo() {
	Nom = "";
	ValAchat = 0;
	AAchat = MAchat = AVente = MVente = 0;
	TypeAmor = ' ';
	Duree = 0;
//    Present='O';  //O/N
//    memset(Amor,0,sizeof(float)*N_X);
//    memset(VResid,0,sizeof(float)*N_X);
//    Groupe=0;
//    ValResidO=0;
	NoTva = 0;
	Tva = NULL;
}
//-----------------------------------------------------------
CL_Petit::CL_Petit() //A
{
	ValAchat = 0;
	NoTva = 0;
	Repart = NULL;
	NoRepart = -1;
}
//-----------------------------------------------------------
CL_TotSub::CL_TotSub() {
	memset(Valeur, 0, sizeof(float) * N_X);
	memset(Resid, 0, sizeof(float) * (N_X + 1));
	memset(Amor, 0, sizeof(float) * N_X);
}
CL_TotSub::CL_TotSub(CL_TotSub *source) {
	memcpy(Valeur, source->Valeur, sizeof(float) * N_X);
	memcpy(Resid, source->Resid, sizeof(float) * (N_X + 1));
	memcpy(Amor, source->Amor, sizeof(float) * N_X);
}
void CL_TotSub::Maz(void) {
	memset(Valeur, 0, sizeof(float) * N_X);
	memset(Resid, 0, sizeof(float) * (N_X + 1));
	memset(Amor, 0, sizeof(float) * N_X);
}

//-----------------------------------------------------------
CL_TotEnCours::CL_TotEnCours() {
	memset(Flux, 0, sizeof(float) * N_X);
	memset(Stock, 0, sizeof(float) * (N_X + 1));
	memset(CrDette, 0, sizeof(float) * (N_X + 1));
	memset(Tva, 0, sizeof(float) * N_X);
	EstVide = true;
}
//-----------------------------------------------------------
CL_TotEnCours::CL_TotEnCours(CL_TotEnCours *autre) {
	memcpy(Flux, autre->Flux, sizeof(float) * N_X);
	memcpy(Stock, autre->Stock, sizeof(float) * (N_X + 1));
	memcpy(CrDette, autre->Stock, sizeof(float) * (N_X + 1));
	memcpy(Tva, autre->Tva, sizeof(float) * N_X);
	EstVide = autre->EstVide;
}
//-----------------------------------------------------------
void CL_TotEnCours::Maz(void) {
	memset(Flux, 0, sizeof(float) * N_X);
	memset(Stock, 0, sizeof(float) * (N_X + 1));
	memset(CrDette, 0, sizeof(float) * (N_X + 1));
	memset(Tva, 0, sizeof(float) * N_X);
	EstVide = true;
}
//-----------------------------------------------------------
CL_EnCours::CL_EnCours() {
	Item = NULL;
	NoFamille = 0;
	NoItem = 0;
	Valeur = 0;
	EnStock = 'N';
	APaie = 0;
	MPaie = 0;
}
//-----------------------------------------------------------
CL_EnCours::CL_EnCours(CL_EnCours *source) {
	Item = source->Item;
	NoFamille = source->NoFamille;
	NoItem = source->NoItem;
	Valeur = source->Valeur;
	EnStock = source->EnStock;
	APaie = source->APaie;
	MPaie = source->MPaie;
}
//-----------------------------------------------------------
CL_StockIni::CL_StockIni() {
	No = 0;
	Flag = ' ';
	Nom = "";
	NoItem = 0;
	Item = NULL;
	memset(Quantite, 0, sizeof(float) * N_X);
	memset(PrixRevient, 0, sizeof(float) * N_X);
}
;
//-----------------------------------------------------------
CL_StockIni::CL_StockIni(CL_StockIni *source) {
	No = 0;
	Flag = ' ';
	Nom = "";
	NoItem = source->NoItem;
	Item = source->Item;
	memcpy(Quantite, source->Quantite, sizeof(float) * N_X);
	memcpy(PrixRevient, source->PrixRevient, sizeof(float) * N_X);
}
;
//-----------------------------------------------------------
// Les totaux
//-----------------------------------------------------------
CL_TotEmp::CL_TotEmp() {
	Maz();
}
//-----------------------------------------------------------
CL_TotEmp::CL_TotEmp(CL_TotEmp *totEmp) {
	int n;
	for (n = 0; n < N_X; n++) {
		Capital[n] = totEmp->Capital[n];
		Remb[n] = totEmp->Remb[n];
		Interet[n] = totEmp->Interet[n];
		Annuite[n] = totEmp->Annuite[n];
	}
	for (n = 0; n < N_X + 1; n++) {
		Dette[n] = totEmp->Dette[n];
	}
}
//-----------------------------------------------------------
void CL_TotEmp::Maz(void) {
	memset(Capital, 0, sizeof(float) * N_X);
	memset(Remb, 0, sizeof(float) * N_X);
	memset(Interet, 0, sizeof(float) * N_X);
	memset(Annuite, 0, sizeof(float) * N_X);
	memset(Dette, 0, sizeof(float) * (N_X + 1));
	EstVide = true;
}
//-----------------------------------------------------------
void CL_TotEmp::Ajoute(float *capital, float *remb, float *interet,
		float *dette) {
	for (int i = 0; i < N_X; i++) {
		Capital[i] += capital[i];
		Dette[i] += dette[i];
		Remb[i] += remb[i];
		Interet[i] += interet[i];
		Annuite[i] += remb[i] + interet[i];
	}
	Dette[N_X] += dette[N_X];
	EstVide = false;
}
//-----------------------------------------------------------
CL_TotImmo::CL_TotImmo() {
	Maz();
}
//-----------------------------------------------------------
void CL_TotImmo::Maz(void) {
	memset(Achat, 0, sizeof(float) * N_X);
	memset(Vente, 0, sizeof(float) * N_X);
	memset(Amor, 0, sizeof(float) * N_X);
	memset(Resid, 0, sizeof(float) * (N_X + 1));
	memset(ValBrut, 0, sizeof(float) * N_X);
	memset(TvaVersee, 0, sizeof(float) * N_X);
	memset(TvaRecue, 0, sizeof(float) * N_X);
	memset(ValCompta, 0, sizeof(float) * N_X); //070202
//    memset(PlusVal,   0,sizeof(float)*N_X);
//    memset(MoinsVal,  0,sizeof(float)*N_X);
	memset(ProdImmo, 0, sizeof(float) * N_X);
	EstVide = true;
}
//-----------------------------------------------------------
CL_TotImmo::CL_TotImmo(CL_TotImmo *totImmo) {
	int n;
	for (n = 0; n < N_X; n++) {
		Achat[n] = totImmo->Achat[n];
		Vente[n] = totImmo->Vente[n];
		Amor[n] = totImmo->Amor[n];
		ValBrut[n] = totImmo->ValBrut[n];
		TvaVersee[n] = totImmo->TvaVersee[n];
		TvaRecue[n] = totImmo->TvaRecue[n];
		ValCompta[n] = totImmo->ValCompta[n];
//        PlusVal[n]=   totImmo->TvaRecue[n];
	}
	for (n = 0; n < N_X + 1; n++) {
		Resid[n] = totImmo->Resid[n];
	}
}
//-----------------------------------------------------------
//CL_Prog
//-----------------------------------------------------------
CL_Prog::CL_Prog() {
	Source = AnsiString("");
	Arbre = NULL;
	Reseau = NULL;
}
//-----------------------------------------------------------
CL_Prog::CL_Prog(CL_Prog *prog) {
	Source = prog->Source;
	Arbre = NULL;
	Reseau = NULL;
	if (prog->Arbre)
		Arbre = new CL_Arbre(prog->Arbre);
	if (prog->Reseau)
		Reseau = new CL_Reseau(prog->Reseau);
}
//-----------------------------------------------------------
CL_Prog::~CL_Prog() {
	if (Arbre) {
		delete Arbre;
		Arbre = NULL;
	}
	if (Reseau) {
		delete Reseau;
		Reseau = NULL;
	}
}
//-----------------------------------------------------------
bool CL_Prog::EstIdentique(CL_Prog *prog) {
	if (Arbre == NULL && prog->Arbre)
		return false;
	if (Arbre && prog->Arbre == NULL)
		return false;

	if (Arbre && prog->Arbre) {
		if (Arbre->EstIdentique(prog->Arbre) == false)
			return false;
	}
	if (Reseau == NULL && prog->Reseau == NULL)
		return true;
	if (Reseau && prog->Reseau == NULL)
		return false;
	if (Reseau == NULL && prog->Reseau)
		return false;

	if (Reseau->EstIdentique(prog->Reseau) == false)
		return false;
	return true;
}
//-----------------------------------------------------------
bool CL_Prog::EstNumerique(void) {
	if (Reseau != NULL)
		return false;
	if (Arbre->EstNumerique() == true)
		return true;
	return false;
}
//-----------------------------------------------------------
//CL_Formule
//-----------------------------------------------------------
CL_Formule::CL_Formule() {
	int n;
	Supprimable = true;
	No = 0;
	Item = NULL;
	NoFamille = 0;
	Origine = ' ';
	EstCalcule = false;
	for (n = 0; n < N_X; n++)
		LesProg[n] = NULL;
	memset(Valeur, 0, sizeof(Valeur));
//    memset( Recette,0,sizeof(Recette));

//        Stock[n]=      0;
}
//-----------------------------------------------------------
CL_Formule::CL_Formule(CL_Formule *formule) {
	int n, j, k;
	CL_Prog *pS, *p;
	bool recopie[N_X];

	Supprimable = formule->Supprimable;
	No = formule->No;
	Item = formule->Item;
	NoFamille = formule->NoFamille;
	Origine = formule->Origine;
	for (n = 0; n < N_X; n++) {
		LesProg[n] = NULL;
		Valeur[n] = formule->Valeur[n];
//        Recette[n]=    formule->Recette[n];
//        Stock[n]=      formule->Stock[n];
	}
	for (j = 0; j < N_X; j++)
		recopie[j] = false;
	for (j = 0; j < N_X; j++) {
		if (recopie[j] == true)
			continue;

		pS = formule->LesProg[j];

		if (pS)
			p = new CL_Prog(pS);
		else
			p = NULL;

		LesProg[j] = p;
		recopie[j] = true;
		for (k = j + 1; k < N_X; k++) {
			if (formule->LesProg[k] == pS) {
				LesProg[k] = p;
				recopie[k] = true;
			}
		}
	}
}
//-----------------------------------------------------------
CL_Formule::~CL_Formule() {
	int n, j;
	for (n = 0; n < N_X; n++) {
		if (LesProg[n]) {
			delete LesProg[n];
			for (j = n + 1; j < N_X; j++) {
				if (LesProg[j] == LesProg[n])
					LesProg[j] = NULL;
			}
			LesProg[n] = NULL;
		}
	}
}

//------------------ ------------------------------------------------------------
CL_Periode::CL_Periode() {
	Supprimable = true;
	No = 0;
	Nom = "";
	JDeb = 0;
	MDeb = 0;
	JFin = 0;
	MFin = 0;
	Duree = 0;
	PcentDispo = 0;
	HpJ = 0.; //heurs par jour
	JDispo = 0;
	HDispo = 0;
	memset(Valeur, 0, sizeof(float) * N_X);
}
//------------------ ------------------------------------------------------------
CL_Periode::CL_Periode(CL_Periode *ptr) {
	Supprimable = true;
	No = 0;
	Nom = ptr->Nom;
	JDeb = ptr->JDeb;
	MDeb = ptr->MDeb;
	JFin = ptr->JFin;
	MFin = ptr->MFin;
	Duree = ptr->Duree;
	PcentDispo = ptr->PcentDispo;
	HpJ = ptr->HpJ; //heurs par jour
	HDispo = ptr->HDispo;
	JDispo = ptr->JDispo;
	memcpy(Valeur, ptr->Valeur, sizeof(float) * N_X);
}
//------------------ ------------------------------------------------------------
bool CL_Periode::CalculDuree(void) {
	TDateTime dtDeb;
	TDateTime dtFin;
	Word anDeb, anFin;
	if (MFin == 0)
		return false;
	if (MDeb == 0)
		return false;

	// pour avoir une année  nécssaire a EncodeDate
	anDeb = 2001;
	if (MFin >= MDeb)
		anFin = anDeb;
	else
		anFin = anDeb + 1;

	dtDeb = EncodeDate(anDeb, (Word) MDeb, (Word) JDeb);
	dtFin = EncodeDate(anFin, (Word) MFin, (Word) JFin);
	Duree = dtFin - dtDeb;
	if (Duree == 0) {
		ShowMessage(" La période a une duree nulle");
		return false;
	}
	return true;

}
//------------------ ------------------------------------------------------------
void CL_Periode::CalculDispo(void) {
	if (PcentDispo == 0)
		return;
	JDispo = Duree * PcentDispo / 100.;

	if (HpJ == 0)
		return;
	HDispo = JDispo * HpJ;
}
//------------------ ------------------------------------------------------------
CL_Calendrier::CL_Calendrier() {
	No = 0;
	Nom = "";
	Supprimable = true;
	V_Periode = new CL_Vecteur<CL_Periode>();
}
//------------------ ------------------------------------------------------------
CL_Calendrier::CL_Calendrier(CL_Calendrier* ptr) {
	No = 0;
	Nom = ptr->Nom;
	Supprimable = true;
	V_Periode = new CL_Vecteur<CL_Periode>(ptr->V_Periode);
}
//---------------------------------------------------------------------------
//Commercialisation
//---------------------------------------------------------------------------
CL_QuantPrix::CL_QuantPrix() {
	NoItem = -1;
	Item = NULL;
	AnProd = 0;
	AnComm = 0;
	Quant = 0;
	Prix = 0;
}
//---------------------------------------------------------------------------
CL_QuantPrix::CL_QuantPrix(CL_Item *item, int anProd, int anComm, float quant,
		float prix) {
	NoItem = item->No;
	Item = item;
	AnProd = anProd;
	AnComm = anComm;
	Quant = quant;
	Prix = prix;
}
//---------------------------------------------------------------------------
CL_QuantPrix::CL_QuantPrix(CL_QuantPrix *source) {
	NoItem = source->Item->No;
	Item = source->Item;
	AnProd = source->AnProd;
	AnComm = source->AnComm;
	Quant = source->Quant;
	Prix = source->Prix;
}
//---------------------------------------------------------------------------
void CL_QuantPrix::EcrireFichier(FILE *fichier) {
	fwrite(&NoItem, sizeof(int), 1, fichier);
	fwrite(&AnProd, sizeof(int), 1, fichier);
	fwrite(&AnComm, sizeof(float), 1, fichier);
	fwrite(&Quant, sizeof(float), 1, fichier);
	fwrite(&Prix, sizeof(float), 1, fichier);
}
//---------------------------------------------------------------------------
void CL_QuantPrix::LireFichier(FILE *fichier) {
	fread(&NoItem, sizeof(int), 1, fichier);
	fread(&AnProd, sizeof(int), 1, fichier);
	fread(&AnComm, sizeof(float), 1, fichier);
	fread(&Quant, sizeof(float), 1, fichier);
	fread(&Prix, sizeof(float), 1, fichier);
	Item = V_Produit->trouve(NoItem);
}

//---------------------------------------------------------------------------
//CL_AgriRes
//---------------------------------------------------------------------------
CL_AgriRes::CL_AgriRes() {
	try {
		//Resultats
		V_Produit = new CL_Vecteur<CL_QuanVal>();
		V_Charge = new CL_Vecteur<CL_QuanVal>();

		V_Externalite = new CL_Vecteur<CL_QuanVal>();
		V_ExtNeg = new CL_Vecteur<CL_QuanVal>();
		V_ExtPos = new CL_Vecteur<CL_QuanVal>();

		V_ChStruct = new CL_Vecteur<CL_QuanVal>();
		V_RecDiv = new CL_Vecteur<CL_QuanVal>();
		V_DepDiv = new CL_Vecteur<CL_QuanVal>();
		V_RecFam = new CL_Vecteur<CL_QuanVal>();
		V_DepFam = new CL_Vecteur<CL_QuanVal>();

		// total valeur par categorie
		V_CatProduitTot = new CL_Vecteur<CL_QuanVal>();
		V_CatChargeTot = new CL_Vecteur<CL_QuanVal>();

		V_CatExtNegTot = new CL_Vecteur<CL_QuanVal>();
		V_CatExtPosTot = new CL_Vecteur<CL_QuanVal>();

		V_CatChStructTot = new CL_Vecteur<CL_QuanVal>();

		V_CatRecDivTot = new CL_Vecteur<CL_QuanVal>();
		V_CatDepDivTot = new CL_Vecteur<CL_QuanVal>();

		V_CatRecFamTot = new CL_Vecteur<CL_QuanVal>();
		V_CatDepFamTot = new CL_Vecteur<CL_QuanVal>();

		//cree(new) un CL_QuanVal pour mettre le total par categorie
		// seul quanVal->Val sera utilisé
		creeVCat_Tot(V_CatProduit, V_CatProduitTot);
		creeVCat_Tot(V_CatCharge, V_CatChargeTot);

		creeVCat_Tot(V_CatChStruct, V_CatChStructTot);

		creeVCat_Tot(V_CatRecDiv, V_CatRecDivTot);
		creeVCat_Tot(V_CatDepDiv, V_CatDepDivTot);

		creeVCat_Tot(V_CatRecFam, V_CatRecFamTot);
		creeVCat_Tot(V_CatDepFam, V_CatDepFamTot);
	} catch (Exception& err) {
		ShowMessage(err.Message);
	}

	memset(Produit, 0, sizeof(float) * N_X);
	memset(Charge, 0, sizeof(float) * N_X);

	memset(VenteAni, 0, sizeof(float) * N_X); //181201
	memset(AchatAni, 0, sizeof(float) * N_X); //181201
	memset(InvAniRepro, 0, sizeof(InvAniRepro)); //260903
	memset(InvAniAutre, 0, sizeof(InvAniAutre)); //260903

	memset(RecDiv, 0, sizeof(float) * N_X);
	memset(DepDiv, 0, sizeof(float) * N_X);

	memset(ChStruct, 0, sizeof(float) * N_X);

	memset(RecFam, 0, sizeof(float) * N_X);
	memset(DepFam, 0, sizeof(float) * N_X);

	memset(Stock, 0, sizeof(float) * (N_X + 1));
	memset(StockIni, 0, sizeof(float) * (N_X + 1));
	memset(Avance, 0, sizeof(float) * (N_X + 1));
	memset(ProdImmo, 0, sizeof(float) * N_X); //031201
	memset(ProdImmoFam, 0, sizeof(float) * N_X); //051201
	memset(AmorPlant, 0, sizeof(float) * N_X); //051201
	memset(ValPlant, 0, sizeof(float) * (N_X + 1));
	memset(PertePlant, 0, sizeof(float) * N_X);

	// les totaux : Produit Charge etc... sont définis dans la classe
	// Produit[N_X]..DepFam

	EmpLTE = new CL_TotEmp(); //entreprise
	EmpCTE = new CL_TotEmp();
	EmpLTP = new CL_TotEmp(); //privé
	EmpCTP = new CL_TotEmp();

	EmpSomLT = new CL_TotEmp();
	EmpSomCT = new CL_TotEmp();
	EmpTotal = new CL_TotEmp();

	PlactE = new CL_TotEmp();
	PlactP = new CL_TotEmp();

	Immo = new CL_TotImmo();
	ImmoPetit = new CL_TotImmo();
	ImmoSom = new CL_TotImmo();
	ImmoTotal = new CL_TotImmo();

	TotSub = new CL_TotSub();
	Creance = new CL_TotEnCours();
	Dette = new CL_TotEnCours();
	// définis dans la classe
	// FraisOccc ...SoldeCumul[N_X]..

	memset(FraisOccc, 0, sizeof(float) * N_X);
	memset(Marge, 0, sizeof(float) * N_X);
	memset(AutreDepense, 0, sizeof(float) * N_X);
	memset(AutreRecette, 0, sizeof(float) * N_X);
	memset(Solde, 0, sizeof(float) * N_X);
	memset(SoldeCumul, 0, sizeof(float) * N_X);

	Tva = new CL_TvaEnt();

	V_SurCulture = new CL_Vecteur<CL_Valeur>();
	V_SurVerger = new CL_Vecteur<CL_Valeur>();
	V_EffAnimaux = new CL_Vecteur<CL_Valeur>();

	memset(SurCulture, 0, sizeof(float) * N_X);
	memset(SurVerger, 0, sizeof(float) * N_X);
	memset(EffAnimaux, 0, sizeof(float) * N_X);

	TresoIni = 0;
	memset(Caf, 0, sizeof(float) * N_X);
	memset(Ebe, 0, sizeof(float) * N_X);
	memset(Msa, 0, sizeof(float) * N_X);

}
//---------------------------------------------------------------------------
CL_AgriRes::CL_AgriRes(CL_AgriRes *source) {

	V_Produit = new CL_Vecteur<CL_QuanVal>(source->V_Produit);
	V_Charge = new CL_Vecteur<CL_QuanVal>(source->V_Charge);

	V_Externalite = new CL_Vecteur<CL_QuanVal>(source->V_Externalite);
	V_ExtNeg = new CL_Vecteur<CL_QuanVal>(source->V_ExtNeg);
	V_ExtPos = new CL_Vecteur<CL_QuanVal>(source->V_ExtPos);

	V_ChStruct = new CL_Vecteur<CL_QuanVal>(source->V_ChStruct);
	V_RecDiv = new CL_Vecteur<CL_QuanVal>(source->V_RecDiv);
	V_DepDiv = new CL_Vecteur<CL_QuanVal>(source->V_DepDiv);
	V_RecFam = new CL_Vecteur<CL_QuanVal>(source->V_RecFam);
	V_DepFam = new CL_Vecteur<CL_QuanVal>(source->V_DepFam);

	// total valeur par categorie
	V_CatProduitTot = new CL_Vecteur<CL_QuanVal>(source->V_CatProduitTot);
	V_CatChargeTot = new CL_Vecteur<CL_QuanVal>(source->V_CatChargeTot);

	V_CatExtNegTot = new CL_Vecteur<CL_QuanVal>(source->V_CatExtNegTot);
	V_CatExtPosTot = new CL_Vecteur<CL_QuanVal>(source->V_CatExtPosTot);

	V_CatChStructTot = new CL_Vecteur<CL_QuanVal>(source->V_CatChStructTot);

	V_CatRecDivTot = new CL_Vecteur<CL_QuanVal>(source->V_CatRecDivTot);
	V_CatDepDivTot = new CL_Vecteur<CL_QuanVal>(source->V_CatDepDivTot);

	V_CatRecFamTot = new CL_Vecteur<CL_QuanVal>(source->V_CatRecFamTot);
	V_CatDepFamTot = new CL_Vecteur<CL_QuanVal>(source->V_CatDepFamTot);

	//les totaux
	memcpy(Produit, source->Produit, sizeof(float) * N_X);
	memcpy(Charge, source->Charge, sizeof(float) * N_X);

	memcpy(VenteAni, source->VenteAni, sizeof(float) * N_X); //181201
	memcpy(AchatAni, source->VenteAni, sizeof(float) * N_X); //181201
	memcpy(InvAniRepro, source->InvAniRepro, sizeof(InvAniRepro)); //260903
	memcpy(InvAniAutre, source->InvAniAutre, sizeof(InvAniAutre)); //260903

	memcpy(RecDiv, source->RecDiv, sizeof(float) * N_X);
	memcpy(DepDiv, source->DepDiv, sizeof(float) * N_X);

	memcpy(ChStruct, source->ChStruct, sizeof(float) * N_X);

	memcpy(RecFam, source->RecFam, sizeof(float) * N_X);
	memcpy(DepFam, source->DepFam, sizeof(float) * N_X);

	memcpy(Stock, source->Stock, sizeof(float) * (N_X + 1));
	memcpy(StockIni, source->StockIni, sizeof(float) * (N_X + 1));
	memcpy(Avance, source->Avance, sizeof(float) * (N_X + 1));
	memcpy(ProdImmo, source->ProdImmo, sizeof(float) * N_X);
	memcpy(ProdImmoFam, source->ProdImmoFam, sizeof(float) * N_X);
	memcpy(AmorPlant, source->AmorPlant, sizeof(float) * N_X);
	memcpy(ValPlant, source->ValPlant, sizeof(float) * (N_X + 1));
	memcpy(PertePlant, source->PertePlant, sizeof(float) * N_X);

	EmpLTE = new CL_TotEmp(source->EmpLTE); //entreprise
	EmpCTE = new CL_TotEmp(source->EmpCTE);
	EmpLTP = new CL_TotEmp(source->EmpLTP); //privé
	EmpCTP = new CL_TotEmp(source->EmpCTP);

	EmpSomLT = new CL_TotEmp(source->EmpSomLT);
	EmpSomCT = new CL_TotEmp(source->EmpSomCT);
	EmpTotal = new CL_TotEmp(source->EmpTotal);

	PlactE = new CL_TotEmp(source->PlactE);
	PlactP = new CL_TotEmp(source->PlactP);

	Immo = new CL_TotImmo(source->Immo);
	ImmoPetit = new CL_TotImmo(source->ImmoPetit);
	ImmoSom = new CL_TotImmo(source->ImmoSom);
	ImmoTotal = new CL_TotImmo(source->ImmoTotal);

	TotSub = new CL_TotSub(source->TotSub);
	Creance = new CL_TotEnCours(source->Creance);
	Dette = new CL_TotEnCours(source->Dette);

	memcpy(FraisOccc, source->FraisOccc, sizeof(float) * N_X);
	memcpy(Marge, source->Marge, sizeof(float) * N_X);
	memcpy(AutreDepense, source->AutreDepense, sizeof(float) * N_X);
	memcpy(AutreRecette, source->AutreRecette, sizeof(float) * N_X);
	memcpy(Solde, source->Solde, sizeof(float) * N_X);
	memcpy(SoldeCumul, source->SoldeCumul, sizeof(float) * N_X);

	Tva = new CL_TvaEnt(source->Tva);

	V_SurCulture = new CL_Vecteur<CL_Valeur>(source->V_SurCulture);
	V_SurVerger = new CL_Vecteur<CL_Valeur>(source->V_SurVerger);
	V_EffAnimaux = new CL_Vecteur<CL_Valeur>(source->V_EffAnimaux);

	memcpy(SurCulture, source->SurCulture, sizeof(float) * N_X);
	memcpy(SurVerger, source->SurVerger, sizeof(float) * N_X);
	memcpy(EffAnimaux, source->EffAnimaux, sizeof(float) * N_X);

	//ceg
	memcpy(deltaStock, source->deltaStock, sizeof(deltaStock));
	memcpy(deltaAvance, source->deltaAvance, sizeof(deltaAvance));
	memcpy(deltaValPlant, source->deltaValPlant, sizeof(deltaValPlant));
	memcpy(deltaVarInvAniRepro, source->deltaVarInvAniRepro,
			sizeof(deltaVarInvAniRepro));
	memcpy(deltaVarInvAniAutre, source->deltaVarInvAniAutre,
			sizeof(deltaVarInvAniAutre));
	memcpy(totProduit, source->totProduit, sizeof(totProduit));
	memcpy(totDepense, source->totDepense, sizeof(totDepense));
	memcpy(totChStruct, source->totChStruct, sizeof(totChStruct));
	memcpy(totCharge, source->totCharge, sizeof(totCharge));
	memcpy(resExercice, source->totCharge, sizeof(totCharge));
	//bilan
	memcpy(totImmo, source->totImmo, sizeof(totImmo));
	memcpy(tresorerie, source->tresorerie, sizeof(tresorerie));
	memcpy(perte, source->perte, sizeof(perte));
	memcpy(benefice, source->benefice, sizeof(benefice));
	memcpy(totActif, source->totActif, sizeof(totActif));
	memcpy(totPassif, source->totPassif, sizeof(totPassif));
	memcpy(capital, source->capital, sizeof(capital));
	memcpy(creanceTva, source->creanceTva, sizeof(creanceTva));
	memcpy(detteTva, source->detteTva, sizeof(detteTva));

	TresoIni = source->TresoIni;

}
//-----------------------------------------------------------------------------
void CL_AgriRes::creeVCat_Tot(CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vecteur) {
	CL_QuanVal *quanVal;
	CL_Categorie *categorie;

	for (int i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		quanVal = new CL_QuanVal(); //210202

		memset(quanVal->Qte, 0, sizeof(float) * N_X);
		memset(quanVal->Val, 0, sizeof(float) * N_X);

		quanVal->No = categorie->No;
		quanVal->Categorie = categorie;
		vecteur->insSans(quanVal);
	}
}

//---------------------------------------------------------------------------
CL_AgriRes::~CL_AgriRes(void) {
// a compléter
	Maz();
	delete V_Produit;
	V_Produit = NULL;
	delete V_Charge;
	V_Charge = NULL;

	delete V_Externalite;
	V_Externalite = NULL;
	delete V_ExtNeg;
	V_ExtNeg = NULL;
	delete V_ExtPos;
	V_ExtPos = NULL;

	delete V_ChStruct;
	V_ChStruct = NULL;
	delete V_RecDiv;
	V_RecDiv = NULL;
	delete V_DepDiv;
	V_DepDiv = NULL;
	delete V_RecFam;
	V_RecFam = NULL;
	delete V_DepFam;
	V_DepFam = NULL;

	delete V_CatProduitTot;
	V_CatProduitTot = NULL;
	delete V_CatChargeTot;
	V_CatChargeTot = NULL;

	delete V_CatExtNegTot;
	V_CatExtNegTot = NULL;
	delete V_CatExtPosTot;
	V_CatExtPosTot = NULL;

	delete V_CatChStructTot;
	V_CatChStructTot = NULL;

	delete V_CatRecDivTot;
	V_CatRecDivTot = NULL;
	delete V_CatDepDivTot;
	V_CatDepDivTot = NULL;

	delete V_CatRecFamTot;
	V_CatRecFamTot = NULL;
	delete V_CatDepFamTot;
	V_CatDepFamTot = NULL;

	delete EmpLTE;
	EmpLTE = NULL;
	delete EmpCTE;
	EmpCTE = NULL;
	delete EmpLTP;
	EmpLTP = NULL;
	delete EmpCTP;
	EmpCTP = NULL;
	delete EmpSomLT;
	EmpSomLT = NULL;
	delete EmpSomCT;
	EmpSomCT = NULL;
	delete EmpTotal;
	EmpTotal = NULL;

	delete PlactE;
	PlactE = NULL;
	delete PlactP;
	PlactP = NULL;

	delete Immo;
	Immo = NULL;
	delete ImmoPetit;
	ImmoPetit = NULL;
	delete ImmoSom;
	ImmoSom = NULL;
	delete ImmoTotal;
	ImmoTotal = NULL;

	delete TotSub;
	TotSub = NULL;
	delete Creance;
	Creance = NULL;
	delete Dette;
	Dette = NULL;

	delete V_SurCulture;
	V_SurCulture = NULL;
	delete V_SurVerger;
	V_SurVerger = NULL;
	delete V_EffAnimaux;
	V_EffAnimaux = NULL;
}
//---------------------------------------------------------------------------
void CL_AgriRes::Maz(void) {
	//Resultats
	V_Produit->purge();
	V_Charge->purge();

	V_Externalite->purge();
	V_ExtNeg->purge();
	V_ExtPos->purge();

	V_ChStruct->purge();
	V_RecDiv->purge();
	V_DepDiv->purge();
	V_RecFam->purge();
	V_DepFam->purge();

	//maZ le total par categorie

	MaZCat_Tot(V_CatProduitTot);
	MaZCat_Tot(V_CatChargeTot);

	MaZCat_Tot(V_CatExtNegTot);
	MaZCat_Tot(V_CatExtPosTot);

	MaZCat_Tot(V_CatChStructTot);

	MaZCat_Tot(V_CatRecDivTot);
	MaZCat_Tot(V_CatDepDivTot);

	MaZCat_Tot(V_CatRecFamTot);
	MaZCat_Tot(V_CatDepFamTot);

	//totaux          Rec Recette  Dep Depense
	memset(Produit, 0, sizeof(float) * N_X);
	memset(Charge, 0, sizeof(float) * N_X);

	memset(VenteAni, 0, sizeof(float) * N_X); //181201
	memset(AchatAni, 0, sizeof(float) * N_X); //181201
	memset(InvAniRepro, 0, sizeof(InvAniRepro)); //260903
	memset(InvAniAutre, 0, sizeof(InvAniAutre)); //260903

	memset(RecDiv, 0, sizeof(float) * N_X);
	memset(DepDiv, 0, sizeof(float) * N_X);

	memset(ChStruct, 0, sizeof(float) * N_X);

	memset(RecFam, 0, sizeof(float) * N_X);
	memset(DepFam, 0, sizeof(float) * N_X);

	memset(Stock, 0, sizeof(Stock));
	memset(StockIni, 0, sizeof(StockIni));
	memset(Avance, 0, sizeof(Avance));
	memset(ProdImmo, 0, sizeof(ProdImmo));
	memset(ProdImmoFam, 0, sizeof(ProdImmoFam));
	memset(AmorPlant, 0, sizeof(AmorPlant));
	memset(ValPlant, 0, sizeof(ValPlant));
	memset(PertePlant, 0, sizeof(PertePlant));

	EmpLTE->Maz(); //entreprise
	EmpCTE->Maz();
	EmpLTP->Maz(); //privé
	EmpCTP->Maz();

	EmpSomLT->Maz();
	EmpSomCT->Maz();
	EmpTotal->Maz();

	PlactE->Maz(); //entreprise
	PlactP->Maz();

	Immo->Maz();
	ImmoPetit->Maz();
	ImmoSom->Maz();
	ImmoTotal->Maz();

	TotSub->Maz();
	Creance->Maz();
	Dette->Maz();

	memset(FraisOccc, 0, sizeof(float) * N_X);
	memset(Marge, 0, sizeof(float) * N_X);
	memset(AutreRecette, 0, sizeof(float) * N_X);
	memset(AutreDepense, 0, sizeof(float) * N_X);
	memset(Solde, 0, sizeof(float) * N_X);
	memset(SoldeCumul, 0, sizeof(float) * N_X);

	//systeme de production
	V_SurCulture->purge();
	V_SurVerger->purge();
	V_EffAnimaux->purge();

	memset(SurCulture, 0, sizeof(float) * N_X);
	memset(SurVerger, 0, sizeof(float) * N_X);
	memset(EffAnimaux, 0, sizeof(float) * N_X);

	TresoIni = 0;

}
//---------------------------------------------------------------------------
void CL_AgriRes::MaZCat_Tot(CL_Vecteur<CL_QuanVal> *vecteur) {
	CL_QuanVal *quanVal;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		quanVal = vecteur->Vecteur[i];
		memset(quanVal->Qte, 0, sizeof(float) * N_X);
		memset(quanVal->Val, 0, sizeof(float) * N_X);
	}
}
//---------------------------------------------------------------------------
//CL_Agriculteur
//---------------------------------------------------------------------------
CL_Agriculteur::CL_Agriculteur() {
	No = 0;
	Nom = "";
	Notes = "";
	Supprimable = true;
	EstVariante = false;
	NoVariante = 0;
	NbVariante = 0;
	DefSim = new CL_AgriDefSim();
	Pere = NULL;
	TresoIni = 0;

//voir    CatBestiaux=NULL;         //290802
//voir    NoCatBestiaux=-1;
	TypeAgreg = SANS;

//    Ancetre->No=-1;
//    Ancetre->Agri=NULL;

	try {
		V_Culture = new CL_Vecteur<CL_Valeur>();
		V_Animaux = new CL_Vecteur<CL_Valeur>();
		V_Verger = new CL_Vecteur<CL_Verger>();
		V_Vivrier = new CL_Vecteur<CL_Verger>();
		LstTroupeaux = new TList;

		V_Produits = new CL_Vecteur<CL_Formule>();
		V_Charges = new CL_Vecteur<CL_Formule>();
		V_ChStruct = new CL_Vecteur<CL_Formule>();

		V_RecDiv = new CL_Vecteur<CL_Formule>();
		V_DepDiv = new CL_Vecteur<CL_Formule>();
		V_RecFam = new CL_Vecteur<CL_Formule>();
		V_DepFam = new CL_Vecteur<CL_Formule>();

		V_ExtPos = new CL_Vecteur<CL_Formule>();
		V_ExtNeg = new CL_Vecteur<CL_Formule>();

		V_Variable = new CL_Vecteur<CL_Valeur>();

		V_EmpLT = new CL_Vecteur<CL_EmpLT>();
		V_EmpCT = new CL_Vecteur<CL_EmpCT>();
		V_Sub = new CL_Vecteur<CL_Sub>();
		V_Plact = new CL_Vecteur<CL_Plact>();
		V_Occc = new CL_Vecteur<CL_Occc>();
		V_FinSom = new CL_Vecteur<CL_FN_Xp1>();
		V_InvSom = new CL_Vecteur<CL_FN_Xp1>();

		V_Immo = new CL_Vecteur<CL_Immo>();
		V_Petit = new CL_Vecteur<CL_Petit>();

		V_Creance = new CL_Vecteur<CL_EnCours>();
		V_Dette = new CL_Vecteur<CL_EnCours>();

		V_StockIni = new CL_Vecteur<CL_StockIni>();
		V_PrixRevient = new CL_Vecteur<CL_FN_Xp1>(); //150302
		V_PolStock = new CL_Vecteur<CL_PolStock>(); //300302
		V_ItemRepart = new CL_Vecteur<CL_ItemRepart>(); //180903

		LstCritere = new TList();
		LstVariante = new TList();
		LstPasse = new TList;
		LstQuantPrix = new TList(); //a recopier:!!!!!!
		TvaEntIni = new CL_TvaEntIni();
		PossibOcPlact = NULL; //150604
		QuanValPetit = new CL_QuanVal(PETITMAT);
		//QuanValPetit	=new CL_QuanVal(0);
	}
//    catch(bad_alloc)
	catch (Exception& err) {
		ShowMessage(err.Message);
	}
	TroupeauEnCours = NULL;
	Resultat = NULL;
}
//---------------------------------------------------------------------------
CL_Agriculteur::CL_Agriculteur(const CL_Agriculteur *agri) {
	int i;
	CL_Item *critere;
	ST_NoAgri *variante, *varianteA;
//CL_MvtAni *mvtAni0,*mvtAni;
	CL_QuantPrix *quantPrix, *quantPrix0;
	CL_Troupeau *troupeau, *troupeau0;
	CL_Passe *eltPasse0, *eltPasse;
	No = agri->No;
	Nom = agri->Nom;
	Notes = agri->Notes;
	Supprimable = agri->Supprimable;
	EstVariante = agri->EstVariante;
	NoVariante = agri->NoVariante;
//    NbVariante ??
	DefSim = new CL_AgriDefSim(agri->DefSim);
	Pere = agri->Pere;
	Resultat = agri->Resultat; //???
	EstVariante = agri->EstVariante;
	Pere = agri->Pere;
//voir    CatBestiaux     =agri->CatBestiaux;         //290802
//voir    NoCatBestiaux   =agri->NoCatBestiaux;
	TypeAgreg = agri->TypeAgreg;

	V_Culture = new CL_Vecteur<CL_Valeur>(agri->V_Culture);
	V_Animaux = new CL_Vecteur<CL_Valeur>(agri->V_Animaux);
	V_Verger = new CL_Vecteur<CL_Verger>(agri->V_Verger);
	V_Vivrier = new CL_Vecteur<CL_Verger>(agri->V_Vivrier);
//    V_InvAni        =new CL_Vecteur<CL_InvAni>(agri->V_InvAni );
	LstTroupeaux = new TList;
	for (i = 0; i < agri->LstTroupeaux->Count; i++) {
		troupeau0 = (CL_Troupeau*) agri->LstTroupeaux->Items[i];
		troupeau = new CL_Troupeau(troupeau0);
		LstTroupeaux->Add(troupeau);
	}
//test
	V_Produits = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_Produits, agri->V_Produits);

	V_Charges = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_Charges, agri->V_Charges);

	V_ChStruct = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_ChStruct, agri->V_ChStruct);

	V_RecDiv = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_RecDiv, agri->V_RecDiv);

	V_DepDiv = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_DepDiv, agri->V_DepDiv);

	V_RecFam = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_RecFam, agri->V_RecFam);

	V_DepFam = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_DepFam, agri->V_DepFam);

	V_ExtPos = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_ExtPos, agri->V_ExtPos);

	V_ExtNeg = new CL_Vecteur<CL_Formule>;
	RecopierFormule(V_ExtNeg, agri->V_ExtNeg);

	V_Variable = new CL_Vecteur<CL_Valeur>(agri->V_Variable);

	V_EmpLT = new CL_Vecteur<CL_EmpLT>(agri->V_EmpLT);
	V_EmpCT = new CL_Vecteur<CL_EmpCT>(agri->V_EmpCT);
	V_Sub = new CL_Vecteur<CL_Sub>(agri->V_Sub);
	V_Plact = new CL_Vecteur<CL_Plact>(agri->V_Plact);
	V_Occc = new CL_Vecteur<CL_Occc>(agri->V_Occc);
	V_FinSom = new CL_Vecteur<CL_FN_Xp1>(agri->V_FinSom);
	V_InvSom = new CL_Vecteur<CL_FN_Xp1>(agri->V_InvSom);

	V_Immo = new CL_Vecteur<CL_Immo>(agri->V_Immo);
	V_Petit = new CL_Vecteur<CL_Petit>(agri->V_Petit);

	V_Creance = new CL_Vecteur<CL_EnCours>(agri->V_Creance);
	V_Dette = new CL_Vecteur<CL_EnCours>(agri->V_Dette);

	V_StockIni = new CL_Vecteur<CL_StockIni>(agri->V_StockIni);
	V_PrixRevient = new CL_Vecteur<CL_FN_Xp1>(agri->V_PrixRevient); //150302
	V_PolStock = new CL_Vecteur<CL_PolStock>(agri->V_PolStock); //300302
	V_ItemRepart = new CL_Vecteur<CL_ItemRepart>(agri->V_ItemRepart); //300302

	LstCritere = new TList();
	LstVariante = new TList();
	LstPasse = new TList;
	LstQuantPrix = new TList();
	TvaEntIni = new CL_TvaEntIni(agri->TvaEntIni);
	PossibOcPlact = NULL;
	QuanValPetit = new CL_QuanVal(agri->QuanValPetit);

	if (agri->PossibOcPlact)
		PossibOcPlact = new CL_PossibOcPlact(agri->PossibOcPlact);

	for (int i = 0; i < agri->LstQuantPrix->Count; i++) {
		quantPrix0 = (CL_QuantPrix*) agri->LstQuantPrix->Items[i];
		quantPrix = new CL_QuantPrix(quantPrix0);
		LstQuantPrix->Add(quantPrix);
	}

	for (i = 0; i < agri->LstPasse->Count; i++) {
		eltPasse0 = (CL_Passe*) agri->LstPasse->Items[i];
		eltPasse = new CL_Passe(eltPasse0);
		LstPasse->Add(eltPasse);
	}
	TresoIni = agri->TresoIni;
	//recopier criteres
	for (int i = 0; i < agri->LstCritere->Count; i++) {
		critere = (CL_Item*) agri->LstCritere->Items[i];
		LstCritere->Add(critere);
	}
	//recopier variantes
	for (int i = 0; i < agri->LstVariante->Count; i++) {
		varianteA = (ST_NoAgri*) agri->LstVariante->Items[i];
		variante = new ST_NoAgri;
		memcpy(variante, varianteA, sizeof(ST_NoAgri));
		LstVariante->Add(variante);
	}
}
//---------------------------------------------------------------------------
void CL_Agriculteur::RecopierFormule(CL_Vecteur<CL_Formule>*vecteur,
		const CL_Vecteur<CL_Formule> *vSource) {
	int i;
	CL_Formule *formSource, *formule;
	for (i = 0; i < vSource->Nbelt; i++) {
		formSource = vSource->Vecteur[i];
		formule = new CL_Formule(formSource);
		vecteur->insSans(formule);
	}
}

//---------------------------------------------------------------------------
CL_Agriculteur::~CL_Agriculteur(void) {
	int i;
	CL_Troupeau *troupeau;
	if (DefSim)
		delete DefSim;
	DefSim = NULL;
	if (Resultat)
		delete Resultat;
	Resultat = NULL;

	V_Culture->purge();
	delete V_Culture;
	V_Culture = NULL;
	V_Animaux->purge();
	delete V_Animaux;
	V_Animaux = NULL;
	V_Verger->purge();
	delete V_Verger;
	V_Verger = NULL;
	V_Vivrier->purge();
	delete V_Vivrier;
	V_Vivrier = NULL;
	for (i = 0; i < LstTroupeaux->Count; i++) {
		troupeau = (CL_Troupeau*) LstTroupeaux->Items[i];
		delete troupeau;
	}
	delete LstTroupeaux;

	V_Produits->purge();
	delete V_Produits;
	V_Produits = NULL;
	V_Charges->purge();
	delete V_Charges;
	V_Charges = NULL;
	V_ChStruct->purge();
	delete V_ChStruct;
	V_ChStruct = NULL;

	V_RecDiv->purge();
	delete V_RecDiv;
	V_RecDiv = NULL;
	V_DepDiv->purge();
	delete V_DepDiv;
	V_DepDiv = NULL;
	V_RecFam->purge();
	delete V_RecFam;
	V_RecFam = NULL;
	V_DepFam->purge();
	delete V_DepFam;
	V_DepFam = NULL;

	V_ExtPos->purge();
	delete V_ExtPos;
	V_ExtPos = NULL;
	V_ExtNeg->purge();
	delete V_ExtNeg;
	V_ExtNeg = NULL;

	V_Variable->purge();
	delete V_Variable;
	V_Variable = NULL;

	V_Immo->purge();
	delete V_Immo;
	V_Immo = NULL;
	V_Petit->purge();
	delete V_Petit;
	V_Petit = NULL;
	V_InvSom->purge();
	delete V_InvSom;
	V_InvSom = NULL;

	V_EmpLT->purge();
	delete V_EmpLT;
	V_EmpLT = NULL;
	V_EmpCT->purge();
	delete V_EmpCT;
	V_EmpCT = NULL;
	V_Sub->purge();
	delete V_Sub;
	V_Sub = NULL;
	V_Occc->purge();
	delete V_Occc;
	V_Occc = NULL;
	V_Plact->purge();
	delete V_Plact;
	V_Plact = NULL;
	V_FinSom->purge();
	delete V_FinSom;
	V_FinSom = NULL;

	V_Creance->purge();
	delete V_Creance;
	V_Creance = NULL;
	V_Dette->purge();
	delete V_Dette;
	V_Dette = NULL;
	V_StockIni->purge();
	delete V_StockIni;
	V_StockIni = NULL;

	V_PrixRevient->purge();
	delete V_PrixRevient;
	V_PrixRevient = NULL;
	V_PolStock->purge();
	delete V_PolStock;
	V_PolStock = NULL;
	V_ItemRepart->purge();
	delete V_ItemRepart;
	V_ItemRepart = NULL;

	for (int i = 0; i < LstQuantPrix->Count; i++)
		delete (CL_QuantPrix *) LstQuantPrix->Items[i];
//    delete LstQuantPrix;

	for (int i = 0; i < LstVariante->Count; i++)
		delete (ST_NoAgri*) LstVariante->Items[i];
//    delete LstVariante;

	for (int i = 0; i < LstPasse->Count; i++)
		delete (CL_Passe*) LstPasse->Items[i];
//    delete LstPasse;

	delete TvaEntIni;
	TvaEntIni = NULL;

}
// 260902

//Est Ensemble
//---------------------------------------------------------------------------
void CL_Agriculteur::IniGlobal(void) {
	AnsiString debNom;
	debNom = AnsiString(Nom).SubString(1, 5);
	if (debNom == "TOTAL")
		Global = TOTAL;
	else if (debNom == "MOYEN")
		Global = MOYENNE;
	else
		Global = AGRI;
//Global est défini à ENSEMBLE quand on est dans les ensembles
//AGRI 18 TOTAL 1 MOYENNE 2 ENSEMBLE 3
}
//Nom variante
//---------------------------------------------------------------------------
AnsiString CL_Agriculteur::NomV(void) {
	AnsiString nom;
	if (NoVariante == 0)
		return Nom;

	nom = Nom + "  " + IntToStr(NoVariante);
	return nom;

}
//Nom variante critères
//---------------------------------------------------------------------------
AnsiString CL_Agriculteur::NomVC(void) {
	AnsiString nom;
	CL_Item *critere;
	if (NoVariante == 0)
		nom = Nom;
	else
		nom = Nom + "  " + IntToStr(NoVariante);
	for (int i = 0; i < LstCritere->Count; i++) {
		critere = (CL_Item*) LstCritere->Items[i];
		nom = nom + "  ";
		nom = nom + critere->Nom;
	}
	return nom;
}
//---------------------------------------------------------------------------
void CL_Agriculteur::Maz(void) {

}

//----------------------------------------------------------------------------
void CL_Agriculteur::SupMaFalse(void) {
	int i, j, n;
	CL_Item *critere;
	CL_Troupeau *troupeau;
	CL_InvAni *invAni;
	CL_Atelier *atelier;
	for (int j = 0; j < LstCritere->Count; j++) {
		critere = (CL_Item*) LstCritere->Items[j];
		critere->Supprimable = false;
		critere->Categorie->Supprimable = false;
	}

	for (i = 0; i < V_Culture->Nbelt; i++)
		V_Culture->Vecteur[i]->Atelier->Supprimable = false;
	for (i = 0; i < V_Animaux->Nbelt; i++)
		V_Animaux->Vecteur[i]->Atelier->Supprimable = false;
	for (i = 0; i < V_Verger->Nbelt; i++)
		V_Verger->Vecteur[i]->Atelier->Supprimable = false;
	for (i = 0; i < V_Vivrier->Nbelt; i++)
		V_Vivrier->Vecteur[i]->Atelier->Supprimable = false;

	for (i = 0; i < LstTroupeaux->Count; i++) //131003
			{
		troupeau = (CL_Troupeau*) LstTroupeaux->Items[i];
		troupeau->CatBestiaux->Supprimable = false;
		for (j = 0; j < troupeau->V_InvAni->Nbelt; j++) {
			invAni = troupeau->V_InvAni->Vecteur[j];
			{
				for (n = 0; n < N_X; n++) {
					atelier = invAni->Atelier[n];
					if (atelier)
						atelier->Supprimable = false;
				}
			}
		}
	}
	FormuleSupMaFalse(V_Produits);
	FormuleSupMaFalse(V_Charges);
	FormuleSupMaFalse(V_ChStruct);

	FormuleSupMaFalse(V_RecDiv);
	FormuleSupMaFalse(V_DepDiv);
	FormuleSupMaFalse(V_RecFam);
	FormuleSupMaFalse(V_DepFam);

	FormuleSupMaFalse(V_ExtPos);
	FormuleSupMaFalse(V_ExtNeg);

	for (i = 0; i < V_Variable->Nbelt; i++)
		V_Variable->Vecteur[i]->Item->Supprimable = false;

	for (i = 0; i < V_Creance->Nbelt; i++)
		V_Creance->Vecteur[i]->Item->Supprimable = false;
	for (i = 0; i < V_Dette->Nbelt; i++)
		V_Dette->Vecteur[i]->Item->Supprimable = false;

}
//----------------------------------------------------------------------------
void CL_Agriculteur::FormuleSupMaFalse(CL_Vecteur<CL_Formule>*vecteur) {
	int i;
	CL_Formule *formule;
	for (i = 0; i < vecteur->Nbelt; i++) {
		formule = vecteur->Vecteur[i];
		if (formule->Item == NULL)
			continue;
		formule->Item->Supprimable = false;
		formule->Item->Categorie->Supprimable = false;
		//270902
		/*
		 for(j=0;j<N_X;j++)vu[j]=false;
		 for(j=0;j<N_X;j++)
		 {
		 if(vu[j]==true) continue;

		 prog=formule->LesProg[j];
		 if(prog==NULL)
		 {
		 bidon=0;
		 continue; //!!!!!!!!
		 }
		 arbre=prog->Arbre;
		 for(k=0;k< arbre->BrancheX;k++)
		 {
		 branche=arbre->LesBranches[k];
		 if(branche.code!=IDENT) continue;
		 elt=Compil->trouveElt(branche.arg[0],branche.arg[1],branche.arg[2]);
		 if(elt==NULL)
		 {
		 bidon=0;
		 }
		 elt->Item->Supprimable=false;
		 }
		 vu[j]=true;
		 for(k=j+1;k<N_X;k++)
		 {
		 if(formule->LesProg[k]==prog) vu[k]=true;
		 }
		 }
		 */
	}
}

//---------------------------------------------------------------------------
//CL_AgriEff
//---------------------------------------------------------------------------
CL_AgriEff::CL_AgriEff(CL_Agriculteur *agri) {
	Agri = agri;
	Nom = Agri->Nom;
	NoAgri = Agri->No;
	Notes = "";
	memset(Effectif, 0, sizeof(int) * N_X);
}
//---------------------------------------------------------------------------
CL_AgriEff::CL_AgriEff(CL_AgriEff *agriEff) {
	Agri = agriEff->Agri;
	Nom = agriEff->Agri->Nom;
	NoAgri = Agri->No;
	Notes = "";
	memcpy(Effectif, agriEff->Effectif, sizeof(int) * N_X);
}
//---------------------------------------------------------------------------
//CL_Ensemble
//---------------------------------------------------------------------------
CL_Ensemble::CL_Ensemble() {
	V_AgriEff = new CL_Vecteur<CL_AgriEff>();
	Notes = "";
	Ancetre = new (ST_NoEnsemble);
	Total = new CL_Agriculteur();
	EstVariante = false;
	LstVariante = new TList();

}
//---------------------------------------------------------------------------
CL_Ensemble::CL_Ensemble(const CL_Ensemble *ens) {
	EstVariante = false;
	Ancetre = new ST_NoEnsemble;
	memcpy(Ancetre, ens->Ancetre, sizeof(ST_NoEnsemble));

	Nom = ens->Nom;
	No = ens->No;
	Notes = ens->Notes;
	V_AgriEff = new CL_Vecteur<CL_AgriEff>(ens->V_AgriEff);
	Total = new CL_Agriculteur();
	LstVariante = new TList();

}

//---------------------------------------------------------------------------
// CL_Elt
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(void) {
	NoFamille = 0;
	NoCategorie = 0;
	NoType = 0;
	NoItem = 0;
//    NoIndic=     0;
	Poste = NULL;
	Item = NULL;
//    Indic=       NULL;
	Categorie = NULL;
	Nom = "";
	NomCat = "";
	NomFamille = "";
	Unite = "";
	Valeur = NULL;
	Pcent = NULL;
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::~CL_Elt(void) {
	if (Pcent) {
		delete[] Pcent;
		Pcent = NULL;
	}
	if (Passe) {
		delete[] Passe;
		Passe = NULL;
	}
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Elt *elt) {
	No = elt->No;
//    int           Cmp(CL_Elt *ptr){ return 0;};//non utilisé
	Flag = elt->Flag;
	NoFamille = elt->NoFamille; //PRODUIT CHARGE RECDIV...INDIC  cf olympedec.h
	NoCategorie = elt->NoCategorie; //seult pour produit charge irrigation
	NoType = elt->NoType;
	NoItem = elt->NoItem;
	NoEspece = elt->NoEspece;
	NoEtat = elt->NoEtat;
	Poste = elt->Poste;
	Item = elt->Item;
	Etat = elt->Etat;
	Categorie = elt->Categorie;
	Espece = elt->Espece;
	Nom = elt->Nom;
	NomCat = elt->NomCat;
	NomFamille = elt->NomFamille;
	Unite = elt->Unite;
	Valeur = elt->Valeur;
	Pcent = elt->Pcent;
	VMin = elt->VMin;
	VMax = elt->VMax;
	Passe = NULL;
	if (elt->Passe) {
		Passe = new float[5];
		memcpy(Passe, elt->Passe, sizeof(float) * 5);
	}

}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste) {
	NoFamille = POSTE;
	NoCategorie = -1;
	NoItem = poste->No;
	NoType = 0;
	Poste = poste;
	Item = NULL;
	Categorie = NULL;
//	Indic=       NULL;
	Nom = Poste->Nom.c_str();
	NomCat = "";
	NomFamille = ""; //Poste->Nom.c_str();
	NomCat = "";
	Unite = "";
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, CL_Categorie *categorie, CL_Item *item) {
	NoFamille = poste->No;
	NomFamille = poste->Nom.c_str();
	//pour utilisation dans TVChoixElt dans Indic
	NoCategorie = categorie->No;
	NoType = 0;
	Categorie = categorie;
	NomCat = categorie->Nom.c_str();
	NoItem = item->No;
	Item = item;
	Nom = Item->Nom.c_str();
	Unite = "";
	Poste = poste;
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;

}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, int noType, CL_Categorie *categorie,
		CL_Item *item) {
	NoFamille = poste->No;
	NomFamille = poste->Nom.c_str();
	//pour utilisation dans TVChoixElt dans Indic
	NoCategorie = categorie->No;
	NoType = noType;
	Categorie = categorie;
	NomCat = categorie->Nom.c_str();
	NoItem = item->No;
	Item = item;
	Nom = Item->Nom.c_str();
	Unite = "";
	Poste = poste;
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;

}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, CL_Categorie *categorie, CL_Indicateur *indic) {
	NoFamille = poste->No;
	NoCategorie = categorie->No;
	NoType = 0;
	NoItem = indic->No;
	Poste = poste;
	Item = NULL;
	Categorie = categorie;
//    Indic=       indic;
	Nom = indic->Nom.c_str();
	NomCat = categorie->Nom.c_str();
	NomFamille = poste->Nom.c_str();
	Unite = "";
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;

}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, CL_Categorie *categorie, CL_Atelier *atelier) {
//cultures et vivriers
	NoFamille = poste->No;
	NoCategorie = categorie->No;
	NoType = 0;
	NoEspece = 0;
	NoItem = atelier->No;
	Poste = poste;
	Item = NULL;
	Categorie = categorie;
	Nom = atelier->Nom.c_str();
	NomCat = categorie->Nom.c_str();
	NomFamille = poste->Nom.c_str();
	Unite = "";
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, CL_Espece *espece, CL_Atelier *atelier) {
//perenne
	NoFamille = poste->No;
	NoCategorie = espece->No; //!!!
	NoType = 0;
	NoEspece = espece->No;
	NoItem = atelier->No;
	Poste = poste;
	Item = NULL;
	Categorie = (CL_Categorie*) espece;
	Nom = atelier->Nom.c_str();
	NomCat = espece->Nom.c_str();
	NomFamille = poste->Nom.c_str();
	Unite = "";
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, CL_Item *item) {
	NoFamille = poste->No;
	NoCategorie = -1;
	NoType = 0;
	NoItem = item->No;
	Poste = poste;
	Item = item;
	Categorie = NULL;
//	Indic=       NULL;
	Nom = Item->Nom.c_str();
	NomCat = "";
	NomFamille = poste->Nom.c_str();
	Unite = "";
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, CL_Categorie *categorie) {
	NoFamille = poste->No;
	NomFamille = poste->Nom.c_str();

	NoCategorie = categorie->No;
	NoType = 0;
	Categorie = categorie;
	NomCat = categorie->Nom.c_str();

	NoItem = -1;
	Poste = poste;
	Unite = "";
	Item = NULL;
//    Nom=         NULL;
	Nom = "  ";
	Pcent = NULL;
	Valeur = NULL; //130302
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(CL_Poste *poste, char *nom, int no) {
	NoFamille = poste->No;
	NoCategorie = -1;
	NoType = 0;
	NoItem = no;
	Poste = poste;
	Item = NULL;
	Categorie = NULL;
	Nom = nom;
	NomCat = "";
	NomFamille = poste->Nom.c_str();
	Unite = "";
	Pcent = NULL;
	Valeur = NULL; //261101
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(int type) {
	NoFamille = FORME;
	NoCategorie = -1;
	NoType = 0;
	NoItem = type;
	Poste = NULL;
	Item = NULL;
	Categorie = NULL;
	Nom = "";
	NomCat = "";
	NomFamille = "Mise En Forme";
	Unite = "";
	if (type == TRAIT)
		Nom = "_______";
	else if (type == TITRE)
		NomFamille = "Titre";
	Pcent = NULL;
	Passe = NULL;
}
//---------------------------------------------------------------------------
CL_Elt::CL_Elt(char *nomFamille) {
	NoFamille = 0;
	NoCategorie = 0;
	NoType = 0;
	NoItem = 0;
	Poste = NULL;
	Item = NULL;
	Categorie = NULL;
	Nom = "";
	NomCat = "";
	NomFamille = nomFamille;
	Unite = "";
	Pcent = NULL;
	Passe = NULL;
}

//----------------------------------------------------------------------------
AnsiString CL_Elt::Donne_Nom(void) {
	AnsiString as;
	if (NoFamille == INDIC)
		return AnsiString("Ind: ") + Nom; //211002 //230103
	if (Poste) {
		switch (Poste->No) {
		case CULTURE:
		case PERENNE:
		case VIVRIER:
		case ANIMAUX:
		case BILAN:
		case CEG:
		case POSTE:
			return AnsiString(Nom);
		case IMMO:
		case EMP:
		case EMPLT:
		case EMPCT:
			as = AnsiString(NomFamille) + " : " + AnsiString(Nom);
			return as;
		case MVT:
			as = NomTypeMvtAni(NoType);
			/*
			 switch(NoType)
			 {
			 case EFF:     as="Effectifs";   break;
			 case EFFV:    as="Eff Vendus";  break;
			 case EFFA:    as="Eff Achetés"; break;
			 case VALV:    as="Val Ventes";  break;
			 case VALA:    as="Val Achats";  break;
			 case VALINV:  as="Val Inv";    break;
			 }
			 */
			as = as + ":" + AnsiString(NomCat) + ":" + AnsiString(Nom);
			return as;
		default:
			as = Poste->Nom;
			break;
		}
	} else
		as = NomFamille;
	if (Item) {
		as = as + " :" + Item->Nom;
		return as;
	}
	return as;
}
//----------------------------------------------------------------------------
//AnsiString CL_Elt::Donne_Unite(void)
char* CL_Elt::Donne_Unite(void) //121103
		{
	CL_SystemeUnite *sysUnite;
	switch (NoFamille) {
	case POSTE:
	case MARGE:
	case PRODUIT:
	case CHARGE:
	case CHSTRUCT:
	case RECDIV:
	case DEPDIV:
	case RECFAM:
	case DEPFAM:
	case PPRODUIT:
	case PCHARGE:
	case SOLDE:
	case SOLDECUMUL:
	case FINANCE:
	case IMMO:
	case AVANCE:
	case STOCK:
	case PRODIMMO:
	case EMP:
	case EMPLT:
	case EMPCT:

	case AMOR:
	case VALRESID:
	case VALACHAT:
	case VALBRUT:

	case ANNUITE:
	case REMB:
	case INTERET:
	case NOUVEMP:
	case VALV:
	case VALA:
	case VALINV:
	case BILAN:
	case CEG:
		sysUnite = SysMonnaie;
		break;

	case QPRODUIT:
	case QCHARGE:
		//item=elt->Item;
		sysUnite = Item->SysUnite;
		break;
	case EFF:
	case EFFV:
	case EFFA:
		return "tête";
	case CULTURE:
	case PERENNE:
	case VIVRIER:
		return "ha";
	case ANIMAUX:
		return "tête";
	case MVT:
		return "tête"; //121103
		//modifier void CL_ES::EcrireEtatSortie et lire
		// je n'ecris pas NoType
		/*
		 switch(NoType)
		 {
		 case EFF:
		 case EFFV:
		 case EFFA:   return "tête";
		 case VALV:
		 case VALA:
		 case VALINV: return SysMonnaie->UTrans.c_str();
		 }
		 */
	default:
		return "  ";

	}
	if (Global == AGRI || Global == MOYENNE)
		return sysUnite->UTrans.c_str();
	else
		return sysUnite->UGlobal.c_str();

}
//----------------------------------------------------------------------------
AnsiString CL_Elt::NomTypeMvtAni(int noType) {
	switch (noType) {
	case EFF:
		return "Effectifs";
	case EFFV:
		return "Eff Vendus";
	case EFFA:
		return "Eff Achetés";
	case VALV:
		return "Val Ventes";
	case VALA:
		return "Val Achats";
	case VALINV:
		return "Val Inv";
	default:
		return "?????";
	}
}
//----------------------------------------------------------------------------
CL_EtatSortie::CL_EtatSortie() {
	Supprimable = true;
	V_Elt = new CL_Vecteur<CL_Elt>;
}
//----------------------------------------------------------------------------
CL_EtatSortie::CL_EtatSortie(CL_EtatSortie *etat) {
	Supprimable = true;
	Nom = etat->Nom;
	No = etat->No;
	NoCategorie = etat->NoCategorie;
	Categorie = etat->Categorie;
	V_Elt = new CL_Vecteur<CL_Elt>(etat->V_Elt);

}
//---------------------------------------------------------------------------
CL_EtatSortie::~CL_EtatSortie(void) {
	delete V_Elt;
	V_Elt = NULL;

}
// A COMPLETER
//----------------------------------------------------------------------------
CL_Indicateur::CL_Indicateur() {
	Supprimable = true;
	Nom = "";
	No = 0;
	NoSysteme = 0;
	SysUnite = NULL;
	Prog = new CL_Prog;
	Compile = false;
	Calcule = false;
	memset(Valeur, 0, sizeof(Valeur));
}
//----------------------------------------------------------------------------
CL_Indicateur::CL_Indicateur(CL_Indicateur *indicateur) {
	Supprimable = true;
	Nom = indicateur->Nom;
	No = indicateur->No;
	NoCategorie = indicateur->NoCategorie;
	Categorie = indicateur->Categorie;
	NoSysteme = indicateur->NoSysteme;
	SysUnite = indicateur->SysUnite;
	Prog = new CL_Prog(indicateur->Prog);
	Compile = false;
	Calcule = false;
	memset(Valeur, 0, sizeof(Valeur));
}
//---------------------------------------------------------------------------
CL_Indicateur::~CL_Indicateur(void) {

}
//---------------------------------------------------------------------------
//   Arbre Reseau
//---------------------------------------------------------------------------
CL_Arbre::CL_Arbre(int n, int delta) {
	BrancheMax = n;
	BrancheX = 0;
	LesBranches = new ST_Branche[BrancheMax];
	Delta = delta;
}
//---------------------------------------------------------------------------
CL_Arbre::CL_Arbre(CL_Arbre *Ancien) {
	int n;
	if (Ancien == NULL)
		return; //080303
	BrancheMax = Ancien->BrancheMax;
	BrancheX = Ancien->BrancheX;
	LesBranches = new ST_Branche[BrancheMax];
	Delta = Ancien->Delta;
	for (n = 0; n < BrancheX; n++) {
		LesBranches[n].code = Ancien->LesBranches[n].code;
		LesBranches[n].arg[0] = Ancien->LesBranches[n].arg[0];
		LesBranches[n].arg[1] = Ancien->LesBranches[n].arg[1];
		LesBranches[n].arg[2] = Ancien->LesBranches[n].arg[2];
		LesBranches[n].valeur = Ancien->LesBranches[n].valeur;
		LesBranches[n].type = Ancien->LesBranches[n].type;
		LesBranches[n].date = Ancien->LesBranches[n].date;
	}
	//    memcpy(LesBranches,Ancien->LesBranches,sizeof(Ancien->LesBranches));
}
//---------------------------------------------------------------------------
CL_Arbre::~CL_Arbre() {
	BrancheMax = 0;
	BrancheX = 0;
	delete LesBranches;
}
//---------------------------------------------------------------------------
bool CL_Arbre::EstIdentique(CL_Arbre *arbre) {
	ST_Branche branche, brancheAutre;
	int n;
	if (BrancheX != arbre->BrancheX)
		return false;
	for (n = 0; n < BrancheX; n++) {
		branche = LesBranches[n];
		brancheAutre = arbre->LesBranches[n];
		if (branche.code != brancheAutre.code)
			return false;
		if (branche.arg[0] != brancheAutre.arg[0])
			return false;
		if (branche.arg[1] != brancheAutre.arg[1])
			return false;
		if (branche.arg[2] != brancheAutre.arg[2])
			return false;
		if (branche.type != brancheAutre.type)
			return false;
		if (branche.date != brancheAutre.date)
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool CL_Arbre::EstNumerique(void) {
	ST_Branche branche;
	if (BrancheX != 1)
		return false;
	branche = LesBranches[0];
//    if(branche.code!=NOMBRE) return false;
//   Compilateur.h                A Modifier
//  enum {  ERREUR=300,NOMBRE,NUM,BOOLEEN,FIN,INFEG,SUPEG,MUNAIRE,PONT,

	if (branche.code != 301)
		return false;
	return true;
}
//---------------------------------------------------------------------------
bool CL_Arbre::ContientIndic(void) {
	ST_Branche branche;
	int n;
	if (BrancheX != 1)
		return false;
	for (n = 0; n < BrancheX; n++) {
		branche = LesBranches[n];
		if (branche.arg[0] == INDIC)
			return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void CL_Arbre::MetIndicNonSupprimable(void) {
	CL_Indicateur *indic;
	ST_Branche branche;
	int n;
	if (BrancheX != 1)
		return;
	for (n = 0; n < V_Indicateur->Nbelt; n++)
		indic = V_Indicateur->Vecteur[n];
	for (n = 0; n < BrancheX; n++) {
		branche = LesBranches[n];
		if (branche.code != INDIC)
			continue;

		indic = V_Indicateur->trouve(branche.arg[2]);
		indic->Supprimable = false;
	}
	return;
}

//---------------------------------------------------------------------------
CL_Reseau::CL_Reseau(int n, int delta) {
	MailleMax = n;
	MailleX = 0;
	LesMailles = new ST_Maille[MailleMax];
	Delta = delta;
}
//---------------------------------------------------------------------------
CL_Reseau::CL_Reseau(CL_Reseau *Ancien) {
	if (Ancien == NULL)
		return; //080303
	MailleMax = Ancien->MailleX;
	MailleX = Ancien->MailleX;
	LesMailles = new ST_Maille[MailleX];
	Delta = Ancien->Delta;
	memcpy(LesMailles, Ancien->LesMailles, sizeof(ST_Maille) * Ancien->MailleX);
}
//---------------------------------------------------------------------------
CL_Reseau::~CL_Reseau() {
	MailleMax = 0;
	MailleX = 0;
	delete LesMailles;
}
//---------------------------------------------------------------------------
bool CL_Reseau::EstIdentique(CL_Reseau *reseau) {
	ST_Maille maille, mailleAutre;
	int n;
	if (MailleX != reseau->MailleX)
		return false;
	for (n = 0; n < MailleX; n++) {
		maille = LesMailles[n];
		mailleAutre = reseau->LesMailles[n];
		if (maille.code != mailleAutre.code)
			return false;
		if (maille.branche != mailleAutre.branche)
			return false;
		if (maille.apG != mailleAutre.apG)
			return false;
		if (maille.apD != mailleAutre.apD)
			return false;
	}
	return true;
}
//-----------------------------------------------------------
CL_Delta::CL_Delta() {
	Item = NULL;
	NoItem = 0;
	Atelier = NULL;
	NoAtelier = 0;
	Nature = 0;
	Rdt = 0.;
	for (int i = 0; i < N_X; i++)
		Pcent[i] = 100.;
//    memset(Pcent,100,sizeof(float)*N_X);
}
//-----------------------------------------------------------
CL_Tendance::CL_Tendance() {
	Nom = "";
	Supprimable = true;
	V_Delta = new CL_Vecteur<CL_Delta>();
}
//-----------------------------------------------------------
CL_Tendance::CL_Tendance(CL_Tendance *tend) {
	No = tend->No;
	Nom = tend->Nom;
	Supprimable = true;
	V_Delta = new CL_Vecteur<CL_Delta>(tend->V_Delta);
}
//-----------------------------------------------------------
CL_Tendance::~CL_Tendance() {
	Nom = "";
	Supprimable = true;
	V_Delta->purge();
}
//------------------ ------------------------------------------------------------
CL_AgriDefSim::CL_AgriDefSim() {
	TDateTime time;
	unsigned short a, m, j;

	time = TDateTime::CurrentDate();
	time.DecodeDate(&a, &m, &j);
//    EstAgrege=false;   //130302
	An_0 = a; //début simulation
	No = 0; //ne sert à rien quand utilisé par CL_Agri
	NbAnSim = N_X; //nb année simulation
	MDeb = 1; //mois
	AnCalage = 0;
	TypeAlea = SANS; //SANS TENDANCE ENCHDEF ENCHALEA MCARLO
	NoPrixProd = -1;
	NoPrixCharge = -1;
	NoQProd = -1;
	NoQCharge = -1;
	NoQExt = -1;
	strcpy(Enchainement, "AAAAAAAAAA");

	TouSPrixProd = 0; // 0 Aucun 1 Tendance 2 Scénario
	TouSPrixCharge = 0;
	TouSQProd = 0;
	TouSQCharge = 0;
	TouSQExt = 0;

	PrixProd = NULL;
	PrixCharge = NULL;
	QProd = NULL;
	QCharge = NULL;
	QExt = NULL;

	TPProd = NULL;
	TPCharge = NULL;
	TQProd = NULL;
	TQCharge = NULL;
	TQExt = NULL;
}
//------------------ ------------------------------------------------------------
CL_AgriDefSim::CL_AgriDefSim(CL_AgriDefSim *autre) {
	An_0 = autre->An_0;
	NbAnSim = autre->NbAnSim;
	MDeb = autre->MDeb;
	AnCalage = autre->AnCalage;
	TypeAlea = autre->TypeAlea;

	TouSPrixProd = autre->TouSPrixProd;
	TouSPrixCharge = autre->TouSPrixCharge;
	TouSQProd = autre->TouSQProd;
	TouSQCharge = autre->TouSQCharge;
	TouSQExt = autre->TouSQExt;

	NoPrixProd = autre->NoPrixProd;
	NoPrixCharge = autre->NoPrixCharge;
	NoQProd = autre->NoQProd;
	NoQCharge = autre->NoQCharge;
	NoQExt = autre->NoQExt;

	strcpy(Enchainement, autre->Enchainement);

	PrixProd = NULL;
	PrixCharge = NULL;
	QProd = NULL;
	QCharge = NULL;
	QExt = NULL;
	if (autre->PrixProd)
		PrixProd = autre->PrixProd;
	if (autre->PrixCharge)
		PrixCharge = autre->PrixCharge;
	if (autre->QProd)
		QProd = autre->QProd;
	if (autre->QCharge)
		QCharge = autre->QCharge;
	if (autre->QExt)
		QExt = autre->QExt;

	TPProd = NULL;
	TPCharge = NULL;
	TQProd = NULL;
	TQCharge = NULL;
	TQExt = NULL;
}
//------------------ ------------------------------------------------------------
void CL_AgriDefSim::SupMaFalse(void) {
	if (PrixProd)
		PrixProd->Supprimable = false;
	if (PrixCharge)
		PrixCharge->Supprimable = false;
	if (QProd)
		QProd->Supprimable = false;
	if (QCharge)
		QCharge->Supprimable = false;
	if (QExt)
		QExt->Supprimable = false;
}
//------------------ ------------------------------------------------------------
CL_MvtAni::CL_MvtAni(int noAnimal, int date, int type, int eff, float info) {
	NoAnimal = noAnimal;
	Type = type;
	Date = date;
	Eff = eff;
	Info = info;
}
//------------------ ------------------------------------------------------------
CL_MvtAni::CL_MvtAni(CL_MvtAni *mvtAni) {
	NoAnimal = mvtAni->NoAnimal;
	Type = mvtAni->Type;
	Date = mvtAni->Date;
	Eff = mvtAni->Eff;
	Info = mvtAni->Info;
}
//------------------ ------------------------------------------------------------
CL_Conversion::CL_Conversion() {
	NoBase = SysMonnaie->No;
	Base = SysMonnaie;

	NoSortie = SysMonnaie->No;
	Sortie = SysMonnaie;
	for (int i = 0; i < N_X; i++)
		TauxConvFrancVersEuro[i] = 1;
	for (int i = 0; i < N_X; i++)
		TauxConvEuroVersFranc[i] = 1;
}

CL_Conversion::CL_Conversion(CL_SystemeUnite *base, CL_SystemeUnite *sortie) {
	Base = base;
	NoBase = base->No;
	Sortie = sortie;
	NoSortie = sortie->No;
	for (int i = 0; i < N_X; i++)
		TauxConvFrancVersEuro[i] = 1;
	for (int i = 0; i < N_X; i++)
		TauxConvEuroVersFranc[i] = 1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
CL_IntFloat::CL_IntFloat() {
	i = 0;
	Val = 0;
}
//---------------------------------------------------------------------------
CL_IntFloat::CL_IntFloat(int n, float v) {
	i = n;
	Val = v;
}
//---------------------------------------------------------------------------
CL_IntFloat::CL_IntFloat(CL_IntFloat *source) {
	i = source->i;
	Val = source->Val;
}
//---------------------------------------------------------------------------
void CL_IntFloat::FichierEcrire(FILE* fichier) {
	fwrite(&i, sizeof(int), 1, fichier);
	fwrite(&Val, sizeof(float), 1, fichier);

}
//---------------------------------------------------------------------------
void CL_IntFloat::FichierLire(FILE* fichier) {
	fread(&i, sizeof(int), 1, fichier);
	fread(&Val, sizeof(float), 1, fichier);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CL_Repart::CL_Repart() {
	Nom = "";
	LstPcent = new TList;
}
//---------------------------------------------------------------------------
CL_Repart::CL_Repart(CL_Repart *source) {
	int i;
	CL_IntFloat *moisVal;
	Nom = source->Nom;
	NoCategorie = source->NoCategorie;
	Categorie = source->Categorie;
	LstPcent = new TList;
	for (i = 0; i < source->LstPcent->Count; i++) {
		moisVal = (CL_IntFloat *) source->LstPcent->Items[i];
		LstPcent->Add(new CL_IntFloat(moisVal));
	}
}
//---------------------------------------------------------------------------
CL_Repart::~CL_Repart() {
	LstPcent->Clear();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int CL_Repart::Cmp(CL_Repart *source) {
	return (Nom.AnsiCompare(source->Nom));
}
// lire la grille
//---------------------------------------------------------------------------
float CL_Repart::LireTotal(TStringGrid *SG) {
	int c, r;
	float val;
	float total;

	total = 0.;
	for (c = 1; c < 4; c++) {
		for (r = 1; r < 13; r++) {
			val = LireCell(SG, c, r);
			total += val;
		}
	}
	return total;
}
//---------------------------------------------------------------------------
float CL_Repart::Total(void) {
	int i;
	float total;
	CL_IntFloat *moisVal;
	for (i = 0; i < LstPcent->Count; i++) {
		moisVal = (CL_IntFloat *) LstPcent->Items[i];
		total += moisVal->Val;
	}
	return total;
}
//---------------------------------------------------------------------------
void CL_Repart::GrilleEcrire(TStringGrid* sg, float valTot) {
	int i, r, c;
	int mois;
	CL_IntFloat *moisVal;
	for (c = 1; c < 4; c++)
		for (r = 1; r < 13; r++)
			sg->Cells[c][r] = "";
	for (i = 0; i < LstPcent->Count; i++) {
		moisVal = (CL_IntFloat *) LstPcent->Items[i];
		mois = moisVal->i;
		if (mois < 13) {
			c = 1;
			r = mois;
		} else if (mois < 25) {
			c = 2;
			r = mois - 12;
		} else {
			c = 3;
			r = mois - 24;
		}
		sg->Cells[c][r] = Aff(moisVal->Val);
		if (sg->ColCount < 7)
			continue;
		c += 3;
		sg->Cells[c][r] = Aff(valTot * moisVal->Val / 100., 0);
	}
}
//---------------------------------------------------------------------------
AnsiString CL_Repart::Aff(float x) {
	int y;
	if (x == 0)
		return AnsiString(" "); //"" ou " "      ????
	y = x;
	if (y == x)
		return FloatToStrF((double) x, ffNumber, 7, 0);
	else
		return FloatToStrF((double) x, ffNumber, 7, 2);
}
//---------------------------------------------------------------------------
AnsiString CL_Repart::Aff(float x, int digits) {
	if (x == 0)
		return AnsiString(" "); //"" ou " "      ????
	return FloatToStrF((double) x, ffNumber, 7, digits);
}
//---------------------------------------------------------------------------
void CL_Repart::GrilleLire(TStringGrid* SG) {
	int c, r;
	CL_IntFloat *moisVal;
	float val;
	LstPcent->Clear();
	for (c = 1; c < 4; c++) {
		for (r = 1; r < 13; r++) {
			val = LireCell(SG, c, r);
			if (val == 0)
				continue;
			moisVal = new CL_IntFloat((c - 1) * 12 + r, val);
			LstPcent->Add(new CL_IntFloat(moisVal));
		}
	}
}
//---------------------------------------------------------------------------
float CL_Repart::LireCell(TStringGrid* SG, int col, int row) {
	return as2float(SG->Cells[col][row]);
}
//---------------------------------------------------------------------------
float CL_Repart::as2float(AnsiString as) {
	int n, c;
	char car;
	char chaine[20];
	bool negatif = false;
	float val;
	as = as.Trim();
	n = as.Length();
	if (n == 0)
		return 0.;
	c = 0;
	for (n = 0; n < as.Length(); n++) {
		car = as[n + 1];
		if (car == '-') {
			negatif = true;
			continue;
		}
		if (car >= '0' && car <= '9')
			chaine[c++] = car;
		else if (car == '.')
			chaine[c++] = car;
	}
	chaine[c] = 0;
	val = atof(chaine);
	if (negatif == true)
		return -val;
	else
		return val;
}
//---------------------------------------------------------------------------
void CL_Repart::FichierEcrire(FILE *fichier) {
	int i, n;
	int l;
	AnsiString s;
	CL_IntFloat *dateVal;
	fwrite(&No, sizeof(int), 1, fichier);

	//fwriteString      a supprimer
	s = Nom.Trim();
	l = s.Length();
	fwrite(&l, sizeof(int), 1, fichier);
	fwrite(s.c_str(), sizeof(char) * (l + 1), 1, fichier);

	fwrite(&NoCategorie, sizeof(int), 1, fichier);
	n = LstPcent->Count;
	fwrite(&n, sizeof(int), 1, fichier);
	for (i = 0; i < LstPcent->Count; i++) {
		dateVal = (CL_IntFloat*) LstPcent->Items[i];
		dateVal->FichierEcrire(fichier);
	}
}
//---------------------------------------------------------------------------
void CL_Repart::FichierLire(FILE *fichier) {
	int i, n;
	int l;
	char chaine[100];
	AnsiString s;
	CL_IntFloat *dateVal;
	fread(&No, sizeof(int), 1, fichier);

	//freadString      a supprimer
	fread(&l, sizeof(int), 1, fichier);
	fread(chaine, sizeof(char) * (l + 1), 1, fichier);
	Nom = AnsiString(chaine);

	fread(&NoCategorie, sizeof(int), 1, fichier);
	Categorie = V_CatRepart->trouve(NoCategorie);
	LstPcent = new TList;
	fread(&n, sizeof(int), 1, fichier);
	for (i = 0; i < n; i++) {

		dateVal = new CL_IntFloat();
		dateVal->FichierLire(fichier);
		LstPcent->Add(dateVal);
	}
}

