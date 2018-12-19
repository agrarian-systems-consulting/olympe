//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <stdio.h>
#include <vcl\printers.hpp>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//--------------------------------------------------------------------------
//-------------------------------------------------------------------------
bool TFBrouillon::EstVide(int *vecteur) {
	for (int n = 0; n < N_X; n++) {
		if (vecteur[n] != 0)
			return false;
	}
	return true;
}
//-------------------------------------------------------------------------
bool TFBrouillon::EstVide(float *vecteur) {
	for (int n = 0; n < N_X; n++) {
		if (vecteur[n] != 0)
			return false;
	}
	return true;
}
//--------------------------------------------------------------------------
void TFBrouillon::Resultat(AnsiString nom, AnsiString unite, float *valeur,
		TColor couleur) {
	int i, pos;
	TypeImp("Courier", size2, couleur, 'M');

	AsLambda = AsBlanc;

	AsLambda.Insert(nom.Trim(), posNom);
	AsLambda += AsBlanc;
	AsLambda.Insert(unite.Trim(), posUnite);
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
void TFBrouillon::Resultat(AnsiString nom, float *valeur, TColor couleur) {
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
void TFBrouillon::Resultat(AnsiString nom, int *valeur, TColor couleur) {
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
// dette sur 11 années :bilan ouverture
//interet sur 10
//--------------------------------------------------------------------------
void TFBrouillon::ResultatBilan(AnsiString nom, float *valeur, int nX,
		TColor couleur) {
	int i, pos;
	TypeImp("Courier", size2, couleur, 'M');

	AsLambda = AsBlanc;

	AsLambda.Insert(nom.Trim(), posNom);
	AsLambda += AsBlanc;
	if (valeur == NULL)
		return;

	if (nX == N_X)
		pos = posVal + delta;
	else
		pos = posVal;

	for (i = 0; i < nX; i++, pos += delta) {
		if (valeur[i] != 0.)
			placer(valeur[i], pos, 0);
		AsLambda += AsBlanc;
	}

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
void TFBrouillon::Total(AnsiString nom, float *valeur, TColor couleur) {

//    Memo1->SelAttributes->Style=TFontStyles()<<fsBold;
	Trait();
	TypeImp("Courier", size2, couleur, 'M');
	Resultat(nom, valeur);

}

