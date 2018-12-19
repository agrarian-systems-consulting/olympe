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

#include "MvtAni.h"
#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
//extern CL_Compil *Compil;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//***************************************************************************
/*
 CONTROLE
 ControleCell est appelé par Grille0Click cf Forme00
 VerifGrille
 */
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCell(int col,int row)
{
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GAni:
		case GVariable: return ControleCellFloat(col,row,2);
		case GInvAni: return ControleCellInvAni(col,row);
		case GResul:
		case GClose:
		case GNotes: return true;

		case GVivrier: return ControleCellVivrier(col,row);
		case GPerenne: return ControleCellVerger(col,row);

		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		case GExtNeg:
		case GExtPos: return ControleCellFormule(col,row);
		case GEmpLT: return ControleCellEmpLT(col,row);
		case GEmpCT: return ControleCellEmpCT(col,row);
		case GSub: return ControleCellSub(col,row);
		case GPlact: return ControleCellPlact(col,row);
		case GOccc: return ControleCellOccc(col,row);
		case GFinSom: return ControleCellFloat(col,row,0);
		case GImmo: return ControleCellImmo(col,row);
		case GPetit: return ControleCellPetit(col,row);
		case GInvSom: return ControleCellFloat(col,row,0);
		case GCreance:
		case GDette: return ControleCellCreanceDette(col,row);
		case GStock: return ControleCellStockIni(col,row);
		default: ShowMessage("ControleCell Oubli");
		return true;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellFloat(int col,int row,int digits)
{
	if(col<3)return true;

	ReAffFloat(col,row,digits);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellVerger(int col,int row)
{
	int anPlant,anArr;
	if(col==5 )
	{
		anPlant=GrilleInt(5,row);
		if(anPlant<100)
		{
			if(anPlant>60) anPlant+=1900;
			else anPlant+=2000;
			LaGrille->Cells[5][row]=Aff(anPlant);
		}
	}
	if(col==6)
	{
		anArr=GrilleInt(6,row);
		if(anArr<100)
		{
			if(anArr>60) anArr+=1900;
			else anArr+=2000;
			LaGrille->Cells[5][row]=Aff(anArr);
		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellVivrier(int col,int row)
{
	int anPlant;
	if(col==5 )
	{
		anPlant=GrilleInt(5,row);
		if(anPlant<100)
		{
			if(anPlant>60) anPlant+=1900;
			else anPlant+=2000;
			LaGrille->Cells[5][row]=Aff(anPlant);
		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellInvAni(int col,int row)
{
	int digits=0;
	CL_InvAni *invAni;
	invAni=(CL_InvAni*)LaGrille->Objects[0][row];
	// impossible ???
	if (invAni==NULL) return false;

/// on peut saisir seult en
///  3 val inventaire
///  4 effectif début
	switch(col)
	{
		case 3:
		invAni->ValUnit=GrilleFloat(col,row);
		ReAffFloat(col,row,digits);
		break;
		case 4:
		invAni->Effectif[0]=GrilleInt(col,row);
		MvtAniFrm->CalculMvt();
		break;
//        default:
//            ShowMessage("Problème dans ControleCellInvAni(");
	}
	return true;
}
//---------------------------------------------------------------------------
//bool __fastcall TAgriSaisieFrm::ControleCellFormule(int col,int row)
// cf AgriSaisieFormule
//-----------------------------------------------------------------------------
//bool __fastcall TAgriSaisieFrm::CreeProg(CL_Formule *formule,int n)
// cf AgriSaisieFormule
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellEmpLT(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_EmpLT *empLT;

	LabelModifie->Visible=true;
	empLT=(CL_EmpLT*)LaGrille->Objects[0][row];
	if(empLT!=NULL)
	{
		if(empLT->Flag!='N')
		empLT->Flag='M';
	}
	else
	{
		empLT=new CL_EmpLT;
		empLT->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)empLT;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	switch(col)
	{
		case 3: //montant
		ReAffFloat(col,row,0);
		return true;
		case 4://durée1
		case 6://durée2
		ReAffInt(col,row);
		return true;
		case 5://taux1
		case 7://taux2
		ReAffFloat(col,row,2);
		return true;
		case 8:
		return GrilleEmpLTType(col,row,remb,freq);

		case 9://réalisation
		case 10://remboursement
		return GrilleMoisAn(col,row,mois,an);
		case 11://Entreprise ou Privé
		return GrilleCarPermis(col,row,type,"EP");
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellEmpCT(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_EmpCT *empCT;

	LabelModifie->Visible=true;
	empCT=(CL_EmpCT*)LaGrille->Objects[0][row];
	if(empCT!=NULL)
	{
		if(empCT->Flag!='N')
		empCT->Flag='M';
	}
	else
	{
		empCT=new CL_EmpCT;
		empCT->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)empCT;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	switch(col)
	{
		case 3: //montant
		ReAffFloat(col,row,0);
		return true;
		case 4://taux
		ReAffFloat(col,row,2);
		return true;
		case 5://interet Normal ou Precompte N ou P
		return GrilleCarPermis(col,row,type,"NP");
		case 6://réalisation
		case 7://remboursement
		return GrilleMoisAn(col,row,mois,an);
		case 8://Entreprise ou Privé
		return GrilleCarPermis(col,row,type,"EP");
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellSub(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_Sub *sub;

	LabelModifie->Visible=true;
	sub=(CL_Sub*)LaGrille->Objects[0][row];
	if(sub!=NULL)
	{
		if(sub->Flag!='N')
		sub->Flag='M';
	}
	else
	{
		sub=new CL_Sub;
		sub->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)sub;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	switch(col)
	{
		case 3: //montant
		ReAffFloat(col,row,0);
		return true;
		case 4://date
		return GrilleMoisAn(col,row,mois,an);
		case 5://durée
		ReAffInt(col,row);
		return true;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellPlact(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_Plact *plact;

	LabelModifie->Visible=true;
	plact=(CL_Plact*)LaGrille->Objects[0][row];
	if(plact!=NULL)
	{
		if(plact->Flag!='N')
		plact->Flag='M';
	}
	else
	{
		plact=new CL_Plact;
		plact->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)plact;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	switch(col)
	{
		case 3: //montant
		ReAffFloat(col,row,0);
		return true;
		case 4://taux
		ReAffFloat(col,row,2);
		return true;
		case 5:// type A interet versé annuellement F à la fin
		return GrilleCarPermis(col,row,type,"FA");
		case 6://réalisation
		case 7://remboursement
		return GrilleMoisAn(col,row,mois,an);
		case 8://Entreprise ou Privé
		return GrilleCarPermis(col,row,type,"EP");
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellOccc(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_Occc *occc;
	float montant,pcent,taux,frais;
//040302
	LabelModifie->Visible=true;
	occc=(CL_Occc*)LaGrille->Objects[0][row];
	if(occc!=NULL)
	{
		if(occc->Flag!='N')
		occc->Flag='M';
	}
	else
	{
		occc=new CL_Occc;
		occc->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)occc;
		LaGrille->Cells[0][row]=row;
	}
//    AjouterRow();
	montant=GrilleFloat(1,row);
	pcent= GrilleFloat(2,row);
	taux= GrilleFloat(3,row);
	frais=montant*(pcent/100)*(taux/100);
	LaGrille->Cells[4][row]=Aff(frais,0);
	switch(col)
	{
		case 1: //montant
		ReAffFloat(col,row,0);
		return true;
		case 2://% consommé
		ReAffFloat(col,row,0);
		return true;
		case 3://taux
		ReAffFloat(col,row,2);
		return true;
//        case 6:         //frais
//            LaGrille->Cells[7][row]=Aff(frais,0);
//            return true;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellImmo(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_Immo *immo;

	LabelModifie->Visible=true;
	immo=(CL_Immo*)LaGrille->Objects[0][row];
	if(immo!=NULL)
	{
		if(immo->Flag!='N')
		immo->Flag='M';
	}
	else
	{
		immo=new CL_Immo;
		immo->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)immo;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	switch(col)
	{
		case 3: //val d'achat
		ReAffFloat(col,row,0);
		return true;
		case 4://année achat
		return GrilleMoisAn(col,row,mois,an);
		case 5://Dégressif Lineaire Nul
		return GrilleCarPermis(col,row,type,"DLN");
		case 6://Durée d'amortissement
		ReAffInt(col,row);
		return true;
		//7 tva
		case 8://valeur de vente
		ReAffFloat(col,row,0);
		return true;
		case 9://date Vente
		return GrilleMoisAn(col,row,mois,an);
//            return true;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellPetit(int col,int row)
{
	int mois, an;
	char type;
	CL_Petit *petit;

	LabelModifie->Visible=true;
	petit=(CL_Petit*)LaGrille->Objects[0][row];
	if(petit!=NULL)
	{
		if(petit->Flag!='N')
		petit->Flag='M';
	}
	else
	{
		petit=new CL_Petit;
		petit->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)petit;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	switch(col)
	{
		case 3: //val d'achat
		ReAffFloat(col,row,0);
		return true;
		//4 tva
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellCreanceDette(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_EnCours *enCours; //A voir
	int colSaisie;
	LabelModifie->Visible=true;
	enCours=(CL_EnCours*)LaGrille->Objects[0][row];
	if(enCours!=NULL)
	{
		if(enCours->Flag!='N')
		enCours->Flag='M';
	}
	else
	{
		enCours=new CL_EnCours;
		enCours->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)enCours;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	if(col>=colSaisie)
	ReAffFloat(col,row,0);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellStockIni(int col,int row)
{
	int mois, an;
	char type;
	char remb,freq;
	CL_StockIni *stock;

	LabelModifie->Visible=true;
	stock=(CL_StockIni*)LaGrille->Objects[0][row];
	if(stock!=NULL)
	{
		if(stock->Flag!='N')
		stock->Flag='M';
	}
	else
	{
		stock=new CL_StockIni;
		stock->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)stock;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	/// 2 nom
	/// 3 valeur initiale
	/// 4 taux d'augmentation de la valeur par an
	/// 5 6 7... valeur vendue par an
	switch(col)
	{
		case 3: //valeur en stock  stock->ValStock[0]
		ReAffFloat(col,row,0);
		return true;
		case 4://taux augmentation par an
		ReAffFloat(col,row,2);
		return true;
		case 5://vente
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		ReAffFloat(col,row,0);
		return true;
	}
	return true;
}
//-----------------------------------------------------------------------------
//VerifGrille
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrille(void)
{
	bool correct;
	switch(LaGrille->Tag)
	{
		case GAssol: correct=VerifGrilleNom( );break;
		case GPerenne: correct=VerifGrilleVerger ( );break;
		case GVivrier: correct=VerifGrilleVivrier( );break;
		case GInvAni:
		case GAni: correct=VerifGrilleNom( );break;
		case GVariable: correct=VerifGrilleNom( );break;
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		case GExtNeg:
		case GExtPos: correct=VerifGrilleFormule( );break;
		case GEmpLT: correct=VerifGrilleEmpLT();break;
		case GEmpCT: correct=VerifGrilleEmpCT();break;
		case GSub: correct=VerifGrilleSub();break;
		case GPlact: correct=VerifGrillePlact();break;
		case GOccc: correct=VerifGrilleOccc();break;
		case GFinSom: correct=VerifGrilleFinSom();break;
		case GImmo: correct=VerifGrilleImmo();break;
		case GPetit: correct=VerifGrillePetit();break;
		case GInvSom: correct=VerifGrilleInvSom();break;
		case GCreance:
		case GDette: correct=VerifGrilleCreanceDette();break;
		case GStock: correct=VerifGrilleStockIni();break;
		case GNotes: correct=true;break;
		case GPolStock: correct=true;break; //le controle est fait dans PolStock
		default: ShowMessage("VerifGrille Oubli");
	}
	return correct;
}
//-----------------------------------------------------------------------------
// existence de nom
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleNom(void)
{
	int row;
	bool correct=true;
	char buf[100];

	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(CellVide(2,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleVerger(void)
{
	int row;
	bool correct=true;
	char buf[100];
	int anArr;
	int anPlant;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(CellVide(2,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(4,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de surface ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(5,row))
		{
			correct=false;
			ErreurFrm->Edit->Lines->Add(buf);
			sprintf(buf,"ligne n°:%2d Pas de date de plantation ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		anPlant=GrilleInt(5,row);

		if(CellVide(6,row))
		{
			anArr=anPlant+100;
			LaGrille->Cells[6][row]=Aff(anArr);
		}
		else
		anArr=GrilleInt(6,row);

		if(anArr <= anPlant)
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Arrachage AVANT Plantation ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	if(correct==false)ErreurFrm->Show();
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleVivrier(void)
{
	int row;
	bool correct=true;
	char buf[100];
	int duree;
	CL_Verger *vivrier;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		vivrier=(CL_Verger*)LaGrille->Objects[0][row];
		if(RowVide(row)==true) continue;

		if(CellVide(2,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(4,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de surface ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(5,row))
		{
			correct=false;
			ErreurFrm->Edit->Lines->Add(buf);
			sprintf(buf,"ligne n°:%2d Pas de date de plantation ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}

		if(CellVide(6,row))
		LaGrille->Cells[6][row]=Aff(vivrier->Atelier->NbPhase-1);

		duree=GrilleInt(6,row);
		if(duree >vivrier->Atelier->NbPhase-1)
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Durée trop longue ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	return correct;
}
//-----------------------------------------------------------------------------
// existence de nom
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleFormule(void)
{
	int row;
	bool correct=true;
	char buf[100];
//CL_Formule *formule;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(CellVide(2,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleEmpLT(void)
{
	int row;
	bool correct=true;
	bool rep=true;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		rep=VerifEmpLT(row);
		if(rep==false) correct=false;
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifEmpLT(int row)
{
	char buf[100];
	bool correct=true;
	int duree;
	CL_EmpLT* empLT;
	empLT=(CL_EmpLT*)LaGrille->Objects[0][row];
	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Durée 1",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Taux 1",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(6,row)==false)
	{
		if(CellVide(7,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de Taux 2",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	duree=GrilleInt(4,row)+GrilleInt(6,row);
	if(duree>50)
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Durée supérieure à 50 ans",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row)==false)
	{
		if(CellVide(6,row))
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de Durée 2",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	if(LaGrille->Cells[8][row]!=LaGrille->Cells[8][row].UpperCase())
	{
		LaGrille->Cells[8][row]=LaGrille->Cells[8][row].UpperCase();
		if(empLT->Flag!='N') empLT->Flag='M';
	}
	if(CellVide(8,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Type CA par défaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[8][row]="CA";
	}
	if(CellVide(9,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(10,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de remboursement ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(LaGrille->Cells[11][row]!=LaGrille->Cells[11][row].UpperCase())
	{
		LaGrille->Cells[11][row]=LaGrille->Cells[11][row].UpperCase();
		empLT->Flag='M';
	}
	LaGrille->Cells[11][row]=LaGrille->Cells[11][row].UpperCase();
	if(CellVide(11,row))
	{
		sprintf(buf,"ligne n°:%2d Entreprise ou Privé E par defaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[11][row]="E";
	}
	if(correct==true)correct=VerifDateEmpLT(row);

	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleEmpCT(void)
{
	int row;
	bool rep,correct=true;

	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		rep=VerifEmpCT(row);
		if(rep==false)correct=false;
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifEmpCT(int row)
{
	bool correct=true;
	char buf[100];
	int moisReal,anReal;
	int moisRemb,anRemb;
	float delai;

	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Taux ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		sprintf(buf,"ligne n°:%2d Intérêts Non précmptés N par defaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[5][row]="N";
	}
	if(CellVide(6,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de remboursement ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(8,row))
	{
		sprintf(buf,"ligne n°:%2d Entreprise ou Privé E par defaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[8][row]="E";
	}
	if(correct==true)
	{
		GrilleMoisAn (6, row, moisReal,anReal);
		GrilleMoisAn (7, row, moisRemb,anRemb);
		delai=((anRemb-1900)*12+moisRemb)-((anReal-1900)*12+moisReal);
		if(delai<=0)
		{
			sprintf(buf,"ligne n°:%2d Problème de date",row);
			ErreurFrm->Edit->Lines->Add(buf);
			correct= false;
		}
	}
	return correct;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifDateEmpLT(int row)
{
	char buf[100];
	int moisReal,anReal;
	int moisRemb,anRemb;
	char remb,freq;
	float delai,duree;
	int intervalle;

	GrilleMoisAn (9, row, moisReal,anReal);
	GrilleMoisAn (10, row, moisRemb,anRemb);
	delai=((anRemb-1900)*12+moisRemb)-((anReal-1900)*12+moisReal);
	if(delai<=0)
	{
		sprintf(buf,"ligne n°:%2d Problème de date",row);
		ErreurFrm->Edit->Lines->Add(buf);
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleSub(void)
{
	int row;
	bool correct=true;
	bool rep;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		rep=VerifSub(row);
		if(rep==false) correct=false;
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifSub(int row)
{
	bool correct=true;
	char buf[100];
	int moisReal,anReal;
	int duree;

	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Durée",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	duree=GrilleInt(5,row);
	if(duree>50)
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Durée supérieure à 50 ans",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrillePlact(void)
{
	int row;
	bool correct=true;
	bool rep;
	char buf[100];
	int moisReal,anReal;
	int moisTerme,anTerme;
	float delai;

	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		rep=VerifPlact(row);
		if (rep==false) correct=false;
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifPlact(int row)
{
	bool correct=true;
	bool rep;
	char buf[100];
	int moisReal,anReal;
	int moisTerme,anTerme;
	float delai;
	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Taux 1",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Type AF A défaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[5][row]="A";
	}
	if(CellVide(6,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date de terme",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(8,row))
	{
		sprintf(buf,"ligne n°:%2d Entreprise ou Privé E par defaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[8][row]="E";
	}
	if(correct==true)
	{
		GrilleMoisAn (6, row, moisReal,anReal);
		GrilleMoisAn (7, row, moisTerme,anTerme);
		delai=((anTerme-1900)*12+moisTerme)-((anReal-1900)*12+moisReal);
		if(delai<=0)
		{
			sprintf(buf,"ligne n°:%2d Problème de date",row);
			ErreurFrm->Edit->Lines->Add(buf);
			correct= false;
		}
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleOccc(void)
{
	bool correct=true;
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleFinSom(void)
{
	int i,j,c,c0,cMax,n;
	int row;
	bool correct=true;
	char buf[100];
	float tableau[7][N_X+1];
	float *detteLT,*rembLT,*nouvLT,*detteCT,*rembCT,*nouvCT;
	float vDette;
	float delta;
	bool propre=false;
	float limite=50;
	for(i=0;i<7;i++)
	for(j=0;j<N_X+1;j++) tableau[i][j]=0;

	cMax=3+N_X+1;
	for(row=1,i=0;row<LaGrille->RowCount;row++,i++)
	{
		if(RowVide(row)==true) continue;

		if(row==1) c0=3;
		else c0=4;
		for(c=c0,j=0;c<cMax;c++,j++)
		{
			if(LaGrille->Cells[c][row]=="") continue;
			else tableau[i][j]=GrilleFloat(c,row);
		}
	}
	detteLT=tableau[0];
	rembLT= tableau[1];
	nouvLT= tableau[3];

	detteCT=tableau[4];
	rembCT= tableau[5];
	nouvCT= tableau[7];

	for(int n=0;n<N_X;n++)
	{
//        detteLT[n+1]=detteLT[n]-rembLT[n]+empLT[n]);
		vDette=detteLT[n]-rembLT[n]+nouvLT[n];
		if(vDette!=detteLT[n+1])
		{
			delta=vDette-detteLT[n+1];
			if(delta>limite ||delta <-limite)
			{
				ErreurFrm->Edit->Clear();
				sprintf(buf,"Long Terme");
				propre=true;
				correct=false;
			}
		}
	}
	for(int n=0;n<N_X;n++)
	{
//        detteLT[n+1]=detteLT[n]-rembLT[n]+empLT[n]);
		vDette=detteCT[n]-rembCT[n]+nouvCT[n];
		if(vDette!=detteCT[n+1])
		{
			delta=vDette-detteCT[n+1];
			if(delta>limite ||delta <-limite)
			{
				if(propre==false)ErreurFrm->Edit->Clear();
				sprintf(buf,"Court Terme");
				correct=false;
			}
		}
	}
	if(correct==false)
	{
		sprintf(buf,"Erreur Vraisemblable La Formule:");
		ErreurFrm->Edit->Lines->Add(buf);
		sprintf(buf,"Dette[n]=Dette[n-1]-Remboursement[n]-Nouveau[n]");
		ErreurFrm->Edit->Lines->Add(buf);
		sprintf(buf,"N'est PAS vérifièe");
		ErreurFrm->Edit->Lines->Add(buf);
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleInvSom(void)
{
	int i,j,c,c0,cMax,n;
	int row;
	bool correct=true;
	char buf[100];
	float tableau[7][N_X+1];
	float *resid,*amor,*achat,*revente,*prodImmo;
//float *plusVal,*moinsVal;
	float vResid;
	float delta;
	float limite=50;

	for(i=0;i<7;i++)
	for(j=0;j<N_X+1;j++) tableau[i][j]=0;

	cMax=3+N_X+1;
	for(row=1,i=0;row<LaGrille->RowCount;row++,i++)
	{
		if(RowVide(row)==true) continue;

		if(row==1) c0=3;
		else c0=4;
		for(c=c0,j=0;c<cMax;c++,j++)
		{
			if(LaGrille->Cells[c][row]=="") continue;
			else tableau[i][j]=GrilleFloat(c,row);
		}
	}
	resid= tableau[0];
	amor= tableau[1];
	achat= tableau[2];
	revente= tableau[3];
//    plusVal=   tableau[4];
//    moinsVal=  tableau[5];
	prodImmo= tableau[6];
	for(int n=0;n<N_X;n++)
	{
//        resid[n+1]=resid[n]-amor[n]+achat[n]-revente[n]+prodImmo[n]);
		vResid=resid[n]-amor[n]+achat[n]-revente[n]+prodImmo[n];
		if(vResid!=resid[n+1])
		{
			delta=vResid-resid[n+1];
			if(delta>limite ||delta <-limite)

			correct=false;
		}
	}

	if(correct==false)
	{
		ErreurFrm->Edit->Clear();
		sprintf(buf,"Erreur Vraisemblable La Formule:");
		ErreurFrm->Edit->Lines->Add(buf);
		sprintf(buf,"Residuelle[n]=Residuelle[n-1]-Amortissement[n]+Achat[n]-Revente[n]+ProdImmo[n]");
		ErreurFrm->Edit->Lines->Add(buf);
		sprintf(buf,"N'est PAS vérifièe");
		ErreurFrm->Edit->Lines->Add(buf);
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleImmo(void)
{
	int row;
	bool rep;
	bool correct=true;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		rep=VerifImmo(row);
		if(rep==false) correct=false;
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifImmo(int row)
{
	bool correct=true;
	char buf[100];
	int mAchat,anAchat;
	int mVente,anVente;
	float delai;
	CL_Immo *immo;
	char typeAmor;
	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de Valeur à neuf",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de date d'achat",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de type d'amortissement",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	typeAmor=GrilleCar(5,row);
	if(typeAmor=='l') LaGrille->Cells[5][row]="L";
	else if(typeAmor=='d') LaGrille->Cells[5][row]="D";
	else if(typeAmor=='n') LaGrille->Cells[5][row]="N";

	if(CellVide(6,row) && LaGrille->Cells[5][row]!="N" )
	{
		correct=false;
		sprintf(buf,"ligne n°:%2d Pas de durée d'amortissement",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row))
	{
		// immo->Tva=NULL cf constructeur
		// si NULL immo->Tva=TvaDefaut cf deGrilleImmo
		/*
		 immo=(CL_Immo*)LaGrille->Objects[7][row];
		 immo->NoTva=  TvaImmo->No;
		 immo->Tva=    TvaImmo;
		 LaGrille->Cells[7][row]=TvaImmo->Nom;
		 */
		//correct=false;
		//sprintf(buf,"ligne n°:%2d Pas de TVA",row);
		//ErreurFrm->Edit->Lines->Add(buf);
	}
	if(correct==true)
	{
		if(CellVide(8,row)==false)
		{
			GrilleMoisAn (4, row, mAchat,anAchat);
			GrilleMoisAn (9, row, mVente,anVente);
			delai=((anVente-1900)*12+mVente)-((anAchat-1900)*12+mAchat);
			if(delai<=0)
			{
				sprintf(buf,"ligne n°:%2d Problème de date",row);
				ErreurFrm->Edit->Lines->Add(buf);
				correct= false;
			}
		}
	}

	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrillePetit(void)
{
	bool correct=true;
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleCreanceDette(void)
{
	int row;
	bool correct=true;
	bool rep;
	char buf[100];
	int mois,an;

	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(LaGrille->Cells[2][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(LaGrille->Cells[3][row].IsEmpty()) //EnStock
		{
			LaGrille->Cells[3][row]="N";
		}
		if(LaGrille->Cells[4][row].IsEmpty()) //Valeur
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de Valeur",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(LaGrille->Cells[5][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de date ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		else
		{
			rep=GrilleMoisAn(5,row,mois,an);
			if(rep==false)
			{
				correct=false;
				sprintf(buf,"ligne n°:%2d Erreur sur la date ",row);
				ErreurFrm->Edit->Lines->Add(buf);
			}
		}
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleStockIni(void)
{
	int row;
	int i,c;
	bool correct=true;
	char buf[100];
	int pcentAn;
	int pcentTot;
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(LaGrille->Cells[2][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	return correct;
}
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
		case GInvAni: DeGrilleInvAni(Agri->V_InvAni);break;
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

		case GNotes: Agri->Notes=Memo->Text;break;
		case GPolStock: break; //cest fait dans PolStock
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
	int c,col,g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;
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
		for(c=0,col=3;c<10;c++,col++)
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
	CL_Espece* espece;
	int g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

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
	int g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

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
	int row;
	CL_InvAni* invAni;
	int c,col,g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		invAni=(CL_InvAni*)LaGrille->Objects[0][row];
		/*   MvtAni a appelé TVChoix
		 et TVChoix pour les animaux a inseré invAni
		 switch(invAni->Flag)
		 {
		 case 'N':                                    //nouveau
		 vecteur->ins(invAni);
		 break;
		 case 'O':                                    //origine
		 case 'M':                                    //modifié
		 break;
		 }
		 */
		invAni->ValUnit=GrilleFloat(3,row);
		for(c=0,col=4;c<11;c++,col++)
		{
			if(LaGrille->Cells[col][row]=="") invAni->Effectif[c]=0;
			else
			invAni->Effectif[c]=GrilleInt(col,row);
		}
		invAni->Flag='O';
	}
	if(vecteur->Nbelt==0) return;
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		invAni=vecteur->Vecteur[i];
		if(invAni->Flag=='S') {vecteur->sup(invAni);i--;}
	}
	MvtAniFrm->CreeLstMvtAni();
	return;
}
//---------------------------------------------------------------------------
// DeGrille  Formule
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DeGrilleFormule(CL_Vecteur<CL_Formule> *vecteur)
{
	int row;
	CL_Formule* formule;
	int c,col,g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;
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
		for(c=0,col=3;c<10;c++,col++)
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
	int c,col,g;
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
		GrilleCarPermis(11,row,empLT->Pour,"EP");
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
	int c,col,g;
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
	int c,col,g;
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
		GrilleCarPermis (8,row,empCT->Pour,"EP");
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
	int c,col,g;
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
	int c,col,g;
	CL_Vecteur<CL_Plact> *vecteur=Agri->V_Plact;

//	g=LaGrille->Tag;
//  if(GrilleModif[0]==false) return;
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
	int c,col,g;
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
		GrilleCarPermis (8, row,plact->Pour,"EP");

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
	int c,col,g;
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
			occc->Ex= GrilleInt (0, row);
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
	int c,col,g;

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
	int c,col,g;
//CL_Vecteur<CL_Petit> *vecteur=Agri->V_Petit;

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

		if(row==1) {col=3;cMax=N_X+1;} //V Residuelle Bilan ->N_X+1 donnees
		else {col=4;cMax=N_X;} // autre ceg treso   ->N_X

		for(c=0;c<cMax;c++,col++)
		{
			if(LaGrille->Cells[col][row]=="")
			nXp1->Valeur[c]=0;
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
	int c,col,g;

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
			//enCours->EnStock=  GrilleCar( 3,row);
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
	int i,c,col,g;

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

