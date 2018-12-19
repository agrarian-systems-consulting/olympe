//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"

#include "QRGrille00.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQRGrille00Frm *QRGrille00Frm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRGrille00Frm::TQRGrille00Frm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRGrille00Frm::Initialise(void)
{
	if(AgriEnCours)
	NomAgri->Caption=AgriEnCours->Nom.c_str();
	else
	NomAgri->Caption="";

	/*  pb Gateway test infructueux
	 if (QRGrille00Frm->Height > Screen->Height)
	 QRGrille00Frm->Height = Screen->Height;
	 if (QRGrille00Frm->Width > Screen->Width)
	 QRGrille00Frm->Width = Screen->Width;
	 */

	NLigne=0;

	LstVal=new TObjectList;
	LstVal->Add(Val0);
	LstVal->Add(Val1);
	LstVal->Add(Val2);
	LstVal->Add(Val3);
	LstVal->Add(Val4);
	LstVal->Add(Val5);
	LstVal->Add(Val6);
	LstVal->Add(Val7);
	LstVal->Add(Val8);
	LstVal->Add(Val9);
	LstVal->Add(Val10);
	LstVal->Add(Val11);
	LstVal->Add(Val12);
	LstVal->Add(Val13); //270502
	LstVal->Add(Val14);
	LstVal->Add(Val15);
	if (LstVal->Count < LaGrille->ColCount) ColCount=LstVal->Count-1;
	else ColCount=LaGrille->ColCount;

}
//---------------------------------------------------------------------------
void __fastcall TQRGrille00Frm::QRNeedData(TObject *Sender, bool &MoreData)
{
	/*
	 if(LstVal->Count<LaGrille->ColCount)
	 {
	 ShowMessage("Trop de colonnes");
	 MoreData=false;
	 return;
	 }
	 */
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRGrille00Frm::CompleteDonnees(void)
{
	int c,r;
	TQRLabel *tqr;
	static int position[50];
	int largeur;
	if(NLigne==0)
	{
		position[0]=0;
		//si largeur d'une colonne est trop petite l'agrandir
		for(c=0;c<ColCount;c++)
		{
			largeur=LaGrille->ColWidths[c];
			position[c+1]=position[c]+largeur*1.2;
		}
	}

	if(NLigne>=LaGrille->RowCount) return false;

	r=NLigne;
	for(c=0;c<ColCount;c++)
	{
		tqr=(TQRLabel*)LstVal->Items[c];
		tqr->Caption=LaGrille->Cells[c][r];
		tqr->Left=position[c];
	}
	for(c=ColCount;c<LstVal->Count;c++)
	{
		tqr=(TQRLabel*)LstVal->Items[c];
		tqr->Caption="";
	}

	if(r==0)
	{
		DetailBand1->Color=clLime;
		DetailBand1->Frame->DrawTop=true;
		DetailBand1->Frame->DrawBottom=true;
		for(c=0;c<ColCount;c++)
		{
			tqr=(TQRLabel*)LstVal->Items[c];
			tqr->Color=clLime;
			if(TypeCol[c]=='T') tqr->Alignment=taCenter;
			else tqr->Alignment=taRightJustify;
		}
	}
	else
	{
		DetailBand1->Color=clInfoBk;
		DetailBand1->Frame->DrawTop=false;
		DetailBand1->Frame->DrawBottom=false;
		for(c=0;c<ColCount;c++)
		{
			tqr=(TQRLabel*)LstVal->Items[c];
			tqr->Color=clInfoBk;
		}
	}
	NLigne++;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TQRGrille00Frm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=0;
	PrintReport=true;
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TQRGrille00Frm::IniCaption(void) {
	NomAgri->Caption = T->LC_NomAgri_A;
	QRGrille00Frm->Caption = LC_QRGrille00Frm;
	TitreEtat->Caption = T->LC_TitreEtat;
	Val0->Caption = T->LC_Val0;
	Val1->Caption = T->LC_Val1;
	Val10->Caption = T->LC_Val10;
	Val11->Caption = T->LC_Val11;
	Val12->Caption = LC_Val12;
	Val13->Caption = LC_Val13;
	Val14->Caption = LC_Val14;
	Val15->Caption = LC_Val15;
	Val2->Caption = T->LC_Val2;
	Val3->Caption = T->LC_Val3;
	Val4->Caption = T->LC_Val4;
	Val5->Caption = T->LC_Val5;
	Val6->Caption = T->LC_Val6;
	Val7->Caption = T->LC_Val7;
	Val8->Caption = T->LC_Val8;
	Val9->Caption = T->LC_Val9;
}
//--------------------------------------------
void TQRGrille00Frm::TexteCaption(void) {
	LC_NomAgri_A = T->TrouveCaption("CL_Trad", "LC_NomAgri_A");
	LC_QRGrille00Frm = T->TrouveCaption("QRGrille00", "LC_QRGrille00Frm");
	LC_TitreEtat = T->TrouveCaption("CL_Trad", "LC_TitreEtat");
	LC_Val0 = T->TrouveCaption("CL_Trad", "LC_Val0");
	LC_Val1 = T->TrouveCaption("CL_Trad", "LC_Val1");
	LC_Val10 = T->TrouveCaption("CL_Trad", "LC_Val10");
	LC_Val11 = T->TrouveCaption("CL_Trad", "LC_Val11");
	LC_Val12 = T->TrouveCaption("QRGrille00", "LC_Val12");
	LC_Val13 = T->TrouveCaption("QRGrille00", "LC_Val13");
	LC_Val14 = T->TrouveCaption("QRGrille00", "LC_Val14");
	LC_Val15 = T->TrouveCaption("QRGrille00", "LC_Val15");
	LC_Val2 = T->TrouveCaption("CL_Trad", "LC_Val2");
	LC_Val3 = T->TrouveCaption("CL_Trad", "LC_Val3");
	LC_Val4 = T->TrouveCaption("CL_Trad", "LC_Val4");
	LC_Val5 = T->TrouveCaption("CL_Trad", "LC_Val5");
	LC_Val6 = T->TrouveCaption("CL_Trad", "LC_Val6");
	LC_Val7 = T->TrouveCaption("CL_Trad", "LC_Val7");
	LC_Val8 = T->TrouveCaption("CL_Trad", "LC_Val8");
	LC_Val9 = T->TrouveCaption("CL_Trad", "LC_Val9");

	IniCaption();

}
//--------------------------------------------

void __fastcall TQRGrille00Frm::FormClick(TObject *Sender)
{
	ShowMessage("TQRGrille00Frm::FormClick");
}
//---------------------------------------------------------------------------

