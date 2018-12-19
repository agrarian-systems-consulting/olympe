//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "Erreur.h"
//#include "Compilateur.h"
#include "ErreurImmoSommaire.h"

#include "MvtAni.h"
#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
//extern CL_Compil *Compil;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//***************************************************************************
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DesGrilles(void)
{
	switch(LaGrille->Tag)
	{
		case GAssol: DeGrilleValeur(Agri->V_Culture);break;
		case GPerenne: DeGrilleVerger(Agri->V_Verger); break;
		case GVivrier: DeGrilleVivrier(Agri->V_Vivrier); break;
		case GAni: DeGrilleValeur(Agri->V_Animaux);break;
		case GVariable: DeGrilleValeur(Agri->V_Variable);break;
		case GProduit: DeGrilleFormule(Agri->V_Produits);break;
		case GCharge: DeGrilleFormule(Agri->V_Charges);break;
		case GChStruct: DeGrilleFormule(Agri->V_ChStruct);break;
		case GRecDiv: DeGrilleFormule(Agri->V_RecDiv);break;
		case GDepDiv: DeGrilleFormule(Agri->V_DepDiv);break;
		case GRecFam: DeGrilleFormule(Agri->V_RecFam);break;
		case GDepFam: DeGrilleFormule(Agri->V_DepFam);break;
		case GExtNeg: DeGrilleFormule(Agri->V_ExtNeg);break;
		case GExtPos: DeGrilleFormule(Agri->V_ExtPos);break;
		case GEmpLT: DeGrilleEmpLT();break;
		case GEmpCT: DeGrilleEmpCT();break;
		case GSub: DeGrilleSub();break;
		case GPlact: DeGrillePlact();break;
		case GOccc: DeGrilleOccc();break;
		case GFinSom: DeGrilleFinSom();break;
		case GImmo: DeGrilleImmo();break;
		case GPetit: DeGrillePetit();break;
		case GInvSom: DeGrilleInvSom();break;
		case GCreance: DeGrilleCrDette(Agri->V_Creance);break;
		case GDette: DeGrilleCrDette(Agri->V_Dette);break;
		case GStock: DeGrilleStockIni(Agri->V_StockIni);break;
		case GPolStock: DeGrillePolStock();break; //cest fait dans PolStock
		case GPasse: DeGrillePasse();break;

		case GNotes: Agri->Notes=Memo->Text;break;
		default: ShowMessage("AgriSaisie DesGrilles Oubli");
	}
//    Calcul(Agri);
}

