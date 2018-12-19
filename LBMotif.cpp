//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"

#include "TravCal.h"

//#include "LBMotif.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBMotifFrm *LBMotifFrm;
//---------------------------------------------------------------------------
__fastcall TLBMotifFrm::TLBMotifFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLBMotifFrm::FormPaint(TObject *Sender)
{
	Canvas->Brush->Style=bsCross;
	Canvas->Pen->Color=clWhite; //Yellow;
	Canvas->Brush->Color=clBlack;//clBlack;
	Canvas->Rectangle(10,220,50,250);

	int x1,y1,x2,y2;
	int m;
	X0=100;
	Y0=20;
	Largeur=40;
	Hauteur=30;
	Canvas->Pen->Width=1;
	Canvas->Pen->Color=clBlack;
	Canvas->Brush->Color=clBlack;

	x1=X0;
	x2=X0+Largeur;
	for(m=0;m<TravCalFrm->MotifX;m++)
	{
		y1=Y0+m*Hauteur;
		y2=y1+Hauteur;
		Canvas->Brush->Style=TravCalFrm->LesMotifs[m];
		Canvas->Brush->Color=clBlack;
		Canvas->Rectangle(x1,y1,x2,y2);
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBMotifFrm::FormMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int n;
	if(X<X0 ||X >X0+Largeur) return;
	if(Y<Y0 ||Y >Y0+Hauteur*TravCalFrm->MotifX) return;

	n=Y/30;
	ShowMessage(n);

}
//---------------------------------------------------------------------------

