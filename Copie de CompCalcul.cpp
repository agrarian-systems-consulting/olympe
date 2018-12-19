//---------------------------------------------------------------------------
#include <vcl.h>
#include <values.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "Erreur.h"

#include "Compilateur.h"

//#include "CompCalcul.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool CL_Compil::Calculer(CL_Reseau *reseau, CL_Arbre *arbre, int exDeb,
		int exFin, float *valeur) {
	int ex;
	float res, resultat[N_X];
//char chaine[100];
	Arbre = arbre;
	Reseau = reseau;
	Erreur = false;
	if (Reseau) {
		for (ex = exDeb; ex < exFin; ex++) //les années
				{
			res = 0;
			traiterReseau(0, ex, res);
			resultat[ex] = res;
		}
	} else if (Arbre) {
		if (Arbre->BrancheX > 0) {
			for (ex = exDeb; ex < exFin; ex++) //les années
					{
				res = 0;
				traiterArbre(Arbre->BrancheX - 1, ex, res);
				resultat[ex] = res;
			}
		} else {
			for (ex = exDeb; ex < exFin; ex++) //les années
				resultat[ex] = 0;
		}
	} else {
		for (ex = exDeb; ex < exFin; ex++)
			resultat[ex] = 0.;
		Erreur = true;
	}
	for (ex = exDeb; ex < exFin; ex++)
		valeur[ex] = resultat[ex];

	if (Erreur == true)
		return false;
	else
		return true;

	//resultats
	/*
	 for(i=exDeb;i<exFin;i++)
	 {
	 sprintf(chaine," %2d %6.0f ",i,resultat[i]);
	 ErreurFrm->Edit->Lines->Add(chaine);
	 }
	 ErreurFrm->Show();
	 */
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool CL_Compil::traiterArbre(int b, int ex, float &res) {
	int j;
	int date;
//CL_Elt *elt;
	float *valeur;
	AnsiString message;
	float resG, resD;
	ST_Branche branche;
	CL_Elt *elt;
	CL_Indicateur *indic;
	branche = Arbre->LesBranches[b];
	switch (branche.code) {
	case NOMBRE:
		if (branche.arg[0] == '%')
			res = branche.valeur / 100.;
		else
			res = branche.valeur;
		return true;

	case IDENT:
		elt = trouveElt(branche.arg[0], branche.arg[1], branche.arg[2]);
		if (elt == NULL) //210502
				{
			ShowMessage("traiterArbre elt=NULL  ");
			return true;
		}
		if (branche.arg[0] == INDIC) //280902
		{
			indic = V_Indicateur->trouve(branche.arg[2]);
			Calculer(indic->Prog->Reseau, indic->Prog->Arbre, 0, N_X,
					indic->Valeur);
			elt->Valeur = indic->Valeur;

		}
		valeur = elt->Valeur;
		date = branche.date;
		j = ex - date;
		if (j < 0) {
			erreur("date négative");
			j = 0;
		}
		res = valeur[j];
		return true;

	case SIGMA: //010302
		res = Sigma(ex, branche.arg[0], branche.arg[1]);
		return true;

	case '+':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT || resD == MAXFLOAT)
			res = MAXFLOAT;
		else
			res = resG + resD;
		return true;

	case '-':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT || resD == MAXFLOAT)
			res = MAXFLOAT;
		else
			res = resG - resD;
		return true;

	case '*':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT || resD == MAXFLOAT)
			res = MAXFLOAT;
		else
			res = resG * resD;
		return true;

	case '/':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT)
			res = MAXFLOAT;
		else if (resD != 0.)
			res = resG / resD;
		else
			res = MAXFLOAT;
		return true;

	case MUNAIRE:
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		res = -resG;
		return true;

	case ET:
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG && resD);
		return true;

	case OU:
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG || resD);
		return true;

	case '<':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG < resD);
		return true;

	case '>':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG > resD);
		return true;

	case INFEG:
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG <= resD);
		return true;

	case SUPEG:
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG >= resD);
		return true;

	case '#':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG != resD);
		return true;

	case '=':
		if (traiterArbre(branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG == resD);
		return true;

	default:
		message = AnsiString("Oubli traiterArbre") + branche.code;
		ShowMessage(message);
		return true;
	}
}
//---------------------------------------------------------------------------
float CL_Compil::Sigma(int ex, int noFam, int noCat) {
	int i;
	CL_Elt *elt;
	float total;
	total = 0;
	for (i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (elt->NoFamille == noFam && elt->NoCategorie == noCat) {
			while (1) {
				total += elt->Valeur[ex];
				i++;
				elt = V_Elt->Vecteur[i];
				if (elt->NoCategorie != noCat)
					return total;
			}
		}
	}
	return total;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CL_Compil::traiterReseau(int m, int an, float &resultat) {
	m = 0;
	while (m != -1) {
		m = traiterMaille(m, an, resultat);
	}
}
//---------------------------------------------------------------------------
int CL_Compil::traiterMaille(int m, int i, float &resultat) {
	float res;
	ST_Maille maille = Reseau->LesMailles[m];
	switch (maille.code) {
	case SI:
		traiterArbre(maille.branche, i, res);
		if (res == 0.)
			return maille.apD;
		else
			return maille.apG;
	case NUM:
		traiterArbre(maille.branche, i, res);
		resultat = res;
		return maille.apG;
	case PONT:
		return maille.apG;
	default:
		erreur("Reseau identificateur inconnu");
		return -1;
	}
}

