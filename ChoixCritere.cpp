//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "TriAgri.h"

#include "ChoixCritere.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChoixCritereFrm *ChoixCritereFrm;
//---------------------------------------------------------------------------
__fastcall TChoixCritereFrm::TChoixCritereFrm(TComponent* Owner) :
		TForm(Owner) {

}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::FormActivate(TObject *Sender)
{
	CL_Categorie *categorie;
	LabelModifie->Visible=false;
	LstR= new TList;
	LstNR= new TList;

	for(int n=0;n<LBCritere->Items->Count;n++)
	{
		categorie=(CL_Categorie*)LBCritere->Items->Objects[n];
		LstR->Add((TObject*)categorie);
	}
	for(int n=0;n<LBCritereNR->Items->Count;n++)
	{
		categorie=(CL_Categorie*)LBCritereNR->Items->Objects[n];
		LstNR->Add((TObject*)categorie);
	}
}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::BtEntrerClick(TObject *Sender)
{
	int n;
	CL_Categorie *categorie;

	if(LBCritereNR->Items->Count==0)return;

	LabelModifie->Visible=true;

	for(n=0;n<LBCritereNR->Items->Count;n++)
	{
		if(LBCritereNR->Selected[n]==false) continue;

		categorie=(CL_Categorie*)LBCritereNR->Items->Objects[n];
		LBCritere->Items->AddObject(categorie->Nom,(TObject*)categorie);
		LBCritereNR->Items->Delete(n);
		n--;
	}
}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::BtToutEntrerClick(TObject *Sender)
{
	int n;
	CL_Categorie *categorie;

	LabelModifie->Visible=true;

	for(n=0;n<LBCritereNR->Items->Count;n++)
	{
		categorie=(CL_Categorie*)LBCritereNR->Items->Objects[n];
		LBCritere->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	LBCritereNR->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::BtSortirClick(TObject *Sender)
{
	int n;
	CL_Categorie *categorie;

	if(LBCritere->Items->Count==0)return;

	LabelModifie->Visible=true;

	for(n=0;n<LBCritere->Items->Count;n++)
	{
		if(LBCritere->Selected[n]==false) continue;

		categorie=(CL_Categorie*)LBCritere->Items->Objects[n];
		LBCritereNR->Items->AddObject(categorie->Nom,(TObject*)categorie);
		LBCritere->Items->Delete(n);
		n--;
	}
}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::BtToutSortirClick(TObject *Sender)
{
	int n;
	CL_Categorie *categorie;

	LabelModifie->Visible=true;

	for(n=0;n<LBCritere->Items->Count;n++)
	{
		categorie=(CL_Categorie*)LBCritere->Items->Objects[n];
		LBCritereNR->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	LBCritere->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::BtAnnulClick(TObject *Sender)
{
	CL_Categorie *categorie;

	LBCritere->Clear();
	LBCritereNR->Clear();

	for(int n=0;n<LstR->Count;n++)
	{
		categorie=(CL_Categorie*)LstR->Items[n];
		LBCritere->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	for(int n=0;n<LstNR->Count;n++)
	{
		categorie=(CL_Categorie*)LstNR->Items[n];
		LBCritereNR->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}

}
//---------------------------------------------------------------------------
void __fastcall TChoixCritereFrm::BtOKClick(TObject *Sender)
{
	int n;
	CL_Categorie *categorie;

	for(n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		categorie=V_CatTypeZone->Vecteur[n];
		categorie->Flag=false;
	}
	for(n=0;n<LBCritere->Items->Count;n++)
	{
		categorie=(CL_Categorie*)LBCritere->Items->Objects[n];
		categorie->Flag=true;
	}
	if(VientDe=="GereAgri" )
	GereAgriFrm->CreeGrilleAgri();
	else if(VientDe=="TriAgri" )
	TriAgriFrm->IniEcran();
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TChoixCritereFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	if(LstR) delete LstR;
	if(LstNR) delete LstNR;
	LstR=NULL;
	LstNR=NULL;
}
//---------------------------------------------------------------------------

