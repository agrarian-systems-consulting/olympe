/* modif montp 5sept2001
 piment agriSaisieCalculEns appel direct à calcul0
 mais appel inutile à completeEtatSortie et CalculIndicateur
 faire un test avec produit basé sur indicateur

 vérifier si destructeur de AgriRes est complet

 Agriculteur
 affichage de nombre de variante
 ET n° de variante si les variantes sont affichées
 classées selon ordre alpha de agri origine
 id Ensemble

 Conversion
 Atelier
 Categorie suppression de Edit remplacé par Label

 a Faire ?
 supprimer Creer le [...] suffit
 A conserver a supprimer dans Nettoyer

 supprimé periode de travail ->à remettre
 cheetah jansfreeware.com
 */
/** débogage (ac) */
//#include "XLRessource.h"
//---------------------------------------------------------------------------
#include <vcl.h>
#include <dir.h>
#include <stdio.h>
#include <extctrls.hpp>
#include <SysUtils.hpp>
#pragma hdrstop
//atto 160801
//#include <string>
//#include "hh.hpp"        //150710
//#include "Htmlhelp.h"  //atto060810

#include "APropos.h"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.h"
#include "FichierLire.h"
#include "Erreur.h"
#include "Forme0.h"
#include "Tableur.h"

#include "SysUnite.h"
#include "Tva.h"

#include "GereCatProduit.h"
#include "GereCatVariable.h"
#include "GereCatBestiaux.h"
#include "GereCatChStruct.h"
#include "GereCatZone.h"

#include "GereAtelier.h"
#include "GereEspece.h"

#include "Espece.h"
#include "Atelier.h"

#include "GereAgri.h"
#include "AgriSaisie.h"
#include "AgriDefSim.h"

#include "Resultat.h"
#include "Conversion.h"

#include "GereEnsemble.h"
#include "Ensemble.h"
//#include "Brouillon.h"
#include "AleaPrix.h"

#include "TVChoix.h"
#include "TVPrixChoix.h"
#include "TVRdtChoix.h"
#include "TVChoixElt.h"         //250502
#include "TVDico.h"

#include "LBSysUnit.h"
#include "LBTva.h"
#include "LBToutAgri.h"
//#include "LBChoixTva.h"

//#include "Configuration.h"
#include "GereIndic.h"
#include "GereEtat.h"
#include "GereComparaison.h"
#include "GereProcedure.h"
#include "GereCalendrier.h"
#include "DefBestiaux.h"
#include "DefCalendrier.h"

#include "DefEtatSortie.h"
#include "DefProduit.h"
#include "DefChStruct.h"
#include "DefProcedure.h"
#include "DefVariable.h"
#include "DefZone.h"
#include "AtelierMarge.h"
#include "AtelierMDetail.h"

#include "Indicateur.h"
#include "Assol.h"

//#include "ReClasse.h"
#include "Compilateur.h"
#include "GereAleaPrix.h"
#include "GereAleaRdt.h"

#include "Effacer.h"
//#include "QuelExcelCSV.h"
#include "LesDefSim.h"
#include "NoteAgri.h"
//#include "Assol.h"
#include "MvtAnnee.h"
//#include "EntreChaine.h"
//#include "GereCalendrier.h"
#include "Tarif.h"
#include "TriAgri.h"
#include "Commercialisation.h"
#include "PolStock.h"
#include "Treso.h"
#include "Motif.h"
#include "Olympe.h"
#include "DefAction.h"

//#include "AppelFct.h"
//#include "CreerLstNom.h"

#include "FichierEcrireXml.h"
#include "CL_Trad.h"
#include "CL_Don.h"
#include "AgriData.h"
#include "LBCompAgri.h"

#include "Aide.h"
#include "LireAccess.h"
#include "EcrireAccess.h"
#include "RacDef.h"
#include "ImpDelta.h"

#include "Main.h"

//!Nos variables globales
CL_ES *ES;
//CL_Imp    *Imp;
CL_Compil *Compil;
CL_Excel *EX;
CL_Xml *Xml;
CL_Don *Don;
CL_Trad *T;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "Excel_97_SRVR"
#pragma resource "*.dfm"
TMainForm *MainForm;

void ImprimerTout(void); //!!

#define MyWidth  800.0  //montpellier
#define MyHeight 600.0

