//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "FichierLire.h"

#include "Forme0.h"
#include "Forme00.h"
#include "TriAgri.h"
#include "GereAgri.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "AgriClasst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAgriClasstFrm *AgriClasstFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TAgriClasstFrm::TAgriClasstFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::FormCreate(TObject *Sender)
{
	ChLBCatTypeZoneEstCree=false;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::FormActivate(TObject *Sender)
{
	if(ChLBCatTypeZoneEstCree==false)
	CreerChLBCatTypeZone();
	//cree à la lecture du fichier
//   ChLBCatTypeZone initialisé dans void CL_ES::LireCreeLBCatCritere(void)
	AffGrille();
//    CreeLaGrilleCatTypeZone();
}
//---------------------------------------------------------------------------
void TAgriClasstFrm::CreerChLBCatTypeZone() {
	int n;
	CL_Categorie *categorie;
	ChLBCatTypeZoneEstCree = true;
	for (n = 0; n < V_CatTypeZone->Nbelt; n++) {
		categorie = V_CatTypeZone->Vecteur[n];
		ChLBCatTypeZone->AddItem(categorie->Nom, (TObject*) categorie);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::AffGrille(void)
{
	int c,r,col;
	int i,nCol;
	CL_Categorie *cat;
	CL_Item *item;
	if(ChLBCatTypeZoneEstCree==false)
	CreerChLBCatTypeZone();
	//vide la grille
	Forme00Frm->VideGrille(LaGrille);

	//combien de colonnes
	nCol=CompteColonne();

	LaGrille->ColCount=nCol;
	LaGrille->RowCount=2;

	col=0;
	for(c=0;c<ChLBCatTypeZone->Count;c++)
	{
		if(ChLBCatTypeZone->Checked[c]==false) continue;

		cat=(CL_Categorie*)ChLBCatTypeZone->Items->Objects[c];
		//cat=V_CatTypeZone->Vecteur[c];
		LaGrille->Cells[col][0]=cat->Nom;
		LaGrille->Objects[col][0]=(TObject*)cat;
		r=1;
		for(i=0;i<V_TypeZone->Nbelt;i++)
		{
			item=V_TypeZone->Vecteur[i];
			if(item->Categorie==cat)
			{
				LaGrille->Cells[col][r]=item->Nom;
				LaGrille->Objects[col][r]=(TObject*)item;
				r++;
				if(r > LaGrille->RowCount) LaGrille->RowCount++;
			}
		}
		col++;
	}
}
//---------------------------------------------------------------------------
int __fastcall TAgriClasstFrm::CompteColonne(void)
{
	int c;
	int nCol;
	nCol=0;
	for(c=0;c<ChLBCatTypeZone->Count;c++)
	{
		if(ChLBCatTypeZone->Checked[c]==true)
		nCol++;
	}
	return nCol;
}
//---------------------------------------------------------------------------
//classt CHLB
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::BtClLBClick(TObject *Sender)
{
	int n;
	AnsiString s;
	TObject *object;
	bool checked;
	int delta;
	n=ChLBCatTypeZone->ItemIndex;
	if(n<0) return; //on n'a pas choisi
	if(Sender==BtClHautLB)//Bas
	{
		delta=-1;
		if(n==0) return;
	}
	else if(Sender==BtClBasLB) //Haut
	{
		delta=1;
		if(n>=ChLBCatTypeZone->Count-1) return;
	}
	LabelModifie->Visible=true;

	object=ChLBCatTypeZone->Items->Objects[n];
	ChLBCatTypeZone->Items->Objects[n]=ChLBCatTypeZone->Items->Objects[n+delta];
	ChLBCatTypeZone->Items->Objects[n+delta]=object;

	s=ChLBCatTypeZone->Items->Strings[n];
	ChLBCatTypeZone->Items->Strings[n]=ChLBCatTypeZone->Items->Strings[n+delta];
	ChLBCatTypeZone->Items->Strings[n+delta]=s;

	checked=ChLBCatTypeZone->Checked[n];
	ChLBCatTypeZone->Checked[n]=ChLBCatTypeZone->Checked[n+delta];
	ChLBCatTypeZone->Checked[n+delta]=checked;

	ChLBCatTypeZone->ItemIndex+=delta;

	AffGrille();

}
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::ChLBCatTypeZoneClickCheck(TObject *Sender)
{
	LabelModifie->Visible=true;
	AffGrille();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//classt LaGrille
//---------------------------------------------------------------------------

void __fastcall TAgriClasstFrm::BtBnClLaGrilleClick(TObject *Sender)
{
	int row;
	int col;
	AnsiString s;
	TObject *object;
	int delta;
	LabelModifie->Visible=true;
	row=LaGrille->Row;
	col=LaGrille->Col;
	if(Sender==BtBnClHautLaGrille) //Bas
	{
		delta=-1;
		if(row<=1) return;
	}
	else if(Sender==BtBnClBasLaGrille) //Haut
	{
		delta=1;
		if(LaGrille->Cells[col][row+1].IsEmpty()) return;
	}

	MarquerCell(col,row);

	object=LaGrille->Objects[col][row];
	LaGrille->Objects[col][row]=LaGrille->Objects[col][row+delta];
	LaGrille->Objects[col][row+delta]=object;

	s=LaGrille->Cells[col][row];
	LaGrille->Cells[col][row]=LaGrille->Cells[col][row+delta];
	LaGrille->Cells[col][row+delta]=s;

	LaGrille->Row+=delta;
	MarquerCell(col,row+delta);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::MarquerCell(int c,int r)
{
	TGridRect selection;
	selection.Left=c;
	selection.Right=c;
	selection.Top=r;
	selection.Bottom=r;
	LaGrille->Selection=selection;
}
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::BtBnOkClick(TObject *Sender)
{
	AffGrille();
}
//---------------------------------------------------------------------------

void __fastcall TAgriClasstFrm::BtOKClick(TObject *Sender)
{
	if(LabelModifie->Visible==true)
	{
		Classer();
		if(VientDe=="TriAgri")
		TriAgriFrm->IniEcran();
	}
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TAgriClasstFrm::BtIgnoreClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::Classer(void)
{
	int n;
	int c,r;
	int i;
	int k,crMax;
	int nbElt,noX;
	char cle[50];
	char cleNo[5];
	CL_Categorie *cat;
	CL_Item *critere;
	CL_Agriculteur *agri;
	MapAgri map;
	ItAgri it;
	TList *lstTypeZone;

	/*
	 ofstream outfile("LesCles.txt");
	 TDateTime time;
	 AnsiString date;

	 time=TDateTime::CurrentDateTime();
	 date=time.DateTimeString();
	 outfile << date.c_str() <<endl;
	 */

	lstTypeZone=new TList;
	for(n=0;n<V_TypeZone->Nbelt;n++)
	{
		critere=V_TypeZone->Vecteur[n];
		critere->Flag='z';
		lstTypeZone->Add(critere);
	}
	crMax=ChLBCatTypeZone->Count;
	//cle 0 à crMax les criteres
	// crMax   crMax+1 noAgri
	// crMax+2 crMax+3 noVariante

	//numerote les categories de critère
	for(n=0;n<ChLBCatTypeZone->Count;n++)
	{
		cat=(CL_Categorie*)ChLBCatTypeZone->Items->Objects[n];
		cat->Flag='A'+n;
	}
	//numerote les critères par catégorie
	for(c=0;c<LaGrille->ColCount;)
	{
		for(r=1;r<LaGrille->RowCount;r++)
		{
			critere=(CL_Item*)LaGrille->Objects[c][r];
			if(critere==NULL) break;
			lstTypeZone->Remove(critere);
			critere->Flag='A'+r-1;
		}
		c++;
	}

	for(n=0;n<V_Agriculteur->Nbelt;n++)
	{
		agri=V_Agriculteur->Vecteur[n];
		memset(cle,'z',sizeof(cle));

		for(i=0;i<agri->LstCritere->Count;i++)
		{
			critere=(CL_Item*)agri->LstCritere->Items[i];
			k=critere->Categorie->Flag-'A';
			cle[k]=critere->Flag;
		}
		cle[crMax]=0;
		ES->CleCree(cleNo,agri->No);
		strcat(cle,cleNo);
		ES->CleCree(cleNo,agri->NoVariante);
		strcat(cle,cleNo);
		map[cle]=agri;
//        outfile <<n <<"  " << cle <<endl;
	}

//	outfile <<"_____________________________" <<endl;

	nbElt=V_Agriculteur->Nbelt;
	noX=V_Agriculteur->NoX;

	V_Agriculteur->vide();
	n=0;
	for(it=map.begin();it!=map.end();it++)
	{
		agri=it->second;
//        outfile <<n <<"  " << it->first <<endl;
		V_Agriculteur->insSans(agri);
		n++;
	}
	V_Agriculteur->Nbelt=nbElt;
	V_Agriculteur->NoX=noX;

	nbElt=V_TypeZone->Nbelt;
	noX=V_TypeZone->NoX;
	V_TypeZone->vide();
	for(c=0;c<LaGrille->ColCount;c++)
	{
		for(r=1;r<LaGrille->RowCount;r++)
		{
			critere=(CL_Item*)LaGrille->Objects[c][r];
			if(critere==NULL) break;

			V_TypeZone->insSans(critere);
		}
	}
	for(n=0;n<lstTypeZone->Count;n++)
	{
		critere=(CL_Item*)lstTypeZone->Items[n];
		V_TypeZone->insSans(critere);
	}
	V_TypeZone->Nbelt=nbElt;
	V_TypeZone->NoX=noX;
	delete lstTypeZone;
}
//---------------------------------------------------------------------------
void __fastcall TAgriClasstFrm::ClasserAlpha(void)
{
	int n;
//char cle[50];
//char cleNo[5];
	CL_Agriculteur *agri;

	MapAgri map;
	ItAgri it;
	TStringList *sLst;
	sLst=new TStringList;
	sLst->Sorted=true;
	sLst->Duplicates=dupAccept;
	for(n=0;n<V_Agriculteur->Nbelt;n++)//020211
	{
		agri=V_Agriculteur->Vecteur[n];
		sLst->AddObject(agri->Nom,(TObject*)agri);
//        strncpy(cle,agri->Nom.c_str(),sizeof(cle));
//        ES->CleCree(cleNo,agri->NoVariante);
//		strcat(cle,cleNo);
//        map[cle]=agri;
	}
	V_Agriculteur->vide();
	for(n=0;n<sLst->Count;n++)
	{
		agri=(CL_Agriculteur*)sLst->Objects[n];
		V_Agriculteur->insSans(agri);
	}
	delete sLst;
	/*
	 V_Agriculteur->vide();
	 for(it=map.begin();it!=map.end();it++)
	 {
	 agri=it->second;
	 V_Agriculteur->insSans(agri);
	 }
	 */
}

void TAgriClasstFrm::IniCaption(void) {
	AgriClasstFrm->Caption = LC_AgriClasstFrm;
	CleDeClassif->Caption = LC_CleDeClassif;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	GBOrdreTri->Caption = LC_GBOrdreTri;
}
//--------------------------------------------
void TAgriClasstFrm::TexteCaption(void) {
	LC_AgriClasstFrm = T->TrouveCaption("AgriClasst", "LC_AgriClasstFrm");
	LC_CleDeClassif = T->TrouveCaption("AgriClasst", "LC_CleDeClassif");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_GBOrdreTri = T->TrouveCaption("AgriClasst", "LC_GBOrdreTri");

	IniCaption();
}

bool __fastcall TAgriClasstFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

