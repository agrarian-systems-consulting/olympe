//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CL_Trad.h"

#include "Motif2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMotif2Frm *Motif2Frm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TMotif2Frm::TMotif2Frm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TMotif2Frm::FormCreate(TObject *Sender)
{
	int n;
	n=0;
	LesMotifs[n++]=bsSolid;
	LesMotifs[n++]=bsHorizontal;
	LesMotifs[n++]=bsVertical;
	LesMotifs[n++]=bsCross;
	LesMotifs[n++]=bsDiagCross;
	LesMotifs[n++]=bsBDiagonal;
	LesMotifs[n++]=bsFDiagonal;
	MotifX=n;

}
//---------------------------------------------------------------------------

void __fastcall TMotif2Frm::LegendeAtelier(void)
{
	int i;
	TRect rect;
	int x1,x2,y1,y2;
	int X0,Y0;
	int Hauteur,Largeur;

	Canvas->Brush->Style=bsCross;
	Canvas->Pen->Color=clWhite; //Yellow;
	Canvas->Brush->Color=clBlack;//clBlack;
	Canvas->Rectangle(10,220,50,250);

	Canvas->Pen->Width=1;
	Canvas->Pen->Color=clWhite;
	Canvas->Brush->Color=clBlack;
	X0=600;Y0=20;
	Largeur=50;Hauteur=20;
//	X0=10+GB->Left;Y0=20+GB->Top;
//	for(i=0;i<LstAtelier->Count;i++)
	for(i=0;i<5;i++)
	{
		x1=X0;x2=x1+Largeur;
		y1=Y0+i*Hauteur;
		y2=y1+Hauteur;
		Canvas->Brush->Style=(TBrushStyle)LesMotifs[i];
		Canvas->Rectangle(x1,y1,x2,y2);
	}
}

//---------------------------------------------------------------------------
void __fastcall TMotif2Frm::FormPaint(TObject *Sender)
{
	LegendeAtelier();

}
//---------------------------------------------------------------------------
void TMotif2Frm::IniCaption(void) {
	GroupBox1->Caption = LC_GroupBox1;
	Motif2Frm->Caption = LC_Motif2Frm;
}
//--------------------------------------------
void TMotif2Frm::TexteCaption(void) {
	LC_GroupBox1 = T->TrouveCaption("Motif2", "LC_GroupBox1");
	LC_Motif2Frm = T->TrouveCaption("Motif2", "LC_Motif2Frm");

	IniCaption();

}
//--------------------------------------------

