//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
//#include "ChoixCritere.h"
#include "AgriClasst.h"

#include "GereEnsemble.h"
#include "TVVarianteAgri.h"
#include "LBToutAgri.h"
#include "LBSelectionAgri.h"
#include "TriAgri.h"
#include "LBToutEnsemble.h"
#include "CL_Trad.h"
#include "Outil.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "Ensemble.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TEnsembleFrm *EnsembleFrm;

extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TEnsembleFrm::TEnsembleFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
	EstInitialise = false;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::FormCreate(TObject *Sender)
{
	LarColAgri=100; //201206
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::FormActivate(TObject *Sender)
{
//	LabelModifie->Visible=false;
	if(EstInitialise==true) return;

	EstInitialise=true;
	Personnaliser();
	DefinirLesGrilles();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::SaisirCell(int col,int row)
{
	CellAVerifier=true;
	if(row==1) {CellModifiable(false); return;}

	if(col<ColAn0) CellModifiable(false);
	else CellModifiable(true);
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::Personnaliser(void)
{
	LaGrille=Grille0;
//    Grille0->RowCount=10;
//    Grille0->FixedRows=1;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::DefinirLesGrilles(void)
{
	AjoutRow=false;
	Grille0->Visible=true;
	GrilleX=1;

	LesGrilles[0]=Grille0;
	LesGrilles[0]->Tag=0;
// cf CreeGrille
//	ColM[0]=2;
//  RowM[0]=1;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::VersGrille(TStringGrid *grille)
{
//	ShowMessage("VersGrille A faire EnsembleFrm");
}

//---------------------------------------------------------------------------
// pour creer un ensemble //seult titreV_Agriculteur->Nbelt+1;
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::AffGrilleVide(void)
{

//int r;
//CL_Agriculteur *agri;
	CreeGrille();
	/** il faut que RowCount soiT > FixedRows*/
//	Grille0->RowCount=2;
//    Grille0->FixedRows=1; mis dans inspecteur d'objets
//    Grille0->Row=1;
//    CreeGrille();
}
//---------------------------------------------------------------------------
//utilisé par LBToutAgri
// si on supprime veut savoir si il y a des effectifs
// renoie n°ligne ou 0
//---------------------------------------------------------------------------
int __fastcall TEnsembleFrm::EstAffiche(CL_Agriculteur *agri0)
{
	CL_AgriEff *agriEff;
	int r;
///*  erreur à trouver 041001

	for(r=1;r<Grille0->RowCount;r++)
	{
		agriEff=(CL_AgriEff *)Grille0->Objects[0][r];
		if(agriEff==NULL) continue;
		if(agriEff->Agri==agri0) return r;
	}
//*/
	return 0;
}
// affiche les agriEff
// met adresse de agri dans	  		Grille0->Objects[0][r]=(TObject*)agri;
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::VoirEnsemble(void)
{
	int r;
	int i;
	CL_AgriEff *agriEff;
	AnsiString as;
	as=Ensemble->Nom+L_NbType+AnsiString(Ensemble->V_AgriEff->Nbelt);
	//as=Ensemble->Nom+" nb types=  "+AnsiString(Ensemble->V_AgriEff->Nbelt);
	switch(AFaire)
	{
		case VOIR:
		LabEnsemble->Caption=as;
		break;
		case MODIFIER: //GereEnsemble a écrit le nom
		case COPIER:
		break;
	}
	Grille0->RowCount=Ensemble->V_AgriEff->Nbelt+2;
	CreeGrille();
	//compter les agri
	TotalAgri();

	// afficher total en premiere ligne
	r=1;
	Grille0->Cells[0][r]=T->L_Total;//"Total";
	for(int n=0,c=ColAn0;n<N_X;n++,c++)
	{
		Grille0->Cells[c][r]=EffTotal[n];
	}

	//afficher les agri
	for(i=0;i<Ensemble->V_AgriEff->Nbelt;i++)
	{
		r++;
		agriEff=Ensemble->V_AgriEff->Vecteur[i];
		AffAgriEff(r,agriEff);
	}
	ValueAvant=Grille0->Cells[ColM[0]][RowM[0]];
}
//affiche tous les agri y compris les variantes
// met son adresse dans	    Grille0->Objects[0][r]=(TObject*)agri;
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::CreeGrille(void)
{
	int r,c;
	int j,n;
	CL_Categorie *categorie;
	CL_AgriEff *agriEff;
	int an_0;

	LaGrille=Grille0;
	n=0;
	for(j=0;j<AgriClasstFrm->ChLBCatTypeZone->Items->Count;j++)
	{
		if(AgriClasstFrm->ChLBCatTypeZone->Checked[j]==true)n++;
	}
	ColAn0=2+n;
	Grille0->ColCount=ColAn0+N_X;
//    Grille0->FixedCols=ColAn0;
//    Grille0->FixedRows=1;
	VideGrille(Grille0);
	// cellule initiale
	ColM[0]=ColAn0;
	RowM[0]=1;

	for(c=ColAn0;c<Grille0->ColCount;c++) TypeCol[c]='N';
	CellAVerifier=true;

	//en tete
	r=0;
	c=0;
	Grille0->ColWidths[c]=LarColAgri;
	Grille0->Cells[c][r]=T->L_Agri;//"Agriculteur";

	c=1;
	Grille0->ColWidths[c]=40;
	Grille0->Cells[c][r]=L_NVar;//"N° Var";
	for(j=0;j<AgriClasstFrm->ChLBCatTypeZone->Items->Count;j++)
	{
		if(AgriClasstFrm->ChLBCatTypeZone->Checked[j]==false) continue;

//	for(j=0;j<ChoixCritereFrm->LBCritere->Items->Count;j++)
//    {
		c=j+2;
		Grille0->ColWidths[c]=64;
//		categorie=(CL_Categorie*)ChoixCritereFrm->LBCritere->Items->Objects[j];
		categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[j];
		Grille0->Cells[c][r]=categorie->Nom;
	}
//    Grille0->RowCount=1+V_Agriculteur->Nbelt;  //pb des variantes
	// an_0 est l'année de début de la première exploitation de l'ensemble   SI IL Y en a
	//261108
	if(Ensemble->V_AgriEff->Nbelt==0)
	an_0=An_0;
	else
	{
		agriEff=Ensemble->V_AgriEff->Vecteur[0];
		an_0=agriEff->Agri->DefSim->An_0;
	}
	for(int i=0;i<10;i++)
	Grille0->Cells[i+ColAn0][0]="  "+AnsiString(an_0+i);

	GrilleEstVide=true;
}
/*
 // a voir c'est presque la meme fonction dans GereAgri
 //---------------------------------------------------------------------------
 int __fastcall TEnsembleFrm::AffLesVariantes(CL_Agriculteur *agri,int r)
 {
 ST_NoAgri      *variante;
 AffAgri(r,agri);
 if(agri->LstVariante->Count==0) return r;

 for(int i=0;i<agri->LstVariante->Count;i++)
 {
 variante=(ST_NoAgri*)agri->LstVariante->Items[i];   // Agri ou agri
 r++;
 r=AffLesVariantes(variante->Agri,r);
 }
 return r;
 }
 */
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::AffAgriEff(int r,CL_AgriEff *agriEff)
{
	int c;
	int j,k;
	CL_Agriculteur *agri;
//ST_NoItem      *critere;
	CL_Categorie *categorie;
	TList *lstCritere;
	CL_Item *item;
	bool trouve;
	agri=agriEff->Agri;

	lstCritere=agri->LstCritere;

	Grille0->Objects[0][r]=(TObject*)agriEff;
	Grille0->Cells[0][r]=agriEff->Agri->Nom;

	Grille0->Cells[1][r]=agriEff->Agri->NoVariante;
	for(j=0;j<AgriClasstFrm->ChLBCatTypeZone->Items->Count;j++)
	{
		if(AgriClasstFrm->ChLBCatTypeZone->Checked[j]==false) continue;

//    for(j=0;j<ChoixCritereFrm->LBCritere->Items->Count;j++)
//    {
		c=j+2;
		categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[j];
		trouve=false;
		for (k=0;k<lstCritere->Count;k++)
		{
			item=(CL_Item*)lstCritere->Items[k];
			if(item->Categorie==categorie)
			{
				Grille0->Cells[c][r]=item->Nom;
				trouve=true;
				k=lstCritere->Count;
			}
		}
		if(trouve==false) Grille0->Cells[c][r]="???";
	}

	for(int j=0,c=ColAn0;j<N_X;j++,c++)
	{
		Grille0->Cells[c][r]=Aff(agriEff->Effectif[j]);
	}
	GrilleEstVide=false;
}
/*
 //---------------------------------------------------------------------------
 CL_AgriEff* __fastcall TEnsembleFrm::TrouveAgriEff(CL_Agriculteur *agri)
 {
 CL_AgriEff* agriEff;

 if(Ensemble==NULL) return NULL;

 for(int i=0;i<Ensemble->V_AgriEff->Nbelt;i++)
 {
 agriEff=Ensemble->V_AgriEff->Vecteur[i];
 if(agriEff->Agri==agri) return agriEff;
 }
 return NULL;
 }
 */
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::EffaceEnsemble(void)
{
	int rep;
	rep=MessageBox(Handle,L_EffQ.c_str(),T->L_SupT.c_str(),
			//rep=MessageBox(Handle,"J'efface ?","SUPPRESSION",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==ID_YES)
	{
		V_Ensemble->sup(Ensemble);
		GereEnsembleFrm->CreeGrilleEns();
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtReportDroitClick(TObject *Sender)
{
	int c;
	int r0,c0;
	c0=LaGrille->Col;
	if(c0<ColAn0) return;
	r0=LaGrille->Row;
	if(r0<2)return;
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false ) continue;
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtReportBasClick(TObject *Sender)
{
	int r;
	int r0,c0;
	c0=LaGrille->Col;
	if(c0<ColAn0) return;
	r0=LaGrille->Row;
	if(r0<2)return;
	for(r=r0+1;r<LaGrille->RowCount;r++)
	{
		if(RepPossible(c0,r)==false ) continue;
		LaGrille->Cells[c0][r]=LaGrille->Cells[c0][r0];
	}
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtReportLigne(TObject *Sender)
{
	int c,r;
	int r0;
	r0=LaGrille->Row;
	if(r0<2)return;
	for(c=ColAn0;c<LaGrille->ColCount;c++)
	{
		for(r=r0+1;r<LaGrille->RowCount;r++)
		{
			if(RepPossible(c,r)==false ) continue;
			LaGrille->Cells[c][r]=LaGrille->Cells[c][r0];
			LabelModifie->Visible=true;
		}
	}
	LabelModifie->Visible=true;
}
//240406
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtReportTout(TObject *Sender)
{
	int c,r;
	int r0,c0;
	c0=LaGrille->Col;
	if(c0<ColAn0) return;
	r0=LaGrille->Row;
	if(r0<2)return;
	for(r=r0;r<LaGrille->RowCount;r++)
	{
		for(c=c0;c<LaGrille->ColCount;c++)
		{
			if(RepPossible(c,r)==false ) continue;
			LaGrille->Cells[c][r]=LaGrille->Cells[c0][r0];
		}
	}
	LabelModifie->Visible=true;
}
// compte tenu de la façon de remplir la grille
//      SelectionManuelle
//      SelectionTri
//      SelectionAddition
//      Extraction
// il n'y a pas de doublon
// peut etre faire une fonction pour vérifier
//CL_AgriEff contient obligatoirement No et Nom pour pouvoi etre stocké dans
// son Vecteur: Ensemble->V_AgriEff
// lui donner un No = n° de la ligne
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::DeGrille(TStringGrid *grille)
{
	int row,c,n,i;
	AnsiString value;
	CL_AgriEff *agriEff;
	switch (AFaire)
	{
		case CREER: break;
		case COPIER:Ensemble=new CL_Ensemble();break;
		case VOIR:
		// pour repérer les suppressions cf fin de cette méthode
		case MODIFIER: Ensemble->V_AgriEff->FlagMisA('O');break;
		case SUPPRIMER: return;
		default:ShowMessage("DeGrille Oubli");
	}
	// je vide le vecteur
	Ensemble->V_AgriEff->Nbelt=0;
	Ensemble->V_AgriEff->NoX=0;
	// row=1 contient total
	for(row=1;row<Grille0->RowCount;row++)
	{
		agriEff=(CL_AgriEff*)Grille0->Objects[0][row];
		if(agriEff==NULL) continue;

		agriEff->Flag='N';
		agriEff->No=row;

		for(c=ColAn0,n=0;n<N_X;n++,c++)agriEff->Effectif[n]=GrilleInt(c,row);

		Ensemble->V_AgriEff->ins(agriEff);
	}

	//si on a supprimé des agriEff ils ne sont plus dans la grille
	// mais ils sont tjrs dans..Vecteur
	// ils sont reconnaissables avec Flag='O'
	// cela a été initialisé au début de cette fonction
	for(i=0;i<Ensemble->V_AgriEff->Nbelt;i++)
	{
		agriEff=Ensemble->V_AgriEff->Vecteur[i];
		if(agriEff->Flag=='O')
		{
			Ensemble->V_AgriEff->sup(agriEff->No);
			i--;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtBnStockerClick(TObject *Sender)
{
	Stocker();
}
//---------------------------------------------------------------------------
bool __fastcall TEnsembleFrm::Stocker(void)
{
	AnsiString nom;
	int rep;
	if(AFaire!=SUPPRIMER)
	{
		DeGrille(Grille0);
		if(Ensemble->V_AgriEff->Nbelt==0)
		{
			rep=MessageBox(Handle,L_Abandon.c_str(),L_Vide.c_str(),
					//rep=MessageBox(Handle,"J'abandonne ?","Ensemble Vide",
					MB_YESNO|MB_ICONEXCLAMATION);
			if(rep==ID_NO) return false;//280405
			else return true;
		}
//        LabEnsemble->Caption=EdNomEnsemble->Text;
//        Ensemble->Nom=EdNomEnsemble->Text;
	}
	switch(AFaire)
	{
		case CREER:
		case COPIER:
		V_Ensemble->ins(Ensemble);
		break;
		case VOIR:
		case MODIFIER:
		case SUPPRIMER:
		break;
		default:ShowMessage("Oubli Stocker");
	}
	GereEnsembleFrm->CreeGrilleEns();
	ES->ecrireFichier();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtAutreClick(TObject *Sender)
{
	LBSelectionAgriFrm->VientDe="Ensemble";
	LBSelectionAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::SelectionManuelle(void)
{
//	EnsembleFrm->AFaire=CREER;

//    EnsembleFrm->AffGrilleVide();
	Forme0Frm->CreeLBToutAgri(LBToutAgriFrm->ChLB);
	LBToutAgriFrm->VientDe="Ensemble";

	LBToutAgriFrm->Show();
//	EnsembleFrm->Show();
//    EnsembleFrm->LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::SelectionTri(void)
{
	TriAgriFrm->VientDe="SelectionTri";
	TriAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::SelectionAddition(void)
{
	LBToutEnsembleFrm->VientDe="SelectionAddition";
	LBToutEnsembleFrm->CreeLB();
	LBToutEnsembleFrm->BtBnVisible(true);
	LBToutEnsembleFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::Extraction(void)
{
	LBToutEnsembleFrm->VientDe="Extraction";
	LBToutEnsembleFrm->CreeLB();
	LBToutEnsembleFrm->BtBnVisible(false);
	LBToutEnsembleFrm->Show();

	TriAgriFrm->VientDe="Extraction";
	TriAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtBnSupClick(TObject *Sender)
{
	int r0;
	int rep;
	AnsiString as;
	CL_AgriEff *agriEff;
	r0=LaGrille->Row;
	if(r0==0) return;
	MarquerLigne(r0);
	as=L_SupQ+LaGrille->Cells[0][r0]+L_SupQ2;
	//as=AnsiString (" Je supprime   ")+LaGrille->Cells[0][r0]+"  Vous êtes sur ?";
	rep=MessageBox(Handle,as.c_str(),T->L_SupT.c_str(),MB_YESNO);

	DeSelLigne();

	if(rep==IDNO) return;
	agriEff=(CL_AgriEff*)LaGrille->Objects[0][r0];
	LBToutAgriFrm->Decoche(agriEff->Agri);
	SupLigne(r0);
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::SupLigne(int r0)
{
	int r,c;
	for(r=r0;r<LaGrille->RowCount;r++)
	{
		for(c=0;c<LaGrille->ColCount;c++)
		LaGrille->Cells[c][r]=LaGrille->Cells[c][r+1];
		LaGrille->Objects[0][r]=LaGrille->Objects[0][r+1];
	}

	LaGrille->RowCount--;
//    LaGrille->Repaint();
	GrilleModif[LaGrille->Tag]=true;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtClHautClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
	TObject *object;
	LabelModifie->Visible=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row<=1) return;

	object=LaGrille->Objects[0][row];
	LaGrille->Objects[0][row]=LaGrille->Objects[0][row-1];
	LaGrille->Objects[0][row-1]=object;

	for(c=0;c<cX;c++)
	{
		s=LaGrille->Cells[c][row];
		LaGrille->Cells[c][row]=LaGrille->Cells[c][row-1];
		LaGrille->Cells[c][row-1]=s;
	}
//    LaGrille->Cells[0][row-1] =row-1;
//    LaGrille->Cells[0][row]   =row;
	MarquerLigne(row-1);
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtClBasClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
	TObject *object;
	LabelModifie->Visible=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row>=LaGrille->RowCount-1) return;

	object=LaGrille->Objects[0][row];
	LaGrille->Objects[0][row]=LaGrille->Objects[0][row+1];
	LaGrille->Objects[0][row+1]=object;
	for(c=0;c<cX;c++)
	{
		s=LaGrille->Cells[c][row];
		LaGrille->Cells[c][row]=LaGrille->Cells[c][row+1];
		LaGrille->Cells[c][row+1]=s;
	}
//    LaGrille->Cells[0][row]  =row;
//    LaGrille->Cells[0][row+1]=row+1;

	MarquerLigne(row+1);
//    PosClasst();
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::TotalAgri(void)
{
	int i,n;
	CL_AgriEff *agriEff;
	memset(EffTotal,0,sizeof(int)*N_X);
	for(i=0;i<Ensemble->V_AgriEff->Nbelt;i++)
	{
		agriEff=Ensemble->V_AgriEff->Vecteur[i];
		for(n=0;n<N_X;n++)
		EffTotal[n]+=agriEff->Effectif[n];
	}
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::TotalAgriDeGrille(void)
{
	int i,n;
	int c,r;
	int eff;
	memset(EffTotal,0,sizeof(int)*N_X);
	r=2;
//	for(i=0;i<Ensemble->V_AgriEff->Nbelt;i++)
	for(i=2;i<Grille0->RowCount;i++)
	{
		for(n=0,c=ColAn0; n<N_X; n++,c++)
		{
			eff=GrilleInt(c, r);
			EffTotal[n]+=eff;
		}
		r++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtBnSommeClick(TObject *Sender)
{
	int r=1;
	TotalAgriDeGrille();
	// afficher total en premiere ligne
	Grille0->Cells[0][r]=T->L_Total;//"Total";
	for(int n=0,c=ColAn0;n<N_X;n++,c++)
	{
		Grille0->Cells[c][r]=EffTotal[n];
	}
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	bool rep;
	LarColAgri=Grille0->ColWidths [0];
	rep=Stocker();
	if(rep==false)
	{
		CanClose=false;
		return;
	}
//    ChoixCritereFrm->Close();
	TVVarianteAgriFrm->Close();
	LBToutAgriFrm->Close();
	LBSelectionAgriFrm->Close();
	TriAgriFrm->Close();
	LBToutEnsembleFrm->Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TEnsembleFrm::TexteChaine(void) {
	L_NbType = T->TrouveTexte("EnsembleFrm", "L_NbType");
	L_NVar = T->TrouveTexte("EnsembleFrm", "L_NVar");
	L_EffQ = T->TrouveTexte("EnsembleFrm", "L_EffQ");
	L_Abandon = T->TrouveTexte("EnsembleFrm", "L_Abandon");
	L_Vide = T->TrouveTexte("EnsembleFrm", "L_Vide");
	L_SupQ = T->TrouveTexte("EnsembleFrm", "L_SupQ");
	L_SupQ2 = T->TrouveTexte("EnsembleFrm", "L_SupQ2");
}
//--------------------------------------------
void TEnsembleFrm::IniCaption(void) {
	BtAutre->Caption = LC_BtAutre;
	EnsembleFrm->Caption = T->LC_ChBEnsemble;
	LabEnsemble->Caption = T->LC_ChBEnsemble;
	BtBnSomme->Caption = LC_BtBnSomme;
}
//--------------------------------------------
void TEnsembleFrm::TexteCaption(void) {
	LC_BtAutre = T->TrouveCaption("Ensemble", "LC_BtAutre");
	LC_ChBEnsemble = T->TrouveCaption("CL_Trad", "LC_ChBEnsemble");
	LC_BtBnSomme = T->TrouveCaption("Ensemble", "LC_BtBnSomme");

	IniCaption();

}

//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtBnVersExcelClick(TObject *Sender)
{
	OutilFrm->VersExcel(LaGrille,0,0,Grille0->ColCount,Grille0->RowCount);
}
//---------------------------------------------------------------------------
void __fastcall TEnsembleFrm::BtBnDExcelClick(TObject *Sender)
{
	OutilFrm->DExcel(LaGrille,0,0,Grille0->ColCount,Grille0->RowCount);
	LabelModifie->Visible==true;

}
//---------------------------------------------------------------------------

void __fastcall TEnsembleFrm::BtBnNotesClick(TObject *Sender)
{

//020507
	NoteAgriFrm->VientDe="Ensemble";//ne pas traduire
	NoteAgriFrm->Ensemble=Ensemble;
	NoteAgriFrm->Caption=Ensemble->Nom;
	NoteAgriFrm->Memo->Text=Ensemble->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TEnsembleFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

