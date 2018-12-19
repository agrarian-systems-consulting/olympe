//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "Outil.h"
#include "QRSortieVal.h"
#include "QRSortieQuant.h"
#include "AgriDefSerie.h"

#include "SortieLD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSortieLDFrm *SortieLDFrm;
//---------------------------------------------------------------------------
__fastcall TSortieLDFrm::TSortieLDFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void TSortieLDFrm::DimGrille(int nature) {
	int nSerie;
	int n;
	int c0;
	ST_NoAgri *noAgri;
	CL_Agriculteur *agri;
	int an_0, an;
	VideGrille();
	noAgri = (ST_NoAgri*) Agri->LstSerie->Items[0];
	agri = noAgri->Agri;
	an_0 = agri->DefSim->An_0;

	nSerie = Agri->LstSerie->Count;

	SG->RowCount = 20;
	SG->ColWidths[0] = 128;
	switch (nature) {
	case QUANTITE:
		SG->ColCount = 2 + nSerie * 10;
		SG->ColWidths[1] = 32;
		SG->Cells[1][0] = " Unite";
		c0 = 2;
		Caption = "Quantités";
		break;
	case VALEUR:
		SG->ColCount = 1 + nSerie * 10;
		c0 = 1;
		Caption = "Recettes Dépenses";
		break;

	case CEG:
		SG->ColCount = 1 + nSerie * 10;
		c0 = 1;
		Caption = "Compte d'entreprise";
		break;
	}

	SG->FixedCols = c0;
	for (n = c0; n < SG->ColCount; n++)
		SG->ColWidths[n] = 64;
	SG->Cells[0][0] = ""; //" Produits";

	for (n = c0, an = an_0; n < SG->ColCount; n++, an++)
		SG->Cells[n][0] = an;

}
//---------------------------------------------------------------------------
void TSortieLDFrm::Aff(int nature) {
	int n, nSerie;
	ST_NoAgri *noAgri;
	CL_Agriculteur *agri, *agriAvant;
	nSerie = Agri->LstSerie->Count;

	agriAvant = NULL;
	for (n = 0; n < nSerie; n++) //de tte façon calculer le 0
			{
		noAgri = (ST_NoAgri*) Agri->LstSerie->Items[n];
		agri = noAgri->Agri;
		//230908
		if (agri == NULL) {
			AgriDefSerieFrm->DefAgriApres(agriAvant, noAgri);
			agri = noAgri->Agri;
		}
		//...
		if (agriAvant)
			agri->TresoIni = agriAvant->Resultat->SoldeCumul[N_X - 1];
		AgriSaisieFrm->Calcul0(agri);
		agriAvant = agri;
		switch (nature) {
		case QUANTITE:
			AffQuantite(n, agri->Resultat);
			break;
		case VALEUR:
			AffValeur(n, agri->Resultat);
			break;
		case CEG:
			AffCeg(n, agri->Resultat);
			break;
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TSortieLDFrm::AffQuantite(int noSerie, CL_AgriRes *resultat) {
	int r;
	AnsiString s;
	r = 1;
	s = QRSortieQuantFrm->L_3; //Produits
	r = AffQuantiteDetail(r, s, noSerie, V_CatProduit, resultat->V_Produit);

	s = QRSortieQuantFrm->L_4; //Charges
	AffQuantiteDetail(r, s, noSerie, V_CatCharge, resultat->V_Charge);
//    SG->RowCount=r;
}
//---------------------------------------------------------------------------
int TSortieLDFrm::AffQuantiteDetail(int rowDeb, AnsiString titre, int noSerie,
		CL_Vecteur<CL_Categorie>*vCategorie, CL_Vecteur<CL_QuanVal>*vQuanVal) {
	int r;
	int i, j;
	int c0;
	char *unite;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal;
	TColor couleur;
	couleur = (TColor) 0x00F1E0BC; //gris bleu
	// 2 colonnes de gauche
	r = rowDeb;
	if (noSerie == 0) {
		SG->Objects[0][r] = (TObject*) couleur;
		SG->Cells[0][r++] = titre;
		for (i = 0; i < vCategorie->Nbelt; i++) {
			categorie = vCategorie->Vecteur[i];
			if (categorie->Flag == 'N')
				continue;
			if (r >= SG->RowCount)
				SG->RowCount += 10;

			SG->Cells[0][r++] = AnsiString("   ") + categorie->Nom;

			for (j = 0; j < vQuanVal->Nbelt; j++) {
				quanVal = vQuanVal->Vecteur[j];
				item = quanVal->Item;
				if (item->Categorie != categorie)
					continue;

				unite = item->SysUnite->UTrans.c_str();
				SG->Cells[0][r] = AnsiString("       ") + item->Nom;
				SG->Cells[1][r++] = unite;
			}
		}
	}

	r = rowDeb + 1; //titre
	c0 = 2 + noSerie * N_X;
	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		//SG->Cells[0][r]=AnsiString("   ")+categorie->Nom;
		r++;
		for (j = 0; j < vQuanVal->Nbelt; j++) {
			quanVal = vQuanVal->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;

			//unite=item->SysUnite->UTrans.c_str();
			//SG->Cells[1][r]=unite;
			AffVal(c0, r, quanVal->Qte, 0);
			r++;
		}
	}
	return r;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TSortieLDFrm::AffValeur(int noSerie, CL_AgriRes *resultat) {
	int r;
	AnsiString s1, s2;

	r = 1;
	s1 = QRSortieValFrm->L_22; //"Produits
	s2 = QRSortieValFrm->L_59; //TOTAL Recettes Produits
	r = AffValeurDetail(r, s1, s2, noSerie, V_CatProduit, resultat->V_Produit,
			NULL, resultat->V_CatProduitTot);

	r = AffValeurResultat(r, s2, noSerie, resultat->Produit);

	s1 = QRSortieValFrm->L_35; //Charges
	s2 = QRSortieValFrm->L_60; //TOTAL Charges Opérationnelles
	r = AffValeurDetail(r, s1, s2, noSerie, V_CatCharge, resultat->V_Charge,
			resultat->Charge, resultat->V_CatChargeTot);
	r = AffValeurResultat(r, QRSortieValFrm->L_13, noSerie, resultat->Marge); //MARGE

	s1 = QRSortieValFrm->L_39; //Charges de Structure"
	s2 = QRSortieValFrm->L_61; //TOTAL Structure"
	r = AffValeurDetail(r, s1, s2, noSerie, V_CatChStruct, resultat->V_ChStruct,
			resultat->ChStruct, resultat->V_CatChStructTot);

	s1 = QRSortieValFrm->L_24; //Recettes Diverses
	s2 = QRSortieValFrm->L_62; //"TOTAL Recettes Diverses
	r = AffValeurDetail(r, s1, s2, noSerie, V_CatRecDiv, resultat->V_RecDiv,
			resultat->RecDiv, resultat->V_CatRecDivTot);

	s1 = QRSortieValFrm->L_37; //"Dépenses Diverses
	s2 = QRSortieValFrm->L_63; //TOTAL Dépenses Diverses"
	r = AffValeurDetail(r, s1, s2, noSerie, V_CatDepDiv, resultat->V_DepDiv,
			resultat->DepDiv, resultat->V_CatDepDivTot);

	s1 = QRSortieValFrm->L_64; //Recettes Familiales
	s2 = QRSortieValFrm->L_65; //TOTAL Recettes Familiales
	r = AffValeurDetail(r, s1, s2,
			noSerie, //L_64.c_str(),L_65.c_str(),
			V_CatRecFam, resultat->V_RecFam, resultat->RecFam,
			resultat->V_CatRecFamTot);

	s1 = QRSortieValFrm->L_66; //DépensesFamiliales
	s2 = QRSortieValFrm->L_67; //TOTAL Dépenses Familiales
	r = AffValeurDetail(r, s1, s2, noSerie, V_CatDepFam, resultat->V_DepFam,
			resultat->DepFam, resultat->V_CatDepFamTot);

	r = AffImmo(r, resultat, noSerie);
	r = AffEmprunt(r, resultat, noSerie);

	s1 = QRSortieValFrm->L_72; //"Tva
	s2 = QRSortieValFrm->L_73; //"Solde Tva
	r = AffTva(r, s1, s2, noSerie, resultat->Tva->Solde);

	s1 = QRSortieValFrm->L_16; //SOLDE
	r = AffValeurResultat(r, s1, noSerie, resultat->Solde);

	s1 = QRSortieValFrm->L_17; //SOLDE CUMULE
	r = AffValeurResultat(r, s1, noSerie, resultat->SoldeCumul);
	SG->RowCount = r;
}
//---------------------------------------------------------------------------
int TSortieLDFrm::AffValeurDetail(int rowDeb, AnsiString titre,
		AnsiString titreTotal, int noSerie,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_QuanVal> *vProduit,
		float *total, CL_Vecteur<CL_QuanVal> *vCatTot) {
	int i, j, l;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal, *quanValTot;
	AnsiString as;
	TColor couleur;
	int r;
	int c0;
	r = rowDeb;
	couleur = (TColor) 0x00F1E0BC; //gris bleu

	if (vProduit->Nbelt == 0)
		return r;

	if (noSerie == 0) {
		SG->Objects[0][r] = (TObject*) couleur;
		SG->Cells[0][r++] = titre;

		for (i = 0; i < vCategorie->Nbelt; i++) {
			categorie = vCategorie->Vecteur[i];
			if (categorie->Flag == 'N')
				continue;

			quanValTot = vCatTot->trouve(categorie->No);
			l = 0;
			if (r >= SG->RowCount)
				SG->RowCount += 10;
			SG->Cells[0][r++] = AnsiString("   ") + categorie->Nom;

			for (j = 0; j < vProduit->Nbelt; j++) {
				quanVal = vProduit->Vecteur[j];
				item = quanVal->Item;
				if (item->Categorie != categorie)
					continue;
				l++;
				SG->Cells[0][r++] = AnsiString("       ") + item->Nom;
			}
			if (l > 1)
				SG->Cells[0][r++] = AnsiString("   ") + QRSortieValFrm->L_75; //"total";
		}
		if (total)
			SG->Cells[0][r++] = AnsiString("   ") + titreTotal;
	}
	r = rowDeb;
	r++; //titre
	c0 = 1 + noSerie * N_X;
	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		quanValTot = vCatTot->trouve(categorie->No);
		l = 0;
		//SG->Cells[0][r++]=AnsiString("   ")+categorie->Nom;
		r++;
		for (j = 0; j < vProduit->Nbelt; j++) {
			quanVal = vProduit->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;
			l++;
			AffVal(c0, r, quanVal->Val, 0);
			r++;
		}
		if (l > 1) {
			AffVal(c0, r, quanValTot->Val, 0);
			r++;
		}
	}
	if (total) {
		AffVal(c0, r, total, 0);
		r++;
	}
	return r;
}
//---------------------------------------------------------------------------
int TSortieLDFrm::AffValeurResultat(int rowDeb, AnsiString titre, int noSerie,
		float *valeur) {
	int c0;
	int r = rowDeb;
	TColor couleur;
	couleur = (TColor) 0x00F1E0BC; //gris bleu
	couleur = clAqua;
	SG->Objects[0][r] = (TObject*) couleur;

	if (noSerie == 0)
		SG->Cells[0][r] = titre;
	c0 = 1 + noSerie * N_X;
	AffVal(c0, r, valeur, 0);
	r++;
	return r;
}

//---------------------------------------------------------------------------
int TSortieLDFrm::AffImmo(int rowDeb, CL_AgriRes *resultat, int noSerie) {
	int r, n;
	int c0;
	float solde[N_X];
	TColor couleur;
	r = rowDeb;
	couleur = (TColor) 0x00F1E0BC; //gris bleu
	SG->Objects[0][r] = (TObject*) couleur;

	if (r + 4 > SG->RowCount)
		SG->RowCount += 10;
	if (noSerie == 0) {
		SG->Cells[0][r++] = QRSortieValFrm->L_81; //"Immobilisation";
		SG->Cells[0][r++] = QRSortieValFrm->L_82; //"   Achat";
		SG->Cells[0][r++] = QRSortieValFrm->L_83; //"   Vente";
		SG->Cells[0][r++] = QRSortieValFrm->L_84; //"   Achat-vente";
	}
	c0 = 1 + noSerie * N_X;
	r = rowDeb;
	r++;
	for (n = 0; n < N_X; n++)
		solde[n] = resultat->ImmoTotal->Achat[n]
				- resultat->ImmoTotal->Vente[n];

	AffVal(c0, r, resultat->ImmoTotal->Achat, 0);
	r++;
	AffVal(c0, r, resultat->ImmoTotal->Vente, 0);
	r++;
	AffVal(c0, r, solde, 0);
	r++;
	return r;
}
//---------------------------------------------------------------------------
int TSortieLDFrm::AffEmprunt(int rowDeb, CL_AgriRes *resultat, int noSerie) {
	int r, c0;
	int n;
	float net[N_X];
	TColor couleur;
	r = rowDeb;
	couleur = (TColor) 0x00F1E0BC; //gris bleu
	SG->Objects[0][r] = (TObject*) couleur;

	if (r + 5 > SG->RowCount)
		SG->RowCount += 10;
	if (noSerie == 0) {
		SG->Cells[0][r++] = QRSortieValFrm->L_85; //"Emprunts";
		SG->Cells[0][r++] = QRSortieValFrm->L_86; //"   Emprunt";
		SG->Cells[0][r++] = QRSortieValFrm->L_87; //"   Remboursement";
		SG->Cells[0][r++] = QRSortieValFrm->L_88; //"   Intérêt";
		SG->Cells[0][r++] = QRSortieValFrm->L_89; //"   net";
	}

	c0 = 1 + noSerie * N_X;
	r = rowDeb;
	r++;
	for (n = 0; n < N_X; n++)
		net[n] = resultat->EmpTotal->Capital[n] - resultat->EmpTotal->Remb[n]
				- resultat->EmpTotal->Interet[n];

	AffVal(c0, r, resultat->EmpTotal->Capital, 0);
	r++;
	AffVal(c0, r, resultat->EmpTotal->Remb, 0);
	r++;
	AffVal(c0, r, resultat->EmpTotal->Interet, 0);
	r++;
	AffVal(c0, r, net, 0);
	r++;
	return r;

}
//---------------------------------------------------------------------------
int TSortieLDFrm::AffTva(int rowDeb, AnsiString titre, AnsiString titre1,
		int noSerie, float *valeur) {
	int r, c0;
	TColor couleur;

	r = rowDeb;
	couleur = (TColor) 0x00F1E0BC; //gris bleu
	SG->Objects[0][r] = (TObject*) couleur;

	if (r + 5 > SG->RowCount)
		SG->RowCount += 10;
	if (noSerie == 0) {
		SG->Cells[0][r++] = titre;
		SG->Cells[0][r++] = AnsiString("   ") + titre1;
	}
	r = rowDeb;
	AffVal(c0, r, valeur, 0);
	r++;
	return r;
}

//---------------------------------------------------------------------------
void TSortieLDFrm::AffCeg(int noSerie, CL_AgriRes *resultat) {
	if (noSerie == 0)
		AffCegTitre();
	AffCegValeur(noSerie, resultat);

}
//---------------------------------------------------------------------------
void TSortieLDFrm::AffCegTitre(void) {
	int r;
	SG->RowCount = 40;
	r = 1;
	SG->Cells[0][r++] = QRSortieValFrm->L_22; //"Produits"
//    blanc(;

	SG->Cells[0][r++] = QRSortieValFrm->L_23; //"Recettes"
	SG->Cells[0][r++] = QRSortieValFrm->L_24; //"Recettes Diverses"
	SG->Cells[0][r++] = QRSortieValFrm->L_25; //"Var. Stock"
	SG->Cells[0][r++] = QRSortieValFrm->L_26; //"Var. stock en terre"
//    Resultat(".  Variation valeur plantation",   resultat->deltaValPlant,clNavy;
	SG->Cells[0][r++] = QRSortieValFrm->L_28; //"Var. inv animal Repro"
	SG->Cells[0][r++] = QRSortieValFrm->L_29; //"                Autre"

	SG->Cells[0][r++] = QRSortieValFrm->L_30; //"Produits financiers"
	SG->Cells[0][r++] = QRSortieValFrm->L_31; //"Production d'immo"
	SG->Cells[0][r++] = QRSortieValFrm->L_32; //"Cession d'actif"
	SG->Cells[0][r++] = QRSortieValFrm->L_33; //"Perte Exceptionnelle"
	SG->Cells[0][r++] = QRSortieValFrm->L_34; //"Amortissement Subvention"

	SG->Cells[0][r++] = " "; //    entreBlanc(;
	SG->Cells[0][r++] = QRSortieValFrm->L_35; //"Charges"
//    blanc(;

	SG->Cells[0][r++] = QRSortieValFrm->L_36; //"Dépenses Exploitation"
	SG->Cells[0][r++] = QRSortieValFrm->L_37; //"Dépenses Diverses"
	SG->Cells[0][r++] = QRSortieValFrm->L_38; //"Val comptable cession"

	SG->Cells[0][r++] = "  "; //   entreBlanc(;
	SG->Cells[0][r++] = QRSortieValFrm->L_39; //"Charges de Structure"
//    blanc(;
	SG->Cells[0][r++] = QRSortieValFrm->L_20; //"Amortissement Immo"
	SG->Cells[0][r++] = QRSortieValFrm->L_21; //"Amortissement Plantation"
	SG->Cells[0][r++] = QRSortieValFrm->L_40; //"Frais fin LT"
	SG->Cells[0][r++] = QRSortieValFrm->L_41; //"Frais fin CT"
	SG->Cells[0][r++] = QRSortieValFrm->L_42; //"Frais fin OCCC"
	SG->Cells[0][r++] = QRSortieValFrm->L_43; //"Autres Ch Struct"
	SG->Cells[0][r++] = "  "; //   entreBlanc(;
	SG->Objects[0][r] = (TObject*) clAqua; //
	SG->Cells[0][r++] = QRSortieValFrm->L_44; //"Resultat

	SG->RowCount = r;

}
//---------------------------------------------------------------------------
void TSortieLDFrm::AffCegValeur(int noSerie, CL_AgriRes *resultat) {
	int r;
	int c0;
	r = 1;
	c0 = 1 + noSerie * N_X;
	AffVal(c0, r++, resultat->totProduit); //"Produits"
//    blanc();

	AffVal(c0, r++, resultat->Produit); //"Recettes"
	AffVal(c0, r++, resultat->RecDiv); //"Recettes Diverses"
	AffVal(c0, r++, resultat->deltaStock); //"Var. Stock"
	AffVal(c0, r++, resultat->deltaAvance); //"Var. stock en terre"
//    Resultat(".  Variation valeur plantation",   resultat->deltaValPlant,clNavy);
	AffVal(c0, r++, resultat->deltaVarInvAniRepro); //"Var. inv animal Repro"
	AffVal(c0, r++, resultat->deltaVarInvAniAutre); //"                Autre"

	AffVal(c0, r++, resultat->PlactE->Interet); //"Produits financiers"
	AffVal(c0, r++, resultat->ProdImmo); //"Production d'immo"
	AffVal(c0, r++, resultat->ImmoTotal->Vente); //"Cession d'actif"
	AffVal(c0, r++, resultat->PertePlant); //"Perte Exceptionnelle"
	AffVal(c0, r++, resultat->TotSub->Amor); //"Amortissement Subvention"

	r++; //entreBlanc();
	AffVal(c0, r++, resultat->totDepense); //"Charges"
//    blanc();

	AffVal(c0, r++, resultat->Charge); //"Dépenses Exploitation"
	AffVal(c0, r++, resultat->DepDiv); //"Dépenses Diverses"
	AffVal(c0, r++, resultat->ImmoTotal->ValCompta); //"Val comptable cession"

	r++; //entreBlanc();
	AffVal(c0, r++, resultat->totChStruct); //"Charges de Structure"
//    blanc();
	AffVal(c0, r++, resultat->ImmoTotal->Amor); //"Amortissement Immo"
	AffVal(c0, r++, resultat->AmorPlant); //"Amortissement Plantation"
	AffVal(c0, r++, resultat->EmpLTE->Interet); //"Frais fin LT"
	AffVal(c0, r++, resultat->EmpCTE->Interet); //"Frais fin CT"
	AffVal(c0, r++, resultat->FraisOccc); //"Frais fin OCCC"
	AffVal(c0, r++, resultat->ChStruct); //"Autres Ch Struct"
	r++; //entreBlanc();
	AffVal(c0, r++, resultat->resExercice); //"Résultat"
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TSortieLDFrm::VideGrille(void) {
	int r, c;
	for (r = 0; r < SG->RowCount; r++) {
		SG->Objects[0][r] = NULL;
		for (c = 0; c < SG->ColCount; c++)
			SG->Cells[c][r] = "";
	}
}
//---------------------------------------------------------------------------
void TSortieLDFrm::AffVal(int c0, int r, float *valeur, int digits) {
	int n;
	int c;
	for (n = 0, c = c0; n < N_X; n++, c++)
		SG->Cells[c][r] = Aff(valeur[n], digits);
}
//---------------------------------------------------------------------------
//     Aff tranforme un float ou un int en AnsiString
//-----------------------------------------------------------
AnsiString TSortieLDFrm::Aff(float x, int digits) {
	if (x == 0)
		return AnsiString(" "); //"" ou " "      ????
	return FloatToStrF((double) x, ffNumber, 7, digits);
}

//---------------------------------------------------------------------------
void __fastcall TSortieLDFrm::BtBnPlus10Click(TObject *Sender)
{
//ShowMessage(SG->Col);
	if(SG->Col+10>=SG->ColCount)
	SG->Col=SG->ColCount-1;
	else
	SG->Col+=10;
}
//---------------------------------------------------------------------------
void __fastcall TSortieLDFrm::BtBnMoin10Click(TObject *Sender)
{
//ShowMessage(SG->Col);
	if(SG->Col-10<0)SG->Col=2;
	else SG->Col-=10;
}
//---------------------------------------------------------------------------

void __fastcall TSortieLDFrm::SGDrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State)
{
	TColor couleur;
	AnsiString s;
	s=SG->Cells[ACol][ARow];

	couleur=(TColor)SG->Objects[0][ARow];

	if(couleur)
	SG->Canvas->Brush->Color=couleur; //TColor)0x00F1E0BC; //gris bleu
	SG->Canvas->FillRect(Rect);
	SG->Canvas->TextRect(Rect,Rect.Left+1,Rect.Top+1,s);

}
//---------------------------------------------------------------------------

void __fastcall TSortieLDFrm::BtBnVersExcelClick(TObject *Sender)
{
	OutilFrm->VersExcel(SG,0,0,SG->ColCount,SG->RowCount);
}
//---------------------------------------------------------------------------

