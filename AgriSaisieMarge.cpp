//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"

#include "AgriAtelierMarge.h"
#include "LBMarge.h"
#include "CL_Trad.h"
#include "AgriSaisie.h"
#include "Aide.h"

#include "AgriSaisieMarge.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
extern CL_Trad *T;

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MargeAtelier(void)
{
// 250805
	int i,n;
	CL_Atelier *atelier;
	CL_Vecteur<CL_QuanVal> *V_Produit;
	CL_Vecteur<CL_QuanVal> *V_Charge;
	CL_Vecteur<CL_QuanVal> *V_Exter;

//QUANTITE  en tenant compte des aleas
//calcul pour chaque item quantite[n]
//le met dans un quanval->Qte[n]
//               quanVal->Val et quanVal->Stock sont à zero
//ce quanval est stocké dans V_Produit
//                           V_Charge
//                           V_Externalite
//                           avec pb d'ou séparation à la fin des ext+ et -
// calculs se font à partir de agri->V_Culture
//                                 ->V_Animaux
//                                 ->V_Verger
//                                 ->V_Vivrier

	V_Produit =new CL_Vecteur<CL_QuanVal>();
	V_Charge =new CL_Vecteur<CL_QuanVal>();
	V_Exter =new CL_Vecteur<CL_QuanVal>();
	AgriAtelierMargeFrm->LabNomAtelier->Caption=T->L_Atelier+" : ";//"Les ateliers:";
	// rechercher les ateliers
	n=0;
	for(i=0;i<LBMargeFrm->ChLB->Items->Count;i++)
	{
		if(LBMargeFrm->ChLB->Checked[i]==false) continue;

		atelier=(CL_Atelier*)LBMargeFrm->ChLB->Items->Objects[i];
		if(n==0)
		AgriAtelierMargeFrm->LabNomAtelier->Caption=
		AgriAtelierMargeFrm->LabNomAtelier->Caption+"  "+atelier->Nom;
		else
		AgriAtelierMargeFrm->LabNomAtelier->Caption=
		AgriAtelierMargeFrm->LabNomAtelier->Caption+" + "+atelier->Nom;
		n++;
		switch(atelier->Nature)
		{
			/*
			 case VENTE:             //250805
			 //  bidouille dans AgriAtelierMarge Qte * Prix ->Val
			 for(n=0;n<N_X;n++)
			 quanValVente->Qte[n]=Agri->Resultat->VenteAni[n];
			 V_Produit->insSans(quanValVente);
			 break;
			 case ACHAT:
			 for(n=0;n<N_X;n++)
			 quanValAchat->Qte[n]=Agri->Resultat->AchatAni[n];
			 V_Charge->insSans(quanValAchat);
			 break;
			 */
			case BESTIAUX:
			MargeBestiaux(atelier->Nom,V_Produit,V_Charge);
			break;
			case CULTURE:
			MargeCultAni(atelier,Agri->V_Culture,V_Produit,V_Charge,V_Exter);
			break;
			case ANIMAUX:
			MargeCultAni(atelier,Agri->V_Animaux,V_Produit,V_Charge,V_Exter);
			break;
			case PERENNE:
			MargePerViv(atelier,Agri->V_Verger,V_Produit,V_Charge,V_Exter);
			break;
			case VIVRIER:
			MargePerViv(atelier,Agri->V_Vivrier,V_Produit,V_Charge,V_Exter);
			break;
		}
	}
	// afficher les produits et charges
	// calcul marge

	AgriAtelierMargeFrm->Agri=Agri;
	AgriAtelierMargeFrm->V_Produit=V_Produit;
	AgriAtelierMargeFrm->V_Charge= V_Charge;
	AgriAtelierMargeFrm->V_Exter= V_Exter;
	AgriAtelierMargeFrm->Show();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MargeCultAni(
		CL_Atelier *lAtelier,
		CL_Vecteur<CL_Valeur> *vAtelier,
		CL_Vecteur<CL_QuanVal>*vProduit,
		CL_Vecteur<CL_QuanVal>*vCharge,
		CL_Vecteur<CL_QuanVal>*vExter )
{
	int i;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	for(i=0;i<vAtelier->Nbelt;i++)
	{
		// calculer quanVal->Qte
		valeur=vAtelier->Vecteur[i];
		atelier=valeur->Atelier;
		if(atelier!=lAtelier) continue;

		CalculAtelier (atelier,atelier->V_Produit, vProduit,
				valeur->Valeur, atelier->NbPhase,Agri->DefSim->TQProd);

		CalculAtelier (atelier,atelier->V_Charge, vCharge,
				valeur->Valeur, atelier->NbPhase,Agri->DefSim->TQCharge);

		CalculAtelierVol(atelier,atelier->V_ChargeVolume, vCharge,
				valeur->Valeur, atelier->NbPhase,Agri->DefSim->TQProd,
				Agri->DefSim->TQCharge);

		CalculAtelier (atelier,atelier->V_Externalite, vExter,
				valeur->Valeur, atelier->NbPhase,Agri->DefSim->TQExt);
//        CalculMarge(V_Produit
		/*
		 // calculer quanVal->Valeur
		 for(i=0;i<V_Produit->Nbelt;i++)
		 {
		 quanVal=V_Produit->Vecteur[i];
		 for(n=0;n<N_X;n++)
		 quanVal->Val[n]=quanVal->Qte[n]*quanVal->Item->Prix;// pb alea unite !!
		 }
		 */
	}
}

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MargePerViv(
		CL_Atelier *lAtelier,
		CL_Vecteur<CL_Verger> *vVerger,
		CL_Vecteur<CL_QuanVal>*vProduit,
		CL_Vecteur<CL_QuanVal>*vCharge,
		CL_Vecteur<CL_QuanVal>*vExter )
{
	int i;
	CL_Verger *verger;
	CL_Atelier *atelier;

	for(i=0;i<vVerger->Nbelt;i++)
	{
		// calculer quanVal->Qte
		verger=vVerger->Vecteur[i];

		atelier=verger->Atelier;
		if(atelier!=lAtelier) continue;

		CalculVerger (atelier->V_Produit,vProduit, verger,Agri->DefSim->TQProd);

		CalculVerger (atelier->V_Charge, vCharge, verger,Agri->DefSim->TQCharge);

		CalculVergerVol(atelier->V_ChargeVolume, vCharge,verger,Agri->DefSim->TQProd,
				Agri->DefSim->TQCharge);

		CalculVerger (atelier->V_Externalite, vExter, verger, Agri->DefSim->TQExt);
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MargeBestiaux(AnsiString nom,
		CL_Vecteur<CL_QuanVal>*vProduit,
		CL_Vecteur<CL_QuanVal>*vCharge)
{
	int i,j,n;
	CL_Troupeau *troupeau;
	CL_InvAni *invAni;
	CL_Item *item,*animal;
	for(i=0;i<Agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)Agri->LstTroupeaux->Items[i];
		if(troupeau->CatBestiaux->Nom!=nom) continue;

		CalculProChaDuTroupeau(troupeau,vProduit,vCharge);
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			animal=invAni->Animal;
			item=NULL;
			for(n=0;n<N_X;n++)
			{
				if(invAni->ValVente[n]>0)
				{
					item=new CL_Item();
					item->Nom=animal->Nom;
					item->Prix=1; // les calculs sont déjà faits et tiennent compte de prix /année
					// ne pas les refaire

					MargeBestiaux2(vProduit,invAni->ValVente,item);
					break;
				}
			}
			for(n=0;n<N_X;n++)
			{
				if(invAni->ValAchat[n]>0)
				{
					item=new CL_Item();
					item->Nom=animal->Nom;
					item->Prix=1; // les calculs sont déjà faits et tiennent compte de prix /année
					// ne pas les refaire
					MargeBestiaux2(vCharge,invAni->ValAchat,item);
					break;
				}
			}
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MargeBestiaux2(CL_Vecteur<CL_QuanVal>*vProCha,
		float *valeur,CL_Item *item)
{
	int n;
	CL_QuanVal *quanVal;
	quanVal=new CL_QuanVal();
	quanVal->Item=item;
	for(n=0;n<N_X;n++)
	quanVal->Qte[n]=valeur[n];
	vProCha->ins(quanVal);
}
//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CalculProChaDuTroupeau(CL_Troupeau *troupeau,
		CL_Vecteur<CL_QuanVal> *vProduit,CL_Vecteur<CL_QuanVal> *vCharge)
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

			CalculAtelier (atelier,atelier->V_Produit, vProduit,
					effectif, atelier->NbPhase,Agri->DefSim->TQProd);

			CalculAtelier (atelier,atelier->V_Charge, vCharge,
					effectif, atelier->NbPhase,Agri->DefSim->TQCharge);

			CalculAtelierVol(atelier,atelier->V_ChargeVolume, vCharge,
					effectif, atelier->NbPhase,Agri->DefSim->TQProd,
					Agri->DefSim->TQCharge);
		}
	}
}
//----------------------------------------------------------------------------

