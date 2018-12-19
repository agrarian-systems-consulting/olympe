//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "TVDico.h"

#include "QRGrille00.h"
#include "Erreur.h"
#include "LBTva.h"
#include "LBSysUnit.h"
#include "NoteAgri.h"
#include "CL_Trad.h"
#include "GereCatItem.h"

#include "Outil.h"
#include "Aide.h"

#include "DefItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TDefItemFrm *DefItemFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
/*
 Forme0	Forme00 Atelier
 DefItem	DefBestiaux
 DefCalendrier
 DefChStruct
 DefEtatSortie
 DefProduit
 DefVariable
 DefZone
 AleaPrix	AleaRdt
 Indicateur
 */
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TDefItemFrm::TDefItemFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
	if (ES->Verrou == MEDTER) {
		BtSup->Enabled = false;
		BtRepBas->Enabled = false;
		BtRecopBas->Enabled = false;
		BtBnVideTout->Enabled = false;
		BtBnNote->Enabled = false;
		BtBnUnite->Enabled = false;
		BtBnTva->Enabled = false;
	}

}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::FormActivate(TObject *Sender)
{
	AnsiString as;
	as=GereCatItemFrm->L_Impo;
	if(Origine==0)
	{
		Origine=1; //0;//1;
		ErreurAAfficher=false;
		GrilleX=1;
		LesGrilles[0]=Grille0;
		LaGrille=Grille0;
		Personnaliser();
		VideGrille(Grille0);
		IniGrille(Grille0);
		VersGrille(Grille0);
	}
	if(Categorie) //si pas de Categorie eg Calendrier DefXX se charge de l'affichage
	{
//		LabCatVar->Caption=Categorie->Nom;
//	    VideGrille(Grille0);
//	    VersGrille(Grille0);
	}
}
//---------------------------------------------------------------------------
//a personnaliser
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::Personnaliser(void)
{
}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::IniGrille(TStringGrid *grille)
{
	int c;
	int largeur[]= {20,10,128,64,64,64,96,64,64,64,64,64,64,64,64,64};

	Grille0->Width=0;
	for(c=0;c<Grille0->ColCount;c++)
	{
		Grille0->ColWidths[c]=largeur[c];
		Grille0->Width+=largeur[c];
	}
	Grille0->Width+=30; //place pour l'ascenseur
	Grille0->FixedCols=2;
	Grille0->FixedRows=1;
	AjoutRow=true;

}
//---------------------------------------------------------------------------
/// Remplit la grille avec les données de l'item
///     utilise fonction ad hoc AffItem...(row,item)
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	AnsiString value;
	CL_Item *item;
	int nLigne=0;
	if(V_Item==NULL)
	return;
	// nb ligne de la grille
	for( r=0;r<V_Item->Nbelt;r++)
	{
		item=V_Item->Vecteur[r];
		if(item->Categorie!=Categorie) continue;
		nLigne++;
	}
	grille->RowCount=nLigne+3;
	LaGrille=grille;
	row=1;
	for( r=0;r<V_Item->Nbelt;r++)
	{
		item=V_Item->Vecteur[r];
		item->Flag='O'; //Flag =O est d'origine peut devenir M si modifié N pour nouveau
		if(item->Categorie!=Categorie) continue;
		grille->Objects[0][row]=(TObject*)item;

		grille->Cells[0][row]=row;
		AffItem (row,item);
		if(item->Supprimable==false) grille->Cells[1][row]='*';
		row++;
	}
	CellInitiale(2,1);
}

