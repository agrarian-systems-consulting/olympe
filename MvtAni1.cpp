//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Forme01.h"

#include "AgriSaisie.h"
//#include "LBMvtAni.h"
//#include "Brouillon.h"
#include "CL_MvtAnnee.h"
#include "InvAni.h"

#include "MvtAni.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//  Mouvement
//       il y a grille à gauche de synthese  Grille
//       elle contient des grilles à droite  SGVente...
//           pour les ventes les achats les mvt
/// remplit la fenetre mouvement
/// fait les calculs d'effectif fin
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::AffMvtAnnee(CL_MvtAnnee *mvtAnnee)
{
	CL_MvtAni *mvtAni;
	CL_MvtAnnee *mvtAnneeOrigine;
	int i,iDest;
	int j;
	int effFin,entree,sortie,vente,achat;
	float valVente,valAchat;
	/// Grille à gauche
	/// SG... a droite
	GrMvt->EditorMode=true;
	SGVente->EditorMode=true;
	SGAchat->EditorMode=true;
	SGEntree->EditorMode=true;
	SGSortie->EditorMode=true;

	LabMvtModif->Visible=false;

	LabVenteModif->Visible=false;
	LabAchatModif->Visible=false;
	LabSortieModif->Visible=false;
	LabEntreeModif->Visible=false;

	VideGrille(SGVente);
	VideGrille(SGAchat);
	VideGrille(SGEntree);
	VideGrille(SGSortie);

//    Debut=effDeb;
//    GrMvt->Cells[1][0]=effDeb;
	GrMvt->Cells[1][0]=mvtAnnee->Debut;

	//Vente
	vente=0;
	for(i=0;i<mvtAnnee->iVente;i++)
	{
		SGVente->Cells[i][0]= mvtAnnee->Vente[i];
		SGVente->Cells[i][1]= mvtAnnee->PrixVente[i];
		vente+=mvtAnnee->Vente[i];
	}
	GrMvt->Cells[1][1]=vente;

	//Achat
	achat=0;
	for(i=0;i<mvtAnnee->iAchat;i++)
	{
		SGAchat->Cells[i][0]= mvtAnnee->Achat[i];
		SGAchat->Cells[i][1]= mvtAnnee->PrixAchat[i];
		achat+=mvtAnnee->Achat[i];
	}
	GrMvt->Cells[1][2]=achat;

	//Naissance
	GrMvt->Cells[1][3]= mvtAnnee->Ne;

	//Mort
	GrMvt->Cells[1][4]= mvtAnnee->Mort;

	//Entree
	entree=0;
	for(i=0;i<mvtAnnee->iOr;i++)
	{
		SGEntree->Cells[i][0]= mvtAnnee->Entree[i];
		j=InvAniFrm->TrouverLigne(mvtAnnee->Origine[i]);
		SGEntree->Cells[i][1]=j;
		entree+=mvtAnnee->Entree[i];
	}
	GrMvt->Cells[1][5]=entree;

	//Sortie
	sortie=0;
	for(i=0;i<mvtAnnee->iDest;i++)
	{
		SGSortie->Cells[i][0]= mvtAnnee->Sortie[i];
		j=InvAniFrm->TrouverLigne(mvtAnnee->Destin[i]);
		SGSortie->Cells[i][1]= j;
		sortie+=mvtAnnee->Sortie[i];
	}
	GrMvt->Cells[1][6]=sortie;

	mvtAnnee->Fin=mvtAnnee->Debut+entree-sortie+achat-vente+mvtAnnee->Ne-mvtAnnee->Mort;

	GrMvt->Cells[1][7]=mvtAnnee->Fin;
//    GrilleClick(this);  //pour calculer effFin
}

