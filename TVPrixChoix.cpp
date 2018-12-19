//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Forme0.h"

#include "TendanceEnum.h"
#include "AleaPrix.h"

#include "FichierLire.h"

//..
#include "TVPrixChoix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
extern CL_ES *ES;
TTVPrixChoixFrm *TVPrixChoixFrm;

//---------------------------------------------------------------------------
__fastcall TTVPrixChoixFrm::TTVPrixChoixFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVPrixChoixFrm::FormActivate(TObject *Sender)
{
//    LaGrille=TendanceFrm->LaGrille;
//    Digits=AleaPrixFrm->Digits; ??
//    Left= AleaPrixFrm->Left-AleaPrixFrm->Width;
	Top= AleaPrixFrm->Top+20;
	DigitsPrix=2;
	if(AleaPrixFrm->RGPrecision->ItemIndex==0) Digits=0;
	else Digits=2;

	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd: Caption="Les Produits";break;
		case GTCharge:
		case GSCharge: Caption="Les Charges";break;
		case GTExter:
		case GSExter: Caption="Les Externalités";break;

		default:ShowMessage("TVTChoix ActivateOubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVPrixChoixFrm::TVDblClick(TObject *Sender)
{
	TVDblClickProduit();
}
//---------------------------------------------------------------------------
void __fastcall TTVPrixChoixFrm::TVDblClickProduit(void)
{
	CL_Delta *delta;
	TTreeNode *elt;
	CL_Item *item;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	int col;
	int rep;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Text=="[...]")
	{
		TVPrixChoixFrm->Close(); //Visible=false;
		switch(LaGrille->Tag)
		{
			case GTProd:
			case GSProd: MainForm->NouvelleDefinition(PRODUIT);return;
			case GTCharge :
			case GSCharge :MainForm->NouvelleDefinition(CHARGE);return;
			case GTExter:
			case GSExter :MainForm->NouvelleDefinition(EXTPOS);return;
		}
	}

	if(elt->Level==0) return;

	item=(CL_Item*)elt->Data;
	if(item==NULL) return;
	if(Doublon(item)==true) return;

	delta=(CL_Delta*)LaGrille->Objects[0][r];

	if(delta==NULL)
	{
		delta=new CL_Delta();
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
	LaGrille->Cells[4][r]=Forme00Frm->Aff(item->Prix,DigitsPrix);
	if(AleaPrixFrm->RGPcentVal->ItemIndex==0)
	for(c=0,col=5;c<N_X;c++,col++)
	LaGrille->Cells[col][r]=Forme00Frm->Aff(delta->Pcent[c],Digits);
	else
	for(c=0,col=5;c<N_X;c++,col++)
	LaGrille->Cells[col][r]=Forme00Frm->Aff(item->Prix,Digits);

	Forme00Frm->AjouterRow();

}
//---------------------------------------------------------------------------
bool __fastcall TTVPrixChoixFrm::Doublon(CL_Item *item)
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