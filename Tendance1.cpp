//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "Tendance.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::TailleGrille(void)
{
	Grille0->Top=40;
	Grille0->Height=Height-160; //200;//140;
}

//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::IniGrilleTendance(void)
{
	char car;
	AnsiString s="      ";
	IniGrille0();
	TailleGrille();
	strcpy(TypeCol, "00TTNNNNNNNNNNNNNNN");

	VideGrille(LaGrille);

	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd:
		LaGrille->Cells[2][0]="PRODUIT";break;
		case GTCharge:
		case GSCharge:
		LaGrille->Cells[2][0]="CHARGE"; break;
		case GTExter:
		case GSExter:
		LaGrille->Cells[2][0]="EXTERNALITE"; break;
		default:ShowMessage("IniGrilleTendance Oubli");
	}

	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GTExter:
		for(int i=0;i<10;i++)
		LaGrille->Cells[i+5][0]="  "+AnsiString(An_0+i);
		break;
		case GSProd:
		case GSCharge:
		case GSExter:
		for(int i=0;i<10;i++)
		{
			car='A'+i;
			s[5]=car;
			LaGrille->Cells[i+5][0]=s;
		}
		break;
		default:ShowMessage("IniGrilleTendance Oubli");
	}
}
//-----------------------------------------------------------------------------
void __fastcall TTendanceFrm::IniGrille0(void)
{
	int l=0;
//              0  1  2   3  4  5  6  7  8  9  0  1  2  3  4  5
	int largeur[] = {20,10,128,64,48,48,48,48,48,48,48,48,48,48,48,48};
	LaGrille->ColCount=15;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;
	LaGrille->Cells[3][0]="Catégorie";
	LaGrille->Cells[4][0]="Base";

}
//-----------------------------------------------------------------------------
void __fastcall TTendanceFrm::VersGrille(TStringGrid *grille)
{
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		VersGrilleTendance(Tendance->V_Delta);break;

		default:ShowMessage("Méthode VersGrille NON définie");
	}
}
//-----------------------------------------------------------------------------
void __fastcall TTendanceFrm::VersGrilleTendance(CL_Vecteur<CL_Delta> *vecteur)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Delta *delta;
	CL_Item *item;
	float prix;

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		delta=vecteur->Vecteur[r];
		delta->Flag='O';
		item=delta->Item;
		LaGrille->Objects[0][row]=(TObject*)delta;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=item->Nom;
		LaGrille->Cells[3][row]=item->Categorie->Nom;
		LaGrille->Cells[4][row]=Aff(item->Prix,Digits);
		for(c=0,col=5;c<10;c++,col++)
		{
			switch(RGPcentVal->ItemIndex)
			{
				case 0: // en pcent
				LaGrille->Cells[col][row]=Aff(delta->Pcent[c],Digits);
				break;
				case 1:
				prix=(item->Prix*delta->Pcent[c])/100.;
				LaGrille->Cells[col][row]=Aff(prix,Digits);
				break;
			}
		}
	}

}
//-----------------------------------------------------------------------------
void __fastcall TTendanceFrm::ReAffGrilleTendance(void)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Delta *delta;
	CL_Item *item;
	float base,prix,pcent;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		delta=(CL_Delta*)LaGrille->Objects[0][row];
		base=delta->Item->Prix;

		for(c=0,col=5;c<10;c++,col++)
		{
			switch(RGPcentVal->ItemIndex)
			{
				case 0: //a afficher en pcent
				prix=GrilleFloat(col,row);
				pcent=(prix/base)*100;
				LaGrille->Cells[col][row]=Aff(pcent,Digits);
				break;
				case 1://a afficher en valeur
				pcent=GrilleFloat(col,row);
				prix =(pcent*base)/100.;
				LaGrille->Cells[col][row]=Aff(prix,Digits);
				break;
			}
		}
	}
}
