//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
#include "LireFichier.h"

#include "Immo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//void projeter_emprunt_r_const(ST_EMPRUNT *ptr_emp,float *tot_int,float *tot_cap);
//void projeter_emprunt_r_var  (ST_EMPRUNT *ptr_emp,float *tot_int,float *tot_cap);
static float verst_const(float valeur, float taux, float duree);

/*-------------------------------------------------------------------------*/
/*
 remboursement constant prog g‚n‚ral
 au maximum pret de 51 ans  ->  detteLT[51] etc...
 calcul sur ces vecteurs  pour l'ann‚e i
 puis d‚calage pour resituer dans le temps de la simulation
 ptr_emp->duree  dur‚e premier  taux
 ptr_emp->dure2  dur‚e deuxieme taux

 */
/*-------------------------------------------------------------------------*/

//class CL_EmpLT::RembVariable(void);
void CL_EmpLT::RembConstant(void)
//;void projeter_emprunt_r_const(ST_EMPRUNT *ptr_emp,float *tot_int,float *tot_cap)
		{
	float detteLT[51], detteCT[51], capRemb[51], interet[51];
	float verst, du, remb, interest, taux, taux1, taux2;
	int m, m_remb, deltaT, i, duree, duree1, duree2, chgtEx, delai;
	int j, j0, j9, n0, n, a_real;
	bool flagChgtTaux = false;
	char periodicite = Type[1];

	memset(detteLT, 0, sizeof(float) * 51);
	memset(detteCT, 0, sizeof(float) * 51);
	memset(capRemb, 0, sizeof(float) * 51);
	memset(interet, 0, sizeof(float) * 51);

	if (periodicite == CarMens) {
		taux1 = (Taux / 12.) / 100.;
		taux2 = (Taux2 / 12.) / 100.;

		duree1 = Duree;
		duree2 = Duree2;
		duree = duree1 + duree2;

		deltaT = 1;
	} else if (periodicite == CarTrim) {
		taux1 = (Taux / 4.) / 100.;
		taux2 = (Taux2 / 4.) / 100.;

		duree1 = Duree / 3.;
		duree2 = Duree2 / 3.;
		duree = duree1 + duree2;

		deltaT = 3;
	} else if (periodicite == CarSem) {
		taux1 = (Taux / 2.) / 100.;
		taux2 = (Taux2 / 2.) / 100.;

		duree1 = Duree / 6.;
		duree2 = Duree2 / 6.;
		duree = duree1 + duree2;

		deltaT = 6;
	} else if (periodicite == CarAn) {
		taux1 = (Taux) / 100.;
		taux2 = (Taux2) / 100.;

		duree1 = Duree / 12.;
		duree2 = Duree2 / 12.;
		duree = duree1 + duree2;

		deltaT = 12;
	}

	//lprintf(" duree ptr_emp->duree %3d %3d\n",duree, ptr_emp->duree);
	m = ptr_emp->m_real;
	if (m < Mois_0)
		chgtEx = Mois_0;
	else
		chgtEx = Mois_0 + 12;

	du = ptr_emp->valeur;
	m_remb = (ptr_emp->m_remb + ptr_emp->a_remb * 12)
			- (ptr_emp->m_real + ptr_emp->a_real * 12) + ptr_emp->m_real;

	delai = (m_remb - m) / deltaT;
	duree -= delai - 1;
	//calcul annuit‚s
	taux = taux1;
	verst = verst_const(ptr_emp->valeur, taux, duree);

	i = 0;
	//lprintf("i m m_remb chgtEx duree verst du %2d %2d %2d %2d %2d   %8.0f %8.0f \n",i,m,m_remb,duree,chgtEx,verst,du);
	interest = remb = 0;
	//lprintf("   i  m m_remb   du       int       int[i]   remb   remb[i]\n");
	while (1) {
		m += deltaT;
		if (m >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = du;
			i++;
		}

		if (m == m_remb)
			break;
		else
			interet[i] += du * taux;
		//lprintf("S %2d %2d %2d %8.0f %8.0f %8.0f %8.0f %8.0f\n",i,m,m_remb,du,interest,interet[i],remb,capRemb[i]);
	}
	flagChgtTaux = false;
	while (1) {
		if (duree2 > 0 && flagChgtTaux == NON
				&& m > ptr_emp->m_real + duree1 * deltaT) {
			taux = taux2;
			verst = verst_const(du, taux, duree2);
			flagChgtTaux = true;
		}
		interest = du * taux;
		interet[i] += interest;
		remb = verst - interest;
		if (remb >= du) {
			remb = du;
			capRemb[i] += remb;
			du = 0;
			//lprintf("F %2d %2d %2d %8.0f %8.0f %8.0f %8.0f %8.0f\n",i,m,m_remb,du,interest,interet[i],remb,capRemb[i]);
			break;
		}
		capRemb[i] += remb;
		du -= remb;
		//lprintf("A %2d %2d %2d %8.0f %8.0f %8.0f %8.0f %8.0f\n",i,m,m_remb,du,interest,interet[i],remb,capRemb[i]);
		m += deltaT;

		if (m >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = du;
			i++;
		}
	}

	a_real = ptr_emp->a_real;
	if (ptr_emp->m_real < Mois_0)
		a_real--;
	calcul_j0_j9_n0(a_real, ptr_emp->duree, &j0, &j9, &n0);

	memset(ptr_emp->detteLT, 0, sizeof(float) * TAILLE);
	memset(ptr_emp->detteCT, 0, sizeof(float) * TAILLE);
	memset(ptr_emp->capRemb, 0, sizeof(float) * TAILLE);
	memset(ptr_emp->interet, 0, sizeof(float) * TAILLE);

	if (j9 > TAILLE)
		j9 = TAILLE;
	for (j = j0, n = n0; j < j9; j++, n++) {
		ptr_emp->detteLT[j] = detteLT[n];
		ptr_emp->detteCT[j] = detteCT[n];
		ptr_emp->capRemb[j] = capRemb[n];
		ptr_emp->interet[j] = interet[n];
	}

	(*tot_int) = 0.;
	(*tot_cap) = 0.;
	//for(j=0;j<50;j++)lprintf(" %d %6.0f %6.0f\n",j,interet[j],capRemb[j]);
	//lprintf("%3d %3d %3d %3d\n",ptr_emp->duree,ptr_emp->duree2,deltaT,duree);
	duree = (ptr_emp->duree + ptr_emp->duree2) / 12 + 2;
	for (j = 0; j < duree; j++) {
		(*tot_int) += interet[j];
		(*tot_cap) += capRemb[j];
	}
}
/**/
/*-------------------------------------------------------------------------*/
/*               valeur * taux                     a
 annuite=  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ           =  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
 1 -     1                  1 -           1
 ÄÄÄÄÄÄÄÄÄÄÄ                   ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
 duree                     duree
 (1  +  taux )                      ( b)
 */
