//---------------------------------------------------------------------------

#include <vcl.h>
//#include <checklst.hpp>

#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
//#include "Forme0.h"
//#include "FichierLire.h"
//#include "Brouillon.h"
//#include "Tableur.h"

#include "Main.h"
#include "AgriClasst.h"

//#include "AgriSaisie.h"
#include "NoteAgri.h"
#include "TVVarianteAgri.h"
#include "CL_Trad.h"

//#include "GereAtelier.h"
//#include "GereCatItem.h"

#include "TresoCopieRepart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTresoCopieRepartFrm *TresoCopieRepartFrm;

extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TTresoCopieRepartFrm::TTresoCopieRepartFrm(TComponent* Owner) :
		TForm(Owner) {
}
//----------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::FormActivate(TObject *Sender)
{
	TexteChaine();
	CreeGrilleAgri();
	Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// CreeGrilleAgri
//-----------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::VideGrille(TStringGrid *grille)
{
	for(int r=1;r<grille->RowCount;r++)
	{
		grille->Objects[0][r]=NULL;
		for(int c=0;c<grille->ColCount;c++)
		grille->Cells[c][r]="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::CreeGrilleAgri(void)
{

	CL_Categorie *categorie;
	CL_Agriculteur *agri; //, *ancetre;
	AnsiString s;
	int c,i,j,r;
	VideGrille(GrilleAgri);
	// nb row
	if(V_Agriculteur->Nbelt==0)GrilleAgri->RowCount=2;
	else
	GrilleAgri->RowCount=V_Agriculteur->Nbelt+1;

	// 1 colonne pour le nom, a répartition O/N, le nombre de variante, le n° de variante +les criteres
	GrilleAgri->ColCount=V_CatTypeZone->Nbelt+4;
	//en tete
	r=0;

	c=0;
	GrilleAgri->ColWidths[c]=120;
	GrilleAgri->Cells[c][r]=T->L_Agri;//"Agriculteur";

	c=1;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][r]=L_Repart;//" Répartition";

	c=2;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][r]=L_NbVar;//" Nb Var";

	c=3;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][r]=L_NoVar;//" N° Var";

	c=4;

	for(j=0;j<AgriClasstFrm->ChLBCatTypeZone->Count;j++)
	{
		categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[j];
		GrilleAgri->ColWidths[c]=90;
		GrilleAgri->Cells[c][r]=categorie->Nom;
		GrilleAgri->Objects[c][r]=(TObject*)categorie;
		c++;
	}
	//agri
	Row=1;
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->EstVariante==true) continue;

		agri->Pere==NULL;
		AffLesVariantes( agri);
	}
	GrilleAgri->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::AffAgri(CL_Agriculteur *agri)
{
	CL_Categorie *categorie;
	TList *lstCritere;
	CL_Item *critere;
	int c,k;
	bool trouve;
	lstCritere=agri->LstCritere;

	GrilleAgri->Objects[0][Row]=(TObject*)agri;
	GrilleAgri->Cells[0][Row]=agri->Nom;
	if(agri->V_ItemRepart->Nbelt >0)
	GrilleAgri->Cells[1][Row]="  O";

	GrilleAgri->Cells[2][Row]=AnsiString(agri->NbVariante);
	GrilleAgri->Cells[3][Row]=AnsiString(agri->NoVariante);
	for(c=4;c<GrilleAgri->ColCount;c++)
	{
		categorie=(CL_Categorie*)GrilleAgri->Objects[c][0];
		trouve=false;
		for (k=0;k<lstCritere->Count;k++)
		{
			critere=(CL_Item*)lstCritere->Items[k];
			if(critere->Categorie==categorie)
			{
				GrilleAgri->Cells[c][Row]=critere->Nom;
				trouve=true;
				k=lstCritere->Count;
				break;
			}
		}
		if(trouve==false)
		GrilleAgri->Cells[c][Row]="???";
	}
	Row++;

}
//---------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::AffLesVariantes(CL_Agriculteur *agri)
{
	ST_NoAgri *variante;
	AffAgri(agri);
	GrilleAgri->Cells[2][Row-1]=AnsiString(agri->NoVariante);
	if(agri->LstVariante->Count==0) return;

	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i];
		AffLesVariantes(variante->Agri);
	}
	return;
}
//---------------------------------------------------------------------------
// Verif Close            a modifier cf saisagri
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTEROLYMPE",
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------

void __fastcall TTresoCopieRepartFrm::GrilleAgriDblClick(TObject *Sender)
{
	int r;
	int rep;
	AnsiString as;
	CL_Agriculteur *agri; //, *ancetre;
	r=GrilleAgri->Row;
	agri=(CL_Agriculteur*)GrilleAgri->Objects[0][r];
	if(agri==NULL) return;
	else if(agri->V_ItemRepart->Nbelt==0)
	{
		ShowMessage(L_PasRep); //"N'a PAS de répartitions  !!");
		return;
	}
	else
	{
		//as=AnsiString(" Recopier les répartitions de ")+agri->Nom;
		as=AnsiString(L_RecopRepDe)+agri->Nom;
		rep=MessageBox(Handle,as.c_str(),L_RecopRep.c_str(),//"COPIER REPARTITONS",
				MB_YESNOCANCEL|MB_ICONQUESTION);
		if(rep!=IDYES) return;

		CopierRepart(agri);
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoCopieRepartFrm::CopierRepart(CL_Agriculteur *agri)
{
	int i;
	CL_ItemRepart *rep0,*rep1;
	for(i=0;i<agri->V_ItemRepart->Nbelt;i++)
	{
		rep0=agri->V_ItemRepart->Vecteur[i];
		rep1=new CL_ItemRepart(rep0);
		AgriEnCours->V_ItemRepart->ins(rep1);
	}
}

//---------------------------------------------------------------------------
void TTresoCopieRepartFrm::TexteChaine(void) {
	AnsiString as;
	as = T->TrouveTexte("TresoCopieRepartFrm", "L_Repart");
	L_Repart = "aaa"; //as;
///*     a voir
	L_Repart = T->TrouveTexte("TresoCopieRepartFrm", "L_Repart");
	L_NbVar = T->TrouveTexte("TresoCopieRepartFrm", "L_NbVar");
	L_NoVar = T->TrouveTexte("TresoCopieRepartFrm", "L_NoVar");
	L_PasRep = T->TrouveTexte("TresoCopieRepartFrm", "L_PasRep");
	L_RecopRepDe = T->TrouveTexte("TresoCopieRepartFrm", "L_RecopRepDe");
	L_RecopRep = T->TrouveTexte("TresoCopieRepartFrm", "L_RecopRep");
//*/
}
