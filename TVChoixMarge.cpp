//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "Resultat.h"
#include "AgriSaisie.h"
#include "AgriAtelierMarge.h"

#include "TVChoixMarge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoixEtat"
#pragma resource "*.dfm"
TTVChoixMargeFrm *TVChoixMargeFrm;
//---------------------------------------------------------------------------
__fastcall TTVChoixMargeFrm::TTVChoixMargeFrm(TComponent* Owner) :
		TTVChoixEtatFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixMargeFrm::FormActivate(TObject *Sender)
{
	Left=ResultatFrm->Left+ResultatFrm->Width-Width;
	Top =ResultatFrm->Top+20;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTVChoixMargeFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Atelier *atelier;

	elt=TV->Selected;
	if(elt==NULL) return;
	if(elt->Level==0)return;

	atelier=(CL_Atelier*)elt->Data;
	AgriAtelierMargeFrm->Atelier=atelier;
//    AgriSaisieFrm->MargeAtelier(atelier);
	AgriAtelierMargeFrm->Arret=false;
}

//---------------------------------------------------------------------------
void __fastcall TTVChoixMargeFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	AgriAtelierMargeFrm->Arret=true;
}
//---------------------------------------------------------------------------

