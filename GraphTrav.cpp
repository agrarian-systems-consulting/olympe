//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphTrav.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGraphTravFrm *GraphTravFrm;
//---------------------------------------------------------------------------
__fastcall TGraphTravFrm::TGraphTravFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGraphTravFrm::Dessiner(void)
{
	/*
	 int n;
	 n=Xde(3);
	 n=Yde(27);
	 n=Xde(37);
	 n=Yde(3);
	 */
	GraphTravFrm->Canvas->Pen->Color=clRed;
	GraphTravFrm->Canvas->Pen->Style = psSolid;
	GraphTravFrm->Canvas->Pen->Width = 5;
	GraphTravFrm->Canvas->Rectangle(Xde(3),Yde(27),Xde(37),Yde(3));

//    GraphTravFrm->Canvas->MoveTo(Xde(3),Yde(3));
//    GraphTravFrm->Canvas->LineTo(Xde(37),Yde(3));

}
//---------------------------------------------------------------------------
//           UTILITAIRE de CONVERSION
//---------------------------------------------------------------------------
int __fastcall TGraphTravFrm::Xde(int x)
{
	// toutes les coordonnees sont exprimees en foction d'un ecran 40*30
//    x=(x*Screen->Width)/40;
	x=(x*Width)/40;
	return x;
}
//---------------------------------------------------------------------------
int __fastcall TGraphTravFrm::Yde(int y)
{
	// toutes les coordonnees sont exprimees en fonction d'un ecran 40*30
	// l'axe des y commence en bas
//    y= Screen->Height-(y*Screen->Height)/30;
	y= Height-(y*Height)/30;
	return y;
}

