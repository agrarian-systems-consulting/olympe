//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Treso.h"
#include "TVChoixRepart.h"

#include "FenRepart.h"
#include "TresoRes.h"
#include "TresoEnum.h"
#include "TresoGraph.h"
#include "CL_Trad.h"

#include "TresoRepart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
extern CL_ES *ES;
extern CL_Trad *T;

TTresoRepartFrm *TresoRepartFrm;
/*
 on vient de Treso
 Treso a mis Origine à 0
 */
//---------------------------------------------------------------------------
__fastcall TTresoRepartFrm::TTresoRepartFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::FormActivate(TObject *Sender)
{
	int i;
	bool rep;
	if(Origine!=0) return;
	LabelModifie->Visible=false;
	TVChoixRepartFrm->AFaire=AnsiString("Choisir");
	Origine=1;
	Top=TresoFrm->Top+50;
	Left=TresoFrm->Left;
	SG->ColWidths[0]=128;
	// aff annéees
	for(i=0;i<10;i++)
	SG->Cells[i+1][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i);

//    BtBnCalculQuant->Visible=false;
	switch(TresoFrm->Nature)
	{
		case PRODUIT:
		V_QuanVal=AgriEnCours->Resultat->V_Produit;
		V_Categorie=V_CatProduit;
		Caption="Produits";
//            BtBnCalculQuant->Visible=true;
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case CHARGE:
		V_QuanVal=AgriEnCours->Resultat->V_Charge;
		V_Categorie=V_CatCharge;
		Caption="Charges";
//            BtBnCalculQuant->Visible=true;
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case VENTE://111206
		case ACHAT://180512
		V_QuanVal=AgriEnCours->Resultat->V_VenteAni;
		//V_Categorie=V_CatCharge;
		if(CalculEn==VALEUR)
		Caption="Ventes Animaux VALEUR";
		else
		Caption="Charges QUANTITE";
		rep=AffRepartitionsBestiaux();
		//rep=AffRepartitions();
		if(rep==false) return;
		break;
//pense achats
		case CHSTRUCT:
		V_QuanVal=AgriEnCours->Resultat->V_ChStruct;
		V_Categorie=V_CatChStruct;
		Caption="Charges de Structure en valeur";
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case RECDIV:
//            V_QuanVal=AgriEnCours->Resultat->V_RecDiv;
		V_QuanVal=AgriEnCours->Resultat->V_RecDiv;//200512
		V_Categorie=V_CatRecDiv;
		Caption="Recettes Diverses en valeur";
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case DEPDIV:
		V_QuanVal=AgriEnCours->Resultat->V_DepDiv;
		V_Categorie=V_CatDepDiv;
		Caption="Dépenses Diverses en valeur";
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case RECFAM:
		V_QuanVal=AgriEnCours->Resultat->V_RecFam;
		V_Categorie=V_CatRecFam;
		Caption="Recettes Familiales en valeur";
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case DEPFAM:
		V_QuanVal=AgriEnCours->Resultat->V_DepFam;
		V_Categorie=V_CatDepFam;
		Caption="Dépenses Familiales en valeur";
		rep=AffRepartitions();
		if(rep==false) return;
		break;

		case EXTER:
		Caption="Externalités en quantite";
		CalculEn=QUANTITE;
		rep=AffRepartitionsExter();
		if(rep==false) return;
		break;
		/*
		 case IMMO:
		 Caption="Immobilisations";
		 BtBnCalculClick(this);
		 //ShowMessage("En Cours!!!");
		 break;
		 */
		case PETITMAT:
		Caption="Petit Matériel";
		CalculEn=VALEUR;
		rep=AffRepartitionsPetitMat();
		if(rep==false) return;
		break;

		case FINANCE:
		Caption="Financement";
		BtBnCalculValClick(this); //130107
		ShowMessage("En Cours!!!");
		break;

		default:
		ShowMessage("TresoRepart/n Oubli Nature ???");
		return;
	}
//	rep=AffRepartitions();       //150107  180512
//    if(rep==false) return;

	SG->Col=1;
	SG->Row=1;
}
//---------------------------------------------------------------------------
bool __fastcall TTresoRepartFrm::AffRepartitions(void)
{
	int i,j,r,c;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	CL_Repart *repart;
	SG->RowCount=1+V_QuanVal->Nbelt;
	if(V_QuanVal->Nbelt==0)
	{
		ShowMessage("Aucun élément");
		return false;
	}

	//nettoie la grille
	for(c=0;c<SG->ColCount;c++)
	{
		for(r=1;r<SG->RowCount;r++)
		{
			SG->Cells[c][r]="";
			SG->Objects[c][r]=NULL; //170610
		}
	}

	r=1;
	for(i=0;i<V_Categorie->Nbelt;i++)
	{
		cat=V_Categorie->Vecteur[i];
		for(j=0;j<V_QuanVal->Nbelt;j++)
		{
			quanVal=V_QuanVal->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			SG->Cells[0][r]=quanVal->Item->Nom;
			SG->Objects[0][r]=(TObject*)quanVal;
//CalculEn=VALEUR;    //200810
			for(c=1;c<N_X+1;c++)
			{
				if(CalculEn==VALEUR)
				repart=quanVal->ItemRepart->LesRepartV[c-1];
				else
				repart=quanVal->ItemRepart->LesRepartQ[c-1];

				SG->Objects[c][r]=(TObject*)repart;
				if(repart)
				SG->Cells[c][r] =repart->Nom;
			}
			r++;
		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TTresoRepartFrm::AffRepartitionsBestiaux(void)
{
	int i,j,r,c;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	CL_Repart *repart;
	SG->RowCount=1+V_QuanVal->Nbelt;
	if(V_QuanVal->Nbelt==0)
	{
		ShowMessage("Aucun élément");
		return false;
	}
	//nettoie la grille
	for(c=0;c<SG->ColCount;c++)
	for(r=1;r<SG->RowCount;r++)
	SG->Cells[c][r]="";
	r=1;
//    for(i=0;i<V_Categorie->Nbelt;i++)
//    {
//    	cat=V_Categorie->Vecteur[i];
	for(j=0;j<V_QuanVal->Nbelt;j++)
	{
		quanVal=V_QuanVal->Vecteur[j];
//            if(quanVal->Item->Categorie!=cat) continue;

		SG->Cells[0][r]=quanVal->Item->Nom;
		SG->Objects[0][r]=(TObject*)quanVal;
		for(c=1;c<N_X+1;c++)
		{
			if(CalculEn==VALEUR)
			repart=quanVal->ItemRepart->LesRepartV[c-1];
			else
			repart=quanVal->ItemRepart->LesRepartQ[c-1];

			SG->Objects[c][r]=(TObject*)repart;
			if(repart)
			SG->Cells[c][r] =repart->Nom;
		}
		r++;
	}
//	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TTresoRepartFrm::AffRepartitionsExter(void)
{
	int i,j,r,c;
	CL_Categorie *cat;
	CL_QuanVal *quanVal;
	CL_Repart *repart;
	int nbelt;
	nbelt=AgriEnCours->Resultat->V_ExtNeg->Nbelt
	+ AgriEnCours->Resultat->V_ExtPos->Nbelt;

	if(nbelt==0)
	{
		ShowMessage("Aucun élément");
		return false;
	}
	SG->RowCount=1+nbelt;
	//nettoie la grille
	for(c=0;c<SG->ColCount;c++)
	for(r=1;r<SG->RowCount;r++)
	SG->Cells[c][r]="";
	r=1;
	for(i=0;i<V_CatExternalite->Nbelt;i++)
	{
		if(i==0) V_QuanVal=AgriEnCours->Resultat->V_ExtNeg;
		else if(i==1) V_QuanVal=AgriEnCours->Resultat->V_ExtPos;
		cat=V_CatExternalite->Vecteur[i];
		for(j=0;j<V_QuanVal->Nbelt;j++)
		{
			quanVal=V_QuanVal->Vecteur[j];
			if(quanVal->Item->Categorie!=cat) continue;

			SG->Cells[0][r]=quanVal->Item->Nom;
			SG->Objects[0][r]=(TObject*)quanVal;
			for(c=1;c<N_X+1;c++)
			{
				repart=quanVal->ItemRepart->LesRepartQ[c-1];

				SG->Objects[c][r]=(TObject*)repart;
				if(repart)
				SG->Cells[c][r] =repart->Nom;
			}
			r++;
		}
	}
	SG->RowCount=r;
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TTresoRepartFrm::AffRepartitionsPetitMat(void)
{
	int c ,r,n;
	CL_Vecteur<CL_Petit> *vecteur;
//CL_Petit *petit;
	CL_Repart *repart;
	CL_QuanVal *quanVal=AgriEnCours->QuanValPetit;
	//QuanValPetit est créé à la lecture

	//nettoie la grille
	for(c=0;c<SG->ColCount;c++)
	for(r=1;r<SG->RowCount;r++)
	SG->Cells[c][r]="";

	SG->RowCount=2;
	SG->Cells[0][1]="Petit matériel";
	vecteur=AgriEnCours->V_Petit;
	if(vecteur->Nbelt==0)
	{
		ShowMessage("Aucun élément");
		return false;
	}

	// voir lecture de petit
	//Tresorepart travaille sur des quanVal
	//petit doit s'y raccrocher
	//  création du quanVal

	//affichage
	r=1;
	SG->RowCount=2;
	SG->Objects[0][r]=(TObject*)quanVal;
//    SG->Cells[1][r]=quanVal->Item->Nom;  //190512
	for(c=1,n=0;c<N_X+1;c++,n++)
	{
		repart=quanVal->ItemRepart->LesRepartV[c-1];
		//petit=AgriEnCours->V_Petit->Vecteur[n];
		SG->Objects[c][r]=(TObject*)repart;
		if(repart)
		SG->Cells[c][r] =repart->Nom;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BoutFermerClick(TObject *Sender)
{
	TresoFrm->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::SGDblClick(TObject *Sender)
{
	int n;
	int c=SG->Col;
	int r=SG->Row;
	AnsiString as;
	if(c==0) return;
	n=SG->Col-1;
	if(r==0) return; //180512
	TrouveLesRepart(r);

	FenRepartFrm->SG=SG;
	FenRepartFrm->EdAn->Text=SG->Cells[c][0];
	if(LesRepart[n])
	{
		FenRepartFrm->Repart=LesRepart[n];
		FenRepartFrm->Show();
	}
	else
	TVChoixRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::TrouveLesRepart(int r)
{
	CL_QuanVal *quanVal;
	if(r==0) return; //180512
	quanVal=(CL_QuanVal*)SG->Objects[0][r];
	if(quanVal==NULL) return;

	if(CalculEn==VALEUR)
	{
		LesRepart = quanVal->ItemRepart->LesRepartV;
		LesNoRepart= quanVal->ItemRepart->LesNoRepartV;
	}
	else
	{
		LesRepart=quanVal->ItemRepart->LesRepartQ;
		LesNoRepart= quanVal->ItemRepart->LesNoRepartQ;
	}
}
//---------------------------------------------------------------------------
//      Appel TresoRes qui fait calcul et affichage
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BtBnCalculValClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=DETAIL;
	if(RGRepart->ItemIndex==0) CalculEn=VALEUR;
	else CalculEn=QUANTITE;
	TresoResFrm->Nature=TresoFrm->Nature;

	TresoResFrm->Show();
}
/* a sup
 //---------------------------------------------------------------------------
 void __fastcall TTresoRepartFrm::BtBnCalculQuantClick(TObject *Sender)
 {
 TresoResFrm->Origine=0;
 TresoResFrm->TypeSortie=DETAIL;
 TresoRepartFrm->CalculEn=QUANTITE;
 TresoResFrm->Nature=TresoFrm->Nature;
 TresoResFrm->Show();
 }
 //---------------------------------------------------------------------------
 */
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BtRepBasClick(TObject *Sender)
{
	int n,r;
	int c=SG->Col;
	int r0=SG->Row;
	CL_Repart *repart;

	TrouveLesRepart(r0);
	n=c-1;
	repart=LesRepart[n];
	if(repart==NULL)
	{
		ShowMessage(" Pas de Répartition");
		return;
	}

	for(r=r0;r<SG->RowCount;r++)
	{
		if(SG->Objects[c][r] && ChBRepTout->Checked==false) continue;
		TrouveLesRepart(r);
		LesRepart[n]=repart;
		LesNoRepart[n]=repart->No;

		SG->Cells[c][r]=repart->Nom;
		SG->Objects[c][r]=(TObject*)repart;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BtReportDroitClick(TObject *Sender)
{
	int c,n;
	int c0=SG->Col;
	int r=SG->Row;
	CL_QuanVal *quanVal;
	CL_Repart *repart;

	n=SG->Col;
	r=SG->Row;
	quanVal=(CL_QuanVal*)SG->Objects[0][r];

	repart=(CL_Repart*)SG->Objects[n][r]; //LesRepart[n];

	if(repart==NULL)
	{
		ShowMessage(" Rien à reporter");
		return;
	}
	for(c=c0;c<SG->ColCount;c++)
	{
		n=c-1;
		if(SG->Cells[c][r].Length()>1 && ChBRepTout->Checked==false) continue;

		if(TresoRepartFrm->CalculEn==VALEUR)
		{
			quanVal->ItemRepart->LesRepartV[n]=repart;
			quanVal->ItemRepart->LesNoRepartV[n]=repart->No;
		}
		else
		{
			quanVal->ItemRepart->LesRepartQ[n]=repart;
			quanVal->ItemRepart->LesNoRepartQ[n]=repart->No;
		}

		SG->Objects[c][r]=(TObject*)repart;
		SG->Cells[c][r]=repart->Nom;
	}

}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BtRepToutDroitClick(TObject *Sender)
{
	int c,c0,r,r0;
	CL_Repart *repart;
	c0=SG->Col;
	r0=SG->Row;
	repart=(CL_Repart*)SG->Objects[c0][r0]; //191205
	if(repart==NULL)
	{
		ShowMessage(" Rien à reporter");
		return;
	}

//	BtReportDroitClick(this);

	for(r=r0;r<SG->RowCount;r++)
	{
		SG->Row=r;
		SG->Objects[c0][r]=(TObject*)repart;
		for(c=c0;c<SG->ColCount;c++)
		{
			SG->Col=c;
			BtReportDroitClick(this);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BtBnRepartClick(TObject *Sender)//valeur
{
	TVChoixRepartFrm->AFaire=AnsiString("Choisir");
	TVChoixRepartFrm->Show();
}
//151211
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::BtBnRepartQuantClick(TObject *Sender)
{
	TVChoixRepartFrm->AFaire=AnsiString("Choisir");
	TVChoixRepartFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TTresoRepartFrm::RGRepartClick(TObject *Sender)
{
//161211
	if(RGRepart->ItemIndex==0)CalculEn=VALEUR;
	else CalculEn=QUANTITE;
	AffRepartitions();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TTresoRepartFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(LabelModifie->Visible==false)return;
	ES->ecrireFichier();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTresoRepartFrm::IniCaption(void) {
	LabelModifie->Caption = T->LC_LabelModifie_A;
//    BtBnRepart->Caption=T->LC_Definition;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtBnCalculVal->Caption = T->LC_BtBnResultat;
	//BtBnCalculQuant->Caption=T->LC_BtBnResultat;
	TresoRepartFrm->Caption = LC_TresoRepartFrm;
}
//--------------------------------------------
void TTresoRepartFrm::TexteCaption(void) {
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_Definition = T->TrouveCaption("CL_Trad", "LC_Definition");
	LC_ChBRepTout = T->TrouveCaption("CL_Trad", "LC_ChBRepTout");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_TresoRepartFrm = T->TrouveCaption("TresoRepart", "LC_TresoRepartFrm");

	IniCaption();

}
//--------------------------------------------

void __fastcall TTresoRepartFrm::BtBnVideToutClick(TObject *Sender)
{
	int rep;
	int r,c;
	CL_QuanVal* quanVal;
//	rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO) return;
	for (r=1;r<SG->RowCount;r++)
	{
		quanVal=(CL_QuanVal*)SG->Objects[0][r];
		if(quanVal==NULL) continue;

		for(c=1;c<N_X+1;c++)
		{
			quanVal->ItemRepart->LesRepartQ[c-1]=NULL;
			quanVal->ItemRepart->LesRepartV[c-1]=NULL;
			SG->Objects[c][r]=NULL;
			SG->Cells[c][r] ="";
		}
	}
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TTresoRepartFrm::BtBnSupClick(TObject *Sender)
{
	int rep;
	int r,c;
	CL_QuanVal* quanVal;
	r=SG->Row;
	c=SG->Col;
//	rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO) return;

	quanVal=(CL_QuanVal*)SG->Objects[0][r];
	if(quanVal==NULL) return;

	quanVal->ItemRepart->LesRepartQ[c-1]=NULL;
	quanVal->ItemRepart->LesRepartV[c-1]=NULL;
	SG->Objects[c][r]=NULL;
	SG->Cells[c][r] ="";
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

