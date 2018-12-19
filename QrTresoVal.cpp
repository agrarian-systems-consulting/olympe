//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "CL_TresoMens.h"
#include "CL_Trad.h"

#include "QrTresoVal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQRTresoValFrm *QRTresoValFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRTresoValFrm::TQRTresoValFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TQRTresoValFrm::FormCreate(TObject *Sender)
{
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

	//lire LabMois et non LabAn  QRtresoVal hérite de QRTreso
	LstMois=new TObjectList;
	LstMois->Add(LabM0);
	LstMois->Add(LabM1);
	LstMois->Add(LabM2);
	LstMois->Add(LabM3);
	LstMois->Add(LabM4);
	LstMois->Add(LabM5);
	LstMois->Add(LabM6);
	LstMois->Add(LabM7);
	LstMois->Add(LabM8);
	LstMois->Add(LabM9);
	LstMois->Add(LabM10);
	LstMois->Add(LabM11);

}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
//  met les mois
// cree LstCaption  pour afficher les données an/an
//---------------------------------------------------------------------------
void __fastcall TQRTresoValFrm::Initialise(void)
{
	int n,m,an,mFin,anFin;
	static char* LesMois[12]= {"Janv","Fev","Mars","Avril","Mai","Juin","Juil","Aout","Sept","Oct","Nov","Déc"};
	TQRLabel *labMois,*labVal;
	int posG, ecart;
	AnsiString titre;

	NomAgri->Caption=AgriSaisieFrm->Caption;
	//an=2004;
//    an=Agri->DefSim->An_0-1;
	//m=MoisDeb;
	m=(LaGrille->LeftCol-2)%12;
	an=(LaGrille->LeftCol-2)/12;
	an+=AgriEnCours->DefSim->An_0;
	titre=AnsiString("Trésorerie de ")+AnsiString(LesMois[m])+"  "+AnsiString(an);
	mFin=(m+11)%12;
	if(m==0) anFin=an;
	else anFin=an+1;
	titre+=AnsiString(" à ")+AnsiString(LesMois[mFin])+"  "+AnsiString(anFin);

	posG=LabM0->Left;
	ecart=(LabM11->Left-LabM0->Left)/11;

	for(n=0;n<12;n++)
	{
		labMois=(TQRLabel*)LstMois->Items[n];
		labMois->Caption=AnsiString(LesMois[m]);
		labMois->Left=posG+ecart*n;
		labVal=(TQRLabel*)LstVal->Items[n];
		labVal->Left=labMois->Left;
		m++;
		if(m>11) m=0;
	}
	UniteMonnaie->Caption=SysMonnaie->UTrans.c_str();
	TitreEtat->Caption=titre;

}

//---------------------------------------------------------------------------
void __fastcall TQRTresoValFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=1;
	PrintReport=true;
}
//---------------------------------------------------------------------------
void __fastcall TQRTresoValFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TQRTresoValFrm::CompleteDonnees(void)
{
	if(NLigne>=LaGrille->RowCount) return false;

	AffRow();

	NLigne++;
	return true;
}

