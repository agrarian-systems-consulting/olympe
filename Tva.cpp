//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
#include "Erreur.h"
#include "ReClasse.h"
#include "CL_Trad.h"
#include "NoteAgri.h"

#include "Aide.h"
#include "Tva.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TTvaFrm *TvaFrm;
// Les extern
extern CL_ES *ES;
extern CL_Trad *T;

/* TODO : pret pour import d'excel */

//---------------------------------------------------------------------------
__fastcall TTvaFrm::TTvaFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TTvaFrm::FormCreate(TObject *Sender)
{
//020507
	Notes="";
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------/////// Boutons /////////////////////////////////////////////////////////////
/////// Boutons /////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//                            Stocker
void __fastcall TTvaFrm::BtBnStockerClick(TObject *Sender)
{
	Stocker();
}
//---------------------------------------------------------------------------
void __fastcall TTvaFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_Tva* tva;
	int rep;
	tva=(CL_Tva*)LaGrille->Objects[0][r];
	if(tva==NULL) return;
	SelLigne();
	if(tva!= NULL && tva->Supprimable==false)
	{
		ShowMessage(LC_Utilise); //" UTILISE ");
		DeSelLigne();
		return;
	}
//	rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDYES)
	{
		if(tva!=NULL) tva->Flag='S';
		SupprimerLigne();
	}
	DeSelLigne();
}
//---------------------------------------------------------------------------
//vide Inutilisé
//---------------------------------------------------------------------------
void __fastcall TTvaFrm::BtBnVideToutClick(TObject *Sender)
{
	int r;
	int rep;
	bool ilYaModif;
	CL_Tva* item;
//    rep=MessageBox(Handle,"j'efface tous les éléments INUTILISES ?","NETTOYER",MB_YESNO|MB_ICONQUESTION);
	rep=MessageBox(Handle,LC_Jefface.c_str(),LC_Nettoyer.c_str(),MB_YESNO|MB_ICONQUESTION);
	if(rep==IDNO) return;

	ilYaModif=false;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		item=(CL_Tva*)LaGrille->Objects[0][r];
		if(item==NULL) continue;

		if(item->Supprimable!=false) V_Tva->sup(item);
		ilYaModif=true;
	}
	if(ilYaModif==false) return;

	VideGrille(LaGrille);
	VersGrille(LaGrille);
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
 //---------------------------------------------------------------------------
 void __fastcall TTvaFrm::BtBnImpClick(TObject *Sender)
 {
 CL_Tva *tva;
 if(V_Tva->Nbelt<=0)return;

 FBrouillon->Demarre();
 FBrouillon->Blanc();
 FBrouillon->Titre1("LES TVA");
 FBrouillon->EnTeteTva();
 for(int i=0;i<V_Tva->Nbelt;i++)
 {
 tva=V_Tva->Vecteur[i];
 FBrouillon->Tva(tva);
 }
 FBrouillon->Blanc();
 FBrouillon->Show();
 }
 */
///////////// 1 ////////////////////////////////////////////////////////////
///////////// 1 ////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// FONCTIONS A PERSONNALISER
//----------------------------------------------------------------------------
void __fastcall TTvaFrm::Personnaliser(void)
{
//pour l'impression
	TitreGrille=Caption;
	strcpy(TypeCol,"00TNT");
}
//---------------------------------------------------------------------------
void __fastcall TTvaFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
}
//-----------------------------------------------------------------------------
void __fastcall TTvaFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[]= {20,10,64,64};
	int c;
	grille->ColCount =4;
	grille->FixedCols=2;
	grille->FixedRows=1;

	for(c=0;c<4;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	grille->Width=l+25; //place pour l'ascenseur

	// attention col row
	grille->Cells[2][0]=LC_Nom;//"Nom";
	grille->Cells[3][0]=LC_Taux;//"Taux";
	AjoutRow=true;
	CellAVerifier=true;
}
//------------------------------------------------------------------------------
void __fastcall TTvaFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	AnsiString value;
	CL_Tva *tva;
	CL_Vecteur<CL_Tva> *vecteur;
	vecteur=V_Tva;
	grille->RowCount=vecteur->Nbelt+3;
	for( r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		tva=vecteur->Vecteur[r];
		tva->Flag='O';
		grille->Objects[0][row]=(TObject*)tva;
		grille->Cells[0][row]=row;
		if(tva->Supprimable==false) grille->Cells[1][row]='*';
		grille->Cells[2][row]=tva->Nom;
		if(tva->Taux==0) grille->Cells[3][row]="     0";
		else grille->Cells[3][row]=Aff(tva->Taux,2);
	}
	IniCB();
	CellInitiale(2,1);

}
//---------------------------------------------------------------------------

