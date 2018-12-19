//-------------------------------- -------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <dir.h>
#include <vcl.h>
#include <stdio.h>
using namespace std;

#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
//#include "Brouillon.h"
#include "SortieEcran.h"

//#include "ChoixCritere.h"
#include "Compilateur.h"

//extern
#include "Olympe.hse"
#include "LesVecteurs.hse"
// A CORRIGER ?
// envoi dans memo1 qui doit servir pour pour notes . stocké ???
//

//---------------------------------------------------------------------------
void CL_ES::ImpFichierAscii(void) {

	char nomFichier[MAXPATH];
	char sortieNom[MAXPATH];
	char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT];
	AnsiString date;
	TDateTime time;

	strncpy(nomFichier, FEcriture.c_str(), MAXPATH);
// Construire le nom du fichier.Txt */
	fnsplit(nomFichier, drive, dir, name, ext);
	fnmerge(sortieNom, drive, dir, name, ".txt");

	ofstream outfile(sortieNom);
//char chaine[100];

	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();

	outfile << date.c_str() << endl;

	outfile << sortieNom << endl;

	ImpSysUnit(outfile);
	ImpTva(outfile);

	ImpCategorie(outfile, V_CatProduit, "V_CatProduit");
	ImpItem(outfile, V_Produit, "V_Produit");

	ImpCategorie(outfile, V_CatCharge, "V_CatCharge");
	ImpItem(outfile, V_Charge, "V_Charge");

	ImpCategorie(outfile, V_CatExternalite, "V_CatExternalite");
	ImpItem3(outfile, V_Externalite, "V_Externalite");

	ImpCalendrier(outfile, V_Calendrier, "V_Calendrier");

	ImpCategorie(outfile, V_CatCulture, "V_CatCulture");
	ImpAtelier(outfile, V_Culture, "V_Culture");
	ImpLesAteliers(outfile, V_Culture);

	ImpCategorie(outfile, V_CatAnimaux, "V_CatAnimaux");
	ImpAtelier(outfile, V_Animaux, "V_Animaux");
	ImpLesAteliers(outfile, V_Animaux);

	ImpCategorie(outfile, V_CatVivrier, "V_CatVivrier");
	ImpAtelier(outfile, V_Vivrier, "V_Vivrier");
	ImpLesAteliers(outfile, V_Vivrier);

	ImpEspece(outfile);
	ImpAtelier(outfile, V_Perenne, "V_Perenne");
	ImpLesAteliers(outfile, V_Perenne);

	ImpCategorie(outfile, V_CatChStruct, "V_CatChStruct");
	ImpItem2(outfile, V_ChStruct, "V_Chstruct");

	ImpCategorie(outfile, V_CatRecDiv, "V_CatRecDiv");
	ImpItem2(outfile, V_RecDiv, "V_Recdiv");

	ImpCategorie(outfile, V_CatDepDiv, "V_CatDepDiv");
	ImpItem2(outfile, V_DepDiv, "V_DepDiv");

	ImpCategorie(outfile, V_CatRecFam, "V_CatRecFam");
	ImpItem2(outfile, V_RecFam, "V_RecFam");

	ImpCategorie(outfile, V_CatDepFam, "V_CatDepFam");
	ImpItem2(outfile, V_DepFam, "V_DepFam");

	// types zone
	ImpCategorie(outfile, V_CatTypeZone, "V_CatTypeZone");
	ImpItem4(outfile, V_TypeZone, "V_TypeZone");

	ImpLesIndicateurs(outfile);

	ImpCategorie(outfile, V_CatEtatSortie, "V_CatEtatSortie");
	ImpLesEtatSortie(outfile);

	ImpTendance(outfile, V_TendPrixProd, V_Produit, "V_TendPrixProd");
	ImpTendance(outfile, V_TendPrixCharge, V_Charge, "V_TendPrixCharge");
	ImpTendance(outfile, V_ScenPrixProd, V_Produit, "V_ScenPrixProd");
	ImpTendance(outfile, V_ScenPrixCharge, V_Charge, "V_ScenPrixCharge");

	ImpTendance(outfile, V_TendQProd, V_Produit, "V_TendQProd");
	ImpTendance(outfile, V_TendQCharge, V_Charge, "V_TendQCharge");
	ImpTendance(outfile, V_ScenQProd, V_Produit, "V_ScenQProd");
	ImpTendance(outfile, V_ScenQCharge, V_Charge, "V_ScenQCharge");
	ImpTendance(outfile, V_TendQExt, V_Externalite, "V_TendQExt");
	ImpTendance(outfile, V_ScenQExt, V_Externalite, "V_ScenQExt");

