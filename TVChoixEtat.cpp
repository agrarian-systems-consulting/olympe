//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
#include "Tableur.h"
#include "Resultat.h"
#include "QRSortieQuant.h"

#include "TVChoixEtat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVChoixEtatFrm *TVChoixEtatFrm;

extern CL_Excel *EX;

//---------------------------------------------------------------------------
__fastcall TTVChoixEtatFrm::TTVChoixEtatFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEtatFrm::FormActivate(TObject *Sender)
{
	Left=ResultatFrm->Left+ResultatFrm->Width-Width;
	Top =ResultatFrm->Top+20;
	Caption=ResultatFrm->LC_Etat;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixEtatFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *eltEtat;
	CL_EtatSortie *etat;

	eltEtat=TV->Selected;
	if(eltEtat==NULL) return;
	if(eltEtat->Level==0)return;
	if(eltEtat->Text=="[...]")return;

	if(QRSortieQuantFrm->LstDonnees)
	{
		QRSortieQuantFrm->DelDonnees(); //211204
		QRSortieValFrm->CloseQuery();
	}
	etat=(CL_EtatSortie*)eltEtat->Data;
	if(ResultatFrm->RBExcel->Checked==true)
	EX->Etat(ResultatFrm->Agri,etat);
	else
	QRSortieQuantFrm->Etat(etat,ResultatFrm->Agri);
//    FBrouillon->EnCours=ETAT;
//    FBrouillon->Etat(ResultatFrm->Agri,etat);
}

