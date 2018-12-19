//-------------+-------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Erreur.h"
#include "CL_Trad.h"
//extern CL_Trad *T;
#include "NoteAgri.h"
#include "Aide.h"

#include "DefZone.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefChProduit"
#pragma link "DefItem"
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefZoneFrm *DefZoneFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TDefZoneFrm::TDefZoneFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefZoneFrm::Personnaliser(void)
{

	LabCatVar->Caption=Categorie->Nom;

	BtBnTva->Visible=false;
	BtBnUnite->Visible=false;

	Grille0->ColCount=3;
	Grille0->Cells[2][0]=T->L_Nom;
//    Grille0->Rows[0]->CommaText=L_Titre;//=".,.,NOM";
	//Grille0->Rows[0]->CommaText=".,.,NOM";
	strcpy(TypeCol,"00T");

	ColNom=2;
	//ColSys=3;
	//ColPrix=6;
	//ColTva=7;

}
//---------------------------------------------------------------------------
void __fastcall TDefZoneFrm::AffItem(int row,CL_Item *item)
{
	LaGrille->Cells[2][row]=item->Nom;

	LaGrille->Objects[0][row]=(TObject*)item;

}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool __fastcall TDefZoneFrm::VerifGrille(TStringGrid *grille)
{
	VerifExistenceNom(grille);
	if(ErreurAAfficher==true)return false;
	else return true;
}
//------------------------------------------------------------------------------
void __fastcall TDefZoneFrm::LireItem(CL_Item *item,int row)
{
	item->Nom=LaGrille->Cells[ColNom][row];
}
//------------------------------------------------------------------------------
void TDefZoneFrm::TexteChaine(void) {
	L_Titre = T->TrouveTexte("DefZoneFrm", "L_Titre");
}
//--------------------------------------------
void TDefZoneFrm::TexteCaption(void) {
	DefZoneFrm->Caption = T->LC_DefZoneFrm;
	BtClasser->Caption = T->LC_BtClasser;
	Grille0->Cells[2][0] = T->L_Nom;

}
//--------------------------------------------
void TDefZoneFrm::IniCaption(void) {
	LC_DefZoneFrm = T->TrouveCaption("CL_Trad", "LC_DefZoneFrm");
}
//--------------------------------------------

void __fastcall TDefZoneFrm::BtBnNotesClick(TObject *Sender)
{
	//020507
	NoteAgriFrm->VientDe="DefZone";//ne pas traduire
	NoteAgriFrm->Categorie=Categorie;
	NoteAgriFrm->Caption=Categorie->Nom;
	NoteAgriFrm->Memo->Text=Categorie->Notes;

	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------

bool __fastcall TDefZoneFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=880;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

