//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <vector.h>
#include <Clipbrd.hpp>
//#include <utilcls.h>

#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "SysUnite.h"
#include "ReclasseG.h"
#include "FichierLire.h"
#include "QuelExcelCSV.h"
//#include "Brouillon.h"

#include "Tableur.h"
#include "LBSysUnit.h"
#include "LBTva.h"

//#include "Classer.h"
#include "QRGrille00.h"
#include "CL_Trad.h"
#include "Forme00.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "Excel_97_SRVR"
#pragma link "Forme0"
#pragma resource "*.dfm"

TForme00Frm *Forme00Frm;
extern CL_ES *ES;
extern CL_Excel *EX;
extern CL_Trad *T;

//---------------------------------------------------------------------------
/*                   NOTES
 Modifier ordre des tabulations leblanc p 200
 Edition->ordre de tabulation
 GrilleFrm position podefault
 */

//---------------------------------------------------------------------------
__fastcall TForme00Frm::TForme00Frm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::FormCreate(TObject *Sender)
{
	EstInitialise=false;
	CCRow=new TStringList;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::FormActivate(TObject *Sender)
{
	int g;
	if(EstInitialise==false)
	{
		Personnaliser();
		DefinirLesGrilles();

		for(int g=0;g<GrilleX;g++)
		IniGrille(LesGrilles[g]); // nb col,row, non défilable

		CellDebut();
//	    for(int g=0;g<GrilleX;g++) GrilleModif[g]=false;
//	    for(int g=0;g<GrilleX;g++) VersGrille(LesGrilles[g]);

		AjoutRow= true;
		LabelModifie->Visible=false;

		LaGrille=LesGrilles[0];
		g=LaGrille->Tag;
		if(g>COLMAX)
		{
			ShowMessage("Forme00 g>ColMax");
		}
//	   	ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
		EstInitialise=true;
		VideLesGrilles();
		AutreDonnee=true;
	}

	//    VideLesGrilles();  ???
	//    CellDebut();
	if(PClasst->Visible==true)
	{
		BtBnFermClasstClick(this);
		PClasst->Visible=false;
	}
	if(AutreDonnee==true) //defini par stocker
	{
		VideLesGrilles(); // 230202
//        for(g=0;g<GrilleX;g++) GrilleModif[g]=false;
		for(g=0;g<GrilleX;g++) VersGrille(LesGrilles[g]);
		CellDebut();
	}
//..........
//    ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];  //la grille est vide ->bug
}
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
//en entrant CanClose=true;
	int rep;
	int g;
	// fermer les fenetre LB TV   a completer
	LBTvaFrm->Close();
	LBSysUnitFrm->Close();

	DerniereCell();
	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),T->L_DonModifT.c_str(),
				//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		switch(rep)
		{
			case ID_YES:
			CanClose=Stocker();
			if(CanClose==true) LabelModifie->Visible=false;
			break;
			case ID_CANCEL:
			CanClose=false;
			break;
			case ID_NO:
			VideLesGrilles();
			CanClose=true;
			for(int g=0;g<GrilleX;g++) VersGrille(LesGrilles[g]);
			LaGrille=LesGrilles[0];
			g=LaGrille->Tag;
			ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
			LabelModifie->Visible=false;
			break;
		}
	}
	else
	CanClose=true;
}
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::BoutFermerClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
/*            VERIFICATION
 On entre dans une grille
 soit CellInitiale(col,row) détermine ou se placer
 soit CellInitiale(void)    détermine ou on est
 ColEC et RowEC sont alors connus

 Grille0Click
 On vient de sélectionner une nouvelle cellule
 verifier que la précédente repérée par ColEC et RowEC est correcte
 si non correcte y rester
 pour ceci utilise
 ControleCell
 est spécifique
 peut verifier le contenu de la cellule
 notamment l'absence de doublon
 peut creer si nouveau l'objet (eg item) et met son adresse dans LaGrille->Objects[0][row]

 repere la cellule en cours: ColEC et RowEC
 SaisirCell
 peut faire appel à fonction spécifique: saisir cell
 à partie de Grille0KeyPress qui connait TypeCol
 filtre numerique ou alpha
 */
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::CellInitiale(int col,int row)
{
	LaGrille->Row=row;
	LaGrille->Col=col; //
	//	LaGrille->Col=2; //
	RepereCellEC(col,row);
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::CellInitiale(void)
{
	RepereCellEC(LaGrille->Col,LaGrille->Row);
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::RepereCellEC(int col,int row)
{
	ColEC=col;
	RowEC=row;
	CellModif=false;
	ValueAvant=LaGrille->Cells[col][row];
}
//---------------------------------------------------------------------------
/*       saisie d'une cellule de la grille
 la dernière cellule ou j'ai été est repérée par ColEC et RowEC
 elle contenait une AnsiString ValueAvant
 je viens de cliquer sur une autre cellule :
 je reste sur la Cell précédente DerniereCell
 avant de passer à cette cell je ControleCell

 si le contenu de la derniere cellule n'a pas changé  ok
 sinon controle de la validité de cette deniere cell ControleCell
 nota on a pu saisir que des caractères autorisés
 ce controle se fait par un ControleCell spécifique de la grille et de la cellule
 si controle != ok on reste sur cette dernière cell

 je repere les coordonnées de cette cell et son contenu pour verifier quand j'en sortirai

 j'appelle la fonction spécifique de saisie de cette cell si elle existe
 sinon je saisis par Grille0KeyPress

 */
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::Grille0Click(TObject *Sender)
{
	AnsiString Value;
	if(DerniereCell()==false)return;
	if(LaGrille->Col<0 || LaGrille->Col>LaGrille->ColCount )return; //240406
	if(LaGrille->Row<0 || LaGrille->Col>LaGrille->RowCount )return;//240406
	RepereCellEC(LaGrille->Col,LaGrille->Row);// ColEC RowEC ValueAvant
	SaisirCell(LaGrille->Col,LaGrille->Row);//il y a fonction de saisie
											//pour cas particulier

	if (PClasst->Visible)//seult si bouton classer actif
	MarquerLigne(LaGrille->Row);
}
//---------------------------------------------------------------------
/*
 verifie le contenu de la derniére cellule
 si Ok    renvoie true
 sinon            false et reste dans la cellule
 */
//---------------------------------------------------------------------
bool __fastcall TForme00Frm::DerniereCell(void)
{

	//rustine à supprimer
	if(LaGrille==NULL) {ShowMessage("DerniereCell"); return true;}

	if(LaGrille->Cells[ColEC][RowEC]==ValueAvant) return true;

	LabelModifie->Visible =true;

	if(ControleCell(ColEC,RowEC)==true)
	{
		AjouterRow();

		RepereCellEC(LaGrille->Col,LaGrille->Row);

		return true;
	}
	else
	{
		//il y a erreur on reste dans la cellule
		LaGrille->Col=ColEC;
		LaGrille->Row=RowEC;
		return false;
	}
}
//---------------------------------------------------------------------------
/*
 Grille0KeyPress
 si TypeCol[col]='0' non modifiable //290302
 si colonne reçoit du mumérique TypeCol[col]='N'
 verifie numéricité
 affiche LabelModifie->Visible  //300302
 revoir ttes lers fonctions qui définissent LabelModifie->Visible=true;
 cela devrait tout simplifier
 */
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::Grille0KeyPress(TObject *Sender, char &Key)
{
	/*040507
	 //280306
	 if(Key==11 || Key==22)  //CtrlV  Coller
	 {
	 Key=0;
	 LireClipBoard();
	 CellModif=true;LabelModifie->Visible=true;
	 return;
	 }
	 if(Key==3)  //CtrlC    Copier
	 {
	 //        ShowMessage(AnsiString(CDebSel)+"  "+RDebSel+"  "+CFinSel+"  "+RFinSel);
	 Key=0;
	 if(CDebSel==CFinSel && RDebSel==RFinSel )return;
	 EcrireClipBoard();
	 return;
	 }
	 if(Key==26)  //CtrlZ Restaurer
	 {
	 Restaurer();
	 //ShowMessage(AnsiString(LaGrille->Tag));
	 }
	 */
	if (TypeCol[LaGrille->Col]=='0') {Key=0; return;} //290302

	if (TypeCol[LaGrille->Col]!='N') {CellModif=true;LabelModifie->Visible=true; return;}
	else if(Key >='0' && Key <='9') {CellModif=true;LabelModifie->Visible=true; return;}
	else if(Key=='-') {CellModif=true;LabelModifie->Visible=true; return;}
	else if(Key=='.') {CellModif=true;LabelModifie->Visible=true; return;}
	else if(Key==VK_BACK) {return;}
	Key=0;
}
//------------------------------------------------------------------
/// verifie caractère alpha étendu
//------------------------------------------------------------------
int TForme00Frm::isalnumA(unsigned char c) {
//recopie de analex
// prise en compte de é à etc
	if (isalnum(c))
		return 1;
	if (c == '_')
		return 1;
	if (c == '.')
		return 1;
	if (c >= 128 && c <= 176)
		return 1;
	if (c >= 224 && c <= 244)
		return 1;
	if (c >= 249 && c <= 255)
		return 1; // le û de août 061206

	return 0;
}
//---------------------------------------------------------------------------
//------------------------------------CLIPBOARD------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int TForme00Frm::LireClipBoard(void) {
	int nLu;
	char buf[10000];
	int b;

	char mot[50];
	int m;

//int col0;//,row0;
	int col, row;

	char car;
	bool stop;
	bool formatOK;
	if (SLRestaurer == NULL)
		SLRestaurer = new TStringList;
	SLRestaurer->Clear();
	/*  verifier si clipboard contient du texte
	 n=CF_TEXT;        1
	 n=CF_BITMAP;      2
	 n=CF_METAFILEPICT;3
	 n=CF_PICTURE;
	 n=CF_COMPONENT;
	 */
	formatOK = false;
	for (int i = 0; i < Clipboard()->FormatCount; i++) {
		if (Clipboard()->Formats[i] == CF_TEXT) {
			formatOK = true;
			break;
		}
	}
	if (formatOK == false) {
		ShowMessage("Clipboard ne contient pas de Texte");
		return 0;
	}

	nLu = Clipboard()->GetTextBuf(buf, 10000);
	if (nLu == 0)
		return 0;

	ColCB = LaGrille->Col;
	RowCB = LaGrille->Row;

	col = LaGrille->Col;
	row = LaGrille->Row;

	b = 0;
	m = 0;
	stop = false;
	while (stop == false) {
		car = buf[b++];
		if (b >= nLu)
			break;
		switch (car) {
		case 0:
			break;

		case '\n':
			// ne pas dépasser RowCount-1
			SLRestaurer->Add("\n");
			row++;
			if (row >= LaGrille->RowCount) {
				stop = true;
				break;
			}
			col = ColCB;
			break;

		case '\r':
		case '\t':
			mot[m] = 0;

			if (col < LaGrille->ColCount) {
				SLRestaurer->Add(LaGrille->Cells[col][row]);
				LaGrille->Cells[col][row] = mot;
			}
			col++;
			m = 0;
			mot[m] = 0;
			break;
		case ',': //excel français met des , ex 10,50 ->10.50
			mot[m++] = '.';
			break;
		default:
			mot[m++] = car;
		}
	}
//    ShowMessage(LaGrille->Cells[col0][row0]);
	return 2;

}
//---------------------------------------------------------------------------
int TForme00Frm::Restaurer(void) {
	int n;
	int c, r;
	AnsiString mot;

	c = ColCB;
	r = RowCB;
	for (n = 0; n < SLRestaurer->Count; n++) {
		mot = SLRestaurer->Strings[n];
		if (mot == "/n") {
			r++;
			c = ColCB;
		}

		else
			LaGrille->Cells[c++][r] = mot;
	}
	return 2; //??
}
//---------------------------------------------------------------------------
int TForme00Frm::EcrireClipBoard(void) {
	AnsiString as;
	int c, r;
	//ShowMessage("EcrireClipBoard");
	Clipboard()->Clear();
	for (r = RDebSel; r < RFinSel + 1; r++) {
		for (c = CDebSel; c < CFinSel + 1; c++) {
			as += LaGrille->Cells[c][r];
			if (c < CFinSel)
				as += '\t';
			else
				as += "\r\n";
		}
	}
	Clipboard()->SetTextBuf(as.c_str());
	Clipboard()->Close();
//    ShowMessage(as);
	return 1;

}
//---------------------------------------------------------------------------
/*
 void __fastcall TForme00Frm::Grille0MouseDown(TObject *Sender,
 TMouseButton Button, TShiftState Shift, int X, int Y)
 {
 int c,r;
 MouseActive=true;

 LaGrille->MouseToCell(X,Y,c,r);

 if(c<0) c=0;          //plante si cliquer hors grille 300406
 if(r<0) r=0;

 CDebSel=c;
 RDebSel=r;

 CFinSel=c;
 RFinSel=r;
 //    ShowMessage(AnsiString(CDebSel)+"  "+RDebSel);

 }
 */
//---------------------------------------------------------------------------
/*
 void __fastcall TForme00Frm::Grille0MouseUp(TObject *Sender,
 TMouseButton Button, TShiftState Shift, int X, int Y)
 {
 int c,r;
 MouseActive=false;

 LaGrille->MouseToCell(X,Y,c,r);

 if(c<0) c=0;          //plante si cliquer hors grille 300406
 if(r<0) r=0;

 CFinSel=c;
 RFinSel=r;
 //ShowMessage(AnsiString(CFinSel)+"  "+RFinSel);
 if ((CDebSel!=CFinSel) ||(RDebSel!=RFinSel))
 {
 PlageCellules.Left =   CDebSel;
 PlageCellules.Top =    RDebSel;

 PlageCellules.Right =  CFinSel;//+1;
 PlageCellules.Bottom = RFinSel;

 LaGrille->Selection = PlageCellules;
 }

 }
 */
/*  100407
 //---------------------------------------------------------------------------
 void __fastcall TForme00Frm::Grille0MouseMove(TObject *Sender,
 TShiftState Shift, int X, int Y)
 {
 int c,r;
 if(MouseActive==false) return;

 LaGrille->MouseToCell(X,Y,c,r);

 if(c<0) c=0;          //plante si cliquer hors grille 300406
 if(r<0) r=0;

 CFinSel=c;
 RFinSel=r;
 //ShowMessage(AnsiString(CFinSel)+"  "+RFinSel);
 //    if ((CDebSel!=CFinSel) ||(RDebSel!=RFinSel))
 //    {
 PlageCellules.Left =   CDebSel;
 PlageCellules.Top =    RDebSel;

 PlageCellules.Right =  c;//CFinSel+1;
 PlageCellules.Bottom = r;//RFinSel;

 //LaGrille->EditorMode = false;

 LaGrille->Selection = PlageCellules;
 //    }
 }
 */
//---------------------------------------------------------------------------
/*
 //---------------------------------------------------------------------
 bool __fastcall TForme00Frm::DerniereCell(void)
 {
 int g;
 bool modif=false;
 AnsiString Value;
 if(CellAVerifier==false) return true;

 g=LaGrille->Tag;
 // a verifier
 //    if(ColM[g]==0 || ColM[g]==1) return true;
 //    if(Value==NULL) return true;
 Value=LaGrille->Cells[ColM[g]][RowM[g]];
 if(Value.AnsiCompare(ValueAvant)!=0)
 {
 modif =true;
 GrilleModif[g]=true;
 LabelModifie->Visible=true;
 ValueAvant=Value;
 }

 if ( modif==true)
 {
 if(ControleCell(ColM[g],RowM[g])==true)
 {
 AjouterRow();
 return true;
 }
 else
 {
 // on reste dans la cellule
 LaGrille->Col=ColM[g];
 LaGrille->Row=RowM[g];
 return false;
 }
 }
 else
 return true;
 }
 */
//-----------------------------------------------------------------------------
/*
 CellDebut est appelé systematiquement à l'initialisation
 sur demande
 determine la première cellule active
 initie ValueAvant
 coutcircuite les tests de Grill0Click appelé par c++ à l'instruction LaGrille-Col=2
 */
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::CellDebut(void)
{
//	ShowMessage("CellDebut à faire"); //bidon
}
//---------------------------------------------------------------------------
// agrandir la grille
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::AjouterRow(void)
{
	int r;
	if(AjoutRow==false) return;

	r=LaGrille->RowCount-2;
	if(LaGrille->Objects[0][r]==NULL ) return;
	LaGrille->RowCount++;
}
//----------------------------------------------------------------------------
bool __fastcall TForme00Frm::RowVide(int row,int c0)
{
	AnsiString s;
	for(int c=c0;c<LaGrille->ColCount;c++) // en 0 c'est num° de ligne
	{
		s=LaGrille->Cells[c][row].Trim();
		if(s=="") continue; //010105
		if(s.IsEmpty()==false) return false;
	}
	return true;
}
//----------------------------------------------------------------------------
bool __fastcall TForme00Frm::CellVide(int col,int row)
{
	AnsiString as;
	if(LaGrille->Cells[col][row].IsEmpty()) return true;
	if(LaGrille->Cells[col][row]=="") return true;
	as=LaGrille->Cells[col][row];
	as=as.Trim();
	if(as=="") return true;
	return false;
}
//-----------------------------------------------------------------------------
// ne sert plus à rien OnKeyPress filtre
// peut servir pour verrouiller une grille
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::CellModifiable(bool modifiable)
{
	modifiable=true; //261103 ????
	if (modifiable==false)
	{
		LaGrille->Options>>goAlwaysShowEditor;
		LaGrille->Options>>goEditing;
		LaGrille->EditorMode=false;
		LaGrille->Options<<goDrawFocusSelected;
	}
	else
	{
		LaGrille->Options<<goAlwaysShowEditor;
		LaGrille->Options<<goEditing;
		LaGrille->EditorMode=true;
		LaGrille->Options>>goDrawFocusSelected;
	}
}
//-----------------------------------------------------------
// ReClasse
//-----------------------------------------------------------
void __fastcall TForme00Frm::BtClasserClick(TObject *Sender)
{
	DemarrerClasst();
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::DemarrerClasst(void)
{
	int row;
	row=LaGrille->Row;
	if(row==0) Close();

	Grille0Click(this);
	LaGrille->Options >> goEditing;
	LaGrille->EditorMode=false;
	LaGrille->Options << goRowSelect;
	if( LaGrille->Row >0 && LaGrille->Col >0)
	MarquerLigne(row);
	PClasst->Top =BtClasser->Top;
	PClasst->Left=BtClasser->Left;
//    PosClasst();
	PClasst->Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::BtClHautClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
//TObject    *object;
	LabelModifie->Visible=true;
	OrdreModif=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row<=1) return;

	SwapObjet(LaGrille,0,row,row-1);
	/*
	 object=LaGrille->Objects[0][row];
	 LaGrille->Objects[0][row]=LaGrille->Objects[0][row-1];
	 LaGrille->Objects[0][row-1]=object;
	 */
	for(c=0;c<cX;c++)
	{
		SwapAs(LaGrille,c,row,row-1);
		/*
		 s=LaGrille->Cells[c][row];
		 LaGrille->Cells[c][row]=LaGrille->Cells[c][row-1];
		 LaGrille->Cells[c][row-1]=s;
		 */
	}
	LaGrille->Cells[0][row-1] =row-1;
	LaGrille->Cells[0][row] =row;

	MarquerLigne(row-1);
//    PosClasst();
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::BtClBasClick(TObject *Sender)
{
	int row;
	int c,cX;
	AnsiString s;
//TObject    *object;
	LabelModifie->Visible=true;
	OrdreModif=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row>=LaGrille->RowCount-1) return;

	SwapObjet(LaGrille,0,row,row+1);
	/*
	 object=LaGrille->Objects[0][row];
	 LaGrille->Objects[0][row]=LaGrille->Objects[0][row+1];
	 LaGrille->Objects[0][row+1]=object;
	 */
	for(c=0;c<cX;c++)
	{
		SwapAs(LaGrille,c,row,row+1);
		/*
		 s=LaGrille->Cells[c][row];
		 LaGrille->Cells[c][row]=LaGrille->Cells[c][row+1];
		 LaGrille->Cells[c][row+1]=s;
		 */
	}
	LaGrille->Cells[0][row] =row;
	LaGrille->Cells[0][row+1]=row+1;

	MarquerLigne(row+1);
//    PosClasst();
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::SwapObjet(TStringGrid *laGrille,int col,int row0,int row1)
{
	TObject *object;

	object=laGrille->Objects[col][row0];
	LaGrille->Objects[col][row0]=LaGrille->Objects[col][row1];
	LaGrille->Objects[col][row1]=object;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::SwapAs(TStringGrid *laGrille,int col,int row0,int row1)
{
	AnsiString as;

	as=laGrille->Cells[col][row0];
	LaGrille->Cells[col][row0]=LaGrille->Cells[col][row1];
	LaGrille->Cells[col][row1]=as;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::BtBnFermClasstClick(TObject *Sender)
{
	TGridRect selection;

	LaGrille->Options << goEditing;
	LaGrille->Options >> goRowSelect;
	PClasst->Visible=false;

	selection.Top=LaGrille->Row;
	selection.Bottom=LaGrille->Row;
	selection.Right=2;
	selection.Left=2;
	LaGrille->Selection=selection;
}
//---------------------------------------------------------------------------
/*
 void __fastcall TForme00Frm::PosClasst(void)
 {
 PClasst->Top =BtClasser->Top;//BtClasser->Top;
 PClasst->Left=BtClasser->Left;

 //    PClasst->Left=LaGrille->Left;//-PClasst->Width;//Top+LaGrille->DefaultRowHeight;
 MarquerLigne(LaGrille->Row);
 }
 */
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::MarquerLigne(int row)
{
	TGridRect selection;
	int cX=LaGrille->ColCount;
	selection.Left=1;
	selection.Right=cX-1;
	selection.Top=row;
	selection.Bottom=row;
	LaGrille->Selection=selection;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::MarquerCell(int col,int row)
{
	TGridRect selection;
	selection.Left=col; //col-1
	selection.Right=col;
	selection.Top=row;
	selection.Bottom=row;
	LaGrille->Selection=selection;
}
//---------------------------------------------------------------------------
//     Aff tranforme un float ou un int en AnsiString
//-----------------------------------------------------------
AnsiString TForme00Frm::Aff(float x, int digits) {
	if (x == 0.)
		return AnsiString(" "); //"" ou " "      ????
	return FloatToStrF((double) x, ffNumber, 7, digits);
}
/*
 static AnsiString s;
 char chaine[20];
 int l;

 if(x==0.) return " ";
 memset(chaine,' ',sizeof(char)*20);
 s=FloatToStrF(x,ffNumber,7,digits);
 l=s.Length();
 chaine[10-l]=0;
 s=AnsiString(chaine)+s;
 return s;
 }
 */
//-----------------------------------------------------------
AnsiString TForme00Frm::Aff0(float x, int digits) {
	if (x == 0)
		return AnsiString("0");
	return FloatToStrF((double) x, ffNumber, 7, digits);
}
/*
 AnsiString s;
 char chaine[20];
 int l;
 if(x==0.) return "0";
 return (Aff(x,digits));
 */
//-----------------------------------------------------------
AnsiString TForme00Frm::Aff(int x) {
	if (x == 0)
		return "";
	return IntToStr(x);
}
/*
 AnsiString s;
 char chaine[20];
 int l;
 if(x==0) return " ";
 memset(chaine,' ',sizeof(char)*20);
 s=AnsiString(x);
 l=s.Length();
 chaine[5-l]=0;
 s=AnsiString(chaine)+s;
 return s;
 */
//peut mieux faire
//-----------------------------------------------------------
AnsiString TForme00Frm::Aff(char c) {
	static AnsiString s;
	char chaine[20];
	chaine[0] = c;
	chaine[1] = 0;
	s = AnsiString(chaine);
	return s;
}
//-----------------------------------------------------------
AnsiString TForme00Frm::Aff(int x1, int x2) {
	static AnsiString s;
	if (x1 + x2 != 0)
		s = AnsiString(x1) + " " + AnsiString(x2);
	else
		s = " ";
	return s;
}
//-----------------------------------------------------------
AnsiString TForme00Frm::AffJourMois(int jour, int mois) {
	static AnsiString s;
	char chaine[10];
	sprintf(chaine, "%02d  %02d", jour, mois);
	s = chaine;
	return s;
}
//-----------------------------------------------------------
//     extrait valeur (float,int, chaine)
//-----------------------------------------------------------
float __fastcall TForme00Frm::GrilleFloat(int col,int row)
{
	int n,c;
	AnsiString s;
	char car;
	char chaine[20];
	int point=0;
	double val;
	char *endptr;

//    if(LaGrille->Cells[col][row].IsEmpty()==true) return 0.;
	s=LaGrille->Cells[col][row];
	s=s.Trim();
	if(s=="" ||s=="."||s=="-") return 0.;
	c=0;
	for(n=1;n<s.Length()+1;n++)
	{
		car=s[n];
		if (car>='0' && car<='9') chaine[c++] =car;
		else if(car=='.' ||car==',')
		{
			if(point==0) {chaine[c++] ='.';point++;}
		}
		else if(car=='-' && c==0) chaine[c++] ='-';
	}
	if(c==0) return 0; //150105
	if(point==0)
	{	chaine[c]='.';chaine[c+1]=0;}
	else
	chaine[c]=0;

//   val=atof(chaine);
	val=strtod(chaine,&endptr);

//   s=AnsiString(chaine);
//	val=s.ToDouble();
	/*
	 try
	 {
	 val=s.ToDouble();
	 }
	 catch(...)
	 {
	 val=0;
	 }
	 */
	return val;
}
//---------------------------------------------------------------------
int __fastcall TForme00Frm::GrilleInt(int col,int row)
{
	int n,c;
	AnsiString s;
	char car;
	char chaine[20];
	s=LaGrille->Cells[col][row];
	s=s.Trim();
	if(s=="")return 0;
	c=0;
	for(n=1;n<s.Length()+1;n++)
	{
		car=s[n];
		if (car>='0' && car<='9') chaine[c++] =car;
		else if(car=='-') chaine[c++] ='-';
	}
	chaine[c]=0;
	s=AnsiString(chaine);
	return s.ToInt();
}
//---------------------------------------------------------------------
AnsiString __fastcall TForme00Frm::GrilleChaine(int col, int row) {
	return (LaGrille->Cells[col][row].Trim());
}
//---------------------------------------------------------------------
char __fastcall TForme00Frm::GrilleCar(int col,int row)
{
	AnsiString s;
	s=LaGrille->Cells[col][row];
	s=s.Trim();
	if(s.Length()==0) return ' ';
	else return s[1];
}
/*
 traite une chaine mois an 6 caractéres maxi aprés avoir retiré blanc
 6 caracteres 061992 121992
 5             61992
 4             0692
 3              692

 */
//---------------------------------------------------------------------
bool __fastcall TForme00Frm::GrilleMoisAn(int col,int row,int &mois,int &an)
{
	AnsiString s,sMois,sAn;
	char *chaine;
	int n,i,j;
	s=LaGrille->Cells[col][row];
	s=s.Trim();
	chaine=s.c_str();
	n=s.Length();
	if(n==0) {mois=0;an=0;return false;} //231006
	//retire blancs de la chaine
	i=0;
	j=i;
	while(1)
	{
		if(chaine[i]==' ') i++;
		if(chaine[i]!=' ') {chaine[j]=chaine[i];i++;j++;}
		if(chaine[i]==0) {chaine[j]=0; break;}

	}
	s=AnsiString(chaine);
	switch(s.Length())
	{
		default:
		MessageBox(Handle,L_ErrDate.c_str(),T->L_Erreur.c_str(),
				//MessageBox(Handle,"Erreur sur la date","ERREUR",
				MB_OK|MB_ICONSTOP);
		return false;

		case 3:sMois=s.SubString(1,1);sAn=s.SubString(2,2);break;
		case 4:sMois=s.SubString(1,2);sAn=s.SubString(3,2);break;
		case 5:sMois=s.SubString(1,1);sAn=s.SubString(2,4);break;
		case 6:sMois=s.SubString(1,2);sAn=s.SubString(3,4);break;
	}
	mois=sMois.ToInt();
	if(mois<1 || mois >12)
	{
		MessageBox(Handle,L_ErrMois.c_str(),T->L_Erreur.c_str(),
				//MessageBox(Handle,"Erreur sur le mois","ERREUR",
				MB_OK|MB_ICONSTOP);
		return false;
	}
	an=sAn.ToInt();
	if(an <100 )
	{
		if(an <50) an+=2000;
		else an+=1900;
	}
	if(an<1950 || an >2050)
	{
		MessageBox(Handle,L_ErrAn.c_str(),T->L_Erreur.c_str(),
				//MessageBox(Handle,"Erreur sur l'année","ERREUR",
				MB_OK|MB_ICONSTOP);
		return false;
	}
	s=AnsiString(mois)+" "+AnsiString(an);
	LaGrille->Cells[col][row]=s;
	return true;
}
/*
 traite une chaine jour mois 4 caractéres maxi aprés avoir retiré blanc
 4             0602
 3              602
 2               62
 */
//---------------------------------------------------------------------
bool __fastcall TForme00Frm::GrilleJourMois(int col,int row,int &jour,int &mois)
{
	AnsiString s,sJour,sMois;
	char *chaine;
	int n,i,j;
	int nbJour; // janvier est le mois 1
	int jourDuMois[]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

	s=LaGrille->Cells[col][row];
	s=s.Trim();
	chaine=s.c_str();
	n=s.Length();
	if(n==0 ) return false;
	//retire blancs de la chaine
	i=0;
	j=i;
	while(1)
	{
		if(chaine[i]==' ') i++;
		if(chaine[i]!=' ') {chaine[j]=chaine[i];i++;j++;}
		if(chaine[i]==0) {chaine[j]=0; break;}

	}
	s=AnsiString(chaine);
	switch(s.Length())
	{
		default:
		MessageBox(Handle,L_ErrDate.c_str(),T->L_Erreur.c_str(),
				//MessageBox(Handle,"Erreur sur la date","ERREUR",
				MB_OK|MB_ICONSTOP);
		return false;

		case 2:sJour=s.SubString(1,1);sMois=s.SubString(2,1);break;//12
		case 3:sJour=s.SubString(1,1);sMois=s.SubString(2,2);break;//102
		case 4:sJour=s.SubString(1,2);sMois=s.SubString(3,2);break;//0102
	}
	mois=sMois.ToInt();
	if(mois<1 || mois >12)
	{
		MessageBox(Handle,L_ErrMois.c_str(),T->L_Erreur.c_str(),
				MB_OK|MB_ICONSTOP);
		return false;
	}
	jour=sJour.ToInt();
	nbJour=jourDuMois[mois];
	if(jour <0 || jour>nbJour)
	{
		MessageBox(Handle,L_ErrNbJour.c_str(),T->L_Erreur.c_str(),
				//MessageBox(Handle,"Erreur sur nombre de jours du mois","ERREUR",
				MB_OK|MB_ICONSTOP);
		return false;
	}
	LaGrille->Cells[col][row]=AffJourMois(jour,mois);
	return true;
}
//---------------------------------------------------------------------
bool __fastcall TForme00Frm::GrilleCarPermis(int col,int row,char &type,char *permis)
{
	AnsiString s;
	char buf[100];
	s=LaGrille->Cells[col][row];
	type=' ';
	if(s.Length()>0)
	{
		s=s.Trim();
		s=s.UpperCase();
		for(unsigned n=0;n<strlen(permis);n++)
		{
			if(s[1]==permis[n]) {type=permis[n];break;}
		}
	}
	if(type==' ')
	{
		sprintf(buf,"%s non choisi %c par défaut",permis,permis[0]);
		MessageBox(Handle,buf,"CORRECTION",MB_OK|MB_ICONEXCLAMATION);
		type=permis[0];
	}
	LaGrille->Cells[col][row]=type;
	return true;
}
//---------------------------------------------------------------------
bool __fastcall TForme00Frm::GrilleEmpLTType(int col,int row,char &remb,char &freq)
{
	AnsiString s=GrilleChaine(col,row);
//char freq;  //Annuel Semestriel Trimestriel Mensuel
//char remb;  //Constant Variablz
	bool correctF=false;
	bool correctR=false;
	if(s.Length()==2)
	{
		s=s.LowerCase();
		remb=s[1];
		if(remb=='c'||remb=='v'||remb=='d') //120407
		correctR=true;
		freq=s[2];

		if(freq=='a'||freq=='s'||freq=='t'||freq=='m')
		correctF=true;
	}
	if(correctF==true && correctR==true) return true;
	MessageBox(Handle,"Erreur sur type cv astm","ERREUR",MB_OK|MB_ICONSTOP);
	return false;
}
//----------------------------------------------------------------------------
//Reaffiche correctement
//----------------------------------------------------------------------------
void __fastcall TForme00Frm::ReAffFloat(int col, int row,int digits)
{
	float val;
	val=GrilleFloat(col,row);
	LaGrille->Cells[col][row]=Aff(val,digits);
}
//----------------------------------------------------------------------------
void __fastcall TForme00Frm::ReAffInt(int col, int row)
{
	int val;
	val=GrilleInt(col,row);
	LaGrille->Cells[col][row]=Aff(val);
}
//----------------------------------------------------------------------------
// Reaffiche une grille en Changeant la précision
//----------------------------------------------------------------------------
void __fastcall TForme00Frm::ChangePrecision(TStringGrid *SG,int digits,int c0,int r0)
{
	int c,r;
	int n;
	AnsiString as;
	double val;
	AnsiString blanc=AnsiString(" ");
	for(c=c0;c<SG->ColCount;c++)
	{
		for(r=r0;r<SG->RowCount;r++)
		{
			as=SG->Cells[c][r];
			if(as.Length()==0) continue;
			n=as.Pos(blanc);
			while(n>0)
			{
				as.Delete(n,1);
				n=as.Pos(blanc);
			}
			val=as.ToDouble();
			SG->Cells[c][r]=FloatToStrF(val,ffNumber,7,digits);
		}
	}
}
//----------------------------------------------------------------------------
// Vide les Grilles
//----------------------------------------------------------------------------
void __fastcall TForme00Frm::VideLesGrilles(void)
{
	for(int g=0;g<GrilleX;g++)
	VideGrille(LesGrilles[g]);
}
//----------------------------------------------------------------------------
void __fastcall TForme00Frm::VideGrille(TStringGrid *grille)
{
	for(int r=1;r<grille->RowCount;r++)
	{
		grille->Objects[0][r]=NULL;
		for(int c=0;c<grille->ColCount;c++)
		grille->Cells[c][r]="";
	}
}
//----------------------------------------------------------------------------
// Modif
/*
 IlYaGrilleModif à SUPPRIMER il suffit de tester si LabelModifie->Visible=true
 cf Grille0Click
 */

//---------------------------------------------------------------------
bool __fastcall TForme00Frm::IlYaGrilleModif(void)
{
	for(int g=0;g<GrilleX;g++)
	{
		if(GrilleModif[g] ==true) return true;
	}
	return false;
}

//---------------------------------------------------------------------
void __fastcall TForme00Frm::MazModif(void)
{
	for(int g=0;g<GrilleX;g++)
	GrilleModif[g] =false;
}

//---------------------------------------------------------------------
//      verifie l'absence de doublon dans la colonne
//  créé si necessaire Doublon(TStringGrid* grille,int col1,int col2,int row)
//---------------------------------------------------------------------
bool __fastcall TForme00Frm::Doublon(TStringGrid* grille,int col,int row)
{
	AnsiString s,t;
	int res;
	s=grille->Cells[col][row];
	s=s.Trim();

	for(int r=1;r<grille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(r==row) continue;
		t=grille->Cells[2][r];
		t=t.Trim();
		res=s.AnsiCompare(t);
		if(res==0)
		{
			MessageBox(Handle,L_NomDonne.c_str(),T->L_Erreur.c_str(),MB_OK|MB_ICONEXCLAMATION);
			//MessageBox(Handle,"Nom déjà donné ","Erreur",MB_OK|MB_ICONEXCLAMATION);
			return true;
		}
	}
	return false;
}

//EXCEL
//exporte vers excel
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	EX->EcritGrilleFichier(LaGrille,TitreGrille);
	EX->FermerFichier();
	//fermer ici A FAIRE
}
/*
 rep=EX->DemarreExcel(); pour test
 if(rep==false) return;

 EX->EcritGrille(LaGrille);
 ///(ac) déplacé en privé dans EcritGrille ()
 EX->Quitter();
 */
/*
 //importe depuis excel
 //---------------------------------------------------------------------------
 void __fastcall TForme00Frm::XLClick(TObject *Sender)
 {
 bool rep;
 bool visible;

 visible=EX->EstVisible;
 //    QuelExcelCSVFrm->RGVisible->Enabled=false;

 rep=EX->DemarreExcel();
 if(rep==false)
 {
 EX->EstVisible=visible;
 //        QuelExcelFrm->RGVisible->Enabled=true;
 return;
 }

 EX->EstVisible=true;

 EX->EcritGrille(LaGrille);
 EX->Quitter();
 EX->Excel.OleFunction("Quit");

 EX->OuvreClasseur();
 EX->LitGrille(LaGrille);

 EX->EstVisible=visible;

 LabelModifie->Visible = true;

 }
 */
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// METHODES A CREER
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::Personnaliser(void)
{	ShowMessage("Méthode Personnaliser NON définie");}
//-------------------------------------------------------------------------
void __fastcall TForme00Frm::DefinirLesGrilles(void)
{	ShowMessage("Méthode DefinirLesGrilles   NON définie");}
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::IniGrille(TStringGrid *grille)
{	ShowMessage("Méthode IniGrille  NON définie");}
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::SaisirCell(int col,int row)
{
//	CellAVerifier=true;
}
/*
 détermine si cellule est éditable par defaut oui
 */
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::VersGrille(TStringGrid *grille)
{	ShowMessage("Méthode VersGrille NON définie");}
//-----------------------------------------------------------------------------
void __fastcall TForme00Frm::DeGrille(TStringGrid *grille)
{	ShowMessage("Méthode DeGrille   NON définie");}
//-----------------------------------------------------------------------------
bool __fastcall TForme00Frm::ControleCell(int col,int row)
{	return true;}
/*
 ControleCell
 est spécifique
 peut verifier le contenu de la cellule
 notamment l'absence de doublon
 cree si nouveau l'objet (eg item) et met son adresse dans LaGrille->Objects[0][row]
 */
//-----------------------------------------------------------------------------
bool __fastcall TForme00Frm::ControleGrille(void)
{
//	ShowMessage("Méthode ControleGrille NON définie");
	return true;
}
/*
 A supprimer remplacé par Stocker
 */
//---------------------------------------------------------------------------
/*
 Mauvais nom de Bouton:BoutAnnulClick
 */
//                           Stocker
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::BtBnStockerClick(TObject *Sender)
{
	bool rep;
	DerniereCell();
	if(LabelModifie->Visible==false) return;

	rep=Stocker();
	if(rep==true) LabelModifie->Visible=false;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
/* Stocker
 verifie la deniere cellule

 si il y a modification dans la/les grilles
 controle la/les grilles
 si erreur
 envoie les erreurs dans ErreurFrm
 indique OnContinue=true pour que FormActivate ne
 mette pas LabelModifie=false au retour de ErreurFrm->Show()
 renvoie false
 sinon
 met le contenu des grilles dans les objets(eg item)
 envoie sur fichier
 LabelModifie->Visible=false
 OnContinue=           false
 renvoie true
 sinon
 renvoie true
 Est appelé par BoutonStocker en fait BoutAnnulClick
 par FormCloseQuery
 */
//---------------------------------------------------------------------------
bool __fastcall TForme00Frm::Stocker(void)
{
	{	ShowMessage("Méthode Stocker  NON définie");}
	return true;
}
//---------------------------------------------------------------------------
// ligne
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::SelLigne(void)
{
	PlageCellules.Left=0;
	PlageCellules.Top=LaGrille->Row;
	PlageCellules.Bottom=LaGrille->Row;
	PlageCellules.Right=LaGrille->ColCount;
	LaGrille->EditorMode = false;
	LaGrille->Selection = PlageCellules;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::DeSelLigne(void)
{
	PlageCellules.Left=LaGrille->Col;
	PlageCellules.Right=LaGrille->Col;
	LaGrille->Selection = PlageCellules;
	LaGrille->EditorMode = true;
}
//---------------------------------------------------------------------------
void __fastcall TForme00Frm::SupprimerLigne(int rASupprimer)
{
	int r;
//	r0=LaGrille->Row;
	for(r=LaGrille->Row;r<LaGrille->RowCount;r++)
	{
		LaGrille->Rows[r] =LaGrille->Rows[r+rASupprimer];
		if(RowVide(r)==false)
		{
			LaGrille->Objects[0][r]=LaGrille->Objects[0][r+rASupprimer];
			LaGrille->Cells[0][r]=r;
		}
		else
		{
			LaGrille->Objects[0][r]=NULL;
			LaGrille->Cells[0][r]="  ";
		}
	}
	ValueAvant=""; //evite les pb de creation d'objet intempestif cf Landes Emprunt
	LaGrille->RowCount-=rASupprimer;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------/*
void __fastcall TForme00Frm::BtBnImpClick(TObject *Sender)
{

	QRGrille00Frm->LaGrille=LaGrille;
	QRGrille00Frm->TitreEtat->Caption=TitreGrille; //Forme00Frm->Caption;
	QRGrille00Frm->TypeCol=TypeCol;
	QRGrille00Frm->Initialise();
	QRGrille00Frm->QR->Preview();
}
//---------------------------------------------------------------------------

/*
 //---------------------------------------------------------------------------
 void __fastcall TForme00Frm::BtBnImpClick(TObject *Sender)
 {
 int c,r;
 AnsiString asLambda,asBlanc;
 AnsiString caption;
 int largeur[50];
 int pos;
 int pos0=   4;
 int l;
 float alpha=10./64.;   //64 pixels largeur std colonne grille ->10
 int larTrait=LaGrille->Width*alpha;
 //si largeur d'une colonne est trop petite l'agrandir
 for(c=0;c<LaGrille->ColCount;c++)
 {
 largeur[c]=LaGrille->ColWidths[c];
 if(largeur[c]<=10) largeur[c]*=2;
 largeur[c]*=alpha;
 }
 asBlanc="                                           ";
 FBrouillon->Demarre();
 FBrouillon->Titre1(Caption.c_str());
 // M pour dire de ne pas imprimer en Gras G
 FBrouillon->TypeImp("Courier",8,clBlack,'M');
 //Trait
 FBrouillon->Trait(larTrait);

 //ligne en tete: du texte
 r=0;
 pos=pos0;
 for(c=0;c<LaGrille->ColCount;c++)
 {
 pos+=largeur[c];//LaGrille->ColWidths[c]*alpha;
 l=LaGrille->Cells[c][r].Length();
 if(l)
 asLambda.Insert(LaGrille->Cells[c][r],pos-l);
 asLambda+=asBlanc;
 }
 FBrouillon->Memo1->Lines->Add(asLambda.TrimRight());
 FBrouillon->Trait(larTrait);

 for(r=1;r<LaGrille->RowCount;r++)
 {
 asLambda=asBlanc;
 pos=pos0;
 for(c=0;c<LaGrille->ColCount;c++)
 {
 if(TypeCol[c]=='T'|| TypeCol[c]=='0')
 {
 l=LaGrille->Cells[c][r].Length();
 if(l)
 asLambda.Insert(LaGrille->Cells[c][r],pos);
 pos+=largeur[c];//LaGrille->ColWidths[c]*alpha;
 }
 else //(TypeCol[c]=='N')
 {
 pos+=largeur[c];//LaGrille->ColWidths[c]*alpha;
 l=LaGrille->Cells[c][r].Length();
 if(l==0) continue;
 asLambda.Insert(LaGrille->Cells[c][r],pos-l);
 }
 asLambda+=asBlanc;
 }
 FBrouillon->Memo1->Lines->Add(asLambda.TrimRight());
 }
 FBrouillon->Trait(larTrait);

 FBrouillon->Blanc(5);
 FBrouillon->Show();
 }
 */
//---------------------------------------------------------------------------
// ReportDroit
//---------------------------------------------------------------------------
//float
void __fastcall TForme00Frm::RepDroit(TStringGrid *grille,int digits)
{
	int c,c0,r0;
	c0=grille->Col;
	r0=grille->Row;
	ReAffFloat(c0,r0,digits);
	for(c=c0+1;c<grille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		grille->Cells[c][r0]=grille->Cells[c0][r0];
	}
	Grille0Click(this);
}
//---------------------------------------------------------------------------
//le report est il possible dans cellule c r ?
//---------------------------------------------------------------------------
bool __fastcall TForme00Frm::RepPossible(int c,int r)
{
	AnsiString as;
	as=LaGrille->Cells[c][r];
	if(as.Length()>1 && ChBRepTout->Checked==false) return false;

	LabelModifie->Visible=true;
	return true;
}

//-----------------------------------------------------------------------------
void TForme00Frm::TexteChaine(void) {
	L_ErrDate = T->TrouveTexte("Forme00Frm", "L_ErrDate");
	L_ErrMois = T->TrouveTexte("Forme00Frm", "L_ErrMois");
	L_ErrAn = T->TrouveTexte("Forme00Frm", "L_ErrAn");
	L_ErrNbJour = T->TrouveTexte("Forme00Frm", "L_ErrNbJour");
	L_NomDonne = T->TrouveTexte("Forme00Frm", "L_NomDonne");

}
//--------------------------------------------
void TForme00Frm::IniCaption(void) {
	BtClasser->Caption = T->LC_BtClasser;
	Forme00Frm->Caption = LC_Forme00Frm;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	ChBRepTout->Caption = T->LC_ChBRepTout;
}
//--------------------------------------------
void TForme00Frm::TexteCaption(void) {
	LC_BtClasser = T->TrouveCaption("CL_Trad", "LC_BtClasser");
	LC_Forme00Frm = T->TrouveCaption("Forme00", "LC_Forme00Frm");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_ChBRepTout = T->TrouveCaption("CL_Trad", "LC_ChBRepTout");

	IniCaption();

}
//--------------------------------------------

