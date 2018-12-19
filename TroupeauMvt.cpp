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
			mvtAnnee->Animal=invAni->Animal; //111107 ?
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
/*
 //pour chaque cellule de la grille informe mvtAnnee
 //à partir de LstMvtAni  stocké dans fichier
 switch(RGCouS->ItemIndex)         //simuler ou effectifsconstants
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
 */
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
	CL_Bestiaux *animal;
	CL_MvtAnnee *mvt;

	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;

		animal=invAni->Animal;
		/*
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
		 */
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
	CL_InvAni *invAni;
	int col,r;
	int i,noDest;
	int n;
	bool trouve;

	// on est passé par filiation
	for(n=0;n<TroupeauEnCours->LstMvtAni->Count;n++)
	{
		mvtAni=(CL_MvtAni*)TroupeauEnCours->LstMvtAni->Items[n];
		if(mvtAni->Eff==0) continue; //en principe impossible mais !?

		col=mvtAni->Date+Col0;
		r=mvtAni->Ligne;
		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];
		if(mvt==NULL) return false;

		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		mvt->Animal=invAni->Animal;
		switch(mvtAni->Type)
		{
			case VENTE: //vente pour reguler taille troupeau  100304
			i=mvt->DonneiRegul();
			mvt->Vente[i]= mvtAni->Eff;
			mvt->PrixVente[i]= mvtAni->Info;
			break;

			case VDECIS://vente définie par l'utilisateur  100304
			i=mvt->iVente++;
			if(i>2) {mvt->iVente--;break;} // impossible!!!???               mvt->Vente[i]=      mvtAni->Eff;
			mvt->Vente[i]= mvtAni->Eff;
			mvt->PrixVente[i]= mvtAni->Info;
			break;

			case ACHAT:// achats décidés par l'utilisateur
			i=mvt->iAchat++;
			if(i>2) {mvt->iAchat--;break;} // impossible!!!???
			mvt->Achat[i]= mvtAni->Eff;
			mvt->PrixAchat[i]= mvtAni->Info;
			break;

			case AACHETER://achats automatiques
			i=mvt->DonneiAchatAuto();
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
			//        trouver ligne
			//        incrementer Entree
			case MVT://animal va vers  ligne :mvtAni->Info mvtDest
			noDest=(int)mvtAni->Info;
			mvtDest=(CL_MvtAnnee*)GrilleMvt->Objects[col][noDest];
			if(mvtDest==NULL) break;

			//j'ai trouvé mvtDest modifier mvt->Destin et mvt->Sortie
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
				i=mvt->iDest++;
				if(mvt->iDest>2) {mvt->iDest--;break;} // impossible!!??

				mvt->Sortie[i]=mvtAni->Eff;
				mvt->Destin[i]=noDest;
			}

			//entree
			trouve=false;
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
				i=mvtDest->iOr++;
				if(mvtDest->iOr>2) {mvt->iOr--;break;} // impossible!!??

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
	int i,iO,iD,iV;
	int noOr,noDest;
	int n;
	CL_MvtAnnee *mvt,*mvtOr,*mvtSuite,*mvtNaissance,*mvtDest,*mvtTest;
	CL_InvAni *invAni;
	double ne;
	float prixMoy;
//CL_MvtAnnee *mvt1,*mvt4;
//pour test
//ofstream outfile("mvtAnnee.txt");

	//pour la première année de simulation
	// initie mvt->Debut à l'effectif initial défini par l'utisateur
	// il est dans la colonne 2   Col0=3