//---------------------------------------------------------------------------
// DeGrille  Atelier
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleValeur(CL_Vecteur<CL_Valeur> *vecteur)
{
	int row;
	CL_Valeur* valeur;
	int c,col;
	int col0=4;
	//g=LaGrille->Tag;
	//if(GrilleModif[g]==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		valeur=(CL_Valeur*)LaGrille->Objects[0][row];

		switch(valeur->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(valeur);
			break;
			case 'O'://origine
			case 'M'://modifié
			break;
		}
		for(c=0,col=col0;c<10;c++,col++)
		{
			if(LaGrille->Cells[col][row]=="") valeur->Valeur[c]=0;
			else
			valeur->Valeur[c]=GrilleFloat(col,row);
		}
		valeur->Flag='O';
	}
	if(vecteur->Nbelt==0) return;
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		valeur=vecteur->Vecteur[i];
		if(valeur->Flag=='S') {vecteur->sup(valeur);i--;}
	}
	return;
}
//---------------------------------------------------------------------------
// DeGrille  Verger
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleVerger(CL_Vecteur<CL_Verger> *vecteur)
{
	int row;
	CL_Verger* verger;
//int g;
//	g=LaGrille->Tag;
	//if(GrilleModif[g]==false) return;

	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		verger=(CL_Verger*)LaGrille->Objects[0][row];
		switch(verger->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(verger);
			break;
			case 'O'://origine
			case 'M'://modifié
			break;
		}

		verger->Surface =GrilleFloat(4,row);
		verger->AnPlant =GrilleInt(5,row);
		verger->AnArr =GrilleInt(6,row);
		verger->Flag='O';
	}
	if(vecteur->Nbelt==0) return;

	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		verger=vecteur->Vecteur[i];
		if(verger->Flag=='S') {vecteur->sup(verger);i--;}
	}
	return;
}
//---------------------------------------------------------------------------
// DeGrille  Vivrier
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleVivrier(CL_Vecteur<CL_Verger> *vecteur)
{
	int row;
	CL_Verger* verger;
//int g;
//	g=LaGrille->Tag;
	//if(GrilleModif[g]==false) return;

	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		verger=(CL_Verger*)LaGrille->Objects[0][row];
		switch(verger->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(verger);
			break;
			case 'O'://origine
			case 'M'://modifié
			break;
		}

		verger->Surface =GrilleFloat(4,row);
		verger->AnPlant =GrilleInt(5,row);
		verger->AnArr =verger->AnPlant+GrilleInt(6,row);
		verger->Flag='O';
	}
	if(vecteur->Nbelt==0) return;

	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		verger=vecteur->Vecteur[i];
		if(verger->Flag=='S') {vecteur->sup(verger);i--;}
	}
	return;
}
//---------------------------------------------------------------------------
// DeGrille  Inventaire Animaux
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleInvAni (CL_Vecteur<CL_InvAni> *vecteur)
{
	// a    supprimer tout est géré par InvAni
}
//---------------------------------------------------------------------------
// DeGrille  Formule
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleFormule(CL_Vecteur<CL_Formule> *vecteur)
{
	int row;
	CL_Formule* formule;
	int c,col; //,g;
//	g=LaGrille->Tag;
//    if(GrilleModif[g]==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		formule=(CL_Formule*)LaGrille->Objects[0][row];
		switch(formule->Flag)
		{
			case 'N': //nouveau
			vecteur->insSans(formule);// formule->No=Item->No
			formule->Flag='O';
			break;
			case 'O'://origine
			case 'M'://modifié
			formule->Flag='O';
			break;
		}
		for(c=0,col=4;c<10;c++,col++)
		{
			if (LaGrille->Cells[col][row]=="") formule->Valeur[c]=0;
			else formule->Valeur[c]=GrilleFloat(col,row);
		}
	}
	if(vecteur->Nbelt==0) return;

	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		formule=vecteur->Vecteur[i];
		if(formule->Flag=='S') {vecteur->sup(formule);i--;}
	}

	return;
}
//---------------------------------------------------------------------------
// DeGrille  LongTerme
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleEmpLT(void)
{

	int row;
	CL_EmpLT *empLT;
	CL_Vecteur<CL_EmpLT> *vecteur=Agri->V_EmpLT;

//	g=LaGrille->Tag;
//  if(GrilleModif[0]==false) return;
	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		DeGEmpLT(row);
	}
	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		empLT=vecteur->Vecteur[i];
		if(empLT->Flag=='S') {vecteur->sup(empLT);i--;}
	}
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGEmpLT(int row)
{
	CL_EmpLT *empLT;
	CL_Vecteur<CL_EmpLT> *vecteur=Agri->V_EmpLT;
	empLT=(CL_EmpLT*)LaGrille->Objects[0][row];

	switch(empLT->Flag)
	{
		case 'N': //nouveau
		vecteur->ins(empLT);
		case 'O':
		case 'M'://modifié
		empLT->Nom= GrilleChaine (2, row);
		empLT->Montant= GrilleFloat (3, row);
		empLT->Duree= GrilleInt (4, row);
		empLT->Taux= GrilleFloat (5, row);
		empLT->Duree2= GrilleInt (6, row);
		empLT->Taux2= GrilleFloat (7, row);
		empLT->Type= GrilleChaine (8, row);
		GrilleMoisAn (9, row,empLT->MReal,empLT->AReal);
		GrilleMoisAn (10,row,empLT->MRemb,empLT->ARemb);
		GrilleCarPermis(11,row,empLT->Pour,"EP");//ProbTrad!!
//            empLT->Calcul();
		break;
	}
	empLT->Flag='O';

}
//---------------------------------------------------------------------------
// DeGrille  CourtTerme
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleEmpCT(void)
{

	int row;
	CL_EmpCT *empCT;
	CL_Vecteur<CL_EmpCT> *vecteur=Agri->V_EmpCT;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		DeGEmpCT(row);
	}
	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		empCT=vecteur->Vecteur[i];
		if(empCT->Flag=='S') {vecteur->sup(empCT);i--;}
	}
	return;
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGEmpCT(int row)
{
	CL_EmpCT *empCT;
	CL_Vecteur<CL_EmpCT> *vecteur=Agri->V_EmpCT;

	empCT=(CL_EmpCT*)LaGrille->Objects[0][row];

	switch(empCT->Flag)
	{
		case 'N': //nouveau
		vecteur->ins(empCT);
		case 'O':
		case 'M'://modifié
		empCT->Nom= GrilleChaine (2, row);
		empCT->Montant= GrilleFloat (3, row);
		empCT->Taux= GrilleFloat (4, row);
		empCT->Type= GrilleCar (5, row);
		GrilleMoisAn (6, row,empCT->MReal,empCT->AReal);
		GrilleMoisAn (7,row,empCT->MRemb,empCT->ARemb);
		GrilleCarPermis (8,row,empCT->Pour,"EP");//ProbTrad!!
		break;
	}
	empCT->Flag='O';
}

