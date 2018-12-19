//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Ensemble.h"

//#include "ChoixCritere.h"
#include "LBToutEnsemble.h"
#include "AgriClasst.h"
#include "DefProcedure.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "TriAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTriAgriFrm *TriAgriFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTriAgriFrm::TTriAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::FormCreate(TObject *Sender)
{
	EstInitialise=false;
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::FormActivate(TObject *Sender)
{
	int i;
	CL_Item *critere;
	if(EstInitialise==true) return;

	for(i=0;i<V_TypeZone->Nbelt;i++)
	{
		critere=V_TypeZone->Vecteur[i];
		critere->Flag='N';
	}
	IniEcran();
	EstInitialise=true;
	BtBnCritereClick(this); //280405
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::IniEcran(void)
{
	int i,n;
	int p; //p comme panel
	TPanel *pan;
//TListBox      *lB;
	TLabel *lab;
	TCheckListBox *chLB;
//TCheckBox     *chB;
	CL_Categorie *categorie;
	CL_Item *critere;
	//pour me faciliter la vie je mets tous les Panel de saisie dant LstPan
	LstPan=new TList;
	LstPan->Clear();

	LstPan->Add(Pan1);
	LstPan->Add(Pan2);
	LstPan->Add(Pan3);
	LstPan->Add(Pan4);
	LstPan->Add(Pan5);

	LstLabel=new TList;
	LstLabel->Clear();

	LstLabel->Add(Lab1);
	LstLabel->Add(Lab2);
	LstLabel->Add(Lab3);
	LstLabel->Add(Lab4);
	LstLabel->Add(Lab5);

	LstChLB=new TList;
	LstChLB->Clear();

	LstChLB->Add(ChLB1);
	LstChLB->Add(ChLB2);
	LstChLB->Add(ChLB3);
	LstChLB->Add(ChLB4);
	LstChLB->Add(ChLB5);
	/*
	 LstChB=new TList;
	 LstChB->Clear();

	 LstChB->Add(ChB1);
	 LstChB->Add(ChB2);
	 LstChB->Add(ChB3);
	 LstChB->Add(ChB4);
	 LstChB->Add(ChB5);

	 //Tous les CheckBox sont cochés
	 for(i=0;i<LstChB->Count;i++)
	 {
	 chB=(TCheckBox*)LstChB->Items[i];
	 chB->Checked=true;
	 }
	 */
	// je les rends Non Visible
	for(p=0;p<LstPan->Count;p++)
	{
		pan=(TPanel*)LstPan->Items[p];
		pan->Visible=false;
	}

//    lB=ChoixCritereFrm->LBCritere;  //critere Retenu
	//chLB=AgriClasstFrm->ChLBCatTypeZone;
	//  !!!!!!!!!!!!!!!!

	//par categorie
	// afficher les criteres de la categorie
	p=0;
	for(n=0;n<AgriClasstFrm->ChLBCatTypeZone->Items->Count;n++)
	{
		if(AgriClasstFrm->ChLBCatTypeZone->Checked[n]==false) continue;

		//categorie=(CL_Categorie*)lB->Items->Objects[n];
		categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[n];
		// label
		lab=(TLabel*)LstLabel->Items[p];
		lab->Caption=categorie->Nom;

		//visible
		pan=(TPanel*)LstPan->Items[p];
		pan->Visible=true;

		//CheckListBox
		//ajouter tous les critères de la catégorie
		chLB=(TCheckListBox *)LstChLB->Items[p];
		chLB->Clear();
		for(i=0;i<V_TypeZone->Nbelt;i++)
		{
			critere=V_TypeZone->Vecteur[i];
			if(critere->Categorie!=categorie)continue;
			chLB->Items->AddObject(critere->Nom,(TObject*)critere);

		}
		for(i=0;i<chLB->Items->Count;i++)
		{
			critere=(CL_Item*)chLB->Items->Objects[i];
			if(critere->Flag=='O')
			chLB->Checked[i]=true;
			else
			chLB->Checked[i]=false;
		}
		p++;
	}
}

//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::BtBnAucunClick(TObject *Sender)
{
	int n;
	TButton *bouton;
	TCheckListBox *chLB;
	CL_Item *critere;
	bouton=(TButton*)Sender;
	if(bouton->Name==BtBnAucun1->Name) chLB=ChLB1;
	if(bouton->Name==BtBnAucun2->Name) chLB=ChLB2;
	if(bouton->Name==BtBnAucun3->Name) chLB=ChLB3;
	if(bouton->Name==BtBnAucun4->Name) chLB=ChLB4;
	if(bouton->Name==BtBnAucun5->Name) chLB=ChLB5;

	for(n=0;n<chLB->Items->Count;n++)
	{
		chLB->Checked[n]=false;
		critere=(CL_Item*)chLB->Items->Objects[n];
		critere->Flag='N';
	}
}
//---------------------------------------------------------------------------

void __fastcall TTriAgriFrm::BtBnTousClick(TObject *Sender)
{
	int n;
	TButton *bouton;
	TCheckListBox *chLB;
	CL_Item *critere;

	bouton=(TButton*)Sender;
	if(bouton->Name==BtBnTous1->Name) chLB=ChLB1;
	if(bouton->Name==BtBnTous2->Name) chLB=ChLB2;
	if(bouton->Name==BtBnTous3->Name) chLB=ChLB3;
	if(bouton->Name==BtBnTous4->Name) chLB=ChLB4;
	if(bouton->Name==BtBnTous5->Name) chLB=ChLB5;

	for(n=0;n< chLB->Items->Count;n++)
	{
		chLB->Checked[n]=true;
		critere=(CL_Item*)chLB->Items->Objects[n];
		critere->Flag='O';
	}
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::ChLBClickCheck(TObject *Sender)
{
	int n;
	TCheckListBox *chLB;
	CL_Item *critere;
	chLB=(TCheckListBox*)Sender;
	/*
	 if(bouton->Name==BtBnTous1->Name) chLB=ChLB1;
	 if(bouton->Name==BtBnTous2->Name) chLB=ChLB2;
	 if(bouton->Name==BtBnTous3->Name) chLB=ChLB3;
	 if(bouton->Name==BtBnTous4->Name) chLB=ChLB4;
	 if(bouton->Name==BtBnTous5->Name) chLB=ChLB5;
	 */
	n=chLB->ItemIndex;
	critere=(CL_Item*)chLB->Items->Objects[n];
	if(chLB->Checked[n]==true)
	critere->Flag='O';
	else
	critere->Flag='N';

}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::BtBnCritereClick(TObject *Sender)
{
	/*
	 ChoixCritereFrm->VientDe="TriAgri";
	 ChoixCritereFrm->Show();
	 */
	AgriClasstFrm->VientDe="TriAgri";
	AgriClasstFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::BtBnOkClick(TObject *Sender)
{
	int n,i,j,k,l;
	bool trouve;
	int nbAgri;
	CL_Agriculteur *agri;
	CL_Item *critere,*critere2;
	CL_Categorie *categorie;
	TCheckListBox *chLB;

	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->LstCritere==NULL) {agri->Flag='N';continue;}
		if(agri->LstCritere->Count==0) {agri->Flag='N';continue;}

		agri->Flag='O'; // sélectionné jusqu'à élimination
		// en cas d'ajout ne pas faire de doublon
		if(estDejaSelectionne(agri)==true)
		{
			agri->Flag='N';
			continue;
		}
		// pour chaque categorie retenue
		for(n=0,k=0;n<AgriClasstFrm->ChLBCatTypeZone->Items->Count;n++,k++)
		{
			if(AgriClasstFrm->ChLBCatTypeZone->Checked[n]==false) continue;

			categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[k];

			chLB=(TCheckListBox*)LstChLB->Items[k];

			trouve=false;
			for(j=0;j<agri->LstCritere->Count;j++)
			{
				critere=(CL_Item*)agri->LstCritere->Items[j];
				if(categorie!=critere->Categorie) continue;

				for(l=0;l<chLB->Count;l++)
				{
					if(chLB->Checked[l]==false)continue;

					critere2=(CL_Item*)chLB->Items->Objects[l];
					if(critere2->Nom==critere->Nom)
					{
						trouve=true;
						break;
					}
				}
				// on a trouve Le critére de cette catégorie
				// soit 'O' on laisse agri->Flag à 'O'
				//       N     met                 'N'
//                trouve=true;
				if(critere->Flag=='N') agri->Flag='N';
				// on a trouvé le critere pas la peine d'aller + loin
				break;
			}
			// aucun critére  donc rejet
			if(trouve==false)
			agri->Flag='N';
			if(agri->Flag=='N') break;
		}
		if( agri->Flag=='N') continue; //idiot !?
	}
	nbAgri=0;
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->Flag=='O') nbAgri++;
	}
	if(nbAgri==0)
	{
		ShowMessage("Pas de nouvelle Sélection");
		return;
	}
	if (VientDe=="SelectionTri") SelectionTri();
	else if(VientDe=="Extraction") Extraction();
	else if(VientDe=="DefProcedure") SelectionProcedure();
	else ShowMessage("Oubli TriAgri");
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm:: SelectionTri(void)
{
	int i;
	int r;
	CL_Agriculteur *agri;
	CL_AgriEff *agriEff;
	AnsiString as;
	int nbAgri;
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->Flag=='N') continue;

		/// afficher les nouveaux entrés
		agriEff =new CL_AgriEff (agri);
		// la grille a au moins 2 lignes
		// cf Ensemble AffGrilleVide
		/// il faut que RowCount soiT > FixedRows
		///GrilleEstVide=false  dans EnsembleFrm->AffAgriEff
		if(EnsembleFrm->GrilleEstVide==true)
		{
			// afficher total en premiere ligne
			r=1;
			EnsembleFrm->Grille0->Cells[0][r]="Total";
			EnsembleFrm->Grille0->RowCount=2;
		}
		r=EnsembleFrm->Grille0->RowCount;
		EnsembleFrm->Grille0->RowCount++;

		EnsembleFrm->AffAgriEff(r,agriEff);
		EnsembleFrm->LabelModifie->Visible=true;
	}
	Close();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=true;
	nbAgri=EnsembleFrm->Grille0->RowCount-2;
	as=EnsembleFrm->Ensemble->Nom+" nb types=  "+AnsiString(nbAgri);
	EnsembleFrm->LabEnsemble->Caption=as;

}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm:: Extraction(void)
{
	//aller dans LBToutEnsemble
	LBToutEnsembleFrm->Extraction();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm:: SelectionProcedure(void)
{
	int i;
	CL_Agriculteur *agri;
	DefProcedureFrm->VAgri.clear();
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->Flag=='N') continue;

		DefProcedureFrm->VAgri.push_back(agri);
	}
	ShowMessage("Tri Effectué");
	AgriClasstFrm->Close();
	Close();
}
//---------------------------------------------------------------------------
bool __fastcall TTriAgriFrm::estDejaSelectionne(CL_Agriculteur *agri)
{
	int r;
	CL_AgriEff *agriEff;
	for(r=2;r<EnsembleFrm->Grille0->RowCount;r++)
	{
		agriEff=(CL_AgriEff *)EnsembleFrm->Grille0->Objects[0][r];
		if(agriEff==NULL)continue;
		if(agriEff->Agri==agri) return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void __fastcall TTriAgriFrm::BtBnPasOKClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTriAgriFrm::IniCaption(void) {
	BtBnAucun1->Caption = T->LC_BtIndAucun;
	BtBnAucun2->Caption = T->LC_BtIndAucun;
	BtBnAucun3->Caption = T->LC_BtIndAucun;
	BtBnAucun4->Caption = T->LC_BtIndAucun;
	BtBnAucun5->Caption = T->LC_BtIndAucun;
	TriAgriFrm->Caption = LC_TriAgriFrm;
	BtBnCritere->Caption = LC_BtBnCritere;
	Lab1->Caption = LC_Lab1;
	Lab2->Caption = LC_Lab2;
	Lab3->Caption = LC_Lab3;
	Lab4->Caption = LC_Lab4;
	Lab5->Caption = LC_Lab5;
	Pan1->Caption = LC_Pan1;
	Pan2->Caption = LC_Pan2;
	Pan3->Caption = LC_Pan3;
	Pan4->Caption = LC_Pan4;
	Pan5->Caption = LC_Pan5;
	BtBnTous1->Caption = T->LC_BtIndTous;
	BtBnTous2->Caption = T->LC_BtIndTous;
	BtBnTous3->Caption = T->LC_BtIndTous;
	BtBnTous4->Caption = T->LC_BtIndTous;
	BtBnTous5->Caption = T->LC_BtIndTous;
}
//--------------------------------------------
void TTriAgriFrm::TexteCaption(void) {
	LC_BtIndAucun = T->TrouveCaption("CL_Trad", "LC_BtIndAucun");
	LC_TriAgriFrm = T->TrouveCaption("TriAgri", "LC_TriAgriFrm");
	LC_BtBnCritere = T->TrouveCaption("TriAgri", "LC_BtBnCritere");
	LC_Lab1 = T->TrouveCaption("TriAgri", "LC_Lab1");
	LC_Lab2 = T->TrouveCaption("TriAgri", "LC_Lab2");
	LC_Lab3 = T->TrouveCaption("TriAgri", "LC_Lab3");
	LC_Lab4 = T->TrouveCaption("TriAgri", "LC_Lab4");
	LC_Lab5 = T->TrouveCaption("TriAgri", "LC_Lab5");
	LC_Pan1 = T->TrouveCaption("TriAgri", "LC_Pan1");
	LC_Pan2 = T->TrouveCaption("TriAgri", "LC_Pan2");
	LC_Pan3 = T->TrouveCaption("TriAgri", "LC_Pan3");
	LC_Pan4 = T->TrouveCaption("TriAgri", "LC_Pan4");
	LC_Pan5 = T->TrouveCaption("TriAgri", "LC_Pan5");
	LC_BtIndTous = T->TrouveCaption("CL_Trad", "LC_BtIndTous");

	IniCaption();

}
//--------------------------------------------

