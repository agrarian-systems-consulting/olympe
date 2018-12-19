//---------------------------------------------------------------------------
//-------------------------------- -------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <dir.h>
#include <vcl.h>
#include <stdio.h>
using namespace std;

#pragma package(smart_init)

#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Main.h"
#include "FichierLire.h"

#include "Compilateur.h"
#include "CL_Matrice.h"

//extern
#include "Olympe.hse"
#include "LesVecteurs.hse"

#include "FichierEcrireXml.h"
extern CL_ES *ES;
extern CL_Compil *Compil;
extern CL_Xml *Xml;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void CL_Xml::EcrireFichier(void) {
	AnsiString date;
	TDateTime time;
	ofstream outfile(NomFichier);

	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();
	outfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> " << endl;
	outfile << "<Olympe>" << endl;
	outfile << "<!--" << date << "-->" << endl;

	V_SystemeUnite->EcrireXml(outfile, "LesSystemeUnite", "SystemeUnite", 0);
	V_Tva->EcrireXml(outfile, "LesTva", "tva", 0);
	LesTvaDefaut(outfile);

	EcrireFamilleItem(outfile, V_CatProduit, V_Produit, "LesProduits");
	EcrireFamilleItem(outfile, V_CatCharge, V_Charge, "LesCharges");
	EcrireFamilleItem(outfile, V_CatExternalite, V_Externalite,
			"LesExternalites", 1);

	EcrireFamilleBestiaux(outfile, V_CatBestiaux, V_Bestiaux, "LesTroupeaux");

	V_Calendrier->EcrireXml(outfile, "LesCalendriers", "Calendrier", 0);

	EcrireFamilleItem(outfile, V_CatChStruct, V_ChStruct, "LesChargesStructure",
			2);

	EcrireFamilleItem(outfile, V_CatDepDiv, V_DepDiv, "LesDepensesDiverses", 2);
	EcrireFamilleItem(outfile, V_CatRecDiv, V_RecDiv, "LesRecettesDiverses", 2);

	EcrireFamilleItem(outfile, V_CatRecFam, V_RecFam, "LesRecettesPrivees", 2);
	EcrireFamilleItem(outfile, V_CatDepFam, V_DepFam, "LesDepensesPrivees", 2);
	EcrireFamilleItem(outfile, V_CatVar, V_Variable, "LesVariables", 1);

	V_Espece->EcrireXml(outfile, "LesEspeces", "Espece", 0);

	EcrireFamilleAtelier(outfile, V_CatCulture, V_Culture, "LesCultures",
			"Culture");
	EcrireFamilleAtelier(outfile, V_CatAnimaux, V_Animaux, "LesAnimaux",
			"Animal");
	EcrireFamilleAtelier(outfile, V_CatVivrier, V_Vivrier, "LesVivriers",
			"Vivrier");

	EcrireFamillePerenne(outfile, V_Espece, V_Perenne, "LesPerennes",
			"Perenne");

	EcrireFamilleIndicateur(outfile, "LesIndicateurs");

	EcrireLesAleas(outfile, "LesAleas");

	EcrireFamilleItem(outfile, V_CatTypeZone, V_TypeZone, "LesClassifications",
			0);

	V_Agriculteur->EcrireXml(outfile, "LesAgriculteurs", "Agriculteur", 0);

	V_Ensemble->EcrireXml(outfile, "LesEnsembles", "Ensemble", 0);

	outfile << "</Olympe>" << endl;
	outfile.close();

}
//-----------------------------------------------------------
template<class T>
void CL_Vecteur<T>::EcrireXml(ofstream &fichier, char *nomV, char *nomE,
		int nb) {
	string balise;
	int i;
	T* ptr;
	if (Nbelt == 0)
		return;

	balise = "<" + string(nomV) + ">";
	fichier << balise << endl;
	for (i = 0; i < Nbelt; i++) {
		ptr = Vecteur[i];
		if (ptr == NULL)
			continue;

		ptr->EcrireXml(fichier, nomE, nb);
	}
	balise = "</" + string(nomV) + ">";
	fichier << balise << endl;
}
//-----------------------------------------------------------
void CL_Xml::EcrireFamilleItem(ofstream &fichier,
		CL_Vecteur<CL_Categorie> *vCat, CL_Vecteur<CL_Item> *vItem,
		char *nomFamille, int type) {
	int i, j;
	CL_Categorie *cat;
	CL_Item *item;
	if (vCat->Nbelt == 0)
		return;
	Xml->baliseDebut(fichier, nomFamille);

	for (i = 0; i < vCat->Nbelt; i++) {
		cat = vCat->Vecteur[i];
		Xml->baliseDebut(fichier, "categorie", "nom", cat->Nom);
		for (j = 0; j < vItem->Nbelt; j++) {
			item = vItem->Vecteur[j];
			if (item->Categorie != cat)
				continue;
			switch (type) {
			case 0:
				fichier << "<" << "Item";
				Xml->ecrire(fichier, "nom", item->Nom);
				break;
			case 1:
				fichier << "<" << "Item";
				Xml->ecrire(fichier, "nom", item->Nom);
				Xml->ecrire(fichier, "unite", item->SysUnite->UTrans);
				break;
			case 2:
				fichier << "<" << "Item";
				Xml->ecrire(fichier, "nom", item->Nom);
				Xml->ecrire(fichier, "tva", item->Tva->Nom);
				break;
			case 3:
				fichier << "<" << "Item";
				Xml->ecrire(fichier, "nom", item->Nom);
				Xml->ecrire(fichier, "prix", item->Prix);
				Xml->ecrire(fichier, "unite", item->SysUnite->UTrans);
				Xml->ecrire(fichier, "tva", item->Tva->Nom);
				break;
			}
			fichier << "/>" << endl;
		}
		Xml->baliseFin(fichier, "categorie");
	}
	fichier << "</" << nomFamille << ">" << endl;

}
//-----------------------------------------------------------------
//bestiaux
//-----------------------------------------------------------
void CL_Xml::EcrireFamilleBestiaux(ofstream &fichier,
		CL_Vecteur<CL_Categorie> *vCat, CL_Vecteur<CL_Bestiaux> *vBestiaux,
		char *nomFamille) {
	int i, j, k;
	CL_Categorie *cat;
	CL_Bestiaux *bestiaux; //,*origine;//,*veaux;
	TList *lstTroupeau;
	lstTroupeau = new TList;
	Xml->baliseDebut(fichier, "lesTroupeaux");

	for (i = 0; i < vCat->Nbelt; i++) {
		lstTroupeau->Clear();
		cat = vCat->Vecteur[i];
		Xml->baliseDebut(fichier, "troupeau", "nom", cat->Nom);

		// je crée une liste avec tous les bestiaux de la categorie==troupeau
		for (j = 0; j < vBestiaux->Nbelt; j++) {
			bestiaux = vBestiaux->Vecteur[j];
			if (bestiaux->Categorie != cat)
				continue;
			lstTroupeau->Add(bestiaux);
		}
		for (j = 0; j < lstTroupeau->Count; j++) {
			bestiaux = (CL_Bestiaux*) lstTroupeau->Items[j];
			fichier << "<" << "animal" << " ";
			Xml->ecrire(fichier, "nom", bestiaux->Nom);
			Xml->ecrire(fichier, "valInv", bestiaux->ValInv);
			Xml->ecrire(fichier, "prix", bestiaux->Prix);
			Xml->ecrire(fichier, "tva", bestiaux->Tva->Nom);
			fichier << ">" << endl;

			if (bestiaux->NoOrigine != -1) {
				baliseDebutFin(fichier, "origine", "no", bestiaux->NoOrigine);
			}

			for (k = 0; k < 4; k++) {
				if (bestiaux->DonnePcent[k] == 0)
					continue;
				fichier << "<genere" << " ";
				Xml->ecrire(fichier, "no", bestiaux->DonneNo[k]);
				Xml->ecrire(fichier, "taux", bestiaux->DonnePcent[k]);
				fichier << "/>" << endl;
			}

			fichier << "</animal>" << endl;
		}

		fichier << "</troupeau>" << endl;
	}

	fichier << "</lesTroupeaux>" << endl;
	delete lstTroupeau;
}
//-----------------------------------------------------------
//atelier
//-----------------------------------------------------------
void CL_Xml::EcrireFamilleAtelier(ofstream &fichier,
		CL_Vecteur<CL_Categorie> *vCat, CL_Vecteur<CL_Atelier> *vAtelier,
		char *nomFamille, char *nomType) {
	int i, j, k;
	int n;
	int iX, jX;
	int ik, jk;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	CL_BesTrav *besTrav;
	CL_Periode *periode;
	CL_Matrice *matrice;
	CL_EEF *eEF;
	if (vCat->Nbelt == 0)
		return;

	fichier << "<" << nomFamille << ">" << endl;

	for (i = 0; i < vCat->Nbelt; i++) {
		cat = vCat->Vecteur[i];
		Xml->baliseDebut(fichier, "categorie", "nom", cat->Nom);

		for (j = 0; j < vAtelier->Nbelt; j++) {
			atelier = vAtelier->Vecteur[j];
			if (atelier->Categorie != cat)
				continue;
			fichier << "<" << nomType << " ";
			Xml->ecrire(fichier, "nom", atelier->Nom);
			Xml->ecrire(fichier, "nbPhase", atelier->NbPhase);
			fichier << ">" << endl;

			if (atelier->Derobe == true)
				fichier << "<derobe/>" << endl;

			atelier->V_Produit->EcrireXml(fichier, "LesProduits", "Produit",
					atelier->NbPhase);
			atelier->V_Charge->EcrireXml(fichier, "LesCharges", "Charge",
					atelier->NbPhase);
			atelier->V_ChargeVolume->EcrireXml(fichier, "LesChargesVolume",
					"Charge", atelier->NbPhase);
			atelier->V_Externalite->EcrireXml(fichier, "LesExternalites",
					"Externalite", atelier->NbPhase);
			if (atelier->V_Avance->Nbelt > 0) {
				fichier << "<lesAvances>" << endl;
				for (k = 0; k < atelier->V_Avance->Nbelt; k++) {
					eEF = atelier->V_Avance->Vecteur[k];
					fichier << "<avance" << " ";
					Xml->ecrire(fichier, "debut", eEF->Deb);
					Xml->ecrire(fichier, "fin", eEF->Fin);
					Xml->ecrire(fichier, "valeur", eEF->Val);
					fichier << "/>" << endl;
				}
				fichier << "</lesAvances>" << endl;
			}

			if (atelier->V_BesTrav->Nbelt > 0) {
				fichier << "<lesBesTravail>" << endl;

				for (k = 0; k < atelier->V_BesTrav->Nbelt; k++) {
					besTrav = atelier->V_BesTrav->Vecteur[k];
					fichier << "<besTravail" << " ";
					Xml->ecrire(fichier, "nom", besTrav->Calendrier->Nom);
					Xml->ecrire(fichier, "nbPhase", besTrav->NbPhase);
					Xml->ecrire(fichier, "nbPeriode", besTrav->NbPeriodeCal);
					fichier << ">" << endl;

					matrice = besTrav->Besoins;
					iX = matrice->iX;
					jX = matrice->jX;

					for (ik = 0; ik < iX; ik++) {
						periode = besTrav->Calendrier->V_Periode->Vecteur[ik];
						fichier << "<periode";
						Xml->ecrire(fichier, "nom", periode->Nom);
						fichier << " valeur=" << "\" ";
						for (jk = 0; jk < jX; jk++) {
							n = ik + jk * iX;
							fichier << matrice->X[n] << " ";
						}
						fichier << "\"/>" << endl;
					}
					fichier << "</besTravail>" << endl;
				}
				fichier << "</lesBesTravail>" << endl;
			}
			fichier << "</" << nomType << ">" << endl;
		}
		fichier << "</categorie>" << endl;
	}
	fichier << "</" << nomFamille << ">" << endl;
}
//-----------------------------------------------------------
//perenne
//-----------------------------------------------------------
void CL_Xml::EcrireFamillePerenne(ofstream &fichier,
		CL_Vecteur<CL_Espece> *vEspece, CL_Vecteur<CL_Atelier> *vAtelier,
		char *nomFamille, char *nomType) {
	int i, j;
	CL_Espece *espece;
	CL_Atelier *atelier;
	char buf[200];
	if (vEspece->Nbelt == 0)
		return;

	fichier << "<" << nomFamille << ">" << endl;

	for (i = 0; i < vEspece->Nbelt; i++) {
		espece = vEspece->Vecteur[i];
		sprintf(buf, "<Espece nom= \"%s\" >", espece->Nom.c_str());
		fichier << buf << endl;

		for (j = 0; j < vAtelier->Nbelt; j++) {
			atelier = vAtelier->Vecteur[j];
			if (atelier->Espece != espece)
				continue;

			sprintf(buf, "<%s nom= \"%s\"  nbPhase= \"%d\"  >", nomType,
					atelier->Nom, atelier->NbPhase);
			fichier << buf << endl;

			atelier->V_Produit->EcrireXml(fichier, "LesProduits", "Produit",
					atelier->NbPhase);
			atelier->V_Charge->EcrireXml(fichier, "LesCharges", "Charge",
					atelier->NbPhase);
			atelier->V_ChargeVolume->EcrireXml(fichier, "LesChargesVolume",
					"Charge", atelier->NbPhase);
			atelier->V_Externalite->EcrireXml(fichier, "LesExternalites",
					"Externalite", atelier->NbPhase);

			fichier << "</" << nomType << ">" << endl;
		}
		fichier << "</Espece>" << endl;
	}
	fichier << "</" << nomFamille << ">" << endl;
}
//-----------------------------------------------------------
//indicateur
//-----------------------------------------------------------
void CL_Xml::EcrireFamilleIndicateur(ofstream &fichier, char *nomFamille) {
	int i, j;
	CL_Categorie *cat;
	CL_Indicateur *indic;
	if (V_CatIndic->Nbelt == 0)
		return;
	Xml->baliseDebut(fichier, nomFamille);

	for (i = 0; i < V_CatIndic->Nbelt; i++) {
		cat = V_CatIndic->Vecteur[i];
		Xml->baliseDebut(fichier, "categorie", "nom", cat->Nom);

		for (j = 0; j < V_Indicateur->Nbelt; j++) {
			indic = V_Indicateur->Vecteur[j];
			if (indic->Categorie != cat)
				continue;
			Xml->baliseDebut(fichier, "indicateur", "nom", indic->Nom);

			if (indic->Nom == "dt rec autres végétaux") {
				int idx = 0;
			}
			fichier << "<formule>" << endl;
			fichier << "<![CDATA[" << endl;
			Compil->ReEcritFormule(indic->Prog);
			fichier << indic->Prog->Source;
			fichier << "]]>" << endl;
			fichier << endl << "</formule>" << endl;
			Xml->baliseFin(fichier, "indicateur");
		}
		Xml->baliseFin(fichier, "categorie");
	}
	Xml->baliseFin(fichier, nomFamille);
}

