//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TVChoixAniProCha.h"
#include "AgriSaisie.h"

#include "InvAniProCha.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "InvAniMax"
#pragma resource "*.dfm"
TInvAniProChaFrm *InvAniProChaFrm;
//---------------------------------------------------------------------------
__fastcall TInvAniProChaFrm::TInvAniProChaFrm(TComponent* Owner) :
		TInvAniMaxFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::FormActivate(TObject *Sender)
{
	if(Origine==1) return;
	Origine=1;
	LabelModifie->Visible=false;

	Agri= AgriSaisieFrm->Agri;
	An_0=Agri->DefSim->An_0;
	GrilleMax=Grille0; //pour ne pas avoir de message de Forme00 ??
	LaGrille=Grille0;
	IniGrille(LaGrille);
	VersGrille(LaGrille);

}
//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(LabelModifie->Visible==false) return;
	DeGrille(GrilleMax);
}

//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::DefinirLesGrilles(void)
{

	AjoutRow=false;
	GrilleX=1;

	TVChoixAniProChaFrm->LaGrille=Grille0;
	LesGrilles[0]=GrilleMax;
	LaGrille=GrilleMax;
	LaGrille->ColCount=12;
	ColM[0]=1; //???
	RowM[0]=1;
	VideLesGrilles();
}
//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
//int largeur[] ={20,128,48,48,48,48,48,48,48,48,48,48,48,48,48};
	int largeur[] = {20,128,64,64,64,64,64,64,64,64,64,64};

	// T alpha N numérique 0 non modifiable
	strcpy(TypeCol, "00TTTTTTTTTTTTTTTTTT");

	LaGrille->ColCount=12;
	LaGrille->RowCount=Agri->V_InvAni->Nbelt+1;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=1;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);
	LaGrille->Cells[2][0]="NOM";

	for(int i=0;i<10;i++)
	LaGrille->Cells[i+2][0]="  "+AnsiString(An_0+i);

}

//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::VersGrille(TStringGrid *grille)
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
		LaGrille->Objects[0][row]=(TObject*)invAni;
		LaGrille->Cells[0][row]=row; //n0 de la ligne

		LaGrille->Cells[1][row]=animal->Nom;
		for(n=0,c=2;n<N_X;n++,c++)
		{
			LaGrille->Objects[c][row]=(TObject*)invAni->Atelier[n];
			if(invAni->Atelier[n])
			LaGrille->Cells[c][row]=invAni->Atelier[n]->Nom;

		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::DeGrille(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	for(row=1;row<GrilleMax->RowCount;row++)
	{
		invAni=(CL_InvAni*)LaGrille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		{
			invAni->Atelier[n]=(CL_Atelier*)LaGrille->Objects[c][row];
			if(invAni->Atelier[n])
			invAni->NoAtelier[n]=invAni->Atelier[n]->No;
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::BtBnProchaClick(TObject *Sender)
{
	CreeTVAtelier (TVChoixAniProChaFrm->TV, V_CatAnimaux,V_Animaux);
	TVChoixAniProChaFrm->LaGrille=LaGrille;
	TVChoixAniProChaFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TInvAniProChaFrm::BtReportDroitClick(TObject *Sender)
{
	int c,c0,r0;
	c0=Grille0->Col;
	r0=Grille0->Row;
	//ReAffFloat(c0,r0,digits);
	for(c=c0+1;c<Grille0->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		Grille0->Cells[c][r0]=Grille0->Cells[c0][r0];
		Grille0->Objects[c][r0]=Grille0->Objects[c0][r0];
	}
}
//---------------------------------------------------------------------------

