//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CL_Repart.h"
#include "FenRepart1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFenRepartFrm1 *FenRepartFrm1;
//---------------------------------------------------------------------------
__fastcall TFenRepartFrm1::TFenRepartFrm1(TComponent* Owner) :
		TForm(Owner) {
	Repart = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::FormCreate(TObject *Sender)
{
	LaGrille->ColWidths[0]=60;
	for(int i=1;i<4;i++)LaGrille->ColWidths[i]=30;
	for(int i=4;i<7;i++)LaGrille->ColWidths[i]=60;

	LaGrille->Cells[0][1]="Janvier";
	LaGrille->Cells[0][2]="Février";
	LaGrille->Cells[0][3]="Mars";
	LaGrille->Cells[0][4]="Avril";
	LaGrille->Cells[0][5]="Mai";
	LaGrille->Cells[0][6]="Juin";
	LaGrille->Cells[0][7]="Juillet";
	LaGrille->Cells[0][8]="Août";
	LaGrille->Cells[0][9]="Septembre";
	LaGrille->Cells[0][10]="Octobre";
	LaGrille->Cells[0][11]="Novembre";
	LaGrille->Cells[0][12]="Décembre";

	LaGrille->Cells[1][0]="  -1";
	LaGrille->Cells[2][0]="   0";
	LaGrille->Cells[3][0]="   1";

	LaGrille->Cells[4][0]="  -1";
	LaGrille->Cells[5][0]="   0";
	LaGrille->Cells[6][0]="   1";

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::FormActivate(TObject *Sender)
{
//static bool debut=true;
	float total;
//if(debut==true){debut=false;return;}

	Visible=true;
	LabelModifie->Visible=false;

	EdProduit->Text=Item->Nom;
	if(Repart==NULL) Repart=new CL_Repart();

	EdValeur->Text=FloatToStrF((double)ValTot,ffNumber,7,0);
	Repart->GrilleEcrire(LaGrille,ValTot);
	total=Repart->Total();
	EdTotPcent->Text=FloatToStrF((double)total,ffNumber,7,0);
	EdTotValeur->Text=FloatToStrF((double)ValTot*total/100.,ffNumber,7,0);
	LaGrille->Col=1;LaGrille->Row=1;

// Col se rapporte à la partie active de la Grille
	if(ValTot)
	{
		LaGrille->ColCount=7;
		GBValeur->Visible=true;
		EdTotValeur->Visible=true;
		LabTotalVal->Visible=true;
	}
	else
	{
		LaGrille->ColCount=4;
		GBValeur->Visible=false;
		EdTotValeur->Visible=false;
		LabTotalVal->Visible=false;
	}

}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	float total;
//bool rep;
	int rep;
	if(Repart->Egal==false)
	SGSelectCell(this,LaGrille->Col,LaGrille->Row,true);
//	Repart->GrilleLire(LaGrille);
	total=Repart->Total();
	if(total<100-5 ||total >100+5)
	{
		rep=MessageBox(Handle,"Vous gardez ?","Total #100",
				MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDYES) CanClose=true;
		else CanClose=false;
	}
	Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER",
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDYES) Application->Terminate();

	else return;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::SGKeyPress(TObject *Sender, char &Key)
{

	if(Key >='0' && Key <='9') {LabelModifie->Visible=true; return;}
	else if(Key=='-') {LabelModifie->Visible=true; return;}
	else if(Key=='.') {LabelModifie->Visible=true; return;}
	else if(Key==VK_BACK) {LabelModifie->Visible=true; return;}
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::BtRepBasClick(TObject *Sender)
{
	ShowMessage("BtRepBasClick");
}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::SGSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect)
{
	int i,n;
	int c;
	AnsiString as;
	float tot,val;
	if(LaGrille->Col<4)
	{
		n=(LaGrille->Col-1)*12+LaGrille->Row-1;
		Repart->Pcent[n]=Repart->LireCell(LaGrille,LaGrille->Col,LaGrille->Row);
		val=ValTot*Repart->Pcent[n]/100.;
		if(val)
		LaGrille->Cells[LaGrille->Col+3][LaGrille->Row]=FloatToStrF((double)val,ffNumber,7,0);
		else
		LaGrille->Cells[LaGrille->Col+3][LaGrille->Row]=" ";
//        Col=ACol;
//        Row=ARow-1;
	}
	else
	{
		val=Repart->LireCell(LaGrille,LaGrille->Col,LaGrille->Row);
		LaGrille->Cells[LaGrille->Col][LaGrille->Row]=Repart->Aff(val);
		n=(LaGrille->Col-4)*12+LaGrille->Row-1;
		Repart->Pcent[n]=(val/ValTot)*100.;
		val=Repart->Pcent[n];
		if(val)
		LaGrille->Cells[LaGrille->Col-3][LaGrille->Row]=FloatToStrF((double)val,ffNumber,7,0);
		else
		LaGrille->Cells[LaGrille->Col-3][LaGrille->Row]=" ";
	}
	tot=Repart->Total();

	EdTotPcent->Text=FloatToStrF((double)tot,ffNumber,7,0);
	tot*=ValTot;
	tot/=100.;
	EdTotValeur->Text=FloatToStrF((double)tot,ffNumber,7,0);

}
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::BtBn100Click(TObject *Sender)
{
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	if(c>=4)return;

	LaGrille->Cells[c][r]=100;
	LaGrille->Cells[c+3][r]=FloatToStrF((double)ValTot,ffNumber,7,0);
}
//---------------------------------------------------------------------------
//  100/12
//---------------------------------------------------------------------------
void __fastcall TFenRepartFrm1::BtBnEgalClick(TObject *Sender)
{
	int i;
	int c=LaGrille->Col;
	int r=LaGrille->Row;
	int k;
	float tot;
	Repart->Egal=true;
	if(c>=4)return;
	for(i=0;i<12;i++)
	{
		LaGrille->Cells[c][r]=FloatToStrF((double)100./12.,ffNumber,7,2);
		LaGrille->Cells[c+3][r]=FloatToStrF((double)ValTot/12.,ffNumber,7,0);
		k=(c-1)*12+r-1;
		Repart->Pcent[k]=100./12.;
		if(r<12) r++;
		else
		{
			c++;r=1;
			if(c==4) break;
		}
	}

	tot=Repart->Total();

	EdTotPcent->Text=FloatToStrF((double)tot,ffNumber,7,0);
	tot*=ValTot;
	tot/=100.;
	EdTotValeur->Text=FloatToStrF((double)tot,ffNumber,7,0);

}
//---------------------------------------------------------------------------

