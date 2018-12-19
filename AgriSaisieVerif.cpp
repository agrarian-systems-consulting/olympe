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

#include "ErreurImmoSommaire.h"
#include "ErreurFinSommaire.h"

#include "MvtAni.h"
#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//***************************************************************************
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
		case GBestiaux:
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
		case GPolStock: correct=VerifGrillePolStock();break;
		case GPasse: correct=true;break;
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
			sprintf(buf,L_ErrPasNom.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
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
			sprintf(buf,L_ErrPasNom.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(4,row))
		{
			correct=false;
			sprintf(buf,L_ErrPasSurf.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de surface ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(5,row))
		{
			correct=false;
			ErreurFrm->Edit->Lines->Add(buf);
			sprintf(buf,L_ErrPasDatePlant.c_str(),row);
//            sprintf(buf,"ligne n°:%2d Pas de date de plantation ",row);
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
			sprintf(buf,L_ErrArrach.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Arrachage AVANT Plantation ",row);
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
			sprintf(buf,L_ErrPasNom.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(4,row))
		{
			correct=false;
			sprintf(buf,L_ErrPasSurf.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de surface ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(5,row))
		{
			correct=false;
			ErreurFrm->Edit->Lines->Add(buf);
			sprintf(buf,L_ErrPasDatePlant.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de date de plantation ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}

		if(CellVide(6,row))
		LaGrille->Cells[6][row]=Aff(vivrier->Atelier->NbPhase-1);

		duree=GrilleInt(6,row);
		if(duree >vivrier->Atelier->NbPhase-1)
		{
			correct=false;
			sprintf(buf,L_ErrDurTropL.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Durée trop longue ",row);
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
//formule=(CL_Formule*)LaGrille->Objects[0][1];
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(CellVide(2,row))
		{
			correct=false;
			sprintf(buf,L_ErrPasNom.c_str(),row);
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
		sprintf(buf,L_ErrPasNom.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasMontant.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDuree.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Durée 1",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasTaux.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Taux 1",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(6,row)==false)
	{
		if(CellVide(7,row))
		{
			correct=false;
			sprintf(buf,L_ErrPasTaux2.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de Taux 2",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	duree=GrilleInt(4,row)+GrilleInt(6,row);
	if(duree>50)
	{
		correct=false;
		sprintf(buf,L_ErrDurSup50.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Durée supérieure à 50 ans",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row)==false)
	{
		if(CellVide(6,row))
		{
			correct=false;
			sprintf(buf,L_ErrPasDur2.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de Durée 2",row);
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
		sprintf(buf,L_ErrPasTypEmp.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Type CA par défaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[8][row]="CA";
	}
	if(CellVide(9,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateReal.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(10,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateRembEmp.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de remboursement ",row);
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
		sprintf(buf,L_ErrPasEPEmp.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Entreprise ou Privé E par defaut",row);
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
		sprintf(buf,L_ErrPasNom.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasMontant.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasTaux.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Taux ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		sprintf(buf,L_ErrIntEmpCT.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Intérêts Non précomptés N par defaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[5][row]="N";
	}
	if(CellVide(6,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateReal.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateRembEmp.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de remboursement ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(8,row))
	{
		sprintf(buf,L_ErrPasEPEmp.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Entreprise ou Privé E par defaut",row);
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
			sprintf(buf,L_ErrPbDate.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Problème de date",row);
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
	float delai;

	GrilleMoisAn (9, row, moisReal,anReal);
	GrilleMoisAn (10, row, moisRemb,anRemb);
	delai=((anRemb-1900)*12+moisRemb)-((anReal-1900)*12+moisReal);
	if(delai<=0)
	{
		sprintf(buf,L_ErrPbDate.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Problème de date",row);
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
	int duree;

	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasNom.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasMontant.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateReal.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDuree.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Durée",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	duree=GrilleInt(5,row);
	if(duree>50)
	{
		correct=false;
		sprintf(buf,L_ErrDurSup50.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Durée supérieure à 50 ans",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrillePlact(void)
{
	int row;
	bool correct=true;
	int rep;
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
	char buf[100];
	int moisReal,anReal;
	int moisTerme,anTerme;
	float delai;
	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasNom.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasMontant.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Montant",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasTaux.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Taux 1",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,L_ErrTypePlact.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Type AF A défaut",row);
		ErreurFrm->Edit->Lines->Add(buf);
		LaGrille->Cells[5][row]="A";
	}
	if(CellVide(6,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateReal.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de réalisation ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(7,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateTerme.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date de terme",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(8,row))
	{
		sprintf(buf,L_ErrPasEPEmp.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Entreprise ou Privé E par defaut",row);
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
			sprintf(buf,L_ErrPbDate.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Problème de date",row);
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

		if(row==1||row==5) c0=3; //130103
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
	nouvCT= tableau[6];

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
				sprintf(buf,L_LT.c_str());
				//sprintf(buf,"Long Terme");
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
				sprintf(buf,L_EmpCT.c_str());
				//sprintf(buf,"Court Terme");
				correct=false;
			}
		}
	}
	if(correct==false)
	{
		for(n=0;n<N_X+1;n++)
		{
			ErreurFinSommaireFrm->detteLT[n]=detteLT[n];
			ErreurFinSommaireFrm->detteCT[n]=detteCT[n];
		}
		for(n=0;n<N_X;n++)
		{
			ErreurFinSommaireFrm->rembLT[n]=rembLT[n];
			ErreurFinSommaireFrm->nouvLT[n]=nouvLT[n];

			ErreurFinSommaireFrm->rembCT[n]=rembCT[n];
			ErreurFinSommaireFrm->nouvCT[n]=nouvCT[n];
		}
		/*
		 sprintf(buf,"Erreur Vraisemblable La Formule:");
		 ErreurFrm->Edit->Lines->Add(buf);
		 sprintf(buf,"Dette[n]=Dette[n-1]-Remboursement[n]+Nouveau[n]");
		 ErreurFrm->Edit->Lines->Add(buf);
		 sprintf(buf,"N'est PAS vérifièe");
		 ErreurFrm->Edit->Lines->Add(buf);
		 */
	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrilleInvSom(void)
{
	int i,j,c,c0,cMax;
	int row;
	bool correct=true;
//char buf[100];
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
	prodImmo= tableau[6];

	for(int n=0;n<N_X;n++)
	{
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
		for(i=0;i<N_X+1;i++)
		{
			ErreurImmoSommaireFrm->Resid[i]=resid[i];
			ErreurImmoSommaireFrm->Amor[i]=amor[i];
			ErreurImmoSommaireFrm->Achat[i]=achat[i];
			ErreurImmoSommaireFrm->Revente[i]=revente[i];
			ErreurImmoSommaireFrm->ProdImmo[i]=prodImmo[i];
		}
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
//CL_Immo *immo;
	char typeAmor;
	if(CellVide(2,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasNom.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(3,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasValNeuf.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de Valeur à neuf",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(4,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasDateAchat.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de date d'achat",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(CellVide(5,row))
	{
		correct=false;
		sprintf(buf,L_ErrPasTypAmor.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de type d'amortissement",row);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	typeAmor=GrilleCar(5,row);
	if(typeAmor=='l') LaGrille->Cells[5][row]="L";
	else if(typeAmor=='d') LaGrille->Cells[5][row]="D";
	else if(typeAmor=='n') LaGrille->Cells[5][row]="N";

	if(CellVide(6,row) && LaGrille->Cells[5][row]!="N" )
	{
		correct=false;
		sprintf(buf,L_ErrPasDurAmor.c_str(),row);
		//sprintf(buf,"ligne n°:%2d Pas de durée d'amortissement",row);
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
				sprintf(buf,L_ErrPbDate.c_str(),row);
				//sprintf(buf,"ligne n°:%2d Problème de date",row);
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
			sprintf(buf,L_ErrPasNom.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		/*     110203
		 if(LaGrille->Cells[3][row].IsEmpty())  //EnStock
		 {
		 LaGrille->Cells[3][row]="N";
		 }
		 */
		if(LaGrille->Cells[3][row].IsEmpty()) //Valeur
		{
			correct=false;
			sprintf(buf,L_ErrPasVal.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de Valeur",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(LaGrille->Cells[4][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,L_ErrPasDate.c_str(),row);
			//sprintf(buf,"ligne n°:%2d Pas de date ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		else
		{
			rep=GrilleMoisAn(4,row,mois,an);
			if(rep==false)
			{
				correct=false;
				sprintf(buf,L_ErrPbDate.c_str(),row);
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
	bool correct=true;
	char buf[100];
	ErreurFrm->Edit->Clear();
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		if(LaGrille->Cells[2][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,L_ErrPasNom.c_str(),row);
			sprintf(buf,"ligne n°:%2d Pas de NOM ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	return correct;
}
//----------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::VerifGrillePolStock(void)
{
	int r;
	bool correct,rep;
	CL_PolStock *polStock;

	correct=true;
	ErreurFrm->Edit->Clear();
	for(r=1;r<LaGrille->RowCount;r++)
	{
		polStock=(CL_PolStock *)LaGrille->Objects[0][r];
		if(polStock==NULL) continue;

		rep=polStock->EstCorrect(LaGrille,r);
		if(rep==false) correct=false;
	}

	if(correct==false)
	ErreurFrm->Show();

	return correct;
}
/*
 L_ErrPasNom=          "ligne n°:%2d Pas de NOM ",row";
 L_ErrPasSurf=         "Pas de surface ";
 L_ErrPasDatePlant=    "ligne n°:%2d Pas de date de plantation ";
 L_ErrArrach=          "ligne n°:%2d Arrachage AVANT Plantation ";
 L_ErrDurTropL=        "ligne n°:%2d Durée trop longue ";
 L_ErrPasMontant=      "ligne n°:%2d Pas de Montant";
 L_ErrPasDur=          "ligne n°:%2d Pas de Durée";
 L_ErrPasDur2=         "ligne n°:%2d Pas de Durée 2";
 L_ErrPasTaux=         "ligne n°:%2d Pas de Taux;
 L_ErrPasTaux2=        "ligne n°:%2d Pas de Taux 2";
 L_ErrDurSup50=        "ligne n°:%2d Durée supérieure à 50 ans";
 L_ErrPasTypEmp=       "ligne n°:%2d Pas de Type CA par défaut";
 L_ErrPasDateReal=     "ligne n°:%2d Pas de date de réalisation ";
 L_ErrPasDateRembEmp=  "ligne n°:%2d Pas de date de remboursement ";
 L_ErrPasEPEmp=        "ligne n°:%2d Entreprise ou Privé E par defaut";
 L_ErrIntEmpCT=        "ligne n°:%2d Intérêts Non précomptés N par defaut";
 L_ErrPbDate=          "ligne n°:%2d Problème de date";
 L_ErrTypePlact=       "ligne n°:%2d Pas de Type AF A défaut";
 L_ErrPasDateTerme=    "ligne n°:%2d Pas de date de terme";
 L_LT=                 "Long Terme";
 L_CT=                 "Court Terme";
 L_ErrPasValNeuf=      "ligne n°:%2d Pas de Valeur à neuf";
 L_ErrPasDateAchat=    "ligne n°:%2d Pas de date d'achat";
 L_ErrPasTypAmor=      "ligne n°:%2d Pas de type d'amortissement";
 L_ErrPasDurAmor=      "ligne n°:%2d Pas de durée d'amortissement";
 L_ErrPasVal=          "ligne n°:%2d Pas de Valeur";
 L_ErrPasDate=         "ligne n°:%2d Pas de date ";

 */