//-----------------------------------------------------------
//aleas
//-----------------------------------------------------------
void CL_Xml::EcrireLesAleas(ofstream &fichier, char *nomFamille) {
	if (V_TendPrixProd->Nbelt + V_TendPrixCharge->Nbelt + V_ScenPrixProd->Nbelt
			+ V_ScenPrixCharge->Nbelt + V_TendQProd->Nbelt
			+ V_TendQCharge->Nbelt + V_TendQExt->Nbelt + V_ScenQProd->Nbelt
			+ V_ScenQCharge->Nbelt + V_ScenQExt->Nbelt) {
		fichier << "<lesAleas>" << endl;

		if (V_TendPrixProd->Nbelt + V_TendPrixCharge->Nbelt
				+ V_ScenPrixProd->Nbelt + V_ScenPrixCharge->Nbelt) {
			fichier << "<lesAleasPrix>" << endl;
			if (V_TendPrixProd->Nbelt + V_TendPrixCharge->Nbelt) {
				{
					fichier << "<lesTendancesPrix>" << endl;
					V_TendPrixProd->EcrireXml(fichier, "lesProduits", "produit",
							0);
					V_TendPrixCharge->EcrireXml(fichier, "lesCharges", "charge",
							0);
					fichier << "</lesTendancesPrix>" << endl;
				}
			}
			if (V_ScenPrixProd->Nbelt + V_ScenPrixCharge->Nbelt) {
				fichier << "<lesScenariosPrix>" << endl;
				V_ScenPrixProd->EcrireXml(fichier, "lesProduits", "produit", 0);
				V_ScenPrixCharge->EcrireXml(fichier, "lesCharges", "charge", 0);
				fichier << "</lesScenariosPrix>" << endl;
			}
			fichier << "</lesAleasPrix>" << endl;
		}
		if (V_TendQProd->Nbelt + V_TendQCharge->Nbelt + V_TendQExt->Nbelt
				+ V_ScenQProd->Nbelt + V_ScenQCharge->Nbelt
				+ V_ScenQExt->Nbelt) {
			fichier << "<lesAleasQuantite>" << endl;
			if (V_TendQProd->Nbelt + V_TendQCharge->Nbelt + V_TendQExt->Nbelt) {
				fichier << "<lesTendancesQuant>" << endl;
				V_TendQProd->EcrireXml(fichier, "lesProduits", "produit", 0);
				V_TendQCharge->EcrireXml(fichier, "lesCharges", "charge", 0);
				V_TendQExt->EcrireXml(fichier, "lesExternalites", "externalite",
						0);
				fichier << "</lesTendancesQuant>" << endl;
			}

			if (V_ScenQProd->Nbelt + V_ScenQCharge->Nbelt + V_ScenQExt->Nbelt) {
				fichier << "<lesScenariosQuant>" << endl;
				V_ScenQProd->EcrireXml(fichier, "lesProduits", "produit", 0);
				V_ScenQCharge->EcrireXml(fichier, "lesCharges", "charge", 0);
				V_ScenQExt->EcrireXml(fichier, "lesExternalites", "externalite",
						0);
				fichier << "</lesScenariosQuant>" << endl;
			}
			fichier << "</lesAleasQuantite>" << endl;
		}

		fichier << "</lesAleas>" << endl;
	}

}
//------------------------------------------------------------------------------
void CL_Tendance::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	CL_Delta* delta;
	int i;
	char *nature;
	Xml->baliseDebut(fichier, "tendance", "nom", Nom);
