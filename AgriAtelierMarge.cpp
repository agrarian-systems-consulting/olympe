//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "QRGrille00.h"
#include "QuelExcelCSV.h"
#include "Tableur.h"
#include "Forme0.h"

#include "CL_Trad.h"
#include "Resultat.h"
#include "Aide.h"

#include "AgriAtelierMarge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAgriAtelierMargeFrm *AgriAtelierMargeFrm;
extern CL_Excel *EX;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TAgriAtelierMargeFrm::TAgriAtelierMargeFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAgriAtelierMargeFrm::FormActivate(TObject *Sender)
{
	int r,c;
	if(Arret==true) return;
	Grille->ColWidths[0]=128;
	for(int i=0;i<10;i++)
	Grille->Cells[i+1][0]="  "+AnsiString(Agri->DefSim->An_0+i);

	for(r=1;r<Grille->RowCount;r++)
	for(c=0;c<Grille->ColCount;c++)
	Grille->Cells[c][r]="";

	Calcul();
	AffDetail();
}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall TAgriAtelierMargeFrm::Calcul(void)
{
	int i,n;
	CL_QuanVal *quanVal;
	CL_Item *item;
	float *pcent;
	static float pcent0[N_X];
	static debut=true;
	if(debut==true)
	{
		for(n=0;n<N_X;n++) pcent0[n]=1.;
		debut=false;
	}
	memset(TotProd,0,sizeof(TotProd));
	memset(TotCharge,0,sizeof(TotProd));
	if(V_Produit->Nbelt)
	{
		for(i=0;i<V_Produit->Nbelt;i++)
		{
			quanVal=V_Produit->Vecteur[i];
			item=quanVal->Item;
			pcent=Forme0Frm->trouveDelta(item,Agri->DefSim->TPProd);
			if(pcent==NULL) pcent=pcent0;
			for(n=0;n<N_X;n++)
			{
				quanVal->Val[n]=quanVal->Qte[n]*quanVal->Item->Prix*pcent[n]; // pb alea unite !!
				TotProd[n]+=quanVal->Val[n];
			}
		}
	}
	if(V_Charge->Nbelt)
	{
		for(i=0;i<V_Charge->Nbelt;i++)
		{
			quanVal=V_Charge->Vecteur[i];
			item=quanVal->Item;
			pcent=Forme0Frm->trouveDelta(item,Agri->DefSim->TPCharge);
			if(pcent==NULL) pcent=pcent0;
			for(n=0;n<N_X;n++)
			{
				quanVal->Val[n]=quanVal->Qte[n]*quanVal->Item->Prix*pcent[n]; // 110810pb alea unite !!
				TotCharge[n]+=quanVal->Val[n];
			}
		}
	}
	for(n=0;n<N_X;n++)
	Marge[n]=TotProd[n]-TotCharge[n];
}
//------------------------------------------------------------------------------
void __fastcall TAgriAtelierMargeFrm::AffDetail(void)
{
	int i,j,n,r;
	int digits=ResultatFrm->Digits;
	float totCat[N_X];
	CL_QuanVal *quanVal;
	CL_Categorie *categorie;
	bool trouve;
	Detail=true;

	r=1;
	Grille->RowCount=1+V_Produit->Nbelt+2+V_CatCharge->Nbelt+2+2;
	if(V_Produit->Nbelt)
	{
		Grille->Cells[0][r++]=T->L_Produit; //"Produits";
		for(i=0;i<V_Produit->Nbelt;i++)
		{
			quanVal=V_Produit->Vecteur[i];
			Grille->Cells[0][r]=quanVal->Item->Nom;
			for(n=0;n<N_X;n++)
			Grille->Cells[n+1][r]=FloatToStrF(quanVal->Val[n],ffNumber,7,digits);
			r++;
		}
		Grille->Cells[0][r]=L_TotProd; //"Total Produits";
		for(n=0;n<N_X;n++)
		Grille->Cells[n+1][r]=FloatToStrF(TotProd[n],ffNumber,7,digits);
		r++;
	}
	//310805                    //ventes d'animaux
	for(j=0;j<V_Charge->Nbelt;j++)
	{
		quanVal=V_Charge->Vecteur[j];
		quanVal->Flag='N';
	}
	if(V_Charge->Nbelt)
	{
		Grille->Cells[0][r++]=T->L_Charge; //"Charges";
		for(i=0;i<V_CatCharge->Nbelt;i++)
		{
			memset(totCat,0,sizeof(totCat));
			trouve=false;
			categorie=V_CatCharge->Vecteur[i];
			for(j=0;j<V_Charge->Nbelt;j++)
			{
				quanVal=V_Charge->Vecteur[j];
				if(quanVal->Item->Categorie==categorie)
				{
					trouve=true;
					quanVal->Flag='O';
					for(n=0;n<N_X;n++)
					totCat[n]+=quanVal->Val[n];
				}
			}
			if(trouve==true)
			{
				Grille->Cells[0][r]=categorie->Nom;
				for(n=0;n<N_X;n++)
				Grille->Cells[n+1][r]=FloatToStrF(totCat[n],ffNumber,7,digits);
				r++;
			}
		}
		//ventes animaux
		for(j=0;j<V_Charge->Nbelt;j++)
		{
			quanVal=V_Charge->Vecteur[j];
			if(quanVal->Flag=='N')
			{
				Grille->Cells[0][r]=quanVal->Item->Nom;
				for(n=0;n<N_X;n++)
				Grille->Cells[n+1][r]=FloatToStrF(quanVal->Val[n],ffNumber,7,digits);
				r++;
			}
		}
		Grille->Cells[0][r]=L_TotCharge; //"Total Charges";
		for(n=0;n<N_X;n++)
		Grille->Cells[n+1][r]=FloatToStrF(TotCharge[n],ffNumber,7,digits);
		r++;
	}
	Grille->Cells[0][r++]="";
	Grille->Cells[0][r]=T->L_Marge; //"Marge";
	for(n=0;n<N_X;n++)
	Grille->Cells[n+1][r]=FloatToStrF(Marge[n],ffNumber,7,digits);
}
//------------------------------------------------------------------------------
void __fastcall TAgriAtelierMargeFrm::AffSynthese(void)
{
	int n,r;
	int digits=0;
	Detail=false;
	r=1;
	Grille->RowCount=1+2+2+2;
	if(V_Produit->Nbelt)
	{
		Grille->Cells[0][r]=T->L_Produit;
		//Grille->Cells[0][r]="Produits";
		for(n=0;n<N_X;n++)Grille->Cells[n+1][r]="";
		r++;
		Grille->Cells[0][r]=L_TotProd;
		//Grille->Cells[0][r]="Total Produits";
		for(n=0;n<N_X;n++)
		Grille->Cells[n+1][r]=FloatToStrF(TotProd[n],ffNumber,7,digits);
		r++;
	}

	if(V_Charge->Nbelt)
	{
		Grille->Cells[0][r]=T->L_Charge;
		//Grille->Cells[0][r]="Charges";
		for(n=0;n<N_X;n++)Grille->Cells[n+1][r]="";
		r++;

		Grille->Cells[0][r]=L_TotCharge;
		//Grille->Cells[0][r]="Total Charges";
		for(n=0;n<N_X;n++)
		Grille->Cells[n+1][r]=FloatToStrF(TotCharge[n],ffNumber,7,digits);
		r++;
	}

	Grille->Cells[0][r++]="";
	Grille->Cells[0][r]=T->L_Marge;
	//Grille->Cells[0][r]="Marge";
	for(n=0;n<N_X;n++)
	Grille->Cells[n+1][r]=FloatToStrF(Marge[n],ffNumber,7,digits);
}
//------------------------------------------------------------------------------

