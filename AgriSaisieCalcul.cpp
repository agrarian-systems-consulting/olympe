//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

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
#include "TVChoixElt.h"
#include "Compilateur.h"
#include "GereEtat.h"
#include "TVChoixEltAgri.h"

#include "SortieEcran.h"

#include "CL_Comm.h"
#include "Commercialisation.h"

#include "AgriSaisie.h"

extern CL_ES *ES;
extern CL_Imp *Imp;
extern CL_Compil *Compil;
/*
 Calcul0 est appelé par

 AgriSaisie            FormActivate
 Resultat              RetourDeLBCompAgri
 RetourDeTVChoixComp

 GereIndic             FormActivate
 GereEtat              ActivateEtat

 AgrisaisieCestBon     CEstBon
 AgrisaisieCalculEns   CalculEnsemble
 */
//calcul initial
//  quand on arrive dans resultat pour 1 agriculteur (Global=false)
//     si modif des données Olympe appelle Calcul
// pour un ensemble(Global=true)
//     AgriSaisieCalculEnsemble appelle Calcul0 pour chaque agri
//     puis fait les totaux en tenant compte des effectifs
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::Calcul0(CL_Agriculteur *agri)
{
	int g;

	Agri=agri; //nécessaire si on vient de GereIndic GereEtat
	//Global =true si on vient AgriSaisCalculEnsemble
	//dans ce cas le travail ci dessous a été fait
	if(Global==false)
	{
		if(agri->Resultat) delete agri->Resultat;
		agri->Resultat= new CL_AgriRes;
		MazNFlagCat(); //pour repérer les catégories à imprimer si sortie
		ES->IniV_Elt();
		TrouveDonneesAnterieures(agri);
	}

	//QUANTITE  en tenant compte des aleas
	//calcul pour chaque item quantite[n]
	//le met dans un quanval->Qte[n]
	//               quanVal->Val et quanVal->Stock sont à zero
	//               où servent ils ???
	//ce quanval est stocké dans agri->Resultat->V_Produit
	//                           agri->Resultat->V_Charge
	//                           agri->Resultat->V_Externalite
	//                           avec pb d'ou séparation à la fin des ext+ et -
	// calculs se font à partir de agri->V_Culture
	//                                 ->V_Animaux
	//                                 ->V_Verger
	//                                 ->V_Vivrier
	trouveTend(agri);//PProd,PCharge,QProd,QCharge,QExt
					 // en modifiant delta si Scenario
	CalculQuantite(agri);
	CalculAvance(agri);
	CalculProdImmo(agri);
//    CalculAnimaux(agri);   mis dans Calcul Valeur
	//METTRE AVANT LES CALCULS DE FORMULE
	// les formules peuvent tenir compte de ces éléments
	// 2
	TotalLT();//cf agrisaisie5
	TotalCT();
	TotalOCCC();
	TotalFinSom();
	TotaliserEmp();

	TotalSub();
	TotalPlact();

	TotalImmo();
	TotalImmoPetit();
	TotalImmoSom();
	TotaliserImmo();

	// 1
	//VALEUR en tenant compte des aleas
	// reprend les formules (définies par Olympe et/ou par l'utilisateur)
	//met les résultats dans formule->Valeur
	//les formules sont dans vecteur V_Produits
	//ou V_Charges.. cf CL_Agriculteur
	//ES->IniV_Elt() a été créé dans AgriSaisieCalculEns si Global=true;

	//accroche à elt la valeur de l'item sur N_X années
	// pour tenir compte des aléas utilise metPcentDansElt()
	// pour les prix, notamment, le prix tient copte de l'alea
	Forme0Frm->CompleteV_Elt(agri);

	// CompleteFormule recree formule de calcul pour ce qui est entré
	// via l'assolement, les animaux, le verger, les vivriers
	// dans le tableau de saisie il y a un C en première ? colonne

	// CompleteFormule2 pour ce qui est entré directement dans
	// les tableaux produits charges externalités
	// pas de C en première  colonne

	// CalcFormule tient compte des aleas prix
	// résultats dans formule->Valeur

	// CalcStock formule->Valeur valeur totale des produits
	//                y compris les stocks
	// ce n'est qu'au moment de faire les calculs comptables
	// qu'il faut retirer les stocks et les afficher dans les stocks
	g=LaGrille->Tag;

	LaGrille->Tag=GProduit;
	// calcule formule->Valeur
	CompleteFormule();
	// calcule formule->Valeur     et recopie dans formule recette
	// a voir pour aléas et politique de stockage
	CompleteFormule2(agri->V_Produits);
	CalcFormule (agri->V_Produits);
	//CalcStock       (agri->V_Produits); //seult pour les produits  130303

	// il y a eu problèmes j'ai effacé ...ça peut reservir
	//agri->V_Charges->purge();
	LaGrille->Tag=GCharge;
	CompleteFormule();
	CompleteFormule2(agri->V_Charges);
	CalcFormule (agri->V_Charges);

	LaGrille->Tag=GExtNeg;
	CompleteFormule();
	CompleteFormule2(agri->V_ExtNeg);
	CalcFormule (agri->V_ExtNeg);

	LaGrille->Tag=GExtPos;
	CompleteFormule();
	CompleteFormule2(agri->V_ExtPos);
	CalcFormule (agri->V_ExtPos);

	LaGrille->Tag=GChStruct;
	CompleteFormule2(agri->V_ChStruct);
	CalcFormule (agri->V_ChStruct);

	LaGrille->Tag=GRecDiv;//061104
	CompleteFormule2(agri->V_RecDiv);
	CalcFormule (agri->V_RecDiv);

	LaGrille->Tag=GDepDiv;//061104
	CompleteFormule2(agri->V_DepDiv);
	CalcFormule (agri->V_DepDiv);

	LaGrille->Tag=GRecFam;
	CompleteFormule2(agri->V_RecFam);
	CalcFormule (agri->V_RecFam);

	LaGrille->Tag=GDepFam;
	CompleteFormule2(agri->V_DepFam);
	CalcFormule (agri->V_DepFam);

	LaGrille->Tag=g;

	CalculValeur (agri);

	if(Global==true) return;
	//revoir FaireCompta(void)
//    Agri->Resultat->Compta->FaireCompta(Agri->Resultat);
	FaireCompta(Agri->Resultat);

	CreeTVToutElt(TVChoixEltAgriFrm->TV,Agri,false);

	CalculIndicateur();
	// les etats aprés les indic
	CompleteEtatSortie();
	GereEtatFrm->CompleteComparaison();

}
//----------------------------------------------------------------------------

