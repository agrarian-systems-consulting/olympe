//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//#include "DefVecteur.h"

#include "Main.h"
#include "LireAccess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLireAccessFrm *LireAccessFrm;
extern bool FichierLu;
//---------------------------------------------------------------------------
__fastcall TLireAccessFrm::TLireAccessFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireFichier(void) {
	AnsiString as;
	TADOTable *adoTable;

	AnsiString asProvider = "Provider=Microsoft.Jet.OLEDB.4.0;";
	AnsiString asUserId = "User ID=Admin;";
//AnsiString asDataSource="Data Source=C:\\OlympAccess\\olympeAccess.mdb;";
	AnsiString asDataSource;

	bool res;
	res = OpenDialog->Execute();
	if (res == false)
		return;

	as = OpenDialog->FileName;
	asDataSource = AnsiString("Data Source=") + as;

	adoTable = new TADOTable(this);

	adoTable->Active = false;
	adoTable->ConnectionString = asProvider + asUserId + asDataSource;

	LireSystemeUnite(adoTable, "SystemeUnite", V_SystemeUnite);
	LireTva(adoTable, "TVA", V_Tva);

	LireR_Def_Categ(adoTable, "R_DefCatProduit", V_CatProduit);
	LireR_Def_Categ(adoTable, "R_DefCatCharge", V_CatCharge);
	LireR_Def_Categ(adoTable, "R_DefCatExternalite", V_CatExternalite);
	LireR_Def_Categ(adoTable, "R_DefCatBestiaux", V_CatBestiaux);
	LireR_Def_Categ(adoTable, "R_DefCatChStruct", V_CatChStruct);
	LireR_Def_Categ(adoTable, "R_DefCatDepDiv", V_CatDepDiv);
	LireR_Def_Categ(adoTable, "R_DefCatDepFam", V_CatDepFam);
	LireR_Def_Categ(adoTable, "R_DefCatRecDiv", V_CatRecDiv);
	LireR_Def_Categ(adoTable, "R_DefCatRecFam", V_CatRecFam);
	//rien dans cette requete !!!!!!!!!!!!!!
	LireR_Def_Categ(adoTable, "R_DefCatTypeZone", V_CatTypeZone);
	LireR_Def_Categ(adoTable, "R_DefCatVariable", V_CatVar);

	LireR_Def_ProCha(adoTable, "R_Def_Prod", V_CatProduit, V_Produit);
	LireR_Def_ProCha(adoTable, "R_Def_Cha", V_CatCharge, V_Charge);

	LireR_Def_ExtVar(adoTable, "R_Def_Ext", V_CatExternalite, V_Externalite);
	LireR_Def_ExtVar(adoTable, "R_Def_Var", V_CatVar, V_Variable);

	LireR_Def_ChStructRecDep(adoTable, "R_Def_ChStruct", V_CatChStruct,
			V_ChStruct);
	LireR_Def_ChStructRecDep(adoTable, "R_Def_RecDiv", V_CatRecDiv, V_RecDiv);
	LireR_Def_ChStructRecDep(adoTable, "R_Def_DepDiv", V_CatDepDiv, V_DepDiv);
	LireR_Def_ChStructRecDep(adoTable, "R_Def_RecFam", V_CatRecFam, V_RecFam);
	LireR_Def_ChStructRecDep(adoTable, "R_Def_DepFam", V_CatDepFam, V_DepFam);
	//rien nom plus la dedans
	// dans l'ancien fichier il y avait du monde ->Plantage
	LireR_Def_ChStructRecDep(adoTable, "R_Def_TypeZone", V_CatTypeZone,
			V_TypeZone);

	LireR_Ate_CatAtelier(adoTable, "R_AteCatCulture", V_CatCulture);
	LireR_Ate_CatAtelier(adoTable, "R_AteCatAnimaux", V_CatAnimaux);
	LireR_Ate_CatPerenne(adoTable, "R_AteCatPerenne");
	LireR_Ate_CatAtelier(adoTable, "R_AteCatVivrier", V_CatVivrier);

	LireR_Ate_Atelier(adoTable, "R_Ate_Culture", CULTURE, V_CatCulture,
			V_Culture);
	LireR_Ate_Atelier(adoTable, "R_Ate_Animaux", ANIMAUX, V_CatAnimaux,
			V_Animaux);
	LireR_Ate_Atelier(adoTable, "R_Ate_Perenne");
	LireR_Ate_Atelier(adoTable, "R_Ate_Vivrier", VIVRIER, V_CatVivrier,
			V_Vivrier);

	LireR_Ate_Item(adoTable, "R_Ate_CultureItem", V_Culture);
	LireR_Ate_Item(adoTable, "R_Ate_AnimauxItem", V_Animaux);
	LireR_Ate_Item(adoTable, "R_Ate_PerenneItem", V_Perenne);
	LireR_Ate_Item(adoTable, "R_Ate_VivrierItem", V_Vivrier);

	AdresseChFVol(V_Culture);
	AdresseChFVol(V_Animaux);
	AdresseChFVol(V_Perenne);
	AdresseChFVol(V_Vivrier);

	// Agriculteur
	LireR_Agri(adoTable, "R_Agri");
	// R_DefCatTypeZone ??
//    LireR_Agri_Critere(adoTable,"R_Agri_Critere");

	LireR_AgriAssol(adoTable, "R_Agri_Assol", CULTURE);
	LireR_AgriAssol(adoTable, "R_Agri_Animaux", ANIMAUX);
	LireR_AgriPerenne(adoTable, "R_Agri_Perenne", PERENNE);
	LireR_AgriPerenne(adoTable, "R_Agri_Vivrier", VIVRIER);

	LireR_AgriFormule(adoTable, "R_Agri_ValProduit", PRODUIT);
	LireR_AgriFormule(adoTable, "R_Agri_ValCharge", CHARGE);
	LireR_AgriFormule(adoTable, "R_Agri_ValChStruct", CHSTRUCT);
	LireR_AgriFormule(adoTable, "R_Agri_ValRecDiv", RECDIV);
	LireR_AgriFormule(adoTable, "R_Agri_ValDepDiv", DEPDIV);
	LireR_AgriFormule(adoTable, "R_Agri_ValRecFam", RECFAM);
	LireR_AgriFormule(adoTable, "R_Agri_ValDepFam", DEPFAM);

	LireR_AgriVariable(adoTable, "R_Agri_ValVariable");

	FichierLu = true;
	// R_AgriValeur  impossible de l'ouvrir dans Access
	// a faire emprunts, matériel
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
void TLireAccessFrm::LireSystemeUnite(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_SystemeUnite> *vecteur) {
	CL_SystemeUnite *sysUnit;
	MajTable(adoTable, nomTable);

	vecteur->purge();

	adoTable->First();
	while (!adoTable->Eof) {
		sysUnit = new CL_SystemeUnite();
		sysUnit->No = adoTable->FieldByName("No")->AsString.ToInt();

		sysUnit->UUt = adoTable->FieldByName("UUt")->AsString;
		sysUnit->UTrans = adoTable->FieldByName("UTrans")->AsString;
		sysUnit->UGlobal = adoTable->FieldByName("uGlobal")->AsString;

		sysUnit->Ratio = adoTable->FieldByName("ratio")->AsString.ToDouble();
		sysUnit->RatioG = adoTable->FieldByName("ratioG")->AsString.ToDouble();

		sysUnit->Monnaie = adoTable->FieldByName("monnaie")->AsString[1];

		vecteur->insSans(sysUnit);

		adoTable->Next();
	}
//!!
	if (SysMonnaie == NULL) {
		SysMonnaie = vecteur->Vecteur[0];
		SysMonnaie->Monnaie = 'O';
	}

}
//----------------------------------------------------------------------------
void TLireAccessFrm::LireTva(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Tva> *vecteur) {
//int nbelt;
	CL_Tva *tva;
	MajTable(adoTable, nomTable);

	vecteur->purge();

	adoTable->First();
	while (!adoTable->Eof) {
		tva = new CL_Tva();
		tva->No = adoTable->FieldByName("No")->AsString.ToDouble();
		tva->Nom = adoTable->FieldByName("Nom")->AsString;
		tva->Taux = adoTable->FieldByName("Taux")->AsString.ToDouble();
		vecteur->insSans(tva);

		adoTable->Next();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_Categ(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	AnsiString as, asMessage;
	CL_Categorie *categorie;

	vCategorie->purge();

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		categorie = new CL_Categorie();
		categorie->No = adoTable->FieldByName("No")->AsString.ToInt();
		categorie->Nom = adoTable->FieldByName("Nom")->AsString;
		categorie->Notes = adoTable->FieldByName("Notes")->AsString;
		vCategorie->insSans(categorie);
		adoTable->Next();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_ProCha(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_Item> *vItem) {
//int nature;
	AnsiString as, asMessage;
//CL_Categorie *categorie;
	CL_Item *item;

	vItem->purge();

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		item = new CL_Item();

		item->NoCategorie = adoTable->FieldByName("NoCateg")->AsString.ToInt();
		item->Categorie = vCategorie->trouve(item->NoCategorie);

		item->No = adoTable->FieldByName("No")->AsString.ToInt();
		item->Nom = adoTable->FieldByName("Nom")->AsString;

		item->NoSysteme = adoTable->FieldByName("NoSysteme")->AsString.ToInt();
		item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);

		item->Prix = adoTable->FieldByName("Prix")->AsString.ToDouble();

		item->NoTva = adoTable->FieldByName("NoTva")->AsString.ToInt();
		item->Tva = V_Tva->trouve(item->NoTva);

		vItem->insSans(item);

		adoTable->Next();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_ExtVar(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_Item> *vItem) {
//int nature;
	AnsiString as, asMessage;
//CL_Categorie *categorie;
	CL_Item *item;

	vItem->purge();

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		item = new CL_Item();

		item->NoCategorie = adoTable->FieldByName("NoCateg")->AsString.ToInt();
		item->Categorie = vCategorie->trouve(item->NoCategorie);

		item->No = adoTable->FieldByName("No")->AsString.ToInt();
		item->Nom = adoTable->FieldByName("Nom")->AsString;

		item->NoSysteme = adoTable->FieldByName("NoSysteme")->AsString.ToInt();
		item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);

		vItem->insSans(item);

		adoTable->Next();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Def_ChStructRecDep(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_Item> *vItem) {
//int nature;
	AnsiString as, asMessage;
//CL_Categorie *categorie;
	CL_Item *item;

	vItem->purge();

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		item = new CL_Item();

		item->NoCategorie = adoTable->FieldByName("NoCateg")->AsString.ToInt();
		item->Categorie = vCategorie->trouve(item->NoCategorie);

		item->No = adoTable->FieldByName("No")->AsString.ToInt();
		item->Nom = adoTable->FieldByName("Nom")->AsString;
		item->NoTva = adoTable->FieldByName("NoTva")->AsString.ToInt();
		item->Tva = V_Tva->trouve(item->NoTva);

		vItem->insSans(item);

		adoTable->Next();
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_CatAtelier(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Categorie *categorie;
	vCategorie->purge();
	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		categorie = new CL_Categorie();
		categorie->No = adoTable->FieldByName("No")->AsString.ToInt();
		categorie->Nom = adoTable->FieldByName("Nom")->AsString;
		categorie->Notes = adoTable->FieldByName("Notes")->AsString;
		vCategorie->insSans(categorie);

		adoTable->Next();

	}
}
//---------------------------------------------------------------------------
// en fait LireEspece
void TLireAccessFrm::LireR_Ate_CatPerenne(TADOTable *adoTable,
		AnsiString nomTable) {
	CL_Espece *espece;
	int i;
	AnsiString as, asPhase;
	V_Espece->purge();
	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		espece = new CL_Espece();
		espece->No = adoTable->FieldByName("No")->AsString.ToInt();
		espece->Nom = adoTable->FieldByName("Nom")->AsString;
//        espece->Notes=adoTable->FieldByName("Notes")->AsString;
		espece->DebAmor = adoTable->FieldByName("DebAmor")->AsString.ToInt();
		espece->DurAmor = adoTable->FieldByName("DurAmor")->AsString.ToInt();
		espece->NbPhase = adoTable->FieldByName("NbPhase")->AsString.ToInt();
		for (i = 0; i < espece->NbPhase + 1; i++) {
			asPhase = AnsiString("Ph") + i;
			as = adoTable->FieldByName(asPhase)->AsString;
			if (as.Length() == 0)
				continue;
			espece->Phase[i] =
					adoTable->FieldByName(asPhase)->AsString.ToDouble();
		}

		V_Espece->insSans(espece);

		adoTable->Next();

	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Atelier(TADOTable *adoTable, AnsiString nomTable,
		int nature, CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	AnsiString as;
	float val;
	int n;
//CL_Categorie *categorie;
	CL_Atelier *atelier;

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		atelier = new CL_Atelier();
		atelier->Nature = nature;
		atelier->No = adoTable->FieldByName("No")->AsString.ToInt();
		atelier->Nom = adoTable->FieldByName("Nom")->AsString;
		atelier->NoCategorie =
				adoTable->FieldByName("NoCateg")->AsString.ToInt();
		atelier->Categorie = vCategorie->trouve(atelier->NoCategorie);
		if (nature == VIVRIER)
			atelier->NbPhase = 5;
		else
			atelier->NbPhase = 3;
		n = adoTable->FieldByName("Derobe")->AsString.ToInt();
		if (n == 1)
			atelier->Derobe = true;
		else
			atelier->Derobe = false;
		/*??? A VOIR
		 n=adoTable->FieldByName("PImmoExiste")->AsString.ToInt();
		 n=adoTable->FieldByName("PImmoFamExiste")->AsString.ToInt();
		 val=adoTable->FieldByName("ValInvRepro")->AsString.ToInt();
		 val=adoTable->FieldByName("ValInvAutre")->AsString.ToInt();
		 */
		vAtelier->insSans(atelier);

		adoTable->Next();

	}
}
//perennes
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Atelier(TADOTable *adoTable,
		AnsiString nomTable) {
	AnsiString as;
	float val;
	int n;
//CL_Categorie *categorie;
	CL_Atelier *atelier;

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		atelier = new CL_Atelier();
		atelier->Nature = 3;
		atelier->No = adoTable->FieldByName("No")->AsString.ToInt();
		atelier->Nom = adoTable->FieldByName("Nom")->AsString;
		atelier->NoEspece = adoTable->FieldByName("NoCateg")->AsString.ToInt();
		atelier->Espece = V_Espece->trouve(atelier->NoEspece);
		atelier->NbPhase = atelier->Espece->NbPhase + 1;

		n = adoTable->FieldByName("Derobe")->AsString.ToInt();
		if (n == 1)
			atelier->Derobe = true;
		else
			atelier->Derobe = false;

		n = adoTable->FieldByName("PImmoExiste")->AsString.ToInt();
		if (n == 1)
			atelier->PImmoExiste = true;
		else
			atelier->PImmoExiste = false;

		n = adoTable->FieldByName("PImmoFamExiste")->AsString.ToInt();
		if (n == 1)
			atelier->PImmoFamExiste = true;
		else
			atelier->PImmoFamExiste = false;

		atelier->ValInvRepro =
				adoTable->FieldByName("ValInvRepro")->AsString.ToInt();
		atelier->ValInvAutre =
				adoTable->FieldByName("ValInvAutre")->AsString.ToInt();

		V_Perenne->insSans(atelier);

		adoTable->Next();

	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Ate_Item(TADOTable *adoTable, AnsiString nomTable,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	AnsiString as, asPhase;
	int i; //,n;
	int noList, noAtel;
	int nature;
	float val[N_PHASE];
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_Vecteur<CL_Item> *vItem;
	CL_ItemParAtelier *itemPA;

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		itemPA = new CL_ItemParAtelier();
		//atelier
		noAtel = adoTable->FieldByName("NoAtel")->AsString.ToInt();
		atelier = vAtelier->trouve(noAtel);
		// Produit charge chargeVol etc..
		noList = adoTable->FieldByName("NoList")->AsString.ToInt();
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
		case 10:
			vecteurIPA = atelier->V_ProdPied;
			break;
		case 11:
			vecteurIPA = atelier->V_ChPied;
			break;
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
			itemPA->NoItem = adoTable->FieldByName("NoItem")->AsString.ToInt();
			itemPA->Item = vItem->trouve(itemPA->NoItem);
			itemPA->QtePhase = new float[atelier->NbPhase];
			LireQtePhase(adoTable, atelier->NbPhase, itemPA->QtePhase);
			vecteurIPA->insSans(itemPA);
			break;
		case 3: //  ch f vol
			// produit
			itemPA->NoItem = adoTable->FieldByName("NoItem")->AsString.ToInt();
			itemPA->Item = V_Produit->trouve(itemPA->NoItem);
			// Charge
			itemPA->NoCharge =
					adoTable->FieldByName("NoChFVol")->AsString.ToInt();
			itemPA->Charge = V_Charge->trouve(itemPA->NoCharge);
			itemPA->QtePhase = new float[atelier->NbPhase];
			LireQtePhase(adoTable, atelier->NbPhase, itemPA->QtePhase);
			vecteurIPA->insSans(itemPA);
			break;
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
			itemPA->NoItem = adoTable->FieldByName("NoItem")->AsString.ToInt();
			itemPA->Item = vItem->trouve(itemPA->NoItem);
			itemPA->QtePhase = new float[atelier->NbPhase];
			LireQtePhase(adoTable, atelier->NbPhase, itemPA->QtePhase);
			vecteurIPA->insSans(itemPA);
			break;
		}
		adoTable->Next();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireQtePhase(TADOTable *adoTable, int nbPhase,
		float *qtePhase) {
	int i;
	AnsiString as, asPhase;
	for (i = 0; i < nbPhase; i++)
		qtePhase[i] = 0.;
	for (i = 0; i < nbPhase; i++) {
		asPhase = AnsiString("Ph") + i;
		as = adoTable->FieldByName(asPhase)->AsString;
		if (as.Length() == 0)
			continue;
		qtePhase[i] = adoTable->FieldByName(asPhase)->AsString.ToDouble();
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
void TLireAccessFrm::LireR_Agri(TADOTable *adoTable, AnsiString nomTable) {
	CL_Agriculteur *agri;

	V_Agriculteur->purge();
	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		agri = new CL_Agriculteur();

		agri->No = adoTable->FieldByName("No")->AsString.ToInt();
		agri->Nom = adoTable->FieldByName("Nom")->AsString;
		agri->Notes = adoTable->FieldByName("Notes")->AsString;
//??    	agri->DefSim->An_0=adoTable->FieldByName("An_0")->AsString.ToInt();
		agri->DefSim->An_0 = 2008;
		V_Agriculteur->insSans(agri);

		adoTable->Next();

	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_Agri_Critere(TADOTable *adoTable,
		AnsiString nomTable) {
	int noAgri;
	CL_Agriculteur *agri;
	int noCritere;
	CL_Item *critere;

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		noAgri = adoTable->FieldByName("NoAgri")->AsString.ToInt();
		agri = V_Agriculteur->trouve(noAgri);
		noCritere = adoTable->FieldByName("NoCritere")->AsString.ToInt();
		critere = V_TypeZone->trouve(noCritere);
		agri->LstCritere->Add(critere);

		adoTable->Next();
	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriAssol(TADOTable *adoTable, AnsiString nomTable,
		int nature) {
	int noAgri;
	int noAtelier;

	CL_Agriculteur *agri;
	CL_Atelier *atelier;
	CL_Valeur *valeur;

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		noAgri = adoTable->FieldByName("NoAgri")->AsString.ToInt();
		agri = V_Agriculteur->trouve(noAgri);

		noAtelier = adoTable->FieldByName("NoAtel")->AsString.ToInt();
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
		LireValeur(adoTable, valeur->Valeur);

		switch (nature) {
		case CULTURE:
			agri->V_Culture->insSans(valeur);
			break;
		case ANIMAUX:
			agri->V_Animaux->insSans(valeur);
			break;
		}
		adoTable->Next();

	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriPerenne(TADOTable *adoTable, AnsiString nomTable,
		int nature) {
	int noAgri;
	int noAtelier;

	CL_Agriculteur *agri;
	CL_Atelier *atelier;
	CL_Verger *verger;
	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		noAgri = adoTable->FieldByName("NoAgri")->AsString.ToInt();
		agri = V_Agriculteur->trouve(noAgri);

		noAtelier = adoTable->FieldByName("NoAtelier")->AsString.ToInt();
//??    	noAtelier=adoTable->FieldByName("NoAtel")->AsString.ToInt();
		switch (nature) {
		case PERENNE:
			atelier = V_Perenne->trouve(noAtelier);
			break;
		case VIVRIER:
			atelier = V_Vivrier->trouve(noAtelier);
			break;
		}

		verger = new CL_Verger();
		verger->NoAtelier = noAtelier;
		verger->Atelier = atelier;
		if (nature == PERENNE) {
			verger->Espece = atelier->Espece;
			verger->NoEspece = verger->Espece->No;
		}
		verger->AnPlant = adoTable->FieldByName("AnPlant")->AsString.ToInt();
		verger->AnArr = adoTable->FieldByName("AnArr")->AsString.ToInt();
		verger->Surface = adoTable->FieldByName("Surface")->AsString.ToDouble();

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

		adoTable->Next();

	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireValeur(TADOTable *adoTable, float *valeur, int nbVal) {
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

}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriFormule(TADOTable *adoTable, AnsiString nomTable,
		int nature) {
	int n;
	int noAgri;
	int noItem;

	CL_Agriculteur *agri;
	CL_Item *item;
	CL_Formule *formule;
	CL_Prog *prog;
	CL_Arbre *arbre;
//ST_Branche     *branche;

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		noAgri = adoTable->FieldByName("NoAgri")->AsString.ToInt();
		agri = V_Agriculteur->trouve(noAgri);

		noItem = adoTable->FieldByName("NoItem")->AsString.ToInt();
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
		}
		formule = new CL_Formule();
		formule->Item = item;

		LireValeur(adoTable, formule->Valeur);

		for (n = 0; n < N_X; n++) {
			prog = new CL_Prog();
			arbre = new CL_Arbre();
			arbre->LesBranches[0].code = 301; //NOMBRE
			arbre->BrancheX = 1;
			for (int i = 0; i < 3; i++)
				arbre->LesBranches[0].arg[i] = -1;
			arbre->LesBranches[0].valeur = formule->Valeur[n];
			arbre->LesBranches[0].type = 302; //NUM
			prog->Arbre = arbre;
			formule->LesProg[n] = prog;
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
		}
		adoTable->Next();

	}
}
//---------------------------------------------------------------------------
void TLireAccessFrm::LireR_AgriVariable(TADOTable *adoTable,
		AnsiString nomTable) {
	int noAgri;
	int noItem;
	CL_Item *item;
	CL_Valeur *valeur;

	CL_Agriculteur *agri;
	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		noAgri = adoTable->FieldByName("NoAgri")->AsString.ToInt();
		agri = V_Agriculteur->trouve(noAgri);

		noItem = adoTable->FieldByName("NoItem")->AsString.ToInt();
		item = V_Variable->trouve(noItem);
		valeur = new CL_Valeur();
		valeur->Item = item;
		valeur->NoAtelier = -1; // ??voir le constructeur
		valeur->Atelier = NULL;

		LireValeur(adoTable, valeur->Valeur);

		agri->V_Variable->insSans(valeur);

		adoTable->Next();

	}
}
