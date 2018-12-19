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
#include "GereEtat.h"
//#include "TVChoixElt.h"

#include "SortieEcran.h"

#include "CL_Comm.h"
#include "Commercialisation.h"

#include "AgriSaisie.h"

extern CL_ES *ES;
extern CL_Imp *Imp;
extern CL_Compil *Compil;

//                 VALEUR
// tendance pris en compte dans CalculFormule cf AgriSaisieFormule
// introduire des tendances pour ch structure etc...
// sans doute a mettre aussi dans CalculFormule
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculValeur(CL_Agriculteur *agri, int an)
{
	CL_AgriRes *resultat=agri->Resultat;
	if(an==0)
	{
		/*     transféré dans AgriSaisieCalcul Quant
		 resultat->Tva->MaZ();
		 PurgeLstQuantPrix();
		 memset(	resultat->Charge,0,sizeof(float)*N_X);
		 memset(	resultat->ChStruct,0,sizeof(float)*N_X);
		 memset(	resultat->RecDiv,0,sizeof(float)*N_X);
		 memset(	resultat->DepDiv,0,sizeof(float)*N_X);
		 memset(	resultat->RecFam,0,sizeof(float)*N_X);
		 memset(	resultat->DepFam,0,sizeof(float)*N_X);
		 */
		//calcul de la valeur de la production
		//tient compte dans l'ordre de ce qui est intoduit dans
		//    commercialisation
		//    politique de stockage
		//    ce qui vient des formules
		/*
		 TotalValeurProduction(agri->V_Produits, resultat->V_Produit,
		 resultat->Produit, resultat->V_CatProduitTot,
		 resultat->Tva->Recu);
		 //191201
		 CalculAnimaux(agri); //calcule la tva recue et versee
		 for(int n=0;n<N_X;n++)
		 resultat->Produit[n]+=resultat->VenteAni[n]- resultat->AchatAni[n];
		 //creance et dette initiale calcule date paiement et tva
		 TotalEnCours(agri);        //180102
		 */
	}
	/*
	 TotalValeur(agri->V_Charges, resultat->V_Charge,
	 resultat->Charge,  resultat->V_CatChargeTot,
	 resultat->Tva->Verse,
	 an);
	 */
//mettre tendance
	/*
	 TotalValeur(agri->V_ChStruct,resultat->V_ChStruct,
	 resultat->ChStruct,resultat->V_CatChStructTot,
	 resultat->Tva->Verse,
	 an);
	 */
	/*
	 TotalValeur(agri->V_RecDiv, resultat->V_RecDiv,
	 resultat->RecDiv,resultat->V_CatRecDivTot,
	 resultat->Tva->Recu,
	 an);
	 */
	/*
	 TotalValeur(agri->V_DepDiv,resultat->V_DepDiv,
	 resultat->DepDiv,resultat->V_CatDepDivTot,
	 resultat->Tva->Verse,
	 an);
	 */
	/*
	 TotalValeur(agri->V_RecFam,resultat->V_RecFam,
	 resultat->RecFam,resultat->V_CatRecFamTot,
	 NULL,
	 an);
	 */
	TotalValeur(agri->V_DepFam,resultat->V_DepFam,
			resultat->DepFam,resultat->V_CatDepFamTot,
			NULL,
			an);

	// tva sur immo                                      191201
	// cf AgriSaisieTotal TotalImmo  a fait les totaux
	resultat->Tva->Verse[an] +=resultat->ImmoTotal->TvaVersee[an];
	resultat->Tva->Recu[an] +=resultat->ImmoTotal->TvaRecue[an];

	CalculTva(agri->TvaEntIni,resultat->Tva);// 191201

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
	// pour retirer ce qui correspond à des productions qui n'existent plus
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
void __fastcall TAgriSaisieFrm::TotalValeurProduction( CL_Agriculteur *agri,int an)
{
	int i,n;
	CL_Item *item;
	CL_QuanVal *quanVal,*quanValTot;
	float tauxTva;
	CL_Vecteur<CL_Formule>*vFormule;
	CL_Vecteur<CL_QuanVal>*vProduit;
	float *total;
	CL_Vecteur<CL_QuanVal>*vCatTot;
	float *totTva;

	if(an!=0) return;
	//calcul en une fois
	//  a revoir pour pouvoir utiliser regle concernant modif assolement

	vFormule=agri->V_Produits;
	vProduit=agri->Resultat->V_Produit;
	total=agri->Resultat->Produit;
	vCatTot=agri->Resultat->V_CatProduitTot;
	totTva=agri->Resultat->Tva->Recu;

	//mettre item->Flag='N'
	V_Produit->FlagMisA('N');
	for(i=0;i<vProduit->Nbelt;i++)
	{
		quanVal=vProduit->Vecteur[i];
		memset(quanVal->Val,0,sizeof(float)*N_X);
		memset(quanVal->Stock,0,sizeof(float)*(N_X+1));
	}

	//Stock/commercialisation
	if(agri->LstQuantPrix && agri->LstQuantPrix->Count>0)
	TotVProdComm(vProduit);

	//Stock/politique de stockage
	if(agri->V_PolStock->Nbelt >0)
	TotVProdPolStock(vProduit);

	//a partir de vFormule calcul quanVal->Val
	// + stock/stock initial      quanVal et quanVal->Stock
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

	CalculAnimaux(agri); //calcule la tva recue et versee
	for(n=0;n<N_X;n++)
	agri->Resultat->Produit[n]+=agri->Resultat->VenteAni[n]-agri->Resultat->AchatAni[n];
	//creance et dette initiale calcule date paiement et tva
	TotalEnCours(agri);//180102

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
	Agri->LstQuantPrix->Pack();
	for(i=0;i<Agri-> LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix==NULL) continue;

		item=quantPrix->Item;
		// pour ne pas calculer 3 fois  ici TotVFormule TotVProdPolStock
		item->Flag='O';
		if(item!=item0)
		{
			//quanVal=TrouveQuanVal(vProduit,item);  //test
			for(n=0;n<N_X*2;n++) prixRevient[n]= item->Prix;//provisoire

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
		// si a été produit avant le début de la simulation
		//évaluer valeur des stocks initiaux
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
		if(anComm>=an_0 && (anComm-an_0)<N_X)
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
			if(prog->Arbre==NULL) continue; //271004
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
		CL_Vecteur<CL_QuanVal>*vCatTot,float *totTva,
		int an)
{
	int i;
	CL_Formule *formule;
	CL_Item *item;
	CL_QuanVal *quanVal,*quanValTot;
//CL_Prog *prog;
	float tauxTva;
//	memset(	total,0,sizeof(float)*N_X);
	for(i=0;i<vFormule->Nbelt;i++)
	{
		formule=vFormule->Vecteur[i];
		/*
		 prog=formule->LesProg[an];
		 if(prog==NULL) continue;
		 if(prog->Arbre==NULL) continue; //220603
		 if(prog->Arbre->ContientIndic()==true)
		 Compil->Calculer(prog->Reseau,prog->Arbre,an,an+1,formule->Valeur);
		 */
		item=formule->Item;
		if(item==NULL) continue; //060508 access
		item->Categorie->Flag='O';//pour simplifier edition

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
		total[an] +=formule->Valeur[an];
		quanVal->Val[an] +=formule->Valeur[an];
		quanValTot->Val[an]+=formule->Valeur[an];
		if(totTva!=NULL)
		totTva[an] +=formule->Valeur[an]*tauxTva;
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

	//Production/animaux
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

	//Production/Troupeaux
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
			tauxTva=animal->Tva->Taux/100.; //210705.
			for(n=0;n<N_X+1;n++)//260903
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

	if(totTva > 0) acompte=totTva/5;//280805
	else acompte=0;

	regul = totTva
	-tvaIni->AcompteMai
	-tvaIni->AcompteAout
	-tvaIni->AcompteNov
	-tvaIni->AcompteFev;
	n=0;
	tva->AcompteFev[0]=tvaIni->AcompteFev;

	tva->AcompteMai[n]= acompte;
	tva->AcompteAout[n]= acompte;
	tva->AcompteNov[n]= acompte;
	tva->AcompteFev[n+1]= acompte;

	if(regul<0)
	{
		tva->RembTva[n]=-regul;
		//tva->Solde[n]  =-regul +3*acompte;
	}
	else
	{
		tva->Regul[n]= regul;
		//tva->Solde[n]  = regul +3*acompte;
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
		{
			tva->RembTva[n] =-regul;
			tva->Regul[n]= 0;
		}
		else
		{
			tva->RembTva[n] =0; //280805
			tva->Regul[n]= regul;
		}

		//tva->Solde[n]= regul+ tva->AcompteFev[n]+tva->AcompteMai[n]
		//                + tva->AcompteAout[n]+tva->AcompteNov[n];
	}
//    si tva->Solde >0 c'est à payer  si <0  à recevoir
// j'harmonise les >0 sont des sorties les <0 sont des rentrées
//    for(n=0;n<N_X;n++) tva->Solde[n]*=-1;
//    for(n=0;n<N_X;n++) tva->Solde[n]+=tva->Recu[n]-tva->Verse[n];
	for(n=0;n<N_X;n++)
	{
		tva->Solde[n]= tva->Recu[n]
		-tva->Verse[n]
		-tva->AcompteFev[n]
		-tva->Regul[n]
		+tva->RembTva[n]
		-tva->AcompteMai[n]
		-tva->AcompteAout[n]
		-tva->AcompteNov[n];
	}

}

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculTreso(CL_Agriculteur *agri, int n)
{
	CL_AgriRes *resultat=agri->Resultat;

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
//                            + resultat->PlactE->Interet[n]

	+ resultat->TotSub->Valeur[n]
	// stocks enCours
	+resultat->Creance->Flux[n]
	-resultat->Dette->Flux[n]

	+ resultat->Tva->Solde[n];

	resultat->TresoIni=agri->TresoIni;
	// pour permettre conversion qui ne convertit que resultat
	resultat->SoldeCumul[0]=resultat->TresoIni+resultat->Solde[0];
	if(n==0) return;

	for(int i=1;i<n+1;i++)
	{
		if(i>=N_X) break;
		resultat->SoldeCumul[i]= resultat->SoldeCumul[i-1]
		+ resultat->Solde[i];
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculIndicateur(int n)
{
	int i;
	CL_Indicateur *indic;
	for(i=0;i<V_Indicateur->Nbelt;i++)
	{
		indic=V_Indicateur->Vecteur[i];
		if(indic->Flag==true) continue;
		Compil->JeTraite=indic->Nom;
		Compil->Calculer(indic->Prog->Reseau,indic->Prog->Arbre,n,n+1,indic->Valeur);

	}
}

// A VOIR
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FaireCompta(CL_AgriRes *resultat, int an)
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
		resultat->detteTva[0]=0; //230905
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

