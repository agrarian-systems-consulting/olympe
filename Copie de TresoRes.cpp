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

#include "TresoRes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TTresoResFrm *TresoResFrm;
extern CL_Excel *EX;
//---------------------------------------------------------------------------
__fastcall TTresoResFrm::TTresoResFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
// Nature soit une famille eg PRODUIt soit ensemble AGRI
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

	switch(Nature)
	{
		case PRODUIT:
		if(TresoRepartFrm->CalculEn==VALEUR)
		Caption="Produits VALEUR";
		else
		Caption="Produits QUANTITE";
		CreeLstTresoMens(V_CatProduit,
				AgriEnCours->Resultat->V_Produit,
				"Produits",
				PRODUIT);
		break;

		case CHARGE:
		if(TresoRepartFrm->CalculEn==VALEUR)
		Caption="Charges VALEUR";
		else
		Caption="Charges QUANTITE";
		CreeLstTresoMens(V_CatCharge,
				AgriEnCours->Resultat->V_Charge,
				"Charges",
				CHARGE);
		break;
		case CHSTRUCT:
		Caption="Charges de Structure en valeur";
		CreeLstTresoMens(V_CatChStruct,
				AgriEnCours->Resultat->V_ChStruct,
				"Charges de Structure",
				CHARGE);
		break;
		case RECDIV:
		Caption="Recettes Diverses";
		CreeLstTresoMens(V_CatRecDiv,
				AgriEnCours->Resultat->V_RecDiv,
				"Recettes Diverses",
				PRODUIT);
		break;
		case DEPDIV:
		Caption="Dépenses Diverses";
		CreeLstTresoMens(V_CatDepDiv,
				AgriEnCours->Resultat->V_DepDiv,
				"Dépenses Diverses",
				CHARGE);
		break;

		case EXTER:
		Caption="Externalités";
		CreeLstTresoMens(V_CatExternalite,AgriEnCours->Resultat->V_ExtNeg,"Externalités Négatives",PRODUIT);
		CreeLstTresoMens(V_CatExternalite,AgriEnCours->Resultat->V_ExtPos,"Externalités Positives",PRODUIT);
		break;

		case RECFAM:
		Caption="Recettes Familiales";
		CreeLstTresoMens(V_CatRecFam,
				AgriEnCours->Resultat->V_RecFam,
				"Recettes Familiales",
				PRODUIT);

		break;
		case DEPFAM:
		Caption="Dépenses Familiales";
		CreeLstTresoMens(V_CatDepFam,
				AgriEnCours->Resultat->V_DepFam,
				"Dépenses Familiales",
				CHARGE);

		break;
		case IMMO:
		Caption="Immobilisations";
		CreeLstTresoMensImmo();
		break;

		case PETITMAT:
		Caption="Petit Matériel";
		CreeLstTresoMensPetit();
		break;

		case FINANCE: //EMPLT:
		Caption="Finance";
		tresoMens=new CL_TresoMens("Finance",PRODUIT,TITREFAM);
		LstTresoMens->Add(tresoMens);
		CreeLstTresoMensEmpruntLT();
		CreeLstTresoMensEmpruntCT();
		CreeLstTresoMensSubvention();
		CreeLstTresoMensPlact();

		tresoMens=new CL_TresoMens("Total Reçu",FinancePlus,PRODUIT,RESGLOB);
		LstTresoMens->Add(tresoMens);

		tresoMens=new CL_TresoMens("Total Sortie",FinanceMoins,CHARGE,RESGLOB);
		LstTresoMens->Add(tresoMens);
		break;

		case DETTE:
		Caption="Créances Dettes";
		CreeLstTresoMensEnCours(AgriEnCours->V_Creance,PRODUIT);
		CreeLstTresoMensEnCours(AgriEnCours->V_Dette, CHARGE);
		break;

		case AGRI:
		case OCCC:
		if(AgriEnCours->V_Creance->Nbelt+AgriEnCours->V_Dette->Nbelt)
		{
			memset(TotalLambda, 0,sizeof(float)*120);
			tresoMens=new CL_TresoMens("Créances et Dettes",PRODUIT,TITREFAM);
			LstTresoMens->Add(tresoMens);
			CreeLstTresoMensEnCours(AgriEnCours->V_Creance,PRODUIT);
			CreeLstTresoMensEnCours(AgriEnCours->V_Dette, CHARGE);
			tresoMens=new CL_TresoMens("Total Créances Dettes",TotalLambda,PRODUIT,RESGLOB);
			LstTresoMens->Add(tresoMens);
		}
		CreeLstTresoMens(V_CatProduit, AgriEnCours->Resultat->V_Produit, "Produits",PRODUIT);
		CreeLstTresoMens(V_CatCharge, AgriEnCours->Resultat->V_Charge, "Charges",CHARGE);
		CreeLstTresoMens(V_CatChStruct,AgriEnCours->Resultat->V_ChStruct, "Charges de Structure",CHARGE);
		CreeLstTresoMens(V_CatRecDiv, AgriEnCours->Resultat->V_RecDiv, "Recettes Diverses",PRODUIT);
		CreeLstTresoMens(V_CatDepDiv, AgriEnCours->Resultat->V_DepDiv, "Dépenses Diverses",CHARGE);
		CreeLstTresoMens(V_CatRecFam, AgriEnCours->Resultat->V_RecFam, "Recettes Familiales",PRODUIT);
		CreeLstTresoMens(V_CatDepFam, AgriEnCours->Resultat->V_DepFam, "Dépenses Familiales",CHARGE);

		CreeLstTresoMensImmo();

		tresoMens=new CL_TresoMens("Finance",PRODUIT,TITREFAM);
		LstTresoMens->Add(tresoMens);

		CreeLstTresoMensEmpruntLT();
		CreeLstTresoMensEmpruntCT();
		CreeLstTresoMensSubvention();
		CreeLstTresoMensPlact();

		tresoMens=new CL_TresoMens("Total Emprunt",FinancePlus,PRODUIT,RESGLOB);
		LstTresoMens->Add(tresoMens);

		tresoMens=new CL_TresoMens("Total Remb Emprunt",FinanceMoins,CHARGE,RESGLOB);
		LstTresoMens->Add(tresoMens);

		CalculTva();
		CalculSolde();
		if(AgriEnCours->PossibOcPlact)
		CalculOccc();

		break;
		default:
		ShowMessage("TresoRepart Oubli/nNature ???");
		return;
	}
	memset(TotalRecette,0,sizeof(TotalRecette));
	memset(TotalDepense,0,sizeof(TotalDepense));
	memset(Solde, 0,sizeof(Solde));
	memset(SoldeCumule, 0,sizeof(SoldeCumule));
	memset(TvaEncaissee,0,sizeof(TvaEncaissee));
	memset(TvaVersee, 0,sizeof(TvaVersee));
	memset(TvaAcompte, 0,sizeof(TvaAcompte));
	memset(TvaRegularisation,0,sizeof(TvaRegularisation));
	memset(TvaRemboursement,0,sizeof(TvaRemboursement));

	if(TresoRepartFrm->CalculEn==VALEUR)
	{
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
			SG->Cells[c++][0]=date.FormatString("mmm  yy");
		}
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
			if(tresoMens->ProOuCha==PRODUIT)
			tresoMens->Calcul(TvaEncaissee);
			else
			tresoMens->Calcul(TvaVersee);
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

	tresoTotFam=new CL_TresoMens(famille,totalFam,proOUcha,TOTFAM);
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
	tresoTitreCat=new CL_TresoMens("Créances",PRODUIT,TITRECAT);
	else
	tresoTitreCat=new CL_TresoMens("Dettes",PRODUIT,TITRECAT);
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

		immo->CalculTreso(mVente,valVente,tvaRecu,mAchat,valAchat,tvaVerse);
		if(valVente!=0 ||valAchat!=0)
		{
			if(nImmo==0)
			{
				tresoTitreFam=new CL_TresoMens("Immobilisations",CHARGE,TITREFAM);
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

	tresoTitreFam=new CL_TresoMens("Petit Matériel",CHARGE,TITREFAM);
	LstTresoMens->Add(tresoTitreFam);
	tresoMens=new CL_TresoMens(quanVal,VALEUR,"Petit Matériel",CHARGE);
	LstTresoMens->Add(tresoMens);
	tresoMens->Calcul(TvaVersee);
	tresoMens->AdditioneDans(totalAchat);
	if(nAchat )
	{
		tresoMens=new CL_TresoMens("Total Achat",totalAchat,CHARGE,TOTCAT);
		LstTresoMens->Add(tresoMens);
	}
	if(nVente )
	{
		tresoMens=new CL_TresoMens("Total Ventes",totalVente,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
	}

	for(n=0;n<120;n++)TotalRecette[n]+=totalVente[n];
	for(n=0;n<120;n++)TotalDepense[n]+=totalAchat[n];
	for(n=0;n<120;n++)solde[n]=totalAchat[n]-totalVente[n];

	tresoMens=new CL_TresoMens("Investissement net",solde,CHARGE,RESGLOB);
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

	tresoTitreFam=new CL_TresoMens("Petit Matériel",CHARGE,TITREFAM);
	LstTresoMens->Add(tresoTitreFam);
	tresoMens=new CL_TresoMens(quanVal,VALEUR,"Petit Matériel",CHARGE);
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

		empLT->RembConstantTreso(recu,verse);
		ilYaRecu=ilYaValeur(recu);
		ilYaVerse=ilYaValeur(verse);
		if(ilYaRecu) nRecu++;
		if(ilYaVerse) nVerse++;

		if(ilYaRecu==true || ilYaVerse==true)
		{
			if(nEmp==0)
			{
				tresoTitreFam=new CL_TresoMens("Emprunts LT",PRODUIT,TITRECAT);
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
		tresoMens=new CL_TresoMens("Total Nouveaux Emprunts",totalRecu,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalRecette[n]+=totalRecu[n];
			FinancePlus[n]+=totalRecu[n];
		}
	}
	if(nVerse )
	{
		tresoMens=new CL_TresoMens("Total Remboursements",totalVerse,CHARGE,TOTCAT);
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

		empCT->CalculTreso(recu,verse);
		ilYaRecu=ilYaValeur(recu);
		ilYaVerse=ilYaValeur(verse);
		if(ilYaRecu) nRecu++;
		if(ilYaVerse) nVerse++;

		if(ilYaRecu==true || ilYaVerse==true)
		{
			if(nEmp==0)
			{
				tresoTitreFam=new CL_TresoMens("Emprunts CT",PRODUIT,TITRECAT);
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
		tresoMens=new CL_TresoMens("Total Nouveaux CT",totalRecu,PRODUIT,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalRecette[n]+=totalRecu[n];
			FinancePlus[n]+=totalRecu[n];
		}

	}
	if(nVerse )
	{
		tresoMens=new CL_TresoMens("Total Remboursements CT",totalVerse,CHARGE,TOTCAT);
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
			tresoTitreFam=new CL_TresoMens("Subventions",PRODUIT,TITRECAT);
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
		tresoMens=new CL_TresoMens("Total Subventions",total,PRODUIT,TOTCAT);
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

		plact->CalculTreso(recu,verse);
		ilYaRecu=ilYaValeur(recu);
		ilYaVerse=ilYaValeur(verse);
		if(ilYaRecu) nRecu++;
		if(ilYaVerse) nVerse++;

		if(ilYaRecu==true || ilYaVerse==true)
		{
			if(nPlact==0)
			{
				tresoTitreFam=new CL_TresoMens("Placements",PRODUIT,TITRECAT);
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
		tresoMens=new CL_TresoMens("Total Placements faits",totalVerse,CHARGE,TOTCAT);
		LstTresoMens->Add(tresoMens);
		for(n=0;n<120;n++)
		{
			TotalDepense[n]+=totalVerse[n];
			FinanceMoins[n]+=totalVerse[n];
		}
	}
	if(nRecu )
	{
		tresoMens=new CL_TresoMens("Resultats des placements",totalRecu,PRODUIT,TOTCAT);
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
	tresoMens=new CL_TresoMens("Tva",PRODUIT,TITREFAM);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Tva Encaissée",TvaEncaissee,PRODUIT,RESTVA,false);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Tva Versée",TvaVersee,CHARGE,RESTVA,false);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Acompte Tva",TvaAcompte,CHARGE,RESTVA);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Régularisation Tva",TvaRegularisation,CHARGE,RESTVA);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Remboursement Tva",TvaRemboursement,PRODUIT,RESTVA);
	LstTresoMens->Add(tresoMens);
	for(n=0;n<N_X;n++)
	{
		solde[n]=TvaEncaissee[n]-TvaVersee[n]-TvaAcompte[n]-TvaRegularisation[n]+TvaRegularisation[n];
	}
	tresoMens=new CL_TresoMens("Solde Tva",solde,PRODUIT,RESGLOB);
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

	tresoMens=new CL_TresoMens("Total Recettes ttc",TotalRecette,PRODUIT,RESGLOB,false);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Total Dépenses ttc",TotalDepense,CHARGE,RESGLOB,false);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Solde",Solde,SOLDE,RESGLOB,false);
	LstTresoMens->Add(tresoMens);

	tresoMens=new CL_TresoMens("Solde Cumulé",SoldeCumule,SOLDE,RESGLOB,false);
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
		tresoMens=new CL_TresoMens("Solde Cumulé",SoldeCumule,SOLDE,RESGLOB,false);
		lst->Add(tresoMens);
		if(oc1Existe==true)//oc1
		{
			tresoMens=new CL_TresoMens("Occc  1",oc1,SOLDE,TOTCAT,false);
			lst->Add(tresoMens);
			tresoMens=new CL_TresoMens("Interet Oc1",intOc1,CHARGE,TOTCAT,false);
			lst->Add(tresoMens);
		}
		if(oc2Existe==true) //oc2
		{
			tresoMens=new CL_TresoMens("Occc  2",oc2,SOLDE,TOTCAT,false);
			lst->Add(tresoMens);
			tresoMens=new CL_TresoMens("Interet Oc2",intOc2,CHARGE,TOTCAT,false);
			lst->Add(tresoMens);
		}
	}
	else
	lst=LstTresoMens;

	if(oc1Existe==true) //total oc
	{
		tresoMens=new CL_TresoMens("Interet Occc",intOcTot,CHARGE,TOTCAT,false);
		lst->Add(tresoMens);
		tresoMens=new CL_TresoMens("Occc",ocTot,SOLDE,TOTCAT,false);
		lst->Add(tresoMens);

		tresoMens=new CL_TresoMens("Solde Apres Occc",SoldeApresOccc,SOLDE,RESGLOB,false);
		lst->Add(tresoMens);
	}

	if(plactExiste==true)
	{
		tresoMens=new CL_TresoMens("Interet Placement",intPlact,SOLDE,TOTCAT,false);
		lst->Add(tresoMens);

		tresoMens=new CL_TresoMens("Placement",plact,SOLDE,TOTCAT,false);
		lst->Add(tresoMens);

		tresoMens=new CL_TresoMens("Solde Apres Placement",SoldeApresPlact,SOLDE,RESGLOB,false);
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

//    if(SG->FixedCols==1)
//    	SG->FixedCols=2;
	SG->Col+=12;
//    SG->FixedCols=1;//???????
}
//---------------------------------------------------------------------------

void __fastcall TTresoResFrm::BtBnMoin12Click(TObject *Sender)
{

	if(SG->Col-12<2) return;
	//   if(SG->FixedCols==1)
	//	SG->FixedCols=2;
	SG->Col-=12;
	//SG->FixedCols=1;//???????
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

		tresoMens->AffGrilleValeur(SG,r,digits);
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
	if( ACol==0 &&(tresoMens->Contient==TITREFAM || tresoMens->Contient==TOTFAM))
	SG->Canvas->Brush->Color=(TColor)0x00F1E0BC; //gris bleu
	else if( tresoMens->Contient==RESGLOB )
	SG->Canvas->Brush->Color=(TColor)0x00F1E0BC;//gris bleu

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
	int colSelec;;
	AnsiString s;
	CL_TresoMens *tresoMens;
	if(TresoRepartFrm->CalculEn==VALEUR)
	colSelec=1;
	else
	colSelec=2;

//	if(SG->Col!=colSelec) return;
	r=SG->Row;
	tresoMens=(CL_TresoMens*)SG->Objects[0][r];
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
	TresoGraphFrm->Origine=0;
	TresoGraphFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoResFrm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	EX->EcritGrilleFichier(SG);
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

