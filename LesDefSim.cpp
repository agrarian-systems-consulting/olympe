//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriDefSim.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LesDefSim.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TLesDefSimFrm *LesDefSimFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLesDefSimFrm::TLesDefSimFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::Personnaliser(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::DefinirLesGrilles(void)
{

	AjoutRow=true;
	Grille0->Visible=false;
	GrilleX=1;

	LesGrilles[0]=Grille0;

	LaGrille=Grille0;
}
//---------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::IniGrille(TStringGrid *grille)
{
	int l,col;
	AnsiString as;
//                 prix   .       quantite   scenario
	int largeur[] = {16,92,16,92, 16,92,16,92,16,92, 92};

	grille->ColCount=2*2 +2*3 +1;

	grille->FixedRows=1;
	grille->FixedCols=0; //4; //5;
	for(int c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	l=l+grille->Left+25; //25

//    as="T/S";
//    for(int col=0;col<=8;col+=2)
//        grille->Cells[col][0]="T/S";
	col=1;
	grille->Cells[col][0]="PRODUIT"; col+=2;
	grille->Cells[col][0]="CHARGE"; col+=2;
	grille->Cells[col][0]="PRODUIT"; col+=2;
	grille->Cells[col][0]="CHARGE"; col+=2;
	grille->Cells[col][0]="EXTERNALITE"; col+=1;
	grille->Cells[col][0]="SCENARIO"; col+=2;
}
//***************************************************************************
//  VERSGRILLE
//------------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	CL_Vecteur<CL_AgriDefSim> *vecteur;
	CL_AgriDefSim *defSim;
	AnsiString value;
	VideLesGrilles();

	LaGrille=grille;
	LaGrille->RowCount=2;
	row=0;
	vecteur=V_DefSim;
	LaGrille->RowCount=vecteur->Nbelt+3;
	for( r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		defSim=vecteur->Vecteur[r];

		AffEnch=false;
		LaGrille->Objects[0][row]=(TObject*)defSim;
		AffTouS(defSim->TouSPrixProd, 0,row);
		AffTouS(defSim->TouSPrixCharge,2,row);
		AffTouS(defSim->TouSQProd, 4,row);
		AffTouS(defSim->TouSQCharge, 6,row);
		AffTouS(defSim->TouSQExt, 8,row);

		AffTend(defSim->PrixProd, 1,row);
		AffTend(defSim->PrixCharge,3,row);
		AffTend(defSim->QProd, 5,row);
		AffTend(defSim->QCharge, 7,row);
		AffTend(defSim->QExt, 9,row);
		if(AffEnch==true)
		LaGrille->Cells[10][row]=defSim->Enchainement;
	}

	Grille0->Visible=true;

}
//------------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::AffTouS(int no,int col,int row)
{
	switch(no)
	{
		case 0:LaGrille->Cells[col][row]=" ";break;
		case 1:LaGrille->Cells[col][row]="T";break;
		case 2:LaGrille->Cells[col][row]="S";AffEnch=true;break;
	}
}
//------------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::AffTend(CL_Tendance *tend,int col,int row)
{
	if(tend) LaGrille->Cells[col][row]=tend->Nom;
}
//------------------------------------------------------------------------------
void __fastcall TLesDefSimFrm::Grille0Click(TObject *Sender)
{
	SelLigne();
}
//---------------------------------------------------------------------------

void __fastcall TLesDefSimFrm::BtBnReprendreClick(TObject *Sender)
{
	CL_AgriDefSim *defSim;
	int row=LaGrille->Row;
	if(row>V_DefSim->Nbelt)
	{
		ShowMessage(" Rien à reprendre");
		return;
	}
	defSim=(CL_AgriDefSim *)LaGrille->Objects[0][row];
	AgriDefSimFrm->DefSim=defSim;
	AgriDefSimFrm->IniEcran();
	//AgriDefSimFrm->Show();
	Close();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLesDefSimFrm::IniCaption(void) {
	LesDefSimFrm->Caption = LC_LesDefSimFrm;
	LabPrix->Caption = T->LC_GBPrix;
	LabQuantite->Caption = T->LC_GBQuantite;
	BtBnReprendre->Caption = LC_BtBnReprendre;
}
//--------------------------------------------
void TLesDefSimFrm::TexteCaption(void) {
	LC_LesDefSimFrm = T->TrouveCaption("LesDefSim", "LC_LesDefSimFrm");
	LC_GBPrix = T->TrouveCaption("CL_Trad", "LC_GBPrix");
	LC_GBQuantite = T->TrouveCaption("CL_Trad", "LC_GBQuantite");
	LC_BtBnReprendre = T->TrouveCaption("LesDefSim", "LC_BtBnReprendre");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLesDefSimFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

