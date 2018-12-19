//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Forme01.h"

#include "AgriSaisie.h"
#include "Brouillon.h"

#include "InvAni.h"
#include "CL_MvtAnnee.h"

#include "MvtAni.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMvtAniFrm *MvtAniFrm;
/*
 A chaque cellule de la grille Inventaire
 est accrochée une classe CL_MvtAnnee
 qui contient les mouvements de l'année


 AU DEPART RIEN
 entrer  def animaux mettre a NULL les objets de la ligne
 inventaire
 creer mvtAn de N=0 avec Debut=
 choix animal
 afficher les grilles
 si mvtAn=NULL le creer

 aprés Ok
 mettre dans LstMvtAni
 DeGrMvtEntree
 Sortie
 Achat
 Vente
 pb pour ne et mort
 pour l'année N
 appeler mouvt(N)
 qui cree si necessaire mvtAn et informe Debut pour an suivant

 */

//---------------------------------------------------------------------------
__fastcall TMvtAniFrm::TMvtAniFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::FormCreate(TObject *Sender)
{

	GrMvt->Cells[0][0]="Début";
	GrMvt->Cells[0][1]="Vente";
	GrMvt->Cells[0][2]="Achat";
	GrMvt->Cells[0][3]="Né";
	GrMvt->Cells[0][4]="Mort";
	GrMvt->Cells[0][5]="Entrée";
	GrMvt->Cells[0][6]="Sortie";
	GrMvt->Cells[0][7]="Fin";

}
//---------------------------------------------------------------------------
/*
 c=5 correspond à An_0
 Vente achat mort in out sont les mouvements de l'année n  il y a N_X
 Effectif[n] effectif à la fin de l'année n  il y en a N_X+1
 Effectif[0] effectif au début de la simulation fin de An_0-1
 */
/// affiche la fenetre Mouvement
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::FormActivate(TObject *Sender)
{
	int c,r;
	int an;
	CL_MvtAnnee *mvtAnnee;
	CL_Item *animal;
	CL_InvAni *invAni;
	//repredre paramètres de InvAni
	An_0=InvAniFrm->An_0;
	GrilleInv=InvAniFrm->GrilleInv;
	Agri=InvAniFrm->Agri;

	r=GrilleInv->Row;
	c=GrilleInv->Col;

	InvAni=(CL_InvAni*)InvAniFrm->GrilleInv->Objects[0][r];
	N=c-5;//si c=5 je suis en début de la simulation:An_0 N=0
	an=An_0+N;
	LabNom->Caption=InvAni->Animal->Nom+ " "+an;

	MvtAnnee=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
	AffMvtAnnee(MvtAnnee);

}
//---------------------------------------------------------------------------
/*
 BtBnOKClick
 BtBnAnnulClick
 */
/// dans grille Mouvement
/// reprend le contenu des sous grilles vente achat etc aprés verif
///  et le met dans MvtAnnee (attaché à la cellule)
/// remplit grille de gauche (synthèse)
/// dans la grille inventaire
/// met dans la cellule à gauche( l'année d'après) l'effectif
/// MaJMvtAnnee
/// MvtAnnee est global et defini dans BtBnOKClick
/// pour tous les mouvements on connait effectif destination
///   ->rechercher et mettre à jour les mvtAnne
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::BtBnOKClick(TObject *Sender)
{
	int col;
	int r;
	int dest,orig;
//int entree,sortie,effVente,effAchat;
	int i,j;
	float valVente,valAchat;
	int effVente,effAchat;
	int effFin,effSortie;
//bool sortieTout[3],entreeTout[3];
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee;

	if(LabMvtModif->Visible==false) return;
	InvAniFrm->Erreur=false;

	InvAniFrm->LabelModifie->Visible=true;

	// la  nouvelle information est dans GrilleMvt: je mets à zero MvtAnnee
	//pour verifier l'existence de prix
	// voir si controle à faire dans GrMvtClick
	GrMvtClick(this);

	effSortie= GrMvt->Cells[1][6].ToIntDef(0);
	effFin= GrMvt->Cells[1][7].ToIntDef(0);

	if(effFin<0 ||effSortie<0)
	{
		ShowMessage("IMPOSSIBLE Effectif négatif");
		InvAniFrm->Erreur=true;
	}
	if(InvAniFrm->Erreur==true) return;

	InvAniFrm->Erreur=false;
	if(N+1>=N_X) return;

	/// de cette categorie des effectifs sont partis ailleurs
	/// j'annule ce qui est lié à ce MvtAni
	/// je mets a jour

	col=N+5;
	MaZMvtAnnee(col);
	MaJMvtAnnee(col);

	InvAniFrm->Simuler();
	InvAniFrm->AffEffectifs();
}