void __fastcall TTvaFrm::GBDefautEnter(TObject *Sender)
{
	IniCB();
}
//---------------------------------------------------------------------------
void __fastcall TTvaFrm::IniCB(void)
{
	int i;
	CL_Tva *tva;
	CBDefaut->Clear();
	CBImmo->Clear();
	for(i=0;i<V_Tva->Nbelt;i++)
	{
		tva=V_Tva->Vecteur[i];
		CBDefaut->Items->AddObject(tva->Nom,(TObject*)tva);
		CBImmo->Items->AddObject(tva->Nom,(TObject*)tva);
		if(tva==TvaDefaut)CBDefaut->ItemIndex=i;
		if(tva==TvaImmo) CBImmo->ItemIndex=i;
	}
}
//-----------------------------------------------------------------------------
//void  __fastcall TTvaFrm::CellDebut(void)
//cf Forme00
//---------------------------------------------------------------------------
//void  __fastcall TTvaFrm::SaisirCell(int col,int row)
//cf Forme00
///////////// 2 ////////////////////////////////////////////////////////////
///////////// 2 ////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
bool __fastcall TTvaFrm::ControleCell(int col,int row)
{
	AnsiString value;
	AnsiString pasDeNom("??????");
	CL_Tva *tva;

	if(RowVide(row)==true )return true;

	// nouveau ou modifié ?
	LabelModifie->Visible=true;
	tva=(CL_Tva*)LaGrille->Objects[0][row];
	if(tva==NULL)
	{
		tva=new CL_Tva();
		tva->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)tva;
		LaGrille->Cells[0][row]=row;
	}
	else if(tva->Flag!='N')
	tva->Flag='M';
	return true;
}
//------------------------------------------------------------------------------
void __fastcall TTvaFrm::DeGrille(TStringGrid *grille)
{
	int row;
	CL_Tva *tva;
	CL_Vecteur<CL_Tva> *vecteur;
//char chaine[100];

	vecteur=V_Tva;
	LaGrille=grille;
	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		tva=(CL_Tva*)grille->Objects[0][row];
		switch(tva->Flag)
		{
			case 'N': //nouveau
			vecteur->ins(tva);
//                break;
			case 'O'://origine
			case 'M'://modifie
			tva->Nom =grille->Cells[2][row];
			tva->Taux =GrilleFloat(3,row);
			break;
		}
		tva->Flag='O';
	}
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		tva=vecteur->Vecteur[i];
		if(tva->Flag=='S') {vecteur->sup(tva);i--;}
	}
}
//----------------------------------------------------------------------------
void __fastcall TTvaFrm::ImpTva(void)
{
}
//---------------------------------------------------------------------------
bool __fastcall TTvaFrm::Stocker(void)
{
	bool correct=true;
	char buf[100];
	ErreurFrm->Edit->Clear();

//    g=LaGrille->Tag;
	DerniereCell();
	if(LabelModifie->Visible==false)

	if(LabelModifie->Visible==false) return true;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(CellVide(2,r))
		{
			correct=false;
			//wsprintf(buf,"Pas de Nom %d ",r);
			wsprintf(buf,"%s  %d ",LC_PasNom.c_str(),r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(3,r))
		{
			correct=false;
			//wsprintf(buf,"Pas de Taux",r);
			wsprintf(buf,"%s  %d ",LC_PasTaux.c_str(),r);
			ErreurFrm->Edit->Lines->Add(buf);
		}

	}
	if(TvaDefaut==NULL)
	{
		correct=false;
		//wsprintf(buf,"Pas de TVA par defaut");
		wsprintf(buf,"%s ",LC_PasTvaDefaut.c_str());
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(TvaImmo==NULL)
	{
		correct=false;
		//wsprintf(buf,"Pas de TVA pour les immo");
		wsprintf(buf,"%s ",LC_PasTvaImmo.c_str());
		ErreurFrm->Edit->Lines->Add(buf);
	}
//.......................
	if(correct==false)
	{
		ErreurFrm->Show();
		return false;
	}
	else
	{
		DeGrille(LaGrille);
		if(OrdreModif==true) StockerOrdre(V_Tva);
		ES->ecrireFichier();
		LabelModifie->Visible=false;
		return true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTvaFrm:: StockerOrdre(CL_Vecteur<CL_Tva> *vecteur)
{
	int i,r;
	i=0;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_Tva*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------

void __fastcall TTvaFrm::CBDefautClick(TObject *Sender)
{
	int n;
	n=CBDefaut->ItemIndex;
	TvaDefaut=(CL_Tva*)CBDefaut->Items->Objects[n];
	TvaDefaut->Supprimable=false;
}
//---------------------------------------------------------------------------

void __fastcall TTvaFrm::CBImmoClick(TObject *Sender)
{
	int n;
	n=CBImmo->ItemIndex;
	TvaImmo=(CL_Tva*)CBImmo->Items->Objects[n];
	TvaImmo->Supprimable=false;
}
//--------------------------------------------
void TTvaFrm::IniCaption(void) {

	LabImmo->Caption = T->LC_Immo;
	GBDefaut->Caption = LC_GBDefaut;
	TvaFrm->Caption = T->LC_BtBnTva;
	LabTva->Caption = T->LC_BtBnTva;
	BtClasser->Caption = T->LC_BtClasser; //070206

}
//--------------------------------------------
void TTvaFrm::TexteCaption(void) {
	LC_Immo = T->TrouveCaption("CL_Trad", "LC_Immo");
	LC_GBDefaut = T->TrouveCaption("Tva", "LC_GBDefaut");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");
	//correction rapide ce devrait etre dans un TexteChaine
	// creer aussi IniTexte
	LC_Jefface = T->TrouveCaption("Tva", "LC_Jefface");
	LC_Nettoyer = T->TrouveCaption("Tva", "LC_Nettoyer");
	LC_PasNom = T->TrouveCaption("Tva", "LC_PasNom");
	LC_PasTaux = T->TrouveCaption("Tva", "LC_PasTaux");
	LC_PasTvaDefaut = T->TrouveCaption("Tva", "LC_PasTvaDefaut");
	LC_PasTvaImmo = T->TrouveCaption("Tva", "LC_PasTvaImmo");
	LC_Nom = T->TrouveCaption("Tva", "LC_Nom");
	LC_Taux = T->TrouveCaption("Tva", "LC_Taux");
	LC_Utilise = T->TrouveCaption("Tva", "LC_Utilise");

	IniCaption();
}
//--------------------------------------------
//020507
void __fastcall TTvaFrm::BtBnNotesClick(TObject *Sender)
{
//
	NoteAgriFrm->VientDe="Tva";//ne pas traduire
	NoteAgriFrm->Memo->Text=Notes;
	NoteAgriFrm->Caption=Caption;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TTvaFrm::FormHelp(WORD Command, int Data, bool &CallHelp)
{
	CallHelp = false;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