//    fichier << "<tendance  " << "Nom= " << Nom <<endl;
	for (i = 0; i < V_Delta->Nbelt; i++) {
		delta = V_Delta->Vecteur[i];
		fichier << "<delta " << " ";
		if (delta->Item) {
			Xml->ecrire(fichier, "nom", delta->Item->Nom);
			Xml->ecrire(fichier, "categorie", delta->Item->Categorie->Nom);
		}
		if (delta->Atelier) {
			Xml->ecrire(fichier, "atelier", delta->Atelier->Nom);
			if (delta->Atelier->Categorie) {
				switch (delta->Atelier->Nature) {
				case ANIMAUX:
					nature = "animaux";
					break;
				case CULTURE:
					nature = "culture";
					break;
				case PERENNE:
					nature = "perenne";
					break;
				case VIVRIER:
					nature = "vivrier";
					break;
				}
				Xml->ecrire(fichier, nature, delta->Atelier->Categorie->Nom);
			}
			if (delta->Atelier->Espece)
				Xml->ecrire(fichier, "espece", delta->Atelier->Espece->Nom);
		}
		Xml->ecrire(fichier, "valeur", delta->Pcent, N_X);

		fichier << "/>" << endl;
	}

	fichier << "</tendance>" << endl;
}
//-----------------------------------------------------------
void CL_SystemeUnite::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";
	Xml->ecrire(fichier, "uAtelier", UUt);
	Xml->ecrire(fichier, "uEntreprise", UTrans);
	Xml->ecrire(fichier, "uRegion", UGlobal);
	Xml->ecrire(fichier, "ratio21", Ratio);
	Xml->ecrire(fichier, "ration32", RatioG);
	Xml->ecrire(fichier, "monnaie", Monnaie);
	fichier << "/>" << endl;

}
//----------------------------------------------------------------
void CL_Tva::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE;
	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "taux", Taux);
	fichier << "/>" << endl;
}
//----------------------------------------------------------------
void CL_Xml::LesTvaDefaut(ofstream &fichier) {
	char buf[200];
	fichier << "<LesTvaDefaut>" << endl;

	sprintf(buf, "<TvaDefaut nom= \"%s\"  />", TvaDefaut->Nom);
	fichier << buf << endl;
	sprintf(buf, "<TvaImmo nom= \"%s\"  />", TvaImmo->Nom);
	fichier << buf << endl;

	fichier << "</LesTvaDefaut>" << endl;
}
//---------------------------------------------------------------------------
void CL_Categorie::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	Xml->baliseDebut(fichier, nomE, "nom", Nom);
}
//----------------------------------------------------------------
void CL_Item::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE;
	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "categorie", Categorie->Nom);
	Xml->ecrire(fichier, "prix", Prix);
	Xml->ecrire(fichier, "tva", Tva->Nom);
	fichier << "/>" << endl;
}
//---------------------------------------------------------------------------
void CL_Repart::EcrireXml(ofstream &fichier, char *nomE, int nb) {
}
//----------------------------------------------------------------
void CL_ItemRepart::EcrireXml(ofstream &fichier, char *nomE, int nb) {
}
//-----------------------------------------------------------------
void CL_Espece::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";
	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "debAmor", DebAmor);
	Xml->ecrire(fichier, "maxi", DurAmor);
	Xml->ecrire(fichier, "phase", Phase, NbPhase);
	fichier << "/>" << endl;
}
//-----------------------------------------------------------------
void CL_Bestiaux::EcrireXml(ofstream &fichier, char *nomE, int nb) {
//non utilisé
}
// entier entier flottant
//----------------------------------------------------------------
void CL_EEF::EcrireXml(ofstream &fichier, char *nomE, int nb) {
}
//----------------------------------------------------------------
void CL_Atelier::EcrireXml(ofstream &fichier, char *nomE, int nb) {

	fichier << "<" << nomE << " ";
	Xml->ecrire(fichier, "nom", Nom);
	if (Espece)
		Xml->ecrire(fichier, "espece", Espece->Nom);
	else
		Xml->ecrire(fichier, "categorie", Categorie->Nom);
	Xml->ecrire(fichier, "nbPhase", NbPhase);
	fichier << ">" << endl;

	V_Produit->EcrireXml(fichier, "lesProduits", "produit", NbPhase);
	V_Charge->EcrireXml(fichier, "lesCharges", "charge", NbPhase);
	V_ChargeVolume->EcrireXml(fichier, "lesChargesVolume", "charge", NbPhase);
	V_Externalite->EcrireXml(fichier, "lesExternalites", "externalite",
			NbPhase);

	fichier << "</" << nomE << ">" << endl;
}
//----------------------------------------------------------------
void CL_ItemParAtelier::EcrireXml(ofstream &fichier, char *nomE, int nbPhase) {
	int n;
	if (Item) {
		fichier << "<" << nomE << " ";
		Xml->ecrire(fichier, "nom", Item->Nom);
		Xml->ecrire(fichier, "categorie", Item->Categorie->Nom);
		fichier << ">" << endl;
	} else if (ItemPA) {
		if (Charge == NULL)
			return;

		fichier << "<" << nomE << " ";
		Xml->ecrire(fichier, "nomProduit", ItemPA->Item->Nom);
		Xml->ecrire(fichier, "catProduit", ItemPA->Item->Categorie->Nom);
		Xml->ecrire(fichier, "nomCharge", Charge->Nom);
		Xml->ecrire(fichier, "catCharge", Charge->Categorie->Nom);
		fichier << ">" << endl;

	} else
		return;

	for (n = 0; n < nbPhase; n++) {
		if (QtePhase[n]) {
			fichier << "<phase" << " ";
			Xml->ecrire(fichier, "n", n);
			Xml->ecrire(fichier, "val", QtePhase[n]);
			fichier << "/>" << endl;
		}
	}
	fichier << "</" << nomE << ">" << endl;
}