//    ImpLesAgri();

}
//-------------------------------------------------------------------
void CL_ES::ImpSysUnit(ofstream &outfile) {
	CL_SystemeUnite *sysUnit;
	char buf[100];
	CL_Vecteur<CL_SystemeUnite> *vecteur = V_SystemeUnite;

	outfile << "V_SystemeUnite" << endl;
	sprintf(buf, " Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "N°   UUt  UTrans UGlobal" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		sysUnit = vecteur->Vecteur[i];
		sprintf(buf, "%3d %-6.6s %-6.6s %-6.6s", sysUnit->No, sysUnit->UUt,
				sysUnit->UTrans, sysUnit->UGlobal);
		outfile << buf << endl;
	}
	outfile << endl;
	/*
	 int    No;
	 float  Ratio;    //Utrans/UUt
	 float  RatioG;   //Uglobal/UUt
	 AnsiString Nom;
	 AnsiString UUt;       //unite de rdt ou d'utilisation UTILISATION
	 AnsiString UTrans;    //unite de vente ou d'achat     TRANSACTION
	 AnsiString UGlobal;   //unite pour résultat d'ensemble
	 */
}
//-------------------------------------------------------------------
void CL_ES::ImpTva(ofstream &outfile) {
	CL_Tva *tva;
	char buf[100];
	CL_Vecteur<CL_Tva> *vecteur = V_Tva;

	outfile << "V_Tva" << endl;
	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "  No  Nom Taux" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		tva = vecteur->Vecteur[i];
		sprintf(buf, "%3d %-20.20s %6.2f ", tva->No, tva->Nom, tva->Taux);
		outfile << buf << endl;
	}
	outfile << endl;
}
//----------------------------------------------------------------------------
void CL_ES::ImpCategorie(ofstream &outfile, CL_Vecteur<CL_Categorie> *vecteur,
		char *titre) {
	CL_Categorie *categorie;
	char buf[100];

	outfile << endl;
	outfile << titre << endl;
	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	if (vecteur->Nbelt == 0)
		return;

	outfile << "  No       NOM" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		categorie = vecteur->Vecteur[i];
		sprintf(buf, "%3d %-20.20s", categorie->No, categorie->Nom);
		outfile << buf << endl;
	}
	outfile << endl;
}
//-------------------------------------------------------------------
void CL_ES::ImpItem(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur,
		char *titre) {
	CL_Item *item;
	char buf[100];

	outfile << titre << endl;
	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "  No  NoCategorie " << endl;
	outfile << "          NoSysteme " << endl;
	outfile << "              NoTva " << endl;
	outfile << "                  Prix NOM" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		sprintf(buf, "%3d %3d %3d %3d %6.2f      %-20.20s", item->No,
				item->NoCategorie, item->NoSysteme, item->NoTva, item->Prix,
				item->Nom);
		outfile << buf << endl;
	}
	outfile << endl;
}
//-------------------------------------------------------------------
void CL_ES::ImpItem2(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur,
		char *titre) {
	CL_Item *item;
	char buf[100];
	if (vecteur->Nbelt == 0)
		return;

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "  No  NoCategorie NoTva  NOM" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		sprintf(buf, "%3d %3d %3d  %-20.20s", item->No, item->NoCategorie,
				item->NoTva, item->Nom);
		outfile << buf << endl;
	}
}
//-------------------------------------------------------------------
void CL_ES::ImpItem3(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur,
		char *titre) {
	int i;
	CL_Item *item;
	char buf[100];

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "  No  NoCategorie NoSysteme  NOM" << endl;
	for (i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		sprintf(buf, "%3d %3d %3d  %-20.20s", item->No, item->NoCategorie,
				item->NoSysteme, item->Nom);
		outfile << buf << endl;
	}
}
//-------------------------------------------------------------------
void CL_ES::ImpItem4(ofstream &outfile, CL_Vecteur<CL_Item> *vecteur,
		char *titre) {
	CL_Item *item;
	char buf[100];

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "  No  NoCategorie NOM" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		sprintf(buf, "%3d %3d  %-20.20s", item->No, item->NoCategorie,
				item->Nom);
		outfile << buf << endl;
	}
}
//-------------------------------------------------------------------------
void CL_ES::ImpCalendrier(ofstream &outfile, CL_Vecteur<CL_Calendrier> *vecteur,
		char *titre) {
	char buf[100];
	int i, j;
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	int nbPeriode;
	outfile << titre << endl;
	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	for (i = 0; i < vecteur->Nbelt; i++) {
		calendrier = vecteur->Vecteur[i];
		outfile << "    " << calendrier->No << calendrier->Nom.c_str() << endl;
		sprintf(buf, "Nbelt=%2d  NoX=%2d", calendrier->V_Periode->Nbelt,
				calendrier->V_Periode->NoX);
		outfile << "    " << buf << endl;
		nbPeriode = calendrier->V_Periode->Nbelt;
		for (j = 0; j < nbPeriode; j++) {
			periode = calendrier->V_Periode->Vecteur[j];
			sprintf(buf, "%3d %-20.20s %3d%3d  %3d%3d   %3d %3d ", periode->No,
					periode->Nom, periode->JDeb, periode->MDeb, periode->JFin,
					periode->MFin, periode->PcentDispo, periode->HpJ);
			outfile << "    " << buf << endl;
		}
		outfile << endl;
	}
}
//-------------------------------------------------------------------------
void CL_ES::ImpAtelier(ofstream &outfile, CL_Vecteur<CL_Atelier> *vecteur,
		char *titre) {
	char buf[100];
	CL_Atelier *atelier;

	outfile << titre << endl;
	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "  i No Nature" << endl;
	outfile << "            NoEspece " << endl;
	outfile << "                NbPhase " << endl;
	outfile << "                    NoCategorie Nom" << endl;
	outfile << "                      Nom" << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		sprintf(buf, "%3d %3d %3d %3d %3d %3d %-20.20s", i, atelier->No,
				atelier->Nature, atelier->NoEspece, atelier->NbPhase,
				atelier->NoCategorie, atelier->Nom);
		outfile << buf << endl;
	}
	outfile << endl;
}
//-------------------------------------------------------------------------
void CL_ES::ImpLesAteliers(ofstream &outfile, CL_Vecteur<CL_Atelier> *vecteur) {

	CL_Atelier *atelier;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		outfile << atelier->Nom.c_str() << "  " << atelier->No << endl;
		ImpAtelierItem(outfile, atelier, atelier->V_Produit, "V_Produit");
		ImpAtelierItem(outfile, atelier, atelier->V_Charge, "V_Charge");
		//impAtelierItem(atelier->V_ChargeVolume);
		ImpAtelierItem(outfile, atelier, atelier->V_Externalite,
				"V_Externalite");
		ImpAtelierBesTrav(outfile, atelier, atelier->V_BesTrav, "V_BesTrav");

		outfile << endl;
	}
}
/*
 //-------------------------------------------------------------------------
 void CL_ES::ImpAtelierItem(ofstream &outfile,CL_Vecteur<CL_ItemParAtelier>*vecteur,char *titre)
 {
 int i,nbelt;
 CL_ItemParAtelier *itemPA;
 char buf[200];
 nbelt=vecteur->Nbelt;
 if(nbelt==0) return;
 outfile <<"    "<<titre << endl;
 outfile <<"    "<<"item->No NoItem" << endl;

 for(i=0;i<nbelt;i++)
 {
 itemPA=vecteur->Vecteur[i];
 sprintf(buf,"%3d %3d ",itemPA->No,itemPA->NoItem);
 outfile << buf << endl;
 }
 }
 */
