//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Brouillon.h"
#include "Indicateur.h"
#include "OlympeDec.h"
//#include "Graph.h"111002
#include "QRGrille00.h"
#include "CL_SousPeriode.h"
#include "CL_BesTravAtelier.h"
#include "ResGraph.h"
#include "CL_Trad.h"
#include "TresoGraph.h"  //170512

#include "Forme01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TForme01Frm *Forme01Frm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TForme01Frm::TForme01Frm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// METHODES A CREER
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::Personnaliser(void)
{
// chgt couleur
// interdiction de modifier contenu
	Grille0->Options>>goAlwaysShowEditor;
	Grille0->Options>>goEditing;
	Grille0->EditorMode=false;
	Grille0->Options<<goDrawFocusSelected;
//modif non visible et à gauche pour pouvoir dimensionner la fenêtre
	LabelModifie->Visible=false;
	LabelModifie->Left=0;

	AjoutRow=false;
	CellAVerifier=false;

}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
void __fastcall TForme01Frm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::IniGrille(TStringGrid *grille)
{
//evite message de Forme00
}
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::VersGrille(TStringGrid *grille)
{
//evite message de Forme00
}
//nbCol sans la colonne du titre
//nbRow sans la ligne de titre
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::IniGrilleStandard(AnsiString titre,int nbCol,
		int nbElt,int an_0)
{
	int l=0;
	int largeur[20];
	int c;
	int an;
	int hauteur;
	RGPrecision->Visible=true;
	hauteur=LaGrille->RowHeights[0];
	LaGrille->RowCount= nbElt+2; //dont titre
	LaGrille->ColCount= nbCol+1;
	LaGrille->FixedCols=1;
	LaGrille->FixedRows=1;

	largeur[0]=128;
	for(c=1;c<nbCol+1;c++)largeur[c]=64;

	for(c=0;c<nbCol+1;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}

	Width=l+25+10;
//    Height=hauteur+hauteur*(nbElt+2)+PanHaut->Height+Panell->Height+20;
	Height=hauteur+hauteur*(nbElt+2)+Panell->Height+20;
	if(Height>600) Height=600;
	LaGrille->Width=l+25;//place pour l'ascenseur
	LaGrille->Height=hauteur*(nbElt+2)+10;

	if(nbCol>N_X) Width=LaGrille->Width+50;

//	AjoutRow=false;
//    CellAVerifier=false;
//    LabelModifie->Visible=false;
	Forme01Frm->Caption=titre;
	LaGrille->Cells[0][0]="Nom";

	an=an_0;
	if(nbCol>N_X) an=an_0-1;
	for(c=0;c<nbCol+1;c++,an++)
	LaGrille->Cells[c+1][0]="  "+AnsiString(an);
	LaGrille->Row=1;
}
// titre à supprimer ?
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::IniGrilleTreso(AnsiString titre,int QouV,
		int nbElt,int an_0,int mois_0)
{
	int l=0;
	int largeur[20];
	int c,cDeb;
	int m,an;
	int hauteur;
	TDateTime date;
	RGPrecision->Visible=true;
	hauteur=LaGrille->DefaultRowHeight; //RowHeights[0]; 180515
	LaGrille->RowCount= nbElt+3;//dont titre
	BtBnMoin12->Visible=true;//170512
	BtBnPlus12->Visible=true;
	if(QouV==VALEUR)
	{
		Caption="Valeurs";
		LaGrille->ColCount= 12+1; //12 mois + nom item
		LaGrille->FixedCols=1;
		cDeb=1;
	}
	else //QUANTITE
	{
		Caption="Quantités";
		LaGrille->ColCount= 12+1+1; //id°+unité
		LaGrille->FixedCols=1;//2;
		cDeb=2;
		largeur[1]=32;
	}
	LaGrille->FixedRows=1;

	largeur[0]=128;
	for(c=cDeb;c<cDeb+12;c++)largeur[c]=64;

	for(c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}

	Width=l+25+10;
	LaGrille->Width=l+25; //place pour l'ascenseur
//test
//int x=nbElt+4;
//int h=hauteur*x+10;
	LaGrille->Height=hauteur*(nbElt+4)+10;//180512
//    Height=LaGrille->Height+Panell->Height+20;
//    Height=LaGrille->Height+61;//180512
	Height=hauteur*(nbElt+4)+10+200;//180512     pb à éclaircir!!
	if(Height>600) Height=600;

	LaGrille->Cells[0][0]="Nom";
	m=mois_0;
	an=an_0;
	for(c=cDeb;c<cDeb+12;c++)
	{
		date=TDateTime(an,m,1);
		LaGrille->Cells[c][0]=date.FormatString("mmm  yy");
		m++;
		if(m>12)
		{
			m=1;an++;
		}
	}
	LaGrille->Row=1;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
///     spécifique aux emprunts LT
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::IniGrilleEmprunt(AnsiString nature,AnsiString titre)
{
	int l=0;
	int largeur[20];
	int c;
	int hauteur=LaGrille->RowHeights[0];
	int nbCol;
	if (NatureGEmprunt=="lt") nbCol=5; //150408
	else if(NatureGEmprunt=="ct") nbCol=5;
	else if(NatureGEmprunt=="plact")nbCol=5;
	else if(NatureGEmprunt=="sub") nbCol=3;
	else if(NatureGEmprunt=="immo") nbCol=3;

	// N_X ligne+ annee avant +total +titre
	LaGrille->RowCount= N_X+4;//??
	LaGrille->ColCount= nbCol;
	LaGrille->FixedCols=1;
	LaGrille->FixedRows=1;

	largeur[0]=32;
	for(c=1;c<nbCol;c++)largeur[c]=64;

	for(c=0;c<nbCol;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}

	Forme01Frm->Height=hauteur*(N_X+4)+Panell->Height+50; //50??
	Forme01Frm->Width=l+50;

	LaGrille->Width=l+20;
	LaGrille->Height=hauteur+hauteur*(N_X+4);

	if(NatureGEmprunt=="lt")
	{
		LaGrille->Cells[0][0]="";
		LaGrille->Cells[1][0]="Annuité";
		LaGrille->Cells[2][0]="dont Capital";
		LaGrille->Cells[3][0]="dont Intérêt";
		LaGrille->Cells[4][0]="reste Du";
	}
	else if(NatureGEmprunt=="ct")
	{
		LaGrille->Cells[0][0]="";
		LaGrille->Cells[1][0]="Capital";
		LaGrille->Cells[2][0]="Remboursement";
		LaGrille->Cells[3][0]="Intérêt";
		LaGrille->Cells[4][0]="reste Du";
	}
	else if(NatureGEmprunt=="plact")
	{
		LaGrille->Cells[0][0]="";
		LaGrille->Cells[1][0]="Capital";
		LaGrille->Cells[2][0]="Interet";
		LaGrille->Cells[3][0]="Disponible";
		LaGrille->Cells[4][0]="Créance";
	}
	else if(NatureGEmprunt=="sub" || NatureGEmprunt=="immo")
	{
		LaGrille->Cells[0][0]="";
		LaGrille->Cells[1][0]="Amortissement";
		LaGrille->Cells[2][0]="Valeur Résiduelle";
	}
	Forme01Frm->Caption=titre;

	LaGrille->Row=1;
}
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::IniGrilleTravail(TList *LstAtelier,
		TList *LstSousPeriodes,float *TotBesSousPer,
		float *DispoSousPer,float *TravNec,
		int NbTrav,int an, TDateTime DtDebut)
{
	int l=0;
	int largeur[30];
	int c,r,n,r0;
	int digits=0;
	int hauteur;
	int nbCol,nbElt,nbLText;
//float *besSousPer;
	float *heuresDispo,*heuresManquantes,*heuresExces;
	float totAtelier,totBesoin;
	char chaine[20];
	CL_Atelier *atelier;
	CL_SousPeriode *sPeriode;
	CL_BesTravAtelier *besTravAtelier;
	Word Year,jDeb,mDeb,jFin,mFin;

	RGPrecision->Visible=false;
	nbLText=7;

	hauteur=LaGrille->RowHeights[0];
	nbCol=LstSousPeriodes->Count+2;//1;
	nbElt=LstAtelier->Count+2;
	LaGrille->RowCount= nbElt+nbLText;

	// ligne total, dispo ouvrier,nbOuvrier
	r0=nbElt;
//    LaGrille->RowCount+=7;
	LaGrille->ColCount=nbCol;
	LaGrille->FixedCols=1;
	LaGrille->FixedRows=1;

	largeur[0]=128;
	for(c=1;c<nbCol;c++)largeur[c]=64;//48;//72;

	for(c=0;c<nbCol;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}

//    Width=l+25+10;
	Height=hauteur+hauteur*(nbElt+7)+Panell->Height+20;

	LaGrille->Width=l+25;//place pour l'ascenseur
	LaGrille->Height=hauteur*(LaGrille->RowCount)+10;
	Width=LaGrille->Width+25;

//    if(nbCol>N_X) Width=LaGrille->Width+50;
	// ligne 0 intitulé

	LaGrille->Cells[1][0]="Total";//!!
	for(n=0;n<LstSousPeriodes->Count;n++)
	{
		sPeriode=(CL_SousPeriode *)LstSousPeriodes->Items[n];
		DecodeDate(DtDebut+(Word)sPeriode->JD, Year, mDeb, jDeb);
		DecodeDate(DtDebut+(Word)sPeriode->JF, Year, mFin, jFin);
		sprintf(chaine,"%2d/%2d %2d/%2d",jDeb,mDeb,jFin,mFin);
		LaGrille->Cells[n+2][0]=chaine; //!!
	}

	//LaGrille->Cells[0][0]=Aff(an);
	Caption=AnsiString("Besoins en Travail  ")+an;

	// remplir la grille
	totBesoin=0;
	for(r=0;r<LstAtelier->Count;r++)
	{
		besTravAtelier=(CL_BesTravAtelier*)LstAtelier->Items[r];
		atelier= besTravAtelier->Atelier;
		LaGrille->Cells[0][r+1]=atelier->Nom;
		totAtelier=0;
		for(c=0;c<LstSousPeriodes->Count;c++)
		{
			LaGrille->Cells[c+2][r+1]=Aff(besTravAtelier->besSousPeriode[c],digits);
			totAtelier+=besTravAtelier->besSousPeriode[c]; //!!
		}
		LaGrille->Cells[1][r+1]=Aff(totAtelier);
		totBesoin+=totAtelier;
	}
	// total besoins sous periodes
	r=r0;
	//LaGrille->Cells[0][r]="Besoins en travail";
	LaGrille->Cells[0][r]=L_BesTrav;
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(TotBesSousPer[c],digits);
	LaGrille->Cells[1][r]=Aff(totBesoin);

	r=r0+1;
	LaGrille->Cells[0][r]=L_DispoT;//"Dispo par travailleur";
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(DispoSousPer[c],digits);

	r=r0+2;
	LaGrille->Cells[0][r]=L_TravNec;//"travailleurs nécessaires";
	digits=2;
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(TravNec[c],digits);

	r=r0+3;
	LaGrille->Cells[0][r]=L_TravDispo;//"travailleurs disponibles";
	digits=0;
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(NbTrav,digits);

	heuresDispo= (float*)calloc(LstSousPeriodes->Count,sizeof(float));
	heuresManquantes=(float*)calloc(LstSousPeriodes->Count,sizeof(float));
	heuresExces= (float*)calloc(LstSousPeriodes->Count,sizeof(float));

	for(c=0;c<LstSousPeriodes->Count;c++)
	{
		heuresDispo[c]=DispoSousPer[c]*NbTrav;
		if(heuresDispo[c]>TotBesSousPer[c])
		heuresExces[c]=heuresDispo[c]-TotBesSousPer[c];
		else
		heuresManquantes[c]=TotBesSousPer[c]-heuresDispo[c];

	}
	r=r0+4;
	LaGrille->Cells[0][r]=L_HDispo; //"Heures disponibles";
	digits=0;
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(heuresDispo[c]);

	r=r0+5;
	LaGrille->Cells[0][r]=L_HManq;//"Heures manquantes";
	digits=0;
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(heuresManquantes[c],digits);

	r=r0+6;
	LaGrille->Cells[0][r]=L_HExces;//"Heures excédentaires";
	digits=0;
	for(c=0;c<LstSousPeriodes->Count;c++)
	LaGrille->Cells[c+2][r]=Aff(heuresExces[c],digits);

	free(heuresDispo);
	free(heuresManquantes);
	free(heuresExces);

}
//---------------------------------------------------------------------------
/// fonctions standards
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireTitre(AnsiString titre)
{
	int row=LaGrille->Row;
	// attention col row
	LaGrille->Cells[0][row]=titre;
	LaGrille->Row++;
}
/// titre et float
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireLigne(AnsiString titre,float *vecteur)
{
	int col;
	int row=LaGrille->Row;
	int colMax=LaGrille->ColCount;
	// attention col row
	LaGrille->Cells[0][row]=titre;
	for(col=1;col<colMax;col++)
	{
		if(vecteur[col-1]==0) continue;
		LaGrille->Cells[col][row]=Aff(vecteur[col-1],Digits);
	}
	LaGrille->Row++;
}
/// titre et float commençant en col 2
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireLigneCol2(AnsiString titre,float *vecteur)
{
	int col;
	int row=LaGrille->Row;
	int colMax=LaGrille->ColCount;
	// attention col row
	LaGrille->Cells[0][row]=titre;
	for(col=2;col<colMax;col++)
	LaGrille->Cells[col][row]=Aff(vecteur[col-2],Digits);
	LaGrille->Row++;
}
/// float
//---------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireLigne(float *vecteur)
{
	int col;
	int row=LaGrille->Row;
	int colMax=LaGrille->ColCount;
	// attention col row
	for(col=0;col<colMax;col++)
	{
//        if(vecteur[col-1]==0) continue;
		if(vecteur[col]==0) continue;//080103
		LaGrille->Cells[col][row]=Aff(vecteur[col],Digits);
	}
	LaGrille->Row++;
}
/// titre entier
//-----------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireLigne(AnsiString titre,int *vecteur)
{
	int col;
	int row=LaGrille->Row;
	int colMax=LaGrille->ColCount;
	// attention col row
	LaGrille->Cells[0][row]=titre;
	for(col=1;col<colMax;col++)
	{
		if(vecteur[col-1]==0) continue;
		LaGrille->Cells[col][row]=IntToStr(vecteur[col-1]);
	}
	LaGrille->Row++;
}

//---------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireLigneTresoValeur(AnsiString nom,float *flux,int mDeb)
{
	int col,m,colDeb;
	int row=LaGrille->Row;
	int digits=0;
	// attention col row
	colDeb=1;
	LaGrille->Cells[0][row]=nom;
	for(col=colDeb,m=mDeb;col<colDeb+12;col++,m++)
	{
		if(flux[m])
		LaGrille->Cells[col][row]=Aff(flux[m],digits);
	}
	LaGrille->Row++;
}
//---------------------------------------------------------------------------
void __fastcall TForme01Frm::EcrireLigneTresoQuantite(AnsiString nom,AnsiString unite,float *flux,int mDeb)
{
	int col,colDeb,m;
	int row=LaGrille->Row;
	int digits=0;
	// attention col row
	colDeb=2;
	LaGrille->Cells[0][row]=nom;
	LaGrille->Cells[1][row]=unite;
	for(col=colDeb,m=mDeb;col<colDeb+12;col++,m++)
	{
		if(flux[m])
		LaGrille->Cells[col][row]=Aff(flux[m],digits);
	}
	LaGrille->Row++;
}
//---------------------------------------------------------------------------
void __fastcall TForme01Frm::BtBnImpClick(TObject *Sender)
{

	QRGrille00Frm->LaGrille=LaGrille;
	QRGrille00Frm->TitreEtat->Caption=Caption; //TitreGrille;//Forme00Frm->Caption;
	QRGrille00Frm->TypeCol=TypeCol;
	QRGrille00Frm->Initialise();
	QRGrille00Frm->QR->Preview();
}
//---------------------------------------------------------------------------
void __fastcall TForme01Frm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	BtBnMoin12->Visible=true; //170512
	BtBnPlus12->Visible=true;

	//sinon on retournr dans forme00 qui pose question idiote
	CanClose=true;
}
//---------------------------------------------------------------------------

