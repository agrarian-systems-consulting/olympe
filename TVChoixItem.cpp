//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Atelier.h"
#include "Forme00.h"
#include "Main.h"
#include "TVChoixItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVChoixItemFrm *TVChoixItemFrm;

// utilisé par Atelier

//---------------------------------------------------------------------------
__fastcall TTVChoixItemFrm::TTVChoixItemFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixItemFrm::FormActivate(TObject *Sender)
{
	LaGrille=AtelierFrm->LaGrille;
	Forme00Frm->AjoutRow=true; //???
	Forme00Frm->LaGrille=LaGrille;//???
	Top=30+AtelierFrm->Top+AtelierFrm->BtBnProduit->Top+AtelierFrm->BtBnProduit->Height;
	Left=AtelierFrm->Left+AtelierFrm->BtBnProduit->Left;
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixItemFrm::TVDblClick(TObject *Sender)
{
	int rep;
	TTreeNode *elt,*parent;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_SystemeUnite *sysUnit;
	int col=LaGrille->Col;
	int row=LaGrille->Row;
	//saisie en col 2 pour toutes les grilles sauf
	//              4 pour charge prop au volume
	// la saisie du produit de la culture est réglée ailleurs

	if (LaGrille->Tag==GChProp) {if(col!=4) return;}
	else {if(col!=2) return;}

	if(LaGrille->Cells[col][row].Length()>0)
	{
		rep=MessageBox(Handle,"A changer ?","Déja défini",
				MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO) return;
	}
	elt=TV->Selected;
	if(elt==NULL)return;
//    if(elt->Level==0) return;
	if(elt->Text=="[...]")
	{
		TVChoixItemFrm->Visible=false;
		switch(LaGrille->Tag)
		{
			case GProduit:MainForm->NouvelleDefinition(PRODUIT);return;
			case GCharge :
			case GChProp :MainForm->NouvelleDefinition(CHARGE);return;
			case GExter :MainForm->NouvelleDefinition(EXTPOS);return;
		}
	}

	parent=elt->Parent;
	if(parent==NULL) return; //
	categorie=(CL_Categorie*)parent->Data;
	item=(CL_Item*)elt->Data;
	sysUnit=item->SysUnite;
	CompleteGrille(item,categorie,sysUnit);

//    TV->Visible=false;

	AtelierFrm->LabelModifie->Visible=true;
	//AtelierFrm->GrilleModif[LaGrille->Tag]=true;
	AtelierFrm->ColM[LaGrille->Tag]=LaGrille->Col;
	AtelierFrm->RowM[LaGrille->Tag]=LaGrille->Row;
	Forme00Frm->AjouterRow();
}

//----------------------------------------------------------------------------
void __fastcall TTVChoixItemFrm::CompleteGrille(CL_Item *item,
		CL_Categorie *categorie, CL_SystemeUnite *sysUnit )
{
	int r;
	int row=LaGrille->Row;
	CL_ItemParAtelier *itemPA;

	for(r=1;r<LaGrille->RowCount;r++) //310810
	{
		itemPA=(CL_ItemParAtelier*)LaGrille->Objects[0][r];
		if(itemPA==NULL) continue;
		if(itemPA->Item==item)
		{
			ShowMessage("Existe déjà");
			return;
		}
	}

	itemPA=(CL_ItemParAtelier*)LaGrille->Objects[0][row];
	if(itemPA==NULL)
	{
		itemPA=new CL_ItemParAtelier();
		itemPA->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)itemPA;
		LaGrille->Cells[0][row]=row;
	}
	else
	if(itemPA->Flag!='N')itemPA->Flag='M';

	if(LaGrille->Tag==GChProp)
	{
		itemPA->NoCharge=item->No;
		itemPA->Charge =item;
		LaGrille->Cells[4][row]=item->Nom;
		LaGrille->Cells[5][row]=sysUnit->UUt;
	}
	else
	{
		itemPA->NoItem=item->No;
		itemPA->Item =item;
		LaGrille->Cells[2][row]=item->Nom;
		LaGrille->Cells[3][row]=categorie->Nom;
		LaGrille->Cells[4][row]=sysUnit->UUt;
	}
}

