//---------------------------------------------------------------------------

#include <math.h>
#pragma hdrstop
#include "CL_MvtAnnee.h"
#include "MvtAnnee.h"

#include "Troupeau.h"
//#include "TroupeauMvt.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
/// accroche à chaque cellule un CL_MvtAnnee
/// pour stocker les mouvements
/// dans premier temps ils sont vides

//  appelle Filiation
//  	complète mvtAnnee de chaque cellule
//		en indiquant origine destination: vient de, va vers
// appelle RemplitLesMvtAnnee
//      complète mvtAnnee de chaque cellule
//		en introduisant les ventes achats entres sorties...
//      à partir des mvtAni de LstMvtAni
//
//-----------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrilleMvt(TStringGrid *grille)
{
	int row,r,nbelt,col;
	int i,j;
	int repMB;
	bool rep;
	AnsiString value,s;
	CL_InvAni *invAni,*invAni2;
	CL_Item *animal;
//CL_Categorie *catBestiaux;
	CL_MvtAnnee *mvtAnnee;
	CL_Vecteur<CL_InvAni> *v_InvAni;
	TList *lstInvAni;
	bool chgtOrdre;
	int nouveauR[50];
	CL_MvtAni*mvtAni;
	lstInvAni=new TList;

	v_InvAni=TroupeauEnCours->V_InvAni;
	nbelt=v_InvAni->Nbelt;
	GrilleMvt->RowCount=nbelt+1;
//test
//ImpMvt();
//test à supprimer
	/*
	 for( r=0;r<v_InvAni->Nbelt;r++)
	 {
	 invAni=v_InvAni->Vecteur[r];
	 }
	 */
	//Lb pour choisir
	MvtAnneeFrm->LBAnimaux->Clear();

	/// accroche à chaque cellule un CL_MvtAnnee
	/// pour stocker les mouvements
	/// à ce moment ils sont vides

	//classer les invani dans le meme ordre que le mvt cf DefBestiaux
	//
	// on peut avoir modifié l'ordre et le n° des lignes a de l'importance
//    invAni=v_InvAni->Vecteur[0];
//    animal=invAni->Animal;
//    catBestiaux=animal->Categorie;
	for(i=0;i<V_Bestiaux->Nbelt;i++)
	{
		animal=V_Bestiaux->Vecteur[i];
		for(j=0;j<v_InvAni->Nbelt;j++)
		{
			invAni=v_InvAni->Vecteur[j];
			if(invAni->NoAnimal==animal->No)
			{
				lstInvAni->Add(invAni);
				break;
			}
		}
	}

	// a-t-on changé l'ordre ?
	chgtOrdre=false;
	for(i=0;i<lstInvAni->Count;i++)
	{
		invAni=(CL_InvAni*)lstInvAni->Items[i];
		invAni2=v_InvAni->Vecteur[i];
		if(invAni->NoAnimal!=invAni2->NoAnimal)
		{
			chgtOrdre=true;
			break;
		}
	}

	if(chgtOrdre==true)
	{
		for(i=0;i<v_InvAni->Nbelt;i++)
		{
			invAni2=v_InvAni->Vecteur[i];
			for(j=0;j<lstInvAni->Count;j++)
			{
				invAni=(CL_InvAni*)lstInvAni->Items[j];
				if(invAni2->NoAnimal==invAni->NoAnimal)
				{
					nouveauR[i+1]=j+1;
					break;
				}
			}
		}
		/* pour test
		 for(i=0;i<v_InvAni->Nbelt;i++)
		 {
		 invAni2=v_InvAni->Vecteur[i];
		 animal=invAni2->Animal;
		 s=AnsiString(i+1)+"  "+AnsiString(nouveauR[i]+1)+"  "+animal->Nom;
		 }
		 */

		v_InvAni->vide();
		for(i=0;i<lstInvAni->Count;i++)
		{
			invAni=(CL_InvAni*)lstInvAni->Items[i];
			v_InvAni->insSans(invAni);
		}
		for(i=0;i<TroupeauEnCours->LstMvtAni->Count;i++)
		{
			mvtAni=(CL_MvtAni*)TroupeauEnCours->LstMvtAni->Items[i];
			//r=mvtAni->NoAnimal;
			mvtAni->Ligne=nouveauR[mvtAni->Ligne];
			if(mvtAni->Type==MVT)
			mvtAni->Info=nouveauR[(int)mvtAni->Info];
		}
		/*
		 TroupeauEnCours->VideLstMvtAni();
		 EffaceVente();
		 Simuler();
		 AffEffectifs();
		 */
	}

//	for( r=0;r<nbelt;r++)
	for( r=0;r<v_InvAni->Nbelt;r++)
	{
		row=r+1;
		invAni=v_InvAni->Vecteur[r];
		invAni->Flag='O';
//		animal=invAni->Animal;
		if(animal==NULL) continue;

		s=AnsiString(row)+"  "+invAni->Animal->Nom;
		MvtAnneeFrm->LBAnimaux->Items->Add(s);

		GrilleMvt->Objects[0][row]=(TObject*)invAni;
		GrilleMvt->Cells[0][row]=row;
		GrilleMvt->Cells[1][row]=invAni->Animal->Nom;

		GrilleMvt->Cells[2][row]=Aff(invAni->Effectif[0]);
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvtAnnee=new CL_MvtAnnee();
			GrilleMvt->Objects[col][row]=(TObject*)mvtAnnee;
		}
	}
	// complete mvtannee
	Filiation();

	//pour chaque cellule de la grille informe mvtAnnee
	//à partir de LstMvtAni  stocké dans fichier
	switch(RGCouS->ItemIndex)//simuler ou effectifsconstants
	{
		case 0:

		rep=RemplitLesMvtAnnee();
		//si problème a retourné false: signaler pb et refaire les calculs
		if(rep==false)
		{
			TroupeauEnCours->VideLstMvtAni();
			repMB=MessageBox(Handle,"A simuler ?","Problème sur les Données",
					MB_YESNO|MB_ICONEXCLAMATION);
			if(repMB==IDNO)break;
			EffaceVente();
			Simuler();
			AffEffectifs();
			ShowMessage("Simulation  REFAITE");
			LabelModifie->Visible=true;
			break;
		}
		else
		{
			Simuler();
			AffEffectifs();
		}
		break;
		case 1:
		EffConstant();
		break;
	}

}
//---------------------------------------------------------------------------
// rustine je mets à zero toutes les ventes
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::EffaceVente(void)
{
	int r,i;
	int col;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvt;
	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			mvt->iVente=0;
			for(i=0;i<3;i++)
			{
				mvt->Vente[i]=0;
				mvt->PrixVente[i]=0;
			}
		}
	}
}
//---------------------------------------------------------------------------
/// complete mvtAnnee de chaque cellule
//		en indiquant origine destination: vient de, va vers
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::Filiation(void)
{
	int col,r;
	int n;
	float tot;
	CL_InvAni *invAni;
	CL_Item *animal;
	CL_MvtAnnee *mvt;

	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;

		animal=invAni->Animal;
		if(animal->NoOrigine >=0)
		{

			// NoOrigine est le no ligne dans la saisie NomAnimaux

			//Origine
			for(col=Col0;col<GrilleMvt->ColCount;col++)
			{
				mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
				mvt->iOr=1;
				mvt->Origine[0]=animal->NoOrigine;
				mvt->EntreeTout[0]=true;
			}

			//Destination
			// pour l'origine indiquer destination
			for(col=Col0;col<GrilleMvt->ColCount;col++)
			{
				mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][animal->NoOrigine];
				mvt->iDest=1;
				mvt->Destin[0]=r;
				mvt->SortieTout[0]=true;
			}
		}

		//Descendance
		for(n=0,tot=0;n<4;n++)
		tot+=animal->DonnePcent[n];
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			if(tot)
			{
				mvt->ADescendance=true;
				for(n=0;n<4;n++)
				{
					mvt->DonnePcent[n]=animal->DonnePcent[n]/100.;
					mvt->DonneNo[n] =animal->DonneNo[n];
				}
			}
			else
			mvt->ADescendance=false;
		}
		// si a des descendants
	}
}
//... pour test
/*
 col=col0;
 for(r=1;r<GrilleMvt->RowCount;r++)
 mvtDest=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
 */

