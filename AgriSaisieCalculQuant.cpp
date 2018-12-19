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
#include "TVDico.h"
#include "Compilateur.h"
//#include "GereEtat.h"
#include "GereComparaison.h"

//#include "TVChoixElt.h"

#include "SortieEcran.h"

#include "CL_Comm.h"
#include "Commercialisation.h"
#include "CL_Passe.h"
#include "TravCal.h"
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
//  quand on arrive dans resultat pour 1 agriculteur Global=AGRI TOTAL MOYENNE
//     si modif des données Olympe appelle Calcul
// pour un ensemble(Global=ENSEMBLE)
//     AgriSaisieCalculEnsemble appelle Calcul0 pour chaque agri
//     puis fait les totaux en tenant compte des effectifs
// remettre Global=ENSEMBLE
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::Calcul0(CL_Agriculteur *agri)
{
	int g;
	int an;
	CL_AgriRes *resultat;

	Agri=agri; //nécessaire si on vient de GereIndic GereEtat
	AgriEnCours=agri;
	// regler ou Agri ou AgriEnCours  en supprimer 1  061008
	//Global =ENSEMBLE si on vient AgriSaisCalculEnsemble
	//dans ce cas le travail ci dessous a été fait
	if(Global!=ENSEMBLE)
	{
		if(agri->Resultat) delete agri->Resultat;
		agri->Resultat= new CL_AgriRes();
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
	TotaliserEmpPrive();

	TotalSub();
	TotalPlact();

	TotalImmo();
	TotalImmoPetit();
	TotalImmoSom();
	TotaliserImmo();

	TravCalFrm->Agri=Agri;
	TravCalFrm->CalculTotBesoins();//090306

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
	//ES->ImpV_Elt();
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

	LaGrille->Tag=GCharge;
	CompleteFormule();
	CompleteFormule2(agri->V_Charges);
	LaGrille->Tag=GExtNeg;
	CompleteFormule();
	CompleteFormule2(agri->V_ExtNeg);

	LaGrille->Tag=GExtPos;
	CompleteFormule();
	CompleteFormule2(agri->V_ExtPos);

	LaGrille->Tag=GChStruct;
	/*
	 //..........
	 CL_Formule *formule;
	 CL_Prog *prog;
	 CL_Arbre *arbre;
	 ST_Branche branche;
	 float val;
	 formule=agri->V_ChStruct->Vecteur[0];
	 val=100;
	 for(int n=0;n<N_X;n++ )
	 {
	 prog=new CL_Prog();
	 prog->Arbre=new CL_Arbre(1,0);
	 prog->Arbre->LesBranches[0].code=NOMBRE;
	 prog->Arbre->LesBranches[0].valeur=val;
	 prog->Arbre->BrancheX=1;
	 formule->LesProg[n]=prog;
	 //formule->LesProg[n]->Arbre->LesBranches[0].valeur=val;
	 formule->Valeur[n]=val;
	 val++;
	 }

	 ///......
	 */
	CompleteFormule2(agri->V_ChStruct);

	LaGrille->Tag=GRecDiv; //061104
	CompleteFormule2(agri->V_RecDiv);

	LaGrille->Tag=GDepDiv;//061104
	CompleteFormule2(agri->V_DepDiv);

	LaGrille->Tag=GRecFam;
	CompleteFormule2(agri->V_RecFam);

	LaGrille->Tag=GDepFam;
	CompleteFormule2(agri->V_DepFam);

	LaGrille->Tag=g;
	// calcul an par an pour tenir compte des indicateurs introduits notamment dans charges de structure
	//CreeTVToutElt(TVDicoFrm->TV,agri,false);

	resultat=agri->Resultat;//test
	resultat->Tva->MaZ();
	PurgeLstQuantPrix();
	memset( resultat->Charge,0,sizeof(float)*N_X);
	memset( resultat->ChStruct,0,sizeof(float)*N_X);
	memset( resultat->RecDiv,0,sizeof(float)*N_X);
	memset( resultat->DepDiv,0,sizeof(float)*N_X);
	memset( resultat->RecFam,0,sizeof(float)*N_X);
	memset( resultat->DepFam,0,sizeof(float)*N_X);

	for(an=0;an<N_X;an++)
	{
		V_Indicateur->FlagMisA(false);
		CalcFormule (agri->V_Produits, an);
		//test 141104
		TotalValeurProduction(agri,an);

		CalcFormule (agri->V_Charges, an);

		TotalValeur(agri->V_Charges, resultat->V_Charge,
				resultat->Charge, resultat->V_CatChargeTot,
				resultat->Tva->Verse,
				an);
		CalcFormule (agri->V_ExtNeg, an);
		CalcFormule (agri->V_ExtPos, an);

		CalcFormule (agri->V_ChStruct, an);
		TotalValeur(agri->V_ChStruct,resultat->V_ChStruct,
				resultat->ChStruct,resultat->V_CatChStructTot,
				resultat->Tva->Verse,
				an);

		CalcFormule (agri->V_RecDiv, an);//210512   à rétablir
		TotalValeur(agri->V_RecDiv, resultat->V_RecDiv,
				resultat->RecDiv,resultat->V_CatRecDivTot,
				resultat->Tva->Recu,
				an);

		CalcFormule (agri->V_DepDiv, an);
		TotalValeur(agri->V_DepDiv,resultat->V_DepDiv,
				resultat->DepDiv,resultat->V_CatDepDivTot,
				resultat->Tva->Verse,
				an);

		CalcFormule (agri->V_RecFam, an);
		TotalValeur(agri->V_RecFam,resultat->V_RecFam,
				resultat->RecFam,resultat->V_CatRecFamTot,
				NULL,
				an);

		CalcFormule (agri->V_DepFam, an);
		TotalValeur(agri->V_DepFam,resultat->V_DepFam,
				resultat->DepFam,resultat->V_CatDepFamTot,
				NULL,
				an);
		resultat->Tva->Verse[an] +=resultat->ImmoTotal->TvaVersee[an];
		resultat->Tva->Recu[an] +=resultat->ImmoTotal->TvaRecue[an];

		CalculTva(agri->TvaEntIni,resultat->Tva);// 191201

		//CalculValeur    (agri,              an);
		CalculTreso (agri, an);
		FaireCompta (agri->Resultat, an);//par simplification je calcule tout
		if(an==0)
		CreeTVToutElt(TVDicoFrm->TV,agri,false);

		CalculIndicateur(an);
	}

	CompleteEtatSortie();

	if(Global==ENSEMBLE) return;
	/*
	 CreeTVToutElt(TVChoixEltFrm->TV,agri,false);
	 for(an=0;an<N_X;an++)
	 {
	 CalculIndicateur(an);
	 }
	 */
	// les etats aprés les indic
	GereComparaisonFrm->CompleteComparaison();

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
		//for (j=0;j<delta->NMax;j++) delta->Pcent[j]/=100.;
		for (j=0;j<100;j++) delta->Pcent[j]/=100.;//191207
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::avecEnchainement(CL_AgriDefSim *defSim,CL_Tendance *tendance)
{
	int i,j,k;
	float pcent[N_X];
	CL_Delta *delta; //240907 a voir
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
		if(atelier->V_ProdPied->Nbelt >0)
		CalculAtelierPied(atelier,atelier->V_ProdPied,atelier->PiedHa,resultat->V_Produit,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQProd);
		if(atelier->V_ChPied->Nbelt >0)
		CalculAtelierPied(atelier,atelier->V_ChPied,atelier->PiedHa,resultat->V_Produit,
				valeur->Valeur, atelier->NbPhase,agri->DefSim->TQProd);

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
		if(atelier->V_ProdPied->Nbelt >0)
		CalculVergerPied(atelier->V_ProdPied,atelier->PiedHa,resultat->V_Produit,
				verger,agri->DefSim->TQProd);
		if(atelier->V_ProdPied->Nbelt >0)
		CalculVergerPied(atelier->V_ChPied,atelier->PiedHa,resultat->V_Charge,
				verger,agri->DefSim->TQCharge);

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
	int i,j,j0;
	static float alea0[N_X];
	static bool debut=true;
	CL_Delta *delta;
	ST_NoAgri *noAgri;
	CL_Agriculteur* agri; //test
	agri=AgriEnCours;
	float bidon[N_X];//a sup
	// à voir NoSerie est toujours à 0
	/*
	 if(AgriEnCours->LstSerie)
	 {
	 for(i=0;i<AgriEnCours->LstSerie->Count;i++)
	 {
	 noAgri=(ST_NoAgri*)AgriEnCours->LstSerie->Items[i];
	 if(noAgri->Agri==AgriEnCours)
	 {
	 j0=N_X*i;
	 break;
	 }
	 }
	 }
	 */
	j0=N_X*AgriEnCours->NoSerie;
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
			for(j=0;j<N_X;j++)
			{
				alea[j]=delta->Pcent[j0+j];
				bidon[j]=alea[j];
			}
			//,sizeof(float)*N_X);
			return;
		}
	}
	//si je n'ai rien trouvé
	memcpy(alea,alea0,sizeof(float)*N_X);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::trouveDelta(CL_Item *item,CL_Tendance *tendance,
		float *pcent)
{
	int i,j,j0;
	static float pcent0[N_X];
	static bool debut=true;
	CL_Delta *delta;
	j0=N_X*AgriEnCours->NoSerie;
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
			pcent[j]=delta->Pcent[j+j0]/100.; //240907
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
// calcul quantite fonction de
// production par pied et nombre de pied par ha
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculAtelierPied (
		CL_Atelier *atelier,
		CL_Vecteur<CL_ItemParAtelier> *vQuantPied,
		float *piedHa,
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
	float qteParPied,qteHa;

	bool charge;

	if(vQuantPied==atelier->V_ChPied) charge=true;
	else charge=false;
	//produits
	for(i=0;i<vQuantPied->Nbelt;i++)
	{
		itemPA=vQuantPied->Vecteur[i];
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
				qteParPied=itemPA->QtePhase[p];
				qteHa=qteParPied*piedHa[p];
				qtePhase=(qteHa/ratio)*surface[n];
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
			qteParPied=itemPA->QtePhase[p];
			qteHa=qteParPied*piedHa[p];
			qtePhase=(qteHa/ratio)*surface[n];
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

		if(atelier->DurAmor>0)
		{
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
		}
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
// calcul quantite fonction de
// production par pied et nombre de pied par ha
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculVergerPied(
		CL_Vecteur<CL_ItemParAtelier> *vQuantPied,
		float *PiedHa,
		CL_Vecteur<CL_QuanVal> *vecteurRes,
		CL_Verger *verger,
		CL_Tendance *tendance)
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
	float qteParPied,qteHa;

	atelier=verger->Atelier;
	ilYaStock=false;
	//produits
	for(i=0;i<vQuantPied->Nbelt;i++)
	{
		itemPA=vQuantPied->Vecteur[i];
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
			qteParPied=itemPA->QtePhase[p];
			qteHa=qteParPied*PiedHa[p];
			qtePhase=(qteHa/ratio)*verger->Surface;
			//qtePhase=(itemPA->QtePhase[p]/ratio)*verger->Surface;
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
		if(produitA==NULL) continue; //060508 access
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
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TrouveDonneesAnterieures(CL_Agriculteur *agri)
{

	int i;
	CL_Elt *elt;
	CL_Passe *eltPasse;
	CL_Indicateur *indicateur;
	if(agri->LstPasse==NULL) return; //070104
	if(agri->LstPasse->Count==0)return;
	//reprend les elt du passé(LstPassé) et met sa valeur dans elt pout tratt dans compCalcul
	for(i=0;i<agri->LstPasse->Count;i++)
	{
		eltPasse=(CL_Passe*)agri->LstPasse->Items[i];
		elt=Compil->trouveElt(eltPasse->noFam,eltPasse->noCat,eltPasse->noItem);
		if(elt==NULL) continue;
		elt->Passe=eltPasse->Valeur;
	}

	for(i=0;i<V_Indicateur->Nbelt;i++)
	{
		indicateur=V_Indicateur->Vecteur[i];
		AccrochePasse(agri->LstPasse,indicateur->Prog->Arbre);
	}

	TrouveDonneesAnterieures (agri->LstPasse,agri->V_Produits);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_Charges);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_ChStruct);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_RecDiv);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_DepDiv);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_RecFam);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_DepFam);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_ExtPos);
	TrouveDonneesAnterieures (agri->LstPasse,agri->V_ExtNeg);

}
//-------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TrouveDonneesAnterieures(TList *lstPasse,CL_Vecteur<CL_Formule> *vecteur)
{
	int i;
	CL_Formule *formule;
	CL_Prog *prog;
	bool estVu[N_X];
	int n,j;
	int nbelt;
	nbelt=vecteur->Nbelt;
	for(i=0;i<nbelt;i++)
	{
		formule=vecteur->Vecteur[i];
		for(n=0;n<N_X;n++)estVu[n]=false;
		prog=NULL;

		for(n=0;n<N_X;n++)
		{
			prog=formule->LesProg[n];
			if(prog==NULL) continue;

			if(estVu[n]==true) continue;

			for(j=n+1;j<N_X;j++)
			{
				if(formule->LesProg[j]==prog)
				estVu[j]=true;
			}
			AccrochePasse(lstPasse,prog->Arbre);
		}
	}
}
//-------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AccrochePasse(TList *lstPasse,CL_Arbre *arbre)
{
	int n;
	ST_Branche branche;
	CL_Elt *elt;
	CL_Passe *eltPasse;

	if(arbre==NULL) return;

	for(n=0;n<arbre->BrancheX;n++)
	{
		branche=arbre->LesBranches[n];
		if(branche.date!=0)
		{
			elt=Compil->trouveElt(branche.arg[0],branche.arg[1],branche.arg[2]);
			if(elt->Passe==NULL)
			{
				eltPasse=new CL_Passe(branche.arg);
				lstPasse->Add(eltPasse);
				elt->Passe=eltPasse->Valeur;
				memset(eltPasse->Valeur,0,sizeof(eltPasse->Valeur));
			}
		}
	}
}

