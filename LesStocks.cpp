//---------------------------------------------------------------------------

#include <vcl.h>
#include "CL_Trad.h"
extern CL_Trad *T;
#pragma hdrstop
#include "Aide.h"
#include "LesStocks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Assol"
#pragma resource "*.dfm"
TLesStocksFrm *LesStocksFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLesStocksFrm::TLesStocksFrm(TComponent* Owner) :
		TAssolFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLesStocksFrm::VersGrille(TStringGrid *grille)
{
	int n,i;
	int row,col;
	CL_AgriRes *resultat;
	CL_QuanVal *quanVal;
	CL_Item *item;
	int digits=0;
	float total[N_X];
	Caption=LC_LesStocksFrm; //??
	memset(total,0,sizeof(total));
	for(i=0;i<10;i++)
	LaGrille->Cells[i+1][0]="  "+AnsiString(Agri->DefSim->An_0+i);
	resultat=Agri->Resultat;
	for(n=0,row=1;n<resultat->V_Produit->Nbelt;n++)
	{
		quanVal=resultat->V_Produit->Vecteur[n];
		item=quanVal->Item;
		if(ilYAStock(quanVal)==false) continue;

		LaGrille->Cells[0][row]=item->Nom;
		for(i=0,col=1;i<N_X;i++,col++)
		{
			LaGrille->Cells[col][row]=Aff(quanVal->Stock[i],digits);
			total[i]+=quanVal->Stock[i];
		}
		row++;
	}
	LaGrille->Cells[0][row]="Total";
	for(i=0,col=1;i<N_X;i++,col++)
	LaGrille->Cells[col][row]=Aff(total[i],digits);
	row++;
	LaGrille->RowCount=row;
}
//---------------------------------------------------------------------------
bool __fastcall TLesStocksFrm::ilYAStock(CL_QuanVal *quanVal)
{
	int n;
	for(n=0;n<N_X;n++)
	if(quanVal->Stock[n]>0) return true;
	return false;

}

//--------------------------------------------
void TLesStocksFrm::IniCaption(void) {
	LesStocksFrm->Caption = LC_LesStocksFrm;
}
//--------------------------------------------
void TLesStocksFrm::TexteCaption(void) {
	LC_LesStocksFrm = T->TrouveCaption("LesStocks", "LC_LesStocksFrm");

	IniCaption();

}

bool __fastcall TLesStocksFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

