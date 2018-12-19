//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Forme01.h"

#include "AgriSaisie.h"
//#include "LBMvtAni.h"
//#include "Brouillon.h"
#include "CL_MvtAnnee.h"

#include "InvAni.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::CalculValeur(void)
{
	int r,col,i,j;
	int n;
	int eff;
	float val;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee;
	float valInv;
	for(r=1;r<GrilleInv->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
		if(invAni==NULL) continue;
		valInv=GrilleFloat(3,r);
		invAni->ValInv=valInv;
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			n=col-5;
			mvtAnnee=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
			// achat
			eff=0;
			val=0;
			for(i=0;i<mvtAnnee->iAchat;i++)
			{
				eff+=mvtAnnee->Achat[i];
				val+=mvtAnnee->Achat[i]*mvtAnnee->PrixAchat[i];
			}
			invAni->Achat[n]= eff;
			invAni->ValAchat[n]= val;
			// vente
			eff=0;
			val=0;
			for(i=0;i<mvtAnnee->iVente;i++)
			{
				eff+=mvtAnnee->Vente[i];
				val+=mvtAnnee->Vente[i]*mvtAnnee->PrixVente[i];
			}
			invAni->Vente[n]= eff;
			invAni->ValVente[n]= val;

		}
		for(j=0;j<N_X+1;j++)
		invAni->Valeur[j]=invAni->ValInv*invAni->Effectif[j];
	}
}
//---------------------------------------------------------------------------

//     SORTIES

//---------------------------------------------------------------------------
//Effectifs Achetés
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnEAchatClick(TObject *Sender)
{
	int i,nbElt;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur=Agri->V_InvAni;

//    MvtAniFrm->WindowState=wsMinimized;
	CalculValeur();
	nbElt=vecteur->Nbelt;
	Forme01Frm->Origine=0;
	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard("Effectifs Achetés",N_X,nbElt,An_0);
	for(i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->Achat);
	}

}
//Effectifs Vendus
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnEVenteClick(TObject *Sender)
{
	int i,nbElt;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur=Agri->V_InvAni;

//    MvtAniFrm->WindowState=wsMinimized;
	CalculValeur();
	nbElt=vecteur->Nbelt;
	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard("Effectifs Vendus",N_X,nbElt,An_0);
	for(i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->Vente);
	}
}
//Valeur des Achats
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnVAchatClick(TObject *Sender)
{
	int i,j,nbElt;
	float total[N_X+1];
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur=Agri->V_InvAni;

//    MvtAniFrm->WindowState=wsMinimized;
	CalculValeur();
	nbElt=vecteur->Nbelt;
	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard("Valeurs des Achats",N_X,nbElt+1,An_0);

	memset(total,0,sizeof(float)*(N_X));
	for(i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->ValAchat);
		for(j=0;j<N_X;j++) total[j]+=invAni->ValAchat[j];
	}
	Forme01Frm->EcrireLigne("Total",total);

}
//Valeur des Ventes
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnVVenteClick(TObject *Sender)
{
	int i,j,nbElt;
	float total[N_X+1];
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur=Agri->V_InvAni;

//    MvtAniFrm->WindowState=wsMinimized;
	CalculValeur();
	nbElt=vecteur->Nbelt;
	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard("Valeurs des Ventes",N_X,nbElt+1,An_0);

	memset(total,0,sizeof(float)*(N_X+1));
	for(i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->ValVente);
		for(j=0;j<N_X;j++) total[j]+=invAni->ValVente[j];
	}
	Forme01Frm->EcrireLigne("Total",total);
}
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnInventaireClick(TObject *Sender)
{
	int i,j,nbElt;
	float total[N_X+1];
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur=Agri->V_InvAni;

//    MvtAniFrm->WindowState=wsMinimized;
	CalculValeur();
	nbElt=vecteur->Nbelt;
	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard("Valeurs d'inventaire",N_X+1,nbElt+1,An_0);
	memset(total,0,sizeof(float)*(N_X+1));
	for(i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->Valeur);
		for(j=0;j<N_X+1;j++) total[j]+=invAni->Valeur[j];
	}
	Forme01Frm->EcrireLigne("Total",total);
}

