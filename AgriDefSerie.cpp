//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Aide.h"

#include "AgriDefSerie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAgriDefSerieFrm *AgriDefSerieFrm;
//---------------------------------------------------------------------------
__fastcall TAgriDefSerieFrm::TAgriDefSerieFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void TAgriDefSerieFrm::DefSerie(CL_Agriculteur *agriDepart, int nbAnSim) {
	int n, nSerie;
	int an_0;
	ST_NoAgri *noAgri;

	agriDepart->DefSim->NbAnSim = nbAnSim;

	nSerie = nbAnSim / 10; //nombre de series de simulation
	an_0 = agriDepart->DefSim->An_0;

	agriDepart->LstSerie = new TList;

	noAgri = new ST_NoAgri;
	noAgri->No = agriDepart->No;
	noAgri->Agri = agriDepart;
	agriDepart->LstSerie->Add(noAgri);

	//creer les ST_NoAgri pour séries de simulation à la suite
	for (n = 1; n < nSerie; n++) {

		noAgri = new ST_NoAgri;
		noAgri->No = 0;
		noAgri->Agri = NULL;
		//noAgri structure le no de l'agri pour stocker
		//et retrouver à la lecture
		// ptr sur Agri
		// seront créés + tard   aprés modif éventuelle dans la decade initiale
		// voir TAgriDefSimFrm::LBResultatPourClick(TObject *Sender)
		agriDepart->LstSerie->Add(noAgri);
	}
//    agriDepart->Nom=agriDepart->Nom+ "  "+an_0+"-"+AnsiString(an_0+9);//191207

}
/*
 //---------------------------------------------------------------------------
 void TAgriDefSerieFrm::DefSerie(CL_Agriculteur *agriDepart,int nbAnSim)
 {
 int n,nSerie;
 int an_0;
 CL_Agriculteur *agriBis;
 CL_AgriDefSim *defSim;
 ST_NoAgri *noAgri;

 agriDepart->DefSim->NbAnSim=nbAnSim;

 nSerie=    nbAnSim/10 ;       //nombre de series de simulation
 an_0=      agriDepart->DefSim->An_0;

 agriDepart->LstSerie=new TList;

 noAgri=new ST_NoAgri;
 noAgri->No=agriDepart->No;
 noAgri->Agri=agriDepart;
 agriDepart->LstSerie->Add(noAgri);

 //creer les agri pour séries de simulation à la suite
 for(n=1;n<nSerie+1;n++)
 {
 agriBis=new CL_Agriculteur(agriDepart); //copie et copie de DefSim
 CopieCulture(agriBis,agriDepart);     //culture animaux Bestiaux

 V_Agriculteur->ins(agriBis);            //ins et incremente agri->No

 noAgri=new ST_NoAgri;
 noAgri->No=agriBis->No;
 noAgri->Agri=agriBis;
 //noAgri structure le no de l'agri pour stocker
 //et retrouver à la lecture
 // otr sur Agri
 agriDepart->LstSerie->Add(noAgri);
 }
 // modifie les noms en ajoutant 2006-2015 n-  n+9
 for(n=1;n<agriDepart->LstSerie->Count;n++)
 {
 noAgri=(ST_NoAgri*)agriDepart->LstSerie->Items[n];
 agriBis=noAgri->Agri;
 defSim=agriBis->DefSim;
 defSim->An_0=an_0+10*n;
 agriBis->Resultat=NULL;
 agriBis->LstSerie=agriDepart->LstSerie;
 agriBis->Nom=agriDepart->Nom+ "  "+defSim->An_0+"-"+AnsiString(defSim->An_0+9);

 }
 agriDepart->Nom=agriDepart->Nom+ "  "+an_0+"-"+AnsiString(an_0+9);

 }
 /*
 //---------------------------------------------------------------------------
 /*
 agriAvant les 10 années qui précèdent
 noAgri pour l'agri créé a compléter
 */
