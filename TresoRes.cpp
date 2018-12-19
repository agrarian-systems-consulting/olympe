//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Forme00.h"
#include "CL_TresoMens.h"
#include "Treso.h"
#include "AgriSaisie.h"
#include "TresoGraph.h"
#include "QuelExcelCSV.h"
#include "Tableur.h"
#include "QRTresoVal.h"
#include "QrTresoQuant.h"

#include "TresoEnum.h"
#include "TresoRepart.h"
#include "CL_PossibOcPlact.h"
#include "CL_Trad.h"

#include "TresoRes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TTresoResFrm *TresoResFrm;
extern CL_Excel *EX;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTresoResFrm::TTresoResFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
// Nature soit une famille eg PRODUIT ou CHARGE soit tout AGRI
//         cf menu de TresoFrm
//CalculEn QUANTITE ou VALEUR
//          cf TresoRepartFrm->CalculEn VALEUR ou QUANTITE
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::FormActivate(TObject *Sender)
{
	int r,c;
	CL_TresoMens *tresoMens;
	if(Origine!=0) return;

	An_0=AgriEnCours->DefSim->An_0;

	Origine=1;

	for(r=0;r<SG->RowCount;r++)
	for(c=0;c<SG->ColCount;c++)
	SG->Cells[c][r]="";

	if(TresoRepartFrm->CalculEn==VALEUR)
	{
		SG->ColCount=2+10*12;
		SG->ColWidths[0]=128;
		SG->ColWidths[1]=12;
		SG->FixedCols=2;
		SG->RowCount=2;
	}
	else //QUANTITE
	{
		SG->ColCount=3+10*12;
		SG->ColWidths[0]=128;
		SG->ColWidths[1]=32;
		SG->ColWidths[2]=12;
		SG->FixedCols=3;
		SG->RowCount=2;
	}

	if(LstTresoMens==NULL)
	LstTresoMens =new TList;
	else
	LstTresoMens->Clear();

	if(TresoRepartFrm->CalculEn==VALEUR) //140107
	{
		memset(Solde, 0,sizeof(float)*120);
		memset(SoldeCumule, 0,sizeof(float)*120);
		memset(TotalRecette, 0,sizeof(float)*120);
		memset(TotalDepense, 0,sizeof(float)*120);
		memset(TvaEncaissee, 0,sizeof(float)*120);
		memset(TvaVersee, 0,sizeof(float)*120);
		memset(TvaAcompte, 0,sizeof(float)*120);
		memset(TvaRegularisation,0,sizeof(float)*120);
		memset(TvaRemboursement, 0,sizeof(float)*120);
		memset(FinancePlus, 0,sizeof(float)*120);
		memset(FinanceMoins, 0,sizeof(float)*120);
	}
	switch(Nature)
	{
		default:
		ShowMessage("TresoRepart Oubli/Nature ???");
		return;

		case PRODUIT:
		if(TresoRepartFrm->CalculEn==VALEUR)
		Caption="Produits VALEUR"; //LC_ProVal   a voir
		else
		Caption=LC_ProQuant;//"Produits QUANTITE";  //LC_ProQuant
		CreeLstTresoMens(V_CatProduit,
				AgriEnCours->Resultat->V_Produit,
				T->LC_BtBnProduit.c_str(),//"Produits",
				PRODUIT);
		break;

		case CHARGE:
		if(TresoRepartFrm->CalculEn==VALEUR)
		Caption=LC_ChaVal;//"Charges VALEUR";     //LC_ChaVal
		else
		Caption=LC_ChaQuant;//"Charges QUANTITE";   //LC_ChaQuant
		CreeLstTresoMens(V_CatCharge,
				AgriEnCours->Resultat->V_Charge,
				LC_Charges.c_str(),//"Charges",
				CHARGE);
		break;

		case CHSTRUCT:
		Caption=LC_ChStructVal;//"Charges de Structure en valeur";         //LC_ChStructVal
		CreeLstTresoMens(V_CatChStruct,
				AgriEnCours->Resultat->V_ChStruct,
				LC_ChStructVal.c_str(),//"Charges de Structure",
				CHARGE);
		break;

		case VENTE://BESTIAUX
		case ACHAT:
		if(TresoRepartFrm->CalculEn==VALEUR)
		Caption=LC_AniVal;//"Ventes et Achats d'animaux VALEUR";     //LC_AniVal
		else
		Caption=LC_AniEff;//"Ventes et Achats d'animaux EFFECTIF";   //LC_AniEff
		CreeTresoVenteNetteAni();
		break;

		case RECDIV:
		Caption=LC_RecDiv;//"Recettes Diverses";              //LC_RecDiv
		CreeLstTresoMens(V_CatRecDiv,
				AgriEnCours->Resultat->V_RecDiv,
				LC_RecDiv.c_str(),//"Recettes Diverses",
				PRODUIT);
		break;

		case DEPDIV://LC_DepDiv
		Caption=LC_DepDiv;//"Dépenses Diverses";
		CreeLstTresoMens(V_CatDepDiv,
				AgriEnCours->Resultat->V_DepDiv,
				LC_DepDiv.c_str(),//"Dépenses Diverses",
				CHARGE);
		break;

		case EXTER:
		Caption=LC_Ext;//"Externalités";                 //LC_Ext
//        CreeLstTresoMens(V_CatExternalite,AgriEnCours->Resultat->V_ExtNeg,"Externalités Négatives",PRODUIT);
//        CreeLstTresoMens(V_CatExternalite,AgriEnCours->Resultat->V_ExtPos,"Externalités Positives",PRODUIT);
		CreeLstTresoMens(V_CatExternalite,AgriEnCours->Resultat->V_ExtNeg,LC_ExtNeg.c_str(),PRODUIT);
		CreeLstTresoMens(V_CatExternalite,AgriEnCours->Resultat->V_ExtPos,LC_ExtPos.c_str(),PRODUIT);
		break;

		case RECFAM:
		Caption=LC_RecFam;//"Recettes Familiales";         //LC_RecFam
		CreeLstTresoMens(V_CatRecFam,
				AgriEnCours->Resultat->V_RecFam,
				LC_RecFam.c_str(),//"Recettes Familiales",
				PRODUIT);

		break;
		case DEPFAM:
		Caption=LC_DepFam;//"Dépenses Familiales";           //LC_DepFam
		CreeLstTresoMens(V_CatDepFam,
				AgriEnCours->Resultat->V_DepFam,
				LC_DepFam.c_str(),//"Dépenses Familiales",
				CHARGE);

		break;
		case IMMO:
		Caption=LC_Immo;//"Immobilisations";               //LC_Immo
		CreeLstTresoMensImmo();
		break;

		case PETITMAT:
		Caption=LC_PetitMat;//"Petit Matériel";               //LC_PetitMat
		CreeLstTresoMensPetit();
		break;

		case FINANCE:	//EMPLT:
		Caption=LC_Finance;"Finance";//LC_Finance
		//tresoMens=new CL_TresoMens("Finance",PRODUIT,TITREFAM);
		tresoMens=new CL_TresoMens(LC_Finance.c_str(),PRODUIT,TITREFAM);
		LstTresoMens->Add(tresoMens);
		CreeLstTresoMensEmpruntLT();
		CreeLstTresoMensEmpruntCT();
		CreeLstTresoMensSubvention();
		CreeLstTresoMensPlact();
		//LC_TotRecu
		tresoMens=new CL_TresoMens(LC_TotRecu.c_str(),FinancePlus,PRODUIT,RESGLOB);
		LstTresoMens->Add(tresoMens);
		//LC_TotSorti
		tresoMens=new CL_TresoMens(LC_TotSorti.c_str(),FinanceMoins,CHARGE,RESGLOB);
		LstTresoMens->Add(tresoMens);
		break;

		case DETTE:
		Caption=LC_CreanDette;//"Créances Dettes";       //LC_CreanDette
		CreeLstTresoMensEnCours(AgriEnCours->V_Creance,PRODUIT);
		CreeLstTresoMensEnCours(AgriEnCours->V_Dette, CHARGE);
		break;

		case AGRI:
		case OCCC:
		if(TresoRepartFrm->CalculEn==VALEUR)
		{
			if(AgriEnCours->V_Creance->Nbelt+AgriEnCours->V_Dette->Nbelt)
			{
				memset(TotalLambda, 0,sizeof(float)*120);
				//LC_CreanceEtDette
				//tresoMens=new CL_TresoMens("Créances et Dettes",PRODUIT,TITREFAM);
				tresoMens=new CL_TresoMens(LC_CreanceEtDette.c_str(),PRODUIT,TITREFAM);
				LstTresoMens->Add(tresoMens);
				CreeLstTresoMensEnCours(AgriEnCours->V_Creance,PRODUIT);
				CreeLstTresoMensEnCours(AgriEnCours->V_Dette, CHARGE);
				//LC_TotCreanceEtDette

				tresoMens=new CL_TresoMens("Total Créances Dettes",TotalLambda,PRODUIT,RESGLOB);
				tresoMens=new CL_TresoMens(LC_TotCreanceEtDette.c_str(),TotalLambda,PRODUIT,RESGLOB);
				LstTresoMens->Add(tresoMens);
			}
			CreeLstTresoMensProduit(); //(V_CatProduit, AgriEnCours->Resultat->V_Produit,  "Produits",PRODUIT);
			/*
			 CreeLstTresoMens(V_CatCharge,  AgriEnCours->Resultat->V_Charge,   "Charges",CHARGE);
			 CreeLstTresoMens(V_CatChStruct,AgriEnCours->Resultat->V_ChStruct, "Charges de Structure",CHARGE);
			 CreeLstTresoMens(V_CatRecDiv,  AgriEnCours->Resultat->V_RecDiv,   "Recettes Diverses",PRODUIT);
			 CreeLstTresoMens(V_CatDepDiv,  AgriEnCours->Resultat->V_DepDiv,   "Dépenses Diverses",CHARGE);
			 CreeLstTresoMens(V_CatRecFam,  AgriEnCours->Resultat->V_RecFam,   "Recettes Familiales",PRODUIT);
			 CreeLstTresoMens(V_CatDepFam,  AgriEnCours->Resultat->V_DepFam,   "Dépenses Familiales",CHARGE);
			 */
			CreeLstTresoMens(V_CatCharge, AgriEnCours->Resultat->V_Charge, LC_Charges.c_str(),CHARGE);
			CreeLstTresoMens(V_CatChStruct,AgriEnCours->Resultat->V_ChStruct, LC_ChStructVal.c_str(),CHARGE);
			CreeLstTresoMens(V_CatRecDiv, AgriEnCours->Resultat->V_RecDiv, LC_RecDiv.c_str(),PRODUIT);
			CreeLstTresoMens(V_CatDepDiv, AgriEnCours->Resultat->V_DepDiv, LC_DepDiv.c_str(),CHARGE);
			CreeLstTresoMens(V_CatRecFam, AgriEnCours->Resultat->V_RecFam, LC_RecFam.c_str(),PRODUIT);
			CreeLstTresoMens(V_CatDepFam, AgriEnCours->Resultat->V_DepFam, LC_DepFam.c_str(),CHARGE);
			CreeLstTresoMensImmo();

			//tresoMens=new CL_TresoMens("Finance",PRODUIT,TITREFAM);
			tresoMens=new CL_TresoMens(LC_Finance.c_str(),PRODUIT,TITREFAM);
			LstTresoMens->Add(tresoMens);

			CreeLstTresoMensEmpruntLT();
			CreeLstTresoMensEmpruntCT();
			CreeLstTresoMensSubvention();
			CreeLstTresoMensPlact();

			//tresoMens=new CL_TresoMens("Total Emprunt",FinancePlus,PRODUIT,RESGLOB);
			tresoMens=new CL_TresoMens(LC_TotEmprunt.c_str(),FinancePlus,PRODUIT,RESGLOB);
			LstTresoMens->Add(tresoMens);

			//tresoMens=new CL_TresoMens("Total Remb Emprunt",FinanceMoins,CHARGE,RESGLOB);
			tresoMens=new CL_TresoMens(LC_TotRembEmpr.c_str(),FinanceMoins,CHARGE,RESGLOB);
			LstTresoMens->Add(tresoMens);

			CalculTva();
			CalculSolde();
			if(AgriEnCours->PossibOcPlact)
			CalculOccc();

		}
		else //QUANTITE
		{
			CreeLstTresoMensProduit(); //(V_CatProduit, AgriEnCours->Resultat->V_Produit,  "Produits",PRODUIT);
			CreeLstTresoMens(V_CatCharge, AgriEnCours->Resultat->V_Charge, "Charges",CHARGE);
		}
		break;
	}

	//........Affichage
	if(TresoRepartFrm->CalculEn==VALEUR)
	{
		memset(TotalRecette,0,sizeof(TotalRecette));
		memset(TotalDepense,0,sizeof(TotalDepense));
		memset(Solde, 0,sizeof(Solde));
		memset(SoldeCumule, 0,sizeof(SoldeCumule));
		memset(TvaEncaissee,0,sizeof(TvaEncaissee));
		memset(TvaVersee, 0,sizeof(TvaVersee));
		memset(TvaAcompte, 0,sizeof(TvaAcompte));
		memset(TvaRegularisation,0,sizeof(TvaRegularisation));
		memset(TvaRemboursement,0,sizeof(TvaRemboursement));

		AffMoisAn(2);
		switch(TypeSortie)
		{
			case DETAIL: AffLesTresoMensValeurDetail(0);break;
			case SEMIDETAIL: AffLesTresoMensValeurSemiDetail(0);break;
			case GLOBAL: AffLesTresoMensValeurSynthese(0);break;
			case OCCC:;break; // voir CalculOccc qui a affiché
		}
	}
	else //QUANTITE
	{
		AffMoisAn(3);
		AffLesTresoMensQuantite(0);
		SG->Col=3;
		SG->Row=1;
	}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::AffMoisAn(int col0)
{
	int i,m;
	int an;
	int c;
	TDateTime date;
	c=col0;
	for(i=0;i<N_X;i++)
	{
		an=An_0+i;
		for(m=1;m<13;m++)
		{
			date=TDateTime(an,m,1);
			SG->Cells[c++][0]=date.FormatString("mmm  yyyy");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensProduit(void)
{
	int i,j,n;
	int qOUv; // quantité ou valeur
	float totalCat[120],totalFam[120];
	float totalProduit[120],totalVenteAni[120],totalAchatAni[120];
	bool catExiste,famExiste;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	CL_TresoMens *tresoMens,*tresoTotCat,*tresoTitreCat,*tresoTotFam,*tresoTitreFam;
	CL_Vecteur<CL_Categorie> *v_Categorie;
	CL_Vecteur<CL_QuanVal> *v_QuanVal;
	char* chProduit;
	char *chVenteAni;
	char *chAchatAni;
	chProduit=T->LC_BtBnProduit.c_str();
	chVenteAni=LC_VenteAni.c_str();
	chAchatAni=LC_AchatAni.c_str();

	qOUv=TresoRepartFrm->CalculEn;

	memset(totalFam,0,sizeof(totalFam));
	memset(totalProduit,0,sizeof(totalFam));
	memset(totalVenteAni,0,sizeof(totalFam));
	memset(totalAchatAni,0,sizeof(totalFam));

//PRODUITS
	famExiste=false;
	v_Categorie=V_CatProduit;
	v_QuanVal=AgriEnCours->Resultat->V_Produit;
	for(i=0;i<v_Categorie->Nbelt;i++)
	{
		cat=v_Categorie->Vecteur[i];
		catExiste=false;

		for(j=0;j<v_QuanVal->Nbelt;j++)
		{
			quanVal=v_QuanVal->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			if(famExiste==false)
			{
				famExiste=true;
				memset(totalProduit,0,sizeof(totalFam));
//	            tresoTitreFam=new CL_TresoMens("Produits",PRODUIT,TITREFAM);
				tresoTitreFam=new CL_TresoMens(chProduit,PRODUIT,TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}

			if(catExiste==false)
			{
				famExiste=true;
				catExiste=true;
				memset(totalCat,0,sizeof(totalCat));
				tresoTitreCat=new CL_TresoMens(cat->Nom.c_str(),PRODUIT,TITRECAT);
//                TotCategorie(v_QuanVal,cat,totalCat);  //061206
				LstTresoMens->Add(tresoTitreCat);
			}

			//tresoMens=new CL_TresoMens(quanVal,qOUv,"Produits",PRODUIT);
			tresoMens=new CL_TresoMens(quanVal,qOUv,chProduit,PRODUIT);

			LstTresoMens->Add(tresoMens);
			tresoMens->Calcul(TvaEncaissee);
			tresoMens->AdditioneDans(totalCat);
		}
		if(catExiste==true)
		{
			tresoTotCat=new CL_TresoMens(cat->Nom.c_str(),totalCat,PRODUIT,TOTCAT); //160106
			LstTresoMens->Add(tresoTotCat);
			for(n=0;n<120;n++)totalProduit[n]+=totalCat[n];
		}
	}
	if(V_CatBestiaux->Nbelt==0)
	{
		tresoTotFam=new CL_TresoMens(chProduit,totalProduit,PRODUIT,TOTFAM); //160106
		LstTresoMens->Add(tresoTotFam);
		for(n=0;n<120;n++)TotalRecette[n]+=totalProduit[n];
		return;
	}

// BESTIAUX
//   VENTES
	v_Categorie=V_CatBestiaux;
	v_QuanVal=AgriEnCours->Resultat->V_VenteAni;
	famExiste=false;

	for(i=0;i<v_Categorie->Nbelt;i++)
	{
		cat=v_Categorie->Vecteur[i];
		catExiste=false;

		for(j=0;j<v_QuanVal->Nbelt;j++)
		{
			quanVal=v_QuanVal->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			if(famExiste==false)
			{
				famExiste=true;
				memset(totalVenteAni,0,sizeof(totalFam));
				//tresoTitreFam=new CL_TresoMens("Vente d'Animaux",PRODUIT,TITREFAM);
				tresoTitreFam=new CL_TresoMens(chVenteAni,PRODUIT,TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}

			if(catExiste==false)
			{
				famExiste=true;
				catExiste=true;
				memset(totalCat,0,sizeof(totalCat));
				char *chaine;
				chaine=new char[8+cat->Nom.Length()+1];
				strcpy(chaine,"Troupeau:");
				strcat(chaine,cat->Nom.c_str());
				tresoTitreCat=new CL_TresoMens(chaine,PRODUIT,TITRECAT);
				LstTresoMens->Add(tresoTitreCat);
			}

			tresoMens=new CL_TresoMens(quanVal,qOUv,chVenteAni,PRODUIT);
			LstTresoMens->Add(tresoMens);
			tresoMens->Calcul(TvaEncaissee);
			tresoMens->AdditioneDans(totalCat);
		}
		if(catExiste==true)
		{
			tresoTotCat=new CL_TresoMens(cat->Nom.c_str(),totalCat,PRODUIT,TOTCAT); //160106
			LstTresoMens->Add(tresoTotCat);
			for(n=0;n<120;n++)totalVenteAni[n]+=totalCat[n];
		}
	}

// BESTIAUX
//   ACHATS
	famExiste=false;
	v_QuanVal=AgriEnCours->Resultat->V_AchatAni;
	for(i=0;i<v_Categorie->Nbelt;i++)
	{
		cat=v_Categorie->Vecteur[i];
		catExiste=false;

		for(j=0;j<v_QuanVal->Nbelt;j++)
		{
			quanVal=v_QuanVal->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			if(famExiste==false)
			{
				famExiste=true;
				memset(totalAchatAni,0,sizeof(totalFam));
				//tresoTitreFam=new CL_TresoMens("Achat d'Animaux",CHARGE,TITREFAM);
				tresoTitreFam=new CL_TresoMens(chAchatAni,CHARGE,TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}

			if(catExiste==false)
			{
				famExiste=true;
				catExiste=true;
				memset(totalCat,0,sizeof(totalCat));
				char *chaine;
				chaine=new char[8+cat->Nom.Length()+1];
				strcpy(chaine,"Troupeau:");
				strcat(chaine,cat->Nom.c_str());
				tresoTitreCat=new CL_TresoMens(chaine,CHARGE,TITRECAT);
				LstTresoMens->Add(tresoTitreCat);
			}

			//tresoMens=new CL_TresoMens(quanVal,qOUv,"Achat d'Animaux",CHARGE);
			tresoMens=new CL_TresoMens(quanVal,qOUv,chAchatAni,CHARGE);
			LstTresoMens->Add(tresoMens);
			tresoMens->Calcul(TvaVersee);
			tresoMens->AdditioneDans(totalCat);
		}
		if(catExiste==true)
		{
			tresoTotCat=new CL_TresoMens(cat->Nom.c_str(),totalCat,CHARGE,TOTCAT); //160106
			LstTresoMens->Add(tresoTotCat);
			for(n=0;n<120;n++)totalAchatAni[n]+=totalCat[n];
		}
	}
//TOTALISER ->Net
	for(n=0;n<120;n++)totalProduit[n]+=totalVenteAni[n]-totalAchatAni[n];

	//tresoTotFam=new CL_TresoMens("Produits",totalProduit,PRODUIT,TOTFAM); //160106
	tresoTotFam=new CL_TresoMens(chProduit,totalProduit,PRODUIT,TOTFAM);//160106
	LstTresoMens->Add(tresoTotFam);

	for(n=0;n<120;n++)TotalRecette[n]+=totalProduit[n];

}
//---------------------------------------------------------------------------
void TTresoResFrm::CreeTresoVenteNetteAni(void) {
	int i, j, n;
	int qOUv; // quantité ou valeur
	float totalCat[120], totalFam[120];
	float totalProduit[120], totalVenteAni[120], totalAchatAni[120];
	bool catExiste, famExiste;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	CL_TresoMens *tresoMens, *tresoTotCat, *tresoTitreCat, *tresoTotFam,
			*tresoTitreFam;
	CL_Vecteur<CL_Categorie> *v_Categorie;
	CL_Vecteur<CL_QuanVal> *v_QuanVal;
	AnsiString as;

//char* chProduit;
	char *chVenteAni;
	char *chAchatAni;
//	chProduit=T->LC_BtBnProduit.c_str();
	chVenteAni = LC_VenteAni.c_str();
	chAchatAni = LC_AchatAni.c_str();

	qOUv = TresoRepartFrm->CalculEn;

	memset(totalVenteAni, 0, sizeof(totalFam));
	memset(totalAchatAni, 0, sizeof(totalFam));

	if (V_CatBestiaux->Nbelt == 0)
		return;

// BESTIAUX
//   VENTES
	v_Categorie = V_CatBestiaux;
	v_QuanVal = AgriEnCours->Resultat->V_VenteAni;
	famExiste = false;

	for (i = 0; i < v_Categorie->Nbelt; i++) {
		cat = v_Categorie->Vecteur[i];
		catExiste = false;

		for (j = 0; j < v_QuanVal->Nbelt; j++) {
			quanVal = v_QuanVal->Vecteur[j];
			if (quanVal->Item->Categorie != cat)
				continue;

			if (famExiste == false) {
				famExiste = true;
				memset(totalVenteAni, 0, sizeof(totalFam));
				//tresoTitreFam=new CL_TresoMens("Vente d'Animaux",PRODUIT,TITREFAM);
				tresoTitreFam = new CL_TresoMens(chVenteAni, PRODUIT, TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}

			if (catExiste == false) {
				famExiste = true;
				catExiste = true;
				memset(totalCat, 0, sizeof(totalCat));
				//as=AnsiString("Troupeau: ")+cat->Nom;
				as = LC_Troupeau + cat->Nom;
				tresoTitreCat = new CL_TresoMens(as.c_str(), PRODUIT, TITRECAT);
				LstTresoMens->Add(tresoTitreCat);
			}

			tresoMens = new CL_TresoMens(quanVal, qOUv, chVenteAni, PRODUIT);
			LstTresoMens->Add(tresoMens);
			tresoMens->Calcul(TvaEncaissee);
			tresoMens->AdditioneDans(totalCat);
		}
		if (catExiste == true) {
			tresoTotCat = new CL_TresoMens(cat->Nom.c_str(), totalCat, PRODUIT,
					TOTCAT); //160106
			LstTresoMens->Add(tresoTotCat);
			for (n = 0; n < 120; n++)
				totalVenteAni[n] += totalCat[n];
		}
	}

// BESTIAUX
//   ACHATS
	famExiste = false;
	v_QuanVal = AgriEnCours->Resultat->V_AchatAni;
	for (i = 0; i < v_Categorie->Nbelt; i++) {
		cat = v_Categorie->Vecteur[i];
		catExiste = false;

		for (j = 0; j < v_QuanVal->Nbelt; j++) {
			quanVal = v_QuanVal->Vecteur[j];
			if (quanVal->Item->Categorie != cat)
				continue;

			if (famExiste == false) {
				famExiste = true;
				memset(totalAchatAni, 0, sizeof(totalFam));
				tresoTitreFam = new CL_TresoMens(chAchatAni, CHARGE, TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}

			if (catExiste == false) {
				famExiste = true;
				catExiste = true;
				memset(totalCat, 0, sizeof(totalCat));
				//char *chaine;
				//chaine=new char[8+cat->Nom.Length()+1];
				as = LC_Troupeau + cat->Nom;
				tresoTitreCat = new CL_TresoMens(as.c_str(), CHARGE, TITRECAT);
				//strcpy(chaine,"Troupeau:");
				//strcat(chaine,cat->Nom.c_str());
				//tresoTitreCat=new CL_TresoMens(chaine,CHARGE,TITRECAT);
				LstTresoMens->Add(tresoTitreCat);
			}

			tresoMens = new CL_TresoMens(quanVal, qOUv, chAchatAni, CHARGE);
			LstTresoMens->Add(tresoMens);
			tresoMens->Calcul(TvaVersee);
			tresoMens->AdditioneDans(totalCat);
		}
		if (catExiste == true) {
			tresoTotCat = new CL_TresoMens(cat->Nom.c_str(), totalCat, CHARGE,
					TOTCAT); //160106
			LstTresoMens->Add(tresoTotCat);
			for (n = 0; n < 120; n++)
				totalAchatAni[n] += totalCat[n];
		}
	}
//TOTALISER ->Net
	for (n = 0; n < 120; n++)
		totalProduit[n] = totalVenteAni[n] - totalAchatAni[n];

	tresoTotFam = new CL_TresoMens("Produits", totalProduit, PRODUIT, TOTFAM); //160106
	LstTresoMens->Add(tresoTotFam);

	for (n = 0; n < 120; n++)
		TotalRecette[n] += totalProduit[n];

}
//---------------------------------------------------------------------------
// total d'une categorie
void TTresoResFrm::TotCategorie(CL_Vecteur<CL_QuanVal> *v_QuanVal,
		CL_Categorie *cat, float *totalCat) //061206
		{
	int j;
	CL_QuanVal *quanVal;
	for (j = 0; j < v_QuanVal->Nbelt; j++) {
		quanVal = v_QuanVal->Vecteur[j];
		if (quanVal->Item->Categorie != cat)
			continue;
	}
}

//---------------------------------------------------------------------------
//  classés par categorie
// proOUcha PRODUIT ou CHARGE
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMens(CL_Vecteur<CL_Categorie> *v_Categorie,
		CL_Vecteur<CL_QuanVal> *v_QuanVal,
		char *famille,int proOUcha)
{
	int i,j,n;
	int qOUv; // quantité ou valeur
	float totalCat[120],totalFam[120];
	bool catExiste,famExiste;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	CL_TresoMens *tresoMens,*tresoTotCat,*tresoTitreCat,*tresoTotFam,*tresoTitreFam;
	qOUv=TresoRepartFrm->CalculEn;

	memset(totalFam,0,sizeof(totalCat));

	famExiste=false;
	for(i=0;i<v_Categorie->Nbelt;i++)
	{
		cat=v_Categorie->Vecteur[i];
		catExiste=false;

		for(j=0;j<v_QuanVal->Nbelt;j++)
		{
			quanVal=v_QuanVal->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			if(famExiste==false)
			{
				famExiste=true;
				memset(totalFam,0,sizeof(totalFam));
				tresoTitreFam=new CL_TresoMens(famille,proOUcha,TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}

			if(catExiste==false)
			{
				famExiste=true;
				catExiste=true;
				memset(totalCat,0,sizeof(totalCat));
				tresoTitreCat=new CL_TresoMens(cat->Nom.c_str(),proOUcha,TITRECAT);
				LstTresoMens->Add(tresoTitreCat);
			}

			tresoMens=new CL_TresoMens(quanVal,qOUv,famille,proOUcha);
			LstTresoMens->Add(tresoMens);
//            if(TresoRepartFrm->CalculEn==VALEUR)
//            {
			//ne calcul tva que siTreso RepartFrm->CalculEn==VALEUR
			if(tresoMens->ProOuCha==PRODUIT)
			tresoMens->Calcul(TvaEncaissee);
			else
			tresoMens->Calcul(TvaVersee);
//            }
			tresoMens->AdditioneDans(totalCat);
		}
		if(catExiste==true)
		{
			tresoTotCat=new CL_TresoMens(cat->Nom.c_str(),totalCat,proOUcha,TOTCAT);
			LstTresoMens->Add(tresoTotCat);
			for(n=0;n<120;n++)totalFam[n]+=totalCat[n];
		}
	}
	if(famExiste==false) return;

	tresoTotFam=new CL_TresoMens(famille,totalFam,proOUcha,TOTFAM); //161006
	LstTresoMens->Add(tresoTotFam);

	if(proOUcha==PRODUIT)
	for(n=0;n<120;n++)TotalRecette[n]+=totalFam[n];
	else
	for(n=0;n<120;n++)TotalDepense[n]+=totalFam[n];
}
//---------------------------------------------------------------------------
//  EnCours
//      recette ou dépense
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensEnCours(CL_Vecteur<CL_EnCours> *vecteur,int proOUcha)
{
	int i,j,n,m;
	CL_Item *item0;
	float total[120],totalCat[120];
	float tva[120];
	CL_EnCours *enCours;
	CL_TresoMens *tresoMens,*tresoTotCat,*tresoTitreCat;

	if(vecteur->Nbelt==0)return;

	if(proOUcha==PRODUIT)
	tresoTitreCat=new CL_TresoMens(LC_Creances.c_str(),PRODUIT,TITRECAT);
	else
	tresoTitreCat=new CL_TresoMens(LC_Dettes.c_str(),PRODUIT,TITRECAT);
	LstTresoMens->Add(tresoTitreCat);

	memset(totalCat,0,sizeof(totalCat));
	memset(tva, 0,sizeof(tva));

	vecteur->FlagMisA(false);

	for(i=0;i<vecteur->Nbelt;i++)
	{
		enCours=vecteur->Vecteur[i];
		if(enCours->Flag==true) continue;

		memset(total,0,sizeof(total));

		m=(enCours->APaie-An_0)*12+enCours->MPaie-1;
		if(m<0 ||m>=120) continue;

		enCours->Flag=true;
		item0=enCours->Item;
		total[m]+=enCours->Valeur;
		tva[m]+=enCours->Valeur*item0->Tva->Taux/100;
		for(j=i+1;j<vecteur->Nbelt;j++)
		{
			enCours=vecteur->Vecteur[j];
			if(enCours->Flag==true) continue;
			if(enCours->Item!=item0)continue;

			m=(enCours->APaie-An_0)*12+enCours->MPaie-1;
			if(m<0 ||m>=120) continue;

			enCours->Flag=true;
			total[m]+=enCours->Valeur;
			tva[m]+=enCours->Valeur*item0->Tva->Taux/100;

		}
		tresoMens=new CL_TresoMens(item0->Nom.c_str(),total,proOUcha,UnITEM);
		LstTresoMens->Add(tresoMens);
		Ajoute(totalCat,total);
	}
	if(proOUcha==PRODUIT)
	{
		for(n=0;n<120;n++)
		{
			TotalRecette[n]+=totalCat[n];
			TotalLambda[n]+=totalCat[n];
			TvaEncaissee[n]+=tva[n];
		}
		tresoTotCat=new CL_TresoMens("Total Créances",totalCat,PRODUIT,TOTCAT);
	}
	else
	{
		for(n=0;n<120;n++)
		{
			TotalDepense[n]+=totalCat[n];
			TotalLambda[n]-=totalCat[n];
			TvaVersee[n]+=tva[n];
		}
		tresoTotCat=new CL_TresoMens("Total Dettes",totalCat,CHARGE,TOTCAT);
	}
	LstTresoMens->Add(tresoTotCat);
}
//Immo
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensImmo(void)
{
	int r,n;
	CL_Immo *immo;
	int mVente,mAchat;
	float valVente,tvaRecu,valAchat,tvaVerse;
	float totalVente[120],totalAchat[120],solde[120];
	int nImmo,nVente,nAchat;
	CL_TresoMens *tresoMens,*tresoTitreFam;
	CL_QuanVal *quanVal=AgriEnCours->QuanValPetit;

	memset(totalVente,0,sizeof(totalVente));
	memset(totalAchat,0,sizeof(totalAchat));
	nImmo=0;
	nAchat=0;
	nVente=0;
	for( r=0;r<AgriEnCours->V_Immo->Nbelt;r++)
	{
		immo=AgriEnCours->V_Immo->Vecteur[r];

		immo->CalculTreso(An_0,mVente,valVente,tvaRecu,mAchat,valAchat,tvaVerse);
		if(valVente!=0 ||valAchat!=0)
		{
			if(nImmo==0)
			{
				tresoTitreFam=new CL_TresoMens(LC_Immo.c_str(),CHARGE,TITREFAM);
				//tresoTitreFam=new CL_TresoMens("Immobilisations",CHARGE,TITREFAM);
				LstTresoMens->Add(tresoTitreFam);
			}
			nImmo++;
			tresoMens=new CL_TresoMens(immo->Nom.c_str(),valVente,mVente,valAchat,mAchat,UnITEM,UnITEM);
			LstTresoMens->Add(tresoMens);
			if(valAchat!=0)
			{
				nAchat++;
				totalAchat[mAchat]+=valAchat;
				TvaVersee[mAchat]+=tvaVerse;
			}
			if(valVente!=0)
			{
				nVente++;
				totalVente[mVente]+=valVente;
			}
		}
	}
	quanVal=AgriEnCours->QuanValPetit;

	tresoTitreFam=new CL_TresoMens(LC_PetitMat.c_str(),CHARGE,TITREFAM);
	//tresoTitreFam=new CL_TresoMens("Petit Matériel",CHARGE,TITREFAM);
	LstTresoMens->Add(tresoTitreFam);
	tresoMens=new CL_TresoMens(quanVal,VALEUR,LC_PetitMat.c_str(),CHARGE);
	LstTresoMens->Add(tresoMens);
	tresoMens->Calcul(TvaVersee);
	tresoMens->AdditioneDans(totalAchat);
	if(nAchat )
	{
		//tresoMens=new CL_TresoMens("Total Achat",totalAchat,CHARGE,TOTCAT);
		tresoMens=new CL_TresoMens(LC_TotalAchat.c_str(),totalAchat,CHARGE,TOTCAT);
		LstTresoMens->Add(tresoMens);
	}
	if(nVente )
	{
		tresoMens=new CL_TresoMens(LC_TotalVente.c_str(),totalVente,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
	}

	for(n=0;n<120;n++)TotalRecette[n]+=totalVente[n];
	for(n=0;n<120;n++)TotalDepense[n]+=totalAchat[n];
	for(n=0;n<120;n++)solde[n]=totalAchat[n]-totalVente[n];

	//tresoMens=new CL_TresoMens("Investissement net",solde,CHARGE,RESGLOB);
	tresoMens=new CL_TresoMens(LC_InvNet.c_str(),solde,CHARGE,RESGLOB);
	LstTresoMens->Add(tresoMens);
}
//---------------------------------------------------------------------------
bool __fastcall TTresoResFrm::ilYaValeur(float *valeur)
{
	int n;
	for(n=0;n<120;n++)
	{
		if(valeur[n])
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensPetit(void)
{
	CL_QuanVal *quanVal=AgriEnCours->QuanValPetit;

	CL_TresoMens *tresoMens,*tresoTitreFam;

	//tresoTitreFam=new CL_TresoMens("Petit Matériel",CHARGE,TITREFAM);
	tresoTitreFam=new CL_TresoMens(LC_PetitMat.c_str(),CHARGE,TITREFAM);
	LstTresoMens->Add(tresoTitreFam);
	tresoMens=new CL_TresoMens(quanVal,VALEUR,LC_PetitMat.c_str(),CHARGE);
	LstTresoMens->Add(tresoMens);
	tresoMens->Calcul(TvaVersee);
}
//empLT
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensEmpruntLT(void)
{
	int r,n;
	CL_EmpLT *empLT;
	float recu[120],verse[120];
	float totalRecu[120],totalVerse[120];
	CL_TresoMens *tresoMens,*tresoTitreFam;
	bool ilYaRecu,ilYaVerse;
	int nEmp,nVerse,nRecu;;

	memset(totalRecu,0,sizeof(totalRecu));
	memset(totalVerse,0,sizeof(totalVerse));

	nEmp=0;nVerse=0;nRecu=0;

	for( r=0;r<AgriEnCours->V_EmpLT->Nbelt;r++)
	{
		empLT=AgriEnCours->V_EmpLT->Vecteur[r];

		memset(recu,0,sizeof(totalRecu));
		memset(verse,0,sizeof(totalVerse));

		empLT->RembConstantTreso(An_0,recu,verse);
		ilYaRecu=ilYaValeur(recu);
		ilYaVerse=ilYaValeur(verse);
		if(ilYaRecu) nRecu++;
		if(ilYaVerse) nVerse++;

		if(ilYaRecu==true || ilYaVerse==true)
		{
			if(nEmp==0)
			{
				tresoTitreFam=new CL_TresoMens(LC_EmpLT.c_str(),PRODUIT,TITRECAT);
				//tresoTitreFam=new CL_TresoMens("Emprunts LT",PRODUIT,TITRECAT);
				LstTresoMens->Add(tresoTitreFam);
				nEmp++;
			}
			tresoMens=new CL_TresoMens(empLT->Nom.c_str(),recu,verse,UnITEM,UnITEM);
			LstTresoMens->Add(tresoMens);

			if(ilYaRecu) Ajoute(totalRecu,recu);
			if(ilYaVerse)Ajoute(totalVerse,verse);
		}
	}

	if(nRecu)
	{
		//tresoMens=new CL_TresoMens("Total Nouveaux Emprunts",totalRecu,PRODUIT,TOTCAT);
		tresoMens=new CL_TresoMens(LC_TotNouvEmp.c_str(),totalRecu,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalRecette[n]+=totalRecu[n];
			FinancePlus[n]+=totalRecu[n];
		}
	}
	if(nVerse )
	{
		//tresoMens=new CL_TresoMens("Total Remboursements",totalVerse,CHARGE,TOTCAT);
		tresoMens=new CL_TresoMens(LC_TotRemb.c_str(),totalVerse,CHARGE,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalDepense[n]+=totalVerse[n];
			FinanceMoins[n]+=totalVerse[n];
		}
	}

}
//empCT
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensEmpruntCT(void)
{
	int r,n;
	CL_EmpCT *empCT;
	float recu[120],verse[120];
	float totalRecu[120],totalVerse[120];
	CL_TresoMens *tresoMens,*tresoTitreFam;
	bool ilYaRecu,ilYaVerse;
	int nEmp,nVerse,nRecu;;

	memset(totalRecu,0,sizeof(totalRecu));
	memset(totalVerse,0,sizeof(totalVerse));

	nEmp=0;nVerse=0;nRecu=0;

	for( r=0;r<AgriEnCours->V_EmpCT->Nbelt;r++)
	{
		empCT=AgriEnCours->V_EmpCT->Vecteur[r];

		memset(recu,0,sizeof(totalRecu));
		memset(verse,0,sizeof(totalVerse));

		empCT->CalculTreso(An_0,recu,verse);
		ilYaRecu=ilYaValeur(recu);
		ilYaVerse=ilYaValeur(verse);
		if(ilYaRecu) nRecu++;
		if(ilYaVerse) nVerse++;

		if(ilYaRecu==true || ilYaVerse==true)
		{
			if(nEmp==0)
			{
				//tresoTitreFam=new CL_TresoMens("Emprunts CT",PRODUIT,TITRECAT);
				tresoTitreFam=new CL_TresoMens(LC_EmpCT.c_str(),PRODUIT,TITRECAT);
				LstTresoMens->Add(tresoTitreFam);
				nEmp++;
			}
			tresoMens=new CL_TresoMens(empCT->Nom.c_str(),recu,verse,UnITEM,UnITEM);
			LstTresoMens->Add(tresoMens);

			if(ilYaRecu) Ajoute(totalRecu,recu);
			if(ilYaVerse)Ajoute(totalVerse,verse);
		}
	}

	if(nRecu)
	{
		//tresoMens=new CL_TresoMens("Total Nouveaux CT",totalRecu,PRODUIT,TOTCAT);
		tresoMens=new CL_TresoMens(LC_TotNouvCT.c_str(),totalRecu,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalRecette[n]+=totalRecu[n];
			FinancePlus[n]+=totalRecu[n];
		}

	}
	if(nVerse )
	{
		//tresoMens=new CL_TresoMens("Total Remboursements CT",totalVerse,CHARGE,TOTCAT);
		tresoMens=new CL_TresoMens(LC_TotRembCT.c_str(),totalVerse,CHARGE,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalDepense[n]+=totalVerse[n];
			FinanceMoins[n]+=totalVerse[n];
		}
	}
}
//Subvention
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensSubvention(void)
{
	int r,n;
	int mReal;
	CL_Sub *sub;
	float total[120];
	int nSub;
	CL_TresoMens *tresoMens,*tresoTitreFam;

	memset(total,0,sizeof(total));
	nSub=0;
	for( r=0;r<AgriEnCours->V_Sub->Nbelt;r++)
	{
		sub=AgriEnCours->V_Sub->Vecteur[r];
		mReal=(sub->AReal-An_0)*12+sub->MReal-1;
		if(mReal<0 ||mReal>=120) continue;

		if(nSub==0)
		{
			//tresoTitreFam=new CL_TresoMens("Subventions",PRODUIT,TITRECAT);
			tresoTitreFam=new CL_TresoMens(LC_Subvention.c_str(),PRODUIT,TITRECAT);
			LstTresoMens->Add(tresoTitreFam);
		}
		nSub++;
		//pour réutiliser le meme constructeur que les immo
		tresoMens=new CL_TresoMens(sub->Nom.c_str(),sub->Montant,mReal,0,0,UnITEM,UnITEM);
		LstTresoMens->Add(tresoMens);
		total[mReal]+=sub->Montant;
	}

	if(nSub)
	{
		tresoMens=new CL_TresoMens(LC_SubTot.c_str(),total,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
	}

	for(n=0;n<120;n++)
	{
		TotalRecette[n]+=total[n];
		FinancePlus[n]+=total[n];
	}
}
//Plact
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CreeLstTresoMensPlact(void)
{
	int r,n;
	CL_Plact *plact;
	float recu[120],verse[120];
	float totalRecu[120],totalVerse[120];
	CL_TresoMens *tresoMens,*tresoTitreFam;
	bool ilYaRecu,ilYaVerse;
	int nPlact,nVerse,nRecu;;

	memset(totalRecu,0,sizeof(totalRecu));
	memset(totalVerse,0,sizeof(totalVerse));

	nPlact=0;nVerse=0;nRecu=0;

	for( r=0;r<AgriEnCours->V_Plact->Nbelt;r++)
	{
		plact=AgriEnCours->V_Plact->Vecteur[r];

		memset(recu,0,sizeof(totalRecu));
		memset(verse,0,sizeof(totalVerse));

		plact->CalculTreso(An_0,recu,verse);
		ilYaRecu=ilYaValeur(recu);
		ilYaVerse=ilYaValeur(verse);
		if(ilYaRecu) nRecu++;
		if(ilYaVerse) nVerse++;

		if(ilYaRecu==true || ilYaVerse==true)
		{
			if(nPlact==0)
			{
				tresoTitreFam=new CL_TresoMens(LC_Plact.c_str(),PRODUIT,TITRECAT);
				LstTresoMens->Add(tresoTitreFam);
				nPlact++;
			}
			tresoMens=new CL_TresoMens(plact->Nom.c_str(),recu,verse,UnITEM,UnITEM);
			LstTresoMens->Add(tresoMens);

			if(ilYaVerse)Ajoute(totalVerse,verse);
			if(ilYaRecu) Ajoute(totalRecu,recu);
		}
	}

	if(nVerse)
	{
		tresoMens=new CL_TresoMens(LC_PlactTot.c_str(),totalVerse,CHARGE,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalDepense[n]+=totalVerse[n];
			FinanceMoins[n]+=totalVerse[n];
		}
	}
	if(nRecu )
	{
		//tresoMens=new CL_TresoMens("Resultats des placements",totalRecu,PRODUIT,TOTCAT);
		tresoMens=new CL_TresoMens(LC_PlactRes.c_str(),totalRecu,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalRecette[n]+=totalRecu[n];
			FinancePlus[n]+=totalRecu[n];
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::Ajoute(float *total,float *valeur)
{
	int m;
	for(m=0;m<N_X*12;m++)
	total[m]+=valeur[m];
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CalculTva(void)
{
	int n,m,i;
	CL_TresoMens *tresoMens;
	CL_TvaEnt *tva=AgriEnCours->Resultat->Tva;
	float solde[120];
	//reprise des calculs tva cf AgriSaisieCalculValeur
	memset(tva->Recu,0,sizeof(tva->Recu));
	memset(tva->Verse,0,sizeof(tva->Verse));
	memset(solde,0,sizeof(solde));

	for(n=0,i=0;n<N_X;n++)
	{
		for(m=0;m<12;m++)
		{
			tva->Recu[n] +=TvaEncaissee[i];
			tva->Verse[n] +=TvaVersee[i];
			i++;
		}
	}

	AgriSaisieFrm->CalculTva(AgriEnCours->TvaEntIni,tva);
	for(n=0;n<N_X;n++)
	{
		TvaAcompte[4+n*12]=tva->AcompteMai[n];
		TvaAcompte[7+n*12]=tva->AcompteAout[n];
		TvaAcompte[10+n*12]=tva->AcompteNov[n];
		if(n<9)
		TvaAcompte[13+n*12]=tva->AcompteFev[n+1];
	}
	for(n=0;n<N_X;n++)
	{
		TvaRegularisation[4+n*12]=tva->Regul[n];
		TvaRemboursement[4+n*12]=tva->RembTva[n];
	}
	tresoMens=new CL_TresoMens(LC_Tva.c_str(),PRODUIT,TITREFAM); //"Tva"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_TvaEnc.c_str(),TvaEncaissee,PRODUIT,RESTVA,false);//"Tva Encaissée"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_TvaVer.c_str(),TvaVersee,CHARGE,RESTVA,false);//"Tva Versée"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_TvaAc.c_str(),TvaAcompte,CHARGE,RESTVA);//"Acompte Tva"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_TvaReg.c_str(),TvaRegularisation,CHARGE,RESTVA);//"Régularisation Tva"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_TvaRemb.c_str(),TvaRemboursement,PRODUIT,RESTVA);//"Remboursement Tva"
	LstTresoMens->Add(tresoMens);
	for(n=0;n<N_X;n++)
	{
		solde[n]=TvaEncaissee[n]-TvaVersee[n]-TvaAcompte[n]-TvaRegularisation[n]+TvaRegularisation[n];
	}
	tresoMens=new CL_TresoMens(LC_TvaSolde.c_str(),solde,PRODUIT,RESGLOB); //"Solde Tva
	LstTresoMens->Add(tresoMens);
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CalculSolde(void)
{
	int i;
	float tresoIni=AgriEnCours->TresoIni;
	CL_TresoMens *tresoMens;

	for(i=0;i<120;i++)
	TotalRecette[i]+=TvaEncaissee[i]+TvaRemboursement[i];
	for(i=0;i<120;i++)
	TotalDepense[i]+=TvaVersee[i]+TvaAcompte[i]+TvaRegularisation[i];
	for(i=0;i<120;i++)
	Solde[i]= TotalRecette[i]-TotalDepense[i];

	SoldeCumule[0]=tresoIni+Solde[0];
	for(i=1;i<120;i++) SoldeCumule[i]=SoldeCumule[i-1]+Solde[i];

	tresoMens=new CL_TresoMens(LC_TotRec.c_str(),TotalRecette,PRODUIT,RESGLOB,false); //"Total Recettes ttc"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_TotDep.c_str(),TotalDepense,CHARGE,RESGLOB,false);//"Total Dépenses ttc"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_Solde.c_str(),Solde,SOLDE,RESGLOB,false);//"Solde"
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens(LC_SoldeCumul.c_str(),SoldeCumule,SOLDE,RESGLOB,false);//"Solde Cumulé"
	LstTresoMens->Add(tresoMens);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::CalculOccc(void)
{
	int n,j,m,i,r;
	int digits=0;
	float intOc1[121],intOc2[121],intPlact[121]; //evite test débordement
	float oc1[121],oc2[121],plact[121];
	float ocTot[121],intOcTot[121];
	float oc1Max,oc2Max;
	float deficit,solde,excedent;
	float taux1,taux2,tauxPlact,plactMax;
	CL_TresoMens *tresoMens;
	CL_PossibOcPlact *PossibOcPlact;
	TList *lstOccc,*lst;
	bool oc1Existe,oc2Existe,plactExiste;

	oc1Existe=false;
	oc2Existe=false;
	plactExiste=false;

	memset(SoldeApresOccc,0,sizeof(SoldeApresOccc));
	memset(SoldeApresPlact,0,sizeof(SoldeApresOccc));
	memset(ocTot,0,sizeof(ocTot));
	memset(intOcTot,0,sizeof(intOcTot));
	memset(oc1,0,sizeof(oc1));
	memset(oc2,0,sizeof(oc2));
	memset(intOc1,0,sizeof(intOc1));
	memset(intOc2,0,sizeof(intOc2));
	memset(plact,0,sizeof(plact));
	memset(intPlact,0,sizeof(intPlact));

// PossibOcPlact est créé dans TresoDefOccc
	PossibOcPlact=AgriEnCours->PossibOcPlact;

	m=0;

	for(n=0;n<N_X;n++)
	{
		oc1Max=PossibOcPlact->Max[0][n];
		oc2Max=PossibOcPlact->Max[1][n];

		taux1=PossibOcPlact->Taux[0][n]/(12*100.);
		taux2=PossibOcPlact->Taux[1][n]/(12*100.);

		tauxPlact=PossibOcPlact->PlactTaux[n]/(12*100);
		plactMax=PossibOcPlact->PlactMax[n];

		for(j=0;j<12;j++)
		{
			intOcTot[m]=intOc1[m]+intOc2[m];
			solde=SoldeCumule[m]-intOc1[m]-intOc2[m]+intPlact[m];

			deficit=0; excedent=0;

			if(solde<0)
			{
				deficit=-solde;
				if(deficit<=oc1Max)
				{
					oc1[m]=deficit;
					oc1Existe=true;
				}
				else if(deficit<=oc1Max+oc2Max)
				{
					oc1[m]=oc1Max;
					oc2[m]=deficit-oc1Max;
					oc1Existe=true;
					oc2Existe=true;
				}
				else
				{
					oc1[m]=oc1Max;
					oc2[m]=oc2Max;
					oc1Existe=true;
					oc2Existe=true;
				}
			}
			else if(plactMax==0 && solde>0) //pas de placement
			{
				excedent=solde;
			}
			else
			{
				excedent=solde;
				plact[m]=excedent;
				plactExiste=true;
				SoldeApresOccc[m]=solde-plact[m];
			}
			intOc1[m+1]=oc1[m]*taux1;
			intOc2[m+1]=oc2[m]*taux2;
			intPlact[m+1]=plact[m]*tauxPlact;

			ocTot[m]=oc1[m]; //!!!!???????
			ocTot[m]+=oc2[m];
			SoldeApresOccc[m]=solde+ocTot[m];
			SoldeApresPlact[m]=SoldeApresOccc[m]-plact[m];
			m++;
		}
	}
	if(TypeSortie==OCCC)
	{
		lstOccc =new TList;
		lst=lstOccc;
		//détail occc
		tresoMens=new CL_TresoMens(LC_SoldeCumul.c_str(),SoldeCumule,SOLDE,RESGLOB,false);//"Solde Cumulé"
		lst->Add(tresoMens);
		if(oc1Existe==true)//oc1
		{
			tresoMens=new CL_TresoMens(LC_Oc1.c_str(),oc1,SOLDE,TOTCAT,false); //"Occc  1"
			lst->Add(tresoMens);
			tresoMens=new CL_TresoMens(LC_Oc1Int.c_str(),intOc1,CHARGE,TOTCAT,false);//"Interet Oc1"
			lst->Add(tresoMens);
		}
		if(oc2Existe==true) //oc2
		{
			tresoMens=new CL_TresoMens(LC_Oc2.c_str(),oc2,SOLDE,TOTCAT,false); //"Occc  2"
			lst->Add(tresoMens);
			tresoMens=new CL_TresoMens(LC_Oc2Int.c_str(),intOc2,CHARGE,TOTCAT,false);//"Interet Oc2"
			lst->Add(tresoMens);
		}
	}
	else
	lst=LstTresoMens;

	if(oc1Existe==true) //total oc
	{
		tresoMens=new CL_TresoMens(LC_OcccInt.c_str(),intOcTot,CHARGE,TOTCAT,false); //"Interet Occc"
		lst->Add(tresoMens);
		tresoMens=new CL_TresoMens(LC_Occc.c_str(),ocTot,SOLDE,TOTCAT,false);//"Occc"
		lst->Add(tresoMens);

		tresoMens=new CL_TresoMens(LC_SolApOccc.c_str(),SoldeApresOccc,SOLDE,RESGLOB,false);//"Solde Apres Occc"
		lst->Add(tresoMens);
	}
/////////////////////
	if(plactExiste==true)
	{
		tresoMens=new CL_TresoMens(LC_PlactInt.c_str(),intPlact,SOLDE,TOTCAT,false); //"Interet Placement"
		lst->Add(tresoMens);

		tresoMens=new CL_TresoMens(LC_Plact.c_str(),plact,SOLDE,TOTCAT,false);//"Placement"
		lst->Add(tresoMens);

		tresoMens=new CL_TresoMens(LC_SoldeApPlact.c_str(),SoldeApresPlact,SOLDE,RESGLOB,false);//"Solde Apres Placement"
		lst->Add(tresoMens);
	}
	if(TypeSortie==OCCC)
	{
		r=1;
		for(i=0;i<lst->Count;i++)
		{
			tresoMens=(CL_TresoMens *)lstOccc->Items[i];
			tresoMens->AffGrilleValeur(SG,r++,digits);
			delete tresoMens;
		}
		delete lstOccc;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::AffLesTresoMensValeurDetail(int digits)
{
	int i;
	int r=1;
	CL_TresoMens *tresoMens;
	for(i=0;i<LstTresoMens->Count;i++)
	{
		tresoMens=(CL_TresoMens *)LstTresoMens->Items[i];
		tresoMens->AffGrilleValeur(SG,r++,digits);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::AffLesTresoMensValeurSemiDetail(int digits)
{
	int i;
	int r=1;
	CL_TresoMens *tresoMens;
	for(i=0;i<LstTresoMens->Count;i++)
	{
		tresoMens=(CL_TresoMens *)LstTresoMens->Items[i];
		if(tresoMens->Contient==UnITEM) continue;
		if(tresoMens->Contient==TITRECAT) continue;
		if(tresoMens->Contient==RESTVA) continue;

		tresoMens->AffGrilleValeur(SG,r++,digits);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::AffLesTresoMensValeurSynthese(int digits)
{
	int i;
	int r=1;
	CL_TresoMens *tresoMens;
	for(i=0;i<LstTresoMens->Count;i++)
	{
		tresoMens=(CL_TresoMens *)LstTresoMens->Items[i];
		if(tresoMens->Contient==UnITEM) continue;
		if(tresoMens->Contient==TITREFAM) continue;
		if(tresoMens->Contient==TITRECAT) continue;
		if(tresoMens->Contient==TOTCAT) continue;
		if(tresoMens->Contient==RESTVA) continue;

		tresoMens->AffGrilleValeur(SG,r++,digits);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::AffLesTresoMensOccc(int digits)
{
	int i;
	int r=1;
	CL_TresoMens *tresoMens;
	for(i=0;i<LstTresoMens->Count;i++)
	{
		tresoMens=(CL_TresoMens *)LstTresoMens->Items[i];
		if(tresoMens->Contient==UnITEM) continue;
		if(tresoMens->Contient==TITREFAM) continue;
		if(tresoMens->Contient==TITRECAT) continue;
		if(tresoMens->Contient==TOTCAT) continue;
		if(tresoMens->Contient==RESTVA) continue;

		tresoMens->AffGrilleValeur(SG,r++,digits);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::AffLesTresoMensQuantite(int digits)
{
	int i;
	int r=1;
	CL_TresoMens *tresoMens;
	for(i=0;i<LstTresoMens->Count;i++)
	{
		tresoMens=(CL_TresoMens *)LstTresoMens->Items[i];
		if(tresoMens->Contient==TOTCAT) continue;
		if(tresoMens->Contient==TOTFAM) continue;
		if(tresoMens->Contient==RESGLOB) continue;

		tresoMens->AffGrilleQuantite(SG,r++,digits);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::BtBnPlus12Click(TObject *Sender)
{

	if(SG->Col+12>110)return;
	SG->Col+=12;
}
//---------------------------------------------------------------------------

void __fastcall TTresoResFrm::BtBnMoin12Click(TObject *Sender)
{
	if(SG->Col-12<2) return;
	SG->Col-=12;
}
//---------------------------------------------------------------------------

void __fastcall TTresoResFrm::RGPrecisionClick(TObject *Sender)
{
	int digits;
	int r;
	CL_TresoMens *tresoMens;
	if(RGPrecision->ItemIndex==0) digits=0;
	else digits=2;
	for(r=1;r<SG->RowCount;r++)
	{
		tresoMens=(CL_TresoMens*) SG->Objects[0][r];
		if(tresoMens==NULL) continue;
		if(tresoMens->Contient==TITRECAT) continue;
		if(tresoMens->Contient==TITREFAM) continue;
		if(TresoRepartFrm->CalculEn==VALEUR)
		{
			tresoMens->AffGrilleValeur(SG,r,digits);
			//il vient d'être incrementé
			SG->RowCount--;
		}
		else
		{
			tresoMens->AffGrilleQuantite(SG,r,digits);
			SG->RowCount--;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::SGDrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString s;
	CL_TresoMens *tresoMens;
	if(ARow==0) return;

	s=SG->Cells[ACol][ARow];

	tresoMens=(CL_TresoMens*)SG->Objects[0][ARow];
	if(tresoMens==NULL) return;
//    if( ACol==0 &&(tresoMens->Contient==TITREFAM || tresoMens->Contient==TOTFAM))
	if(tresoMens->Contient==TITREFAM || tresoMens->Contient==TOTFAM)
	SG->Canvas->Brush->Color=(TColor)0x00F1E0BC;//gris bleu
	else if( tresoMens->Contient==RESGLOB )
	SG->Canvas->Brush->Color=(TColor)0x00F1E0BC;//gris bleu
//	else if( tresoMens->Contient==TITRECAT ||tresoMens->Contient==TOTCAT)
	else if( tresoMens->Contient==TOTCAT)
	SG->Canvas->Brush->Color=(TColor)0x0040FF00;//(TColor)0x00F1E0BC; //vert

	SG->Canvas->FillRect(Rect);
	SG->Canvas->TextRect(Rect,Rect.Left+1,Rect.Top+1,s);

}

/*
 if(tresoMens->Contient==TITREFAM || tresoMens->Contient==TOTFAM
 || tresoMens->Contient==RESGLOB)
 SG->Canvas->Brush->Color=(TColor)0x00F1E0BC; //gris bleu
 SG->Canvas->FillRect(Rect);
 SG->Canvas->TextRect(Rect,Rect.Left+1,Rect.Top+1,s);
 */
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::SGClick(TObject *Sender)
{
	int r;
	int colSelec;
	AnsiString s;
	CL_TresoMens *tresoMens;
	if(TresoRepartFrm->CalculEn==VALEUR)
	colSelec=1;
	else
	colSelec=2;

//	if(SG->Col!=colSelec) return;
	r=SG->Row;
	tresoMens=(CL_TresoMens*)SG->Objects[0][r];
	if(tresoMens==NULL )return;//131206

	if(SG->Cells[colSelec][r]=="X")
	{
		SG->Cells[colSelec][r]=" ";
		tresoMens->AAfficher=' ';
	}
	else
	{
		SG->Cells[colSelec][r]="X";
		tresoMens->AAfficher='G';
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::BtBnEffSelectionClick(TObject *Sender)
{
	int r;
	CL_TresoMens *tresoMens;
	int colSelec;
	if(TresoRepartFrm->CalculEn==VALEUR)
	colSelec=1;
	else
	colSelec=2;

	for(r=0;r<SG->RowCount;r++)
	{
		tresoMens=(CL_TresoMens*)SG->Objects[0][r];
		if(tresoMens==NULL )continue;

		SG->Cells[colSelec][r]=" ";
		tresoMens->AAfficher=' ';
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int i;
	CL_TresoMens *tresoMens;
//	LstTresoMens->Clear();
	for(i=0;i<LstTresoMens->Count;i++)
	{
		tresoMens=(CL_TresoMens *)LstTresoMens->Items[i];
		delete tresoMens;
	}
	delete LstTresoMens;
	LstTresoMens=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TTresoResFrm::BtBnGraphiqueClick(TObject *Sender)
{
	int n=0;
	int r;
	CL_TresoMens *tresoMens;
	int col0,i,j;
	int an;
	n=0; //131206
	for(r=0;r<SG->RowCount;r++)
	{
		tresoMens=(CL_TresoMens*)SG->Objects[0][r];
		if(tresoMens==NULL) continue;
		if(tresoMens->Contient==TITRECAT) continue;
		if(tresoMens->Contient==TITREFAM) continue;
		if(tresoMens->AAfficher==' ') continue;
		n++;
	}
	if(n==0)
	{
		ShowMessage("Aucune ligne n'est cochée");
		return;
	}

	an=AgriEnCours->DefSim->An_0;
	TresoGraphFrm->CBAn->Clear();
	for(n=0;n<N_X;n++)
	TresoGraphFrm->CBAn->Items->Add(AnsiString(an++));

	col0=SG->LeftCol;
	i=(col0-2)/12;
	j=(col0-2)%12;
	TresoGraphFrm->CBAn->ItemIndex=i;
	TresoGraphFrm->CBMois->ItemIndex=j;
	TresoGraphFrm->Origine=0;
	TresoGraphFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	EX->EcritGrilleFichier(SG,"");
	EX->FermerFichier();
}
//---------------------------------------------------------------------------

void __fastcall TTresoResFrm::BtBnImpClick(TObject *Sender)
{
	if(TresoRepartFrm->CalculEn==VALEUR)
	{
		QRTresoValFrm->LaGrille=SG;
		QRTresoValFrm->Initialise();
		QRTresoValFrm->QR->Preview();
	}
	else
	{
		QRTresoQuantFrm->LaGrille=SG;
		QRTresoQuantFrm->Initialise();
		QRTresoQuantFrm->QR->Preview();
	}
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TTresoResFrm::IniCaption(void) {
	BtBnPlus12->Caption = LC_BtBnPlus12;
	BtBnMoin12->Caption = LC_BtBnMoin12;
	BtBnGraphique->Caption = LC_BtBnGraphique;
	RGPrecision->Caption = T->LC_RGPrecision;
	TresoResFrm->Caption = LC_TresoResFrm;
}
//--------------------------------------------
void TTresoResFrm::TexteCaption(void) {
	LC_BtBnPlus12 = T->TrouveCaption("TresoRes", "LC_BtBnPlus12");
	LC_BtBnMoin12 = T->TrouveCaption("TresoRes", "LC_BtBnMoin12");
	LC_BtBnGraphique = T->TrouveCaption("TresoRes", "LC_BtBnGraphique");
	LC_RGPrecision = T->TrouveCaption("CL_Trad", "LC_RGPrecision");
	LC_TresoResFrm = T->TrouveCaption("TresoRes", "LC_TresoResFrm");
	AnsiString LC_ProVal;
	LC_ProVal = T->TrouveCaption("TresoRes", "LC_ProVal");
	LC_ProQuant = T->TrouveCaption("TresoRes", "LC_ProQuant");
	LC_ChaVal = T->TrouveCaption("TresoRes", "LC_ChaVal");
	LC_ChaQuant = T->TrouveCaption("TresoRes", "LC_ChaQuant");
	LC_ChStructVal = T->TrouveCaption("TresoRes", "LC_ChStructVal");
	LC_AniVal = T->TrouveCaption("TresoRes", "LC_AniVal");
	LC_AniEff = T->TrouveCaption("TresoRes", "LC_AniQuant");
	LC_RecDiv = T->TrouveCaption("TresoRes", "LC_RecDiv");
	LC_DepDiv = T->TrouveCaption("TresoRes", "LC_DepDiv");
	LC_Ext = T->TrouveCaption("TresoRes", "LC_Ext");
	LC_DepFam = T->TrouveCaption("TresoRes", "LC_DepFam");
	LC_RecFam = T->TrouveCaption("TresoRes", "LC_RecFam");
	LC_Immo = T->TrouveCaption("TresoRes", "LC_Immo");
	LC_PetitMat = T->TrouveCaption("TresoRes", "LC_PetitMat");
	LC_Finance = T->TrouveCaption("TresoRes", "LC_Finance");
	LC_CreanDette = T->TrouveCaption("TresoRes", "LC_CreanDette");

	LC_VenteAni = T->TrouveCaption("TresoRes", "LC_VenteAni");
	LC_AchatAni = T->TrouveCaption("TresoRes", "LC_AchatAni");
	LC_Troupeau = T->TrouveCaption("TresoRes", "LC_Troupeau");
	LC_Creances = T->TrouveCaption("TresoRes", "LC_Creances");
	LC_Dettes = T->TrouveCaption("TresoRes", "LC_Dettes");

	LC_VenteAni = T->TrouveCaption("TresoRes", "LC_VenteAni");
	LC_AchatAni = T->TrouveCaption("TresoRes", "LC_AchatAni");
	LC_Troupeau = T->TrouveCaption("TresoRes", "LC_Troupeau");
	LC_Creances = T->TrouveCaption("TresoRes", "LC_Creances");
	LC_Dettes = T->TrouveCaption("TresoRes", "LC_Dettes");
	LC_Charges = T->TrouveCaption("TresoRes", "LC_Charges");
	LC_TotRecu = T->TrouveCaption("TresoRes", "LC_TotRecu");
	LC_TotSorti = T->TrouveCaption("TresoRes", "LC_TotSorti");
	LC_CreanceEtDette = T->TrouveCaption("TresoRes", "LC_CreanceEtDette");
	LC_TotEmprunt = T->TrouveCaption("TresoRes", "LC_TotEmprunt");
	LC_TotRembEmpr = T->TrouveCaption("TresoRes", "LC_TotRembEmpr");

	LC_TotalAchat = T->TrouveCaption("TresoRes", "LC_TotalAchat");
	LC_TotalVente = T->TrouveCaption("TresoRes", "LC_TotalVente");
	LC_InvNet = T->TrouveCaption("TresoRes", "LC_InvNet");
	LC_EmpLT = T->TrouveCaption("TresoRes", "LC_EmpLT");
	LC_TotNouvEmp = T->TrouveCaption("TresoRes", "LC_TotNouvEmp");
	LC_TotRemb = T->TrouveCaption("TresoRes", "LC_TotRemb");
	LC_EmpCT = T->TrouveCaption("TresoRes", "LC_EmpCT");
	LC_TotNouvCT = T->TrouveCaption("TresoRes", "LC_TotNouvCT");
	LC_TotRembCT = T->TrouveCaption("TresoRes", "LC_TotRembCT");
	LC_Subvention = T->TrouveCaption("TresoRes", "LC_Subvention");
	LC_SubTot = T->TrouveCaption("TresoRes", "LC_SubTot");
	LC_Plact = T->TrouveCaption("TresoRes", "LC_Plact");
	LC_PlactTot = T->TrouveCaption("TresoRes", "LC_PlactTot");
	LC_PlactRes = T->TrouveCaption("TresoRes", "LC_PlactRes");
	LC_Tva = T->TrouveCaption("TresoRes", "LC_Tva");
	LC_TvaEnc = T->TrouveCaption("TresoRes", "LC_TvaEnc");
	LC_TvaVer = T->TrouveCaption("TresoRes", "LC_TvaVer");
	LC_TvaAc = T->TrouveCaption("TresoRes", "LC_TvaAc");
	LC_TvaReg = T->TrouveCaption("TresoRes", "LC_TvaReg");
	LC_TvaRemb = T->TrouveCaption("TresoRes", "LC_TvaRemb");
	LC_TvaSolde = T->TrouveCaption("TresoRes", "LC_TvaSolde");

	LC_TotRec = T->TrouveCaption("TresoRes", "LC_TotRec");
	LC_TotDep = T->TrouveCaption("TresoRes", "LC_TotDep");
	LC_Solde = T->TrouveCaption("TresoRes", "LC_Solde");
	LC_SoldeCumul = T->TrouveCaption("TresoRes", "LC_SoldeCumul");
	LC_Oc1 = T->TrouveCaption("TresoRes", "LC_Oc1");
	LC_Oc1Int = T->TrouveCaption("TresoRes", "LC_Oc1Int");
	LC_Oc2 = T->TrouveCaption("TresoRes", "LC_Oc2");
	LC_Oc2Int = T->TrouveCaption("TresoRes", "LC_Oc1Int");

	LC_Occc = T->TrouveCaption("TresoRes", "LC_Occc");
	LC_OcccInt = T->TrouveCaption("TresoRes", "LC_OcccInt");
	LC_SolApOccc = T->TrouveCaption("TresoRes", "LC_SolApOccc");

	LC_PlactInt = T->TrouveCaption("TresoRes", "LC_PlactInt");
	LC_SoldeApPlact = T->TrouveCaption("TresoRes", "LC_SoldeApPlact");

	IniCaption();

}
//--------------------------------------------

