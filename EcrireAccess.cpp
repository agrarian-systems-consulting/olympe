//---------------------------------------------------------------------------
//** Formulaire:: TEcrireAccessFrm
//**    Objet: Export des données Olympe en base de données MS Access.
//**
//** Methode principale: EcrireFichierAccess()
//**    Algorithme:
//**
//** Si Dialogue
//**    * Creation des objets de gestion de la BDD
//**      * Création de la base de données ACCESS
//**      * Creation des adoquery et adotable
//**
//**    * affichage de la fenetre
//**    * Creation rapport
//**
//**    * Création BDD
//**      * Tables
//**      * Clés primaires
//**      * Clés étrangères
//**      * Insertion des définitions et catégories
//**      * Insertion des autres objets
//**
//**      * Destruction des objets de gestion
//**      * fermeture de la fenetre
//**
//---------------------------------------------------------------------------
#include <vcl.h>
#include <comobj.hpp>
#include  "dir.h"

#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//#include "DefVecteur.h"

#include "Main.h"
#include "CL_Trad.h"
#include "FichierLire.h"
#include "AgriClasst.h"

#include "CL_Matrice.h"
#include "CL_BesTrav.h"

#include "EcrireAccess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEcrireAccessFrm *EcrireAccessFrm;
extern CL_Trad *T;
extern CL_ES *ES;
//---------------------------------------------------------------------------
//------------------------modifier le 17-08-2010 par Rebaubier William-------
//------------------------modifier en juin 2012 par Thierry PUCH
//---------------------------------------------------------------------------
__fastcall TEcrireAccessFrm::TEcrireAccessFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireFichier(void) {
	EcrireFichierAccess();

	//EcrireConversion(adoTable,"Conversion",V_Conversion);
	// Agri_defsim
	// FichierLu=true;
	// R_AgriValeur  impossible de l'ouvrir dans Access
	// a faire emprunts, matériel

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireRapport(AnsiString info) {
	char chaine[150];
	ofstream outfile("ExportMdb.rap", ios::app);

	sprintf(chaine, "%s", TimeToStr(Now()));
	outfile << chaine << endl;
	sprintf(chaine, "%s", info);
	outfile << chaine << endl;
	outfile.close();
}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireFichierAccess(void) {
	char file[MAXFILE];

	AnsiString as;
	TADOTable *adoTable;
	TADOTable *adoTable1;
	TADOQuery *adoQuery;
	TADOCommand *adoCommand;

	bool on_y_va = false;
	AnsiString Message;
	cpt = 0;

	AnsiString asDataSource;

	//Dialogue
	if (Dialogue_EcrireAccess(&asDataSource, file)) {
		//Creation des objets de gestion de la BDD
		AnsiString asProvider = "Provider=Microsoft.Jet.OLEDB.4.0;";
		AnsiString asUserId = "User ID=Admin;";
		// Création de la base de données ACCESS
		Variant vADO;
		AnsiString provider = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="
				+ asDataSource + ";";
		asDataSource = AnsiString("Data Source=") + asDataSource;
		vADO = Variant::CreateObject("ADOX.Catalog");
		vADO.OleFunction("create", provider.c_str());

		adoQuery = new TADOQuery(this);
		adoQuery->Active = false;
		adoQuery->ConnectionString = asProvider + asUserId + asDataSource;

		adoTable1 = new TADOTable(this);
		adoTable = new TADOTable(this);
		adoTable->Active = false;
		adoTable->ConnectionString = asProvider + asUserId + asDataSource;
		adoTable1->Active = false;
		adoTable1->ConnectionString = asProvider + asUserId + asDataSource;

		EcrireAccessFrm->Show();

		//Creation rapport
		CreationRapport_EcrireAccess();
		//Création BDD
		//Tables

		CreationTables_EcrireAccess(adoQuery);

		//Clés primaires
		CreationClePrimaire_EcrireAccess(adoQuery);

		//Clés étrangères
		CreationCleEtrangere_EcrireAccess(adoQuery);

		// Définitions et Catégories
		InsertDonneesDefCat_EcrireAccess(adoQuery, adoTable, adoTable1);

		// Autres objets
		InsertDonneesAutres_EcrireAccess(adoQuery, adoTable, adoTable1);

		EcrireRapport("EcrireProjet");
		EcrireProjet(adoTable, "Projet", file);
		ProgressBar->StepBy(1);

		delete adoTable;
		delete adoTable1;
		delete adoQuery;
		EcrireRapport("Fin");

		EcrireAccessFrm->Close();
	}
}
//---------------------------------------------------------------------------
bool TEcrireAccessFrm::Dialogue_EcrireAccess(AnsiString *as, char file[]) {
	bool on_y_va = false;
	AnsiString Message;
	bool res;
	char nomfich[MAXPATH];
	char drive[MAXDRIVE];
	char dir[MAXDIR];
	char ext[MAXEXT];

	EcrireAccessFrm->Caption = LC_Encours;

	fnsplit(ES->FEcriture.c_str(), drive, dir, file, ext);
	fnmerge(nomfich, drive, dir, file, ".mdb");

	SaveDialog->FileName = nomfich;
	SaveDialog->Title = LC_Enregistrer;
	while (on_y_va == false) {
		res = SaveDialog->Execute();
		if (res == false)
			return res;

		*as = SaveDialog->FileName;
		Message = *as + L_RemplaceAll;
		if (FileExists(*as)) {
			//Confirmation d'écrasement si le fichier BDD Access existe déjà
			on_y_va = (MessageBox(Handle, Message.c_str(), L_Remplace.c_str(),
					MB_YESNO | MB_ICONEXCLAMATION) == IDYES);

			if (on_y_va == true)
				if (!DeleteFile(*as)) { //Impossible d'effacer le fichier
					ShowMessage(
							"remplacement impossible veuillez vérifiez que le fichier Access n'est pas ouvert");
				}
		} else
			on_y_va = true;
	}

	return on_y_va;

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::CreationRapport_EcrireAccess() {
	//re-initialise le rapport
	ofstream outfile("ExportMdb.rap");
	outfile.close();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Création des tables
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::CreationTables_EcrireAccess(TADOQuery *adoQuery) {
	//Création des tables sans contraintes //

	// Les Définitions
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE _Definitions (IdDefinitions INTEGER ,NomCat STRING,NameCat STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE _Aleas (IdAleas INTEGER,NomAlea STRING,NameHazard STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE _Ateliers (IdAteliers INTEGER,NomAte STRING,NameAte STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE _Ate_ListItem (IdAteListItem INTEGER,NomAteListItem STRING,NameAteListItem STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE _Agri_ListValeur (IdAgriValeur INTEGER,NomAgriValeur STRING,NameAgriVal STRING)");
	adoQuery->ExecSQL();

	// Création des tables et des champs de la base
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE SystemeUnite (IdSysUnit INTEGER ,UAte STRING,UEnt STRING,UGlobal STRING,Ratio21 DOUBLE,Ratio32 DOUBLE,Monnaie BIT)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE TVA (IdTva INTEGER, Nom STRING,Taux DOUBLE,Defaut BIT,Immo BIT)");
	adoQuery->ExecSQL();

	//----------Categorie------------------------------
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Categ (IdDefinitions INTEGER ,IdDefCateg INTEGER ,Nom STRING ,Notes MEMO) ");
	adoQuery->ExecSQL();

	//----------Definition------------------------------
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Item (IdDefCateg INTEGER,IdDefinitions INTEGER ,IdDefItem INTEGER ,Nom STRING,IdSysUnit INTEGER,Prix DOUBLE,IdTva INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Critere (IdDefCateg INTEGER,IdDefinitions INTEGER,IdDefItem INTEGER,Nom STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Dico (IdDefCateg INTEGER,IdDefinitions INTEGER,IdDefDico INTEGER,Nom STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_EtatSortie (IdDefinitions INTEGER, IdDefCateg INTEGER,IdEtatSortie INTEGER,IdDefEtatSortie INTEGER,Nom STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_SerieComp (IdDefinitions INTEGER, IdDefCateg INTEGER,IdEtatSortie INTEGER,IdDefEtatSortie INTEGER,Nom STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Conversion (IdConversion INTEGER,IdDefinitions INTEGER,NoBase INTEGER,NoSortie INTEGER,APartirDe INTEGER,Nom STRING,EVF1 INTEGER,EVF2 INTEGER,EVF3 INTEGER,EVF4 INTEGER,EVF5 INTEGER,EVF6 INTEGER,EVF7 INTEGER,EVF8 INTEGER,EVF9 INTEGER,EVF10 INTEGER,FVE1 INTEGER,FVE2 INTEGER,FVE3 INTEGER,FVE4 INTEGER,FVE5 INTEGER,FVE6 INTEGER,FVE7 INTEGER,FVE8 INTEGER,FVE9 INTEGER,FVE10 INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Indicateur (IdDefCateg INTEGER,IdDefinitions INTEGER,IdDefItem INTEGER,Nom STRING, Notes MEMO)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Calendrier (IdDefCateg INTEGER,IdDefinitions INTEGER,IdPeriode INTEGER,Nom STRING,JDeb INTEGER,MDeb INTEGER,JFin INTEGER,MFin INTEGER,PcentDispo INTEGER,HpJ DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Def_Bestiaux (IdDefCateg INTEGER,IdDefinitions INTEGER,IdBestiaux INTEGER,Nom STRING,IdOrigine INTEGER,IdTva INTEGER,Prix DOUBLE,Vallnv DOUBLE,Donne1 INTEGER,DonnePcent1 DOUBLE,Donne2 INTEGER,DonnePcent2 DOUBLE, Donne3 INTEGER,DonnePcent3 DOUBLE,Donne4 INTEGER,DonnePcent4 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Indicateur (NoIndic INTEGER,Nom STRING,NoCateg INTEGER,IdDefinitions INTEGER,type INTEGER,NoSys INTEGER,NbBranche INTEGER,NbBoucle Integer,Notes STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Arbre(NoIndic INTEGER, nbrBranche INTEGER, noBranche INTEGER, code INTEGER, arg1 INTEGER, arg2 INTEGER, arg3 INTEGER, valeur DOUBLE, type INTEGER, dateBranche INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Reseau(NoIndic INTEGER, nbrMaille INTEGER, NoMaille INTEGER, codeReseau INTEGER, codeBranche INTEGER, apDreseau INTEGER, apGreseau INTEGER)");
	adoQuery->ExecSQL();

	//----------Tendance------------------------------

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Alea_Categ (IdAleas INTEGER,IdAleaCateg INTEGER,Nom STRING,Notes MEMO)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Alea_Item (IdAleas INTEGER ,IdAleaCateg INTEGER,IdAleaItem INTEGER,IdDefItem INTEGER,IdDefinitions INTEGER,atelier Integer)");
	adoQuery->ExecSQL();

	//----------Cat_Atelier------------------------------

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_Categ (IdAteliers INTEGER ,IdAteCateg INTEGER,Nom STRING,DebAmor INTEGER,DurAmor INTEGER,NbPhase INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_CatPhase (IdPhase INTEGER,IdAteCateg INTEGER,IdAteliers INTEGER,Ph1 INTEGER,Ph2 INTEGER,Ph3 INTEGER,Ph4 INTEGER,Ph5 INTEGER,Ph6 INTEGER,Ph7 INTEGER,Ph8 INTEGER,Ph9 INTEGER,Ph10 INTEGER,Ph11 INTEGER,Ph12 INTEGER,Ph13 INTEGER,Ph14 INTEGER,Ph15 INTEGER,Ph16 INTEGER,Ph17 INTEGER,Ph18 INTEGER,Ph19 INTEGER,Ph20 INTEGER,Ph21 INTEGER,Ph22 INTEGER,Ph23 INTEGER,Ph24 INTEGER,Ph25 INTEGER,Ph26 INTEGER,Ph27 INTEGER,Ph28 INTEGER,Ph29 INTEGER,Ph30 INTEGER,Ph31 INTEGER,Ph32 INTEGER,Ph33 INTEGER,Ph34 INTEGER,Ph35 INTEGER,Ph36 INTEGER,Ph37 INTEGER,Ph38 INTEGER,Ph39 INTEGER,Ph40 INTEGER)");
	adoQuery->ExecSQL();

	//----------Atelier------------------------------

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_SousCateg (IdAteliers INTEGER ,IdAteCateg INTEGER ,IdAteSousCateg INTEGER ,Nom STRING,Derobe INTEGER,PImmoExiste INTEGER,PImmoFamExiste INTEGER,ValInvRepro DOUBLE,ValInvAutre DOUBLE, Notes MEMO)");
	adoQuery->ExecSQL();

	//----------Ate_Item------------------------------

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_Item (IdAteliers INTEGER,IdAteCateg INTEGER,IdAteSousCateg INTEGER,IdAteItem INTEGER,IdList INTEGER, C1IdDefinitions INTEGER,C1IdDefCateg INTEGER,C1IdDefItem INTEGER,C3IdDefinitions INTEGER,C3IdDefCateg INTEGER,C3IdDefItem INTEGER,Ph0 DOUBLE,Ph1 DOUBLE,Ph2 DOUBLE,Ph3 DOUBLE,Ph4 DOUBLE,Ph5 DOUBLE,Ph6 DOUBLE,Ph7 DOUBLE,Ph8 DOUBLE,Ph9 DOUBLE,Ph10 DOUBLE,Ph11 DOUBLE,Ph12 DOUBLE,Ph13 DOUBLE,Ph14 DOUBLE,Ph15 DOUBLE,Ph16 DOUBLE,Ph17 DOUBLE,Ph18 DOUBLE,Ph19 DOUBLE,Ph20 DOUBLE,Ph21 DOUBLE,Ph22 DOUBLE,Ph23 DOUBLE,Ph24 DOUBLE,Ph25 DOUBLE,Ph26 DOUBLE,Ph27 DOUBLE,Ph28 DOUBLE,Ph29 DOUBLE,Ph30 DOUBLE,Ph31 DOUBLE,Ph32 DOUBLE,Ph33 DOUBLE,Ph34 DOUBLE,Ph35 DOUBLE,Ph36 DOUBLE,Ph37 DOUBLE,Ph38 DOUBLE,Ph39 DOUBLE,Ph40 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_PiedHa (IdAteliers INTEGER,IdAteCateg INTEGER,IdAteSousCateg INTEGER,IdAteItem INTEGER,IdList INTEGER, Ph0 DOUBLE,Ph1 DOUBLE,Ph2 DOUBLE,Ph3 DOUBLE,Ph4 DOUBLE,Ph5 DOUBLE,Ph6 DOUBLE,Ph7 DOUBLE,Ph8 DOUBLE,Ph9 DOUBLE,Ph10 DOUBLE,Ph11 DOUBLE,Ph12 DOUBLE,Ph13 DOUBLE,Ph14 DOUBLE,Ph15 DOUBLE,Ph16 DOUBLE,Ph17 DOUBLE,Ph18 DOUBLE,Ph19 DOUBLE,Ph20 DOUBLE,Ph21 DOUBLE,Ph22 DOUBLE,Ph23 DOUBLE,Ph24 DOUBLE,Ph25 DOUBLE,Ph26 DOUBLE,Ph27 DOUBLE,Ph28 DOUBLE,Ph29 DOUBLE,Ph30 DOUBLE,Ph31 DOUBLE,Ph32 DOUBLE,Ph33 DOUBLE,Ph34 DOUBLE,Ph35 DOUBLE,Ph36 DOUBLE,Ph37 DOUBLE,Ph38 DOUBLE,Ph39 DOUBLE,Ph40 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_BesTrav (IdAteliers INTEGER,IdAteSousCateg INTEGER,IdDefCateg INTEGER,IdDefinitions INTEGER, NbPhase INTEGER,NbPeriodeCal INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_BesTrav_Item (IdAteliers INTEGER,IdAteSousCateg INTEGER,IdDefCateg INTEGER,IdDefinitions INTEGER, iX INTEGER,jX INTEGER, Valeur DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_Avance (IdAteliers INTEGER,IdAteSousCateg INTEGER,Item INTEGER,Debut INTEGER, Fin INTEGER,Valeur DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ate_ImmoProd (IdAteliers INTEGER,IdAteSousCateg INTEGER,Item INTEGER,IdList INTEGER,Ph0 DOUBLE,Ph1 DOUBLE,Ph2 DOUBLE,Ph3 DOUBLE,Ph4 DOUBLE,Ph5 DOUBLE,Ph6 DOUBLE,Ph7 DOUBLE,Ph8 DOUBLE,Ph9 DOUBLE,Ph10 DOUBLE,Ph11 DOUBLE,Ph12 DOUBLE,Ph13 DOUBLE,Ph14 DOUBLE,Ph15 DOUBLE,Ph16 DOUBLE,Ph17 DOUBLE,Ph18 DOUBLE,Ph19 DOUBLE,Ph20 DOUBLE,Ph21 DOUBLE,Ph22 DOUBLE,Ph23 DOUBLE,Ph24 DOUBLE,Ph25 DOUBLE,Ph26 DOUBLE,Ph27 DOUBLE,Ph28 DOUBLE,Ph29 DOUBLE,Ph30 DOUBLE,Ph31 DOUBLE,Ph32 DOUBLE,Ph33 DOUBLE,Ph34 DOUBLE,Ph35 DOUBLE,Ph36 DOUBLE,Ph37 DOUBLE,Ph38 DOUBLE,Ph39 DOUBLE,Ph40 DOUBLE)");
	adoQuery->ExecSQL();

	//----------Agriculteur------------------------------
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri (IdAgri INTEGER ,NoVariante INTEGER,Nom STRING,OrVar INTEGER,OrSerie INTEGER,NoSerie INTEGER,NbAnSim INTEGER,An_0 Integer,Notes MEMO)");
	adoQuery->ExecSQL();

	/*    adoQuery->SQL->Clear();
	 adoQuery->SQL->Add("CREATE TABLE AgriVariante (IdAgri STRING,IdVariante INTEGER)");
	 adoQuery->ExecSQL();

	 adoQuery->SQL->Clear();
	 adoQuery->SQL->Add("CREATE TABLE AgriSerie (IdAgri INTEGER,IdSerie INTEGER,OrdreChono INTEGER)");
	 adoQuery->ExecSQL();
	 */

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_DefSim (NoAgri INTEGER,An_0 INTEGER,NbAnSim INTEGER,MDeb INTEGER,AnCalage INTEGER,TypeAlea INTEGER,NoPrixProd INTEGER,NoPrixCharge INTEGER,NoQProd INTEGER,NoQCharge INTEGER,NoQExt INTEGER,TouSPrixProd INTEGER,TouSPrixCharge INTEGER,TouSQProd INTEGER,TouSQCharge INTEGER,TouSQExt INTEGER,Chaine STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Formule (NoAgri INTEGER ,NoFormule Integer,IdDefinitions INTEGER,IdList INTEGER,NoItem INTEGER, Origine INTEGER,An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_FormuleArbre(NoAgri INTEGER ,NoFormule Integer,IdDefinitions INTEGER, IdList INTEGER, NoItem INTEGER, NoAn INTEGER, nbrBranche INTEGER, noBranche INTEGER, code INTEGER, arg1 INTEGER, arg2 INTEGER, arg3 INTEGER, valeur DOUBLE, type INTEGER, dateBranche INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_FormuleReseau(NoAgri INTEGER ,NoFormule Integer,NoItem INTEGER,IdList INTEGER, NoAn INTEGER, nbrMaille INTEGER, NoMaille INTEGER, codeReseau INTEGER, codeBranche INTEGER, apDreseau INTEGER, apGreseau INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Critere (NoAgri INTEGER,NoCritere INTEGER, PRIMARY KEY (NoAgri, NoCritere) )");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Assol (NoAgri INTEGER,NoItem INTEGER,IdAteliers INTEGER,NoAteSousCateg INTEGER,An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Animaux (NoAgri INTEGER,NoItem INTEGER,IdAteliers INTEGER,NoAteSousCateg INTEGER,An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Perenne (NoAgri INTEGER,NoItem INTEGER,IdAteliers INTEGER,NoAteSousCateg INTEGER,AnPlant INTEGER,AnArr INTEGER,Surface DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Vivrier (NoAgri INTEGER,NoItem INTEGER,IdAteliers INTEGER,NoAteSousCateg INTEGER,AnPlant INTEGER,Duree INTEGER,Surface DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Immo (NoAgri INTEGER,NoItem INTEGER,Nom STRING,NoTva INTEGER,ValAchat DOUBLE,AAchat INTEGER,MAchat INTEGER,AVente INTEGER,MVente INTEGER,TypeAmor STRING,Duree INTEGER,ValVente DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_ImmoGlobal (NoAgri INTEGER,NoItem INTEGER,An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_FinanceGlobal (NoAgri INTEGER,NoItem INTEGER,An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_EmpCT (NoAgri INTEGER,NoItem INTEGER,Nom STRING,Montant DOUBLE,Taux DOUBLE,Type STRING,AReal INTEGER,MReal INTEGER,ARemb INTEGER,MRemb INTEGER,Pour STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_EmpLT (NoAgri INTEGER,NoItem INTEGER,Nom STRING,Montant DOUBLE,Duree INTEGER,Duree2 INTEGER,Taux DOUBLE,Taux2 DOUBLE,Type STRING,AReal INTEGER,MReal INTEGER,ARemb INTEGER,MRemb INTEGER,Pour STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Sub (NoAgri INTEGER,NoItem INTEGER,Nom STRING,Montant DOUBLE,AReal INTEGER,MReal INTEGER,Duree INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Plact (NoAgri INTEGER,NoItem INTEGER,Nom STRING,Montant DOUBLE,Taux DOUBLE,Type STRING,AReal INTEGER,MReal INTEGER,ATerme INTEGER,MTerme INTEGER,Pour INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Occc (NoAgri INTEGER,Année INTEGER,Ex INTEGER,Montant DOUBLE,Taux DOUBLE,Pcent INTEGER,Frais INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Petit (NoAgri INTEGER,NoItem INTEGER,Année INTEGER,ValAchat DOUBLE,NoTva INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_EnCoursCreance (NoAgri INTEGER,NoItem INTEGER,Valeur DOUBLE,MPaie INTEGER,APaie INTEGER, NoFamille INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_EnCoursDette (NoAgri INTEGER ,NoItem INTEGER,Valeur DOUBLE,MPaie INTEGER,APaie INTEGER, NoFamille INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_StockIni (NoAgri INTEGER,NoItem INTEGER,An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_PolStock (NoAgri INTEGER,NoItem INTEGER,Prix DOUBLE,IdSysUnit INTEGER,PcentStock DOUBLE,MaxiStockable INTEGER,PcentDecote DOUBLE)");
	adoQuery->ExecSQL();
	//--TP2012
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_Troupeau (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER,Reproducteur INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauEff (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An0 DOUBLE, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauVal (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An0 DOUBLE, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauVIM (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An0 DOUBLE, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauVente (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauAchat (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauValVente (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauValAchat (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauEffMax (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauNoAtelier (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauPVM (NoAgri INTEGER,NoCatBestiau INTEGER,NoItem INTEGER,NoAnimal INTEGER, An1 DOUBLE,An2 DOUBLE,An3 DOUBLE,An4 DOUBLE,An5 DOUBLE,An6 DOUBLE,An7 DOUBLE,An8 DOUBLE,An9 DOUBLE,An10 DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_TroupeauMvt (NoAgri INTEGER,NoCatBestiau INTEGER,Ligne INTEGER,DateMvt INTEGER, Type INTEGER, Effectif INTEGER, Info DOUBLE)");
	adoQuery->ExecSQL();

	//----------------------------------EtatSorties / Comparaisons
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE EtatSortie (IdDefinitions INTEGER, IdDefCateg INTEGER, Item INTEGER, NoElt INTEGER, NoFamille INTEGER, NoCateg INTEGER, NoItemElt INTEGER, Digits INTEGER, Couleur INTEGER, Titre STRING)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE SerieComp (IdDefinitions INTEGER, IdDefCateg INTEGER, Item INTEGER, NoElt INTEGER, NoFamille INTEGER, NoCateg INTEGER, NoItemElt INTEGER, Digits INTEGER, Couleur INTEGER, Titre STRING)");
	adoQuery->ExecSQL();

	//------------------------------------------------------------------------------
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ensemble (IdEnsemble INTEGER,Nom STRING,Notes MEMO)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Ens_Eff ( IdAgriEff INTEGER, NoAgri INTEGER, IdEnsemble INTEGER, Nom STRING,N_X_1 INTEGER,N_X_2 INTEGER,N_X_3 INTEGER,N_X_4 INTEGER,N_X_5 INTEGER,N_X_6 INTEGER,N_X_7 INTEGER,N_X_8 INTEGER,N_X_9 INTEGER,N_X_10 INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Projet (NoProjet COUNTER,NomFichier String,Auteur STRING,Pays STRING)");
	adoQuery->ExecSQL();

	//------------------------------------------------------------------------------
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Repart (IdRepart INTEGER, NomRepart String, IdDefinitions INTEGER, IdDefCateg INTEGER)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE RepartDetail (IdRepart INTEGER, DateRepart INTEGER, ValeurRepart DOUBLE)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"CREATE TABLE Agri_RepartItem (IdRepartItem INTEGER, NoAgri INTEGER, NoFamille INTEGER, Nox INTEGER, Nb INTEGER, NoRepartQ1 INTEGER, NoRepartV1 INTEGER, NoRepartQ2 INTEGER, NoRepartV2 INTEGER, NoRepartQ3 INTEGER, NoRepartV3 INTEGER,  NoRepartQ4 INTEGER, NoRepartV4 INTEGER,  NoRepartQ5 INTEGER, NoRepartV5 INTEGER, NoRepartQ6 INTEGER, NoRepartV6 INTEGER, NoRepartQ7 INTEGER, NoRepartV7 INTEGER, NoRepartQ8 INTEGER, NoRepartV8 INTEGER, NoRepartQ9 INTEGER, NoRepartV9 INTEGER, NoRepartQ10 INTEGER, NoRepartV10 INTEGER)");
	adoQuery->ExecSQL();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Création des clés primaires
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::CreationClePrimaire_EcrireAccess(TADOQuery *adoQuery) {

	EcrireRapport("Creation cles primaires");

	// Classes de bases
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE _Definitions ADD PRIMARY KEY (IdDefinitions);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE _Ateliers ADD PRIMARY KEY (IdAteliers);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE _Ate_ListItem ADD PRIMARY KEY (IdAteListItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE _Aleas ADD PRIMARY KEY (IdAleas);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE _Agri_ListValeur ADD PRIMARY KEY (IdAgriValeur);");
	adoQuery->ExecSQL();

	//--------------------------------------------------

	//Clés primaire Definitions

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE SystemeUnite ADD PRIMARY KEY (IdSysUnit);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE TVA ADD PRIMARY KEY (IdTva);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Categ ADD PRIMARY KEY (IdDefinitions,IdDefCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Bestiaux ADD PRIMARY KEY (IdBestiaux);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Indicateur ADD PRIMARY KEY (IdDefItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Def_Dico ADD PRIMARY KEY (IdDefDico);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Calendrier ADD PRIMARY KEY (IdPeriode, IdDefCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_EtatSortie ADD PRIMARY KEY (IdEtatSortie);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_SerieComp ADD PRIMARY KEY (IdEtatSortie);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Def_Critere ADD PRIMARY KEY (IdDefItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Conversion ADD PRIMARY KEY (IdConversion);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Item ADD PRIMARY KEY (IdDefinitions,IdDefItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Indicateur ADD PRIMARY KEY (NoIndic);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Arbre ADD PRIMARY KEY (NoIndic, NoBranche);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Reseau ADD PRIMARY KEY (NoIndic, NoMaille);");
	adoQuery->ExecSQL();

	//--------------------------------------
	// Création clés primaire atelier
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Categ ADD PRIMARY KEY (IdAteliers,IdAteCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_CatPhase ADD PRIMARY KEY (IdAteCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_SousCateg ADD PRIMARY KEY (IdAteliers,IdAteSousCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Item ADD PRIMARY KEY (IdAteliers,IdAteSousCateg,IdAteItem,IdList,C1IdDefinitions,C1IdDefItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_PiedHa ADD PRIMARY KEY (IdAteliers,IdAteSousCateg,IdAteItem,IdList);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_BesTrav ADD PRIMARY KEY (IdAteliers,IdAteSousCateg,IdDefCateg,IdDefinitions);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_BesTrav_Item ADD PRIMARY KEY (IdAteliers,IdAteSousCateg,IdDefCateg,idDefinitions,iX,jX);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Avance ADD PRIMARY KEY (IdAteliers,IdAteSousCateg,Item);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_ImmoProd ADD PRIMARY KEY (IdAteliers,IdAteSousCateg,Item,IdList);");
	adoQuery->ExecSQL();

	//--------------------------------------
	// Création clés primaires aléa

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Alea_Categ ADD PRIMARY KEY (IdAleas,IdAleaCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Alea_Item ADD PRIMARY KEY (IdAleas,IdAleaCateg,IdAleaItem);");
	adoQuery->ExecSQL();

	//---------------------------------------
	// Création clés primaires agriculteur

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Agri ADD PRIMARY KEY (IdAgri);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Assol ADD PRIMARY KEY (NoAgri,NoItem,NoAteSousCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Perenne ADD PRIMARY KEY (NoAgri,NoItem,NoAteSousCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Animaux ADD PRIMARY KEY (NoAgri,NoItem,NoAteSousCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Vivrier ADD PRIMARY KEY (NoAgri,NoItem,NoAteSousCateg);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Formule ADD PRIMARY KEY (NoAgri,IdDefinitions,IdList,NoItem,NoFormule);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FormuleArbre ADD PRIMARY KEY (NoAgri,IdDefinitions,IdList,NoItem,NoFormule,NoAn,noBranche);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FormuleReseau ADD PRIMARY KEY (NoAgri,IdList,NoItem,NoFormule,NoAn,NoMaille);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Ensemble ADD PRIMARY KEY (IdEnsemble);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Ens_Eff ADD PRIMARY KEY (IdAgriEff);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Agri_DefSim ADD PRIMARY KEY (NoAgri);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Immo ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_ImmoGlobal ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Petit ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EmpCT ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EmpLT ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Plact ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FinanceGlobal ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Agri_Sub ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Agri_Occc ADD PRIMARY KEY (NoAgri,Ex);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_StockIni ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_PolStock ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EnCoursDette ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EnCoursCreance ADD PRIMARY KEY (NoAgri,NoItem);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Troupeau ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauEff ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauVal ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauVente ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauAchat ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauValVente ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauValAchat ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauEffMax ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauNoAtelier ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauPVM ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauVIM ADD PRIMARY KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal);");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauMvt ADD PRIMARY KEY (NoAgri,NoCatBestiau,Ligne,DateMvt,Type);");
	adoQuery->ExecSQL();

	//----------------------------------EtatSorties / Comparaisons
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE EtatSortie ADD PRIMARY KEY (Item,NoElt)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE SerieComp ADD PRIMARY KEY (Item,NoElt)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add("ALTER TABLE Repart ADD PRIMARY KEY (IdRepart)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE RepartDetail ADD PRIMARY KEY (IdRepart, DateRepart)");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_RepartItem ADD PRIMARY KEY (IdRepartItem, NoAgri, NoFamille);");
	adoQuery->ExecSQL();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Création des clés étrangères
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::CreationCleEtrangere_EcrireAccess(TADOQuery *adoQuery) {
	EcrireRapport("Creation cles etrangeres");

	// Création des clés étrangères de définitions

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Categ ADD FOREIGN KEY (IdDefinitions) REFERENCES _Definitions(IdDefinitions) ON DELETE CASCADE ON UPDATE CASCADE ;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Item ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Item ADD FOREIGN KEY (IdSysUnit) REFERENCES SystemeUnite(IdSysUnit)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Item ADD FOREIGN KEY (IdTva) REFERENCES TVA(IdTva)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Bestiaux ADD FOREIGN KEY (IdTva) REFERENCES TVA(IdTva)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Bestiaux ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Dico ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Calendrier ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_EtatSortie ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_SerieComp ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Def_Critere ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Indicateur ADD FOREIGN KEY (IdDefinitions,noCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Arbre ADD FOREIGN KEY (NoIndic) REFERENCES Indicateur(NoIndic)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Reseau ADD FOREIGN KEY (NoIndic) REFERENCES Indicateur(NoIndic)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE EtatSortie ADD FOREIGN KEY (Item) REFERENCES Def_EtatSortie(IdEtatSortie)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE SerieComp ADD FOREIGN KEY (Item) REFERENCES Def_SerieComp(IdEtatSortie)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	// Création des clés étrangères d'atelier

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Categ ADD FOREIGN KEY (IdAteliers) REFERENCES _Ateliers(IdAteliers)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_SousCateg ADD FOREIGN KEY (IdAteliers,IdAteCateg) REFERENCES Ate_Categ(IdAteliers,IdAteCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Item ADD FOREIGN KEY (IdAteliers,IdAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Item ADD FOREIGN KEY (C1IdDefinitions,C1IdDefItem) REFERENCES Def_Item(IdDefinitions,IdDefItem)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Item ADD FOREIGN KEY (IdList) REFERENCES _Ate_ListItem(IdAteListItem)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_PiedHa ADD FOREIGN KEY (IdAteliers,IdAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_PiedHa ADD FOREIGN KEY (IdList) REFERENCES _Ate_ListItem(IdAteListItem)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_CatPhase ADD FOREIGN KEY (IdAteliers,IdAteCateg) REFERENCES Ate_Categ(IdAteliers,IdAteCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_BesTrav ADD FOREIGN KEY (IdAteliers,IdAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_BesTrav ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_BesTrav_Item ADD FOREIGN KEY (IdAteliers,IdAteSousCateg,IdDefCateg,IdDefinitions) REFERENCES Ate_BesTrav(IdAteliers,IdAteSousCateg,IdDefCateg,IdDefinitions)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_Avance ADD FOREIGN KEY (IdAteliers,IdAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ate_ImmoProd ADD FOREIGN KEY (IdAteliers,IdAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	// clés étrangère d'aléas

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Alea_Categ ADD FOREIGN KEY (IdAleas) REFERENCES _Aleas(IdAleas)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Alea_Item ADD FOREIGN KEY (IdAleas,IdAleaCateg) REFERENCES Alea_Categ(IdAleas,IdAleaCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Alea_Item ADD FOREIGN KEY (IdDefinitions,IdDefItem) REFERENCES Def_Item(IdDefinitions,IdDefItem)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	// Clés étrangère d'agriculteur

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri ADD FOREIGN KEY (OrVar) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri ADD FOREIGN KEY (OrSerie) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Assol ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Perenne ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Animaux ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Vivrier ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Formule ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Formule ADD FOREIGN KEY (IdDefinitions,NoItem) REFERENCES Def_Item(IdDefinitions,IdDefItem) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Formule ADD FOREIGN KEY (IdList) REFERENCES _Agri_ListValeur(IdAgriValeur)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FormuleArbre ADD FOREIGN KEY (IdDefinitions,NoItem) REFERENCES Def_Item(IdDefinitions,IdDefItem) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FormuleArbre ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FormuleReseau ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Critere ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_DefSim ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Immo ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Immo ADD FOREIGN KEY (NoTva) REFERENCES TVA(IdTva)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_ImmoGlobal ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Petit ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EmpCT ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Critere ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EmpLT ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Occc ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Sub ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Plact ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_FinanceGlobal ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_StockIni ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_PolStock ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EnCoursDette ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_EnCoursCreance ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Assol ADD FOREIGN KEY (IdAteliers,NoAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Perenne ADD FOREIGN KEY (IdAteliers,NoAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Animaux ADD FOREIGN KEY (IdAteliers,NoAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Vivrier ADD FOREIGN KEY (IdAteliers,NoAteSousCateg) REFERENCES Ate_SousCateg(IdAteliers,IdAteSousCateg)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Critere ADD FOREIGN KEY (NoCritere) REFERENCES Def_Critere(IdDefItem)ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	//--TP 2012 - todo : Cle etrangere
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Troupeau ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_Troupeau ADD FOREIGN KEY (NoAnimal) REFERENCES Def_Bestiaux(IdBestiaux) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauEff ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauVal ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauVente ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauAchat ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauValVente ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauValAchat ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauEffMax ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauNoAtelier ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauPVM ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauVIM ADD FOREIGN KEY (NoAgri,NoCatBestiau,NoItem,NoAnimal) REFERENCES Agri_Troupeau(NoAgri,NoCatBestiau,NoItem,NoAnimal) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_TroupeauMvt ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ens_Eff ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Ens_Eff ADD FOREIGN KEY (IdEnsemble) REFERENCES Ensemble(IdEnsemble) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Repart ADD FOREIGN KEY (IdDefinitions,IdDefCateg) REFERENCES Def_Categ(IdDefinitions,IdDefCateg) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE RepartDetail ADD FOREIGN KEY (IdRepart) REFERENCES Repart(IdRepart) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE Agri_RepartItem ADD FOREIGN KEY (NoAgri) REFERENCES Agri(IdAgri) ON DELETE CASCADE ON UPDATE CASCADE;");
	adoQuery->ExecSQL();

	adoQuery->SQL->Clear();

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Insertion des données définitions et catégories
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::InsertDonneesDefCat_EcrireAccess(TADOQuery *adoQuery,
		TADOTable *adoTable, TADOTable *adoTable1) {
	EcrireRapport("Debut Insertion");

	EcrireRapport("EcrireDefinitions");
	EcrireDefinitions(adoTable, "_Definitions");
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAleas");
	EcrireAleas(adoTable, "_Aleas");
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAteliers");
	EcrireAteliers(adoTable, "_Ateliers");
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAteListItem");
	EcrireAteListItem(adoTable, "_Ate_ListItem");
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriValeur");
	EcrireAgriValeur(adoTable, "_Agri_ListValeur");
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireSystemeUnite");
	EcrireSystemeUnite(adoTable, "SystemeUnite", V_SystemeUnite);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireTva");
	EcrireTva(adoTable, "TVA", V_Tva);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireCategorieV_CatProduit");
	EcrireCategorie(adoTable, "Def_Categ", V_CatProduit, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatCharge");
	EcrireCategorie(adoTable, "Def_Categ", V_CatCharge, 2);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatExternalite");
	EcrireCategorie(adoTable, "Def_Categ", V_CatExternalite, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatBestiaux");
	EcrireCategorie(adoTable, "Def_Categ", V_CatBestiaux, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatChStruct");
	EcrireCategorie(adoTable, "Def_Categ", V_CatChStruct, 6);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatDepDiv");
	EcrireCategorie(adoTable, "Def_Categ", V_CatDepDiv, 8);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatDepFam");
	EcrireCategorie(adoTable, "Def_Categ", V_CatDepFam, 10);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatRecDiv");
	EcrireCategorie(adoTable, "Def_Categ", V_CatRecDiv, 7);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatRecFam");
	EcrireCategorie(adoTable, "Def_Categ", V_CatRecFam, 9);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatTypeZone");
	EcrireCategorie(adoTable, "Def_Categ", V_CatTypeZone, 13);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatVar");
	EcrireCategorie(adoTable, "Def_Categ", V_CatVar, 11);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireCategorieV_CatEtatSortie");
	EcrireCategorie(adoTable, "Def_Categ", V_CatEtatSortie, 14);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatSerieComp");
	EcrireCategorie(adoTable, "Def_Categ", V_CatSerieComp, 15);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatIndic");
	EcrireCategorie(adoTable, "Def_Categ", V_CatIndic, 16);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatDico");
	EcrireCategorie(adoTable, "Def_Categ", V_CatDico, 12);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireCategorieV_CatRepart");
	EcrireCategorie(adoTable, "Def_Categ", V_CatRepart, 17);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireCatCalendrier");
	EcrireCatCalendrier(adoTable, "Def_Categ", V_Calendrier, 5);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_ProChaV_Produit");
	EcrireDef_ProCha(adoTable, "Def_Item", V_Produit, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireDef_ProChaV_Charge");
	EcrireDef_ProCha(adoTable, "Def_Item", V_Charge, 2);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_ExtVarV_Externalite");
	EcrireDef_ExtVar(adoTable, "Def_Item", V_Externalite, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireDef_ExtVarV_Variable");
	EcrireDef_ExtVar(adoTable, "Def_Item", V_Variable, 11);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_ChStructRecDepV_ChStruct");
	EcrireDef_ChStructRecDep(adoTable, "Def_Item", V_ChStruct, 6);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireDef_ChStructRecDepV_RecDiv");
	EcrireDef_ChStructRecDep(adoTable, "Def_Item", V_RecDiv, 7);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireDef_ChStructRecDepV_DepDiv");
	EcrireDef_ChStructRecDep(adoTable, "Def_Item", V_DepDiv, 8);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireDef_ChStructRecDepV_RecFam");
	EcrireDef_ChStructRecDep(adoTable, "Def_Item", V_RecFam, 9);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireDef_ChStructRecDepV_DepFam");
	EcrireDef_ChStructRecDep(adoTable, "Def_Item", V_DepFam, 10);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_Critere");
	EcrireDef_Critere(adoTable, "Def_Critere", V_TypeZone);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_Dico");
	EcrireDef_Dico(adoTable, "Def_Dico", V_Dico);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_EtatSortieV_EtatSortie");
	EcrireDef_EtatSortie(adoQuery, adoTable, "Def_EtatSortie", V_EtatSortie,
			adoTable1);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireDef_EtatSortieV_SerieComp");
	EcrireDef_EtatSortie(adoQuery, adoTable, "Def_SerieComp", V_SerieComp,
			adoTable1);
	ProgressBar->StepBy(1);

	ProgressBar->StepBy(1);
	EcrireRapport("Def_Calendrier");
	//EcrireDef_Periode(adoTable,"Def_Calendrier",V_Calendrier);
	EcrireDef_Periode(adoQuery, "Def_Calendrier", V_Calendrier);
	ProgressBar->StepBy(1);
	EcrireRapport("Def_Bestiaux");
	EcrireDef_Bestiaux(adoTable, "Def_Bestiaux", V_Bestiaux);
	ProgressBar->StepBy(1);

	//Tendance
	EcrireRapport("Alea_CategV_TendPrixProd");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_TendPrixProd, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_TendPrixCharge");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_TendPrixCharge, 2);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_ScenPrixProd");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_ScenPrixProd, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_ScenPrixCharge");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_ScenPrixCharge, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_TendQProd");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_TendQProd, 5);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_TendQCharge");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_TendQCharge, 6);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_ScenQProd");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_ScenQProd, 7);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_ScenQCharge");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_ScenQCharge, 8);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_TendQExt");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_TendQExt, 9);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_CategV_ScenQExt");
	EcrireAleaCateg(adoTable, "Alea_Categ", V_ScenQExt, 10);
	ProgressBar->StepBy(1);

	EcrireRapport("Alea_ItemV_TendPrixProd");
	EcrireTendance(adoTable, "Alea_Item", V_TendPrixProd, PRIX, adoQuery, 1, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_TendPrixCharge");
	EcrireTendance(adoTable, "Alea_Item", V_TendPrixCharge, PRIX, adoQuery, 2,
			2);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_ScenPrixProd");
	EcrireTendance(adoTable, "Alea_Item", V_ScenPrixProd, PRIX, adoQuery, 3, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_ScenPrixCharge");
	EcrireTendance(adoTable, "Alea_Item", V_ScenPrixCharge, PRIX, adoQuery, 4,
			2);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_TendQProd");
	EcrireTendance(adoTable, "Alea_Item", V_TendQProd, QUANTITE, adoQuery, 5,
			1);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_TendQCharge");
	EcrireTendance(adoTable, "Alea_Item", V_TendQCharge, QUANTITE, adoQuery, 6,
			2);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_ScenQProd");
	EcrireTendance(adoTable, "Alea_Item", V_ScenQProd, QUANTITE, adoQuery, 7,
			1);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_ScenQCharge");
	EcrireTendance(adoTable, "Alea_Item", V_ScenQCharge, QUANTITE, adoQuery, 8,
			2);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_TendQExt");
	EcrireTendance(adoTable, "Alea_Item", V_TendQExt, QUANTITE, adoQuery, 9, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("Alea_ItemV_ScenQExt");
	EcrireTendance(adoTable, "Alea_Item", V_ScenQExt, QUANTITE, adoQuery, 10,
			3);
	ProgressBar->StepBy(1);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Insertion des données définitions et catégories
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::InsertDonneesAutres_EcrireAccess(TADOQuery *adoQuery,
		TADOTable *adoTable, TADOTable *adoTable1) {

	/*
	 //creer AgriClasstFrm->ChLBCatTypeZone
	 // a mettre ailleurs
	 CL_Categorie *categorie;
	 AgriClasstFrm->ChLBCatTypeZone->Clear();
	 for(int n=0;n<V_CatTypeZone->Nbelt;n++)
	 {
	 categorie=V_CatTypeZone->Vecteur[n];
	 categorie->Flag=true;
	 AgriClasstFrm->ChLBCatTypeZone->Items->AddObject(categorie->Nom,(TObject*)categorie);
	 }
	 */
	//criteres Non Retenus
	EcrireRapport("EcrireAte_CatAtelierV_CatCulture");
	EcrireAte_CatAtelier(adoTable, "Ate_Categ", V_CatCulture, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_CatAtelierV_CatAnimaux");
	EcrireAte_CatAtelier(adoTable, "Ate_Categ", V_CatAnimaux, 2);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_CatPerenne");
	EcrireAte_CatPerenne(adoTable, "Ate_Categ", V_Espece, adoQuery, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_CatAtelierV_CatVivrier");
	EcrireAte_CatAtelier(adoTable, "Ate_Categ", V_CatVivrier, 4);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_AtelierAte_SousCategCULTURE");
	EcrireAte_Atelier(adoTable, "Ate_SousCateg", CULTURE, V_Culture, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_AtelierAte_SousCategANIMAUX");
	EcrireAte_Atelier(adoTable, "Ate_SousCateg", ANIMAUX, V_Animaux, 2);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_AtelierAte_SousCategV_Perenne");
	EcrireAte_Atelier(adoTable, "Ate_SousCateg", V_Perenne);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_AtelierAte_SousCategVIVRIER");
	EcrireAte_Atelier(adoTable, "Ate_SousCateg", VIVRIER, V_Vivrier, 4);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_ItemV_Culture1");
	EcrireAte_Item(adoTable, "Ate_Item", V_Culture, 1, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Culture2");
	EcrireAte_Item(adoTable, "Ate_Item", V_Culture, 2, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Culture3");
	EcrireAte_Item(adoTable, "Ate_Item", V_Culture, 3, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Culture4");
	EcrireAte_Item(adoTable, "Ate_Item", V_Culture, 4, 1);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_ItemItemPiedHaV_Culture9");
	EcrireAte_PiedHa(adoTable, "Ate_PiedHa", V_Culture, 9, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Culture10");
	EcrireAte_Item(adoTable, "Ate_Item", V_Culture, 10, 1);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Culture11");
	EcrireAte_Item(adoTable, "Ate_Item", V_Culture, 11, 1);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_ItemV_Animaux1");
	EcrireAte_Item(adoTable, "Ate_Item", V_Animaux, 1, 2);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Animaux2");
	EcrireAte_Item(adoTable, "Ate_Item", V_Animaux, 2, 2);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Animaux3");
	EcrireAte_Item(adoTable, "Ate_Item", V_Animaux, 3, 2);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Animaux4");
	EcrireAte_Item(adoTable, "Ate_Item", V_Animaux, 4, 2);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_ItemPer1");
	EcrireAte_ItemPer(adoTable, "Ate_Item", V_Perenne, 1, adoQuery, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemPer2");
	EcrireAte_ItemPer(adoTable, "Ate_Item", V_Perenne, 2, adoQuery, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemPer3");
	EcrireAte_ItemPer(adoTable, "Ate_Item", V_Perenne, 3, adoQuery, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemPer4");
	EcrireAte_ItemPer(adoTable, "Ate_Item", V_Perenne, 4, adoQuery, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemPiedHaPer9");
	EcrireAte_PiedHaPer(adoTable, "Ate_PiedHa", V_Perenne, 9, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemPer10");
	EcrireAte_ItemPer(adoTable, "Ate_Item", V_Perenne, 10, adoQuery, 3);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemPer11");
	EcrireAte_ItemPer(adoTable, "Ate_Item", V_Perenne, 11, adoQuery, 3);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAte_ItemV_Vivrier1");
	EcrireAte_Item(adoTable, "Ate_Item", V_Vivrier, 1, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Vivrier2");
	EcrireAte_Item(adoTable, "Ate_Item", V_Vivrier, 2, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Vivrier3");
	EcrireAte_Item(adoTable, "Ate_Item", V_Vivrier, 3, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Vivrier4");
	EcrireAte_Item(adoTable, "Ate_Item", V_Vivrier, 4, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemItemPiedHaV_Vivrier9");
	EcrireAte_PiedHa(adoTable, "Ate_PiedHa", V_Vivrier, 9, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Vivrier10");
	EcrireAte_Item(adoTable, "Ate_Item", V_Vivrier, 10, 4);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAte_ItemV_Vivrier11");
	EcrireAte_Item(adoTable, "Ate_Item", V_Vivrier, 11, 4);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrirePhase");
	EcrirePhase(adoTable, "Ate_CatPhase", V_Espece);
	ProgressBar->StepBy(1);

	AdresseChFVol(V_Culture);
	AdresseChFVol(V_Animaux);
	AdresseChFVol(V_Perenne);
	AdresseChFVol(V_Vivrier);
	//Repart
	EcrireRapport("EcrireRepart");
	EcrireRepart(adoTable, "Repart", adoTable1, "RepartDetail", V_Repart);
	ProgressBar->StepBy(1);

	//--Les BesTrav
	EcrireRapport("EcrireAte_BesTrav1");
	EcrireAte_BesTrav(adoQuery, adoTable, adoTable1, "Ate_BesTrav",
			"Ate_BesTrav_Item", V_Culture, 1);
	EcrireRapport("EcrireAte_BesTrav2");
	EcrireAte_BesTrav(adoQuery, adoTable, adoTable1, "Ate_BesTrav",
			"Ate_BesTrav_Item", V_Animaux, 2);
	EcrireRapport("EcrireAte_BesTrav3");
	EcrireAte_BesTrav(adoQuery, adoTable, adoTable1, "Ate_BesTrav",
			"Ate_BesTrav_Item", V_Perenne, 3);
	EcrireRapport("EcrireAte_BesTrav4");
	EcrireAte_BesTrav(adoQuery, adoTable, adoTable1, "Ate_BesTrav",
			"Ate_BesTrav_Item", V_Vivrier, 4);

	//--Les Avances
	EcrireRapport("EcrireAte_Avance 1 3 et 4");
	EcrireAte_Avance(adoTable, "Ate_Avance", V_Culture, 1);
	EcrireAte_Avance(adoTable, "Ate_Avance", V_Perenne, 3);
	EcrireAte_Avance(adoTable, "Ate_Avance", V_Vivrier, 4);
	//--Les Immos Entreprise et familiale
	EcrireRapport("EcrireAte_Immo 1 3 et 4");
	EcrireAte_Immo(adoTable, "Ate_ImmoProd", V_Culture, 1);
	EcrireAte_Immo(adoTable, "Ate_ImmoProd", V_Perenne, 3);
	EcrireAte_Immo(adoTable, "Ate_ImmoProd", V_Vivrier, 4);

	//Traité dans EcrireDef_EtatSortie
	//EcrireEtatSortie(adoTable,"EtatSortie",V_EtatSortie);
	//ProgressBar->StepBy(1);

	// Agriculteur
	EcrireRapport("EcrireAgri");
	EcrireAgri(adoTable, "Agri", V_Agriculteur);
	EcrireRapport("EcrireAgri_DefSim");
	EcrireAgri_DefSim(adoTable, "Agri_DefSim", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgri_Critere");
	EcrireAgri_Critere(adoTable, "Agri_Critere", V_Agriculteur);
	ProgressBar->StepBy(1);

	/*   EcrireAgriVariante(adoTable,"AgriVariante",V_Agriculteur);
	 ProgressBar->StepBy(1);

	 EcrireAgriSerie(adoTable,"AgriSerie",V_Agriculteur);
	 ProgressBar->StepBy(1);
	 */

	EcrireRapport("EcrireAgri_Critere");
	EcrireAgri_Critere(adoTable, "Agri_Critere", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgri_Assol");
	EcrireAgriAssol(adoTable, "Agri_Assol", CULTURE, V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgri_Animaux");
	EcrireAgriAssol(adoTable, "Agri_Animaux", ANIMAUX, V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgri_Perenne");
	EcrireAgriPerenne(adoTable, "Agri_Perenne", PERENNE, V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgri_Vivrier");
	EcrireAgriPerenne(adoTable, "Agri_Vivrier", VIVRIER, V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriFormulePRODUIT");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", PRODUIT,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleCHARGE");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", CHARGE,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleCHSTRUCT");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", CHSTRUCT,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleRECDIV");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", RECDIV,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleDEPDIV");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", DEPDIV,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleRECFAM");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", RECFAM,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleDEPFAM");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", DEPFAM,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleEXTPOS");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", EXTPOS,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriFormuleEXTNEG");
	EcrireAgriFormule(adoTable, adoTable1, "Agri_Formule", EXTNEG,
			V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriVariable");
	EcrireAgriVariable(adoTable, "Agri_Formule", V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriImmo");
	EcrireAgriImmo(adoTable, "Agri_Immo", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriXXXGlobalIMMO");
	EcrireAgriXXXGlobal(adoTable, "Agri_ImmoGlobal", IMMO, V_Agriculteur,
			adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriXXXGlobalFINANCE");
	EcrireAgriXXXGlobal(adoTable, "Agri_FinanceGlobal", FINANCE, V_Agriculteur,
			adoQuery);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriEmpCT");
	EcrireAgriEmpCT(adoTable, "Agri_EmpCT", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriEmpLT");
	EcrireAgriEmpLT(adoTable, "Agri_EmpLT", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriSub");
	EcrireAgriSub(adoTable, "Agri_Sub", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriPlact");
	EcrireAgriPlact(adoTable, "Agri_Plact", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriOccc");
	EcrireAgriOccc(adoTable, "Agri_Occc", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriPetit");
	EcrireAgriPetit(adoTable, "Agri_Petit", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriEnCoursCREANCE");
	EcrireAgriEnCours(adoTable, "Agri_EnCoursCreance", V_Agriculteur, CREANCE);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriEnCoursDETTE");
	EcrireAgriEnCours(adoTable, "Agri_EnCoursDette", V_Agriculteur, DETTE);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireAgriStockIni");
	EcrireAgriStockIni(adoTable, "Agri_StockIni", V_Agriculteur, adoQuery);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireAgriPolStock");
	EcrireAgriPolStock(adoTable, "Agri_PolStock", V_Agriculteur);
	ProgressBar->StepBy(1);
	//--TP 2012 -Gestion Agri_Troupeau et Agri_TroupeauMvt

	EcrireRapport("Agri_Troupeau");
	EcrireAgriTroupeau(adoTable, "Agri_Troupeau", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauEff");
	EcrireAgriTroupeauEff(adoTable, "Agri_TroupeauEff", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauVal");
	EcrireAgriTroupeauVal(adoTable, "Agri_TroupeauVal", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauVente");
	EcrireAgriTroupeauVente(adoTable, "Agri_TroupeauVente", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauAchat");
	EcrireAgriTroupeauAchat(adoTable, "Agri_TroupeauAchat", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauValVente");
	EcrireAgriTroupeauValVente(adoTable, "Agri_TroupeauValVente",
			V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauValAchat");
	EcrireAgriTroupeauValAchat(adoTable, "Agri_TroupeauValAchat",
			V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("Agri_TroupeauEffMax");
	EcrireAgriTroupeauEffMax(adoTable, "Agri_TroupeauEffMax", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauNoAtelier");
	EcrireAgriTroupeauNoAtelier(adoTable, "Agri_TroupeauNoAtelier",
			V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauPVM");
	EcrireAgriTroupeauPVM(adoTable, "Agri_TroupeauPVM", V_Agriculteur);
	ProgressBar->StepBy(1);
	EcrireRapport("Agri_TroupeauVIM");
	EcrireAgriTroupeauVIM(adoTable, "Agri_TroupeauVIM", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("Agri_TroupeauMvt");
	EcrireAgriTroupeauMvt(adoTable, "Agri_TroupeauMvt", V_Agriculteur);
	ProgressBar->StepBy(1);

	EcrireRapport("Agri_RepartItem");
	EcrireAgri_RepartItem(adoTable, "Agri_RepartItem", V_Agriculteur);
	ProgressBar->StepBy(1);

	//--
	EcrireRapport("EcrireEnsemble");
	EcrireEnsemble(adoTable, "Ensemble", V_Ensemble);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireEns_Eff");
	EcrireEns_Eff(adoTable, "Ens_Eff", V_Ensemble);
	ProgressBar->StepBy(1);
	EcrireRapport("EcrireConversion");
	EcrireConversion(adoTable, "Def_Conversion", V_Conversion);
	ProgressBar->StepBy(1);

	EcrireRapport("EcrireIndicateur");
	EcrireIndicateur(adoTable, adoQuery, "Indicateur", V_Indicateur);
	ProgressBar->StepBy(1);

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::MajTable(TADOTable *adoTable, AnsiString nomTable) {
	adoTable->Active = false;
	adoTable->TableName = nomTable;
	adoTable->Active = true;
	adoTable->Open();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------- Méthodes de bases d'insertion des donées --------------------------
//------- par Objets.                              --------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-- Trois grandes familles de méthodes:                                    --
//--                                                                       --
//--- 1/ Exploite composant TADOTable:                                     --
//--    L'objet TADOTable est un dataSet connecté à une table via la       --
//--    MajTable(adoTable,nomTable).                                       --
//--    Il manipule donc la table dans sa totalité.                        --
//--            ->Append() pour ajout d'un enregistrement                  --
//--            ->Post() pour faire un update de la table complète         --
//--                                                                       --
//--    /!\ - Vérifier de ne pas réaliser des update trop fréquents        --
//--          car peut être lent.                                           --
//--                                                                       --
//--                                                                       --
//--- 1/ Exploite composant TADOQuery:                                     --
//--    L'objet TADOQuery est un composant connecté à la base de donnée    --
//--    via sa proprieté ->ConnectionString.                               --
//--    Il permet d'éxécuter une requête (ou serie de requêtes)            --
//--            ->SQL->Add(<requete>) pour ajout d'une requête             --
//--            ->ExecSQL() pour lancer l'éxécution des requêtes           --
//--                                                                       --
//--    /!\ - De façon générale préférer cette solution                    --
//--                                                                       --
//--                                                                       --
//--- 1/ Exploite composant TADOTable et TADOQuery:                        --
//--     Ces méthodes mixtes sont par exemple utilisées pour inserer       --
//--     des données dans des tables "Mères/Filles".                       --
//--                                                                       --
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAleas(TADOTable *adoTable, AnsiString nomTable) {
	MajTable(adoTable, nomTable);

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 1;
	adoTable->FieldValues["NomAlea"] = "Prix Prod Tend";
	adoTable->FieldValues["NameHazard"] = "Price Output Tend";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 2;
	adoTable->FieldValues["NomAlea"] = "Prix Charge Tend";
	adoTable->FieldValues["NameHazard"] = "Price Input Tend";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 3;
	adoTable->FieldValues["NomAlea"] = "Prix Prod Scen";
	adoTable->FieldValues["NameHazard"] = "Price Output Scen";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 4;
	adoTable->FieldValues["NomAlea"] = "Prix Charge Scen";
	adoTable->FieldValues["NameHazard"] = "Price Input Scen";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 5;
	adoTable->FieldValues["NomAlea"] = "Qte Prod Tend";
	adoTable->FieldValues["NameHazard"] = "Qty Output Tend";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 6;
	adoTable->FieldValues["NomAlea"] = "Qte Charge Tend";
	adoTable->FieldValues["NameHazard"] = "Qty Input Tend";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 7;
	adoTable->FieldValues["NomAlea"] = "Qte Prod Scen";
	adoTable->FieldValues["NameHazard"] = "Qty Output Scen";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 8;
	adoTable->FieldValues["NomAlea"] = "Qte Charge Scen";
	adoTable->FieldValues["NameHazard"] = "Qty Input Scen";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 9;
	adoTable->FieldValues["NomAlea"] = "Qte Ext Tend";
	adoTable->FieldValues["NameHazard"] = "Qty Ext Tend";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAleas"] = 10;
	adoTable->FieldValues["NomAlea"] = "Qte Ext Scen";
	adoTable->FieldValues["NameHazard"] = "Qty Ext Scen";
	adoTable->Post();

	ProgressBar1->StepIt();

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAteliers(TADOTable *adoTable,
		AnsiString nomTable) {
	MajTable(adoTable, nomTable);

	adoTable->Append();
	adoTable->FieldValues["IdAteliers"] = 1;
	adoTable->FieldValues["NomAte"] = "Culture";
	adoTable->FieldValues["NameAte"] = "Annual Crop";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteliers"] = 2;
	adoTable->FieldValues["NomAte"] = "Animaux";
	adoTable->FieldValues["NameAte"] = "Animals";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteliers"] = 3;
	adoTable->FieldValues["NomAte"] = "Perennes";
	adoTable->FieldValues["NameAte"] = "Tree_Crops";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteliers"] = 4;
	adoTable->FieldValues["NomAte"] = "Pluriannuelles";
	adoTable->FieldValues["NameAte"] = "Perennials";
	adoTable->Post();

	ProgressBar1->StepIt();

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAteListItem(TADOTable *adoTable,
		AnsiString nomTable) {
	MajTable(adoTable, nomTable);

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 1;
	adoTable->FieldValues["NomAteListItem"] = "Produit";
	adoTable->FieldValues["NameAteListItem"] = "Outputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 2;
	adoTable->FieldValues["NomAteListItem"] = "Charge";
	adoTable->FieldValues["NameAteListItem"] = "Inputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 3;
	adoTable->FieldValues["NomAteListItem"] = "ChargeVolume";
	adoTable->FieldValues["NameAteListItem"] = "Input_Volume";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 4;
	adoTable->FieldValues["NomAteListItem"] = "Externalite";
	adoTable->FieldValues["NameAteListItem"] = "Externality";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 5;
	adoTable->FieldValues["NomAteListItem"] = "Avance";
	adoTable->FieldValues["NameAteListItem"] = "Advance";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 6;
	adoTable->FieldValues["NomAteListItem"] = "Immo_Ent";
	adoTable->FieldValues["NameAteListItem"] = "Fix_Ass_Farm";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 7;
	adoTable->FieldValues["NomAteListItem"] = "Immo_Fam";
	adoTable->FieldValues["NameAteListItem"] = "Fix_Ass_Fam";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 8;
	adoTable->FieldValues["NomAteListItem"] = "Travail";
	adoTable->FieldValues["NameAteListItem"] = "Labour";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 9;
	adoTable->FieldValues["NomAteListItem"] = "Pied_Ha";
	adoTable->FieldValues["NameAteListItem"] = "Tree_ha";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 10;
	adoTable->FieldValues["NomAteListItem"] = "Prod_Pied";
	adoTable->FieldValues["NameAteListItem"] = "Output_Tree";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAteListItem"] = 11;
	adoTable->FieldValues["NomAteListItem"] = "Ch_Pied";
	adoTable->FieldValues["NameAteListItem"] = "Input_Tree";
	adoTable->Post();

	ProgressBar1->StepIt();

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDefinitions(TADOTable *adoTable,
		AnsiString nomTable) {
	MajTable(adoTable, nomTable);

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 1;
	adoTable->FieldValues["NomCat"] = "Produits";
	adoTable->FieldValues["NameCat"] = "Outputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 2;
	adoTable->FieldValues["NomCat"] = "Charges";
	adoTable->FieldValues["NameCat"] = "Inputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 3;
	adoTable->FieldValues["NomCat"] = "Externalites";
	adoTable->FieldValues["NameCat"] = "Externalities";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 4;
	adoTable->FieldValues["NomCat"] = "Bestiaux";
	adoTable->FieldValues["NameCat"] = "Animals";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 5;
	adoTable->FieldValues["NomCat"] = "Calendriers";
	adoTable->FieldValues["NameCat"] = "Calendars";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 6;
	adoTable->FieldValues["NomCat"] = "ChargesStruct";
	adoTable->FieldValues["NameCat"] = "Fixed_Assets";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 7;
	adoTable->FieldValues["NomCat"] = "Rec_Div";
	adoTable->FieldValues["NameCat"] = "Misc_Outputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 8;
	adoTable->FieldValues["NomCat"] = "Dep_Div";
	adoTable->FieldValues["NameCat"] = "Misc_Inputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 9;
	adoTable->FieldValues["NomCat"] = "Rec_Fam";
	adoTable->FieldValues["NameCat"] = "Fam_Outputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 10;
	adoTable->FieldValues["NomCat"] = "Dep_Fam";
	adoTable->FieldValues["NameCat"] = "Fam_Inputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 11;
	adoTable->FieldValues["NomCat"] = "Variables";
	adoTable->FieldValues["NameCat"] = "Variables";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 12;
	adoTable->FieldValues["NomCat"] = "Dico";
	adoTable->FieldValues["NameCat"] = "Dictionary";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 13;
	adoTable->FieldValues["NomCat"] = "Classification";
	adoTable->FieldValues["NameCat"] = "Classification";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 14;
	adoTable->FieldValues["NomCat"] = "EtatSortie";
	adoTable->FieldValues["NameCat"] = "Custom Form";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 15;
	adoTable->FieldValues["NomCat"] = "SerieComp";
	adoTable->FieldValues["NameCat"] = "ComparForm";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 16;
	adoTable->FieldValues["NomCat"] = "Indicat";
	adoTable->FieldValues["NameCat"] = "Indicator";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 17;
	adoTable->FieldValues["NomCat"] = "Repart";
	adoTable->FieldValues["NameCat"] = "Repart";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdDefinitions"] = 18;
	adoTable->FieldValues["NomCat"] = "Conversion";
	adoTable->FieldValues["NameCat"] = "Conversion";
	adoTable->Post();

	ProgressBar1->StepIt();

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriValeur(TADOTable *adoTable,
		AnsiString nomTable) {
	MajTable(adoTable, nomTable);

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 1;
	adoTable->FieldValues["NomAgriValeur"] = "Produits";
	adoTable->FieldValues["NameAgriVal"] = "Outputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 2;
	adoTable->FieldValues["NomAgriValeur"] = "Charges";
	adoTable->FieldValues["NameAgriVal"] = "Inputs";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 3;
	adoTable->FieldValues["NomAgriValeur"] = "ChStruct";
	adoTable->FieldValues["NameAgriVal"] = "Fixed_Ass";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 4;
	adoTable->FieldValues["NomAgriValeur"] = "RecDiv";
	adoTable->FieldValues["NameAgriVal"] = "Misc_Rev";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 5;
	adoTable->FieldValues["NomAgriValeur"] = "DepDiv";
	adoTable->FieldValues["NameAgriVal"] = "Misc_Exp";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 6;
	adoTable->FieldValues["NomAgriValeur"] = "RecFam";
	adoTable->FieldValues["NameAgriVal"] = "Fam_Rev";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 7;
	adoTable->FieldValues["NomAgriValeur"] = "DepFam";
	adoTable->FieldValues["NameAgriVal"] = "Fam_Exp";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 8;
	adoTable->FieldValues["NomAgriValeur"] = "ExtPos";
	adoTable->FieldValues["NameAgriVal"] = "ExtPos";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 9;
	adoTable->FieldValues["NomAgriValeur"] = "ExtNeg";
	adoTable->FieldValues["NameAgriVal"] = "ExtNeg";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 10;
	adoTable->FieldValues["NomAgriValeur"] = "Variable";
	adoTable->FieldValues["NameAgriVal"] = "Variable";
	//adoTable->Post();

	adoTable->Append();
	adoTable->FieldValues["IdAgriValeur"] = 11;
	adoTable->FieldValues["NomAgriValeur"] = "StockIni";
	adoTable->FieldValues["NameAgriVal"] = "StockIni";
	adoTable->Post();

	ProgressBar1->StepIt();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireSystemeUnite(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_SystemeUnite> *vecteur) {
	int n;
	CL_SystemeUnite *sysUnit;
	char coche;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vecteur->Nbelt; n++) {

		try {
			adoTable->Append();
		} catch (Exception &e) {
		}
		sysUnit = vecteur->Vecteur[n];

		adoTable->FieldValues["IdSysUnit"] = sysUnit->No;
		adoTable->FieldValues["UAte"] = sysUnit->UUt;
		adoTable->FieldValues["UEnt"] = sysUnit->UTrans;
		adoTable->FieldValues["UGlobal"] = sysUnit->UGlobal;
		adoTable->FieldValues["Ratio21"] = sysUnit->Ratio;
		adoTable->FieldValues["Ratio32"] = sysUnit->RatioG;
		if (SysMonnaie->No == sysUnit->No) {
			adoTable->FieldValues["Monnaie"] = true;
		} else {
			adoTable->FieldValues["Monnaie"] = false;
		}

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireTva(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Tva> *vecteur) {
	int n;
	CL_Tva *tva;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vecteur->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		tva = vecteur->Vecteur[n];

		adoTable->FieldValues["IdTva"] = tva->No;
		adoTable->FieldValues["Nom"] = tva->Nom;
		adoTable->FieldValues["Taux"] = tva->Taux;

		//if(TvaDefaut->No==tva->No)
		//{
		//  adoTable->FieldValues["Defaut"]=1;
		//}
		// else
		//{
		// adoTable->FieldValues["Defaut"]=0;
		//}
		if (TvaDefaut->No == tva->No) {
			adoTable->FieldValues["Defaut"] = true;
		} else {
			adoTable->FieldValues["Defaut"] = false;
		}
		//if(TvaImmo->No==tva->No)
		//{
		//  adoTable->FieldValues["Immo"]=1;
		//}
		// else
		//{
		//  adoTable->FieldValues["Immo"]=0;
		//}
		if (TvaImmo->No == tva->No) {
			adoTable->FieldValues["Immo"] = true;
		} else {
			adoTable->FieldValues["Immo"] = false;
		}

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireCategorie(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie, int nature) {
	CL_Categorie *categorie;
	int n;

	char chaine[100];

	if (nature == 12) {

		ofstream outfile("exportDefDico.txt");

		sprintf(chaine, "la %3d ", vCategorie->Nbelt);
		outfile << chaine << endl;
		outfile.close();
	}

	MajTable(adoTable, nomTable);

	for (n = 0; n < vCategorie->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		categorie = vCategorie->Vecteur[n];

		adoTable->FieldValues["IdDefCateg"] = categorie->No;
		adoTable->FieldValues["Nom"] = categorie->Nom;
		adoTable->FieldValues["IdDefinitions"] = nature;
		adoTable->FieldValues["Notes"] = categorie->Notes;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireCatCalendrier(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Calendrier> *vCalendrier,
		int nature) {
	CL_Calendrier *calendrier;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vCalendrier->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		calendrier = vCalendrier->Vecteur[n];

		adoTable->FieldValues["IdDefCateg"] = calendrier->No;
		adoTable->FieldValues["Nom"] = calendrier->Nom;
		adoTable->FieldValues["IdDefinitions"] = nature;
		adoTable->FieldValues["Notes"] = calendrier->Notes;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_ProCha(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Item> *vItem, int nature) {
	CL_Item *item;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vItem->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		item = vItem->Vecteur[n];

		adoTable->FieldValues["IdDefItem"] = item->No;
		adoTable->FieldValues["Nom"] = item->Nom;
		adoTable->FieldValues["IdDefCateg"] = item->NoCategorie;
		adoTable->FieldValues["IdDefinitions"] = nature;
		adoTable->FieldValues["IdSysUnit"] = item->NoSysteme;
		adoTable->FieldValues["Prix"] = item->Prix;
		adoTable->FieldValues["IdTva"] = item->NoTva;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_ExtVar(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Item> *vItem, int nature) {
	CL_Item *item;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vItem->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		item = vItem->Vecteur[n];

		adoTable->FieldValues["IdDefItem"] = item->No;
		adoTable->FieldValues["Nom"] = item->Nom;
		adoTable->FieldValues["IdDefCateg"] = item->NoCategorie;
		adoTable->FieldValues["IdDefinitions"] = nature;
		adoTable->FieldValues["IdSysUnit"] = item->NoSysteme;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_ChStructRecDep(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Item> *vItem, int nature) {
	CL_Item *item;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vItem->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		item = vItem->Vecteur[n];

		adoTable->FieldValues["IdDefItem"] = item->No;
		adoTable->FieldValues["Nom"] = item->Nom;
		adoTable->FieldValues["IdDefCateg"] = item->NoCategorie;
		adoTable->FieldValues["IdDefinitions"] = nature;
		adoTable->FieldValues["IdTva"] = item->NoTva;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_Critere(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Item> *vItem) {
	CL_Item *item;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vItem->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		item = vItem->Vecteur[n];
		adoTable->FieldValues["IdDefinitions"] = 13;
		adoTable->FieldValues["IdDefItem"] = item->No;
		adoTable->FieldValues["IdDefCateg"] = item->NoCategorie;
		adoTable->FieldValues["Nom"] = item->Nom;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_Dico(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Item> *vItem) {
	CL_Item *item;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vItem->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		item = vItem->Vecteur[n];
		adoTable->FieldValues["IdDefinitions"] = 12;
		adoTable->FieldValues["IdDefDico"] = item->No;
		adoTable->FieldValues["IdDefCateg"] = item->NoCategorie;
		adoTable->FieldValues["Nom"] = item->Nom;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_EtatSortie(TADOQuery *adoQuery,
		TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_EtatSortie> *vEtat, TADOTable *adoTable1) {
	CL_EtatSortie *etatSortie;
	int n;
	CL_Elt *elt;
	CL_Vecteur<CL_Elt> *vecteur;
	AnsiString requete;

	char chaine[100];

	bool bComparaison = false;

	ofstream outfile("exportEtatSortie.txt", ios::app);

	if (nomTable == "Def_EtatSortie") {
		sprintf(chaine, "****** ETAT sortie");
		outfile << chaine << endl;
		bComparaison = false;
	} else {
		sprintf(chaine, "****** Serie Comp");
		outfile << chaine << endl;
		bComparaison = true;
	}

	MajTable(adoTable, nomTable);
	for (n = 0; n < vEtat->Nbelt; n++) {

		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		etatSortie = vEtat->Vecteur[n];
		adoTable->FieldValues["IdDefinitions"] =
				(bComparaison == true) ? 15 : 14;
		adoTable->FieldValues["IdEtatSortie"] = n;
		adoTable->FieldValues["IdDefEtatSortie"] = etatSortie->No;
		adoTable->FieldValues["IdDefCateg"] = etatSortie->NoCategorie;
		adoTable->FieldValues["Nom"] = etatSortie->Nom;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		//-- Enregistrement du détails
		vecteur = etatSortie->V_Elt;
		if (vecteur->Nbelt > 0) {
			for (int j = 0; j < vecteur->Nbelt; j++) {
				elt = vecteur->Vecteur[j];

				requete = "insert into ";
				if (bComparaison)
					requete += "SerieComp";
				else
					requete += "EtatSortie";
				requete +=
						"(IdDefinitions, IdDefCateg, Item, NoElt, NoFamille, NoCateg, NoItemElt, Digits, Couleur, Titre)";
				requete += " values( ";
				if (bComparaison)
					requete += "15";
				else
					requete += "14";
				requete += ", " + IntToStr(etatSortie->NoCategorie);
				requete += ", " + IntToStr(n);
				requete += ", " + IntToStr(j);
				requete += ", " + IntToStr(elt->NoFamille);
				requete += ", " + IntToStr(elt->NoCategorie);
				requete += ", " + IntToStr(elt->NoItem);
				requete += ", " + IntToStr(elt->Digits);
				requete += ", " + IntToStr(elt->Coul);
				requete += ", '" + AnsiString(elt->Nom) + "'";
				requete += ");";
				adoQuery->SQL->Clear();
				adoQuery->SQL->Add(requete);
				try {
					adoQuery->Prepared = true;
					adoQuery->ExecSQL(); // Open();
				} catch (Exception &e) {
					cpt++;
				}
			}
		}
		//--

		ProgressBar1->StepIt();
	}
	outfile.close();
}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_Periode(TADOQuery *adoQuery,
		AnsiString nomTable, CL_Vecteur<CL_Calendrier> *vCalendrier) {
	CL_Calendrier *calendrier;
	CL_Vecteur<CL_Periode> *vPeriode;
	CL_Periode *periode;
	int n, i;
	AnsiString requete;
	AnsiString requeteBase =
			"insert into " + nomTable
					+ " (IdDefCateg, IdDefinitions, IdPeriode, Nom, JDeb, MDeb, JFin, MFin, PcentDispo, HpJ)";

	//MajTable(adoTable,nomTable);

	for (n = 0; n < vCalendrier->Nbelt; n++) {

		calendrier = vCalendrier->Vecteur[n];
		vPeriode = calendrier->V_Periode;

		for (i = 0; i < vPeriode->Nbelt; i++) {
			periode = vPeriode->Vecteur[i];
			/*try{
			 adoTable->Append();
			 }
			 catch (Exception &e)
			 {}

			 adoTable->FieldValues["IdDefinitions"] = 5;
			 //adoTable->FieldValues["IdPeriode"]=periode->No;
			 adoTable->FieldValues["IdPeriode"]=i;
			 adoTable->FieldValues["Nom"]=periode->Nom;
			 adoTable->FieldValues["IdDefCateg"]=calendrier->No;
			 adoTable->FieldValues["JDeb"]=periode->JDeb;
			 adoTable->FieldValues["MDeb"]=periode->MDeb;
			 adoTable->FieldValues["JFin"]=periode->JFin;
			 adoTable->FieldValues["MFin"]=periode->MFin;
			 adoTable->FieldValues["PcentDispo"]=periode->PcentDispo;
			 adoTable->FieldValues["HpJ"]=periode->HpJ;

			 try
			 {adoTable->Post();}
			 catch (Exception &e)
			 {cpt++;
			 }
			 */
			requete = requeteBase;
			requete += " values( ";
			requete += IntToStr(calendrier->No);
			requete += ", 5";
			requete += ", " + IntToStr(periode->No);
			requete += ", '" + AnsiString(periode->Nom) + "'";
			requete += ", " + IntToStr(periode->JDeb);
			requete += ", " + IntToStr(periode->MDeb);
			requete += ", " + IntToStr(periode->JFin);
			requete += ", " + IntToStr(periode->MFin);
			requete += ", " + IntToStr(periode->PcentDispo);
			requete += ", " + AnsiString(periode->HpJ);
			requete += ");";
			adoQuery->SQL->Clear();
			adoQuery->SQL->Add(requete);
			try {
				adoQuery->Prepared = true;
				adoQuery->ExecSQL(); // Open();
			} catch (Exception &e) {
				cpt++;
			}

			ProgressBar1->StepIt();
		}
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireDef_Bestiaux(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Bestiaux> *vBestiaux) {
	CL_Bestiaux *bestiaux;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vBestiaux->Nbelt; n++) {

		try {
			adoTable->Append();
		} catch (Exception &e) {
		}
		bestiaux = vBestiaux->Vecteur[n];
		adoTable->FieldValues["IdDefinitions"] = 4;
		adoTable->FieldValues["IdBestiaux"] = bestiaux->No;
		adoTable->FieldValues["Nom"] = bestiaux->Nom;
		adoTable->FieldValues["IdDefCateg"] = bestiaux->NoCategorie;
		adoTable->FieldValues["IdOrigine"] = bestiaux->NoOrigine;
		adoTable->FieldValues["IdTva"] = bestiaux->NoTva;
		adoTable->FieldValues["Prix"] = bestiaux->Prix;
		adoTable->FieldValues["Vallnv"] = bestiaux->ValInv;
		adoTable->FieldValues["Donne1"] = bestiaux->DonneNo[0];
		adoTable->FieldValues["DonnePcent1"] = bestiaux->DonnePcent[0];
		adoTable->FieldValues["Donne2"] = bestiaux->DonneNo[1];
		adoTable->FieldValues["DonnePcent2"] = bestiaux->DonnePcent[1];
		adoTable->FieldValues["Donne3"] = bestiaux->DonneNo[2];
		adoTable->FieldValues["DonnePcent3"] = bestiaux->DonnePcent[2];
		adoTable->FieldValues["Donne4"] = bestiaux->DonneNo[3];
		adoTable->FieldValues["DonnePcent4"] = bestiaux->DonnePcent[3];

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireAleaCateg(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Tendance> *vTendance, int nature) {
	CL_Tendance *tendance;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vTendance->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		tendance = vTendance->Vecteur[n];

		adoTable->FieldValues["IdAleaCateg"] = tendance->No;
		adoTable->FieldValues["Nom"] = tendance->Nom;
		adoTable->FieldValues["IdAleas"] = nature;
		adoTable->FieldValues["Notes"] = tendance->Notes;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
// Quesque une tendance? pourquoi autant de paramètre?
void TEcrireAccessFrm::EcrireTendance(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Tendance> *vTendance, int nature, TADOQuery *adoQuery,
		int t, int natureDefinition) {
	CL_Tendance *tendance;
	CL_Vecteur<CL_Delta> *vDelta;
	CL_Delta *delta;
	int n, i, j, l;
	AnsiString annee;
	AnsiString an = "An";
	bool test = false;

	if (test == false && t == 1) {
		for (j = 0; j < 100; j++) {

			annee = AnsiString(an + (j + 1));
			RequeteTable(adoQuery, nomTable, annee);
		}
		test = true;
	}
	for (n = 0; n < vTendance->Nbelt; n++) {
		tendance = vTendance->Vecteur[n];
		MajTable(adoTable, nomTable);

		if (nature == PRIX) {
			vDelta = tendance->V_Delta;
			for (i = 0; i < vDelta->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				delta = vDelta->Vecteur[i];
				adoTable->FieldValues["IdAleaItem"] = delta->No;
				adoTable->FieldValues["IdDefinitions"] = natureDefinition;
				adoTable->FieldValues["IdDefItem"] = delta->NoItem;
				adoTable->FieldValues["IdAleaCateg"] = tendance->No;
				adoTable->FieldValues["atelier"] = delta->Nature;
				adoTable->FieldValues["IdAleas"] = t;
				for (l = 0; l < 100; l++) {
					adoTable->FieldValues[an + (l + 1)] = delta->Pcent[l];

				}

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == QUANTITE) {
			vDelta = tendance->V_Delta;
			for (i = 0; i < vDelta->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				delta = vDelta->Vecteur[i];
				adoTable->FieldValues["IdAleaItem"] = delta->NoAtelier;
				adoTable->FieldValues["IdDefinitions"] = natureDefinition;
				adoTable->FieldValues["IdDefItem"] = delta->NoItem;
				adoTable->FieldValues["IdAleaCateg"] = tendance->No;
				adoTable->FieldValues["IdAleas"] = t;
				adoTable->FieldValues["atelier"] = delta->Nature;
				for (l = 0; l < 100; l++) {
					adoTable->FieldValues[an + (l + 1)] = delta->Pcent[l];

				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_CatAtelier(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Categorie> *vCategorie, int nature) {
	CL_Categorie *categorie;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vCategorie->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		categorie = vCategorie->Vecteur[n];

		adoTable->FieldValues["IdAteCateg"] = categorie->No;
		adoTable->FieldValues["Nom"] = categorie->Nom;
		adoTable->FieldValues["IdAteliers"] = nature;
		//adoTable->FieldValues["DebAmor"]=categorie->DebAmor;
		//adoTable->FieldValues["DurAmor"]=categorie->DurAmor;
		//adoTable->FieldValues["NbPhase"]=categorie->NbPhase;

		//adoTable->FieldValues["Notes"]=categorie->Notes;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
// en fait EcrireEspece
void TEcrireAccessFrm::EcrireAte_CatPerenne(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Espece> *vEspece,
		TADOQuery *adoQuery, int nature) {
	CL_Espece *espece;
	int n;
	AnsiString as, asPhase;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vEspece->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		espece = vEspece->Vecteur[n];

		adoTable->FieldValues["IdAteCateg"] = espece->No;
		adoTable->FieldValues["Nom"] = espece->Nom;
		adoTable->FieldValues["IdAteliers"] = nature;
		adoTable->FieldValues["DebAmor"] = espece->DebAmor;
		adoTable->FieldValues["DurAmor"] = espece->DurAmor;
		adoTable->FieldValues["NbPhase"] = espece->NbPhase;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_Atelier(TADOTable *adoTable,
		AnsiString nomTable, int nature, CL_Vecteur<CL_Atelier> *vAtelier,
		int ate) {
	bool b, b2, b3;
	int n;
	CL_Atelier *atelier;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		atelier = vAtelier->Vecteur[n];

		adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
		adoTable->FieldValues["Nom"] = atelier->Nom;
		adoTable->FieldValues["IdAteliers"] = ate;
		adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
		adoTable->FieldValues["Notes"] = atelier->Notes;

		b = atelier->Derobe;
		if (b == true) {
			adoTable->FieldValues["Derobe"] = 1;
		} else {
			adoTable->FieldValues["Derobe"] = 0;
		}

		b2 = atelier->PImmoExiste;
		if (b2 == true) {
			adoTable->FieldValues["PImmoExiste"] = 1;
		} else {
			adoTable->FieldValues["PImmoExiste"] = 0;
		}

		b3 = atelier->PImmoFamExiste;
		if (b3 == true) {
			adoTable->FieldValues["PImmoFamExiste"] = 1;
		} else {
			adoTable->FieldValues["PImmoFamExiste"] = 0;
		}

		adoTable->FieldValues["ValInvRepro"] = atelier->ValInvRepro;
		adoTable->FieldValues["ValInvAutre"] = atelier->ValInvAutre;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_Atelier(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Atelier> *vAtelier) {
	int n;
	bool b1, b2, b3;
	CL_Atelier *atelier;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		atelier = vAtelier->Vecteur[n];

		adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
		adoTable->FieldValues["Nom"] = atelier->Nom;
		adoTable->FieldValues["IdAteliers"] = 3;
		adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
		adoTable->FieldValues["Notes"] = atelier->Notes;

		b1 = atelier->Derobe;
		if (b1 == true) {
			adoTable->FieldValues["Derobe"] = 1;
		} else {
			adoTable->FieldValues["Derobe"] = 0;
		}

		b2 = atelier->PImmoExiste;
		if (b2 == true) {
			adoTable->FieldValues["PImmoExiste"] = 1;
		} else {
			adoTable->FieldValues["PImmoExiste"] = 0;
		}

		b3 = atelier->PImmoFamExiste;
		if (b3 == true) {
			adoTable->FieldValues["PImmoFamExiste"] = 1;
		} else {
			adoTable->FieldValues["PImmoFamExiste"] = 0;
		}

		adoTable->FieldValues["ValInvRepro"] = atelier->ValInvRepro;
		adoTable->FieldValues["ValInvAutre"] = atelier->ValInvAutre;

		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_Item(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Atelier> *vAtelier, int nature, int ate) {
	int n, i, j;
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_ItemParAtelier *itemPA;
	CL_Vecteur<CL_EEF> *vEEF;
	CL_EEF *eef;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		if (nature == 1) {
			vecteurIPA = atelier->V_Produit;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; //   itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 1;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 2) {
			vecteurIPA = atelier->V_Charge;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 2;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 3) {
			vecteurIPA = atelier->V_ChargeVolume;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 1;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Charge->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				adoTable->FieldValues["C3IdDefinitions"] = 2;
				adoTable->FieldValues["C3IdDefCateg"] =
						itemPA->Charge->NoCategorie;
				adoTable->FieldValues["C3IdDefItem"] = itemPA->NoCharge;

				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 4) {
			vecteurIPA = atelier->V_Externalite;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 3;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 5) {

			vEEF = atelier->V_Avance;

			for (i = 0; i < vEEF->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				eef = vEEF->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = eef->No;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["Avant1"] = eef->Deb;
				adoTable->FieldValues["Ph1"] = eef->Val;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 6) {
			//  vecteurIPA=atelier->V_Externalite;       //A changer        ImmoFam

			// for(i=0;i<vecteurIPA->Nbelt;i++)
			// {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			//itemPA=vecteurIPA->Vecteur[i];
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
			adoTable->FieldValues["IdList"] = nature;
			adoTable->FieldValues["IdAteliers"] = ate;
			adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
			adoTable->FieldValues["Ph0"] = atelier->ProdImmo;
			adoTable->FieldValues["Ph1"] = atelier->ProdImmo;
			//adoTable->FieldValues["2"]=atelier->
			//adoTable->FieldValues["3"]=atelier->
			//adoTable->FieldValues["4"]=atelier->
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
			//  }
		}

		if (nature == 7) {
			//  vecteurIPA=atelier->V_Externalite;       //A changer        ImmoEnt

			// for(i=0;i<vecteurIPA->Nbelt;i++)
			// {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			//itemPA=vecteurIPA->Vecteur[i];
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
			adoTable->FieldValues["IdList"] = nature;
			adoTable->FieldValues["IdAteliers"] = ate;
			adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
			adoTable->FieldValues["Ph0"] = atelier->ProdImmoFam;
			adoTable->FieldValues["Ph1"] = atelier->ProdImmoFam;
			//adoTable->FieldValues["2"]=atelier->
			//adoTable->FieldValues["3"]=atelier->
			//adoTable->FieldValues["4"]=atelier->
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
			//  }
		}

		if (nature == 8) {
			vecteurIPA = atelier->V_Externalite; //A changer       Travail

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;
				adoTable->FieldValues["IdItem"] = itemPA->NoItem;
				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 10) {
			vecteurIPA = atelier->V_ProdPied;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;

				adoTable->FieldValues["C1IdDefinitions"] = 1;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				//adoTable->FieldValues["IdItem"]=itemPA->NoItem;
				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 11) {
			vecteurIPA = atelier->V_ChPied;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoCategorie;

				adoTable->FieldValues["C1IdDefinitions"] = 2;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				//adoTable->FieldValues["IdItem"]=itemPA->NoItem;
				adoTable->FieldValues["Ph0"] = itemPA->QtePhase[0];
				adoTable->FieldValues["Ph1"] = itemPA->QtePhase[1];
				adoTable->FieldValues["Ph2"] = itemPA->QtePhase[2];
				if (ate == 4) {
					adoTable->FieldValues["Ph3"] = itemPA->QtePhase[3];
					adoTable->FieldValues["Ph4"] = itemPA->QtePhase[4];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}
	}

}
//-----------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_BesTrav(TADOQuery *adoQuery,
		TADOTable *adoTable, TADOTable *adoTable1, AnsiString nomTable,
		AnsiString nomTable1, CL_Vecteur<CL_Atelier> *vAtelier, int ate) {
	int n, i;
	CL_Atelier *atelier;
	CL_Vecteur<CL_BesTrav> *vecteurBesTrav;
	CL_BesTrav* besTrav;
	AnsiString requete;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		vecteurBesTrav = atelier->V_BesTrav;

		for (i = 0; i < vecteurBesTrav->Nbelt; i++) {
			if (vecteurBesTrav->Vecteur[i] != NULL) {
				besTrav = vecteurBesTrav->Vecteur[i];
				requete = "insert into Ate_BesTrav";
				requete +=
						"(IdAteliers, IdAteSousCateg, IdDefCateg, IdDefinitions, NbPhase, NbPeriodeCal)";
				requete += " values( ";
				requete += IntToStr(ate);
				requete += ", " + IntToStr(atelier->No);
				requete += ", " + IntToStr(besTrav->No);
				requete += ", 5";
				requete += ", " + IntToStr(besTrav->NbPhase);
				requete += ", " + IntToStr(besTrav->NbPeriodeCal);
				requete += ");";
				adoQuery->SQL->Clear();
				adoQuery->SQL->Add(requete);
				try {
					adoQuery->Prepared = true;
					adoQuery->ExecSQL(); // Open();
				} catch (Exception &e) {
					cpt++;
				}

				int atNo = atelier->No;
				int bNo = besTrav->No;

				// Ecriture des Items (Matrice)
				EcrireAte_BesTrav_Item(adoQuery, adoTable1, nomTable1,
						besTrav->Besoins, ate, atNo, bNo);

				ProgressBar1->StepIt();
			}
		}

	}

}

//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_BesTrav_Item(TADOQuery *adoQuery,
		TADOTable *adoTable, AnsiString nomTable, CL_Matrice *besoin, int ate,
		int numAte, int numCal) {
	int i, j;
	int k;
	AnsiString requete;

	MajTable(adoTable, nomTable);

	for (i = 0; i < besoin->iX; i++) {
		for (j = 0; j < besoin->jX; j++) {
			k = i + (j * besoin->iX);

			if ((besoin->X[k] != NULL) && (besoin->X[k] != 0)) {
				requete = "insert into Ate_BesTrav_Item";
				requete +=
						"(IdAteliers, IdAteSousCateg, IdDefCateg, IdDefinitions, iX, jX, Valeur)";
				requete += " values( ";
				requete += IntToStr(ate);
				requete += ", " + IntToStr(numAte);
				requete += ", " + IntToStr(numCal);
				requete += ", 5";
				requete += ", " + IntToStr(i);
				requete += ", " + IntToStr(j);
				requete += ", " + AnsiString(besoin->X[k]);
				requete += ");";
				adoQuery->SQL->Clear();
				adoQuery->SQL->Add(requete);
				try {
					adoQuery->Prepared = true;
					adoQuery->ExecSQL(); // Open();
				} catch (Exception &e) {
					cpt++;
				}
			}
		}
	}
	try {
		adoTable->Post();
	} catch (Exception &e) {
		cpt++;
	}

}
//-----------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireAte_Avance(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Atelier> *vAtelier, int ate) {
	int n, i;
	CL_Atelier *atelier;
	CL_Vecteur<CL_EEF> *vecteurAvance;

	CL_EEF* eEF;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		vecteurAvance = atelier->V_Avance;

		//ShowMessage("ici "+IntToStr(ate)+" - "+IntToStr(atelier->No)+" - "+IntToStr(vecteurAvance->Nbelt)+" * ");
		for (i = 0; i < vecteurAvance->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			eEF = vecteurAvance->Vecteur[i];

			adoTable->FieldValues["IdAteliers"] = ate; //Def. Atelier
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No; //N° Atelier
			adoTable->FieldValues["Item"] = i;
			adoTable->FieldValues["Debut"] = eEF->Deb;
			adoTable->FieldValues["Fin"] = eEF->Fin;
			adoTable->FieldValues["Valeur"] = eEF->Val;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}

			ProgressBar1->StepIt();
		}

	}

}

//-----------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireAte_Immo(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Atelier> *vAtelier, int ate) {
	int n, i;
	CL_Atelier *atelier;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		if (atelier->PImmoExiste == true) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			adoTable->FieldValues["IdAteliers"] = ate; //Def. Atelier
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No; //N° Atelier
			adoTable->FieldValues["IdList"] = 6; //Immo Entreprise
			adoTable->FieldValues["Item"] = 0; //1 seul enregistrement
			for (i = 0; i < atelier->NbPhase; i++) {
				adoTable->FieldValues[AnsiString("Ph") + (i)] =
						atelier->ProdImmo[i];
			}

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}

		}

		if (atelier->PImmoFamExiste == true) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			adoTable->FieldValues["IdAteliers"] = ate; //Def. Atelier
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No; //N° Atelier
			adoTable->FieldValues["IdList"] = 7; //ImmoFam
			adoTable->FieldValues["Item"] = 0; //1 seul enregistrement
			for (i = 0; i < atelier->NbPhase; i++) {
				adoTable->FieldValues[AnsiString("Ph") + (i)] =
						atelier->ProdImmoFam[i];
			}

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}

		}

		ProgressBar1->StepIt();
	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_PiedHaPer(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Atelier> *vAtelier, int nature,
		int ate) {
	int n, i, j;
	AnsiString asPhase;
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_ItemParAtelier *itemPA;
	CL_EEF *eef;
	CL_Vecteur<CL_EEF> *vecteurAvance;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		if (nature == 9) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			nature = 9;
			adoTable->FieldValues["IdAteItem"] = 0;
			adoTable->FieldValues["IdAteliers"] = ate;
			adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
			adoTable->FieldValues["IdList"] = nature;

			for (j = 0; j < atelier->NbPhase; j++) {
				asPhase = AnsiString("Ph") + (j);
				adoTable->FieldValues[asPhase] = atelier->PiedHa[j];
			}

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();

		}

	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_PiedHa(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Atelier> *vAtelier, int nature,
		int ate) {
	int n, i, j;
	AnsiString asPhase;
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_ItemParAtelier *itemPA;
	CL_EEF *eef;
	CL_Vecteur<CL_EEF> *vecteurAvance;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		if (nature == 9) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			nature = 9;
			adoTable->FieldValues["IdAteItem"] = 0;
			adoTable->FieldValues["IdAteliers"] = ate;
			adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
			adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
			adoTable->FieldValues["IdList"] = nature;

			adoTable->FieldValues["Ph0"] = atelier->PiedHa[0];
			adoTable->FieldValues["Ph1"] = atelier->PiedHa[1];
			adoTable->FieldValues["Ph2"] = atelier->PiedHa[2];
			if (ate == 4) {
				adoTable->FieldValues["Ph3"] = atelier->PiedHa[3];
				adoTable->FieldValues["Ph4"] = atelier->PiedHa[4];
			}

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();

		}

	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAte_ItemPer(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Atelier> *vAtelier, int nature,
		TADOQuery *adoQuery, int ate) {
	int n, i, j;
	AnsiString asPhase;
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_ItemParAtelier *itemPA;
	CL_EEF *eef;
	CL_Vecteur<CL_EEF> *vecteurAvance;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAtelier->Nbelt; n++) {
		atelier = vAtelier->Vecteur[n];

		if (nature == 1) {
			vecteurIPA = atelier->V_Produit;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				//nature=1;
				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 1;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				for (j = 0; j < atelier->NbPhase; j++) {
					asPhase = AnsiString("Ph") + (j);
					adoTable->FieldValues[asPhase] = itemPA->QtePhase[j];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 2) {
			vecteurIPA = atelier->V_Charge;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				//nature=2;
				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 2;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				for (j = 0; j < atelier->NbPhase; j++) {
					asPhase = AnsiString("Ph") + (j);
					adoTable->FieldValues[asPhase] = itemPA->QtePhase[j];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 3) {
			vecteurIPA = atelier->V_ChargeVolume;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				//nature=3;
				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 1;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Charge->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				adoTable->FieldValues["C3IdDefinitions"] = 2;
				adoTable->FieldValues["C3IdDefCateg"] =
						itemPA->Charge->NoCategorie;
				adoTable->FieldValues["C3IdDefItem"] = itemPA->NoCharge;

				for (j = 0; j < atelier->NbPhase; j++) {
					asPhase = AnsiString("Ph") + (j);
					adoTable->FieldValues[asPhase] = itemPA->QtePhase[j];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		if (nature == 4) {
			vecteurIPA = atelier->V_Externalite;

			for (i = 0; i < vecteurIPA->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				//nature=4;
				itemPA = vecteurIPA->Vecteur[i];
				adoTable->FieldValues["IdAteItem"] = i; // itemPA->No;
				adoTable->FieldValues["IdAteliers"] = ate;
				adoTable->FieldValues["IdAteCateg"] = atelier->NoEspece;
				adoTable->FieldValues["IdAteSousCateg"] = atelier->No;
				adoTable->FieldValues["IdList"] = nature;

				adoTable->FieldValues["C1IdDefinitions"] = 3;
				adoTable->FieldValues["C1IdDefCateg"] =
						itemPA->Item->NoCategorie;
				adoTable->FieldValues["C1IdDefItem"] = itemPA->NoItem;

				for (j = 0; j < atelier->NbPhase; j++) {
					asPhase = AnsiString("Ph") + (j);
					adoTable->FieldValues[asPhase] = itemPA->QtePhase[j];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}

		//------- nature==5,6,7,8,9,10 et 11
		//------- Traité ailleurs - voir Ate_avances, Ate_ImmoProd, Ate_BesTrav et Ate_PiedHa
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrirePhase(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Espece> *vEspece) {
	int n, j;
	AnsiString asPhase;
	CL_Espece *espece;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vEspece->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}
		espece = vEspece->Vecteur[n];
		adoTable->FieldValues["IdAteliers"] = 3;
		adoTable->FieldValues["IdAteCateg"] = espece->No;
		for (j = 0; j < espece->NbPhase; j++) {
			asPhase = AnsiString("Ph") + (j + 1);
			adoTable->FieldValues[asPhase] = espece->Phase[j];
		}
		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEcrireAccessFrm::AdresseChFVol(CL_Vecteur<CL_Atelier> *vAtelier) {
	int i, j;
	CL_Atelier *atelier;
	CL_ItemParAtelier *itemPA;

	for (i = 0; i < vAtelier->Nbelt; i++) {
		atelier = vAtelier->Vecteur[i];
		for (j = 0; j < atelier->V_ChargeVolume->Nbelt; j++) {
			itemPA = atelier->V_ChargeVolume->Vecteur[j];
			itemPA->ItemPA = atelier->V_Produit->trouve(itemPA->NoItemPA);
		}
	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireRepart(TADOTable *adoTable, AnsiString nomTable,
		TADOTable *adoTable1, AnsiString nomTable1,
		CL_Vecteur<CL_Repart> *vRepart) {
	int n, j;
	AnsiString asPhase;
	CL_Repart *repart;
	TList *lstPcent; //liste de CL_IntFloat mois 0 à 36 et pcent
	CL_IntFloat *datVal;

	MajTable(adoTable, nomTable);
	MajTable(adoTable1, nomTable1);

	for (n = 0; n < vRepart->Nbelt; n++) {
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		repart = vRepart->Vecteur[n];

		adoTable->FieldValues["IdRepart"] = repart->No;
		adoTable->FieldValues["NomRepart"] = repart->Nom;
		adoTable->FieldValues["IdDefinitions"] = 17;
		adoTable->FieldValues["IdDefCateg"] = repart->NoCategorie;
		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}

		lstPcent = repart->LstPcent;

		for (j = 0; j < lstPcent->Count; j++) {
			try {
				adoTable1->Append();
			} catch (Exception &e) {
			}
			datVal = (CL_IntFloat *) lstPcent->Items[j];

			adoTable1->FieldValues["IdRepart"] = repart->No;
			adoTable1->FieldValues["DateRepart"] = datVal->i;
			adoTable1->FieldValues["ValeurRepart"] = datVal->Val;
			try {
				adoTable1->Post();
			} catch (Exception &e) {
				cpt++;
			}
		}
		ProgressBar1->StepIt();
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------------------Agri-----------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireAgri(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	ST_NoAgri *variante;
	int n, i;
	bool test = false;
	int noMax = 0;
	int ident = 0;

	for (n = 0; n < vAgri->Nbelt; n++) {
		MajTable(adoTable, nomTable);
		agri = vAgri->Vecteur[n];

		if (agri->EstVariante == false && agri->EstPlus10Ans == false) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			adoTable->FieldValues["IdAgri"] = agri->No;
			adoTable->FieldValues["Nom"] = agri->Nom;
			adoTable->FieldValues["NoSerie"] = agri->NoSerie;
			adoTable->FieldValues["Notes"] = agri->Notes;
			adoTable->FieldValues["NbAnSim"] = agri->DefSim->NbAnSim;
			adoTable->FieldValues["An_0"] = agri->DefSim->An_0;
			adoTable->FieldValues["NoVariante"] = 1;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
		}
	}

	for (n = 0; n < vAgri->Nbelt; n++) {
		MajTable(adoTable, nomTable);
		agri = vAgri->Vecteur[n];
		if (agri->EstVariante == true && agri->NoSerie == 0) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			adoTable->FieldValues["IdAgri"] = agri->No;
			adoTable->FieldValues["Nom"] = agri->Nom;
			adoTable->FieldValues["OrVar"] = agri->Pere->No;
			adoTable->FieldValues["NoSerie"] = agri->NoSerie;
			adoTable->FieldValues["Notes"] = agri->Notes;
			adoTable->FieldValues["NoVariante"] = agri->NoVariante;
			adoTable->FieldValues["NbAnSim"] = agri->DefSim->NbAnSim;
			adoTable->FieldValues["An_0"] = agri->DefSim->An_0;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
		}

	}

	for (n = 0; n < vAgri->Nbelt; n++) {
		MajTable(adoTable, nomTable);
		agri = vAgri->Vecteur[n];
		if (agri->DefSim->NbAnSim > 10 && agri->NoSerie == 0) {
			for (i = 1; i < agri->LstSerie->Count; i++) {
				variante = (ST_NoAgri*) agri->LstSerie->Items[i];
				if (variante->Agri->EstVariante == false) {
					try {
						adoTable->Append();
					} catch (Exception &e) {
					}

					adoTable->FieldValues["IdAgri"] = variante->No;
					adoTable->FieldValues["OrSerie"] = agri->No;
					adoTable->FieldValues["NoSerie"] = agri->NoSerie + i;
					adoTable->FieldValues["Notes"] = agri->Notes;
					adoTable->FieldValues["NbAnSim"] = agri->DefSim->NbAnSim;
					adoTable->FieldValues["An_0"] = agri->DefSim->An_0;

					try {
						adoTable->Post();
					} catch (Exception &e) {
						cpt++;
					}
				} else {
					try {
						adoTable->Append();
					} catch (Exception &e) {
					}

					adoTable->FieldValues["IdAgri"] = variante->No;
					adoTable->FieldValues["OrSerie"] = agri->No;
					adoTable->FieldValues["OrVar"] = variante->Agri->Pere->No;
					adoTable->FieldValues["NoVariante"] =
							variante->Agri->NoVariante;
					adoTable->FieldValues["NoSerie"] = agri->NoSerie + i;
					adoTable->FieldValues["Notes"] = agri->Notes;
					adoTable->FieldValues["NbAnSim"] = agri->DefSim->NbAnSim;
					adoTable->FieldValues["An_0"] = agri->DefSim->An_0;

					try {
						adoTable->Post();
					} catch (Exception &e) {
						cpt++;
					}
				}
			}
		}
	}
	ProgressBar1->StepIt();
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriVariante(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	ST_NoAgri *variante;

	MajTable(adoTable, nomTable);

	for (int i = 0; i < vAgri->Nbelt; i++) {
		agri = vAgri->Vecteur[i];

		for (int n = 0; n < agri->LstVariante->Count; n++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			variante = (ST_NoAgri*) agri->LstVariante->Items[n];

			adoTable->FieldValues["IdAgri"] = variante->Agri->Nom;
			ShowMessage(variante->Agri->Nom);
			adoTable->FieldValues["IdVariante"] = variante->No;
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}

		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgri_DefSim(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	CL_AgriDefSim *DefSim;
	int n;

	MajTable(adoTable, nomTable);
	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		DefSim = agri->DefSim;
		if (DefSim != NULL) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["An_0"] = DefSim->An_0;
			adoTable->FieldValues["NbAnSim"] = DefSim->NbAnSim;
			adoTable->FieldValues["MDeb"] = DefSim->MDeb;
			adoTable->FieldValues["AnCalage"] = DefSim->AnCalage;
			adoTable->FieldValues["TypeAlea"] = DefSim->TypeAlea;
			adoTable->FieldValues["NoPrixProd"] = DefSim->NoPrixProd;
			adoTable->FieldValues["NoPrixCharge"] = DefSim->NoPrixCharge;
			adoTable->FieldValues["NoQProd"] = DefSim->NoQProd;
			adoTable->FieldValues["NoQCharge"] = DefSim->NoQCharge;
			adoTable->FieldValues["NoQExt"] = DefSim->NoQExt;
			adoTable->FieldValues["TouSPrixProd"] = DefSim->TouSPrixProd;
			adoTable->FieldValues["TouSPrixCharge"] = DefSim->TouSPrixCharge;
			adoTable->FieldValues["TouSQProd"] = DefSim->TouSQProd;
			adoTable->FieldValues["TouSQCharge"] = DefSim->TouSQCharge;
			adoTable->FieldValues["TouSQExt"] = DefSim->TouSQExt;
			adoTable->FieldValues["Chaine"] = DefSim->Enchainement;
			ProgressBar1->StepIt();
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriSerie(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	CL_Item *serie;
	int nbSerie;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		if (agri->DefSim->NbAnSim > 10) {
			nbSerie = agri->DefSim->NbAnSim / 10;

			for (int i = 0; i < nbSerie; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				adoTable->FieldValues["IdAgri"] = agri->No;
				serie = (CL_Item*) agri->LstSerie->Items[i];
				adoTable->FieldValues["IdSerie"] = serie->No;
				adoTable->FieldValues["OrdreChono"] = i + 1;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
			}
			ProgressBar1->StepIt();
		}
	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgri_Critere(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	CL_Item *critere;
	int nbCritere;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		//        adoTable->Append();
		agri = vAgri->Vecteur[n];

		//    	adoTable->FieldValues["NoAgri"]=agri->No;

		nbCritere = agri->LstCritere->Count;
		for (int i = 0; i < nbCritere; i++) {
			try {

				adoTable->Append();
			} catch (Exception &e) {
			}
			adoTable->FieldValues["NoAgri"] = agri->No;
			critere = (CL_Item*) agri->LstCritere->Items[i];
			adoTable->FieldValues["NoCritere"] = critere->No;
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgri_RepartItem(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	CL_Vecteur<CL_ItemRepart> *vecteur;
	CL_ItemRepart *itemRepart;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		vecteur = agri->V_ItemRepart;

		for (int i = 0; i < vecteur->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			itemRepart = vecteur->Vecteur[i];

			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoFamille"] = itemRepart->Famille;
			adoTable->FieldValues["IdRepartItem"] = itemRepart->NoItem;
			adoTable->FieldValues["NoX"] = vecteur->NoX;
			adoTable->FieldValues["Nb"] = vecteur->Nbelt;
			for (int j = 0; j < N_X; j++) {
				adoTable->FieldValues[AnsiString("NoRepartQ") + (j + 1)] =
						itemRepart->LesNoRepartQ[j];
				adoTable->FieldValues[AnsiString("NoRepartV") + (j + 1)] =
						itemRepart->LesNoRepartV[j];

			}
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriAssol(TADOTable *adoTable, AnsiString nomTable,
		int nature, CL_Vecteur<CL_Agriculteur> *vAgri, TADOQuery *adoQuery) {
	int n, i, l;
	CL_Agriculteur *agri;
	CL_Valeur *valeur;
	CL_Vecteur<CL_Valeur> *vValeur;
	AnsiString annee;
	AnsiString an = "An";

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		valeur = new CL_Valeur();

		switch (nature) {
		case CULTURE:
			vValeur = agri->V_Culture;
			for (i = 0; i < vValeur->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				valeur = vValeur->Vecteur[i];
				adoTable->FieldValues["IdAteliers"] = 1;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = valeur->No;
				adoTable->FieldValues["NoAteSousCateg"] = valeur->NoAtelier;
				for (l = 0; l < 10; l++) {
					adoTable->FieldValues[an + (l + 1)] = valeur->Valeur[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;

		case ANIMAUX:
			vValeur = agri->V_Animaux;
			for (i = 0; i < vValeur->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				valeur = vValeur->Vecteur[i];
				adoTable->FieldValues["IdAteliers"] = 2;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = valeur->No;
				adoTable->FieldValues["NoAteSousCateg"] = valeur->NoAtelier;
				for (l = 0; l < 10; l++) {
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = valeur->Valeur[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriPerenne(TADOTable *adoTable,
		AnsiString nomTable, int nature, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_Agriculteur *agri;
	CL_Verger *verger;
	CL_Vecteur<CL_Verger> *vVerger;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		verger = new CL_Verger();

		switch (nature) {
		case PERENNE:
			vVerger = agri->V_Verger;
			for (i = 0; i < vVerger->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				verger = vVerger->Vecteur[i];
				adoTable->FieldValues["IdAteliers"] = 3;
				adoTable->FieldValues["NoItem"] = verger->No;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoAteSousCateg"] = verger->NoAtelier;
				adoTable->FieldValues["AnPlant"] = verger->AnPlant;
				adoTable->FieldValues["AnArr"] = verger->AnArr;
				adoTable->FieldValues["Surface"] = verger->Surface;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;

		case VIVRIER:
			vVerger = agri->V_Vivrier;
			for (i = 0; i < vVerger->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				verger = vVerger->Vecteur[i];
				adoTable->FieldValues["IdAteliers"] = 4;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = verger->No;
				adoTable->FieldValues["NoAteSousCateg"] = verger->NoAtelier;
				adoTable->FieldValues["AnPlant"] = verger->AnPlant;
				adoTable->FieldValues["Duree"] = verger->AnArr;
				adoTable->FieldValues["Surface"] = verger->Surface;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireValeur(TADOTable *adoTable, float *valeur,
		int nbVal) {
	int i;
	AnsiString as, asAn;
	for (i = 0; i < nbVal; i++)
		valeur[i] = 0.;
	for (i = 0; i < nbVal; i++) {
		asAn = AnsiString("An") + AnsiString(i + 1);
		as = adoTable->FieldByName(asAn)->AsString;
		if (as.Length() == 0)
			continue;
		valeur[i] = adoTable->FieldByName(asAn)->AsString.ToDouble();
	}
	ProgressBar->StepIt();
}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriFormule(TADOTable *adoTable,
		TADOTable *adoTable1, AnsiString nomTable, int nature,
		CL_Vecteur<CL_Agriculteur> *vAgri, TADOQuery *adoQuery) {
	int n, i, l;
	CL_Agriculteur *agri;
	CL_Formule *formule;
	CL_Vecteur<CL_Formule> *vFormule;
	CL_Prog *prog;
	int ident = 0;
	int _idDef = -1;
	int _idList = -1;
	int _ident = -1;
	int _noAgri = -1;
	int _noItem = -1;

	//CL_Prog        *prog;
	//CL_Arbre       *arbre;

	AnsiString annee;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		_noAgri = agri->No;
		ident = 0;
		MajTable(adoTable, nomTable);

		formule = new CL_Formule();

		switch (nature) {
		case PRODUIT:
			vFormule = agri->V_Produits;
			break;
		case CHARGE:
			vFormule = agri->V_Charges;
			break;
		case CHSTRUCT:
			vFormule = agri->V_ChStruct;
			break;
		case RECDIV:
			vFormule = agri->V_RecDiv;
			break;
		case RECFAM:
			vFormule = agri->V_RecFam;
			break;
		case DEPDIV:
			vFormule = agri->V_DepDiv;
			break;
		case DEPFAM:
			vFormule = agri->V_DepFam;
			break;
		case EXTPOS:
			vFormule = agri->V_ExtPos;
			break;
		case EXTNEG:
			vFormule = agri->V_ExtNeg;
			break;
		default:
			return;
		}

		for (i = 0; i < vFormule->Nbelt; i++) {
			if (vFormule->Vecteur[i] != NULL) {
				formule = vFormule->Vecteur[i];
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				switch (nature) {
				case PRODUIT:
					_idDef = 1;
					_idList = 1;
					break;
				case CHARGE:
					_idDef = 2;
					_idList = 2;
					break;
				case CHSTRUCT:
					_idDef = 6;
					_idList = 3;
					break;
				case RECDIV:
					_idDef = 7;
					_idList = 4;
					break;
				case RECFAM:
					_idDef = 9;
					_idList = 6;
					break;
				case DEPDIV:
					_idDef = 8;
					_idList = 5;
					break;
				case DEPFAM:
					_idDef = 10;
					_idList = 7;
					break;
				case EXTPOS:
					_idDef = 3;
					_idList = 8;
					break;
				case EXTNEG:
					_idDef = 3;
					_idList = 9;
					break;
				default:
					return;
				}

				_ident = ident;
				_noItem = formule->Item->No;
				adoTable->FieldValues["IdDefinitions"] = _idDef;
				adoTable->FieldValues["IdList"] = _idList;
				adoTable->FieldValues["NoFormule"] = _ident;
				ident++;
				adoTable->FieldValues["NoAgri"] = _noAgri;
				adoTable->FieldValues["NoItem"] = _noItem;
				adoTable->FieldValues["Origine"] = formule->Origine;
				for (l = 0; l < N_X; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				//Sauvegarde arbre et reseau
				for (l = 0; l < N_X; l++) {
					if (formule->LesProg[l] != NULL) {
						prog = formule->LesProg[l];

						if (prog->Arbre != NULL) {
							EcrireAgriFormuleArbre(adoQuery, adoTable1, _noAgri,
									_idDef, _ident, _noItem, _idList, l,
									prog->Arbre);
						}
						if (prog->Reseau != NULL) {
							//EcrireAgriFormuleReseau(adoTable1, _noAgri, _ident, _noItem, _idList, l, prog->Reseau);
						}
					}
				}
				ProgressBar1->StepIt();
			} else
				EcrireRapport(
						" -- erreur agriculteur: " + AnsiString(_noAgri)
								+ " vFormule->Vecteur[" + AnsiString(i)
								+ "]==NULL");
		}

	}
}
//--------------------------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriFormuleArbre(TADOQuery *adoQuery,
		TADOTable *adoTable, int noAgri, int idDef, int ident, int noItem,
		int idList, int noAn, CL_Arbre *Arbre) {
	AnsiString codebranche;
	AnsiString arg1branche;
	AnsiString arg2branche;
	AnsiString arg3branche;
	AnsiString valeurbranche;
	AnsiString typebranche;
	AnsiString datebranche;
	AnsiString requete;

	for (int n = 0; n < Arbre->BrancheX; n++) {
		requete =
				"insert into Agri_FormuleArbre(NoAgri, NoFormule, IdDefinitions, NoItem, IdList, NoAn,";
		requete +=
				" nbrBranche, noBranche, code, arg1, arg2, arg3, valeur, type, dateBranche)";
		requete += " values( ";
		requete += IntToStr(noAgri);
		requete += ", " + IntToStr(ident);
		requete += ", " + IntToStr(idDef);
		requete += ", " + IntToStr(noItem);
		requete += ", " + IntToStr(idList);
		requete += ", " + IntToStr(noAn);
		requete += ", " + IntToStr(Arbre->BrancheX);
		requete += ", " + IntToStr(n);
		requete += ", " + IntToStr(Arbre->LesBranches[n].code);
		requete += ", " + IntToStr(Arbre->LesBranches[n].arg[0]);
		requete += ", " + IntToStr(Arbre->LesBranches[n].arg[1]);
		requete += ", " + IntToStr(Arbre->LesBranches[n].arg[2]);
		if ((Arbre->LesBranches[n].valeur != NULL)
				&& (Arbre->LesBranches[n].valeur < 100000000000000000000.0)
				&& (Arbre->LesBranches[n].valeur > -100000000000000000000.0))
			requete += ", " + AnsiString(Arbre->LesBranches[n].valeur);
		else
			requete += ", null ";

		requete += ", " + IntToStr(Arbre->LesBranches[n].type);
		requete += ", " + IntToStr(Arbre->LesBranches[n].date);
		requete += ");";
		adoQuery->SQL->Clear();
		adoQuery->SQL->Add(requete);
		try {
			adoQuery->Prepared = true;
			adoQuery->ExecSQL(); // Open();
		} catch (Exception &e) {
			cpt++;
		}
	}
}
//--------------------------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriFormuleReseau(TADOTable *adoTable, int noAgri,
		int ident, int noItem, int idList, int noAn, CL_Reseau *Reseau) {
	CL_Reseau *reseau;
	AnsiString codereseau;
	AnsiString codebranchereseau;
	AnsiString apDreseau;
	AnsiString apGreseau;
	int mxM = -1;

	MajTable(adoTable, "Agri_FormuleReseau");

	reseau = Reseau;
	if (reseau != NULL) {
		if (mxM < reseau->MailleX)
			mxM = reseau->MailleX;

		for (int n = 0; n < reseau->MailleX; n++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			adoTable->FieldValues["NoAgri"] = noAgri;
			adoTable->FieldValues["NoFormule"] = ident;
			adoTable->FieldValues["NoItem"] = noItem;
			adoTable->FieldValues["IdList"] = idList;
			adoTable->FieldValues["NoAn"] = noAn;

			adoTable->FieldValues["nbrMaille"] = reseau->MailleX;
			adoTable->FieldValues["noMaille"] = n;
			adoTable->FieldValues["codeReseau"] = reseau->LesMailles[n].code;
			adoTable->FieldValues["codeBranche"] =
					reseau->LesMailles[n].branche;
			adoTable->FieldValues["apDreseau"] = reseau->LesMailles[n].apD;
			adoTable->FieldValues["apGreseau"] = reseau->LesMailles[n].apG;
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
		}

	}
}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriVariable(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri,
		TADOQuery *adoQuery) {
	int n, i, l;
	CL_Valeur *valeur;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_Valeur> *vValeur;
	AnsiString annee;
	int ident = 0;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		MajTable(adoTable, nomTable);

		valeur = new CL_Valeur();
		vValeur = agri->V_Variable;
		ident = 0;
		for (i = 0; i < vValeur->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			valeur = vValeur->Vecteur[i];
			adoTable->FieldValues["IdDefinitions"] = 11;
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = valeur->NoItem;
			adoTable->FieldValues["IdList"] = 10;
			adoTable->FieldValues["NoFormule"] = ident;
			ident++;
			for (l = 0; l < 10; l++) {
				AnsiString an = "An";
				annee = AnsiString(an + (l + 1));
				adoTable->FieldValues[annee] = valeur->Valeur[l];
			}
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriImmo(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_Immo *immo;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_Immo> *vImmo;

	MajTable(adoTable, nomTable);
	for (n = 0; n < vAgri->Nbelt; n++) {
		int id = 0;
		agri = vAgri->Vecteur[n];

		immo = new CL_Immo();

		vImmo = agri->V_Immo;
		for (i = 0; i < vImmo->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			immo = vImmo->Vecteur[i];
			adoTable->FieldValues["Nom"] = immo->Nom;
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = id;
			id++;
			adoTable->FieldValues["NoTva"] = immo->NoTva;
			adoTable->FieldValues["ValAchat"] = immo->ValAchat;
			adoTable->FieldValues["AAchat"] = immo->AAchat;
			adoTable->FieldValues["MAchat"] = immo->MAchat;
			adoTable->FieldValues["AVente"] = immo->AVente;
			adoTable->FieldValues["MVente"] = immo->MVente;
			adoTable->FieldValues["TypeAmor"] = immo->TypeAmor;
			adoTable->FieldValues["Duree"] = immo->Duree;
			adoTable->FieldValues["ValVente"] = immo->ValVente;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//immo finance global ou sommaire
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriXXXGlobal(TADOTable *adoTable,
		AnsiString nomTable, int nature, CL_Vecteur<CL_Agriculteur> *vAgri,
		TADOQuery *adoQuery) {
	int n, i, l;
	CL_FN_Xp1 *fN_Xp1;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_FN_Xp1> *vFN_Xp1;
	AnsiString annee;
	int ident;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		ident = 0;
		MajTable(adoTable, nomTable);

		fN_Xp1 = new CL_FN_Xp1();

		switch (nature) {
		case IMMO:
			vFN_Xp1 = agri->V_InvSom;
			for (i = 0; i < vFN_Xp1->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				fN_Xp1 = vFN_Xp1->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				//adoTable->FieldValues["NoItem"]=fN_Xp1->No;
				adoTable->FieldValues["NoItem"] = ident;
				ident++;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = fN_Xp1->Valeur[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;

		case FINANCE:
			vFN_Xp1 = agri->V_FinSom;
			for (i = 0; i < vFN_Xp1->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				fN_Xp1 = vFN_Xp1->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				//adoTable->FieldValues["NoItem"]=fN_Xp1->No;
				adoTable->FieldValues["NoItem"] = ident;
				ident++;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = fN_Xp1->Valeur[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriEmpCT(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_EmpCT *empCT;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_EmpCT> *vEmpCT;
	int ident;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		ident = 0;
		empCT = new CL_EmpCT();

		vEmpCT = agri->V_EmpCT;

		for (i = 0; i < vEmpCT->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			empCT = vEmpCT->Vecteur[i];

			adoTable->FieldValues["Nom"] = empCT->Nom;
			adoTable->FieldValues["NoAgri"] = agri->No;
			//adoTable->FieldValues["NoItem"]=empCT->No;
			adoTable->FieldValues["NoItem"] = ident;
			ident++;
			adoTable->FieldValues["Montant"] = empCT->Montant;
			adoTable->FieldValues["Taux"] = empCT->Taux;
			adoTable->FieldValues["Type"] = empCT->Type;
			adoTable->FieldValues["AReal"] = empCT->AReal;
			adoTable->FieldValues["MReal"] = empCT->MReal;
			adoTable->FieldValues["MRemb"] = empCT->MRemb;
			adoTable->FieldValues["ARemb"] = empCT->ARemb;
			adoTable->FieldValues["Pour"] = empCT->Pour;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriEmpLT(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_EmpLT *empLT;
	CL_Agriculteur *agri;
	CL_Vecteur<CL_EmpLT> *vEmpLT;
	int ident;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {

		ident = 0;
		agri = vAgri->Vecteur[n];

		vEmpLT = agri->V_EmpLT;

		empLT = new CL_EmpLT();

		for (i = 0; i < vEmpLT->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			empLT = vEmpLT->Vecteur[i];

			adoTable->FieldValues["Nom"] = empLT->Nom;
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = ident;
			ident++;
			// adoTable->FieldValues["NoItem"]=empLT->No;
			adoTable->FieldValues["Montant"] = empLT->Montant;
			adoTable->FieldValues["Duree"] = empLT->Duree;
			adoTable->FieldValues["Duree2"] = empLT->Duree2;
			adoTable->FieldValues["Taux"] = empLT->Taux;
			adoTable->FieldValues["Taux2"] = empLT->Taux2;
			adoTable->FieldValues["Type"] = empLT->Type;
			adoTable->FieldValues["AReal"] = empLT->AReal;
			adoTable->FieldValues["MReal"] = empLT->MReal;
			adoTable->FieldValues["ARemb"] = empLT->ARemb;
			adoTable->FieldValues["MRemb"] = empLT->MRemb;
			adoTable->FieldValues["Pour"] = empLT->Pour;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriSub(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_Agriculteur *agri;
	CL_Sub *sub;
	CL_Vecteur<CL_Sub> *vSub;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		vSub = agri->V_Sub;

		sub = new CL_Sub();

		for (i = 0; i < vSub->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			sub = vSub->Vecteur[i];

			adoTable->FieldValues["Nom"] = sub->Nom;
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = sub->No;
			adoTable->FieldValues["Montant"] = sub->Montant;
			adoTable->FieldValues["AReal"] = sub->AReal;
			adoTable->FieldValues["MReal"] = sub->MReal;
			adoTable->FieldValues["Duree"] = sub->Duree;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriPlact(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_Plact *plact;
	CL_Vecteur<CL_Plact> *vPlact;
	CL_Agriculteur *agri;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		vPlact = agri->V_Plact;

		plact = new CL_Plact();

		for (i = 0; i < vPlact->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			plact = vPlact->Vecteur[i];

			adoTable->FieldValues["Nom"] = plact->Nom;
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = plact->No;
			adoTable->FieldValues["Montant"] = plact->Montant;
			adoTable->FieldValues["Taux"] = plact->Taux;
			adoTable->FieldValues["Type"] = plact->Type;
			adoTable->FieldValues["AReal"] = plact->AReal;
			adoTable->FieldValues["MReal"] = plact->MReal;
			adoTable->FieldValues["ATerme"] = plact->ATerme;
			adoTable->FieldValues["MTerme"] = plact->MTerme;
			adoTable->FieldValues["Pour"] = plact->Pour;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriOccc(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;
	CL_Occc *occc;
	CL_Vecteur<CL_Occc> *vOccc;
	CL_Agriculteur *agri;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		vOccc = agri->V_Occc;

		occc = new CL_Occc();

		for (i = 0; i < vOccc->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			occc = vOccc->Vecteur[i];

			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["Ex"] = occc->Ex;
			adoTable->FieldValues["Montant"] = occc->Montant;
			adoTable->FieldValues["Taux"] = occc->Taux;
			adoTable->FieldValues["Pcent"] = occc->Pcent;
			adoTable->FieldValues["Frais"] = occc->Frais;
			adoTable->FieldValues["Année"] = agri->DefSim->An_0 + i;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}
//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriPetit(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i; //,l;
	CL_Petit *petit;
	CL_Vecteur<CL_Petit> *vPetit;
	CL_Agriculteur *agri;
	int ident;
	//AnsiString asTva, asValAchat;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		ident = 0;
		agri = vAgri->Vecteur[n];

		vPetit = agri->V_Petit;

		petit = new CL_Petit();

		for (i = 0; i < vPetit->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			petit = vPetit->Vecteur[i];

			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = ident;
			ident++;
			//adoTable->FieldValues["NoItem"]=petit->No;
			adoTable->FieldValues["ValAchat"] = petit->ValAchat;
			adoTable->FieldValues["NoTva"] = petit->NoTva;
			adoTable->FieldValues["Année"] = agri->DefSim->An_0 + i;
			//adoTable->FieldValues["NoRepart"]=petit->NoRepart;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriEnCours(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri, int nature) {
	int n, i;
	CL_EnCours *enCours;
	CL_Vecteur<CL_EnCours> *vEnCours;
	CL_Agriculteur *agri;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		enCours = new CL_EnCours();

		switch (nature) {
		case CREANCE:
			vEnCours = agri->V_Creance;
			for (i = 0; i < vEnCours->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				enCours = vEnCours->Vecteur[i];

				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = enCours->NoItem;
				adoTable->FieldValues["Valeur"] = enCours->Valeur;
				adoTable->FieldValues["APaie"] = enCours->APaie;
				adoTable->FieldValues["MPaie"] = enCours->MPaie;
				adoTable->FieldValues["NoFamille"] = enCours->NoFamille;
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;

		case DETTE:
			vEnCours = agri->V_Dette;
			for (i = 0; i < vEnCours->Nbelt; i++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				enCours = vEnCours->Vecteur[i];

				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = enCours->NoItem;
				adoTable->FieldValues["Valeur"] = enCours->Valeur;
				adoTable->FieldValues["APaie"] = enCours->APaie;
				adoTable->FieldValues["MPaie"] = enCours->MPaie;
				adoTable->FieldValues["NoFamille"] = enCours->NoFamille;
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
			break;
		}
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriStockIni(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri,
		TADOQuery *adoQuery) {
	int n, i, l;
	CL_StockIni *stockIni;
	CL_Vecteur<CL_StockIni> *vStockIni;
	CL_Agriculteur *agri;
	CL_Item item;
	AnsiString annee;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		stockIni = new CL_StockIni();

		vStockIni = agri->V_StockIni;

		for (i = 0; i < vStockIni->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			stockIni = vStockIni->Vecteur[i];
			for (l = 0; l < 10; l++) {
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = stockIni->Item[l].No;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = stockIni->Quantite[l];
				}
			}
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
			adoTable->Append();
			for (l = 0; l < 10; l++) {
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = stockIni->Item[l].No;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = stockIni->PrixRevient[l];
				}
			}
			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
				ShowMessage(e.Message);
			}
			ProgressBar1->StepIt();
		}
		//EcrireAnnee(adoTable,"Annee",agri->No,agri->DefSim->An_0);
	}

}

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriPolStock(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i;

	CL_PolStock *polStock;
	CL_Vecteur<CL_PolStock> *vPolStock;
	CL_Agriculteur *agri;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		polStock = new CL_PolStock();

		vPolStock = agri->V_PolStock;

		for (i = 0; i < vPolStock->Nbelt; i++) {
			try {
				adoTable->Append();
			} catch (Exception &e) {
			}

			polStock = vPolStock->Vecteur[i];

			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["NoItem"] = polStock->Item->No;
			adoTable->FieldValues["Prix"] = polStock->PcentDeltaPrix;
			adoTable->FieldValues["IdSysUnit"] = polStock->Item->NoSysteme;
			adoTable->FieldValues["PcentStock"] = polStock->PcentStock;
			adoTable->FieldValues["MaxiStockable"] = polStock->Maxi;
			//adoTable->FieldValues["PcentAugmentation"]=polStock->;
			adoTable->FieldValues["PcentDecote"] = polStock->PcentDecote;

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeau(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_Troupeau
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;
				adoTable->FieldValues["Reproducteur"] =
						(invAni->Reproducteur == 'O') ? 1 : 0;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();

			}

		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauEff(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		MajTable(adoTable, nomTable);
		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauEff
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X + 1; l++) {
					annee = AnsiString("AN") + AnsiString(l);
					adoTable->FieldValues[annee] = invAni->Effectif[l];

				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauVal(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		MajTable(adoTable, nomTable);
		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];
			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauVal
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X + 1; l++) {
					annee = AnsiString("AN") + AnsiString(l);
					adoTable->FieldValues[annee] = invAni->Valeur[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}
	}
}

//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauVente(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--Vente (0)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->Vente[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauAchat(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--Achat (1)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->Achat[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();

			}
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauValVente(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--ValVente (2)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->ValVente[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();
			}
		}
	}
}

//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauValAchat(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--ValAchat (3)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->ValAchat[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();

			}
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauEffMax(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--EffMax (4)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->EffMax[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();

			}
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauNoAtelier(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--NoAtelier (5)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->NoAtelier[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();

			}

		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauPVM(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--PrixVenteMoy (6)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X; l++) {
					annee = AnsiString("AN") + AnsiString(l + 1);
					adoTable->FieldValues[annee] = invAni->PrixVenteMoy[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();

			}
		}
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauVIM(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vInvAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			invAni = new CL_InvAni();
			vInvAni = troupeau->V_InvAni;

			for (i = 0; i < vInvAni->Nbelt; i++) {
				//--Agri_TroupeauBase
				//--ValInvMoy (7)
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				invAni = vInvAni->Vecteur[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = invAni->No;
				adoTable->FieldValues["NoAnimal"] = invAni->NoAnimal;

				for (l = 0; l < N_X + 1; l++) {
					annee = AnsiString("AN") + AnsiString(l);
					adoTable->FieldValues[annee] = invAni->ValInvMoy[l];
				}
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}

				ProgressBar1->StepIt();
			}
		}
	}
}

//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriTroupeauMvt(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	int n, i, l, m;

	CL_Agriculteur *agri;
	CL_Item item;
	CL_MvtAni *mvtAni;
	CL_Troupeau *troupeau;
	AnsiString annee;
	TList *lstTroupeaux;
	TList *lstMvtAni;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];
		MajTable(adoTable, nomTable);
		lstTroupeaux = agri->LstTroupeaux;

		for (m = 0; m < lstTroupeaux->Count; m++) {
			troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];

			lstMvtAni = troupeau->LstMvtAni;
			int ag = agri->No;
			int tr = troupeau->NoCatBestiaux;
			int nb = lstMvtAni->Count;

			//ShowMessage("ici agri: "+ IntToStr(ag) + " Tr: " +IntToStr(tr)+" NbMvt: "+IntToStr(nb));
			for (i = 0; i < lstMvtAni->Count; i++) {
				//--Agri_TroupeauMvt
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				mvtAni = (CL_MvtAni*) lstMvtAni->Items[i];
				adoTable->FieldValues["NoCatBestiau"] = troupeau->NoCatBestiaux;
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["Ligne"] = mvtAni->Ligne;
				adoTable->FieldValues["DateMvt"] = mvtAni->Date;
				adoTable->FieldValues["Type"] = mvtAni->Type;
				adoTable->FieldValues["Effectif"] = mvtAni->Eff;
				adoTable->FieldValues["Info"] = mvtAni->Info;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
				ProgressBar1->StepIt();
			}
		}
	}
}

//---------------Ensemble------------------------------------------------
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireEnsemble(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Ensemble> *vEnsemble) {
	CL_Ensemble *ensemble;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vEnsemble->Nbelt; n++) {
		ensemble = vEnsemble->Vecteur[n];

		try {
			adoTable->Append();
		} catch (Exception &e) {
		}

		adoTable->FieldValues["IdEnsemble"] = ensemble->No;
		adoTable->FieldValues["Nom"] = ensemble->Nom;
		adoTable->FieldValues["Notes"] = ensemble->Notes;
		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();

	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireEns_Eff(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Ensemble> *vEnsemble) {
	CL_Ensemble *ensemble;
	CL_Vecteur<CL_AgriEff> *vAgriEff;
	CL_AgriEff *agriEff;
	CL_Agriculteur *agri;

	int j, i;

	MajTable(adoTable, nomTable);

	for (i = 0; i < vEnsemble->Nbelt; i++) {
		ensemble = vEnsemble->Vecteur[i];
		vAgriEff = ensemble->V_AgriEff;
		for (j = 0; j < vAgriEff->Nbelt; j++) {
			agriEff = vAgriEff->Vecteur[j];

			agri = agriEff->Agri;

			try {
				adoTable->Append();
			} catch (Exception &e) {
			}
			adoTable->FieldValues["IdAgriEff"] = agriEff->No;
			adoTable->FieldValues["NoAgri"] = agri->No;
			adoTable->FieldValues["Nom"] = agriEff->Nom;
			adoTable->FieldValues["IdEnsemble"] = ensemble->No;
			adoTable->FieldValues["N_X_1"] = agriEff->Effectif[0];
			adoTable->FieldValues["N_X_2"] = agriEff->Effectif[1];
			adoTable->FieldValues["N_X_3"] = agriEff->Effectif[2];
			adoTable->FieldValues["N_X_4"] = agriEff->Effectif[3];
			adoTable->FieldValues["N_X_5"] = agriEff->Effectif[4];
			adoTable->FieldValues["N_X_6"] = agriEff->Effectif[5];
			adoTable->FieldValues["N_X_7"] = agriEff->Effectif[6];
			adoTable->FieldValues["N_X_8"] = agriEff->Effectif[7];
			adoTable->FieldValues["N_X_9"] = agriEff->Effectif[8];
			adoTable->FieldValues["N_X_10"] = agriEff->Effectif[9];

			try {
				adoTable->Post();
			} catch (Exception &e) {
				cpt++;
			}
			ProgressBar1->StepIt();
		}
	}
}
//---------------Pour les années, les phases, et les branches------------------------------------------------
//--------------------------------------------------------------------------
void TEcrireAccessFrm::RequeteTable(TADOQuery *adoQuery, AnsiString nomTable,
		AnsiString asPhase) {
	adoQuery->SQL->Clear();
	adoQuery->SQL->Add(
			"ALTER TABLE " + nomTable + " ADD " + asPhase + " DOUBLE");
	adoQuery->ExecSQL();

}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireProjet(TADOTable *adoTable, AnsiString nomTable,
		char file[MAXFILE]) {
	MajTable(adoTable, nomTable);

	try {
		adoTable->Append();
	} catch (Exception &e) {
	}
	adoTable->FieldValues["NomFichier"] = file;
	try {
		adoTable->Post();
	} catch (Exception &e) {
		cpt++;
	}
	ProgressBar1->StepIt();
}

//--------------------------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireIndicateur(TADOTable *adoTable,
		TADOQuery *adoQuery, AnsiString nomTable,
		CL_Vecteur<CL_Indicateur> *vIndic) {
	CL_Indicateur *indic;
	int maxbranche = 0;
	int maxmaille = 0;
	bool TestCompil;

	for (int n = 0; n < vIndic->Nbelt; n++) {
		indic = vIndic->Vecteur[n];
		//indic->No = n; !!!!!
		MajTable(adoTable, nomTable);
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}
		adoTable->FieldValues["IdDefinitions"] = 16;
		adoTable->FieldValues["NoIndic"] = indic->No;
		adoTable->FieldValues["Nom"] = indic->Nom;
		adoTable->FieldValues["NoCateg"] = indic->NoCategorie;
		adoTable->FieldValues["NoSys"] = indic->NoSysteme;
		adoTable->FieldValues["Notes"] = indic->Notes;
		adoTable->FieldValues["type"] = 0; //indic->type;
		if (indic->Prog->Arbre != NULL) {
			adoTable->FieldValues["nbBranche"] = indic->Prog->Arbre->BrancheX;
			if (indic->Prog->Arbre->BrancheX > maxbranche)
				maxbranche = indic->Prog->Arbre->BrancheX;

		}
		if (indic->Prog->Reseau != NULL) {
			adoTable->FieldValues["nbBoucle"] = indic->Prog->Reseau->MailleX;
			if (indic->Prog->Reseau->MailleX > maxmaille)
				maxmaille = indic->Prog->Reseau->MailleX;
		}
		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}

	}
	//ShowMessage("avant nbIndic=" +IntToStr(vIndic->Nbelt)+" MaxBranche="+IntToStr(maxbranche)+" maxMaille=" + IntToStr(maxmaille));
	EcrireArbre(adoTable, adoQuery, vIndic, maxbranche);
	EcrireReseau(adoTable, adoQuery, vIndic, maxmaille);

}

//--------------------------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireArbre(TADOTable *adoTable, TADOQuery *adoQuery,
		CL_Vecteur<CL_Indicateur> *vIndic, int brancheMax) {
	CL_Indicateur *indic;
	CL_Arbre *arbre;
	AnsiString codebranche;
	AnsiString arg1branche;
	AnsiString arg2branche;
	AnsiString arg3branche;
	AnsiString valeurbranche;
	AnsiString typebranche;
	AnsiString datebranche;
	int mxB = -1;

	for (int n = 0; n < vIndic->Nbelt; n++) {
		indic = vIndic->Vecteur[n];
		MajTable(adoTable, "Arbre");

		arbre = indic->Prog->Arbre;
		if (arbre != NULL) {
			if (mxB < arbre->BrancheX)
				mxB = arbre->BrancheX;

			for (int n = 0; n < arbre->BrancheX; n++) {
				try {
					adoTable->Append();
				} catch (Exception &e) {
				}

				adoTable->FieldValues["nbrBranche"] = arbre->BrancheX;
				adoTable->FieldValues["noIndic"] = indic->No;
				adoTable->FieldValues["noBranche"] = n;

				adoTable->FieldValues["code"] = arbre->LesBranches[n].code;
				adoTable->FieldValues["arg1"] = arbre->LesBranches[n].arg[0];
				adoTable->FieldValues["arg2"] = arbre->LesBranches[n].arg[1];
				adoTable->FieldValues["arg3"] = arbre->LesBranches[n].arg[2];
				adoTable->FieldValues["valeur"] = arbre->LesBranches[n].valeur;
				adoTable->FieldValues["type"] = arbre->LesBranches[n].type;
				adoTable->FieldValues["dateBranche"] =
						arbre->LesBranches[n].date;

				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------

void TEcrireAccessFrm::EcrireReseau(TADOTable *adoTable, TADOQuery *adoQuery,
		CL_Vecteur<CL_Indicateur> *vIndic, int mailleMax) {
	CL_Indicateur *indic;
	CL_Reseau *reseau;
	AnsiString codereseau;
	AnsiString codebranchereseau;
	AnsiString apDreseau;
	AnsiString apGreseau;
	int mxM = -1;

	for (int n = 0; n < vIndic->Nbelt; n++) {
		indic = vIndic->Vecteur[n];
		MajTable(adoTable, "Reseau");

		reseau = indic->Prog->Reseau;
		if (reseau != NULL) {
			if (mxM < reseau->MailleX)
				mxM = reseau->MailleX;

			for (int n = 0; n < reseau->MailleX; n++) {

				try {
					adoTable->Append();
				} catch (Exception &e) {
				}
				adoTable->FieldValues["nbrMaille"] = reseau->MailleX;
				adoTable->FieldValues["noIndic"] = indic->No;
				adoTable->FieldValues["noMaille"] = n;
				adoTable->FieldValues["codeReseau"] =
						reseau->LesMailles[n].code;
				adoTable->FieldValues["codeBranche"] =
						reseau->LesMailles[n].branche;
				adoTable->FieldValues["apDreseau"] = reseau->LesMailles[n].apD;
				adoTable->FieldValues["apGreseau"] = reseau->LesMailles[n].apG;
				try {
					adoTable->Post();
				} catch (Exception &e) {
					cpt++;
				}
			}

		}

	}

}
//----------------------------------
void TEcrireAccessFrm::EcrireConversion(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Conversion> *vConversion) {
	CL_Conversion *conversion;

	int n, i;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vConversion->Nbelt; n++) {
		conversion = vConversion->Vecteur[n];
		try {
			adoTable->Append();
		} catch (Exception &e) {
		}
		adoTable->FieldValues["IdConversion"] = conversion->No;
		adoTable->FieldValues["Nom"] = conversion->Nom;
		adoTable->FieldValues["NoBase"] = conversion->NoBase;
		adoTable->FieldValues["APartirDe"] = conversion->APartirDe;
		for (i = 0; i < N_X; i++) {
			AnsiString fve = "FVE" + (AnsiString)(i + 1);
			AnsiString evf = "EVF" + (AnsiString)(i + 1);
			adoTable->FieldValues[fve] = conversion->TauxConvFrancVersEuro[i];
			adoTable->FieldValues[evf] = conversion->TauxConvEuroVersFranc[i];
		}
		try {
			adoTable->Post();
		} catch (Exception &e) {
			cpt++;
		}
		ProgressBar1->StepIt();
	}
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::TexteChaine(void) {
	L_Remplace = T->TrouveTexte("EcrireAccessFrm", "L_Remplace");
	L_RemplaceAll = T->TrouveTexte("EcrireAccessFrm", "L_RemplaceAll");
}
//--------------------------------------------------------------------------
void TEcrireAccessFrm::TexteCaption(void) {
	LC_Encours = T->TrouveCaption("EcrireAccessFrm", "LC_Encours");
	LC_Enregistrer = T->TrouveCaption("Main", "LC_Enregistrersous");
}
//----------------------------------------------------------------------------

