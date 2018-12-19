//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "AgriSaisie.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "Assol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAssolFrm *AssolFrm;
extern CL_Trad *T;
int DigitAssol;
//---------------------------------------------------------------------------
__fastcall TAssolFrm::TAssolFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// METHODES A CREER
//-----------------------------------------------------------------------------
void __fastcall TAssolFrm::Personnaliser(void)
{
	Grille0->Options>>goAlwaysShowEditor;
	Grille0->Options>>goEditing;
	Grille0->EditorMode=false;
	Grille0->Options<<goDrawFocusSelected;
	Caption=L_Assol;
}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
void __fastcall TAssolFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
	LaGrille->ColCount=11;
	LaGrille->RowCount=4;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TAssolFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[11];
	int c;
	largeur[0]=128;
	for(c=1;c<11;c++)largeur[c]=64;
	LaGrille->RowCount=20; //2;
	LaGrille->ColCount =11;
	LaGrille->FixedCols=0;//201206
	LaGrille->FixedRows=1;

	for(c=0;c<11;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+25; //place pour l'ascenseur

//    LaGrille->Cells[0][0]="CULTURE";
//	for(int i=0;i<10;i++)
//        LaGrille->Cells[i+1][0]="  "+AnsiString(Agri->DefSim->An_0+i);

	AjoutRow=true;
	CellAVerifier=false;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TAssolFrm::VersGrille(TStringGrid *grille)
{
	CL_Valeur *culture;
	CL_Verger *verger,*vivrier;
	float surCult[N_X],surCultDerobe[N_X];
	float surPer[N_X],surPerDerobe[N_X];
	float surViv[N_X],surVivDerobe[N_X];
	float surTot[N_X];
	int nbCult,nbCultDerobe;
	int nbPer, nbPerDerobe;
	int nbViv, nbVivDerobe;
	int nbTot;
	int nbLi;
	int i,j;
	int row,col;
//int an_0=Agri->DefSim->An_0;
	int digits;
	if(RGPrecision->ItemIndex==0) digits=0;
	else digits=2;
	for(i=0;i<10;i++)
	LaGrille->Cells[i+1][0]="  "+AnsiString(Agri->DefSim->An_0+i);

	// derobe Perenne Vivrier 220102
	row=1;
	memset(surCult, 0,sizeof(float)*N_X);
	memset(surCultDerobe, 0,sizeof(float)*N_X);
	memset(surPer, 0,sizeof(float)*N_X);
	memset(surPerDerobe, 0,sizeof(float)*N_X);
	memset(surViv, 0,sizeof(float)*N_X);
	memset(surVivDerobe, 0,sizeof(float)*N_X);
	memset(surTot, 0,sizeof(float)*N_X);

	/// calcul du nombre de culture et du nombre de derobe
	nbCult=0;
	nbCultDerobe=0;
	for(i=0;i<Agri->V_Culture->Nbelt;i++)
	{
		culture=Agri->V_Culture->Vecteur[i];
		if(culture->Atelier->Derobe==false) nbCult++;
		else nbCultDerobe++;
	}
	nbPer=0;
	nbPerDerobe=0;
	for(i=0;i<Agri->V_Verger->Nbelt;i++)
	{
		verger=Agri->V_Verger->Vecteur[i];
		if(verger->Atelier->Derobe==false) nbPer++;
		else nbPerDerobe++;
	}
	nbViv=0;
	nbVivDerobe=0;
	for(i=0;i<Agri->V_Vivrier->Nbelt;i++)
	{
		vivrier=Agri->V_Vivrier->Vecteur[i];
		if(vivrier->Atelier->Derobe==false) nbViv++;
		else nbVivDerobe++;
	}
	nbLi=1;
	if(nbCult+nbCultDerobe >0) nbLi++; //titre
	if(nbCult >0) nbLi+=nbCult+1;//nbCult + ligne total
	if(nbCultDerobe >0) nbLi+=nbCultDerobe+2;//DEROBE +nbCultDerobe+total

	if(nbPer+nbPerDerobe >0) nbLi++;//titre
	if(nbPer >0) nbLi+=nbPer+1;//nbPer + ligne total
	if(nbPerDerobe >0) nbLi+=nbPerDerobe+2;//DEROBE +nbPerDerobe+total

	if(nbViv+nbVivDerobe >0) nbLi++;//titre
	if(nbViv >0) nbLi+=nbViv+1;//nbViv + ligne total
	if(nbVivDerobe >0) nbLi+=nbVivDerobe+2;//DEROBE +nbVivDerobe+total

	LaGrille->RowCount=nbLi+3;//total   200405
	LaGrille->Cells[0][0]="";

	row=1;
	// erreur aprés avoir appuyé sur précision le toatal des surfaces est nul
	// confusion nbTot n'est pas calculé
	// remplacer nbTot  par nbLi
	// supprimer nbTot
	// A Faire au calme
	nbTot=nbLi;// test 260202
	// cultures principales
	if(nbTot>0 && nbCult+nbCultDerobe>0)
	{
		LaGrille->Cells[0][row]=T->L_Culture; //"CULTURES";
		row++;
	}
	if(nbTot>0 && nbCult>0)
	{
		for(i=0;i<Agri->V_Culture->Nbelt;i++)
		{
			culture=Agri->V_Culture->Vecteur[i];
			if(culture->Atelier->Derobe==true) continue;

			LaGrille->Cells[0][row]=culture->Atelier->Nom;
			for(j=0,col=1;j<N_X;j++,col++)
			{
				LaGrille->Cells[col][row]=Aff(culture->Valeur[j],digits);
				surCult[j]+=culture->Valeur[j];
				surTot[j]+=culture->Valeur[j];
			}
			row++;
		}
		LaGrille->Cells[0][row]=L_TotCulture; //"total cultures";
		for(j=0,col=1;j<N_X;j++,col++)
		LaGrille->Cells[col][row]=Aff(surCult[j],digits);
		row++;
	}

	// dérobées
	if(nbTot>0 && nbCultDerobe>0)//nbTot=1 ou 2 ou 3
	{
		LaGrille->Cells[0][row]=L_Derobee; //"DEROBEES";
		row++;
		for(i=0;i<Agri->V_Culture->Nbelt;i++)
		{
			culture=Agri->V_Culture->Vecteur[i];
			if(culture->Atelier->Derobe==false) continue;

			LaGrille->Cells[0][row]=culture->Atelier->Nom;
			for(j=0,col=1;j<N_X;j++,col++)
			{
				LaGrille->Cells[col][row]=Aff(culture->Valeur[j],digits);
				surCultDerobe[j]+=culture->Valeur[j];
				//surTot[j]+=culture->Valeur[j];
			}
			row++;
		}
		LaGrille->Cells[0][row]=L_TotDerobee; //"total derobées";
		for(j=0,col=1;j<N_X;j++,col++)
		LaGrille->Cells[col][row]=Aff(surCultDerobe[j],digits);
		row++;
	}
	//Perennes
	if(nbTot>0 && nbPer+nbPerDerobe>0 )
	{
		LaGrille->Cells[0][row]=L_Perenne; //"PERENNE";
		row++;
	}
	if(nbTot>0 && nbPer>0 )
	{
		for(i=0;i<Agri->V_Verger->Nbelt;i++)
		{
			verger=Agri->V_Verger->Vecteur[i];
//            VergerSurface(verger);                       //280202
			if(verger->Atelier->Derobe==true) continue;

			//c'est déja calculé !?
//            AgriSaisieFrm->CalculSurfaceVerger(verger);
			LaGrille->Cells[0][row]=verger->Atelier->Nom;
			for(j=0,col=1;j<N_X;j++,col++)
			{
				LaGrille->Cells[col][row]=Aff(verger->SurfaceAn[j],digits);
				surPer[j]+=verger->SurfaceAn[j];
				surTot[j]+=verger->SurfaceAn[j];
			}
			row++;
		}
		LaGrille->Cells[0][row]=L_TotPerenne; //"total pérennes";
		for(j=0,col=1;j<N_X;j++,col++)
		LaGrille->Cells[col][row]=Aff(surPer[j],digits);
		row++;
	}
	//Perennes dérobées
	if(nbTot>0 && nbPerDerobe>0)//nbTot=1 ou 2 ou 3
	{
		LaGrille->Cells[0][row]=L_Derobee; //"DEROBEES";
		row++;
//        for(i=0;i<Agri->V_Culture->Nbelt;i++)
		for(i=0;i<Agri->V_Verger->Nbelt;i++)
		{
			verger=Agri->V_Verger->Vecteur[i];
			if(verger->Atelier->Derobe==false) continue;

			LaGrille->Cells[0][row]=verger->Atelier->Nom;
			for(j=0,col=1;j<N_X;j++,col++)
			{
				LaGrille->Cells[col][row]=Aff(verger->SurfaceAn[j],digits);
				surPerDerobe[j]+=verger->SurfaceAn[j];
				//surTot[j]+=culture->Valeur[j];
			}
			row++;
		}
		LaGrille->Cells[0][row]=L_TotDerobee; //"total derobées";
		for(j=0,col=1;j<N_X;j++,col++)
		LaGrille->Cells[col][row]=Aff(surPerDerobe[j],digits);
		row++;
	}

	if(nbTot>0 && nbViv+nbVivDerobe>0)
	{
		LaGrille->Cells[0][row]=L_Pluri; //"PLURIANNUELLE";
		row++;
	}
	if(nbTot>0 && nbViv>0)
	{
		for(i=0;i<Agri->V_Vivrier->Nbelt;i++)
		{
			vivrier=Agri->V_Vivrier->Vecteur[i];
//            AgriSaisieFrm->CalculSurfaceVivrier(verger);
//!!!!
			LaGrille->Cells[0][row]=vivrier->Atelier->Nom;
			for(j=0,col=1;j<N_X;j++,col++)
			{
				LaGrille->Cells[col][row]=Aff(vivrier->SurfaceAn[j],digits);
				surViv[j]+=vivrier->SurfaceAn[j];
				surTot[j]+=vivrier->SurfaceAn[j];
			}
			row++;
		}
		LaGrille->Cells[0][row]=L_TotPluri; //"total PluriAnnuelles";
		for(j=0,col=1;j<N_X;j++,col++)
		LaGrille->Cells[col][row]=Aff(surViv[j],digits);
		row++;
	}
	// Vivriers dérobées
	if(nbTot>0 && nbVivDerobe>0)//nbTot=1 ou 2 ou 3
	{
		LaGrille->Cells[0][row]=L_Derobee; //"DEROBEES";
		row++;
//        for(i=0;i<Agri->V_Verger->Nbelt;i++)
		for(i=0;i<Agri->V_Vivrier->Nbelt;i++)
		{
			vivrier=Agri->V_Vivrier->Vecteur[i];
			if(vivrier->Atelier->Derobe==false) continue;

			LaGrille->Cells[0][row]=vivrier->Atelier->Nom;
			for(j=0,col=1;j<N_X;j++,col++)
			{
				LaGrille->Cells[col][row]=Aff(vivrier->SurfaceAn[j],digits);
				surVivDerobe[j]+=vivrier->SurfaceAn[j];
				//surTot[j]+=culture->Valeur[j];
			}
			row++;
		}
		LaGrille->Cells[0][row]=L_TotDerobee; //"total derobées";
		for(j=0,col=1;j<N_X;j++,col++)
		LaGrille->Cells[col][row]=Aff(surVivDerobe[j],digits);
		row++;
	}
	LaGrille->Cells[0][row]=T->L_TotalM; //"TOTAL";
	for(j=0,col=1;j<N_X;j++,col++)
	LaGrille->Cells[col][row]=Aff(surTot[j],digits);
}
//----------------------------------------------------------------------------
void __fastcall TAssolFrm::VergerSurface(CL_Verger *verger)
{
	int n;
	int age,ageArr;
//	age=     AgriEnCours->DefSim->An_0-verger->AnPlant;
	age= Agri->DefSim->An_0-verger->AnPlant;
	ageArr= verger->AnArr-verger->AnPlant;
	for(n=0;n<N_X;n++)
	{
		verger->Phase[n]=-1;
		verger->SurfaceAn[n]=0;
		if(age>=0 && age <ageArr)
		verger->SurfaceAn[n]=verger->Surface;
		age++;
	}
}
//----------------------------------------------------------------------------
void __fastcall TAssolFrm::RGPrecisionClick(TObject *Sender)
{
//
//    if(RGPrecision->ItemIndex==0) RGPrecision->Tag=0;
//    else                          RGPrecision->Tag=2;
	VersGrille(Grille0);
}

//----------------------------------------------------------------------------
void TAssolFrm::TexteChaine(void) {
	L_TotCulture = T->TrouveTexte("AssolFrm", "L_TotCulture");
	L_Derobee = T->TrouveTexte("AssolFrm", "L_Derobee");
	L_TotDerobee = T->TrouveTexte("AssolFrm", "L_TotDerobee");
	L_Perenne = T->TrouveTexte("AssolFrm", "L_Perenne");
	L_TotPerenne = T->TrouveTexte("AssolFrm", "L_TotPerenne");
	L_Pluri = T->TrouveTexte("AssolFrm", "L_Pluri");
	L_TotPluri = T->TrouveTexte("AssolFrm", "L_TotPluri");
	L_Assol = T->TrouveTexte("AssolFrm", "L_Assol");
}
//--------------------------------------------
void TAssolFrm::TexteCaption(void) {
	AssolFrm->Caption = T->LC_Assolement;
	RGPrecision->Caption = T->LC_RGPrecision;
}
//--------------------------------------------
void TAssolFrm::IniCaption(void) {
	LC_Assolement = T->TrouveCaption("CL_Trad", "LC_Assolement");
	LC_RGPrecision = T->TrouveCaption("CL_Trad", "LC_RGPrecision");
}

bool __fastcall TAssolFrm::FormHelp(WORD Command, int Data, bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