//affiche à parir de colonne 1
//---------------------------------------------------------------------------
void __fastcall TQRTresoValFrm::AffRow(void)
{
	int r;
	TQRLabel *tqr;
	int i,c;
	r=NLigne;
	QRBand1->Frame->DrawTop=false;
	QRBTitreCol->Frame->DrawTop=false;
	IntituleP->Caption=LaGrille->Cells[0][r];
	for(c=LaGrille->LeftCol,i=0;i<12;i++,c++)
	{
		tqr=(TQRLabel*)LstVal->Items[i];
		tqr->Caption=LaGrille->Cells[c][r];
	}
}
//affiche à partir de colonne 0
//---------------------------------------------------------------------------
//--------------------------------------------
void TQRTresoValFrm::IniCaption(void) {
	IntituleP->Caption = T->LC_IntituleP;
	LabM0->Caption = LC_LabM0;
	LabM1->Caption = LC_LabM1;
	LabM10->Caption = LC_LabM10;
	LabM11->Caption = LC_LabM11;
	LabM2->Caption = LC_LabM2;
	LabM3->Caption = LC_LabM3;
	LabM4->Caption = LC_LabM4;
	LabM5->Caption = LC_LabM5;
	LabM6->Caption = LC_LabM6;
	LabM7->Caption = LC_LabM7;
	LabM8->Caption = LC_LabM8;
	LabM9->Caption = LC_LabM9;
	NomAgri->Caption = T->LC_NomAgri;
	QRTresoValFrm->Caption = LC_QRTresoValFrm;
	TitreEtat->Caption = T->LC_TitreEtat;
	UniteMonnaie->Caption = T->LC_UniteMonnaie;
	Val0->Caption = T->LC_Val0;
	Val1->Caption = T->LC_Val1;
	Val10->Caption = T->LC_Val10;
	Val11->Caption = T->LC_Val11;
	Val2->Caption = T->LC_Val2;
	Val3->Caption = T->LC_Val3;
	Val4->Caption = T->LC_Val4;
	Val5->Caption = T->LC_Val5;
	Val6->Caption = T->LC_Val6;
	Val7->Caption = T->LC_Val7;
	Val8->Caption = T->LC_Val8;
	Val9->Caption = T->LC_Val9;
	ValeurEn->Caption = T->LC_ValeurEn;
	QRValeurEn->Caption = T->LC_ValeurEn;
}
//--------------------------------------------
void TQRTresoValFrm::TexteCaption(void) {
	LC_IntituleP = T->TrouveCaption("CL_Trad", "LC_IntituleP");
	LC_LabM0 = T->TrouveCaption("QrTresoVal", "LC_LabM0");
	LC_LabM1 = T->TrouveCaption("QrTresoVal", "LC_LabM1");
	LC_LabM10 = T->TrouveCaption("QrTresoVal", "LC_LabM10");
	LC_LabM11 = T->TrouveCaption("QrTresoVal", "LC_LabM11");
	LC_LabM2 = T->TrouveCaption("QrTresoVal", "LC_LabM2");
	LC_LabM3 = T->TrouveCaption("QrTresoVal", "LC_LabM3");
	LC_LabM4 = T->TrouveCaption("QrTresoVal", "LC_LabM4");
	LC_LabM5 = T->TrouveCaption("QrTresoVal", "LC_LabM5");
	LC_LabM6 = T->TrouveCaption("QrTresoVal", "LC_LabM6");
	LC_LabM7 = T->TrouveCaption("QrTresoVal", "LC_LabM7");
	LC_LabM8 = T->TrouveCaption("QrTresoVal", "LC_LabM8");
	LC_LabM9 = T->TrouveCaption("QrTresoVal", "LC_LabM9");
	LC_NomAgri = T->TrouveCaption("CL_Trad", "LC_NomAgri");
	LC_QRTresoValFrm = T->TrouveCaption("QrTresoVal", "LC_QRTresoValFrm");
	LC_TitreEtat = T->TrouveCaption("CL_Trad", "LC_TitreEtat");
	LC_UniteMonnaie = T->TrouveCaption("CL_Trad", "LC_UniteMonnaie");
	LC_Val0 = T->TrouveCaption("CL_Trad", "LC_Val0");
	LC_Val1 = T->TrouveCaption("CL_Trad", "LC_Val1");
	LC_Val10 = T->TrouveCaption("CL_Trad", "LC_Val10");
	LC_Val11 = T->TrouveCaption("CL_Trad", "LC_Val11");
	LC_Val2 = T->TrouveCaption("CL_Trad", "LC_Val2");
	LC_Val3 = T->TrouveCaption("CL_Trad", "LC_Val3");
	LC_Val4 = T->TrouveCaption("CL_Trad", "LC_Val4");
	LC_Val5 = T->TrouveCaption("CL_Trad", "LC_Val5");
	LC_Val6 = T->TrouveCaption("CL_Trad", "LC_Val6");
	LC_Val7 = T->TrouveCaption("CL_Trad", "LC_Val7");
	LC_Val8 = T->TrouveCaption("CL_Trad", "LC_Val8");
	LC_Val9 = T->TrouveCaption("CL_Trad", "LC_Val9");
	LC_ValeurEn = T->TrouveCaption("CL_Trad", "LC_ValeurEn");

	IniCaption();

}
//--------------------------------------------

