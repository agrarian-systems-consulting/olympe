//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop
#include "TVChoixAniProCha.h"

#include "Troupeau.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
extern CL_ES *ES;

//---------------------------------------------------------------------------
//           Les BOUTONS
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnStockerClick(TObject *Sender)
{
	//verif et stocker avant de passer à la suite
	if (DernierePage==TSNature)
	{
		ShowMessage("A faire");
	}
	else if(DernierePage==TSMaxi)
	{
		DeGrilleMaxi(GrilleMaxi);
		LaGrille=GrilleMvt;
		BtBnSimulerClick(this);
	}
	else if(DernierePage==TSPrix) DeGrillePrix(GrillePrix);
	else if(DernierePage==TSValInv) DeGrilleValInv(GrilleValInv);
	else if(DernierePage==TSMouvement)
	{
		VideLstMvtAni();
		CreeLstMvtAni();
	}
	else if(DernierePage==TSProCha) DeGrilleProCha(GrilleProCha);
	ES->ecrireFichier();
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::LBTroupeauClick(TObject *Sender)
{
	int n;
	AnsiString s;
	n=LBTroupeau->ItemIndex;
	s=LBTroupeau->Items->Strings[n];
	if(s=="[...]")
	{
		LBChoixBestiauxFrm->Show();
		return;
	}
	TroupeauEnCours=(CL_Troupeau*)LBTroupeau->Items->Objects[n];
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnProchaClick(TObject *Sender)
{
	CreeTVAtelier (TVChoixAniProChaFrm->TV, V_CatAnimaux,V_Animaux);
	TVChoixAniProChaFrm->LaGrille=LaGrille;
	TVChoixAniProChaFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnSansBorneClick(TObject *Sender)
{
	int c,r;
	int n;
	CL_InvAni *invAni;
	c=GrilleMaxi->Col;
	r=GrilleMaxi->Row;
	invAni=(CL_InvAni*)GrilleMaxi->Objects[0][r];
	n=c-2;
	if(n<0)return;
	if(r==0)return;
	invAni->EffMax[n]=SANSBORNE;
	GrilleMaxi->Cells[c][r]="";
	LabelModifie->Visible=true;

}

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtReportDroitClick(TObject *Sender)
{
	/*
	 if     (DernierePage==TSNature)
	 {
	 ;//a faire
	 }
	 */
	if (DernierePage==TSMaxi) BtRepDroitNum();
	else if(DernierePage==TSPrix) BtRepDroitNum();
	else if(DernierePage==TSValInv) BtRepDroitNum();
	else if(DernierePage==TSMouvement) ShowMessage("A faire");
	else if(DernierePage==TSProCha) BtRepDroitProCha();

	LabelModifie->Visible==false;

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepDroitNum(void)
{
	int c,c0,r0;
	if(c0<2) return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepDroitProCha(void)
{
	int c,c0,r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	//ReAffFloat(c0,r0,digits);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
		LaGrille->Objects[c][r0]=LaGrille->Objects[c0][r0];
	}
}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::BtReportBasClick(TObject *Sender)
{
	if (DernierePage==TSMaxi) BtRepBasNum();
	else if(DernierePage==TSPrix) BtRepBasNum();
	else if(DernierePage==TSValInv) BtRepBasNum();
	else if(DernierePage==TSMouvement) ShowMessage("A faire");
	else if(DernierePage==TSProCha) BtRepBasProCha();

	LabelModifie->Visible==false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepBasNum(void)
{
	int r,c0,r0;
	if(c0<2) return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	for(r=r0+1;r<LaGrille->RowCount;r++)
	{
		if(RepPossible(c0,r)==false) continue;
		LaGrille->Cells[c0][r]=LaGrille->Cells[c0][r0];
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepBasProCha(void)
{
	int r,c0,r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	//ReAffFloat(c0,r0,digits);
	for(r=r0+1;r<LaGrille->RowCount;r++)
	{
		if(RepPossible(c0,r)==false) continue;
		LaGrille->Cells[c0][r]=LaGrille->Cells[c0][r0];
		LaGrille->Objects[c0][r]=LaGrille->Objects[c0][r0];
	}
}
