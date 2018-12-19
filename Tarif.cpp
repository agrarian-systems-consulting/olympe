//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Tableur.h"

#include "TVDico.h"
#include "CL_Trad.h"

#include "Tarif.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TTarifFrm *TarifFrm;
extern CL_Excel *EX;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TTarifFrm::TTarifFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTarifFrm::FormActivate(TObject *Sender)
{

	Grille0->Cells[0][1]="Borne";
	Grille0->Cells[0][2]="Prix";
	Grille0->Cells[2][0]="   1";
	Grille0->Cells[3][0]="   2";
	Grille0->Cells[4][0]="   3";
	Grille0->Cells[5][0]="   4";
	RGLimiteClick(this);
	LaGrille=Grille0;
	strcpy(TypeCol,"00NNNN");

}
//---------------------------------------------------------------------------
void __fastcall TTarifFrm::RGLimiteClick(TObject *Sender)
{
	switch(RGLimite->ItemIndex)
	{
		case 0: Grille0->Cells[1][1]="  <";break;
		case 1: Grille0->Cells[1][1]="  <=";break;
		case 2: Grille0->Cells[1][1]="  >";break;
		case 3: Grille0->Cells[1][1]="  >=";break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTarifFrm::BtBnDicoClick(TObject *Sender)
{
	ES->IniV_Elt();
	TVDicoFrm->Origine=RESULTAT; //A MODIFIER

	ShowMessage("A revoir cf source");
	// Agri à voir
//    Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,Agri,false);
	TVDicoFrm->Visible=true;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTarifFrm::IniCaption(void) {
	LabCondition->Caption = T->LC_GBCondition;
	BtBnDico->Caption = T->LC_BtBnDico;
	LabNom->Caption = T->LC_LabNom;
	RGLimite->Caption = LC_RGLimite;
	RGMultiple->Caption = LC_RGMultiple;
	TarifFrm->Caption = LC_TarifFrm;
}
//--------------------------------------------
void TTarifFrm::TexteCaption(void) {
	LC_GBCondition = T->TrouveCaption("CL_Trad", "LC_GBCondition");
	LC_BtBnDico = T->TrouveCaption("CL_Trad", "LC_BtBnDico");
	LC_LabNom = T->TrouveCaption("CL_Trad", "LC_LabNom");
	LC_RGLimite = T->TrouveCaption("Tarif", "LC_RGLimite");
	LC_RGMultiple = T->TrouveCaption("Tarif", "LC_RGMultiple");
	LC_TarifFrm = T->TrouveCaption("Tarif", "LC_TarifFrm");

	IniCaption();

}
//--------------------------------------------

