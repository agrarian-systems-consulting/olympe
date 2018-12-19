//-------------- -------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "NouvAgri.h"
#include "NoteAgri.h"
#include "Forme0.h"
#include "AgriSaisie.h"
#include "Ensemble.h"

#include "TVVarianteAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVVarianteAgriFrm *TVVarianteAgriFrm;
//---------------------------------------------------------------------------
__fastcall TTVVarianteAgriFrm::TTVVarianteAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVVarianteAgriFrm::FormActivate(TObject *Sender)
{
	TV->FullExpand();
}
//---------------------------------------------------------------------------//pour afficher les notes de la variante
//---------------------------------------------------------------------------
void __fastcall TTVVarianteAgriFrm::TVClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Agriculteur *agri;
	TVDblClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TTVVarianteAgriFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
//TTreeNodes *tt;
	CL_Agriculteur *agri,*pere, *fils,*ancetre;
	ST_NoAgri *variante;
	int r;
//test
//?    TV->FullExpand();

	elt=TV->Selected;
	if(elt==NULL) return;//      031001
	if(elt->Level==0) return;

	agri=(CL_Agriculteur*)elt->Data;

	if(elt->Text=="[...]")
	{
		NouvAgriFrm->GrilleAgri->RowCount++;
		r=NouvAgriFrm->GrilleAgri->RowCount-1;

		pere=agri;
		fils=new CL_Agriculteur(pere);
		fils->EstVariante=true;
		fils->Pere=pere; //300408
		V_Agriculteur->ins(fils);

		fils->LstVariante->Count=0;

		variante=new ST_NoAgri;
		variante->No=fils->No;
		variante->Agri=fils;

		// augmenter NbVariante des parents
		pere->LstVariante->Add(variante);
		pere->NbVariante++;
		fils->NoVariante=pere->NoVariante*10 + pere->LstVariante->Count;
		fils->NbVariante=0;
		ancetre=pere;
		while(1)
		{
			pere=pere->Pere;
			if(pere==NULL) break;
			pere->NbVariante++;
			ancetre=pere;
		}
		NouvAgriFrm->Agri=ancetre;
		NouvAgriFrm->AffVariante();
//        NouvAgriFrm->AffAgri(fils,r);

		Forme0Frm->CreeTVVarianteAgri(TV,ancetre);
		TV->FullExpand();

		NoteAgriFrm->Agri=fils;
		NoteAgriFrm->Show();

		NouvAgriFrm->GrilleAgri->Row=r;
		NouvAgriFrm->GrilleAgri->Col=1;
		NouvAgriFrm->AStocker=true;
		NouvAgriFrm->GrilleAgriClick(this);
		return;
	}
	if( TVVarianteAgriFrm->TV->Tag==0)
	{
		trouveRow(agri);
		NoteAgriFrm->Agri=agri;
		NoteAgriFrm->Show();
		NouvAgriFrm->GrilleAgriClick(this);
	}
	else
	{
		r=EnsembleFrm->Grille0->RowCount;
		EnsembleFrm->Grille0->Cells[0][r]=agri->Nom;
		ShowMessage("TVVariante A completer");
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVVarianteAgriFrm::trouveRow(CL_Agriculteur *agri)
{
	AnsiString as,as1;
	as=agri->NoVariante;
	for(int r=1;r<NouvAgriFrm->GrilleAgri->RowCount;r++)
	{
		as1=NouvAgriFrm->GrilleAgri->Cells[1][r];
		if(NouvAgriFrm->GrilleAgri->Cells[1][r]==as)
		{
//		    ShowMessage(r);
			NouvAgriFrm->GrilleAgri->Row=r;
			NouvAgriFrm->GrilleAgri->Col=1;
			return;
		}
	}
}
//---------------------------------------------------------------------------
void TTVVarianteAgriFrm::TexteCaption(void) {
}

