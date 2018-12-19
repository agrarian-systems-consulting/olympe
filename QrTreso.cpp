//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "CL_TresoMens.h"

#include "QrTreso.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQRTresoFrm *QRTresoFrm;
//---------------------------------------------------------------------------
__fastcall TQRTresoFrm::TQRTresoFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TQRTresoFrm::FormCreate(TObject *Sender)
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
void __fastcall TQRTresoFrm::Initialise(void)
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
void __fastcall TQRTresoFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=1;
	PrintReport=true;
}
//---------------------------------------------------------------------------
void __fastcall TQRTresoFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TQRTresoFrm::CompleteDonnees(void)
{
	int r;
	if(NLigne>=LaGrille->RowCount) return false;

	AffRow();

	NLigne++;
	return true;
}

//affiche à parir de colonne 1
//---------------------------------------------------------------------------
void __fastcall TQRTresoFrm::AffRow(void)
{
	int r;
	TQRLabel *tqr;
	CL_TresoMens *tresoMens;

//int nColonne;
	int i,c;
//    nColonne=QR->Tag;
	r=NLigne;
	QRBand1->Frame->DrawTop=false;
	QRBTitreCol->Frame->DrawTop=false;
	IntituleP->Caption=LaGrille->Cells[0][r];

//    IntituleP->Left=donnees->PosNom;
//    IntituleP->Font->Color=donnees->Couleur;

	for(c=LaGrille->LeftCol,i=0;i<12;i++,c++)
	{
		tqr=(TQRLabel*)LstVal->Items[i];
		tqr->Caption=LaGrille->Cells[c][r];
	}
}
//affiche à partir de colonne 0
//---------------------------------------------------------------------------

