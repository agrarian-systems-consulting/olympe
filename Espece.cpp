//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
//#include "Brouillon.h"
#include "Erreur.h"
#include "GereEspece.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"
#include "Main.h"

#include "Espece.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SysUnite"
#pragma resource "*.dfm"
TEspeceFrm *EspeceFrm;
// Les extern
extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TEspeceFrm::TEspeceFrm(TComponent* Owner) :
		TSysUniteFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TEspeceFrm::FormCreate(TObject *Sender)
{
	Notes="";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// FONCTIONS A PERSONNALISER
//----------------------------------------------------------------------------
void __fastcall TEspeceFrm::Personnaliser(void)
{
//pour l'impression
// N_PHASE phases=14 cf olympe.dec
	TitreGrille=LabForme->Caption;
//0123456789012345678
//     12345678901234
	strcpy(TypeCol,"00TNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
}
//---------------------------------------------------------------------------
void __fastcall TEspeceFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
}
//-----------------------------------------------------------------------------
void __fastcall TEspeceFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int i,c;
	//     |         |1  2  3  4  5  6  7  8  9 10 11 12 13 14
	// 0  1  2   3   4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
//int largeur[]={ 20,10,128,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
	int largeur[50];

//  col 0 n°ligne
//      1  supprimable
//      2  debut amortissement
//      3  durée de vie
//      4 à 10 phases

	largeur[0]= 20;
	largeur[1]= 10;
	largeur[2]= 128;
	for(c=3;c<50;c++)largeur[c]= 32;
	largeur[3]= 64;
	if(ES->Version<=130)//060208
	grille->ColCount=19;
	else
	grille->ColCount=45;//19;
	grille->FixedCols=2;
	grille->FixedRows=1;

//largeur première colonne            //largeur standard =64 pixels
	for(c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	grille->Width=l+25; //place pour l'ascenseur

	// attention col row
//    grille->Rows[0]->CommaText=L_Titre;

	grille->Rows[0]->CommaText=".,.,ESPECE,Deb_Amor,Maxi,1,2,3,4,5,6,7,8,9,10,11,12,13,14";
	grille->Cells[2][0]=L_Espece;//110907
	grille->Cells[3][0]=L_DebAmor;
	grille->Cells[4][0]=L_Maxi;

	for(i=1,c=5;i<N_PHASE+1;i++,c++)grille->Cells[c][0]=i;
	AjoutRow=true;
	CellAVerifier=true;
}
//---------------------------------------------------------------------------
bool __fastcall TEspeceFrm::ControleCell(int col,int row)
{
	AnsiString value;
	AnsiString pasDeNom("??????");
	CL_Espece *espece;

	if(RowVide(row)==true )return true;

	// nouveau ou modifié ?
	espece=(CL_Espece*)LaGrille->Objects[0][row];
	if(espece==NULL)
	{
		espece=new CL_Espece();
		espece->Supprimable=true;
		espece->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)espece;
		LaGrille->Cells[0][row]=row;
		LaGrille->RowCount++;
	}
	else if(espece->Flag!='N')
	espece->Flag='M';
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TEspeceFrm::VersGrille(TStringGrid *grille)
{
	int row,r,c,col;
	AnsiString value;
	CL_Espece* espece;
	CL_Vecteur<CL_Espece> *vecteur;

	vecteur=V_Espece;
	grille->RowCount=vecteur->Nbelt+3;
	for( r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		espece=vecteur->Vecteur[r];
		espece->Flag='O';
		grille->Objects[0][row]=(TObject*)espece;
		grille->Cells[0][row]=row;
		if(espece->Supprimable==false) grille->Cells[1][row]='*';
		grille->Cells[2][row]=espece->Nom;
		grille->Cells[3][row]=Aff(espece->DebAmor);
		grille->Cells[4][row]=Aff(espece->DurAmor);
		for(c=0,col=5;c<N_PHASE;c++,col++) //a voir
		{
			if(espece->Phase[c]==0) break;
			grille->Cells[col][row]=Aff(espece->Phase[c]);
		}
	}
	CellInitiale(2,1);
}
//---------------------------------------------------------------------------
void __fastcall TEspeceFrm::CellDebut(void)
{
	ColM[0]=2;
	RowM[0]=1;
	ValueAvant=LaGrille->Cells[ColM[0]][RowM[0]]; //la grille est vide ->bug

}

//------------------------------------------------------------------------------
void __fastcall TEspeceFrm::DeGrille(TStringGrid *grille)
{
	int row;
	CL_Espece *espece;
	CL_Vecteur<CL_Espece> *vecteur;

	vecteur=V_Espece;

	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		espece=(CL_Espece*)grille->Objects[0][row];

		switch(espece->Flag)
		{
			case 'O': //origine
//                break;      //050208
			case 'M'://modifié
			VersEspece(row,espece);
			break;
			case 'N'://nouveau
			VersEspece(row,espece);
			vecteur->ins(espece);
			espece->Flag='M';//
		}
	}
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		espece=vecteur->Vecteur[i];
		if(espece->Flag=='S') {vecteur->sup(espece);i--;}
	}
}
//------------------------------------------------------------------------------
void __fastcall TEspeceFrm::VersEspece(int row,CL_Espece *espece)
{
	int p,c;
	espece->Nom =LaGrille->Cells[2][row];
	//espece->DebAmor=LaGrille->Cells[3][row].ToDouble();
	//espece->MaxAn  =LaGrille->Cells[4][row].ToDouble();
	espece->DebAmor=GrilleFloat(3,row);
	espece->DurAmor=GrilleFloat(4,row);
	for(p=0,c=5;p<N_PHASE;p++,c++)
	{
		if (LaGrille->Cells[c][row].IsEmpty()==true)
		{
			espece->Phase[p]=0;
			break;
		}
		//espece->Phase[p]=LaGrille->Cells[c][row].ToDouble();
		espece->Phase[p]=GrilleFloat(c,row);

	}
	for(p=0;p<N_PHASE;p++)
	{
		if (espece->Phase[p]==0 )
		break;
	}
	espece->NbPhase=p;
}
//-----------------------------------------------------------------------------
void __fastcall TEspeceFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_Espece* espece;
	int rep;
	espece=(CL_Espece*)LaGrille->Objects[0][r];
	if(espece==NULL) return;
	SelLigne();
	if(espece->Supprimable==false)
	{
		ShowMessage(L_Util); //" UTILISE ");
		DeSelLigne();
		return;
	}
	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	//rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		espece->Flag='S';
		SupprimerLigne();
	}
	DeSelLigne();

}
//---------------------------------------------------------------------------
// a mettre dan qr???
/*
 //---------------------------------------------------------------------------

 void __fastcall TEspeceFrm::BtBnImpClick(TObject *Sender)
 {
 int i;

 CL_Espece *espece;
 if(V_Espece->Nbelt<=0)return;

 FBrouillon->Demarre();
 FBrouillon->Blanc();
 FBrouillon->Titre1("LES PHASES de PRODUCTION");
 FBrouillon->EnTeteEspece(clBlack);
 for(i=0;i<V_Espece->Nbelt;i++)
 {
 espece=V_Espece->Vecteur[i];
 FBrouillon->Espece(espece,clBlack);
 }
 FBrouillon->Blanc();
 FBrouillon->Show();

 }
 */
