//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <dir.h>
#pragma hdrstop

#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Main.h"

#include "LBCompAgri.h"
#include "Resultat.h"
#include "AgriSaisie.h"
#include "Compilateur.h"
#include "QRSortieVal.h"
#include "QRSortieQuant.h"
#include "Aide.h"
#include "Erreur.h"

#include "ImpDelta.h"
#include "Erreur.h"

#include "AgriData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAgriDataFrm *AgriDataFrm;
extern bool FichierLu;
extern CL_ES *ES;
extern CL_Compil *Compil;

//---------------------------------------------------------------------------
__fastcall TAgriDataFrm::TAgriDataFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TAgriDataFrm::FormCreate(TObject *Sender)
{
	SLstErreur=new TStringList;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::FormActivate(TObject *Sender)
{
	EdFicOlympe->Text=ES->FLecture;
	AsNature="";
}
//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	SLstErreur->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::EdFicOlympeClick(TObject *Sender)
{
	bool rep;
	rep=OpenDialogFicOlympe->Execute();
	if(rep)
	EdFicOlympe->Text=OpenDialogFicOlympe->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::EdFicCsvClick(TObject *Sender)
{
	bool rep;
	AnsiString as;
	rep=OpenDialogFicCsv->Execute();
	if(rep)
	{
		EdFicCsv->Text=OpenDialogFicCsv->FileName;
		as = ChangeFileExt(OpenDialogFicCsv->FileName,".oly");
		EdFicResultat->Text=as;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::EdFicResultatClick(TObject *Sender)
{
	bool rep;
	rep=SaveDialogFicResultat->Execute();
	if(rep)
	EdFicResultat->Text=SaveDialogFicResultat->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::BtBnOKClick(TObject *Sender)
{
	AnsiString as;
	char langue;
	int rep;

	ES->FLecture=EdFicOlympe->Text;
	ES->FEcriture=ES->FLecture; // à changer int CL_ES::lireFichier(bool tout)

	//Langue
	MainForm->CBLangue->ItemIndex=CBLangue->ItemIndex;
	switch(CBLangue->ItemIndex)
	{
		case 0: langue='F';break;
		case 1: langue='E';break; //English
		case 2: langue='S';break;//Spanish
		case 3: langue='N';break;//Nederland
		case 4: langue='P';break;//Portugais
		case 5: langue='X';break;//a définir

		default: langue='F';MainForm->CBLangue->ItemIndex=0;
	}

	MainForm->Langue=langue;
	MainForm->TexteEtCaption();

	//les identificateurs pour la langue
	LireIdent(MainForm->CBLangue->ItemIndex);

	//delimiter =séparateur    de champ
	switch(RGSeparateurCsv->ItemIndex)
	{
		case 0:Delimiter=';';break;
		case 1:Delimiter=',';break;
	}
	//séparateur décimal
	switch(RGSeparateurDecimal->ItemIndex)
	{
		case 0:DecSep='.';break;
		case 1:DecSep=',';break;
	}

	//lire seult données générales dans xxx.oly
	rep=ES->lireFichier(false);
	if(rep==0)//Ok
	FichierLu=true;
	ES->StockagePermis=true;//????
//    ES->FEcriture=EdFicResultat->Text.c_str();

	//lire données spécifiques depuis xxx.csv
	NoLi=0;
	IlYaErreur=false;
	ErreurFrm->Edit->Clear();

	LireData(EdFicCsv->Text.c_str());

	ES->FEcriture=EdFicResultat->Text.c_str();

//    ES->FLecture=ES->FEcriture;
//    ES->ecrireFichier();

	if(IlYaErreur==true)
	ErreurFrm->Show();

	ES->FLecture=ES->FEcriture;
	ES->ecrireFichier();

	if(IlYaErreur==true)
	{
		for(int n=0;n<SLstErreur->Count;n++)
		ErreurFrm->Edit->Lines->Add(SLstErreur->Strings[n]);
		ErreurFrm->Show();
	}
	Close();
	AffResultats(); //      201009
}

//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::BtBnPasOkClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TAgriDataFrm::ImportDelta(void) {
	AnsiString as;
	char langue;
	int rep;
	//delimiter =séparateur    de champ
	switch (ImpDeltaFrm->RGSeparateurCsv->ItemIndex) {
	case 0:
		Delimiter = ';';
		break;
	case 1:
		Delimiter = ',';
		break;
	}
	//séparateur décimal
	switch (ImpDeltaFrm->RGSeparateurDecimal->ItemIndex) {
	case 0:
		DecSep = '.';
		break;
	case 1:
		DecSep = ',';
		break;
	}

	//les identificateurs pour la langue
	LireIdent(MainForm->CBLangue->ItemIndex);

	//lire données spécifiques depuis xxx.csv
	NoLi = 0;
	IlYaErreur = false;
	ErreurFrm->Edit->Clear();
	LireData(ImpDeltaFrm->EdFicCsv->Text.c_str());
	if (IlYaErreur == true)
		ErreurFrm->Show();
	ShowMessage(ImpDeltaFrm->EdFicCsv->Text + "  lu");
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TAgriDataFrm::LireLigneCommande(void) {
	AnsiString as;
	FILE *fichCommande;
	char nomFichOly[MAXPATH], stockerSous[MAXPATH];
	char *nomFichData; //[MAXPATH];
	char chaine[MAXPATH], chaine1[10];
	char Langue;
	int rep;
	fichCommande = fopen("AgriData.txt", "r");

	//Fichier données générales  *.oly
	fgets(nomFichOly, MAXPATH, fichCommande);
	NoLi++;
	nomFichOly[strlen(nomFichOly) - 1] = 0;
	ES->FEcriture = nomFichOly;
	ES->FLecture = nomFichOly;

	//Langue
	fgets(chaine, 10, fichCommande);
	NoLi++;
	sscanf(chaine, "%s %c", chaine1, &Langue);
	switch (Langue) //010806
	{
	case 'F':
		MainForm->CBLangue->ItemIndex = 0;
		break;
	case 'E':
		MainForm->CBLangue->ItemIndex = 1;
		break; //English
	case 'S':
		MainForm->CBLangue->ItemIndex = 2;
		break; //Spanish
	case 'N':
		MainForm->CBLangue->ItemIndex = 3;
		break; //Nederland
	case 'P':
		MainForm->CBLangue->ItemIndex = 4;
		break; //Portugues
	case 'X':
		MainForm->CBLangue->ItemIndex = 5;
		break;
	default:
		Langue = 'F';
		MainForm->CBLangue->ItemIndex = 0;
		break;
	}
	MainForm->Langue = Langue;
	MainForm->TexteEtCaption();

	//les identificateurs pour la langue
	LireIdent(MainForm->CBLangue->ItemIndex);

	//delimiter =séparateur
	fgets(chaine, 100, fichCommande);
	NoLi++;
	sscanf(chaine, "%s %c  %c", chaine1, &Delimiter, &DecSep);

	//Fichier données de l'agriculteur *.csv
	fgets(chaine, MAXPATH, fichCommande);
	NoLi++;
	nomFichData = strtok(chaine, "\n");
	CreerNomFicAStocker(nomFichData, stockerSous);
//    ES->FEcriture=stockerSous;

	//lire seult données générales dans xxx.oly
	rep = ES->lireFichier(false);
	ES->FEcriture = stockerSous;
	if (rep == 0) //Ok
		FichierLu = true;
//    MainForm->FichierLu=true;
	ES->StockagePermis = true; //????

	//lire données spécifiques dans xxx.txt
	LireData(nomFichData);
	AffResultats();
}
/*

 //cas hollandais  commencer par comparer --->
 CL_EtatSortie *etat;
 CL_Agriculteur *agri;
 int n;
 if(V_SerieComp->Nbelt==0) return;

 etat=V_SerieComp->Vecteur[0];
 for(n=0;n<V_Agriculteur->Nbelt;n++)
 {
 agri=V_Agriculteur->Vecteur[n];
 LBCompAgriFrm->ChLB->AddItem(agri->Nom,(TObject*)agri);
 LBCompAgriFrm->ChLB->Checked[n]=true;

 }
 Global=AGRI;
 AgriEnCours=V_Agriculteur->Vecteur[0];
 //--->

 //    AgriSaisieFrm->Show(); //plante
 //ResultatFrm->Show();
 ResultatFrm->Agri=AgriEnCours;
 ResultatFrm->RetourDeTVChoixComp(etat);
 Global=AGRI;   //test
 //    MainForm->WindowState=wsMinimized;
 //    AgriSaisieFrm->Show();
 //   BtAgriEnCoursClick(this);
 //ResultatFrm->Show();
 */
//---------------------------------------------------------------------------
void TAgriDataFrm::CreerNomFicAStocker(char *nomFichData, char *stockerSous) {
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];

	fnsplit(nomFichData, drive, dir, file, ext);

	fnmerge(stockerSous, drive, dir, file, "oly"); /* merge everything into one string */

}
//---------------------------------------------------------------------------
// fichier csv
// séparateur
//---------------------------------------------------------------------------
void TAgriDataFrm::LireData(char *nomFichData) {
	FILE *fichier;
	char chaine[500];
	char *p;
	AnsiString as;
	CL_Agriculteur *agri;
	int NoLiX;
	fichier = fopen(nomFichData, "r");

	NoLiX = 100;
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;

		if (NoLi > NoLiX)
			NoLiX += 100;
		if (p == NULL)
			break;
		if (p[0] == '/' && p[1] == '/')
			continue;
		if (p[0] == ';' && p[1] == ';')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			continue; //ligne vide
		as = AnsiString(p);
		as = as.Trim();
		//Agriculteur; nom
		if (as.AnsiCompareIC(L_Agriculteur) == 0) //"Agriculteur")
				{

			//p=strtok(NULL,";,");
			agri = new CL_Agriculteur();
			LireNomAgri(agri, p);
			V_Agriculteur->ins(agri);
			if (V_Agriculteur->Nbelt == 1)
				AgriEnCours = agri;
		} else if (as.AnsiCompareIC(L_Delta) == 0)
			LireDelta(fichier, agri, chaine);
		else if (as.AnsiCompareIC(L_Assolement) == 0)
			LireAssolement(fichier, CULTURE, agri, V_Culture, V_CatCulture);
		else if (as.AnsiCompareIC(L_Animaux) == 0)
			LireAssolement(fichier, ANIMAUX, agri, V_Animaux, V_CatAnimaux);
		else if (as.AnsiCompareIC(L_Perenne) == 0)
			LirePerenne(fichier, agri);

		else if (as.AnsiCompareIC(L_Variable) == 0) //110607
			LireVariable(fichier, agri);

		else if (as.AnsiCompareIC(L_ChStruct) == 0) //110607
			LireFormule(fichier, agri, CHSTRUCT);

		else if (as.AnsiCompareIC(L_DepDiv) == 0) //110607
			LireFormule(fichier, agri, DEPDIV);
		else if (as.AnsiCompareIC(L_RecDiv) == 0) //110607
			LireFormule(fichier, agri, RECDIV);
		else if (as.AnsiCompareIC(L_DepPriv) == 0) //110607
			LireFormule(fichier, agri, DEPFAM);
		else if (as.AnsiCompareIC(L_RecPriv) == 0) //110607
			LireFormule(fichier, agri, RECFAM);

		else if (as.AnsiCompareIC(L_Immo) == 0)
			LireImmoGlobal(fichier, agri);
		else if (as.AnsiCompareIC(L_Materiel) == 0) //110607
			LireMateriel(fichier, agri);
		else if (as.AnsiCompareIC(L_PetitMateriel) == 0) //110607
			LirePetitMateriel(fichier, agri);
		else if (as.AnsiCompareIC(L_Finance) == 0)
			LireFinGlobal(fichier, agri);
		else if (as.AnsiCompareIC(L_Resultat) == 0) //130907
			LireResultats();
		else {
			Erreur(as + "  Inconnu");
		}
	}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::LireNomAgri(CL_Agriculteur *agri, char *chaine) {
	char *nom, *chaineAn_0;
	int an_0;
	nom = strtok(NULL, ";,\n");
	agri->Nom = AnsiString(nom);
	chaineAn_0 = strtok(NULL, ";,\n");
	if (chaineAn_0 == NULL)
		return;
	//pas de date par défaut année en cours

	an_0 = atoi(chaineAn_0);
	agri->DefSim->An_0 = an_0;

}
//---------------------------------------------------------------------------
// Delta;Prix;Tendance;identificateur
//        as1  as2     as3;
//---------------------------------------------------------------------------
void TAgriDataFrm::LireDelta(FILE *fichier, CL_Agriculteur *agri,
		char *chaine) {
	int n, type;
	char *p;
	AnsiString as1, as2, as3, as4;
	CL_Vecteur<CL_Tendance> *vecteur;
	CL_Tendance *tendance;
	bool trouve;
	//strtok a mis \0 à la place du séparateur
	// faire démarrer chaine aprés
	n = strlen(chaine);
	chaine += n + 1;

	p = strtok(chaine, ";,\n\0"); //Prix ou Quantité
	as1 = AnsiString(p);
	as1 = as1.Trim(); //301009

	p = strtok(NULL, ";,\n"); //Produit ou Charge
	as2 = AnsiString(p);
	as2 = as2.Trim();

	p = strtok(NULL, ";,\n"); //Tendance ou Scenario
	as3 = AnsiString(p);
	as3 = as3.Trim();

	p = strtok(NULL, ";,\n"); // nom
	as4 = AnsiString(p);
	as4 = as4.Trim();

	trouve = false;
	if (as1.AnsiCompareIC(L_Prix) == 0) {
		if (as2.AnsiCompareIC(L_Produit) == 0) {
			if (as3.AnsiCompareIC(L_Tendance) == 0) {
				vecteur = V_TendPrixProd;
				type = 1;
				trouve = LireDeltaPrix(fichier, as4, V_TendPrixProd, V_Produit);
			} else if (as3.AnsiCompareIC(L_Scenario) == 0) {
				vecteur = V_ScenPrixProd;
				type = 2;
				trouve = LireDeltaPrix(fichier, as4, V_ScenPrixProd, V_Produit);
			}
		} else if (as2.AnsiCompareIC(L_Charge) == 0) {
			if (as3.AnsiCompareIC(L_Tendance) == 0) {
				vecteur = V_TendPrixCharge;
				type = 3;
				trouve = LireDeltaPrix(fichier, as4, V_TendPrixCharge,
						V_Charge);
			} else if (as3.AnsiCompareIC(L_Scenario) == 0) {
				vecteur = V_ScenPrixCharge;
				type = 4;
				trouve = LireDeltaPrix(fichier, as4, V_ScenPrixCharge,
						V_Charge);
			}
		}
	} else if (as1.AnsiCompareIC(L_Quantite) == 0) {
		if (as2.AnsiCompareIC(L_Produit) == 0) {
			if (as3.AnsiCompareIC(L_Tendance) == 0) {
				vecteur = V_TendQProd;
				type = 5;
				trouve = LireDeltaQuantite(fichier, as4, V_TendQProd, PRODUIT);
			} else if (as3.AnsiCompareIC(L_Scenario) == 0) {
				vecteur = V_ScenQProd;
				type = 6;
				trouve = LireDeltaQuantite(fichier, as4, V_ScenQProd, PRODUIT);
			}

		} else if (as2.AnsiCompareIC(L_Charge) == 0) {
			if (as3.AnsiCompareIC(L_Tendance) == 0) {
				vecteur = V_TendQCharge;
				type = 7;
				trouve = LireDeltaQuantite(fichier, as4, V_TendQCharge, CHARGE);
			} else if (as3.AnsiCompareIC(L_Scenario) == 0) {
				vecteur = V_ScenQCharge;
				type = 8;
				trouve = LireDeltaQuantite(fichier, as4, V_ScenQCharge, CHARGE);
			}
		}
	}
	if (trouve == false)
		return;
	for (n = 0; n < vecteur->Nbelt; n++) {
		tendance = vecteur->Vecteur[n];
		if (tendance->Nom == as4) {
			agri->DefSim->TypeAlea = 1;
			switch (type) {
			// Prix Produit tendance ou scenario
			case 1:
			case 2:
				if (type == 1)
					agri->DefSim->TouSPrixProd = 1; //tendance
				else
					agri->DefSim->TouSPrixProd = 2; //scenario
				agri->DefSim->NoPrixProd = tendance->No;
				agri->DefSim->PrixProd = tendance;
				break;
				//Prix charge
			case 3:
			case 4:
				if (type == 3)
					agri->DefSim->TouSPrixCharge = 1;
				else
					agri->DefSim->TouSPrixCharge = 2;
				agri->DefSim->NoPrixCharge = tendance->No;
				agri->DefSim->PrixCharge = tendance;
				break;
				// quantite produite
			case 5:
			case 6:
				if (type == 5)
					agri->DefSim->TouSQProd = 1;
				else
					agri->DefSim->TouSQProd = 2;
				agri->DefSim->NoQProd = tendance->No;
				agri->DefSim->QProd = tendance;
				break;

			case 7:
			case 8:
				if (type == 7)
					agri->DefSim->TouSQCharge = 1;
				else
					agri->DefSim->TouSQCharge = 2;
				agri->DefSim->NoQCharge = tendance->No;
				agri->DefSim->QCharge = tendance;
				break;
			}

		}
	}
}
//---------------------------------------------------------------------------
bool TAgriDataFrm::LireDeltaPrix(FILE *fichier, AnsiString nom,
		CL_Vecteur<CL_Tendance>*vTendance, CL_Vecteur<CL_Item> *vItem) {
	int i, j;
	CL_Tendance *tendance;
	CL_Delta *delta;
	char chaine[500];
	float valeur[N_X + 1]; // 10 valeurs+ 1 pour base
	char *p;
	AnsiString asNom, asNomCat;
	int nMax;
	for (i = 0; i < vTendance->Nbelt; i++) {
		tendance = vTendance->Vecteur[i];
		if (tendance->Nom == nom)
			goto SUITE;
		//301007
	}
	tendance = new CL_Tendance();
	tendance->Nom = nom;
	vTendance->ins(tendance);
	SUITE:

	fgets(chaine, 500, fichier);
	NoLi++; //Produit;categorie;base;...je saute
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			return false; //fin fichier

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide
//        p=fgets(chaine,500,fichier);

		//nom
		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//categorie
		p = strtok(NULL, ";,");
		asNomCat = AnsiString(p);
		if (asNomCat == "\n") {
			Erreur("Ligne Incomplete");
			continue;
		}
		delta = TrouverDelta(tendance, asNom, asNomCat, vItem);
		p = strtok(NULL, "\n");
		if (delta == NULL) {
			Erreur("Delta Inconnu");
			continue;
		}
		nMax = 11; //201209
		LireValeur(valeur, p, nMax);
		if (delta) {
			for (i = 0, j = 1; i < nMax - 1; i++, j++) //201209 //200907
				delta->Pcent[i] = (100. * valeur[j]) / valeur[0];
		}
	}
	return true;
}
//---------------------------------------------------------------------------
CL_Delta* TAgriDataFrm::TrouverDelta(CL_Tendance *tendance, AnsiString nom,
		AnsiString nomCat, CL_Vecteur<CL_Item> *vItem) {
	int i, n;
	CL_Delta *delta;
	CL_Item *item;
	for (i = 0; i < tendance->V_Delta->Nbelt; i++) {
		delta = tendance->V_Delta->Vecteur[i];
		if (delta->Item->Nom == nom && delta->Item->Categorie->Nom == nomCat)
			return delta;
	}

	delta = new CL_Delta();
	for (n = 0; n < vItem->Nbelt; n++) {
		item = vItem->Vecteur[n];
		if (item->Nom == nom && item->Categorie->Nom == nomCat) {
			delta->Item = item;
			delta->NoItem = item->No;
			delta->Nature = 0; //seult pour les rendements
			tendance->V_Delta->ins(delta);
			return delta;
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
bool TAgriDataFrm::LireDeltaQuantite(FILE *fichier, AnsiString nom,
		CL_Vecteur<CL_Tendance>*vTendance, int type) //PRODUIT ou CHARGE
		{
	int i, j;
	CL_Tendance *tendance;
	CL_Delta *delta;
	char chaine[500];
	float valeur[N_X + 1]; // 10 valeurs+ 1 pour base
	char *p;
	AnsiString asNom, asNomAtelier;
	int nMax;
	for (i = 0; i < vTendance->Nbelt; i++) {
		tendance = vTendance->Vecteur[i];
		if (tendance->Nom == nom)
			break; //sans erreur !!!!
	}

	fgets(chaine, 500, fichier);
	NoLi++; //Produit;atelier;base;... OU charge;atelier;base;.
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			return false; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide
//        p=fgets(chaine,500,fichier);

		//nom
		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//atelier
		p = strtok(NULL, ";,");
		asNomAtelier = AnsiString(p);
		if (asNomAtelier == "\n") {
			Erreur("Ligne Incomplete");
			continue;
		}

		delta = TrouverDeltaQuantite(tendance, asNom, asNomAtelier, type);
		p = strtok(NULL, "\n");
		nMax = 11;
		LireValeur(valeur, p, nMax);
		if (delta) {
			if (valeur[0] == 0)
				valeur[0] = 1;
			for (i = 0, j = 1; i < nMax - 1; i++, j++) //201209 //200907
				//for(i=0,j=1;i<nMax;i++,j++)
				delta->Pcent[i] = (100. * valeur[j]) / valeur[0];
		}
	}
	return true;
}
//---------------------------------------------------------------------------
CL_Delta* TAgriDataFrm::TrouverDeltaQuantite(CL_Tendance *tendance,
		AnsiString nom, AnsiString nomAtelier, int type) {
	int i, j;
	CL_Delta *delta;
	CL_ItemParAtelier *itemPA;
	CL_Atelier *atelier;
	int nature;
	CL_Vecteur<CL_ItemParAtelier> *vItem;
	for (i = 0; i < tendance->V_Delta->Nbelt; i++) {
		delta = tendance->V_Delta->Vecteur[i];
		if (delta->Item->Nom == nom && delta->Atelier->Nom == nomAtelier)
			return delta;
	}

	delta = new CL_Delta();
	nature = CULTURE;
	atelier = TrouverAtelierQ(nomAtelier, V_Culture);
	if (atelier == NULL) {
		nature = ANIMAUX;
		atelier = TrouverAtelierQ(nomAtelier, V_Animaux);
	}
	if (atelier == NULL)
		return NULL;
	if (type == PRODUIT)
		vItem = atelier->V_Produit;
	else if (type == CHARGE)
		vItem = atelier->V_Charge;

	for (j = 0; j < vItem->Nbelt; j++) //V_Charge
			{
		itemPA = vItem->Vecteur[j];
		if (itemPA->Item->Nom == nom) {
			delta->Atelier = atelier;
			delta->NoAtelier = atelier->No;
			delta->Item = itemPA->Item;
			delta->NoItem = itemPA->Item->No;
			delta->Nature = nature; //  !!!!
			tendance->V_Delta->ins(delta);
			return delta;
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
CL_Atelier* TAgriDataFrm::TrouverAtelierQ(AnsiString nomAtelier,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	int i;
	CL_Atelier *atelier;
	for (i = 0; i < vAtelier->Nbelt; i++) {
		atelier = vAtelier->Vecteur[i];
		if (atelier->Nom == nomAtelier)
			return atelier;
	}
	return NULL;
}
//---------------------------------------------------------------------------
// assolement Animaux
//---------------------------------------------------------------------------
void TAgriDataFrm::LireAssolement(FILE *fichier, int nature,
		CL_Agriculteur *agri, CL_Vecteur<CL_Atelier> *vAtelier,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	char chaine[500];
	char *p;
	AnsiString asNom, asCat, asVal;
	CL_Atelier *atelier;
	CL_Valeur *valeur;
	int nMax = 10;
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		//nom atelier
//        p=strtok(NULL,";,");
		asNom = AnsiString(p);
		asNom = asNom.Trim();
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//categorie
		p = strtok(NULL, ";,");
		asCat = AnsiString(p);
		asCat = asCat.Trim();
		atelier = TrouveAtelier(asNom, asCat, vAtelier, vCategorie);
		if (atelier) {
			valeur = new CL_Valeur(atelier);
//            valeur->Atelier=atelier;
//            valeur->NoAtelier=atelier->No;
			switch (nature) {
			case CULTURE:
				agri->V_Culture->ins(valeur);
				break;
			case ANIMAUX:
				agri->V_Animaux->ins(valeur);
				break;
			}
			p = strtok(NULL, "\n");
			LireValeur(valeur->Valeur, p, nMax);
		} else {
			Erreur(asNom + "   " + asCat + " Inconnu");
		}
	}
}
//---------------------------------------------------------------------------
CL_Atelier* TAgriDataFrm::TrouveAtelier(AnsiString asNom, AnsiString asCat,
		CL_Vecteur<CL_Atelier> *vAtelier,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	int n;
	CL_Atelier *atelier;
	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];
		if (atelier->Nom == asNom) {
			if (atelier->Categorie->Nom == asCat)
				return atelier;
		}
	}
	return NULL;
}

//---------------------------------------------------------------------------
void TAgriDataFrm::LireValeur(float *valeur, char *chaine, int nMax) {
	int i, j, n;
	char car;
	char nombre[20];
//char point;
	float val;
//    if(delimiter==',')point='.';
//    else              point=',';
	i = 0;
	j = 0;
	n = 0;
	while (1) {
		car = chaine[i++];
		if (car >= '0' && car <= '9')
			nombre[j++] = car;
		else if (car == DecSep)
			nombre[j++] = car;
		else if (car == '-')
			nombre[j++] = car;
		else if (car == '+')
			nombre[j++] = car;

		else if (car == Delimiter || car == 0 || car == '\n') {
			nombre[j] = 0;
			val = atof(nombre);
			valeur[n] = val;
			n++;
			if (n > nMax - 1)
				return; //141009
			j = 0;
		}
		if (car == 0 || car == '\n')
			return;
	}
}
//-----------------------------------------------------------------------------
void TAgriDataFrm::LirePerenne(FILE *fichier, CL_Agriculteur *agri) {
	char chaine[500];
	char *p;
	AnsiString asNom, asEspece, asSur, asAnPlant, asAnArr;
	CL_Atelier *atelier;
	CL_Espece *espece;
	CL_Verger *verger;
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//categorie
		p = strtok(NULL, ";,");
		asEspece = AnsiString(p);
		atelier = TrouvePerenne(asNom, asEspece);
		espece = TrouveEspece(asEspece);
		if (atelier == NULL)
			continue;

		p = strtok(NULL, ";,");
		asSur = AnsiString(p);

		p = strtok(NULL, ";,");
		asAnPlant = AnsiString(p);

		p = strtok(NULL, ";,");
		asAnArr = AnsiString(p);

		verger = new CL_Verger();
		verger->Surface = asSur.ToDouble();
		verger->AnPlant = asAnPlant.ToIntDef(0);
		verger->AnArr = asAnArr.ToIntDef(0);
		verger->NoAtelier = atelier->No;
		verger->Espece = espece;
		verger->NoEspece = espece->No;

		agri->V_Verger->ins(verger);
	}
}
//-----------------------------------------------------------------------------
CL_Atelier* TAgriDataFrm::TrouvePerenne(AnsiString asNom, AnsiString asEspece) {
	int n;
	CL_Atelier* atelier;
	for (n = 0; n < V_Perenne->Nbelt; n++) {
		atelier = V_Perenne->Vecteur[n];
		if (atelier->Nom == asNom) {
			if (atelier->Espece->Nom == asEspece)
				return atelier;
		}
	}
	return NULL;
}
//-----------------------------------------------------------------------------
CL_Espece* TAgriDataFrm::TrouveEspece(AnsiString asEspece) {
	int n;
	CL_Espece* espece;
	for (n = 0; n < V_Espece->Nbelt; n++) {
		espece = V_Espece->Vecteur[n];
		if (espece->Nom == asEspece)
			return espece;
	}
	return NULL;
}
//-----------------------------------------------------------------------------
//LireVariable(fichier,VARIABLE,agri,V_Variable,V_CatVariable);
void TAgriDataFrm::LireVariable(FILE *fichier, CL_Agriculteur *agri) {
	char chaine[500];
	char *p;
	AnsiString asNom, asCat, asVal;
	CL_Valeur *valeur;
	CL_Item *item;
	int nMax = 10;
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
//if(NoLi==515)
//	NoLi=515;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//categorie
		p = strtok(NULL, ";,");
		asCat = AnsiString(p); //V_CatVar ne sert à rien
		item = TrouveItem(asNom, asCat, V_Variable);
		if (item) {
			p = strtok(NULL, "\n");
			valeur = new CL_Valeur();
			//	fread(&valeur->No,sizeof(int),1,fichier);
			//    fread(&valeur->NoAtelier,sizeof(int),1,fichier);
			//	fread(&valeur->NoItem,sizeof(int),1,fichier);
			//    fread(valeur->Valeur,sizeof(float)*N_X,1,fichier);
			valeur->NoAtelier = -1; //170105
			valeur->Atelier = NULL;
			valeur->NoItem = item->No;
			valeur->Item = item; //V_Variable->trouve(valeur->NoItem);
			agri->V_Variable->insSans(valeur);

			LireValeur(valeur->Valeur, p, nMax);
		}
	}
}
//---------------------------------------------------------------------------
CL_Item* TAgriDataFrm::TrouveItem(AnsiString asNom, AnsiString asCat,
		CL_Vecteur<CL_Item> *vItem) {
	int n;
	CL_Item* item;
	for (n = 0; n < vItem->Nbelt; n++) {
		item = vItem->Vecteur[n];
		if (item->Nom == asNom && item->Categorie->Nom == asCat) {
			return item;
		}
	}
	return NULL;

}
//---------------------------------------------------------------------------
//        else if(as.AnsiCompareIC(L_ChStruct)==0)   //110607
//            LireFormule(fichier,agri->V_ChStruct);
//            LireFormule(fichier,agri,CHSTRUCT);

//---------------------------------------------------------------------------
// Ch struct recdiv depdiv recfam depfam
//---------------------------------------------------------------------------
void TAgriDataFrm::LireFormule(FILE *fichier, CL_Agriculteur *agri,
		int nature) {
	char chaine[500];
	char *p;
//int n;
	AnsiString asNom, asCat, asVal;
	CL_Formule *formule;
	CL_Vecteur<CL_Formule> *vFormule;
	CL_Vecteur<CL_Item> *vItem;
	CL_Item *item;
	int nMax = 10;
	switch (nature) {
	case CHSTRUCT:
		vFormule = agri->V_ChStruct;
		vItem = V_ChStruct;
		break;
	case DEPDIV:
		vFormule = agri->V_DepDiv;
		vItem = V_DepDiv;
		break;
	case RECDIV:
		vFormule = agri->V_RecDiv;
		vItem = V_RecDiv;
		break;
	case DEPFAM:
		vFormule = agri->V_DepFam;
		vItem = V_DepFam;
		break;
	case RECFAM:
		vFormule = agri->V_RecFam;
		vItem = V_RecFam;
		break;
	}
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		//nom item
//        p=strtok(NULL,";,");
		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//categorie
		p = strtok(NULL, ";,");
		asCat = AnsiString(p);
		item = TrouveItem(asNom, asCat, vItem);
		if (item) {
			p = strtok(NULL, "\n");
			formule = new CL_Formule();
			formule->Item = item;
			formule->NoFamille = nature;
			vFormule->insSans(formule);
			LireValeur(formule->Valeur, p, nMax);
			CreerFormuleProg(formule);
		}
	}
}
//---------------------------------------------------------------------------
CL_Formule* TAgriDataFrm::TrouveFormule(AnsiString asNom, AnsiString asCat,
		CL_Vecteur<CL_Formule> *vFormule) {
	CL_Formule *formule;
	int n;
	for (n = 0; n < vFormule->Nbelt; n++) {
		formule = vFormule->Vecteur[n];
		if (formule->Item->Nom == asNom)
			return formule;
	}
	return NULL;
}
//---------------------------------------------------------------------------
void TAgriDataFrm::CreerFormuleProg(CL_Formule *formule) {
	int n;
	AnsiString asVal;
	CL_Prog *prog;
	n = 0;
	asVal = FloatToStrF(formule->Valeur[0], ffNumber, 8, 2);
	Compil->Compiler(asVal.c_str());
	prog = new CL_Prog();
	prog->Arbre = new CL_Arbre(Compil->Arbre);
	formule->LesProg[n] = prog;
	prog->Source = asVal;
	for (n = 1; n < N_X; n++) {
		if (formule->Valeur[n] == formule->Valeur[n - 1]) {
			formule->LesProg[n] = prog;
			continue;
		}
		asVal = FloatToStrF(formule->Valeur[n], ffNumber, 8, 2);
		Compil->Compiler(asVal.c_str());
		prog = new CL_Prog();
		prog->Arbre = new CL_Arbre(Compil->Arbre);
		formule->LesProg[n] = prog;
		prog->Source = asVal;

	}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::LireImmoGlobal(FILE *fichier, CL_Agriculteur *agri) {
	int i;
	char chaine[500];
	char *p;
	AnsiString asCat;
	CL_FN_Xp1 *fN_Xp1;
	for (i = 0; i < 7; i++) {
		fN_Xp1 = new CL_FN_Xp1();
		fN_Xp1->No = i;
		agri->V_InvSom->ins(fN_Xp1);
	}
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		asCat = AnsiString(p);
		if (asCat == L_Nom)
			continue;

		//categorie
		if (asCat == L_ValResid)
			LireFN_Xp1(agri->V_InvSom, 0, 11, chaine); //11 valeurs
		else if (asCat == L_Amor)
			LireFN_Xp1(agri->V_InvSom, 1, 10, chaine); //10 valeurs
		if (asCat == L_Achat)
			LireFN_Xp1(agri->V_InvSom, 2, 10, chaine); //10 valeurs
	}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::LireMateriel(FILE *fichier, CL_Agriculteur *agri) {
	char chaine[500];
	char *p;
	int n;
	AnsiString asNom, asTva;
	CL_Immo *immo;
	char *endptr;
	CL_Tva *tva;
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		//ligne titre à sauter
		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//nom matériel
		immo = new CL_Immo();
		agri->V_Immo->ins(immo);
		immo->Nom = asNom;

		p = strtok(NULL, ";,");
		immo->ValAchat = strtod(p, &endptr);

		p = strtok(NULL, ";,");
		immo->MAchat = strtod(p, &endptr);

		p = strtok(NULL, ";,");
		immo->AAchat = strtod(p, &endptr);

		p = strtok(NULL, ";,");
		immo->TypeAmor = p[0];

		p = strtok(NULL, ";,");
		immo->Duree = strtod(p, &endptr);

		p = strtok(NULL, ";,\n");
		asTva = AnsiString(p);
		for (n = 0; n < V_Tva->Nbelt; n++) {
			tva = V_Tva->Vecteur[n];
			if (tva->Nom == asTva) {
				immo->Tva = tva;
				goto SUITE;
			}
		}
		immo->Tva = TvaDefaut;
		SUITE:

		p = strtok(NULL, ";,");
		if (p == NULL || p[0] == '\n')
			continue;
		immo->ValVente = strtod(p, &endptr);

		p = strtok(NULL, ";,");
		if (p == NULL || p[0] == '\n')
			continue;
		immo->MVente = strtod(p, &endptr);

		p = strtok(NULL, ";,");
		if (p == NULL || p[0] == '\n')
			continue;
		immo->AVente = strtod(p, &endptr);

	}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::LirePetitMateriel(FILE *fichier, CL_Agriculteur *agri) {
	char chaine[500];
	char *p;
	int n;
	AnsiString asNom, asTva;
	CL_Petit *petit;
	char *endptr;
	CL_Tva *tva;
	AnsiString asAn, asBlanc;
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		//ligne titre à sauter
		asNom = AnsiString(p);
		if (asNom.AnsiCompareIC(L_Nom) == 0)
			continue;

		//premiére cellule à sauter  blanc
		//deuxieme cellule à sauter  année
		petit = new CL_Petit();
		agri->V_Petit->insSans(petit);
		p = strtok(NULL, ";,");
		petit->ValAchat = strtod(p, &endptr);

		p = strtok(NULL, ";,");
		asTva = AnsiString(p);
		for (n = 0; n < V_Tva->Nbelt; n++) {
			tva = V_Tva->Vecteur[n];
			if (tva->Nom == asTva) {
				petit->Tva = tva;
				petit->NoTva = tva->No;
				goto SUITE;
			}
		}
		petit->Tva = TvaDefaut;
SUITE	:

}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::LireFinGlobal(FILE *fichier, CL_Agriculteur *agri) {
	int i;
	char chaine[500];
	char *p;
	AnsiString asCat;
	CL_FN_Xp1 *fN_Xp1;
	for (i = 0; i < 8; i++) {
		fN_Xp1 = new CL_FN_Xp1();
		fN_Xp1->No = i;
		agri->V_FinSom->ins(fN_Xp1);
	}
	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break; //fin fichier
		if (p[0] == '/' && p[1] == '/')
			continue;

		p = strtok(chaine, ";,\n");
		if (p == NULL)
			break; //ligne vide

		asCat = AnsiString(p);
		if (asCat == L_Nom)
			continue;

		//categorie
		if (asCat == L_Dette)
			LireFN_Xp1(agri->V_FinSom, 0, 11, chaine); //11 valeurs
		else if (asCat == L_RembCap)
			LireFN_Xp1(agri->V_FinSom, 1, 10, chaine); //10 valeurs
		if (asCat == L_Interet)
			LireFN_Xp1(agri->V_FinSom, 2, 10, chaine); //10 valeurs
	}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::LireFN_Xp1(CL_Vecteur<CL_FN_Xp1>*vecteur, int no, int nbVal,
		char *chaine) {
	int n;
	CL_FN_Xp1 *fN_Xp1;
	float valeur[N_X + 1];
	int nMax = 11;
	//strtok a mis \0 à la place du séparateur
	// faire démarrer chaine aprés
	n = strlen(chaine);
	chaine += n + 1;
	LireValeur(valeur, chaine, nMax); //';');

	fN_Xp1 = vecteur->trouve(no);
	if (nbVal == 11)
		for (n = 0; n < 11; n++)
			fN_Xp1->Valeur[n] = valeur[n];
	else if (nbVal == 10)
		for (n = 0; n < 10; n++)
			fN_Xp1->Valeur[n] = valeur[n + 1];

}
//---------------------------------------------------------------------------
void TAgriDataFrm::LireResultats(void) {
	char *p;
	p = strtok(NULL, ";,");
	AsNature = AnsiString(p);
	if (AsNature.AnsiCompareIC(L_Standard) == 0) {
		p = strtok(NULL, ";,");
		AsType = AnsiString(p);
		/*
		 if     (asType.AnsiCompareIC(L_Synthese)==0) ;
		 else if(asType.AnsiCompareIC(L_RecDepense)==0);
		 else if(asType.AnsiCompareIC(L_RecDepGP)==0)   ;
		 else if(asType.AnsiCompareIC(L_Quantite)==0)    ;
		 else if(asType.AnsiCompareIC(L_CEG)==0)          ;
		 else if(asType.AnsiCompareIC(L_Bilan)==0)         ;
		 */

	} else if (AsNature.AnsiCompareIC(L_Comparaison) == 0) {
		;
	}
}
//---------------------------------------------------------------------------
void TAgriDataFrm::AffResultats(void) { //291007
	CL_Agriculteur *agri;
	agri = V_Agriculteur->Vecteur[0];
	AgriSaisieFrm->Calcul0(agri);
	ResultatFrm->Agri = agri;
	if (AsNature.AnsiCompareIC(L_Standard) == 0) {
		if (AsType.AnsiCompareIC(L_Synthese) == 0)
			QRSortieValFrm->Prepare(SYNTHESE, agri);
		else if (AsType.AnsiCompareIC(L_RecDepense) == 0)
			QRSortieValFrm->Prepare(VALEUR, agri);
		else if (AsType.AnsiCompareIC(L_RecDepGP) == 0)
			QRSortieValFrm->Prepare(TRESO, agri);
		else if (AsType.AnsiCompareIC(L_Quantite) == 0)
			QRSortieQuantFrm->Prepare(QUANTITE, agri);
		else if (AsType.AnsiCompareIC(L_CEG) == 0)
			QRSortieValFrm->Prepare(CEG, agri);
		else if (AsType.AnsiCompareIC(L_Bilan) == 0)
			QRSortieValFrm->Prepare(BILAN, agri);
	} else if (AsNature == L_Comparaison) {
		ShowMessage("Comparaison à faire"); // a faire
		ResultatFrm->Show();
	} else {
		ResultatFrm->Show();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TAgriDataFrm::Erreur(AnsiString message) {
	AnsiString as;
	as = AnsiString(NoLi) + "  " + message;
	SLstErreur->Add(as);
	IlYaErreur = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TAgriDataFrm::LireIdent(int noLangue) {
	int col, colLangue;
	FILE *fichier;
	AnsiString asFichier; //asCurDir
	char chaine[500], *p;
	TStringList *SLAsIdent, *SLAsTrad;
	AnsiString asIdent, asTrad;
	colLangue = noLangue + 2; //les textes traduits commencent en colonne 2
	SLAsIdent = new TStringList;
	SLAsTrad = new TStringList;
	// AgriDataIdent.csv se trouve dans le chemin de l'exécutable
//    asCurDir=GetCurrentDir();
	asFichier = MainForm->AsDirOlympe + "\\AgriDataIdent.csv";
	fichier = fopen(asFichier.c_str(), "r");

	while (1) {
		p = fgets(chaine, 500, fichier);
		NoLi++;
		if (p == NULL)
			break;
		if (p[0] == '/' && p[1] == '/')
			continue;

		if (chaine[0] == '/' || chaine[0] == ' ')
			continue;
		p = strtok(chaine, ";,\n");
		if (p == NULL)
			continue; //ligne vide
		col = 1;
		while (1) {
			p = strtok(NULL, ";,\n");
			if (p == NULL)
				break;
			if (col == 1) {
				asIdent = AnsiString(p);
				SLAsIdent->Add(asIdent);
				col++;
				continue;
			} else if (col == colLangue) {
				asTrad = AnsiString(p);
				SLAsTrad->Add(asTrad);
				break;
			}
			col++;
		}
	}
	L_Agriculteur = Trouve("L_Agriculteur", SLAsIdent, SLAsTrad);
	L_Assolement = Trouve("L_Assolement", SLAsIdent, SLAsTrad);
	L_Animaux = Trouve("L_Animaux", SLAsIdent, SLAsTrad);
	L_Perenne = Trouve("L_Perenne", SLAsIdent, SLAsTrad);
	L_Nom = Trouve("L_Nom", SLAsIdent, SLAsTrad);

	L_Delta = Trouve("L_Delta", SLAsIdent, SLAsTrad);
	L_Prix = Trouve("L_Prix", SLAsIdent, SLAsTrad);
	L_Quantite = Trouve("L_Quantite", SLAsIdent, SLAsTrad);
	L_Produit = Trouve("L_Produit", SLAsIdent, SLAsTrad);
	L_Charge = Trouve("L_Charge", SLAsIdent, SLAsTrad);
	L_Tendance = Trouve("L_Tendance", SLAsIdent, SLAsTrad);
	L_Scenario = Trouve("L_Scenario", SLAsIdent, SLAsTrad);

	L_Immo = Trouve("L_Immo", SLAsIdent, SLAsTrad);
	L_Finance = Trouve("L_Finance", SLAsIdent, SLAsTrad);

	L_ValResid = Trouve("L_ValResid", SLAsIdent, SLAsTrad);
	L_Amor = Trouve("L_Amor", SLAsIdent, SLAsTrad);
	L_Achat = Trouve("L_Achat", SLAsIdent, SLAsTrad);

	L_Dette = Trouve("L_Dette", SLAsIdent, SLAsTrad);
	L_RembCap = Trouve("L_Remb", SLAsIdent, SLAsTrad);
	L_Interet = Trouve("L_Interet", SLAsIdent, SLAsTrad);

	L_ChStruct = Trouve("L_ChStruct", SLAsIdent, SLAsTrad);
	L_DepDiv = Trouve("L_DepDiv", SLAsIdent, SLAsTrad);
	L_RecDiv = Trouve("L_RecDiv", SLAsIdent, SLAsTrad);
	L_DepPriv = Trouve("L_DepPriv", SLAsIdent, SLAsTrad);
	L_RecPriv = Trouve("L_RecPriv", SLAsIdent, SLAsTrad);
	L_Variable = Trouve("L_Variable", SLAsIdent, SLAsTrad);

	L_Materiel = Trouve("L_Materiel", SLAsIdent, SLAsTrad);
	L_PetitMateriel = Trouve("L_PetitMateriel", SLAsIdent, SLAsTrad);

	L_Resultat = Trouve("L_Resultat", SLAsIdent, SLAsTrad);

	L_Standard = Trouve("L_Standard", SLAsIdent, SLAsTrad);
	L_Comparaison = Trouve("L_Comparaison", SLAsIdent, SLAsTrad);

	L_Synthese = Trouve("L_Synthese", SLAsIdent, SLAsTrad);
	L_RecDepense = Trouve("L_RecDepense", SLAsIdent, SLAsTrad);
	L_RecDepGP = Trouve("L_RecDepGP", SLAsIdent, SLAsTrad);
	L_CEG = Trouve("L_CEG", SLAsIdent, SLAsTrad);
	L_Bilan = Trouve("L_Bilan", SLAsIdent, SLAsTrad);

}

//---------------------------------------------------------------------------
AnsiString TAgriDataFrm::Trouve(AnsiString as, TStringList *sLAsIdent,
		TStringList *sLAsTrad) {
	int i;
	AnsiString trad;
	i = sLAsIdent->IndexOf(as);
	if (i == -1) {
		ShowMessage(AnsiString("Manque ") + as);
		return ("Absent");
	}
	trad = sLAsTrad->Strings[i];
	return trad;
}

//---------------------------------------------------------------------------
void __fastcall TAgriDataFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=114;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