// pour un agri trouve les aleas (tendance ou scenario) à utiliser

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::trouveTend(CL_Agriculteur *agri)
{
	if(agri->DefSim->TPProd) delete agri->DefSim->TPProd;
	if(agri->DefSim->TPCharge) delete agri->DefSim->TPCharge;
	if(agri->DefSim->TQProd) delete agri->DefSim->TQProd;
	if(agri->DefSim->TQCharge) delete agri->DefSim->TQCharge;
	if(agri->DefSim->TQExt) delete agri->DefSim->TQExt;

	agri->DefSim->TPProd= NULL;
	agri->DefSim->TPCharge= NULL;
	agri->DefSim->TQProd= NULL;
	agri->DefSim->TQCharge= NULL;
	agri->DefSim->TQExt= NULL;

	if(agri->DefSim->TypeAlea!=SANS)
	{
		if(agri->DefSim->PrixProd)
		agri->DefSim->TPProd= new CL_Tendance(agri->DefSim->PrixProd);
		if(agri->DefSim->PrixCharge)
		agri->DefSim->TPCharge=new CL_Tendance(agri->DefSim->PrixCharge);
		if(agri->DefSim->QProd)
		agri->DefSim->TQProd= new CL_Tendance(agri->DefSim->QProd);
		if(agri->DefSim->QCharge)
		agri->DefSim->TQCharge=new CL_Tendance(agri->DefSim->QCharge);
		if(agri->DefSim->QExt)
		agri->DefSim->TQExt= new CL_Tendance(agri->DefSim->QExt);
	}
	EtablitPcent(agri->DefSim,agri->DefSim->TouSPrixProd, agri->DefSim->TPProd);
	EtablitPcent(agri->DefSim,agri->DefSim->TouSPrixCharge, agri->DefSim->TPCharge);
	EtablitPcent(agri->DefSim,agri->DefSim->TouSQProd, agri->DefSim->TQProd);
	EtablitPcent(agri->DefSim,agri->DefSim->TouSQCharge, agri->DefSim->TQCharge);
	EtablitPcent(agri->DefSim,agri->DefSim->TouSQExt, agri->DefSim->TQExt);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::EtablitPcent(CL_AgriDefSim *defSim,int tOUs,CL_Tendance *tend)
{
	if(tend)
	{
		switch(tOUs) //tendance ou scénario
		{
			case 1:sansEnchainement(tend);break;
			case 2:avecEnchainement(defSim,tend);break;
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::sansEnchainement(CL_Tendance *tendance)
{
	int i,j;
	CL_Delta *delta;
	if(tendance==NULL) return;
	for(i=0;i<tendance->V_Delta->Nbelt;i++)
	{
		delta=tendance->V_Delta->Vecteur[i];
		for (j=0;j<N_X;j++) delta->Pcent[j]/=100.;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::avecEnchainement(CL_AgriDefSim *defSim,CL_Tendance *tendance)
{
	int i,j,k;
	float pcent[N_X];
	CL_Delta *delta;
	char car;
	if(tendance==NULL) return;
	for(i=0;i<tendance->V_Delta->Nbelt;i++)
	{
		delta=tendance->V_Delta->Vecteur[i];
		for (j=0;j<N_X;j++)
		{
			car=defSim->Enchainement[j];
			k=(int)(car-'A');
			pcent[j]=delta->Pcent[k];
		}
		for (j=0;j<N_X;j++) delta->Pcent[j]=pcent[j]/100.;
	}
}
//-------------------------------------------------------------------------
void TAgriSaisieFrm::CompleteEtatSortie(void) {
	CL_EtatSortie *etat;
	CL_Elt *elt, *elt0;
	int i, j, k;
	bool trouve;
	for (i = 0; i < V_EtatSortie->Nbelt; i++) {
		etat = V_EtatSortie->Vecteur[i];
		for (j = 0; j < etat->V_Elt->Nbelt; j++) {
			elt = etat->V_Elt->Vecteur[j];
			if (elt->NoFamille == FORME)
				continue;
			trouve = false; //210202  ???a voir
			for (k = 0; k < V_Elt->Nbelt; k++) {
				elt0 = V_Elt->Vecteur[k];
				if (elt0->NoFamille == elt->NoFamille
						&& elt0->NoCategorie == elt->NoCategorie
						&& elt0->NoItem == elt->NoItem) {
					elt->Nom = elt0->Nom;
					elt->Item = elt0->Item; //040302
					elt->NomCat = elt0->NomCat;
					elt->NomFamille = elt0->NomFamille;
					elt->Valeur = elt0->Valeur; //101103
					elt->NoEspece = elt0->NoEspece; //101103
					elt->NoItem = elt0->NoItem; //101103
					trouve = true;
					break;
				}
			}
			if (trouve == true)
				CompleteElt(elt, Agri); //080202
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MazNFlagCat(void)
{

	V_CatProduit ->FlagMisA('N');
	V_CatCharge ->FlagMisA('N');
	V_CatExternalite->FlagMisA('N');

	V_CatChStruct ->FlagMisA('N');
	V_CatRecDiv ->FlagMisA('N');
	V_CatDepDiv ->FlagMisA('N');
	V_CatRecFam ->FlagMisA('N');
	V_CatDepFam ->FlagMisA('N');
}
//	resultat=agri->Resultat;
/* verifier destructeur

 resultat->V_Produit->purge();
 resultat->V_Charge->purge();
 resultat->V_Externalite->purge();

 resultat->V_RecDiv->purge();
 resultat->V_DepDiv->purge();

 resultat->V_RecFam->purge();
 resultat->V_DepFam->purge();
 */
// calcul quantite pour ce qui est introduit par tableaus assolement animaux vivrier verger
//  ne tient pas compte des aléas
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculQuantite(CL_Agriculteur *agri)
{
	int i;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_Verger *verger,*vivrier;
	CL_QuanVal *quanVal;
	CL_AgriRes *resultat=agri->Resultat;

	// Assolement
	//Produit
	for(i=0;i<agri->V_Culture->Nbelt;i++)
	{
		valeur=agri->V_Culture->Vecteur[i];
		atelier=valeur->Atelier;
		CalculAtelier (atelier,atelier->V_Produit, resultat->V_Produit,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQProd);

		CalculAtelier (atelier,atelier->V_Charge, resultat->V_Charge,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQCharge);

		CalculAtelierVol(atelier,atelier->V_ChargeVolume, resultat->V_Charge,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQProd,
				agri->DefSim->TQCharge);

		CalculAtelier (atelier,atelier->V_Externalite, resultat->V_Externalite,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQExt);
	}

	for(i=0;i<agri->V_Animaux->Nbelt;i++)
	{
		valeur=agri->V_Animaux->Vecteur[i];
		atelier=valeur->Atelier;

		CalculAtelier (atelier,atelier->V_Produit, resultat->V_Produit,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQProd);

		CalculAtelier (atelier,atelier->V_Charge, resultat->V_Charge,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQCharge);

		CalculAtelierVol(atelier,atelier->V_ChargeVolume, resultat->V_Charge,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQProd,
				agri->DefSim->TQCharge);

		CalculAtelier (atelier,atelier->V_Externalite, resultat->V_Externalite,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQExt);

	}
	//pour les animaux issus du calcul de mouvement
	CalculTroupeaux(agri,resultat);

	for(i=0;i<agri->V_Verger->Nbelt;i++)
	{
		verger=agri->V_Verger->Vecteur[i];
		// surface par an
		// phase ou est la pérenne chaque année de simulation -1 si rien
		CalculSurfaceVerger(verger);
		atelier=verger->Atelier;
		CalculVerger (atelier->V_Produit, resultat->V_Produit ,verger,
				agri->DefSim->TQProd);
		CalculVerger (atelier->V_Charge, resultat->V_Charge ,verger,
				agri->DefSim->TQCharge);
		CalculVergerVol (atelier->V_ChargeVolume, resultat->V_Charge , verger,
				agri->DefSim->TQProd,agri->DefSim->TQCharge);
		CalculVerger (atelier->V_Externalite, resultat->V_Externalite,verger,
				agri->DefSim->TQExt);
	}
	for(i=0;i<agri->V_Vivrier->Nbelt;i++)
	{
		vivrier=agri->V_Vivrier->Vecteur[i];
		CalculSurfaceVivrier(vivrier);
		atelier=vivrier->Atelier;
		CalculVerger (atelier->V_Produit, resultat->V_Produit ,vivrier,
				agri->DefSim->TQProd);
		CalculVerger (atelier->V_Charge, resultat->V_Charge ,vivrier,
				agri->DefSim->TQCharge);
		CalculVergerVol (atelier->V_ChargeVolume, resultat->V_Charge ,vivrier,
				agri->DefSim->TQProd,agri->DefSim->TQCharge);
		CalculVerger (atelier->V_Externalite, resultat->V_Externalite,vivrier,
				agri->DefSim->TQExt);
	}
	//séparer externalite
	resultat->V_ExtNeg->Nbelt=0;
	resultat->V_ExtPos->Nbelt=0;
	for(i=0;i<resultat->V_Externalite->Nbelt;i++)
	{
		quanVal=resultat->V_Externalite->Vecteur[i];
		if(quanVal->Item->NoCategorie==EXTPOS)
		resultat->V_ExtPos->insSans(quanVal);
		else if(quanVal->Item->NoCategorie==EXTNEG)
		resultat->V_ExtNeg->insSans(quanVal);
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculAtelier (
		CL_Atelier *atelier,
		CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
		CL_Vecteur<CL_QuanVal> *vecteurRes,
		float *surface,int nbPhase,CL_Tendance *tendance)

{
	//210902
	int i,n,p,a;
	float quantite[N_X],qtePhase;
	float ratio;
	CL_ItemParAtelier *itemPA;
	CL_Item *item;
	CL_QuanVal *quanVal;
	float alea[N_X];
	float coef;

	bool charge;

	if(vecteurIPA==atelier->V_Charge) charge=true;
	else charge=false;
	//produits
	for(i=0;i<vecteurIPA->Nbelt;i++)
	{
		itemPA=vecteurIPA->Vecteur[i];
		item=itemPA->Item;
		item->Categorie->Flag='O'; //131003        
		trouveDeltaAtelier(atelier,item,tendance,alea);
		ratio=item->SysUnite->Ratio;
		memset(quantite,0,sizeof(quantite));
		for(n=0;n<N_X;n++)
		{
			if(surface[n]==0.)continue;
			coef=alea[n];
			for(p=0;p<nbPhase;p++)
			{
				qtePhase=(itemPA->QtePhase[p]/ratio)*surface[n];
				if(qtePhase==0) continue;

				qtePhase*=coef;
				a=n+p-1;
				if(a<0 || a>=N_X) continue;
				quantite[a]+=qtePhase;
			}
		}
		// l'année aprés la simulation
		if(charge==true && surface[N_X-1]>0)
		{
			n=N_X-1;
			coef=alea[n];
			p=0;
			qtePhase=(itemPA->QtePhase[p]/ratio)*surface[n];
			if(qtePhase)
			{
				qtePhase*=coef;
				quantite[N_X-1]+=qtePhase;
			}
		}

//        ...
		quanVal=vecteurRes->trouve(item->No);
		if(quanVal==NULL)
		{
			quanVal=new CL_QuanVal(); //210202???
			quanVal->Item=item;
			quanVal->No= item->No;
			vecteurRes->insSans(quanVal);
		}
		for(n=0;n<N_X;n++)
		{
			quanVal->Qte[n] +=quantite[n];
			quanVal->Stock[n] =0; //210802   normalement ne sert à rien
			quanVal->Val[n] =0;
		}
		quanVal->Stock[N_X] =0;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::trouveDeltaAtelier(CL_Atelier *atelier,
		CL_Item *item,CL_Tendance *tendance,float *alea)
{
	int i;
	static float alea0[N_X];
	static bool debut=true;
	CL_Delta *delta;
	if(debut==true)
	{
		for (i=0;i<N_X;i++) alea0[i]=1.;
		debut=false;
	}

	if ( tendance==NULL)
	{
		memcpy(alea,alea0,sizeof(float)*N_X);
		return;
	}
	for(i=0;i<tendance->V_Delta->Nbelt;i++)
	{
		delta=tendance->V_Delta->Vecteur[i];
		if(delta->Item==item && delta->Atelier==atelier)
		{
			memcpy(alea,delta->Pcent,sizeof(float)*N_X);
			return;
		}
	}
	memcpy(alea,alea0,sizeof(float)*N_X);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::trouveDelta(CL_Item *item,CL_Tendance *tendance,
		float *pcent)
{
	int i,j;
	static float pcent0[N_X];
	static bool debut=true;
	CL_Delta *delta;
	if(debut==true)
	{
		for (i=0;i<N_X;i++) pcent0[i]=1.;
		debut=false;
	}

	if ( tendance==NULL)
	{
		memcpy(pcent,pcent0,sizeof(float)*N_X);
		return;
	}
	for(i=0;i<tendance->V_Delta->Nbelt;i++)
	{
		delta=tendance->V_Delta->Vecteur[i];
		if(delta->Item==item )
		{
			for(j=0;j<N_X;j++)
			pcent[j]=delta->Pcent[j]/100.;
			return;
		}
	}
	//si je n'ai rien trouvé
	memcpy(pcent,pcent0,sizeof(float)*N_X);
}
//----------------------------------------------------------------------------
// les resultats sont en unite de transaction
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculAtelierVol (
		CL_Atelier *atelier,
		CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
		CL_Vecteur<CL_QuanVal> *vecteurRes,
		float *surface, int nbPhase,CL_Tendance *tendPro,CL_Tendance *tendCha )
{
	int i,n,p,a;
	float quantite[N_X],production, chargeVolUnit;
	float qtePhase;
	float ratio;
	CL_ItemParAtelier *itemPA,*produitA;
	CL_Item *charge;
	CL_QuanVal *quanVal;
	CL_Item *produit;
	float pcentPro[N_X],pcentCha[N_X];
	float coefPro,coefCha;
	//charges prop au volume
	for(i=0;i<vecteurIPA->Nbelt;i++)
	{
		itemPA=vecteurIPA->Vecteur[i];
		produitA= itemPA->ItemPA;
		produit=produitA->Item;
		trouveDeltaAtelier(atelier,produit,tendPro,pcentPro);

		charge= itemPA->Charge;
		trouveDeltaAtelier(atelier,charge,tendCha,pcentCha);

//		charge->Categorie->Flag='O';
		ratio= charge->SysUnite->Ratio;
		memset(quantite,0,sizeof(float)*N_X);

		for(n=0;n<N_X;n++)
		{
			if(surface[n]==0.)continue;
			coefPro=pcentPro[n];
			coefCha=pcentCha[n];
			for(p=0;p<nbPhase;p++)
			{
				a=n+p-1;
				if(a<0 || a>=N_X) continue;
				production=(produitA->QtePhase[p]/ratio)*surface[n];
				production*=coefPro;
				chargeVolUnit=itemPA->QtePhase[p];
				chargeVolUnit*=coefCha;
				qtePhase=production*chargeVolUnit;
				//if(Global==true) qtePhase*=Effectif[n];
				quantite[a]+=qtePhase;

			}
		}

		quanVal=vecteurRes->trouve(charge->No);
		if(quanVal==NULL)
		{
			quanVal=new CL_QuanVal(); //210202
//            memset(quanVal->Qte,0,sizeof(float)*N_X);
//            memset(quanVal->Val,0,sizeof(float)*N_X);
			quanVal->Item=charge;
			quanVal->No= charge->No;
			vecteurRes->insSans(quanVal);
		}
		for(n=0;n<N_X;n++)
		{
			quanVal->Qte[n]+=quantite[n];
			quanVal->Val[n]=0;
		}
	}
}
//----------------------------------------------------------------------------
// avances aux cultures Stocks
// compte de bilan donc N_X +1
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculAvance(CL_Agriculteur *agri)
{
	int i,j,k,p;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_Verger *verger;
	float *surface;
	float avance[N_PHASE];
	int mOuv; //mois d'ouverture
	mOuv=agri->DefSim->MDeb;
	for(i=0;i<N_X+1;i++)
	agri->Resultat->Avance[i]=0;

	// Assolement
	for(i=0;i<agri->V_Culture->Nbelt;i++)
	{
		valeur=agri->V_Culture->Vecteur[i];
		atelier=valeur->Atelier;
		surface=valeur->Valeur;
		// Avance
		memset(avance,0,sizeof(avance));
		trouveAvance(avance,atelier,mOuv);//190802
		for(j=0;j<N_X;j++)
		{
			for(k=0;k<atelier->NbPhase;k++)
			{
				if(j+k >=N_X+1) break;
				agri->Resultat->Avance[j+k]+=avance[k]*surface[j];
			}
		}
	}

	// je fais l'hypothése que l'année aprés
	// l'assolement sera le même
	agri->Resultat->Avance[N_X]=agri->Resultat->Avance[N_X-1];

	for(i=0;i<agri->V_Verger->Nbelt;i++)
	{
		verger=agri->V_Verger->Vecteur[i];
		atelier=verger->Atelier;
		///Avance
		memset(avance,0,sizeof(avance));
		trouveAvance (avance,atelier,mOuv);//190802
		for(j=0;j<N_X;j++)
		{
			p=verger->Phase[j];
			//Phase[j]=0  pour l'année de plantation
			// mais avance[0] definit les avances l'année d'avant la plantation
			// et il y a toujours un décalage de 1 entre Phase de j
			// et avance
			// pour avoir les avances de p il faut aller chercher avance de p+1
			if(p==-1)
			{
				if(j>=N_X+1) continue;
				if(verger->Phase[j+1]==0)
				agri->Resultat->Avance[j]+=avance[0]*verger->SurfaceAn[j];
				continue;
			}
			agri->Resultat->Avance[j]+=avance[p+1]*verger->SurfaceAn[j];
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::trouveAvance(float *avance,CL_Atelier *atelier,
		int mOuv )
{
	int i,j;
	int nbelt;
	CL_EEF *eEF;
	CL_Vecteur<CL_EEF> *vecteur;
	/*
	 switch(nature)
	 {
	 case AVANCE: vecteur=atelier->V_Avance;break;  //AVANCE
	 case STOCK:  vecteur=atelier->V_Stock; break;  //STOCK

	 }
	 */
	vecteur=atelier->V_Avance;
	memset(avance,0,sizeof(float)*N_PHASE); //210202
	nbelt=vecteur->Nbelt;
	for(i=0;i<atelier->NbPhase;i++)
	{
		for( j=0;j<nbelt;j++)
		{
			eEF=vecteur->Vecteur[j];
			if(mOuv>=eEF->Deb && mOuv<=eEF->Fin )
			{
				avance[i]=eEF->Val;
				break;
			}
		}
		mOuv+=12;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculStock(CL_Agriculteur *agri)
{
}
//----------------------------------------------------------------------------
// Production d'immo
// N_X
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculProdImmo(CL_Agriculteur *agri)
{
	int i,j,n,p;
	int a, a0, a1;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_Espece *espece;
	CL_Verger *verger; //,*vivrier;
	float *surface;
//float              avSt[N_PHASE];
	float valPlant;
	float amor;
	float valResidVerger;
	float pImmo,pImmoFam;
	float prodImmo[100];//210602
	float prodImmoFam[100];
	int an,an0;
	// c'est fait dans le constructeur
	memset(agri->Resultat->ProdImmo, 0,sizeof(float)*N_X);
	memset(agri->Resultat->ProdImmoFam, 0,sizeof(float)*N_X);
	memset(agri->Resultat->AmorPlant, 0,sizeof(float)*N_X);

	// Assolement
	for(i=0;i<agri->V_Culture->Nbelt;i++)
	{
		valeur=agri->V_Culture->Vecteur[i];
		atelier=valeur->Atelier;
		if(atelier->PImmoExiste==false && atelier->PImmoFamExiste==false)
		continue;

		surface=valeur->Valeur;
		for(j=0;j<atelier->NbPhase;j++)
		prodImmo[j]=prodImmoFam[j]=0;

		// Prod Immo Entreprise
		if(atelier->PImmoExiste==true)
		{
			for(j=0;j<atelier->NbPhase;j++)
			prodImmo[j]=atelier->ProdImmo[j];
		}
		if(atelier->PImmoFamExiste==true)
		{
			for(j=0;j<atelier->NbPhase;j++)
			prodImmoFam[j]=atelier->ProdImmoFam[j];
		}
		for(n=0;n<N_X;n++)
		{
			if(surface[n]==0) continue;
			valPlant=0;
			/// la boucle sur j s'arrete quand il n'y a plus rien à amortir
			/// je ne peux pas utiliser boucle sur n_Phase
			/// j'oublierai des amor
			j=0;
			/// pourqoi +1
			/// culture a 3 annes -1 0 1
			/// eg si DebAmor=1 cela correspond à j=2
			while(1)
			{
				/// en phase de prod d'immo
				if(j<atelier->DebAmor+1)
				{
					valPlant+=prodImmo[j]+prodImmoFam[j];
					pImmo= prodImmo[j];
					pImmoFam= prodImmoFam[j];
				}
				/// on commence à amortir
				else if(j ==atelier->DebAmor+1)
				{
					pImmo=pImmoFam=0;
					amor=valPlant/atelier->DurAmor;
					valPlant-=amor;
				}
				///on amortit
				else if(j >atelier->DebAmor)
				{
					pImmo=pImmoFam=0;
					if(valPlant > amor) valPlant-=amor;
					else
					{
						amor=valPlant; //??
						valPlant=0;
					}
				}

				if(j+n>=0 && j+n<N_X+1)
				{
					an=j+n-1;
					if(an==-1) //pour bilan d'ouverture an+1=0
					agri->Resultat->ValPlant[an+1] +=valPlant*surface[n];
					else
					{
						agri->Resultat->ProdImmo[an] +=pImmo *surface[n];
						agri->Resultat->ProdImmoFam[an] +=pImmoFam*surface[n];
						//compte de bilan
						if(an+1<N_X)
						agri->Resultat->ValPlant[an+1] +=valPlant*surface[n];
						agri->Resultat->AmorPlant[an] +=amor *surface[n];
					}
				}
				if(valPlant<=0) break;
				if(j+n >=N_X ) break;
				j++;
			}

		}
	}

	for(i=0;i<agri->V_Verger->Nbelt;i++)
	{
		verger=agri->V_Verger->Vecteur[i];
		atelier=verger->Atelier;

		if(atelier->PImmoExiste==false && atelier->PImmoFamExiste==false)
		continue;

		// Prod Immo Entreprise
		memset(prodImmo, 0,sizeof(prodImmo));
		memset(prodImmoFam, 0,sizeof(prodImmo));
		if(atelier->PImmoExiste==true)
		{
			// calcul des  pimmo par an depuis l'annee de plantation -1
			// espece->Phase[0]     année de plantation
			// atelier->ProdImmo[0] année precedent   année de plantation
			prodImmo[0]=atelier->ProdImmo[0];

			espece=atelier->Espece;
//            for(p=0;p<atelier->NbPhase;p++)
			// si on  change les nb phases de l'espece
			// celles de l'atelier ne sont pas modifiées !!
			// autant prendre directement celles de l'espece

			for(p=0;p<espece->NbPhase;p++)//210602
			{
				a0=espece->Phase[p];
				a1=espece->Phase[p+1];
				for(a=a0;a<a1;a++)
				prodImmo[a]=atelier->ProdImmo[p+1];
				//               if(atelier->ProdImmo[p+2]==0) break;

			}
		}
		// Prod Immo Famille
		if(atelier->PImmoFamExiste==true)
		{
			// calcul des  pimmo par an depuis l'annee de plantation -1
			prodImmoFam[0]+=atelier->ProdImmoFam[0];
			espece=atelier->Espece;
			for(p=0;p<espece->NbPhase;p++)//210602
			{
				a0=espece->Phase[p];
				a1=espece->Phase[p+1];
				for(a=a0;a<a1;a++)
				prodImmoFam[a]=atelier->ProdImmoFam[p+1];
				if(atelier->ProdImmoFam[p+2]==0) break;
			}
		}
		//l'année de plantation il a 1 an!!  par définition
		// age >0
		// il peut y avoir des prod immo l'année precedent la plantation
		an=verger->AnPlant-1;
		an0= agri->DefSim->An_0;
		j=0;
		valPlant=0;
		amor=0;
		valResidVerger=0;
		// sauter les vergers où il n'y a pas d'info sur les amortissements

		if(atelier->DurAmor==0) goto SUITEVERGER;

		while(1)
		{
			if (j <atelier->DebAmor)
			{
				valPlant+=prodImmo[j]+prodImmoFam[j];
				pImmo= prodImmo[j];
				pImmoFam= prodImmoFam[j];
			}
			else if(j ==atelier->DebAmor)
			{
				pImmo=pImmoFam=0;
				amor=valPlant/atelier->DurAmor;
				valPlant-=amor;
			}
			else if(j >atelier->DebAmor)
			{
				pImmo=pImmoFam=0;
				if(valPlant > amor) valPlant-=amor;
				else
				{
					amor=valPlant; //??
					valPlant=0;
				}
			}
			n=an-an0;
			if(n>=N_X) break;

			// arrachage
			if( n>=0 && an== verger->AnArr)
			{
				agri->Resultat->PertePlant[n]+=valResidVerger;
				valResidVerger=0;
				break;
			}

			if(n==-1) //bilan d'ouverture
			{
				agri->Resultat->ValPlant[0] +=valPlant*verger->SurfaceAn[n+1];
				valResidVerger =valPlant*verger->SurfaceAn[n+1];
			}
			else if(n>=0)
			{
				agri->Resultat->ProdImmo[n] +=pImmo *verger->SurfaceAn[n];
				agri->Resultat->ProdImmoFam[n] +=pImmoFam*verger->SurfaceAn[n];
				//compte de bilan
				agri->Resultat->ValPlant[n+1] +=valPlant*verger->SurfaceAn[n];
				valResidVerger =valPlant*verger->SurfaceAn[n];
				agri->Resultat->AmorPlant[n] +=amor*verger->SurfaceAn[n];
			}
			if(valPlant<=0) amor=0;
			j++;
			an++;
		}
		SUITEVERGER:;
	}

}
//----------------------------------------------------------------------------
//					VERGER   VIVRIER
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculSurfaceVerger(CL_Verger *verger)
{
	int i,n;
	int age,ageArr;
	int nbPhase;
	CL_Espece *espece;
	//l'année de plantation il a 1 an!!  par définition
//	age=     AgriEnCours->DefSim->An_0-verger->AnPlant+1; //151001
	age= Agri->DefSim->An_0-verger->AnPlant+1;//151001
//	age=     AgriEnCours->DefSim->An_0-verger->AnPlant; //100101
	ageArr= verger->AnArr-verger->AnPlant+1;
	espece=verger->Atelier->Espece;
	nbPhase=espece->NbPhase;
	for(n=0;n<N_X;n++)
	{
		verger->Phase[n]=-1;
		verger->SurfaceAn[n]=0;
		// année avant plantation où il peut y avoir des charges
		if(age==0)//-1)
		{
			verger->Phase[n]=0;
		}
		//espece->Phase est Défini à partir de la plantation
		// EX     1 2 4 10
		// Rdt    0 5 8 9
		// les quantités produites ou consommées sont dans itemPA->QtePhase
		// qui contient pour les rdt
		//        0 0 5 8 9
		// en fait QtePhase correspond à l'année -1
		else if(age>0 && age <ageArr)
		{
			verger->SurfaceAn[n]=verger->Surface;
			if(age>=espece->Phase[nbPhase-1])
			verger->Phase[n]=nbPhase;
			else
			{
				for(i=0;i<espece->NbPhase;i++)
				{
					if(age>=espece->Phase[i] && age<espece->Phase[i+1])
					{
						verger->Phase[n]=i+1; //100102
						break;
					}
				}
			}
		}
		age++;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculSurfaceVivrier(CL_Verger *vivrier)
{
	int n;
	int age,ageArr;
	age= AgriEnCours->DefSim->An_0-vivrier->AnPlant;
	ageArr= vivrier->AnArr-vivrier->AnPlant;
	for(n=0;n<N_X;n++)
	{
		vivrier->Phase[n]=-1;
		vivrier->SurfaceAn[n]=0;
		if(age>=-1 && age <ageArr)
		{
			vivrier->SurfaceAn[n]=vivrier->Surface;
			vivrier->Phase[n]=age+1;
		}
		age++;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculVerger(
		CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
		CL_Vecteur<CL_QuanVal> *vecteurRes,
		CL_Verger *verger,CL_Tendance *tendance)
{
	int i,n,p;
	CL_ItemParAtelier *itemPA;
	CL_Item *item;
	CL_QuanVal *quanVal;
	CL_Atelier *atelier;
	float qtePhase;
	float alea[N_X];
	float pcentStock[N_X];
	float quantite[N_X];
	float stock[N_X];
	float ratio;
	float coef;
	float pcStocke,pcVendu;
	bool ilYaStock;

	atelier=verger->Atelier;
	ilYaStock=false;
	/*190802
	 if(vecteurIPA==atelier->V_Produit)ilYaStock=true;
	 if( ilYaStock==true)
	 {
	 mOuv=Agri->DefSim->MDeb;
	 trouveAvance(pcentStock,STOCK,atelier,mOuv);
	 }
	 */
	//produits
	for(i=0;i<vecteurIPA->Nbelt;i++)
	{
		itemPA=vecteurIPA->Vecteur[i];
		item=itemPA->Item;
		trouveDeltaAtelier(atelier,item,tendance,alea);
		ratio=item->SysUnite->Ratio;

		memset(quantite,0,sizeof(float)*N_X);
		memset(stock, 0,sizeof(float)*N_X);
		for(n=0;n<N_X;n++)
		{
			coef=alea[n];
			p=verger->Phase[n];
			if(p==-1) continue;
			//!!!!
			qtePhase=(itemPA->QtePhase[p]/ratio)*verger->Surface;
			qtePhase*=coef;
			if( ilYaStock==true)
			{
				pcStocke=pcentStock[p]/100;
				pcVendu=1-pcStocke; //????????????
				quantite[n]+=qtePhase*pcVendu;
				stock[n] +=qtePhase*pcStocke;
			}
			else
			quantite[n]+=qtePhase;
		}
		quanVal=vecteurRes->trouve(item->No);
		if(quanVal==NULL)
		{
			quanVal=new CL_QuanVal(); //210202
			quanVal->Item=item;
			quanVal->No= item->No;
			vecteurRes->insSans(quanVal);
		}
		// je viens de calculer la quantité produite quanVal->Qte[n]
		//                                  stockée  quanVal->Stock[n]
		// + tard cfCalculValeur
		// je calculerai les valeurs vendues quanVal->Val[n]
		// et les valeurs des stocks vendus l'année suivante quanVal->Stock[n]
		// donc attention
		//             quanVal->Stock[n] conyient ici des quantités
		//              +tard des valeurs
		for(n=0;n<N_X;n++)
		{
			quanVal->Qte[n]+=quantite[n];
			quanVal->Val[n]=0;
			quanVal->Stock[n]=0;
		}
		quanVal->Stock[N_X] =0;

	}
}
//----------------------------------------------------------------------------
// les resultats sont en unite de transaction
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculVergerVol (
		CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
		CL_Vecteur<CL_QuanVal> *vecteurRes,
		CL_Verger *verger,CL_Tendance *tendPro,CL_Tendance *tendCha)
{
	int i,n,p;
	float rdt[N_X];
	float conso[N_X];
	float quantite[N_X];
	float ratio;
	CL_ItemParAtelier *itemPA,*produitA;
	CL_Item *produit,*charge;
	CL_QuanVal *quanVal;
	CL_Atelier *atelier;
	float pcentPro[N_X],pcentCha[N_X];
	atelier=verger->Atelier;

	//charges prop au volume
	for(i=0;i<vecteurIPA->Nbelt;i++)
	{
		itemPA=vecteurIPA->Vecteur[i];
		produitA= itemPA->ItemPA;
		produit=produitA->Item;
		trouveDeltaAtelier(atelier,produit,tendPro,pcentPro);

		charge= itemPA->Charge;
		trouveDeltaAtelier(atelier,charge,tendCha,pcentCha);

		memset(rdt, 0,sizeof(float)*N_X);
		memset(conso, 0,sizeof(float)*N_X);
		memset(quantite,0,sizeof(float)*N_X);

		for(n=0;n<N_X;n++)
		{

			p=verger->Phase[n];
			if(p==-1) continue;
			rdt[n]=produitA->QtePhase[p];
			rdt[n]*=pcentPro[n];
			conso[n]=itemPA->QtePhase[p];

		}

		charge= itemPA->Charge;
		trouveDelta(charge,tendCha,pcentCha);

		ratio= charge->SysUnite->Ratio;

//		charge->Categorie->Flag='O';
		for(n=0;n<N_X;n++)
		{
//            quantite[n]=(itemPA->QtePhase[n]*rdt[n]/ratio)*verger->Surface;
			quantite[n]=(conso[n]*rdt[n]/ratio)*verger->Surface;
			quantite[n]*=pcentCha[n];
		}
		quanVal=vecteurRes->trouve(charge->No);
		if(quanVal==NULL)
		{
			quanVal=new CL_QuanVal(); //210202
			quanVal->Item=charge;
			quanVal->No= charge->No;
			vecteurRes->insSans(quanVal);
		}
		for(n=0;n<N_X;n++)
		{
			quanVal->Qte[n]+=quantite[n];
			quanVal->Val[n]=0;
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculTroupeaux(CL_Agriculteur *agri,CL_AgriRes *resultat)
{
	int n;
	CL_Troupeau *troupeau;
	for(n=0;n<agri->LstTroupeaux->Count;n++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[n];
		CalculDuTroupeau(agri,troupeau,resultat);
	}
}

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculDuTroupeau(CL_Agriculteur *agri,CL_Troupeau *troupeau,CL_AgriRes *resultat)
{
//...
	int i,n;
	CL_Atelier *atelier;
	CL_InvAni *invAni;
	float effectif[N_X];
	for(i=0;i<troupeau->V_InvAni->Nbelt;i++)
	{
		invAni=troupeau->V_InvAni->Vecteur[i];

		for(n=0;n<N_X;n++)
		{
			memset(effectif,0,sizeof(effectif));
			atelier=invAni->Atelier[n];
			if(atelier==NULL) continue;

			effectif[n]=invAni->Effectif[n];

			while(1)
			{
				if(n+1>=N_X) break;
				if(invAni->Atelier[n+1]==atelier)
				{
					effectif[n+1]=invAni->Effectif[n+1];
					n++;
				}
				else
				break;
			}

			CalculAtelier (atelier,atelier->V_Produit, resultat->V_Produit,
					effectif, atelier->NbPhase,agri->DefSim->TQProd);

			CalculAtelier (atelier,atelier->V_Charge, resultat->V_Charge,
					effectif, atelier->NbPhase,agri->DefSim->TQCharge);

			CalculAtelierVol(atelier,atelier->V_ChargeVolume, resultat->V_Charge,
					effectif, atelier->NbPhase,agri->DefSim->TQProd,
					agri->DefSim->TQCharge);
			CalculAtelier (atelier,atelier->V_Externalite, resultat->V_Externalite,
					effectif, atelier->NbPhase,agri->DefSim->TQExt);
		}
	}
}
//----------------------------------------------------------------------------

//                 VALEUR
// tendance pris en compte dans CalculFormule cf AgriSaisieFormule
// introduire des tendances pour ch structure etc...
// sans doute a mettre aussi dans CalculFormule
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculValeur(CL_Agriculteur *agri)
{
	int n;
	CL_AgriRes *resultat=agri->Resultat;

	resultat->Tva->MaZ();
	PurgeLstQuantPrix();
	// commercialisation
	// politique de stockage
	// ce qui vient des formules
	TotalValeurProduction(agri->V_Produits, resultat->V_Produit,
			resultat->Produit, resultat->V_CatProduitTot,
			resultat->Tva->Recu);
	//191201
	CalculAnimaux(agri);//calcule la tva recue et versee
	for(n=0;n<N_X;n++)
	resultat->Produit[n]+=resultat->VenteAni[n]- resultat->AchatAni[n];

	TotalValeur(agri->V_Charges, resultat->V_Charge,
			resultat->Charge, resultat->V_CatChargeTot,
			resultat->Tva->Verse);

//mettre tendance
	TotalValeur(agri->V_ChStruct,resultat->V_ChStruct,
			resultat->ChStruct,resultat->V_CatChStructTot,
			resultat->Tva->Verse);

	TotalValeur(agri->V_RecDiv, resultat->V_RecDiv,
			resultat->RecDiv,resultat->V_CatRecDivTot,
			resultat->Tva->Recu);

	TotalValeur(agri->V_DepDiv,resultat->V_DepDiv,
			resultat->DepDiv,resultat->V_CatDepDivTot,
			resultat->Tva->Verse);

	TotalValeur(agri->V_RecFam,resultat->V_RecFam,
			resultat->RecFam,resultat->V_CatRecFamTot,
			NULL);
	TotalValeur(agri->V_DepFam,resultat->V_DepFam,
			resultat->DepFam,resultat->V_CatDepFamTot,
			NULL);
	//calcule la tva
	TotalEnCours();//180102

	/// tva sur immo                                      191201
	/// TotalImmo() cf AgriSaisieTotal a fait les totaux
	for(n=0;n<N_X;n++)
	{
		resultat->Tva->Verse[n] +=resultat->ImmoTotal->TvaVersee[n];
		resultat->Tva->Recu[n] +=resultat->ImmoTotal->TvaRecue[n];
	}
	CalculTva(agri->TvaEntIni,resultat->Tva); // 191201

	CalculResultat(agri);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PurgeLstQuantPrix(void)
{
	int i;
	CL_Formule *formule;
	CL_StockIni *stockIni;
	CL_QuantPrix *quantPrix;
	bool fairePack;
	V_Produit->FlagMisA('N');
	for(i=0;i<Agri->V_Produits->Nbelt;i++)
	{
		formule=Agri->V_Produits->Vecteur[i];
		formule->Item->Flag='O';
	}
	for(i=0;i<Agri->V_StockIni->Nbelt;i++)
	{
		stockIni=Agri->V_StockIni->Vecteur[i];
		stockIni->Item->Flag='O';
	}
	//LstQuantPrix défini dans commercialisation
	// pour retirer ce qui coorespond à des productions qui n'existent plus
	fairePack=false;
	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->Item==NULL)
		{
			Agri->LstQuantPrix->Items[i]=NULL;
			continue;
		}
		if(quantPrix->Item->Flag=='O') continue;

		fairePack=true;
		Agri->LstQuantPrix->Items[i]=NULL;
	}
	if(fairePack==true)
	Agri->LstQuantPrix->Pack();
}
//----------------------------------------------------------------------------
//  partiel utilisé seulement pour Troupeau
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculValeurAnimaux(CL_Agriculteur *agri)
{
	int i,n;
	float *total;
	float val;
	CL_AgriRes *resultat=agri->Resultat;
	CL_Item *item;
	CL_QuanVal *quanVal,*quanValTot;
	float pcent[N_X];
//    resultat->Tva->MaZ();
//	PurgeLstQuantPrix();

	total=resultat->Produit;
	memset( total,0,sizeof(float)*N_X);
	for(i=0;i<resultat->V_Produit->Nbelt;i++)
	{
		quanVal=resultat->V_Produit->Vecteur[i];

		item=quanVal->Item;
		item->Categorie->Flag='O'; //pour simplifier edition

		trouveDelta(item,agri->DefSim->PrixProd,pcent);
		quanValTot=resultat->V_CatProduitTot->trouve(item->NoCategorie);
		for(n=0;n<N_X;n++)
		{
			val=quanVal->Qte[n]*item->Prix*pcent[n];
			quanVal->Val[n] =val;
			total[n] +=val;
			quanValTot->Val[n] +=val;
		}
	}
	//191201
	CalculAnimaux(agri);
	for(n=0;n<N_X;n++)
	resultat->Produit[n]+=resultat->VenteAni[n]- resultat->AchatAni[n];

	total=resultat->Charge;
	memset( total,0,sizeof(float)*N_X);
	for(i=0;i<resultat->V_Charge->Nbelt;i++)
	{
		quanVal=resultat->V_Charge->Vecteur[i];

		item=quanVal->Item;
		item->Categorie->Flag='O'; //pour simplifier edition
		trouveDelta(item,agri->DefSim->PrixCharge,pcent);
		quanValTot=resultat->V_CatChargeTot->trouve(item->NoCategorie);
		for(n=0;n<N_X;n++)
		{
			val=quanVal->Qte[n]*item->Prix*pcent[n];
			quanVal->Val[n] =val;
			total[n] +=val;
			quanValTot->Val[n] +=val;
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalValeurProduction(
		CL_Vecteur<CL_Formule>*vFormule,
		CL_Vecteur<CL_QuanVal>*vProduit,
		float *total,
		CL_Vecteur<CL_QuanVal>*vCatTot,
		float *totTva)
{
	int i,n;
	CL_Item *item;
	CL_QuanVal *quanVal,*quanValTot;
	float tauxTva;

	//mettre item->Flag='N'
	V_Produit->FlagMisA('N');
	for(i=0;i<vProduit->Nbelt;i++)
	{
		quanVal=vProduit->Vecteur[i];
		memset(quanVal->Val,0,sizeof(float)*N_X);
		memset(quanVal->Stock,0,sizeof(float)*(N_X+1));
	}

	if(Agri->LstQuantPrix && Agri->LstQuantPrix->Count>0) //commercialisation
	TotVProdComm(vProduit);

	if(Agri->V_PolStock->Nbelt >0)//politique de stockage
	TotVProdPolStock(vProduit);

	TotVFormule(vFormule,vProduit);

	memset( total,0,sizeof(float)*N_X);
	for(i=0;i<vProduit->Nbelt;i++)
	{
		quanVal=vProduit->Vecteur[i];

		item=quanVal->Item;
		tauxTva=item->Tva->Taux/100;

		item->Categorie->Flag='O'; //pour simplifier edition

		quanValTot=vCatTot->trouve(item->NoCategorie);
		for(n=0;n<N_X;n++)
		{
			total[n] +=quanVal->Val[n];

			quanValTot->Val[n] +=quanVal->Val[n];

			if(totTva!=NULL)
			totTva[n] +=quanVal->Val[n]*tauxTva;
		}
		for(n=0;n<N_X+1;n++)
		quanValTot->Stock[n] +=quanVal->Stock[n];

	}
}
//----------------------------------------------------------------------------
CL_QuanVal* __fastcall TAgriSaisieFrm::TrouveQuanVal(CL_Vecteur<CL_QuanVal>*vProduit,
		CL_Item *item)
{
	CL_QuanVal* quanVal;
	quanVal=vProduit->trouve(item->No);
	if(quanVal==NULL)
	{
		quanVal=new CL_QuanVal(); //210202
		quanVal->Item=item;
		quanVal->No= item->No;
		vProduit->insSans(quanVal);
	}
	return quanVal;
}
//----------------------------------------------------------------------------
// provisoirement prix revient =prix vente standard
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotVProdComm(CL_Vecteur<CL_QuanVal>*vProduit)
{
	int i,j,n,nProd;
	int an_0=Agri->DefSim->An_0;
	int an,anComm,anProd;
	float prixRevient[N_X*2]; //prixRevient
	CL_QuantPrix *quantPrix;
	CL_Item *item,*item0;
	CL_QuanVal *quanVal;
	CL_StockIni *stockIni;
	for(i=0;i<Agri-> LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		item=quantPrix->Item;
		// pour ne pas calculer 3 fois  ici TotVFormule TotVProdPolStock
		item->Flag='O';
		if(item!=item0)
		{
			for(n=0;n<N_X*2;n++) prixRevient[n]= item->Prix; //provisoire

			for(j=0;j<Agri->V_StockIni->Nbelt;j++)
			{
				stockIni=Agri->V_StockIni->Vecteur[j];
				if(stockIni->Item==item)
				{
					for(n=0;n<N_X;n++)prixRevient[n]=stockIni->PrixRevient[n];
					break;
				}
			}
		}
		quanVal=TrouveQuanVal(vProduit,item);

		anComm=quantPrix->AnComm;
		anProd=quantPrix->AnProd;
		nProd=anProd-an_0+N_X;
		if(anProd<an_0)
		{
			quanVal->Stock[0]+=quantPrix->Quant*prixRevient[nProd];
			anProd=an_0;
		}
		for(an=anProd;an<anComm;an++)
		{
			n=an-an_0+1;
			if(n>N_X+1) break;
			quanVal->Stock[n]+=quantPrix->Quant*prixRevient[nProd];
		}
		if((anComm-an_0)<N_X)
		quanVal->Val[anComm-an_0]+=quantPrix->Quant*quantPrix->Prix;
		item0=item;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotVProdPolStock(CL_Vecteur<CL_QuanVal>*vProduit)
{
	int i,j,n;
	float quant,qStock;
	CL_Item *item;
	CL_QuanVal *quanVal;
	CL_PolStock *polStock;
	CL_StockIni *stockIni;
	float prix[N_X];
	for(i=0;i<vProduit->Nbelt;i++)
	{
		quanVal=vProduit->Vecteur[i];
		if(quanVal->Item->Flag=='O') continue;

		item=quanVal->Item;
		trouveDelta(item,Agri->DefSim->TPProd,prix);
		for(n=0;n<N_X;n++)prix[n]*=item->Prix;

		polStock=Agri->V_PolStock->trouve(item->No);
		if(polStock==NULL) continue;

		item->Flag='O';
		for(n=0;n<N_X;n++)
		{
			quant=quanVal->Qte[n];
			qStock=quant*polStock->PcentStock/100.;
			if(qStock > polStock->Maxi)qStock=polStock->Maxi;
			quanVal->Val[n]+=(quant-qStock)*prix[n];
			if((n+1)<N_X)
			quanVal->Val[n+1]+=qStock*prix[n]*polStock->PcentDeltaPrix/100.;
			quanVal->Stock[n+1]+=qStock*prix[n]*(100-polStock->PcentDecote)/100.;
		}

		for(j=0;j<Agri->V_StockIni->Nbelt;j++)
		{
			stockIni=Agri->V_StockIni->Vecteur[j];
			if(stockIni->Item!=item) continue;

			quant=stockIni->Quantite[N_X-1];
			stockIni->PrixRevient[N_X-1];

			quanVal->Val[0]+=quant*stockIni->PrixRevient[N_X-1];
			quanVal->Stock[0]+=quant*stockIni->PrixRevient[N_X-1];

			//quanVal->Val[0]+=quant*item->Prix; //???
			//quanVal->Stock[0]+=quant*item->Prix*(100-polStock->PcentDecote)/100.;

		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotVFormule(CL_Vecteur<CL_Formule>*vFormule,
		CL_Vecteur<CL_QuanVal>*vProduit)

{
	int i,j,n;
	float quant;
	CL_Formule *formule;
	CL_Item *item;
	CL_QuanVal *quanVal;
	CL_Prog *prog;
	CL_StockIni *stockIni;

	for(i=0;i<vFormule->Nbelt;i++)
	{
		formule=vFormule->Vecteur[i];
		item=formule->Item;
		if(item->Flag=='O') continue;

		for(n=0;n<N_X;n++)
		{
			prog=formule->LesProg[n];
			if(prog==NULL) continue;
			if(prog->Arbre->ContientIndic()==true)
			Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
		}

		quanVal=TrouveQuanVal(vProduit,item);
		for(n=0;n<N_X;n++)
		quanVal->Val[n] +=formule->Valeur[n]; //270303

		for(j=0;j<Agri->V_StockIni->Nbelt;j++)
		{
			stockIni=Agri->V_StockIni->Vecteur[j];
			if(stockIni->Item!=item) continue;

			quant=stockIni->Quantite[N_X-1];
			stockIni->PrixRevient[N_X-1];

			quanVal->Val[0]+=quant*stockIni->PrixRevient[N_X-1];
			quanVal->Stock[0]+=quant*stockIni->PrixRevient[N_X-1];

			//quanVal->Val[0]+=quant*item->Prix; //???
			//quanVal->Stock[0]+=quant*item->Prix*(100-polStock->PcentDecote)/100.;

		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TotalValeur(
		CL_Vecteur<CL_Formule>*vFormule,
		CL_Vecteur<CL_QuanVal>*vProduit,
		float *total,
		CL_Vecteur<CL_QuanVal>*vCatTot,float *totTva)
{
	int i,n;
	CL_Formule *formule;
	CL_Item *item;
	CL_QuanVal *quanVal,*quanValTot;
	CL_Prog *prog;
	float tauxTva;
	memset( total,0,sizeof(float)*N_X);
	for(i=0;i<vFormule->Nbelt;i++)
	{
		formule=vFormule->Vecteur[i];
		for(n=0;n<N_X;n++)
		{
			prog=formule->LesProg[n];
			if(prog==NULL) continue;
			if(prog->Arbre==NULL) continue; //220603
			if(prog->Arbre->ContientIndic()==true)
			Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
		}

		item=formule->Item;
		item->Categorie->Flag='O'; //pour simplifier edition

		tauxTva=item->Tva->Taux/100;
		quanVal=vProduit->trouve(item->No);
		if(quanVal==NULL)
		{
			quanVal=new CL_QuanVal(); //210202
			quanVal->Item=item;
			quanVal->No= item->No;
			vProduit->insSans(quanVal);
		}
		quanValTot=vCatTot->trouve(item->NoCategorie);
		for(n=0;n<N_X;n++)
		{
			total[n] +=formule->Valeur[n];
			quanVal->Val[n] +=formule->Valeur[n];
			quanValTot->Val[n]+=formule->Valeur[n];
			if(totTva!=NULL)
			totTva[n] +=formule->Valeur[n]*tauxTva;
		}
	}
}
//----------------------------------------------------------------------------
/// inventaire animal-> VenteAni venteNette
///                  -> InvAni Inventaire en valeur
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculAnimaux(CL_Agriculteur *agri)
{
	int i,j,n;
	bool ilYaErreur;
	CL_Valeur *valeur;
	CL_Atelier *atelier;

	CL_InvAni *invAni;
	CL_AgriRes *resultat;
	CL_Item *animal;
	CL_Troupeau *troupeau;
	float tauxTva;
	resultat=agri->Resultat;
	/// a chaque calcul Calcul0 a utilisé new CL_AgriRes
	// ??? avant sortie MvtAni a t il lancé CalculValeur
	for(i=0;i<agri->V_Animaux->Nbelt;i++)//260903
	{
		valeur=agri->V_Animaux->Vecteur[i];
		atelier=valeur->Atelier;
		for(n=0;n<N_X;n++)
		{
			resultat->InvAniRepro[n]+=atelier->ValInvRepro*valeur->Valeur[n];
			resultat->InvAniAutre[n]+=atelier->ValInvAutre*valeur->Valeur[n];
		}
		// je suppose que aprés dernier année c'st constant
		resultat->InvAniRepro[N_X]+=atelier->ValInvRepro*valeur->Valeur[N_X-1];
		resultat->InvAniAutre[N_X]+=atelier->ValInvAutre*valeur->Valeur[N_X-1];
	}
	ilYaErreur=false;
	for(i=0;i<agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			animal=invAni->Animal;
			if(animal==NULL)
			{
				troupeau->V_InvAni->sup(invAni);
				if(ilYaErreur==false)
				{
					ShowMessage("Revoir le Troupeau");
					ilYaErreur=true;
					troupeau->VideLstMvtAni();
				}
				i--;
				continue;
			}
			tauxTva=animal->Tva->Taux;
			for(n=0;n<N_X+1;n++) //260903
			{
				if(invAni->Reproducteur=='O' ||invAni->Reproducteur=='o')
				resultat->InvAniRepro[n]+=invAni->Valeur[n];
				else
				resultat->InvAniAutre[n]+=invAni->Valeur[n];
			}
			for(n=0;n<N_X;n++)
			{
				resultat->VenteAni[n] +=invAni->ValVente[n];
				resultat->Tva->Recu[n] +=invAni->ValVente[n]*tauxTva;

				resultat->AchatAni[n] +=invAni->ValAchat[n];
				resultat->Tva->Verse[n]+=invAni->ValAchat[n]*tauxTva;
			}
		}
	}
}
//----------------------------------------------------------------------------
/*
 pour un exercice comptable démarrant au 1er janvier

 en mai regularisation tva
 je calcule la régularisation tva comme suit
 regul=    tva encaissée exercice précédent
 -tva versée
 -acomptes versés en aout et novembre de l'an passé
 -comptes versés en février et mai de l'année
 si regul <0
 j'ai versé plus que je n'ai encaissé
 remboursement en juin
 sinon
 j'ai encaissé plus que je n'ai versé
 je verserai en juin
 calculer acomptes=regul /5
 et je verserai  acompte en aout nov de cette année
 et en Fev Mai de l'année prochaine

 */
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculTva(CL_TvaEntIni *tvaIni, CL_TvaEnt *tva)
{
	int n;
	float regul;
	float totTva;
	float acompte;
	//hypothèse ouverture janvier
	// les calculs se  font en mai
	totTva= tvaIni->Recu - tvaIni->Verse;
	acompte=totTva/5;

	regul =
	totTva
	-tvaIni->AcompteMai
	-tvaIni->AcompteAout
	-tvaIni->AcompteNov
	-tvaIni->AcompteFev;
	n=0;
	tva->AcompteMai[n]= acompte;
	tva->AcompteAout[n]= acompte;
	tva->AcompteNov[n]= acompte;
	tva->AcompteFev[n+1]= acompte;

	if(regul<0)
	{
		tva->RembTva[n]=-regul;
		tva->Solde[n] =-regul +3*acompte;
	}
	else
	{
		tva->Regul[n]= regul;
		tva->Solde[n] = regul +3*acompte;
	}

	for(n=1;n<N_X;n++)
	{
		totTva= tva->Recu[n-1] - tva->Verse[n-1];
		if(totTva<0) acompte=0;
		else acompte=totTva/5;
		// calcul des acomptes

		tva->AcompteMai[n]= acompte;
		tva->AcompteAout[n]= acompte;
		tva->AcompteNov[n]= acompte;
		if( (n+1)<N_X)
		tva->AcompteFev[n+1]= acompte;

		//calcul régularisation
		regul = totTva
		-tva->AcompteMai[n-1]
		-tva->AcompteAout[n-1]
		-tva->AcompteNov[n-1]
		-tva->AcompteFev[n];

		if(regul<0)
		tva->RembTva[n] =-regul;
		else
		tva->Regul[n]= regul;

		tva->Solde[n]= regul+ tva->AcompteFev[n]+tva->AcompteMai[n]
		+ tva->AcompteAout[n]+tva->AcompteNov[n];
	}
//    si tva->Solde >0 c'est à payer  si <0  à recevoir
// j'harmonise les >0 sont des sorties les <0 sont des rentrées
	for(n=0;n<N_X;n++) tva->Solde[n]*=-1;
	for(n=0;n<N_X;n++) tva->Solde[n]+=tva->Recu[n]-tva->Verse[n];

}

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculResultat(CL_Agriculteur *agri)
{
	CL_AgriRes *resultat=agri->Resultat;

	for(int n=0;n<N_X;n++)
	{
		resultat->Marge[n]= resultat->Produit[n]
//        						 + resultat->VenteAni[n]
//                               - resultat->AchatAni[n]
		- resultat->Charge[n];

		resultat->AutreDepense[n]= resultat->ChStruct[n]
		+ resultat->DepDiv[n]
		+ resultat->DepFam[n];

		resultat->AutreRecette[n]= resultat->RecDiv[n]
		+ resultat->RecFam[n];

		resultat->Solde[n]= resultat->Marge[n]

		- resultat->AutreDepense[n]
		+ resultat->AutreRecette[n]
		- resultat->ImmoTotal->Achat[n]
		+ resultat->ImmoTotal->Vente[n]
		+ resultat->EmpTotal->Capital[n]
		- resultat->EmpTotal->Remb[n]
		- resultat->EmpTotal->Interet[n]

		- resultat->PlactE->Capital[n]
		+ resultat->PlactE->Remb[n]
//                                  + resultat->PlactE->Interet[n]

		+ resultat->TotSub->Valeur[n]
		// stocks enCours
		+resultat->Creance->Flux[n]
		-resultat->Dette->Flux[n]

		+ resultat->Tva->Solde[n];
	}
	resultat->TresoIni=agri->TresoIni;
	// pour permettre conversion qui ne convertit que resultat
	resultat->SoldeCumul[0]=resultat->TresoIni+resultat->Solde[0];
	for(int n=1;n<N_X;n++)
	{
		resultat->SoldeCumul[n]= resultat->SoldeCumul[n-1]
		+ resultat->Solde[n];
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculIndicateur(void)
{
	int i;
	CL_Indicateur *indic;

	for(i=0;i<V_Indicateur->Nbelt;i++)
	{
		indic=V_Indicateur->Vecteur[i];
		Compil->Calculer(indic->Prog->Reseau,indic->Prog->Arbre,0,N_X,indic->Valeur);

	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FaireCompta(CL_AgriRes *resultat)
// la mettre en methode de CL_AgriRes
{
	int n,i;
	CL_QuanVal *quanVal;
//calculs TVA créances dettes
	resultat->creanceTva[0]=0;
	resultat->detteTva[0]= resultat->Tva->AcompteFev[0]
	+resultat->Tva->Regul[0];
	if(resultat->detteTva[0]<0)
	{
		resultat->creanceTva[0]=-resultat->detteTva[0];
		resultat->detteTva[n]=0;
	}
	for(n=1;n<N_X+1;n++)
	resultat->detteTva[n]=
	resultat->Tva->Recu[n-1]
	- resultat->Tva->Verse[n-1]
	- resultat->Tva->AcompteMai[n-1]
	- resultat->Tva->AcompteAout[n-1]
	- resultat->Tva->AcompteNov[n-1];

	for(n=1;n<N_X+1;n++)
	{
		resultat->creanceTva[n]=0;
		if(resultat->detteTva[n] <0)
		{
			resultat->creanceTva[n]=-resultat->detteTva[n];
			resultat->detteTva[n]=0;
		}
	}
//stocks produits + inventaire animaux non reproducteurs
	memset(resultat->StockIni,0,sizeof(float)*(N_X+1));

	// 1 stocks produits

	memset(resultat->Stock,0,sizeof(float)*(N_X+1));
	for(n=0;n<resultat->V_Produit->Nbelt;n++)
	{
		quanVal=resultat->V_Produit->Vecteur[n];
		for(i=0;i<N_X+1;i++)
		resultat->Stock[i]+=quanVal->Stock[i];
	}
	// stock comporte stock + stockIni
	// variation de stock
	for(n=0;n<N_X;n++)
	{
		resultat->deltaStock[n]= resultat->Stock[n+1]-resultat->Stock[n];
		resultat->deltaAvance[n]= resultat->Avance[n+1]-resultat->Avance[n];
		resultat->deltaVarInvAniRepro[n]= resultat->InvAniRepro[n+1]-resultat->InvAniRepro[n]; //260903
		resultat->deltaVarInvAniAutre[n]= resultat->InvAniAutre[n+1]-resultat->InvAniAutre[n];//260903
	}

	//.................
//Ceg
	//Total Produits
	for(n=0;n<N_X;n++)
	resultat->totProduit[n]=
	resultat->Produit[n]//tient compte des ventes et achats d'animaux
	+ resultat->RecDiv[n]
	+ resultat->deltaStock[n]
	+ resultat->deltaAvance[n]
	+ resultat->deltaVarInvAniRepro[n]//260903
	+ resultat->deltaVarInvAniAutre[n]//260903
	+ resultat->PlactE->Interet[n]
	+ resultat->ProdImmo[n]
	+ resultat->ImmoTotal->Vente[n]
	- resultat->PertePlant[n]
	+ resultat->TotSub->Amor[n];
	//Total Dépenses
	for(n=0;n<N_X;n++)
	resultat->totDepense[n]=
	resultat->Charge[n]
	+ resultat->DepDiv[n]
	+ resultat->ImmoTotal->ValCompta[n];
	//Total Charges de structure
	for(n=0;n<N_X;n++)
	resultat->totChStruct[n]=
	resultat->ImmoTotal->Amor[n]
	+ resultat->AmorPlant[n]
	+ resultat->EmpTotal->Interet[n]//050402
//                        + resultat->EmpLTE->Interet[n]
//                        + resultat->EmpCTE->Interet[n]
//                        + resultat->FraisOccc[n]  130303
	+ resultat->ChStruct[n];//ch struct du tableau de saisie
	for(n=0;n<N_X;n++)
	resultat->resExercice[n]=
	resultat->totProduit[n]
	- resultat->totDepense[n]
	- resultat->totChStruct[n];
//Ebe
	for(n=0;n<N_X;n++)
	resultat->Ebe[n]=
	resultat->Produit[n]//tient compte des ventes et achats d'animaux
	+ resultat->RecDiv[n]
	+ resultat->deltaStock[n]//variations d'inventaire
	+ resultat->deltaAvance[n]
	+ resultat->deltaVarInvAniRepro[n]
	+ resultat->deltaVarInvAniAutre[n]
	- resultat->Charge[n]// ch ope
	- resultat->DepDiv[n]
	- resultat->ChStruct[n];//ch struct hors amor et frais fi
//                      -resultat->Msa[n]

//Caf
	for(n=0;n<N_X;n++)
	resultat->Caf[n]=
	resultat->Ebe[n]
	- resultat->EmpLTE->Interet[n]
	- resultat->EmpLTE->Remb[n]

	//- resultat->EmpCTE->Remb[n]      //??
	- resultat->EmpCTE->Interet[n]

	- resultat->FraisOccc[n]

	- resultat->EmpLTP->Remb[n]
	- resultat->EmpLTP->Interet[n]

	- resultat->DepFam[n]
	+ resultat->RecFam[n]
	+ resultat->PlactE->Interet[n];

//Prive
	for(n=0;n<N_X;n++)
	resultat->soldePrive[n]=
	resultat->RecFam[n]
	- resultat->DepFam[n]
	+ resultat->ProdImmoFam[n]
	+ resultat->PlactP->Interet[n]
	- resultat->EmpLTP->Remb[n]
	- resultat->EmpCTP->Remb[n]
	- resultat->EmpLTP->Interet[n]
	- resultat->EmpCTP->Interet[n]
	- resultat->PlactP->Capital[n];
//Bilan
	for(n=0;n<N_X+1;n++)
	resultat->totImmo[n] =
	resultat->ImmoTotal->Resid[n]
	+ resultat->InvAniRepro[n]//260903
	+ resultat->InvAniAutre[n]//260903
	+ resultat->ValPlant[n];
	resultat->tresorerie[0]=resultat->TresoIni;
	for(n=1;n<N_X+1;n++)
	resultat->tresorerie[n]=resultat->SoldeCumul[n-1];

	//bilan d'ouverture
	resultat->totActif[0]=
	resultat->totImmo[0]
//                +resultat->StockIni[0]
	+resultat->Stock[0]
	+resultat->Avance[0]
	//creance
	+resultat->Creance->CrDette[0]
	+resultat->PlactE->Dette[0]
	+resultat->creanceTva[0]
	+resultat->tresorerie[0];

	resultat->totPassif[0]=
	resultat->TotSub->Resid[0]
	+resultat->Dette->CrDette[0]
	+resultat->EmpLTE->Dette[0]
	+resultat->EmpCTE->Dette[0]
	+resultat->detteTva[0];

	resultat->capital[0]= resultat->totActif[0]-resultat->totPassif[0];

	resultat->totPassif[0]=resultat->totActif[0];
	resultat->capital[1]=resultat->capital[0];
	// calcul bilan
	for(n=1;n<N_X+1;n++)
	{
		resultat->totActif[n]= resultat->totImmo[n]
		+resultat->Stock[n]
		+resultat->Avance[n]
		//creance
		+resultat->Creance->CrDette[n]
		+resultat->PlactE->Dette[n]
		+resultat->creanceTva[n]
		+resultat->tresorerie[n];

		resultat->totPassif[n]= resultat->capital[n]
		+resultat->soldePrive[n-1]
		+resultat->Dette->CrDette[n]
		+resultat->TotSub->Resid[n]
		+resultat->EmpLTE->Dette[n]
		+resultat->EmpCTE->Dette[n]
		+resultat->detteTva[n];

		resultat->benefice[n-1]=resultat->totActif[n] -resultat->totPassif[n];
		if(resultat->benefice[n-1] >0)
		{
			resultat->perte[n-1]=0;
			resultat->totPassif[n]+=resultat->benefice[n-1];
		}
		else
		{
			resultat->perte[n-1]=-resultat->benefice[n-1];
			resultat->benefice[n-1]=0;
			resultat->totActif[n]+=resultat->perte[n-1];
		}
		if(n+1>=N_X+1) continue;

		resultat->capital[n+1]=resultat->capital[n]+resultat->benefice[n-1]-resultat->perte[n-1]+resultat->soldePrive[n-1];
	}

}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TrouveDonneesAnterieures(CL_Agriculteur *agri)
{
	int i,n;
	CL_Indicateur *indicateur;
	ST_Branche branche;
	CL_Elt *elt;
	int toto;
	/*
	 TrouveDonneesAnterieures      (agri->V_Produits);
	 TrouveDonneesAnterieures      (agri->V_Charges);
	 TrouveDonneesAnterieures      (agri->V_ChStruct);
	 TrouveDonneesAnterieures      (agri->V_RecDiv);
	 TrouveDonneesAnterieures      (agri->V_DepDiv);
	 TrouveDonneesAnterieures      (agri->V_RecFam);
	 TrouveDonneesAnterieures      (agri->V_DepFam);
	 TrouveDonneesAnterieures      (agri->V_ExtPos);
	 TrouveDonneesAnterieures      (agri->V_ExtNeg);


	 for(i=0;i<V_Indicateur->Nbelt;i++)
	 {
	 indicateur=V_Indicateur->Vecteur[i];
	 for(n=0;n<indicateur->Prog->Arbre->BrancheX;n++)
	 {
	 branche=indicateur->Prog->Arbre->LesBranches[n];
	 if(branche.date!=0)
	 {
	 elt=new CL_Elt();
	 toto=1;
	 }
	 }
	 }
	 */
}
//-------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TrouveDonneesAnterieures(CL_Vecteur<CL_Formule> *vecteur)
{
	int i;
	CL_Formule *formule;
	CL_Prog *prog;
	int leProgDe[N_X];
	int n,j;
	int nbelt,noX;
	nbelt=vecteur->Nbelt;
	for(i=0;i<nbelt;i++)
	{
		formule=vecteur->Vecteur[i];
//        for(n=0;n<N_X;n++)estEcrit[n]=false;
		prog=NULL;
		/*
		 for(n=0;n<N_X;n++)
		 {
		 prog=formule->LesProg[j]==prog
		 for(j=n;j<N_X;j++)
		 {
		 if(formule->LesProg[j]==prog)
		 {
		 leProgDe[j]=1;
		 estEcrit[j]=true;
		 }
		 }
		 fwrite(leProgDe,sizeof(int)*N_X,1,fichier);
		 ecrireArbre(prog->Arbre);
		 }
		 */
	}
}
//-------------------------------------------------------------------------

