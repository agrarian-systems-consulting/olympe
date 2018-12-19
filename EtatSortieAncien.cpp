//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <mem.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
//#include "Brouillon.h"
#include "GereEtat.h"
#include "Forme0.h"
#include "TVChoixElt.h"
#include "Resultat.h"
#include "QRSortieQuant.h"

#include "EtatSortieAncien.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TEtatSortieFrm *EtatSortieFrm;

extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TEtatSortieFrm::TEtatSortieFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
	EstInitialise = false;
}
//---------------------------------------------------------------------------
///* fille de Forme00
void __fastcall TEtatSortieFrm::FormActivate(TObject *Sender)
{
// une seule grille
	if(EstInitialise==false)
	{
		Personnaliser();
		DefinirLesGrilles();

		for(int g=0;g<GrilleX;g++)
		IniGrille(LesGrilles[0]); // nb col,row, non défilable

		for(int g=0;g<GrilleX;g++) GrilleModif[g]=false;
		EstInitialise=true;

		CellInitiale(1,2);
	}
//    Forme0Frm->CreeTVChoix(TVChoix,true);
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::AffEtatSortie(void)
{
	int g;

	LabelModifie->Visible=false;
	GereEtatFrm->Origine=2;
//  	EdEtatSortie->Text =EtatSortie->Nom;
	LabEtatSortie->Caption =EtatSortie->Nom;
//GereEtat a appelé CreeTVToutElt via Calcul0
	//AgriEnCours ou EnsembleEnCours ???

	if(Global==ENSEMBLE)//130602
	CreeTVToutElt(TVChoixEltFrm->TV,EnsembleEnCours->Total,true);
	else
	CreeTVToutElt(TVChoixEltFrm->TV,AgriEnCours,true);

	TVChoixEltFrm->Visible=true;
	CellAVerifier=false;
	VideLesGrilles();

	for(g=0;g<GrilleX;g++)
	{
		VersGrille(LesGrilles[g]);
		ColM[g]=2; // O N M
		RowM[g]=1;
		GrilleModif[g]=false;
	}
	g=0;
	LaGrille=LesGrilles[g]; //commencer par les produits

	ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
	CellAVerifier=true;
	CellDebut();
//	TVChoixEltFrm->Visible;//=!TVChoixEltFrm->Visible;

//    TVChoix->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::LBServiceClick(TObject *Sender)
{
	int n=LBService->ItemIndex;
	if(RGModifiable->ItemIndex==0)return;

	LabelModifie->Visible=true;
	switch(n)
	{
		case 0: Inserer(); break;
		case 1: Supprimer(); break;
		case 2: Blanc(); break;
		case 3: Trait(); break;
		case 4: Titre(); break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::Inserer(void)
{
	int r;
	int rIns=LaGrille->Row;

	LaGrille->RowCount++;
	for(r=LaGrille->RowCount;r>LaGrille->Row;r--)
	{
		LaGrille->Rows[r]=LaGrille->Rows[r-1];
		LaGrille->Objects[0][r]=LaGrille->Objects[0][r-1];
		if(RowVide(r)==false)
		LaGrille->Cells[0][r]=r;
		else
		LaGrille->Objects[0][r]=NULL;
	}
	LaGrille->Objects[0][rIns]=NULL;
	LaGrille->Cells[2][rIns]="";
	LaGrille->Cells[3][rIns]="";
	LaGrille->Cells[4][rIns]="";

	GrilleModif[LaGrille->Tag]=true;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
//supprime ligne
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::Supprimer(void)
{
	int r=LaGrille->Row;
	CL_Elt* elt;
	int rep;
	elt=(CL_Elt*)LaGrille->Objects[0][r];
	rep=MessageBox(Handle," Je supprime la ligne\n Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	if(rep==IDNO) return;
	if(elt!=NULL) elt->Flag='S';
	LabelModifie->Visible=true;
	SupprimerLigne();
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::Blanc(void)
{
	PlaceEltForme(EltBlanc);
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::Trait(void)
{
	PlaceEltForme(EltTrait);
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::Titre(void)
{
	PlaceEltForme(EltTitre);
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::PlaceEltForme(CL_Elt *eltForme)
{
	int row;
	CL_Elt *elt;

	row=LaGrille->Row;

	if( LaGrille->Objects[0][row]==NULL)
	elt=new CL_Elt();
	else
	elt=(CL_Elt*)LaGrille->Objects[0][row];

	memcpy(elt,eltForme,sizeof(CL_Elt));

	LaGrille->Objects[0][row]=(TObject*)elt;

	LaGrille->Cells[0][row]=row;
	LaGrille->Cells[2][row]=elt->Nom;
	LaGrille->Cells[3][row]=elt->NomCat;
	LaGrille->Cells[4][row]=elt->NomFamille;
	GrilleModif[LaGrille->Tag]=true;
	ColM[LaGrille->Tag]=LaGrille->Col;
	RowM[LaGrille->Tag]=LaGrille->Row;
	AjouterRow();
	LaGrille->Row++;
	LaGrille->Col=2;
}
//---------------------------------------------------------------------------
bool __fastcall TEtatSortieFrm::Stocker(void)
{
	if(EtatSortie==NULL) return true;
	DesGrilles();
//    if(EtatSortie->Flag!=NOUVEAU)
//    {
//        V_EtatSortie->remplace(EtatSortieOr,EtatSortie);
//        delete EtatSortieOr;
//        EtatSortieOr=EtatSortie;
//    }
	ES->ecrireFichier();
	MazModif();
	EtatSortie->Flag=EXISTE;
	LabelModifie->Visible=false;
	return true;
}
//---------------------------------------------------------------------------
//void __fastcall TEtatSortieFrm::BtClasserClick(TObject *Sender)
//---------------------------------------------------------------------------

void __fastcall TEtatSortieFrm::RGModifiableClick(TObject *Sender)
{
	if(RGModifiable->ItemIndex==0)
	RGModifiable->Color=clRed;
	else
	RGModifiable->Color=clLime;
}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::PossibleModifier(bool modifiable)
{
	if(modifiable==false)
	{
		RGModifiable->ItemIndex=0;
		RGModifiable->Color=clRed;
	}
	else
	{
		RGModifiable->ItemIndex=1;
		RGModifiable->Color=clLime;
	}
}
//---------------------------------------------------------------------------

void __fastcall TEtatSortieFrm::BtBnStockerClick(TObject *Sender)
{
	TVChoixEltFrm->Visible=false;

	if(LabelModifie->Visible==false) return;
	Stocker();
}
//---------------------------------------------------------------------------

void __fastcall TEtatSortieFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_Elt* elt;
	int rep;
	if(RGModifiable->ItemIndex==0)return;
	elt=(CL_Elt*)LaGrille->Objects[0][r];
	if(elt==NULL) return;
	SelLigne();
	/*
	 if(elt!= NULL && elt->Supprimable==false)
	 {
	 ShowMessage(" UTILISE ");
	 return;
	 }
	 */
	rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		if(elt!=NULL) elt->Flag='S';
		SupprimerLigne();
		LabelModifie->Visible=true;
	}
	DeSelLigne();

}
//---------------------------------------------------------------------------
void __fastcall TEtatSortieFrm::BtBnResultatClick(TObject *Sender)
{
	DesGrilles();
	//FBrouillon->EnCours=ETAT;
	/*
	 if(Global==ENSEMBLE)                              //080202
	 FBrouillon->Etat(EnsembleEnCours->Total,EtatSortie);
	 else
	 FBrouillon->Etat(AgriEnCours,EtatSortie);
	 */
	if(Global==ENSEMBLE) //080202
	QRSortieQuantFrm->Etat(EtatSortie,EnsembleEnCours->Total);
	else
	QRSortieQuantFrm->Etat(EtatSortie,AgriEnCours);

}
//---------------------------------------------------------------------------

void __fastcall TEtatSortieFrm::BoutFermerClick(TObject *Sender)
{
	TVChoixEltFrm->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TEtatSortieFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	int g;
	TVChoixEltFrm->Visible=false;
	DerniereCell();
	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		switch(rep)
		{
			case ID_YES:
			CanClose=Stocker();
			if(CanClose==true) LabelModifie->Visible=false;
			break;
			case ID_CANCEL:
			CanClose=false;
			break;
			case ID_NO:
			VideLesGrilles();
			CanClose=true;
			for(int g=0;g<GrilleX;g++) VersGrille(LesGrilles[g]);
			LaGrille=LesGrilles[0];
			g=LaGrille->Tag;
			ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
			LabelModifie->Visible=false;
			break;
		}
	}
	else
	CanClose=true;
}
//---------------------------------------------------------------------------

void __fastcall TEtatSortieFrm::BtBnDicoClick(TObject *Sender)
{
	TVChoixEltFrm->Visible=true;
}
//---------------------------------------------------------------------------

