//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "GereEtat.h"
#include "Forme0.h"
#include "TVDico.h"
#include "Resultat.h"
#include "QRSortieQuant.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"
#include "Main.h"

#include "DefEtatSortie.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefEtatSortieFrm *DefEtatSortieFrm;
extern CL_Trad *T;
extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TDefEtatSortieFrm::TDefEtatSortieFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//personnaliser

//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::Personnaliser(void)
{
	LabCatVar->Caption=EtatSortie->Nom;
	BtBnTva->Visible=false;
	BtBnUnite->Visible=false;

	Grille0->ColCount=6; //181109
//    if(ES->Version >=134 )Grille0->ColCount=7;    //160608
//    Grille0->ColCount=7;    //160608
	Grille0->Rows[0]->CommaText=L_Titre=";//.,.,CATEGORIE,FAMILLE";
	//Grille0->Rows[0]->CommaText=".,.,CATEGORIE,FAMILLE";
	strcpy(TypeCol,"00T00N00");//pour entrer titre mais risque ! mineur

	ColNom=2;
	if(Nature==ETAT)
	{
		BtClasser->Visible=true;
		BtClasser->Enabled=true;
		BtBnResultat->Visible=true;
	}
	else //COMPARAISON
	{
		BtClasser->Visible=false;
		BtBnResultat->Visible=false;
	}
	//ColTva=3;

	//ColSys=;
	//ColPrix=;
}
//---------------------------------------------------------------------------
//AffEtatSortie
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::AffEtatSortie(void)
{

	TVDicoFrm->Visible=true;
	VersGrille(LaGrille);

}
//-----------------------------------------------------------------------------
// IniGrille
//-----------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[]= {20,10,128,128,128,20,20}; //160608
	int c;//,cMax;
	grille->FixedCols=2;
	grille->FixedRows=1;
	for(c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	grille->Width=l+28; //place pour l'ascenseur

	// attention col row
	grille->Rows[0]->CommaText=L_Titre2;//=".,.,NOM,CATEGORIE,FAMILLE";
	//grille->Rows[0]->CommaText=".,.,NOM,CATEGORIE,FAMILLE";
	if(grille->ColCount==6)
	grille->Cells[5][0]="Precision";
//	grille->Cells[6][0]="Couleur";

	AjoutRow=true;
	CellAVerifier=true;

}
//-----------------------------------------------------------------------------
//VersGrille
//------------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	AnsiString value,as,asType;
	CL_Elt *elt;
	CL_Bestiaux *bestiaux;
	CL_Poste *poste;
	CL_Vecteur<CL_Elt> *vecteur;
	static char LesNoms[20][41];
	int l=0;
	if(EtatSortie==NULL) return;

	vecteur=EtatSortie->V_Elt;
	grille->RowCount=vecteur->Nbelt+3;
	for( r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		elt=vecteur->Vecteur[r];
		if(elt->NoFamille==FORME)
		{
			if(elt->NoItem==TRAIT) {elt=EltTrait;vecteur->Vecteur[r]=elt;}
			if(elt->NoItem==BLANC) {elt=EltBlanc;vecteur->Vecteur[r]=elt;}
		}
		grille->Objects[0][row]=(TObject*)elt;
		grille->Cells[0][row]=row;
		//rustine pour elt correspondant à bestiaux elt->NoCategorie ...
		//TVDico/ClickEtat a mis dans elt->NoCategorie elt->NoType
		// pour les etats je stocke seulement No NoFamille NoCategorie NoItem
		// et je changerai avec une nouvelle version!!!
		if(elt->NoFamille==MVT)
		{
			elt->NoType=elt->NoCategorie;
			bestiaux=V_Bestiaux->trouve(elt->NoItem);
			asType=TVDicoFrm->TrouveMvtType(elt->NoType);
			poste=V_Poste->trouve(elt->NoFamille);
			grille->Cells[2][row]=bestiaux->Nom;
			grille->Cells[3][row]=asType;
			grille->Cells[4][row]=poste->Nom;
			as=bestiaux->Nom+ "  "+asType;
			strncpy(LesNoms[l],as.c_str(),40);
			elt->Nom=LesNoms[l];
			if(l<19)l++;
		}
		else
		{
			grille->Cells[2][row]=elt->Nom;
			grille->Cells[3][row]=elt->NomCat;
			grille->Cells[4][row]=elt->NomFamille;
			if(grille->ColCount>5)
			grille->Cells[5][row]=elt->Digits;

		}
	}
	CellInitiale(2,1);
}
//---------------------------------------------------------------------------
//a personnaliser
//---------------------------------------------------------------------------
//void __fastcall TDefItemFrm::AffItem(int row,CL_Item *item)