//------------------------------------------------------------------------------
/// complete mvtAnnee à partir de Agri->LstMvtAni
/// c'est une TList contenant des mvtAni
/// est lue /sera envoyée sur fichier
///class CL_MvtAni
///{
///    ...
///    int NoAnimal;
///    int Type;    VENTE ACHAT MORT NE MVT
///    int Date;
///    int Eff;
///    float Info; contient Prix(float) ou Origine(int)
///};
//Complète MvtAnnee de chaque cellule de la grille a partir des mvtAni
// envisage erreurs mvt iDest >3 ou iOr >3
// dans ce cas s'arrete et signale qu'il faut refaire les calculs
//---------------------------------------------------------------------------
bool __fastcall TTroupeauFrm::RemplitLesMvtAnnee(void)
{
	CL_MvtAni *mvtAni;
	CL_MvtAnnee *mvt,*mvtDest;
	int col,r;
	int i,noDest;
	int n;
	bool trouve;

//    n=TroupeauEnCours->LstMvtAni->Count;
//!!!!!!  test
//    EcritLstMvtAni(TroupeauEnCours->LstMvtAni);
//return true;;

	for(n=0;n<LstAchat->Count;n++)
	{
		mvtAni=(CL_MvtAni*)LstAchat->Items[n];
		if(mvtAni->Eff==0) continue; //en principe immpossible mais !?

		col=mvtAni->Date+Col0;
		r=mvtAni->Ligne;
		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
		if(mvt==NULL) return false;
		i=mvt->iAchat++;
		if(i>2) {mvt->iAchat--;return false;}

		mvt->Achat[i]= mvtAni->Eff;
		mvt->PrixAchat[i]= mvtAni->Info;
	}

	// on est passé par filiation
	for(n=0;n<TroupeauEnCours->LstMvtAni->Count;n++)
	{
		mvtAni=(CL_MvtAni*)TroupeauEnCours->LstMvtAni->Items[n];
		if(mvtAni->Eff==0) continue; //en principe immpossible mais !?

		col=mvtAni->Date+Col0;
		r=mvtAni->Ligne;
		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
		if(mvt==NULL) return false;
		switch(mvtAni->Type)
		{
			case VENTE: //vente pour reguler taille troupeau  100304
			if(mvt->iRegul==-1)
			i=mvt->iVente++;//!!!!!!!
			else
			i=mvt->iRegul;
			if(i>2) return false;
			mvt->Vente[i]= mvtAni->Eff;
			mvt->PrixVente[i]= mvtAni->Info;
			mvt->iRegul=i;
			break;

			case VDECIS://vente définie par l'utilisateur  100304
			/*
			 i=mvt->iVente++;
			 if(i>3) return false;
			 mvt->Vente[i]=      mvtAni->Eff;
			 mvt->PrixVente[i]=  mvtAni->Info;
			 */
			break;

			case ACHAT:
			i=mvt->iAchat++; //!!!!!!!
			if(i>2) return false;
			mvt->Achat[i]= mvtAni->Eff;
			mvt->PrixAchat[i]= mvtAni->Info;
			break;
			case MORT:
			mvt->Mort= mvtAni->Eff;
			break;
			case NE:
			mvt->Ne= mvtAni->Eff;
			break;
			// seult les sorties ont ete stockées
			// donc générer les entrées
			case MVT://animal va vers  MvtAni->Info
			noDest=(int)mvtAni->Info;
			//mvtDest=TrouverMvt(noDest,col);
			mvtDest=(CL_MvtAnnee*)GrilleMvt->Objects[col][noDest];
			if(mvtDest==NULL) return false;
			trouve=false;
			// sortie
			for(i=0;i<mvt->iDest;i++)
			{
				if(mvt->Destin[i]==noDest)
				{
					mvt->Sortie[i]+=mvtAni->Eff;
					trouve=true;
					break;
				}
			}
			if(trouve==false)
			{
				i=mvt->iDest++; //!!!!!!!
				if(mvt->iDest>2)return false;
				mvt->Sortie[i]=mvtAni->Eff;
				mvt->Destin[i]=noDest;
			}
			//entree
			for(i=0;i<mvtDest->iOr;i++)
			{
				if(mvtDest->Origine[i]==mvtAni->Ligne)
				{
					mvtDest->Entree[i]+=mvtAni->Eff;
					trouve=true;
					break;
				}
			}
			if(trouve==false)
			{
				i=mvtDest->iOr++; //!!!!!!!
				if(mvtDest->iOr>2)return false;
				mvtDest->Entree[i]=mvtAni->Eff;
				mvtDest->Origine[i]=mvtAni->Ligne;
			}
			break;
		}
	}
	/*
	 CL_MvtAnnee *mvtAnnee;
	 for(r=1;r<GrilleMvt->RowCount;r++)
	 {
	 for(col=Col0;col<GrilleMvt->ColCount;col++)
	 {
	 mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[Col0][r];
	 if(mvtAnnee->iVente >1
	 ||mvtAnnee->iDest >1
	 ||mvtAnnee->iOr >1 )
	 ShowMessage("pbtroupeuMvt");
	 }
	 }
	 */
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::SansSimuler(void)
{
	int r,c;
	CL_MvtAnnee *mvt,*mvt0,*mvt1;

	//pour la première année de simulation
	// initie mvt->Debut à l'effectif initial défini par l'utisateur
	// il est dans la colonne col0-1 =2

	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		if(GrilleMvt->Objects[0][r]==NULL) continue;

		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[Col0][r];
		mvt->Debut=GrilleInt(Col0-1,r);
		mvt->Solde();
	}

	//mvt mouvement d'une catégorie à une autre
	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
//        if(c==GrilleMvt->ColCount-1) return;
//         voir si modif nécessaire dans Simuler

		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;

			mvt0=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			mvt0->Solde();
			if(c<GrilleMvt->ColCount-1)
			{
				mvt1=(CL_MvtAnnee*)GrilleMvt->Objects[c+1][r];
				mvt1->Debut=mvt0->Fin;
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::AffEffectifs(void)
{
	int r,col;
	CL_MvtAnnee *mvtAnnee;
	for(col=Col0;col<GrilleMvt->ColCount;col++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			if(mvtAnnee->Fin)
			GrilleMvt->Cells[col][r]=Aff(mvtAnnee->Fin);
			else
			GrilleMvt->Cells[col][r]="  ";
		}
	}
}
//-----------------------------------------------------------------------------
//    mouvement des animaux
//    soit
//			effConstant
//          simuler
//-----------------------------------------------------------------------------
// Recopie de l'inventaire initial
// aucun mouvement n'est effectué
// utile pour troupeu stationnaire ->fournit elt bilan ceg
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::EffConstant(void)
{
	int r,c;
	int i;
	CL_InvAni *invAni;
	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;

		invAni->Effectif[0]=GrilleInt(Col0-1,r);
		for(c=Col0,i=1;c<GrilleMvt->ColCount;c++,i++)
		{
			invAni->Effectif[i]= invAni->Effectif[0];
			if(invAni->Effectif[i])
			GrilleMvt->Cells[c][r]=Aff(invAni->Effectif[i]);
			else
			GrilleMvt->Cells[c][r]="  ";
		}
	}
}
//---------------------------------------------------------------------------
// pour chaque animal informe mvtAnnee->Debut
//        de la première année de simulation
//        c'est l'inventaire initial
//pour chaque annee
//	pour chaque catégorie d'animal
//		recherche les catégories qui l'alimentent
//			pour chacune de ces catégories
//             calcule :mvtOr->Dispo() ie:
//	           Debut-mort-toutes les ventes -sorties fixées par l'utilisateur
//	pour chaque catégorie d'animal
//      calcule :mvt->Solde
//       vente achat quantités valeurs..
//
//	pour chaque catégorie d'animal
//		effectifs début de l'année suivante=effectif fin de l'année
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::Simuler(void)
{
	int r,c;
	int i;
	int noOr;
	int n;
	CL_MvtAnnee *mvt,*mvtOr,*mvt1,*mvtNaissance; //,*mvtTest;
	CL_InvAni *invAni;
	double ne;
	//pour la première année de simulation
	// initie mvt->Debut à l'effectif initial défini par l'utisateur
	// il est dans la colonne 4

	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		if(GrilleMvt->Objects[0][r]==NULL) continue;

		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[Col0][r];
		mvt->Debut=GrilleInt(Col0-1,r);
	}

	// maz
	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;
			// mouvement d'une catégorie à une autre
			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			if(mvt->iRegul!=-1)mvt->Vente[mvt->iRegul]=0;
			mvt->Ne=0;
		}
	}

	//mvt mouvement d'une catégorie à une autre et naissance
	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;
			// mouvement d'une catégorie à une autre
			invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			for(i=0;i<mvt->iOr;i++)
			{
				noOr=mvt->Origine[i];
				//++mvtOr=TrouverMvt(noOr,c);
				mvtOr=(CL_MvtAnnee*)GrilleMvt->Objects[c][noOr];
				mvt->Entree[i]=mvtOr->Dispo(r);
//                mvt->Entree[i]=mvtOr->Dispo(invAni->NoAnimal);
			}
			// Naissance
			if(mvt->ADescendance==false) continue;
			for(i=0;i<4;i++)
			{
				if (mvt->DonnePcent[i]==0.)continue;
				n=mvt->DonneNo[i];
				//++mvtNaissance=TrouverMvt(n,c);
				mvtNaissance=(CL_MvtAnnee*)GrilleMvt->Objects[c][n];
				ne=mvt->Debut* mvt->DonnePcent[i];//voir si Debut ou Fin
				ne=ceil(ne);
				mvtNaissance->Ne+=ne;
			}

		}
		// effectifs fin d'année
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;
			invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];

			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];

			mvt->Solde();
			if(invAni->EffMax[c-Col0]!=SANSBORNE)
			{
				if(mvt->Fin > invAni->EffMax[c-Col0])
				{
					if(mvt->iRegul==-1)
					{
						i=mvt->iVente;
						mvt->iRegul=i;
						mvt->iVente++;
					}
					else
					i=mvt->iRegul;
					mvt->Vente[i]=mvt->Fin- invAni->EffMax[c-Col0];
					mvt->PrixVente[i]=invAni->PrixVenteMoy[c-Col0];
					mvt->Fin-=mvt->Vente[i];
				}
			}
			else
			mvt->iRegul=-1;

			// effectifs debut annee suivante =eff fin annee précedente
			if(c<GrilleMvt->ColCount-1)
			{
				mvt1=(CL_MvtAnnee*)GrilleMvt->Objects[c+1][r];
				mvt1->Debut=mvt->Fin;
			}

		}
	}
	CompleteInvAni(); //211003
	/* test
	 for(r=1;r<GrilleMvt->RowCount;r++)
	 {
	 invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
	 }
	 //fin test
	 */
}

