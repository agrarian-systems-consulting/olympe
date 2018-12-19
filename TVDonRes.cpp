//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "TVDonRes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVDonResFrm *TVDonResFrm;
//---------------------------------------------------------------------------
__fastcall TTVDonResFrm::TTVDonResFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVDonResFrm::CreeTV(void)
{
	CreeTVDon();
	CreeTVRes();
}
//---------------------------------------------------------------------------
void __fastcall TTVDonResFrm::CreeTVDon(void)
{
	TTreeView *tV=TVDon;
	CL_Agriculteur *agri=AgriEnCours;
	TTreeNode *tn0,*tn1,*tn2;
	//   TV->Visible=false;
	tV->Items->Clear();

	tn0=new TTreeNode(tV->Items);
	//PRODUCTION
	tn1=tV->Items->AddChildObject(tn0,"Production",NULL);
	if(agri->V_Culture->Nbelt)
	{
		tn2=tV->Items->AddChildObject(tn1,"Assolement",NULL);
		BrancheValeur(tV,tn2,agri->V_Culture);
	}
	if(agri->V_Animaux->Nbelt)
	{
		tn2=tV->Items->AddChildObject(tn1,"Animaux",NULL);
		BrancheValeur(tV,tn2,agri->V_Animaux);
	}
	//perennes vivriers bestiaux !!!!!!!!

	//VARIABLES
	if(agri->V_Variable->Nbelt)
	{
		tn1=tV->Items->AddChildObject(tn0,"Variables",NULL);
		BrancheValeur(tV,tn1,agri->V_Variable);
	}
	//PRODUITS
	if(agri->Resultat->V_Produit->Nbelt)
	{
		tn1=tV->Items->AddChildObject(tn0,"Produits",NULL);
		//Quantités
		tn2=tV->Items->AddChildObject(tn1,"Quantités",NULL);
		BrancheQuanValValeur(tV,tn2,agri->Resultat->V_Produit);
		//Prix
		tn2=tV->Items->AddChildObject(tn1,"Prix",NULL);
		BrancheQuanValPrix(tV,tn2,agri->Resultat->V_Produit);
	}
	//CHARGES
	if(agri->Resultat->V_Produit->Nbelt)
	{
		tn1=tV->Items->AddChildObject(tn0,"Charges",NULL);
		//Quantités
		tn2=tV->Items->AddChildObject(tn1,"Quantités",NULL);
		BrancheQuanValValeur(tV,tn2,agri->Resultat->V_Charge);
		//Prix
		tn2=tV->Items->AddChildObject(tn1,"Prix",NULL);
		BrancheQuanValPrix(tV,tn2,agri->Resultat->V_Charge);
	}

}
//---------------------------------------------------------------------------
void __fastcall TTVDonResFrm::BrancheValeur(TTreeView *tV,TTreeNode *tn0,
		CL_Vecteur<CL_Valeur> *vecteur)
{
	int n;
	CL_Valeur *valeur;
	for(n=0;n<vecteur->Nbelt;n++)
	{
		valeur=vecteur->Vecteur[n];
		if(valeur->Atelier)
		tV->Items->AddChildObject(tn0,valeur->Atelier->Nom,valeur->Valeur);
		else
		tV->Items->AddChildObject(tn0,valeur->Item->Nom,valeur->Valeur);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDonResFrm::BrancheQuanValValeur(TTreeView *tV,TTreeNode *tn0,
		CL_Vecteur<CL_QuanVal> *vecteur)
{
	int n;
	CL_QuanVal *quanVal;
	for(n=0;n<vecteur->Nbelt;n++)
	{
		quanVal=vecteur->Vecteur[n];
		tV->Items->AddChildObject(tn0,quanVal->Item->Nom,quanVal->Qte);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDonResFrm::BrancheQuanValPrix(TTreeView *tV,TTreeNode *tn0,
		CL_Vecteur<CL_QuanVal> *vecteur)
{
	int n;
	CL_QuanVal *quanVal;
	for(n=0;n<vecteur->Nbelt;n++)
	{
		quanVal=vecteur->Vecteur[n];
		//voir comment on peut avoir prix et ou le stocker!!
		tV->Items->AddChildObject(tn0,quanVal->Item->Nom,quanVal->Qte);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDonResFrm::CreeTVRes(void)
{
}