//------------------------------------------------------------------------------
void CL_Calendrier::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	Xml->baliseDebut(fichier, nomE, "nom", Nom);

	V_Periode->EcrireXml(fichier, "lesPeriodes", "periode", 0);

	Xml->baliseFin(fichier, nomE);

}
//------------------ ------------------------------------------------------------
void CL_Periode::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";
	Xml->ecrire(fichier, "debut", JDeb, MDeb);
	Xml->ecrire(fichier, "fin", JFin, MFin);
	Xml->ecrire(fichier, "heureParJour", HpJ);
	Xml->ecrire(fichier, "pcentDispo", PcentDispo);
	fichier << "/>" << endl;

}
//---------------------------------------------------------------------------
void CL_Indicateur::EcrireXml(ofstream &fichier, char *nomE, int nb) {
}

//----------------------------------------------------------------------------
void CL_EtatSortie::EcrireXml(ofstream &fichier, char *nomE, int nb) {
}
//------------------------------------------------------------------------------
void CL_Conversion::EcrireXml(ofstream &fichier, char *nomE, int nb) {
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void CL_Agriculteur::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	int n;
	char buf[200];
	CL_Item *critere;
	fichier << "<" << "agriculteur" << " ";
	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "noVariante", NoVariante);
	fichier << ">";

	DefSim->EcrireXml(fichier, "definition", 0);

	Xml->ecrireTxt(fichier, "notes", Notes);

	if (LstCritere->Count) {
		fichier << "<Classification>" << endl;
		for (n = 0; n < LstCritere->Count; n++) {
			critere = (CL_Item*) LstCritere->Items[n];
			sprintf(buf, "<critere categorie= \"%s\" nom=\"%s\" />",
					critere->Categorie->Nom, critere->Nom);
			fichier << buf;
		}
		fichier << "</Classification>" << endl;
	}

	V_Culture->EcrireXml(fichier, "Assolement", "Culture", 0);
	V_Animaux->EcrireXml(fichier, "LesAnimaux", "Animal", 0);
	V_Verger->EcrireXml(fichier, "LesPerennes", "Perenne", PERENNE);
	V_Vivrier->EcrireXml(fichier, "LesVivriers", "Vivrier", VIVRIER);

	if (LstTroupeaux->Count)
		Xml->EcrireLesTroupeaux(fichier, LstTroupeaux);

	V_Produits->EcrireXml(fichier, "LesProduits", "Produit", 0);
	V_Charges->EcrireXml(fichier, "LesCharges", "Charge", 0);

	V_ChStruct->EcrireXml(fichier, "LesChargesStruct", "ChargeStruct", 0);

	V_RecDiv->EcrireXml(fichier, "LesRecettesDiverses", "RecetteDiverse", 0);
	V_DepDiv->EcrireXml(fichier, "LesDepensesDiverses", "DepenseDiverse", 0);
	V_RecFam->EcrireXml(fichier, "LesRecettesFamiliales", "RecetteFamiliale",
			0);
	V_DepFam->EcrireXml(fichier, "LesDepensesFamiliales", "RecetteFamiliale",
			0);

	V_ExtPos->EcrireXml(fichier, "LesExternalitesPositives",
			"ExternalitePositive", 0);
	V_ExtNeg->EcrireXml(fichier, "LesExternalitesNegatives",
			"ExternaliteNegative", 0);

	V_Variable->EcrireXml(fichier, "LesVariables", "Variable", 0);

	//immo
	V_Immo->EcrireXml(fichier, "LesMateriels", "Materiel", 0);

	Xml->EcrireAgriPetit(fichier, V_Petit);
	if (V_InvSom->Nbelt)
		Xml->EcrireV_InvSom(fichier, V_InvSom);

	//financement
	V_EmpLT->EcrireXml(fichier, "LesEmpruntsLT", "EmpruntLT", 0);
	V_EmpCT->EcrireXml(fichier, "LesEmpruntsCT", "EmpruntCT", 0);
	V_Sub->EcrireXml(fichier, "LesSubventions", "Subvention", 0);
	V_Occc->EcrireXml(fichier, "LesOccc", "Occc", 0);
	V_Plact->EcrireXml(fichier, "LesPlacements", "Placement", 0);
	if (V_FinSom->Nbelt)
		Xml->EcrireV_FinSom(fichier, V_InvSom);
	//creances dettes stocks
	V_Creance->EcrireXml(fichier, "LesCreances", "Creance", 0);
	V_Dette->EcrireXml(fichier, "LesDettes", "Dette", 0);
	V_StockIni->EcrireXml(fichier, "LesStocks", "Stock", 0);

	V_PolStock->EcrireXml(fichier, "LesPolitiquesStockage", "PolStock", 0);

	fichier << "</agriculteur>";
}

