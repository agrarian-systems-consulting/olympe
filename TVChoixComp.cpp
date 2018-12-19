//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "Main.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
#include "Tableur.h"
#include "Resultat.h"
#include "CL_Trad.h"

#include "TVChoixComp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVChoixCompFrm *TVChoixCompFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTVChoixCompFrm::TTVChoixCompFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixCompFrm::FormActivate(TObject *Sender)
{
	static debut=true; //100512

	if (debut==true)
	{
		debut=false;
		Left=ResultatFrm->Left+ResultatFrm->Width +2; //Width-Width; //100512
		Top =ResultatFrm->Top+20;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixCompFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *eltSerie;
	CL_EtatSortie *serieComp;
	serieComp=NULL;
	eltSerie=TV->Selected;
	if(eltSerie->Level==0)return;

	if(eltSerie==NULL) {ResultatFrm->RetourDeTVChoixComp(NULL);return;}
	if(eltSerie->Level==0) {ResultatFrm->RetourDeTVChoixComp(NULL);return;}
	if(eltSerie->Text=="[...]")
	{
		TVChoixCompFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		MainForm->NouvelleDefinition(COMPARAISON);
		ResultatFrm->RetourDeTVChoixComp(NULL);
		return;
	}

	serieComp=(CL_EtatSortie*)eltSerie->Data;
	ResultatFrm->RetourDeTVChoixComp(serieComp);
//ResultatFrm->Show();          //150412
	/*
	 eltSeries=ETAT;
	 FBrouillon->Etat(ResultatFrm->Agri,etat);
	 */
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTVChoixCompFrm::TVClick(TObject *Sender)
{
//    TVDblClick(this);
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTVChoixCompFrm::IniCaption(void) {
	TVChoixCompFrm->Caption = LC_TVChoixCompFrm;
}
//--------------------------------------------
void TTVChoixCompFrm::TexteCaption(void) {
	LC_TVChoixCompFrm = T->TrouveCaption("TVChoixComp", "LC_TVChoixCompFrm");

	IniCaption();

}
//--------------------------------------------

