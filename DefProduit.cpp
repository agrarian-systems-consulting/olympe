//---------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Erreur.h"
#include "LBTva.h"
#include "LBSysUnit.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "DefProduit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefProduitFrm *DefProduitFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefProduitFrm::TDefProduitFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefProduitFrm::Personnaliser(void)
{
	LabCatVar->Caption=Categorie->Nom;
	BtBnTva->Visible=true;
	BtBnUnite->Visible=true;
	Grille0->ColCount=8;
	Grille0->Rows[0]->CommaText=L_Titre;
	//Grille0->Rows[0]->CommaText=".,.,NOM,U.Atelier,U.Entreprise,U.Région,Prix/U.Ent,Tva";
	switch(ES->Verrou)
	{
		case SANS: strcpy(TypeCol,"00T000N0");
		break;
		case MEDTER: strcpy(TypeCol,"00000000");
		BtBnUnite->Enabled=false;
		BtBnTva->Enabled=false;
		break;
	}
	TitreGrille=Caption+" ; "+Categorie->Nom;
	ColNom=2;
	ColSys=3;
	ColPrix=6;
	ColTva=7;
}
//---------------------------------------------------------------------------
void __fastcall TDefProduitFrm::AffItem(int row,CL_Item *item)
{
	LaGrille->Cells[ColNom][row]=item->Nom;

	LaGrille->Cells[ColSys][row]=item->SysUnite->UUt;
	LaGrille->Cells[ColSys+1][row]=item->SysUnite->UTrans;
	LaGrille->Cells[ColSys+2][row]=item->SysUnite->UGlobal;

	LaGrille->Cells[ColPrix][row]=Aff(item->Prix,2);
	LaGrille->Cells[ColTva][row]=item->Tva->Nom;

	LaGrille->Objects[0][row]=(TObject*)item;
	LaGrille->Objects[ColTva][row]=(TObject*)item->Tva;
	LaGrille->Objects[ColSys][row]=(TObject*)item->SysUnite;

}