//--------------------------------------------------------------------------
void CL_ES::ImpAtelierItem(ofstream &outfile, CL_Atelier *atelier,
		CL_Vecteur<CL_ItemParAtelier> *vecteur, char *titre) {
	int i, n, nbelt;
	CL_ItemParAtelier *itemPA;
	char buf[200];
	nbelt = vecteur->Nbelt;
	if (nbelt == 0)
		return;
	outfile << "    " << titre << endl;
	outfile << "    " << "item->No NoItem" << endl;

	for (i = 0; i < nbelt; i++) {
		itemPA = vecteur->Vecteur[i];
		sprintf(buf, "%3d %3d ", itemPA->No, itemPA->NoItem);
		outfile << buf << "     ";
		for (n = 0; n < atelier->NbPhase; n++) {
			outfile << itemPA->QtePhase[n];
			outfile << "  ";
		}
		outfile << endl;
	}
}
//--------------------------------------------------------------------------
void CL_ES::ImpAtelierBesTrav(ofstream &outfile, CL_Atelier *atelier,
		CL_Vecteur<CL_BesTrav> *vecteur, char *titre) {
	int i;
	CL_BesTrav *besTrav;
	char buf[100];
	outfile << titre << endl;
	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << "NbPhase No" << endl;
	for (i = 0; i < vecteur->Nbelt; i++) {
		besTrav = vecteur->Vecteur[i];
		outfile << besTrav->NbPhase << "  " << besTrav->No << endl;
	}
	outfile << endl;
}
/*
 //-------------------------------------------------------------------
 void CL_ES::ImpEspece(ofstream &outfile)
 {
 ShowMessage("Revoir impEspece");
 int nbelt;
 CL_Espece *espece;
 CL_Vecteur<CL_Espece> *vecteur;
 char buf[100],buf2[100];
 AnsiString as;
 int i,j;
 vecteur=V_Espece;
 FBrouillon->Memo1->Lines->Add("____________");
 FBrouillon->Memo1->Lines->Add("Les Especes");

 sprintf(buf,"Nbelt=%2d  NoX=%2d",vecteur->Nbelt,vecteur->NoX);
 FBrouillon->Memo1->Lines->Add(buf);

 for(i=0;i<vecteur->Nbelt;i++)
 {
 vecteur->Vecteur[i];
 espece= vecteur->Vecteur[i];
 sprintf(buf," %2d %-20.20s %2d %2d %2d   ",
 espece->No,espece->Nom,espece->DebAmor,espece->DurAmor,espece->NbPhase);
 as=buf;
 for(j=0;j<espece->NbPhase;j++)
 {
 sprintf(buf2,"%2d  ",espece->Phase[j]);
 as+=buf2;
 }
 FBrouillon->Memo1->Lines->Add(as.c_str());
 }
 }
 */
