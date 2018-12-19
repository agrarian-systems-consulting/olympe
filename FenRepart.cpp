//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "OlympeDec.h"
#include "LesClassesApp.h"
#include "TresoProduits.h"
#include "TresoRepart.h"
#include "TVChoixRepart.h"

#include "CL_Trad.h"
#include "Aide.h"

#include "FenRepart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TFenRepartFrm *FenRepartFrm;

extern CL_Trad *T;
/*
 on vient de TVChoixRepart
 affiche SEULEMENT
 */
//---------------------------------------------------------------------------
__fastcall TFenRepartFrm::TFenRepartFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::FormActivate(TObject *Sender)
{
	static bool debut=true;

	if(debut==true) //return;
	{
		debut=false;
		Demarre();
	}

	if(Repart==NULL) return;
	Affiche();

}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::Demarre(void)
{
	int c;
	LaGrille->ColWidths[0]=60;
	for(int i=1;i<4;i++)LaGrille->ColWidths[i]=30;
	for(int i=4;i<7;i++)LaGrille->ColWidths[i]=60;
	for(c=1;c<13;c++)
	LaGrille->Cells[0][c]=NomMois(c);
	LaGrille->Cells[1][0]=T->L_Avt1; //Avt 1";
	LaGrille->Cells[2][0]="   1";
	LaGrille->Cells[3][0]="   2";

	LaGrille->Cells[4][0]=T->L_Avt1;//"Avt 1";
	LaGrille->Cells[5][0]="   1";
	LaGrille->Cells[6][0]="   2";
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::EffaceGrille(void)
{
	int r,c;
	for(r=1;r<LaGrille->RowCount;r++)
	for(c=1;c<LaGrille->ColCount;c++)
	LaGrille->Cells[c][r]="";
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::Affiche(void)
{
	float totalPcent;
	int c,r,n;

	EdCode->Text=Repart->Nom;
	c=TresoRepartFrm->SG->Col;
	r=TresoRepartFrm->SG->Row;
	n=c-1;
	LaQuanVal=(CL_QuanVal*)TresoRepartFrm->SG->Objects[0][r];
	EdProduit->Text=LaQuanVal->Item->Nom;
	if(TresoRepartFrm->CalculEn==VALEUR)
	ValTot=LaQuanVal->Val[n];
	else
	ValTot=LaQuanVal->Qte[n];

	EdValeur->Text=FloatToStrF((double)ValTot,ffNumber,7,0);
	EffaceGrille();
	Repart->GrilleEcrire(LaGrille,ValTot);
	EdAn->Text=AgriEnCours->DefSim->An_0+n; //010506
	totalPcent=Repart->Total();
	EdTotPcent->Text=FloatToStrF((double)totalPcent,ffNumber,7,0);
	EdTotValeur->Text=FloatToStrF((double)ValTot*totalPcent/100.,ffNumber,7,0);
	LaGrille->Col=1;LaGrille->Row=1;

}
/*
 on a choisi une répartition cf TVChoixRepart
 */
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::InformeSGTreso(void)
{
	int c,c0,cMax,r,n;
	c0=TresoRepartFrm->SG->Col;
	r=TresoRepartFrm->SG->Row;
	if(TresoRepartFrm->ChBRepTout->Checked==false)cMax=c0+1;
	else cMax=N_X+1;
	for(c=c0;c<cMax;c++)
	{
		n=c-1;
		if(TresoRepartFrm->CalculEn==VALEUR)
		{
			LaQuanVal->ItemRepart->LesRepartV[n]=Repart;
			LaQuanVal->ItemRepart->LesNoRepartV[n]=Repart->No;
		}
		else
		{
			LaQuanVal->ItemRepart->LesRepartQ[n]=Repart;
			LaQuanVal->ItemRepart->LesNoRepartQ[n]=Repart->No;
		}

		TresoRepartFrm->SG->Cells[c][r]=Repart->Nom; //EdCode->Text;
		TresoRepartFrm->SG->Objects[c][r]=(TObject*)Repart;//191205
	}
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::AffTotal(void)
{
	float tot;
	tot=Repart->Total();

	EdTotPcent->Text=FloatToStrF((double)tot,ffNumber,7,0);
	tot*=ValTot;
	tot/=100.;
	EdTotValeur->Text=FloatToStrF((double)tot,ffNumber,7,0);

}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm::BtBnOkClick(TObject *Sender)
{
	InformeSGTreso();
	Close();
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TFenRepartFrm::IniCaption(void) {
	GBAn->Caption = T->LC_GBAn;
	GBCode->Caption = T->LC_GBCode;
	LabPcent->Caption = LC_LabPcent;
	GBProduit->Caption = T->LC_LabPProduit;
	FenRepartFrm->Caption = LC_FenRepartFrm;
	LabTotalVal->Caption = T->LC_LabTotal;
	LabTotPcent->Caption = T->LC_LabTotPcent;
	LabVal->Caption = T->LC_LabVal;
	GBValeur->Caption = T->LC_LabVal;
}
//--------------------------------------------
void TFenRepartFrm::TexteCaption(void) {
	LC_GBAn = T->TrouveCaption("CL_Trad", "LC_GBAn");
	LC_GBCode = T->TrouveCaption("CL_Trad", "LC_GBCode");
	LC_LabPcent = T->TrouveCaption("FenRepart", "LC_LabPcent");
	LC_LabPProduit = T->TrouveCaption("CL_Trad", "LC_LabPProduit");
	LC_FenRepartFrm = T->TrouveCaption("FenRepart", "LC_FenRepartFrm");
	LC_LabTotal = T->TrouveCaption("CL_Trad", "LC_LabTotal");
	LC_LabTotPcent = T->TrouveCaption("CL_Trad", "LC_LabTotPcent");
	LC_LabVal = T->TrouveCaption("CL_Trad", "LC_LabVal");

	IniCaption();

}
//--------------------------------------------

void __fastcall TFenRepartFrm::RGPrecisionClick(TObject *Sender)
{
	Affiche();
}
//---------------------------------------------------------------------------

bool __fastcall TFenRepartFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