/*-------------------------------------------------------------------------*/
static float verst_const(float valeur, float taux, float duree) {
	float annuite;
	double a, b, c, d;
	if (taux == 0)
		return valeur / duree;
	a = valeur * taux;
	b = 1. + taux;
	c = pow(b, duree);
	d = 1. - 1. / c;
	annuite = a / d;
	/*lprintf("annuite=%10.0f\n",annuite);*/
	return annuite;
}
/**/
/*-------------------------------------------------------------------------*/
/*
 */
/*-------------------------------------------------------------------------*/
void projeter_emprunt_r_var(ST_EMPRUNT *ptr_emp, float *tot_int,
		float *tot_cap) {
	float detteLT[51], detteCT[51], capRemb[51], interet[51];
	float verst, du, remb, interest, taux1, taux2;
	int m, m_remb, deltaT, i, duree, chgtEx, delai;
	int j, j0, j9, n0, n, a_real;

	memset(detteLT, 0, sizeof(float) * 51);
	memset(detteCT, 0, sizeof(float) * 51);
	memset(capRemb, 0, sizeof(float) * 51);
	memset(interet, 0, sizeof(float) * 51);

	if (ptr_emp->type[1] == CarMens) {
		taux1 = (ptr_emp->taux / 12.) / 100.;
		taux2 = (ptr_emp->taux2 / 12.) / 100.;
		duree = ptr_emp->duree + ptr_emp->duree2;
		deltaT = 1;
	} else if (ptr_emp->type[1] == CarTrim) {
		taux1 = (ptr_emp->taux / 4.) / 100.;
		taux2 = (ptr_emp->taux2 / 4.) / 100.;
		duree = ptr_emp->duree + ptr_emp->duree2;
		duree = duree / 3.;
		deltaT = 3;
	} else if (ptr_emp->type[1] == CarSem) {
		taux1 = (ptr_emp->taux / 2.) / 100.;
		taux2 = (ptr_emp->taux2 / 2.) / 100.;
		duree = ptr_emp->duree + ptr_emp->duree2;
		duree = duree / 6.;
		deltaT = 6;
	} else if (ptr_emp->type[1] == CarAn) {
		taux1 = (ptr_emp->taux) / 100.;
		taux2 = (ptr_emp->taux2) / 100.;
		duree = ptr_emp->duree + ptr_emp->duree2;
		duree = duree / 12.;
		deltaT = 12;
	}

	m = ptr_emp->m_real;
	if (m < Mois_0)
		chgtEx = Mois_0;
	else
		chgtEx = Mois_0 + 12;

	du = ptr_emp->valeur;
	//mois du premier remboursement
	m_remb = (ptr_emp->m_remb + ptr_emp->a_remb * 12)
			- (ptr_emp->m_real + ptr_emp->a_real * 12) + ptr_emp->m_real;

	delai = (m_remb - m) / deltaT;
	duree -= delai - 1;

	i = 0;

	//lprintf("i m m_remb chgtEx duree verst du %2d %2d %2d %2d %2d   %8.0f %8.0f \n",i,m,m_remb,duree,chgtEx,verst,du);
	interest = remb = 0;
	//lprintf("   i  m m_remb   du       int       int[i]   remb   remb[i]\n");

	//diff‚r‚ de remboursement
	while (1) {
		m += deltaT;
		if (m >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = du;
			i++;
		}
		if (m == m_remb)
			break;
		else
			interet[i] += du * taux1;
		//lprintf("S %2d %2d %2d %8.0f %8.0f %8.0f %8.0f %8.0f\n",i,m,m_remb,du,interest,interet[i],remb,capRemb[i]);
	}

	verst = ptr_emp->valeur / duree;
	while (1) {
		interest = du * taux1;
		interet[i] += interest;
		remb = verst;
		if (remb >= du) {
			remb = du;
			capRemb[i] += remb;
			du = 0;
			//lprintf("F %2d %2d %2d %8.0f %8.0f %8.0f %8.0f %8.0f\n",i,m,m_remb,du,interest,interet[i],remb,capRemb[i]);
			break;
		}
		capRemb[i] += remb;
		du -= remb;
		//lprintf("A %2d %2d %2d %8.0f %8.0f %8.0f %8.0f %8.0f\n",i,m,m_remb,du,interest,interet[i],remb,capRemb[i]);
		m += deltaT;

		if (m >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = du;
			i++;
		}
	}

	a_real = ptr_emp->a_real;
	if (ptr_emp->m_real < Mois_0)
		a_real--;
	calcul_j0_j9_n0(a_real, ptr_emp->duree, &j0, &j9, &n0);

	memset(ptr_emp->detteLT, 0, sizeof(float) * TAILLE);
	memset(ptr_emp->detteCT, 0, sizeof(float) * TAILLE);
	memset(ptr_emp->capRemb, 0, sizeof(float) * TAILLE);
	memset(ptr_emp->interet, 0, sizeof(float) * TAILLE);

	if (j9 > TAILLE)
		j9 = TAILLE;
	for (j = j0, n = n0; j < j9; j++, n++) {
		ptr_emp->detteLT[j] = detteLT[n];
		ptr_emp->detteCT[j] = detteCT[n];
		ptr_emp->capRemb[j] = capRemb[n];
		ptr_emp->interet[j] = interet[n];
	}
	*tot_int = 0.;
	*tot_cap = 0.;

	for (j = 0; j < (ptr_emp->duree / 12) + 2; j++) {
		(*tot_int) += interet[j];
		(*tot_cap) += capRemb[j];
	}

}