void __fastcall TForme01Frm::RGPrecisionClick(TObject *Sender)
{ /* TODO : forme01 RGPrecisionClick */
	if(RGPrecision->ItemIndex==0) Digits=0;
	else Digits=2;
	if(UtilisePar=="Graph")
	ResGraphFrm->BtTableauClick(this);

//        GraphiqueFrm->BtTableauClick(this);//111002
	else if(UtilisePar=="indicateur")
	IndicateurFrm->BtBnResultatClick(this);
	else return;
	// a completer pour Emprunt MvtAni AgriSaisieVoir

}
//---------------------------------------------------------------------------
void TForme01Frm::IniGrilleImmo(CL_Agriculteur *agri, int nature) //300406
		{
	int i, c, n, row;
	int digits;
	int nbelt;
	int an_0;
	CL_Immo *immo;
	CL_Vecteur<CL_Immo> *vecteur = agri->V_Immo;
	float amor[N_X], vResid[N_X + 1];
	int exAchat, exVente;
	float *valeur;
	float total[N_X];
	int hauteur = LaGrille->RowHeights[0];
	int largeur = 0;
	RGPrecision->Visible = false;
//    if(RGPrecision->ItemIndex==0) digits=0;
//    else                          digits=2;
	memset(total, 0, sizeof(total));
	digits = 0;
	nbelt = vecteur->Nbelt;
	Grille0->RowCount = nbelt + 3;
	Grille0->ColCount = N_X + 2;

	LaGrille->FixedCols = 1;
	LaGrille->FixedRows = 1;

	Grille0->ColWidths[0] = 32;
	Grille0->ColWidths[1] = 128;
	for (c = 2; c < Grille0->ColCount; c++)
		Grille0->ColWidths[c] = 64;

	for (c = 0; c < Grille0->ColCount; c++)
		largeur += Grille0->ColWidths[c];

	LaGrille->Height = hauteur * (nbelt + 1 + 2);
	LaGrille->Width = largeur;
	Forme01Frm->Height = hauteur * (nbelt + 1 + 2) + Panell->Height + 50; //50??
	Forme01Frm->Width = largeur + 50;

	Grille0->Cells[1][0] = "Immobilisation";
	an_0 = agri->DefSim->An_0;
	for (i = 0; i < 10; i++)
		Grille0->Cells[i + 2][0] = "  " + AnsiString(an_0 + i);

	for (n = 0, row = 1; n < nbelt; n++, row++) {
		immo = vecteur->Vecteur[n];
		immo->Calcul(an_0, amor, vResid, exAchat, exVente);

		if (nature == AMOR)
			valeur = amor;
		else if (nature == VALRESID)
			valeur = vResid;

		Grille0->Objects[0][row] = (TObject*) immo;
		Grille0->Cells[0][row] = row;
		Grille0->Cells[1][row] = immo->Nom;
		for (c = 2, i = 0; c < 2 + N_X; c++, i++) {
			Grille0->Cells[c][row] = Aff(valeur[i], digits);
			total[i] += valeur[i];
		}
	}
	row = Grille0->RowCount - 1;
	Grille0->Cells[1][row] = "Total";

	for (c = 2, i = 0; c < 2 + N_X; c++, i++)
		Grille0->Cells[c][row] = Aff(total[i], digits);
}
//---------------------------------------------------------------------------

