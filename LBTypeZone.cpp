//---------------------------------------------------------------------------

#include <vcl.h>
#include "Main.h"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#pragma hdrstop
#include "AgriSaisie.h"
#include "AgriDefSim.h"
#include "NouvAgri.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBTypeZone.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBTypeZoneFrm *LBTypeZoneFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBTypeZoneFrm::TLBTypeZoneFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBTypeZoneFrm::CreeLB(int posG,int posH,int r,CL_Categorie *categorie)
{
	int i;
	CL_Item *critere;
	TRect rect;
	LBTypeZone->Clear();
	Left=posG;
	Top =posH;
	LBTypeZoneFrm->FormStyle=fsStayOnTop;
	/*
	 if(Origine=="AgriDefSim")            //bizarre !
	 LBTypeZoneFrm->FormStyle=fsStayOnTop;
	 else
	 LBTypeZoneFrm->FormStyle=fsNormal;
	 */
	LBTypeZoneFrm->Visible=true;
	LBTypeZoneFrm->Caption=categorie->Nom;
	for(i=0;i<V_TypeZone->Nbelt;i++)
	{
		critere=V_TypeZone->Vecteur[i];
		if(critere->Categorie!=categorie)continue;
		LBTypeZone->Items->AddObject(critere->Nom,(TObject*)critere);
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBTypeZoneFrm::LBTypeZoneClick(TObject *Sender)
{
	if(Origine=="AgriDefSim")
	AgriDefSimClick();
	else if(Origine=="NouvAgri")
	NouvAgriClick();

	else
	ShowMessage("Oubli dans LBTypeZone");

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TLBTypeZoneFrm::AgriDefSimClick(void)
{
	int n;
	int c,r;
	CL_Item *critere;
	c=AgriDefSimFrm->GrilleCritere->Col;
	r=AgriDefSimFrm->GrilleCritere->Row;
	// critere stocké comme une ST_NoItem
	n=LBTypeZone->ItemIndex;
	critere=(CL_Item*)LBTypeZone->Items->Objects[n];

	AgriDefSimFrm->GrilleCritere->Cells[c][r]=critere->Nom;
	AgriDefSimFrm->GrilleCritere->Objects[c][r]=(TObject*)critere;
	AgriDefSimFrm->LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TLBTypeZoneFrm::NouvAgriClick(void)
{
	int n;
	int c,r;
	CL_Item *critere;
//ST_NoItem   *critere;
//CL_Agriculteur *agri;
//CL_Categorie   *categorie;
//	agri=(CL_Agriculteur*)GrilleAgri->Objects[0][r];
	c=NouvAgriFrm->GrilleAgri->Col;
	r=NouvAgriFrm->GrilleAgri->Row;
	n=LBTypeZone->ItemIndex;
	critere=(CL_Item*)LBTypeZone->Items->Objects[n];
	NouvAgriFrm->GrilleAgri->Cells[c][r]=critere->Nom;
	NouvAgriFrm->GrilleAgri->Objects[c][r]=(TObject*)critere;

	NouvAgriFrm->AStocker=true;

//retirer les critères remplacés les nouveaux seront introduits par BtOk
// attention pb possible
}
//--------------------------------------------
void TLBTypeZoneFrm::IniCaption(void) {
	LBTypeZoneFrm->Caption = LC_LBTypeZoneFrm;
}
//--------------------------------------------
void TLBTypeZoneFrm::TexteCaption(void) {
	LC_LBTypeZoneFrm = T->TrouveCaption("LBTypeZone", "LC_LBTypeZoneFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBTypeZoneFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

