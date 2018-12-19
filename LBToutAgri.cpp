//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "NoteAgri.h"
#include "Ensemble.h"
#include "GereEnsemble.h"
#include "Erreur.h"
#include "DefProcedure.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBToutAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBToutAgriFrm *LBToutAgriFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLBToutAgriFrm::TLBToutAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLBToutAgriFrm::BtBnOKClick(TObject *Sender)
{
	CL_Agriculteur *agri;
	int r,n;
//int an_0=0;
	AnsiString as;
	CL_AgriEff *agriEff;
	int nbAgri;
	if(VientDe=="DefProcedure")
	{
		DefProcedureFrm->VAgri.clear();
		for( n=0;n<ChLB->Items->Count;n++)
		{
			if(ChLB->Checked[n]==false) continue;

			agri=(CL_Agriculteur *)ChLB->Items->Objects[n];
			DefProcedureFrm->VAgri.push_back(agri);
		}

	}
	else //GereEnsemble Ensemble
	{
		for( n=0;n<ChLB->Items->Count;n++)
		{
			if(ChLB->Checked[n]==false) continue;

			agri=(CL_Agriculteur *)ChLB->Items->Objects[n];

			if(EnsembleFrm->EstAffiche(agri)>0) continue;

			/// afficher les nouveaux entrés
			agriEff =new CL_AgriEff (agri);
			// la grille a au moins 2 lignes
			// cf Ensemble AffGrilleVide
			/// il faut que RowCount soiT > FixedRows
			///GrilleEstVide=false  dans EnsembleFrm->AffAgriEff
			if(EnsembleFrm->GrilleEstVide==true)
			{
				// afficher total en premiere ligne
				r=1;
				EnsembleFrm->Grille0->Cells[0][r]="Total";
				EnsembleFrm->Grille0->RowCount=2;
			}
			r=EnsembleFrm->Grille0->RowCount;
			EnsembleFrm->Grille0->RowCount++;

			EnsembleFrm->AffAgriEff(r,agriEff);
			EnsembleFrm->LabelModifie->Visible=true;
		}
		nbAgri=EnsembleFrm->Grille0->RowCount-2;
		as=EnsembleFrm->Ensemble->Nom+" nb types=  "+AnsiString(nbAgri);
		EnsembleFrm->LabEnsemble->Caption=as;
	}
	//verif cohérence date debut     ne pas effacer
	/*
	 int an_0=0;

	 for( n=0;n<ChLB->Items->Count;n++)
	 {
	 if(ChLB->Checked[n]==false) continue;

	 agri=(CL_Agriculteur *)ChLB->Items->Objects[n];
	 if(an_0==0)
	 an_0=agri->DefSim->An_0;
	 else
	 {
	 if (an_0!=agri->DefSim->An_0)
	 {
	 MontrerErreurAn_0();
	 break;
	 }
	 }
	 }
	 */

}
//---------------------------------------------------------------------------

void __fastcall TLBToutAgriFrm::BtBnPasOKClick(TObject *Sender)
{
//    ShowMessage("Pas OK");
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TLBToutAgriFrm::MontrerErreurAn_0(void)
{
	char buf[128];
	CL_Agriculteur *agri;
	ErreurFrm->Edit->Clear();
	sprintf(buf,"Il y a des incohérences dans les dates de début");
	ErreurFrm->Edit->Lines->Add(buf);
	for(int n=0;n<ChLB->Items->Count;n++)
	{
		if(ChLB->Checked[n]==false) continue;

		agri=(CL_Agriculteur *)ChLB->Items->Objects[n];
		sprintf(buf,"%-20.20s Variante n°:%d    Debut:%d ",
				agri->Nom,agri->NoVariante,agri->DefSim->An_0);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	ErreurFrm->Show();
}
//doit pouvoir se supprimer
//cf Ensemble.cpp
//---------------------------------------------------------------------------
void __fastcall TLBToutAgriFrm::Decoche(CL_Agriculteur *agri0)
{
	int n;
	CL_Agriculteur *agri;
	for(n=0;n<ChLB->Items->Count;n++)
	{
		agri=(CL_Agriculteur *)ChLB->Items->Objects[n];
		if(agri==agri0)
		{
			ChLB->Checked[n]=false;
			return;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBToutAgriFrm::ChLBClickCheck(TObject *Sender)
{
	CL_Agriculteur *agri;
	int n;
	int rep;
	int r;
	n=ChLB->ItemIndex;
	agri=(CL_Agriculteur*)ChLB->Items->Objects[n];
	// vérifier si on veut bien supprimer cet agri dans l'ensemble

	if(ChLB->Checked[n]==false)
	{
		r=EnsembleFrm->EstAffiche(agri);
		/// c'est la ligne ou il est affiché
		if(r>0)
		{
			rep=MessageBox(Handle," Est déjà dans l'ensemble Je supprime Vous êtes sur ?","SUPPRESSION",
					MB_YESNO|MB_ICONEXCLAMATION);

			if(rep==IDNO) ChLB->Checked[n]=true;
			else
			{
				ChLB->Checked[n]=false;
				EnsembleFrm->SupLigne(r);
			}
		}
	}
	NoteAgriFrm->Agri=agri;
	if(GereEnsembleFrm->RGNote->ItemIndex==0)
	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------
/*
 //----------------------------------------------------------------------------
 bool __fastcall TForme00Frm::RowVide(int row)
 {
 AnsiString s;
 for(int c=1;c<LaGrille->ColCount;c++)  // en 0 c'est num° de ligne
 {
 s=LaGrille->Cells[c][row].Trim();
 if(s.IsEmpty()==false) return false;
 //    	if(LaGrille->Cells[c][row].IsEmpty()==false) return false;
 }
 return true;
 }
 */

//---------------------------------------------------------------------------
void __fastcall TLBToutAgriFrm::BtBnTousClick(TObject *Sender)
{
	int n;
	for( n=0;n<ChLB->Items->Count;n++)
	ChLB->Checked[n]=true;

}
//---------------------------------------------------------------------------

void __fastcall TLBToutAgriFrm::BtBnAucunClick(TObject *Sender)
{
	int n;
	for( n=0;n<ChLB->Items->Count;n++)
	ChLB->Checked[n]=false;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBToutAgriFrm::IniCaption(void) {
	BtBnAucun->Caption = T->LC_BtIndAucun;
	LBToutAgriFrm->Caption = T->LC_GereAgriFrm;
	BtBnTous->Caption = T->LC_BtIndTous;
}
//--------------------------------------------
void TLBToutAgriFrm::TexteCaption(void) {
	LC_BtIndAucun = T->TrouveCaption("CL_Trad", "LC_BtIndAucun");
	LC_GereAgriFrm = T->TrouveCaption("CL_Trad", "LC_GereAgriFrm");
	LC_BtIndTous = T->TrouveCaption("CL_Trad", "LC_BtIndTous");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBToutAgriFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

