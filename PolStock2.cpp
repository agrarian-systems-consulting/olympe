//---------------------------------------------------------------------------

#include <vcl.h>
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
 problèmes possible? A voir
 */
/*
 //---------------------------------------------------------------------------
 //---------------------------------------------------------------------------
 //---------------------------------------------------------------------------
 //---------------------------------------------------------------------------
 __fastcall TPolStockFrm::TPolStockFrm(TComponent* Owner)
 : TForme00Frm(Owner)
 {
 }
 //---------------------------------------------------------------------------
 // FONCTIONS A PERSONNALISER
 //----------------------------------------------------------------------------
 void  __fastcall TPolStockFrm::Personnaliser(void)
 {
 //pour l'impression
 TitreGrille=Caption;
 strcpy(TypeCol,"0000NNNN");
 }
 //---------------------------------------------------------------------------
 void __fastcall	TPolStockFrm::DefinirLesGrilles(void)
 {
 GrilleX=1;
 Grille0->Tag=0;
 LesGrilles[0]=Grille0;
 LaGrille=Grille0;
 }
 //-----------------------------------------------------------------------------
 void __fastcall TPolStockFrm::IniGrille(TStringGrid *grille)
 {
 int l=0;
 int largeur[]={20,64,64,64,64,64,64,64};
 int c;
 grille->ColCount =8;
 grille->FixedCols=1;
 grille->FixedRows=1;

 for(c=0;c<grille->ColCount;c++)
 {
 grille->ColWidths[c]=largeur[c];
 l+=largeur[c];
 }
 grille->Width=l+25;  //place pour l'ascenseur

 // attention col row
 grille->Cells[1][0]="Produit";
 grille->Cells[2][0]="Prix";
 grille->Cells[3][0]="Unité";
 grille->Cells[4][0]="%Stocké";
 grille->Cells[5][0]="Maxi Stockable";
 grille->Cells[6][0]="%Augmentation Prix";
 grille->Cells[7][0]="%Décote";
 AjoutRow=false;
 CellAVerifier=true;
 }
 //------------------------------------------------------------------------------
 void __fastcall TPolStockFrm::VersGrille(TStringGrid *grille)
 {
 int i;
 int r;
 CL_QuanVal  *quanVal;
 CL_Item     *item;
 CL_PolStock *polStock;
 r=1;
 for(i=0;i<Agri->Resultat->V_Produit->Nbelt;i++,r++)
 {
 quanVal=Agri->Resultat->V_Produit->Vecteur[i];
 item=quanVal->Item;
 polStock=Agri->V_PolStock->trouve(item->No);
 if(polStock==NULL)
 {
 polStock=new CL_PolStock(item);
 Agri->V_PolStock->insSans(polStock);
 LabelModifie->Visible=true;
 }
 polStock->AffRow(LaGrille,r);
 }
 LaGrille->RowCount=r;
 AjoutRow=false;
 }
 //------------------------------------------------------------------------------
 void __fastcall TPolStockFrm::DeGrille(TStringGrid *grille)
 {
 int r;
 CL_PolStock *polStock;
 Agri->V_PolStock->vide();
 for(r=1;r<LaGrille->RowCount;r++)
 {
 polStock=(CL_PolStock *)LaGrille->Objects[0][r];
 if(polStock==NULL) continue;

 polStock->LitRow(LaGrille,r);
 Agri->V_PolStock->insSans(polStock);
 }
 }
 //------------------------------------------------------------------------------
 bool __fastcall TPolStockFrm::ControleGrille(void)
 {
 int r;
 bool correct,rep;
 CL_PolStock *polStock;

 correct=true;
 ErreurFrm->Edit->Clear();
 for(r=1;r<LaGrille->RowCount;r++)
 {
 polStock=(CL_PolStock *)LaGrille->Objects[0][r];
 if(polStock==NULL) continue;

 rep=polStock->EstCorrect(LaGrille,r);
 if(rep==false) correct=false;
 }

 if(correct==false)
 ErreurFrm->Show();

 return correct;
 }
 //------------------------------------------------------------------------------
 bool __fastcall TPolStockFrm::Stocker(void)
 {
 if(LabelModifie->Visible==false) return true;

 AutreDonnee=false;
 if(ControleGrille()==false)      return false;

 DeGrille(LaGrille);
 LabelModifie->Visible=false;
 AgriSaisieFrm->LabelModifie->Visible=true;
 //    AgriSaisieFrm->Calcul0();
 //    AgriSaisieFrm->Stocker();
 return true;
 }
 //---------------------------------------------------------------------------
 void __fastcall TPolStockFrm::BtReportBasClick(TObject *Sender)
 {
 int r;
 int col=LaGrille->Col;
 int row=LaGrille->Row;
 AnsiString s=LaGrille->Cells[col][row];

 if(col<4) return;

 LabelModifie->Visible=true;

 for(r=row+1;r<LaGrille->RowCount;r++)
 {
 if(RowVide(r)==true) continue;
 if(RepPossible(col,r)==false) continue;

 LaGrille->Cells[col][r]=s;
 }
 }
 //---------------------------------------------------------------------------
 void __fastcall TPolStockFrm::BtRecopBasClick(TObject *Sender)
 {
 int row=LaGrille->Row;
 int r,c;
 int c0;
 c0=4;

 LabelModifie->Visible=true;

 for(c=c0;c<LaGrille->ColCount;c++)
 {
 if(LaGrille->Cells[c][row].IsEmpty() )continue;
 LabelModifie->Visible=true;
 for(r=row+1;r<LaGrille->RowCount;r++)
 {
 if(RepPossible(c,r)==false) continue;

 LaGrille->Cells[c][r]=LaGrille->Cells[c][row];
 }
 }
 }
 //---------------------------------------------------------------------------
 */
