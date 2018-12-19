//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"

#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "Erreur.h"
#include "Compilateur.h"

#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
extern CL_Compil *Compil;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StockerOrdre(void)
{
	switch(LaGrille->Tag)
	{
		case GAssol: StOrdreValeur(Agri->V_Culture);break;
		case GPerenne: StOrdreVerger(Agri->V_Verger); break;
		case GAni: StOrdreValeur(Agri->V_Animaux);break;
		case GVariable: StOrdreValeur(Agri->V_Variable);break;
		case GProduit: StOrdreFormule(Agri->V_Produits);break;
		case GCharge: StOrdreFormule(Agri->V_Charges);break;
		case GChStruct: StOrdreFormule(Agri->V_ChStruct);break;
		case GRecPrive: StOrdreFormule(Agri->V_RecFam);break;
		case GDepPrive: StOrdreFormule(Agri->V_DepFam);break;
		case GExtNeg: StOrdreFormule(Agri->V_ExtNeg);break;
		case GExtPos: StOrdreFormule(Agri->V_ExtPos);break;
		case GEmpLT: StOrdreEmpLT();break;
		case GEmpCT: StOrdreEmpCT();break;
		case GSub: StOrdreSub();break;
		case GPlact: StOrdrePlact();break;
		case GImmo: StOrdreImmo();break;
		case GCreance: StOrdreStock(Agri->V_Creance);break;
		case GDette: StOrdreStock(Agri->V_Dette);break;
		default: ShowMessage("Stocker ordre A Faire");
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreValeur(CL_Vecteur<CL_Valeur> *vecteur)
{
	int i,r;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Valeur*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreVerger(CL_Vecteur<CL_Verger> *vecteur)
{
	int i,r;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Verger*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreFormule(CL_Vecteur<CL_Formule> *vecteur)
{
	int i,r;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Formule*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreEmpLT(void)
{
	int i,r;
	CL_Vecteur<CL_EmpLT> *vecteur=Agri->V_EmpLT;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_EmpLT*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreEmpCT(void)
{
	int i,r;
	CL_Vecteur<CL_EmpCT> *vecteur=Agri->V_EmpCT;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_EmpCT*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreSub(void)
{
	int i,r;
	CL_Vecteur<CL_Sub> *vecteur=Agri->V_Sub;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Sub*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdrePlact(void)
{
	int i,r;
	CL_Vecteur<CL_Plact> *vecteur=Agri->V_Plact;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Plact*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreImmo(void)
{
	int i,r;
	CL_Vecteur<CL_Immo> *vecteur=Agri->V_Immo;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Immo*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreStockIni(CL_Vecteur<CL_StockIni> *vecteur)
{
	int i,r;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_StockIni*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StOrdreCrDette(CL_Vecteur<CL_CrDette> *vecteur)
{
}
