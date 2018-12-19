//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "Erreur.h"
#include "LBSysUnit.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "DefVariable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefVariableFrm *DefVariableFrm;

extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefVariableFrm::TDefVariableFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefVariableFrm::Personnaliser(void)
{
	LabCatVar->Caption=Categorie->Nom;
//	Caption="Variables";

	BtBnTva->Visible=false;
	BtBnUnite->Visible=true;

	Grille0->ColCount=6;
	Grille0->Rows[0]->CommaText=L_Titre;
//Grille0->Rows[0]->CommaText=".,.,NOM,U.Atelier,U.Entreprise,U.Region";
	strcpy(TypeCol,"00T000");

	ColNom=2;
	ColSys=3;
	ColPrix=0;
	ColTva=0;

}
//---------------------------------------------------------------------------
void __fastcall TDefVariableFrm::AffItem(int row,CL_Item *item)
{
	LaGrille->Cells[2][row]=item->Nom; //030105
	if(item->SysUnite)
	{
		LaGrille->Cells[ColSys][row]=item->SysUnite->UUt;
		LaGrille->Cells[ColSys+1][row]=item->SysUnite->UTrans;
		LaGrille->Cells[ColSys+2][row]=item->SysUnite->UGlobal;
	}
	LaGrille->Objects[0][row]=(TObject*)item;
	if(item->SysUnite)
	LaGrille->Objects[ColSys][row]=(TObject*)item->SysUnite;
}
//---------------------------------------------------------------------------
void __fastcall TDefVariableFrm::BtBnUniteClick(TObject *Sender)
{
	LBSysUnitFrm->AppelePar="DefVariableFrm";
	LBSysUnitFrm->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/// le choix a été fait LBSysUnit
/// sur LBClick il appelle RetourDeChoixUnite
//---------------------------------------------------------------------------
void __fastcall TDefVariableFrm::RetourDeChoixUnite(CL_SystemeUnite *sysUnit)
{
	CL_Item* item;
	int row;

	row=LaGrille->Row;
	item=(CL_Item*)LaGrille->Objects[0][row];

	if(item==NULL)
	{
		ShowMessage(T->L_NonDef);
		//ShowMessage("Elément non défini");
		return;
	}
	LabelModifie->Visible=true;
	LaGrille->Objects[ColSys][row]=(TObject*)sysUnit;
	item->SysUnite=sysUnit;
	item->NoSysteme=sysUnit->No;
	LaGrille->Cells[ColSys] [row]=sysUnit->UUt;
	LaGrille->Cells[ColSys+1][row]=sysUnit->UTrans;
	LaGrille->Cells[ColSys+2][row]=sysUnit->UGlobal;
}
//------------------------------------------------------------------------------
void __fastcall TDefVariableFrm::BtRepBasClick(TObject *Sender)
{
	int row,col;
	CL_Item *item;
	CL_SystemeUnite *sysUnit;
	row=LaGrille->Row;
	col=LaGrille->Col;
	item=(CL_Item*)LaGrille->Objects[0][row];

	if(item==NULL) return;
	if(col==ColSys||col==ColSys+1||col==ColSys+2)
	{
		sysUnit=(CL_SystemeUnite*)LaGrille->Objects[ColSys][row];
		RepBasSysUnite(sysUnit);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefVariableFrm::BtRecopBasClick(TObject *Sender)
{
	BtRepBasClick(this);
}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool __fastcall TDefVariableFrm::VerifGrille(TStringGrid *grille)
{
	int row;
	char buf[100];
	AnsiString value;
	CL_SystemeUnite *sysUnite;

	VerifExistenceNom(grille);

	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		sysUnite=(CL_SystemeUnite*)LaGrille->Objects[ColSys][row];

		if(sysUnite==NULL)
		{
			ErreurAAfficher=true;
			wsprintf(buf,T->L_PasUnite.c_str(),row);
			//wsprintf(buf,"Pas d'unité ligne %d ",row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	if(ErreurAAfficher==true)return false;
	else return true;
}

//------------------------------------------------------------------------------
void __fastcall TDefVariableFrm::LireItem(CL_Item *item,int row)
{

	item->Nom=LaGrille->Cells[ColNom][row];
	item->SysUnite=(CL_SystemeUnite*)LaGrille->Objects[ColSys][row];

}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
void TDefVariableFrm::TexteChaine(void) {
	L_Titre = T->TrouveTexte("DefVariableFrm", "L_Titre");
}
//--------------------------------------------
void TDefVariableFrm::IniCaption(void) {
	DefVariableFrm->Caption = T->LC_VARIABLES;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
	BtBnUnite->Caption = T->LC_BtBnUnite;
}
//--------------------------------------------
void TDefVariableFrm::TexteCaption(void) {
	LC_VARIABLES = T->TrouveCaption("CL_Trad", "LC_VARIABLES");
	LC_BtBnUnite = T->TrouveCaption("CL_Trad", "LC_BtBnUnite");
	IniCaption();
}

//---------------------------------------------------------------------------
void __fastcall TDefVariableFrm::BtBnNoteClick(TObject *Sender)
{
//
	NoteAgriFrm->VientDe="DefVariable";//ne pas traduire
	NoteAgriFrm->Categorie=Categorie;
	NoteAgriFrm->Caption=Categorie->Nom;
	NoteAgriFrm->Memo->Text=Categorie->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TDefVariableFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
//    HelpContext=0;     voir GereCatVariable
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

