//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "TravCal.h"
#include "CL_Trad.h"

#include "ChoixMotif.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChoixMotifFrm *ChoixMotifFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TChoixMotifFrm::TChoixMotifFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TChoixMotifFrm::FormPaint(TObject *Sender)
{
	int x1,x2,y1,y2;
	int m;
	X0=10;Y0=20;
	Largeur=40;
	Hauteur=20;
	Canvas->Pen->Width=1;
	Canvas->Pen->Color=clBlack;
	Canvas->Brush->Color=clBlack;

	x1=X0;
	x2=x1+Largeur;
	for(m=0;m<TravCalFrm->MotifX;m++)
	{
		y1=Y0+m*Hauteur;
		y2=y1+Hauteur;
		Canvas->Brush->Style=(TBrushStyle)TravCalFrm->LesMotifs[m];
		Canvas->Rectangle(x1,y1,x2,y2);
	}
	ShowCursor(true);
}
//---------------------------------------------------------------------------
void __fastcall TChoixMotifFrm::FormMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int n;
	if(X<X0 ||X >X0+Largeur) return;
	if(Y<Y0 ||Y >Y0+Hauteur*TravCalFrm->MotifX) return;

	n=(Y-Y0)/Hauteur;
	Atelier->Motif=(int)TravCalFrm->LesMotifs[n];
	TravCalFrm->BtBnLegendeClick(this);
}
//---------------------------------------------------------------------------
void TChoixMotifFrm::IniCaption(void) {
	ChoixMotifFrm->Caption = LC_ChoixMotifFrm;
}
//--------------------------------------------
void TChoixMotifFrm::TexteCaption(void) {
	LC_ChoixMotifFrm = T->TrouveCaption("ChoixMotif", "LC_ChoixMotifFrm");

	IniCaption();

}

