//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "CL_TresoMens.h"
#include "TresoEnum.h"
#include "QrTresoQuant.h"
#include "CL_Trad.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QrTresoVal"
#pragma resource "*.dfm"
TQRTresoQuantFrm *QRTresoQuantFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRTresoQuantFrm::TQRTresoQuantFrm(TComponent* Owner) :
		TQRTresoValFrm(Owner) {
}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
//  met les mois
// cree LstCaption  pour afficher les données an/an
//---------------------------------------------------------------------------
void __fastcall TQRTresoQuantFrm::Initialise(void)
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
	UniteMonnaie->Caption="";
	TitreEtat->Caption=titre;

}
//---------------------------------------------------------------------------
void __fastcall TQRTresoQuantFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=1;
	PrintReport=true;
}
//---------------------------------------------------------------------------
void __fastcall TQRTresoQuantFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TQRTresoQuantFrm::CompleteDonnees(void)
{
	if(NLigne>=LaGrille->RowCount) return false;

	AffRow();

	NLigne++;
	return true;
}

//affiche à parir de colonne 1
//---------------------------------------------------------------------------
void __fastcall TQRTresoQuantFrm::AffRow(void)
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

	tresoMens=(CL_TresoMens *)LaGrille->Objects[0][r];
	QRLabUnite->Caption=AnsiString(" ");

	if(tresoMens==NULL) return;

	if(tresoMens->Contient==UnITEM)
	QRLabUnite->Caption=tresoMens->QuanVal->Item->SysUnite->UTrans;

	for(c=LaGrille->LeftCol,i=0;i<12;i++,c++)
	{
		tqr=(TQRLabel*)LstVal->Items[i];
		tqr->Caption=LaGrille->Cells[c][r];
	}
}
//affiche à partir de colonne 0
//---------------------------------------------------------------------------
//--------------------------------------------
void TQRTresoQuantFrm::IniCaption(void) {
	QRTresoQuantFrm->Caption = LC_QRTresoQuantFrm;
	LabUnite->Caption = LC_LabUnite;
	QRLabUnite->Caption = T->LC_Unite;
}
//--------------------------------------------
void TQRTresoQuantFrm::TexteCaption(void) {
	LC_QRTresoQuantFrm = T->TrouveCaption("QrTresoQuant", "LC_QRTresoQuantFrm");
	LC_LabUnite = T->TrouveCaption("QrTresoQuant", "LC_LabUnite");
	LC_Unite = T->TrouveCaption("CL_Trad", "LC_Unite");

	IniCaption();

}
//--------------------------------------------

