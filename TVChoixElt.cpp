//---------------------------------------------------------------------------
#include <vcl.h>
#include <grids.hpp>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Forme00.h"
#include "Indicateur.h"
#include "DefEtatSortie.h"
#include "Resultat.h"
#include "Compilateur.h"
#include "LBCompAgri.h"
#include "AgriSaisieEnum.h"

#include "AgriSaisie.h"
#include "Graph.h"

#include "TVChoixElt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVChoixEltFrm *TVChoixEltFrm;

// utilise par Indicateur
extern CL_Compil *Compil;
extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TTVChoixEltFrm::TTVChoixEltFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::FormActivate(TObject *Sender)
{
	//  mis à jour systématiquement
	ES->IniV_Elt();
	Forme0Frm->CreeTVToutElt(TVChoixEltFrm->TV,AgriEnCours,true);

	switch(Origine)
	{
		case AGRI:
		Memo=AgriSaisieFrm->Memo;
		RGModifiable=AgriSaisieFrm->RGModifiable;
		Left=AgriSaisieFrm->BtDico->Left;
		Top =AgriSaisieFrm->Top+Memo->Top+20;
		EstInitialise=true;

//            ShowMessage("TVChoixEltFrm AGRI");
		break;
		case INDIC://INDICATEUR:
		Edit=IndicateurFrm->Edit;
		RGModifiable=IndicateurFrm->RGModifiable;
		Left=IndicateurFrm->Left+Edit->Left+Edit->Width-Width;
		Top =IndicateurFrm->Top+Edit->Top+20;
		break;
		case ETAT:
		case COMPARAISON:
		RGModifiable=DefEtatSortieFrm->RGModifiable;
		LaGrille=DefEtatSortieFrm->LaGrille;
		Left=DefEtatSortieFrm->Left+DefEtatSortieFrm->Width-TV->Width;
		Left-=10;
		//            Top =EtatSortieFrm->Top+EtatSortieFrm->LaGrille->Top;
		Top=DefEtatSortieFrm->Top+60;
		break;
		case RESULTAT:
		case SERIECOMP:
		Left=ResultatFrm->Left+ResultatFrm->Width-TV->Width;
		Left-=10;
		Top=ResultatFrm->Top+20;
		//Top=ResultatFrm->Top+60;
		break;
		default:
		ShowMessage("Oubli dans TVChoixElt");
		Close();
	}
	EstInitialise=true;
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::TVDblClick(TObject *Sender)
{
	switch(Origine)
	{
		case AGRI: ClickAgri(); break;
		case INDIC: ClickIndic(); break; //INDICATEUR
		case ETAT:
		case COMPARAISON: ClickEtat(); break;
		case RESULTAT: ClickResultat(); break;
		case SERIECOMP: ClickSerieComp();break;
		default:
		ShowMessage("Oubli dans TVChoixElt TVDblClick");
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::ClickIndic(void)
{
	TTreeNode *choix;
	CL_Elt *elt;
	AnsiString as;
	AnsiString aInserer;
	int startPos=Edit->SelStart+1;
	//if(startPos==1) startPos=Edit->Text.Length(); //???

	startPos=Edit->Text.Length()+4;
	if(RGModifiable->ItemIndex==0)return;
	choix=TV->Selected;
	if(choix->Level==0) return;

	elt=(CL_Elt*)choix->Data;

	if(elt==NULL) return;//  031001
	if(elt->NoFamille!=MVT)
	{
		aInserer=elt->NomFamille;
		if(elt->Categorie)
		aInserer+=AnsiString(":")+AnsiString(elt->Categorie->Nom);
		if(elt->Nom)
		aInserer+=AnsiString(":")+AnsiString(elt->Nom);
		aInserer+=AnsiString("  "); //121103
	}
	else
	{
		aInserer=elt->NomFamille; //Mvt Animaux
		aInserer+=AnsiString(":")+AnsiString(elt->Categorie->Nom);//Laitier
		switch(elt->NoType)
		{
			case EFF: as="Effectifs"; break; //Effectifs
			case EFFV: as="Eff Vendus"; break;
			case EFFA: as="Eff Achetés"; break;
			case VALV: as="Val Ventes"; break;
			case VALA: as="Val Achats"; break;
			case VALINV: as="Val Inv"; break;
		}
		aInserer+=AnsiString(":")+as;
		aInserer+=AnsiString(":")+AnsiString(elt->Nom); //VL
	}
	as=Edit->Text;
	as.Insert(aInserer,startPos);
	Edit->Text=as;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::ClickEtat(void)
{
	TTreeNode *choix;
	CL_Elt *eltSource,*elt;
	int row;
	int rep;
	if(RGModifiable->ItemIndex==0)return;

	choix=TV->Selected;
	if(choix->Level==0) return;

	eltSource=(CL_Elt*)choix->Data;
	if(eltSource==NULL) return; //031001

	row=LaGrille->Row;
	/*
	 if( LaGrille->Objects[0][row]==NULL)
	 elt=new CL_Elt();
	 else
	 elt=(CL_Elt*)LaGrille->Objects[0][row];
	 */
	if( LaGrille->Objects[0][row]!=NULL)
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;

		elt=(CL_Elt*)LaGrille->Objects[0][row];
		delete elt;
	}

	elt=new CL_Elt(eltSource);
//    memcpy(elt,eltSource,sizeof(CL_Elt));

//    elt->Flag='N';

	LaGrille->Objects[0][row]=(TObject*)elt;
	LaGrille->Cells[0][row]=row;
	LaGrille->Cells[2][row]=elt->Nom;
	if(elt->Categorie)
	LaGrille->Cells[3][row]=elt->NomCat;
	LaGrille->Cells[4][row]=elt->NomFamille;

//    Forme00Frm->GrilleModif[LaGrille->Tag]=true;
//    ColM[LaGrille->Tag]=LaGrille->Col;
//    RowM[LaGrille->Tag]=LaGrille->Row;
	DefEtatSortieFrm->AjouterRow();
	DefEtatSortieFrm->LaGrille->Row++;
	DefEtatSortieFrm->LaGrille->RowCount++;
	DefEtatSortieFrm->LaGrille->Col=2;
	DefEtatSortieFrm->LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::ClickResultat(void)
{
	TTreeNode *choix;
	CL_Elt *elt;
	char *nom;
	AnsiString asNom; //130103

/// probleme
	choix=TV->Selected;
	if(choix->Count!=0) return;
	if(choix->Level==0) return;//150602

	elt=(CL_Elt*)choix->Data;
	if(elt==NULL) return;
	if(elt->NoFamille==ETAT)
	{
		CourbeEtat(elt->Etat);
		return;
	}
	/*
	 if(elt->NoFamille==PERENNE)
	 {
	 // où deleter eltVerger  surVerger ????
	 eltVerger=new CL_Elt(elt);
	 surVerger=new float(N_X);
	 memset(surVerger,0,sizeof(float)*N_X);
	 for(n=0;n<Agri->V_Verger->Nbelt;n++)
	 {
	 verger=Agri->V_Verger->Vecteur[n];
	 if(verger->NoAtelier==elt->NoItem)
	 {
	 for(int i=0;i<N_X;i++)
	 surVerger[i]+=verger->SurfaceAn[i];
	 }
	 eltVerger->Valeur=surVerger;
	 elt=eltVerger;
	 }
	 }
	 */
//    if(elt->NoFamille==INDIC)
//    {
//        indic=elt->Indic;
//    	Compil->Calculer(indic->Prog->Reseau,indic->Prog->Arbre,0,N_X,indic->Valeur);
//    }
	asNom=elt->Donne_Nom();//130103
	nom=asNom.c_str();
//    nom=elt->Donne_Nom().c_str();
	switch(ResultatFrm->RGAxe->ItemIndex)
	{
		case 0:
		if(ResultatFrm->LBGauche->Items->Count>10)
		{
			MessageBox(Handle,"Pas plus de 10 Eléments","Problème",MB_OK|MB_ICONEXCLAMATION);
			return;
		}
//          ResultatFrm->LBGauche->Items->AddObject(elt->Nom,(TObject*)elt);
		ResultatFrm->LBGauche->Items->AddObject(nom,(TObject*)elt);//021102
		break;
		case 1:
		if(ResultatFrm->LBDroit->Items->Count>10)
		{
			MessageBox(Handle,"Pas plus de 10 Eléments","Problème",MB_OK|MB_ICONEXCLAMATION);
			return;
		}
//          ResultatFrm->LBDroit->Items->AddObject(elt->Nom,(TObject*)elt);
		ResultatFrm->LBDroit->Items->AddObject(nom,(TObject*)elt);//021102
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::CourbeEtat(CL_EtatSortie *etat)
{
	int n;
	CL_Elt *elt;
	for(n=0;n<etat->V_Elt->Nbelt;n++)
	{
		elt=etat->V_Elt->Vecteur[n];

		if(elt->NoFamille==FORME)
		{
			if (elt->NoItem==TRAIT) continue;
			else if(elt->NoItem==BLANC) continue;
			else if(elt->NoItem==TITRE) continue;
		}
		else
		{
			switch(ResultatFrm->RGAxe->ItemIndex)
			{
				case 0:
				if(ResultatFrm->LBGauche->Items->Count>10)
				{
					MessageBox(Handle,"Pas plus de 10 Eléments","Problème",MB_OK|MB_ICONEXCLAMATION);
					return;
				}
				ResultatFrm->LBGauche->Items->AddObject(elt->Nom,(TObject*)elt);
				break;
				case 1:
				if(ResultatFrm->LBDroit->Items->Count>10)
				{
					MessageBox(Handle,"Pas plus de 10 Eléments","Problème",MB_OK|MB_ICONEXCLAMATION);
					return;
				}
				ResultatFrm->LBDroit->Items->AddObject(elt->Nom,(TObject*)elt);
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::ClickSerieComp(void)
{
	TTreeNode *choix;
	CL_Elt *eltAComp; //element A Comparer

	choix=TV->Selected;
	eltAComp=(CL_Elt*)choix->Data;
	if(eltAComp==NULL) return;

	ResultatFrm->RetourDeLBCompAgri(eltAComp->NoFamille,eltAComp->NoCategorie,
			eltAComp->NoItem);
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEltFrm::ClickAgri(void)
{
	TTreeNode *choix;
	CL_Elt *elt;
	AnsiString as;
	AnsiString aInserer;
	int startPos=Memo->SelStart+1;
	int g=AgriSaisieFrm->LaGrille->Tag;
	int r,c;

	if(startPos==1) startPos=Memo->Text.Length();

	choix=TV->Selected;
	if(choix->Level==0) return;
	if(choix->HasChildren==true) return; //110203
	elt=(CL_Elt*)choix->Data;
	if(elt==NULL) return;//    031001
	if(elt->Categorie==NULL)
	{
		aInserer=elt->NomFamille;
		aInserer=aInserer+":"+elt->Nom+"  ";
	}
	else
	{
		aInserer=elt->NomFamille;
		aInserer=aInserer+":"+elt->NomCat+":"+elt->Nom+"  ";
	}

	if(g==GCreance||g==GDette) // mettre le nom en colonne 2
	{
		c=AgriSaisieFrm->LaGrille->Col;
		r=AgriSaisieFrm->LaGrille->Row;
		if(c!=2) return;
		AgriSaisieFrm->LaGrille->Cells[c][r]=elt->Nom;
		return;
	}
	else
	{
		if(RGModifiable->ItemIndex==0)return;
		as=Memo->Text;
		as.Insert(aInserer,startPos);
		Memo->Text=as;
	}
	AgriSaisieFrm->LabelModifie->Visible=true; //241103
	AgriSaisieFrm->MemoDblClick(this);
}
//---------------------------------------------------------------------------
