//---------------------------------------------------------------------------
#include <vcl.h>
#include <values.h>
#include <stack>
#include <math.h>

using namespace std;
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "Erreur.h"
#include "Forme0.h"

#include "Compilateur.h"

//#include "CompCalcul.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool CL_Compil::Calculer(CL_Reseau *reseau, CL_Arbre *arbre, int exDeb,
		int exFin, float *valeur) {
	int ex;
	float res, resultat[N_X];
	/* test
	 ofstream outfile("compil.txt");
	 Arbre=arbre;
	 ecrireArbre(outfile );
	 outfile.close();
	 */
	//101002
//    Reseau=reseau;           //121102
	Erreur = false;
	if (reseau) {
		for (ex = exDeb; ex < exFin; ex++) //les années
				{
			res = 0;
			traiterReseau(reseau, arbre, 0, ex, res); //121102
			resultat[ex] = res;
		}
	} else if (arbre) {
		if (arbre->BrancheX > 0) {
			for (ex = exDeb; ex < exFin; ex++) //les années
					{
				res = 0;
				traiterArbre(arbre, arbre->BrancheX - 1, ex, res);
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
bool CL_Compil::traiterArbre(CL_Arbre *arbre, int b, int ex, float &res) {
	int j;
	int date;
//CL_Elt *elt;
	float *valeur;
	float *valPasse;
	AnsiString message;
	float resG, resD;
	ST_Branche branche;
	CL_Elt *elt;
	CL_Indicateur *indic;
	date = 0; //240512
	branche = arbre->LesBranches[b];
	switch (branche.code) {
	case NOMBRE:
		if (branche.arg[0] == '%')
			res = branche.valeur / 100.;
		else
			res = branche.valeur;
		return true;

	case IDENT:
//if(branche.arg[0]==40 &&  branche.arg[1]==8  && branche.arg[2]==50)
//    branche.arg[1]=161;

		elt = trouveElt(branche.arg[0], branche.arg[1], branche.arg[2]);
		if (elt == NULL) //210502
				{
			ShowMessage("traiterArbre elt=NULL  ");
			res = 0;
			return true;
		}
		if (elt->Item)
			elt->Item->Supprimable = false; //081002

		date = branche.date;

		if (branche.arg[0] == INDIC) //280902
		{
			indic = V_Indicateur->trouve(branche.arg[2]);
			if (date > 0) // valeur de l'indcateur déjà calculé pour une année antérieure
					{
				if (date < 100) {
					if (ex - date >= 0) //indic(N-1)
						res = indic->Valeur[ex - date]; //j est <0
					else {
						j = ex - date;
						if (j < -5)
							res = 0;
						else {
							if (elt->Passe)
								res = elt->Passe[5 + j]; //j est <0
							else
								res = 0;
						}
					}
					return true;
				} else if (date == 100) //indic(N) our obliger à ecrire (N)
						{
					res = indic->Valeur[ex];
					return true;
				} else //indic(1) date a été stocké avec +100 et 1 utilisateur=0 c++
				{
					res = indic->Valeur[date - 101];
					return true;
				}
			} else if (indic->Flag == false) {
				Calculer(indic->Prog->Reseau, indic->Prog->Arbre, ex, ex + 1,
						indic->Valeur);
				indic->Flag = true;
			}
			elt->Valeur = indic->Valeur;
		}
		valeur = elt->Valeur;

		j = ex - date;
		if (date == 100)
			j = ex; //truc(N)
		if (date > 100)
			j = date - 100 - 1; //truc(3)

		if (j < 0) {
			//donnees antérieures
			if (j < -5) {
				res = 0;
				return true;
			}
			valPasse = elt->Passe;
			if (valPasse == NULL)
				res = 0;
			else
				res = valPasse[5 + j]; //j est <0
			return true;
		}
		if (valeur == NULL) //250512
				{
			Forme0Frm->CompleteElt(elt, AgriEnCours);
			valeur = elt->Valeur;
		}
		res = valeur[j];
		return true;

	case TOTSUR:
		res = TotalSurface(ex);
		return true;

	case 'N':
		res = ex + 1; // ec C++ on commence à 0 mais pour l'utilisateur on commence à l'année 1
		return true;

	case AN:
		if (AgriEnCours)
			res = AgriEnCours->DefSim->An_0 + ex;
		else
			res = 0;
		return true;

	case SIGMA: //010302
		res = Sigma(ex, branche.arg[0], branche.arg[1]);
		return true;

	case LOG:
		traiterArbre(arbre, branche.arg[0], ex, res);
		if (res > 0)
			res = log(res);
		else
			res = -99999.;
		return true;

	case EXP:
		traiterArbre(arbre, branche.arg[0], ex, res);
		res = exp(res);
		return true;

	case '+':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT || resD == MAXFLOAT)
			res = MAXFLOAT;
		else
			res = resG + resD;
		return true;

	case '-':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT || resD == MAXFLOAT)
			res = MAXFLOAT;
		else
			res = resG - resD;
		return true;

	case '*':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT || resD == MAXFLOAT)
			res = MAXFLOAT;
		else
			res = resG * resD;
		return true;

	case '/':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;

		if (resG == MAXFLOAT)
			res = 0.; //res=MAXFLOAT;
		else if (resD != 0.)
			res = resG / resD;
		else
			res = 0.; //MAXFLOAT;
		return true;

	case MUNAIRE:
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		res = -resG;
		return true;

	case ET:
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG && resD);
		return true;

	case OU:
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG || resD);
		return true;

	case '<':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG < resD);
		return true;

	case '>':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG > resD);
		return true;

	case INFEG:
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG <= resD);
		return true;

	case SUPEG:
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG >= resD);
		return true;

	case '#':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG != resD);
		return true;

	case '=':
		if (traiterArbre(arbre, branche.arg[0], ex, resG) == false)
			return false;
		if (traiterArbre(arbre, branche.arg[1], ex, resD) == false)
			return false;
		res = (float) (resG == resD);
		return true;
