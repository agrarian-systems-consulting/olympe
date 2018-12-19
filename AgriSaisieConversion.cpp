//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>

#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Atelier.h"
#include "Impression.h"
#include "Tableur.h"
#include "Resultat.h"
#include "AgriSaisieEnum.h"
#include "Erreur.h"
//#include "TVChoixElt.h"
#include "Compilateur.h"

#include "AgriSaisie.h"
//#include "AgriSaisieConversion.h"

#pragma hdrstop
extern CL_ES *ES;
extern CL_Imp *Imp;
extern CL_Compil *Compil;

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::Convertir(CL_AgriRes *resultat, float *taux)
{

	ConvertirQuanVal(taux, resultat->V_Produit);
	ConvertirQuanVal(taux, resultat->V_Charge);
	ConvertirQuanVal(taux, resultat->V_Externalite);
	ConvertirQuanVal(taux, resultat->V_ExtNeg);
	ConvertirQuanVal(taux, resultat->V_ExtPos);

	ConvertirQuanVal(taux, resultat->V_ChStruct);
	ConvertirQuanVal(taux, resultat->V_RecDiv);
	ConvertirQuanVal(taux, resultat->V_DepDiv);
	ConvertirQuanVal(taux, resultat->V_RecFam);
	ConvertirQuanVal(taux, resultat->V_DepFam);

	ConvertirQuanVal2(taux, resultat->V_CatProduitTot);
	ConvertirQuanVal2(taux, resultat->V_CatChargeTot);
//    ConvertirQuanVal2(taux, resultat->V_CatExtNegTot);
//    ConvertirQuanVal2(taux, resultat->V_CatExtPosTot);

	ConvertirQuanVal2(taux, resultat->V_CatChStructTot);
	ConvertirQuanVal2(taux, resultat->V_CatRecDivTot);
	ConvertirQuanVal2(taux, resultat->V_CatDepDivTot);

	ConvertirQuanVal2(taux, resultat->V_CatRecFamTot);
	ConvertirQuanVal2(taux, resultat->V_CatDepFamTot);

	ConvertirValeur(taux,resultat->Produit);
	ConvertirValeur(taux,resultat->InvAniRepro,N_X+1);//260903
	ConvertirValeur(taux,resultat->InvAniAutre,N_X+1);//260903
	ConvertirValeur(taux,resultat->Charge);

	ConvertirValeur(taux,resultat->RecDiv);
	ConvertirValeur(taux,resultat->DepDiv);

	ConvertirValeur(taux,resultat->ChStruct);

	ConvertirValeur(taux,resultat->RecFam);
	ConvertirValeur(taux,resultat->DepFam);

	ConvertirTotEmp(taux,resultat->EmpLTE);
	ConvertirTotEmp(taux,resultat->EmpCTE);
	ConvertirTotEmp(taux,resultat->EmpLTP);
	ConvertirTotEmp(taux,resultat->EmpCTP);

	ConvertirTotEmp(taux,resultat->EmpSomLT);
	ConvertirTotEmp(taux,resultat->EmpSomCT);
	ConvertirTotEmp(taux,resultat->EmpTotal);

	ConvertirTotEmp(taux,resultat->PlactE);
	ConvertirTotEmp(taux,resultat->PlactP);

	ConvertirTotImmo(taux,resultat->Immo);
	ConvertirTotImmo(taux,resultat->ImmoPetit);
	ConvertirTotImmo(taux,resultat->ImmoSom);
	ConvertirTotImmo(taux,resultat->ImmoTotal);

	ConvertirValeur(taux,resultat->FraisOccc);
	/*
	 ConvertirValeur(taux,resultat->Marge);
	 ConvertirValeur(taux,resultat->AutreDepense);
	 ConvertirValeur(taux,resultat->AutreRecette);
	 ConvertirValeur(taux,resultat->Solde);
	 ConvertirValeur(taux,resultat->SoldeCumul);
	 */
	ConvertirTva (taux,resultat->Tva);
	resultat->TresoIni*=taux[0];
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirQuanVal(float *taux,CL_Vecteur<CL_QuanVal> *vecteur)
{
	int i,n;
	CL_QuanVal *quanVal;
	CL_Item *item;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		quanVal=vecteur->Vecteur[i];
		item=quanVal->Item;
		if (item->SysUnite==SysMonnaie)
		{
			for(n=0;n<N_X;n++)
			quanVal->Qte[n]*=taux[n];
		}
		for(n=0;n<N_X;n++)
		{
			quanVal->Val[n]*=taux[n];
			quanVal->Stock[n]*=taux[n]; //300603
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirQuanVal2(float *taux,CL_Vecteur<CL_QuanVal> *vecteur)
{
	int i,n;
	CL_QuanVal *quanVal;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		quanVal=vecteur->Vecteur[i];
		if(quanVal==NULL) continue;
		for(n=0;n<N_X;n++)
		quanVal->Val[n]*=taux[n];

	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirValeur(float *taux,float *valeur,int n_x)
{
	int n;
	for(n=0;n<n_x;n++) valeur[n]*=taux[n];
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirTotEmp(float *taux,CL_TotEmp *totEmp)
{
	ConvertirValeur(taux,totEmp->Capital);
	ConvertirValeur(taux,totEmp->Remb);
	ConvertirValeur(taux,totEmp->Interet);
	ConvertirValeur(taux,totEmp->Dette,N_X+1);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirTotImmo(float *taux,CL_TotImmo *totImmo)
{
	ConvertirValeur(taux,totImmo->Achat);
	ConvertirValeur(taux,totImmo->Vente);
	ConvertirValeur(taux,totImmo->Amor);
	ConvertirValeur(taux,totImmo->Resid,N_X+1);
	ConvertirValeur(taux,totImmo->TvaVersee);
	ConvertirValeur(taux,totImmo->TvaRecue);
	ConvertirValeur(taux,totImmo->ValCompta);
//    ConvertirValeur(taux,totImmo->PlusVal);
//    ConvertirValeur(taux,totImmo->MoinsVal);
	ConvertirValeur(taux,totImmo->ProdImmo);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirTotEnCours(float *taux,CL_TotEnCours *totEnCours)
{
	ConvertirValeur(taux,totEnCours->Flux);
	ConvertirValeur(taux,totEnCours->Stock,N_X+1);
	ConvertirValeur(taux,totEnCours->CrDette,N_X+1);
	ConvertirValeur(taux,totEnCours->Tva);

}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ChangeUniteMonnaie(CL_SystemeUnite *deMonnaie,CL_SystemeUnite *enMonnaie)
{
	ChangeUniteMonnaie2(deMonnaie,enMonnaie,V_Produit);
	ChangeUniteMonnaie2(deMonnaie,enMonnaie,V_Charge);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ChangeUniteMonnaie2(CL_SystemeUnite *deMonnaie,CL_SystemeUnite *enMonnaie,
		CL_Vecteur<CL_Item> *vecteur)
{
	int i;
	CL_Item *item;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		item=vecteur->Vecteur[i];
		if (item->SysUnite==deMonnaie)
		item->SysUnite=enMonnaie;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ConvertirTva(float *taux,CL_TvaEnt *tva)
{
	ConvertirValeur(taux,tva->Recu);
	ConvertirValeur(taux,tva->Verse);
	ConvertirValeur(taux,tva->AcompteAout);
	ConvertirValeur(taux,tva->AcompteNov);
	ConvertirValeur(taux,tva->AcompteFev);
	ConvertirValeur(taux,tva->AcompteMai);
	ConvertirValeur(taux,tva->RembTva);
	ConvertirValeur(taux,tva->Regul);
	ConvertirValeur(taux,tva->Solde);
}

