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
#include "GereEnsemble.h"

#include "AgriSaisie.h"
#pragma hdrstop
extern CL_ES *ES;
extern CL_Imp *Imp;
// calcul du résultat d'un ensemble d'agriculteurs
//       calcul un par un et sommation dans agriTotal
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculEnsemble(CL_Ensemble *ensemble)
{
	int i;
	int an;
	CL_Agriculteur *agriTotal,*agri;
	CL_AgriEff *agriEff;
	CL_AgriRes *resultat;
//CL_Indicateur  *indic;
	float ponderation[N_X];
	int nbAgri;
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;

	Global=ENSEMBLE;

	if(ensemble->Total)delete ensemble->Total;
	ensemble->Total= new CL_Agriculteur();
	agriTotal=ensemble->Total;
	agriTotal->Nom=ensemble->Nom;
	agriTotal->NoVariante=ensemble->NoVariante;
	agriTotal->Resultat=new CL_AgriRes();
	Agri=agriTotal;
	AgriEnCours=Agri;//181205
	//pour ne pas générer un grand nombre CL_AgriRes
	// en génerer un seul et le vider à chaque agriculteur
	resultat=new CL_AgriRes();

	//agri->agriTotal
	//       commence comme le premier
	//       vérifier que tous commencent la meme année  à faire
	agriEff=ensemble->V_AgriEff->Vecteur[0];
	agri=agriEff->Agri;
	agriTotal->DefSim->An_0= agri->DefSim->An_0;
	agriTotal->TresoIni=0;

	//combien de calculs à faire
	// pour déterminer parametres de ProgressBar dans GereEnsemble
	nbAgri=ensemble->V_AgriEff->Nbelt;
	GereEnsembleFrm->ProgressBar->Position=0;
	GereEnsembleFrm->ProgressBar->Max=nbAgri;

	// on fait les calculs pour une série d'agriculteurs
	// les éléments ne peuvent pas changer dans la boucle suivante
	// donc une seule fois IniV_Elt
	ES->IniV_Elt();

	for(i=0;i<ensemble->V_AgriEff->Nbelt;i++)
	{
		agriEff=ensemble->V_AgriEff->Vecteur[i];
		agri=agriEff->Agri;

		// sans doute inutile
		if(agri==NULL) continue;

		// pas la peine de se fatiguer si aucun effectif
		if(ilYaEffectif(agriEff)==false) continue;

		// mettre à zero le resultat de agriculteur
		resultat->Maz();
		agri->Resultat=resultat;

		//trouveTend(agri); c'est fait dans AgriSaisieCalcul
		Calcul0(agri);//050901
		//FaireCompta(agri->Resultat); c'est fait maintenant dans Calcul0
		//totaliser
		EnsembleTotalise(agri->Resultat,agriTotal->Resultat,agriEff->Effectif);
		EnsembleSurface(agri,agriTotal,agriEff->Effectif);
		//appel à fonction de agrégation
		for(int i=0;i<N_X;i++)ponderation[i]=agriEff->Effectif[i];
		AgregeInvAni(ponderation,agri->LstTroupeaux,agriTotal->LstTroupeaux);

		agriTotal->TresoIni+=agri->TresoIni*agriEff->Effectif[0]*ratioP;

		GereEnsembleFrm->ProgressBar->StepBy(1);
		agri->Resultat=NULL;

	}
	delete resultat;
	for(int an=0;an<N_X;an++)
	CalculTreso(agriTotal,an);
	FaireCompta(agriTotal->Resultat,an);

	//pour repérer les catégories à imprimer si sortie
	MazOFlagCat(agriTotal);//040901

	// pour accéder par TreeView à tous les éléments de l'ensemble
//    Forme0Frm->Agri=agriTotal;  090202
	//a faire dans Resultat
	//Forme0Frm->CreeTVToutElt(TVChoixEltFrm->TV,agriTotal,false);

	// d'abord les indicateurs: ils peuvent etre dans les etats

	Forme0Frm->CompleteV_Elt(agriTotal);
	//dans les Calcul0 Agri= a successivement pris différentes valeurs
	Agri=agriTotal;//210202

	for(an=0;an<N_X;an++)
	{
		V_Indicateur->FlagMisA(false);
		CalculIndicateur(an);
	}
	CompleteEtatSortie();

}

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MazOFlagCat(CL_Agriculteur* agriTotal)
{
	CL_AgriRes *resultat=agriTotal->Resultat;

	MazNFlagCat(); //pour repérer les catégories à imprimer si sortie
	MazOFlagCat1(resultat->V_Produit);
	MazOFlagCat1(resultat->V_Charge);
	MazOFlagCat1(resultat->V_ChStruct);
	MazOFlagCat1(resultat->V_RecDiv);
	MazOFlagCat1(resultat->V_DepDiv);
	MazOFlagCat1(resultat->V_RecFam);
	MazOFlagCat1(resultat->V_DepFam);

	MazOFlagCat1(resultat->V_ExtNeg);
	MazOFlagCat1(resultat->V_ExtPos);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MazOFlagCat1(CL_Vecteur<CL_QuanVal> *vecteur)
{
	int i;
	CL_QuanVal *quanVal;
	CL_Item *item;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		quanVal=vecteur->Vecteur[i];
		item=quanVal->Item;
		item->Categorie->Flag='O';
	}
}
//040901
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ilYaEffectif(CL_AgriEff *agriEff)
{
	int n;
	for(n=0;n<N_X;n++)
	{
		if(agriEff->Effectif[n]!=0) return true;
	}
	return false;
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsembleTotalise(CL_AgriRes* resAgri,
		CL_AgriRes* resTotal,int *effectif)
{
	EnsTotQuanVal(resAgri->V_Produit, resTotal->V_Produit, effectif);
	EnsTotQuanVal(resAgri->V_Charge, resTotal->V_Charge, effectif);
	EnsTotQuanVal(resAgri->V_ExtNeg, resTotal->V_ExtNeg, effectif);
	EnsTotQuanVal(resAgri->V_ExtPos, resTotal->V_ExtPos, effectif);
	EnsTotQuanVal(resAgri->V_ChStruct,resTotal->V_ChStruct,effectif);

	EnsTotQuanVal(resAgri->V_RecDiv, resTotal->V_RecDiv, effectif);
	EnsTotQuanVal(resAgri->V_DepDiv, resTotal->V_DepDiv, effectif);
	EnsTotQuanVal(resAgri->V_RecFam, resTotal->V_RecFam, effectif);
	EnsTotQuanVal(resAgri->V_DepFam, resTotal->V_DepFam, effectif);

	EnsTotQuanVal2(resAgri->V_CatProduitTot, resTotal->V_CatProduitTot, effectif);
	EnsTotQuanVal2(resAgri->V_CatChargeTot, resTotal->V_CatChargeTot, effectif);
// a corriger
//    EnsTotQuanVal2(resAgri->V_CatExtNegTot,  resTotal->V_CatExtNegTot,  effectif);
//    EnsTotQuanVal2(resAgri->V_CatExtPosTot,  resTotal->V_CatExtPosTot,  effectif);

	EnsTotQuanVal2(resAgri->V_CatChStructTot,resTotal->V_CatChStructTot,effectif);
	EnsTotQuanVal2(resAgri->V_CatRecDivTot, resTotal->V_CatRecDivTot, effectif);
	EnsTotQuanVal2(resAgri->V_CatDepDivTot, resTotal->V_CatDepDivTot, effectif);
	EnsTotQuanVal2(resAgri->V_CatRecFamTot, resTotal->V_CatRecFamTot, effectif);
	EnsTotQuanVal2(resAgri->V_CatDepFamTot, resTotal->V_CatDepFamTot, effectif);

	EnsTotEmp (resAgri->EmpLTE, resTotal->EmpLTE, effectif);
	EnsTotEmp (resAgri->EmpCTE, resTotal->EmpCTE, effectif);
	EnsTotEmp (resAgri->EmpLTP, resTotal->EmpLTP, effectif);
	EnsTotEmp (resAgri->EmpCTP, resTotal->EmpCTP, effectif);
	EnsTotEmp (resAgri->EmpTotal, resTotal->EmpTotal, effectif);

	EnsTotEmp (resAgri->PlactE, resTotal->PlactE, effectif);
	EnsTotEmp (resAgri->PlactP, resTotal->PlactP, effectif);

	EnsTotImmo (resAgri->Immo, resTotal->Immo, effectif);
	EnsTotImmo (resAgri->ImmoPetit,resTotal->ImmoPetit, effectif);
	EnsTotImmo (resAgri->ImmoSom, resTotal->ImmoSom, effectif);
	EnsTotImmo (resAgri->ImmoTotal,resTotal->ImmoTotal, effectif);

	EnsTotSub (resAgri->TotSub, resTotal->TotSub, effectif);

	EnsTotEnCours(resAgri->Creance, resTotal->Creance, effectif);
	EnsTotEnCours(resAgri->Dette, resTotal->Dette, effectif);

	EnsTotFloat (resAgri->FraisOccc, resTotal->FraisOccc, effectif);

	EnsTotFloat (resAgri->Produit, resTotal->Produit, effectif);
	EnsTotFloat (resAgri->VenteAni, resTotal->VenteAni, effectif);
	EnsTotFloat (resAgri->AchatAni, resTotal->AchatAni, effectif);
	//attention bilan N_X+1
	EnsTotFloat (resAgri->InvAniRepro, resTotal->InvAniRepro, effectif,N_X+1);
	EnsTotFloat (resAgri->InvAniAutre, resTotal->InvAniAutre ,effectif,N_X+1);
	// calcul fait dans FaireCompta
//    EnsTotFloat  (resAgri->Stock,          resTotal->Stock,       effectif,N_X+1);
	EnsTotFloat (resAgri->Avance, resTotal->Avance, effectif,N_X+1);

	EnsTotFloat (resAgri->Charge, resTotal->Charge, effectif);
	EnsTotFloat (resAgri->ChStruct, resTotal->ChStruct, effectif);
	EnsTotFloat (resAgri->DepDiv, resTotal->DepDiv, effectif);
	EnsTotFloat (resAgri->RecDiv, resTotal->RecDiv, effectif);
	EnsTotFloat (resAgri->DepFam, resTotal->DepFam, effectif);
	EnsTotFloat (resAgri->RecFam, resTotal->RecFam, effectif);

	EnsTotTva (resAgri->Tva, resTotal->Tva, effectif);

	EnsTotCeg (resAgri, resTotal, effectif);

	EnsTotBilan (resAgri, resTotal, effectif);

	//SoldeCumul treso initiale  et solde cumulé
//    EnsTotSoldeCumul(resAgri,              resTotal,      effectif);

//    FaireCompta(resTotal);   ->TresoIni

}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotCeg(CL_AgriRes* resAgri,
		CL_AgriRes* resTotal,int *effectif)
{

	EnsTotFloat(resAgri->totProduit, resTotal->totProduit,effectif);
//1    EnsTotFloat(resAgri->Produit,         resTotal->Produit,effectif);

//2    EnsTotFloat(resAgri->RecDiv,          resTotal->RecDiv,effectif);
	EnsTotFloat(resAgri->deltaStock, resTotal->deltaStock,effectif);
	EnsTotFloat(resAgri->deltaAvance, resTotal->deltaAvance,effectif);

//    Resultat(".  Variation valeur plantation",   resultat->deltaValPlant,clNavy);

	EnsTotFloat(resAgri->deltaVarInvAniRepro, resTotal->deltaVarInvAniRepro,effectif);
	EnsTotFloat(resAgri->deltaVarInvAniAutre, resTotal->deltaVarInvAniAutre,effectif);

//    EnsTotFloat(resAgri->PlactE->Interet, resTotal->PlactE->Interet,effectif);
	EnsTotFloat(resAgri->ProdImmo, resTotal->ProdImmo,effectif);
//    EnsTotFloat(resAgri->ImmoTotal->Vente,resTotal->ImmoTotal->Vente,effectif);
	EnsTotFloat(resAgri->PertePlant, resTotal->PertePlant,effectif);
//    EnsTotFloat(resAgri->TotSub->Amor,    resTotal->TotSub->Amor,effectif);

	EnsTotFloat(resAgri->totDepense, resTotal->totDepense,effectif);

//    EnsTotFloat(resAgri->Charge,          resTotal->Charge,effectif);
//    EnsTotFloat(resAgri->DepDiv,          resTotal->DepDiv,effectif);
	EnsTotFloat(resAgri->ImmoTotal->ValCompta, resTotal->ImmoTotal->ValCompta,effectif);

	EnsTotFloat(resAgri->totChStruct, resTotal->totChStruct,effectif);
//    EnsTotFloat(resAgri->ImmoTotal->Amor, resTotal->ImmoTotal->Amor,effectif);
	EnsTotFloat(resAgri->AmorPlant, resTotal->AmorPlant,effectif);
//    EnsTotFloat(resAgri->EmpLTE->Interet, resTotal->EmpLTE->Interet,effectif);
//    EnsTotFloat(resAgri->EmpCTE->Interet, resTotal->EmpCTE->Interet,effectif);
//    EnsTotFloat(resAgri->FraisOccc,       resTotal->FraisOccc,effectif);
//    EnsTotFloat(resAgri->ChStruct,        resTotal->ChStruct,effectif);
	EnsTotFloat(resAgri->resExercice, resTotal->resExercice,effectif);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotBilan(CL_AgriRes* resAgri,
		CL_AgriRes* resTotal,int *effectif)
{
	EnsTotFloat(resAgri->totImmo, resTotal->totImmo,effectif);
//    EnsTotFloat(resAgri->ImmoTotal->Resid,resTotal->ImmoTotal->Resid,effectif);
//    EnsTotFloat(resAgri->InvAniRepro,     resTotal->InvAniRepro,effectif); //260903
	EnsTotFloat(resAgri->ValPlant, resTotal->ValPlant,effectif);

	EnsTotFloat(resAgri->Stock, resTotal->Stock,effectif);
//    EnsTotFloat(resAgri->Avance,          resTotal->Avance,effectif);
//    EnsTotFloat(resAgri->InvAniAutre,     resTotal->InvAniAutre,effectif); //260903
	//creance
//    EnsTotFloat(resAgri->PlactE->Dette,   resTotal->PlactE->Dette,effectif);
	EnsTotFloat(resAgri->creanceTva, resTotal->creanceTva,effectif);
//    EnsTotFloat(resAgri->Creance->CrDette,resTotal->Creance->CrDette,effectif);
	EnsTotFloat(resAgri->tresorerie, resTotal->tresorerie,effectif);
	EnsTotFloat(resAgri->perte, resTotal->perte,effectif);
	EnsTotFloat(resAgri->totActif, resTotal->totActif,effectif);

//	PASSIF);
	EnsTotFloat(resAgri->capital, resTotal->capital,effectif);
	EnsTotFloat(resAgri->soldePrive, resTotal->soldePrive,effectif);

//    EnsTotFloat(resAgri->TotSub->Resid,     resTotal->TotSub->Resid,effectif);
//    EnsTotFloat(resAgri->EmpLTE->Dette,     resTotal->EmpLTE->Dette,effectif);
//    EnsTotFloat(resAgri->EmpCTE->Dette,     resTotal->EmpCTE->Dette,effectif);
	EnsTotFloat(resAgri->detteTva, resTotal->detteTva,effectif);
//    EnsTotFloat(resAgri->Dette->CrDette,    resTotal->Dette->CrDette,effectif);
	EnsTotFloat(resAgri->benefice, resTotal->benefice,effectif);
	EnsTotFloat(resAgri->totPassif, resTotal->totPassif,effectif);

}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotQuanVal(CL_Vecteur<CL_QuanVal> *vecteurA,
		CL_Vecteur<CL_QuanVal> *vecteurT,int *effectif)
{
	int i,n;
	CL_Item *item;
	CL_QuanVal *quanValA,*quanValT;
	CL_SystemeUnite *sysUnite;
	float ratioP=SysMonnaie->RatioG;
	float ratioQ;
	for(i=0;i<vecteurA->Nbelt;i++)
	{
		quanValA=vecteurA->Vecteur[i];
		item=quanValA->Item;
		sysUnite =item->SysUnite;
		if(sysUnite==NULL)
		sysUnite=SysMonnaie;
		ratioQ=sysUnite->RatioG;
		quanValT=vecteurT->trouve(item->No);
		if(quanValT==NULL)
		{
			quanValT=new CL_QuanVal(); //210202
			quanValT->Item=item;
			quanValT->No= item->No;
			vecteurT->insSans(quanValT);
		}
		for(n=0;n<N_X;n++)
		{
			quanValT->Qte[n]+=quanValA->Qte[n]*effectif[n]/ratioQ;
			quanValT->Val[n]+=quanValA->Val[n]*effectif[n]/ratioP;
			quanValT->Stock[n]+=quanValA->Stock[n]*effectif[n]/ratioP;
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotQuanVal2(CL_Vecteur<CL_QuanVal> *vecteurA,
		CL_Vecteur<CL_QuanVal> *vecteurT,int *effectif)
{
	int i,n;
	CL_QuanVal *quanValA,*quanValT;
	CL_Categorie *categorie;
	float ratioP=SysMonnaie->RatioG;
	for(i=0;i<vecteurA->Nbelt;i++)
	{
		quanValA=vecteurA->Vecteur[i];
		categorie=quanValA->Categorie;
		quanValT=vecteurT->trouve(categorie->No);
		if(quanValT==NULL)
		{
			quanValT=new CL_QuanVal(); //210202
			quanValT->Categorie= categorie;
			quanValT->No= categorie->No;
			vecteurT->insSans(quanValT);
		}
		for(n=0;n<N_X;n++)
		{
			quanValT->Val[n]+=quanValA->Val[n]*effectif[n]/ratioP;
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotEmp(CL_TotEmp *totEmpA,CL_TotEmp *totEmpT,int *effectif)
{
	int n;
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	if(totEmpA->EstVide==true) return;

	totEmpT->EstVide=false;
	for(n=0;n<N_X;n++)
	{
		totEmpT->Capital[n] +=totEmpA->Capital[n] *effectif[n]*ratioP;
		totEmpT->Remb[n] +=totEmpA->Remb[n] *effectif[n]*ratioP;
		totEmpT->Interet[n] +=totEmpA->Interet[n] *effectif[n]*ratioP;
		totEmpT->Dette[n] +=totEmpA->Dette[n] *effectif[n]*ratioP;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotImmo(CL_TotImmo *totImmoA,
		CL_TotImmo *totImmoT,int *effectif)
{
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	int n;
	if(totImmoA->EstVide==true) return;

	totImmoT->EstVide=false;
	for(n=0;n<N_X;n++)
	{
		totImmoT->Achat [n]+=totImmoA->Achat [n]*effectif[n]*ratioP;
		totImmoT->Vente [n]+=totImmoA->Vente [n]*effectif[n]*ratioP;
		totImmoT->Amor [n]+=totImmoA->Amor [n]*effectif[n]*ratioP;
		totImmoT->TvaVersee [n]+=totImmoA->TvaVersee [n]*effectif[n]*ratioP;
		totImmoT->TvaRecue [n]+=totImmoA->TvaRecue [n]*effectif[n]*ratioP;
//        totImmoT->PlusVal   [n]+=totImmoA->PlusVal   [n]*effectif[n]*ratioP;
//        totImmoT->MoinsVal  [n]+=totImmoA->MoinsVal  [n]*effectif[n]*ratioP;
		totImmoT->ProdImmo [n]+=totImmoA->ProdImmo [n]*effectif[n]*ratioP;
	}
	for(n=0;n<N_X+1;n++)
	totImmoT->Resid [n]+=totImmoA->Resid [n]*effectif[n]*ratioP;
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotSub(CL_TotSub* totSubA,
		CL_TotSub* totSubT,int *effectif)
{
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	int n;

	for(n=0;n<N_X;n++)
	{
		totSubT->Valeur [n]+=totSubA->Valeur [n]*effectif[n]*ratioP;
		totSubT->Amor [n]+=totSubA->Amor [n]*effectif[n]*ratioP;
	}
	for(n=0;n<N_X+1;n++)
	totSubT->Resid [n]+=totSubA->Resid [n]*effectif[n]*ratioP;
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotEnCours(CL_TotEnCours *totECA,
		CL_TotEnCours *totECT,int *effectif)
{
	int n;
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	for(n=0;n<N_X;n++)
	{
		totECT->Flux [n]+=totECA->Flux [n]*effectif[n]*ratioP;
		totECT->Tva [n]+=totECA->Tva [n]*effectif[n]*ratioP;
	}
	for(n=0;n<N_X+1;n++)
	{
		totECT->Stock [n] +=totECA->Stock [n]*effectif[n]*ratioP;
		totECT->CrDette[n] +=totECA->CrDette [n]*effectif[n]*ratioP;
	}
}
// A supprimer
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotSoldeCumul(CL_AgriRes* resAgri,
		CL_AgriRes* resTotal,int *effectif)
{

	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	resTotal->TresoIni=resAgri->TresoIni*effectif[0]*ratioP;
	EnsTotFloat(resAgri->SoldeCumul,resTotal->SoldeCumul,effectif,N_X);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotFloat(float *valA,float *valT,int *effectif,int nMax)
{
	int n;
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	for(n=0;n<N_X;n++) valT[n]+=valA[n]*effectif[n]*ratioP;
	if(nMax==N_X) return;
	valT[nMax-1]=valT[nMax-2];
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsTotTva(CL_TvaEnt *Tva,CL_TvaEnt *TvaTot, int *effectif)
{
	int n;
	float ratioP=SysMonnaie->Ratio/SysMonnaie->RatioG;
	for(n=0;n<N_X;n++)
	{
		TvaTot->Recu[n] +=Tva->Recu[n] *effectif[n]*ratioP;
		TvaTot->Verse[n] +=Tva->Verse[n] *effectif[n]*ratioP;
		TvaTot->AcompteAout[n]+=Tva->AcompteAout[n]*effectif[n]*ratioP;
		TvaTot->AcompteNov[n] +=Tva->AcompteNov[n] *effectif[n]*ratioP;
		TvaTot->AcompteFev[n] +=Tva->AcompteFev[n] *effectif[n]*ratioP;
		TvaTot->AcompteMai[n] +=Tva->AcompteMai[n] *effectif[n]*ratioP;
		TvaTot->RembTva[n] +=Tva->RembTva[n] *effectif[n]*ratioP;
		TvaTot->Regul[n] +=Tva->Regul[n] *effectif[n]*ratioP;
		TvaTot->Solde[n] +=Tva->Solde[n] *effectif[n]*ratioP;
	}
}
//----------------------------------------------------------------------------
// Assolement Perenne Vivrier Animaux(pas mouvement)
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EnsembleSurface(CL_Agriculteur *agri,CL_Agriculteur *agriTot,int *effectif)
{
	CL_Valeur *valeur,*valeurT;
	CL_Verger *verger, *vergerT;
	CL_Verger *vivrier,*vivrierT;
	int i,j;
	bool trouve;
	//Cultures
	for(i=0;i<agri->V_Culture->Nbelt;i++)
	{
		valeur=agri->V_Culture->Vecteur[i];
		if(valeur->Atelier->Nature!=CULTURE) continue;
		trouve=false;
		for(j=0;j<agriTot->V_Culture->Nbelt;j++)
		{
			valeurT=agriTot->V_Culture->Vecteur[j];
			if(valeurT->Atelier==valeur->Atelier)
			{
				trouve=true;
				break;
			}
		}
		if(trouve==false)
		{
			valeurT=new CL_Valeur(valeur);
			memset(valeurT->Valeur,0,sizeof(float)*N_X);
			agriTot->V_Culture->ins(valeurT);
		}

		for(j=0;j<N_X;j++)
		valeurT->Valeur[j]+=valeur->Valeur[j]*effectif[j];
	}
	//Animaux
	for(i=0;i<agri->V_Animaux->Nbelt;i++)
	{
		valeur=agri->V_Animaux->Vecteur[i];
		if(valeur->Atelier->Nature!=ANIMAUX) continue;
		trouve=false;
		for(j=0;j<agriTot->V_Animaux->Nbelt;j++)
		{
			valeurT=agriTot->V_Animaux->Vecteur[j];
			if(valeurT->Atelier==valeur->Atelier)
			{
				trouve=true;
				break;
			}
		}
		if(trouve==false)
		{
			valeurT=new CL_Valeur(valeur);
			memset(valeurT->Valeur,0,sizeof(float)*N_X);
			agriTot->V_Animaux->ins(valeurT);
		}

		for(j=0;j<N_X;j++)
		valeurT->Valeur[j]+=valeur->Valeur[j]*effectif[j];
	}

	//Verger
	for(i=0;i<agri->V_Verger->Nbelt;i++)
	{
		verger=agri->V_Verger->Vecteur[i];
		trouve=false;
		for(j=0;j<agriTot->V_Verger->Nbelt;j++)
		{
			vergerT=agriTot->V_Verger->Vecteur[j];
			if(vergerT->Atelier==verger->Atelier)
			{
				trouve=true;
				break;
			}
		}
		if(trouve==false)
		{
			vergerT=new CL_Verger(verger);
			memset(vergerT->SurfaceAn,0,sizeof(float)*N_X);
			agriTot->V_Verger->ins(vergerT);
		}
		for(j=0;j<N_X;j++)
		{
			vergerT->SurfaceAn[j]+= verger->SurfaceAn[j]*effectif[j];
		}
	}
	//Vivrier
	for(i=0;i<agri->V_Vivrier->Nbelt;i++)
	{
		vivrier=agri->V_Vivrier->Vecteur[i];
		trouve=false;
		for(j=0;j<agriTot->V_Vivrier->Nbelt;j++)
		{
			vivrierT=agriTot->V_Vivrier->Vecteur[j];
			if(vivrierT->Atelier==vivrier->Atelier)
			{
				trouve=true;
				break;
			}
		}
		if(trouve==false)
		{
			vivrierT=new CL_Verger(vivrier);
			memset(vivrierT->SurfaceAn,0,sizeof(float)*N_X);
			agriTot->V_Vivrier->ins(vivrierT);
		}
		for(j=0;j<N_X;j++)
		{
			vivrierT->SurfaceAn[j]+= vivrier->SurfaceAn[j]*effectif[j];
		}
	}
}

