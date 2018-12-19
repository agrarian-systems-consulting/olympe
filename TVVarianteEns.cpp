//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "NouvAgri.h"
#include "Forme0.h"
#include "NoteEnsemble.h"
#include "GereEnsemble.h"
#include "Ensemble.h"

#include "TVVarianteEns.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVVarianteAgri"
#pragma resource "*.dfm"
TTVVarianteEnsFrm *TVVarianteEnsFrm;
//---------------------------------------------------------------------------
__fastcall TTVVarianteEnsFrm::TTVVarianteEnsFrm(TComponent* Owner) :
		TTVVarianteAgriFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVVarianteEnsFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Ensemble *ens,*pere, *fils; //,*ancetre;
	ST_NoEnsemble *variante;
	elt=TV->Selected;
	if(elt==NULL) return;//     031001
	if(elt->Level==0) return;

	ens=(CL_Ensemble*)elt->Data;

	if(elt->Text=="[...]")
	{
		pere=ens;
		fils=new CL_Ensemble(pere);
		fils->EstVariante=true;
		V_Ensemble->ins(fils);

		fils->LstVariante->Count=0;

		variante=new ST_NoEnsemble;
		variante->No=fils->No;
		variante->Ensemble=fils;

		pere->LstVariante->Add(variante);
		fils->NoVariante=pere->NoVariante*10 + pere->LstVariante->Count;

		Forme0Frm->CreeTVVarianteEnsemble(TV,Ensemble);
		TV->FullExpand();

		NoteEnsembleFrm->Ensemble=fils;
		NoteEnsembleFrm->Show(); //A REMETTRE
		//RGVarianteClick cree la Grille avec les variantes
		if(EnsembleFrm->Visible==true) EnsembleFrm->Close();

		GereEnsembleFrm->LabelModifie->Visible=true;//A REMETTRE
		GereEnsembleFrm->RGVariante->ItemIndex=0;
		GereEnsembleFrm->RGVarianteClick(this);
		return;
	}
	// click sur une variante existante
	trouveRow(ens);
	NoteEnsembleFrm->Ensemble=ens;
	NoteEnsembleFrm->Show();
	GereEnsembleFrm->BtEffectifClick(this);

}
//---------------------------------------------------------------------------
void __fastcall TTVVarianteEnsFrm::trouveRow(CL_Ensemble *ens)
{
	CL_Ensemble *ens0;
	for(int r=1;r<GereEnsembleFrm->GrilleEns->RowCount;r++)
	{
		ens0=(CL_Ensemble*)GereEnsembleFrm->GrilleEns->Objects[0][r];
		if(ens!=ens0) continue;

		GereEnsembleFrm->GrilleEns->Row=r;
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTVVarianteEnsFrm::TVClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Ensemble *ens;
	elt=TV->Selected;
	if(elt==NULL) return; //       031001

	ens=(CL_Ensemble*)elt->Data;

	if(elt->Text=="[...]") return;
	trouveRow(ens);
	NoteEnsembleFrm->Ensemble=ens;
	NoteEnsembleFrm->Show();
	GereEnsembleFrm->BtEffectifClick(this);
}
//---------------------------------------------------------------------------

