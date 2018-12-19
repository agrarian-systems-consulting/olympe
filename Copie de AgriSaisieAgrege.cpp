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
#include "Compilateur.h"
#include "Assol.h"

#include "AgriSaisie.h"
#pragma hdrstop
extern CL_ES *ES;
extern CL_Imp *Imp;
// calcul du résultat d'un ensemble d'agriculteurs
//       calcul un par un et sommation dans agriTotal
//----------------------------------------------------------------------------
CL_Agriculteur* __fastcall TAgriSaisieFrm::Agrege(CL_Ensemble *ensemble)
{
	int i,n;
	CL_Agriculteur *agriTot,*agriTot0;
	CL_Agriculteur *agri;
	CL_AgriEff *agriEff;
	float ponderation[N_X];
	int effectifTot[N_X];
	int nbAgri;
	bool correct;
	AnsiString nom0;

	ErreurFrm->Edit->Clear();

	agriTot=new CL_Agriculteur();
	// rajouter le n° de variante
	if(AgriSaisieFrm->TypeAgreg==TOTAL)
	agriTot->Nom=AnsiString("TOTAL")+ensemble->Nom;
	else//MOYENNE
	agriTot->Nom=AnsiString("MOY")+ensemble->Nom;

	nom0=agriTot->Nom;

	//rechercher si on a déjà défini cet ensemble agrégé
	agriTot0=V_Agriculteur->trouve(nom0);

	if(agriTot0)
	{
		agriTot->No=agriTot0->No;
		V_Agriculteur->remplace(agriTot0,agriTot);
		delete agriTot0;
	}
	else
	V_Agriculteur->ins(agriTot);

	if(agriTot->Resultat) delete agriTot->Resultat;
	agriTot->Resultat= new CL_AgriRes();
//    MazNFlagCat();//pour repérer les catégories à imprimer si sortie

	agriEff=ensemble->V_AgriEff->Vecteur[0];
	agri=agriEff->Agri;

	//année de début du résultat agrégé= le début du premier agri de l'ensemble a voir !!!!
	agriTot->DefSim->An_0= agri->DefSim->An_0;

	// a replacer
	agriTot->TresoIni=0;
	AssolFrm->Agri=agriTot;//ça sert ??
	// rajouter le n° de variante

	//       commence comme le premier
	//       vérifier que tous commencent la meme année  à faire

	//combien de calculs à faire
	// pour déterminer parametres de ProgressBar dans GereEnsemble
	nbAgri=ensemble->V_AgriEff->Nbelt;
	GereEnsembleFrm->ProgressBar->Position=0;
	GereEnsembleFrm->ProgressBar->Max=nbAgri;

	// on fait les calculs pour une série d'agriculteurs
	// les éléments ne peuvent pas changer dans la boucle suivante
	// donc une seule fois IniV_Elt
	ES->IniV_Elt();
	memset(effectifTot,0,sizeof(int)*N_X);
	for(i=0;i<ensemble->V_AgriEff->Nbelt;i++)
	{
		agriEff=ensemble->V_AgriEff->Vecteur[i];
		// pas la peine de se fatiguer si aucun effectif
		if(ilYaEffectif(agriEff)==false) continue;

		for(n=0;n<N_X;n++) effectifTot[n]+=agriEff->Effectif[n];
	}

	//
	for(i=0;i<ensemble->V_AgriEff->Nbelt;i++)
	{
		agriEff=ensemble->V_AgriEff->Vecteur[i];
		// pas la peine de se fatiguer si aucun effectif
		if(ilYaEffectif(agriEff)==false) continue;
		if(AgriSaisieFrm->TypeAgreg==TOTAL)
		{
			for(n=0;n<N_X;n++) ponderation[n]=(float)agriEff->Effectif[n];
		}
		else //MOYENNE
		{
			for(n=0;n<N_X;n++)
			ponderation[n]=(float)agriEff->Effectif[n]/(float)effectifTot[n];
		}

		//for(n=0;n<N_X;n++)  effectifTot[n]+=agriEff->Effectif[n];

		agri=agriEff->Agri;

		if(agri->Resultat) delete agri->Resultat;
		agri->Resultat= new CL_AgriRes();

		correct=MetDans(agri,agriTot,ponderation);
		GereEnsembleFrm->ProgressBar->StepBy(1);
	}
	if(correct==false)
	{
		ErreurFrm->Show();
		return NULL;
	}
	//les valeurs numériques sont total pondére par les effectifs
//    Moyenne(effectifTot,agriTot);

	if(AgriSaisieFrm->TypeAgreg==TOTAL)
	MoyenneVariable(effectifTot,agriTot);
	ES->ecrireFichier();

	return(agriTot);

}
//----------------------------------------------------------------------------
//bool __fastcall TAgriSaisieFrm::MetDans(CL_Agriculteur *agriTot,CL_AgriEff *agriEff)
bool __fastcall TAgriSaisieFrm::MetDans(CL_Agriculteur *agri,CL_Agriculteur *agriTot,float *ponderation)
{

//CL_Agriculteur *agri;
	bool correct=true;
	bool rep;
//    agri=agriEff->Agri;

	rep=AgregeValeur(ponderation,agri->V_Culture,agriTot->V_Culture);
	if(rep==false) correct=false;

	rep=AgregeValeur(ponderation,agri->V_Animaux,agriTot->V_Animaux);
	if(rep==false) correct=false;

	rep=AgregeVerger(ponderation,agri->V_Verger, agriTot->V_Verger);
	if(rep==false) correct=false;

	rep=AgregeVerger(ponderation,agri->V_Vivrier,agriTot->V_Vivrier);
	if(rep==false) correct=false;

	rep=AgregeInvAni(ponderation,agri->LstTroupeaux,agriTot->LstTroupeaux);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_Produits, agriTot->V_Produits,true);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_Charges, agriTot->V_Charges,true);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_ChStruct, agriTot->V_ChStruct,false);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_RecDiv, agriTot->V_RecDiv,false);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_DepDiv, agriTot->V_DepDiv,false);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_RecFam, agriTot->V_RecFam,false);
	if(rep==false) correct=false;

	rep=AgregeFormule(ponderation,agri->V_DepFam, agriTot->V_DepFam,false);
	if(rep==false) correct=false;

	rep=AgregeEmprunt(ponderation,agri,agriTot);
	if(rep==false) correct=false;

	rep=AgregeImmo(ponderation,agri,agriTot);
	if(rep==false) correct=false;

	rep=AgregeSubvention(ponderation,agri->V_Sub,agriTot->V_Sub);
	if(rep==false) correct=false;

	rep=AgregeVariable(ponderation,agri,agriTot);
	if(rep==false) correct=false;

	rep=AgregeTresoIni(ponderation,agri,agriTot);
	if(rep==false) correct=false;

	return correct;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeValeur(float *ponderation,
		CL_Vecteur<CL_Valeur> *vecteur,
		CL_Vecteur<CL_Valeur> *vecteurTot)
{

	CL_Valeur *valeur,*valeurTot;
	int i,n;

	for(i=0;i<vecteur->Nbelt;i++)
	{
		valeur=vecteur->Vecteur[i];
		valeurTot=trouveValeur(vecteurTot,valeur->Atelier);
		if(valeurTot==NULL)
		{
			valeurTot=new CL_Valeur(valeur);
			memset(valeurTot->Valeur,0,sizeof(float)*N_X);
			vecteurTot->ins(valeurTot);
		}
		for(n=0;n<N_X;n++)
		valeurTot->Valeur[n]+=valeur->Valeur[n]*ponderation[n];
	}
	return true;
}
//----------------------------------------------------------------------------
CL_Valeur* __fastcall TAgriSaisieFrm::trouveValeur( CL_Vecteur<CL_Valeur> *vecteurTot,
		CL_Atelier *atelier)
{
	int i;
	CL_Valeur *valeurTot;
	for(i=0;i<vecteurTot->Nbelt;i++)
	{
		valeurTot=vecteurTot->Vecteur[i];
		if(valeurTot->Atelier==atelier)
		return valeurTot;
	}
	return NULL;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeVerger(float *ponderation,
		CL_Vecteur<CL_Verger> *vecteur,
		CL_Vecteur<CL_Verger> *vecteurTot)

{

	CL_Verger *verger,*vergerTot;
	int i,n;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		verger=vecteur->Vecteur[i];
		AssolFrm->VergerSurface(verger);

		vergerTot=TrouveVerger(verger,vecteurTot);
		if(vergerTot==NULL)
		{
			vergerTot=new CL_Verger(verger);
			vergerTot->Surface=0;
			vecteurTot->ins(vergerTot);
		}
		vergerTot->Surface+=verger->Surface*ponderation[0];
		for(n=0;n<N_X;n++)
		vergerTot->SurfaceAn[n]+=verger->SurfaceAn[n]*ponderation[n];
		//problème les effectifs peuvent changer
	}
	return true;
}
//----------------------------------------------------------------------------
CL_Verger* __fastcall TAgriSaisieFrm::TrouveVerger(CL_Verger *verger,
		CL_Vecteur<CL_Verger> *vecteurTot)
{
	int i;
	CL_Verger *vergerTot;
	for(i=0;i<vecteurTot->Nbelt;i++)
	{
		vergerTot=vecteurTot->Vecteur[i];
		if( vergerTot->AnPlant ==verger->AnPlant
				&& vergerTot->AnArr ==verger->AnArr
				&& vergerTot->NoAtelier ==verger->NoAtelier
				&& vergerTot->NoEspece ==verger->NoEspece )
		return vergerTot;
	}
	return NULL;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeVariable(float *ponderation,
		CL_Agriculteur *agri,
		CL_Agriculteur *agriTot)

{
	CL_Vecteur<CL_Valeur> *vecteur;
	CL_Vecteur<CL_Valeur> *vecteurTot;
//CL_Categorie *categorie;
//CL_Item      *item;
	CL_Valeur *valeur,*valeurTot;
	int i,n;
	vecteur =agri->V_Variable;
	vecteurTot=agriTot->V_Variable;

	for(i=0;i<vecteur->Nbelt;i++)
	{
		valeur=vecteur->Vecteur[i];
		//       item=valeur->Item;
		//       categorie=item->Categorie;
		valeurTot=vecteurTot->trouve(valeur->No);
		if(valeurTot==NULL)
		{
			valeurTot=new CL_Valeur(valeur);
			memset(valeurTot->Valeur,0,sizeof(float)*N_X);
			vecteurTot->ins(valeurTot);
		}
		for(n=0;n<N_X;n++)
		valeurTot->Valeur[n]+=valeur->Valeur[n]*ponderation[n];
	}
	return true;

}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MoyenneVariable(int *effectifTot,
		CL_Agriculteur *agriTot)
{
	CL_Vecteur<CL_Valeur> *vecteurTot;
	CL_Categorie *categorie;
	CL_Item *item;
	CL_Valeur *valeurTot;
	int i,n;

	vecteurTot=agriTot->V_Variable;

	for(i=0;i<vecteurTot->Nbelt;i++)
	{
		valeurTot=vecteurTot->Vecteur[i];
		item=valeurTot->Item;
		categorie=item->Categorie;
		if(categorie->Nom.AnsiCompareIC("Surface")==0) continue;

		for(n=0;n<N_X;n++)
		{
			if(effectifTot[n]==0)
			valeurTot->Valeur[n]=0;
			else
			valeurTot->Valeur[n]/=effectifTot[n];
		}
	}
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeInvAni(float *ponderation,
		TList *lstTroupeaux,
		TList *lstTroupeauxTot)

{
	CL_Troupeau *troupeau,*troupeauTot;
	CL_InvAni *invAni,*invAniTot;
	CL_MvtAni *mvtAni,*mvtAniTot;
	int i,j,n;
	float ratioP=SysMonnaie->RatioG;

	if(Global==AGRI || Global==MOYENNE)ratioP=1;
	else ratioP=SysMonnaie->RatioG;

//	if(Global==true)ratioP=SysMonnaie->RatioG;
//    else            ratioP=1;
	for(i=0;i<lstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)lstTroupeaux->Items[i];
		troupeauTot=TrouveTroupeauTot(troupeau,lstTroupeauxTot);
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			invAniTot=troupeauTot->V_InvAni->trouve(invAni->No);
			if(invAniTot==NULL)
			{
				invAniTot=new CL_InvAni(); //constructeur +simple que par copie
				invAniTot->No=invAni->No;
				invAniTot->NoAnimal=invAni->NoAnimal;
				invAniTot->Animal=invAni->Animal;
				for(n=0;n<N_X+1;n++)
				invAniTot->ValInvMoy[n]=invAni->ValInvMoy[n];//031003 260903
				for(n=0;n<N_X;n++)
				{
					invAniTot->PrixVenteMoy[n]=invAni->PrixVenteMoy[n]; //031003 260903
					invAniTot->Atelier[n]=invAni->Atelier[n];
					invAniTot->NoAtelier[n]=invAni->NoAtelier[n];
					invAniTot->EffMax[n]=0;
				}
				troupeauTot->V_InvAni->ins(invAniTot);
			}
			for(n=0;n<N_X+1;n++)
			{
				invAniTot->Effectif [n]+=invAni->Effectif[n] *ponderation[n];
				invAniTot->Valeur[n] +=invAni->Valeur[n] *ponderation[n]/ratioP;
			}
			for(n=0;n<N_X;n++)
			{
				invAniTot->Vente[n] +=invAni->Vente[n]*ponderation[n];
				invAniTot->Achat[n] +=invAni->Achat[n]*ponderation[n];
				invAniTot->ValVente[n] +=invAni->ValVente[n]*ponderation[n]/ratioP;
				invAniTot->ValAchat[n] +=invAni->ValAchat[n]*ponderation[n]/ratioP;
				invAniTot->EffMax[n] +=invAni->EffMax[n]*ponderation[n];
			}
		}

		for(j=0;j<troupeau->LstMvtAni->Count;j++)
		{
			mvtAni=(CL_MvtAni*)troupeau->LstMvtAni->Items[j];
			n=mvtAni->Date;
			mvtAniTot=TrouveMvtAni(troupeauTot->LstMvtAni,mvtAni);
			if(mvtAniTot==NULL)
			{
				mvtAniTot=new CL_MvtAni(mvtAni);
				mvtAniTot->Eff=mvtAni->Eff*ponderation[n];
				troupeauTot->LstMvtAni->Add(mvtAniTot);
			}
			else
			mvtAniTot->Eff+=mvtAni->Eff*ponderation[n];
		}
	}
	return true;
}
//----------------------------------------------------------------------------
CL_Troupeau* __fastcall TAgriSaisieFrm::TrouveTroupeauTot(CL_Troupeau*troupeau0, TList *lstTroupeauxTot)
{
	int i;
	CL_Troupeau *troupeau;
	for(i=0;i<lstTroupeauxTot->Count;i++)
	{
		troupeau=(CL_Troupeau*)lstTroupeauxTot->Items[i];
		if(troupeau==troupeau0)
		return troupeau;
	}
	troupeau=new CL_Troupeau();
	troupeau->CatBestiaux=troupeau0->CatBestiaux;
	troupeau->NoCatBestiaux=troupeau0->NoCatBestiaux;
	lstTroupeauxTot->Add(troupeau);
	return troupeau;
}
//----------------------------------------------------------------------------
CL_MvtAni* __fastcall TAgriSaisieFrm::TrouveMvtAni(TList *lst,CL_MvtAni *mvtAni0)
{
	int i;
	CL_MvtAni *mvtAni;
	for(i=0;i<lst->Count;i++)
	{
		mvtAni=(CL_MvtAni*)lst->Items[i];
		if(mvtAni->NoAnimal!=mvtAni0->NoAnimal) continue;
		if(mvtAni->Type !=mvtAni0->Type) continue;
		if(mvtAni->Date !=mvtAni0->Date) continue;
		return mvtAni;
	}
	return NULL;
}
/*
 //----------------------------------------------------------------------------
 bool  __fastcall TAgriSaisieFrm::AgregeInvAni(float *ponderation,
 CL_Vecteur<CL_InvAni> *vecteur,
 CL_Vecteur<CL_InvAni> *vecteurTot)

 {

 CL_InvAni *invAni,*invAniTot;
 int i,n;
 for(i=0;i<vecteur->Nbelt;i++)
 {
 invAni=vecteur->Vecteur[i];
 invAniTot=vecteurTot->trouve(invAni->No);
 if(invAniTot==NULL)
 {
 invAniTot=new CL_InvAni(); //constructeur +simple que par copie
 invAniTot->No=invAni->No;
 invAniTot->NoAnimal=invAni->NoAnimal;
 invAniTot->Animal=invAni->Animal;
 for(n=0;n<N_X+1;n++)
 {
 invAniTot->ValInvMoy[n]=invAni->ValInvMoy[n];   //031003 260903
 invAniTot->PrixVenteMoy[n]=invAni->PrixVenteMoy[n];   //031003 260903
 }
 vecteurTot->ins(invAniTot);
 }
 for(n=0;n<N_X+1;n++)
 {
 invAniTot->Effectif [n]+=invAni->Effectif[n] *ponderation[n];
 invAniTot->Valeur[n]   +=invAni->Valeur[n]   *ponderation[n];
 }
 for(n=0;n<N_X+1;n++)
 {
 invAniTot->Vente[n]    +=invAni->Vente[n]*ponderation[n];
 invAniTot->Achat[n]    +=invAni->Achat[n]*ponderation[n];
 invAniTot->ValVente[n] +=invAni->ValVente[n]*ponderation[n];
 invAniTot->ValAchat[n] +=invAni->ValAchat[n]*ponderation[n];
 }
 }
 return true;
 }
 */
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeFormule(float *ponderation,
		CL_Vecteur<CL_Formule> *vecteur,
		CL_Vecteur<CL_Formule> *vecteurTot,
		bool avecFormule)

