//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
#include "Forme01.h"
#include "AgriSaisieEnum.h"

#include "AgriSaisie.h"
#include "CL_MvtAnnee.h"
#include "MvtAni.h"
#include "Matrice.h"
#include "InvAniMax.h"
#include "InvAniProCha.h"

#include "InvAni.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TInvAniFrm *InvAniFrm;
extern CL_ES *ES;
//---------------------------------------------------------------------------
__fastcall TInvAniFrm::TInvAniFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::FormActivate(TObject *Sender)
{
	if(Origine==1) return;

	Origine =1;

	Agri= AgriSaisieFrm->Agri;
	An_0=Agri->DefSim->An_0;

	Demarrer();

	VersGrilleInvAni();
}
//---------------------------------------------------------------------------
//Demarrer
//		Personnaliser
//		DefinirLesGrilles
//		IniGrille
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::Demarrer(void)
{
	int n;
	CL_Categorie *cat;
	Personnaliser();
	DefinirLesGrilles();
	IniGrille(GrilleInv);
	CBCatAnimaux->Clear();
	CBCatAnimaux->ItemIndex=0;
	for(n=0;n<V_CatBestiaux->Nbelt;n++)
	{
		cat=V_CatBestiaux->Vecteur[n];
		CBCatAnimaux->Items->AddObject(cat->Nom,(TObject*)cat);
		if(cat==Agri->CatBestiaux)CBCatAnimaux->ItemIndex=n;
	}
	CBCatAnimaux->Items->AddObject("[...]",NULL);

	// trouver categorie en cours !!!
	//  elle est lue dans Fichier
	LabelModifie->Visible=false;
	Erreur=false;
}
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::Personnaliser(void)
{
	GrilleInv=Grille0;
//pour ne pas avoir de message de Forme00
}
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::DefinirLesGrilles(void)
{

	AjoutRow=true;
//    GrilleInv->Visible=false;
	GrilleX=1;

	LesGrilles[0]=GrilleInv;
	LaGrille=GrilleInv;
	GrilleInv->Tag=GInvAni;
	GrilleInv->ColCount=15;
	ColM[0]=2;
	RowM[0]=1;
	VideLesGrilles();
}