//---------------------------------------------------------------------------
//                            Stocker
void __fastcall TEspeceFrm::BtBnStockerClick(TObject *Sender)
{
	Stocker();
}
//---------------------------------------------------------------------------
bool __fastcall TEspeceFrm::Stocker(void)
{
	bool correct=true;
	char buf[100];
	int p,c;
	int calendrier[N_PHASE];
	int n;

	ErreurFrm->Edit->Clear();
	DerniereCell();
	if(LabelModifie->Visible==false) return true;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(LaGrille->Cells[2][r].IsEmpty()==true)
		{
			correct=false;
			wsprintf(buf,L_PasEsp.c_str(),r);
			//wsprintf(buf,"Pas de Nom d'Espèces ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(LaGrille->Cells[3][r].IsEmpty()==true)
		{
			correct=false;
			wsprintf(buf,L_PasAm.c_str(),r);
			wsprintf(buf,"Pas de Debut d'Amortissement ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(LaGrille->Cells[4][r].IsEmpty()==true)
		{
			LaGrille->Cells[4][r]="100";
			wsprintf(buf,L_Dur100.c_str(),r);
			//wsprintf(buf,"Maximum de vie mis à 100 ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		// pas de zero en phase 0
		n=GrilleInt(5,r);
		if (n!=1 )
		{
			wsprintf(buf,L_MisA1.c_str(),r);
			//wsprintf(buf,"  0 aberrant  pour la Phase 1 Mis A 1",r);
			LaGrille->Cells[5][r]="1";
			ErreurFrm->Edit->Lines->Add(buf);
		}
		// coherence des phases
		for(p=0,c=5;p<N_PHASE;p++,c++)
		{
			if (LaGrille->Cells[c][r].IsEmpty()==true)
			{
				calendrier[p]=0;
				break;
			}
			//calendrier[p]=LaGrille->Cells[c][r].ToDouble();
			calendrier[p]=GrilleFloat(c,r);
		}
		for(p=1;p<N_PHASE;p++)
		{
			if(calendrier[p]==0) break;
			if(calendrier[p]<=calendrier[p-1] )
			{
				correct=false;
				wsprintf(buf,L_Incoherent.c_str(),r);
				//wsprintf(buf,"Incohérence dans les phases ligne %d ",r);
				ErreurFrm->Edit->Lines->Add(buf);
			}
		}
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
		ES->ecrireFichier();
		LabelModifie->Visible=false;
		if(GereEspeceFrm->Visible==true)
		GereEspeceFrm->RetourDeDefEspece();
		return true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TEspeceFrm::BoutImpEcranClick(TObject *Sender)
{
//TBitmap *image = GetFormImage();

}
//---------------------------------------------------------------------------
void TEspeceFrm::TexteChaine(void) {
	L_Titre = T->TrouveTexte("EspeceFrm", "L_Titre");
	L_Util = T->TrouveTexte("EspeceFrm", "L_Util");
	L_PasEsp = T->TrouveTexte("EspeceFrm", "L_PasEsp");
	L_PasAm = T->TrouveTexte("EspeceFrm", "L_PasAm");
	L_Dur100 = T->TrouveTexte("EspeceFrm", "L_Dur100");
	L_MisA1 = T->TrouveTexte("EspeceFrm", "L_MisA1");
	L_Incoherent = T->TrouveTexte("EspeceFrm", "L_Incoherent");
	L_Espece = T->TrouveTexte("EspeceFrm", "L_Espece");
	L_DebAmor = T->TrouveTexte("EspeceFrm", "L_DebAmor");
	L_Maxi = T->TrouveTexte("EspeceFrm", "L_Maxi");
}
//--------------------------------------------
void TEspeceFrm::IniCaption(void) {
	EspeceFrm->Caption = T->LC_EspeceFrm;
	LabForme->Caption = LC_LabForme;
	LabPhase->Caption = LC_LabForme;

	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
	Grille0->Cells[2][0] = L_Espece; //110907
	Grille0->Cells[3][0] = L_DebAmor;
	Grille0->Cells[4][0] = L_Maxi;

}
//--------------------------------------------
void TEspeceFrm::TexteCaption(void) {
	LC_EspeceFrm = T->TrouveCaption("CL_Trad", "LC_EspeceFrm");
	LC_LabForme = T->TrouveCaption("Espece", "LC_LabForme");

	IniCaption();

}

//---------------------------------------------------------------------------
void __fastcall TEspeceFrm::BtBnNotesClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="Espece";//ne pas traduire
	NoteAgriFrm->Memo->Text=Notes;
	NoteAgriFrm->Caption=Caption;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TEspeceFrm::BtBn123Click(TObject *Sender)
{
	int c,c0,cMax;
	int n;
	int r;
	int rep;

	rep=MessageBox(Handle,"Années 1 2 3 etc.."," Créer ?",MB_YESNO|MB_ICONQUESTION);
	if(rep==IDNO)
	return;
	r=Grille0->Row;
	c0=5;
	if(ES->Version<=130) cMax= 19;
	else cMax=Grille0->ColCount;
	for(c=c0,n=1;c<cMax;c++,n++) //050208
	Grille0->Cells[c][r]=n;
	LabelModifie->Visible=true;//050208
//
}
//---------------------------------------------------------------------------

void __fastcall TEspeceFrm::BtBnMazClick(TObject *Sender)
{
	int c,c0;
	int n;
	int r;

	r=Grille0->Row;
	c0=Grille0->Col;
	for(c=c0,n=1;c<Grille0->ColCount;c++,n++)
	Grille0->Cells[c][r]="";
	LabelModifie->Visible=true; //050208

}
//---------------------------------------------------------------------------

bool __fastcall TEspeceFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=530;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

