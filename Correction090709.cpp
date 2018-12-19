//---------------------------------------------------------------------------

#pragma hdrstop

#include "Correction090709.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
// MODIFIER ACCESS
//                          adoTable->FieldValues["Origine"]=formule->Origine;

//---------------------------------------------------------------------------
void TEcrireAccessFrm::EcrireAgriFormule(TADOTable *adoTable,
		AnsiString nomTable, int nature, CL_Vecteur<CL_Agriculteur> *vAgri,
		TADOQuery *adoQuery) {
	int n, i, l;
	CL_Agriculteur *agri;
	CL_Formule *formule;
	CL_Vecteur<CL_Formule> *vFormule;

//CL_Prog        *prog;
//CL_Arbre       *arbre;

	AnsiString annee;

	for (n = 0; n < vAgri->Nbelt; n++) {
		agri = vAgri->Vecteur[n];

		MajTable(adoTable, nomTable);

		formule = new CL_Formule();

		switch (nature) {
		case PRODUIT:
			vFormule = agri->V_Produits;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 1;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case CHARGE:
			vFormule = agri->V_Charges;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 2;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case CHSTRUCT:
			vFormule = agri->V_ChStruct;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 3;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case RECDIV:
			vFormule = agri->V_RecDiv;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 4;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case RECFAM:
			vFormule = agri->V_RecFam;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 6;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case DEPDIV:
			vFormule = agri->V_DepDiv;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 5;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case DEPFAM:
			vFormule = agri->V_DepFam;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 7;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case EXTPOS:
			vFormule = agri->V_ExtPos;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 8;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;

		case EXTNEG:
			vFormule = agri->V_ExtNeg;
			for (i = 0; i < vFormule->Nbelt; i++) {
				adoTable->Append();
				formule = vFormule->Vecteur[i];
				adoTable->FieldValues["NoAgri"] = agri->No;
				adoTable->FieldValues["NoItem"] = formule->Item->No;
//                          adoTable->FieldValues["Origine"]=formule->Origine;
				adoTable->FieldValues["IdList"] = 9;
				for (l = 0; l < 10; l++) {
					AnsiString an = "An";
					annee = AnsiString(an + (l + 1));
					adoTable->FieldValues[annee] = formule->Valeur[l];
				}
				adoTable->Post();
				ProgressBar1->StepIt();
			}
			break;
		}
	}
}

//---------------------------------------------------------------------------
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
	char origine;
//ST_Branche     *branche;
	AnsiString asFormule; //!!

	MajTable(adoTable, nomTable);

	adoTable->First();
	while (!adoTable->Eof) {
		noAgri = adoTable->FieldByName("NoAgri")->AsString.ToInt();
		agri = V_Agriculteur->trouve(noAgri);

		noItem = adoTable->FieldByName("NoItem")->AsString.ToInt();
		origine = adoTable->FieldByName("Origine")->AsString.ToInt(); //AsString pas ok
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
		formule->No = noItem; //020908
		formule->Origine = origine; //090708
// a tester
				/*
				 asFormule=adoTable->FieldByName("An1")->AsString;
				 ErreurFrm->Edit->Clear();
				 Compil->Erreur=false;
				 Compil->Compiler(asFormule.c_str());
				 if(Compil->Erreur==true)return false;//il y a erreur et c'est affiché



				 */
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
void TEcrireAccessFrm::EcrireAgri_Critere(TADOTable *adoTable,
		AnsiString nomTable, CL_Vecteur<CL_Agriculteur> *vAgri) {
	CL_Agriculteur *agri;
	CL_Item *critere;
	int nbCritere;
	int n;

	MajTable(adoTable, nomTable);

	for (n = 0; n < vAgri->Nbelt; n++) {
		adoTable->Append();

		agri = vAgri->Vecteur[n];

//    	adoTable->FieldValues["NoAgri"]=agri->No;

		nbCritere = agri->LstCritere->Count;
		for (int i = 0; i < nbCritere; i++) {
			adoTable->FieldValues["NoAgri"] = agri->No;
			critere = (CL_Item*) agri->LstCritere->Items[i];
			adoTable->FieldValues["NoCritere"] = critere->No;
		}
		adoTable->Post();
		ProgressBar1->StepIt();
	}

}

