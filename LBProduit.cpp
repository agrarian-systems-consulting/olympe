//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <utilcls.h>
#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Atelier.h"
#include "CL_Trad.h"
#include "Aide.h"
#include "LBProduit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBProduitFrm *LBProduitFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLBProduitFrm::TLBProduitFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBProduitFrm::FormActivate(TObject *Sender)
{
	Top=30+AtelierFrm->Top+AtelierFrm->BtBnProduit->Top+AtelierFrm->BtBnProduit->Height;
	Left=AtelierFrm->Left+AtelierFrm->BtBnProduit->Left;

}
//---------------------------------------------------------------------------
void __fastcall TLBProduitFrm::LBClick(TObject *Sender)
{
//	choix du produit de la perenne
//      n'est utilisé que pour les charges prop au volume
	int n;
	int rep;
	CL_ItemParAtelier *itemPA;
	CL_ItemParAtelier *itemPAProduit;
	CL_Item *produit;
	CL_SystemeUnite *sysUnite;
	int row;
	int col;
	TStringGrid *laGrille;

	laGrille=AtelierFrm->LaGrille;
	row=laGrille->Row;
	col=laGrille->Col;
	laGrille=AtelierFrm->LaGrille;
	if(laGrille->Cells[col][row].Length()>0)
	{
		rep=MessageBox(Handle,"A changer ?","Déja défini",
				MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO) return;
	}
	itemPA=(CL_ItemParAtelier*)laGrille->Objects[0][row];
	if(itemPA==NULL)
	{
		itemPA=new CL_ItemParAtelier();
		itemPA->Flag='N';
		laGrille->Objects[0][row]=(TObject*)itemPA;
		laGrille->Cells[0][row]=row;
	}
	else if(itemPA->Flag!='N')itemPA->Flag='M';

	// aller dans les produits de l'atelier
	n=LB->ItemIndex;
	itemPAProduit =(CL_ItemParAtelier*)LB->Items->Objects[n];

	itemPA->ItemPA=itemPAProduit;
	itemPA->NoItemPA=itemPAProduit->No;

	produit =itemPAProduit->Item;
	sysUnite =produit->SysUnite;

	itemPA->NoItem =itemPAProduit->No;
	itemPA->Qte =itemPAProduit->Qte;

	laGrille->Cells[2][row]=produit->Nom;
	laGrille->Cells[3][row]=sysUnite->UUt;
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBProduitFrm::IniCaption(void) {
	LBProduitFrm->Caption = T->LC_BtBnProduit;
}
//--------------------------------------------
void TLBProduitFrm::TexteCaption(void) {
	LC_BtBnProduit = T->TrouveCaption("CL_Trad", "LC_BtBnProduit");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBProduitFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

