//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Forme0.h"
#include "Ensemble.h"
#include "TriAgri.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBToutEnsemble.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBToutEnsembleFrm *LBToutEnsembleFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBToutEnsembleFrm::TLBToutEnsembleFrm(TComponent* Owner) :
		TForm(Owner) {

}
//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::CreeLB(void)
{
	Forme0Frm->CreeLBToutEnsemble(ChLB);
}
//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::BtBnVisible(bool visible)
{
	LBToutEnsembleFrm->BtBnOK->Visible= visible;
	LBToutEnsembleFrm->BtBnPasOK->Visible= visible;
}
//---------------------------------------------------------------------------

void __fastcall TLBToutEnsembleFrm::BtBnOKClick(TObject *Sender)
{
//    ChoixEstFait=true;
//    if(TriAgriFrm->ChoixEstFait==false)
//    {
//        ShowMessage("Critères de Tri NON sélectionnés");
//        return;
//    }

	if (VientDe=="SelectionAddition") SelectionAddition();
	else if(VientDe=="Extraction") Extraction();
	else ShowMessage("Oubli Vient De LBToutEnsemble");
}
//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::SelectionAddition(void)
{
	int n,i,j,r;
	int nbAgri;
	AnsiString as;
	CL_Ensemble *ensemble;
	CL_Agriculteur *agri;
	CL_AgriEff *agriEff,*agriEffT; //T comme total
	for( n=0;n<ChLB->Items->Count;n++)
	{
		if(ChLB->Checked[n]==false) continue;

		ensemble=(CL_Ensemble *)ChLB->Items->Objects[n];
		for(i=0;i<ensemble->V_AgriEff->Nbelt;i++)
		{
			agriEff=ensemble->V_AgriEff->Vecteur[i];
			agri=agriEff->Agri;
			r= EnsembleFrm->EstAffiche(agri);
			//il est déjà dans l'ensemble à construire ou à compléter
			if(r>0)
			{
				agriEffT=(CL_AgriEff *)EnsembleFrm->Grille0->Objects[0][r];
				for(j=0;j<N_X;j++)
				agriEffT->Effectif[j]+=agriEff->Effectif[j];
				EnsembleFrm->AffAgriEff(r,agriEffT);
				EnsembleFrm->LabelModifie->Visible=true;
			}
			// il n'y est pas
			else
			{
				/// afficher les nouveaux entrés
				agriEffT =new CL_AgriEff (agriEff);
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

				EnsembleFrm->AffAgriEff(r,agriEffT);
				EnsembleFrm->LabelModifie->Visible=true;
			}
		}
	}
	Close();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=true;
	nbAgri=EnsembleFrm->Grille0->RowCount-2;
	as=EnsembleFrm->Ensemble->Nom+" nb types=  "+AnsiString(nbAgri);
	EnsembleFrm->LabEnsemble->Caption=as;
}

//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::Extraction(void)
{
	int n,i,j,r;
	int nbAgri;
	AnsiString as;
	CL_Ensemble *ensemble;
	CL_Agriculteur *agri;
	CL_AgriEff *agriEff,*agriEffT; //T comme total
	for( n=0;n<ChLB->Items->Count;n++)
	{
		if(ChLB->Checked[n]==false) continue;

		ensemble=(CL_Ensemble *)ChLB->Items->Objects[n];
		for(i=0;i<ensemble->V_AgriEff->Nbelt;i++)
		{
			agriEff=ensemble->V_AgriEff->Vecteur[i];
			agri=agriEff->Agri;
			// correspond aux critères de selection
			//cf TriAgri
			if(agri->Flag=='N') continue;

			r= EnsembleFrm->EstAffiche(agri);
			//il est déjà dans l'ensemble à construire ou à compléter
			if(r>0)
			{
				agriEffT=(CL_AgriEff *)EnsembleFrm->Grille0->Objects[0][r];
				for(j=0;j<N_X;j++)
				agriEffT->Effectif[j]+=agriEff->Effectif[j];
				EnsembleFrm->AffAgriEff(r,agriEffT);
				EnsembleFrm->LabelModifie->Visible=true;
			}
			// il n'y est pas
			else
			{
				/// afficher les nouveaux entrés
				agriEffT =new CL_AgriEff (agriEff);
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

				EnsembleFrm->AffAgriEff(r,agriEffT);
				EnsembleFrm->LabelModifie->Visible=true;
			}
		}
	}
	Close();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=true;
	nbAgri=EnsembleFrm->Grille0->RowCount-2;
	as=EnsembleFrm->Ensemble->Nom+" nb types=  "+AnsiString(nbAgri);
	EnsembleFrm->LabEnsemble->Caption=as;
}
//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::BtBnPasOKClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::BtBnTousClick(TObject *Sender)
{
	int n;
	for( n=0;n<ChLB->Items->Count;n++)
	ChLB->Checked[n]=true;

}
//---------------------------------------------------------------------------
void __fastcall TLBToutEnsembleFrm::BtBnAucunClick(TObject *Sender)
{
	int n;
	for( n=0;n<ChLB->Items->Count;n++)
	ChLB->Checked[n]=false;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBToutEnsembleFrm::IniCaption(void) {
	BtBnAucun->Caption = T->LC_BtIndAucun;
	LBToutEnsembleFrm->Caption = T->LC_GereEnsembleFrm;
	BtBnTous->Caption = T->LC_BtIndTous;
}
//--------------------------------------------
void TLBToutEnsembleFrm::TexteCaption(void) {
	LC_BtIndAucun = T->TrouveCaption("CL_Trad", "LC_BtIndAucun");
	LC_GereEnsembleFrm = T->TrouveCaption("CL_Trad", "LC_GereEnsembleFrm");
	LC_BtIndTous = T->TrouveCaption("CL_Trad", "LC_BtIndTous");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBToutEnsembleFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

