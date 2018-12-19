//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Main.h"
#include "Commercialisation.h"

#include "TVChoixProduit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVChoixProduitFrm *TVChoixProduitFrm;
//---------------------------------------------------------------------------
__fastcall TTVChoixProduitFrm::TTVChoixProduitFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixProduitFrm::TVClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Item *item;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVChoixProduitFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		MainForm->NouvelleDefinition( PRODUIT );
		return;
	}

	if(elt->Level==0) return;

	item=(CL_Item*)elt->Data;
//    if(item==NULL)         return;
	CommercialisationFrm->Item=item;
	CommercialisationFrm->RetourDeTVChoixProduit();
}
//---------------------------------------------------------------------------