//!Variable Globale
bool FichierLu;
//---------------------------------------------------------------------------
//!Les instanciations des objets de l'application se font ici
__fastcall TMainForm::TMainForm(TComponent* Owner) :
		TForm(Owner) {
	CL_Categorie *cat;
	TDateTime time;
	unsigned short a, m, j;
	char buf[100];

	DecimalSeparator = '.';
	ThousandSeparator = ' ';
	MEMORYSTATUS X;
	double TailleDeLaRam;
	X.dwLength = sizeof(X);
	GlobalMemoryStatus(&X);

	/*  Probleme sous 7 64bits - 110412
	 TailleDeLaRam = (X.dwTotalPhys+524288)/1024/1024;
	 if(TailleDeLaRam<128)  //256
	 ShowMessage("Mémoire vide INSUFFISANTE!!!\n Risque d'erreurs bizarres");
	 */
	//!Instanciation d'une classe d'entrées-sorties
	ES = new CL_ES; //new CL_ES('E')
	EX = new CL_Excel;
	Don = new CL_Don;
	Compil = new CL_Compil;

	//    ES->Version   =   126;   //280102
	//    ES->Version   =   127;   //091002
	//    ES->Version   =   128;   //220103
	//    ES->Version   =   129;   //170903
//   ES->Version   =   130;   //031003
	//     ES->Version   =   131;   //200407
	//     ES->Version   =   132;   //030507
//        ES->Version   =   133;   //210907
	ES->Version = 134; //210907

///////////               Olympe ou Medter

	ES->Verrou = SANS;
	AnLimite = 2015;
	MoisLimite = 01;

	/*

	 ES->Verrou=MEDTER;
	 AnLimite=2050;
	 MoisLimite=6;
	 */

//////////
	//_____________________
//	Imp           =   new CL_Imp;
//    Compil        =   new CL_Compil;
///*.........
//  le gros bug deevait etre lié ?? à l'utilisation de constructeurs par défaut
// qui n'initialisait pas
// mais je n'en suis pas sur
// il y avait des erreurs aléatoires qui sentaient l'écrasement
// depuis ces lignes c'est supprimé !?
	CL_Vecteur<CL_Valeur> *V_CultureA;
	CL_Vecteur<CL_Verger> *V_Verger;
	CL_Vecteur<CL_InvAni> *V_InvAni;

	CL_Vecteur<CL_Formule> *V_Produits;

	CL_Vecteur<CL_Valeur> *V_VariableA;

	CL_Vecteur<CL_Immo> *V_Immo;
	CL_Vecteur<CL_Petit> *V_Petit;
	CL_Vecteur<CL_FN_Xp1> *V_FinSom;

	CL_Vecteur<CL_EmpLT> *V_EmpLT;
	CL_Vecteur<CL_EmpCT> *V_EmpCT;
	CL_Vecteur<CL_Sub> *V_Sub;
	CL_Vecteur<CL_Occc> *V_Occc;
	CL_Vecteur<CL_Plact> *V_Plact;

	CL_Vecteur<CL_EnCours> *V_Creance;
	CL_Vecteur<CL_StockIni> *V_StockIni; //111201
	CL_Vecteur<CL_PolStock> *V_PolStock; //300302

	CL_QuanVal *quanVal;
	CL_Delta *delta;

//ShowMessage("Main 1");
	// ça permet d'eviter le GROS BUG mais pourquoi ???
	V_CultureA = new CL_Vecteur<CL_Valeur>();
	V_Verger = new CL_Vecteur<CL_Verger>();
	V_InvAni = new CL_Vecteur<CL_InvAni>();

	V_Produits = new CL_Vecteur<CL_Formule>();

	V_VariableA = new CL_Vecteur<CL_Valeur>();

	V_EmpLT = new CL_Vecteur<CL_EmpLT>();
	V_EmpCT = new CL_Vecteur<CL_EmpCT>();
	V_Sub = new CL_Vecteur<CL_Sub>();
	V_Plact = new CL_Vecteur<CL_Plact>();
	V_Occc = new CL_Vecteur<CL_Occc>();
	V_FinSom = new CL_Vecteur<CL_FN_Xp1>();

	V_Immo = new CL_Vecteur<CL_Immo>();
	V_Petit = new CL_Vecteur<CL_Petit>();

	V_Creance = new CL_Vecteur<CL_EnCours>();

	V_StockIni = new CL_Vecteur<CL_StockIni>();
	V_PolStock = new CL_Vecteur<CL_PolStock>();

	quanVal = new CL_QuanVal();

	delta = new CL_Delta();

//ShowMessage("Main 2");

	delete V_CultureA;
	delete V_Verger;
	delete V_InvAni;

	delete V_Produits;

	delete V_VariableA;

	delete V_Immo;
	delete V_Petit;
	delete V_FinSom;

	delete V_EmpLT;
	delete V_EmpCT;
	delete V_Sub;
	delete V_Occc;
	delete V_Plact;

	delete V_Creance;
	delete V_StockIni;
	delete quanVal;
	delete V_PolStock;
	delete delta;
//ShowMessage("Main 3");

//..................*/
	try {
		V_SystemeUnite = new CL_Vecteur<CL_SystemeUnite>();
		V_Tva = new CL_Vecteur<CL_Tva>();

		V_CatProduit = new CL_Vecteur<CL_Categorie>();
		V_CatCharge = new CL_Vecteur<CL_Categorie>();
		V_CatBestiaux = new CL_Vecteur<CL_Categorie>();
		V_CatExternalite = new CL_Vecteur<CL_Categorie>();
		cat = new CL_Categorie("Négative", EXTNEG);
		V_CatExternalite->insSans(cat);

		cat = new CL_Categorie("Positive", EXTPOS);
		V_CatExternalite->insSans(cat);

		V_CatCulture = new CL_Vecteur<CL_Categorie>();
		V_CatAnimaux = new CL_Vecteur<CL_Categorie>();
		V_CatVivrier = new CL_Vecteur<CL_Categorie>();

		V_CatChStruct = new CL_Vecteur<CL_Categorie>();
		V_CatDepDiv = new CL_Vecteur<CL_Categorie>();
		V_CatRecDiv = new CL_Vecteur<CL_Categorie>();
		V_CatRecFam = new CL_Vecteur<CL_Categorie>();
		V_CatDepFam = new CL_Vecteur<CL_Categorie>();

		V_CatTypeZone = new CL_Vecteur<CL_Categorie>();

		V_CatIndic = new CL_Vecteur<CL_Categorie>();
		V_CatEtatSortie = new CL_Vecteur<CL_Categorie>();
		V_CatSerieComp = new CL_Vecteur<CL_Categorie>();
		V_CatProcedure = new CL_Vecteur<CL_Categorie>();

		V_Produit = new CL_Vecteur<CL_Item>();
		V_Charge = new CL_Vecteur<CL_Item>();
		V_Bestiaux = new CL_Vecteur<CL_Bestiaux>();
		V_Externalite = new CL_Vecteur<CL_Item>();

		V_Culture = new CL_Vecteur<CL_Atelier>();
		V_Animaux = new CL_Vecteur<CL_Atelier>();
		V_Vivrier = new CL_Vecteur<CL_Atelier>();

		V_Espece = new CL_Vecteur<CL_Espece>();
		V_Perenne = new CL_Vecteur<CL_Atelier>();

		V_ChStruct = new CL_Vecteur<CL_Item>();
		V_RecDiv = new CL_Vecteur<CL_Item>();
		V_DepDiv = new CL_Vecteur<CL_Item>();

		V_RecFam = new CL_Vecteur<CL_Item>();
		V_DepFam = new CL_Vecteur<CL_Item>();

		V_TypeZone = new CL_Vecteur<CL_Item>();

		V_CatVar = new CL_Vecteur<CL_Categorie>();
		V_Variable = new CL_Vecteur<CL_Item>();

		V_Calendrier = new CL_Vecteur<CL_Calendrier>();

		V_Agriculteur = new CL_Vecteur<CL_Agriculteur>();

		V_Ensemble = new CL_Vecteur<CL_Ensemble>();

		V_CatRepart = new CL_Vecteur<CL_Categorie>();
		V_Repart = new CL_Vecteur<CL_Repart>; //240203

		V_EtatSortie = new CL_Vecteur<CL_EtatSortie>();
		V_SerieComp = new CL_Vecteur<CL_EtatSortie>();
		V_Procedure = new CL_Vecteur<CL_Procedure>();
		V_Indicateur = new CL_Vecteur<CL_Indicateur>();

		V_Poste = new CL_Vecteur<CL_Poste>();
		V_Elt = new CL_Vecteur<CL_Elt>();

		V_CatDico = new CL_Vecteur<CL_Categorie>();
		V_Dico = new CL_Vecteur<CL_Item>();

		// tendance produits charges
		V_TendPrixProd = new CL_Vecteur<CL_Tendance>();
		V_TendPrixCharge = new CL_Vecteur<CL_Tendance>();
		V_ScenPrixProd = new CL_Vecteur<CL_Tendance>();
		V_ScenPrixCharge = new CL_Vecteur<CL_Tendance>();

		// production et consommation de charges
		V_TendQProd = new CL_Vecteur<CL_Tendance>();
		V_TendQCharge = new CL_Vecteur<CL_Tendance>();
		V_ScenQProd = new CL_Vecteur<CL_Tendance>();
		V_ScenQCharge = new CL_Vecteur<CL_Tendance>();
		V_TendQExt = new CL_Vecteur<CL_Tendance>();
		V_ScenQExt = new CL_Vecteur<CL_Tendance>();

		V_DefSim = new CL_Vecteur<CL_AgriDefSim>();

		V_Conversion = new CL_Vecteur<CL_Conversion>();

		EltTrait = new CL_Elt(TRAIT);
		EltBlanc = new CL_Elt(BLANC);
		EltTitre = new CL_Elt(TITRE);
	} catch (...) {
		ShowMessage(L_PasMemoire);
		//ShowMessage("Mémoire épuisée");
	}

	ES->StockagePermis = true;

	time = TDateTime::CurrentDate();
	time.DecodeDate(&a, &m, &j);
	if (a > AnLimite || (a == AnLimite && m >= MoisLimite)) {
//        sprintf(buf," %s  %2d %2d",L_DateLim.c_str(),m,a);
		sprintf(buf, "date limite %2d %2d", MoisLimite, AnLimite);
//        MessageBox(Handle,buf,L_FinTest.c_str(),MB_OK|MB_ICONSTOP);
		MessageBox(Handle, buf, "PERIODE DE TEST ECOULEE", MB_OK | MB_ICONSTOP);
		Application->Terminate();

		// exit(EXIT_SUCCESS);//CloseQuery();
//        Application->Terminate();
	}

	An_0 = a; //début simulation           par defaut
	Mois_0 = 1;
//    RGExcelClick(this);
//ShowMessage("Main FIN");

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	Application->OnException = AppException;
	Notes="";
	/** Variable globale : le rep de travail courant */
	//rep_ini = GetWorkingDirectory ();
//1  conf = new Configuration( GetOlympeDir ());
	FichierLu=false;
//  AsCodeLangue=AnsiString("FESNP");  //T à introduire  mis dans OnActivate
	SLstLangue=new TStringList;//Français  English
	SLstLangue->Add("Français");
	SLstLangue->Add("English");
	SLstLangue->Add("Espanol");
	SLstLangue->Add("Nederlands");
	SLstLangue->Add("Portuges");
	CBLangue->Items->Clear();
	for(int n=0;n<SLstLangue->Count;n++)
	CBLangue->Items->Add(SLstLangue->Strings[n]);

//  Application->OnHelp=HelpHook;
	Application->OnHelp = FormHelp;

}
//-----------------------------------------------------------------------------
bool __fastcall TMainForm::HelpHook( Word Command, int Data,bool &CallHelp)
{
	CallHelp=false;
	AideFrm->AfficherAide(Langue,HelpContext);
	return true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMainForm::AppException(TObject *Sender,Exception *E)
//void __fastcall TMainForm::AppException(TObject *Sender, SysUtils::Exception *E)

{
	Application->ShowException(E); //pour afficher les exceptions
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject *Sender)
{
//static bool debut=true;
//string historique;
	FILE *fichier;
	AnsiString as;
	char nomfich[1000];//[MAXPATH];   081108
	int rep;
//    char car;
	char buf[2000];//[101];
	char ident[10];
	int n,nPara;
	bool bFicCommande = false;//110512
	if(FichierLu==true) return;

	AsCodeLangue=AnsiString("FESNP");//T à introduire

	//test ligne de commande   //110512
	//AsDirOlympe=GetCurrentDir();      //Dans le contexte d'un double click sur un fichier .oly
	//CurrentDir est le répertoire du fichier .oly
	char result[ MAX_PATH ];
	GetModuleFileName( NULL, result, MAX_PATH );//Retourne dans result le chemin complet de Olympe2.exe
	AsDirOlympe= AnsiString(result);
	AsDirOlympe = AsDirOlympe.SubString(0,AsDirOlympe.LastDelimiter("\\"));//On ne garde que le chemin

	//si ligne de commande
	nPara=ParamCount();
	//ShowMessage(nPara);//220108

	if(nPara ==1)// nom du fichier de commande
	{
		//110512
		AnsiString ficDef=UpperCase(ParamStr(nPara));//Si le fichier est un .oly
		AnsiString stExt = ficDef.SubString(ficDef.Length()-3,4);// On le mémorise
		if (stExt==".OLY")
		{
			sprintf(nomfich,"%s",ficDef.c_str());
			bFicCommande = true;
		}
		else //sinon il s'agit d'un fichier de conf./selection (Agidata.txt)
		{
			LigneCommande();
			return;
		}
	}
	//110512
	//else
	//{
	/** Olympe.fic se trouve dans le chemin de l'exécutable */
	//        historique = conf->exec_path() + "\\olympe.fic";
	AsHistorique = AsDirOlympe+ "\\olympe.fic";
	fichier=fopen(AsHistorique.c_str() ,"rb");
	//}                                                        // Le bloc else ne servait déjà plus (return apres LigneCommande)

	//pb Toulouse 131106
	if(fichier==NULL)
	{
		Langue='F';CBLangue->ItemIndex=0;
		TexteEtCaption();
		return;
	}
//240406
	/** Le fichier est OUVERT */
	//fgets(buf,MAXPATH+1, fichier);
	fgets(buf,2000, fichier);//2000 170108
	if (bFicCommande==false)//120512
	{
		n=0;
		while(1)
		{
			if(buf[n]=='\n') {nomfich[n]=0;break;}
			nomfich[n]=buf[n];
			n++;
		}
	}
	bFicCommande==false;
	//fin modif 120512

//    sscanf(buf,"%s ",nomfich);
//    char *p;
//    p=strtok(nomfich,"\n");

	//langue à utiliser
	fgets(buf,100, fichier);
	sscanf(buf,"%s %c",ident,&Langue);
//210610
	for(n=1;n<AsCodeLangue.Length();n++)
	{
		if(AsCodeLangue[n]==Langue )
		{
			CBLangue->ItemIndex=n-1;
			break;
		}
	}
	/*
	 switch(Langue)                                        //010806
	 {
	 case 'F':CBLangue->ItemIndex=0;break;
	 case 'E':CBLangue->ItemIndex=1;break;           //English
	 case 'S':CBLangue->ItemIndex=2;break;           //Spanish
	 case 'N':CBLangue->ItemIndex=3;break;           //Nederlanc
	 case 'P':CBLangue->ItemIndex=4;break;           //Portugues
	 case 'X':CBLangue->ItemIndex=5;break;
	 default:Langue='F';CBLangue->ItemIndex=0;break;
	 }
	 */
	TexteEtCaption();

	rep=MessageBox(Handle,L_AOuvrir.c_str(),nomfich,
			//rep=MessageBox(Handle,"A ouvrir ?",nomfich,
			MB_YESNO|MB_ICONEXCLAMATION);

	/** Le fichier est FERME */
	fclose(fichier);

	/// on ne veut pas de ce fichier qui existe
	if(rep==IDNO) return;

	/** On propage le nom du fichier de travail à la Classe d'ES */
	ES->FEcriture=nomfich;
	ES->FLecture =nomfich;
	rep=ES->lireFichier(true);
	/// cl lireFichier
	/// return 0   OK
	///        1  N'existe Pas MAIS Créer Nouveau
	///        2               Abandon

	if(rep==0)
	{
		/** Redondant avec StockerNomFichier */
		//Caption=AnsiString("Olympe")+"  Fichier="+ES->FLecture;
		FichierLu=true;

		StockerNomFichier();
		ES->StockagePermis=true;
	}
	else if(rep==1) // creer
	{
		ES->FEcriture =ES->FLecture;
		ES->Purge();
		ES->IniNouveau();
		FichierLu=true;

		StockerNomFichier();
		ES->StockagePermis=true;
	}
	//fichier n'existe pas ou version inconnue
	// ou on ne veut pas faire la mise a jour
	else if(rep==2)
	{
		FichierLu=false;
		ES->StockagePermis=false;
		return;
	}

// reduction en icone
// les ecrans sont prévus pour 1024 768
//  redimensionner si plus petit
	//tant qu'on est pas chez un agriculteur le dico affiche tous les elt
	TVDicoFrm->Complet=true;

	if(Screen->Width<1024)
	AdapterEcran();
}
//---------------------------------------------------------------------------
//ligne commande
//  contient seulement le nom du type d'action à faire
// les fichiers de commande doivent etre dans le réperoire d'olympe
//---------------------------------------------------------------------------
void TMainForm::LigneCommande(void) {
	AnsiString as;

//    as=    ParamStr(1);
	as = "AgriData"; //        c:\\olympeInter\\commandeOlympe.txt";
	//ShowMessage(as);
	if (as == "AgriData") {
		AgriDataFrm->LireLigneCommande();
		FichierLu = true;
	} else
		ShowMessage("Paramètre inconnu dans ligne de commande");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::CBLangueChange(TObject *Sender)
{
	char langue;
	langue=AsCodeLangue[CBLangue->ItemIndex+1]; //210610
	/*
	 switch(CBLangue->ItemIndex)
	 {
	 case 0: Langue='F';break;
	 case 1: Langue='E';break;  //English
	 case 2: Langue='S';break;  //Spanish
	 case 3: Langue='N';break;  //Nederland
	 case 4: Langue='P';break;  //Portugais
	 case 5: Langue='X';break;  //a définir

	 default: Langue='F';
	 }
	 */
	if(langue!=Langue)
	{
		Langue=langue;
		TexteEtCaption();
		AideFrm->Initialiser(Langue);

//        StockerNomFichier();
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TMainForm::TexteEtCaption(void) {
	bool estLu;
//char bufL[4];
// pour trouver la langue mais supprimé
//      GetLocaleInfo(LOCALE_USER_DEFAULT,LOCALE_SABBREVLANGNAME,bufL,sizeof(bufL));
//      Langue=bufL[0];   //si langue=='F' ne rien faire
//      Langue='E';//!!!!!!!!!!!!!!E comme English
//      Langue='F';//!!!!!!!!!!!!!!F comme Francais
//      Langue='S';//!!!!!!!!!!!!!!E comme Spanish
//      Langue='N';//!!!!!!!!!!!!!!F comme Nederland

	T = new CL_Trad;
	T->Erreur = false; //170306

	estLu = T->LireTraduction("Texte", Langue);
	//Fichier est ouvert dans la lecture de OlympeTxt
	//              mais pas dans           OlympeCaption
	// sera ferme ici aprés lectures
	if (estLu == false) {
		ShowMessage("Manque Fichier OlympeTxt.csv");
		Close();
		Application->Terminate();
		exit (EXIT_SUCCESS);
	}
	T->CreeTxtDialogue(); //Langue inutile

	estLu = T->LireTraduction("Caption", Langue); //pb estLu pourtexte & caption
	if (estLu == false) {
		ShowMessage("Manque Fichier OlympeCaption.csv");
		Close();
		Application->Terminate();
		exit (EXIT_SUCCESS);
	}
	T->CreeTxtCaption(); //Langue inutile

//      as=GereCatItemFrm->L_Impo;

	fclose(T->FichierErreur);
	if (T->Erreur == true)
		ShowMessage("Erreur voir OlympeTxtErreur.txt");

	ES->IniV_Poste();
}
//---------------------------------------------------------------------------
void TMainForm::AdapterEcran(void) {
	char buf[100];
	sprintf(buf, L_Ecran.c_str(), Screen->Width, Screen->Height);
	//sprintf(buf,"Ecran l=%d h=%d \n Adaptation à cet écran !!!",Screen->Width,Screen->Height);
	MessageBox(Handle, buf, L_Affichage.c_str(), MB_OK | MB_ICONEXCLAMATION);
	//MessageBox(Handle,buf,"AFFICHAGE",

	GereCatItemFrm->Left = Left;
	GereCatItemFrm->Top = Top + 40;

	GereAtelierFrm->Left = Left;
	GereAtelierFrm->Top = Top + 40;

	GereIndicFrm->Left = Left;
	GereIndicFrm->Top = Top + 40;

	GereEtatFrm->Left = Left;
	GereEtatFrm->Top = Top + 40;

	AgriSaisieFrm->Height = Height;
	AgriSaisieFrm->Width = Width; // 800;

	LBToutAgriFrm->Left = Left;
	LBToutAgriFrm->Top = Top + 40;

	TVPrixChoixFrm->Left = Screen->Width - TVPrixChoixFrm->Width;
	TVRdtChoixFrm->Left = Screen->Width - TVRdtChoixFrm->Left;

	TVDicoFrm->Left = Screen->Width - TVDicoFrm->Width;
	TVDicoFrm->Left = Screen->Width - TVDicoFrm->Left;

	LBSysUnitFrm->Left = Left; // 250202
	LBSysUnitFrm->Top = Top + 40;

	LBTvaFrm->Left = Left + 5;
	LBTvaFrm->Top = Top + 40; // LBSysUnitFrm->Height;

	MvtAnneeFrm->Left = Screen->Width - MvtAnneeFrm->Width;
}
/*
 //---------------------------------------------------------------------------
 void __fastcall TMainForm::ChoisirLangue(void)
 {
 switch(Langue)
 {
 case 'F':
 Francais();
 SysUniteFrm->Francais();
 Forme0Frm->Francais();
 Forme00Frm->Francais();
 DefProduitFrm->Francais();
 DefBestiauxFrm->Francais();
 DefCalendrierFrm->Francais();
 DefChStructFrm->Francais();
 DefEtatSortieFrm->Francais();
 DefItemFrm->Francais();
 DefProcedureFrm->Francais();
 DefProduitFrm->Francais();
 DefVariableFrm->Francais();
 DefZoneFrm->Francais();

 AgriDefSimFrm->Francais();
 AgriSaisieFrm->Francais();

 AleaPrixFrm->Francais();
 AssolFrm->Francais();
 AtelierFrm->Francais();
 AtelierMargeFrm->Francais();
 AtelierMDetailFrm->Francais();

 CommercialisationFrm->Francais(); //creé NON envoyé 6 juin


 break;

 case 'A':
 Anglais();
 SysUniteFrm->Anglais();
 Forme0Frm-> Anglais();
 Forme00Frm->Anglais();
 DefProduitFrm->Anglais();
 DefBestiauxFrm->Anglais();
 DefCalendrierFrm->Anglais();
 DefChStructFrm->Anglais();
 DefEtatSortieFrm->Anglais();
 DefItemFrm->Anglais();
 DefProcedureFrm->Anglais();
 DefProduitFrm->Anglais();
 DefVariableFrm->Anglais();
 DefZoneFrm->Anglais();

 AgriDefSimFrm->Anglais();
 AgriSaisieFrm->Anglais();
 AleaPrixFrm->Anglais();
 AssolFrm->Anglais();
 AtelierFrm->Anglais();
 AtelierMargeFrm->Anglais();
 AtelierMDetailFrm->Anglais();

 CommercialisationFrm->Anglais(); //creé NON envoyé 6 juin
 break;
 default:
 ShowMessage(L_Inco.c_str());
 //ShowMessage("langue inconnue");

 }
 }
 */
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int rep;
	//ES->AffLstMvtAniCount();
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
	//rep=MessageBox(Handle,"Vous voulez vraiment quitter ?","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		CanClose=true;
		//ne le fait que si ES->StockagePermis=true;
		ES->ecrireFichier();
	}

	else CanClose=false;

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::OuvrirClick(TObject *Sender)
{
	int rep;
	int tagSender;
	bool tout;
	// pour récupérer les données de base
	tagSender=((TMainMenu*)Sender)->Tag;//141105

	rep=1;
	OpenDialog->Title=L_Ouvrir;
	//OpenDialog->Title="Ouvrir";
//    OpenDialog->InitialDir = conf->data_path().c_str();
	//ne sert à rien
	//OpenDialog->InitialDir = AsHistorique.c_str();
	if ( !OpenDialog->Execute() )
	return;;

	ES->FLecture =OpenDialog->FileName;
	ES->FEcriture =ES->FLecture;
	ES->Purge();//160801
	/** Redondant avec StockerNomFichier */
	//Caption=AnsiString("Olympe")+"  Fichier="+ES->FLecture;
	if(tagSender==0)tout=true;
	else tout=false;

	rep=ES->lireFichier(tout);
	/// cl lireFichier
	/// return 0   OK
	///        1  N'existe Pas MAIS Créer Nouveau
	///        2               Abandon

	if(rep==2)//ancienne version on n'a pas voulu la mettre à jour
	{
		FichierLu=false;
		ES->StockagePermis=false;
		return;
	}
	FichierLu=true;

	StockerNomFichier();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::NouveauClick(TObject *Sender)
{
	SauverSous->Title=L_Nouveau;
	//SauverSous->Title="Nouveau";

	AnsiString fic = "";
	AnsiString Message;
	bool on_y_va = false;
	do {
		if (!SauverSous->Execute())
		return;
		fic = SauverSous->FileName;
		Message = fic + L_EcraserQ;
		//Message = fic + " existe déjà !\nEtes-vous bien sûr(e) de vouloir l'écraser ?\n";
		if (FileExists(fic))
		on_y_va = (MessageBox(Handle,Message.c_str(),L_EcraseFic.c_str(), MB_YESNO|MB_ICONEXCLAMATION) == IDYES);
		//on_y_va = (MessageBox(Handle,Message.c_str(),"Ecraser Un Fichier ?", MB_YESNO|MB_ICONEXCLAMATION) == IDYES);
		else
		on_y_va = true;
	}while (! on_y_va);

	ES->FLecture = fic;
	ES->FEcriture = fic;

	ES->Purge();
	ES->IniNouveau();

	FichierLu=true;

	StockerNomFichier();

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::EnregistrersousClick(TObject *Sender)
{
	int rep;
	SauverSous->Title=L_SauverSous;
	//SauverSous->Title="Enregistrer Sous";
	if(FichierLu==false)
	{
		MessageBox(Handle,L_PasFicOuv.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"Pas de fichier ouvert","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}
	//------
	SauverSous->FileName=ES->FEcriture;
	rep=SauverSous->Execute();
	if(rep==false) return;

	ES->FEcriture =SauverSous->FileName;
	ES->FLecture=ES->FEcriture;
	ES->ecrireFichier();

	FichierLu=true;

	StockerNomFichier();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StockerNomFichier(void)
{
	FILE *fichier;
	char nomFich[MAXPATH];
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char file[MAXFILE];
	char ext[MAXEXT];
	char buf[100];
	/** On reconstruit le titre de l'application */
	// voir il est possible que L_Fichier ne soit pas initialisé ??
//	Caption=AnsiString("OlympeInter")+L_Fichier+ES->FLecture;
	Caption=AnsiString("OlympeInter")+"  fichier : "+ES->FLecture;

	/** Construction du nom du fichier XL*/
	fnsplit(ES->FEcriture.c_str(),drive,dir,file,ext);
	fnmerge(nomFich,drive,dir,file,"CSV"); //210901
	ES->FExcel=nomFich;

	/** Traitement de l'historique des fichiers utilisés */
//string historique;
	/** Attention, conf a été instancié dans CreateForm */
//    historique = conf->exec_path () + "\\olympe.fic";
	fichier=fopen( AsHistorique.c_str() ,"wb");
	if(fichier==NULL) return;
	fputs(ES->FLecture.c_str(), fichier);
	sprintf(buf,"\nLangue %c",Langue);
	fputs(buf, fichier);
	fclose(fichier);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LireAccessClick(TObject *Sender)
{
	LireAccessFrm->LireFichier();
	ES->ecrireFichier();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::EcrireAccessClick(TObject *Sender)
{
	EcrireAccessFrm->EcrireFichier();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImpDeltaClick(TObject *Sender)
{
	ImpDeltaFrm->Show();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMainForm::ImprimanteClick(TObject *Sender)
{
	PrintDialog->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::QuitterClick(TObject *Sender)
{
	/*
	 //!Pourquoi tous ces delete ? (ac)
	 delete V_SystemeUnite;
	 delete V_Tva;
	 delete V_CatExternalite;
	 delete V_Produit;
	 delete V_Culture;
	 delete V_Espece;
	 delete V_Agriculteur;
	 delete V_EtatSortie;
	 delete V_Indicateur;
	 delete V_Poste;
	 delete V_Elt;
	 delete V_Ensemble;
	 */
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::EnregistrerClick(TObject *Sender)
{
	if(FichierLu==false)
	{
		MessageBox(Handle,L_PasFicOuv.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,L_PasFicOuv"Pas de fichier ouvert","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}
	ES->ecrireFichier();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImprimerToutClick(TObject *Sender)
{
//	FBrouillon->ImprimerLesDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AProposClick(TObject *Sender)
{
	AProposFrm->ShowModal();
}
//---------------------------------------------------------------------------

bool __fastcall TMainForm::VerifFichier(void)
{
	if(FichierLu==false)
	{
		MessageBox(Handle,L_PasFicOuv.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"Pas de fichier ouvert","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return false;
	}
	else
	return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//----------------------------BOUTONS----------------------------------------
//---------------------------------------------------------------------------
//  colonne 1
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtUniteClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	SysUniteFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtTVAClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	TvaFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::EnTestClick(TObject *Sender)
{
//    TarifFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtBnNettoyerClick(TObject *Sender)
{
	EffacerFrm->Show();
}
//---------------------------------------------------------------------------

//colonne 2
//---------------------------------------------------------------------------
void __fastcall TMainForm::LBDefinitionClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
}
//---------------------------------------------------------------------------
// colonne 3
//---------------------------------------------------------------------------
void __fastcall TMainForm::EspecesClick(TObject *Sender)
{

	if(VerifFichier()==false)return;
	EspeceFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LBProductionClick(TObject *Sender)
{
	int n;

	if(VerifFichier()==false)return;
	if(GereDefFrm && GereDefFrm->Visible==true) GereDefFrm->Close();

//    if(GereAtelierFrm->Visible==true) GereAtelierFrm->Close();
//    if(GereEspeceFrm->Visible==true)  GereEspeceFrm->Close();

	n=LBProduction->ItemIndex;
	GereAtelierFrm->Caption=LBProduction->Items->Strings[n];
	GereEspeceFrm->Caption=LBProduction->Items->Strings[n];
	switch(n)
	{
		case 0:GereAtelierFrm->Nature=CULTURE;break;
		case 1:GereAtelierFrm->Nature=ANIMAUX;break;
		case 2:GereEspeceFrm->Nature=PERENNE;break;
		case 3:GereAtelierFrm->Nature=VIVRIER;break;
	}
	switch(n)
	{
		case 0:
		case 1:
		case 3:
		GereDefFrm=GereAtelierFrm;
		GereAtelierFrm->Origine=0; //301203
		GereAtelierFrm->Show();
		break;
		case 2:
		GereDefFrm=GereEspeceFrm;
		GereEspeceFrm->Origine=0;//301203
		GereEspeceFrm->Show();
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LBAleaClick(TObject *Sender)
{
	int n;

	if(GereDefFrm && GereDefFrm->Visible==true) GereDefFrm->Close();
	n=LBAlea->ItemIndex;
	switch(n)
	{
		case 0:
		GereAleaPrixFrm->Origine=0;
		GereDefFrm=GereAleaPrixFrm;
		GereAleaPrixFrm->Show();
		break;
		case 1:
		GereAleaRdtFrm->Origine=0;
		GereDefFrm=GereAleaRdtFrm;
		GereAleaRdtFrm->Show();
		break;
	}
}
//---------------------------------------------------------------------------
// colonne 3
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtAgriEnCoursClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	if(AgriEnCours==NULL)
	{
		ShowMessage(L_PasAgri.c_str());
		//ShowMessage("Pas d'agriculteur sélectionné");
		return;
	}
	AgriSaisieFrm->Agri=AgriEnCours;
	AgriSaisieFrm->Origine=0;
	AgriSaisieFrm->Show();
	//ES->AffLstMvtAniCount();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtAutreAgriClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	GereAgriFrm->Origine=0;
	GereAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtEnsEnCoursClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	if(EnsembleEnCours==NULL)
	{
		ShowMessage(L_PasEnsemble.c_str());
		//ShowMessage("Pas d'ensemble selectionné");
		return;
	}
	GereEnsembleFrm->VientDe="Main";
	GereEnsembleFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtAutreEnsembleClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	GereEnsembleFrm->VientDe="Main";
	GereEnsembleFrm->Show();
}
//---------------------------------------------------------------------------
//colonne 5
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtZoneTypeClick(TObject *Sender)
{
	if(VerifFichier()==false)return;

	GereCatZoneFrm->Nature=ZONE;
	GereCatZoneFrm->Origine=0;
	GereCatZoneFrm->Caption=BtZoneType->Caption;
	GereCatZoneFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtIndicateurClick(TObject *Sender)
{
	if(VerifFichier()==false) return;

	if(GereDefFrm && GereDefFrm->Visible==true) GereDefFrm->Close();

	GereDefFrm= GereIndicFrm;
	GereIndicFrm->Nature=INDIC;
	GereIndicFrm->Origine = 0;
	GereIndicFrm->Caption=BtIndicateur->Caption; //140206
	GereIndicFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtEtatSortieClick(TObject *Sender)
{
	if(VerifFichier()==false)return;

	if(GereDefFrm && GereDefFrm->Visible==true) GereDefFrm->Close();

	GereDefFrm= GereEtatFrm;
	GereEtatFrm->Nature=ETAT;
	GereEtatFrm->Origine=0;
	GereEtatFrm->Caption=BtEtatSortie->Caption; //140206
	GereEtatFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtComparaisonClick(TObject *Sender)
{
	if(VerifFichier()==false)return;

	if(GereDefFrm && GereDefFrm->Visible==true) GereDefFrm->Close();

	GereDefFrm= GereComparaisonFrm;

	GereComparaisonFrm->Nature=COMPARAISON;
	GereComparaisonFrm->Origine=0;
	GereComparaisonFrm->Caption=BtComparaison->Caption; //140206
	GereComparaisonFrm->Show();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
 void __fastcall TMainForm::BtProcedureClick(TObject *Sender)
 { //11512
 if(VerifFichier()==false)return;

 if(GereDefFrm && GereDefFrm->Visible==true)   GereDefFrm->Close();

 GereDefFrm= GereProcedureFrm;


 GereProcedureFrm->Nature=PROCEDURE;
 GereProcedureFrm->Origine=0;
 GereProcedureFrm->Caption=BtProcedure->Caption;          //140206
 GereProcedureFrm->Show();

 }
 */
//---------------------------------------------------------------------------
// appelé par ailleurs ex TVChoix
//---------------------------------------------------------------------------
void __fastcall TMainForm::NouvelleDefinition(int nature)
{
	Forme0Frm->Nature=nature;
//ShowMessage(AnsiString("NouvelleDefinition  ")+nature);
	switch(nature)
	{
		case CULTURE:
		case ANIMAUX:
		case VIVRIER:
		GereAtelierFrm->Nature=nature;
		GereAtelierFrm->Show();
		break;
		case PERENNE:
		GereEspeceFrm->Nature=nature;
		GereEspeceFrm->Show();
		break;
		case PRODUIT:
		case CHARGE:
		GereCatProduitFrm->Nature=nature;
		GereCatProduitFrm->Personnaliser();
		GereCatProduitFrm->Show();
		break;
		case EXTPOS:
		case CHSTRUCT:
		case DEPDIV:
		case RECDIV:
		case DEPFAM:
		case RECFAM:
		GereCatChStructFrm->Nature=nature;
		GereCatChStructFrm->Show();
		break;
		case VARIABLE:
		GereCatVariableFrm->Nature=nature;
		GereCatVariableFrm->Show();
		break;
		case COMPARAISON:
		BtComparaisonClick(this);
		break;
		default:
		ShowMessage(L_NouvDef.c_str());break;
		//ShowMessage("NouvelleDéfinition");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	_fcloseall();
	// a supprimer
	/*
	 if (ES) 	delete ES;
	 if (Compil) delete Compil;
	 if (EX)     delete EX;
	 */
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StockageClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,L_StocPermis.c_str(),L_Fich.c_str(),MB_YESNO|MB_ICONQUESTION);
	//rep=MessageBox(Handle,"Stockage Permis ?","FICHIER",MB_YESNO|MB_ICONQUESTION);
	if(rep==IDYES) ES->StockagePermis=true;
	else ES->StockagePermis=false;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtBnNotesClick(TObject *Sender)
{

	NoteAgriFrm->VientDe="Main";
	NoteAgriFrm->Caption=L_Note;
	//NoteAgriFrm->Caption="Notes";
	NoteAgriFrm->Memo->Text=Notes;

	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TestClick(TObject *Sender)
{
//rien (ac) pour faire plaisir au lieur
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Prfrences1Click(TObject *Sender)
{
//    conf->gui_input();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TMainForm::LBItemAtelierClick(TObject *Sender)
{
	int n;
	AnsiString as;
	as=GereCatItemFrm->L_Impo;

	if(VerifFichier()==false)return;

	n=LBItemAtelier->ItemIndex;
	if(n==4) //gere des CL_Periode
	{
		GereCalendrierFrm->Origine=0;
		GereCalendrierFrm->Caption=LBItemAtelier->Items->Strings[n];
		GereCalendrierFrm->Show();
		return;
	}

	// une seule fenêtre ouverte
	if(GereDefFrm && GereDefFrm->Visible==true)GereDefFrm->Close();
	switch(n)//gere des CL_Item
	{
		case 0:
		GereDefFrm=GereCatProduitFrm;
		GereCatProduitFrm->Origine=0;
		GereCatProduitFrm->Nature= PRODUIT;
		GereCatProduitFrm->Caption=LBItemAtelier->Items->Strings[n];
		GereCatProduitFrm->Show();
		break;
		case 1:
		GereDefFrm=GereCatProduitFrm;
		GereCatProduitFrm->Origine=0;
		GereCatProduitFrm->Nature= CHARGE;
		GereCatProduitFrm->Caption=LBItemAtelier->Items->Strings[n];
		GereCatProduitFrm->Show();
		break;
		case 2:
		GereDefFrm=GereCatVariableFrm;
		GereCatVariableFrm->Origine=0;
		GereCatVariableFrm->Nature=EXTPOS;
		GereCatVariableFrm->Caption=LBItemAtelier->Items->Strings[n];
		GereCatVariableFrm->Show();
		break;
		case 3:
		GereDefFrm=GereCatBestiauxFrm;
		GereCatBestiauxFrm->Origine=0;
		GereCatBestiauxFrm->Nature=BESTIAUX;
		GereCatBestiauxFrm->Caption=LBItemAtelier->Items->Strings[n];
		GereCatBestiauxFrm->Show();
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LBItemEntrepriseClick(TObject *Sender)
{
	int n;
	if(VerifFichier()==false)return;

	n=LBItemEntreprise->ItemIndex;
	if(GereDefFrm && GereDefFrm->Visible==true)GereDefFrm->Close();
	GereDefFrm=GereCatChStructFrm;
	GereCatChStructFrm->Origine=0;
	switch(n)
	{
		case 0: GereCatChStructFrm->Nature=CHSTRUCT; break;
		case 1: GereCatChStructFrm->Nature=DEPDIV; break;
		case 2: GereCatChStructFrm->Nature=RECDIV; break;
	}
	GereCatChStructFrm->Caption=LBItemEntreprise->Items->Strings[n]; //130206
	GereCatChStructFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBItemFamilleClick(TObject *Sender)
{
	int n;
	if(VerifFichier()==false)return;

	n=LBItemFamille->ItemIndex;
	if(GereDefFrm && GereDefFrm->Visible==true)GereDefFrm->Close();
	GereDefFrm=GereCatChStructFrm;
	GereCatChStructFrm->Origine=0;
	switch(n)
	{
		case 0: GereCatChStructFrm->Nature=RECFAM; break;
		case 1: GereCatChStructFrm->Nature=DEPFAM; break;
	}
	GereCatChStructFrm->Caption=LBItemFamille->Items->Strings[n]; //130206
	GereCatChStructFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBItemDiversClick(TObject *Sender)
{
	if(VerifFichier()==false)return;
	// un seul choix
	//n=LBItemDivers->ItemIndex;

	if(GereDefFrm && GereDefFrm->Visible==true)GereDefFrm->Close();

	GereDefFrm=GereCatVariableFrm;
	GereCatVariableFrm->Origine=0;
	GereCatVariableFrm->Nature=VARIABLE;
	GereCatVariableFrm->Caption=LBItemDivers->Items->Strings[0];
	GereCatVariableFrm->Show();

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::LBItemAtelierExit(TObject *Sender)
{
	LBItemAtelier->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBItemEntrepriseExit(TObject *Sender)
{
	LBItemEntreprise->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBItemFamilleExit(TObject *Sender)
{
	LBItemFamille->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBItemDiversExit(TObject *Sender)
{
	LBItemDivers->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBProductionExit(TObject *Sender)
{
	LBProduction->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::LBAleaExit(TObject *Sender)
{
	LBAlea->ItemIndex=-1;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TMainForm::EmpecherGrosBug(void) {
	CL_Vecteur<CL_Valeur> *V_Culture;
	CL_Vecteur<CL_Verger> *V_Verger;
	CL_Vecteur<CL_InvAni> *V_InvAni;

	CL_Vecteur<CL_Formule> *V_Produits;

	CL_Vecteur<CL_Valeur> *V_Variable;

	CL_Vecteur<CL_Immo> *V_Immo;
	CL_Vecteur<CL_Petit> *V_Petit;
	CL_Vecteur<CL_FN_Xp1> *V_FinSom;

	CL_Vecteur<CL_EmpLT> *V_EmpLT;
	CL_Vecteur<CL_EmpCT> *V_EmpCT;
	CL_Vecteur<CL_Sub> *V_Sub;
	CL_Vecteur<CL_Occc> *V_Occc;
	CL_Vecteur<CL_Plact> *V_Plact;

	CL_Vecteur<CL_EnCours> *V_Creance;
	CL_Vecteur<CL_StockIni> *V_StockIni; //111201

	// ça permet d'eviter le GROS BUG mais pourquoi ???
	V_Culture = new CL_Vecteur<CL_Valeur>();
	V_Verger = new CL_Vecteur<CL_Verger>();
	V_InvAni = new CL_Vecteur<CL_InvAni>();

	V_Produits = new CL_Vecteur<CL_Formule>();

	V_Variable = new CL_Vecteur<CL_Valeur>();

	V_EmpLT = new CL_Vecteur<CL_EmpLT>();
	V_EmpCT = new CL_Vecteur<CL_EmpCT>();
	V_Sub = new CL_Vecteur<CL_Sub>();
	V_Plact = new CL_Vecteur<CL_Plact>();
	V_Occc = new CL_Vecteur<CL_Occc>();
	V_FinSom = new CL_Vecteur<CL_FN_Xp1>();

	V_Immo = new CL_Vecteur<CL_Immo>();
	V_Petit = new CL_Vecteur<CL_Petit>();

	V_Creance = new CL_Vecteur<CL_EnCours>();

	V_StockIni = new CL_Vecteur<CL_StockIni>();

	delete V_Culture;
	delete V_Verger;
	delete V_InvAni;

	delete V_Produits;

	delete V_Variable;

	delete V_Immo;
	delete V_Petit;
	delete V_FinSom;

	delete V_EmpLT;
	delete V_EmpCT;
	delete V_Sub;
	delete V_Occc;
	delete V_Plact;

	delete V_Creance;
	delete V_StockIni;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::BtBnXmlClick(TObject *Sender)
{
	bool res;
//AnsiString as;
	char nomFichier[MAXPATH];
	char sortieNom[MAXPATH];
	char drive[MAXDRIVE], dir[MAXDIR], name[MAXFILE], ext[MAXEXT];

	strncpy(nomFichier,ES->FEcriture.c_str(),MAXPATH);

	// Construire le nom du fichier.Xml !!! */
	fnsplit( nomFichier, drive, dir, name, ext);
	fnmerge( sortieNom, drive, dir, name, ".xml");

	OpenDialogXml->FileName=AnsiString(sortieNom);
	res=OpenDialogXml->Execute();
	if(res==false) return;

//    as=OpenDialogXml->FileName;
	Xml=new CL_Xml();
	Xml->NomFichier=OpenDialogXml->FileName.c_str();
	Xml->EcrireFichier();
	delete Xml;

//	ES->ImpFichierAscii();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TMainForm::TexteChaine(void) {
	L_PasMemoire = T->TrouveTexte("MainForm", "L_PasMemoire");
	L_DateLim = T->TrouveTexte("MainForm", "L_DateLim");
	L_FinTest = T->TrouveTexte("MainForm", "L_FinTest");
	L_AOuvrir = T->TrouveTexte("MainForm", "L_AOuvrir");
	L_Ecran = T->TrouveTexte("MainForm", "L_Ecran");
	L_Affichage = T->TrouveTexte("MainForm", "L_Affichage");
	L_Inco = T->TrouveTexte("MainForm", "L_Inco");
	L_Ouvrir = T->TrouveTexte("MainForm", "L_Ouvrir");
	L_Nouveau = T->TrouveTexte("MainForm", "L_Nouveau");
	L_EcraserQ = T->TrouveTexte("MainForm", "L_EcraserQ");
	L_EcraseFic = T->TrouveTexte("MainForm", "L_EcraseFic");
	L_SauverSous = T->TrouveTexte("MainForm", "L_SauverSous");
	L_PasFicOuv = T->TrouveTexte("MainForm", "L_PasFicOuv");
	L_Fichier = T->TrouveTexte("MainForm", "L_Fichier");
	L_PasAgri = T->TrouveTexte("MainForm", "L_PasAgri");
	L_PasEnsemble = T->TrouveTexte("MainForm", "L_PasEnsemble");
	L_NouvDef = T->TrouveTexte("MainForm", "L_NouvDef");
	L_StocPermis = T->TrouveTexte("MainForm", "L_StocPermis");
	L_Fich = T->TrouveTexte("MainForm", "L_Fich");
	L_Note = T->TrouveTexte("MainForm", "L_Note");

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TMainForm::IniCaption(void) {
	Enregistrer->Caption = LC_Enregistrer;
	Fichier1->Caption = LC_Fichier1;
	APropos->Caption = LC_APropos;
	Nouveau->Caption = LC_Nouveau;
	Ouvrir->Caption = LC_Ouvrir;
	LireDonGlob->Caption = LC_LireDonGlob; //121007
	LireAccess->Caption = LC_LireAccess;
	EcrireAccess->Caption = LC_EcrireAccess;

	ImporterDonneesCSV->Caption = LC_ImportDon;
	GBAgri->Caption = T->LC_GBAgri;
	GBAlea->Caption = T->LC_GBAlea;
	GBAtelier->Caption = T->LC_GBAtelier;
	BtAutreAgri->Caption = T->LC_BtAutreAgri;
	BtAutreEnsemble->Caption = T->LC_BtAutreAgri;
	BtZoneType->Caption = T->LC_LabZone;
	BtComparaison->Caption = T->LC_GereComparaisonFrm;
	Prfrences1->Caption = LC_Prfrences1;
	GBDefinition->Caption = T->LC_GBDefinition;
	GBDivers->Caption = T->LC_DIVERS1;
//    Label4->Caption=T->LC_Label11;
//    LabFleche5->Caption=LC_LabFleche5;     //supprimer LC_LabFleche5 ...
	BtAgriEnCours->Caption = LC_BtAgriEnCours;
	Enregistrersous->Caption = LC_Enregistrersous;
	BtEnsEnCours->Caption = T->LC_BtEnsEnCours;
	GBEnsemble->Caption = T->LC_GBEnsemble;
	BtEtatSortie->Caption = T->LC_DefEtatSortieFrm;
//    BtBnAscii->Caption=LC_BtBnAscii;
	BtBnXml->Caption = LC_BtBnXml;
	BtIndicateur->Caption = T->LC_LabIndicateur;
	BtBnEffacer->Caption = T->LC_BtBnEffacer;
	BtBnNotes->Caption = T->LC_BtBnNotes;
//    PanClassif->Caption=T->LC_PanClassif;
	BtPhase->Caption = T->LC_EspeceFrm;
	GBItemAtelier->Caption = LC_GBItemAtelier;
	GBItemAgri->Caption = LC_GBItemAgri;
	GBItemFamille->Caption = LC_GBItemFamille;
//      BtProcedure->Caption=T->LC_LabProcedure; //110512
	GBProduction->Caption = T->LC_PRODUCTIONS;
	BoutFermer->Caption = T->LC_BtBnQuitter;
	Test->Caption = LC_Test;
	BtTVA->Caption = T->LC_BtBnTva;
	BtUnite->Caption = T->LC_BtBnUnite;
	GBProduction->Caption = LC_Atelier;

	LBItemAtelier->Items->Strings[0] = LC_Produits;
	LBItemAtelier->Items->Strings[1] = LC_Charges;
	LBItemAtelier->Items->Strings[2] = LC_Exter;
	LBItemAtelier->Items->Strings[3] = LC_Troupeaux;
	LBItemAtelier->Items->Strings[4] = LC_PerTrav;

	LBItemEntreprise->Items->Strings[0] = LC_ChStruct;
	LBItemEntreprise->Items->Strings[1] = LC_DepDiv;
	LBItemEntreprise->Items->Strings[2] = LC_RecDiv;

	LBItemFamille->Items->Strings[0] = LC_RecFam;
	LBItemFamille->Items->Strings[1] = LC_DepFam;

	LBItemDivers->Items->Strings[0] = LC_Var;

	LBProduction->Items->Strings[0] = LC_Cultures;
	LBProduction->Items->Strings[1] = LC_Animaux;
	LBProduction->Items->Strings[2] = LC_Perennes;
	LBProduction->Items->Strings[3] = LC_Pluri;

	LBAlea->Items->Strings[0] = LC_Prix;
	LBAlea->Items->Strings[1] = LC_Quant;

	GBDivers->Caption = LC_Divers;
//    BtBnRacDef->Caption=LC_DefRaccourci;    //181109  110512

	//200206
//??    LireDonneesGlobales->Caption=LC_LireDonGlob;
//    MainMenu1->Fichier1->LireDonneesGlobales->Caption=LC_LireDonGlob;
}
//--------------------------------------------
void TMainForm::TexteCaption(void) {
	LC_Enregistrer = T->TrouveCaption("Main", "LC_Enregistrer");
	LC_Fichier1 = T->TrouveCaption("Main", "LC_Fichier1");
	LC_APropos = T->TrouveCaption("Main", "LC_APropos");
	LC_Nouveau = T->TrouveCaption("Main", "LC_Nouveau");
	LC_Ouvrir = T->TrouveCaption("Main", "LC_Ouvrir");
	LC_LireDonGlob = T->TrouveCaption("Main", "LC_LireDonGlob");
	LC_ImportDon = T->TrouveCaption("Main", "LC_ImportDon");
	LC_LireAccess = T->TrouveCaption("Main", "LC_LireAccess"); //301008
	LC_EcrireAccess = T->TrouveCaption("Main", "LC_EcrireAccess"); //301008

	LC_GBAgri = T->TrouveCaption("CL_Trad", "LC_GBAgri");
	LC_GBAlea = T->TrouveCaption("CL_Trad", "LC_GBAlea");
	LC_GBAtelier = T->TrouveCaption("CL_Trad", "LC_GBAtelier");
	LC_BtAutreAgri = T->TrouveCaption("CL_Trad", "LC_BtAutreAgri");
	LC_LabZone = T->TrouveCaption("CL_Trad", "LC_LabZone");
	LC_GereComparaisonFrm = T->TrouveCaption("CL_Trad",
			"LC_GereComparaisonFrm");
	LC_Prfrences1 = T->TrouveCaption("Main", "LC_Prfrences1");
	LC_GBDefinition = T->TrouveCaption("CL_Trad", "LC_GBDefinition");
	LC_DIVERS1 = T->TrouveCaption("CL_Trad", "LC_DIVERS1");
	LC_Label11 = T->TrouveCaption("CL_Trad", "LC_Label11");
	LC_LabFleche5 = T->TrouveCaption("Main", "LC_LabFleche5");
	LC_CreancesDettes1 = T->TrouveCaption("CL_Trad", "LC_CreancesDettes1");
	LC_Enregistrersous = T->TrouveCaption("Main", "LC_Enregistrersous");
	LC_BtEnsEnCours = T->TrouveCaption("CL_Trad", "LC_BtEnsEnCours");
	LC_GBEnsemble = T->TrouveCaption("CL_Trad", "LC_GBEnsemble");
	LC_DefEtatSortieFrm = T->TrouveCaption("CL_Trad", "LC_DefEtatSortieFrm");
	LC_BtBnAscii = T->TrouveCaption("Main", "LC_BtBnAscii");
	LC_BtBnXml = T->TrouveCaption("Main", "LC_BtBnXml");
	LC_LabIndicateur = T->TrouveCaption("CL_Trad", "LC_LabIndicateur");
	LC_BtBnEffacer = T->TrouveCaption("CL_Trad", "LC_BtBnEffacer");
	LC_BtBnNotes = T->TrouveCaption("CL_Trad", "LC_BtBnNotes");
	LC_PanClassif = T->TrouveCaption("CL_Trad", "LC_PanClassif");
	LC_EspeceFrm = T->TrouveCaption("CL_Trad", "LC_EspeceFrm");
	LC_GBItemAtelier = T->TrouveCaption("Main", "LC_GBItemAtelier");
	LC_GBItemAgri = T->TrouveCaption("Main", "LC_GBItemAgri");
	LC_GBItemFamille = T->TrouveCaption("Main", "LC_GBItemFamille");
	LC_LabProcedure = T->TrouveCaption("CL_Trad", "LC_LabProcedure");
	LC_PRODUCTIONS = T->TrouveCaption("CL_Trad", "LC_PRODUCTIONS");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_Test = T->TrouveCaption("Main", "LC_Test");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");
	LC_BtBnUnite = T->TrouveCaption("CL_Trad", "LC_BtBnUnite");
	LC_BtAgriEnCours = T->TrouveCaption("Main", "LC_BtAgriEnCours");
	LC_Atelier = T->TrouveCaption("Main", "LC_Atelier");

	LC_Produits = T->TrouveCaption("Main", "LC_Produits");
	LC_Charges = T->TrouveCaption("Main", "LC_Charges");
	LC_Exter = T->TrouveCaption("Main", "LC_Exter");
	LC_Troupeaux = T->TrouveCaption("Main", "LC_Troupeaux");
	LC_PerTrav = T->TrouveCaption("Main", "LC_PerTrav");

	LC_ChStruct = T->TrouveCaption("Main", "LC_ChStruct");
	LC_DepDiv = T->TrouveCaption("Main", "LC_DepDiv");
	LC_RecDiv = T->TrouveCaption("Main", "LC_RecDiv");

	LC_RecFam = T->TrouveCaption("Main", "LC_RecFam");
	LC_DepFam = T->TrouveCaption("Main", "LC_DepFam");

	LC_Var = T->TrouveCaption("Main", "LC_Var");

	LC_Cultures = T->TrouveCaption("Main", "LC_Cultures");
	LC_Animaux = T->TrouveCaption("Main", "LC_Animaux");
	LC_Perennes = T->TrouveCaption("Main", "LC_Perennes");
	LC_Pluri = T->TrouveCaption("Main", "LC_Pluri");

	LC_Prix = T->TrouveCaption("Main", "LC_Prix");
	LC_Quant = T->TrouveCaption("Main", "LC_Quant");

	LC_Divers = T->TrouveCaption("Main", "LC_Divers");
	LC_DefRaccourci = T->TrouveCaption("Main", "LC_DefRaccourci"); //181109

//     LC_LireDonGlob=T->TrouveCaption("Main","LC_LireDonGlob");

	IniCaption();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Aide1Click(TObject *Sender)
{
//	AideFrm->Show();
	AideFrm->AfficherAide(Langue,0);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ImporterDonneesCSVClick(TObject *Sender)
{
	AgriDataFrm->Show();
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::FormHelp(WORD Command, int Data, bool &CallHelp)
{
	CallHelp = false;
	AideFrm->AfficherAide(Langue,HelpContext);
	return true;
}
//---------------------------------------------------------------------------
/*
 void __fastcall TMainForm::RGExcelClick(TObject *Sender)
 {
 if(RGExcel->ItemIndex==0)
 AsExcelExt="xls";
 else
 AsExcelExt="xslx";

 }
 */
//---------------------------------------------------------------------------
/*         100512
 void __fastcall TMainForm::BtBnRacDefClick(TObject *Sender)
 {
 RacDefFrm->Show();
 }
 */
//---------------------------------------------------------------------------

void __fastcall TMainForm::BoutFermerClick(TObject *Sender)
{
	int a=0;
}
//---------------------------------------------------------------------------