void __fastcall TForme01Frm::Grille0DrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State)
{
	int w=Rect.Right-Rect.Left;
	if(ACol==0) return;
	if(ARow==0) return;
	SetTextAlign(LaGrille->Canvas->Handle,TA_RIGHT);
	LaGrille->Canvas->TextRect(Rect,Rect.Left+w,Rect.Top+4,LaGrille->Cells[ACol][ARow]);
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TForme01Frm::TexteChaine(void) {
	L_BesTrav = T->TrouveTexte("TForme01Frm", "L_BesTrav");
	L_DispoT = T->TrouveTexte("TForme01Frm", "L_DispoT");
	L_TravNec = T->TrouveTexte("TForme01Frm", "L_TravNec");
	L_TravDispo = T->TrouveTexte("TForme01Frm", "L_TravDispo");
	L_HDispo = T->TrouveTexte("TForme01Frm", "L_HDispo");
	L_HManq = T->TrouveTexte("TForme01Frm", "L_HManq");
	L_HExces = T->TrouveTexte("TForme01Frm", "L_HExces");
}
//--------------------------------------------
void TForme01Frm::IniCaption(void) {
	RGPrecision->Caption = T->LC_RGPrecision;
	Forme01Frm->Caption = LC_Forme01Frm;
}
//--------------------------------------------
void TForme01Frm::TexteCaption(void) {
	LC_RGPrecision = T->TrouveCaption("CL_Trad", "LC_RGPrecision");
	LC_Forme01Frm = T->TrouveCaption("Forme01", "LC_Forme01Frm");

	IniCaption();

}
//--------------------------------------------
void __fastcall TForme01Frm::BtBnMoin12Click(TObject *Sender)//170512
{
	TresoGraphFrm->AffTableauMoins12(); // 170512
}
//---------------------------------------------------------------------------

void __fastcall TForme01Frm::BtBnPlus12Click(TObject *Sender)
{
	TresoGraphFrm->AffTableauPlus12(); // 170512
//
}
//---------------------------------------------------------------------------