//---------------------------------------------------------------------------
//a personnaliser
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::AffItem(int row,CL_Item *item)
{
	ShowMessage("AffItem nON défini");
}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_Item* item;
	int rep;
	char buf[100];
	item=(CL_Item*)LaGrille->Objects[0][r];
	if(item==NULL) return;
	SelLigne();
	if(item->Supprimable==false)
	{
		ShowMessage(T->L_Utilise); //=" UTILISE ");
		//ShowMessage(" UTILISE ");
		DeSelLigne();
		return;
	}
	sprintf(buf,T->L_SupQ.c_str(),item->Nom.c_str() );
	//sprintf(buf," Je supprime %s \n Vous êtes sur ?",item->Nom.c_str() );
	rep=MessageBox(Handle,buf,T->L_SupT.c_str(),MB_YESNO);
	//rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		item->Flag='S';
		SupprimerLigne();
		LabelModifie->Visible=true;
	}
	DeSelLigne();
}
//---------------------------------------------------------------------------
//Commun   il y a problème
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::FormResize(TObject *Sender)
{
	/*
	 int h,hauteur;
	 hauteur=DefItemFrm->Height;
	 //696 480 largeur et hauteur de la fenetre
	 h=hauteur-Panell->Height-PanHaut->Height-LaGrille->Top-30;     // 30 ??
	 LaGrille->Height= h;
	 Repaint();
	 */
}
//---------------------------------------------------------------------------
// si on est en col 2   existence d'un nom
// 						absence de doublon
// new item si nécessaire
//Commun   sauf bestiaux
//---------------------------------------------------------------------------
bool __fastcall TDefItemFrm::ControleCell(int col,int row)
{
	AnsiString pasDeNom("??????");
	CL_Item* item;
	int colNom=2;
	if(RowVide(row)==true )return true;

	item=(CL_Item*)LaGrille->Objects[0][row];
	/// nom
	if(col==colNom)
	if(NomCorrect(col,row)==false)return false;

	if(item==NULL)
	{
		item=new CL_Item;
		item->Flag='N';
		item->Supprimable=true;
		item->Categorie=Categorie;
		item->NoCategorie=Categorie->No;
		LaGrille->Objects[0][row]=(TObject*)item;
		LaGrille->Cells[0][row]=row;
	}
	else if(item->Flag!='N')
	item->Flag='M';

	item->Nom=LaGrille->Cells[2][row];
	return true;
}
//------------------------------------------------------------------------------
//Commun
//------------------------------------------------------------------------------
bool __fastcall TDefItemFrm::NomCorrect(int col,int row)
{
	AnsiString pasDeNom("??????");
	char chaine[100];

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
	return true;
}
//------------------------------------------------------------------------------
// existence d'un nom sur chaque ligne
//Commun
//------------------------------------------------------------------------------
void __fastcall TDefItemFrm::VerifExistenceNom(TStringGrid *grille)
{
	int row;
	char buf[100];
	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		// existence d'un nom et pas de doublon
		if(grille->Cells[2][row].IsEmpty()==true)
		{
			wsprintf(buf,"Pas de Nom ligne %d ",row);
			ErreurFrm->Edit->Lines->Add(buf);
			ErreurAAfficher=true;
		}
	}
}
//------------------------------------------------------------------------------
// à personnaliser éventuellement
//------------------------------------------------------------------------------
bool __fastcall TDefItemFrm::VerifGrille(TStringGrid *grille)
{
	VerifExistenceNom(grille);
	if(ErreurAAfficher==true)
	{
		ErreurFrm->Show();
		return false;
	}
	else return true;
}
//------------------------------------------------------------------------------
//Commun   sauf defBestiaux  050105
//------------------------------------------------------------------------------
void __fastcall TDefItemFrm::DeGrille(TStringGrid *grille)
{
	int row;
	AnsiString value;
	CL_Item *item;
	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		item=(CL_Item*)grille->Objects[0][row];
		switch(item->Flag)
		{
			case 'O':
			case 'M': //modifié
			item->Nom=grille->Cells[2][row];
			break;
			case 'N'://nouveau
			item->Nom =grille->Cells[2][row];
			item->Categorie=Categorie;
			item->NoCategorie=Categorie->No;
			V_Item->ins(item);
			break;
		}
		LireItem(item,row);
	}
	for(int i=0;i<V_Item->Nbelt;i++)
	{
		item=V_Item->Vecteur[i];
		if(item->Flag=='S') {V_Item->sup(item);i--;}
	}
}
//------------------------------------------------------------------------------
void __fastcall TDefItemFrm::LireItem(CL_Item *item,int row)
{
	ShowMessage("LireItem NonDéfini");
}
//------------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm:: StockerOrdre(CL_Vecteur<CL_Item> *vecteur)
{
	int i,j;
	int pos=0;
	CL_Item *item,*item0;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		item=(CL_Item*)LaGrille->Objects[0][r];
		for(j=pos;j<vecteur->Nbelt;j++)
		{
			item0=vecteur->Vecteur[j];
			if(item0->Categorie!=item->Categorie)continue;

			vecteur->Vecteur[j]=(CL_Item*)LaGrille->Objects[0][r];
			pos=j+1;
			break;
		}
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtBnVideToutClick(TObject *Sender)
{
	int r;
	int repMB;
	bool ilYaModif;
	CL_Item *item;
	repMB=MessageBox(Handle,"j'efface tous les éléments INUTILISES ?","NETTOYER",MB_YESNO|MB_ICONQUESTION);
	if(repMB==IDNO) return;

	ilYaModif=false;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		item=(CL_Item*)LaGrille->Objects[0][r];
		if(item==NULL) continue;

		if(item->Supprimable!=false) V_Item->sup(item);
		ilYaModif=true;
	}
	if(ilYaModif==false) return;

	VideGrille(LaGrille);
	VersGrille(LaGrille);
	//VersGrille (via CellInitiale) a mis LabelModif à false
	LabelModifie->Visible=true;

}
//------------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if(LBSysUnitFrm->Visible==true)LBSysUnitFrm->Close();
	if(LBTvaFrm->Visible==true)LBTvaFrm->Close();
	DerniereCell();
	if(LabelModifie->Visible==false)return;

	if(VerifGrille(LaGrille)==false)
	{
		CanClose=false;
		if(ErreurAAfficher==true)
		{
			ErreurFrm->Show();
			CanClose=false;
		}
		return;
	}
	rep=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
			//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
			MB_YESNOCANCEL|MB_ICONEXCLAMATION);
	if(rep==ID_YES)
	{
		DeGrille(LaGrille);
		if(OrdreModif==true) StockerOrdre(V_Item);

		ES->ecrireFichier();
		LabelModifie->Visible=false;
	}
	else
	{
		VideGrille(LaGrille);
		VersGrille(LaGrille);
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtBnStockerClick(TObject *Sender)
{
	bool canClose=false;
	FormCloseQuery(this,canClose);
}
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtBnNoteClick(TObject *Sender)
{
	NoteAgriFrm->VientDe="DefItem";
	NoteAgriFrm->Categorie=Categorie;
	NoteAgriFrm->Caption=Categorie->Nom;
	NoteAgriFrm->Memo->Text=Categorie->Notes;
	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtBnImpClick(TObject *Sender)
{
	if(TVDicoFrm->Visible==true)TVDicoFrm->Close();
	QRGrille00Frm->LaGrille=LaGrille;
	QRGrille00Frm->TitreEtat->Caption=Caption + " : " +LabCatVar->Caption; //Categorie->Nom;
	QRGrille00Frm->TypeCol=TypeCol;
	QRGrille00Frm->Initialise();
	QRGrille00Frm->QR->Preview();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::RepBasPrix(AnsiString prix,int colPrix)
{
	int r;
	for(r=LaGrille->Row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(RepPossible(colPrix,r)==false ) continue;
		LaGrille->Cells[colPrix][r]=prix;
	}
}

//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::RepBasTva(CL_Tva *tva)
{
	int r;
	if(tva==NULL) return;
	for(r=LaGrille->Row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(RepPossible(ColTva,r)==false ) continue;
		LaGrille->Objects[ColTva][r]=(TObject*)tva;
		LaGrille->Cells[ColTva][r]=tva->Nom;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::RepBasSysUnite(CL_SystemeUnite *sysUnite)
{
	int r;
	if(sysUnite==NULL) return;
	for(r=LaGrille->Row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(RepPossible(ColSys,r)==false ) continue;

		LaGrille->Objects[ColSys][r]=(TObject*)sysUnite;

		LaGrille->Cells[ColSys] [r]=sysUnite->UUt;
		LaGrille->Cells[ColSys+1][r]=sysUnite->UTrans;
		LaGrille->Cells[ColSys+2][r]=sysUnite->UGlobal;
	}
}

//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtRepBasClick(TObject *Sender)
{
	ShowMessage("BtRepBasClick oubli");
}
//---------------------------------------------------------------------------

void __fastcall TDefItemFrm::BtRecopBasClick(TObject *Sender)
{
	ShowMessage("BtRecopBasClick oubli");
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtClHautClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
	TObject *object,*obTva,*obSys;
	LabelModifie->Visible=true;
	OrdreModif=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row<=1) return;

	object=LaGrille->Objects[0][row];
	LaGrille->Objects[0][row]=LaGrille->Objects[0][row-1];
	LaGrille->Objects[0][row-1]=object;

	obTva=LaGrille->Objects[ColTva][row];
	LaGrille->Objects[ColTva][row]=LaGrille->Objects[ColTva][row-1];
	LaGrille->Objects[ColTva][row-1]=obTva;

	obSys=LaGrille->Objects[ColSys][row];
	LaGrille->Objects[ColSys][row]=LaGrille->Objects[ColSys][row-1];
	LaGrille->Objects[ColSys][row-1]=obSys;

	for(c=0;c<cX;c++)
	{
		s=LaGrille->Cells[c][row];
		LaGrille->Cells[c][row]=LaGrille->Cells[c][row-1];
		LaGrille->Cells[c][row-1]=s;
	}
	LaGrille->Cells[0][row-1] =row-1;
	LaGrille->Cells[0][row] =row;
	MarquerLigne(row-1);
//    PosClasst();
}
//---------------------------------------------------------------------------
void __fastcall TDefItemFrm::BtClBasClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
	TObject *object,*obTva,*obSys;

	LabelModifie->Visible=true;
	OrdreModif=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row>=LaGrille->RowCount-1) return;

	object=LaGrille->Objects[0][row];
	LaGrille->Objects[0][row]=LaGrille->Objects[0][row+1];
	LaGrille->Objects[0][row+1]=object;
	if(ColTva)
	{
		obTva=LaGrille->Objects[ColTva][row];
		LaGrille->Objects[ColTva][row]=LaGrille->Objects[ColTva][row+1];
		LaGrille->Objects[ColTva][row+1]=obTva;
	}
	if(ColSys)
	{
		obSys=LaGrille->Objects[ColSys][row];
		LaGrille->Objects[ColSys][row]=LaGrille->Objects[ColSys][row+1];
		LaGrille->Objects[ColSys][row+1]=obSys;
	}
	for(c=0;c<cX;c++)
	{
		s=LaGrille->Cells[c][row];
		LaGrille->Cells[c][row]=LaGrille->Cells[c][row+1];
		LaGrille->Cells[c][row+1]=s;
	}
	LaGrille->Cells[0][row] =row;
	LaGrille->Cells[0][row+1]=row+1;

	MarquerLigne(row+1);
//    PosClasst();
}
//---------------------------------------------------------------------------
void TDefItemFrm::Francais(void) {
//    L_Utilise=       " UTILISE ";
//    L_SupQ=          " Je supprime %s \n Vous êtes sur ?";
//	L_Sup=           "SUPPRESSION";
//    L_PasDeNom=      " %s row=%d Pas de nom";

}
//---------------------------------------------------------------------------
void TDefItemFrm::Anglais(void) {
//    L_Utilise=       " USED ";
//    L_SupQ=          " I delete %s \n Are you sure?";
//	L_Sup=           "DELETION";
//    L_PasDeNom=      " %s row=%d No name";

}
//--------------------------------------------
void TDefItemFrm::IniCaption(void) {
	LabCatVar->Caption = T->LC_RGCat;
	DefItemFrm->Caption = LC_DefItemFrm;
	BtBnTva->Caption = T->LC_BtBnTva;
	BtBnUnite->Caption = T->LC_BtBnUnite;

	BtClasser->Caption = T->LC_BtClasser; //090206
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtBnUnite->Caption = T->LC_BtBnUnite;
	BtBnTva->Caption = T->LC_BtBnTva;

}
//--------------------------------------------
void TDefItemFrm::TexteCaption(void) {
	LC_RGCat = T->TrouveCaption("CL_Trad", "LC_RGCat");
	LC_DefItemFrm = T->TrouveCaption("DefItem", "LC_DefItemFrm");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");
	LC_BtBnUnite = T->TrouveCaption("CL_Trad", "LC_BtBnUnite");

	IniCaption();

}
//--------------------------------------------
//110907

void __fastcall TDefItemFrm::BtBnVersExcelClick(TObject *Sender)
{
	OutilFrm->VersExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
}
//---------------------------------------------------------------------------

void __fastcall TDefItemFrm::BtBnDExcelClick(TObject *Sender)
{
	OutilFrm->DExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
	LabelModifie->Visible==true;

}
//---------------------------------------------------------------------------

bool __fastcall TDefItemFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