//-------------------------------------------------------------------
void CL_ES::ImpEspece(ofstream &outfile) {
	CL_Espece *espece;
	CL_Vecteur<CL_Espece> *vecteur;
	char buf[100], buf2[100];
	AnsiString as;
	int i, j;
	vecteur = V_Espece;
	outfile << " Les Especes " << endl;

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;

	for (i = 0; i < vecteur->Nbelt; i++) {
		vecteur->Vecteur[i];
		espece = vecteur->Vecteur[i];
		sprintf(buf, " %2d %-20.20s %2d %2d %2d   ", espece->No, espece->Nom,
				espece->DebAmor, espece->DurAmor, espece->NbPhase);
		as = buf;
		for (j = 0; j < espece->NbPhase; j++) {
			sprintf(buf2, "%2d  ", espece->Phase[j]);
			as += buf2;
		}
		outfile << buf << endl;
	}
	outfile << endl;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void CL_ES::ImpLesIndicateurs(ofstream &outfile) {
	CL_Indicateur *indic;
	char buf[100];
	CL_Vecteur<CL_Indicateur> *vecteur = V_Indicateur;
	outfile << "Les Indicateurs" << endl;

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;

	outfile << endl;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		indic = vecteur->Vecteur[i];
		ImpIndic(outfile, indic);
	}
}
//-------------------------------------------------------------------
void CL_ES::ImpIndic(ofstream &outfile, CL_Indicateur *indic) {
	char buf[100];

	outfile << endl;
	outfile << indic->Nom << endl;
	sprintf(buf, "No NoCategorie type %2d %2d ", indic->No, indic->NoCategorie);
	outfile << buf << endl;

	if (indic->Prog->Arbre == NULL)
		outfile << "Pas d'arbre" << endl;
	else
		ImpArbre(outfile, indic->Prog->Arbre);

	if (indic->Prog->Reseau == NULL)
		outfile << "Pas de réseau" << endl;
	else
		ImpReseau(outfile, indic->Prog->Reseau);

	outfile << endl;
}
//-------------------------------------------------------------------
void CL_ES::ImpArbre(ofstream &outfile, CL_Arbre *arbre) {
	int n;
	char buf[100];
	ST_Branche b;
	sprintf(buf, "Arbre->BrancheX %2d ", arbre->BrancheX);
	outfile << buf << endl;
	sprintf(buf, "n  code,         arg[0],arg[1],arg[2],valeur,type,date");
	outfile << buf << endl;
	for (n = 0; n < arbre->BrancheX; n++) {
		b = arbre->LesBranches[n];
		sprintf(buf, "%3d   %-9.9s   %3d %3d %3d  %6.0f %-9.9s %3d", n,
				nomSymbole(b.code), b.arg[0], b.arg[1], b.arg[2], b.valeur,
				nomSymbole(b.type), b.date);
		outfile << buf << endl;
	}
}
//-------------------------------------------------------------------
void CL_ES::ImpReseau(ofstream &outfile, CL_Reseau *reseau) {
	int n;
	char buf[100];
	ST_Maille m;
	sprintf(buf, "Reseau->MailleX %2d ", reseau->MailleX);
	outfile << buf << endl;
	sprintf(buf, "code,branche,apG,apD");
	outfile << buf << endl;
	for (n = 0; n < reseau->MailleX; n++) {
		m = reseau->LesMailles[n];
		sprintf(buf, " %-9.9s   %3d     %3d %3d ", nomSymbole(m.code),
				m.branche, m.apG, m.apD);
		outfile << buf << endl;
	}
}
//----------------------------------------------------------------------------
char* CL_ES::nomSymbole(int n) {
	static char chaine[10];

	if (n < 256) {
		memset(chaine, ' ', sizeof(chaine));
		chaine[9] = 0;
		chaine[3] = (char) n;
		return chaine;
	}
	switch (n) {
	case ERREUR:
		return "ERREUR";
	case NOMBRE:
		return "NOMBRE";
	case NUM:
		return "NUM";
	case IDENT:
		return "IDENT";
	case FIN:
		return "FIN";
	case INFEG:
		return "INFEG";
	case SUPEG:
		return "SUPEG";
	case MUNAIRE:
		return "MUNAIRE";
	case ET:
		return "ET";
	case OU:
		return "OU";
	case SI:
		return "SI";
	case SINON:
		return "SINON";
	case SINONSI:
		return "SINONSI";
	case BOOLEEN:
		return "BOOLEEN";
	case PONT:
		return "PONT";
	default:
		return "????";
	}
}
//-------------------------------------------------------------------------
void CL_ES::ImpLesEtatSortie(ofstream &outfile) {
	CL_EtatSortie *etat;
//CL_Elt  *elt;
	char buf[100];
	CL_Vecteur<CL_EtatSortie> *vecteur = V_EtatSortie;
//CL_Vecteur<CL_Elt> *v_Elt;

	outfile << "Les Etats de Sortie" << endl;

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	outfile << "No NoCat Nom" << endl;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		etat = vecteur->Vecteur[i];
		sprintf(buf, "%2d  %2d  %-20.20s", etat->No, etat->NoCategorie,
				etat->Nom);
		outfile << buf << endl;
	}
}
/*
 for(int i=0;i<vecteur->Nbelt;i++)
 {
 etat=vecteur->Vecteur[i];
 sprintf(buf,"%2d  %2d  %-20.20s",etat->No,etat->NoCategorie,etat->Nom);
 outfile << buf << endl;
 v_Elt=etat->V_Elt;
 for(int j=0;j<v_Elt->Nbelt;j++)
 {
 elt=v_Elt->Vecteur[j];
 if(elt->NoItem==TITRE)
 {
 sprintf(buf,"TITRE %-20.20s",elt->Nom);
 outfile << buf << endl;
 }
 else
 {
 sprintf(buf,"%2d   %2d %2d %2d",elt->No,elt->NoFamille,
 elt->NoCategorie,elt->NoItem);
 outfile << buf << endl;
 }
 }
 }
 */