//  <Definition An_0="2004" NbAnSim="10" MDeb="1" AnCalage="0" TypeAlea="1" QProd="w" QCharge="alea 80 charge" />

//-----------------------------------------------------------
void CL_AgriDefSim::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << endl;
	fichier << "<" << nomE;
	Xml->ecrire(fichier, "An_0", An_0);
	Xml->ecrire(fichier, "NbAnSim", NbAnSim);
	Xml->ecrire(fichier, "MDeb", MDeb);
	Xml->ecrire(fichier, "AnCalage", AnCalage);
	switch (TypeAlea) {
	case SANS:
		Xml->ecrire(fichier, "TypeAlea", "Sans");
		break;
	case TENDANCE:
		Xml->ecrire(fichier, "TypeAlea", "Tendance");
		break;
	case ENCHDEF:
		Xml->ecrire(fichier, "TypeAlea", "Enchainement");
		break;
	}
	fichier << ">" << endl;

	if (PrixProd)
		Xml->baliseDebutFin(fichier, "alea", "PrixProd", PrixProd->Nom);
	if (PrixCharge)
		Xml->baliseDebutFin(fichier, "alea", "PrixCharge", PrixCharge->Nom);
	if (QProd)
		Xml->baliseDebutFin(fichier, "alea", "QProd", QProd->Nom);
	if (QCharge)
		Xml->baliseDebutFin(fichier, "alea", "QCharge", QCharge->Nom);
	if (QExt)
		Xml->baliseDebutFin(fichier, "alea", "QExt", QExt->Nom);

	if (TypeAlea == ENCHDEF) {
		fichier << "<enchainement";
		Xml->ecrire(fichier, "typeAnnee", Enchainement, N_X);
		fichier << "/>" << endl;
	}
	fichier << "<" << "/" << nomE << ">" << endl;

}
//-----------------------------------------------------------
void CL_Valeur::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	int n;
	int an;
	for (n = 0; n < N_X; n++) {
		if (Valeur[n] == 0)
			continue;

		an = Xml->An_0 + n;
		fichier << "<" << nomE;
		if (Atelier) {
			Xml->ecrire(fichier, "nom", Atelier->Nom); // nom= "Blé"
			Xml->ecrire(fichier, "categorie", Atelier->Categorie->Nom); // categorie="céréales"
		} else if (Item) {
			Xml->ecrire(fichier, "nom", Item->Nom);
			Xml->ecrire(fichier, "categorie", Item->Categorie->Nom);
		}
		Xml->ecrire(fichier, "annee", an);
		Xml->ecrire(fichier, "valeur", Valeur[n]);
		fichier << "/>" << endl;
	}
}
//-----------------------------------------------------------------
void CL_Verger::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	int duree;
	CL_Espece *espece;

	espece = V_Espece->trouve(Atelier->NoEspece);
	fichier << "<" << nomE << " ";
	Xml->ecrire(fichier, "nom", Atelier->Nom);
	Xml->ecrire(fichier, "espece", espece->Nom);
	Xml->ecrire(fichier, "surface", Surface);
	Xml->ecrire(fichier, "AnPlant", AnPlant);
	if (nb == PERENNE) //perenne
		Xml->ecrire(fichier, "AnArr", AnArr);
	else if (nb == VIVRIER) {
		duree = AnArr - AnPlant;
		Xml->ecrire(fichier, "duree", duree);
	}
	fichier << "/>";
}
//-----------------------------------------------------------------
void CL_Xml::EcrireLesTroupeaux(ofstream &fichier, TList *lst) {
	int n;
	CL_Troupeau *troupeau;
	fichier << "<lesTroupeaux>" << endl;
	for (n = 0; n < lst->Count; n++) {
		troupeau = (CL_Troupeau*) lst->Items[n];
		troupeau->EcrireXml(fichier, "troupeau", 0);
	}
	fichier << "</lesTroupeaux>" << endl;
}
//-----------------------------------------------------------
void CL_Troupeau::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<troupeau";
	Xml->ecrire(fichier, "nom", CatBestiaux->Nom);
	fichier << ">" << endl;
	V_InvAni->EcrireXml(fichier, "lesBestiaux", "bestiaux", 0);
	fichier << "</troupeau>";
}
//-----------------------------------------------------------
void CL_InvAni::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<bestiaux" << "  ";

	Xml->ecrire(fichier, "nom", Animal->Nom);
	Xml->ecrire(fichier, "reproducteur", Reproducteur);
	fichier << ">" << endl;

	Xml->ecrireBalVal(fichier, "prixVenteUnitaire", PrixVenteMoy, N_X);
	Xml->ecrireBalVal(fichier, "valInvUnitaire", ValInvMoy, N_X + 1);
	Xml->ecrireBalVal(fichier, "effectif", Effectif, N_X + 1);
	Xml->ecrireBalVal(fichier, "valeurInv", Valeur, N_X + 1);
	Xml->ecrireBalVal(fichier, "effVendu", Vente, N_X);
	Xml->ecrireBalVal(fichier, "effAchete", Achat, N_X);
	Xml->ecrireBalVal(fichier, "valVente", ValVente, N_X);
	Xml->ecrireBalVal(fichier, "valAchat", ValAchat, N_X);
	Xml->ecrireBalVal(fichier, "effMax", EffMax, N_X);
	//atelier
	fichier << "</bestiaux>" << endl;
}
//-----------------------------------------------------------
void CL_Formule::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	int n;
	int an;

	for (n = 0; n < N_X; n++) {
		if (Valeur[n] == 0)
			continue;

		an = Xml->An_0 + n;
		fichier << "<" << nomE;

		Xml->ecrire(fichier, "nom", Item->Nom);
		Xml->ecrire(fichier, "categorie", Item->Categorie->Nom);

		Xml->ecrire(fichier, "annee", an);
		Xml->ecrire(fichier, "valeur", Valeur[n]);
		fichier << "/>" << endl;
	}
}
//-----------------------------------------------------------
void CL_Immo::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE;
	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "valeurANeuf", ValAchat);
	Xml->ecrire(fichier, "dateAchat", MAchat, AAchat);
	Xml->ecrire(fichier, "tva", Tva->Nom);
	Xml->ecrire(fichier, "typAmor", TypeAmor);
	Xml->ecrire(fichier, "durAmor", Duree);
	if (ValVente) {
		Xml->ecrire(fichier, "valVente", ValVente);
		Xml->ecrire(fichier, "dateVente", MVente, AVente);
	}
	fichier << "/>" << endl;
}
//-----------------------------------------------------------
void CL_Xml::EcrireAgriPetit(ofstream &fichier, CL_Vecteur<CL_Petit>*vPetit) {
	int n;
	CL_Petit *petit;
	if (vPetit->Nbelt == 0)
		return;

	fichier << "<" << "LesPetitsMateriels" << ">" << endl;
	for (n = 0; n < vPetit->Nbelt; n++) {
		petit = vPetit->Vecteur[n];
		if (petit == NULL)
			continue;
		petit->EcrireXml(fichier, "petitMateriel", n);
	}
	fichier << "<" << "/LesPetitsMateriels" << ">" << endl;

}
//-----------------------------------------------------------
void CL_Petit::EcrireXml(ofstream &fichier, char *nomE, int n) {
	if (ValAchat == 0)
		return;
	fichier << "<" << nomE << " ";
	Xml->ecrire(fichier, "valeur", ValAchat);
	Xml->ecrire(fichier, "an", Xml->An_0 + n);
	Xml->ecrire(fichier, "tva", Tva->Nom);
	fichier << "/>" << endl;
}
//-----------------------------------------------------------
void CL_Xml::EcrireV_InvSom(ofstream &fichier, CL_Vecteur<CL_FN_Xp1>*vecteur)

