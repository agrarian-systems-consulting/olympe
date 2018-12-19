//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include "Olympe.hse"
//#include "olympedec.h"
//#include "LesClassesApp.h"

#include "AgriSaisie.h"

#include "AniInv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMvtAniFrm *MvtAniFrm;
//---------------------------------------------------------------------------
__fastcall TMvtAniFrm::TMvtAniFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::FormCreate(TObject *Sender)
{
	Grille->FixedColor = (TColor)RGB(17,200,164);

	Grille->Cells[0][0]="Début";
	Grille->Cells[0][1]="Vente";
	Grille->Cells[0][2]="Achat";
	Grille->Cells[0][3]="Mort";
	Grille->Cells[0][4]="Entrée";
	Grille->Cells[0][5]="Sortie";
	Grille->Cells[0][6]="Fin";

}
//---------------------------------------------------------------------------
/*
 c=5 correspond à An_0
 Vente achat mort in out sont les mouvements de l'année n  il y a N_X
 Effectif[n] effectif à la fin de l'année n  il y en a N_X+1
 Effectif[0] effectif au début de la simulation fin de An_0-1
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::FormActivate(TObject *Sender)
{
	int c,r;
	AnsiString s;
	GrilleAgri=AgriSaisieFrm->LaGrille;
	RowPrec=Grille->Row;
	if(GrilleAgri->Col <5) return;

	r=GrilleAgri->Row;
	c=GrilleAgri->Col;
	N=c-5; //si c=5 je suis en début de la simulation:An_0 N=0
	Grille->EditorMode=true;

	InvAni=( CL_InvAni*)GrilleAgri->Objects[0][r];
	s=GrilleAgri->Cells[c-1][r];

	if(s.IsEmpty()==true) Debut=0;
	else Debut=s.ToDouble();

	Grille->Cells[1][0]=Debut;
	Grille->Cells[1][1]=InvAni->Vente[N];
	Grille->Cells[1][2]=InvAni->Achat[N];
	Grille->Cells[1][3]=InvAni->Mort[N];
	Grille->Cells[1][4]=InvAni->In[N];
	Grille->Cells[1][5]=InvAni->Out[N];
	Grille->Cells[1][6]=InvAni->Effectif[N+1];
	MEdOrig->Text="  ";
	MEdDest->Text="  ";

}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::FormKeyPress(TObject *Sender, char &Key)
{
	if(Key >='0' && Key <='9')return;
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::GrilleClick(TObject *Sender)
{
	int r=Grille->Row;
	InvAni->Vente[N] =Grille->Cells[1][1].ToDouble();
	InvAni->Achat[N] =Grille->Cells[1][2].ToDouble();
	InvAni->Mort [N] =Grille->Cells[1][3].ToDouble();
	InvAni->In [N] =Grille->Cells[1][4].ToDouble();
	InvAni->Out [N] =Grille->Cells[1][5].ToDouble();

	Grille->Cells[1][6]=FloatToStrF(EffFin(),ffNumber,7,0);
	RowPrec=r;
}
//---------------------------------------------------------------------------

void __fastcall TMvtAniFrm::GrilleSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect)
{
	if(ACol==0) CanSelect=false;
	if(ARow==0) CanSelect=false;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAniFrm::BtBnOKClick(TObject *Sender)
{
	int c=N+5;
	int r=GrilleAgri->Row;
	float fin;
	int dest,orig;
	CL_InvAni *invAni;
	AnsiString s;
	GrilleClick(this);
	fin=EffFin();
	InvAni->Effectif[N+1]=fin;
	Grille->Cells[1][6]= FloatToStrF(fin,ffNumber,7,0);
	GrilleAgri->Cells[c][r]=FloatToStrF(fin,ffNumber,7,0);
	s=MEdOrig->Text.Trim();
	orig=s.ToIntDef(-1);
	//orig=MEdOrig->Text.ToIntDef(-1);
	if(orig>0 && orig<GrilleAgri->RowCount-2)
	{
		invAni=( CL_InvAni*)GrilleAgri->Objects[0][orig];
		invAni->Out[N]+=InvAni->In[N];
	}
	s=MEdDest->Text.Trim();
	dest=s.ToIntDef(-1);
	if(dest>0 && dest<GrilleAgri->RowCount-2)
	{
		invAni=( CL_InvAni*)GrilleAgri->Objects[0][dest];
		invAni->In[N]+=InvAni->Out[N];
	}

}
//---------------------------------------------------------------------------
float __fastcall TMvtAniFrm::EffFin(void)
{
	float fin;
	fin= Debut
	-InvAni->Vente[N]
	+InvAni->Achat[N]
	-InvAni->Mort[N]
	+InvAni->In[N]
	-InvAni->Out[N];
	return fin;
}
//---------------------------------------------------------------------------

