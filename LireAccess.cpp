//---------------------------------------------------------------------------
//** Formulaire:: TLireAccessFrm
//**    Objet: Import des données Olympe via une base de données MS Access.
//**
//** Methode principale: LireFichier()
//**    Algorithme:
//**
//** Si Dialogue
//**    * affichage de la fenetre
//**
//**    * Creation des objets de gestion de la BDD
//**
//**    * Creation rapport
//**
//**    * Lecture linéaire de la base de données
//**       Pour instancier les objets correspondant.
//**       Structure semblable à FichierLire.cpp qui charge les données
//**       au format propriétaire.
//**
//**      * fermeture de la fenetre
//**
//** PS: la sauvegarde du fichier OLY est réalisée dans la méthode appelante
//**     de TMainForm (Main.cpp).
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//#include "DefVecteur.h"
#include "Main.h"
#include "FichierLire.h"
#include "AgriClasst.h"
#include "Requete.h"
#include "CL_Trad.h"
#include "CL_Matrice.h"

#include "LireAccess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLireAccessFrm *LireAccessFrm;
extern bool FichierLu;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLireAccessFrm::TLireAccessFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-----------Modifier le 18/08/2010 par william Rebaubier--------------------
//-----------Modifier le 06/2012 par Thierry Puch----------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::EcrireRapport(AnsiString info) {
	char chaine[100];
	ofstream outfile("ImportMdb.rap", ios::app);

	sprintf(chaine, "%s", TimeToStr(Now()));
	outfile << chaine << endl;
	sprintf(chaine, "%s", info);
	outfile << chaine << endl;
	outfile.close();
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireFichier(void) {
	AnsiString as;

	TADOQuery *adoQuery;
	TADOQuery *adoQuery1;
	TADOQuery *adoQuery2;

	AnsiString asProvider = "Provider=Microsoft.Jet.OLEDB.4.0;";
	AnsiString asUserId = "User ID=Admin;";
	AnsiString asDataSource;

	bool res;
	AnsiString nomfich;

	nomfich = ES->FEcriture;
	if (nomfich.Length() == 0) // si taille du nom du fichier estvide
			{
		ShowMessage("Définir d'abord le nom du fichier où stocker les données");
		MainForm->NouveauClick(this); // attente d'un nouveau clik
		nomfich = ES->FEcriture; // récupération du nom du fichier
		if (nomfich.Length() == 0) // si toujours nul on retourne rien ???
			return;
	}
	OpenDialog->Title = LC_Ouvrir;
	res = OpenDialog->Execute(); // ouvre fenêtre dialogue

	if (res == false)
		return;

	as = OpenDialog->FileName; // récupère nom fichier dans as
	asDataSource = AnsiString("Data Source=") + as; // créer un string avec "data source =" + le nom du fichier

	LireAccessFrm->Show();

	adoQuery = new TADOQuery(this);
	adoQuery1 = new TADOQuery(this);
	adoQuery2 = new TADOQuery(this);

	adoQuery->ConnectionString = asProvider + asUserId + asDataSource;
	adoQuery1->ConnectionString = asProvider + asUserId + asDataSource;
	adoQuery2->ConnectionString = asProvider + asUserId + asDataSource;

	//re-initialise le rapport
	ofstream outfile("ImportMdb.rap");
	outfile.close();

	EcrireRapport("Debut");
	try {

		EcrireRapport("LireSystemeUnite");
		LireSystemeUnite(adoQuery, V_SystemeUnite); //(1/1)
		ProgressBar->StepBy(1);

		EcrireRapport("LireTva");
		LireTva(adoQuery, V_Tva); //(2/2)

		EcrireRapport("R_DefCatProduit");
		LireR_Def_Categ(adoQuery, "R_DefCatProduit", V_CatProduit); //(3/3)

		EcrireRapport("R_DefCatCharge");
		LireR_Def_Categ(adoQuery, "R_DefCatCharge", V_CatCharge); //(4/5)

		EcrireRapport("R_DefCatExternalite");
		LireR_Def_Categ(adoQuery, "R_DefCatExternalite", V_CatExternalite); //(5/-) ????

		EcrireRapport("R_DefCatBestiaux");
		LireR_Def_Categ(adoQuery, "R_DefCatBestiaux", V_CatBestiaux); //(6/8)

		EcrireRapport("R_DefCatChStruct");
		LireR_Def_Categ(adoQuery, "R_DefCatChStruct", V_CatChStruct); //(7/13)

		EcrireRapport("R_DefCatRecDiv");
		LireR_Def_Categ(adoQuery, "R_DefCatRecDiv", V_CatRecDiv); //(10/14)

		EcrireRapport("R_DefCatDepDiv");
		LireR_Def_Categ(adoQuery, "R_DefCatDepDiv", V_CatDepDiv); //(8/15)

		EcrireRapport("R_DefCatRecFam");
		LireR_Def_Categ(adoQuery, "R_DefCatRecFam", V_CatRecFam); //(11/16)

		EcrireRapport("R_DefCatDepFam");
		LireR_Def_Categ(adoQuery, "R_DefCatDepFam", V_CatDepFam); //(9/17)

		EcrireRapport("R_DefCatClassif");
		LireR_Def_Categ(adoQuery, "R_DefCatClassif", V_CatTypeZone); //(12/30)

		EcrireRapport("R_DefCatVariable");
		LireR_Def_Categ(adoQuery, "R_DefCatVariable", V_CatVar); //(13/39)

		EcrireRapport("R_DefCatIndic");
		LireR_Def_Categ(adoQuery, "R_DefCatIndic", V_CatIndic); //(14/37)

		EcrireRapport("R_DefCatEtatSortie");
		LireR_Def_Categ(adoQuery, "R_DefCatEtatSortie", V_CatEtatSortie); //(15/33)

		EcrireRapport("R_DefCatSerieComp");
		LireR_Def_Categ(adoQuery, "R_DefCatSerieComp", V_CatSerieComp); //(16/35)

		EcrireRapport("R_DefCatRepart");
		LireR_Def_Categ(adoQuery, "R_DefCatRepart", V_CatRepart); //(16/35)

		EcrireRapport("R_DefItemProduit");
		LireR_Def_ProCha(adoQuery, "R_DefItemProduit", V_CatProduit, V_Produit); //(17/4)

		EcrireRapport("R_DefItemCharge");
		LireR_Def_ProCha(adoQuery, "R_DefItemCharge", V_CatCharge, V_Charge); //(18/6)

		EcrireRapport("R_DefItemExternalite");
		LireR_Def_ExtVar(adoQuery, "R_DefItemExternalite", V_CatExternalite,
				V_Externalite); //(19/7)

		EcrireRapport("R_DefItemVariable");
		LireR_Def_ExtVar(adoQuery, "R_DefItemVariable", V_CatVar, V_Variable); //(20/40)

		EcrireRapport("R_DefItemChStruct");
		LireR_Def_ChStructRecDep(adoQuery, "R_DefItemChStruct", V_CatChStruct,
				V_ChStruct); //(21/23)

		EcrireRapport("R_DefItemRecDiv");
		LireR_Def_ChStructRecDep(adoQuery, "R_DefItemRecDiv", V_CatRecDiv,
				V_RecDiv); //(22/24)

		EcrireRapport("R_DefItemDepDiv");
		LireR_Def_ChStructRecDep(adoQuery, "R_DefItemDepDiv", V_CatDepDiv,
				V_DepDiv); //(23/25)

		EcrireRapport("R_DefItemRecFam");
		LireR_Def_ChStructRecDep(adoQuery, "R_DefItemRecFam", V_CatRecFam,
				V_RecFam); //(24/26)

		EcrireRapport("R_DefItemDepFam");
		LireR_Def_ChStructRecDep(adoQuery, "R_DefItemDepFam", V_CatDepFam,
				V_DepFam); //(25/27)

		EcrireRapport("LireR_Def_Critere");
		LireR_Def_Critere(adoQuery, V_CatTypeZone, V_TypeZone); //(26/31)

		EcrireRapport("LireR_DefBestiaux");
		LireR_DefBestiaux(adoQuery); //(27/9)

		ProgressBar1->StepIt();
		ProgressBar->StepIt();
		EcrireRapport("LireR_DefCatCalendrier");
		LireR_DefCatCalendrier(adoQuery); //(61/53)

		EcrireRapport("LireR_DefCalendrier");
		LireR_DefCalendrier(adoQuery); //(62/53)

		EcrireRapport("V_CatTypeZone");
		//creer AgriClasstFrm->ChLBCatTypeZone
		// a mettre ailleurs
		CL_Categorie *categorie;
		AgriClasstFrm->ChLBCatTypeZone->Clear();
		for (int n = 0; n < V_CatTypeZone->Nbelt; n++) //(28) (????)
				{
			categorie = V_CatTypeZone->Vecteur[n];
			categorie->Flag = true;
			AgriClasstFrm->ChLBCatTypeZone->Items->AddObject(categorie->Nom,
					(TObject*) categorie);
		}

		EcrireRapport("R_AteCatCulture");
		LireR_Ate_CatAtelier(adoQuery, "R_AteCatCulture", V_CatCulture); //(29/10)

		EcrireRapport("R_AteCatAnimaux");
		LireR_Ate_CatAtelier(adoQuery, "R_AteCatAnimaux", V_CatAnimaux); //(30/11)

		EcrireRapport("LireR_Ate_CatPerenne");
		LireR_Ate_CatPerenne(adoQuery); //(31)

		EcrireRapport("R_AteCatVivrier");
		LireR_Ate_CatAtelier(adoQuery, "R_AteCatVivrier", V_CatVivrier); //(32/12)

		EcrireRapport("R_AteCulture");
		LireR_Ate_Atelier(adoQuery, "R_AteCulture", CULTURE, V_CatCulture,
				V_Culture); //(33/19)

		EcrireRapport("R_AteAnimaux");
		LireR_Ate_Atelier(adoQuery, "R_AteAnimaux", ANIMAUX, V_CatAnimaux,
				V_Animaux); //(34/20)

		EcrireRapport("LireR_Ate_Atelier");
		LireR_Ate_Atelier(adoQuery); //(35/21)

		EcrireRapport("R_AteVivrier");
		LireR_Ate_Atelier(adoQuery, "R_AteVivrier", VIVRIER, V_CatVivrier,
				V_Vivrier); //(36/22)

		EcrireRapport("R_AteItemCulture");
		LireR_Ate_Item(adoQuery, "R_AteItemCulture", V_Culture); //  23 juin 2009  problème //(37/19)

		EcrireRapport("R_AtePiedHaCulture");
		LireR_Ate_PiedHa(adoQuery, "R_AtePiedHaCulture", V_Culture);

		EcrireRapport("R_AteItemAnimaux");
		LireR_Ate_Item(adoQuery, "R_AteItemAnimaux", V_Animaux); //(38/20)
		EcrireRapport("R_AtePiedHaAnimaux");
		LireR_Ate_PiedHa(adoQuery, "R_AtePiedHaAnimaux", V_Animaux);

		EcrireRapport("R_AteItemPerenne");
		LireR_Ate_Item(adoQuery, "R_AteItemPerenne", V_Perenne); //(39/21)
		EcrireRapport("R_AtePiedHaPerenne");
		LireR_Ate_PiedHa(adoQuery, "R_AtePiedHaPerenne", V_Perenne);

		EcrireRapport("R_AteItemVivrier");
		LireR_Ate_Item(adoQuery, "R_AteItemVivrier", V_Vivrier); //(40/22)
		EcrireRapport("R_AtePiedHaVivrier");
		LireR_Ate_PiedHa(adoQuery, "R_AtePiedHaVivrier", V_Vivrier);

		EcrireRapport("LireR_Ate_BesTrav");
		LireR_Ate_BesTrav(adoQuery);

		EcrireRapport("LireR_Ate_Avance");
		LireR_Ate_Avance(adoQuery);

		EcrireRapport("LireR_Ate_Immo");
		LireR_Ate_Immo(adoQuery);

		EcrireRapport("AdresseChFVol");
		AdresseChFVol(V_Culture); //(41/58)
		AdresseChFVol(V_Animaux); //(42/58)
		AdresseChFVol(V_Perenne); //(43/58)
		AdresseChFVol(V_Vivrier); //(44/58)

		EcrireRapport("LireR_AleaCateg");
		LireR_AleaCateg(adoQuery); //(59/43-52)

		EcrireRapport("LireR_AleaItem");
		LireR_AleaItem(adoQuery); //(60/43-52)                                               //(60/43-52)

		EcrireRapport("LireR_Repart");
		LireR_Repart(adoQuery, adoQuery1);

		//
		ProgressBar1->StepIt();
		ProgressBar->StepIt();
		// Agriculteur

		EcrireRapport("LireR_Agri");
		LireR_Agri(adoQuery); //(45/56)

		EcrireRapport("LireR_Agri_DefSim");
		LireR_Agri_DefSim(adoQuery); //(46/56b)

		EcrireRapport("LireR_Agri_Critere");
		LireR_Agri_Critere(adoQuery); //(47/56a)

		EcrireRapport("R_Agri_Assol");
		LireR_AgriAssol(adoQuery, "R_Agri_Assol", CULTURE); //(48/56c)

		EcrireRapport("R_Agri_Animaux");
		LireR_AgriAssol(adoQuery, "R_Agri_Animaux", ANIMAUX); //(49/56d)

		EcrireRapport("R_Agri_Perenne");
		LireR_AgriPerenne(adoQuery, "R_Agri_Perenne", PERENNE); //(50/ ???? 56/f)

		EcrireRapport("R_Agri_Vivrier");
		LireR_AgriPerenne(adoQuery, "R_Agri_Vivrier", VIVRIER); //(51/56g)

		EcrireRapport("R_Agri_FormuleProduit");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleProduit",
				PRODUIT); //(52/56i)

		EcrireRapport("R_Agri_FormuleCharge");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleCharge", CHARGE); //(53/56j)

		EcrireRapport("R_Agri_FormuleChStruct");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleChStruct",
				CHSTRUCT); //(54/56k)

		EcrireRapport("R_Agri_FormuleRecDiv");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleRecDiv", RECDIV); //(55/56l)

		EcrireRapport("R_Agri_FormuleDepDiv");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleDepDiv", DEPDIV); //(56/56m)

		EcrireRapport("R_Agri_FormuleRecFam");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleRecFam", RECFAM); //(57/56n)

		EcrireRapport("R_Agri_FormuleDepFam");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleDepFam", DEPFAM); //(58/56o)

		EcrireRapport("R_Agri_FormuleExtPos");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleExtPos", EXTPOS);

		EcrireRapport("R_Agri_FormuleExtNeg");
		LireR_AgriFormule(adoQuery, adoQuery1, "R_Agri_FormuleExtNeg", EXTNEG);

		//!!!!!!! V_CatDico (/41)
		//!!!!!!! V_Dico (/42)
		ProgressBar1->StepIt();
		ProgressBar->StepIt();
		EcrireRapport("LireR_AgriVariable");
		LireR_AgriVariable(adoQuery); //(63/56h)
		//180808

		EcrireRapport("LireR_AgriImmo");
		LireR_AgriImmo(adoQuery); //(64/56w)

		EcrireRapport("LireR_AgriXXXGlobal");
		LireR_AgriXXXGlobal(adoQuery, "R_Agri_ImmoGlobal", IMMO); //(65)

		EcrireRapport("LireR_AgriEmpCT");
		LireR_AgriEmpCT(adoQuery); //(66/56s)

		EcrireRapport("LireR_AgriEmpLT");
		LireR_AgriEmpLT(adoQuery); //(67/56r)

		EcrireRapport("LireR_AgriXXXGlobal");
		LireR_AgriXXXGlobal(adoQuery, "R_Agri_FinanceGlobal", FINANCE); //(68)

		EcrireRapport("LireR_AgriSub");
		LireR_AgriSub(adoQuery); //(69/56t)

		EcrireRapport("LireR_Ensemble");
		LireR_Ensemble(adoQuery); //(70/57)

		EcrireRapport("LireR_EnsEff");
		LireR_EnsEff(adoQuery); //(71/57)

		EcrireRapport("LireR_AgriEnCoursDette");
		LireR_AgriEnCoursDette(adoQuery); //(72/56aa)

		EcrireRapport("LireR_AgriEnCoursCreance");
		LireR_AgriEnCoursCreance(adoQuery); //(73/56ab)

		EcrireRapport("LireR_AgriOccc");
		LireR_AgriOccc(adoQuery); //(74)

		EcrireRapport("LireR_AgriPetit");
		LireR_AgriPetit(adoQuery); //(75)    //  23 juin 2009 problème car Damien a fait présentation différente de la table

		EcrireRapport("LireR_AgriPlact");
		LireR_AgriPlact(adoQuery); //(76)

		EcrireRapport("LireR_AgriStockIni");
		LireR_AgriStockIni(adoQuery); //(77/56ad)

		EcrireRapport("LireR_AgriPolStock");
		LireR_AgriPolStock(adoQuery); //(78/56ac)
		ProgressBar1->StepIt();
		ProgressBar->StepIt();
		//--TP2012
		EcrireRapport("LireR_AgriTroupeau");
		LireR_AgriTroupeau(adoQuery, adoQuery1, adoQuery2); //56e

		EcrireRapport("LireR_AgriTroupeauMVT");
		LireR_AgriTroupeauMVT(adoQuery); //56e

		EcrireRapport("LireR_AgriRepartItem");
		LireR_AgriRepartItem(adoQuery); //56e
		//

		EcrireRapport("LireR_DefSerieComp");
		LireR_DefSerieComp(adoQuery, adoQuery1); //(80/36)

		EcrireRapport("LireR_DefEtatSortie");
		LireR_DefEtatSortie(adoQuery, adoQuery1); //(79/34)

		EcrireRapport("LireR_Indicateur");
		LireR_Indicateur(adoQuery); //(81/38)

		EcrireRapport("LireR_DefConversion");
		LireR_DefConversion(adoQuery); //(82/53a)

		ProgressBar1->StepIt();
		ProgressBar->StepIt();
		FichierLu = true;
		EcrireRapport("Fin Lecure");

		EcrireRapport("VerifNumeroAgri");
		ES->VerifNumeroAgri();

		//ShowMessage(L_Termine);

		EcrireRapport("LesAdresses");
		ES->LesAdresses();

		EcrireRapport("IniV_Elt");
		ES->IniV_Elt();

		ImpElt();
		ProgressBar1->StepIt();
		ProgressBar->StepIt();

		//ES->Supprimable();
		EcrireRapport("Fin");

	} catch (const AnsiString &e) {
		ShowMessage(e);
	}

	// a faire emprunts, matériel

	LireAccessFrm->Close();
}
//--------------
void TLireAccessFrm::ImpElt(void) {
	CL_Elt *elt;
	char chaine[100];
	ofstream outfile("exportElt.txt");

	for (int i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		sprintf(chaine, "%3d Elt %3d - %3d - %3d", i, elt->NoFamille,
				elt->NoCategorie, elt->NoItem);
		outfile << chaine << endl;
	}

	outfile.close();

}
//---------------------------------------------------------------------------
void TLireAccessFrm::MajTable(TADOTable *adoTable, AnsiString nomTable) {
	adoTable->Active = false;
	adoTable->TableName = nomTable;
	adoTable->Active = true;
	adoTable->Open();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireSystemeUnite(TADOQuery *adoQuery,
		CL_Vecteur<CL_SystemeUnite> *vecteur) {
	CL_SystemeUnite *sysUnit;
	String coche;
	vecteur->purge();
	// MajTable(adoTable,nomTable);
	if (requete_R_SystemeUnite(adoQuery)) {
		// adoTable->First();
		adoQuery->First();
		// while(!adoTable->Eof)
		while (!adoQuery->Eof) {
			sysUnit = new CL_SystemeUnite();
			sysUnit->No = adoQuery->FieldByName("IdSysUnit")->AsString.ToInt();

			sysUnit->UUt = adoQuery->FieldByName("UAte")->AsString;
			sysUnit->UTrans = adoQuery->FieldByName("UEnt")->AsString;
			sysUnit->UGlobal = adoQuery->FieldByName("UGlobal")->AsString;

			sysUnit->Ratio =
					adoQuery->FieldByName("Ratio21")->AsString.ToDouble();
			sysUnit->RatioG =
					adoQuery->FieldByName("Ratio32")->AsString.ToDouble();

			coche = adoQuery->FieldByName("Monnaie")->AsString;
			if (coche == "Vrai") {
				sysUnit->Monnaie = 'O';
				SysMonnaie = sysUnit;
				SysMonnaie->Monnaie = 'O';
			} else {
				sysUnit->Monnaie = 'N';
			}
			vecteur->insSans(sysUnit);

			adoQuery->Next();
		}
		//!!   pour compléter lire acces inutile
		if (SysMonnaie == NULL) {
			SysMonnaie = vecteur->Vecteur[0];
			SysMonnaie->Monnaie = 'N';
		}
	}
}
//----------------------------------------------------------------------------
void TLireAccessFrm::LireTva(TADOQuery *adoQuery, CL_Vecteur<CL_Tva> *vecteur) {
	CL_Tva *tva;
	String coche;

	vecteur->purge();

	if (requete_R_Tva(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			tva = new CL_Tva();

			tva->No = adoQuery->FieldByName("IdTva")->AsString.ToInt();
			tva->Nom = adoQuery->FieldByName("Nom")->AsString;
			tva->Taux = adoQuery->FieldByName("Taux")->AsString.ToDouble();

			coche = adoQuery->FieldByName("Defaut")->AsString;
			if (coche == "Vrai")
				TvaDefaut = tva;
			coche = adoQuery->FieldByName("Immo")->AsString;
			if (coche == "Vrai")
				TvaImmo = tva;

			vecteur->insSans(tva);

			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_Categ(TADOQuery *adoQuery, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	AnsiString as, asMessage;
	CL_Categorie *categorie;
	bool verif = true;

	vCategorie->purge();
	if (nomTable == "R_DefCatProduit")
		verif = requete_R_DefCatProduit(adoQuery);
	if (nomTable == "R_DefCatCharge")
		verif = requete_R_DefCatCharge(adoQuery);
	if (nomTable == "R_DefCatExternalite")
		verif = requete_R_DefCatExternalite(adoQuery);
	if (nomTable == "R_DefCatBestiaux")
		verif = requete_R_DefCatBestiaux(adoQuery);
	if (nomTable == "R_DefCatChStruct")
		verif = requete_R_DefCatChStruct(adoQuery);
	if (nomTable == "R_DefCatDepDiv")
		verif = requete_R_DefCatDepDiv(adoQuery);
	if (nomTable == "R_DefCatDepFam")
		verif = requete_R_DefCatDepFam(adoQuery);
	if (nomTable == "R_DefCatRecDiv")
		verif = requete_R_DefCatRecDiv(adoQuery);
	if (nomTable == "R_DefCatRecFam")
		verif = requete_R_DefCatRecFam(adoQuery);
	if (nomTable == "R_DefCatClassif")
		verif = requete_R_DefCatClassif(adoQuery);
	if (nomTable == "R_DefCatVariable")
		verif = requete_R_DefCatVariable(adoQuery);
	if (nomTable == "R_DefCatIndic")
		verif = requete_R_DefCatIndic(adoQuery);
	if (nomTable == "R_DefCatEtatSortie")
		verif = requete_R_DefCatEtatSortie(adoQuery);
	if (nomTable == "R_DefCatSerieComp")
		verif = requete_R_DefCatSerieComp(adoQuery);
	if (nomTable == "R_DefCatRepart")
		verif = requete_R_DefCatRepart(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			categorie = new CL_Categorie();
			categorie->No =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			categorie->Nom = adoQuery->FieldByName("Nom")->AsString;
			categorie->Notes = adoQuery->FieldByName("Notes")->AsString;
			vCategorie->insSans(categorie);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_ProCha(TADOQuery *adoQuery, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_Item> *vItem) {
	AnsiString as, asMessage;
	CL_Item *item;
	bool verif = true;

	vItem->purge();
	if (nomTable == "R_DefItemProduit")
		verif = requete_R_DefItemProduit(adoQuery);
	if (nomTable == "R_DefItemCharge")
		verif = requete_R_DefItemCharge(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			item = new CL_Item();

			item->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			item->Categorie = vCategorie->trouve(item->NoCategorie);

			item->No = adoQuery->FieldByName("IdDefItem")->AsString.ToInt();
			item->Nom = adoQuery->FieldByName("Nom")->AsString;

			item->NoSysteme =
					adoQuery->FieldByName("IdSysUnit")->AsString.ToInt();
			item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);

			item->Prix = adoQuery->FieldByName("Prix")->AsString.ToDouble();

			item->NoTva = adoQuery->FieldByName("IdTva")->AsString.ToInt();
			item->Tva = V_Tva->trouve(item->NoTva);
			vItem->insSans(item);

			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_ExtVar(TADOQuery *adoQuery, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_Item> *vItem) {
	AnsiString as, asMessage;
	CL_Item *item;
	bool verif = true;

	vItem->purge();
	if (nomTable == "R_DefItemExternalite")
		verif = requete_R_DefItemExternalite(adoQuery);
	if (nomTable == "R_DefItemVariable")
		verif = requete_R_DefItemVariable(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			item = new CL_Item();

			item->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			item->Categorie = vCategorie->trouve(item->NoCategorie);

			item->No = adoQuery->FieldByName("IdDefItem")->AsString.ToInt();
			item->Nom = adoQuery->FieldByName("Nom")->AsString;

			item->NoSysteme =
					adoQuery->FieldByName("IdSysUnit")->AsString.ToInt();
			item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);
			vItem->insSans(item);

			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_ChStructRecDep(TADOQuery *adoQuery,
		AnsiString nomTable, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_Item> *vItem) {
	AnsiString as, asMessage;
	CL_Item *item;
	bool verif = true;

	vItem->purge();

	if (nomTable == "R_DefItemChStruct")
		verif = requete_R_DefItemChStruct(adoQuery);
	if (nomTable == "R_DefItemRecDiv")
		verif = requete_R_DefItemRecDiv(adoQuery);
	if (nomTable == "R_DefItemDepDiv")
		verif = requete_R_DefItemDepDiv(adoQuery);
	if (nomTable == "R_DefItemRecFam")
		verif = requete_R_DefItemRecFam(adoQuery);
	if (nomTable == "R_DefItemDepFam")
		verif = requete_R_DefItemDepFam(adoQuery);

	if (verif) {

		adoQuery->First();
		while (!adoQuery->Eof) {
			item = new CL_Item();
			item->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			item->Categorie = vCategorie->trouve(item->NoCategorie);

			item->No = adoQuery->FieldByName("IdDefItem")->AsString.ToInt();
			item->Nom = adoQuery->FieldByName("Nom")->AsString;
			item->NoTva = adoQuery->FieldByName("IdTva")->AsString.ToInt();
			item->Tva = V_Tva->trouve(item->NoTva);
			vItem->insSans(item);

			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_Critere(TADOQuery *adoQuery,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_Item> *vItem) {
	AnsiString as, asMessage;
	CL_Item *item;

	vItem->purge();

	if (requete_R_DefCritere(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			item = new CL_Item();
			item->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			item->Categorie = vCategorie->trouve(item->NoCategorie);

			item->No = adoQuery->FieldByName("IdDefItem")->AsString.ToInt();
			item->Nom = adoQuery->FieldByName("Nom")->AsString;
			vItem->insSans(item);

			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_CatAtelier(TADOQuery *adoQuery,
		AnsiString nomTable, CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Categorie *categorie;
	bool verif = true;
	vCategorie->purge();
	if (nomTable == "R_AteCatCulture")
		verif = requete_R_AteCatCulture(adoQuery);
	if (nomTable == "R_AteCatAnimaux")
		verif = requete_R_AteCatAnimaux(adoQuery);
	if (nomTable == "R_AteCatVivrier")
		verif = requete_R_AteCatVivrier(adoQuery);
	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			categorie = new CL_Categorie();
			categorie->No =
					adoQuery->FieldByName("IdAteCateg")->AsString.ToInt();
			categorie->Nom = adoQuery->FieldByName("Nom")->AsString;
			vCategorie->insSans(categorie);

			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
// en fait LireEspece
void TLireAccessFrm::LireR_Ate_CatPerenne(TADOQuery *adoQuery) {
	CL_Espece *espece;
	int i;
	AnsiString as, asPhase;
	V_Espece->purge();

	if (requete_R_AteCatPerenne(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			espece = new CL_Espece();
			espece->No = adoQuery->FieldByName("IdAteCateg")->AsString.ToInt();
			espece->Nom = adoQuery->FieldByName("Nom")->AsString;
			//       espece->Notes=adoTable->FieldByName("Notes")->AsString;
			espece->DebAmor =
					adoQuery->FieldByName("DebAmor")->AsString.ToInt();
			espece->DurAmor =
					adoQuery->FieldByName("DurAmor")->AsString.ToInt();
			espece->NbPhase =
					adoQuery->FieldByName("NbPhase")->AsString.ToInt();
			for (i = 0; i < espece->NbPhase; i++) {
				asPhase = AnsiString("Ph") + (i + 1);
				as = adoQuery->FieldByName(asPhase)->AsString;
				if (as.Length() == 0)
					continue;
				espece->Phase[i] =
						adoQuery->FieldByName(asPhase)->AsString.ToDouble();
			}

			V_Espece->insSans(espece);

			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_DefBestiaux(TADOQuery *adoQuery) {
	CL_Bestiaux *bestiaux;

	V_Bestiaux->purge();
	if (requete_R_DefBestiaux(adoQuery)) {
		adoQuery->First();

		while (!adoQuery->Eof) {
			bestiaux = new CL_Bestiaux();
			bestiaux->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			bestiaux->NoTva = adoQuery->FieldByName("IdTva")->AsString.ToInt();
			bestiaux->No =
					adoQuery->FieldByName("IdBestiaux")->AsString.ToInt();
			bestiaux->Nom = adoQuery->FieldByName("Nom")->AsString;
			bestiaux->NoOrigine =
					adoQuery->FieldByName("IdOrigine")->AsString.ToInt();
			bestiaux->Prix = adoQuery->FieldByName("Prix")->AsString.ToDouble();
			bestiaux->ValInv =
					adoQuery->FieldByName("Vallnv")->AsString.ToDouble();
			bestiaux->DonneNo[0] =
					adoQuery->FieldByName("Donne1")->AsString.ToInt();
			bestiaux->DonneNo[1] =
					adoQuery->FieldByName("Donne2")->AsString.ToInt();
			bestiaux->DonneNo[2] =
					adoQuery->FieldByName("Donne3")->AsString.ToInt();
			bestiaux->DonneNo[3] =
					adoQuery->FieldByName("Donne4")->AsString.ToInt();
			bestiaux->DonnePcent[0] =
					adoQuery->FieldByName("DonnePcent1")->AsString.ToDouble();
			bestiaux->DonnePcent[1] =
					adoQuery->FieldByName("DonnePcent2")->AsString.ToDouble();
			bestiaux->DonnePcent[2] =
					adoQuery->FieldByName("DonnePcent3")->AsString.ToDouble();
			bestiaux->DonnePcent[3] =
					adoQuery->FieldByName("DonnePcent4")->AsString.ToDouble();
			bestiaux->Categorie = V_CatBestiaux->trouve(bestiaux->NoCategorie);
			bestiaux->Tva = V_Tva->trouve(bestiaux->NoTva);
			V_Bestiaux->insSans(bestiaux);
			adoQuery->Next();

		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Avance(TADOQuery *adoQuery) {
	AnsiString as;
	CL_Atelier *atelier;
	CL_Vecteur<CL_EEF> *vecteur;
	CL_EEF* eEF;

	int _idAteliers, _idAteSousCateg;
	int _moisDebut, _moisFin;
	float _aValeur;

	if (requete_R_AteAvance(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {

			_idAteliers = adoQuery->FieldByName("IdAteliers")->AsString.ToInt();
			_idAteSousCateg =
					adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt();

			_moisDebut = adoQuery->FieldByName("Debut")->AsString.ToInt();
			_moisFin = adoQuery->FieldByName("Fin")->AsString.ToInt();
			_aValeur = adoQuery->FieldByName("Valeur")->AsString.ToDouble();

			if (_idAteliers == 1) //CULTURES
					{
				atelier = V_Culture->trouve(_idAteSousCateg);
			}
			if (_idAteliers == 2) //ANIMAUX
					{
				atelier = V_Animaux->trouve(_idAteSousCateg);
			}
			if (_idAteliers == 3) //PERENNES
					{
				atelier = V_Perenne->trouve(_idAteSousCateg);
			}
			if (_idAteliers == 4) //VIVRIER
					{
				atelier = V_Vivrier->trouve(_idAteSousCateg);
			}

			vecteur = atelier->V_Avance;

			eEF = new CL_EEF();
			eEF->Deb = _moisDebut;
			eEF->Fin = _moisFin;
			eEF->Val = _aValeur;

			vecteur->ins(eEF);

			adoQuery->Next();

		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Immo(TADOQuery *adoQuery) {
	AnsiString as;
	CL_Atelier *atelier;

	int _idAteliers, _idAteSousCateg;
	int _idList;
	int i;
	float _aValeur;
	AnsiString asPhase;

	if (requete_R_AteImmo(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {

			_idAteliers = adoQuery->FieldByName("IdAteliers")->AsString.ToInt();
			_idAteSousCateg =
					adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt();

			_idList = adoQuery->FieldByName("IdList")->AsString.ToInt();

			if (_idAteliers == 1) //CULTURES
					{
				atelier = V_Culture->trouve(_idAteSousCateg);
			}
			if (_idAteliers == 2) //ANIMAUX
					{
				atelier = V_Animaux->trouve(_idAteSousCateg);
			}
			if (_idAteliers == 3) //PERENNES
					{
				atelier = V_Perenne->trouve(_idAteSousCateg);
			}
			if (_idAteliers == 4) //VIVRIER
					{
				atelier = V_Vivrier->trouve(_idAteSousCateg);
			}

			if (_idList == 6) {
				atelier->PImmoExiste = true;
				atelier->ProdImmo = new float[atelier->NbPhase];
			}
			if (_idList == 7) {
				atelier->PImmoFamExiste = true;
				atelier->ProdImmoFam = new float[atelier->NbPhase];
			}
			for (i = 0; i < atelier->NbPhase; i++) {
				asPhase = AnsiString("Ph") + i;
				if (adoQuery->FieldByName(asPhase)->AsString != "") {
					_aValeur =
							adoQuery->FieldByName(asPhase)->AsString.ToDouble();
					if (_idList == 6) {
						atelier->ProdImmo[i] = _aValeur;
					}
					if (_idList == 7) {
						atelier->ProdImmoFam[i] = _aValeur;
					}
				}
			}

			adoQuery->Next();

		}
	}
}
//------------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_BesTrav(TADOQuery *adoQuery) {
	AnsiString as;
	CL_Atelier *atelier;
	CL_Vecteur<CL_BesTrav> *vecteur;
	CL_BesTrav *besTrav;
	bool estIdentique = false;
	int _idAteliers, _idAteSousCateg;
	int _nbPhase, _nbPeriodeCal;
	int _idDefCateg;
	int _iX, _jX, k;
	double _valeur;

	if (requete_R_AteBesTrav(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			_idAteliers = adoQuery->FieldByName("IdAteliers")->AsString.ToInt();
			_idAteSousCateg =
					adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt();
			_nbPhase = adoQuery->FieldByName("NbPhase")->AsString.ToInt();
			_nbPeriodeCal =
					adoQuery->FieldByName("NbPeriodeCal")->AsString.ToInt();
			_idDefCateg = adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();

			if (!estIdentique) {
				if (_idAteliers == 1) //CULTURES
						{
					atelier = V_Culture->trouve(_idAteSousCateg);
				}
				if (_idAteliers == 2) //ANIMAUX
						{
					atelier = V_Animaux->trouve(_idAteSousCateg);
				}
				if (_idAteliers == 3) //PERENNES
						{
					atelier = V_Perenne->trouve(_idAteSousCateg);
				}
				if (_idAteliers == 4) //VIVRIER
						{
					atelier = V_Vivrier->trouve(_idAteSousCateg);
				}

				vecteur = atelier->V_BesTrav;

				//besTrav=new CL_BesTrav(_nbPhase, V_Calendrier->trouve(_idDefCateg));

				besTrav = new CL_BesTrav();
				besTrav->NbPhase = _nbPhase;
				besTrav->Calendrier = V_Calendrier->trouve(_idDefCateg);
				besTrav->No = besTrav->Calendrier->No;
				besTrav->NbPeriodeCal = _nbPeriodeCal;
				besTrav->Besoins = new CL_Matrice(_nbPeriodeCal, _nbPhase);

				estIdentique = True;
				while ((!adoQuery->Eof) && (estIdentique)) {
					//LireR_Ate_BesTrav_Item(adoQuery1, _idAteliers, _idAteSousCateg, _idDefCateg, _nbPeriodeCal, besTrav->Besoins);

					_iX = adoQuery->FieldByName("iX")->AsString.ToInt();
					_jX = adoQuery->FieldByName("jX")->AsString.ToInt();
					_valeur =
							adoQuery->FieldByName("Valeur")->AsString.ToDouble();
					k = _iX + (_jX * _nbPeriodeCal);

					besTrav->Besoins->X[k] = _valeur;

					adoQuery->Next();

					estIdentique =
							(_idAteliers
									== adoQuery->FieldByName("IdAteliers")->AsString.ToInt())
									&& (_idAteSousCateg
											== adoQuery->FieldByName(
													"IdAteSousCateg")->AsString.ToInt())
									&& (_nbPhase
											== adoQuery->FieldByName("NbPhase")->AsString.ToInt())
									&& (_nbPeriodeCal
											== adoQuery->FieldByName(
													"NbPeriodeCal")->AsString.ToInt())
									&& (_idDefCateg
											== adoQuery->FieldByName(
													"IdDefCateg")->AsString.ToInt());

				}
				vecteur->insSans(besTrav);
			}
		}
	}
}
//---------------------------------------------------------------------------
/*void TLireAccessFrm::LireR_Ate_BesTrav(TADOQuery *adoQuery, TADOQuery *adoQuery1)
 {
 AnsiString as;
 CL_Atelier *atelier;
 CL_Vecteur<CL_BesTrav> *vecteur;
 CL_BesTrav *besTrav;

 int _idAteliers, _idAteSousCateg;
 int _nbPhase, _nbPeriodeCal;
 int _idDefCateg;

 if  (requete_R_AteBesTrav(adoQuery))
 {
 adoQuery->First();
 while(!adoQuery->Eof)
 {
 _idAteliers=adoQuery->FieldByName("IdAteliers")->AsString.ToInt();
 _idAteSousCateg=adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt();
 _nbPhase=adoQuery->FieldByName("NbPhase")->AsString.ToInt();
 _nbPeriodeCal=adoQuery->FieldByName("NbPeriodeCal")->AsString.ToInt();
 _idDefCateg=adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();

 if (_idAteliers==1) //CULTURES
 {
 atelier=V_Culture->trouve(_idAteSousCateg);
 }
 if (_idAteliers==2) //ANIMAUX
 {
 atelier=V_Animaux->trouve(_idAteSousCateg);
 }
 if (_idAteliers==3) //PERENNES
 {
 atelier=V_Perenne->trouve(_idAteSousCateg);
 }
 if (_idAteliers==4) //VIVRIER
 {
 atelier=V_Vivrier->trouve(_idAteSousCateg);
 }

 vecteur=atelier->V_BesTrav;

 besTrav=new CL_BesTrav(_nbPhase, V_Calendrier->trouve(_idDefCateg));

 besTrav->Besoins=new CL_Matrice(besTrav->NbPeriodeCal,besTrav->NbPhase);

 //LireR_Ate_BesTrav_Item(adoQuery1, _idAteliers, _idAteSousCateg, _idDefCateg, _nbPeriodeCal, besTrav->Besoins);

 vecteur->insSans(besTrav);

 adoQuery->Next();

 }
 }
 }

 //---------------------------------------------------------------------------
 void TLireAccessFrm::LireR_Ate_BesTrav_Item(TADOQuery *adoQuery, int _idAteliers, int _idAteSousCateg, int _idDefCateg, int _nbPeriodeCal, CL_Matrice *besoins)
 {
 AnsiString as;
 int _iX,_jX, k;
 double _valeur;


 if  (requete_R_AteBesTravItem(adoQuery, _idAteliers, _idAteSousCateg, _idDefCateg))
 {
 adoQuery->First();
 while(!adoQuery->Eof)
 {
 _iX=adoQuery->FieldByName("iX")->AsString.ToInt();
 _jX=adoQuery->FieldByName("jX")->AsString.ToInt();
 _valeur=adoQuery->FieldByName("Valeur")->AsString.ToDouble();
 k=_iX+(_jX*_nbPeriodeCal);

 besoins->X[k]=_valeur;

 adoQuery->Next();
 }
 adoQuery->Close();
 }
 }
 */
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Atelier(TADOQuery *adoQuery, AnsiString nomTable,
		int nature, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	AnsiString as;
	int n;
	bool verif = true;
	//CL_Categorie *categorie;
	CL_Atelier *atelier;

	if (nomTable == "R_AteCulture")
		verif = requete_R_AteCulture(adoQuery);
	if (nomTable == "R_AteAnimaux")
		verif = requete_R_AteAnimaux(adoQuery);
	if (nomTable == "R_AteVivrier")
		verif = requete_R_AteVivrier(adoQuery);

	vAtelier->purge();
	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			atelier = new CL_Atelier();
			atelier->Nature = nature;
			atelier->No =
					adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt();
			atelier->Nom = adoQuery->FieldByName("Nom")->AsString;
			atelier->Notes = adoQuery->FieldByName("Notes")->AsString;
			atelier->NoCategorie =
					adoQuery->FieldByName("IdAteCateg")->AsString.ToInt();
			atelier->Categorie = vCategorie->trouve(atelier->NoCategorie);
			if (nature == VIVRIER)
				atelier->NbPhase = 5;
			else
				atelier->NbPhase = 3;
			n = adoQuery->FieldByName("Derobe")->AsString.ToInt();
			if (n == 1)
				atelier->Derobe = true;
			else
				atelier->Derobe = false;

			//n=adoQuery->FieldByName("PImmoExiste")->AsString.ToInt();
			//n=adoQuery->FieldByName("PImmoFamExiste")->AsString.ToInt();
			if (nature == ANIMAUX) {
				if (adoQuery->FieldByName("ValInvRepro")->AsString != "")
					atelier->ValInvRepro =
							adoQuery->FieldByName("ValInvRepro")->AsString.ToDouble();
				if (adoQuery->FieldByName("ValInvAutre")->AsString != "")
					atelier->ValInvAutre =
							adoQuery->FieldByName("ValInvAutre")->AsString.ToDouble();
			}

			vAtelier->insSans(atelier);

			adoQuery->Next();

		}
	}
}
//perennes
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Atelier(TADOQuery *adoQuery) {
	AnsiString as;
	//float val;
	int n;
	//CL_Categorie *categorie;
	CL_Atelier *atelier;

	V_Perenne->purge();
	if (requete_R_AtePerenne(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			atelier = new CL_Atelier();
			atelier->Nature = 3;
			atelier->No =
					adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt();
			atelier->Nom = adoQuery->FieldByName("Nom")->AsString;
			atelier->Notes = adoQuery->FieldByName("Notes")->AsString;
			atelier->NoEspece =
					adoQuery->FieldByName("IdAteCateg")->AsString.ToInt();
			atelier->Espece = V_Espece->trouve(atelier->NoEspece);
			atelier->NbPhase = atelier->Espece->NbPhase + 1;
			atelier->DebAmor = atelier->Espece->DebAmor;
			atelier->DurAmor = atelier->Espece->DurAmor;

			n = adoQuery->FieldByName("Derobe")->AsString.ToInt();
			if (n == 1)
				atelier->Derobe = true;
			else
				atelier->Derobe = false;

			n = adoQuery->FieldByName("PImmoExiste")->AsString.ToInt();
			if (n == 1)
				atelier->PImmoExiste = false; //true;
			// a faire
			//atelier->PImmoExiste  il y a un vecteur de atelier->NbPhase
			else
				atelier->PImmoExiste = false;

			n = adoQuery->FieldByName("PImmoFamExiste")->AsString.ToInt();
			if (n == 1)
				atelier->PImmoFamExiste = true;
			else
				atelier->PImmoFamExiste = false;

			atelier->ValInvRepro =
					adoQuery->FieldByName("ValInvRepro")->AsString.ToInt();
			atelier->ValInvAutre =
					adoQuery->FieldByName("ValInvAutre")->AsString.ToInt();

			V_Perenne->insSans(atelier);

			adoQuery->Next();

		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Item(TADOQuery *adoQuery, AnsiString nomTable,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	AnsiString as, asPhase;
	//int i;//,n;
	int noList, noAtel;
	bool verif = true;
	//float val[N_PHASE];
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_Vecteur<CL_Item> *vItem;
	CL_ItemParAtelier *itemPA;
	CL_Vecteur<CL_EEF> *vecteurAvance;
	CL_EEF *eef;

	if (nomTable == "R_AteItemCulture")
		verif = requete_R_AteItemCulture(adoQuery);
	if (nomTable == "R_AteItemAnimaux")
		verif = requete_R_AteItemAnimaux(adoQuery);
	if (nomTable == "R_AteItemPerenne")
		verif = requete_R_AteItemPerenne(adoQuery);
	if (nomTable == "R_AteItemVivrier")
		verif = requete_R_AteItemVivrier(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			itemPA = new CL_ItemParAtelier();
			eef = new CL_EEF();
			//atelier
			noAtel = adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt(); //090709
			atelier = vAtelier->trouve(noAtel);

			// Produit charge chargeVol etc..
			noList = adoQuery->FieldByName("IdList")->AsString.ToInt();
			switch (noList) {
			case 1:
				vecteurIPA = atelier->V_Produit;
				break;
			case 2:
				vecteurIPA = atelier->V_Charge;
				break;
			case 3:
				vecteurIPA = atelier->V_ChargeVolume;
				break;
			case 4:
				vecteurIPA = atelier->V_Externalite;
				break;
				//case 5:vecteurAvance=atelier->V_Avance;break;
				//case 10:vecteurIPA=atelier->V_ProdPied;break;
				//case 11:vecteurIPA=atelier->V_ChPied;break;
				// A VOIR 9 pied/ha float PiedHa[N_PHASE]
			}
			//item:
			switch (noList) {
			case 1: //Produit
			case 2: //Charge
			case 4: // Externalite
				switch (noList) {
				case 1:
					vItem = V_Produit;
					break;
				case 2:
					vItem = V_Charge;
					break;
				case 4:
					vItem = V_Externalite;
					break;
				}
				itemPA->NoItem =
						adoQuery->FieldByName("C1IdDefItem")->AsString.ToInt();
				itemPA->Item = vItem->trouve(itemPA->NoItem);
				itemPA->QtePhase = new float[atelier->NbPhase];
				LireQtePhase(adoQuery, atelier->NbPhase, itemPA->QtePhase);
				vecteurIPA->insSans(itemPA);
				break;
			case 3: //  ch f vol
				// produit
				itemPA->NoItem =
						adoQuery->FieldByName("C1IdDefItem")->AsString.ToInt();
				itemPA->Item = V_Produit->trouve(itemPA->NoItem);
				// Charge
				itemPA->NoCharge =
						adoQuery->FieldByName("C3IdDefItem")->AsString.ToInt();
				itemPA->Charge = V_Charge->trouve(itemPA->NoCharge);
				itemPA->QtePhase = new float[atelier->NbPhase];
				LireQtePhase(adoQuery, atelier->NbPhase, itemPA->QtePhase);
				vecteurIPA->insSans(itemPA);
				break;
				//case 5: eef->Deb = adoQuery->FieldByName("Ph0")->AsString.ToDouble();
				//        eef->Fin = adoQuery->FieldByName("Ph1")->AsString.ToDouble();
				//        eef->Val = adoQuery->FieldByName("Ph2")->AsString.ToDouble();
				//        vecteurAvance->insSans(eef);
				//        break;
			case 10: // Prod/Pied
			case 11: // Charge/Pied

				switch (noList) {
				case 10:
					vItem = V_Produit;
					break;
				case 11:
					vItem = V_Charge;
					break;
				}
				itemPA->NoItem =
						adoQuery->FieldByName("C1IdDefItem")->AsString.ToInt();
				itemPA->Item = vItem->trouve(itemPA->NoItem);
				itemPA->QtePhase = new float[atelier->NbPhase];
				LireQtePhase(adoQuery, atelier->NbPhase, itemPA->QtePhase);
				vecteurIPA->insSans(itemPA);
				break;
				//case 9 :
				//            for(int i=0;i<atelier->NbPhase;i++)
				//            {
				//                    asPhase=AnsiString("Ph")+i;
				//                    if (adoQuery->FieldByName(asPhase)->AsString != "")
				//                    atelier->PiedHa[i]= adoQuery->FieldByName(asPhase)->AsString.ToDouble();
				//            }
				//            break;
			}
			adoQuery->Next();

		}
	}
}
//----------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_PiedHa(TADOQuery *adoQuery, AnsiString nomTable,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	AnsiString as, asPhase;
	//int i;//,n;
	int noList, noAtel;
	bool verif = true;
	//float val[N_PHASE];
	CL_Atelier *atelier;

	if (nomTable == "R_AtePiedHaCulture")
		verif = requete_R_AtePiedHaCulture(adoQuery);
	if (nomTable == "R_AtePiedHaAnimaux")
		verif = requete_R_AtePiedHaAnimaux(adoQuery);
	if (nomTable == "R_AtePiedHaPerenne")
		verif = requete_R_AtePiedHaPerenne(adoQuery);
	if (nomTable == "R_AtePiedHaVivrier")
		verif = requete_R_AtePiedHaVivrier(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			//atelier
			noAtel = adoQuery->FieldByName("IdAteSousCateg")->AsString.ToInt(); //090709
			atelier = vAtelier->trouve(noAtel);

			noList = adoQuery->FieldByName("IdList")->AsString.ToInt();

			switch (noList) {
			case 9:

				for (int i = 0; i < atelier->NbPhase; i++) {
					asPhase = AnsiString("Ph") + i;
					if (adoQuery->FieldByName(asPhase)->AsString != "")
						atelier->PiedHa[i] =
								adoQuery->FieldByName(asPhase)->AsString.ToDouble();
				}
				break;
			}
			adoQuery->Next();

		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireQtePhase(TADOQuery *adoQuery, int nbPhase,
		float *qtePhase) {
	int i;
	AnsiString as, asPhase;
	for (i = 0; i < nbPhase; i++)
		qtePhase[i] = 0.;
	for (i = 0; i < nbPhase; i++) {
		asPhase = AnsiString("Ph") + i;
		as = adoQuery->FieldByName(asPhase)->AsString;
		if (as.Length() == 0)
			continue;
		qtePhase[i] = adoQuery->FieldByName(asPhase)->AsString.ToDouble();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::AdresseChFVol(CL_Vecteur<CL_Atelier> *vAtelier) {
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
//---------------------------------------------------------------------------
//------------------------Agri-----------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Agri(TADOQuery *adoQuery) {
	// agri est l'agriculteur récupérer de la requête
	CL_Agriculteur *agri;
	// agri Père représente l'origine de agri
	CL_Agriculteur *agriPere;

	CL_Agriculteur *ItemAgri;
	// agri frère représente ,dans le cas ou il y a une série de plus de 20 ans,
	// un agriculteur d'une autre décénie de agri
	ST_NoAgri *agriFils;
	ST_NoAgri *agriFrere;
	// permet de créer les différents item de la liste
	ST_NoAgri *noAgri;
	// numéro courant de l'origine de la variance
	int origineVar = 0;
	// numéro courant de l'origine de la série
	int origineSerie = 0;
	int noVariante = 0;
	//int numagri=0;
	//int nbsimul=0;
	// remet a null tout les élement du vecteur agriculteur
	V_Agriculteur->purge();
	// permet de séléctionné les résultats de la requête Agriculteur
	if (requete_R_Agri(adoQuery)) {
		// on sélectionne le premier agriculteur
		adoQuery->First();
		// on exécute tous les éléments de cette boucle tant qu'il éxiste des agriculteurs dans la requète
		while (!adoQuery->Eof) {
			// si il existe déja un agriculteur dans le vecteur avec le même id on le sélectionne
			agri = new CL_Agriculteur();
			// on récupère les information de la requète qu'on ajoute dans une classe agriculteur
			agri->No = adoQuery->FieldByName("IdAgri")->AsString.ToInt();
			agri->Nom = adoQuery->FieldByName("Nom")->AsString;
			agri->Notes = adoQuery->FieldByName("Notes")->AsString;
			agri->NoSerie = adoQuery->FieldByName("NoSerie")->AsString.ToInt();
			agri->DefSim->NbAnSim =
					adoQuery->FieldByName("NbAnSim")->AsString.ToInt();
			agri->DefSim->An_0 =
					adoQuery->FieldByName("An_0")->AsString.ToInt();
			if (agri->DefSim->NbAnSim > 10) {
				agri->LstSerie = new TList();
				for (int i = 0; i < agri->DefSim->NbAnSim / 10; i++)
					agri->LstSerie->Add(NULL);
			}
			V_Agriculteur->insSans(agri);
			adoQuery->Next();

		}
	}

	if (requete_R_Agri(adoQuery)) {
		// on sélectionne le premier agriculteur
		adoQuery->First();
		// on exécute tous les éléments de cette boucle tant qu'il éxiste des agriculteurs dans la requète
		while (!adoQuery->Eof) {
			if ((adoQuery->FieldByName("OrSerie")->AsString == "")
					&& (adoQuery->FieldByName("OrVar")->AsString != "")) {
				agri = V_Agriculteur->trouve(
						adoQuery->FieldByName("IdAgri")->AsString.ToInt());
				int origineVar =
						adoQuery->FieldByName("OrVar")->AsString.ToInt();
				// on trouve l'agriculteur à l'origine de la variante
				// si il est null on le créer  pour pouvoir le réutiliser
				agri->EstVariante = true;
				agriPere = V_Agriculteur->trouve(origineVar);
				// on ajoute son numéro de variance qui est le nombre d'élément variant
				agri->NoVariante =
						adoQuery->FieldByName("NoVariante")->AsString.ToInt();
				// on initialise un numéro agri qui permet de stocker un numéro et son adresse
				noAgri = new ST_NoAgri();
				noAgri->No = agri->No;
				noAgri->Agri = agri;
				// on insert l'agri dans la liste variant du père
				agriPere->LstVariante->Add(noAgri);
				// on ajoute 1 au nombre de variante
				agriPere->NbVariante += 1;
				agri->Pere = agriPere;
			}

			if ((adoQuery->FieldByName("OrSerie")->AsString != "")
					&& (adoQuery->FieldByName("OrVar")->AsString == "")) {
				agri = V_Agriculteur->trouve(
						adoQuery->FieldByName("IdAgri")->AsString.ToInt());
				int origineSerie =
						adoQuery->FieldByName("OrSerie")->AsString.ToInt();
				agri->EstPlus10Ans = true;
				agriPere = V_Agriculteur->trouve(origineSerie);
				noAgri = new ST_NoAgri();
				noAgri->No = agri->No;
				noAgri->Agri = agri;
				agriPere->LstSerie->Delete(agri->NoSerie);
				agriPere->LstSerie->Insert(agri->NoSerie, noAgri);

				noAgri = new ST_NoAgri();
				noAgri->No = agriPere->No;
				noAgri->Agri = agriPere;
				agriPere->LstSerie->Delete(agriPere->NoSerie);
				agriPere->LstSerie->Insert(agriPere->NoSerie, noAgri);

				for (int i = 1; i < agriPere->LstSerie->Count; i++) {
					noAgri = (ST_NoAgri*) agriPere->LstSerie->Items[i];
					if (noAgri != NULL) {
						ItemAgri = noAgri->Agri;
						for (int j = 0; j < ItemAgri->LstSerie->Count; j++) {
							ItemAgri->LstSerie->Delete(j);
							ItemAgri->LstSerie->Insert(j,
									(ST_NoAgri*) agriPere->LstSerie->Items[j]);
						}
					}
				}
			}

			adoQuery->Next();
		}

	}
}

//---------------------------------------------------------------------------
TLireAccessFrm::heritage(CL_Agriculteur *agri) {
	int parent;

	if (agri->EstVariante)
		parent = heritage(agri->Pere);
	else
		parent = agri->No;

	return parent;
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Agri_DefSim(TADOQuery *adoQuery) {
	CL_Agriculteur *agri;
	int noAgri;
	AnsiString chaine;

	if (requete_R_Agri_DefSim(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri != NULL) {
				agri->DefSim->No = noAgri;
				agri->DefSim->An_0 =
						adoQuery->FieldByName("An_0")->AsString.ToInt();
				agri->DefSim->NbAnSim =
						adoQuery->FieldByName("NbanSim")->AsString.ToInt();
				agri->DefSim->MDeb =
						adoQuery->FieldByName("MDeb")->AsString.ToInt();
				agri->DefSim->AnCalage =
						adoQuery->FieldByName("AnCalage")->AsString.ToInt();
				agri->DefSim->TypeAlea =
						adoQuery->FieldByName("TypeAlea")->AsString.ToInt();
				agri->DefSim->NoPrixProd =
						adoQuery->FieldByName("NoPrixProd")->AsString.ToInt();
				agri->DefSim->NoPrixCharge = adoQuery->FieldByName(
						"NoPrixCharge")->AsString.ToInt();
				agri->DefSim->NoQProd =
						adoQuery->FieldByName("NoQprod")->AsString.ToInt();
				agri->DefSim->NoQCharge =
						adoQuery->FieldByName("NoQCharge")->AsString.ToInt();
				agri->DefSim->NoQExt =
						adoQuery->FieldByName("NoQExt")->AsString.ToInt();
				agri->DefSim->TouSPrixProd = adoQuery->FieldByName(
						"TouSPrixProd")->AsString.ToInt();
				agri->DefSim->TouSPrixCharge = adoQuery->FieldByName(
						"TouSPrixCharge")->AsString.ToInt();
				agri->DefSim->TouSQProd =
						adoQuery->FieldByName("TouSQProd")->AsString.ToInt();
				agri->DefSim->TouSQCharge =
						adoQuery->FieldByName("TouSQCharge")->AsString.ToInt();
				agri->DefSim->TouSQExt =
						adoQuery->FieldByName("TouSQExt")->AsString.ToInt();

				ES->TrouveTendScen(agri->DefSim);

				chaine = adoQuery->FieldByName("Chaine")->AsString;
				strcpy(agri->DefSim->Enchainement, chaine.c_str());
			}
			adoQuery->Next();
		}
	}

}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriEnCoursDette(TADOQuery *adoQuery) {
	CL_EnCours *enCours;
	//CL_Vecteur<CL_EnCours> *vEnCours;
	CL_Agriculteur *agri;
	//CL_Item *item;
	CL_Vecteur<CL_Item> *vItem;
	int noAgri = 0;

	if (requete_R_Agri_EnCoursDette(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri != NULL) {
				enCours = new CL_EnCours();

				enCours->NoItem =
						adoQuery->FieldByName("NoItem")->AsString.ToInt();
				enCours->NoFamille =
						adoQuery->FieldByName("NoFamille")->AsString.ToInt();
				switch (enCours->NoFamille) {
				case PRODUIT:
					vItem = V_Produit;
					break;
				case CHARGE:
					vItem = V_Charge;
					break;
				case CHSTRUCT:
					vItem = V_ChStruct;
					break;
				case DEPDIV:
					vItem = V_DepDiv;
					break;
				case RECDIV:
					vItem = V_RecDiv;
					break;
				default:
					ShowMessage("adresseAgriCreanceDette Oubli");
				}
				enCours->Item = vItem->trouve(enCours->NoItem);
				enCours->Valeur =
						adoQuery->FieldByName("Valeur")->AsString.ToDouble();
				enCours->APaie =
						adoQuery->FieldByName("APaie")->AsString.ToInt();
				enCours->MPaie =
						adoQuery->FieldByName("MPaie")->AsString.ToInt();
				agri->V_Dette->insSans(enCours);

			}
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriEnCoursCreance(TADOQuery *adoQuery) {
	CL_EnCours *enCours;
	//CL_Vecteur<CL_EnCours> *vEnCours;
	CL_Agriculteur *agri;
	//CL_Item *item;
	CL_Vecteur<CL_Item> *vItem;
	int noAgri = 0;

	if (requete_R_Agri_EnCoursCreance(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri != NULL) {
				enCours = new CL_EnCours();

				enCours->NoItem =
						adoQuery->FieldByName("NoItem")->AsString.ToInt();
				enCours->NoFamille =
						adoQuery->FieldByName("NoFamille")->AsString.ToInt();
				switch (enCours->NoFamille) {
				case PRODUIT:
					vItem = V_Produit;
					break;
				case CHARGE:
					vItem = V_Charge;
					break;
				case CHSTRUCT:
					vItem = V_ChStruct;
					break;
				case DEPDIV:
					vItem = V_DepDiv;
					break;
				case RECDIV:
					vItem = V_RecDiv;
					break;
				default:
					ShowMessage("adresseAgriCreanceDette Oubli");
				}
				enCours->Item = vItem->trouve(enCours->NoItem);
				enCours->Valeur =
						adoQuery->FieldByName("Valeur")->AsString.ToDouble();
				enCours->APaie =
						adoQuery->FieldByName("APaie")->AsString.ToInt();
				enCours->MPaie =
						adoQuery->FieldByName("MPaie")->AsString.ToInt();
				agri->V_Creance->insSans(enCours);

			}
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Agri_Critere(TADOQuery *adoQuery) {
	int noAgri;
	CL_Agriculteur *agri;
	int noCritere;
	CL_Item *critere;

	if (requete_R_Agri_Critere(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri == NULL)
				return;
			noCritere = adoQuery->FieldByName("IdDefItem")->AsString.ToInt();
			critere = V_TypeZone->trouve(noCritere);
			agri->LstCritere->Add(critere);
			adoQuery->Next();
		}
	}
	return;
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriAssol(TADOQuery *adoQuery, AnsiString nomTable,
		int nature) {
	int noAgri;
	int noAtelier;

	CL_Agriculteur *agri;
	CL_Atelier *atelier;
	CL_Valeur *valeur;
	bool verif = true;
	if (nomTable == "R_Agri_Assol")
		verif = requete_R_Agri_Assol(adoQuery);

	if (nomTable == "R_Agri_Animaux")
		verif = requete_R_Agri_Animaux(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri == NULL)
				return;
			noAtelier =
					adoQuery->FieldByName("NoAteSousCateg")->AsString.ToInt();
			switch (nature) {
			case CULTURE:
				atelier = V_Culture->trouve(noAtelier);
				break;
			case ANIMAUX:
				atelier = V_Animaux->trouve(noAtelier);
				break;
			}
			valeur = new CL_Valeur();
			valeur->NoAtelier = noAtelier;
			valeur->Atelier = atelier;
			valeur->No = adoQuery->FieldByName("NoItem")->AsString.ToInt();
			LireValeur(adoQuery, valeur->Valeur);
			switch (nature) {
			case CULTURE:
				agri->V_Culture->insSans(valeur);
				break;
			case ANIMAUX:
				agri->V_Animaux->insSans(valeur);
				break;
			}
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriPerenne(TADOQuery *adoQuery, AnsiString nomTable,
		int nature) {
	int noAgri;
	int noAtelier;
	bool verif = true;
	AnsiString asAnArr;

	CL_Agriculteur *agri;
	CL_Atelier *atelier;
	CL_Verger *verger;

	if (nomTable == "R_Agri_Perenne")
		verif = requete_R_Agri_Perenne(adoQuery);
	if (nomTable == "R_Agri_Vivrier")
		verif = requete_R_Agri_Vivrier(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri == NULL)
				return;

			noAtelier =
					adoQuery->FieldByName("NoAteSousCateg")->AsString.ToInt();
			//??    	noAtelier=adoTable->FieldByName("NoAtel")->AsString.ToInt();
			switch (nature) {
			case PERENNE:
				atelier = V_Perenne->trouve(noAtelier);
				break;
			case VIVRIER:
				atelier = V_Vivrier->trouve(noAtelier);
				break;
			}
			asAnArr = AnsiString("Duree");
			verger = new CL_Verger();
			verger->NoAtelier = noAtelier;
			verger->Atelier = atelier;
			if (nature == PERENNE) {
				verger->Espece = atelier->Espece;
				verger->NoEspece = verger->Espece->No;
				asAnArr = AnsiString("AnArr");
			}
			verger->AnPlant =
					adoQuery->FieldByName("AnPlant")->AsString.ToInt();
			verger->AnArr = adoQuery->FieldByName(asAnArr)->AsString.ToInt();
			verger->Surface =
					adoQuery->FieldByName("Surface")->AsString.ToDouble();

			//        LireValeur(adoTable,valeur->Valeur);

			switch (nature) {
			case PERENNE:
				agri->V_Verger->insSans(verger);
				break;
			case VIVRIER:
				agri->V_Vivrier->insSans(verger);
				;
				break;
			}

			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireValeur(TADOQuery *adoQuery, float *valeur, int nbVal) {
	int i;
	AnsiString as, asAn;
	for (i = 0; i < nbVal; i++)
		valeur[i] = 0.;
	for (i = 0; i < nbVal; i++) {
		asAn = AnsiString("An") + AnsiString(i + 1);
		//   as=adoTable->FieldByName(asAn)->AsString;
		as = adoQuery->FieldByName(asAn)->AsString;
		if (as.Length() == 0)
			continue;
		valeur[i] = adoQuery->FieldByName(asAn)->AsString.ToDouble();
		// valeur[i]=adoTable->FieldByName(asAn)->AsString.ToDouble();
	}

}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriFormule(TADOQuery *adoQuery,
		TADOQuery *adoQuery1, AnsiString nomTable, int nature) {
	int n;
	int noAgri;
	int noItem;
	int ident;
	bool verif = true;
	CL_Agriculteur *agri;
	CL_Item *item;
	CL_Formule *formule;
	CL_Prog *prog;
	CL_Arbre *Arbre;
	char origine;
	ST_Branche *branche;
	AnsiString asFormule;
	AnsiString sTemp;
	int nx, _noAn;

	if (nomTable == "R_Agri_FormuleProduit")
		verif = requete_R_Agri_FormuleProduit(adoQuery);
	if (nomTable == "R_Agri_FormuleCharge")
		verif = requete_R_Agri_FormuleCharge(adoQuery);
	if (nomTable == "R_Agri_FormuleChStruct")
		verif = requete_R_Agri_FormuleChStruct(adoQuery);
	if (nomTable == "R_Agri_FormuleRecDiv")
		verif = requete_R_Agri_FormuleRecDiv(adoQuery);
	if (nomTable == "R_Agri_FormuleDepDiv")
		verif = requete_R_Agri_FormuleDepDiv(adoQuery);
	if (nomTable == "R_Agri_FormuleRecFam")
		verif = requete_R_Agri_FormuleRecFam(adoQuery);
	if (nomTable == "R_Agri_FormuleDepFam")
		verif = requete_R_Agri_FormuleDepFam(adoQuery);
	if (nomTable == "R_Agri_FormuleExtPos")
		verif = requete_R_Agri_FormuleExtPos(adoQuery);
	if (nomTable == "R_Agri_FormuleExtNeg")
		verif = requete_R_Agri_FormuleExtNeg(adoQuery);

	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			if (agri == NULL)
				return;

			noItem = adoQuery->FieldByName("NoItem")->AsString.ToInt();
			ident = adoQuery->FieldByName("NoFormule")->AsString.ToInt();
			origine = adoQuery->FieldByName("Origine")->AsString.ToInt(); //AsString pas ok
			switch (nature) {
			case PRODUIT:
				item = V_Produit->trouve(noItem);
				break;
			case CHARGE:
				item = V_Charge->trouve(noItem);
				break;
			case CHSTRUCT:
				item = V_ChStruct->trouve(noItem);
				break;
			case RECDIV:
				item = V_RecDiv->trouve(noItem);
				break;
			case RECFAM:
				item = V_RecFam->trouve(noItem);
				break;
			case DEPDIV:
				item = V_DepDiv->trouve(noItem);
				break;
			case DEPFAM:
				item = V_DepFam->trouve(noItem);
				break;
			case EXTPOS:
				item = V_Externalite->trouve(noItem);
				break;
			case EXTNEG:
				item = V_Externalite->trouve(noItem);
				break;
			}
			formule = new CL_Formule();
			formule->Item = item;
			formule->No = noItem; //020908
			formule->Origine = origine; //090708
			formule->NoFamille = nature; //170709
			// a tester
			/*
			 asFormule=adoTable->FieldByName("An1")->AsString;
			 ErreurFrm->Edit->Clear();
			 Compil->Erreur=false;
			 Compil->Compiler(asFormule.c_str());
			 if(Compil->Erreur==true)return false;//il y a erreur et c'est affiché



			 */
			LireValeur(adoQuery, formule->Valeur);

			switch (nature) {
			case PRODUIT:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 1);
				break;
			case CHARGE:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 2);
				break;
			case CHSTRUCT:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 3);
				break;
			case RECDIV:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 4);
				break;
			case RECFAM:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 6);
				break;
			case DEPDIV:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 5);
				break;
			case DEPFAM:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 7);
				break;
			case EXTPOS:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 8);
				break;
			case EXTNEG:
				verif = requete_R_Agri_FormuleArbre(adoQuery1, noAgri, ident,
						noItem, 9);
				break;
			}

			if (verif) {
				adoQuery1->First();
				if (!adoQuery1->Eof) {

					//for(int i=0;i<N_X;i++)
					while (!adoQuery1->Eof) {
						_noAn =
								adoQuery1->FieldByName("NoAn")->AsString.ToInt();
						nx =
								adoQuery1->FieldByName("nbrBranche")->AsString.ToInt();
						prog = new CL_Prog();
						Arbre = new CL_Arbre(nx, 10);
						Arbre->BrancheX = nx;

						for (int n = 0; n < nx; n++) {
							Arbre->LesBranches[n].code = adoQuery1->FieldByName(
									"code")->AsString.ToInt();
							Arbre->LesBranches[n].arg[0] =
									adoQuery1->FieldByName("arg1")->AsString.ToInt();
							Arbre->LesBranches[n].arg[1] =
									adoQuery1->FieldByName("arg2")->AsString.ToInt();
							Arbre->LesBranches[n].arg[2] =
									adoQuery1->FieldByName("arg3")->AsString.ToInt();
							try {
								sTemp =
										adoQuery1->FieldByName("valeur")->AsString;
								if (sTemp.data() != NULL)
									Arbre->LesBranches[n].valeur =
											adoQuery1->FieldByName("valeur")->AsString.ToDouble();
							} catch (Exception &e) {
								Arbre->LesBranches[n].valeur = NULL;
							}
							Arbre->LesBranches[n].type = adoQuery1->FieldByName(
									"type")->AsString.ToInt();
							Arbre->LesBranches[n].date = adoQuery1->FieldByName(
									"datebranche")->AsString.ToInt();
							adoQuery1->Next();
						}

						prog->Arbre = Arbre;
						formule->LesProg[_noAn] = prog;
					}
				} else { //Pas d'arbre alors constitution d'un arbre par default avec Valeur

					for (int n = 0; n < N_X; n++) {
						prog = new CL_Prog();
						Arbre = new CL_Arbre();
						Arbre->LesBranches[0].code = 301; //NOMBRE
						Arbre->BrancheX = 1;
						for (int j = 0; j < 3; j++)
							Arbre->LesBranches[0].arg[j] = -1;
						Arbre->LesBranches[0].valeur = formule->Valeur[n];
						Arbre->LesBranches[0].type = 302; //NUM
						prog->Arbre = Arbre;
						formule->LesProg[n] = prog;
					}
				}
			}

			switch (nature) {
			case PRODUIT:
				agri->V_Produits->insSans(formule);
				break;
			case CHARGE:
				agri->V_Charges->insSans(formule);
				break;
			case CHSTRUCT:
				agri->V_ChStruct->insSans(formule);
				break;
			case RECDIV:
				agri->V_RecDiv->insSans(formule);
				break;
			case DEPDIV:
				agri->V_DepDiv->insSans(formule);
				break;
			case RECFAM:
				agri->V_RecFam->insSans(formule);
				break;
			case DEPFAM:
				agri->V_DepFam->insSans(formule);
				break;
			case EXTPOS:
				agri->V_ExtPos->insSans(formule);
				break;
			case EXTNEG:
				agri->V_ExtNeg->insSans(formule);
				break;
			}
			adoQuery->Next();

		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriVariable(TADOQuery *adoQuery) {
	int noAgri;
	int noItem;
	CL_Item *item;
	CL_Valeur *valeur;

	CL_Agriculteur *agri;
	if (requete_R_Agri_Variable(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			noItem = adoQuery->FieldByName("NoItem")->AsString.ToInt();
			item = V_Variable->trouve(noItem);
			valeur = new CL_Valeur();
			valeur->Item = item;
			valeur->NoItem = item->No;
			valeur->NoAtelier = -1; // ??voir le constructeur
			valeur->Atelier = NULL;

			LireValeur(adoQuery, valeur->Valeur);

			agri->V_Variable->insSans(valeur);

			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriImmo(TADOQuery *adoQuery) {
	int noAgri;
	CL_Immo *immo;

	CL_Agriculteur *agri;

	if (requete_R_Agri_Immo(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			immo = new CL_Immo();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			immo->Nom = adoQuery->FieldByName("Nom")->AsString;

			immo->NoTva = adoQuery->FieldByName("NoTva")->AsString.ToInt();
			immo->Tva = V_Tva->trouve(immo->NoTva);

			immo->ValAchat =
					adoQuery->FieldByName("ValAchat")->AsString.ToDouble();

			immo->AAchat = adoQuery->FieldByName("AAchat")->AsString.ToInt();
			immo->MAchat = adoQuery->FieldByName("MAchat")->AsString.ToInt();
			immo->AVente = adoQuery->FieldByName("AVente")->AsString.ToInt();
			immo->MVente = adoQuery->FieldByName("MVente")->AsString.ToInt();

			immo->TypeAmor =
					adoQuery->FieldByName("TypeAmor")->AsString.ToInt();

			immo->Duree = adoQuery->FieldByName("Duree")->AsString.ToInt();

			immo->ValVente =
					adoQuery->FieldByName("ValVente")->AsString.ToDouble();

			agri->V_Immo->insSans(immo);
			adoQuery->Next();
		}
	}
}
//immo finance global ou sommaire
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriXXXGlobal(TADOQuery *adoQuery,
		AnsiString nomTable, int nature) {
	int noAgri;
	bool verif = true;
	CL_FN_Xp1 *fN_Xp1;

	CL_Agriculteur *agri;

	if (nomTable == "R_Agri_ImmoGlobal")
		verif = requete_R_Agri_ImmoGlobal(adoQuery);
	if (nomTable == "R_Agri_FinanceGlobal")
		verif = requete_R_Agri_FinanceGlobal(adoQuery);
	if (verif) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			fN_Xp1 = new CL_FN_Xp1();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			fN_Xp1->No = adoQuery->FieldByName("NoItem")->AsString.ToInt();
			// mettre Item au lieu de NoItem 010908
			LireValeur(adoQuery, fN_Xp1->Valeur, N_X); //N_X+1);
			switch (nature) {
			case IMMO:
				agri->V_InvSom->insSans(fN_Xp1);
				break;
			case FINANCE:
				agri->V_FinSom->insSans(fN_Xp1);
				break;
			}
			//agri->V_InvSom->ins(fN_Xp1);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriEmpCT(TADOQuery *adoQuery) {
	int noAgri;
	CL_EmpCT *empCT;

	CL_Agriculteur *agri;
	if (requete_R_Agri_EmpCT(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			empCT = new CL_EmpCT();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			empCT->Nom = adoQuery->FieldByName("Nom")->AsString;

			empCT->Montant =
					adoQuery->FieldByName("Montant")->AsString.ToDouble();

			empCT->Taux = adoQuery->FieldByName("Taux")->AsString.ToDouble();
			empCT->Type = adoQuery->FieldByName("Type")->AsString;

			empCT->AReal = adoQuery->FieldByName("AReal")->AsString.ToInt();
			empCT->MReal = adoQuery->FieldByName("MReal")->AsString.ToInt();
			empCT->MRemb = adoQuery->FieldByName("MRemb")->AsString.ToInt();

			//empCT->Pour=adoQuery->FieldByName("Pour")->AsString[1];
			empCT->Pour = char(adoQuery->FieldByName("Pour")->AsString.ToInt());

			agri->V_EmpCT->insSans(empCT);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriEmpLT(TADOQuery *adoQuery) {
	int noAgri;
	CL_EmpLT *empLT;
	AnsiString as;
	CL_Agriculteur *agri;

	if (requete_R_Agri_EmpLT(adoQuery)) {

		adoQuery->First();
		while (!adoQuery->Eof) {
			empLT = new CL_EmpLT();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			empLT->Nom = adoQuery->FieldByName("Nom")->AsString;

			empLT->Montant =
					adoQuery->FieldByName("Montant")->AsString.ToDouble();

			empLT->Duree = adoQuery->FieldByName("Duree")->AsString.ToInt();

			as = adoQuery->FieldByName("Duree2")->AsString;
			if (as != "")
				empLT->Duree2 = as.ToInt();

			empLT->Taux = adoQuery->FieldByName("Taux")->AsString.ToDouble();
			as = adoQuery->FieldByName("Taux2")->AsString;
			if (as != "")
				empLT->Taux2 = as.ToDouble();

			empLT->Type = adoQuery->FieldByName("Type")->AsString;

			empLT->AReal = adoQuery->FieldByName("AReal")->AsString.ToInt();
			empLT->MReal = adoQuery->FieldByName("MReal")->AsString.ToInt();
			empLT->ARemb = adoQuery->FieldByName("ARemb")->AsString.ToInt();
			empLT->MRemb = adoQuery->FieldByName("MRemb")->AsString.ToInt();
			//TP2012
			//empLT->Pour=adoQuery->FieldByName("Pour")->AsString[1];
			empLT->Pour = char(adoQuery->FieldByName("Pour")->AsString.ToInt());

			agri->V_EmpLT->insSans(empLT);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriSub(TADOQuery *adoQuery) {
	int noAgri;
	CL_Sub *sub;

	CL_Agriculteur *agri;

	if (requete_R_Agri_Sub(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			sub = new CL_Sub();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			sub->Nom = adoQuery->FieldByName("Nom")->AsString;

			sub->Montant =
					adoQuery->FieldByName("Montant")->AsString.ToDouble();

			sub->AReal = adoQuery->FieldByName("AReal")->AsString.ToInt();
			sub->MReal = adoQuery->FieldByName("MReal")->AsString.ToInt();

			sub->Duree = adoQuery->FieldByName("Duree")->AsString.ToInt();

			agri->V_Sub->insSans(sub);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriOccc(TADOQuery *adoQuery) {
	int noAgri;
	CL_Occc *Occc;

	CL_Agriculteur *agri;

	if (requete_R_Agri_Occc(adoQuery)) {

		adoQuery->First();
		while (!adoQuery->Eof) {
			Occc = new CL_Occc();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri != NULL) {
				Occc->Montant =
						adoQuery->FieldByName("Montant")->AsString.ToDouble();
				Occc->Taux = adoQuery->FieldByName("Taux")->AsString.ToDouble();
				Occc->Pcent = adoQuery->FieldByName("Pcent")->AsString.ToInt();
				Occc->Frais = adoQuery->FieldByName("Frais")->AsString.ToInt();
				Occc->Ex = adoQuery->FieldByName("Ex")->AsString.ToInt();
				agri->V_Occc->insSans(Occc);
			}
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriPlact(TADOQuery *adoQuery) {
	int noAgri;
	CL_Plact *plact;

	CL_Agriculteur *agri;

	if (requete_R_Agri_Plact(adoQuery))

	{

		adoQuery->First();
		while (!adoQuery->Eof) {
			plact = new CL_Plact();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			plact->Nom = adoQuery->FieldByName("Nom")->AsString;

			plact->Montant =
					adoQuery->FieldByName("Montant")->AsString.ToDouble();
			plact->Taux = adoQuery->FieldByName("Taux")->AsString.ToDouble();

			plact->Type = adoQuery->FieldByName("Type")->AsString[1];

			plact->AReal = adoQuery->FieldByName("AReal")->AsString.ToInt();
			plact->MReal = adoQuery->FieldByName("MReal")->AsString.ToInt();
			plact->ATerme = adoQuery->FieldByName("ATerme")->AsString.ToInt();
			plact->MTerme = adoQuery->FieldByName("MTerme")->AsString.ToInt();

			plact->Pour = adoQuery->FieldByName("Pour")->AsString[1];

			agri->V_Plact->insSans(plact);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriPetit(TADOQuery *adoQuery) {
	int noAgri;
	//int noTva;
	CL_Petit *petit;
	AnsiString as, asValAchat;
	CL_Agriculteur *agri;

	if (requete_R_Agri_Petit(adoQuery)) {

		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);

			if (agri != NULL) {
				petit = new CL_Petit();
				petit->NoTva = adoQuery->FieldByName("NoTva")->AsString.ToInt();
				petit->No = adoQuery->FieldByName("NoItem")->AsString.ToInt();
				petit->ValAchat =
						adoQuery->FieldByName("ValAchat")->AsString.ToDouble();
				petit->Tva = V_Tva->trouve(petit->NoTva);
				agri->V_Petit->insSans(petit);
			}
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------

void TLireAccessFrm::LireR_Ensemble(TADOQuery *adoQuery) {
	CL_Ensemble *ensemble;
	CL_Vecteur<CL_Ensemble> *vecteur;
	//ST_NoEnsemble *variante;

	vecteur = V_Ensemble;
	vecteur->purge();

	if (requete_R_Ensemble(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			ensemble = new CL_Ensemble();
			ensemble->No =
					adoQuery->FieldByName("IdEnsemble")->AsString.ToInt();
			ensemble->Nom = adoQuery->FieldByName("Nom")->AsString;
			ensemble->Notes = adoQuery->FieldByName("Notes")->AsString;
			vecteur->insSans(ensemble);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_EnsEff(TADOQuery *adoQuery) {
	CL_Ensemble *ensemble;
	CL_Vecteur<CL_Ensemble> *vecteur;
	CL_AgriEff *agriEff;
	//CL_Vecteur<CL_Agriculteur> *vecteurbis;
	CL_Agriculteur *agri;
	int noens, noAgri;
	AnsiString nx;
	AnsiString nomagri;

	vecteur = V_Ensemble;
	if (requete_R_Ens_eff(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noens = adoQuery->FieldByName("IdEnsemble")->AsString.ToInt();
			ensemble = vecteur->trouve(noens);
			nomagri = adoQuery->FieldByName("Nom")->AsString;
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			//vecteurbis = V_Agriculteur;
			//agri = V_Agriculteur->trouve(nomagri);
			agri = V_Agriculteur->trouve(noAgri);
			agriEff = new CL_AgriEff();
			agriEff->NoAgri = agri->No;
			agriEff->Agri = agri;
			agriEff->Nom = nomagri;
			for (int i = 1; i < 11; i++) {
				nx = "N_X_" + (AnsiString) i;
				//ShowMessage(nx);
				agriEff->Effectif[i - 1] =
						adoQuery->FieldByName(nx)->AsString.ToInt();
			}
			ensemble->V_AgriEff->insSans(agriEff);
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriStockIni(TADOQuery *adoQuery) {
	CL_StockIni *stockIni;
	// CL_Vecteur<CL_StockIni> *vStockIni;
	CL_Agriculteur *agri;
	//CL_Item *Item;
	int noAgri;
	AnsiString annee;

	if (requete_R_Agri_StockIni(adoQuery)) {
		adoQuery->First();

		while (!adoQuery->Eof) {

			stockIni = new CL_StockIni();

			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			stockIni->NoItem =
					adoQuery->FieldByName("NoItem")->AsString.ToInt();
			stockIni->Item = V_Produit->trouve(stockIni->NoItem);
			if (stockIni->NoItem >= 0) {
				for (int l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					stockIni->PrixRevient[l] =
							adoQuery->FieldByName(annee)->AsString.ToDouble();
				}

				adoQuery->Next();

				for (int l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					stockIni->Quantite[l] =
							adoQuery->FieldByName(annee)->AsString.ToInt();
				}
			}
			agri->V_StockIni->insSans(stockIni);
			adoQuery->Next();
		}
	}
}
//---------------------------------------------------------------------------

void TLireAccessFrm::LireR_DefCatCalendrier(TADOQuery *adoQuery) {
	CL_Calendrier *calendrier;

	V_Calendrier->purge();
	if (requete_R_DefCatCalendrier(adoQuery)) {
		adoQuery->First();
		V_Calendrier->purge();
		while (!adoQuery->Eof) {
			calendrier = new CL_Calendrier();
			calendrier->No =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			calendrier->Nom = adoQuery->FieldByName("Nom")->AsString;
			calendrier->Notes = adoQuery->FieldByName("Notes")->AsString;
			V_Calendrier->insSans(calendrier);
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_DefCalendrier(TADOQuery *adoQuery) {
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	int nocalendrier;

	if (requete_R_DefCalendrier(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			nocalendrier =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			calendrier = V_Calendrier->trouve(nocalendrier);
			if (calendrier != NULL) {
				periode = new CL_Periode();
				periode->No =
						adoQuery->FieldByName("IdPeriode")->AsString.ToInt();
				periode->Nom = adoQuery->FieldByName("Nom")->AsString;
				periode->JDeb = adoQuery->FieldByName("JDeb")->AsString.ToInt();
				periode->MDeb = adoQuery->FieldByName("MDeb")->AsString.ToInt();
				periode->JFin = adoQuery->FieldByName("JFin")->AsString.ToInt();
				periode->MFin = adoQuery->FieldByName("MFin")->AsString.ToInt();
				periode->PcentDispo =
						adoQuery->FieldByName("PcentDispo")->AsString.ToInt();
				periode->HpJ =
						adoQuery->FieldByName("HpJ")->AsString.ToDouble();
				calendrier->V_Periode->insSans(periode);
			}
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriPolStock(TADOQuery *adoQuery) {
	CL_PolStock *polstock;
	CL_Agriculteur *agri;
	int noAgri, noItem;

	if (requete_R_Agri_Polstock(adoQuery))

	{

		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri != NULL) {
				polstock = new CL_PolStock();
				noItem = adoQuery->FieldByName("NoItem")->AsString.ToInt();
				polstock->PcentDeltaPrix =
						adoQuery->FieldByName("Prix")->AsString.ToDouble();
				polstock->PcentStock =
						adoQuery->FieldByName("PcentStock")->AsString.ToDouble();
				polstock->Maxi =
						adoQuery->FieldByName("MaxiStockable")->AsString.ToInt();
				polstock->PcentDecote =
						adoQuery->FieldByName("PcentDecote")->AsString.ToDouble();
				polstock->Item = V_Produit->trouve(noItem);
				polstock->Item->NoSysteme =
						adoQuery->FieldByName("IdSysUnit")->AsString.ToInt();
				polstock->Item->SysUnite = V_SystemeUnite->trouve(
						polstock->Item->NoSysteme);
				agri->V_PolStock->insSans(polstock);

			}
			adoQuery->Next();
		}
	}
}
//--tp 2012
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriTroupeau(TADOQuery *adoQuery,
		TADOQuery *adoQuery1, TADOQuery *adoQuery2) {
	CL_Agriculteur *agri;
	CL_Troupeau *troupeau;
	int noAgri, noCatBest, noItem;
	CL_InvAni *invAni;

	AnsiString annee;

	if (requete_R_Agri_TroupeauAgri(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			noAgri = adoQuery->FieldByName("NoAgri")->AsString.ToInt();
			noCatBest = adoQuery->FieldByName("NoCatBestiau")->AsString.ToInt();
			agri = V_Agriculteur->trouve(noAgri);
			if (agri != NULL) {
				troupeau = new CL_Troupeau();
				troupeau->NoCatBestiaux = noCatBest;
				troupeau->CatBestiaux = V_CatBestiaux->trouve(noCatBest);

				if (requete_R_Agri_TroupeauInvAni(adoQuery1, noAgri,
						noCatBest)) {

					adoQuery1->First();
					while (!adoQuery1->Eof) {
						//invAni
						invAni = new CL_InvAni();
						noItem =
								adoQuery1->FieldByName("NoItem")->AsString.ToInt();
						invAni->No =
								adoQuery1->FieldByName("NoItem")->AsString.ToInt();
						invAni->NoAnimal =
								adoQuery1->FieldByName("NoAnimal")->AsString.ToInt();
						invAni->Animal = V_Bestiaux->trouve(invAni->NoAnimal);

						if (adoQuery1->FieldByName("Reproducteur")->AsString.ToInt()
								== 1)
							invAni->Reproducteur = 'O';

						//Effectif
						if (requete_R_Agri_TroupeauInvAniEff(adoQuery2, noAgri,
								noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X + 1; i++) {
								annee = AnsiString("AN") + AnsiString(i);
								invAni->Effectif[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
							}

						}
						//Valeur
						if (requete_R_Agri_TroupeauInvAniVal(adoQuery2, noAgri,
								noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X + 1; i++) {
								annee = AnsiString("AN") + AnsiString(i);
								invAni->Valeur[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
							}

						}
						//Vente
						if (requete_R_Agri_TroupeauInvAniVente(adoQuery2,
								noAgri, noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->Vente[i] =
										adoQuery2->FieldByName(annee)->AsString.ToDouble();
							}

						}
						//Achat
						if (requete_R_Agri_TroupeauInvAniAchat(adoQuery2,
								noAgri, noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->Achat[i] =
										adoQuery2->FieldByName(annee)->AsString.ToDouble();
							}

						}
						//ValVente
						if (requete_R_Agri_TroupeauInvAniValVente(adoQuery2,
								noAgri, noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->ValVente[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
							}

						}
						//ValAchat
						if (requete_R_Agri_TroupeauInvAniValAchat(adoQuery2,
								noAgri, noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->ValAchat[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
							}

						}
						//EffMax
						if (requete_R_Agri_TroupeauInvAniEffMax(adoQuery2,
								noAgri, noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->EffMax[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
							}

						}
						//NoAtelier
						if (requete_R_Agri_TroupeauInvAniNoAtelier(adoQuery2,
								noAgri, noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->NoAtelier[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
								invAni->Atelier[i] = V_Animaux->trouve(
										invAni->NoAtelier[i]);
							}

						}
						//PVM
						if (requete_R_Agri_TroupeauInvAniPVM(adoQuery2, noAgri,
								noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X; i++) {
								annee = AnsiString("AN") + AnsiString(i + 1);
								invAni->PrixVenteMoy[i] =
										adoQuery2->FieldByName(annee)->AsString.ToDouble();
							}

						}
						//VIM
						if (requete_R_Agri_TroupeauInvAniVIM(adoQuery2, noAgri,
								noCatBest, noItem)) {
							adoQuery2->First();
							for (int i = 0; i < N_X + 1; i++) {
								annee = AnsiString("AN") + AnsiString(i);
								invAni->ValInvMoy[i] = adoQuery2->FieldByName(
										annee)->AsString.ToDouble();
							}

						}

						troupeau->V_InvAni->insSans(invAni);
						adoQuery1->Next();
					}
				}
			}
			agri->LstTroupeaux->Add(troupeau);
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriTroupeauMVT(TADOQuery *adoQuery) {
	CL_Agriculteur *agri;
	CL_Troupeau *troupeau;
	int noAgri, noCatBestiaux;
	CL_MvtAni *mvtAni;
	int ag, m;
	TList *lstTroupeaux;
	TList *lstMvtAni;
	int noAnimal, dateMvt, type, eff;
	double info;
	//Pour tous les agriculteurs:pour chaque troupeau lire les mouvements

	for (ag = 0; ag < V_Agriculteur->Nbelt; ag++) {

		agri = V_Agriculteur->Vecteur[ag];
		noAgri = agri->No;
		if (agri != NULL) {
			lstTroupeaux = agri->LstTroupeaux;

			for (m = 0; m < lstTroupeaux->Count; m++) {
				troupeau = (CL_Troupeau*) lstTroupeaux->Items[m];
				lstMvtAni = troupeau->LstMvtAni;

				noCatBestiaux = troupeau->NoCatBestiaux;
				if (requete_R_Agri_TroupeauMVT(adoQuery, noAgri,
						noCatBestiaux)) {

					while (!adoQuery->Eof) {
						noAnimal =
								adoQuery->FieldByName(AnsiString("Ligne"))->AsString.ToInt();
						dateMvt =
								adoQuery->FieldByName(AnsiString("DateMvt"))->AsString.ToInt();
						type =
								adoQuery->FieldByName(AnsiString("Type"))->AsString.ToInt();
						eff =
								adoQuery->FieldByName(AnsiString("Effectif"))->AsString.ToInt();
						info =
								adoQuery->FieldByName(AnsiString("Info"))->AsString.ToDouble();

						mvtAni = new CL_MvtAni(noAnimal, dateMvt, type, eff,
								info);

						lstMvtAni->Add(mvtAni);

						adoQuery->Next();
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriRepartItem(TADOQuery *adoQuery) {
	CL_Agriculteur *agri;
	CL_Vecteur<CL_ItemRepart> *vecteur;
	CL_ItemRepart *itemRepart, *itemRepartPetit;
	int noAgri;
	int ag;
	//Pour tous les agriculteurs

	for (ag = 0; ag < V_Agriculteur->Nbelt; ag++) {

		agri = V_Agriculteur->Vecteur[ag];

		if (agri != NULL) {
			vecteur = agri->V_ItemRepart;
			noAgri = agri->No;
			if (requete_R_Agri_RepartItem(adoQuery, noAgri)) {

				while (!adoQuery->Eof) {
					itemRepart = new CL_ItemRepart();

					itemRepart->Famille =
							adoQuery->FieldByName("NoFamille")->AsString.ToInt();
					itemRepart->NoItem =
							adoQuery->FieldByName("IdRepartItem")->AsString.ToInt();
					for (int j = 0; j < N_X; j++) {
						itemRepart->LesNoRepartQ[j] =
								adoQuery->FieldByName(
										AnsiString("NoRepartQ") + (j + 1))->AsString.ToInt();
						itemRepart->LesNoRepartV[j] =
								adoQuery->FieldByName(
										AnsiString("NoRepartV") + (j + 1))->AsString.ToInt();
						if (itemRepart->LesNoRepartQ[j] != -1)
							itemRepart->LesRepartQ[j] = V_Repart->trouve(
									itemRepart->LesNoRepartQ[j]);
						if (itemRepart->LesNoRepartV[j] != -1)
							itemRepart->LesRepartV[j] = V_Repart->trouve(
									itemRepart->LesNoRepartV[j]);
					}
					if (itemRepart->Famille == PETITMAT)
						itemRepartPetit = itemRepart;

					vecteur->ins(itemRepart);

					adoQuery->Next();
				}

				//if(V_Repart->Nbelt==0)         //fichier .oly ou treso non utilisée
				//return;

				//fread(&noRepartDefaut,sizeof(int),1,fichier);
				//fread(&possibOcPlactExiste,sizeof(int),1,fichier);

				//if(possibOcPlactExiste!=0)
				//{
				//    agri->PossibOcPlact=new CL_PossibOcPlact();
				//	agri->PossibOcPlact->LireFichier(fichier);
				//}
				//if(agri->V_Petit->Nbelt==0) return;
				//agri->QuanValPetit->ItemRepart=itemRepartPetit;
			}
		}
	}
}
//--
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AleaCateg(TADOQuery *adoQuery) {
	CL_Tendance *tendance;
	int nature;

	V_TendPrixProd->purge();
	V_TendPrixCharge->purge();
	V_TendQProd->purge();
	V_ScenPrixProd->purge();
	V_ScenPrixCharge->purge();
	V_TendQCharge->purge();
	V_ScenQProd->purge();
	V_ScenQCharge->purge();
	V_TendQExt->purge();
	V_ScenQExt->purge();
	if (requete_R_Alea_Categ(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			nature = adoQuery->FieldByName("IdAleas")->AsString.ToInt();
			tendance = new CL_Tendance();
			tendance->No =
					adoQuery->FieldByName("IdAleaCateg")->AsString.ToInt();
			tendance->Nom = adoQuery->FieldByName("Nom")->AsString;
			tendance->Notes = adoQuery->FieldByName("Notes")->AsString;
			//TP 2012 REMPLACEMENT DE ->ins PAR insSans 010412
			switch (nature) {
			case 1:
				V_TendPrixProd->insSans(tendance);
				break;
			case 2:
				V_TendPrixCharge->insSans(tendance);
				break;
			case 3:
				V_ScenPrixProd->insSans(tendance);
				break;
			case 4:
				V_ScenPrixCharge->insSans(tendance);
				break;
			case 5:
				V_TendQProd->insSans(tendance);
				break;
			case 6:
				V_TendQCharge->insSans(tendance);
				break;
			case 7:
				V_ScenQProd->insSans(tendance);
				break;
			case 8:
				V_ScenQCharge->insSans(tendance);
				break;
			case 9:
				V_TendQExt->insSans(tendance);
				break;
			case 10:
				V_ScenQExt->insSans(tendance);
				break;
			}
			adoQuery->Next();
		}
	}
}

//--
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Repart(TADOQuery *adoQuery, TADOQuery *adoQuery1) {
	CL_Repart *repart;
	int idRepart;
	AnsiString s;
	CL_IntFloat *dateVal;

	V_Repart->purge();
	if (requete_R_Alea_Repart(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			repart = new CL_Repart();

			repart->No = adoQuery->FieldByName("IdRepart")->AsString.ToInt();
			repart->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			repart->Categorie = V_CatRepart->trouve(repart->NoCategorie);
			repart->Nom = adoQuery->FieldByName("NomRepart")->AsString;
			idRepart = repart->No;
			if (requete_R_Alea_RepartDetail(adoQuery1, idRepart)) {
				adoQuery1->First();
				while (!adoQuery1->Eof) {
					dateVal = new CL_IntFloat();
					dateVal->i =
							adoQuery1->FieldByName("DateRepart")->AsString.ToInt();
					dateVal->Val =
							adoQuery1->FieldByName("ValeurRepart")->AsString.ToDouble();

					repart->LstPcent->Add(dateVal);

					adoQuery1->Next();
				}
			}

			V_Repart->insSans(repart);

			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AleaItem(TADOQuery *adoQuery) {
	CL_Tendance *tendance;
	CL_Delta *delta;
	int nature, notendance;
	AnsiString prix;
	// MajTable(adoTable,nomTable);
	if (requete_R_Alea_Item(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {
			notendance = adoQuery->FieldByName("IdAleaCateg")->AsString.ToInt();
			nature = adoQuery->FieldByName("IdAleas")->AsString.ToInt();
			delta = new CL_Delta();
			delta->NoItem =
					adoQuery->FieldByName("IdDefItem")->AsString.ToInt();
			switch (nature) {
			case 1:
				tendance = V_TendPrixProd->trouve(notendance);
				prix = "Prix";
				delta->Item = V_Produit->trouve(delta->NoItem);
				break;

			case 2:
				tendance = V_TendPrixCharge->trouve(notendance);
				prix = "Prix";
				delta->Item = V_Charge->trouve(delta->NoItem);
				break;

			case 3:
				tendance = V_ScenPrixProd->trouve(notendance);
				prix = "Prix";
				delta->Item = V_Produit->trouve(delta->NoItem);
				break;

			case 4:
				tendance = V_ScenPrixCharge->trouve(notendance);
				prix = "Prix";
				delta->Item = V_Charge->trouve(delta->NoItem);
				break;

			case 5:
				tendance = V_TendQProd->trouve(notendance);
				prix = "Quantite";
				delta->Item = V_Produit->trouve(delta->NoItem);
				break;

			case 6:
				tendance = V_TendQCharge->trouve(notendance);
				prix = "Quantite";
				delta->Item = V_Charge->trouve(delta->NoItem);
				break;

			case 7:
				tendance = V_ScenQProd->trouve(notendance);
				prix = "Quantite";
				delta->Item = V_Produit->trouve(delta->NoItem);
				break;

			case 8:
				tendance = V_ScenQCharge->trouve(notendance);
				prix = "Quantite";
				delta->Item = V_Charge->trouve(delta->NoItem);
				break;

			case 9:
				tendance = V_TendQExt->trouve(notendance);
				prix = "Quantite";
				delta->Item = V_Externalite->trouve(delta->NoItem);
				break;
			case 10:
				tendance = V_ScenQExt->trouve(notendance);
				prix = "Quantite";
				delta->Item = V_Externalite->trouve(delta->NoItem);
				break;
			}
			if (prix == "Prix")
				delta->No =
						adoQuery->FieldByName("IdAleaItem")->AsString.ToInt();
			//  delta->No =  adoTable->FieldByName("IdAleaItem")->AsString.ToInt();
			else
				delta->NoAtelier =
						adoQuery->FieldByName("IdAleaItem")->AsString.ToInt();

			delta->Nature = adoQuery->FieldByName("atelier")->AsString.ToInt();
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
			for (int i = 1; i <= 100; i++) {
				AnsiString nx = "An" + (AnsiString) i;
				delta->Pcent[i - 1] =
						adoQuery->FieldByName(nx)->AsString.ToDouble();
			}
			if (tendance != NULL)
				tendance->V_Delta->insSans(delta);
			adoQuery->Next();
		}

	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_DefEtatSortie(TADOQuery *adoQuery,
		TADOQuery *adoQuery1) {
	CL_EtatSortie *etat;
	CL_Elt *elt;
	CL_Vecteur<CL_Elt> *vecteur;
	AnsiString titre;
	int l;
	char *chaine;

	V_EtatSortie->purge();
	if (requete_R_DefEtatSortie(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {

			etat = new CL_EtatSortie();
			//--TP 2012
			etat->No = adoQuery->FieldByName("IdEtatSortie")->AsString.ToInt();
			etat->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			etat->Nom = adoQuery->FieldByName("Nom")->AsString;

			etat->Categorie = V_CatEtatSortie->trouve(etat->NoCategorie);
			//--Lecture du detail
			if (requete_R_EtatSortieItemEtat(adoQuery1, etat->No)) {
				vecteur = etat->V_Elt;
				//Détail
				while (!adoQuery1->Eof) {
					elt = new CL_Elt();

					elt->No = adoQuery1->FieldByName("NoElt")->AsString.ToInt();
					elt->NoFamille =
							adoQuery1->FieldByName("NoFamille")->AsString.ToInt();
					elt->NoCategorie =
							adoQuery1->FieldByName("NoCateg")->AsString.ToInt();
					elt->NoItem =
							adoQuery1->FieldByName("NoItemElt")->AsString.ToInt();
					elt->Digits =
							adoQuery1->FieldByName("Digits")->AsString.ToInt();
					elt->Coul =
							adoQuery1->FieldByName("Couleur")->AsString.ToInt();

					if (elt->NoItem == TITRE) {
						titre = adoQuery1->FieldByName("Titre")->AsString;
						l = titre.Length();
						chaine = new char[l];
						strcpy(chaine, titre.c_str());
						elt->Nom = chaine;
					}
					vecteur->insSans(elt);

					adoQuery1->Next();
				}
			}
			V_EtatSortie->insSans(etat);
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_DefSerieComp(TADOQuery *adoQuery,
		TADOQuery *adoQuery1) {
	CL_EtatSortie *etat;
	CL_Elt *elt;
	CL_Vecteur<CL_Elt> *vecteur;
	AnsiString titre;
	int l;
	char *chaine;

	V_SerieComp->purge();
	if (requete_R_DefSerieComp(adoQuery)) {
		adoQuery->First();
		while (!adoQuery->Eof) {

			etat = new CL_EtatSortie();
			//--TP 2012
			etat->No = adoQuery->FieldByName("IdEtatSortie")->AsString.ToInt();
			etat->NoCategorie =
					adoQuery->FieldByName("IdDefCateg")->AsString.ToInt();
			etat->Nom = adoQuery->FieldByName("Nom")->AsString;

			etat->Categorie = V_CatSerieComp->trouve(etat->NoCategorie);
			//--Lecture du detail
			if (requete_R_SerieCompItemEtat(adoQuery1, etat->No)) {
				vecteur = etat->V_Elt;
				//Détail
				while (!adoQuery1->Eof) {
					elt = new CL_Elt();

					elt->No = adoQuery1->FieldByName("NoElt")->AsString.ToInt();
					elt->NoFamille =
							adoQuery1->FieldByName("NoFamille")->AsString.ToInt();
					elt->NoCategorie =
							adoQuery1->FieldByName("NoCateg")->AsString.ToInt();
					elt->NoItem =
							adoQuery1->FieldByName("NoItemElt")->AsString.ToInt();
					elt->Digits =
							adoQuery1->FieldByName("Digits")->AsString.ToInt();
					elt->Coul =
							adoQuery1->FieldByName("Couleur")->AsString.ToInt();

					if (elt->NoItem == TITRE) {
						titre = adoQuery1->FieldByName("Titre")->AsString;
						l = titre.Length();
						chaine = new char[l];
						strcpy(chaine, titre.c_str());
						elt->Nom = chaine;
					}
					vecteur->insSans(elt);

					adoQuery1->Next();
				}
			}
			V_SerieComp->insSans(etat);
			adoQuery->Next();
		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_DefConversion(TADOQuery *adoQuery) {
	CL_Conversion *conversion;
	AnsiString nx;
	V_Conversion->purge();

	if (requete_R_DefConversion(adoQuery))

	{
		adoQuery->First();
		while (!adoQuery->Eof) {
			conversion = new CL_Conversion();
			conversion->No =
					adoQuery->FieldByName("IdConversion")->AsString.ToInt();
			conversion->Nom = adoQuery->FieldByName("Nom")->AsString;
			conversion->NoBase =
					adoQuery->FieldByName("NoBase")->AsString.ToInt();
			if (adoQuery->FieldByName("NoSortie")->AsString != "") {
				conversion->NoSortie =
						adoQuery->FieldByName("NoSortie")->AsString.ToInt();
			} else
				conversion->NoSortie = NULL;
			conversion->APartirDe =
					adoQuery->FieldByName("APartirDe")->AsString.ToInt();
			conversion->Base = V_SystemeUnite->trouve(conversion->NoBase);
			if (conversion->NoSortie != NULL)
				conversion->Sortie = V_SystemeUnite->trouve(
						conversion->NoSortie);
			for (int i = 1; i < 11; i++) {
				nx = "FVE" + (AnsiString) i;
				//ShowMessage(nx);
				conversion->TauxConvFrancVersEuro[i - 1] =
						adoQuery->FieldByName(nx)->AsString.ToInt();
				nx = "EVF" + (AnsiString) i;
				conversion->TauxConvEuroVersFranc[i - 1] =
						adoQuery->FieldByName(nx)->AsString.ToInt();
			}
			V_Conversion->insSans(conversion);
			adoQuery->Next();

		}
	}
}

//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Indicateur(TADOQuery *adoQuery) {
	char chaine[100];

	CL_Indicateur *indicateur;
	V_Indicateur->purge();

	if (requete_Indicateur(adoQuery)) {

		while (!adoQuery->Eof) {
			indicateur = new CL_Indicateur();
			indicateur->Nom = adoQuery->FieldByName("Nom")->AsString;
			indicateur->Notes = adoQuery->FieldByName("Notes")->AsString;
			indicateur->No = adoQuery->FieldByName("NoIndic")->AsString.ToInt();
			indicateur->NoCategorie =
					adoQuery->FieldByName("NoCateg")->AsString.ToInt();
			indicateur->type = adoQuery->FieldByName("type")->AsString.ToInt();

			indicateur->NoSysteme =
					adoQuery->FieldByName("NoSys")->AsString.ToInt();
			indicateur->SysUnite = V_SystemeUnite->trouve(
					indicateur->NoSysteme);

			indicateur->Categorie = V_CatIndic->trouve(indicateur->NoCategorie);
			indicateur->Prog->Arbre = NULL;
			indicateur->Prog->Reseau = NULL;
			indicateur->Compile = true;
			V_Indicateur->insSans(indicateur);
			sprintf(chaine, "Indic %3d", indicateur->No);
			EcrireRapport(AnsiString(chaine));
			adoQuery->Next();
		}
	}

	lireArbre(adoQuery, V_Indicateur);
	lireReseau(adoQuery, V_Indicateur);

}
//---------------------------------------------------------------------------
//--TP 2012
CL_Arbre* TLireAccessFrm::lireArbre(TADOQuery *adoQuery,
		CL_Vecteur<CL_Indicateur> *vIndic) {
	int nx;
	int noIndic;
	CL_Arbre *Arbre;
	CL_Indicateur *indic;

	AnsiString codebranche;
	AnsiString arg1branche;
	AnsiString arg2branche;
	AnsiString arg3branche;
	AnsiString valeurbranche;
	AnsiString typebranche;
	AnsiString datebranche;
	char chaine[100];

	for (int ind = 0; ind < vIndic->Nbelt; ind++) {
		indic = vIndic->Vecteur[ind];
		noIndic = indic->No;

		if (requete_lireArbre(adoQuery, noIndic)) {
			if (!adoQuery->Eof) {
				nx = adoQuery->FieldByName("nbrBranche")->AsString.ToInt();

				sprintf(chaine, "INDIC %3d ", indic->No);
				EcrireRapport(AnsiString(chaine));
				Arbre = new CL_Arbre(nx, 10);
				Arbre->BrancheX = nx;

				for (int n = 0; n < nx; n++) {
					Arbre->LesBranches[n].code =
							adoQuery->FieldByName("code")->AsString.ToInt();
					Arbre->LesBranches[n].arg[0] =
							adoQuery->FieldByName("arg1")->AsString.ToInt();
					Arbre->LesBranches[n].arg[1] =
							adoQuery->FieldByName("arg2")->AsString.ToInt();
					Arbre->LesBranches[n].arg[2] =
							adoQuery->FieldByName("arg3")->AsString.ToInt();
					Arbre->LesBranches[n].valeur = adoQuery->FieldByName(
							"valeur")->AsString.ToDouble();
					Arbre->LesBranches[n].type =
							adoQuery->FieldByName("type")->AsString.ToInt();
					Arbre->LesBranches[n].date = adoQuery->FieldByName(
							"datebranche")->AsString.ToInt();

					//TP 2012 ???
					if (Arbre->LesBranches[n].code == IDENT
							&& Arbre->LesBranches[n].arg[0] == 40) {
						if (Arbre->LesBranches[n].arg[1] <= 160)
							Arbre->LesBranches[n].arg[1] = 161;
					}
					//indic->Prog->Arbre = Arbre;

					sprintf(chaine,
							"%3d %3d      %3d  %3d  %3d  %3d %2d  %6.2f", n,
							Arbre->LesBranches[n].code,
							Arbre->LesBranches[n].arg[0],
							Arbre->LesBranches[n].arg[1],
							Arbre->LesBranches[n].arg[2],
							Arbre->LesBranches[n].type,
							Arbre->LesBranches[n].date,
							Arbre->LesBranches[n].valeur);
					EcrireRapport(AnsiString(chaine));

					adoQuery->Next();
				}
				//return Arbre;
				indic->Prog->Arbre = Arbre;
			}
			//else return NULL;
		}
	}
	return NULL;
}

//---------------------------------------------------------------------------
CL_Reseau* TLireAccessFrm::lireReseau(TADOQuery *adoQuery,
		CL_Vecteur<CL_Indicateur> *vIndic) {
	int nx;
	int noIndic;
	CL_Reseau *Reseau;
	CL_Indicateur *indic;
	AnsiString st;
	char chaine[100];

	for (int ind = 0; ind < vIndic->Nbelt; ind++) {
		indic = vIndic->Vecteur[ind];
		noIndic = indic->No;

		if (requete_lireReseau(adoQuery, noIndic)) {
			if (!adoQuery->Eof) {
				st = adoQuery->FieldByName("nbrMaille")->AsString;
				if (!st.IsEmpty()) {
					nx = st.ToInt();
					if (nx != 0) {
						sprintf(chaine, "INDIC %3d ", indic->No);
						EcrireRapport(AnsiString(chaine));

						Reseau = new CL_Reseau(nx, 10);
						Reseau->MailleX = nx;
						for (int n = 0; n < Reseau->MailleX; n++) {
							Reseau->LesMailles[n].code = adoQuery->FieldByName(
									"codeReseau")->AsString.ToInt();
							Reseau->LesMailles[n].branche =
									adoQuery->FieldByName("codeBranche")->AsString.ToInt();
							Reseau->LesMailles[n].apG = adoQuery->FieldByName(
									"apGreseau")->AsString.ToInt();
							Reseau->LesMailles[n].apD = adoQuery->FieldByName(
									"apDreseau")->AsString.ToInt();
							adoQuery->Next();

							sprintf(chaine, "%3d %3d %3d      %3d  %3d", n,
									Reseau->LesMailles[n].code,
									Reseau->LesMailles[n].branche,
									Reseau->LesMailles[n].apG,
									Reseau->LesMailles[n].apD);
							EcrireRapport(AnsiString(chaine));

						}
						indic->Prog->Reseau = Reseau;
						//return Reseau;
					}
				}
			}
		}

	}
	return NULL;
}
//---------------------------------------------------------------------------

void TLireAccessFrm::TexteChaine(void) {
	L_Termine = T->TrouveTexte("LireAccessFrm", "L_Termine");
}
//--------------------------------------------------------------------------
void TLireAccessFrm::TexteCaption(void) {
	LC_Ouvrir = T->TrouveCaption("LireAccessFrm", "LC_Ouvrir");
}