{
	int n, i, an;
	CL_FN_Xp1 *fNxP1; //flottant de N_X +1
	char *lesBalises[6];

	if (vecteur->Nbelt == 0)
		return;

	lesBalises[0] = "VResiduelle";
	lesBalises[1] = "Amortissement";
	lesBalises[2] = "Achat";
	lesBalises[3] = "Revente";
	lesBalises[4] = "PlusValue";
	lesBalises[5] = "MoinsValue";
	lesBalises[6] = "ProdImmo";

	fichier << "<" << "LesImmoGlobales" << ">" << endl;

	for (i = 0; i < vecteur->Nbelt; i++) {
		fNxP1 = vecteur->Vecteur[i];
		if (fNxP1 == NULL)
			continue;
		for (n = 0; n < N_X + 1; n++) {
			if (fNxP1->Valeur[n] == 0)
				continue;

			fichier << "<" << lesBalises[i] << " ";
			an = Xml->An_0 + n;
			ecrire(fichier, "an", an);
			ecrire(fichier, "valeur", fNxP1->Valeur[n]);
			fichier << "/>" << endl;
		}
	}

	fichier << "</" << "LesImmoGlobales" << ">" << endl;
}
//-----------------------------------------------------------
void CL_Xml::EcrireV_FinSom(ofstream &fichier, CL_Vecteur<CL_FN_Xp1>*vecteur)

