//---------------------------------------------------------------------------
#include <vcl.h>
#include <checklst.hpp>

#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "FichierLire.h"
#include "Brouillon.h"
#include "Tableur.h"

#include "Main.h"
//#include "ChoixCritere.h" //a retirer
#include "AgriClasst.h"

#include "AgriSaisie.h"
#include "NouvAgri.h"
#include "NoteAgri.h"
#include "TVVarianteAgri.h"

#include "GereAtelier.h"
#include "GereCatItem.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "GereAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGereAgriFrm *GereAgriFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//S_List a Creer
//---------------------------------------------------------------------------
__fastcall TGereAgriFrm::TGereAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::FormCreate(TObject *Sender)
{
	LarColAgri=240;
	Notes="";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::FormActivate(TObject *Sender)
{
	//040302
	if( GereAtelierFrm->Visible==true) GereAtelierFrm->Close();
	if( GereCatItemFrm->Visible==true) GereCatItemFrm->Close();

	if( NoteAgriFrm->Visible==true) NoteAgriFrm->Close();//110905
	if( AgriClasstFrm->Visible==true) AgriClasstFrm->Close();//110905

//    RGClasserCritere->ItemIndex=0;
	if(Origine==0)
	{
		Origine=0; //1;         //tjrs rafraichir

		S_List=new TStringList;//sert pour trier

		AgriClasstFrm->AffGrille();

		//RGVarianteClick(this); //supprimerait les 4 lignes suivantes mais pue compréhensible
		if(RGVariante->ItemIndex==0)//variantes visibles
		AvecVariante=true;
		else
		AvecVariante=false;
		CreeGrilleAgri();

		AgriSaisieFrm->LabelModifie->Visible=false;
		AgriSaisieFrm->Origine=0;
		//GrilleAgriClick(this); a quoi ça sert ?
		TrouveEnCours();
		//AgriClasstFrm->Show();
		//AgriClasstFrm->LabelModifie->Visible=false;
	}
	if(AgriClasstFrm->LabelModifie->Visible==true)
	{
		AgriClasstFrm->LabelModifie->Visible=false;
		CreeGrilleAgri();
	}
}
//---------------------------------------------------------------------------
// fait afficher agri par AgriSaisieFrm
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtDonneesClick(TObject *Sender)
{
	int r;
	CL_Agriculteur *agri;
	AnsiString debNom;
	r=GrilleAgri->Row;
	agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	if(agri==NULL)
	{
		ShowMessage(L_PasAgri.c_str()); //"Pas d'agriculteur défini");
		return;
	}

	AgriSaisieFrm->Agri=agri;
	debNom=AnsiString(agri->Nom).SubString(1,5);
	if (debNom=="TOTAL") agri->TypeAgreg=TOTAL;
	else if(debNom=="MOYEN") agri->TypeAgreg=MOYENNE;
	else agri->TypeAgreg=SANS;
	NoteAgriFrm->Close();
	AgriSaisieFrm->Origine=0;
	AgriSaisieFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtNouveauClick(TObject *Sender)
{
	bool rep;
	NouvAgriFrm->Origine=0;

	NouvAgriFrm->AFaire=CREER;
	NouvAgriFrm->Agri=NULL;
	NouvAgriFrm->Show();
	rep=NouvAgriFrm->SaisirNom();
	if(rep==false)
	NouvAgriFrm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtCopierClick(TObject *Sender)
{
	int r;
	bool rep;
	CL_Agriculteur *agri;
	r=GrilleAgri->Row;
	agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	if(agri==NULL)
	{
		ShowMessage(L_PasAgri.c_str()); //"Pas d'agriculteur défini");
		//ShowMessage("Pas d'agriculteur défini");
		return;
	}

	NouvAgriFrm->Origine=0;
	NouvAgriFrm->AFaire=COPIER;
	NouvAgriFrm->Agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];

	NouvAgriFrm->Show();
	rep=NouvAgriFrm->SaisirNom();
	if(rep==false)
	NouvAgriFrm->Close();
}

//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtSupprimerClick(TObject *Sender)
{
	int r;
	bool rep;
	AnsiString as;
	CL_Agriculteur *agri,*fils,*agriX;
	ST_NoAgri *stFils,*noAgri;

	r=GrilleAgri->Row;
	agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];

	if(agri==NULL)return;
	if(agri->Supprimable==false)
	{
		ShowMessage(T->L_Utilise.c_str()); //"UTILISE");
		return;
	}
	if(agri->LstVariante->Count>0) //230908
	{
		as="Supprimer TOUTES les variantes";
		rep=MessageBox(Handle,as.c_str(),T->L_SupT.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
		//rep=MessageBox(Handle,as.c_str(),L_SupT"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO) return;

		elagueAgri(agri);
		V_Agriculteur->sup(agri);
		CreeGrilleAgri();
		//ShowMessage(L_ADesVar.c_str());//"Impossible: A des Variantes\n Essayer Elaguer");
		return;
	}

	// Suppression
	//260902
	//230908
//    as=L_SupQ+ agri->NomV()+"  ?";
	as=L_SupQ+ agri->Nom+"  ?";
	//as=L_SupQ" Vous Supprimez "+ agri->NomV()+"  ?";
	rep=MessageBox(Handle,as.c_str(),T->L_SupT.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	//rep=MessageBox(Handle,as.c_str(),L_SupT"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	// cas d'une variante
	if(agri->Pere)
	{
		for (int i=0;i<agri->Pere->LstVariante->Count;i++)
		{
			stFils=(ST_NoAgri*)agri->Pere->LstVariante->Items[i];
			fils=stFils->Agri;
			if(fils==agri)
			{
				agri->Pere->LstVariante->Extract(stFils);
				break;
			}
		}
	}
	//cas plus 10 ans
	if(agri->LstSerie!=NULL && agri->LstSerie->Count>1)
	{
		for (int i=1;i<agri->LstSerie->Count;i++)
		{
			noAgri=(ST_NoAgri*)agri->LstSerie->Items[i];
			agriX=noAgri->Agri;
			V_Agriculteur->sup(agriX);
		}
	}
	V_Agriculteur->sup(agri);
	ES->ecrireFichier();

	CreeGrilleAgri();
	GrilleAgri->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtElaguerClick(TObject *Sender)
{
	int r;
	int rep;
	AnsiString as;
	CL_Agriculteur *agri;

	r=GrilleAgri->Row;
	agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];

	if(agri==NULL)return;
	//260902
	as=L_Elaguer+ agri->NomV()+"  ?";
	//as=" Vous Elaguez "+ agri->NomV()+"  ?";
	rep=MessageBox(Handle,as.c_str(),T->L_SupT.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	//rep=MessageBox(Handle,as.c_str(),"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	elagueAgri(agri);
	CreeGrilleAgri();
	GrilleAgri->SetFocus();
}
//---------------------------------------------------------------------------
bool __fastcall TGereAgriFrm::elagueAgri(CL_Agriculteur *agri)
{
	CL_Agriculteur *fils,*pere;
	ST_NoAgri *stFils;

	if(agri->Pere==NULL)
	{
		for(int i=0;i<agri->LstVariante->Count;i++)
		{
			stFils=(ST_NoAgri*)agri->LstVariante->Items[i];
			fils=stFils->Agri;
			elagueAgri(fils);
		}
	}
	else
	{
		for(int i=0;i<agri->LstVariante->Count;i++)
		{
			stFils=(ST_NoAgri*)agri->LstVariante->Items[i];
			fils=stFils->Agri;
			elagueAgri(fils);
		}
		pere=agri->Pere;
		for (int i=0;i<pere->LstVariante->Count;i++)
		{
			stFils=(ST_NoAgri*)pere->LstVariante->Items[i];
			fils=stFils->Agri;
			if(fils==agri)
			{
				if(filsSupprimable(fils)==true)
				{
					V_Agriculteur->sup(fils);
					pere->LstVariante->Extract(stFils);
				}
				break;
			}
		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TGereAgriFrm::filsSupprimable(CL_Agriculteur *agri)
{
	bool rep;
	CL_Agriculteur *fils;
	ST_NoAgri *stFils;
	rep=true;
	if(agri->Supprimable==false) rep=false;

	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		stFils=(ST_NoAgri*)agri->LstVariante->Items[i];
		fils=stFils->Agri;
		if(filsSupprimable(fils)==false) rep=false;
	}
	return rep;
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtModifieClick(TObject *Sender)
{
	int r=GrilleAgri->Row;
	CL_Agriculteur *agri;
	TRect rect;
	int posG,posH;

	agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	if(agri==NULL)
	{
		ShowMessage(L_PasAgri.c_str()); //"Pas d'agriculteur défini");
		//ShowMessage("Pas d'agriculteur défini");
		return;
	}
	rect=GrilleAgri->CellRect(0,r);
	posG=Left+rect.Left;
	posH=Top+rect.Bottom+20; //20 ??

	NouvAgriFrm->Origine=0;
	NouvAgriFrm->Top= posH;
	NouvAgriFrm->Left=PanAgri->Width+posG;
	NouvAgriFrm->AFaire=MODIFIER;
	NouvAgriFrm->Agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	NouvAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtVarianteClick(TObject *Sender)
{
	int r;
	CL_Agriculteur *agri;
	r=GrilleAgri->Row;
	agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	if(agri==NULL)
	{
		ShowMessage(L_PasAgri.c_str()); //"Pas d'agriculteur défini");
		//ShowMessage("Pas d'agriculteur défini");
		return;
	}
//  voir si on prefère arbre partiel ou complet
//    ancetre=trouveAncetre(agri);
	TVVarianteAgriFrm->Caption="Variantes de "+agri->Nom;
	//TVVarianteAgriFrm->Caption="Variantes de "+agri->Nom;

	Forme0Frm->CreeTVVarianteAgri(TVVarianteAgriFrm->TV,agri);
	TVVarianteAgriFrm->Show();

	NouvAgriFrm->Origine=0;
	NouvAgriFrm->AFaire=VARIANTE;
	NouvAgriFrm->Agri=agri;//ancetre;
	NouvAgriFrm->Show();
}
//---------------------------------------------------------------------------
CL_Agriculteur* __fastcall TGereAgriFrm::trouveAncetre(CL_Agriculteur *agri)
{
	CL_Agriculteur *pere;
	while(1)
	{
		pere=agri->Pere;;
		if(pere==agri->Pere) return agri; //280202
		if(pere==NULL) return agri;

		agri=pere;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::RGVarianteClick(TObject *Sender)
{
	if(RGVariante->ItemIndex==0) //variantes visibles
	AvecVariante=true;
	else
	AvecVariante=false;
	CreeGrilleAgri();
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::RGNoteClick(TObject *Sender)
{
	if(AgriEnCours==NULL) return;

	NoteAgriFrm->VientDe="GereAgri";

	if(RGNote->ItemIndex==0) //Note visible
	{
		NoteAgriFrm->Show();
		Origine=1; //110905 court circuiter FormActivate
	}
	else
	NoteAgriFrm->Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::GrilleAgriClick(TObject *Sender)
{
	int r;
	r=GrilleAgri->Row;
	AgriEnCours=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	NoteAgriFrm->Agri=AgriEnCours;
//    NoteAgriFrm->Agri=(CL_Agriculteur *)GrilleAgri->Objects[0][r];
	NoteAgriFrm->VientDe="GereAgri";

	if(NoteAgriFrm->Agri==NULL)return;//on démarre aucun agri n'a été défini

	if(RGNote->ItemIndex==0)
	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::CreeTVVariante(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::GrilleAgriDblClick(TObject *Sender)
{
	BtDonneesClick(this);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// CreeGrilleAgri
//-----------------------------------------------------------------------------
void __fastcall TGereAgriFrm::VideGrille(TStringGrid *grille)
{
	for(int r=1;r<grille->RowCount;r++)
	{
		grille->Objects[0][r]=NULL;
		for(int c=0;c<grille->ColCount;c++)
		grille->Cells[c][r]="";
	}
}
// cree grille avec Nb colonne et lignes adéquats
// nom Nombre de variantes no  de variante + critères
// remplit
// tri par ordre alpha
//----------------------------------------------------------------------------
void __fastcall TGereAgriFrm::CreeGrilleAgri(void)
{

	CL_Categorie *categorie;
	CL_Agriculteur *agri; //, *ancetre;
	AnsiString s;
	int c,i,j,r;
	int nbAgri=0;
//    RGClasserCritere->ItemIndex=-1;

	if(AvecVariante==false)
	{
		for(i=0;i<V_Agriculteur->Nbelt;i++)
		{
			agri=V_Agriculteur->Vecteur[i];
			if(agri->EstPlus10Ans==true)continue; //111206
			if(agri->EstVariante==false) nbAgri++;
		}
	}
	VideGrille(GrilleAgri);
	// nb row
	if(V_Agriculteur->Nbelt==0)GrilleAgri->RowCount=2;
	else
	{
		if(AvecVariante==false) GrilleAgri->RowCount=nbAgri+1;
		else GrilleAgri->RowCount=V_Agriculteur->Nbelt+1;
	}
	// 1 colonne pour le nom, le nombre de variante, le n° de variante +les criteres
	GrilleAgri->ColCount=V_CatTypeZone->Nbelt+4;//111206
	//en tete
	r=0;

	c=0;
	GrilleAgri->ColWidths[c]=LarColAgri;
	GrilleAgri->Cells[c][r]=T->L_Agri;//"Agriculteur";

	c=1;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][r]=L_NbVar;//" Nb Var";

	c=2;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][r]=L_NoVar;//" N° Var";

	c=3;
	GrilleAgri->ColWidths[c]=40;
	GrilleAgri->Cells[c][r]="Duree";//L_NoVar;//" N° Var";//111206

	c=4;
	/*supprimé le 120109
	 for(j=0;j<AgriClasstFrm->ChLBCatTypeZone->Count;j++)
	 {
	 categorie=(CL_Categorie*)AgriClasstFrm->ChLBCatTypeZone->Items->Objects[j];
	 GrilleAgri->ColWidths[c]=90;
	 GrilleAgri->Cells[c][r]=categorie->Nom;
	 GrilleAgri->Objects[c][r]=(TObject*)categorie;
	 c++;
	 }
	 */
//rétabli 120109
//
	for(j=0;j<V_CatTypeZone->Nbelt;j++)
	{
		categorie=V_CatTypeZone->Vecteur[j];
		GrilleAgri->ColWidths[c]=90;
		GrilleAgri->Cells[c][r]=categorie->Nom;
		GrilleAgri->Objects[c][r]=(TObject*)categorie;
		c++;
	}

//    TriAgriAlpha();
	//agri
	Row=1;
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri=V_Agriculteur->Vecteur[i];
		if(agri->EstVariante==true) continue;
		if(agri->EstPlus10Ans==true)continue; //111206

		agri->Pere==NULL;
		if(AvecVariante==false)
		AffAgri(agri);
		else
		AffLesVariantes( agri);
	}
	GrilleAgri->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::AffAgri(CL_Agriculteur *agri)
{
	CL_Categorie *categorie;
	TList *lstCritere;
	CL_Item *critere;
	int c,k;
	bool trouve;
	if(agri==NULL) return; //160408
	lstCritere=agri->LstCritere;

	GrilleAgri->Objects[0][Row]=(TObject*)agri;
	GrilleAgri->Cells[0][Row]=agri->Nom;

//    GrilleAgri->Cells[1][Row]=AnsiString(agri->NbVariante);
	GrilleAgri->Cells[1][Row]=AnsiString(agri->LstVariante->Count);//180108
	GrilleAgri->Cells[2][Row]=AnsiString(agri->NoVariante);
	GrilleAgri->Cells[3][Row]=AnsiString(agri->DefSim->NbAnSim);
	for(c=4;c<GrilleAgri->ColCount;c++)//111206
	{
		categorie=(CL_Categorie*)GrilleAgri->Objects[c][0];
		trouve=false;
		for (k=0;k<lstCritere->Count;k++)
		{
			critere=(CL_Item*)lstCritere->Items[k];
			if(critere->Categorie==categorie)
			{
				GrilleAgri->Cells[c][Row]=critere->Nom;
				trouve=true;
				k=lstCritere->Count;
				break;
			}
		}
		if(trouve==false)
		GrilleAgri->Cells[c][Row]="???";
	}
	Row++;

}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::AffLesVariantes(CL_Agriculteur *agri)
{
	ST_NoAgri *variante;
	if(agri==NULL) return; //160608
	AffAgri(agri);
	GrilleAgri->Cells[2][Row-1]=AnsiString(agri->NoVariante);
	if(agri->LstVariante->Count==0) return;

	for(int i=0;i<agri->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)agri->LstVariante->Items[i];
		AffLesVariantes(variante->Agri);
	}
	return;
}
//---------------------------------------------------------------------------
// Verif Close            a modifier cf saisagri
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTEROLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	NoteAgriFrm->Close();
	NouvAgriFrm->Close();
	LarColAgri=GrilleAgri->ColWidths [0];
}

//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::TrouveEnCours(void)
{
	TGridRect selection;
	int cX=GrilleAgri->ColCount;
	int r;
	CL_Agriculteur *agri;
	bool trouve=false;

	for(r=0;r<GrilleAgri->RowCount;r++)
	{
		agri=(CL_Agriculteur*)GrilleAgri->Objects[0][r];
		if(agri==NULL) continue;
		if(agri==AgriEnCours) {trouve=true;break;}
	}
	if(trouve==false) return;
	NoteAgriFrm->VientDe="GereAgri";

	NoteAgriFrm->Agri=agri;
	if(RGNote->ItemIndex==0)
	NoteAgriFrm->Show();
	selection.Left=0;
	selection.Right=cX;
	selection.Top=r;
	selection.Bottom=r;
	GrilleAgri->Selection=selection;

}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::TriAgriAlpha(void)
{
	int i,j;
	CL_Agriculteur *agri,*agri0;
	for(i=0;i<V_Agriculteur->Nbelt;i++)
	{
		agri0=V_Agriculteur->Vecteur[i];
		if(agri0->EstVariante==true) continue;

		for(j=i+1;j<V_Agriculteur->Nbelt;j++)
		{
			agri=V_Agriculteur->Vecteur[j];
			if(agri->EstVariante==true) continue;

			if(agri->Nom.AnsiCompare(agri0->Nom)<0)
			{
				V_Agriculteur->Vecteur[i]=agri;
				V_Agriculteur->Vecteur[j]=agri0;
				agri0=agri;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TGereAgriFrm::RGClasserCritereClick(TObject *Sender)
{
	/*
	 if(RGClasserCritere->ItemIndex==0)
	 {
	 AgriClasstFrm->ClasserAlpha();
	 CreeGrilleAgri();
	 }
	 else
	 {
	 AgriClasstFrm->VientDe="GereAgri";
	 AgriClasstFrm->Show();
	 }
	 //RGClasserCritere->ItemIndex=-1;
	 */
}
//---------------------------------------------------------------------------
void __fastcall TGereAgriFrm::BtBnClasserClick(TObject *Sender)
{
	if(RGClasserCritere->ItemIndex==0)
	{
		AgriClasstFrm->ClasserAlpha();
		CreeGrilleAgri();
	}
	else
	{
		AgriClasstFrm->VientDe="GereAgri";
		AgriClasstFrm->Show();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TGereAgriFrm::TexteChaine(void) {
	L_PasAgri = T->TrouveTexte("GereAgriFrm", "L_PasAgri");
	L_ADesVar = T->TrouveTexte("GereAgriFrm", "L_ADesVar");
	L_SupQ = T->TrouveTexte("GereAgriFrm", "L_SupQ");
	L_Elaguer = T->TrouveTexte("GereAgriFrm", "L_Elaguer");
	L_VarDe = T->TrouveTexte("GereAgriFrm", "L_VarDe");
	L_NbVar = T->TrouveTexte("GereAgriFrm", "L_NbVar");
	L_NoVar = T->TrouveTexte("GereAgriFrm", "L_NoVar");

}
//--------------------------------------------
void TGereAgriFrm::IniCaption(void) {
//    BtBnCriteres->Caption=T->LC_BtClasser;
	BtBnClasser->Caption = T->LC_BtClasser;
//    BtBnClasserAlpha->Caption=LC_BtBnClasserAlpha;
	RGClasserCritere->Caption = LC_RGClasserCritere;
	BtCopier->Caption = T->LC_BtBnCopier;
//    BtCriteres->Caption=LC_BtCriteres;
	BtDonnees->Caption = T->LC_BtDonnees;
	GereAgriFrm->Caption = T->LC_GereAgriFrm;
	BtModifie->Caption = LC_BtModifie;
	RGNote->Caption = LC_RGNote;
	BtNouveau->Caption = T->LC_BtNouveau;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	BtSupprimer->Caption = T->LC_BtBnSupBesTrav;
	BtElaguer->Caption = LC_BtElaguer;
	BtVariante->Caption = T->LC_BtVariante;
	RGVariante->Caption = T->LC_BtVariante;
	//100206
	RGVariante->Items->Strings[0] = T->LC_Visible;
	RGVariante->Items->Strings[1] = T->LC_NonVisible;
	RGNote->Items->Strings[0] = T->LC_Visible;
	RGNote->Items->Strings[1] = T->LC_NonVisible;
	BtBnClasser->Caption = T->LC_BtClasser;
	RGClasserCritere->Items->Strings[0] = LC_CltAlpha;
	RGClasserCritere->Items->Strings[1] = LC_CltAlaDemande;
}
//--------------------------------------------
void TGereAgriFrm::TexteCaption(void) {
	LC_BtClasser = T->TrouveCaption("CL_Trad", "LC_BtClasser");
	LC_BtBnClasserAlpha = T->TrouveCaption("GereAgri", "LC_BtBnClasserAlpha");
	LC_RGClasserCritere = T->TrouveCaption("GereAgri", "LC_RGClasserCritere");
	LC_BtBnCopier = T->TrouveCaption("CL_Trad", "LC_BtBnCopier");
	LC_BtCriteres = T->TrouveCaption("GereAgri", "LC_BtCriteres");
	LC_BtDonnees = T->TrouveCaption("CL_Trad", "LC_BtDonnees");
	LC_GereAgriFrm = T->TrouveCaption("CL_Trad", "LC_GereAgriFrm");
	LC_BtModifie = T->TrouveCaption("GereAgri", "LC_BtModifie");
	LC_RGNote = T->TrouveCaption("GereAgri", "LC_RGNote");
	LC_BtNouveau = T->TrouveCaption("CL_Trad", "LC_BtNouveau");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");
	LC_BtElaguer = T->TrouveCaption("GereAgri", "LC_BtElaguer");
	LC_BtVariante = T->TrouveCaption("CL_Trad", "LC_BtVariante");
	LC_CltAlpha = T->TrouveCaption("GereAgri", "LC_CltAlpha");
	LC_CltAlaDemande = T->TrouveCaption("GereAgri", "LC_CltAlaDemande");

	IniCaption();

}

void __fastcall TGereAgriFrm::BtBnNotesClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="GereAgri";//ne pas traduire
	NoteAgriFrm->Memo->Text=Notes;
	NoteAgriFrm->Caption=Caption;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TGereAgriFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=890;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TGereAgriFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=890;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

