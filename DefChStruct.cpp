//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "CL_Trad.h"

#include "LBTva.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "DefChStruct.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefChStructFrm *DefChStructFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefChStructFrm::TDefChStructFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TDefChStructFrm::Personnaliser(void)
{
	LabCatVar->Caption=Categorie->Nom;

	BtBnTva->Visible=true;
	BtBnUnite->Visible=false;
//	V_Categorie=V_CatChStruct;  211006
	Grille0->ColCount=4;
	Grille0->Rows[0]->CommaText=L_Titre;//=".,.,NOM,Tva";
	//Grille0->Rows[0]->CommaText=".,.,NOM,Tva";
	switch(ES->Verrou)
	{
		case SANS: strcpy(TypeCol,"00TTTT");break;

		case MEDTER: strcpy(TypeCol,"00000000");
		BtBnUnite->Enabled=false;
		BtBnTva->Enabled=false;
		break;
	}

	ColNom=2;
	ColTva=3;

	//ColSys=;
	//ColPrix=;
}
//---------------------------------------------------------------------------
void __fastcall TDefChStructFrm::AffItem(int row,CL_Item *item)
{
	LaGrille->Cells[ColNom][row]=item->Nom;
	LaGrille->Cells[ColTva][row]=item->Tva->Nom;

	LaGrille->Objects[0][row]=(TObject*)item;
	LaGrille->Objects[ColTva][row]=(TObject*)item->Tva;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefChStructFrm::BtBnTvaClick(TObject *Sender)
{
	LBTvaFrm->AppelePar="DefChStructFrm";
	LBTvaFrm->Show();
}
//---------------------------------------------------------------------------
/// le choix a été fait LBTva
/// sur LBClick il appelle RetourDeChoixTva
//---------------------------------------------------------------------------
void __fastcall TDefChStructFrm::RetourDeChoixTva (CL_Tva *tva)
{
	int row;
	CL_Item* item;
	row=LaGrille->Row;

	item=(CL_Item*)LaGrille->Objects[0][row];
	if(item==NULL)
	{
		ShowMessage(T->L_NonDef);
		//ShowMessage("Elément non défini");
		return;
	}

	LaGrille->Objects[ColTva][row]=(TObject*)tva;

	LaGrille->Cells[ColTva][row]=tva->Nom;
}
//---------------------------------------------------------------------------
/// appelle fonction ad hoc pour faire le report bas
//---------------------------------------------------------------------------
void __fastcall TDefChStructFrm::BtRepBasClick(TObject *Sender)
{
	int row,col;
	CL_Item *item;
	CL_Tva *tva;
	row=LaGrille->Row;
	col=LaGrille->Col;
	item=(CL_Item*)LaGrille->Objects[0][row];

	if(item==NULL) return;
	if(col!=ColTva) return;

	tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
	RepBasTva(tva);
}
//------------------------------------------------------------------------------
bool __fastcall TDefChStructFrm::VerifGrille(TStringGrid *grille)
{
	int row;
	AnsiString value;
	CL_Tva *tva;

	VerifExistenceNom(grille);

	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
		if(tva==NULL)
		{
			LaGrille->Objects[ColTva][row]=(TObject*)TvaDefaut;
			LaGrille->Cells[ColTva][row]=TvaDefaut->Nom;
		}
	}
	if(ErreurAAfficher==true)return false;
	else return true;
}
//---------------------------------------------------------------------------

//------------------------------------------------------------------------------
void __fastcall TDefChStructFrm::LireItem(CL_Item *item,int row)
{
	item->Nom=LaGrille->Cells[ColNom][row];

	item->Tva=(CL_Tva*)LaGrille->Objects[ColTva][row];

	item->NoTva=item->Tva->No;
}
//------------------------------------------------------------------------------
void TDefChStructFrm::TexteChaine(void) {
	L_Titre = T->TrouveTexte("DefChStructFrm", "L_Titre");
}
//--------------------------------------------
void TDefChStructFrm::IniCaption(void) {
	DefChStructFrm->Caption = LC_DefChStructFrm;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
	BtBnTva->Caption = T->LC_BtBnTva;
	BtBnUnite->Caption = T->LC_BtBnUnite;
}
//--------------------------------------------
void TDefChStructFrm::TexteCaption(void) {
	LC_DefChStructFrm = T->TrouveCaption("DefChStruct", "LC_DefChStructFrm");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");
	LC_BtBnUnite = T->TrouveCaption("CL_Trad", "LC_BtBnUnite");

	IniCaption();

}
//--------------------------------------------

void __fastcall TDefChStructFrm::BtBnNoteClick(TObject *Sender)
{
//
	NoteAgriFrm->VientDe="DefChStruct";//ne pas traduire
	NoteAgriFrm->Categorie=Categorie;
	NoteAgriFrm->Caption=Categorie->Nom;
	NoteAgriFrm->Memo->Text=Categorie->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TDefChStructFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
//    HelpContext=0;  voir 
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

