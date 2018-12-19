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
#include "DefAction.h"

#include "Graph.h"
#include "CL_Trad.h"
//#include "SorRapPrep.h"

#include "TVDico.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVDicoFrm *TVDicoFrm;

// utilise par Indicateur
extern CL_Compil *Compil;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TTVDicoFrm::TTVDicoFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::FormActivate(TObject *Sender)
{
//    ShowMessage("TVDico");
	/*
	 ShowMessage("TVDico");

	 //AnsiString as;
	 if(     AgriEnCours!=AncAgri
	 ||  AncTVItemCount!=TV->Items->Count
	 ||  AncComplet!=Complet)
	 {
	 */
//110306        BtBnRafraichirClick(this);
	//   }
//ShowMessage("TTVDicoFrm");
	switch(Origine)
	{
		case AGRI:
		Memo=AgriSaisieFrm->Memo;
		RGModifiable=AgriSaisieFrm->RGModifiable;
		break;
		case INDIC:
		Edit=IndicateurFrm->Edit;
		RGModifiable=IndicateurFrm->RGModifiable;
		break;
		case ETAT:
		case COMPARAISON:
		RGModifiable=DefEtatSortieFrm->RGModifiable;
		LaGrille=DefEtatSortieFrm->LaGrille;
		break;
		case RESULTAT:
		case SERIECOMP:
		case SORRAPIDE:
		break;
		case PROCEDURE:
		ShowMessage("TVDico Procedure");
		break;
		case ACTION:
		Edit=DefActionFrm->REdit;
//            RGModifiable=AgriSaisieFrm->RGModifiable;
//            ShowMessage("TVDicoFrm ACTION");
		break;
		default:
		ShowMessage("Oubli dans TVDico");
		Close();
	}
//    AncAgri=AgriEnCours;
//    AncTVItemCount=TV->Items->Count;
//    AncComplet=Complet;
}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::BtBnRafraichirClick(TObject *Sender)
{

	ES->IniV_Elt();
	Forme0Frm->CreeTVToutElt(TV,AgriEnCours,Complet);

}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::TVDblClick(TObject *Sender)
{
	switch(Origine)
	{
		case AGRI: ClickAgri(); break;
		case INDIC: ClickIndic(); break;
		case ETAT:
		case COMPARAISON: ClickEtat(); break;
		case RESULTAT: ClickResultat(); break;
		case SERIECOMP: ClickSerieComp();break;
		case ACTION: ClickAction(); break;
		default:
		ShowMessage("Oubli dans TVDico TVDblClick");
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::ClickIndic(void)
{
	TTreeNode *choix,*child;
	CL_Elt *elt;
	AnsiString as;
	AnsiString aInserer;
	int startPos=Edit->SelStart+1;
	//if(startPos==1) startPos=Edit->Text.Length(); //???

	startPos=Edit->Text.Length()+4;
	if(RGModifiable->ItemIndex==0)return;
	choix=TV->Selected;
	elt=(CL_Elt*)choix->Data;//pour test
	if(choix->Level==0)
	{
		if(elt->Poste->No==CULTURE)
		{
			as=Edit->Text;
			as.Insert("TOTAL_Culture",startPos);
			Edit->Text=as;
			return;
		}
		else
		return;
	}

	child=choix->getFirstChild();

	elt=(CL_Elt*)choix->Data;

	if(elt==NULL) return; //  031001

	//on veut le TOTAL d'une categorie
	if(elt->NoFamille!=MVT && child!=NULL)//TOTAL
	{
		aInserer=AnsiString("TOTAL( ")+elt->NomFamille;
		if(elt->Categorie)
		aInserer+=AnsiString(":")+AnsiString(elt->Categorie->Nom);
		aInserer+=AnsiString(")  "); //121103
	}

	else if(elt->NoFamille==MVT) //MVT
	EtablirNomMvtAni(aInserer,elt);

	else//CAS GENERAL
	{
		aInserer=elt->NomFamille;
		if(elt->Categorie)
		aInserer+=AnsiString(":")+AnsiString(elt->Categorie->Nom);
		if(elt->Nom)
		aInserer+=AnsiString(":")+AnsiString(elt->Nom);
		aInserer+=AnsiString("  "); //121103
	}
	as=Edit->Text;
	as.Insert(aInserer,startPos);
	Edit->Text=as;

}
//---------------------------------------------------------------------------
void TTVDicoFrm::EtablirNomMvtAni(AnsiString &aInserer, CL_Elt *elt) {
	AnsiString as;
	aInserer = elt->NomFamille; //Mvt Animaux
	aInserer += AnsiString(":") + AnsiString(elt->Categorie->Nom); //Laitier
	// si modif des noms ici modifier aussi dans CompAnalex lireIdent
	as = TrouveMvtType(elt->NoType);

	aInserer += AnsiString(":") + as;
	aInserer += AnsiString(":") + AnsiString(elt->Nom); //VL
}
//---------------------------------------------------------------------------
AnsiString TTVDicoFrm::TrouveMvtType(int type) {
	AnsiString as;
	switch (type) {
	case EFF:
		as = "Effectifs";
		break; //Effectifs
	case EFFV:
		as = "Eff Vendus";
		break;
	case EFFA:
		as = "Eff Achetés";
		break;
	case VALV:
		as = "Val Ventes";
		break;
	case VALA:
		as = "Val Achats";
		break;
	case VALINV:
		as = "Val Inv";
		break;
	}
	return as;
}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::ClickEtat(void)
{
	TTreeNode *choix;
	CL_Elt *eltSource,*elt;
	AnsiString as;
	int row;
	int rep;
	if(RGModifiable->ItemIndex==0)return;

	choix=TV->Selected;
	if(choix->Level==0) return;

	eltSource=(CL_Elt*)choix->Data;
	if(eltSource==NULL) return; //031001

	row=LaGrille->Row;
	if( LaGrille->Objects[0][row]!=NULL)
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;

		elt=(CL_Elt*)LaGrille->Objects[0][row];
		delete elt;
	}

	elt=new CL_Elt(eltSource);

	LaGrille->Objects[0][row]=(TObject*)elt;
	LaGrille->Cells[0][row]=row;
	LaGrille->Cells[2][row]=elt->Nom;

	if(elt->NoFamille==MVT)
	{
		as=TrouveMvtType(elt->NoType);
		LaGrille->Cells[3][row]=as;
		elt->NoCategorie=elt->NoType;
	}
	else if(elt->Categorie)
	LaGrille->Cells[3][row]=elt->NomCat;

	LaGrille->Cells[4][row]=elt->NomFamille;
	if(row >=DefEtatSortieFrm->LaGrille->RowCount-2) //050105
	{
		DefEtatSortieFrm->LaGrille->RowCount=row+2;
	}
	//DefEtatSortieFrm->AjouterRow();
	DefEtatSortieFrm->LaGrille->Row++;
	//DefEtatSortieFrm->LaGrille->RowCount++;
	DefEtatSortieFrm->LaGrille->Col=2;
	DefEtatSortieFrm->LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::ClickResultat(void)
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
	asNom=elt->Donne_Nom(); //130103
	nom=asNom.c_str();
	switch(ResultatFrm->RGAxe->ItemIndex)
	{
		case 0:
		if(ResultatFrm->LBGauche->Items->Count>10)
		{
			MessageBox(Handle,"Pas plus de 10 Eléments","Problème",MB_OK|MB_ICONEXCLAMATION);
			return;
		}
		ResultatFrm->LBGauche->Items->AddObject(nom,(TObject*)elt); //021102
		break;
		case 1:
		if(ResultatFrm->LBDroit->Items->Count>10)
		{
			MessageBox(Handle,"Pas plus de 10 Eléments","Problème",MB_OK|MB_ICONEXCLAMATION);
			return;
		}
		ResultatFrm->LBDroit->Items->AddObject(nom,(TObject*)elt); //021102
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::CourbeEtat(CL_EtatSortie *etat)
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
void __fastcall TTVDicoFrm::ClickSerieComp(void)
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
void __fastcall TTVDicoFrm::ClickAgri(void)
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
		if(elt->NoFamille==MVT) //MVT
		EtablirNomMvtAni(aInserer,elt);
		else
		{
			aInserer=elt->NomFamille;
			aInserer=aInserer+":"+elt->NomCat+":"+elt->Nom+"  ";
		}
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
//---------------------------------------------------------------------------
void __fastcall TTVDicoFrm::ClickAction(void)
{
	TTreeNode *choix;
	CL_Elt *elt;
	AnsiString as;
	AnsiString aInserer;
	int startPos=Memo->SelStart+1;

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

//    if(RGModifiable->ItemIndex==0)return;
	as=Memo->Text;
	as.Insert(aInserer,startPos);
	Memo->Text=as;

	DefActionFrm->LabelModifie->Visible=true;//241103
//    DefActionFrm->MemoDblClick(this);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TTVDicoFrm::TexteChaine(void) {
	L_Dico = T->TrouveTexte("TVDicoFrm", "L_Dico");
	L_Raf = T->TrouveTexte("TVDicoFrm", "L_Raf");
	Caption = L_Dico;
	BtBnRafraichir->Caption = L_Raf;
}