//------------------------------------------------------------------------------
//sup ligne
//------------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_Elt* elt;
	int rep;
	if(RGModifiable->ItemIndex==0)return;
	elt=(CL_Elt*)LaGrille->Objects[0][r];
	//if(elt==NULL) return;
	SelLigne();
	rep=MessageBox(Handle,L_SupQ.c_str(),L_Sup.c_str(),MB_YESNO);
	//rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		if(elt!=NULL) elt->Flag='S';
		SupprimerLigne();
		LabelModifie->Visible=true;
	}
	DeSelLigne();
}
//------------------------------------------------------------------------------
//DeGrille
//------------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::DeGrille(TStringGrid *grille)
{
	int n,row;
	CL_Elt *elt;
	CL_Vecteur<CL_Elt> *vecteur;
	char *chaine;
	vecteur=EtatSortie->V_Elt;
	vecteur->Nbelt=0;
	vecteur->NoX=0;
	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		elt=(CL_Elt*)grille->Objects[0][row];
		if(elt==NULL)
		{
			elt=new CL_Elt();
			elt->NoItem=TITRE;
			grille->Objects[0][row]=(TObject*)elt;
		}
		if(elt->NoItem==TITRE)
		{
			n=grille->Cells[2][row].Length();
			n++;
			chaine=new char[n];
			strcpy(chaine,grille->Cells[2][row].c_str());
			elt->Nom=chaine;
		}
		if(grille->ColCount>5)
		elt->Digits=grille->Cells[5][row].ToIntDef(0); //160808
		vecteur->ins(elt);
	}
}
//---------------------------------------------------------------------------
// ControleCell masque DefItem ControleCell
//---------------------------------------------------------------------------
bool __fastcall TDefEtatSortieFrm::ControleCell(int col,int row)
{
	return true;
}
//---------------------------------------------------------------------------
//LBservice entree Trait Titre ligne Blanche
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::LBServiceClick(TObject *Sender)
{
	int n=LBService->ItemIndex;
	if(RGModifiable->ItemIndex==0)return;

	LabelModifie->Visible=true;
	switch(n)
	{
		case 0: Inserer(); break;
		case 1: BtSupClick(this); break;
		case 2: PlaceEltForme(EltBlanc);break;
		case 3: PlaceEltForme(EltTrait);break;
		case 4: PlaceEltForme(EltTitre);break;
	}

}
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::Inserer(void)
{
	int r;
	int rIns=LaGrille->Row;
	LaGrille->RowCount++;
	//décaler vers le bas
//    for(r=LaGrille->RowCount;r>LaGrille->Row-1;r--)
	for(r=LaGrille->RowCount;r>rIns;r--)
	{
		if(r==0) break;
		LaGrille->Rows[r]=LaGrille->Rows[r-1];
		LaGrille->Objects[0][r]=LaGrille->Objects[0][r-1];
		if(RowVide(r)==false)
		LaGrille->Cells[0][r]=r;
		else
		LaGrille->Objects[0][r]=NULL;
	}
	rIns;
	//mettre rien à la ligne insérée
	LaGrille->Objects[0][rIns]=NULL;
	LaGrille->Cells[2][rIns]="";
	LaGrille->Cells[3][rIns]="";
	LaGrille->Cells[4][rIns]="";
	AjouterRow();
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::PlaceEltForme(CL_Elt *eltForme)
{
	int row;
	CL_Elt *elt;
	int rep;
	row=LaGrille->Row;

	if( LaGrille->Objects[0][row]==NULL)
	elt=new CL_Elt();
	else
	{
		SelLigne();
		rep=MessageBox(Handle,L_ModifQ.c_str(),L_Modif.c_str(),MB_YESNO);
		//rep=MessageBox(Handle," Je remplace Vous êtes sur ?","MODIFICATION",MB_YESNO);
		if(rep==ID_NO)
		return;
		DeSelLigne();
		elt=(CL_Elt*)LaGrille->Objects[0][row];
	}
	memcpy(elt,eltForme,sizeof(CL_Elt));

	LaGrille->Objects[0][row]=(TObject*)elt;

	LaGrille->Cells[0][row]=row;
	LaGrille->Cells[2][row]=elt->Nom;
	LaGrille->Cells[3][row]=elt->NomCat;
	LaGrille->Cells[4][row]=elt->NomFamille;
	ColM[LaGrille->Tag]=LaGrille->Col;
	RowM[LaGrille->Tag]=LaGrille->Row;
//    AjouterRow();
//	LaGrille->Row++;
	LaGrille->Col=2;
}
/*
 //---------------------------------------------------------------------------
 void __fastcall TDefEtatSortieFrm::PlaceEltForme(CL_Elt *eltForme)
 {
 int row;
 CL_Elt *elt;

 row=LaGrille->Row;

 if( LaGrille->Objects[0][row]==NULL)
 elt=new CL_Elt();
 else
 elt=(CL_Elt*)LaGrille->Objects[0][row];

 memcpy(elt,eltForme,sizeof(CL_Elt));

 LaGrille->Objects[0][row]=(TObject*)elt;

 LaGrille->Cells[0][row]=row;
 LaGrille->Cells[2][row]=elt->Nom;
 LaGrille->Cells[3][row]=elt->NomCat;
 LaGrille->Cells[4][row]=elt->NomFamille;
 ColM[LaGrille->Tag]=LaGrille->Col;
 RowM[LaGrille->Tag]=LaGrille->Row;
 AjouterRow();
 LaGrille->Row++;
 LaGrille->Col=2;
 }
 */
//---------------------------------------------------------------------------
// possible O/N de modifier
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::RGModifiableClick(TObject *Sender)
{
	if(RGModifiable->ItemIndex==0)
	{
		RGModifiable->Color=clRed;
		Grille0->Options>>goAlwaysShowEditor;
	}
	else
	{
		RGModifiable->Color=clLime;
		Grille0->Options<<goAlwaysShowEditor;
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::PossibleModifier(bool modifiable)
{
	if(modifiable==false)
	{
		RGModifiable->ItemIndex=0;
		RGModifiable->Color=clRed;
		BtClasser->Enabled=false;
	}
	else
	{
		RGModifiable->ItemIndex=1;
		RGModifiable->Color=clLime;
		BtClasser->Enabled=true;
	}
}
//---------------------------------------------------------------------------
//Resultat
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::BtBnResultatClick(TObject *Sender)
{
	TVDicoFrm->Visible=false;
	DeGrille(LaGrille);

	if(Global==ENSEMBLE) //080202
	QRSortieQuantFrm->Etat(EtatSortie,EnsembleEnCours->Total);
	else
	QRSortieQuantFrm->Etat(EtatSortie,AgriEnCours);

}
//---------------------------------------------------------------------------

void __fastcall TDefEtatSortieFrm::BtBnDicoClick(TObject *Sender)
{
	TVDicoFrm->Complet=true;
	//rustine 110306
	TVDicoFrm->BtBnRafraichirClick(this);
	TVDicoFrm->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::BtBnVideToutClick(TObject *Sender)
{
	int r;
	int repMB;
	CL_Elt *elt;
	repMB=MessageBox(Handle,L_EffaceQ.c_str(),L_Efface.c_str(),MB_YESNO|MB_ICONQUESTION);
	//repMB=MessageBox(Handle,"j'efface TOUT ?","EFFACER TOUT LE TABLEAU",MB_YESNO|MB_ICONQUESTION);
	if(repMB==IDNO) return;

	for(r=0;r<LaGrille->RowCount;r++)
	{
		elt=(CL_Elt*)LaGrille->Objects[0][r];
		delete elt;
		elt=NULL;
		LaGrille->Objects[0][r]=NULL;
	}

	VideGrille(LaGrille);
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
//quitter
//---------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	TVDicoFrm->Visible=false;

	DerniereCell();
	if(LabelModifie->Visible==false ) return;
	if(RGModifiable->ItemIndex==0) return;

	rep=MessageBox(Handle,T->L_DonModifQ.c_str(),L_Modif.c_str(),
			//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
			MB_YESNOCANCEL|MB_ICONEXCLAMATION);
	switch(rep)
	{
		case ID_YES:
		DeGrille(LaGrille);
		break;
		case ID_CANCEL:
		CanClose=false;
		break;
		case ID_NO:
		VideGrille(LaGrille);
		CanClose=true;
		VersGrille(LaGrille);
		LabelModifie->Visible=false;
		break;
	}

}
//---------------------------------------------------------------------------
void TDefEtatSortieFrm::TexteChaine(void) {
	L_Titre = T->TrouveTexte("DefEtatSortieFrm", "L_Titre");
	L_Titre2 = T->TrouveTexte("DefEtatSortieFrm", "L_Titre2");
	Grille0->Rows[0]->CommaText = L_Titre2;

}
//--------------------------------------------
void TDefEtatSortieFrm::IniCaption(void) {
	BtBnDico->Caption = T->LC_BtDico;
	BtBnDico->Caption = T->LC_BtDico;
	DefEtatSortieFrm->Caption = T->LC_DefEtatSortieFrm;
	RGModifiable->Caption = T->LC_RGModifiable;
	BtBnResultat->Caption = T->LC_BtBnResultat;
	BtBnDico->Caption = T->LC_BtBnDico;
	LabelModifie->Caption = T->LC_LabelModifie;
	LBService->Items->Strings[0] = LC_Inserer;
	LBService->Items->Strings[1] = LC_SupLigne;
	LBService->Items->Strings[2] = LC_LigneVide;
	LBService->Items->Strings[3] = LC_Trait;
	LBService->Items->Strings[4] = LC_Titre;

	RGModifiable->Items->Strings[0] = T->LC_Oui;
	RGModifiable->Items->Strings[1] = T->LC_Non;

}
//--------------------------------------------
void TDefEtatSortieFrm::TexteCaption(void) {
	LC_BtDico = T->TrouveCaption("CL_Trad", "LC_BtDico");
	LC_DefEtatSortieFrm = T->TrouveCaption("CL_Trad", "LC_DefEtatSortieFrm");
	LC_RGModifiable = T->TrouveCaption("CL_Trad", "LC_RGModifiable");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_BtBnDico = T->TrouveCaption("CL_Trad", "LC_BtBnDico");
	LC_LabelModifie = T->TrouveCaption("CL_Trad", "LC_LabelModifie");
	LC_RGModifiable = T->TrouveCaption("CL_Trad", "LC_RGModifiable");

	LC_Inserer = T->TrouveCaption("DefEtatSortie", "LC_Inserer");
	LC_SupLigne = T->TrouveCaption("DefEtatSortie", "LC_SupLigne");
	LC_LigneVide = T->TrouveCaption("DefEtatSortie", "LC_LigneVide");
	LC_Trait = T->TrouveCaption("DefEtatSortie", "LC_Trait");
	LC_Titre = T->TrouveCaption("DefEtatSortie", "LC_Titre");

	RGModifiable->Items->Strings[0] = T->LC_Oui;
	RGModifiable->Items->Strings[1] = T->LC_Non;
	IniCaption();
}
//--------------------------------------------

void __fastcall TDefEtatSortieFrm::BtBnNoteClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="DefEtatSortie";//ne pas traduire
	NoteAgriFrm->EtatSortie=EtatSortie;
	NoteAgriFrm->Memo->Text=EtatSortie->Notes;
	NoteAgriFrm->Caption=EtatSortie->Nom;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TDefEtatSortieFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1820;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TDefEtatSortieFrm::BtBnAideClick(TObject *Sender)
{
//    HelpContext=1820; voir GereEtat ou GereComparaison

	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

void __fastcall TDefEtatSortieFrm::Grille0DrawCell(TObject *Sender,
		int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	CL_Elt *elt;
	TColor coul;

	if(ACol!=6) return;
	elt=(CL_Elt*)Grille0->Objects[0][ARow];
	if(elt==NULL) return;

	coul=elt->Coul;
//coul=clRed;
	Grille0->Canvas->Brush->Color=coul;
	Grille0->Canvas->Brush->Style=bsSolid;
	Grille0->Canvas->Rectangle(Rect);

}
//---------------------------------------------------------------------------
//ne sert à rien-> a sup
//-----------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::SaisirCell(int col,int row)
{
	CL_Elt *elt;

	elt=(CL_Elt*)Grille0->Objects[0][row];
	if(elt==NULL) return;

	if(col!=6)return;
	if(ColorDialog->Execute()==true)
	elt->Coul=ColorDialog->Color;
	Grille0->Col--;
}

//-----------------------------------------------------------------------------
void __fastcall TDefEtatSortieFrm::Grille0KeyPress(TObject *Sender,
		char &Key)
{
	if(Grille0->Col!=5)return;
	if(RGModifiable->ItemIndex==0) {Key=0;return;}
	if(Key == '0' || Key=='1' ||Key=='2')return;
	if(Key=='\b')return;
	Key=0;
}
//---------------------------------------------------------------------------

