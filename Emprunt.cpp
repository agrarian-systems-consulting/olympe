//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma hdrstop
#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
#include "FichierLire.h"
#include "Erreur.h"
//#include "Decale.h"
#include "Forme01.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "Emprunt.h"
/*
 attention aux indices pour les comptres de bilan
 Dette[0] dette au début de l'exercice 0
 Remb [0] remboursemnent dans l'exercice 0
 Dette[1]=Dette[0]-Remb[0]
 dette à la fin de l'exercice 0
 ou au début    de l'exercice 1
 */
//---------------------------------------------------------------------------
#pragma package(smart_init)
extern CL_Trad *T;

//int CalculExercice(int aReal,int mReal,int an_0,int mois_0);
//-----------------------------------------------------------------------
int CalculExercice(int aReal, int mReal, int an_0, int mois_0) {
	int n;
	n = (aReal - an_0) * 12 + mReal - mois_0;
	if (n >= 0)
		return n / 12;

	n++;
	n /= 12;
	return n - 1;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//void CL_EmpLT::Calcul(void)
void CL_EmpLT::Calcul(int an_0, float *capital, float *remb, float *interet,
		float *dette) {
	char type; //rustine mais ou est l'erreur dans variante
	if (Type == NULL)
		type = CarConst;
	else
		type = Type[1];
	ExReal = CalculExercice(AReal, MReal, an_0, Mois_0);
//test
	type = type;
	; //aew

	if (type == CarConst)
		RembConstant(capital, remb, interet, dette);
	else if (type == CarVar)
		RembVariable(capital, remb, interet, dette);
	else if (type == CarDif)
		RembDiffere(capital, remb, interet, dette, an_0, Mois_0);

}

//-------------------------------------------------------------------------
/*
 remboursement constant prog général
 au maximum pret de 51 ans  ->  detteLT[51] etc...
 calcul sur ces vecteurs  pour l'année i
 puis décalage pour resituer dans le temps de la simulation
 Duree  durée premier  taux
 Duree2  durée deuxieme taux

 */
//-----------------------------------------------------------------------
void CL_EmpLT::RembConstant(float *capital, float *remb, float *interet,
		float *dette) {
	float detteLT[51], rembLT[51], intLT[51];
	float verst, du, rembt, interest, taux, taux1, taux2;
	int deltaT, i, iMax, duree, duree1, duree2, chgtEx;
	int j, n;
	bool flagChgtTaux = false;
	int m, mRemb, mV, mDernierVerst;
	int mInter, decal;
	memset(detteLT, 0, sizeof(float) * 51);
	memset(rembLT, 0, sizeof(float) * 51);
	memset(intLT, 0, sizeof(float) * 51);
	//si plus d'un an entre real et rembt réduire duree emprunt
	mInter = (ARemb - AReal) * 12 + MRemb - MReal - 1;
	decal = mInter / 12;
	duree1 = Duree - decal;

	TauxDuree(taux1, taux2, duree1, duree2, duree, deltaT);

	//calcul annuités
	taux = taux1;
	verst = VerstConst(Montant, taux, duree);

	if (MReal < Mois_0)
		chgtEx = Mois_0;
	else
		chgtEx = Mois_0 + 12;

	//nouvelle ecriture
	mRemb = (ARemb - AReal) * 12 + MRemb;
	mV = mRemb;
	while (mV > MReal + deltaT)
		mV -= deltaT;
	i = 0;
	mDernierVerst = MReal;
	while (mV < mRemb) {
		interest = Montant * taux * (mV - mDernierVerst) / deltaT;
		mDernierVerst = mV;
		if (mV >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = Montant;
			i++;
		}
		intLT[i] += interest;
		mV += deltaT;
	}
	//PremiersVersements
	du = Montant;
	if (mRemb >= chgtEx) {
		chgtEx += 12;
		detteLT[i] = Montant;
		i++;
	}
	interest = Montant * taux * (mRemb - mDernierVerst) / deltaT;
	rembt = verst - Montant * taux;
	du -= rembt;
	intLT[i] += interest;
	rembLT[i] += rembt;
	m = mRemb + deltaT;

	flagChgtTaux = false;
	while (1) {
		if (m >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = du;
			i++;
		}
		if (duree2 > 0 && flagChgtTaux == false
				&& m > MReal + duree1 * deltaT) {
			taux = taux2;
			verst = VerstConst(du, taux, duree2);
			flagChgtTaux = true;
		}
		interest = du * taux;
		intLT[i] += interest;
		rembt = verst - interest;
		if (rembt >= du) {
			rembt = du;
			rembLT[i] += rembt;
			du = 0;
			break;
		}
		rembLT[i] += rembt;
		du -= rembt;
		m += deltaT;

	}
	iMax = i + 1;
	TotInt = 0;
	for (j = 0; j < iMax + 1; j++)
		TotInt += intLT[j];
//test
	float totCap = 0;
	for (j = 0; j < iMax + 1; j++)
		totCap += rembLT[j];
//...fin test
	memset(dette, 0, sizeof(float) * (N_X + 1));
	memset(remb, 0, sizeof(float) * N_X);
	memset(interet, 0, sizeof(float) * N_X);
	if (ExReal == 0) {
		dette[0] = 0;
		for (i = 0; i < iMax; i++) {
			if (i >= N_X)
				break;
			remb[i] = rembLT[i];
			interet[i] = intLT[i];
			dette[i + 1] = detteLT[i];
		}
	} else if (ExReal > 0) {
//        Dette[ExReal]=0;
		for (i = 0; i < iMax; i++) {
			if (i + ExReal >= N_X)
				break;
			remb[i + ExReal] = rembLT[i];
			interet[i + ExReal] = intLT[i];
			dette[i + 1 + ExReal] = detteLT[i];
		}
	} else if (ExReal < 0) {
		n = -ExReal;
		dette[0] = detteLT[n - 1];
		for (i = 0; i < iMax; i++) {
			if (i >= N_X)
				break;
			remb[i] = rembLT[i + n];
			interet[i] = intLT[i + n];
			dette[i + 1] = detteLT[i + n];
		}
	}
	/*
	 //test
	 char buf[100];
	 ErreurFrm->Close();
	 ErreurFrm->Edit->Clear();

	 for(i=0; i<10 ; i++)
	 {
	 sprintf(buf," %4d  %8.0f%8.0f%8.0f",i,
	 capRemb[i],interet[i],detteLT[i]);
	 ErreurFrm->Edit->Lines->Add(buf);
	 }
	 sprintf(buf,"ExReal=%d",ExReal);
	 ErreurFrm->Edit->Lines->Add(buf);
	 //...
	 int k;
	 char blanc[40];
	 memset(blanc,' ',sizeof(char)*32);
	 blanc[24]=0;

	 sprintf(buf,"%s",Nom);
	 ErreurFrm->Edit->Lines->Add(buf);
	 sprintf(buf,"______________________________________");
	 ErreurFrm->Edit->Lines->Add(buf);
	 sprintf(buf,"         verst    cap    int    du    ");
	 ErreurFrm->Edit->Lines->Add(buf);
	 sprintf(buf,"______________________________________");
	 ErreurFrm->Edit->Lines->Add(buf);
	 sprintf(buf," %4d %s %8.0f",an_0-1,blanc,Dette[0]);
	 ErreurFrm->Edit->Lines->Add(buf);

	 for(k=0,j=an_0; k<N_X; k++,j++)
	 {
	 sprintf(buf," %4d  %8.0f%8.0f%8.0f%8.0f",j,
	 Interet[k]+CapRemb[k]
	 , CapRemb[k]
	 , Interet[k]
	 , Dette[k+1]);
	 ErreurFrm->Edit->Lines->Add(buf);
	 }
	 sprintf(buf,"______________________________________");
	 ErreurFrm->Edit->Lines->Add(buf);

	 sprintf(buf,"Total  %8.0f%8.0f%8.0f        ",
	 TotInt+Montant,
	 Montant,
	 TotInt );
	 ErreurFrm->Edit->Lines->Add(buf);
	 sprintf(buf,"______________________________________");
	 ErreurFrm->Edit->Lines->Add(buf);
	 ErreurFrm->Show();

	 //...
	 ErreurFrm->Show();
	 */
}
//-------------------------------------------------------------------------
void CL_EmpLT::TauxDuree(float &taux1, float &taux2, int &duree1, int &duree2,
		int &duree, int &deltaT) {
	char periodicite = Type[2];
	int mInter;
	int report;
	//si plus d'un an entre real et remb réduire duree emprunt

	mInter = (ARemb - AReal) * 12 + MRemb - MReal; //exprimé en mois
	if (periodicite == CarMens) {
		taux1 = (Taux / 12.) / 100.;
		taux2 = (Taux2 / 12.) / 100.;
		deltaT = 1;
		report = mInter / deltaT - 1;
		duree1 = Duree * 12 - report;
		duree2 = Duree2 * 12;
		duree = duree1 + duree2;

	} else if (periodicite == CarTrim) {
		taux1 = (Taux / 4.) / 100.;
		taux2 = (Taux2 / 4.) / 100.;
		deltaT = 3;
		report = mInter / deltaT - 1;
		duree1 = Duree * 4 - report;
		//duree1=Duree*4;
		duree2 = Duree2 * 4;
		duree = duree1 + duree2;
	} else if (periodicite == CarSem) //semestriel
			{
		taux1 = (Taux / 2.) / 100.;
		taux2 = (Taux2 / 2.) / 100.;
		deltaT = 6;
		report = mInter / deltaT - 1;
		duree1 = Duree * 2 - report;
		duree2 = Duree2 * 2;
		duree = duree1 + duree2;

	} else if (periodicite == CarAn) {
		taux1 = (Taux) / 100.;
		taux2 = (Taux2) / 100.;
		deltaT = 12;
		report = mInter / deltaT - 1;
		duree1 = Duree - report;
		duree2 = Duree2;
		duree = duree1 + duree2;
	}
}
/*
 //-------------------------------------------------------------------------
 void CL_EmpLT::TauxDuree(float &taux1,float &taux2,int &duree1,int &duree2,
 int &duree,int &deltaT)
 {
 char periodicite=Type[2];
 int mInter;
 int anInter;
 //si plus d'un an entre real et remb réduire duree emprunt

 mInter=(ARemb-AReal)*12+MRemb-MReal;
 anInter=mInter/12;
 //    duree1=Duree-(anInter-1);//decal;  //erreur 240604
 duree1=Duree-anInter;//decal;
 //    duree1=Duree;
 duree2=Duree2;
 duree=duree1+duree2;
 if(periodicite==CarMens)
 {
 taux1=(Taux/12.)/100.;
 taux2=(Taux2/12.)/100.;
 deltaT=1;
 duree1*=12;
 //duree1=Duree*12;
 duree2=Duree2*12;
 duree=duree1+duree2;

 }
 else if(periodicite==CarTrim)
 {
 taux1=(Taux/4.)/100.;
 taux2=(Taux2/4.)/100.;
 deltaT=3;
 duree1*=4;
 //duree1=Duree*4;
 duree2=Duree2*4;
 duree=duree1+duree2;
 }
 else if(periodicite==CarSem)
 {
 taux1=(Taux/2.)/100.;
 taux2=(Taux2/2.)/100.;
 deltaT=6;
 duree1*=2;
 duree1=Duree*2;
 duree2=Duree2*2;
 duree=duree1+duree2;

 }
 else if(periodicite==CarAn)
 {
 taux1=(Taux)/100.;
 taux2=(Taux2)/100.;
 deltaT=12;
 //duree1=Duree;
 duree2=Duree2;
 duree=duree1+duree2;
 }
 }
 */
/*-------------------------------------------------------------------------*/
/*               valeur * taux                     a
 annuite=  ________________       =  _______________________
 1 -     1                  1 -           1
 ____________                  __________________
 duree                     duree
 (1  +  taux )                      ( b)
 */
/*-------------------------------------------------------------------------*/
float CL_EmpLT::VerstConst(float valeur, float taux, int duree) {
	float annuite;
	double a, b, c, d;
	if (taux == 0)
		return valeur / duree;

	a = valeur * taux;
	b = 1. + taux;
	c = pow(b, duree);
	d = 1. - 1. / c;
	annuite = a / d;
	return annuite;
}
//-------------------------------------------------------------------------
//duree2 n sert à rien sinon à utiliser  TauxDuree
// emprunt a durée maxi de 50 ans
//calcul sur 50 ans
// puis report dans les années de simulation
//-------------------------------------------------------------------------
void CL_EmpLT::RembVariable(float *capital, float *remb, float *interet,
		float *dette) {
	float detteLT[51], rembLT[51], intLT[51];
	float verst, du, rembt, interest, taux1, taux2;
	int m, mRemb, deltaT, i, iMax, duree, duree1, duree2, chgtEx;
	int j, n;
	int mV, mDernierVerst;
	int mInter, decal;

	memset(detteLT, 0, sizeof(float) * 51);
	memset(rembLT, 0, sizeof(float) * 51);
	memset(intLT, 0, sizeof(float) * 51);

	//si plus d'un an entre real et rembt réduire duree emprunt
	mInter = (ARemb - AReal) * 12 + MRemb - MReal - 1;
	decal = mInter / 12;
	duree1 = Duree - decal;

	TauxDuree(taux1, taux2, duree1, duree2, duree, deltaT);

	if (MReal < Mois_0)
		chgtEx = Mois_0;
	else
		chgtEx = Mois_0 + 12;

	mRemb = (ARemb - AReal) * 12 + MRemb;
	mV = mRemb;
	while (mV > MReal + deltaT)
		mV -= deltaT;

	i = 0;
	mDernierVerst = MReal;
	while (mV < mRemb) {
		interest = Montant * taux1 * (mV - mDernierVerst) / deltaT;
		mDernierVerst = mV;
		if (mV >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = Montant;
			i++;
		}
		intLT[i] += interest;
		mV += deltaT;
	}
	m = mRemb;
	du = Montant;
	verst = Montant / duree;
	while (1) {
		if (m >= chgtEx) {
			chgtEx += 12;
			detteLT[i] = du;
			i++;
		}
		interest = du * taux1;
		intLT[i] += interest;
		rembt = verst;
		if (rembt >= du) {
			rembt = du;
			rembLT[i] += rembt;
			du = 0;
			break;
		}
		rembLT[i] += rembt;
		du -= rembt;
		m += deltaT;

	}
	iMax = i + 1;
	TotInt = 0;
	for (j = 0; j < 50; j++)
		TotInt += intLT[j];
	for (j = 0; j < N_X + 1; j++)
		dette[j] = 0.;
	for (j = 0; j < N_X; j++)
		remb[j] = 0.;
	for (j = 0; j < N_X + 1; j++)
		interet[j] = 0.;
//    memset(dette,  0,sizeof(float)*(N_X+1));  //150202 pose problème ???
//    memset(remb,   0,sizeof(float)*N_X);
//    memset(interet,0,sizeof(float)*N_X);
	if (ExReal == 0) {
		dette[0] = 0;
		for (i = 0; i < iMax; i++) {
			if (i >= N_X)
				break; //150202
			remb[i] = rembLT[i];
			interet[i] = intLT[i];
			dette[i + 1] = detteLT[i];
		}
	} else if (ExReal > 0) {
//        Dette[ExReal]=0;
		for (i = 0; i < iMax; i++) {
			if (i + ExReal >= N_X)
				break;
			remb[i + ExReal] = rembLT[i];
			interet[i + ExReal] = intLT[i];
			dette[i + 1 + ExReal] = detteLT[i];
		}
	} else if (ExReal < 0) {
		n = -ExReal;
		dette[0] = detteLT[n - 1];
		for (i = 0; i < iMax; i++) {
			if (i >= N_X)
				break;
			remb[i] = rembLT[i + n];
			interet[i] = intLT[i + n];
			dette[i + 1] = detteLT[i + n];
		}
	}
}
//-------------------------------------------------------------------------
/*
 remboursement constant prog général
 au maximum pret de 51 ans  ->  detteLT[51] etc...
 calcul sur ces vecteurs  pour l'année i
 puis décalage pour resituer dans le temps de la simulation
 Duree  durée premier  taux
 Duree2  durée deuxieme taux

 */
//-----------------------------------------------------------------------
void CL_EmpLT::RembDiffere(float *capital, float *remb, float *interet,
		float *dette, int an_0, int mois_0) {
	float detteLT[51], rembLT[51], intLT[51];
	float verst, du, taux;
	int i, n;
	int dureeSV, dureeAV; //duree Sans ou Avec versement

	memset(detteLT, 0, sizeof(float) * 51);
	memset(rembLT, 0, sizeof(float) * 51);
	memset(intLT, 0, sizeof(float) * 51);

	//Pas de versement pendant duree1
	dureeSV = ARemb - AReal - 1;
	dureeAV = Duree - dureeSV;
	taux = Taux / 100.;
	TotInt = 0;
	//période sans versement
	//dette au début de l'exercice
	//emprunt est fait en 0 la dette au debut de l'exercice 1=Montant
	n = 1;
	detteLT[1] = Montant;
	n++;
	for (i = 0; i < dureeSV; i++) {
		intLT[n - 1] = detteLT[n - 1] * taux;
		detteLT[n] = detteLT[n - 1] * (1 + taux);
		TotInt += intLT[n - 1];
		n++;
	}
	//avec versement
	n--;
	du = detteLT[n];
	verst = VerstConst(du, taux, dureeAV);
	for (i = 0; i < dureeAV; i++) {
		intLT[n] = detteLT[n] * taux;
		rembLT[n] = verst - intLT[n];
		detteLT[n + 1] = detteLT[n] - rembLT[n];
		TotInt += intLT[n];
		n++;
	}
	//passage à temps de la simulation
	memset(dette, 0, sizeof(float) * N_X);
	memset(remb, 0, sizeof(float) * N_X);
	memset(interet, 0, sizeof(float) * N_X);
	for (i = 0; i < Duree; i++) {
		n = AReal - an_0 + i;
		if (n < 0)
			continue;
		if (n >= N_X)
			break;
		dette[n] = detteLT[i];
		interet[n] = intLT[i];
		remb[n] = rembLT[i];
	}
	dette[n] = detteLT[i];
}
//-----------------------------------------------------------------------
void CL_EmpLT::Aff(int an_0) {
	int k, j;
	float capital[N_X], remb[N_X], interet[N_X], dette[N_X + 1];
	float vecteur[5];
	char type = this->Type[1];
	Calcul(an_0, capital, remb, interet, dette);

	Forme01Frm->Show();
	Forme01Frm->IniGrilleEmprunt("lt", Nom.c_str()); //ne pas traduire

	memset(vecteur, 0, sizeof(float) * 5);
	vecteur[0] = an_0 - 1;
	vecteur[4] = dette[0];
	Forme01Frm->EcrireLigne(vecteur);
	for (k = 0, j = an_0; k < N_X; k++, j++) {
		vecteur[0] = j;
		if (type == CarDif && remb[k] == 0)
			vecteur[1] = 0; //300407
		else
			vecteur[1] = interet[k] + remb[k];
		vecteur[2] = remb[k];
		vecteur[3] = interet[k];
		vecteur[4] = dette[k + 1];
		Forme01Frm->EcrireLigne(vecteur);
	}
	vecteur[0] = TotInt + Montant;
	vecteur[1] = Montant, vecteur[2] = TotInt;
	vecteur[3] = 0;
	Forme01Frm->EcrireLigne(T->L_Emp_Total, vecteur);
	//Forme01Frm->EcrireLigne("Total",vecteur);
}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void CL_EmpCT::Calcul(int an_0, float *capital, float *remb, float *interet,
		float *dette) {
	float duree;
	char type = Type[1];
	int exReal, exRemb;
	float interest;
	int n0, n1;
	exReal = CalculExercice(AReal, MReal, an_0, Mois_0);
	exRemb = CalculExercice(ARemb, MRemb, an_0, Mois_0);
	duree = (ARemb - AReal) * 12 + (MRemb - MReal);
	interest = Montant * Taux * (duree / 12.) / 100.;

	memset(capital, 0, sizeof(float) * N_X);
	memset(remb, 0, sizeof(float) * N_X);
	memset(interet, 0, sizeof(float) * N_X);
	memset(dette, 0, sizeof(float) * (N_X + 1));

	if (type == CarPreCompte) {
		if (exReal >= 0 && exReal < N_X)
			capital[exReal] = Montant - interest;
		if (exRemb >= 0 && exRemb < N_X)
			remb[exRemb] = Montant;
		if (exReal >= 0 && exReal < N_X)
			interet[exReal] = interest;
		n0 = exReal;
		if (exReal < 0)
			n0 = 0;
		n1 = exRemb;
		if (exRemb > N_X)
			n1 = N_X;
		for (int n = n0; n < n1; n++)
			dette[n + 1] = Montant - interest;
	}
	if (type != CarPreCompte) {
		if (exReal >= 0 && exReal < N_X)
			capital[exReal] = Montant;
		if (exRemb >= 0 && exRemb < N_X)
			remb[exRemb] = Montant;
		if (exRemb >= 0 && exRemb < N_X)
			interet[exRemb] = interest;
		n0 = exReal + 1;
		if (exReal < 0)
			n0 = 0;
		n1 = exRemb + 1;
		if (n1 > N_X + 1)
			n1 = N_X + 1;
		for (int n = n0; n < n1; n++)
			dette[n] = Montant;
	}
}
//-----------------------------------------------------------------------
void CL_EmpCT::Aff(int an_0) {
	int k, j;
	float capital[N_X], remb[N_X], interet[N_X], dette[N_X + 1];
	float vecteur[5];
	Calcul(an_0, capital, remb, interet, dette);
	Forme01Frm->Show();
	Forme01Frm->IniGrilleEmprunt(T->L_Emp_Ct, Nom.c_str());

	memset(vecteur, 0, sizeof(float) * 5);
	vecteur[0] = an_0 - 1;
	vecteur[4] = dette[0];
	Forme01Frm->EcrireLigne(vecteur);
	for (k = 0, j = an_0; k < N_X; k++, j++) {
		vecteur[0] = j;
		vecteur[1] = capital[k];
		vecteur[2] = remb[k];
		vecteur[3] = interet[k];
		vecteur[4] = dette[k + 1];
		Forme01Frm->EcrireLigne(vecteur);
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void CL_Sub::Calcul(int an_0, float *amor, float *vResid) {
	float amAn, am1, vR;
	int n;
	memset(amor, 0, sizeof(float) * N_X);
	memset(vResid, 0, sizeof(float) * (N_X + 1));
	ExReal = CalculExercice(AReal, MReal, an_0, Mois_0);
	amAn = Montant / Duree;
	if (ExReal >= 0 && ExReal < N_X) {
		am1 = amAn * (12 - (MReal - Mois_0)) / 12.;
		amor[ExReal] = am1;
		vResid[ExReal + 1] = Montant - am1;
		for (n = ExReal + 1; n < N_X; n++) {
			if (amAn < vResid[n]) {
				amor[n] = amAn;
				vResid[n + 1] = vResid[n] - amAn;
			} else {
				amor[n] = vResid[n];
				vResid[n + 1] = 0;
				break;
			}
		}
	} else if (ExReal < 0) {
		am1 = amAn * (12 - (MReal - Mois_0)) / 12.;
		vR = Montant - am1;
		for (n = ExReal + 1; n < N_X; n++) {
			if (n < 0) {
				if (vR > amAn)
					vR -= amAn;
				else {
					vR = 0;
					break;
				}
			} else if (n == 0) {
				vResid[n] = vR;
				if (vR > amAn) {
					vResid[n + 1] = vR - amAn;
					amor[n] = amAn;
				} else {
					amor[n] = vR;
					vResid[n + 1] = 0;
					break;
				}
			} else {
				if (amAn < vResid[n]) {
					amor[n] = amAn;
					vResid[n + 1] = vResid[n] - amAn;
				} else {
					amor[n] = vResid[n];
					vResid[n + 1] = 0;
					break;
				}
			}
		}
	}

}
//-----------------------------------------------------------------------
void CL_Sub::Aff(int an_0) {
	float amor[N_X], vResid[N_X + 1];
	int j, k;
	float vecteur[5];

	Calcul(an_0, amor, vResid);

	Forme01Frm->Show();
	Forme01Frm->IniGrilleEmprunt(T->L_Emp_Sub, Nom.c_str());
	//Forme01Frm->IniGrilleAn("sub",Nom.c_str());

	memset(vecteur, 0, sizeof(float) * 5);
	vecteur[0] = an_0 - 1;
	vecteur[2] = vResid[0];
	Forme01Frm->EcrireLigne(vecteur);
	for (k = 0, j = an_0; k < N_X; k++, j++) {
		vecteur[0] = j;
		vecteur[1] = amor[k];
		vecteur[2] = vResid[k + 1];
		Forme01Frm->EcrireLigne(vecteur);
	}
}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void CL_Plact::Calcul(int an_0, int mois_0, float *capital, float *verst,
		float *interet, float *creance) {
	float duree;
	char type = Type;
	int exReal, exTerme;
	float cap, intAn;
	int n;
	exReal = CalculExercice(AReal, MReal, an_0, mois_0);
	exTerme = CalculExercice(ATerme, MTerme, an_0, mois_0);
	duree = (ATerme - AReal) * 12 + (MTerme - MReal);
	// à affecter au premier ou deuxieme exercice
	/*
	 if(MReal>mois_0)
	 pcent1=(float)(MReal -mois_0)/12.;
	 else
	 pcent1=(float)(mois_0- MReal)/12.;
	 pcent2=1-pcent1;
	 */
	memset(capital, 0, sizeof(float) * N_X);
	memset(verst, 0, sizeof(float) * N_X);
	memset(interet, 0, sizeof(float) * N_X);
	memset(creance, 0, sizeof(float) * (N_X + 1));

	if (duree < 12) {
		capital[exReal] = Montant;
		intAn = Montant * Taux * (duree / 12.) / 100.;
		interet[exTerme] = intAn;
		verst[exTerme] = Montant + intAn;
		return;
	}

	if (type == CarPlactFin) {
		// année 1
//        int1=Montant*(Taux/12.)*(12-(MReal-Mois_0))/12.;
		if (exReal >= 0 && exReal < N_X) {
			capital[exReal] = Montant;
			creance[exReal + 1] = Montant;
		}
		cap = Montant;
		for (n = exReal + 1; n <= exTerme; n++) {
			if (n >= N_X)
				break;
			if (n == 0)
				creance[0] = cap;
			//intAn1=(cap*Taux/100)*pcent1;
			//intAn2=(cap*Taux/100)*pcent2;
			intAn = cap * Taux / 100;
			cap += intAn;
			if (n < 0)
				continue;

			creance[n + 1] = cap;
			interet[n] = intAn;
			//interet[n+1] +=  intAn2;

			if (n == exTerme) {
				verst[n] = cap;
				creance[n + 1] = 0;
				break;
			}
		}
	} else if (type == CarPlactAn) {
		if (exReal >= 0 && exReal < N_X)
			capital[exReal] = Montant;
		for (n = exReal; n < exTerme; n++) {
			/*
			 if(n>=N_X)break;
			 if(n<0) continue;
			 if(n==0)
			 creance[n]=Montant;
			 */
			if (n + 1 >= N_X)
				break;
			if (n + 1 < 0)
				continue;
			creance[n + 1] = Montant;

		}
		for (n = exReal + 1; n <= exTerme; n++) {
			if (n < 0)
				continue;
			if (n >= N_X)
				break;

			intAn = Montant * Taux / 100;
			interet[n] = intAn;
			verst[n] = intAn;
			creance[n + 1] = Montant;

			if (n == exTerme) {
				verst[n] = Montant + intAn;
				creance[n + 1] = 0;
				break;
			}
		}
	}
}
//-----------------------------------------------------------------------
void CL_Plact::Aff(int an_0, int mois_0) {
	int k, j;
	float capital[N_X], verst[N_X], interet[N_X], creance[N_X + 1];
	float vecteur[5];

	Calcul(an_0, mois_0, capital, verst, interet, creance);
	Forme01Frm->Show();
	Forme01Frm->IniGrilleEmprunt(T->L_Emp_Plact, Nom.c_str());
	//Forme01Frm->IniGrilleAn("plact",Nom.c_str());

	memset(vecteur, 0, sizeof(float) * 5);

	vecteur[0] = an_0 - 1;
	vecteur[4] = creance[0];
	Forme01Frm->EcrireLigne(vecteur);

	for (k = 0, j = an_0; k < N_X; k++, j++) {
		vecteur[0] = j;
		vecteur[1] = capital[k];
		vecteur[2] = interet[k];
		vecteur[3] = verst[k];
		vecteur[4] = creance[k + 1];
		Forme01Frm->EcrireLigne(vecteur);
	}
}

//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void CL_Immo::Calcul(int an_0, float *amorMat, float *vResidMat, int &exAchat,
		int &exVente) {
	int i, n, anRestant;
//float duree;
	int iVente = 100;
//int exAchat,exVente;
	float amor[50], vResid[51];
	float coef, taux, am1, ami, amorLi, pcent;
	ValComptable = 0;
	exAchat = CalculExercice(AAchat, MAchat, an_0, Mois_0);
	exVente = CalculExercice(AVente, MVente, an_0, Mois_0);
	if (exVente > 0) {
		iVente = exVente - exAchat;
	}
//    duree= (AVente-AAchat)*12 +(MVente-MAchat);

	memset(amor, 0, sizeof(float) * 50);
	memset(vResid, 0, sizeof(float) * 51);

	if (TypeAmor == CarDeg) {
		if (Duree < 5)
			coef = 1.5;
		else if (Duree < 7)
			coef = 2.;
		else
			coef = 2.5;
		taux = (1. / Duree) * coef;
		amorLi = ValAchat / Duree;
		// année 1
		i = 0;
		am1 = ValAchat * taux;
		am1 = am1 * (12 - (MAchat - Mois_0)) / 12.;
		amor[i] = am1;
		vResid[i] = ValAchat - amor[i];
		// annees suivantes
		i++;
		while (1) {
			ami = vResid[i - 1] * taux;
			if (ami < amorLi)
				break;
			if (i == iVente) {
				if (MVente >= Mois_0)
					pcent = (MVente - Mois_0) / 12.;
				else
					pcent = (MVente - Mois_0 + 12.) / 12.;
				ami = ami * pcent;
				amor[i] = ami;
				ValComptable = vResid[i - 1] - ami;
				vResid[i] = 0;
				goto FIN;
			}
			amor[i] = ami;
			vResid[i] = vResid[i - 1] - ami;
			i++;
		}
		// passage au linéaire
		anRestant = Duree - i;
		amorLi = vResid[i - 1] / anRestant;
		while (1) {
			if (amorLi < vResid[i - 1])
				ami = amorLi;
			else
				ami = vResid[i - 1];
			if (i == iVente) {
				if (MVente >= Mois_0)
					pcent = (MVente - Mois_0) / 12.;
				else
					pcent = (MVente - Mois_0 + 12.) / 12.;
				ami = ami * pcent;
				amor[i] = ami;
				ValComptable = vResid[i - 1] - ami;
				vResid[i] = 0;
				goto FIN;
			}
			amor[i] = ami;
			vResid[i] = vResid[i - 1] - amor[i];
			if (vResid[i] <= 0.)
				break;
			i++;
		}
	} else if (TypeAmor == CarLin) {
		amorLi = ValAchat / Duree;
		// année 1
		i = 0;
		am1 = amorLi * (12 - (MAchat - Mois_0)) / 12.;
		amor[i] = am1;
		vResid[i] = ValAchat - amor[i];
		// annees suivantes
		i++;
		while (1) {
			if (amorLi < vResid[i - 1])
				ami = amorLi;
			else
				ami = vResid[i - 1];
			if (i == iVente) {
				if (MVente >= Mois_0)
					pcent = (MVente - Mois_0) / 12.;
				else
					pcent = (MVente - Mois_0 + 12.) / 12.;
				ami = ami * pcent;
				amor[i] = ami;
				ValComptable = vResid[i - 1] - ami;
				vResid[i] = 0;
				goto FIN;
			}
			amor[i] = ami;
			vResid[i] = vResid[i - 1] - amor[i];
			if (vResid[i] <= 0.)
				break;
			i++;
		}
	} else if (TypeAmor == CarSans) {
		memset(amor, 0, sizeof(float) * 50);
		if (iVente != 100) {
			for (i = 0; i < iVente; i++)
				vResid[i] = ValAchat;
			ValComptable = ValAchat;
		} else
			for (i = 0; i < 50; i++)
				vResid[i] = ValAchat;
	}
	FIN: memset(vResidMat, 0, sizeof(float) * (N_X + 1));
	memset(amorMat, 0, sizeof(float) * N_X);
	if (exAchat == 0) {
		vResidMat[0] = 0;
		for (i = 0; i < Duree + 2; i++) {
			if (i >= N_X)
				break;
			amorMat[i] = amor[i];
			vResidMat[i + 1] = vResid[i];
		}
	} else if (exAchat > 0) {
		for (i = 0; i < Duree + 2; i++) {
			if (i + exAchat >= N_X)
				break; //250501
			amorMat[i + exAchat] = amor[i];
			vResidMat[i + 1 + exAchat] = vResid[i];
		}
	} else if (exAchat < 0) {
		n = -exAchat;
		vResidMat[0] = vResid[n - 1];
		for (i = 0; i < Duree + 2; i++) {
			if (i >= N_X)
				break;
			amorMat[i] = amor[i + n];
			vResidMat[i + 1] = vResid[i + n];
		}
	}
}
//-----------------------------------------------------------------------
void CL_Immo::Aff(int an_0) {

	int k, j;
	float amor[N_X], vResid[N_X + 1];
	int exAchat, exVente;
	float vecteur[5];

	Calcul(an_0, amor, vResid, exAchat, exVente);
	memset(vecteur, 0, sizeof(float) * 5);

	Forme01Frm->Show();
	Forme01Frm->IniGrilleEmprunt(T->L_Emp_Immo, Nom.c_str());

	vecteur[0] = an_0 - 1;
	vecteur[2] = vResid[0];
	Forme01Frm->EcrireLigne(vecteur);

	for (k = 0, j = an_0; k < N_X; k++, j++) {
		vecteur[0] = j;
		vecteur[1] = amor[k];
		vecteur[2] = vResid[k + 1];
		Forme01Frm->EcrireLigne(vecteur);
	}
}
/*
 ErreurFrm->Close();
 ErreurFrm->Caption="Echéancier";

 ErreurFrm->Close();
 ErreurFrm->Caption="Echéancier d'amortissement";
 ErreurFrm->Edit->Clear();
 sprintf(buf,"%s",Nom);
 ErreurFrm->Edit->Lines->Add(buf);
 sprintf(buf,"______________________________________");
 ErreurFrm->Edit->Lines->Add(buf);
 sprintf(buf,"         amor V Residuelle   ");
 ErreurFrm->Edit->Lines->Add(buf);
 sprintf(buf,"______________________________________");
 ErreurFrm->Edit->Lines->Add(buf);
 sprintf(buf," %4d %s %8.0f",an_0-1,blanc,vResid[0]);
 ErreurFrm->Edit->Lines->Add(buf);
 for(k=0,j=an_0; k<N_X; k++,j++)
 {
 sprintf(buf," %4d  %8.0f%8.0f",j
 , amor[k]
 , vResid[k+1] );
 ErreurFrm->Edit->Lines->Add(buf);
 }
 sprintf(buf,"______________________________________");
 ErreurFrm->Edit->Lines->Add(buf);
 if( AVente+MVente >0)
 {
 sprintf(buf,"Valeur comptable à la vente: %7.0f",ValComptable);
 ErreurFrm->Edit->Lines->Add(buf);
 }
 ErreurFrm->Show();
 }
 */
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void CL_EmpLT::RembConstantTreso(int an_0, float *recu, float *verse) {
	float verst, du, rembt, interest, taux, taux1, taux2;
	int deltaT, duree, duree1, duree2;
	bool flagChgtTaux = false;
	int m, mRemb, mV, mDernierVerst;
	int mInter, decal;

	int t;
	memset(recu, 0, sizeof(recu));
	memset(verse, 0, sizeof(verse));

	t = MoisTreso(an_0, AReal, MReal);
	if (t >= 0 && t < 120)
		recu[t] = Montant;

	//si plus d'un an entre real et rembt réduire duree emprunt
	mInter = (ARemb - AReal) * 12 + MRemb - MReal - 1;
	decal = mInter / 12;
	duree1 = Duree - decal;

	TauxDuree(taux1, taux2, duree1, duree2, duree, deltaT);

	//calcul annuités
	taux = taux1;
	verst = VerstConst(Montant, taux, duree);

	mRemb = (ARemb - AReal) * 12 + MRemb;
	mV = mRemb;
	while (mV > MReal + deltaT)
		mV -= deltaT;
	mDernierVerst = MReal;
	while (mV < mRemb) {
		interest = Montant * taux * (mV - mDernierVerst) / deltaT;
		t = MoisTreso(an_0, AReal, mV);
		if (t >= 0 && t < 120)
			verse[t] = interest;

		mDernierVerst = mV;
		mV += deltaT;
	}
	//PremiersVersements
	du = Montant;
	interest = Montant * taux * (mRemb - mDernierVerst) / deltaT;
	rembt = verst - Montant * taux;
	t = MoisTreso(an_0, AReal, mV);
	if (t >= 0 && t < 120)
		verse[t] = interest + rembt;
	du -= rembt;
	m = mRemb + deltaT;

	flagChgtTaux = false;
	while (1) {
		if (duree2 > 0 && flagChgtTaux == false
				&& m > MReal + duree1 * deltaT) {
			taux = taux2;
			verst = VerstConst(du, taux, duree2);
			flagChgtTaux = true;
		}
		interest = du * taux;
		rembt = verst - interest;
		if (rembt >= du) {
			rembt = du;
			t = MoisTreso(an_0, AReal, m);
			if (t >= 0 && t < 120)
				verse[t] = interest + rembt;
			du = 0;
			break;
		}
		t = MoisTreso(an_0, AReal, m);
		if (t >= 0 && t < 120)
			verse[t] = interest + rembt;
		du -= rembt;
		m += deltaT;
		if (t >= 120)
			break;
	}
//imp pour test
	/*
	 ofstream outfile("Emprunt.txt");
	 AnsiString date;
	 TDateTime time;
	 //char chaine[100];

	 time=TDateTime::CurrentDateTime();
	 date=time.DateTimeString();

	 outfile << date.c_str() <<endl;
	 for(t=0;t<120;t++)
	 {
	 if(verse[t])
	 outfile << t  << "  " << verse[t] << endl;

	 }
	 */
}
//-------------------------------------------------------------------------
void CL_EmpLT::RembVariableTreso(int an_0, float *recu, float *verse) {
	float verst, du, rembt, interest, taux1, taux2;
	int m, mRemb, deltaT, duree, duree1, duree2;

	int mV, mDernierVerst;
	int mInter, decal;

	int t;

	memset(recu, 0, sizeof(recu));
	memset(verse, 0, sizeof(verse));

	t = MoisTreso(an_0, AReal, MReal);
	if (t >= 0 && t < 120)
		recu[t] = Montant;

	//si plus d'un an entre real et rembt réduire duree emprunt
	mInter = (ARemb - AReal) * 12 + MRemb - MReal - 1;
	decal = mInter / 12;
	duree1 = Duree - decal;

	TauxDuree(taux1, taux2, duree1, duree2, duree, deltaT);

	mRemb = (ARemb - AReal) * 12 + MRemb;
	mV = mRemb;
	while (mV > MReal + deltaT)
		mV -= deltaT;

	mDernierVerst = MReal;
	while (mV < mRemb) {
		interest = Montant * taux1 * (mV - mDernierVerst) / deltaT;
		t = MoisTreso(an_0, AReal, mV);
		if (t >= 0 && t < 120)
			verse[t] = interest;

		mDernierVerst = mV;
		mV += deltaT;
	}
	m = mRemb;
	du = Montant;
	verst = Montant / duree;
	while (1) {
		interest = du * taux1;
		rembt = verst;
		if (rembt >= du) {
			rembt = du;
			du = 0;
			t = MoisTreso(an_0, AReal, mV);
			if (t >= 0 && t < 120)
				verse[t] = interest + rembt;
			break;
		}
		t = MoisTreso(an_0, AReal, mV);
		if (t >= 0 && t < 120)
			verse[t] = interest + rembt;
		if (t > 120)
			break;
		du -= rembt;
		m += deltaT;

	}
}
//-----------------------------------------------------------------------
void CL_EmpCT::CalculTreso(int an_0, float *recu, float *verse) {
	float duree;
	char type = Type[1];
	float interest;
//int n0,n1;

	int t;

	memset(recu, 0, sizeof(recu));
	memset(verse, 0, sizeof(verse));

	duree = (ARemb - AReal) * 12 + (MRemb - MReal);
	interest = Montant * Taux * (duree / 12.) / 100.;

	if (type == CarPreCompte) {
		t = MoisTreso(an_0, AReal, MReal);
		if (t >= 0 && t < 120)
			recu[t] = Montant - interest;

		t = MoisTreso(an_0, ARemb, MRemb);
		if (t >= 0 && t < 120)
			verse[t] = Montant;
	}
	if (type != CarPreCompte) {
		t = MoisTreso(an_0, AReal, MReal);
		if (t >= 0 && t < 120)
			recu[t] = Montant;
		t = MoisTreso(an_0, ARemb, MRemb);
		if (t >= 0 && t < 120)
			verse[t] = Montant + interest;
	}
}

//-----------------------------------------------------------------------
void CL_Sub::CalculTreso(int an_0, float *recu, float *verse) {
	int t;
	memset(recu, 0, sizeof(recu));

	t = MoisTreso(an_0, AReal, MReal);
	if (t >= 0 && t < 120)
		recu[t] = Montant;
}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void CL_Plact::CalculTreso(int an_0, float *recu, float *verse) {
	float duree;
	char type = Type;
	float cap, intAn;
	int n;
	int m, t;

	memset(recu, 0, sizeof(recu));
	memset(verse, 0, sizeof(verse));

	duree = (ATerme - AReal) * 12 + (MTerme - MReal);
	// à affecter au premier ou deuxieme exercice
	/*
	 if(MReal>mois_0)
	 pcent1=(float)(MReal -mois_0)/12.;
	 else
	 pcent1=(float)(mois_0- MReal)/12.;
	 pcent2=1-pcent1;
	 */

	t = MoisTreso(an_0, AReal, MReal);
	if (t >= 0 && t < 120)
		verse[t] = Montant;

	if (duree < 12) {
		t = MoisTreso(an_0, ATerme, MTerme);
		if (t >= 0 && t < 120) {
			intAn = Montant * Taux * (duree / 12.) / 100.;
			recu[t] = Montant + intAn;
		}
		return;
	}
	m = MReal;
	if (type == CarPlactFin) {
		cap = Montant;
		for (n = AReal + 1; n <= ATerme; n++) {
			m += 12;
			//if(n>=N_X) break;
			intAn = cap * Taux / 100;
			cap += intAn;
			if (n == ATerme) {
				t = MoisTreso(an_0, AReal, m);
				if (t >= 0 && t < 120)
					recu[t] = cap;
				break;
			}
		}
	} else if (type == CarPlactAn) {
		for (n = AReal + 1; n <= ATerme; n++) {
			m += 12;
			//if(n<0) continue;
			//if(n>=N_X) break;

			intAn = Montant * Taux / 100;
			t = MoisTreso(an_0, AReal, m);
			if (n == ATerme) {
				if (t >= 0 && t < 120)
					recu[t] = Montant + intAn;
				break;
			} else {
				if (t >= 0 && t < 120)
					recu[t] = intAn;
			}
			if (t > 120)
				break;
		}
	}
}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
void CL_Immo::CalculTreso(int an_0, int &mVente, float &valVente,
		float &tvaRecu, int &mAchat, float &valAchat, float &tvaVerse)

		{
//131205
	valVente = 0.;
	tvaRecu = 0.;
	valAchat = 0.;
	tvaVerse = 0.;

	mAchat = MoisTreso(an_0, AAchat, MAchat);
	if (mAchat >= 0 && mAchat < 120) {
		valAchat = ValAchat;
		tvaVerse = ValAchat * Tva->Taux / 100.;
	}
	if (ValVente == 0)
		return;

	mVente = MoisTreso(an_0, AVente, MVente);
	if (mVente >= 0 && mVente < 120)
		valVente = ValVente;

}
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// passer de an mois   an année et m n°du mois avec mois =1 pour janvier de an
// à t avec t=0 pour An_0  Janvier
//-----------------------------------------------------------------------
int MoisTreso(int an_0, int an, int mois) {
	int t;
	t = (an - an_0) * 12 + mois - 1;
	return t;
}
/*
 L_Emp_Lt=       "lt";  //Long Terme
 L_Emp_Total=    "Total";
 L_Emp_Ct=       "ct";
 L_Emp_Sub=      "sub" //Subvention
 L_Emp_Plact=    "plact";//Placement
 L_Emp_Immo=     "immo";
 */