//effectifs début simul
	mvtTest=(CL_MvtAnnee*)GrilleMvt->Objects[Col0][1];
	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		if(GrilleMvt->Objects[0][r]==NULL) continue;
		mvt=(CL_MvtAnnee*)GrilleMvt->Objects[Col0][r];
		mvt->Debut=GrilleInt(Col0-1,r);
	}

	// je mets à zero les ventes effectuées pour respecter contrainte de taille
	//                les naissances qui seront recalculées
	//                les achats  automatiques (ils ont pu changer)
	//mvt->iRegul=-1   si pas de régulation
	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;
			// mouvement d'une catégorie à une autre
			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			// ventes regulation   et achat auto
			// en fait je garde tout ce qui a été decidé par l'utilisateur
			i=mvt->iRegul; if(i>=0)mvt->Vente[i]=0;
			i=mvt->iAchatAuto; if(i>=0)mvt->Achat[i]=0;
			mvt->Ne=0;
		}
	}

	// les achats automatiques  définis par l'utilisateur dans SGAchat
	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;
		for(n=0;n<N_X;n++)
		{
			if(invAni->AAcheter[n]>0 ||invAni->PrixAchat[n]>0)
			{
				c=n+3; //???
				mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
				i=mvt->DonneiAchatAuto();
				mvt->Achat[i]=invAni->AAcheter[n];
				mvt->PrixAchat[i]=invAni->PrixAchat[n];
				mvt->iAchatAuto=i;
			}
		}
	}

	//Effacer les mouvements d'une catégorie à l'autre par vieillissement
	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;

			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			noOr=mvt->Animal->NoOrigine;
			if(noOr==-1) continue; // veaux

			mvtOr=(CL_MvtAnnee*)GrilleMvt->Objects[c][noOr];
			for(i=0;i<mvtOr->iDest;i++)
			{
				if(mvtOr->Destin[i]==r)
				{
					mvtOr->Sortie[i]=0;
					//break;
				}
			}
		}
	}

	// Les passages décidés
	//test

	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;

			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			for(i=0;i<mvt->iDest;i++)
			{
				if(mvt->Sortie[i]!=0)
				{
					noDest=mvt->Destin[i];
					mvtDest=(CL_MvtAnnee*)GrilleMvt->Objects[c][noDest];
					iD=TrouveColDest(r,mvtDest);
					mvtDest->Entree[iD]=mvt->Sortie[i];
					mvtDest->Origine[iD]=r;
				}
			}
		}
	}

	for(c=Col0;c<GrilleMvt->ColCount;c++)
	{
		//mvt mouvement d'une catégorie à une autre et naissance
		// vieillissement:mouvement d'une catégorie à une autre
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			if(GrilleMvt->Objects[0][r]==NULL) continue;

			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			noOr=mvt->Animal->NoOrigine;
			if(noOr!=-1) // noOr=-1 pour les veaux
			{
				mvtOr=(CL_MvtAnnee*)GrilleMvt->Objects[c][noOr];
				//trouver
				iO=TrouveColOrigine(r,mvtOr);
				iD=TrouveColDest(noOr,mvt);

				mvt->Entree[iD]=mvtOr->Dispo(r);//Fin;//230108Dispo(r); // Dispo(n ) n non utilisé
				mvt->Origine[iD]=noOr;
				mvtOr->Sortie[iO]=mvt->Entree[iD];
				mvtOr->Destin[iO]=r;
			}
			// Naissance
			if(mvt->ADescendance==true)
			{
				for(i=0;i<4;i++)
				{
					if (mvt->DonnePcent[i]==0.)continue;
					n=mvt->DonneNo[i];
					mvtNaissance=(CL_MvtAnnee*)GrilleMvt->Objects[c][n];
					ne=mvt->Debut* mvt->DonnePcent[i]; //voir si Debut ou Fin
					ne=ceil(ne);
					mvtNaissance->Ne+=ne;
				}
			}
		}
		// effectifs fin d'année
		for(r=1;r<GrilleMvt->RowCount;r++)
		{
			invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];

			mvt=(CL_MvtAnnee*)GrilleMvt->Objects[c][r];
			mvt->Solde();
			mvt->iRegul=-1; //120108
			// ne pas dépasser le maxi défini
			if(invAni->EffMax[c-Col0]!=SANSBORNE)
			{
				if(mvt->Fin > invAni->EffMax[c-Col0])
				{
					prixMoy=invAni->PrixVenteMoy[c-Col0];
					iV=TrouveColVente(mvt,prixMoy);
					//i=0;//mvt->DonneiRegul();
					mvt->Vente[iV]=mvt->Fin- invAni->EffMax[c-Col0];
					mvt->PrixVente[iV]=invAni->PrixVenteMoy[c-Col0];
					mvt->Fin-=mvt->Vente[iV];
					mvt->iRegul=iV;
				}
			}

			// effectifs debut annee suivante =eff fin annee précedente
			if(c<GrilleMvt->ColCount-1)
			{
				mvtSuite=(CL_MvtAnnee*)GrilleMvt->Objects[c+1][r];
				mvtSuite->Debut=mvt->Fin;
			}
			//mvt->Lister(outfile);
		}
	}
	CompleteInvAni(); //211003
//    outfile.close();
	/* test
	 for(r=1;r<GrilleMvt->RowCount;r++)
	 {
	 invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
	 }
	 //fin test
	 */
}
//---------------------------------------------------------------------------
//TrouveCol...

//---------------------------------------------------------------------------
int TTroupeauFrm::TrouveColOrigine(int noDest, CL_MvtAnnee *mvtOr) {
	int i;

	if (mvtOr->iDest == 0) {
		mvtOr->Destin[0] == noDest;
		mvtOr->iDest = 1;
		return 0;
	}
	for (i = 0; i < mvtOr->iDest; i++) {
		if (mvtOr->Destin[i] == noDest)
			return i;
	}
	i = mvtOr->iDest;
	mvtOr->Destin[i] == noDest;
	mvtOr->iDest++;
	if (mvtOr->iDest > 3) {
		ShowMessage("mvtOr->iDest>3");
		mvtOr->Nettoyer("Origine");
		//mvtDest->iOr=3 ;
	}

	return i;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int TTroupeauFrm::TrouveColDest(int noOr, CL_MvtAnnee *mvtDest) {
	int i;

	if (mvtDest->iOr == 0) {
		mvtDest->Origine[0] == noOr;
		mvtDest->iOr = 1;
		return 0;
	}
	for (i = 0; i < mvtDest->iOr; i++) {
		if (mvtDest->Origine[i] == noOr)
			return i;
	}
	i = mvtDest->iOr;
	mvtDest->Origine[i] = noOr;
	mvtDest->iOr++;
	if (mvtDest->iOr > 3) {
		ShowMessage("mvtDest->iOr>3");
		mvtDest->Nettoyer("Dest");
		//mvtDest->iOr=3 ;
	}
	return i;
}
//---------------------------------------------------------------------------
int TTroupeauFrm::TrouveColVente(CL_MvtAnnee *mvt, float prixMoy) {
	int i;
	if (mvt->iVente == 0) {
		mvt->iVente = 1;
		return 0;
	}

	for (i = 0; i < mvt->iVente; i++) {
		if (mvt->PrixVente[i] == prixMoy)
			return i;
	}
	i = mvt->iVente;
	mvt->iVente++;
	if (mvt->iVente > 3) {
		ShowMessage("mvt->iVente>3");
		mvt->Nettoyer("Vente");
	}
	return i;
}

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