//---------------------------------------------------------------------------
// DeGrille  Subvention
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleSub(void)
{

	int row;
	CL_Sub *sub;
	CL_Vecteur<CL_Sub> *vecteur=Agri->V_Sub;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		DeGSub(row);
	}
	if(vecteur->Nbelt==0) return;
//PROBLEME ligne supprimée
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		sub=vecteur->Vecteur[i];
		if(sub->Flag=='S') {vecteur->sup(sub);i--;}
	}
	return;
}
//------------------- -----------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGSub(int row)
{
	CL_Sub *sub;
	CL_Vecteur<CL_Sub> *vecteur=Agri->V_Sub;

	sub=(CL_Sub*)LaGrille->Objects[0][row];
//    sub->Flag='M';    //a voir
	switch(sub->Flag)
	{
		case 'N': //nouveau
		vecteur->ins(sub);
		case 'O':
		case 'M'://modifié
		sub->Nom= GrilleChaine (2, row);
		sub->Montant= GrilleFloat (3, row);
		GrilleMoisAn (4, row,sub->MReal,sub->AReal);
		sub->Duree= GrilleInt (5,row);
		break;
	}
	sub->Flag='O';
}
//---------------------------------------------------------------------------
// DeGrille  Placement
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrillePlact(void)
{

	int row;
	CL_Plact *plact;
	CL_Vecteur<CL_Plact> *vecteur=Agri->V_Plact;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		DeGPlact(row);
	}
	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		plact=vecteur->Vecteur[i];
		if(plact->Flag=='S') {vecteur->sup(plact);i--;}
	}
	return;
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGPlact(int row)
{
	CL_Plact *plact;
	CL_Vecteur<CL_Plact> *vecteur=Agri->V_Plact;

	plact=(CL_Plact*)LaGrille->Objects[0][row];

	switch(plact->Flag)
	{
		case 'N': //nouveau
		vecteur->ins(plact);
		case 'O':
		case 'M'://modifié
		plact->Nom= GrilleChaine (2, row);
		plact->Montant= GrilleFloat (3, row);
		plact->Taux= GrilleFloat (4, row);
		plact->Type= GrilleCar (5, row);
		GrilleMoisAn (6, row,plact->MReal,plact->AReal);
		GrilleMoisAn (7, row,plact->MTerme,plact->ATerme);
		GrilleCarPermis (8, row,plact->Pour,"EP");//ProbTrad!!

		break;
	}
	plact->Flag='O';

}
//---------------------------------------------------------------------------
// DeGrille  Occc
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleOccc(void)
{

	int row;
	CL_Occc *occc;
	CL_Vecteur<CL_Occc> *vecteur=Agri->V_Occc;

	if(LabelModifie->Visible==false) return;

	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		occc=(CL_Occc*)LaGrille->Objects[0][row];

		switch(occc->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(occc);
			case 'O':
			case 'M'://modifié
//                occc->Ex=       GrilleInt    (0, row);
			occc->Ex= row;
			occc->Montant= GrilleFloat (1, row);
			occc->Pcent= GrilleFloat (2, row);
			occc->Taux= GrilleFloat (3, row);
			//occc->Frais=    GrilleFloat  (6, row);
			occc->Frais=occc->Montant*(occc->Pcent/100)*(occc->Taux/100);
			break;
		}
		occc->Flag='O';

	}
	return;
}
//---------------------------------------------------------------------------
// DeGrille  FinSom
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleFinSom(void )
{
	int row;
	CL_FN_Xp1* nXp1;
	int c,col,cMax;
	AnsiString s;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_FinSom;
	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		nXp1=(CL_FN_Xp1*)LaGrille->Objects[0][row];
		/*
		 switch(nXp1->Flag)
		 {
		 case 'N':                                    //nouveau
		 vecteur->ins(nXp1);
		 break;
		 case 'O':                                    //origine
		 case 'M':                                    //modifié
		 break;
		 }
		 */
		if(row==1 || row==5) {col=3;cMax=N_X+1;}
		else {col=4;cMax=N_X;}
		for(c=0;c<cMax;c++,col++)
		{
			if(LaGrille->Cells[col][row]=="") nXp1->Valeur[c]=0;
			else
			nXp1->Valeur[c]=GrilleFloat(col,row);
		}
		nXp1->Flag='O';
	}
	if(vecteur->Nbelt==0) return;
	return;
}
//---------------------------------------------------------------------------
// DeGrille  Immo
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleImmo(void)
{

	int row;
	CL_Immo *immo;
	CL_Vecteur<CL_Immo> *vecteur=Agri->V_Immo;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		DeGImmo(row);
	}
	if(vecteur->Nbelt==0) return;