//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::VideGrille(TStringGrid *grille)
{
	int c,r;
	for(c=0;c<3;c++)
	{
		for(r=0;r<2;r++)
		{
			grille->Cells[c][r]="";
			grille->Objects[c][r]=NULL;
		}
	}
}
//---------------------------------------------------------------------------
//  choix des animaux destination ou origine ??
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::LBAnimauxClick(TObject *Sender)
{
	int n;
	int c;
	if(GrilleEnCours==NULL) return;
	c=GrilleEnCours->Col;
	n=LBAnimaux->ItemIndex+1;
	GrilleEnCours->Cells[c][1]=n;

}
/*
 GrilleKeyPress
 GrilleClick
 GrilleSelectCell
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::GrMvtKeyPress(TObject *Sender, char &Key)
{
//Entree Sortie est calculé
	switch(GrMvt->Row)
	{
		case 0:
		case 1:Key=0;SGVente->SetFocus(); return;
		case 2:Key=0;SGAchat->SetFocus(); return;
		case 5:Key=0;SGEntree->SetFocus();return;
		case 6:Key=0;SGSortie->SetFocus();return;
		case 7:Key=0;return;
	}
	if(Key >='0' && Key <='9') {LabMvtModif->Visible=true; return;}
	if(Key==VK_BACK) {LabMvtModif->Visible=true; return;}

	Key=0;
}
/// click sur grille gauche calcule l'effectif total
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::GrMvtClick(TObject *Sender)
{
	int dest,orig;
	int entree,sortie,dispo,effVente,effAchat;
	int i,j;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee;

	if(LabMvtModif->Visible==false) return;
	// la  nouvelle information est dans GrilleMvt: je mets à zero MvtAnnee
	MvtAnnee->Maz();

	///reprend ce qui est dans les grille de droite en faisant total
	DeSGVente(effVente);
	DeSGAchat(effAchat);
	if(DeSGEntree(entree)==false) return;
	if(DeSGSortie(sortie)==false) return;
	// tient compte du mvt automatique vers cat suivante
	// il existe dans la grille
	// il faudra le calculer et le réafficher

	/// pas de total à faire
	MvtAnnee->Ne= GrMvt->Cells[1][3].ToIntDef(0);
	MvtAnnee->Mort= GrMvt->Cells[1][4].ToIntDef(0);

	// ce qui passe dans cat suivante
	if(MvtAnnee->SortieTout[0]==true)
	{
		dispo=MvtAnnee->Dispo();
		SGSortie->Cells[0][0]=dispo;
		DeSGSortie(sortie);
	}

	/// calcule le nombre d'animaux compte tenu des mouvements
	MvtAnnee->Solde();
	/// Reaffiche  Grille Sortie

	VideGrille(SGSortie);
	sortie=0;
	for(i=0;i<MvtAnnee->iDest;i++)
	{
		SGSortie->Cells[i][0]= MvtAnnee->Sortie[i];
		j=InvAniFrm->TrouverLigne(MvtAnnee->Destin[i]);
		SGSortie->Cells[i][1]= j;
		sortie+=MvtAnnee->Sortie[i];
	}

	GrMvt->Cells[1][1]=IntToStr(effVente);
	GrMvt->Cells[1][2]=IntToStr(effAchat);
	GrMvt->Cells[1][5]=IntToStr(entree);
	GrMvt->Cells[1][6]=IntToStr(sortie);
	GrMvt->Cells[1][7]=IntToStr(MvtAnnee->Fin);

}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::GrMvtSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect)
{
	if(ACol==0) CanSelect=false;
	if(ARow==0) CanSelect=false;
}

//---------------------------------------------------------------------------
/*
 SGKeyDown
 SGKeyPress
 SGExit
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::SGKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	TLabel *lab;
	if (Sender==SGVente) lab=LabVenteModif;
	else if(Sender==SGAchat) lab=LabAchatModif;
	else if(Sender==SGEntree) lab=LabEntreeModif;
	else if(Sender==SGSortie) lab=LabSortieModif;
	if(Key==VK_DELETE) {lab->Visible=true;return;}
//
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::SGKeyPress(TObject *Sender, char &Key)
{
	TLabel *lab;
	if (Sender==SGVente) lab=LabVenteModif;
	else if(Sender==SGAchat) lab=LabAchatModif;
	else if(Sender==SGEntree) lab=LabEntreeModif;
	else if(Sender==SGSortie) lab=LabSortieModif;
	if(Key >='0' && Key <='9') {lab->Visible=true;return;}
	if(Key==VK_BACK) return;
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::SGExit(TObject *Sender)
{
	int c;
	int eff;
	int tot;
	int row=5;
	TStringGrid *grille;
	TLabel *lab;
	if(Sender==SGVente)
	{
		row=1;
		grille=SGVente;
		lab=LabVente;
	}
	else if(Sender==SGAchat)
	{
		row=2;
		grille=SGAchat;
		lab=LabAchat;
	}
	else if(Sender==SGEntree)
	{
		row=5;
		grille=SGEntree;
		lab=LabEntree;
	}
	else if(Sender==SGSortie)
	{
		row=6;
		grille=SGSortie;
		lab=LabSortie;
	}

	if(lab->Visible==false) return;
	LabMvtModif->Visible=true;
	tot=0;
	for(c=0;c<3;c++)
	{
		eff= grille->Cells[c][0].ToIntDef(0);
		tot+=eff;
	}
	GrMvt->Cells[1][row]=IntToStr(tot);
	GrMvtClick(this);
}
//---------------------------------------------------------------------------
/*
 DeSGVente
 DeSGAchat
 DeSGEntree
 DeSGSortie
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::DeSGVente(int &total)
{
	int r,c;
	int i;
	int eff;
	int prix;
	total=0;
//    if(LabVenteModif->Visible==false) return true;
	MvtAnnee->iVente=0;
	for(c=0;c<3;c++)
	{
		eff= SGVente->Cells[c][0].ToIntDef(0);
		if( eff==0 ) continue;
		prix= SGVente->Cells[c][1].ToIntDef(-999); ///!!
		if( prix==-999) prix=0;
		i=MvtAnnee->iVente++;
		MvtAnnee->Vente[i]=eff;
		MvtAnnee->PrixVente[i]=prix;
		total+=eff;
	}
}
/*
 if(total >  MvtAnnee->Debut)
 {
 GrMvt->Cells[1][6]="?";
 GrMvt->Cells[1][7]="?";

 ShowMessage("Animaux vendus  >effectif Debut");
 return false;
 }
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::DeSGAchat(int &total)
{
	int r,c;
	int i;
	int eff;
	int prix;
	bool correct;
//    row=2;
	total=0;
//    if(LabAchatModif->Visible==false) return true;

	MvtAnnee->iAchat=0;
	for(c=0;c<3;c++)
	{
		eff= SGAchat->Cells[c][0].ToIntDef(0);
		if( eff==0 ) continue;
		prix= SGAchat->Cells[c][1].ToIntDef(-999); ///!!
		if( prix==-999) prix=0;
		i=MvtAnnee->iAchat++;
		MvtAnnee->Achat[i]=eff;
		MvtAnnee->PrixAchat[i]=prix;
		total+=eff;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TMvtAniFrm::DeSGEntree(int &total)
{
	int r,c;
	int i,j;
	int eff;
	int rOrigine;
	int noDest;
	int col;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee, *mvtOrigine;
//    row=5;
	total=0;
//    if(LabEntreeModif->Visible==false) return true;

	MvtAnnee->iOr=0;
	for(c=0;c<3;c++)
	{
		eff= SGEntree->Cells[c][0].ToIntDef(0);
		if( eff==0 ) continue;
		rOrigine= SGEntree->Cells[c][1].ToIntDef(-999); ///!!
		if( rOrigine==-999)
		{
			ShowMessage("Pas d'origine");
			return false;
		}
		if( rOrigine<1 || rOrigine>GrilleInv->RowCount-3)
		{
			ShowMessage("Origine Inconnue");
			return false;
		}
		if( rOrigine==GrilleInv->Row)
		{
			ShowMessage("On tourne en rond");
			return false;
		}

		i=MvtAnnee->iOr++;
		invAni=(CL_InvAni*)GrilleInv->Objects[0][rOrigine];

		MvtAnnee->Entree[i]=eff;
		MvtAnnee->Origine[i]=invAni->NoAnimal;
		total+=eff;
	}
	/*
	 noDest=InvAni->NoAnimal;
	 col=N+5;
	 mvtOrigine=(CL_MvtAnnee*)GrilleInv->Objects[col][rOrigine];

	 i=mvtOrigine->iDest++;
	 mvtOrigine->Sortie[i]=eff;
	 mvtOrigine->Destin[i]=noDest;
	 }
	 */
	return true;
}
// calcule le total des sorties
//---------------------------------------------------------------------------
bool __fastcall TMvtAniFrm::DeSGSortie(int &total)
{
	int r,c;
	int i,j;
	int eff;
	int rDest;
	int noDest;
	int col;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee, *mvtDest;
	total=0;
	MvtAnnee->iDest=0;
	for(c=0;c<3;c++)
	{
		rDest= SGSortie->Cells[c][1].ToIntDef(-999); ///!!
		if(rDest!=-999) MvtAnnee->iDest++;
	}
	i=0;
	for(c=0;c<3;c++)
	{
		// les effectifs qui vont dans la classe suivante
		// seront calculées par Mvt->Solde()
		if(MvtAnnee->SortieTout[c]==true) {i=0;continue;}

		eff= SGSortie->Cells[c][0].ToIntDef(0);
		if( eff==0 ) continue;
		rDest= SGSortie->Cells[c][1].ToIntDef(-999); ///!!
		if( rDest==-999)
		{
			ShowMessage("Pas de destination");
			return false;
		}
		if( rDest<1 || rDest>GrilleInv->RowCount-3)
		{
			ShowMessage("Destination Inconnue");
			return false;
		}
		if( rDest==GrilleInv->Row)
		{
			ShowMessage("On tourne en rond");
			return false;
		}

		//i=MvtAnnee->iDest++;
		i++;
		invAni=(CL_InvAni*)GrilleInv->Objects[0][rDest];

		MvtAnnee->Sortie[i]=eff;
		MvtAnnee->Destin[i]=invAni->NoAnimal;
		total+=eff;

		/*
		 noDest=InvAni->NoAnimal;
		 col=N+5;
		 mvtDest=(CL_MvtAnnee*)GrilleInv->Objects[col][rDest];
		 i=mvtDest->iOr++;
		 mvtDest->Entree[i]=  eff;
		 mvtDest->Origine[i]= noDest;
		 */
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::SGEntreeEnter(TObject *Sender)
{
	GrilleEnCours=SGEntree;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::SGSortieEnter(TObject *Sender)
{
	GrilleEnCours=SGSortie;
}
//---------------------------------------------------------------------------
//
//           POUBELLE
//
/*
 //---------------------------------------------------------------------------
 //  Tous les animaux de la catégorie sont transférés
 //---------------------------------------------------------------------------
 void __fastcall TMvtAniFrm::BtBnToutClick(TObject *Sender)
 {
 int n,c,a;
 int eff;
 CL_InvAni *origine,*enCours;//080802
 CL_MvtAnnee *mvtAnnee;
 mvtAnnee=MvtAnnee;
 if(GrilleEnCours==NULL) return;
 c=GrilleEnCours->Col;
 //les animaux sont affichés à partir de ligne 1
 n=LB->ItemIndex+1;
 if(n<1) return;
 //
 if(GrilleEnCours==SGEntree)    //080702
 {
 origine=(CL_InvAni*)AgriSaisieFrm->LaGrille->Objects[0][n];
 SGEntree->Cells[c][1]=n;
 SGEntree->Cells[c][0]=origine->Effectif[N];
 MvtAniFrm->SGExit(SGEntree);
 }
 //
 if(GrilleEnCours==SGEntree)    //080702
 {
 origine=(CL_InvAni*)AgriSaisieFrm->LaGrille->Objects[0][n];
 SGEntree->Cells[c][1]=n;

 for(int i=0;i<3;i++)   mvtAnnee->EntreeTout[i]=false;
 mvtAnnee->EntreeTout[c]=true;

 eff=origine->Effectif[N];
 for(int i=0;i<3;i++)
 {
 a=SGEntree->Cells[i][0].ToIntDef(-999);
 if(a==-999) continue;
 if(mvtAnnee->EntreeTout[i]==false)
 eff-=a;
 }
 SGEntree->Cells[c][0]=origine->Effectif[N];
 MvtAniFrm->SGExit(SGEntree);
 }

 if(GrilleEnCours==SGSortie)
 {
 enCours=(CL_InvAni*)AgriSaisieFrm->LaGrille->Objects[0][GrilleInv->Row];
 SGSortie->Cells[c][1]=n;
 //noter la catégorie où vont tous les anx disponibles
 for(int i=0;i<3;i++)   mvtAnnee->SortieTout[i]=false;
 mvtAnnee->SortieTout[c]=true;

 eff=enCours->Effectif[N];
 for(int i=0;i<3;i++)
 {
 a=SGSortie->Cells[i][0].ToIntDef(-999);
 if(a==-999) continue;
 if(mvtAnnee->SortieTout[i]==false)
 eff-=a;
 }
 SGSortie->Cells[c][0]=eff;
 MvtAniFrm->SGExit(SGSortie);
 }
 }
 */
