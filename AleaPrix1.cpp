//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"

#include "TendanceEnum.h"
#include "AleaPrix.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
extern CL_Trad *T;

//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::TailleGrille(void)
{
	Grille0->Top=40;
	Grille0->Height=Height-160; //200;//140;
}

//---------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::IniGrilleTendance(void)
{
	char car;
	AnsiString s="      ";
	int an_0;
	int i,iMax;
	if(AgriEnCours)
	{
		an_0=AgriEnCours->DefSim->An_0; //3001008
		if(AgriEnCours->EstPlus10Ans==true)
		an_0-=AgriEnCours->NoSerie*10;
	}
	else an_0=An_0;
	IniGrille0();
	TailleGrille();
	iMax=LaGrille->ColCount-4;

	strcpy(TypeCol, "00000NNNNNNNNNNNNNNN");

	VideGrille(LaGrille);

	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	LaGrille->Cells[2][0]=TitreColonne2; //défini dans
	/*
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
	 */
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GTExter:
		for(i=0;i<iMax;i++) //200907
		LaGrille->Cells[i+5][0]="  "+AnsiString(an_0+i);
		break;
		case GSProd:
		case GSCharge:
		case GSExter:
		for(i=0;i<iMax;i++)
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
void __fastcall TAleaPrixFrm::IniGrille0(void)
{
	int l=0;
//              0  1  2   3  4  5  6  7  8  9  0  1  2  3  4  5
	int largeur[] = {20,10,128,64,48}; //200907
	CL_Delta *deltaBidon;
	deltaBidon=new CL_Delta();
	deltaBidon->NMax;
	LaGrille->ColCount=deltaBidon->NMax+5;//15; //200907
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
	LaGrille->Cells[3][0]=T->L_Cat; //"Catégorie";
	LaGrille->Cells[4][0]=L_Base;//"Base";

}
//-----------------------------------------------------------------------------
void __fastcall TAleaPrixFrm::VersGrille(TStringGrid *grille)
{
	CL_Vecteur<CL_Delta> *vecteur;
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Delta *delta;
	CL_Item *item;
	float prix;

	vecteur=Tendance->V_Delta;

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
		LaGrille->Cells[4][row]=Aff(item->Prix,DigitsPrix);
		for(c=0,col=5;c<delta->NMax;c++,col++)
		{
			switch(RGPcentVal->ItemIndex)
			{
				case 0: // en pcent
//                    LaGrille->Cells[col][row]=Aff(delta->Pcent[c],Digits);
				LaGrille->Cells[col][row]=Aff0(delta->Pcent[c],Digits);
				break;
				case 1:
				prix=(item->Prix*delta->Pcent[c])/100.;
				LaGrille->Cells[col][row]=Aff0(prix,Digits);
//                    LaGrille->Cells[col][row]=Aff(prix,Digits);
				break;
			}
		}
	}
	CellInitiale(5,1); //301203

}
/*
 L_Cat=          "Catégorie";
 L_Base=         "Base";

 */
