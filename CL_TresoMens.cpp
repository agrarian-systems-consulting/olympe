//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "TresoEnum.h"
#include "CL_TresoMens.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CL_TresoMens::CL_TresoMens() {
	Contient = -1;
	QuanVal = NULL;
	Maz();
	LstMoisVal = NULL;
	Valeur = NULL;
}
//tresoMens
//---------------------------------------------------------------------------
CL_TresoMens::CL_TresoMens(CL_QuanVal *quanVal, int type, char *famille,
		int proOUcha) {
	Contient = UnITEM;
	QuanVal = quanVal;
	QouV = type;
	Famille = famille;
	ProOuCha = proOUcha;
	Maz();
	Nom = quanVal->Item->Nom.c_str();

	LstMoisVal = new TList;
	Valeur = NULL;
}
//---------------------------------------------------------------------------
// tresoTotCat tresoTotFam  tva
//total   pour creer liste de valeurs :LstMoisVal(CL_IntFloat)
//proOUcha PRODUIT recu  CHARGE verse
//contient TOTCAT
//---------------------------------------------------------------------------
CL_TresoMens::CL_TresoMens(char *titre, float *total, int proOUcha,
		int contient, bool avecListe) {
	int m;
	AnsiString as;
	CL_IntFloat *moisVal;

	Contient = contient;
	QuanVal = NULL;
	QouV = 0; //A voir
	//Famille=famille;
	ProOuCha = proOUcha;
	Maz();
	repartExiste = true; //pour eviter ? en colonne 1
	Nom = titre;
	if (avecListe == true) {
		Valeur = NULL;
		LstMoisVal = new TList;
		for (m = 0; m < N_X * 12; m++) {
			if (total[m]) {
				moisVal = new CL_IntFloat(m, total[m]);
				LstMoisVal->Add(moisVal);
			}
		}
	} else {
		LstMoisVal = NULL;
		Valeur = new float[120];
		memcpy(Valeur, total, sizeof(float) * 120);
	}
}
//---------------------------------------------------------------------------
//pour  valeur  achat et vente d'immo
//
//---------------------------------------------------------------------------
CL_TresoMens::CL_TresoMens(char *titre, float valVente, int mVente,
		float valAchat, int mAchat, int proOUcha, int contient) {
	AnsiString as;
	CL_IntFloat *moisVal;

	Contient = contient;
	QuanVal = NULL;
	QouV = 0; //A voir
	//Famille=famille;
	ProOuCha = proOUcha;
	Maz();
	repartExiste = true; //pour eviter ? en colonne 1
	Nom = titre;

	LstMoisVal = new TList;
	Valeur = NULL;

	if (valAchat) {
		moisVal = new CL_IntFloat(mAchat, -valAchat);
		LstMoisVal->Add(moisVal);
	}
	if (valVente) {
		moisVal = new CL_IntFloat(mVente, valVente);
		LstMoisVal->Add(moisVal);
	}
}
//---------------------------------------------------------------------------
// emprunts LT
//---------------------------------------------------------------------------
CL_TresoMens::CL_TresoMens(char *titre, float *recu, float *verse, int proOUcha,
		int contient) {
	int m;
	AnsiString as;
	CL_IntFloat *moisVal;

	Contient = contient;
	QuanVal = NULL;
	QouV = 0; //A voir
	//Famille=famille;
	ProOuCha = proOUcha;
	Maz();
	repartExiste = true; //pour eviter ? en colonne 1
	Nom = titre;

	LstMoisVal = new TList;
	Valeur = NULL;
	for (m = 0; m < N_X * 12; m++) {
		if (recu[m]) {
			moisVal = new CL_IntFloat(m, recu[m]);
			LstMoisVal->Add(moisVal);
		}
	}
	for (m = 0; m < N_X * 12; m++) {
		if (verse[m]) {
			moisVal = new CL_IntFloat(m, -verse[m]);
			LstMoisVal->Add(moisVal);
		}
	}
}
//tresoTitreCat tresoTitreFam
//
//---------------------------------------------------------------------------
CL_TresoMens::CL_TresoMens(char *titre, int proOUcha, int contient) {
	Contient = contient;
	QuanVal = NULL;
	QouV = 0; //A voir
	Famille = NULL;
	ProOuCha = proOUcha;
	Maz();
	repartExiste = true; //pour eviter ? en colonne 1
	Nom = titre;
	LstMoisVal = NULL;
	Valeur = NULL;
}
//---------------------------------------------------------------------------
CL_TresoMens::~CL_TresoMens() {
	int i;
	if (LstMoisVal) {
		for (i = 0; i < LstMoisVal->Count; i++)
			LstMoisVal->Delete(i);
		delete LstMoisVal;
	}
	if (Valeur)
		delete[] Valeur;
}
//---------------------------------------------------------------------------
void CL_TresoMens::Maz(void) {
	Nom = NULL;
	AAfficher = ' ';
}
//---------------------------------------------------------------------------
void CL_TresoMens::Calcul(float *ValTva) {
	int n, i, m;
	float val;
	float taux;
	CL_Repart *repart;
	CL_IntFloat *moisPcent, *moisVal;
	CL_Item *item;
	if (LstMoisVal == NULL)
		return;

	item = QuanVal->Item;
	if (QouV == VALEUR && item->Tva)
		taux = item->Tva->Taux / 100;
	else
		taux = 0;

	repartExiste = false;
	for (n = 0; n < N_X; n++) {
		//LesRepartV n'est pas informé 180610
		repart = QuanVal->ItemRepart->LesRepartQ[n];
		if (QouV == VALEUR) {
			repart = QuanVal->ItemRepart->LesRepartV[n];
			val = QuanVal->Val[n];
		} else {
			repart = QuanVal->ItemRepart->LesRepartQ[n];
			val = QuanVal->Qte[n];
		}
		if (repart == NULL)
			continue;

		repartExiste = true;
		for (i = 0; i < repart->LstPcent->Count; i++) {
			moisPcent = (CL_IntFloat*) repart->LstPcent->Items[i];
			m = moisPcent->i - 1 - 12 + n * 12; //moisVal  janvier =1  1 anprec 13 annee1
			if (m >= 0 && m < N_X * 12) {
				moisVal = new CL_IntFloat(m, val * moisPcent->Val / 100);
				if (taux)
					ValTva[m] += moisVal->Val * taux;
				LstMoisVal->Add(moisVal);
			}
		}
	}
}
//---------------------------------------------------------------------------
void CL_TresoMens::AdditioneDans(float *total) {
	int i, m;
	CL_IntFloat *moisVal;
	if (LstMoisVal == NULL)
		return;

	for (i = 0; i < LstMoisVal->Count; i++) {
		moisVal = (CL_IntFloat*) LstMoisVal->Items[i];
		m = moisVal->i;
		total[m] += moisVal->Val;
	}

}
//---------------------------------------------------------------------------
void CL_TresoMens::EtablitFlux(float *flux) {
	int i, m;
	CL_IntFloat *moisVal;

	memset(flux, 0, sizeof(float) * N_X * 12);
	if (LstMoisVal != NULL) {
		for (i = 0; i < LstMoisVal->Count; i++) {
			moisVal = (CL_IntFloat*) LstMoisVal->Items[i];
			m = moisVal->i;
			flux[m] += moisVal->Val;
		}
		return;
	}
	if (Valeur) //131205
	{
		for (m = 0; m < 120; m++)
			flux[m] = Valeur[m];
	}
}
//---------------------------------------------------------------------------
void CL_TresoMens::TrouveMinMax(float &vMin, float &vMax, int mMin, int mMax) {
	int i, m;
	CL_IntFloat *moisVal;

	vMin = MAXFLOAT;
	vMax = MINFLOAT;
	if (LstMoisVal != NULL) {
		for (i = 0; i < LstMoisVal->Count; i++) {
			moisVal = (CL_IntFloat*) LstMoisVal->Items[i];
			m = moisVal->i;
			if (m < mMin)
				continue;

			if (m >= mMax)
				return;

			if (moisVal->Val < vMin)
				vMin = moisVal->Val;
			if (moisVal->Val > vMax)
				vMax = moisVal->Val;
		}
	}
	if (Valeur) {
		for (m = mMin; m < mMax; m++) {
			if (Valeur[m] < vMin)
				vMin = Valeur[m];
			if (Valeur[m] > vMax)
				vMax = Valeur[m];

		}
	}
}
//---------------------------------------------------------------------------
void CL_TresoMens::AffGrilleValeur(TStringGrid *SG, int r, int digits) {
	int i, m, n, c;
	float val;
	CL_IntFloat *moisVal;

	switch (Contient) {
	case UnITEM:
		SG->Cells[0][r] = AnsiString("      ") + Nom;
		break;
	case TITRECAT:
		SG->Cells[0][r] = AnsiString("   ") + Nom;
		break;
	case TITREFAM:
	case RESGLOB:
		SG->Cells[0][r] = AnsiString(Nom);
		break;
	case RESTVA:
		SG->Cells[0][r] = AnsiString("   ") + Nom;
		break;
	case TOTCAT:
		SG->Cells[0][r] = AnsiString("   ") + Nom;
		break;
	case TOTFAM:
		SG->Cells[0][r] = AnsiString(Nom) + " Total ht";
		break;
	default:
		ShowMessage("CL_TresoMens::AffGrille Oubli");
	}

	SG->Objects[0][r] = (TObject*) this;
	SG->Objects[1][r] = (TObject*) ProOuCha; //pour afficher grille en couleur
	if (repartExiste == false) {
		SG->Cells[1][r] = "?";
		SG->RowCount++;
		return;
	}

	SG->Cells[1][r] = "";
	if (Contient == TITRECAT) {
		SG->RowCount++;
		return;
	}
	if (Contient == TITREFAM) {
		SG->RowCount++;
		return;
	}
	if (LstMoisVal) {
		for (i = 0; i < LstMoisVal->Count; i++) {
			moisVal = (CL_IntFloat*) LstMoisVal->Items[i];
			m = moisVal->i;
			val = moisVal->Val;
			if (ProOuCha == CHARGE)
				val = -val;
			SG->Cells[m + 2][r] = FloatToStrF((double) val, ffNumber, 7,
					digits);
		}
		SG->RowCount++;
	}
	if (Valeur) //voir c=2 ou c=3 quantité ou valeur
	{
		for (n = 0, c = 2; n < 120; n++, c++) {
			if (Valeur[n] == 0)
				continue;
			if (ProOuCha == CHARGE)
				SG->Cells[c][r] = FloatToStrF((double) -Valeur[n], ffNumber, 7,
						digits);
			else
				SG->Cells[c][r] = FloatToStrF((double) Valeur[n], ffNumber, 7,
						digits);

		}
		SG->RowCount++;
	}
}
//---------------------------------------------------------------------------
void CL_TresoMens::AffGrilleQuantite(TStringGrid *SG, int r, int digits) {
	int i, m;
	CL_IntFloat *moisVal;
	switch (Contient) {
	case UnITEM:
		SG->Cells[0][r] = AnsiString("      ") + Nom;
		break;
	case TITRECAT:
		SG->Cells[0][r] = AnsiString("   ") + Nom;
		break;
	case TITREFAM:
	case RESGLOB:
		SG->Cells[0][r] = AnsiString(Nom);
		break;
//		case TOTCAT:
//			SG->Cells[0][r]=AnsiString("   ")+Nom;
//            break;
//		case TOTFAM:
//			SG->Cells[0][r]=AnsiString(Nom) +" Total ht";
//            break;
	default:
		ShowMessage("CL_TresoMens::AffGrille Oubli");
	}

	SG->Objects[0][r] = (TObject*) this;
	SG->Objects[1][r] = (TObject*) ProOuCha; //pour afficher grille en couleur
	if (repartExiste == false) {
		SG->Cells[2][r] = "?";
		SG->RowCount++;
		return;
	}

	if (Contient == TITRECAT) {
		SG->RowCount++;
		return;
	}
	if (Contient == TITREFAM) {
		SG->RowCount++;
		return;
	}

	SG->Cells[1][r] = QuanVal->Item->SysUnite->UTrans;

	if (LstMoisVal == NULL)
		return;

	for (i = 0; i < LstMoisVal->Count; i++) {
		moisVal = (CL_IntFloat*) LstMoisVal->Items[i];
		m = moisVal->i;
		SG->Cells[m + 3][r] = FloatToStrF((double) moisVal->Val, ffNumber, 7,
				digits);
	}
	SG->RowCount++;
}