{
	int i, n, an;
	CL_FN_Xp1 *fNxP1; //flottant de N_X +1
	char *lesBalises[6];

	if (vecteur->Nbelt == 0)
		return;

	lesBalises[0] = "DetteLT";
	lesBalises[1] = "RembCapLT";
	lesBalises[2] = "InteretLT";
	lesBalises[3] = "NouveauLT";

	lesBalises[4] = "DetteCT";
	lesBalises[5] = "RembCapCT";
	lesBalises[6] = "InteretCT";
	lesBalises[7] = "NouveauCT";
	fichier << "<" << "LesEmpGlobaux" << ">" << endl;
	for (i = 0; i < vecteur->Nbelt; i++) {
		fNxP1 = vecteur->Vecteur[i];
		if (fNxP1 == NULL)
			continue;
		for (n = 0; n < N_X + 1; n++) {
			if (fNxP1->Valeur[n] == 0)
				continue;

			fichier << "<" << lesBalises[i] << " ";
			an = Xml->An_0 + n;
			ecrire(fichier, "an", an);
			ecrire(fichier, "valeur", fNxP1->Valeur[n]);
			fichier << "/>" << endl;
		}
	}

	fichier << "</" << "LesEmpGlobaux" << ">" << endl;
}
//-----------------------------------------------------------
bool CL_Xml::EstVide(float *valeur, int nMax) {
	int n;
	for (n = 0; n < nMax; n++) {
		if (valeur[n])
			return false;
	}
	return true;
}
//-----------------------------------------------------------
void CL_FN_Xp1::EcrireXml(ofstream &fichier, char *nomE, int nb) {
//int n;
	Xml->baliseDebut(fichier, nomE);
	Xml->ecrire(fichier, "valeur", Valeur, N_X + 1);
	Xml->finBalise(fichier);
}
//-----------------------------------------------------------------
//-----------------------------------------------------------
void CL_EmpLT::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "montant", Montant);
	Xml->ecrire(fichier, "realisation", MReal, AReal);
	Xml->ecrire(fichier, "remboursement", MRemb, ARemb);
	Xml->ecrire(fichier, "duree", Duree);
	Xml->ecrire(fichier, "taux", Taux);
	if (Duree2) {
		Xml->ecrire(fichier, "duree2", Duree2);
		Xml->ecrire(fichier, "taux2", Taux2);
	}
	Xml->ecrire(fichier, "type", Type);
	Xml->ecrire(fichier, "pour", Pour);

	fichier << "/>" << endl;
}

