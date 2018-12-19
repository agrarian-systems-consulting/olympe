//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <dir.h>
#include <vcl.h>
#include <stdio.h>

#include <grids.hpp>
#include <winbase.h>

using namespace std;

#pragma package(smart_init)

#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Forme00.h"
#include "Indicateur.h"
#include "DefEtatSortie.h"
#include "Resultat.h"
#include "Compilateur.h"
#include "LBCompAgri.h"
#include "AgriSaisieEnum.h"

#include "AgriSaisie.h"
#include "FichierEcrireXml.h"

#include "TVDico.h"
#include "TVDonProcedure.h"
#include "GereProcedure.h"
#include "CL_Procedure.h"
#include "LBSelectionAgri.h"
#include "LBToutAgri.h"
#include "TriAgri.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "DefProcedure.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TDefProcedureFrm *DefProcedureFrm;
extern CL_Xml *Xml;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefProcedureFrm::TDefProcedureFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::FormActivate(TObject *Sender)
{
	CL_Agriculteur *agri;
	if(EstInitialise==false)
	{
		EstInitialise=true;
		Personnaliser();
		DefinirLesGrilles();
		IniGrille(Grille0); // nb col,row, non défilable

		AjoutRow= true;

		LaGrille=LesGrilles[0];

		VAgri.clear();
		if(AgriEnCours==NULL)//151106
		{
			agri=V_Agriculteur->Vecteur[0];
			VAgri.push_back(agri);
		}
		else
		//par défaut
		VAgri.push_back(AgriEnCours);

		RGTraitement->ItemIndex=0;
	}

	if(PClasst->Visible==true)
	{
		BtBnFermClasstClick(this);
		PClasst->Visible=false;
	}
	if(Origine==0) //j'evite d'afficher aprés passage dans TVDonProcedure
	{
		// LabelModifie->Visible=false; défini par l'appel à DefProcedure
		VideLesGrilles();
		Procedure=GereProcedureFrm->Procedure;
		Procedure->Afficher(EdProcedure,EdExe,EdFichier,LaGrille);
	}
	Origine=1;
}
//---------------------------------------------------------------------------
//AffProcedure
//mettre en colonne 0    O ou N si modifiable  elt->Flag
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::AffProcedure(void)
{
	VideGrille(LaGrille);
	LabelModifie->Visible=false;
	Procedure->Afficher(EdProcedure,EdExe,EdFichier,LaGrille);
	LaGrille->Row=1;
}
//---------------------------------------------------------------------------
// Executable Excel ou Autre
//---------------------------------------------------------------------------
// type fichier et verif cohérence *.csv ou *.xml
//---------------------------------------------------------------------------
//definir l'exécutable à lancer
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtExeClick(TObject *Sender)
{
	AnsiString s;
	bool rep;
	LabelModifie->Visible=true;
	rep=OpenDialogExe->Execute();
	if(rep==false) return;

	s=OpenDialogExe->FileName;
	EdExe->Text=s;
}
//---------------------------------------------------------------------------
//definir fichier de transfert
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtFichierClick(TObject *Sender)
{
	AnsiString s;
	bool rep;
	LabelModifie->Visible=true;
	rep=OpenDialogFichier->Execute();
	if(rep==false) return;

	s=OpenDialogFichier->FileName;
	EdFichier->Text=s;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// lancer executable    pour test
//               prévoir choix des agri
//-----------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtBnExecuterClick(TObject *Sender)
{
	int rep;
	AnsiString s;
	if(LabelModifie->Visible==true)
	{
		rep=Verifier();
		if (rep==false) return;
	}
	s=Procedure->AsExe+"   "+Procedure->AsFichier+L_LancerQ;
	//s=Procedure->AsExe+"   "+Procedure->AsFichier+"\n   Je lance ?";
	//rep=MessageBox(Handle,s.c_str(),"Procédure",
	rep=MessageBox(Handle,s.c_str(),L_Procedure.c_str(),
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;
	// choisir agri
	/*
	 c'est reporté dans Procedure->Executer();
	 nTrouve=Procedure->TrouveValeur(AgriEnCours);
	 if(nTrouve==0)
	 {
	 ShowMessage("Pas de données Je NE lance PAS" );
	 return;
	 }
	 */
	Procedure->Executer(VAgri);

}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtBnDicoClick(TObject *Sender)
{
//    TVDonProcedureFrm->CreeTV();  c'est fait dans GereProcedure
	TVDonProcedureFrm->Show();
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Utilitaires
//-----------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::Personnaliser(void)
{
	Grille0->Options>>goAlwaysShowEditor;
	Grille0->Options>>goEditing;
	Grille0->EditorMode=false;
	Grille0->Options<<goDrawFocusSelected;

}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
	LaGrille->ColCount=4;
	LaGrille->RowCount=4;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[] = {128,128,128,128,128,128};

	strcpy(TypeCol, "00000000NNNNNNNNNNNNNNN");
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=0;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	AffEnTete();
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::AffEnTete(void)
{
//int i;
//int col;
	LaGrille->Cells[0][0]=T->L_Nom;
	LaGrille->Cells[1][0]=T->L_Cat;
	LaGrille->Cells[2][0]=T->L_Fam;
	LaGrille->Cells[3][0]=T->L_Nat;
}
//---------------------------------------------------------------------------
//pour eviter message de forme00
//-----------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::VersGrille(TStringGrid *grille)
{
}
//---------------------------------------------------------------------------
// possible de modifier oui/non
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::RGModifiableClick(TObject *Sender)
{
	if(RGModifiable->ItemIndex==0)
	{
		RGModifiable->Color=clRed;
		PossibleModifier(false);
	}
	else
	{
		RGModifiable->Color=clLime;
		PossibleModifier(true);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::PossibleModifier(bool modifiable)
{
	if(modifiable==false)
	{
		RGModifiable->ItemIndex=0;
		RGModifiable->Color=clRed;
		BtClasser->Enabled=false;
		BtExe->Enabled=false;
		BtFichier->Enabled=false;
	}
	else
	{
		RGModifiable->ItemIndex=1;
		RGModifiable->Color=clLime;
		BtClasser->Enabled=true;
		BtExe->Enabled=true;
		BtFichier->Enabled=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::EdExeKeyPress(TObject *Sender, char &Key)
{
	if(RGModifiable->ItemIndex==0) {Key=0; return;}
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtBnVideToutClick(TObject *Sender)
{
	int rep;
	if(RGModifiable->ItemIndex==0) return; //Pas modifiable

	rep=MessageBox(Handle,T->L_SupToutQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	//rep=MessageBox(Handle," Je supprime TOUT Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	if(rep==IDNO) return;

	VideGrille(LaGrille);
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtBnSupClick(TObject *Sender)
{
	int r,r0,c;
	int rep;

	if(RGModifiable->ItemIndex==0) return; //Pas modifiable

	rep=MessageBox(Handle,L_EffQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	//rep=MessageBox(Handle," J'efface cette ligne ?","SUPPRESSION",MB_YESNO);
	if(rep==IDNO) return;

	r0=LaGrille->Row;
	for(r=r0;r<LaGrille->RowCount;r++)
	{
		for(c=0;c<LaGrille->ColCount;c++)
		LaGrille->Cells[c][r]=LaGrille->Cells[c][r+1];
		LaGrille->Objects[0][r]=LaGrille->Objects[0][r+1];
	}

	LaGrille->RowCount--;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	bool rep;
	if(LabelModifie->Visible==false) return;

	rep=Verifier();
	if(rep==false)
	{
		CanClose=false;
		return;
	}
}
//-----------------------------------------------------------------------------
bool __fastcall TDefProcedureFrm::Verifier(void)
{
	int r,n;
	AnsiString s;
	if(EdExe->Text=="")
	{
		ShowMessage(L_PasDExe);
		//ShowMessage("Pas d'Executable Indiqué");
		return false;
	}
	if(EdFichier->Text=="")
	{
		ShowMessage(L_PasFTrf);
		//ShowMessage("Pas de Fichier pour Transférer les Données");
		return false;
	}
	n=0;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		//if(LaGrille->Objects[0][r]==NULL) continue;//prevoir ligne blanche
		if(LaGrille->Cells[0][r]=="") continue;//prevoir ligne blanche
		n++;
	}
	if(n==0)
	{
		ShowMessage(L_JStockPas);
		//ShowMessage("Pas de Données Je ne Stocke rien");
		return true;
	}

	//Procedure->TrouveValeur(AgriEnCours);
	Procedure->LireGrille(EdProcedure,EdExe,EdFichier,LaGrille);
	if(Procedure->Flag=='N')//nouvelle procédure
	{
		Procedure->Flag='E'; //existe
		V_Procedure->ins(Procedure);
		Forme0Frm->CreeTVProcedure(GereProcedureFrm->TV,V_Categorie,V_Procedure);
	}
	//GereProcedureFrm->EcrireXml();
	GereProcedureFrm->EcrireXmlTxt();//effacé le 270306
	return true;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::BtBnSelectionClick(TObject *Sender)
{
	ShowMessage("Sélection");
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::RGTraitementClick(TObject *Sender)
{
	int i;
	CL_Agriculteur *agri;
	if(RGTraitement->ItemIndex==0)
	{
		VAgri.clear();
		VAgri.push_back(AgriEnCours);
	}
	else if(RGTraitement->ItemIndex==1)
	{
		VAgri.clear();
		for(i=0;i<V_Agriculteur->Nbelt;i++)
		{
			agri=V_Agriculteur->Vecteur[i];
			VAgri.push_back(agri);
		}
	}
	else
	{
		VAgri.clear();
		LBSelectionAgriFrm->VientDe="DefProcedure";
		LBSelectionAgriFrm->Show();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::SelectionManuelle(void)
{
	Forme0Frm->CreeLBToutAgri(LBToutAgriFrm->ChLB);
	LBToutAgriFrm->VientDe="DefProcedure";
	LBToutAgriFrm->Show();
//    ShowMessage ("SelectionManuelle");
}
//---------------------------------------------------------------------------
void __fastcall TDefProcedureFrm::SelectionTri(void)
{
	TriAgriFrm->VientDe="DefProcedure";
	TriAgriFrm->Show();
}
//------------------------------------------------------------------------------
void TDefProcedureFrm::ExecuterProcedure(AnsiString nomCatProc,
		AnsiString nomProc, CL_Agriculteur *agri) {
	int n;
	CL_Procedure *proc;
	for (n = 0; n < V_Procedure->Nbelt; n++) {
		proc = V_Procedure->Vecteur[n];
		if (proc->Nom == nomProc && proc->Categorie->Nom == nomCatProc)
			;
		{
			Procedure = proc;
			break;
		}
	}
	VAgri.clear();
	VAgri.push_back(agri);

	Procedure->Executer(VAgri);

}

//---------------------------------------------------------------------------
void TDefProcedureFrm::TexteChaine(void) {
	L_LancerQ = T->TrouveTexte("DefProcedureFrm", "L_LancerQ");
	L_Procedure = T->TrouveTexte("DefProcedureFrm", "L_Procedure");
	L_EffQ = T->TrouveTexte("DefProcedureFrm", "L_EffQ");
	L_PasDExe = T->TrouveTexte("DefProcedureFrm", "L_PasDExe");
	L_PasFTrf = T->TrouveTexte("DefProcedureFrm", "L_PasFTrf");
	L_JStockPas = T->TrouveTexte("DefProcedureFrm", "L_JStockPas");
}
//--------------------------------------------
void TDefProcedureFrm::IniCaption(void) {
	BtExe->Caption = LC_BtExe;
	BtFichier->Caption = LC_BtExe;
	DefProcedureFrm->Caption = LC_DefProcedureFrm;
	BtBnDico->Caption = T->LC_BtDico;
	LabExecutable->Caption = LC_LabExecutable;
	LabFichierTransfert->Caption = LC_LabFichierTransfert;
	BtBnExecuter->Caption = LC_BtBnExecuter;
	RGModifiable->Caption = T->LC_RGModifiable;
	LabProcedure->Caption = T->LC_LabProcedure;
}
//--------------------------------------------
void TDefProcedureFrm::TexteCaption(void) {
	LC_BtExe = T->TrouveCaption("DefProcedure", "LC_BtExe");
	LC_DefProcedureFrm = T->TrouveCaption("DefProcedure", "LC_DefProcedureFrm");
	LC_BtDico = T->TrouveCaption("CL_Trad", "LC_BtDico");
	LC_LabExecutable = T->TrouveCaption("DefProcedure", "LC_LabExecutable");
	LC_LabFichierTransfert = T->TrouveCaption("DefProcedure",
			"LC_LabFichierTransfert");
	LC_BtBnExecuter = T->TrouveCaption("DefProcedure", "LC_BtBnExecuter");
	LC_RGModifiable = T->TrouveCaption("CL_Trad", "LC_RGModifiable");
	LC_LabProcedure = T->TrouveCaption("CL_Trad", "LC_LabProcedure");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TDefProcedureFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