//---------------------------------------------------------------------------
//                BOUTONS
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::RGCouSClick(TObject *Sender)
{
	switch(RGCouS->ItemIndex)
	{
		case 0:
		RemplitLesMvtAnnee();
		Simuler();
		AffEffectifs();
		break;
		case 1:
		EffConstant();
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnSimulerClick(TObject *Sender)
{
	if(RGCouS->ItemIndex==0)
	{
		MazTout();
		//VersGrilleMvt(GrilleMvt);//181004
		Simuler();
		AffEffectifs();
		CreeLstMvtAni();
	}
	else
	EffConstant();

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::MazTout(void)
{
	int col;
	AnsiString value,s;
	CL_MvtAnnee *mvtAnnee;

	LabelModifie->Visible=true;
	Erreur=false;
	for(int r=1;r<GrilleMvt->RowCount;r++)
	for(int c=Col0;c<GrilleMvt->ColCount;c++)
	GrilleMvt->Cells[c][r]="";

	for(int r=1;r<GrilleMvt->RowCount;r++)
	{
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			if(mvtAnnee==NULL) continue;

			mvtAnnee->Maz();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnMazClick(TObject *Sender)
{
	int col;
	AnsiString value,s;
	CL_MvtAnnee *mvtAnnee;

	LabelModifie->Visible=true;
	Erreur=false;
	for(int r=1;r<GrilleMvt->RowCount;r++)
	for(int c=Col0;c<GrilleMvt->ColCount;c++)
	GrilleMvt->Cells[c][r]="";

	for(int r=1;r<GrilleMvt->RowCount;r++)
	{
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
			if(mvtAnnee==NULL) continue;

			mvtAnnee->Maz();
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                 chercher dans Grille
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
 int __fastcall TTroupeauFrm::TrouverLigne(int noAnimal)
 {
 int r;
 CL_InvAni  *invAni;
 for(r=1;r<GrilleMvt->RowCount;r++)
 {
 invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
 if(invAni==NULL) continue;
 if(invAni->Animal->No==noAnimal) return r;
 }
 return 999;      //aew
 }
 */

//---------------------------------------------------------------------------
/*
 CL_MvtAnnee* __fastcall TTroupeauFrm::TrouverMvt(int noAnimal,int c)
 {
 int row;
 CL_MvtAnnee *mvt;
 row=TrouverLigne(noAnimal);
 mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][row];
 return mvt;
 }
 */
//---------------------------------------------------------------------------

