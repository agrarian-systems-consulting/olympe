//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "TVPrixChoix.h"

#include "CL_Trad.h"
#include "GereRendement.h"
//#include "TendanceEnum.h"
#include "AleaPrix.h"

#include "AleaRdt.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
extern CL_Trad *T;
//-----------------------------------------------------------------------------
void __fastcall TAleaRdtFrm::IniGrille0(void)
{
	int l=0;
//              0  1  2   3  4  5  6  7  8  9  0  1  2  3  4  5
	int largeur[] = {20,10,96,96,48}; //240907
	CL_Delta *deltaBidon;//pour savoir la version de CL_Delta
	deltaBidon=new CL_Delta();
	LaGrille->ColCount=deltaBidon->NMax+5;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<5;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	for(int c=5;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[4];
		l+=largeur[4];
	}
	LaGrille->Width=l+6+25;
	LaGrille->Cells[3][0]=T->L_Atelier; //"Atelier";
	LaGrille->Cells[4][0]=AleaPrixFrm->L_Base;

}
//-----------------------------------------------------------------------------
void __fastcall TAleaRdtFrm::AppelerVersGrille(void)
{
	VersGrille(LaGrille);
}
//-----------------------------------------------------------------------------
void __fastcall TAleaRdtFrm::VersGrille(TStringGrid *grille)
{
	CL_Vecteur<CL_Delta> *vecteur;
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Delta *delta;
//CL_Item  *item;
	float rdt;//,rdtBase;

	vecteur=Tendance->V_Delta;

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		delta=vecteur->Vecteur[r];
		delta->Flag='O';
//		item=delta->Item;
		LaGrille->Objects[0][row]=(TObject*)delta;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=delta->Item->Nom;
		LaGrille->Cells[3][row]=delta->Atelier->Nom;
		trouveRdt(delta);
		LaGrille->Cells[4][row]=Aff(delta->Rdt,Digits);//190907
		for(c=0,col=5;c<delta->NMax;c++,col++)
		{
			switch(RGPcentVal->ItemIndex)
			{
				case 0: // en pcent
				LaGrille->Cells[col][row]=Aff(delta->Pcent[c],Digits);
				break;
				case 1:
				rdt=(delta->Rdt*delta->Pcent[c])/100.;
				LaGrille->Cells[col][row]=Aff(rdt,Digits);
				break;
			}
		}
	}

}
//-----------------------------------------------------------------------------
void __fastcall TAleaRdtFrm::trouveRdt(CL_Delta *delta)
{
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *v_ItemParAtelier;
	CL_ItemParAtelier *itemParAtelier;

	int i;
	delta->Rdt=0;
	atelier=delta->Atelier;
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd:v_ItemParAtelier=atelier->V_Produit;break;
		case GTCharge:
		case GSCharge: v_ItemParAtelier=atelier->V_Charge;break;
		case GTExter:
		case GSExter: v_ItemParAtelier=atelier->V_Externalite;break;
		default:ShowMessage("AleaRdt1 a compléter");return;
	}
	for(i=0;i<v_ItemParAtelier->Nbelt;i++)
	{
		itemParAtelier=v_ItemParAtelier->Vecteur[i];
		if(itemParAtelier->Item==delta->Item)
		{
			switch(atelier->Nature)
			{
				case PERENNE:
				for(int i=0;i<atelier->NbPhase;i++)
				{
					if(itemParAtelier->QtePhase[i]>delta->Rdt)
					delta->Rdt=itemParAtelier->QtePhase[i];
				}
				return;
				default:
				for(int i=0;i<atelier->NbPhase;i++)
				{
					delta->Rdt+=itemParAtelier->QtePhase[i];
				}
				return;
			}
		}
	}
	return;

}
/*
 L_Atelier=          "Atelier";
 L_Base=             "Base";

 */
