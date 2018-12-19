//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "AgriSaisie.h"

#include "InvAniMax.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TInvAniMaxFrm *InvAniMaxFrm;
//---------------------------------------------------------------------------
__fastcall TInvAniMaxFrm::TInvAniMaxFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::FormActivate(TObject *Sender)
{
	int r;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur;

	LabelModifie->Visible=false;

	Agri= AgriSaisieFrm->Agri;
	An_0=Agri->DefSim->An_0;
	if(Origine==0)
	{
		vecteur=Agri->V_InvAni;
		for(r=0;r<vecteur->Nbelt;r++)
		{
			invAni=vecteur->Vecteur[r];
			invAni->ValVenteDefaut=invAni->ValInv;
		}
	}
	Origine =1;

	Demarrer();

	VersGrille(GrilleMax);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::Demarrer(void)
{
	Personnaliser();
	DefinirLesGrilles();
	IniGrille(GrilleMax);
}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::Personnaliser(void)
{
	GrilleMax=Grille0;
	//pour ne pas avoir de message de Forme00
}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::DefinirLesGrilles(void)
{

	AjoutRow=false;
	GrilleX=1;

	LesGrilles[0]=GrilleMax;
	LaGrille=GrilleMax;
	GrilleMax->ColCount=14;
	ColM[0]=2;
	RowM[0]=1;
	VideLesGrilles();
}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[] = {20,10,128,48,48,48,48,48,48,48,48,48,48,48,48,48};

	// T alpha N numérique 0 non modifiable
	strcpy(TypeCol, "000NNNNNNNNNNNNNNNNN");

	LaGrille->ColCount=14;
	LaGrille->RowCount=Agri->V_InvAni->Nbelt+1;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);
	LaGrille->Cells[2][0]="NOM";
	LaGrille->Cells[3][0]="Prix Vente";

	for(int i=0;i<10;i++)
	LaGrille->Cells[i+4][0]="  "+AnsiString(An_0+i);

}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::VersGrille(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;

	vecteur=Agri->V_InvAni;

	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		GrilleMax->Objects[0][row]=(TObject*)invAni;
		GrilleMax->Cells[0][row]=row;

		GrilleMax->Cells[2][row]=animal->Nom;
		GrilleMax->Cells[3][row]=invAni->ValVenteDefaut;
		for(n=0,c=4;n<N_X;n++,c++)
		{
			if(invAni->EffMax[n]==SANSBORNE)continue;
			if(invAni->EffMax[n]==0) {GrilleMax->Cells[c][row]="  0";continue;}

			GrilleMax->Cells[c][row]=Aff(invAni->EffMax[n]);
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::DeGrille(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	int colPrix=3;

	for(row=1;row<GrilleMax->RowCount;row++)
	{
		invAni=(CL_InvAni*)GrilleMax->Objects[0][row];
		invAni->ValVenteDefaut=GrilleFloat(colPrix,row);
		for(n=0;n<N_X;n++)
		{
			c=colPrix+1+n;
			if(GrilleMax->Cells[c][row]=="")
			invAni->EffMax[n]=SANSBORNE;
			else
			invAni->EffMax[n]=GrilleFloat(c,row);
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(LabelModifie->Visible==false) return;
	DeGrille(GrilleMax);
}
//---------------------------------------------------------------------------
void __fastcall TInvAniMaxFrm::BtReportDroitClick(TObject *Sender)
{
	int c,c0,r0;
	c0=Grille0->Col;
	r0=Grille0->Row;
	//ReAffFloat(c0,r0,digits);
	for(c=c0+1;c<Grille0->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		Grille0->Cells[c][r0]=Grille0->Cells[c0][r0];
	}
	/*
	 Grille0Click(this);

	 int digits=0;
	 RepDroit(Grille0,digits);
	 */
}
//---------------------------------------------------------------------------

void __fastcall TInvAniMaxFrm::BtBnSansBorneClick(TObject *Sender)
{
	int c,r;
	int n;
	CL_InvAni *invAni;
	c=GrilleMax->Col;
	r=GrilleMax->Row;
	invAni=(CL_InvAni*)GrilleMax->Objects[0][r];
	n=c-4;
	if(n<0)return;
	if(r==0)return;
	invAni->EffMax[n]=SANSBORNE;
	GrilleMax->Cells[c][r]="";
	LabelModifie->Visible=true;

//
}
//---------------------------------------------------------------------------

