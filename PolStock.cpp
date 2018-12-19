//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "Forme00.h"
#include "Erreur.h"
#include "PolStock.h"
/*
 //---------------------------------------------------------------------------

 #pragma package(smart_init)
 #include <stdio.h>
 #pragma hdrstop

 #include "Olympedec.h"
 #include "LesClassesApp.h"
 #include "Erreur.h"
 #include "AgriSaisie.h"

 #include "PolStock.h"
 //---------------------------------------------------------------------------
 #pragma package(smart_init)
 #pragma link "Forme00"
 #pragma resource "*.dfm"
 TPolStockFrm *PolStockFrm;
 */
CL_PolStock::CL_PolStock() {

	No = -1;
	Item = NULL;
	PcentStock = 0;
	Maxi = 0;
	PcentDeltaPrix = 0;
	PcentDecote = 0;
}
//---------------------------------------------------------------------------
CL_PolStock::CL_PolStock(CL_Item *item) {
	No = item->No;
	Item = item;
	PcentStock = 0;
	Maxi = 0;
	PcentDeltaPrix = 0;
	PcentDecote = 0;
}
//---------------------------------------------------------------------------
CL_PolStock::CL_PolStock(CL_PolStock *source) {
	No = source->Item->No;
	Item = source->Item;
	PcentStock = source->PcentStock;
	Maxi = source->Maxi;
	PcentDeltaPrix = source->PcentDeltaPrix;
	PcentDecote = source->PcentDecote;
}
//---------------------------------------------------------------------------
void CL_PolStock::AffRow(TStringGrid *grille, int r) {
	grille->Objects[0][r] = (TObject*) this;

	grille->Cells[0][r] = Forme00Frm->Aff(r);
	grille->Cells[1][r] = Item->Nom;
	grille->Cells[2][r] = Forme00Frm->Aff(Item->Prix, 2);
	grille->Cells[3][r] = Item->SysUnite->UTrans;
	grille->Cells[4][r] = Forme00Frm->Aff(PcentStock, 0); //Pcent vendu année suivante
	grille->Cells[5][r] = Forme00Frm->Aff(Maxi, 0); // maxi stockable
	grille->Cells[6][r] = Forme00Frm->Aff(PcentDeltaPrix, 0); // delta prix
	grille->Cells[7][r] = Forme00Frm->Aff(PcentDecote, 0); // decote

}
//---------------------------------------------------------------------------
bool CL_PolStock::EstCorrect(TStringGrid *grille, int r) {
	bool correct = true;
	float pcentStock; //,pcentDeltaPrix,pcentDecote;
	AnsiString as;

	Forme00Frm->LaGrille = grille;
	pcentStock = Forme00Frm->GrilleFloat(4, r);
//    maxi=           Forme00Frm->GrilleFloat(5,r);
//    pcentDeltaPrix= Forme00Frm->GrilleFloat(6,r);
//    pcentDecote=    Forme00Frm->GrilleFloat(7,r);
	if (pcentStock > 100) {
		correct = false;
		as = this->Item->Nom;
		as += " % Stocké > 100";
		ErreurFrm->Edit->Lines->Add(as);
	}
	/*
	 if(pcentDeltaPrix >200)
	 {
	 correct=false;
	 as=this->Item->Nom;
	 as+="% Augmentation de Prix  > 200";
	 ErreurFrm->Edit->Lines->Add(as);
	 }
	 if(pcentDecote <50)
	 {
	 correct=false;
	 as=this->Item->Nom;
	 as+="% Decote < 50";
	 ErreurFrm->Edit->Lines->Add(as);
	 }
	 */
	return correct;
}
//---------------------------------------------------------------------------
void CL_PolStock::LitRow(TStringGrid *grille, int r) {
	Forme00Frm->LaGrille = grille;
	PcentStock = Forme00Frm->GrilleFloat(4, r);
	Maxi = Forme00Frm->GrilleFloat(5, r);
	PcentDeltaPrix = Forme00Frm->GrilleFloat(6, r);
	PcentDecote = Forme00Frm->GrilleFloat(7, r);

}
//---------------------------------------------------------------------------
void CL_PolStock::EcrireFichier(FILE *fichier) {
}
//---------------------------------------------------------------------------
void CL_PolStock::LireFichier(FILE *fichier) {
}
/*
 A NOTER
 ecriture nouvelle à généraliser ?
 polStock comporte méthodes pour se lire se verifier ....
 OnKeyPress( cf Grille00 ) modifié pour activer LabelModifie->Visible=true
 Cl_Vecteur comporte nouvelle méthode nettoie Nbelt=0 NoX=0
 et DeGrille vide Vecteur et puis stocke
 */