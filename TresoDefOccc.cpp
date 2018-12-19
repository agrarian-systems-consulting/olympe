//---------------------------------------------------------------------------

#include <vcl.h>
#include <values.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "CL_PossibOcPlact.h"
#include "TresoRes.h"
#include "TresoRepart.h"
#include "TresoEnum.h"
#include "CL_Trad.h"

#include "TresoDefOccc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TTresoDefOcccFrm *TresoDefOcccFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTresoDefOcccFrm::TTresoDefOcccFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::FormActivate(TObject *Sender)
{
	LabelModifie->Visible=false;
	PossibOcPlact=AgriEnCours->PossibOcPlact;
	if(PossibOcPlact==NULL)
	{
		PossibOcPlact=new CL_PossibOcPlact();
		AgriEnCours->PossibOcPlact=PossibOcPlact;
	}

	LaGrille=Grille0;
	LaGrille->ColCount=11;
	LaGrille->RowCount=10;

	strcpy(TypeCol,"0NNNNNNNNNNNNN");

	LaGrille->ColWidths[0]=128;

	LaGrille->Cells[0][1]="Occc 1";
	LaGrille->Cells[0][2]="   Taux";
	LaGrille->Cells[0][3]="   Maxi";

	LaGrille->Cells[0][4]="Occc 2";
	LaGrille->Cells[0][5]="   Taux";
	LaGrille->Cells[0][6]="   Maxi";

	LaGrille->Cells[0][7]="Placement";
	LaGrille->Cells[0][8]="   Taux";
	LaGrille->Cells[0][9]="   Maxi";

	////////
	/*
	 int n;
	 for(n=0;n<N_X;n++)
	 {
	 PossibOcPlact->Taux[0][n]=12;
	 PossibOcPlact->Max[0][n]=1000;

	 PossibOcPlact->Taux[1][n]=24;
	 PossibOcPlact->Max[1][n]=2000;

	 PossibOcPlact->PlactTaux[n]=12;
	 PossibOcPlact->PlactMax[n]=999999;
	 }
	 //////
	 */
	VersGrille(LaGrille);
}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::VersGrille(TStringGrid *grille)
{

	int n,c;
	int an;
	an=AgriEnCours->DefSim->An_0;
	LaGrille->Objects[0][2]=(TObject*)PossibOcPlact->Taux[0];
	LaGrille->Objects[0][3]=(TObject*)PossibOcPlact->Max[0];

	LaGrille->Objects[0][5]=(TObject*)PossibOcPlact->Taux[1];
	LaGrille->Objects[0][6]=(TObject*)PossibOcPlact->Max[1];

	LaGrille->Objects[0][8]=(TObject*)PossibOcPlact->PlactTaux;
	LaGrille->Objects[0][9]=(TObject*)PossibOcPlact->PlactMax;

	for(n=0,c=1;n<N_X;n++,c++)
	{
		LaGrille->Cells[c][0]=Aff(an+n);

		LaGrille->Cells[c][1]="  ...";
		LaGrille->Cells[c][2]=Aff(PossibOcPlact->Taux [0][n],2);
		LaGrille->Cells[c][3]=Aff(PossibOcPlact->Max [0][n],0);

		LaGrille->Cells[c][4]="  ...";
		LaGrille->Cells[c][5]=Aff(PossibOcPlact->Taux [1][n],2);
		LaGrille->Cells[c][6]=Aff(PossibOcPlact->Max [1][n],0);

		LaGrille->Cells[c][7]="  ...";
		LaGrille->Cells[c][8]=Aff(PossibOcPlact->PlactTaux [n],2);
		LaGrille->Cells[c][9]=Aff(PossibOcPlact->PlactMax [n],0);
	}
}
//---------------------------------------------------------------------------
//     Aff tranforme un float ou un int en AnsiString
//-----------------------------------------------------------
AnsiString TTresoDefOcccFrm::Aff(float x, int digits) {
	if (x == 0)
		return AnsiString(" "); //"" ou " "      ????
	if (x == MAXFLOAT)
		return AnsiString("  Sans");
	return FloatToStrF((double) x, ffNumber, 7, digits);
}

