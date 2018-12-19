//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Forme0.h"

#include "TendanceEnum.h"
#include "AleaPrix.h"

#include "TVTChoix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVTChoixFrm *TVTChoixFrm;
//---------------------------------------------------------------------------
__fastcall TTVTChoixFrm::TTVTChoixFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVTChoixFrm::FormActivate(TObject *Sender)
{
//    LaGrille=TendanceFrm->LaGrille;
	Digits=AleaPrixFrm->Digits;
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd: Caption="Les Produits";break;
		case GTCharge:
		case GSCharge: Caption="Les Charges";break;
		default:ShowMessage("TVTChoix ActivateOubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVTChoixFrm::TVDblClick(TObject *Sender)
{

	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		TVDblClickProduit(); break; //
		default:ShowMessage("TVDblClick Oubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVTChoixFrm::TVDblClickProduit(void)
{
	CL_Delta *delta;
	TTreeNode *elt;
	CL_Item *item;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int rep;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVChoixFrm->Visible=false;
		//oblige a clicker et donc à mettre à jour la TV
		ShowMessage("Nouveau A Faire");
		return;
	}

	if(elt->Level==0) return;

	item=(CL_Item*)elt->Data;
	if(item==NULL) return;
	if(Doublon(item)==true) return;

	delta=(CL_Delta*)LaGrille->Objects[0][r];

	if(delta==NULL)
	{
		delta=new CL_Delta;
		delta->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)delta;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(delta->Flag!='N')delta->Flag='M';

	delta->NoItem=item->No;
	delta->Item =item;
	LaGrille->Cells[2][r]=item->Nom;
	LaGrille->Cells[3][r]=item->Categorie->Nom;
	LaGrille->Cells[4][r]=Forme00Frm->Aff(item->Prix,Digits);

	Forme00Frm->AjouterRow();

}
//---------------------------------------------------------------------------
bool __fastcall TTVTChoixFrm::Doublon(CL_Item *item)
{
	CL_Delta *delta;
	for(int r=1;r<LaGrille->RowCount-2;r++)
	{
		delta=(CL_Delta*)LaGrille->Objects[0][r];
		if(delta->Item==item)
		{
			MessageBox(Handle,"Existe déjà !"," DOUBLON",MB_OK|MB_ICONSTOP);
			return true;
		}
	}
	return false;
}