//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Main.h"
//#include "InvAniProCha.h"
#include "Troupeau.h"
#include "CL_Trad.h"

#include "TVChoixAniProCha.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVChoixAniProChaFrm *TVChoixAniProChaFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTVChoixAniProChaFrm::TTVChoixAniProChaFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixAniProChaFrm::FormActivate(TObject *Sender)
{
//    Left= InvAniProChaFrm->Left+InvAniProChaFrm->Width-Width;
//    Top=  InvAniProChaFrm->Top+20;

	Left= TroupeauFrm->Left+TroupeauFrm->Width-Width;
	Top= TroupeauFrm->Top+20;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixAniProChaFrm::TVDblClick(TObject *Sender)
{
//	if(AgriSaisieFrm->RGModifiable->ItemIndex==0)return;
//	if(RGModifiable->ItemIndex==0)return;

	CL_Atelier *atelier;
	TTreeNode *elt;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;
	if(c<2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		MainForm->NouvelleDefinition(ANIMAUX);
		return;
	}

//	if(elt->Level==0)	return;
	if(elt->Count!=0) return;//160103

	atelier=(CL_Atelier*)elt->Data;
	if(atelier==NULL) return;

	if(LaGrille->Objects[c][r]==NULL)
	{
		LaGrille->Objects[c][r]=(TObject*)atelier;
		LaGrille->Cells[c][r]=atelier->Nom;
		//InvAniProChaFrm->LabelModifie->Visible=true;
		TroupeauFrm->LabelModifie->Visible=true;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
		else
		{
			LaGrille->Objects[c][r]=(TObject*)atelier;
			LaGrille->Cells[c][r]=atelier->Nom;
			//InvAniProChaFrm->LabelModifie->Visible=true;
			TroupeauFrm->LabelModifie->Visible=true;
		}
	}
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTVChoixAniProChaFrm::TexteCaption(void) {
//    TVChoixAniProChaFrm->Caption=T->LC_[0]TLabel;
}
//--------------------------------------------
void TTVChoixAniProChaFrm::IniCaption(void) {
//       LC_[0]TLabel =T->TrouveCaption("CL_Trad" ,"LC_[0]TLabel");
}
//--------------------------------------------

