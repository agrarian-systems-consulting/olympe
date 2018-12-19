//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"

#include "TravCal.h"
#include "CL_Trad.h"

#include "Motif.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMotifFrm *MotifFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TMotifFrm::TMotifFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TMotifFrm::FormCreate(TObject *Sender)
{
	int i,j,n;
	n=0;
	LesCouleurs[n++]=clRed; //1
	LesCouleurs[n++]=clBlue;
	LesCouleurs[n++]=clGreen;
	LesCouleurs[n++]=clPurple;
	LesCouleurs[n++]=clMaroon;//5
	LesCouleurs[n++]=clNavy;
	LesCouleurs[n++]=clOlive;
	LesCouleurs[n++]=clLime;
	LesCouleurs[n++]=clFuchsia;
	LesCouleurs[n++]=clTeal;//10
	LesCouleurs[n++]=clBlack;
	LesCouleurs[n++]=clWhite;//12
	CoulX=n;

	n=0;
	LesMotifs[n++]=bsSolid;
	LesMotifs[n++]=bsHorizontal;
	LesMotifs[n++]=bsVertical;
	LesMotifs[n++]=bsCross;
	LesMotifs[n++]=bsDiagCross;
	LesMotifs[n++]=bsBDiagonal;
	LesMotifs[n++]=bsFDiagonal;
//      LesMotifs[n++]=bsDense; // ?????
	MotifX=n;

	n=0;
	for(i=0;i<CoulX;i++)
	{
		for(j=0;j<MotifX;j++)
		{
			CoulLigne[n]=LesCouleurs[i];
			MotifLigne[n]=LesMotifs[j];
			n++;
			if(n>=SG->RowCount)break;
		}
		if(n>=SG->RowCount)break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMotifFrm::BtBnQuitterClick(TObject *Sender)
{
	ShowMessage("Motif Fin");

//
}
//---------------------------------------------------------------------------
void __fastcall TMotifFrm::FormPaint(TObject *Sender)
{
	/*
	 Canvas->Pen->Color=clBlue;
	 Canvas->Pen->Width=3;
	 Canvas->Brush->Color=clYellow;
	 Canvas->Rectangle(10,20,50,50);
	 //    Canvas->FillRect(Rect(10,20,50,50));

	 Canvas->Brush->Style=bsCross;
	 //    Canvas->Rectangle(10,120,50,150);
	 Canvas->FillRect(Rect(10,120,50,150));
	 */
	Canvas->Brush->Style=bsCross;
	Canvas->Pen->Color=clWhite; //Yellow;
	Canvas->Brush->Color=clBlack;//clBlack;
	Canvas->Rectangle(10,220,50,250);
//    Canvas->FillRect(Rect(10,220,50,250));

}
//---------------------------------------------------------------------------

void __fastcall TMotifFrm::SGDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State)
{
	SG->Color=clLime;

	SG->Canvas->Pen->Color=clBlack;
//    SG->Canvas->Pen->Color=clWhite;
//    SG->Canvas->Pen->Style=psClear;
	SG->Canvas->Pen->Width=1;

//    SG->Canvas->Pen->Color=clWhite;
	switch( ACol)
	{
		case 0:
		SG->Canvas->Brush->Color=(TColor)CoulLigne[ARow];
		SG->Canvas->Brush->Style=bsSolid;
		SG->Canvas->FillRect(Rect);
		break;
		case 1:
		/*
		 SG->FixedColor=clLime;
		 SG->Canvas->Brush->Color=clWhite;//on ne voit rien
		 SG->Canvas->Brush->Style=(TBrushStyle)MotifLigne[ARow];
		 SG->Canvas->FillRect(Rect);

		 SG->Color=clWhite;
		 */
		SG->Canvas->Pen->Color=clBlack;
		Canvas->Brush->Color=clBlack;
		Canvas->Brush->Style=(TBrushStyle)MotifLigne[ARow];
		Canvas->Rectangle(Rect);
		break;
		case 2:

		SG->Canvas->Brush->Color=(TColor)CoulLigne[ARow];
		SG->Canvas->Brush->Style=(TBrushStyle)MotifLigne[ARow];
		SG->Canvas->FillRect(Rect);
		break;
	}

}
//---------------------------------------------------------------------------

void __fastcall TMotifFrm::BtBleuClick(TObject *Sender)
{
	Color=clBlue;
	SG->Color=Color;
}
//---------------------------------------------------------------------------

void __fastcall TMotifFrm::BlancClick(TObject *Sender)
{
	Color=clWhite;
	SG->Color=Color;
}
//---------------------------------------------------------------------------

void __fastcall TMotifFrm::RougeClick(TObject *Sender)
{
	Color=clRed;
	SG->Color=Color;
}
//---------------------------------------------------------------------------

void __fastcall TMotifFrm::DGDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State)
{
	DG->Color=clLime;
	/*
	 DG->Canvas->Pen->Color=clBlack;
	 //    DG->Canvas->Pen->Color=clWhite;
	 DG->Canvas->Pen->Style=psClear;
	 DG->Canvas->Pen->Width=1;
	 */
	DG->Canvas->Pen->Color=clWhite;
	switch( ACol)
	{
		case 0:
		DG->Canvas->Brush->Color=(TColor)CoulLigne[ARow];
		DG->Canvas->Brush->Style=bsSolid;
		DG->Canvas->FillRect(Rect);
		break;
		case 1:
		//           DG->Canvas->Brush->Style=bsClear;
		DG->FixedColor=clLime;
		DG->Canvas->Brush->Color=clWhite;//on ne voit rien

		//           DG->Canvas->Style=clWhite;
		//DG->Canvas->Brush->Color=clWhite;//on voit

		DG->Canvas->Brush->Style=(TBrushStyle)MotifLigne[ARow];
		DG->Canvas->FillRect(Rect);
		break;
		case 2:

		DG->Canvas->Brush->Color=(TColor)CoulLigne[ARow];
		DG->Canvas->Brush->Style=(TBrushStyle)MotifLigne[ARow];
		DG->Canvas->FillRect(Rect);
		break;
	}

}
//---------------------------------------------------------------------------
void TMotifFrm::IniCaption(void) {
	Blanc->Caption = LC_Blanc;
	BtBleu->Caption = LC_BtBleu;
	MotifFrm->Caption = LC_MotifFrm;
	Rouge->Caption = LC_Rouge;
}
//--------------------------------------------
void TMotifFrm::TexteCaption(void) {
	LC_Blanc = T->TrouveCaption("Motif", "LC_Blanc");
	LC_BtBleu = T->TrouveCaption("Motif", "LC_BtBleu");
	LC_MotifFrm = T->TrouveCaption("Motif", "LC_MotifFrm");
	LC_Rouge = T->TrouveCaption("Motif", "LC_Rouge");

	IniCaption();

}
//--------------------------------------------