// a voir
	default:
		res = 0;
//			message=AnsiString("Oubli traiterArbre dans  ")+JeTraite;
//			ShowMessage(message);
		return true;
	}
}
//---------------------------------------------------------------------------
//V_elt contient des elt
//  n°Famille
//      n°catégorie
//          n° item
//tous les elt d'une catégorie sont à la suite
//dès que l'elt suivant n'est pas de la même cateégorie ou de la meme famille
// je peux arreter
//---------------------------------------------------------------------------
float CL_Compil::Sigma(int ex, int noFam, int noCat) {
	int i, k;
	CL_Elt *elt;
	float total;
	total = 0;
	for (i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (elt->NoFamille == noFam && elt->NoCategorie == noCat) {
			total += elt->Valeur[ex];
			k = i + 1; //310105
			if (k >= V_Elt->Nbelt)
				return total;
			elt = V_Elt->Vecteur[k]; //091104
			if (elt->NoFamille != noFam || elt->NoCategorie != noCat)
				return total;
		}
	}
	return total;

}
//---------------------------------------------------------------------------
float CL_Compil::TotalSurface(int ex) {
	int i, k;
	CL_Elt *elt;
	CL_Atelier *culture;
	CL_Valeur *valeur;
	float total;
	int j;
	total = 0;
	for (i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		//retirer les dérobées
		//ce serait + simple si elt->Item était informé A VOIR
		if (elt->NoFamille == CULTURE) {
			culture = NULL;
			for (j = 0; j < AgriEnCours->V_Culture->Nbelt; j++) {
				valeur = AgriEnCours->V_Culture->Vecteur[j];
				culture = valeur->Atelier;
				if (culture->No == elt->NoItem)
					break;
			}
			if (culture == NULL || culture->Derobe == true)
				continue; //021210
			total += elt->Valeur[ex];
			k = i + 1; //310105
			if (k >= V_Elt->Nbelt)
				return total;
			elt = V_Elt->Vecteur[k]; //091104
			if (elt->NoFamille != CULTURE)
				return total;
		}
	}
	return total;
}
/*
 //---------------------------------------------------------------------------
 float CL_Compil::Sigma(int ex,int noFam,int noCat)
 {
 int i;
 CL_Elt *elt;
 float total;
 total=0;
 for(i=0;i<V_Elt->Nbelt;i++)
 {
 elt=V_Elt->Vecteur[i];
 if(   elt->NoFamille==  noFam  && elt->NoCategorie==noCat)
 {
 while(1)
 {
 total +=elt->Valeur[ex];
 i++;
 elt=V_Elt->Vecteur[i];                       //091104
 if(elt->NoFamille!=noFam ||elt->NoCategorie!=noCat)  return total;
 }
 }
 }
 return total;

 }
 */
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CL_Compil::traiterReseau(CL_Reseau *reseau, CL_Arbre *arbre, int m, int an,
		float &resultat) {
	m = 0;
	while (m != -1) {
		m = traiterMaille(reseau, arbre, m, an, resultat); //121102
	}
}
//---------------------------------------------------------------------------
int CL_Compil::traiterMaille(CL_Reseau *reseau, CL_Arbre *arbre, int m, int i,
		float &resultat) //121102
		{
	float res;
//ST_Maille maille=Reseau->LesMailles[m];
	ST_Maille maille = reseau->LesMailles[m]; //121102
	switch (maille.code) {
	case SI:
		traiterArbre(arbre, maille.branche, i, res);
		if (res == 0.)
			return maille.apD;
		else
			return maille.apG;
	case NUM:
		traiterArbre(arbre, maille.branche, i, res);
		resultat = res;
		return maille.apG;
	case PONT:
		return maille.apG;
	default:
		erreur("Reseau identificateur inconnu");
		return -1;
	}
}