//---------------------------------------------------------------------------
void TAgriDefSerieFrm::DefAgriApres(CL_Agriculteur *agriPrec,
		ST_NoAgri *noAgri) {
	CL_Agriculteur *agri;
	AnsiString as;
	int n;
	int anFin;
	agri = new CL_Agriculteur(agriPrec); //copie et copie de DefSim
	agri->NoSerie = agriPrec->NoSerie + 1;
	agri->EstPlus10Ans = true; //191207
	agri->EstVariante = agriPrec->EstVariante; //071008
	V_Agriculteur->ins(agri); //ins et incremente agri->No
	CopieCulture(agri, agriPrec); //culture animaux Bestiaux

	noAgri->No = agri->No;
	noAgri->Agri = agri;

	agri->DefSim->An_0 = agriPrec->DefSim->An_0 + 10;
	agri->Resultat = NULL;
	agri->LstSerie = agriPrec->LstSerie;

	agri->Nom = agriPrec->Nom;
}
//---------------------------------------------------------------------------
// on augmente la duréé
//---------------------------------------------------------------------------
void TAgriDefSerieFrm::DefSeriePlus(CL_Agriculteur *agri, int nbAnSim) {
	int n, nSerie, nSerie0;
	int an_0; //,anFin;
	CL_Agriculteur *agriDepart, *agriBis;
	ST_NoAgri *noAgri;
	AnsiString as, asNom;
	noAgri = (ST_NoAgri*) agri->LstSerie->Items[0];

	agriDepart = noAgri->Agri;
	agriDepart->DefSim->NbAnSim = nbAnSim;

	nSerie = nbAnSim / 10;
	an_0 = agriDepart->DefSim->An_0;

	nSerie0 = agriDepart->LstSerie->Count;
	//creer les agri pour séries de simulation à la suite
	for (n = nSerie0; n < nSerie; n++) {
		agriBis = new CL_Agriculteur(agriDepart); //copie et copie de DefSim
		V_Agriculteur->ins(agriBis); //ins et incremente agri->No

		noAgri = new ST_NoAgri;
		noAgri->No = agriBis->No;
		noAgri->Agri = agriBis;
		//noAgri structure le no de l'agri pour stocker
		//et retrouver à la lecture
		// otr sur Agri
		agriDepart->LstSerie->Add(noAgri);
	}
	// modifie les noms en ajoutant 2006-2015 n-  n+9
	/*
	 as=agriDepart->Nom;
	 n=as.Length();
	 asNom=as.SubString(1,n-9);
	 */
	for (n = 0; n < agriDepart->LstSerie->Count; n++) {
		noAgri = (ST_NoAgri*) agriDepart->LstSerie->Items[n];
		agriBis = noAgri->Agri;
		agriBis->DefSim->An_0 = an_0;
//        anFin=an_0+9;
		agriBis->DefSim->NbAnSim = nbAnSim;
		agriBis->Resultat = NULL;
		agriBis->LstSerie = agriDepart->LstSerie;
		agriBis->Nom = agriDepart->Nom;
		//agriBis->Nom=asNom
		//    +agriBis->DefSim->An_0+"-"+AnsiString(agriBis->DefSim->An_0+9);
		an_0 += 10;
	}
}
//---------------------------------------------------------------------------
// on diminue la durée
//---------------------------------------------------------------------------
void TAgriDefSerieFrm::DefSerieMoins(CL_Agriculteur *agri, int nbAnSim) {
	int n, nSerie, nSerie0;
//int an_0;
	CL_Agriculteur *agriDepart, *agriBis;
//CL_AgriDefSim *defSim;
	ST_NoAgri *noAgri;
	noAgri = (ST_NoAgri*) agri->LstSerie->Items[0];

	agriDepart = noAgri->Agri;
	agriDepart->DefSim->NbAnSim = nbAnSim;

	nSerie = nbAnSim / 10;
//    an_0=      agriDepart->DefSim->An_0;

	nSerie0 = agriDepart->LstSerie->Count;

	// on avait nSerie0  on a plus que nSerie ->supprimer
	for (n = nSerie; n < nSerie0; n++) {
		noAgri = (ST_NoAgri*) agriDepart->LstSerie->Items[n];
		agriBis = noAgri->Agri;
		V_Agriculteur->sup(agriBis);
//        delete agriBis;
//        delete noAgri;
		// voir defSim=agriBis->DefSim;
	}

	agriDepart->LstSerie->Count = nSerie;
	for (n = 1; n < agriDepart->LstSerie->Count; n++) {
		noAgri = (ST_NoAgri*) agriDepart->LstSerie->Items[n];
		agriBis = noAgri->Agri;
		agriBis->LstSerie = agriDepart->LstSerie;
		agriBis->DefSim->NbAnSim = nbAnSim;
	}
//test
	for (n = 0; n < agriDepart->LstSerie->Count; n++) {
		noAgri = (ST_NoAgri*) agriDepart->LstSerie->Items[n];
		agriBis = noAgri->Agri;
	}
}
//---------------------------------------------------------------------------
// copier assol derniere annee id° animaux
//---------------------------------------------------------------------------
void TAgriDefSerieFrm::CopieCulture(CL_Agriculteur *agriBis,
		CL_Agriculteur *agriDepart) //culture animaux Bestiaux
		{
	int i, n;
	CL_Valeur *valeurD, *valeurBis;
	for (i = 0; i < agriDepart->V_Culture->Nbelt; i++) {
		valeurD = agriDepart->V_Culture->Vecteur[i];
		valeurBis = agriBis->V_Culture->Vecteur[i];
		for (n = 0; n < N_X; n++)
			valeurBis->Valeur[n] = valeurD->Valeur[N_X - 1];
	}
	for (i = 0; i < agriDepart->V_Animaux->Nbelt; i++) {
		valeurD = agriDepart->V_Animaux->Vecteur[i];
		valeurBis = agriBis->V_Animaux->Vecteur[i];
		for (n = 0; n < N_X; n++)
			valeurBis->Valeur[n] = valeurD->Valeur[N_X - 1];
	}
}