//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[] = {20,10,128,48,48,48,48,48,48,48,48,48,48,48,48,48};
	// T alpha N numérique 0 non modifiable
	strcpy(TypeCol, "000NN000000000000000000");

	LaGrille->ColCount=15;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);
	LaGrille->Cells[2][0]="NOM";
	LaGrille->Cells[3][0]="Prix Unité";
	LaGrille->Cells[4][0]="Début";

	for(int i=0;i<10;i++)
	LaGrille->Cells[i+5][0]="  "+AnsiString(An_0+i);
}
//---------------------------------------------------------------------------
//SaisirCell
//ControleCell
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::SaisirCell(int col,int row)
{
	if(Erreur==true)
	{
		ShowMessage("Il faut d'abord corriger");
		return;
	}
	if (col==3||col==4)
	{
		CellModifiable(true); //voir Grille00
		CellAVerifier=true;
	}
	else
	{
		CellModifiable(false);
		if(RGCouS->ItemIndex==0)
		MvtAniFrm->Show();
	}

}
//---------------------------------------------------------------------------
bool __fastcall TInvAniFrm::ControleCell(int col,int row)
{
	int digits=0;
	CL_InvAni *invAni;
	invAni=(CL_InvAni*)GrilleInv->Objects[0][row];
	// impossible ???
	if (invAni==NULL) return false;

/// on peut saisir seult en
///  3 val inventaire
///  4 effectif début
	switch(col)
	{
		case 3:
		invAni->ValInv=GrilleFloat(col,row); //2609.3
		ReAffFloat(col,row,digits);
		break;
		case 4:
		invAni->Effectif[0]=GrilleInt(col,row);
		break;
//        default:
//            ShowMessage("Problème dans ControleCellInvAni(");
	}
	return true;
}

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
void __fastcall TInvAniFrm::VersGrilleInvAni(CL_Vecteur<CL_InvAni> *vecteur)
{
	int row,r,nbelt,col;
	AnsiString value,s;
	CL_InvAni *invAni;
	CL_Item *animal;
	CL_MvtAnnee *mvtAnnee;
	//test
//    ImpMvt();
	GrilleInv->RowCount=vecteur->Nbelt+1;
	nbelt=vecteur->Nbelt;

	MvtAniFrm->LBAnimaux->Clear();
	if(Agri->CatBestiaux==NULL) return;//050303
	/// accroche à chaque cellule un CL_MvtAnnee
	/// pour stocker les mouvements
	/// à ce moment ils sont vides
	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		invAni->Flag='O';
		animal=invAni->Animal;
		GrilleInv->Objects[0][row]=(TObject*)invAni;
		GrilleInv->Cells[0][row]=row;

		GrilleInv->Cells[2][row]=animal->Nom;
		s=AnsiString(row)+"  "+animal->Nom;
		MvtAniFrm->LBAnimaux->Items->Add(s);
		GrilleInv->Cells[3][row]=Forme00Frm->Aff(invAni->ValInv,0);
//invAni->Effectif[0]=0; //!!!!!!!!!!!
		GrilleInv->Cells[4][row]=Forme00Frm->Aff(invAni->Effectif[0]);
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			mvtAnnee=new CL_MvtAnnee;
			GrilleInv->Objects[col][row]=(TObject*)mvtAnnee;
		}
	}
	// complete mvtannee
	Filiation();

	//pour chaque cellule de la grille informe mvtAnnee
	//à partir de LstMvtAni  stocké dans fichier
	switch(RGCouS->ItemIndex)
	{
		case 0:
		RemplitLesMvtAnnee();
		SansSimuler();
//            Simuler();
		AffEffectifs();
		break;
		case 1:
		EffConstant();
		break;
	}

}
//---------------------------------------------------------------------------
/// complete mvtAnnee de chaque cellule
//		en indiquant origine destination: vient de, va vers
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::Filiation(void)
{
	int col,r,rOr,lOr;
	int n;
	float tot;
	CL_InvAni *invAni,*invOr;
	CL_Item *animal,*animOr;
	CL_MvtAnnee *mvt;

	for(r=1;r<GrilleInv->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
		if(invAni==NULL) continue;
		animal=invAni->Animal;
		if(animal->NoOrigine==-1) continue;

		// NoOrigine est le no ligne dans la saisie NomAnimaux
		lOr=animal->NoOrigine;
		invOr=(CL_InvAni*)GrilleInv->Objects[0][lOr];
		animOr=invOr->Animal;

		//Origine
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			mvt=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
			mvt->iOr=1;
			mvt->Origine[0]=animOr->No;
			mvt->EntreeTout[0]=true;
		}

		//Destination
		rOr=TrouverLigne(animOr->No);
		if(rOr==999) continue;//aew

		// pour l'origine indiquer destination
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			mvt=(CL_MvtAnnee*)GrilleInv->Objects[col][rOr];
			mvt->iDest=1;
			mvt->Destin[0]=animal->No;
			mvt->SortieTout[0]=true;
		}

		//Descendance
		for(n=0,tot=0;n<4;n++)
		tot+=animal->DonnePcent[n];
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			mvt=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
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
//... pour test
	/*
	 col=5;
	 for(r=1;r<GrilleInv->RowCount;r++)
	 mvtDest=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
	 */
}
//------------------------------------------------------------------------------
/*
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

 Complète MvtAnnee de chaque cellule de la grille a partir des mvtAni
 */
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::RemplitLesMvtAnnee(void)
{
	CL_MvtAni *mvtAni;
	CL_MvtAnnee *mvt,*mvtDest;
	int col;
	int i,noDest;
	int n;
	bool trouve;
	// on est passé par filiation
	for(n=0;n<Agri->LstMvtAni->Count;n++)
	{
		mvtAni=(CL_MvtAni*)Agri->LstMvtAni->Items[n];
		col=mvtAni->Date+5; //5 colonnes pour nom prix etc..
		mvt=TrouverMvt(mvtAni->NoAnimal,col);

		switch(mvtAni->Type)
		{
			case VENTE:
			i=mvt->iVente++;
			mvt->Vente[i]= mvtAni->Eff;
			mvt->PrixVente[i]= mvtAni->Info;
			break;
			case ACHAT:
			i=mvt->iAchat++;
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
			mvtDest=TrouverMvt(noDest,col);
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
				mvt->Sortie[i]=mvtAni->Eff;
				mvt->Destin[i]=noDest;
			}
			//entree
			for(i=0;i<mvtDest->iOr;i++)
			{
				if(mvtDest->Origine[i]==mvtAni->NoAnimal)
				{
					mvtDest->Entree[i]+=mvtAni->Eff;
					trouve=true;
					break;
				}
			}
			if(trouve==false)
			{
				i=mvtDest->iOr++;
				mvtDest->Entree[i]=mvtAni->Eff;
				mvtDest->Origine[i]=mvtAni->NoAnimal;
			}
			break;
		}
	}
}
//---------------------------------------------------------------------------
// Effectifs Constant ou Simulation
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::RGCouSClick(TObject *Sender)
{
// ShowMessage("couS");
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
// Effectifs Constant ou Simulation
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnDemarrerClick(TObject *Sender)
{
	if(RGCouS->ItemIndex==0)
	{
		Simuler();
		AffEffectifs();
	}
	else
	EffConstant();

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
void __fastcall TInvAniFrm::EffConstant(void)
{
	int r,c,c0;
	int i;
	CL_InvAni *invAni;
	c0=4;
	for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
	{
		invAni=(CL_InvAni*)InvAniFrm->GrilleInv->Objects[0][r];
		if(invAni==NULL) continue;

		invAni->Effectif[0]=GrilleInt(c0,r);
		for(c=5,i=1;c<InvAniFrm->GrilleInv->ColCount;c++,i++)
		{
			invAni->Effectif[i]= invAni->Effectif[0];
			if(invAni->Effectif[i])
			InvAniFrm->GrilleInv->Cells[c][r]=Aff(invAni->Effectif[i]);
			else
			InvAniFrm->GrilleInv->Cells[c][r]="  ";
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
void __fastcall TInvAniFrm::Simuler(void)
{
	int r,c,c0;
	int i;
	int noOr;
	int n;
	CL_MvtAnnee *mvt,*mvtOr,*mvt0,*mvt1,*mvtNaissance;
	CL_InvAni *invAni;
	double ne;
	bool CalculerNaissance;

	//pour la première année de simulation
	// initie mvt->Debut à l'effectif initial défini par l'utisateur
	// il est dans la colonne 4
	c=5;
	c0=4;
	Forme00Frm->LaGrille=GrilleInv;
	CalculerNaissance=false;

	for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
	{
		if(GrilleInv->Objects[0][r]==NULL) continue;

		mvt=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
		mvt->Debut=Forme00Frm->GrilleInt(c0,r);
		if(mvt->ADescendance==true)
		CalculerNaissance=true;
	}
	// maz des naissances qui seront calculées + bas
	//200103
	if(CalculerNaissance==true)
	{
		for(c=5;c<GrilleInv->ColCount;c++)
		{
			for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
			{
				if(GrilleInv->Objects[0][r]==NULL) continue;
				// mouvement d'une catégorie à une autre
				mvt=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
				mvt->Ne=0;
			}
		}
	}
	//mvt mouvement d'une catégorie à une autre et naissance
	for(c=5;c<GrilleInv->ColCount;c++)
	{
		for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
		{
			if(GrilleInv->Objects[0][r]==NULL) continue;
			// mouvement d'une catégorie à une autre
			invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
			mvt=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
			for(i=0;i<mvt->iOr;i++)
			{
				noOr=mvt->Origine[i];
				mvtOr=TrouverMvt(noOr,c);
				mvt->Entree[i]=mvtOr->Dispo(invAni->NoAnimal);
				//mvt->Origine[i];//mvtOr->Dispo(r-1);//
			}
			// Naissance
			if(mvt->ADescendance==false) continue;
			for(i=0;i<4;i++)
			{
				if (mvt->DonnePcent[i]==0.)continue;
				n=mvt->DonneNo[i];
				ne=mvt->Debut* mvt->DonnePcent[i]; //voir si Debut ou Fin
				ne=ceil(ne);
				mvtNaissance=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][n];

				mvtNaissance->Ne+=ne;
			}

		}
		// effectifs fin d'année
		for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
		{
//			if(c>= 7 && r==1)
//            	toto=1;
			if(GrilleInv->Objects[0][r]==NULL) continue;
			invAni=(CL_InvAni*)GrilleInv->Objects[0][r];

			mvt=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];

			if(invAni->EffMax[c-5]==SANSBORNE)
			{
				mvt->Solde();
				continue;
			}
			if(mvt->iVenteAuto==-1)
			{
				mvt->iVenteAuto=mvt->iVente;
				mvt->iVente++;
			}
			i=mvt->iVenteAuto;
			mvt->Vente[i]=0;
			mvt->Solde();
			if(mvt->Fin > invAni->EffMax[c-5])
			{
				//i=0;
				//mvt->iVente=1;
				mvt->Vente[i]=mvt->Fin- invAni->EffMax[c-5];
				mvt->PrixVente[i]=invAni->ValVenteDefaut;
				mvt->Fin-=mvt->Vente[i];
			}
		}

		// effectifs debut annee suivante =eff fin annee précedente
		if(c==GrilleInv->ColCount-1) return;

		for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
		{
			if(GrilleInv->Objects[0][r]==NULL) continue;
			if(c==GrilleInv->ColCount-1) break;
			mvt0=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
			mvt1=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c+1][r];
			mvt1->Debut=mvt0->Fin;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::SansSimuler(void)
{
	int r,c,c0;
	CL_MvtAnnee *mvt,*mvt0,*mvt1;

	//pour la première année de simulation
	// initie mvt->Debut à l'effectif initial défini par l'utisateur
	// il est dans la colonne 4
	c=5;
	c0=4;
	Forme00Frm->LaGrille=GrilleInv;

	for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
	{
		if(GrilleInv->Objects[0][r]==NULL) continue;

		mvt=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
		mvt->Debut=Forme00Frm->GrilleInt(c0,r);
		mvt->Solde();
	}

	//mvt mouvement d'une catégorie à une autre
	for(c=5;c<GrilleInv->ColCount;c++)
	{
//        if(c==GrilleInv->ColCount-1) return;
//         voir si modif nécessaire dans Simuler

		for(r=1;r<InvAniFrm->GrilleInv->RowCount;r++)
		{
			if(GrilleInv->Objects[0][r]==NULL) continue;

			mvt0=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c][r];
			mvt0->Solde();
			if(c<GrilleInv->ColCount-1)
			{
				mvt1=(CL_MvtAnnee*)InvAniFrm->GrilleInv->Objects[c+1][r];
				mvt1->Debut=mvt0->Fin;
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::AffEffectifs(void)
{
	int r,col;
	int date;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee;

	for(col=5;col<GrilleInv->ColCount;col++)
	{
		for(r=1;r<GrilleInv->RowCount;r++)
		{
			invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
			if(invAni==NULL) continue;

			date=col-5;
			mvtAnnee=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
			if(col==5)
			invAni->Effectif[0] =mvtAnnee->Debut;
			invAni->Effectif[date+1] =mvtAnnee->Fin;
			invAni->Vente[date] =mvtAnnee->TotVente;
			invAni->ValVente[date] =mvtAnnee->ValVente;
			invAni->Achat[date] =mvtAnnee->TotAchat;
			invAni->ValAchat[date] =mvtAnnee->ValAchat;
			if(mvtAnnee->Fin)
			GrilleInv->Cells[col][r]=Forme00Frm->Aff(mvtAnnee->Fin);
			else
			GrilleInv->Cells[col][r]="  ";
		}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// QUITTER
// à partir du tableau et des mvtAni accrochés creer LstMvtAni()
//---------------------------------------------------------------------------
/// pour stocker le minimum
/// creer LstMvtAni
void __fastcall TInvAniFrm::VideLstMvtAni(void)
{
	int i;
	CL_MvtAni* mvtAni;
	for(i=0;i<Agri->LstMvtAni->Count;i++)
	{
		mvtAni=(CL_MvtAni*)Agri->LstMvtAni->Items[i];
		delete mvtAni;
	}
	Agri->LstMvtAni->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::CreeLstMvtAni(void)
{
	int r;
	int col;
	int i;
	int noAnimal;
	int date;
	CL_InvAni* invAni;
	CL_MvtAnnee* mvtAnnee;
	CL_MvtAni* mvtAni;
	VideLstMvtAni();

	for(r=1;r<GrilleInv->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
		if(invAni==NULL) continue;

		noAnimal=invAni->NoAnimal;
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			date=col-5;
			mvtAnnee=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
			//Vente
			if(mvtAnnee->iVente >0)
			{
				for(i=0;i<mvtAnnee->iVente;i++)
				{
					mvtAni=new CL_MvtAni(noAnimal,date,VENTE,
							mvtAnnee->Vente[i],mvtAnnee->PrixVente[i]);
					Agri->LstMvtAni->Add(mvtAni);
				}
			}
			//Achat
			if(mvtAnnee->iAchat >0)
			{
				for(i=0;i<mvtAnnee->iAchat;i++)
				{
					mvtAni=new CL_MvtAni(noAnimal,date,ACHAT,
							mvtAnnee->Achat[i],mvtAnnee->PrixAchat[i]);
					Agri->LstMvtAni->Add(mvtAni);
				}
			}
			//Naissance
			if(mvtAnnee->Ne>0)
			{
				mvtAni=new CL_MvtAni(noAnimal,date,NE,
						mvtAnnee->Ne,0);
				Agri->LstMvtAni->Add(mvtAni);
			}
			//Mort
			if(mvtAnnee->Mort>0)
			{
				mvtAni=new CL_MvtAni(noAnimal,date,MORT,
						mvtAnnee->Mort,0);
				Agri->LstMvtAni->Add(mvtAni);
			}
			/*
			 //Entree
			 if(mvtAnnee->iOr>0)
			 {
			 for(i=0;i<mvtAnnee->iOr;i++)
			 {
			 mvtAni=new CL_MvtAni(noAnimal,date,MVT,
			 mvtAnnee->Entree[i],(float)mvtAnnee->Origine[i]);
			 Agri->LstMvtAni->Add(mvtAni);
			 }
			 }
			 */
			//Sortie
			if(mvtAnnee->iDest>0)
			{
				for(i=0;i<mvtAnnee->iDest;i++)
				{
					mvtAni=new CL_MvtAni(noAnimal,date,MVT,
							mvtAnnee->Sortie[i],(float)mvtAnnee->Destin[i]);
					Agri->LstMvtAni->Add(mvtAni);
				}
			}
			//recalculé à la lecture
		}
	}
//    ImpMvt();//test   200202
	//effacer mvtAnnee
	for(r=1;r<GrilleInv->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
		if(invAni==NULL) continue;
		for(col=5;col<GrilleInv->ColCount;col++)
		{
			mvtAnnee=(CL_MvtAnnee*)GrilleInv->Objects[col][r];
			delete mvtAnnee;
		}
	}
	/*
	 //test à supprimer
	 for(i=0;i<Agri->LstMvtAni->Count;i++)
	 {
	 mvtAni=(CL_MvtAni*)Agri->LstMvtAni->Items[i];
	 }
	 */
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//                 chercher dans Grille
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int __fastcall TInvAniFrm::TrouverLigne(int noAnimal)
{
	int r;
	CL_InvAni *invAni;
	for(r=1;r<GrilleInv->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
		if(invAni==NULL) continue;
		if(invAni->NoAnimal==noAnimal) return r;
	}
	return 999; //aew
}
//---------------------------------------------------------------------------
int __fastcall TInvAniFrm::TrouverNoAnimal(int r)
{
	CL_InvAni *invAni;

	invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
	if(invAni==NULL) return-1;
	return invAni->NoAnimal;
}

//---------------------------------------------------------------------------
CL_MvtAnnee* __fastcall TInvAniFrm::TrouverMvt(int noAnimal,int c)
{
	int row;
	CL_MvtAnnee *mvt;
	row=TrouverLigne(noAnimal);
	mvt=(CL_MvtAnnee*)GrilleInv->Objects[c][row];
	return mvt;
}
//---------------------------------------------------------------------------
// non fonctionel
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::MarquerCell(TStringGrid *grille,int col,int row)
{
	TGridRect selection;
	selection.Left=col;
	selection.Right=col+1;
	selection.Top=row;
	selection.Bottom=row;
	grille->Selection=selection;
}

//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int r;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur=;

	MvtAniFrm->Close();

	if(LabelModifie->Visible==false)
	{
		CanClose=true;
		return;
	}
	else
	{
		// on est passé par AffEffectifs
		// il a actualisé les invAni
		//calculer les valeurs inventaire pour reprise dans etat indicateurs..
		CalculValeur();
		vecteur->Nbelt=0;
		for(r=1;r<GrilleInv->RowCount;r++)
		{
			invAni=(CL_InvAni*)GrilleInv->Objects[0][r];
			if(invAni==NULL) continue;

			vecteur->insSans(invAni);
		}
		VideLstMvtAni();
		//si on a simulé!=constant
		if(RGCouS->ItemIndex==0)
		CreeLstMvtAni();
		// on a deleté tous les mvtAnnee
		ES->ecrireFichier();
		CanClose=true;
		return;
	}
}
//---------------------------------------------------------------------------
//   cf LesClasses.h
//------------------------------------------------------------------------------
/*
 class CL_MvtAni
 {
 public:
 CL_MvtAni(int noAnimal,int date,int type,int eff,float info);
 CL_MvtAni(CL_MvtAni* mvtAni);
 int NoAnimal;
 int Type;
 int Date;
 int Eff;
 float Info;
 };
 */
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::CBCatAnimauxClick(TObject *Sender)
{
	int i,n;
	AnsiString s;
	CL_Categorie *cat;
	CL_Item *animal;
	CL_InvAni *invAni;
	int rep;
	n=CBCatAnimaux->ItemIndex;
	// pour comprendre
	//ts=CBCatAnimaux->Items;
	//s=ts->Strings[n];
	//cat=(CL_Categorie*)ts->Objects[n]
	s=CBCatAnimaux->Items->Strings[n];
	if(s=="[...]")
	{
		ShowMessage("A faire");
		return;
	}
	rep=MessageBox(Handle,"j'efface Tout ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==ID_NO) return;

	LabelModifie->Visible=true;
	VideLstMvtAni();
	cat=(CL_Categorie*)CBCatAnimaux->Items->Objects[n];
	Agri->CatBestiaux=cat;
	Agri->NoCatBestiaux=cat->No;;

	->purge();
	for(i=0;i<V_Bestiaux->Nbelt;i++)
	{
		animal=V_Bestiaux->Vecteur[i];
		if(animal->Categorie!=cat) continue;

		invAni=new CL_InvAni();
		invAni->Animal=animal;
		invAni->NoAnimal=animal->No;
		invAni->ValInv=animal->Prix;
		Agri->V_InvAni->ins(invAni);
	}
	VideGrille(LaGrille);
	VersGrilleInvAni(Agri->V_InvAni);
}
//---------------------------------------------------------------------------
void __fastcall TInvAniFrm::BtBnRecommencerClick(TObject *Sender)
{
	int col;
	AnsiString value,s;
	CL_MvtAnnee *mvtAnnee;
	LabelModifie->Visible=true;
	Erreur=false;
	for(int r=1;r<LaGrille->RowCount;r++)
	for(int c=5;c<LaGrille->ColCount;c++)
	GrilleInv->Cells[c][r]="";

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		for(col=5;col<LaGrille->ColCount;col++)
		{
			mvtAnnee=(CL_MvtAnnee*)LaGrille->Objects[col][r];
			if(mvtAnnee==NULL) continue;

			mvtAnnee->Maz();
		}
	}
}

//---------------------------------------------------------------------------
// A replacer
void __fastcall TInvAniFrm::BtBnMaxClick(TObject *Sender)
{
	InvAniMaxFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TInvAniFrm::BtBnProChaClick(TObject *Sender)
{
	InvAniProChaFrm->Origine=0;
	InvAniProChaFrm->Show();
}
//---------------------------------------------------------------------------