// A verifier ????
//---------------------------------------------------------------------------
bool __fastcall TDefProduitFrm::ControleCell(int col,int row)
{
	AnsiString pasDeNom("??????");
	CL_Item* item;
	char chaine[100];
	float prix;
//int colPrix;     colPrix=6;
	if(RowVide(row)==true )return true;

	item=(CL_Item*)LaGrille->Objects[0][row];
/// nom
	if(col==2)
	{
		if(LaGrille->Cells[2][row].IsEmpty()
				||pasDeNom.AnsiCompare(LaGrille->Cells[2][row])==0)
		{
			sprintf(chaine,T->L_PasDeNom.c_str(),LaGrille->Name.c_str(),row);
			//sprintf(chaine," %s row=%d Pas de nom",LaGrille->Name.c_str(),row);
			ShowMessage(chaine);
			LaGrille->Row=row;
			LaGrille->Col=2;
			LaGrille->Cells[2][row]=pasDeNom;
			return false;
		}
		else if(Doublon(LaGrille,2,row)==true) return false;
	}
	if(col==ColPrix)
	{
		if(item->SysUnite==SysMonnaie)
		{
			prix=GrilleFloat(ColPrix,row);
			if(prix!=1)
			{
				MessageBox(Handle,L_UnParDef.c_str(),T->L_Erreur.c_str(),MB_OK);
				//MessageBox(Handle,"1 Par définition !! Impossible de changer la monnaie","ERREUR",MB_OK);
				LaGrille->Cells[6][row]=1;//200802
				return false;
			}
		}
	}

	if(item==NULL)
	{
		item=new CL_Item;
		item->Flag='N';
		item->Supprimable=true;
		item->Categorie=Categorie;
		item->NoCategorie=Categorie->No;
		LaGrille->Objects[0][row]=(TObject*)item;
		LaGrille->Cells[0][row]=row;
		GrilleModif[LaGrille->Tag]=true;
	}
	else if(item->Flag!='N')
	item->Flag='M';

	item->Nom=LaGrille->Cells[2][row];
	return true;
}
//------------------------------------------------------------------------------
void __fastcall TDefProduitFrm::BtBnTvaClick(TObject *Sender)
{
	LBTvaFrm->AppelePar="DefProduitFrm";
	LBTvaFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TDefProduitFrm::RetourDeChoixTva (CL_Tva *tva)
{
	int row;
	CL_Item *item;
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

//---------------------------------------------------------------------------
void __fastcall TDefProduitFrm::BtBnUniteClick(TObject *Sender)
{
	LBSysUnitFrm->AppelePar="DefProduitFrm";
	LBSysUnitFrm->Show();
}
//---------------------------------------------------------------------------
/// le choix a été fait LBSysUnit
/// sur LBClick il appelle RetourDeChoixUnite
//---------------------------------------------------------------------------
void __fastcall TDefProduitFrm::RetourDeChoixUnite(CL_SystemeUnite *sysUnit)
{
	int row;
	CL_Item *item;
	row=LaGrille->Row;
	item=(CL_Item*)LaGrille->Objects[0][row];
	if(item==NULL)
	{
		ShowMessage(T->L_NonDef);
		//ShowMessage("Elément non défini");
		return;
	}
	item->SysUnite=sysUnit;
	LaGrille->Objects[ColSys][row]=(TObject*)sysUnit;

	LaGrille->Cells[ColSys] [row]=sysUnit->UUt;
	LaGrille->Cells[ColSys+1][row]=sysUnit->UTrans;
	LaGrille->Cells[ColSys+2][row]=sysUnit->UGlobal;

	if(sysUnit==SysMonnaie)
	LaGrille->Cells[ColPrix][row]=1; //200802

}
//------------------------------------------------------------------------------
void __fastcall TDefProduitFrm::BtRepBasClick(TObject *Sender)
{
	int row,col;
	CL_SystemeUnite *sysUnit;
	AnsiString prix;
	CL_Item *item;
	CL_Tva *tva;
	row=LaGrille->Row;
	col=LaGrille->Col;
	item=(CL_Item*)LaGrille->Objects[0][row];

	if(item==NULL) return;
	if(col==ColSys||col==ColSys+1||col==ColSys+2)
	{
		sysUnit=(CL_SystemeUnite*)LaGrille->Objects[ColSys][row];
		RepBasSysUnite(sysUnit);
	}
	else if(col==ColPrix)
	{
		prix=LaGrille->Cells[col][row];
		RepBasPrix(prix,ColPrix);
	}
	else if(col==ColTva)
	{
		tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
		RepBasTva(tva);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefProduitFrm::BtRecopBasClick(TObject *Sender)
{
	int row,col;
	CL_SystemeUnite *sysUnit;
	AnsiString prix;
	CL_Item *item;
	CL_Tva *tva;

	row=LaGrille->Row;
	col=LaGrille->Col;
	item=(CL_Item*)LaGrille->Objects[0][row];
	if(item==NULL) return;

	col=ColSys;
	sysUnit=(CL_SystemeUnite*)LaGrille->Objects[ColSys][row];
	RepBasSysUnite(sysUnit);

	col=ColPrix;
	prix=LaGrille->Cells[col][row];
	RepBasPrix(prix,ColPrix);

	col=ColTva;
	tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
	RepBasTva(tva);

}
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool __fastcall TDefProduitFrm::VerifGrille(TStringGrid *grille)
{
	int row;
	char buf[100];
	CL_Tva *tva;
	CL_SystemeUnite *sysUnite;
	float prix;

	VerifExistenceNom(grille);
	ErreurAAfficher=false;
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
		if(sysUnite==SysMonnaie)
		{
			prix=GrilleFloat(ColPrix,row);
			if(prix!=1)
			{
				ErreurAAfficher=true;
				wsprintf(buf,L_PrixEg1.c_str(),row);
				//wsprintf(buf,"prix=1 Par définition ligne %d  ",row);
				LaGrille->Cells[6][row]=1;//200802
				ErreurFrm->Edit->Lines->Add(buf);
			}
		}

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
void __fastcall TDefProduitFrm::LireItem(CL_Item *item,int row)
{
	item->Nom=LaGrille->Cells[ColNom][row];

	item->Tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
	item->NoTva=item->Tva->No;

	item->SysUnite=(CL_SystemeUnite*)LaGrille->Objects[ColSys][row];
	item->NoSysteme=item->SysUnite->No;

	item->Prix=GrilleFloat(ColPrix,row);

}
//------------------------------------------------------------------------------
void TDefProduitFrm::TexteChaine(void) {
	L_Titre = T->TrouveTexte("DefProduitFrm", "L_Titre");
	L_PrixEg1 = T->TrouveTexte("DefProduitFrm", "L_PrixEg1");
	L_UnParDef = T->TrouveTexte("DefProduitFrm", "L_UnParDef");

}
//--------------------------------------------
void TDefProduitFrm::IniCaption(void) {
	DefProduitFrm->Caption = LC_DefProduitFrm;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
	BtBnUnite->Caption = T->LC_BtBnUnite;
	BtBnTva->Caption = T->LC_BtBnTva;
}
//--------------------------------------------
void TDefProduitFrm::TexteCaption(void) {
	LC_DefProduitFrm = T->TrouveCaption("DefProduit", "LC_DefProduitFrm");

	IniCaption();

}
//--------------------------------------------

void __fastcall TDefProduitFrm::BtBnNoteClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="DefProduit";//ne pas traduire
	NoteAgriFrm->Categorie=Categorie;
	NoteAgriFrm->Caption=Categorie->Nom;
	NoteAgriFrm->Memo->Text=Categorie->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TDefProduitFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp = false;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