//---------------------------------------------------------------------------/*
//---------------------------------------------------------------------------
/*
 MaZMvtAnnee
 MaJMvtAnnee
 */
// effacer tous les mvts entrainés par l'animal
/// on travaille sur MvtAnnee global
//     et sur InvAni->NoAnimal
/// on a fait des modif dans les grilles de mouvement
/// j'annule ce qui est lié à ce MvtAni
/// je le recreerai + tard avec MajMvtAnnee
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::MaZMvtAnnee(int col)
{
	int r,i,j,rNais;
	CL_MvtAnnee *mvt,*mvtNaissance;
	int noAnimal=InvAni->NoAnimal;
	float pcent;
	int n;
	double ne;

	// effacer tous les mvts entrainés par l'animal
//    MvtAnnee->Maz();
	for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
	{
		mvt=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][r];
		if(mvt==NULL) continue;
		if(mvt==MvtAnnee) continue;
		// annuler les sorties vers MvtAnnee qui vient d'être modifié
		for(i=0;i<mvt->iDest;i++)
		{
			if(mvt->Destin[i]==noAnimal)
			{
				if(mvt->SortieTout[i]==true)
				{
					mvt->Sortie[i]=0;
					break;
				}
				//j<2  car Sortie de j+1 et Sortie[3]
				for(j=i;j<2;j++ )
				mvt->Sortie[j]=mvt->Sortie[j+1];
				mvt->Sortie[2]=0;
				mvt->iDest--;
				break;
			}
		}
		// annuler les entrées en provenance deMvtAnnee qui vient d'être modifié
		for(i=0;i<mvt->iOr;i++)
		{
			if(mvt->Origine[i]==noAnimal)
			{
				if(mvt->EntreeTout[i]==true)
				{
					mvt->Entree[i]=0;
					break;
				}
				//j<2  car Entree de j+1 et Entree[3]
				for(j=i;j<2;j++ )
				mvt->Entree[j]=mvt->Entree[j+1];
				mvt->Entree[2]=0;
				mvt->iOr--;
				break;
			}
		}
		if(mvt->ADescendance==false) continue;
		for(i=0;i<4;i++)
		{
			pcent=mvt->DonnePcent[i];
			if(pcent==0) continue;
			n=mvt->DonneNo[i];
			ne=mvt->Debut* pcent; //voir si Debut ou Fin
			ne=ceil(ne);
			//rNais=InvAniFrm->TrouverLigne(n);
			mvtNaissance=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][n];
			mvtNaissance->Ne-=ne;
		}
	}
}
//---------------------------------------------------------------------------
// MvtAnnee est celui sur lequel on a fait des modif
//  il est visible=global
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::MaJMvtAnnee(int col)
{
	int r,i,j;
	int noDestin,noOrigine;
	int eff;
	CL_MvtAnnee *mvtDest,*mvtOrigine,*mvtNaissance;
	int noAnimal=InvAni->NoAnimal;
	bool aJour;
	float pcent;
	int rNais;
	int n;
	double ne;

	// Destination
	for(i=0;i<MvtAnnee->iDest;i++)
	{
		aJour=false;
		noDestin=MvtAnnee->Destin[i];

		eff= MvtAnnee->Sortie[i]; //pb ad lib

		r=InvAniFrm->TrouverLigne(noDestin);
		mvtDest=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][r];

		if(mvtDest->iOr==0)
		{
			mvtDest->Origine[0]=noAnimal;
			mvtDest->Entree[0]= eff;
			if(MvtAnnee->SortieTout[i]==true) mvtDest->EntreeTout[0]=true;
			mvtDest->iOr++;
		}
		else
		{
			for(j=0;j<mvtDest->iOr;j++)
			{
				if(mvtDest->Origine[j]==noAnimal)
				{
					mvtDest->Entree[j] +=eff;
					if(MvtAnnee->SortieTout[i]==true) mvtDest->EntreeTout[j]=true;
					aJour=true;
					break;
				}
			}
			if(aJour==false)
			{
				j=mvtDest->iOr;
				mvtDest->Origine[j]=noAnimal;
				mvtDest->Entree[j]= eff;
				if(MvtAnnee->SortieTout[i]==true) mvtDest->EntreeTout[j]=true;
				mvtDest->iOr++;
			}
		}
	}

	// Origine
	for(i=0;i<MvtAnnee->iOr;i++)
	{
		aJour=false;
		noOrigine=MvtAnnee->Origine[i];
		eff= MvtAnnee->Entree[i]; //pb ad lib

		r=InvAniFrm->TrouverLigne(noOrigine);
		mvtOrigine=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][r];

		if(mvtOrigine->iDest==0)
		{
			mvtOrigine->Destin[0]=noAnimal;
			mvtOrigine->Sortie[0]= eff;
			if(MvtAnnee->EntreeTout[i]==true) mvtOrigine->SortieTout[0]=true;
			mvtOrigine->iDest++;
		}
		else
		{
			for(j=0;j<mvtOrigine->iDest;j++)
			{
				if(mvtOrigine->Destin[j]==noAnimal)
				{
					mvtOrigine->Sortie[j] +=eff;
					if(MvtAnnee->EntreeTout[i]==true) mvtOrigine->SortieTout[j]=true;
					aJour=true;
					break;
				}
			}
			if(aJour==false)
			{
				j=mvtOrigine->iDest;
				mvtOrigine->Destin[j]=noAnimal;
				mvtOrigine->Sortie[j]= eff;
				if(MvtAnnee->EntreeTout[i]==true) mvtOrigine->SortieTout[j]=true;
				mvtOrigine->iDest++;
			}
		}
	}

	// Naissance
	if(MvtAnnee->ADescendance==false) return;
	for(i=0;i<4;i++)
	{
		pcent=MvtAnnee->DonnePcent[i];
		if(pcent==0) continue;
		n=MvtAnnee->DonneNo[i];
		ne=MvtAnnee->Debut* pcent; //voir si Debut ou Fin
		ne=ceil(ne);
//        rNais=InvAniFrm->TrouverLigne(n);
//        mvtNaissance=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][rNais];
		mvtNaissance=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][n];
		mvtNaissance->Ne+=ne;
	}

}
// pour test de verif
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::ImpMvt(void)
{
	int n;
	CL_MvtAni *mvtAni;
	char chaine[100];

	FBrouillon->Demarre();

	FBrouillon->Memo1->DefAttributes->Name= "Courier";
	FBrouillon->Memo1->DefAttributes->Size= 12; //size1;//12;
	FBrouillon->Memo1->DefAttributes->Color= clBlack;

	for(n=0;n<Agri->LstMvtAni->Count;n++)
	{
		mvtAni=(CL_MvtAni*)Agri->LstMvtAni->Items[n];
		switch(mvtAni->Type)
		{
			case VENTE:
			sprintf(chaine,"%2d  %2d   VENTE    %2d  %2d  %6.0f",
					n,mvtAni->NoAnimal,mvtAni->Date,mvtAni->Eff,mvtAni->Info);
			FBrouillon->Memo1->Lines->Add(chaine);
			break;
			case ACHAT:
			sprintf(chaine,"%2d %2d   ACHAT     %2d  %2d  %6.0f",
					n,mvtAni->NoAnimal,mvtAni->Date,mvtAni->Eff,mvtAni->Info);
			FBrouillon->Memo1->Lines->Add(chaine);
			break;
			case MORT:
			sprintf(chaine,"%2d  %2d  MORT      %2d  %2d  %2d",
					n,mvtAni->NoAnimal,mvtAni->Date,mvtAni->Eff,mvtAni->Info);
			FBrouillon->Memo1->Lines->Add(chaine);
			break;
			case NE:
			sprintf(chaine,"%2d  %2d   NE       %2d  %2d  %2d",
					n,mvtAni->NoAnimal,mvtAni->Date,mvtAni->Eff,mvtAni->Info);
			FBrouillon->Memo1->Lines->Add(chaine);
			break;
			case MVT: //animal vient de MvtAni->Info
			sprintf(chaine,"%2d  %2d  MVT       %2d  %2d  %2d",
					n,mvtAni->NoAnimal,mvtAni->Date,mvtAni->Eff,(int)mvtAni->Info);
			FBrouillon->Memo1->Lines->Add(chaine);
			break;
		}
	}
	FBrouillon->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                              POUBELLE

/*
 traite les mvts de l'année d'apres

 */
/*
 //---------------------------------------------------------------------------
 void   __fastcall TMvtAniFrm::FaitEvoluer(int r0)
 {
 int noAnimal;
 //int col;
 int n0;
 CL_MvtAnnee *mvtAnnee1;

 if(N+1==N_X) return;
 //    col=N+5;
 noAnimal=InvAniFrm->TrouverNoAnimal(r0);
 if(noAnimal==-1) return;

 n0=N;
 for(;N<N_X-1;N++)
 {
 ActualiseEntree(1);
 ActualiseSortie(1);
 ActualiseSuite();
 }
 N=n0;

 }
 //---------------------------------------------------------------------------
 void   __fastcall TMvtAniFrm::ActualiseEntree(int r0)
 {
 int col,r,rOr,rDest;
 int i;
 int noAnimal;
 int noOrigine;
 int eff;
 CL_MvtAnnee *mvtAnnee0, *mvtAnnee1;
 CL_MvtAnnee *mvtOr0, *mvtOr1;
 //CL_MvtAnnee *mvtDest1;

 CL_InvAni *invAni;

 col=N+5;
 noAnimal=InvAniFrm->TrouverNoAnimal(r0);
 if(noAnimal==-1) return;

 // eff debut de l'annee N+1= effectif fin de l'annee N
 mvtAnnee0=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][r0];
 mvtAnnee1=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col+1][r0];
 mvtAnnee1->Maz();
 mvtAnnee1->Debut=mvtAnnee0->Fin;
 //Origine
 for(i=0;i<mvtAnnee0->iOr;i++)
 {
 mvtAnnee1->Origine[i]=mvtAnnee0->Origine[i];
 rOr=InvAniFrm->TrouverLigne(mvtAnnee1->Origine[i]);
 ActualiseEntree(rOr);
 mvtOr1=InvAniFrm->TrouverMvt(mvtAnnee1->Origine[i],col+1);


 //        if(mvtAnnee1->EntreeTout[i]==true)
 if(mvtOr1->Debut==0) break;

 mvtAnnee1->Origine[i]=mvtAnnee0->Origine[i];
 mvtAnnee1->Entree[i] =mvtOr1->Debut;
 mvtAnnee1->iOr++;

 mvtOr1->iDest=1; //!!!!!!
 mvtOr1->Destin[0]=noAnimal;
 mvtOr1->Sortie[0]=mvtOr1->Debut;
 mvtOr1->Solde();
 }
 mvtAnnee1->Solde();
 }
 //---------------------------------------------------------------------------
 void   __fastcall TMvtAniFrm::ActualiseSortie(int r0)
 {
 int col,r,rOr;
 int i;
 int noAnimal;
 int noOrigine;
 int eff;
 CL_MvtAnnee *mvtAnnee0, *mvtAnnee1;
 CL_MvtAnnee *mvtDest0,*mvtDest1;
 int rDest;
 CL_InvAni *invAni;
 if(N+1==N_X) return;

 col=N+5;
 noAnimal=InvAniFrm->TrouverNoAnimal(r0);
 if(noAnimal==-1) return;

 // eff debut de l'annee N+1= effectif fin de l'annee N
 mvtAnnee0=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][r0];
 mvtAnnee1=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col+1][r0];

 //Destination
 for(i=0;i<mvtAnnee0->iDest;i++)
 {
 mvtAnnee1->Destin[i]=mvtAnnee0->Destin[i];
 rDest=InvAniFrm->TrouverLigne(mvtAnnee1->Destin[i]);
 //        ActualiseSortie(rDest);
 mvtDest1=InvAniFrm->TrouverMvt(mvtAnnee1->Destin[i],col+1);
 mvtDest0=InvAniFrm->TrouverMvt(mvtAnnee1->Destin[i],col);
 mvtDest1->Maz();
 mvtDest1->Debut=mvtDest0->Fin;

 //        if(mvtAnnee1->EntreeTout[i]==true)
 if(mvtAnnee1->Debut==0) break;
 mvtAnnee1->Sortie[i] =mvtAnnee1->Debut;
 mvtDest1->iOr=1; //!!!!!!
 mvtDest1->Origine[0]=noAnimal;
 mvtDest1->Entree[0]= mvtAnnee1->Debut;
 mvtDest1->Solde();
 //            InvAniFrm->GrilleInv->Cells[col+1][rDest]=IntToStr(mvtDest1->Fin);
 mvtAnnee1->iDest++;
 ActualiseSortie(rDest);
 //        else
 //            ShowMessage("Actualise tout");
 }


 mvtAnnee1->Solde();
 //    InvAniFrm->GrilleInv->Cells[col+1][r0]=IntToStr(mvtAnnee1->Fin);
 }
 //---------------------------------------------------------------------------
 void   __fastcall TMvtAniFrm::ActualiseSuite(void)
 {
 int col,r,rOr,rDest;
 int i;
 int noAnimal;
 int noOrigine;
 int eff;
 CL_MvtAnnee *mvtAnnee0, *mvtAnnee1;
 //CL_MvtAnnee *mvtDest1;

 CL_InvAni *invAni;
 if(N==N_X-1) return;
 col=N+5;
 for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
 {
 mvtAnnee0=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col][r];
 if(mvtAnnee0==NULL) continue;
 if(mvtAnnee0->Fin >0) continue;

 mvtAnnee1=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[col+1][r];
 if(mvtAnnee1==NULL) continue;
 mvtAnnee1->Debut=0;
 mvtAnnee1->Solde();
 //        InvAniFrm->GrilleInv->Cells[col][r]=IntToStr(mvtAnnee1->Fin);

 }
 }
 //---------------------------------------------------------------------------
 void __fastcall TMvtAniFrm::MetDansEntree(CL_MvtAnnee *mvtAnnee,int noOrigine,int eff,bool tout)
 {
 int i;
 if(mvtAnnee->iOr==0)
 {
 mvtAnnee->iOr=1;
 mvtAnnee->Origine[0]=noOrigine;
 mvtAnnee->Entree[0]=eff;
 return;
 }
 for(i=0;i<mvtAnnee->iOr;i++)
 {
 if(mvtAnnee->Origine[i]==noOrigine)
 {
 mvtAnnee->Entree[i]+=eff;
 return;
 }
 }
 i=mvtAnnee->iOr;
 mvtAnnee->iOr++;
 mvtAnnee->Origine[i]=noOrigine;
 mvtAnnee->Entree[i]=eff;
 }
 */