void __fastcall TAgriAtelierMargeFrm::BtSyntDetailClick(TObject *Sender)
{
	int r,c;
	for(r=1;r<Grille->RowCount;r++)
	for(c=0;c<Grille->ColCount;c++)
	Grille->Cells[c][r]="";

	if(Detail==true)
	{
		BtSyntDetail->Caption=L_Detail;
		//BtSyntDetail->Caption="Détail";
		AffSynthese();
	}
	else
	{
		BtSyntDetail->Caption=L_Synthese;
		//BtSyntDetail->Caption="Synthèse";
		AffDetail();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAgriAtelierMargeFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{

	V_Produit->purge();
	V_Charge->purge();
	V_Exter->purge();

	delete V_Produit;
	delete V_Charge;
	delete V_Exter;
	V_Produit=NULL;
	V_Charge=NULL;
	V_Exter=NULL;

}
//---------------------------------------------------------------------------

void __fastcall TAgriAtelierMargeFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDYES) Application->Terminate();

	else return;
}
//---------------------------------------------------------------------------

void __fastcall TAgriAtelierMargeFrm::BtBnImpClick(TObject *Sender)
{

	QRGrille00Frm->LaGrille=Grille;
	QRGrille00Frm->TitreEtat->Caption=Caption;
	QRGrille00Frm->TypeCol="TNNNNNNNNNNNNN";
	QRGrille00Frm->Initialise();
	QRGrille00Frm->QR->Preview();

}
//---------------------------------------------------------------------------

void __fastcall TAgriAtelierMargeFrm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	EX->EcritGrilleFichier(Grille,T->L_Marge);
	//EX->EcritGrilleFichier(Grille,"Marge");
	EX->FermerFichier();
}
//---------------------------------------------------------------------------
void TAgriAtelierMargeFrm::TexteChaine(void) {
	L_TotProd = T->TrouveTexte("AgriAtelierMargeFrm", "L_TotProd");
	L_TotCharge = T->TrouveTexte("AgriAtelierMargeFrm", "L_TotCharge");
	L_Detail = T->TrouveTexte("AgriAtelierMargeFrm", "L_Detail");
	L_Synthese = T->TrouveTexte("AgriAtelierMargeFrm", "L_Synthese");
}
//---------------------------------------------------------------------------
void TAgriAtelierMargeFrm::TexteCaption(void) {
	LC_LabNomAtelier = T->TrouveTexte("AgriAtelierMarge", "LC_LabNomAtelier");
	LC_AgriAtelierMargeFrm = T->TrouveTexte("AgriAtelierMarge",
			"LC_AgriAtelierMargeFrm");
	LC_BtBnQuitter = T->TrouveTexte("CL_Trad", "LC_BtBnQuitter");
	LC_BtSyntDetail = T->TrouveTexte("CL_Trad", "LC_BtSyntDetail");

	IniCaption();
}
//--------------------------------------------
void TAgriAtelierMargeFrm::IniCaption(void) {
	LabNomAtelier->Caption = LC_LabNomAtelier;
	AgriAtelierMargeFrm->Caption = LC_AgriAtelierMargeFrm;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	BtSyntDetail->Caption = T->LC_BtSyntDetail;
}
//--------------------------------------------

bool __fastcall TAgriAtelierMargeFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

