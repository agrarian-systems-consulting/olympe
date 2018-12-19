//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "LBTva.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "DefChProduit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TDefChProduitFrm *DefChProduitFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefChProduitFrm::TDefChProduitFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::FormActivate(TObject *Sender)
{
	GrilleX=1;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
	Personnaliser();
	IniGrille(Grille0);
	VersGrille(Grille0);
}
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::Personnaliser(void)
{
	V_Item=V_ChStruct;
	V_Categorie=V_CatChStruct;
	Categorie=V_CatChStruct->Vecteur[0];
	LabCatVar->Caption=Categorie->Nom;
	Caption="Charges de Structure";
	Grille0->ColCount=4;
	Grille0->Rows[0]->CommaText=".,.,NOM,Tva";
	strcpy(TypeCol,"00TTTT");
	ColTva=3;
}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::IniGrille(TStringGrid *grille)
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
void __fastcall TDefChProduitFrm::VersGrille(TStringGrid *grille)
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
		if(item->Categorie!=Categorie) continue;
		item->Flag='O';
		grille->Objects[0][row]=(TObject*)item;

		grille->Cells[0][row]=row;
		if(item->Supprimable==false) grille->Cells[1][row]='*';
		AffItem (row,item);
		row++;
	}
	CellInitiale(2,1);
}

//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::AffItem(int row,CL_Item *item)
{
	LaGrille->Cells[2][row]=item->Nom;
	LaGrille->Cells[3][row]=item->Tva->Nom;
}
//---------------------------------------------------------------------------
///appelle LBTva
/// en indiquant qui l'appelle AppelePar=
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::BtTvaClick(TObject *Sender)
{
	LBTvaFrm->AppelePar="Categorie";
	LBTvaFrm->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/// le choix a été fait LBTva
/// sur LBClick il appelle RetourDeChoixTva
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::RetourDeChoixTva (CL_Tva *tva)
{
//n'est pas accessible pour EXTPOS
	int row;
	CL_Item* item;

	row=LaGrille->Row;
	item=(CL_Item*)LaGrille->Objects[0][row];
	if(item==NULL)
	{
		item=new CL_Item;
		item->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)item;
		LaGrille->Cells[0][row]=row;
	}

	item->NoTva=tva->No;
	item->Tva=tva;

	LaGrille->Cells[ColTva][row]=tva->Nom;
}
//---------------------------------------------------------------------------
//Commun
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::BtSupClick(TObject *Sender)
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
		ShowMessage(" UTILISE ");
		DeSelLigne();
		return;
	}
	sprintf(buf," Je supprime %s \n Vous êtes sur ?",item->Nom.c_str() );
	rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		item->Flag='S';
		SupprimerLigne();
		LabelModifie->Visible=true;
	}
	DeSelLigne();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/// appelle fonction ad hoc pour faire le report bas
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::BtRepBasClick(TObject *Sender)
{
	int row,col;
	AnsiString prix;
	CL_Item *item;
	row=LaGrille->Row;
	col=LaGrille->Col;
	item=(CL_Item*)LaGrille->Objects[0][row];

	if(item==NULL) return;
	if(col!=ColTva) return;
	RepBasTva(item,ColTva);
}
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::RepBasTva(CL_Item *item,int colTva)
{
	int r;
	CL_Tva *tva;
	if(item->Tva==NULL) return;
	tva=item->Tva;
	for(r=LaGrille->Row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(RepPossible(colTva,r)==false ) continue;

		item=(CL_Item*)LaGrille->Objects[0][r];

		item->Tva=tva;
		item->NoTva=tva->No;
		LaGrille->Cells[colTva][r]=tva->Nom;
	}
}
//---------------------------------------------------------------------------
//Commun   il y a problème
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::FormResize(TObject *Sender)
{
	int h,hauteur;
	hauteur=DefChProduitFrm->Height;
	//696 480 largeur et hauteur de la fenetre
	h=hauteur-Panell->Height-PanHaut->Height-LaGrille->Top-30;// 30 ??
	LaGrille->Height= h;
	Repaint();
}
//---------------------------------------------------------------------------
// si on est en col 2   existence d'un nom
// 						absence de doublon
// new item si nécessaire
//Commun
//---------------------------------------------------------------------------
bool __fastcall TDefChProduitFrm::ControleCell(int col,int row)
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
bool __fastcall TDefChProduitFrm::NomCorrect(int col,int row)
{
	AnsiString pasDeNom("??????");
	char chaine[100];

	if(LaGrille->Cells[2][row].IsEmpty()
			||pasDeNom.AnsiCompare(LaGrille->Cells[2][row])==0)
	{
		sprintf(chaine," %s row=%d Pas de nom",LaGrille->Name.c_str(),row);
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
// ajoute tva si nécessaire
//Commun
//------------------------------------------------------------------------------
bool __fastcall TDefChProduitFrm::VerifGrille(TStringGrid *grille)
{
	int row;
	AnsiString value;
	CL_Item *item;
	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		// existence d'un nom et pas de doublon
		if(ControleCell(2,row)==false) return false;
		item=(CL_Item*)grille->Objects[0][row];
		if(item->Tva==NULL)
		{
			item->Tva=TvaDefaut;
		}
	}
	return true;
}
//------------------------------------------------------------------------------
//Commun
//------------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::DeGrille(TStringGrid *grille)
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
	}
	for(int i=0;i<V_Item->Nbelt;i++)
	{
		item=V_Item->Vecteur[i];
		if(item->Flag=='S') {V_Item->sup(item);i--;}
	}
}

//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm:: StockerOrdre(CL_Vecteur<CL_Item> *vecteur)
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
void __fastcall TDefChProduitFrm::BtBnVideToutClick(TObject *Sender)
{
	int r;
	int repMB;
	bool ilYaModif;
	CL_Item *item;
	repMB=MessageBox(Handle,"j'efface tous les éléments INUTILISES ?","EFFACER TOUT LE TABLEAU",MB_YESNO|MB_ICONQUESTION);
	if(repMB==IDNO) return;

	ilYaModif=false;
	for(r=0;r<LaGrille->RowCount;r++)
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
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	DerniereCell();
	if(LabelModifie->Visible==false)return;
	if(VerifGrille(LaGrille)==false)
	{
		CanClose=false;
		return;
	}
	DeGrille(LaGrille);
	if(OrdreModif==true) StockerOrdre(V_Item);

	ES->ecrireFichier();
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TDefChProduitFrm::BtBnStockerClick(TObject *Sender)
{
	bool canClose=false;
	FormCloseQuery(this,canClose);
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TDefChProduitFrm::IniCaption(void) {
	/*
	 LabMonnaie->Caption=LC_LabMonnaie;
	 GBMonnaie->Caption=LC_GBMonnaie;
	 SysUniteFrm->Caption=LC_SysUniteFrm;
	 LabForme->Caption=T->LC_LBSysUnitFrm;
	 */
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
}
//--------------------------------------------
void TDefChProduitFrm::TexteCaption(void) {
	IniCaption();

}

bool __fastcall TDefChProduitFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp = false;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

