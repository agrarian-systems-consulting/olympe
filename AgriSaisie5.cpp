//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"

#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "Erreur.h"

#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalLT(void)
{
	CL_AgriRes *resultat;
	CL_EmpLT *empLT;
	CL_TotEmp *totEmpE,*totEmpP;
	float capital[N_X],remb[N_X],interet[N_X],dette[N_X+1];

	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totEmpE=resultat->EmpLTE;
	totEmpE->Maz(); //met EstVide à true
	totEmpP=resultat->EmpLTP;
	totEmpP->Maz();

	for(int i=0;i<Agri->V_EmpLT->Nbelt;i++)
	{
		empLT=Agri->V_EmpLT->Vecteur[i];
		empLT->Calcul (capital,remb,interet,dette);
		memset(capital,0,sizeof(float)*N_X);
		if(empLT->ExReal>=0 && empLT->ExReal<N_X)
		capital[empLT->ExReal]=empLT->Montant;
		if(empLT->Pour==CarEnt)
		/* TODO : verifier capital LT */
		totEmpE->Ajoute (capital,remb,interet,dette);
		else
		totEmpP->Ajoute (capital,remb,interet,dette);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalCT(void)
{
	CL_AgriRes *resultat;
	CL_EmpCT *empCT;
	CL_TotEmp *totEmpE,*totEmpP;
	float capital[N_X],remb[N_X],interet[N_X],dette[N_X+1];

	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totEmpE=resultat->EmpCTE;
	totEmpE->Maz();
	totEmpP=resultat->EmpCTP;
	totEmpP->Maz();

	for(int i=0;i<Agri->V_EmpCT->Nbelt;i++)
	{
		empCT=Agri->V_EmpCT->Vecteur[i];
		empCT->Calcul (capital,remb,interet,dette);
		if(empCT->Pour==CarEnt)
		totEmpE->Ajoute (capital,remb,interet,dette);
		else
		totEmpP->Ajoute (capital,remb,interet,dette);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalOCCC(void)
{
	CL_AgriRes *resultat;
	CL_Occc *occc;
	CL_Vecteur<CL_Occc> *vecteur=Agri->V_Occc;
	int nbelt,r,n;
	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;
	for( n=0;n<N_X;n++)
	resultat->FraisOccc[n]=0;

	nbelt=vecteur->Nbelt;
	for( r=0;r<nbelt;r++)
	{
		occc=vecteur->Vecteur[r];
		n=occc->Ex-1;
		resultat->FraisOccc[n]=occc->Montant*(occc->Pcent/100.)*(occc->Taux/100.);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalSub(void)
{
	CL_AgriRes *resultat;
	CL_Sub *sub;
	CL_Vecteur<CL_Sub> *vecteur=Agri->V_Sub;
	float amor[N_X],vResid[N_X+1];

	int nbelt,r,n;
	if(Agri->Resultat==NULL)
	Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	nbelt=vecteur->Nbelt;

	memset(resultat->Subvention, 0,sizeof(float)*N_X);
	memset(resultat->SubAmor, 0,sizeof(float)*N_X);
	memset(resultat->SubResid, 0,sizeof(float)*(N_X+1));

	for( r=0;r<nbelt;r++)
	{
		sub=vecteur->Vecteur[r];
		//memset(amor,  0,sizeof(float)*N_X);
		//memset(vResid,0,sizeof(float)*(N_X+1));

		sub->Calcul(amor,vResid);
		n=sub->ExReal;
		if(n>=0 && n< N_X)
		resultat->Subvention[n]+=sub->Montant;
		for(n=0; n<N_X; n++)
		resultat->SubAmor[n]+=amor[n];
		for(n=0;n<N_X+1;n++)
		resultat->SubResid[n]+=vResid[n];

	}
}

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalPlact(void)
{
	CL_AgriRes *resultat;
	CL_Plact *plact;
	CL_TotEmp *totPlactE,*totPlactP;
	float capital[N_X],remb[N_X],interet[N_X],dette[N_X+1];

	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totPlactE=resultat->PlactE;
	totPlactE->Maz();
	totPlactP=resultat->PlactP;
	totPlactP->Maz();

	for(int i=0;i<Agri->V_Plact->Nbelt;i++)
	{
		plact=Agri->V_Plact->Vecteur[i];
		plact->Calcul (capital,remb,interet,dette);
		if(plact->Pour==CarEnt)
		totPlactE->Ajoute (capital,remb,interet,dette);
		else
		totPlactP->Ajoute (capital,remb,interet,dette);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalFinSom(void)
{
	int i,j;
	CL_AgriRes *resultat;
	CL_FN_Xp1 *fN_Xp1;
	CL_TotEmp *totEmpLT,*totEmpCT;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_FinSom;

	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totEmpLT=resultat->EmpSomLT;
	totEmpLT->Maz();
	totEmpCT=resultat->EmpSomCT;
	totEmpCT->Maz();
	if(vecteur->Nbelt==0) return; //on a pas utilisé la grille

	// Entreprise
	i=0; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpLT->Dette[j]=fN_Xp1->Valeur[j];

	i=1; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpLT->Remb[j]=fN_Xp1->Valeur[j+1];

	i=2; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpLT->Interet[j]=fN_Xp1->Valeur[j+1];

	i=3; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpLT->Capital[j]=fN_Xp1->Valeur[j+1];

	//Prive
	i=0; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpCT->Dette[j]=fN_Xp1->Valeur[j];

	i=1; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpCT->Remb[j]=fN_Xp1->Valeur[j+1];

	i=2; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpCT->Interet[j]=fN_Xp1->Valeur[j+1];

	i=3; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totEmpCT->Capital[j]=fN_Xp1->Valeur[j+1];

	VoirSiVide(totEmpLT);
	VoirSiVide(totEmpCT);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VoirSiVide(CL_TotEmp *totEmp)
{
	int j;
	for(j=0;j<N_X;j++)
	{
		if(totEmp->Dette[j]>0) {totEmp->EstVide=false;return;}
	}
	for(j=0;j<N_X;j++)
	{
		if(totEmp->Remb[j]>0) {totEmp->EstVide=false;return;}
	}
	for(j=0;j<N_X;j++)
	{
		if(totEmp->Interet[j]>0) {totEmp->EstVide=false;return;}
	}
	for(j=0;j<N_X;j++)
	{
		if(totEmp->Capital[j]>0) {totEmp->EstVide=false;return;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotaliserEmp (void)
{
	CL_AgriRes *resultat;
	CL_TotEmp *totGene,*totEmp;

	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totGene=resultat->EmpTotal;
	totGene->Maz(); //met EstVide à true

	totEmp=resultat->EmpLTE;
	if(totEmp->EstVide==false)
	totGene->Ajoute(totEmp->Capital,totEmp->Remb,totEmp->Interet,totEmp->Dette);

	totEmp=resultat->EmpCTE;
	if(totEmp->EstVide==false)
	totGene->Ajoute(totEmp->Capital,totEmp->Remb,totEmp->Interet,totEmp->Dette);

	totEmp=resultat->EmpSomLT;
	if(totEmp->EstVide==false)
	totGene->Ajoute(totEmp->Capital,totEmp->Remb,totEmp->Interet,totEmp->Dette);

	totEmp=resultat->EmpSomCT;
	if(totEmp->EstVide==false)
	totGene->Ajoute(totEmp->Capital,totEmp->Remb,totEmp->Interet,totEmp->Dette);

	for(int i=0;i<N_X;i++)
	totGene->Interet[i]+=resultat->FraisOccc[i];

	totGene->EstVide=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalImmo (void)
{
	int i,j;
	CL_AgriRes *resultat;
	CL_Immo *immo;
	CL_TotImmo *totImmo;
	float amor[N_X],vResid[N_X+1];
	float delta;
	int exAchat,exVente;
	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totImmo=resultat->Immo;
	totImmo->Maz();

	for(i=0;i<Agri->V_Immo->Nbelt;i++)
	{
		totImmo->EstVide=false;
		immo=Agri->V_Immo->Vecteur[i];
		immo->Calcul (amor,vResid,exAchat,exVente);
		if(exVente>=0 && exVente<N_X)
		{
			totImmo->Achat[exAchat] +=immo->ValAchat;
			totImmo->TvaVersee[exAchat]+=immo->ValAchat*(immo->Tva->Taux/100.);
		}
		if(exVente>=0 && exVente<N_X)
		{
			totImmo->Vente[exVente] +=immo->ValVente;
			totImmo->TvaRecue[exVente]+=immo->ValVente*(immo->Tva->Taux/100.);
			delta=immo->ValVente-immo->ValComptable;
			if(delta >0)
			totImmo->PlusVal[exVente] +=delta;
			else if(delta <0)
			totImmo->MoinsVal[exVente] +=delta;
		}
		for(j=0;j<N_X;j++) totImmo->Amor[j] +=amor[j];
		for(j=0;j<N_X+1;j++) totImmo->Resid[j] +=vResid[j];
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalImmoPetit (void)
{
	int i,n;
	CL_AgriRes *resultat;
	CL_Petit *petit;
	CL_TotImmo *totImmo;
	float amor[N_X],vResid[N_X+1];
	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totImmo=resultat->ImmoPetit;
	totImmo->Maz();
	if(Agri->V_Petit->Nbelt>0)
	totImmo->EstVide=false;

	for(i=0;i<Agri->V_Petit->Nbelt;i++)
	{
		petit=Agri->V_Petit->Vecteur[i];
		n=petit->Ex-1; // c'est affiché en commençant à 1
		totImmo->Achat[n] +=petit->ValAchat;
		totImmo->TvaVersee[n]+=petit->ValAchat*(petit->Tva->Taux/100.);
		totImmo->Amor[n] +=petit->ValAchat;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalImmoSom(void)
{
	int i,j;
	CL_AgriRes *resultat;
	CL_FN_Xp1 *fN_Xp1;
	CL_TotImmo *totImmo;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_InvSom;
// tva à calculer
	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totImmo=resultat->ImmoSom;
	totImmo->Maz();

	if(vecteur->Nbelt==0) return;//on a pas utilisé la grille

	totImmo->EstVide=false;

	i=0; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X+1;j++)totImmo->Resid[j]=fN_Xp1->Valeur[j];

	i=1; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totImmo->Amor[j]=fN_Xp1->Valeur[j+1];

	i=2; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totImmo->Achat[j]=fN_Xp1->Valeur[j+1];

	i=3; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totImmo->Vente[j]=fN_Xp1->Valeur[j+1];

	i=4; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totImmo->PlusVal[j]=fN_Xp1->Valeur[j];

	i=5; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totImmo->MoinsVal[j]=fN_Xp1->Valeur[j];

	i=6; fN_Xp1=vecteur->Vecteur[i];
	for(j=0;j<N_X;j++)totImmo->ProdImmo[j]=fN_Xp1->Valeur[j+1];

	for(j=0;j<N_X;j++)totImmo->TvaVersee[j]=totImmo->Achat[j];
	for(j=0;j<N_X;j++)totImmo->TvaRecue [j]=totImmo->Vente[j];

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotaliserImmo (void)
{
	CL_AgriRes *resultat;
	CL_TotImmo *totGene,*totImmo;
	int i;
	if(Agri->Resultat==NULL) Agri->Resultat= new CL_AgriRes;
	resultat=Agri->Resultat;

	totGene=resultat->ImmoTotal;
	totGene->Maz(); //met EstVide à true

	for(i=0;i<N_X;i++)
	{
		totGene->Vente[i]+=resultat->Immo->Vente[i];
		totGene->Vente[i]+=resultat->ImmoSom->Vente[i];

		totGene->Achat[i]+=resultat->Immo->Achat[i];
		totGene->Achat[i]+=resultat->ImmoSom->Achat[i];
		totGene->Achat[i]+=resultat->ImmoPetit->Achat[i];

		totGene->Amor[i]+=resultat->Immo->Amor[i];
		totGene->Amor[i]+=resultat->ImmoSom->Amor[i];
		totGene->Amor[i]+=resultat->ImmoPetit->Amor[i];

		totGene->PlusVal[i]+=resultat->Immo->PlusVal[i];
		totGene->PlusVal[i]+=resultat->ImmoSom->PlusVal[i];

		totGene->MoinsVal[i]+=resultat->Immo->MoinsVal[i];
		totGene->MoinsVal[i]+=resultat->ImmoSom->MoinsVal[i];

		totGene->TvaVersee[i]+=resultat->Immo->TvaVersee[i];
		totGene->TvaVersee[i]+=resultat->ImmoSom->TvaVersee[i];
		totGene->TvaVersee[i]+=resultat->ImmoPetit->TvaVersee[i];

		totGene->TvaRecue[i]+=resultat->Immo->TvaRecue[i];
		totGene->TvaRecue[i]+=resultat->ImmoSom->TvaRecue[i];
		totGene->TvaRecue[i]+=resultat->ImmoPetit->TvaRecue[i];
	}
	for(i=0;i<N_X+1;i++)
	{
		totGene->Resid[i]+=resultat->Immo->Resid[i];
		totGene->Resid[i]+=resultat->ImmoSom->Resid[i];
		totGene->Resid[i]+=resultat->ImmoPetit->Resid[i];
	}
	/*
	 totGene->Ajoute(totImmo->Capital,totImmo->Remb,totImmo->Interet,totImmo->Dette);

	 totImmo=resultat->EmpCTE;
	 if(totImmo->EstVide==false)
	 totGene->Ajoute(totImmo->Capital,totImmo->Remb,totImmo->Interet,totImmo->Dette);

	 totImmo=resultat->EmpSomLT;
	 if(totImmo->EstVide==false)
	 totGene->Ajoute(totImmo->Capital,totImmo->Remb,totImmo->Interet,totImmo->Dette);

	 totImmo=resultat->EmpSomCT;
	 if(totImmo->EstVide==false)
	 totGene->Ajoute(totImmo->Capital,totImmo->Remb,totImmo->Interet,totImmo->Dette);

	 for(int i=0;i<N_X;i++)
	 totGene->Interet[i]+=resultat->FraisOccc[i];
	 */
	totGene->EstVide=false;
}

