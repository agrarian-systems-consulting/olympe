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
#include "TypeEmpLT.h"
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
	// verifier le c0 de ControleCellfloat
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GAni:
		case GVariable: return ControleCellFloat(4,col,row,2);

		case GBestiaux: return ControleCellInvAni(col,row);
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
		case GFinSom: return ControleCellFloat(3,col,row,0);
		case GImmo: return ControleCellImmo(col,row);
		case GPetit: return ControleCellPetit(col,row);
		case GInvSom: return ControleCellFloat(3,col,row,0);
		case GCreance:
		case GDette: return ControleCellCreanceDette(col,row);
		case GStock: return ControleCellStockIni(col,row);
		case GPolStock: return ControleCellFloat(5,col,row,0);
		case GPasse: return true;
		default: ShowMessage("ControleCell Oubli");
		return true;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellFloat(int col0,int col,int row,int digits)
{
	if(col<col0)return true;

	ReAffFloat(col,row,digits);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellVerger(int col,int row)
{
	int anPlant,anArr;
	AnsiString s;
	if(col==5 )
	{
		s=LaGrille->Cells[5][row];
		if(s.Length()>4)
		{
			ShowMessage(L_ErrDateAn);
			//ShowMessage("Erreur sur la date Seulement l'année !");
			return false;
		}
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
		s=LaGrille->Cells[6][row];
		if(s.Length()>4)
		{
			ShowMessage(L_ErrDateAn);
			//ShowMessage("Erreur sur la date Seulement l'année !");
			return false;
		}
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
	return true; // A SUPPRIMER
}
/*
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
 MvtAniFrm->MvtInitial();
 break;
 //        default:
 //            ShowMessage("Problème dans ControleCellInvAni(");
 }
 return true;
 }
 */
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
	int duree;

	LabelModifie->Visible=true;
	empLT=(CL_EmpLT*)LaGrille->Objects[0][row];
	if(empLT!=NULL)
	{
		if(empLT->Flag!='N')
		empLT->Flag='M';
	}
	else
	{
		empLT=new CL_EmpLT();
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
		duree=GrilleInt(col,row);
		if(duree>50)
		{
			ShowMessage(L_ErrEmpDur); //201204
			//ShowMessage("Durée Emprunt >50 !!");  //201204
			LaGrille->Cells[col][row]=50;
			return false;
		}

		ReAffInt(col,row);
		return true;
		case 5: //taux1
		case 7://taux2
		ReAffFloat(col,row,2);
		return true;
		case 8:
		TypeEmpLTFrm->Show();
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
	CL_EmpCT *empCT;
	bool rep;
	LabelModifie->Visible=true;
	empCT=(CL_EmpCT*)LaGrille->Objects[0][row];
	if(empCT!=NULL)
	{
		if(empCT->Flag!='N')
		empCT->Flag='M';
	}
	else
	{
		empCT=new CL_EmpCT();
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
		rep=GrilleCarPermis(col,row,type,"NPO");//PbTrad!!
		if(type=='O') type=CarPreCompte;
		return rep;//280805
		case 6://réalisation
		case 7://remboursement
		return GrilleMoisAn(col,row,mois,an);
		case 8://Entreprise ou Privé
		return GrilleCarPermis(col,row,type,"EP");//PbTrad!!
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellSub(int col,int row)
{
	int mois, an;
	CL_Sub *sub;
	int duree;

	LabelModifie->Visible=true;
	sub=(CL_Sub*)LaGrille->Objects[0][row];
	if(sub!=NULL)
	{
		if(sub->Flag!='N')
		sub->Flag='M';
	}
	else
	{
		sub=new CL_Sub();
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
		duree=GrilleInt(col,row);
		if(duree>50)
		{
			ShowMessage(L_ErrSub); //201204
			//ShowMessage("Durée Subvention >50 !!");  //201204
			LaGrille->Cells[col][row]=50;
			return false;
		}

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
		plact=new CL_Plact();
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
		return GrilleCarPermis(col,row,type,"FA");//PbTrad
		case 6://réalisation
		case 7://remboursement
		return GrilleMoisAn(col,row,mois,an);
		case 8://Entreprise ou Privé
		return GrilleCarPermis(col,row,type,"EP");//PbTrad
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellOccc(int col,int row)
{
	CL_Occc *occc;
	float montant,pcent,taux,frais;
	if(row==0) return true; //150105
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
		occc=new CL_Occc();
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
	int duree;
	char type;
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
		immo=new CL_Immo();
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
		return GrilleCarPermis(col,row,type,"DLN");//PbTrad
		case 6://Durée d'amortissement
		duree=GrilleInt(col,row);
		if(duree>50)
		{
			ShowMessage(L_ErrAm); //201204
			//ShowMessage("Durée Amortissement >50 !!");  //201204
			LaGrille->Cells[col][row]=50;
			return false;
		}
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
		petit=new CL_Petit();
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
	int mois,an;
	CL_EnCours *enCours; //A voir
	LabelModifie->Visible=true;
	enCours=(CL_EnCours*)LaGrille->Objects[0][row];
	if(enCours!=NULL)
	{
		if(enCours->Flag!='N')
		enCours->Flag='M';
	}
	else
	{
		enCours=new CL_EnCours();
		enCours->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)enCours;
		LaGrille->Cells[0][row]=row;
	}
	AjouterRow();
	if(col==3)
	ReAffFloat(col,row,0);
	else if(col==4)
	GrilleMoisAn(4,row,mois,an);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::ControleCellStockIni(int col,int row)
{
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
		stock=new CL_StockIni();
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
/*
 L_ErrDateAn=         "Erreur sur la date Seulement l'année !";
 L_ErrEmpDur=         "Durée Emprunt >50 !!";
 L_ErrSub=            "Durée Subvention >50 !!";
 L_ErrAm=             "Durée Amortissement >50 !!";

 AnsiString     L_ErrDateAn;
 AnsiString     L_ErrEmpDur;
 AnsiString     L_ErrSub;
 AnsiString     L_ErrAm;
 */
