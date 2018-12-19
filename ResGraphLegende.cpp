//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <values.h>
#pragma hdrstop

#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Resultat.h"

#include "ResGraph.h"

#include "ResGraphLegende.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResGraphLegendeFrm *ResGraphLegendeFrm;
//---------------------------------------------------------------------------
__fastcall TResGraphLegendeFrm::TResGraphLegendeFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TResGraphLegendeFrm::FormActivate(TObject *Sender)
{
	TListBox *lbG,*lbD;
	lbG=ResultatFrm->LBGauche,
	lbD=ResultatFrm->LBDroit;
	Legende(lbG,lbD);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TResGraphLegendeFrm::Legende(TListBox *lbG,TListBox *lbD)
{
	int n;
	int coul;
	int y=10;
	int deltaY=20;
	int xTrait=200;
	int xNom=10;
	int lonTrait=30;
	AnsiString asNom;
	CL_Elt *elt;
	Canvas->Font->Color=clBlack;
	Canvas->Font->Name="Arial";
	Canvas->Font->Size=8;

	Canvas->Pen->Style=psSolid;
	Canvas->Pen->Width =2;
	coul=0;
	for(n=0;n<lbG->Items->Count;n++)
	{
		Canvas->Pen->Color=(TColor)ResGraphFrm->LesCouleurs[coul++];
		elt=(CL_Elt*)lbG->Items->Objects[n];
		asNom=elt->Donne_Nom();
//        as=elt->Poste->Nom;
//		if(elt->Item) as=as+" :"+elt->Item->Nom;
		Canvas->TextOut(xNom,y,asNom);
		Canvas->MoveTo(xTrait,y);
		Canvas->LineTo(xTrait+lonTrait,y);
		y+=deltaY;
	}
	y+=deltaY;
	for(n=0;n<lbD->Items->Count;n++)
	{
		Canvas->Pen->Color=(TColor)ResGraphFrm->LesCouleurs[coul++];
		elt=(CL_Elt*)lbD->Items->Objects[n];
		asNom=elt->Donne_Nom();

//        as=elt->Poste->Nom;
//		if(elt->Item) as=as+" :"+elt->Item->Nom;
		Canvas->TextOut(xNom,y,asNom);
		Canvas->MoveTo(xTrait,y);
		Canvas->LineTo(xTrait+lonTrait,y);
		y+=deltaY;
	}
}

void __fastcall TResGraphLegendeFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
//	CanClose=false;	
}
//---------------------------------------------------------------------------

