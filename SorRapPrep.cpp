//---------------------------------------------------------------------------

#include <vcl.h>
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

//#include "Graph.h"
#include "SorRap.h"

#include "SorRapPrep.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern CL_ES *ES;

TSorRapPrepFrm *SorRapPrepFrm;
//---------------------------------------------------------------------------
__fastcall TSorRapPrepFrm::TSorRapPrepFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TSorRapPrepFrm::FormCreate(TObject *Sender)
{
	int r;

	SLstRaccourci= new TStringList;

	SG->ColCount=5;
	SG->RowCount=21;

	SG->ColWidths[0]=32;
	SG->ColWidths[1]=128;
	SG->ColWidths[2]=128;
	SG->ColWidths[3]=128;
	SG->ColWidths[4]=64;

	SG->Cells[1][0]="Famille";
	SG->Cells[2][0]="Categorie";
	SG->Cells[3][0]="Nom";
	SG->Cells[4][0]="Alias";

	for(r=0;r<SG->RowCount;r++)SG->Cells[0][r]=r;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSorRapPrepFrm::FormActivate(TObject *Sender)
{
	ES->IniV_Elt();
	Forme0Frm->CreeTVToutElt(TV,AgriEnCours,true); //Complet);
}
//---------------------------------------------------------------------------
void __fastcall TSorRapPrepFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
//	TVDicoFrm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TSorRapPrepFrm::SGClick(TObject *Sender)
{
//int r,c;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TSorRapPrepFrm::RetourDeTVDico(char *nomFamille, char* nomCategorie,
		char* nom) {
	int r; //,c;
	r = SG->Row;
	SG->Cells[1][r] = nomFamille;
	SG->Cells[2][r] = nomCategorie;
	SG->Cells[3][r] = nom;
	SG->Cells[4][r] = nom;
	SG->Row++;
}
//---------------------------------------------------------------------------
void __fastcall TSorRapPrepFrm::SGKeyPress(TObject *Sender, char &Key)
{
	int c; //,r;
	c=SG->Col;
	if(c!=4) {Key=0;return;}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSorRapPrepFrm::TVChange(TObject *Sender, TTreeNode *Node)
{
	int r; //,c;
	TTreeNode *choix;
	CL_Elt *elt;

	choix=Node;
	if(choix->Level<2)
	return;
	elt=(CL_Elt*)choix->Data;
	if(elt==NULL) return;

	r=SG->Row;
	SG->Cells[1][r]=elt->NomFamille;
	SG->Cells[2][r]=elt->NomCat;
	SG->Cells[3][r]=elt->Nom;
	SG->Cells[4][r]=elt->Nom;
	SG->Objects[0][r]=(TObject*)elt;
	SG->Row++;

	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TSorRapPrepFrm::Button1Click(TObject *Sender)
{
	SorRapFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TSorRapPrepFrm::BtBnVideToutClick(TObject *Sender)
{
	int r,c;
	int rep;
	rep=MessageBox(Handle," Je supprime TOUT Vous êtes sur ?","SUPPRESSION",MB_YESNO);
//	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO)
	return;

	for(r=1;r<SG->RowCount;r++)
	{
		SG->Objects[0][r]=NULL;
		for(c=1;c<SG->ColCount;c++)
		SG->Cells[c][r]="";
	}
	SG->Row=1;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TSorRapPrepFrm::BtSupClick(TObject *Sender)
{
	int r,r0,c;
	r0=SG->Row;
	for(r=r0;r<SG->RowCount-1;r++)
	{
		SG->Objects[0][r]=SG->Objects[0][r+1];
		for(c=1;c<SG->ColCount;c++)
		SG->Cells[c][r]=SG->Cells[c][r+1];
	}
	r=SG->RowCount-1;
	for(c=1;c<SG->ColCount;c++)
	SG->Cells[c][r]="";
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TSorRapPrepFrm::BtBnClBasClick(TObject *Sender)
{
	int c,r;
	TObject *object;
	AnsiString as;
	r=SG->Row;
	if(r==SG->RowCount) return;

	LabelModifie->Visible=true;
	object=SG->Objects[0][r];
	SG->Objects[0][r]=SG->Objects[0][r+1];
	SG->Objects[0][r+1]=object;
	for(c=1;c<SG->RowCount;c++)
	{
		as=SG->Cells[c][r];
		SG->Cells[c][r]=SG->Cells[c][r+1];
		SG->Cells[c][r+1]=as;
	}
	SG->Row++;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TSorRapPrepFrm::BtBnClHautClick(TObject *Sender)
{
	int c,r;
	TObject *object;
	AnsiString as;
	r=SG->Row;
	if(r==1) return;

	LabelModifie->Visible=true;
	object=SG->Objects[0][r];
	SG->Objects[0][r]=SG->Objects[0][r-1];
	SG->Objects[0][r-1]=object;
	for(c=1;c<SG->RowCount;c++)
	{
		as=SG->Cells[c][r];
		SG->Cells[c][r]=SG->Cells[c][r-1];
		SG->Cells[c][r-1]=as;
	}
	SG->Row--;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TSorRapPrepFrm::BtBnStockerClick(TObject *Sender)
{
	if(LabelModifie->Visible==true)
	DeSG();
//??	FichierFrm->EcrireDonnees(FichierFrm->AsFicTrav.c_str());

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TSorRapPrepFrm::DeSG(void) {
	int r;
	CL_Elt *elt;
	SLstRaccourci->Clear();
	for (r = 1; r < SG->RowCount; r++) {
		elt = (CL_Elt*) SG->Objects[0][r];
		if (elt == NULL) //titre
				{
			if (SG->Cells[1][r] == "")
				continue;
//??	    	elt=new CL_Raccourci(SG->Cells[1][r]);
		}
		elt->NomNature = SG->Cells[4][r].c_str(); //Alias
		SLstRaccourci->AddObject(elt->NomNature, (TObject*) elt);
	}
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TSorRapPrepFrm::TailleSG(int r) {
	SG->Row++;
	if (r > SG->RowCount - 3) {
		SG->RowCount++;
		SG->Cells[0][r] = r;
		SG->Cells[0][r + 1] = r + 1;
		SG->Objects[0][r] = NULL;
		SG->Objects[0][r + 1] = NULL;
	}
}

//---------------------------------------------------------------------------
void TSorRapPrepFrm::VersSG(void) {
	int r;
	int n;
	CL_Elt *elt;
//CL_Etat *etat;
//	n=0;
	//penser trait blanc
//	etat=(CL_Etat*)DonFrm->SLstEtat->Objects[n];
	SG->RowCount = 21;
	if (SLstRaccourci->Count > SG->RowCount)
		SG->RowCount = SLstRaccourci->Count + 5;
	for (r = 1; r < SG->RowCount; r++)
		SG->Cells[0][r] = r;

	for (n = 0, r = 1; n < SLstRaccourci->Count; n++, r++) {
		elt = (CL_Elt*) SLstRaccourci->Objects[n];
		SG->Objects[0][r] = SLstRaccourci->Objects[n];
		SG->Cells[0][r] = r;
		SG->Cells[1][r] = elt->NomFamille;
		SG->Cells[2][r] = elt->NomCat;
		SG->Cells[3][r] = elt->Nom;
		SG->Cells[4][r] = elt->NomNature; //Alias
	}
}

