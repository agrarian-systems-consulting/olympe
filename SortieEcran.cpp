//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Tableur.h"
#include "QuelExcelCSV.h"
#include "CL_Trad.h"

#include "SortieEcran.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSortieEcranFrm *SortieEcranFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TSortieEcranFrm::TSortieEcranFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// envoi dans Memo
//--------------------------------------------------------------------------
void TSortieEcranFrm::Demarre(void) {
	size0 = 12;
	size1 = 10;
	size2 = 8;
	LarTrait = 152;
	Marge1 = "";
	Marge2 = "    "; // ??
	Marge3 = "        ";
	posNom = 7;
	posUnite = 29;
	posVal = 44;
	delta = 10;

	Caption = "";
	if (Global != ENSEMBLE) {
		if (AgriEnCours != NULL)
			Caption = "Agriculteur: " + AgriEnCours->NomVC();
	} else {
		if (EnsembleEnCours != NULL)
			Caption = "Ensemble: " + EnsembleEnCours->Nom;
	}
	AsBlanc = "                            ";
	Memo1->Clear();
	EnTeteDate();

}
//--------------------------------------------------------------------------
void TSortieEcranFrm::EnTeteDate(void) {
	AnsiString date;
	TDateTime time;
//size2=10
	TypeImp("Courier", size2, clBlack, 'M');
//    TypeImp("Times New Roman",size2,clBlack,'M');
	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();
	Memo1->Lines->Add(date);
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::TypeImp(char *police, int size, TColor couleur,
		char style) {
//return;

	Memo1->SelAttributes->Name = police;
	Memo1->SelAttributes->Size = size; //14;
	Memo1->SelAttributes->Color = couleur;
	Memo1->SelAttributes->Pitch = fpFixed;
	if (style == 'g' || style == 'G')
		Memo1->SelAttributes->Style = TFontStyles() << fsBold;
	else
		Memo1->SelAttributes->Style = TFontStyles() >> fsBold;

}
//-------------------------------------------------------------------------
bool TSortieEcranFrm::EstVide(float *vecteur) {
	for (int n = 0; n < N_X; n++) {
		if (vecteur[n] != 0)
			return false;
	}
	return true;
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Titre1(char *titre, TColor couleur) {
//size1=14
	TypeImp("Times New Roman", size0, couleur, 'G');
//    TypeImp("Courier",size0,couleur,'G');
	AsLambda = Marge1 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());

	Memo1->SelAttributes->Style = TFontStyles() >> fsBold;
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Titre2(char *titre, TColor couleur) {
//    TypeImp("Courier",size1,couleur,'G');
	TypeImp("Times New Roman", size1, couleur, 'G');
	AsLambda = Marge2 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());

	Memo1->SelAttributes->Style = TFontStyles() >> fsBold;
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Titre3(char *titre, TColor couleur) {
//size1=12;
//    TypeImp("Courier",size1,couleur,'G');
	TypeImp("Times New Roman", size1, couleur, 'G');

	AsLambda = Marge3 + titre;
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::An(int an0, TColor couleur) {
	int i, an, pos;
	AnsiString s;
	int posVal = 44; //42
	int delta = 10;
	TypeImp("Courier", size2, couleur, 'M');

	AsLambda =
			"                                                               ";
	for (i = 0, pos = posVal, an = an0; i < N_X; i++, an++, pos += delta) {
		s = an;
		AsLambda.Insert(AnsiString(an), pos - s.Length());
		AsLambda += AsBlanc;
	}
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Resultat(AnsiString nom, int *valeur, TColor couleur) {
	int i, pos;
	TypeImp("Courier", size2, couleur, 'M');

	AsLambda = AsBlanc;

	AsLambda.Insert(nom.Trim(), posNom);
	AsLambda += AsBlanc;
	if (valeur == NULL)
		return;

	for (i = 0, pos = posVal; i < N_X; i++, pos += delta) {
		if (valeur[i] != 0.)
			placer(valeur[i], pos, 0);
		AsLambda += AsBlanc;
	}

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Resultat(AnsiString nom, float *valeur, TColor couleur) {
	int i, pos;
	TypeImp("Courier", size2, couleur, 'M');

	AsLambda = AsBlanc;

	AsLambda.Insert(nom.Trim(), posNom);
	AsLambda += AsBlanc;
	if (valeur == NULL)
		return;

	for (i = 0, pos = posVal; i < N_X; i++, pos += delta) {
		if (valeur[i] != 0.)
			placer(valeur[i], pos, 0);
		AsLambda += AsBlanc;
	}

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Total(AnsiString nom, float *valeur, TColor couleur) {

//    Memo1->SelAttributes->Style=TFontStyles()<<fsBold;
	Trait();
	TypeImp("Courier", size2, couleur, 'M');
	Resultat(nom, valeur);

}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Trait(void) {
	char chaine[256];
	memset(chaine, '_', LarTrait + 1);
	chaine[LarTrait] = '\0';
	Memo1->Lines->Add(chaine);
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::Blanc(int nli, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');
	for (int n = 0; n < nli; n++)
		Memo1->Lines->Add("");
}
//--------------------------------------------------------------------------
void TSortieEcranFrm::placer(float val, int pos, int apresVirgule) {
	int lg;
	AnsiString s;
//    s=FloatToStrF((double)val,AnsiString::sffNumber,7,apresVirgule);
	s = FloatToStrF((double) val, ffNumber, 7, apresVirgule);
	lg = s.Length();

	AsLambda.Insert(s, pos - lg);
}

//-------------------------------------------------------------------------
//
//                 IMPRESSION
//                     Valeur
//
//-------------------------------------------------------------------------
void TSortieEcranFrm::Valeur(CL_Agriculteur *agri) {
	int n, i, j;
	CL_AgriRes *resultat;
	AnsiString as;
	float solde[N_X];
	float valeur[N_X];
	AnsiString caption;
	CL_InvAni *invAni;
	CL_Troupeau *troupeau;
	bool titreAffiche;

	caption = agri->NomVC();

	Titre1(caption.c_str());

	resultat = agri->Resultat;
	as = "Valeurs en ";
	if (Global == AGRI || Global == MOYENNE)
		as += SysMonnaie->UTrans;
	else
		as += SysMonnaie->UGlobal;
	Titre1(as.c_str());
	An(agri->DefSim->An_0);

	CategorieV("Produits", V_CatProduit, resultat->V_Produit, resultat->Produit,
			resultat->V_CatProduitTot);

	if (agri->LstTroupeaux->Count > 0) {
		titreAffiche = false;
		//Titre2("Animaux Vendus");
		for (i = 0; i < agri->LstTroupeaux->Count; i++) {
			troupeau = (CL_Troupeau*) agri->LstTroupeaux->Items[i];
			for (j = 0; j < troupeau->V_InvAni->Nbelt; j++) {
				invAni = troupeau->V_InvAni->Vecteur[j];
				if (EstVide(invAni->ValVente) == false) {
					if (titreAffiche == false) {
						Titre2("Ventes d'Animaux ");
						titreAffiche = true;
					}
					Resultat(invAni->Animal->Nom, invAni->ValVente, clNavy);
				}
			}
		}
		//Titre2("Animaux Achetés");
		titreAffiche = false;
		for (i = 0; i < agri->LstTroupeaux->Count; i++) {
			troupeau = (CL_Troupeau*) agri->LstTroupeaux->Items[i];
			for (j = 0; j < troupeau->V_InvAni->Nbelt; j++) {
				invAni = troupeau->V_InvAni->Vecteur[j];
				if (EstVide(invAni->ValAchat) == false) {
					if (titreAffiche == false) {
						Titre2("Achat d'Animaux ");
						titreAffiche = true;
					}
					Resultat(invAni->Animal->Nom, invAni->ValAchat, clNavy);
				}
			}
		}
	}

	CategorieV("Charges", V_CatCharge, resultat->V_Charge, resultat->Charge,
			resultat->V_CatChargeTot);

	Total("MARGE", resultat->Marge);
//	Blanc();

	CategorieV("Charges de Structure", V_CatChStruct, resultat->V_ChStruct,
			resultat->ChStruct, resultat->V_CatChStructTot);
	CategorieV("Recettes Diverses", V_CatRecDiv, resultat->V_RecDiv,
			resultat->RecDiv, resultat->V_CatRecDivTot);
	CategorieV("Dépenses Diverses", V_CatDepDiv, resultat->V_DepDiv,
			resultat->DepDiv, resultat->V_CatDepDivTot);
	CategorieV("Recettes Familiales", V_CatRecFam, resultat->V_RecFam,
			resultat->RecFam, resultat->V_CatRecFamTot);
	CategorieV("Dépenses Familiales", V_CatDepFam, resultat->V_DepFam,
			resultat->DepFam, resultat->V_CatDepFamTot);
	Trait();
	Titre2("Immobilisation");
	for (n = 0; n < N_X; n++)
		solde[n] = resultat->ImmoTotal->Achat[n]
				- resultat->ImmoTotal->Vente[n];
	Resultat("Achat", resultat->ImmoTotal->Achat, clNavy);
	Resultat("Vente", resultat->ImmoTotal->Vente, clNavy);
	Resultat("Achat-Vente", solde);

	Trait();
	Titre2("Emprunts");
	Resultat("Emprunt", resultat->EmpTotal->Capital, clNavy);
	Resultat("Remboursement", resultat->EmpTotal->Remb, clNavy);
	Resultat("Interet", resultat->EmpTotal->Interet, clNavy);
	for (n = 0; n < N_X; n++)
		solde[n] = resultat->EmpTotal->Capital[n] - resultat->EmpTotal->Remb[n]
				- resultat->EmpTotal->Interet[n];
	Resultat("net", solde);

	Trait();
	Titre2("Placements");
	Resultat("Placé", resultat->PlactE->Capital, clNavy);
	Resultat("Disponible", resultat->PlactE->Remb, clNavy);
//    Resultat("Interet",      resultat->PlactE->Interet,clNavy);
	for (int n = 0; n < N_X; n++)
		solde[n] = -resultat->PlactE->Capital[n] + resultat->PlactE->Remb[n];
//                  +resultat->PlactE->Interet[n];
	Resultat("net", solde);

	Trait();
	Titre2("Subventions");
	Resultat("Subventions", resultat->TotSub->Valeur, clNavy);
	Blanc();

	Trait();
	Titre2("Créances et Dettes");
	Resultat("Créances", resultat->Creance->Flux, clNavy);
	for (n = 0; n < N_X; n++)
		valeur[n] = -resultat->Dette->Flux[n];
	Resultat("Dettes", valeur, clNavy);
	Blanc();

	Trait();
	Titre2("Tva");
	Resultat("Solde Tva", resultat->Tva->Solde, clNavy);
	Blanc();

//    Trait(132);  Total trace un trait
	Total("SOLDE", resultat->Solde);
//	Trait(132);

//    Trait(132);
	memset(valeur, 0, sizeof(float) * N_X);
	valeur[0] = resultat->TresoIni;
	Resultat("Trésorerie Initiale", valeur);
	Resultat("SOLDE CUMULE", resultat->SoldeCumul);
	Trait();
}
//-------------------------------------------------------------------------
void TSortieEcranFrm::CategorieV(char *titre,
		CL_Vecteur<CL_Categorie> *vCategorie, CL_Vecteur<CL_QuanVal> *vProduit,
		float *total, CL_Vecteur<CL_QuanVal> *vCatTot) {
	int i, j, l;
	CL_Item *item;
	CL_Categorie *categorie;
	CL_QuanVal *quanVal, *quanValTot;
	LarTrait = 152;
	if (vProduit->Nbelt == 0)
		return;

	Trait();
	Titre2(titre);

	for (i = 0; i < vCategorie->Nbelt; i++) {
		categorie = vCategorie->Vecteur[i];
		if (categorie->Flag == 'N')
			continue;

		quanValTot = vCatTot->trouve(categorie->No);
		l = 0;
		Titre3(categorie->Nom.c_str(), clNavy);

		for (j = 0; j < vProduit->Nbelt; j++) {
			quanVal = vProduit->Vecteur[j];
			item = quanVal->Item;
			if (item->Categorie != categorie)
				continue;
			l++;
			Resultat(item->Nom, quanVal->Val, clNavy);
		}
		if (l > 1) {
			Resultat(AnsiString("total"), quanValTot->Val);
		}
	}
	Total("TOTAL", total);

}
//-------------------------------------------------------------------
void __fastcall TSortieEcranFrm::BtBnImprimerClick(TObject *Sender)
{
	TPrinter *imprimante=Printer();
	int i,x;
	String s;
	/*
	 switch(RGOrientation->ItemIndex)
	 {
	 case 0:Printer()->Orientation = poPortrait;	break;
	 case 1:Printer()->Orientation = poLandscape;break;
	 }
	 */
	Printer()->Orientation = poLandscape;
	s="Bonjour";
	imprimante->BeginDoc();
//    imprimante->Canvas->Font->Name="Times New Roman";
	imprimante->Canvas->Font->Name="Courier";
	imprimante->Canvas->Font->Size=8;
	imprimante->Canvas->Font->Pitch=fpFixed;
	imprimante->Canvas->Font->PixelsPerInch=550;//600;//500;
	x=imprimante->Canvas->TextHeight(s);
	for(i=0;i<Memo1->Lines->Count;i++)
	{
		s=Memo1->Lines->Strings[i];
		imprimante->Canvas->TextOut(1,i*x+1,s);
	}
	imprimante->EndDoc();
//    Memo1->Print("Olympe");
}

//--------------------------------------------
void TSortieEcranFrm::IniCaption(void) {
	SortieEcranFrm->Caption = LC_SortieEcranFrm;
}
//--------------------------------------------
void TSortieEcranFrm::TexteCaption(void) {
	LC_SortieEcranFrm = T->TrouveCaption("SortieEcran", "LC_SortieEcranFrm");

	IniCaption();

}

