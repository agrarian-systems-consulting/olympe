//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
//#include "Brouillon.h"
#include "SortieEcran.h"

//extern
#include "LesVecteurs.hse"
#include "Olympe.hse"
#include "Erreur.h"
#include "CL_Trad.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
extern CL_Trad *T;
bool IlyaErreur;
void CL_ES::LesAdresses(void) {
	IlyaErreur = false;
	ErreurFrm->Edit->Clear();
// Atelier
	adresseAtelier(V_Culture, V_CatCulture);
	adresseAtelier(V_Animaux, V_CatAnimaux);
	adressePerenne(V_Perenne);
	adresseAtelier(V_Vivrier, V_CatVivrier);

//Agriculteur
	adresseAgri();
//EtatSortie
	adresseEtatSortie(V_EtatSortie, V_CatEtatSortie);
	adresseEtatSortie(V_SerieComp, V_CatSerieComp);
//    adresseEtatSortie(V_SerieComp ,V_CatSerieComp);     proc
//Indicateur
	adresseIndicateur();
//Ensemble
	adresseEnsemble();
//??270608
	if (IlyaErreur == true)
		ErreurFrm->Show();

}
//------------------------------------------------------------------------------
void CL_ES::adresseItem3(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);
		item->Tva = V_Tva->trouve(item->NoTva);

	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseItem2(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->Tva = V_Tva->trouve(item->NoTva);
		item->NoSysteme = SysMonnaie->No;
		item->SysUnite = SysMonnaie;
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseItem1(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->NoSysteme = 0;
		item->NoTva = 0;

	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseItem4(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->SysUnite = V_SystemeUnite->trouve(item->NoSysteme);
		if (item->SysUnite == NULL) {
			item->SysUnite = V_SystemeUnite->Vecteur[0];
			item->NoSysteme = item->SysUnite->No;
		}
		item->NoTva = 0;

	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseItem5(CL_Vecteur<CL_Item> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_Item *item;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		item = vecteur->Vecteur[i];
		item->Categorie = vCategorie->trouve(item->NoCategorie);
		item->Tva = V_Tva->trouve(item->NoTva);

		item->SysUnite = 0;
	}
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
void CL_ES::adresseAtelier(CL_Vecteur<CL_Atelier> *vecteur,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	int i, j;
	CL_Atelier* atelier;
	CL_BesTrav *besTrav;
	bool rep;
	for (i = 0; i < vecteur->Nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		if (i == 69)
			i = i;
		atelier->Categorie = vCategorie->trouve(atelier->NoCategorie);
		atelier->Espece = NULL;

		adresseAtelierItem(atelier, 1);
		adresseAtelierItem(atelier, 2);
		adresseAtelierItem(atelier, 3);
		adresseAtelierItem(atelier, 4);

		adresseAtelierItem(atelier, 5); //290307
		adresseAtelierItem(atelier, 6);

		for (j = 0; j < atelier->V_BesTrav->Nbelt; j++) {
			besTrav = atelier->V_BesTrav->Vecteur[j];
			besTrav->Calendrier = V_Calendrier->trouve(besTrav->No);
			//palliatif erreur btpl 240204
			if (besTrav->Calendrier == NULL) {
				rep = besTrav->trouveCalendrier(besTrav->NbPeriodeCal);
				if (rep == false)
					atelier->V_BesTrav->sup(besTrav);
			}
		}
	}
}
//------------------------------------------------------------------------
void CL_ES::adresseAtelierItem(CL_Atelier *atelier, int nature)
//Vecteur<CL_ItemParAtelier> *vecteurIPA,
//							CL_Vecteur<CL_Item> *vecteur)
		{

	CL_ItemParAtelier* itemPA;
	CL_Vecteur<CL_ItemParAtelier> *vecteurIPA;
	CL_Vecteur<CL_Item> *vecteur;
	char *famille;
	switch (nature) {
	case 1:
	case 5:
		famille = T->L_Produit.c_str();
		break; //"Produits";break;
	case 2:
	case 6:
		famille = T->L_Charge.c_str();
		break; //"Charges";break;
	case 3:
		famille = T->L_ChfProd.c_str();
		break; //"Charges f(volume)";break;
	case 4:
		famille = T->L_Exter.c_str();
		break; //"Externalités";break;

	}

	switch (nature) {
	case 1:
		vecteurIPA = atelier->V_Produit;
		vecteur = V_Produit;
		break;
	case 2:
		vecteurIPA = atelier->V_Charge;
		vecteur = V_Charge;
		break;
	case 3:
		vecteurIPA = atelier->V_ChargeVolume;
		vecteur = V_Produit;
		break;
	case 4:
		vecteurIPA = atelier->V_Externalite;
		vecteur = V_Externalite;
		break;
	case 5:
		vecteurIPA = atelier->V_ProdPied;
		vecteur = V_Produit;
		break; //290307
	case 6:
		vecteurIPA = atelier->V_ChPied;
		vecteur = V_Charge;
		break;
	}
	switch (nature) {
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
		for (int i = 0; i < vecteurIPA->Nbelt; i++) {
			itemPA = vecteurIPA->Vecteur[i];
			itemPA->Item = vecteur->trouve(itemPA->NoItem);
			if (itemPA->Item == NULL) {
				itemPA->Item = vecteur->Vecteur[0]; //280608
				/*
				 vecteurIPA->sup(itemPA);
				 i--;
				 */
				messageErreur(atelier->Nom.c_str(), famille);
			}
		}
		break;
	case 3:
		for (int i = 0; i < vecteurIPA->Nbelt; i++) {
			itemPA = vecteurIPA->Vecteur[i];
			itemPA->ItemPA = atelier->V_Produit->trouve(itemPA->NoItemPA);
			if (itemPA->ItemPA == NULL) {
				vecteurIPA->sup(itemPA);
				i--;
				messageErreur(atelier->Nom.c_str(), famille);
				continue;
			}
			itemPA->Charge = V_Charge->trouve(itemPA->NoCharge);

			if (itemPA->Charge == NULL) {
				vecteurIPA->sup(itemPA);
				i--;
				messageErreur(atelier->Nom.c_str(), famille);
			}
		}
	}
}
//------------------------------------------------------------------------
void CL_ES::messageErreur(char *nomAtelier, char *famille) {
	char buf[100];
	IlyaErreur = true;
	sprintf(buf, "Atelier %s %s Probleme de lecture ", nomAtelier, famille);
	ErreurFrm->Edit->Lines->Add(buf);
	ErreurFrm->Edit->Lines->Add(" A VERIFIER");
}
/*
 //------------------------------------------------------------------------
 void CL_ES::adresseAtelierItem(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
 CL_Vecteur<CL_Item> *vecteur)
 {
 CL_ItemParAtelier* itemPA;
 bool erreur=false;
 for(int i=0;i<vecteurIPA->Nbelt;i++)
 {
 itemPA=vecteurIPA->Vecteur[i];
 itemPA->Item=vecteur->trouve(itemPA->NoItem);
 if(itemPA->Item==NULL)
 {
 vecteurIPA->sup(itemPA);
 i--;
 erreur=true;
 }
 }
 if(erreur==true)
 {
 for(int i=0;i<vecteurIPA->Nbelt;i++)
 {
 itemPA=vecteurIPA->Vecteur[i];
 }
 }
 }
 */
/*
 //------------------------------------------------------------------------
 void CL_ES::adresseAtelierItem( CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
 CL_Vecteur<CL_ItemParAtelier> *vecteurP,
 CL_Vecteur<CL_Item> *vecteurC
 )
 {
 CL_ItemParAtelier* itemPA;

 for(int i=0;i<vecteurIPA->Nbelt;i++)
 {
 itemPA=vecteurIPA->Vecteur[i];
 itemPA->ItemPA  =vecteurP->trouve(itemPA->NoItemPA);
 //        itemPA->ItemPA  =vecteurP->trouve(itemPA->NoItemPA);
 itemPA->Charge  =vecteurC->trouve(itemPA->NoCharge);
 }
 }
 */
//-------------------------------------------------------------------------
void CL_ES::adressePerenne(CL_Vecteur<CL_Atelier> *vecteur) {
	int j;
	CL_Atelier* atelier;
	CL_BesTrav *besTrav;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		atelier = vecteur->Vecteur[i];
		atelier->Espece = V_Espece->trouve(atelier->NoEspece);
		atelier->Categorie = NULL;
		adresseAtelierItem(atelier, 1); //Produits
		adresseAtelierItem(atelier, 2); //Charges
		adresseAtelierItem(atelier, 3); //Charge f Vol
		adresseAtelierItem(atelier, 4); //Externalités
		adresseAtelierItem(atelier, 5); //Produits /Pied
		adresseAtelierItem(atelier, 6); //Charges  /Pied

		for (j = 0; j < atelier->V_BesTrav->Nbelt; j++) {
			besTrav = atelier->V_BesTrav->Vecteur[j];
			besTrav->Calendrier = V_Calendrier->trouve(besTrav->No);
		}
	}
}

//-------------------------------------------------------------------------
void CL_ES::adresseAgri(void) {
	CL_Agriculteur *agri;
	ST_NoAgri *variante;
	int i, j;
	for (i = 0; i < V_Agriculteur->Nbelt; i++) {
		agri = V_Agriculteur->Vecteur[i];
		for (j = 0; j < agri->LstVariante->Count; j++) {
			variante = (ST_NoAgri*) agri->LstVariante->Items[j];
			variante->Agri = V_Agriculteur->trouve(variante->No);
		}
		//serie de simu + de 10 ans  251006
		if (agri->LstSerie != NULL) {
			if (agri->LstSerie->Count > 0) {
				for (j = 0; j < agri->LstSerie->Count; j++) {
					variante = (ST_NoAgri*) agri->LstSerie->Items[j];
					variante->Agri = V_Agriculteur->trouve(variante->No);
					if (variante->Agri == NULL)
						continue; //181207
					variante->Agri->NoSerie = j; //190907
					if (j > 0 && variante->Agri)
						variante->Agri->EstPlus10Ans = true;
				}
			}
		}
		adresseAgriValeurAtelier(agri->V_Culture, V_Culture);
		adresseAgriValeurAtelier(agri->V_Animaux, V_Animaux);
		adresseAgriValeurVerger(agri->V_Verger, V_Perenne);
		adresseAgriValeurVerger(agri->V_Vivrier, V_Vivrier);
//voir?        adresseAgriInvAni       (agri->V_InvAni);061003
		adresseAgriValeurItem(agri->V_Variable, V_Variable);
		adresseAgriCreanceDette(agri->V_Creance);
		adresseAgriCreanceDette(agri->V_Dette);

		adresseAgriStockIni(agri->V_StockIni);
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	CL_Valeur* valeur;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		valeur->Atelier = vAtelier->trouve(valeur->NoAtelier);
//        if(valeur->Atelier==NULL){ vecteur->Nbelt=0;return;} //bidouille
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurAtelier(CL_Vecteur<CL_Valeur> *vecteur,
		CL_Vecteur<CL_Atelier> *vAtelier, int nature) {
	CL_Valeur* valeur;
	CL_Atelier* atelier;
	for (int i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		atelier = vAtelier->trouve(valeur->NoAtelier);
		if (atelier == NULL)
			continue;
		if (atelier->Nature != nature)
			continue;

		valeur->Atelier = atelier;
//        if(valeur->Atelier==NULL){ vecteur->Nbelt=0;return;} //bidouille
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurItem(CL_Vecteur<CL_Valeur> *vecteur,
		CL_Vecteur<CL_Item>*vItem) {
	CL_Valeur* valeur;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		valeur = vecteur->Vecteur[i];
		valeur->Item = vItem->trouve(valeur->NoItem);
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriValeurVerger(CL_Vecteur<CL_Verger> *vecteur,
		CL_Vecteur<CL_Atelier> *vAtelier) {
	CL_Verger* verger;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		verger = vecteur->Vecteur[i];
		verger->Atelier = vAtelier->trouve(verger->NoAtelier);
		verger->Espece = verger->Atelier->Espece;
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriInvAni(CL_Vecteur<CL_InvAni> *vecteur) {
	CL_InvAni* invAni;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		invAni = vecteur->Vecteur[i]; //121201
		invAni->Animal = V_Bestiaux->trouve(invAni->NoAnimal);
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriCreanceDette(CL_Vecteur<CL_EnCours> *vecteur) {
	int n;
	CL_EnCours *enCours;
	CL_Vecteur<CL_Item> *vItem;
	for (n = 0; n < vecteur->Nbelt; n++) {
		enCours = vecteur->Vecteur[n];
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
	}
}
//-------------------------------------------------------------------------
void CL_ES::adresseAgriStockIni(CL_Vecteur<CL_StockIni> *vecteur) {
	CL_StockIni* stock;

	for (int i = 0; i < vecteur->Nbelt; i++) {
		stock = vecteur->Vecteur[i];
		stock->Item = V_Produit->trouve(stock->NoItem);
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseEtatSortie(CL_Vecteur<CL_EtatSortie> *vEtat,
		CL_Vecteur<CL_Categorie> *vCategorie) {
	CL_EtatSortie *etat;

	for (int i = 0; i < vEtat->Nbelt; i++) {
		etat = vEtat->Vecteur[i];
		etat->Categorie = vCategorie->trouve(etat->NoCategorie);
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseIndicateur(void) {
	CL_Indicateur *indic;

	for (int i = 0; i < V_Indicateur->Nbelt; i++) {
		indic = V_Indicateur->Vecteur[i];
		indic->Categorie = V_CatIndic->trouve(indic->NoCategorie);
	}
}
//------------------------------------------------------------------------------
void CL_ES::adresseEnsemble(void) {
	int i, j;
	int noAgri;
	CL_Ensemble *ensemble;
	CL_AgriEff *agriEff;
	ST_NoEnsemble *variante;
	for (i = 0; i < V_Ensemble->Nbelt; i++) {
		ensemble = V_Ensemble->Vecteur[i];
		for (j = 0; j < ensemble->V_AgriEff->Nbelt; j++) {
			agriEff = ensemble->V_AgriEff->Vecteur[j];
			noAgri = agriEff->NoAgri;
			agriEff->Agri = V_Agriculteur->trouve(noAgri);
			if (agriEff->Agri == NULL) {
				agriEff->Nom = T->L_Inconnu; //"Inconnu";
				continue; //110203
			}
			agriEff->Nom = agriEff->Agri->Nom;
		}
		for (j = 0; j < ensemble->LstVariante->Count; j++) {
			variante = (ST_NoEnsemble*) ensemble->LstVariante->Items[j];
			variante->Ensemble = V_Ensemble->trouve(variante->No);
			if (variante->Ensemble == NULL) { //300902
				ensemble->LstVariante->Delete(j);
				j--;
			} else
				variante->Ensemble->EstVariante = true; //300902
		}
	}
}
