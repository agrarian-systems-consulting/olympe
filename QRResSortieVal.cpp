#include <vcl.h>
#pragma hdrstop

//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
//#include "TitreFrancais.h"
#include "Resultat.h"
#include "CL_Trad.h"
#include "FichierLire.h"

#include "QRSortieVal.h"
extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::Prepare(int TypeSortie,CL_Agriculteur *agri)
{
	QRSortieValFrm->Agri=agri;
	//inutile c'est fait dans Initialise
	//QRSortieValFrm->NomAgri->Caption=AgriSaisieFrm->Caption;
	if(Global==AGRI||Global==MOYENNE) QRSortieValFrm->UniteMonnaie->Caption=SysMonnaie->UTrans.c_str();
	else QRSortieValFrm->UniteMonnaie->Caption=SysMonnaie->UGlobal.c_str();
	//QRSortieValFrm->QR->Tag= nb Colonne 10 CEG Treso  11 Bilan
	LstDonnees=new TList;
	switch(TypeSortie)
	{
		case SYNTHESE: //131103
		QRSortieValFrm->TitreEtat->Caption=L_1;//"Synthèse Economique";
		QRSortieValFrm->QR->Tag=10;//a quoi ça sert
		IniDonneesSynthese(agri);
		break;
		case CEG:
		QRSortieValFrm->TitreEtat->Caption=L_2;//"Compte de Résultat";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesCeg(agri);
		break;
		case BILAN:
		QRSortieValFrm->TitreEtat->Caption=L_3;//"Bilan";
		QRSortieValFrm->QR->Tag=11;
		IniDonneesBilan(agri);
		break;
		case FAMILLE:
		QRSortieValFrm->TitreEtat->Caption=L_4;//"Privé";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesPrive(agri);
		break;
		case VALEUR://détaillé
		QRSortieValFrm->TitreEtat->Caption=L_5;//"Recettes Dépenses";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesTreso(agri);
		break;
		case TRESO://grands postes
		QRSortieValFrm->TitreEtat->Caption=L_5;//"Recettes Dépenses";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesTresoGrandsPostes(agri);
		break;
		case TVA:
		QRSortieValFrm->TitreEtat->Caption=L_6;//"Calcul Tva";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesTva(agri);
		break;
		case FINANCE:
		QRSortieValFrm->TitreEtat->Caption=L_7;//"Finances";
		QRSortieValFrm->QR->Tag=11;
		IniDonneesFinance(agri);
		break;
		case IMMO:
		QRSortieValFrm->TitreEtat->Caption=L_8;//"Immobilisations";
		QRSortieValFrm->QR->Tag=11;
		IniDonneesImmo(agri);
		break;
		case PERENNE:
		QRSortieValFrm->TitreEtat->Caption=L_9;//"Pérennes Eléments comptables";
		QRSortieValFrm->QR->Tag=11;
		IniDonneesPerenne(agri);
		break;
		case ANIMAUX:
		QRSortieValFrm->TitreEtat->Caption=L_10;//"Animaux Recettes Dépenses";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesAnimaux(agri);
		break;
		case EMPLT://260805
		QRSortieValFrm->TitreEtat->Caption=L_47;//150406"Récapitulatif Emprunt Long Terme";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesRecapEmpLT(agri);
		break;
		case AMOR://260805
		QRSortieValFrm->TitreEtat->Caption=L_128;//"Récapitulatif Immobilisation hors pérennes";
		QRSortieValFrm->QR->Tag=10;
		IniDonneesRecapImmo(agri);
		break;

		default:
		ShowMessage(L_11);//"Oubli dans Prepare");
		return;
	}
//    QRSortieValFrm->Initialise();
	Initialise();
//    QRSortieValFrm->QR->Preview();
	QR->Preview();
	DelDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesSynthese(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;

	resultat=agri->Resultat;

	entreDonnees(QRTITRE,L_12.c_str(),resultat->Produit,clBlack); //"Chiffre d'affaire"
	entreDonnees(QRTITRE,L_13.c_str(),resultat->Marge,clBlack);//"MARGE"
	entreDonnees(QRTITRE,L_14.c_str(),resultat->Ebe,clBlack);//"EBE "
	entreDonnees(QRTITRE,L_15.c_str(),resultat->Caf,clBlack);//"CAF "
	entreDonnees(QRTITRE,L_16.c_str(),resultat->Solde,clBlack);//"SOLDE"
	entreDonnees(QRTITRE,L_17.c_str(),resultat->SoldeCumul,clBlack);//"SOLDE CUMULE"

	entreBlanc();
	entreDonnees(QRTITRE,L_18.c_str(),resultat->totProduit,clBlack);//"Produits Ceg"
	entreDonnees(QRTITRE,L_19.c_str(),resultat->resExercice,clBlack);//"Résultat Ceg"

	entreBlanc();
	entreDonnees(QRBIL,L_8.c_str(),resultat->totImmo);//"Immobilisations"

	entreDonnees(QRTITRE,L_20.c_str(),resultat->ImmoTotal->Amor);//"Amortissement Immo"
	if(EstVide(resultat->AmorPlant)==false)
	entreDonnees(QRTITRE,L_21.c_str(), resultat->AmorPlant);//"Amortissement Plantation"

	entreBlanc();

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesCeg(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;

	entreDonnees(QRTITRE,L_22.c_str(),resultat->totProduit); //"Produits"
//    blanc();

	entreDonnees(QRDON,L_23.c_str(),resultat->Produit);//"Recettes"
	entreDonnees(QRDON,L_24.c_str(),resultat->RecDiv);//"Recettes Diverses"
	entreDonnees(QRDON,L_25.c_str(),resultat->deltaStock);//"Var. Stock"
	entreDonnees(QRDON,L_26.c_str(),resultat->deltaAvance);//"Var. stock en terre"
//    Resultat(".  Variation valeur plantation",   resultat->deltaValPlant,clNavy);
	entreDonnees(QRDON,L_28.c_str(),resultat->deltaVarInvAniRepro);//"Var. inv animal Repro"
	entreDonnees(QRDON,L_29.c_str(),resultat->deltaVarInvAniAutre);//"                Autre"

	entreDonnees(QRDON,L_30.c_str(),resultat->PlactE->Interet);//"Produits financiers"
	entreDonnees(QRDON,L_31.c_str(),resultat->ProdImmo);//"Production d'immo"
	entreDonnees(QRDON,L_32.c_str(),resultat->ImmoTotal->Vente);//"Cession d'actif"
	entreDonnees(QRDON,L_33.c_str(),resultat->PertePlant);//"Perte Exceptionnelle"
	entreDonnees(QRDON,L_34.c_str(),resultat->TotSub->Amor);//"Amortissement Subvention"

	entreBlanc();
	entreDonnees(QRTITRE,L_35.c_str(),resultat->totDepense);//"Charges"
//    blanc();

	entreDonnees(QRDON,L_36.c_str(),resultat->Charge);//"Dépenses Exploitation"
	entreDonnees(QRDON,L_37.c_str(),resultat->DepDiv);//"Dépenses Diverses"
	entreDonnees(QRDON,L_38.c_str(),resultat->ImmoTotal->ValCompta);//"Val comptable cession"

	entreBlanc();
	entreDonnees(QRTITRE,L_39.c_str(),resultat->totChStruct);//"Charges de Structure"
//    blanc();
	entreDonnees(QRDON,L_20.c_str(),resultat->ImmoTotal->Amor);//"Amortissement Immo"
	entreDonnees(QRDON,L_21.c_str(),resultat->AmorPlant);//"Amortissement Plantation"
	entreDonnees(QRDON,L_40.c_str(),resultat->EmpLTE->Interet);//"Frais fin LT"
	entreDonnees(QRDON,L_41.c_str(),resultat->EmpCTE->Interet);//"Frais fin CT"
	entreDonnees(QRDON,L_42.c_str(),resultat->FraisOccc);//"Frais fin OCCC"
	entreDonnees(QRDON,L_43.c_str(),resultat->ChStruct);//"Autres Ch Struct"
	entreBlanc();
	entreDonnees(QRDON,L_44.c_str(),resultat->resExercice,clRed);//"Résultat"
	entreBlanc();
//  entreDonnees(QRDON,"EBE test",                 resultat->Ebe,clBlack);
//  entreDonnees(QRDON,"CAF test",                 resultat->Caf,clBlack);

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesBilan(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;
//	LesTitresBilan[0]="aaaaaaaa";

	entreDonnees(QRTITRE,L_48.c_str(),NULL);//"ACTIF"
//    blanc();
	entreDonnees(QRBIL,ES->LesTitresBilan[0], resultat->totImmo);
	entreDonnees(QRBIL,ES->LesTitresBilan[1], resultat->ImmoTotal->Resid);
	entreDonnees(QRBIL,ES->LesTitresBilan[2], resultat->InvAniRepro);//260903
	entreDonnees(QRBIL,ES->LesTitresBilan[3], resultat->ValPlant);

	entreDonnees(QRBIL,ES->LesTitresBilan[4], resultat->Stock);
	entreDonnees(QRBIL,ES->LesTitresBilan[5], resultat->Avance);
	entreDonnees(QRBIL,ES->LesTitresBilan[6], resultat->InvAniAutre);//260903
	//creance
	entreDonnees(QRBIL,ES->LesTitresBilan[7], resultat->PlactE->Dette);
	entreDonnees(QRBIL,ES->LesTitresBilan[8], resultat->creanceTva);
	entreDonnees(QRBIL,ES->LesTitresBilan[9], resultat->Creance->CrDette);
	entreDonnees(QRBIL,ES->LesTitresBilan[10],resultat->tresorerie);
	entreDonnees(QRDON,ES->LesTitresBilan[11],resultat->perte,clRed);
	entreDonnees(QRBIL,ES->LesTitresBilan[12],resultat->totActif);

//	PASSIF);
	entreBlanc();
	entreDonnees(QRTITRE,ES->LesTitresBilan[13],NULL);
	entreDonnees(QRBIL,ES->LesTitresBilan[14],resultat->capital);
	entreDonnees(QRDON,ES->LesTitresBilan[15],resultat->soldePrive);

	entreDonnees(QRBIL,ES->LesTitresBilan[16], resultat->TotSub->Resid);
	entreDonnees(QRBIL,ES->LesTitresBilan[17], resultat->EmpLTE->Dette);
	entreDonnees(QRBIL,ES->LesTitresBilan[18], resultat->EmpCTE->Dette);
	entreDonnees(QRBIL,ES->LesTitresBilan[19], resultat->detteTva);
	entreDonnees(QRBIL,ES->LesTitresBilan[20], resultat->Dette->CrDette);
//    Blanc(1);
	entreDonnees(QRDON,ES->LesTitresBilan[21], resultat->benefice,clRed);
	entreDonnees(QRBIL,ES->LesTitresBilan[22], resultat->totPassif);
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesPrive(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;

	entreDonnees(QRDON,L_49.c_str(),resultat->RecFam); //"+ Apports "
	entreDonnees(QRDON,L_50.c_str(),resultat->DepFam);//"- Prélevements"
	entreDonnees(QRDON,L_51.c_str(),resultat->ProdImmoFam);//"+ Production d'immo"
	entreDonnees(QRDON,L_52.c_str(),resultat->PlactP->Interet);//"+ Produits financiers"
	entreDonnees(QRDON,L_53.c_str(),resultat->EmpLTP->Remb);//"- Remboursement LT"
	entreDonnees(QRDON,L_54.c_str(),resultat->EmpCTP->Remb);//"- Remboursement CT"
	entreDonnees(QRDON,L_55.c_str(),resultat->EmpLTP->Interet);//"- Frais fin LT"
	entreDonnees(QRDON,L_56.c_str(),resultat->EmpCTP->Interet);//"- Frais fin CT"
	entreDonnees(QRDON,L_57.c_str(),resultat->PlactP->Capital);//"- Placements"
	entreDonnees(QRDON,L_58.c_str(),resultat->soldePrive);//"Solde Privé"

}
//---------------------------------------------------------------------------
// Recettes Dépenses détaillé
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesTreso(CL_Agriculteur *agri)
{
	int n;
	CL_AgriRes *resultat;
	static float dette[N_X];
	static float tresoIni[N_X];
	resultat=agri->Resultat;

	IniDTresoCategorie(L_22.c_str(),L_59.c_str(), //"Produits","TOTAL Recettes Produits",
			V_CatProduit,resultat->V_Produit,
			NULL,resultat->V_CatProduitTot);
	IniDTresoAnimaux(agri);
	entreDonnees(QRDON,L_59.c_str(),resultat->Produit);//"TOTAL Recettes Produits"

	IniDTresoCategorie(L_35.c_str(),L_60.c_str(),//"Charges","TOTAL Charges opérationnelles",
			V_CatCharge ,resultat->V_Charge,
			resultat->Charge,resultat->V_CatChargeTot);
	entreDonnees(QRTITRE,L_13.c_str(),resultat->Marge,clRed);//"MARGE"

	IniDTresoCategorie(L_39.c_str(),L_61.c_str(),//"Charges de Structure","TOTAL Structure",
			V_CatChStruct,resultat->V_ChStruct,
			resultat->ChStruct,resultat->V_CatChStructTot);
	IniDTresoCategorie(L_24.c_str(),L_62.c_str(),//"Recettes Diverses","TOTAL Recettes Diverses",
			V_CatRecDiv,resultat->V_RecDiv,
			resultat->RecDiv,resultat->V_CatRecDivTot);
	IniDTresoCategorie(L_37.c_str(),L_63.c_str(),//"Dépenses Diverses","TOTAL Dépenses Diverses",
			V_CatDepDiv,resultat->V_DepDiv,
			resultat->DepDiv,resultat->V_CatDepDivTot);
	IniDTresoCategorie(L_64.c_str(),L_65.c_str(),//"Recettes Familiales","TOTAL Recettes Familiales",
			V_CatRecFam,resultat->V_RecFam,
			resultat->RecFam,resultat->V_CatRecFamTot);
	IniDTresoCategorie(L_66.c_str(),L_67.c_str(),//"Dépenses Familiales","TOTAL Dépenses Familiales",
			V_CatDepFam,resultat->V_DepFam,
			resultat->DepFam,resultat->V_CatDepFamTot);
	IniDTresoImmo(resultat);
	IniDTresoEmprunt(resultat);
	IniDTresoPlact(resultat);
	if(EstVide(resultat->TotSub->Valeur)==false)
	{
		entreDonnees(QRTITRE,L_68.c_str(),NULL); //"Subventions"
		entreDonnees(QRDON,L_68.c_str(),resultat->TotSub->Valeur,clNavy);//"Subventions"
	}
	if(EstVide(resultat->Creance->Flux)==false||EstVide(resultat->Dette->Flux)==false)
	{
		entreDonnees(QRTITRE,L_69.c_str(),NULL); //"Créances et Dettes"
		entreDonnees(QRDON,L_70.c_str(),resultat->Creance->Flux,clNavy);//"Créances"
		for(n=0;n<N_X;n++)dette[n]=-resultat->Dette->Flux[n];
		entreDonnees(QRDON,L_71.c_str(), dette,clNavy);//"Dettes"
	}

	entreDonnees(QRTITRE,L_72.c_str(),NULL); //"Tva"
	entreDonnees(QRDON,L_73.c_str(),resultat->Tva->Solde,clNavy);//"Solde Tva"
//	Blanc();

//    Trait(132);  Total trace un trait
	entreDonnees(QRTITRE,L_16.c_str(),resultat->Solde,clRed);//"SOLDE"
//	Trait(132);

//    Trait(132);
	memset(tresoIni,0,sizeof(float)*N_X);
	tresoIni[0]=resultat->TresoIni;
	entreDonnees(QRDON,L_74.c_str(),tresoIni);//"Trésorerie Initiale"
	entreDonnees(QRTITRE,L_17.c_str(),resultat->SoldeCumul,clRed);//"SOLDE CUMULE"

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDTresoCategorie(
		char *titre,char *IntitTotal,
		CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vProduit,
		float *total,
		CL_Vecteur<CL_QuanVal> *vCatTot)
{
	int i,j,l;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal,*quanValTot;
	AnsiString as;
	if(vProduit->Nbelt==0) return;
	entreDonnees(QRTITRE,titre,NULL);

//    Trait();

	for(i=0;i<vCategorie->Nbelt;i++)
	{
		categorie=vCategorie->Vecteur[i];
		if(categorie->Flag=='N') continue;

		quanValTot=vCatTot->trouve(categorie->No);
		l=0;
		entreDonnees(QRTITRE1,categorie->Nom.c_str(),NULL,clNavy);

		for(j=0;j<vProduit->Nbelt;j++)
		{
			quanVal=vProduit->Vecteur[j];
			item=quanVal->Item;
			if(item->Categorie!=categorie ) continue;
			l++;
			entreDonnees(QRDON,item->Nom.c_str(),quanVal->Val,clNavy);
		}
		if(l >1)
		{
			entreDonnees(QRDON,L_75.c_str(),quanValTot->Val,clNavy); //"total"
		}
	}
	if(total)
	entreDonnees(QRDON,IntitTotal,total);
}
//..................
// Recettes Dépenses  non détaille
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesTresoGrandsPostes(CL_Agriculteur *agri)
{
	int n;
	CL_AgriRes *resultat;
	static float dette[N_X];
	static float tresoIni[N_X];
	resultat=agri->Resultat;

	IniDTresoCategorieGP(L_22.c_str(),L_59.c_str(), //"Produits","TOTAL Recettes Produits",
			V_CatProduit,resultat->V_Produit,
			NULL,resultat->V_CatProduitTot);
	//NULL pour eviter imprimer total avant animaux
	IniDTresoAnimauxGP(agri);
	entreDonnees(QRDON,L_59.c_str(),resultat->Produit);//"TOTAL Recettes Produits"

	IniDTresoCategorieGP(L_35.c_str(),L_60.c_str(),//"Charges","TOTAL Charges opérationnelles",
			V_CatCharge ,resultat->V_Charge,
			resultat->Charge,resultat->V_CatChargeTot);
	entreDonnees(QRTITRE,L_13.c_str(),resultat->Marge,clRed);//"MARGE"

	IniDTresoCategorieGP(L_39.c_str(),L_61.c_str(),//"Charges de Structure","TOTAL Structure",
			V_CatChStruct,resultat->V_ChStruct,
			resultat->ChStruct,resultat->V_CatChStructTot);
	IniDTresoCategorieGP(L_24.c_str(),L_62.c_str(),//"Recettes Diverses","TOTAL Recettes Diverses",
			V_CatRecDiv,resultat->V_RecDiv,
			resultat->RecDiv,resultat->V_CatRecDivTot);
	IniDTresoCategorieGP(L_37.c_str(),L_63.c_str(),//"Dépenses Diverses","TOTAL Dépenses Diverses",
			V_CatDepDiv,resultat->V_DepDiv,
			resultat->DepDiv,resultat->V_CatDepDivTot);
	IniDTresoCategorieGP(L_64.c_str(),L_65.c_str(),//"Recettes Familiales","TOTAL Recettes Familiales",
			V_CatRecFam,resultat->V_RecFam,
			resultat->RecFam,resultat->V_CatRecFamTot);
	IniDTresoCategorieGP(L_66.c_str(),L_67.c_str(),//"Dépenses Familiales","TOTAL Dépenses Familiales",
			V_CatDepFam,resultat->V_DepFam,
			resultat->DepFam,resultat->V_CatDepFamTot);
	IniDTresoImmo(resultat);
	IniDTresoEmprunt(resultat);
	IniDTresoPlact(resultat);
	if(EstVide(resultat->TotSub->Valeur)==false)
	{
		entreDonnees(QRTITRE,L_68.c_str(),NULL); //"Subventions"
		entreDonnees(QRDON,L_68.c_str(),resultat->TotSub->Valeur,clNavy);//"Subventions"
	}
	if(EstVide(resultat->Creance->Flux)==false||EstVide(resultat->Dette->Flux)==false)
	{
		entreDonnees(QRTITRE,L_69.c_str(),NULL); //"Créances et Dettes"
		entreDonnees(QRDON,L_70.c_str(),resultat->Creance->Flux,clNavy);//"Créances"

		for(n=0;n<N_X;n++)dette[n]=-resultat->Dette->Flux[n];
		entreDonnees(QRDON,L_71.c_str(), dette,clNavy);//"Dettes"
	}
	entreDonnees(QRTITRE,L_72.c_str(),NULL); //"Tva"
	entreDonnees(QRDON,L_73.c_str(),resultat->Tva->Solde,clNavy);//"Solde Tva"

//	Blanc();

//    Trait(132);  Total trace un trait
	entreDonnees(QRTITRE,L_16.c_str(),resultat->Solde,clRed);//"SOLDE"
//	Trait(132);

//    Trait(132);
	memset(tresoIni,0,sizeof(float)*N_X);
	tresoIni[0]=resultat->TresoIni;
	entreDonnees(QRDON,L_74.c_str(),tresoIni);//"Trésorerie Initiale"
	entreDonnees(QRTITRE,L_17.c_str(),resultat->SoldeCumul,clRed);//"SOLDE CUMULE"

}
/*
 IniDTresoCategorie("Produits","TOTAL Recettes Produits",
 V_CatProduit,resultat->V_Produit,
 resultat->Produit,resultat->V_CatProduitTot);
 */
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDTresoCategorieGP(
		char *titre,char *IntitTotal,
		CL_Vecteur<CL_Categorie> *vCategorie,
		CL_Vecteur<CL_QuanVal> *vProduit,
		float *total,
		CL_Vecteur<CL_QuanVal> *vCatTot)
{
	int i;
	CL_Categorie *categorie;
	CL_QuanVal *quanValTot;
	if(vProduit->Nbelt==0) return;
	entreDonnees(QRTITRE,titre,NULL);

//    Trait();

	for(i=0;i<vCategorie->Nbelt;i++)
	{
		categorie=vCategorie->Vecteur[i];
		if(categorie->Flag=='N') continue;

		quanValTot=vCatTot->trouve(categorie->No);
		entreDonnees(QRTITRE1,categorie->Nom.c_str(),quanValTot->Val,clNavy);
	}
	if(total)
	entreDonnees(QRDON,IntitTotal,total);
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDTresoAnimaux(CL_Agriculteur *agri)

{
	int i,j;
	CL_InvAni *invAni;
	CL_Troupeau *troupeau;
	static float solde[N_X];

	bool titreAffiche;
	bool totalAffiche;

	if(agri->LstTroupeaux->Count==0) return;
	titreAffiche=false;
	totalAffiche=false;
	//Ventes
	for(i=0;i<agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			if(EstVide(invAni->Vente)==false)
			{
				if(titreAffiche==false)
				{
					entreDonnees(QRTITRE1,L_76.c_str(),NULL,clNavy); //"Vente d'Animaux"
					titreAffiche=true;totalAffiche=true;
				}
				entreDonnees(QRDON,invAni->Animal->Nom.c_str(),invAni->ValVente,clNavy);
			}
		}
	}
	if(titreAffiche==true)
	entreDonnees(QRDON,L_75.c_str(),agri->Resultat->VenteAni,clNavy); //"total"

	//Achats
	titreAffiche=false;
	for(i=0;i<agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			if(EstVide(invAni->Achat)==false)
			{
				if(titreAffiche==false)
				{
					entreDonnees(QRTITRE1,L_77.c_str(),NULL,clNavy); //"Achat d'Animaux"
					titreAffiche=true;totalAffiche=true;
				}
				entreDonnees(QRDON,invAni->Animal->Nom.c_str(),invAni->ValAchat,clNavy);
			}
		}
	}
	if(titreAffiche==true)
	entreDonnees(QRDON,L_77.c_str(),agri->Resultat->AchatAni,clNavy); //"total"
	if(totalAffiche==false) return;
	for(int n=0;n<N_X;n++)
	solde[n]=agri->Resultat->VenteAni[n]-agri->Resultat->AchatAni[n];

	entreDonnees(QRDON,L_78.c_str(),solde,clNavy);//"SOLDE ventes-achats"

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDTresoAnimauxGP(CL_Agriculteur *agri)
{
	int i,j;
	CL_AgriRes *resultat=agri->Resultat;
	static float achat[N_X];
	for(i=0;i<N_X;i++)
	{
		if(resultat->VenteAni[i]>0)
		{
			entreDonnees(QRTITRE1,L_79.c_str(),resultat->VenteAni,clNavy); //"Ventes d'animaux"
			break;
		}
	}
	for(i=0;i<N_X;i++)
	{
		if(resultat->AchatAni[i]>0)
		{
			for(j=0;j<N_X;j++)achat[j]=-resultat->AchatAni[j];
			entreDonnees(QRTITRE1,L_77.c_str(),achat,clNavy); //"Achats d'animaux"
			break;
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm:: IniDTresoImmo(CL_AgriRes *resultat)
{
	int n;
	static float solde[N_X];

	entreDonnees(QRTITRE,L_81.c_str(),NULL); //"Immobilisation"
	for(n=0;n<N_X;n++)
	solde[n]=resultat->ImmoTotal->Achat[n]
	-resultat->ImmoTotal->Vente[n];

	entreDonnees(QRDON,L_82.c_str(), resultat->ImmoTotal->Achat,clNavy);//"Achat"
	entreDonnees(QRDON,L_83.c_str(), resultat->ImmoTotal->Vente,clNavy);//"Vente"
	entreDonnees(QRDON,L_84.c_str(),solde);//"Achat-Vente"

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm:: IniDTresoEmprunt(CL_AgriRes *resultat)
{
	int n;
	static float solde[N_X];

	entreDonnees(QRTITRE,L_85.c_str(),NULL); //"Emprunts"
	for( n=0;n<N_X;n++)
	solde[n]=resultat->EmpTotal->Capital[n]
	-resultat->EmpTotal->Remb[n]
	-resultat->EmpTotal->Interet[n];

	entreDonnees(QRDON,L_86.c_str(),resultat->EmpTotal->Capital,clNavy);//"Emprunt"
	entreDonnees(QRDON,L_87.c_str(),resultat->EmpTotal->Remb,clNavy);//"Remboursement"
	entreDonnees(QRDON,L_88.c_str(),resultat->EmpTotal->Interet,clNavy);//"Interet"

	entreDonnees(QRDON,L_89.c_str(),solde);//"net"

}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm:: IniDTresoPlact(CL_AgriRes *resultat)
{
	static float solde[N_X];

	for(int n=0;n<N_X;n++)
	solde[n]=-resultat->PlactE->Capital[n]
	+resultat->PlactE->Remb[n];
	if(EstVide(solde)==true) return;

	entreDonnees(QRTITRE,L_90.c_str(),NULL); //"Placements"

	entreDonnees(QRDON,L_91.c_str(),resultat->PlactE->Capital,clNavy);//"Placé"
	entreDonnees(QRDON,L_92.c_str(),resultat->PlactE->Remb,clNavy);//"Disponible"
	entreDonnees(QRDON,L_89.c_str(),solde);//"net"
}

//---------------------------------------------------------------------------
//appelé par TroupeauBouton
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesAnimaux(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	int n;
	static float total[N_X];
	static float solde[N_X];

	memset(total,0,sizeof(total));
	resultat=agri->Resultat;

	IniDTresoCategorie(L_22.c_str(),L_59.c_str(), //"Produits","TOTAL Recettes Produits",
			V_CatProduit,resultat->V_Produit,
			resultat->Produit,resultat->V_CatProduitTot);
	IniDTresoAnimaux(agri);//101003
	for(n=0;n<N_X;n++)
	total[n]=resultat->Produit[n]+resultat->VenteAni[n]-resultat->VenteAni[n];

	entreDonnees(QRDON,"total",total);

	IniDTresoCategorie(L_35.c_str(),L_93.c_str(),//"Charges","TOTAL dépenses charges",
			V_CatCharge ,resultat->V_Charge,
			resultat->Charge,resultat->V_CatChargeTot);
	entreDonnees(QRDON,L_75.c_str(),resultat->Charge);//"total"
	for(n=0;n<N_X;n++)
	solde[n]=total[n]-resultat->Charge[n];
	entreDonnees(QRTITRE,L_16.c_str(),solde,clRed);//"SOLDE"
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesTva(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;

	entreDonnees(QRDON,L_94.c_str(),resultat->Tva->Recu, clNavy); //"Encaissé"
	entreDonnees(QRDON,L_95.c_str(),resultat->Tva->Verse, clNavy);//"Versé"
//    Blanc(1);
	entreDonnees(QRDON,L_96.c_str(),resultat->Tva->AcompteFev, clNavy);//"Acompte Fevrier"
	entreDonnees(QRDON,L_97.c_str(),resultat->Tva->Regul, clNavy);//"Régularisation "
	entreDonnees(QRDON,L_87.c_str(),resultat->Tva->RembTva, clNavy);//"Remboursement"
//    Blanc(1);
	entreDonnees(QRDON,L_98.c_str(),resultat->Tva->AcompteMai, clNavy);//"Acompte Mai"
	entreDonnees(QRDON,L_99.c_str(),resultat->Tva->AcompteAout,clNavy);//"Acompte Aout"
	entreDonnees(QRDON,L_100.c_str(),resultat->Tva->AcompteNov, clNavy);//"Acompte Novembre"

//    Trait();
	entreDonnees(QRDON,L_101.c_str(),resultat->Tva->Solde, clNavy);//"Solde"
//    Trait();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesFinance(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	CL_TotEmp *totPlact;
	CL_TotSub *totSub;
	static float versementLT[N_X+1];
	static float versementCT[N_X+1];
	static float versementTotal[N_X+1];
	resultat=agri->Resultat;
	IniDFinance(resultat->EmpLTE,versementLT,L_102.c_str()); //"Emprunt Long Terme");
	IniDFinance(resultat->EmpCTE,versementCT,L_103.c_str());//"Emprunt Court Terme");
	if(EstVide(resultat->FraisOccc)==false)
	{
		entreDonnees(QRTITRE,L_104.c_str(),NULL); //"OCCC"
		entreDonnees(QRDON,L_105.c_str(),resultat->FraisOccc, clNavy);//"Frais Occc"
	}
	IniDFinance(resultat->EmpTotal,versementTotal,L_106.c_str()); //"RECAPITULATION"
	totSub= resultat->TotSub;
	entreDonnees(QRTITRE,L_107.c_str(),NULL);//"Subvention"
	entreDonnees(QRDON,L_107.c_str(),totSub->Valeur, clNavy);//"Subvention"
	entreDonnees(QRDON,L_108.c_str(),totSub->Amor, clNavy);//"Amortissement"
	entreDonnees(QRBIL,L_109.c_str(),totSub->Resid, clNavy);//"à amortir"
//    Blanc(1);

	if(resultat->PlactE->EstVide==false)
	{
		totPlact=resultat->PlactE;
		entreDonnees(QRTITRE,L_110.c_str(),NULL); //"Placement"
		entreDonnees(QRDON,L_110.c_str(),totPlact->Capital,clNavy);//"Placement"
		entreDonnees(QRDON,L_111.c_str(),totPlact->Remb, clNavy);//"Rentrée"
		entreDonnees(QRDON,L_112.c_str(),totPlact->Interet,clNavy);//"Intérêt"
		entreDonnees(QRBIL,L_113.c_str(),totPlact->Dette, clNavy);//"Créance"
//    Blanc(1);
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDFinance(CL_TotEmp *totEmp,
		float *versement,char *nomEmprunt)
{
	if(totEmp->EstVide==false)
	{
		for(int i=0;i<N_X;i++)versement[i]=totEmp->Remb[i]+totEmp->Interet[i];
		entreDonnees(QRTITRE,nomEmprunt,NULL);
		entreDonnees(QRDON,L_114.c_str(),totEmp->Capital, clNavy); //"Capital"
		entreDonnees(QRDON,L_115.c_str(),versement, clNavy);//"Annuité"
		entreDonnees(QRDON,L_116.c_str(),totEmp->Remb, clNavy);//"  Capital"
		entreDonnees(QRDON,L_117.c_str(),totEmp->Interet, clNavy);//"  Intérêt"
		entreDonnees(QRBIL,L_118.c_str(),totEmp->Dette, clNavy);//"Dette"
//        Blanc(1);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesImmo(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;

	entreDonnees(QRTITRE,L_81.c_str(),NULL); //"Immobilisations",NULL);

	IniDImmo (resultat,resultat->Immo,L_81.c_str());//"Immobilisations");
	IniDImmoPetit(resultat,resultat->ImmoPetit,L_119.c_str());//"Petit Matériel");
	IniDImmoSom (resultat,resultat->ImmoSom,L_120.c_str());//"Autres Immobilisations");
	IniDImmo (resultat,resultat->ImmoTotal,L_106.c_str());//"RECAPITULATION");
	/*

	 ImpImmo(resultat->ImmoSom,"Autres Immobilisations");

	 ImpImmoTotal(resultat,"RECAPITULATION");

	 Blanc(5);
	 */
}
//----------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDImmo(CL_AgriRes *resultat,CL_TotImmo *immo,char *titre)
{
	if(immo->EstVide==true) return;
	entreDonnees(QRTITRE,titre,NULL);
	entreDonnees(QRDON,L_82.c_str(),immo->Achat, clNavy); //"Achat"
	entreDonnees(QRDON,L_83.c_str(),immo->Vente, clNavy);//"Vente"
	entreDonnees(QRBIL,L_121.c_str(),immo->Resid, clNavy);//"Valeur Résiduelle"
	entreDonnees(QRDON,L_108.c_str(),immo->Amor, clNavy);//"Amortissement"
	entreDonnees(QRBIL,L_122.c_str(),resultat->ProdImmo,clNavy);//"Production d'immobilisation"
//    ResultatBilan("Plus Value",        totImmo->PlusVal,N_X,clNavy);
//    ResultatBilan("Moins Value",       totImmo->MoinsVal,N_X,clNavy);
//    Blanc(1);
}
//----------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDImmoPetit(CL_AgriRes *resultat,CL_TotImmo *immo,char *titre)
{
	if(immo->EstVide==true) return;
	entreDonnees(QRTITRE,titre,NULL);
	entreDonnees(QRDON,L_82.c_str(),immo->Achat, clNavy); //"Achat"
	entreDonnees(QRDON,L_108.c_str(),immo->Amor, clNavy);//"Amortissement"
}
//----------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDImmoSom(CL_AgriRes *resultat,CL_TotImmo *immo,char *titre)
{
	if(immo->EstVide==true) return;
	entreDonnees(QRTITRE,titre,NULL);
	entreDonnees(QRDON,L_82.c_str(),immo->Achat, clNavy); //"Achat"
	entreDonnees(QRDON,L_83.c_str(),immo->Vente, clNavy);//"Vente"
	entreDonnees(QRBIL,L_121.c_str(),immo->Resid, clNavy);//"Valeur Résiduelle"
	entreDonnees(QRDON,L_108.c_str(),immo->Amor, clNavy);//"Amortissement"
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesPerenne(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat;
	resultat=agri->Resultat;

	entreDonnees(QRBIL,L_125.c_str(),resultat->ValPlant, clNavy); //"Valeur Plantations"
	entreDonnees(QRDON,L_21.c_str(),resultat->AmorPlant, clNavy);//"Amortissement Plantation"
	entreDonnees(QRDON,L_126.c_str(),resultat->ProdImmo, clNavy);//"Prod Immo"
	entreDonnees(QRDON,L_127.c_str(),resultat->ProdImmoFam, clNavy);//"Prod Immo famille"
	entreDonnees(QRDON,L_33.c_str(), resultat->PertePlant, clNavy);//"Perte Exceptionnelle"

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesRecapEmpLT(CL_Agriculteur *agri)
{
	int i,n;
	int an_0;
	CL_EmpLT *emp;
	float capital[N_X],remb[N_X],interet[N_X],dette[N_X+1];
	float valeur[N_X];
	float total[N_X];
	AnsiString nom;

	an_0=agri->DefSim->An_0;
	memset(total,0,sizeof(total));
	//entreDonnees(QRTITRE,"Annuités + Interet LT",NULL);
	entreDonnees(QRTITRE,L_AnnuInt.c_str(),NULL);
	for(i=0;i<agri->V_EmpLT->Nbelt;i++)
	{
		emp=agri->V_EmpLT->Vecteur[i];
		emp->Calcul(an_0,capital,remb,interet,dette);
		for(n=0;n<N_X;n++) valeur[n]=remb[n]+interet[n];
		for(n=0;n<N_X;n++) total[n]+=valeur[n];
		entreDonnees(QRDON,emp->Nom.c_str(),valeur,clNavy);
	}
	//entreDonnees(QRDON,"Total",total);
	entreDonnees(QRDON,L_75.c_str(),total);

	entreDonnees(QRTITRE,"  ",NULL);
	//entreDonnees(QRTITRE,"Nouveaux Emprunts LT",NULL);
	entreDonnees(QRTITRE,L_NouvEmpLT.c_str(),NULL);
	memset(total,0,sizeof(total));
	for(i=0;i<agri->V_EmpLT->Nbelt;i++)
	{
		emp=agri->V_EmpLT->Vecteur[i];
		n=emp->ExReal;
		if(n>=0 && n< N_X)
		{
			memset(valeur,0,sizeof(total));
			valeur[n]=emp->Montant;
			total[n]+=valeur[n];
			entreDonnees(QRDON,emp->Nom.c_str(),valeur,clNavy);
		}
	}
	//entreDonnees(QRDON,"Total",total);
	entreDonnees(QRDON,L_75.c_str(),total);

	entreDonnees(QRTITRE,"  ",NULL);
	//entreDonnees(QRTITRE,"Capital Restant Du LT",NULL);
	entreDonnees(QRTITRE,L_CapDuLT.c_str(),NULL);
	memset(total,0,sizeof(total));
	for(i=0;i<agri->V_EmpLT->Nbelt;i++)
	{
		emp=agri->V_EmpLT->Vecteur[i];
		emp->Calcul(an_0,capital,remb,interet,dette);
		for(n=0;n<N_X;n++) valeur[n]=dette[n+1];
		for(n=0;n<N_X;n++) total[n]+=valeur[n];
		entreDonnees(QRDON,emp->Nom.c_str(),valeur,clNavy);
	}
	//entreDonnees(QRDON,"Total",total);
	entreDonnees(QRDON,L_75.c_str(),total);

	memset(total,0,sizeof(total));

}

//---------------------------------------------------------------------------
//280805
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::IniDonneesRecapImmo(CL_Agriculteur *agri)
{
	int i,n;
	bool ilYaTitre;
	int an_0;
	CL_Immo *immo;
	float amor[N_X],vResid[N_X+1];
	int exAchat,exVente;
	float valeur[N_X];
	float total[N_X];
	AnsiString nom;

	an_0=agri->DefSim->An_0;
	memset(total,0,sizeof(total));
	entreDonnees(QRTITRE,L_108.c_str(),NULL);
	//entreDonnees(QRTITRE,"Amortissement",NULL);
	for(i=0;i<agri->V_Immo->Nbelt;i++)
	{
		immo=agri->V_Immo->Vecteur[i];
		immo->Calcul(an_0,amor,vResid,exAchat,exVente);
		for(n=0;n<N_X;n++) total[n]+=amor[n];
		entreDonnees(QRDON,immo->Nom.c_str(),amor,clNavy);
	}
	entreDonnees(QRDON,L_75.c_str(),total);
	//entreDonnees(QRDON,"Total",total);
	entreDonnees(QRTITRE,"  ",NULL);

	//ACHAT
	memset(total,0,sizeof(total));
	ilYaTitre=false;
	for(i=0;i<agri->V_EmpLT->Nbelt;i++)
	{
		immo=agri->V_Immo->Vecteur[i];
		immo->Calcul(an_0,amor,vResid,exAchat,exVente);
		n=exAchat;
		if(n>=0 && n< N_X)
		{
			if(ilYaTitre==false)
			entreDonnees(QRTITRE,L_82.c_str(),NULL);
			//entreDonnees(QRTITRE,"Achat",NULL);
			memset(valeur,0,sizeof(total));
			valeur[n]=immo->ValAchat;
			total[n]+=valeur[n];
			entreDonnees(QRDON,immo->Nom.c_str(),valeur,clNavy);
		}
	}
	if(ilYaTitre==true)
	{
		//entreDonnees(QRDON,"Total",total);
		entreDonnees(QRDON,L_75.c_str(),total);
		entreDonnees(QRTITRE,"  ",NULL);
	}

	//REVENTE
	memset(total,0,sizeof(total));
	ilYaTitre=false;
	for(i=0;i<agri->V_EmpLT->Nbelt;i++)
	{
		immo=agri->V_Immo->Vecteur[i];
		immo->Calcul(an_0,amor,vResid,exAchat,exVente);
		n=exVente;
		if(n>=0 && n< N_X)
		{
			if(ilYaTitre==false)
			entreDonnees(QRTITRE,"Revente",NULL); //!!!!!
			ilYaTitre=true;
			memset(valeur,0,sizeof(total));
			valeur[n]=immo->ValAchat;
			total[n]+=valeur[n];
			entreDonnees(QRDON,immo->Nom.c_str(),valeur,clNavy);
		}
	}
	if(ilYaTitre==true)
	{
		entreDonnees(QRDON,L_75.c_str(),total);
		//entreDonnees(QRDON,"Total",total);
		entreDonnees(QRTITRE,"  ",NULL);
	}

	//entreDonnees(QRTITRE,"Valeur Résiduelle",NULL);
	entreDonnees(QRTITRE,L_121.c_str(),NULL);

	memset(total,0,sizeof(total));
	for(i=0;i<agri->V_Immo->Nbelt;i++)
	{
		immo=agri->V_Immo->Vecteur[i];
		immo->Calcul(an_0,amor,vResid,exAchat,exVente);
		for(n=0;n<N_X;n++) valeur[n]=vResid[n+1];
		for(n=0;n<N_X;n++) total[n]+=valeur[n];
		entreDonnees(QRDON,immo->Nom.c_str(),valeur,clNavy);
	}
	//entreDonnees(QRDON,"Total",total);
	entreDonnees(QRDON,L_75.c_str(),total);
	memset(total,0,sizeof(total));

}

