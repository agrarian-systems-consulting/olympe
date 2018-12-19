//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Forme00.h"
/*
 #include "Indicateur.h"
 #include "DefEtatSortie.h"
 #include "Resultat.h"
 #include "Compilateur.h"
 #include "LBCompAgri.h"
 #include "AgriSaisieEnum.h"

 #include "AgriSaisie.h"
 #include "DefAction.h"

 //#include "Graph.h"
 #include "SorRap.h"
 */
#include "Raccourci.h"

#include "RaccourciDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern CL_ES *ES;

//TSorRapPrepFrm *SorRapPrepFrm;
TRaccourciDefFrm *RaccourciDefFrm;
//---------------------------------------------------------------------------
__fastcall TRaccourciDefFrm::TRaccourciDefFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TRaccourciDefFrm::FormCreate(TObject *Sender)
{
	int r;

	SLstRaccourci= new TStringList;

	SG->ColCount=6;
	SG->RowCount=21;

	SG->ColWidths[0]=32;
	SG->ColWidths[1]=128;
	SG->ColWidths[2]=128;
	SG->ColWidths[3]=128;
	SG->ColWidths[4]=128;
	SG->ColWidths[5]=32;

	SG->Cells[1][0]="Famille";
	SG->Cells[2][0]="Categorie";
	SG->Cells[3][0]="Nom";
	SG->Cells[4][0]="Alias";
	SG->Cells[5][0]="G/T";

	for(r=0;r<SG->RowCount;r++)SG->Cells[0][r]=r;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TRaccourciDefFrm::FormActivate(TObject *Sender)
{
	ES->IniV_Elt();
	Forme0Frm->CreeTVToutElt(TV,AgriEnCours,true); //Complet);
}
//---------------------------------------------------------------------------
void __fastcall TRaccourciDefFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
//	TVDicoFrm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TRaccourciDefFrm::SGClick(TObject *Sender)
{
//int r,c;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRaccourciDefFrm::RetourDeTVDico(char *nomFamille, char* nomCategorie,
		char* nom) {
	int r; //,c;
	r = SG->Row;
	SG->Cells[1][r] = nomFamille;
	SG->Cells[2][r] = nomCategorie;
	SG->Cells[3][r] = nom;
	SG->Cells[4][r] = nom;
	SG->Row++;
}
//---------------------------------------------------------------------------
void __fastcall TRaccourciDefFrm::SGKeyPress(TObject *Sender, char &Key)
{
	int c,r;
	c=SG->Col;
	r=SG->Row;
	if(!(c==4 ||c==5)) {Key=0;return;}
	if(c==4) return;

	//G ou T  Graphique Table
	if(Key=='t'||Key=='T') {Key=0;SG->Cells[c][r]="T";return;}
	if(Key=='G'||Key=='g') {Key=0;SG->Cells[c][r]="G";return;}
	Key=0;
	LabelModifie->Visible=true;

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TRaccourciDefFrm::TVChange(TObject *Sender, TTreeNode *Node)
{
	int r; //,c;
	TTreeNode *choix;
	CL_Elt *elt;

	choix=Node;
	if(choix->Level<2)
	return;
	elt=(CL_Elt*)choix->Data;
	if(elt==NULL) return;

	r=SG->Row;
	SG->Cells[1][r]=elt->NomFamille;
	SG->Cells[2][r]=elt->NomCat;
	SG->Cells[3][r]=elt->Nom;
	SG->Cells[4][r]=elt->Nom;
	SG->Objects[0][r]=(TObject*)elt;
	SG->Row++;

	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TRaccourciDefFrm::Button1Click(TObject *Sender)
{
	RaccourciFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TRaccourciDefFrm::BtBnVideToutClick(TObject *Sender)
{
	int r,c;
	int rep;
	rep=MessageBox(Handle," Je supprime TOUT Vous êtes sur ?","SUPPRESSION",MB_YESNO);
//	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO)
	return;

	for(r=1;r<SG->RowCount;r++)
	{
		SG->Objects[0][r]=NULL;
		for(c=1;c<SG->ColCount;c++)
		SG->Cells[c][r]="";
	}
	SG->Row=1;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRaccourciDefFrm::BtSupClick(TObject *Sender)
{
	int r,r0,c;
	r0=SG->Row;
	for(r=r0;r<SG->RowCount-1;r++)
	{
		SG->Objects[0][r]=SG->Objects[0][r+1];
		for(c=1;c<SG->ColCount;c++)
		SG->Cells[c][r]=SG->Cells[c][r+1];
	}
	r=SG->RowCount-1;
	for(c=1;c<SG->ColCount;c++)
	SG->Cells[c][r]="";
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRaccourciDefFrm::BtBnClBasClick(TObject *Sender)
{
	int c,r;
	TObject *object;
	AnsiString as;
	r=SG->Row;
	if(r==SG->RowCount) return;

	LabelModifie->Visible=true;
	object=SG->Objects[0][r];
	SG->Objects[0][r]=SG->Objects[0][r+1];
	SG->Objects[0][r+1]=object;
	for(c=1;c<SG->RowCount;c++)
	{
		as=SG->Cells[c][r];
		SG->Cells[c][r]=SG->Cells[c][r+1];
		SG->Cells[c][r+1]=as;
	}
	SG->Row++;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRaccourciDefFrm::BtBnClHautClick(TObject *Sender)
{
	int c,r;
	TObject *object;
	AnsiString as;
	r=SG->Row;
	if(r==1) return;

	LabelModifie->Visible=true;
	object=SG->Objects[0][r];
	SG->Objects[0][r]=SG->Objects[0][r-1];
	SG->Objects[0][r-1]=object;
	for(c=1;c<SG->RowCount;c++)
	{
		as=SG->Cells[c][r];
		SG->Cells[c][r]=SG->Cells[c][r-1];
		SG->Cells[c][r-1]=as;
	}
	SG->Row--;
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

void __fastcall TRaccourciDefFrm::BtBnSaveClick(TObject *Sender)
{
	if(LabelModifie->Visible==false) return;

	DeSG();
	EcrireFichier();
//??	FichierFrm->EcrireDonnees(FichierFrm->AsFicTrav.c_str());
	/*
	 bool erreur;
	 erreur=Verif();
	 if(erreur==true) return;
	 DeSG();
	 FichierFrm->EcrireDonnees(FichierFrm->AsFicTrav.c_str());
	 */
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRaccourciDefFrm::DeSG(void) {
	int r;
	CL_Elt *elt;
	SLstRaccourci->Clear();
	for (r = 1; r < SG->RowCount; r++) {
		elt = (CL_Elt*) SG->Objects[0][r];
		if (elt == NULL)
			continue;
		elt->NomNature = SG->Cells[4][r].c_str(); //Alias
		elt->Flag = SG->Cells[5][r][1]; //T ou G
		SLstRaccourci->AddObject(elt->NomNature, (TObject*) elt);
	}
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TRaccourciDefFrm::TailleSG(int r) {
	SG->Row++;
	if (r > SG->RowCount - 3) {
		SG->RowCount++;
		SG->Cells[0][r] = r;
		SG->Cells[0][r + 1] = r + 1;
		SG->Objects[0][r] = NULL;
		SG->Objects[0][r + 1] = NULL;
	}
}

//---------------------------------------------------------------------------
void TRaccourciDefFrm::VersSG(void) {
	int r;
	int n;
	CL_Elt *elt;
	SG->RowCount = 21;
	if (SLstRaccourci->Count > SG->RowCount)
		SG->RowCount = SLstRaccourci->Count + 5;
	for (r = 1; r < SG->RowCount; r++)
		SG->Cells[0][r] = r;

	for (n = 0, r = 1; n < SLstRaccourci->Count; n++, r++) {
		elt = (CL_Elt*) SLstRaccourci->Objects[n];
		SG->Objects[0][r] = SLstRaccourci->Objects[n];
		SG->Cells[0][r] = r;
		SG->Cells[1][r] = elt->NomFamille;
		SG->Cells[2][r] = elt->NomCat;
		SG->Cells[3][r] = elt->Nom;
		SG->Cells[4][r] = elt->NomNature; //Alias
		SG->Cells[5][r] = elt->Flag; //T ou G
	}
}

//---------------------------------------------------------------------------
void TRaccourciDefFrm::EcrireFichier(void) {
	int n, i, j;
	CL_Elt *elt;

	char* nomFich;
	nomFich = "c://OlympeInter//Wag2009//Raccourci.csv";

	ofstream fichier(nomFich);

	n = SLstRaccourci->Count;
	fichier << "Raccourcis" << ";\n";

	fichier << "nbRaccourci" << ";" << n << ";\n";

	for (n = 0; n < SLstRaccourci->Count; n++) {
		elt = (CL_Elt*) SLstRaccourci->Objects[n];
		fichier << elt->NomFamille << ";";
		fichier << elt->NomCat << ";";
		fichier << elt->Nom << ";";
		fichier << elt->NomNature << ";"; //Alias
		fichier << elt->Flag << ";\n"; //T ou G
	}
	fichier.close();
}
//---------------------------------------------------------------------------
void TRaccourciDefFrm::LireFichier(void) {
	int n, i, j;
	CL_Elt *elt;
	AnsiString as;
	char* nomFich;
	int nb;
	char *ptr;

	string s;
	/*
	 nomFich="c://OlympeInter//Wag2009//Raccourci.csv";
	 ifstream fichier(nomFich);
	 Fichier=fopen(nomFich,"r");
	 //    FichierFrm->LireChaine();

	 SLstRaccourci->Clear();
	 fichier >> s ;

	 as=FichierFrm->LireAsInt(nb);
	 for(n=0;n<nb;n++)
	 {
	 elt=new CL_Elt();
	 indic->Lire(Fichier);
	 DonFrm->SLstIndic->AddObject(indic->Nom,(TObject*)indic);
	 }
	 */
}

//-----------------------------------------------------------------------------