{
	int i,n;
	float valeur;
	CL_Formule *formule,*formuleTot;
	bool correct=true;
	AnsiString as;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		formule=vecteur->Vecteur[i];

		formuleTot=TrouveFormule(formule,vecteurTot);
		if(formuleTot==NULL)
		{
			//le constructeur de formule ne recopie pas LesProg...
			formuleTot=new CL_Formule(formule);
			formuleTot->Item=formule->Item;
			formuleTot->No =formule->Item->No;
			if(avecFormule==false)
			for(n=0;n<N_X;n++) formuleTot->LesProg[n]=NULL;

			memset(formuleTot->Valeur,0,sizeof(formuleTot->Valeur));
			vecteurTot->insSans(formuleTot);
		}
		for(n=0;n<N_X;n++)
		{
			valeur=formule->Valeur[n];
			valeur*=ponderation[n];
			formuleTot->Valeur[n]+=valeur;
		}
	}
	return correct;
}
/*
 //----------------------------------------------------------------------------
 bool  __fastcall TAgriSaisieFrm::AgregeFormule(float *ponderation,
 CL_Vecteur<CL_Formule> *vecteur,
 CL_Vecteur<CL_Formule> *vecteurTot)
 {
 int i,n,n1;
 float valeur;
 CL_Item    *item;
 CL_Formule *formule,*formuleTot;
 CL_Prog    *prog,*prog1;
 int         noProg[N_X];
 bool correct=true;
 AnsiString  as;
 for(i=0;i<vecteur->Nbelt;i++)
 {
 formule=vecteur->Vecteur[i];

 for(n=0;n<N_X;n++) noProg[n]=-1;
 for(n=0;n<N_X;n++)
 {
 prog=formule->LesProg[n];
 if(noProg[n]!=-1) continue;
 noProg[n]=n;
 for(n1=n+1;n1<N_X;n1++)
 {
 prog1=formule->LesProg[n1];
 //                prog1=formule->LesProg[n];   //310502
 if(prog1==prog)noProg[n1]=n;
 }
 }

 formuleTot=TrouveFormule(formule,vecteurTot);
 if(formuleTot==NULL)
 {
 //le constructeur de formule ne recopie pas LesProg...
 formuleTot=new CL_Formule(formule);
 formuleTot->Item=formule->Item;
 formuleTot->No  =formule->Item->No;
 for(n=0;n<N_X;n++)
 {
 if(noProg[n]== n)
 {
 prog=formule->LesProg[n];
 if(prog==NULL)   //310502
 {
 formuleTot->LesProg[n]=NULL;
 continue;
 }
 formuleTot->LesProg[n]=new CL_Prog(prog);
 }
 else
 {
 n1=noProg[n];
 prog=formule->LesProg[n1];
 if(prog==NULL)   //310502
 {
 formuleTot->LesProg[n]=NULL;
 continue;
 }
 formuleTot->LesProg[n]=formuleTot->LesProg[n1];
 }
 // il n'y a qu'une valeur dans la formule
 if(formuleTot->LesProg[n]->EstNumerique()==true)
 {
 valeur=formule->LesProg[n]->Arbre->LesBranches[0].valeur;
 valeur*=ponderation[n];
 formuleTot->LesProg[n]->Arbre->LesBranches[0].valeur=valeur;
 }
 }
 vecteurTot->insSans(formuleTot);
 }
 else
 {
 for(n=0;n<N_X;n++)
 {
 if(formule->LesProg[n]==NULL) continue;  //310502

 if(formuleTot->LesProg[n]->EstIdentique(formule->LesProg[n])==false)
 {
 correct=false;
 as=formule->Item->Nom;
 as+=" année:  "+IntToStr(n+An_0);
 as+="  la formule de calcul n'est pas la même ";
 ErreurFrm->Edit->Lines->Add(as);
 }
 }
 }
 }
 return correct;
 }
 */