//-------------------------------------------------------------------------
void CL_ES::ImpTendance(ofstream &outfile, CL_Vecteur<CL_Tendance> *vecteur,
		CL_Vecteur<CL_Item> *vItem, char *titre) {
	int i, j, k;
//int nbelt,nbDelta;
	CL_Tendance* tendance;
	CL_Delta* delta;
	CL_Vecteur<CL_Delta> *vDelta;
	char buf[100];
	AnsiString as;

	outfile << endl;
	outfile << titre << endl;

	sprintf(buf, "Nbelt=%2d  NoX=%2d", vecteur->Nbelt, vecteur->NoX);
	outfile << buf << endl;
	if (vecteur->Nbelt == 0)
		return;

	outfile << "  No  NoCategorie NoSysteme  NOM" << endl;

	for (i = 0; i < vecteur->Nbelt; i++) {
		tendance = vecteur->Vecteur[i];
		sprintf(buf, "%2d %-20.20s", tendance->No, tendance->Nom);
		outfile << buf << endl;

		vDelta = tendance->V_Delta;
		sprintf(buf, "nbDelta=%2d  NoX=%2d", vDelta->Nbelt, vDelta->NoX);
		outfile << buf << endl;
		for (j = 0; j < vDelta->Nbelt; j++) {
			delta = vDelta->Vecteur[j];
			sprintf(buf, "%2d %2d %2d %2d", delta->No, delta->NoItem,
					delta->NoAtelier, delta->Nature);
			as = buf;
			sprintf(buf, "   %-20.20s", delta->Item->Nom);
			as += buf;
			if (delta->Nature) {
				sprintf(buf, "   %-20.20s", delta->Atelier->Nom);
				as += buf;
			}
			for (k = 0; k < N_X; k++) {
				sprintf(buf, "%4.0f", delta->Pcent[k]);
				as += buf;
			}
			outfile << as << endl;
		}
	}
}
/*
 //-------------------------------------------------------------------------
 void CL_ES::ImpLesAgri(void)
 {
 int n;
 CL_Agriculteur *agri;
 // imprimer nbelt noX...
 for(n=0;n<V_Agriculteur->Nbelt;n++)
 {
 agri=V_Agriculteur->Vecteur[n];
 ImpAgri(agri);
 }
 }
 //-------------------------------------------------------------------------
 void CL_ES::ImpAgri(CL_Agriculteur *agri)
 {

 }

 */