//----------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::SansMaxiClick(TObject *Sender)
{
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	if(c==0) return;
	if(r==0 || r==1 || r==2 ||r==4 || r==5 ||r==7|| r==8 )return;
	LaGrille->Cells[c][r]="Sans";
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::BtReportDroitClick(TObject *Sender)
{
//
	int r=LaGrille->Row;
	int c0=LaGrille->Col;
	int c;
	if(LaGrille->Cells[c0][r].IsEmpty()==true) return;
	for(c=c0+1;c<Grille0->ColCount;c++)
	{
		if(RepPossible(c,r)==true)
		LaGrille->Cells[c][r]=LaGrille->Cells[c0][r];
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::BtRepToutDroitClick(TObject *Sender)
{
	int r,c,l;
	int lesLignes[]= {2,3,5,6,8,9};
	int c0=LaGrille->Col;
	for(l=0;l<6;l++)
	{
		r=lesLignes[l];
		for(c=c0+1;c<Grille0->ColCount;c++)
		{
			if(RepPossible(c,r)==true)
			LaGrille->Cells[c][r]=LaGrille->Cells[c0][r];
		}
	}
}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::DeGrille(TStringGrid *grille)
{
	int n,c;
	for(n=0,c=1;n<N_X;n++,c++)
	{
		PossibOcPlact->Taux [0][n]=GrilleFloat(c,2);
		PossibOcPlact->Max [0][n]=GrilleFloat(c,3);

		PossibOcPlact->Taux [1][n]=GrilleFloat(c,5);
		PossibOcPlact->Max [1][n]=GrilleFloat(c,6);

		PossibOcPlact->PlactTaux [n]=GrilleFloat(c,8);
		PossibOcPlact->PlactMax [n]=GrilleFloat(c,9);
	}
}
//-----------------------------------------------------------
float __fastcall TTresoDefOcccFrm::GrilleFloat(int col,int row)
{
	int n,c;
	AnsiString s;
	char car;
	char chaine[20];
	int point=0;
	double val;
	s=LaGrille->Cells[col][row];
	s=s.Trim();

	if(s=="Sans" )return MAXFLOAT;

	if(s=="" ||s=="."||s=="-") return 0.;
	c=0;
	for(n=1;n<s.Length()+1;n++)
	{
		car=s[n];
		if (car>='0' && car<='9') chaine[c++] =car;
		else if(car=='.' ||car==',')
		{
			if(point==0) {chaine[c++] ='.';point++;}
		}
		else if(car=='-' && c==0) chaine[c++] ='-';
	}
	chaine[c]=0;
	s=AnsiString(chaine);
	try
	{
		val=s.ToDouble();
	}
	catch(...)
	{
		val=0;
	}
	return val;
}

//---------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(LabelModifie->Visible==false) return;
	DeGrille(LaGrille);
}
//---------------------------------------------------------------------------
void __fastcall TTresoDefOcccFrm::BtBnCalculClick(TObject *Sender)
{

	if(LabelModifie->Visible==true)
	DeGrille(LaGrille);

	TresoResFrm->Origine=0;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->TypeSortie=OCCC;
	TresoResFrm->Nature=OCCC; //pour faire calculer tout
	TresoResFrm->Show();
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TTresoDefOcccFrm::IniCaption(void) {
	BtBnCalcul->Caption = T->LC_BtBnResultat;
	SansMaxi->Caption = LC_SansMaxi;
	TresoDefOcccFrm->Caption = LC_TresoDefOcccFrm;
	ChBRepTout->Caption = T->LC_ChBRepTout;
}
//--------------------------------------------
void TTresoDefOcccFrm::TexteCaption(void) {
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_SansMaxi = T->TrouveCaption("TresoDefOccc", "LC_SansMaxi");
	LC_TresoDefOcccFrm = T->TrouveCaption("TresoDefOccc", "LC_TresoDefOcccFrm");

	IniCaption();

}
//--------------------------------------------

void __fastcall TTresoDefOcccFrm::Grille0KeyPress(TObject *Sender,
		char &Key)
{
	int r,c;
	r=Grille0->Row;
	if(r==1 ||r==4 ||r==7) Key=0;
	if(Key<'0' || Key >'9') Key=0;
}
//---------------------------------------------------------------------------