//----------------------------------------------------------------------------
CL_Formule* __fastcall TAgriSaisieFrm::TrouveFormule(CL_Formule *formule,
		CL_Vecteur<CL_Formule> *vecteurTot)
{
	int i;
	CL_Formule *formuleTot;
	for(i=0;i<vecteurTot->Nbelt;i++)
	{
		formuleTot=vecteurTot->Vecteur[i];
		if( formuleTot->Item ==formule->Item)
		return formuleTot;
	}
	return NULL;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeEmprunt(float *ponderation,CL_Agriculteur *agri,
		CL_Agriculteur *agriTot)
{
	int i,n;
	CL_EmpLT *empLT;
	CL_EmpCT *empCT;
	CL_Occc *occc;
	CL_FN_Xp1 *fN_Xp1;
	float capital[N_X],remb[N_X],interet[N_X],dette[N_X+1];
	float *capitalTot,*rembTot,*interetTot,*detteTot;
	// tous lemprunts sont mis dans V_FinSom
	if(agriTot->V_FinSom->Nbelt==0)
	{
		for(i=0;i<8;i++)
		{
			fN_Xp1=new CL_FN_Xp1 ();
			agriTot->V_FinSom->ins(fN_Xp1);
		}
	}
	//LONG TERME
	detteTot= agriTot->V_FinSom->Vecteur[0]->Valeur;
	rembTot= agriTot->V_FinSom->Vecteur[1]->Valeur;
	interetTot= agriTot->V_FinSom->Vecteur[2]->Valeur;
	capitalTot= agriTot->V_FinSom->Vecteur[3]->Valeur;

	for(i=0;i<agri->V_EmpLT->Nbelt;i++)
	{
		empLT=agri->V_EmpLT->Vecteur[i];
		empLT->Calcul (agri->DefSim->An_0,capital,remb,interet,dette);
		if(empLT->ExReal>=0 && empLT->ExReal<N_X)
		capitalTot[empLT->ExReal]=+empLT->Montant;
		for (n=0;n<N_X;n++)
		{
//            capitalTot[n]  +=capital[n];
			detteTot[n] +=dette[n]*ponderation[n];
			rembTot[n] +=remb[n]*ponderation[n];
			interetTot[n] +=interet[n]*ponderation[n];
		}
		detteTot[N_X]+=dette[N_X]*ponderation[n];
		/*a compléter ??
		 if(empLT->Pour==CarEnt)
		 totEmpE->Ajoute (capital,remb,interet,dette);
		 else
		 totEmpP->Ajoute (capital,remb,interet,dette);
		 */
	}
	// COURT TERME
	detteTot= agriTot->V_FinSom->Vecteur[4]->Valeur;
	rembTot= agriTot->V_FinSom->Vecteur[5]->Valeur;
	interetTot= agriTot->V_FinSom->Vecteur[6]->Valeur;
	capitalTot= agriTot->V_FinSom->Vecteur[7]->Valeur;

	for(i=0;i<agri->V_EmpCT->Nbelt;i++)
	{
		empCT=agri->V_EmpCT->Vecteur[i];
		empCT->Calcul (agri->DefSim->An_0,capital,remb,interet,dette);
//        if(empCT->ExReal>=0 && empCT->ExReal<N_X)
//            capitalTot[empCT->ExReal]=+empCT->Montant;
		for (n=0;n<N_X;n++)
		{
			capitalTot[n] +=capital[n]*ponderation[n];
			detteTot[n] +=dette[n]*ponderation[n];
			rembTot[n] +=remb[n]*ponderation[n];
			interetTot[n] +=interet[n]*ponderation[n];
		}
		detteTot[N_X]+=dette[N_X]*ponderation[n];
		/*a compléter ??
		 if(empCT->Pour==CarEnt)
		 totEmpE->Ajoute (capital,remb,interet,dette);
		 else
		 totEmpP->Ajoute (capital,remb,interet,dette);
		 */
	}
	// OCCC
	for( i=0;i<agri->V_Occc->Nbelt;i++)
	{
		occc=agri->V_Occc->Vecteur[i];
		n=occc->Ex-1;
		interetTot[n]=+occc->Montant*(occc->Pcent/100.)*(occc->Taux/100.)*ponderation[n];
	}
	if(agri->V_FinSom->Nbelt==0) return true;
	//FINANCEMENT SOMMAIRE
	for(i=0;i<8;i++)
	{
		fN_Xp1=agri->V_FinSom->Vecteur[i];
		if(fN_Xp1==NULL) continue;
		for (n=0;n<N_X+1;n++)
		agriTot->V_FinSom->Vecteur[i]->Valeur[n]+=fN_Xp1->Valeur[n]*ponderation[n];
	}
	return true;

}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeImmo(float *ponderation,CL_Agriculteur *agri,
		CL_Agriculteur *agriTot)
{
	int i;
	int n;
	CL_Immo *immo;
	CL_Petit *petit;
	CL_FN_Xp1 *fN_Xp1;
	int an_0;
	float amor[N_X],vResid[N_X+1];
	int exAchat,exVente;
	float delta;
	float *vResidTot,*amorTot,*achatTot,*reventeTot,*plusValTot,*moinsValTot;
//float *prodImmoTot;
	//AJOUTER ProdImmo
	// tous lemprunts sont mis dans V_FinSom
	if(agriTot->V_InvSom->Nbelt==0)
	{
		for(i=0;i<7;i++)
		{
			fN_Xp1=new CL_FN_Xp1();
			agriTot->V_InvSom->ins(fN_Xp1);
		}
	}
	/*
	 for(i=0;i<7;i++)
	 {
	 fN_Xp1=agriTot->V_InvSom->Vecteur[i];
	 memset(fN_Xp1,0,sizeof(float)*(N_X+1));
	 }
	 */
	an_0=agri->DefSim->An_0;
	vResidTot= agriTot->V_InvSom->Vecteur[0]->Valeur;
	amorTot= agriTot->V_InvSom->Vecteur[1]->Valeur;
	achatTot= agriTot->V_InvSom->Vecteur[2]->Valeur;
	reventeTot= agriTot->V_InvSom->Vecteur[3]->Valeur;
	plusValTot= agriTot->V_InvSom->Vecteur[4]->Valeur;
	moinsValTot= agriTot->V_InvSom->Vecteur[5]->Valeur;
//    prodImmoTot= agriTot->V_InvSom->Vecteur[6]->Valeur;

	for(i=0;i<agri->V_Immo->Nbelt;i++)
	{
		immo=agri->V_Immo->Vecteur[i];
		immo->Calcul(an_0,amor,vResid,exAchat,exVente);

		if(exAchat>=0 && exAchat<N_X)
		{
			n=exAchat;
			achatTot[n]=+immo->ValAchat*ponderation[n];
		}
		if(exVente>=0 && exVente<N_X)
		{
			n=exVente;
			reventeTot[n]=+immo->ValVente*ponderation[n];
			delta=immo->ValVente-immo->ValComptable;
			if(delta >0) plusValTot[exVente] +=delta*ponderation[n];
			else if(delta <0) moinsValTot[exVente] +=-delta*ponderation[n];
		}
		for (n=0;n<N_X;n++)
		{
			amorTot[n] +=amor[n]*ponderation[n];
			vResidTot[n] +=vResid[n]*ponderation[n];
		}
	}
	//petits immo
	for(i=0;i<agri->V_Petit->Nbelt;i++)
	{
		petit=agri->V_Petit->Vecteur[i];
		achatTot[i]+=petit->ValAchat*ponderation[i];
		amorTot[i] +=petit->ValAchat*ponderation[i];
	}

	//Immo SOMMAIRE
	if(agri->V_InvSom->Nbelt!=0)//260302
	{
		for(i=0;i<7;i++)
		{
			fN_Xp1=agri->V_InvSom->Vecteur[i];
			if(fN_Xp1==NULL) continue;
			for (n=0;n<N_X+1;n++)
			agriTot->V_InvSom->Vecteur[i]->Valeur[n]+=fN_Xp1->Valeur[n]*ponderation[n];
		}
	}
	return true;

}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeSubvention(float *ponderation,
		CL_Vecteur<CL_Sub> *vecteur,
		CL_Vecteur<CL_Sub> *vecteurTot)
{

	CL_Sub *sub,*subTot;
	int i;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		sub=vecteur->Vecteur[i];

		subTot=TrouveSub(vecteurTot,sub);
		if(subTot==NULL)
		{
			subTot=new CL_Sub(sub);
			vecteurTot->ins(subTot);
		}
		subTot->Montant+=sub->Montant*ponderation[0];
	}
	return true;
}
//----------------------------------------------------------------------------
CL_Sub* __fastcall TAgriSaisieFrm::TrouveSub( CL_Vecteur<CL_Sub> *vecteurTot,
		CL_Sub *sub)
{
//a faire
	return sub;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::AgregeTresoIni(float *ponderation,CL_Agriculteur *agri,
		CL_Agriculteur *agriTot)
{
	int n;
	for(n=0;n<N_X;n++)
	agriTot->TresoIni+=agri->TresoIni*ponderation[n];
	return true;

}
//----------------------------------------------------------------------------