//PROBLEME ligne supprimée
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		immo=vecteur->Vecteur[i];
		if(immo->Flag=='S') {vecteur->sup(immo);i--;}
	}
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGImmo(int row)
{
	CL_Vecteur<CL_Immo> *vecteur=Agri->V_Immo;
	CL_Immo *immo;

	immo=(CL_Immo*)LaGrille->Objects[0][row];

	switch(immo->Flag)
	{
		case 'N': //nouveau
		vecteur->ins(immo);
		case 'O':
		case 'M'://modifié
		immo->Nom= GrilleChaine (2, row);
		immo->ValAchat= GrilleFloat (3, row);
		GrilleMoisAn (4, row,immo->MAchat,immo->AAchat);
		immo->TypeAmor= GrilleCar (5,row);
		immo->Duree= GrilleInt (6,row);
		//tva réglé dans LBChoix      7
		if(immo->Tva==NULL) {immo->Tva=TvaImmo;immo->NoTva=TvaImmo->No;}

		immo->ValVente= GrilleFloat (8,row);
		GrilleMoisAn (9, row,immo->MVente,immo->AVente);
		break;
	}
	immo->Flag='O';
}
//---------------------------------------------------------------------------
// DeGrille  Petit
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrillePetit(void)
{

	int row;
	CL_Petit *petit;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		petit=(CL_Petit*)LaGrille->Objects[0][row];
		petit->ValAchat= GrilleFloat (3, row);
	}
	return;
}
//---------------------------------------------------------------------------
// DeGrille  FinSom
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleInvSom(void )
{
	int row;
	CL_FN_Xp1* nXp1;
	int c,col,cMax;
	AnsiString s;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_InvSom;
	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		nXp1=(CL_FN_Xp1*)LaGrille->Objects[0][row];
		/*
		 switch(nXp1->Flag)
		 {
		 case 'N':                                    //nouveau
		 vecteur->ins(nXp1);
		 break;
		 case 'O':                                    //origine
		 case 'M':                                    //modifié
		 break;
		 }
		 */
		if(row==1) {col=3;cMax=N_X+1;}
		else {col=4;cMax=N_X;}
		for(c=0;c<cMax;c++,col++)
		{
			if(LaGrille->Cells[col][row]=="") nXp1->Valeur[c]=0;
			else
			nXp1->Valeur[c]=GrilleFloat(col,row);
		}
		nXp1->Flag='O';
	}
	if(vecteur->Nbelt==0) return;
	return;
}
//------------------------------------------------------------------------------
// creances dettes
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleCrDette(CL_Vecteur <CL_EnCours> *vecteur)
{

	int row;
	CL_EnCours *enCours;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		enCours=(CL_EnCours*)LaGrille->Objects[0][row];

		switch(enCours->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(enCours);
			case 'O':
			case 'M'://modifié
			//enCours->EnStock=  GrilleCar( 3,row);    110203
			enCours->Valeur= GrilleFloat (3, row);
			GrilleMoisAn (4, row,enCours->MPaie,enCours->APaie);

			break;
		}
		enCours->Flag='O';

	}
	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		enCours=vecteur->Vecteur[i];
		if(enCours->Flag=='S') {vecteur->sup(enCours);i--;}
	}
	return;
}
//---------------------------------------------------------------------------
// Stock ini
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleStockIni(CL_Vecteur <CL_StockIni> *vecteur)
{

	int row;
	CL_StockIni *stock;
	int i,c;

	if(LabelModifie->Visible==false) return;
	for(row=1;row<LaGrille->RowCount;row+=2)
	{
		if(RowVide(row)==true) continue;
		stock=(CL_StockIni*)LaGrille->Objects[0][row];

		switch(stock->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(stock);
			case 'O':
			case 'M'://modifié
			for(i=0,c=3;i<N_X;i++,c++)
			{
				stock->Quantite[i]= GrilleFloat(c, row);
				stock->PrixRevient[i]= GrilleFloat(c, row+1);
			}
			break;
		}
		stock->Flag='O';

	}
	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		stock=vecteur->Vecteur[i];
		if(stock->Flag=='S') {vecteur->sup(stock);i--;}
	}
	return;
}
//---------------------------------------------------------------------------
// PolStock
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrillePolStock(void)
{
	int r;
	CL_PolStock *polStock;
	Agri->V_PolStock->vide();
	for(r=1;r<LaGrille->RowCount;r++)
	{
		polStock=(CL_PolStock *)LaGrille->Objects[0][r];
		if(polStock==NULL) continue;

		polStock->LitRow(LaGrille,r);
		Agri->V_PolStock->insSans(polStock);
	}
}
//---------------------------------------------------------------------------
// Passe
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrillePasse(void)
{
	int r,c;
	CL_Elt *elt;
//CL_Formule *formule;
//	formule=Agri->V_ChStruct->Vecteur[0];

	if(LabelModifie->Visible==false)return;

	for(r=1;r<LaGrille->RowCount;r++)
	{
		elt=(CL_Elt*)LaGrille->Objects[0][r];
		for(c=0;c<5;c++)
		{
			elt->Passe[c]=GrilleFloat(c+3,r);
		}
	}
}