//-----------------------------------------------------------
void CL_EmpCT::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "montant", Montant);
	Xml->ecrire(fichier, "realisation", MReal, AReal);
	Xml->ecrire(fichier, "remboursement", MRemb, ARemb);
	Xml->ecrire(fichier, "taux", Taux);
	Xml->ecrire(fichier, "pour", Pour);

	fichier << "/>" << endl;
}
//-----------------------------------------------------------
void CL_Sub::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "montant", Montant);
	Xml->ecrire(fichier, "realisation", MReal, AReal);
	Xml->ecrire(fichier, "duree", Duree);

	fichier << "/>" << endl;

}
//-----------------------------------------------------------
void CL_Plact::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "nom", Nom);
	Xml->ecrire(fichier, "montant", Montant);
	Xml->ecrire(fichier, "realisation", MReal, AReal);
	Xml->ecrire(fichier, "remboursement", MTerme, ATerme);
	Xml->ecrire(fichier, "taux", Taux);
	Xml->ecrire(fichier, "type", Type);
	Xml->ecrire(fichier, "pour", Pour);

	fichier << "/>" << endl;

}
//-----------------------------------------------------------
void CL_Occc::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "an", Xml->An_0 + Ex - 1);
	Xml->ecrire(fichier, "montant", Montant);
	Xml->ecrire(fichier, "taux", Taux);
	Xml->ecrire(fichier, "pcent", Pcent);
	Xml->ecrire(fichier, "frais", Frais);

	fichier << "/>" << endl;

}
//-----------------------------------------------------------
void CL_EnCours::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "nom", Item->Nom);
	Xml->ecrire(fichier, "categorie", Item->Categorie->Nom);
	Xml->ecrire(fichier, "date", MPaie, APaie);
	Xml->ecrire(fichier, "valeur", Valeur);
	Xml->ecrire(fichier, "enStock", EnStock);

	fichier << "/>" << endl;

}
//-----------------------------------------------------------
void CL_StockIni::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	int n;
	for (n = 0; n < N_X; n++) {
		if (Quantite[n] == 0)
			continue;

		fichier << "<" << nomE << " ";

		Xml->ecrire(fichier, "nom", Item->Nom);
		Xml->ecrire(fichier, "categorie", Item->Categorie->Nom);
		Xml->ecrire(fichier, "an", Xml->An_0 + n);

		Xml->ecrire(fichier, "quantite", Quantite[n]);
		Xml->ecrire(fichier, "prixRevient", PrixRevient[n]);
		fichier << "/>" << endl;
	}
}
//--------------------------------------------------------------------
void CL_PolStock::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << nomE << " ";

	Xml->ecrire(fichier, "nom", Item->Nom);
	Xml->ecrire(fichier, "pcentStocke", PcentStock);
	Xml->ecrire(fichier, "maxi", Maxi);
	Xml->ecrire(fichier, "pcentDeltaPrix", PcentDeltaPrix);
	Xml->ecrire(fichier, "pcentDecote", PcentDecote);

	fichier << "/>" << endl;
}
//---------------------------------------------------------------------------
void CL_Ensemble::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << "ensemble" << " ";
	Xml->ecrire(fichier, "nom", Nom);
	fichier << ">" << endl;

	Xml->ecrireTxt(fichier, "notes", Notes);
	V_AgriEff->EcrireXml(fichier, "lesEffectifs", "effectif", 0);
	fichier << "</ensemble>" << endl;
}
//---------------------------------------------------------------------------
void CL_AgriEff::EcrireXml(ofstream &fichier, char *nomE, int nb) {
	fichier << "<" << "agri";
	Xml->ecrire(fichier, "nom", Agri->Nom.c_str());
	Xml->ecrire(fichier, "effectif", Effectif, N_X);
	fichier << "/>" << endl;
}
//-----------------------------------------------------------
//-----------------------------------------------------------
//----------------ecrire-------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------
//  < nomBalise nomAttribut=" nom ">
//-----------------------------------------------------------
void CL_Xml::baliseDebut(ofstream &fichier, char *nomBalise, char *nomAttribut,
		AnsiString nom) {
	fichier << "<" << nomBalise;
	fichier << " " << nomAttribut << "=\"";
	fichier << nom << "\"" << ">" << endl;
}
//-----------------------------------------------------------
// < nomBalise
//-----------------------------------------------------------
void CL_Xml::baliseDebut(ofstream &fichier, char *nomBalise) {
	fichier << "<" << nomBalise << ">" << endl;
}
//-----------------------------------------------------------
// </nomBalise>
//-----------------------------------------------------------
void CL_Xml::baliseFin(ofstream &fichier, char *nomBalise) {
	fichier << "</" << nomBalise << ">" << endl;
}
//-----------------------------------------------------------
//  < nomBalise nomAttribut=" nom ">
//-----------------------------------------------------------
void CL_Xml::baliseDebutFin(ofstream &fichier, char *nomBalise,
		char *nomAttribut, AnsiString nom) {
	fichier << "<" << nomBalise;
	fichier << " " << nomAttribut << "=\"";
	fichier << nom << "\"" << "/>" << endl;
}
//-----------------------------------------------------------
//  />
//-----------------------------------------------------------
void CL_Xml::finBalise(ofstream &fichier) {
	fichier << "\"/>" << endl;
}
//-----------------------------------------------------------
// nom=" ceci est une chaine"
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, char *valeur) {
	fichier << " " << nom << "=\"" << valeur << "\"  ";
}
//-----------------------------------------------------------
// nom=" A"
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, char valeur) {
	fichier << " " << nom << "=\"" << valeur << "\"  ";
}
//-----------------------------------------------------------
// nom=" ceci est une AnsiString"
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, AnsiString valeur) {
	fichier << " " << nom << "=\"" << valeur << "\"";
}
//-----------------------------------------------------------
// nom=" 10.11 "
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, float valeur) {
	fichier << " " << nom << "=\"" << valeur << "\"";
}
//-----------------------------------------------------------
// nom=" 10 "
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, int valeur) {
	fichier << " " << nom << "=\"" << valeur << "\"";
}
//-----------------------------------------------------------
// nom=" 10 11 "
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, int val1, int val2) {
	fichier << " " << nom << "=\"" << val1 << " " << val2 << "\"";
}
//-----------------------------------------------------------
// nom=" 10.11 20.22 30.33 "
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, float *valeur, int nx) {
	int n;
	fichier << " " << nom << "=\"";
	for (n = 0; n < nx; n++)
		fichier << valeur[n] << " ";
	fichier << "\"";
}
//-----------------------------------------------------------
// nom=" 10 20 30 "
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, int *valeur, int nx) {
	int n;
	fichier << " " << nom << "=\"";
	for (n = 0; n < nx; n++)
		fichier << valeur[n] << " ";
	fichier << "\"";
}
//-----------------------------------------------------------
// nom=" A  B  C "
//-----------------------------------------------------------
void CL_Xml::ecrire(ofstream &fichier, char *nom, char*valeur, int nx) {
	int n;
	fichier << " " << nom << "=\"";
	for (n = 0; n < nx; n++)
		fichier << valeur[n] << " ";
	fichier << "\"";
}
//-----------------------------------------------------------
void CL_Xml::ecrireTxt(ofstream &fichier, char *nom, AnsiString txt) {
	if (txt != "") {
		fichier << "<" << nom << ">" << endl;
		fichier << "<![CDATA[" << endl;
		fichier << txt << endl;
		fichier << "]]>" << endl;
		fichier << "</" << nom << ">" << endl;
	}
}
//
//balise Valeur  <nom>  10 11 12  </nom>
//<nom>  10 11 12  </nom>
//-----------------------------------------------------------
void CL_Xml::ecrireBalVal(ofstream &fichier, char *nom, float *valeur, int nx) {
	int n;
	for (n = 0; n < nx; n++) {
		if (valeur[n] && valeur[n] != SANSBORNE)
			goto SUITE;
	}
	return;
	SUITE: ;
	fichier << "<" << nom << ">";
	for (n = 0; n < nx; n++) {
		fichier << valeur[n] << " ";
	}
	fichier << "</" << nom << ">" << endl;

}

