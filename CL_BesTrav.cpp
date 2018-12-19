//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>

#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "CL_Matrice.h"

#include "CL_BesTrav.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
CL_BesTrav::CL_BesTrav() {
	NbPhase = -1;
	No = -1;
//    NoCal=calendrier->No;
	Calendrier = NULL;
	NbPeriodeCal = -1;
	Besoins = NULL;
}
//---------------------------------------------------------------------------
CL_BesTrav::CL_BesTrav(int nbPhase, CL_Calendrier *calendrier) {
	NbPhase = nbPhase;
	No = calendrier->No;
//    NoCal=calendrier->No;
	Calendrier = calendrier;
	NbPeriodeCal = Calendrier->V_Periode->Nbelt; //pour verif eventuelle
	Besoins = new CL_Matrice(NbPeriodeCal, NbPhase);
}
// const par copie
//---------------------------------------------------------------------------
CL_BesTrav::CL_BesTrav(CL_BesTrav* origine) {
	NbPhase = origine->NbPhase;
	No = origine->No; //n° du Calendrier
//    NoCal=calendrier->No;
	Calendrier = origine->Calendrier;
	NbPeriodeCal = Calendrier->V_Periode->Nbelt; //pour verif eventuelle
	Besoins = new CL_Matrice(origine->Besoins);
}
//---------------------------------------------------------------------------
CL_BesTrav::~CL_BesTrav() {
	delete Besoins;
}

//---------------------------------------------------------------------------
void CL_BesTrav::CopieValeur(CL_BesTrav *Bes0) {
	int i, j;
	int ix, jx;
	float val;
	ix = Bes0->Besoins->iX;
	jx = Bes0->Besoins->jX;
	for (i = 0; i < ix; i++)
		for (j = 0; j < jx; j++) {
			val = Bes0->Besoins->val(i, j);
			Besoins->vaut(i, j, val);
		}

}
//---------------------------------------------------------------------------
//void CL_BesTrav::Totalise(float &TotHeure,float *TotHeureAn,CL_Espece *espece)
void CL_BesTrav::Totalise(float &TotHeure, float *TotHeureAn) {
	int i, j;
	TotHeure = 0; //180105
	for (j = 0; j < Besoins->jX; j++)
		TotHeureAn[j] = 0;

	for (j = 0; j < Besoins->jX; j++) {
		for (i = 0; i < Besoins->iX; i++) {
			TotHeureAn[j] += Besoins->val(i, j);
			TotHeure += Besoins->val(i, j);
		}
	}
}
//---------------------------------------------------------------------------
void CL_BesTrav::ecrireFichier(FILE *fichier) {
	fwrite(&NbPhase, sizeof(int), 1, fichier);
	fwrite(&No, sizeof(int), 1, fichier);
	fwrite(&NbPeriodeCal, sizeof(int), 1, fichier);
	Besoins->ecrireFichier(fichier);

}
//---------------------------------------------------------------------------
void CL_BesTrav::lireFichier(FILE *fichier) {
	fread(&NbPhase, sizeof(int), 1, fichier);
	fread(&No, sizeof(int), 1, fichier);
	fread(&NbPeriodeCal, sizeof(int), 1, fichier);
	//idiot V_calndrier est lu aprés
	// LesAdresses fait le travail
	//Calendrier=V_Calendrier->trouve(No);
	// palliatif à erreur btpl 240204
	Besoins = new CL_Matrice(NbPeriodeCal, NbPhase);

	Besoins->lireFichier(fichier);

}
// rustine en principe inutile
//---------------------------------------------------------------------------
bool CL_BesTrav::trouveCalendrier(int NbPeriodeCal) {
	int i;
	CL_Calendrier *cal;
	for (i = 0; i < V_Calendrier->Nbelt; i++) {
		cal = V_Calendrier->Vecteur[i];
		if (cal->V_Periode->Nbelt == NbPeriodeCal) {
			Calendrier = cal;
			No = Calendrier->No;
			return true;
		}
	}
	//rustine;
	return false;
}
//---------------------------------------------------------------------------
void CL_BesTrav::lireGrille(TStringGrid *grille) {
	AnsiString s;
	float val;
	int i, j;
	int n, c;
	char car;
	char chaine[50];
	for (i = 0; i < Besoins->iX; i++)
		for (j = 0; j < Besoins->jX; j++) {
			// attention matrice ligne colonne
			//           grille colonne ligne

			s = grille->Cells[j + 1][i + 1];
			s = s.Trim();
			if (s == NULL || s == "" || s == "." || s == "-")
				val = 0.;
			else { //250206
				for (c = 0, n = 1; n < s.Length() + 1; n++) {
					car = s[n];
					if (car >= '0' && car <= '9')
						chaine[c++] = car;
					else if (car == '.' || car == ',')
						chaine[c++] = '.';
				}
				chaine[c] = 0;
				s = AnsiString(chaine);
				val = s.ToDouble();
			}
			Besoins->vaut(i, j, val);
//            Besoins->X[i][j]=val;
		}
}
//---------------------------------------------------------------------------
void CL_BesTrav::ecrireGrille(TStringGrid *grille) {
	AnsiString s;
	float val, total;
	int digits = 2;
	int a, p, c, r, rTot;
	/*
	 for(int i=0;i<Besoins->iX;i++)      //periodes
	 for(int j=0;j<Besoins->jX;j++)  //annees
	 {
	 // attention matrice ligne colonne
	 //           grille colonne ligne
	 val=Besoins->val(i,j);//X[i][j];
	 if(val==0)continue;

	 s=FloatToStrF((double)val,ffNumber,7,digits);

	 grille->Cells[j+1][i+1]=s;
	 }
	 */
	rTot = Besoins->iX + 1;
	for (a = 0; a < Besoins->jX; a++) //annees
			{
		total = 0;
		for (p = 0; p < Besoins->iX; p++) //periodes
				{
			// attention matrice ligne colonne
			//           grille colonne ligne
			val = Besoins->val(p, a); //X[i][j];
			if (val == 0)
				continue;

			total += val;
			s = FloatToStrF((double) val, ffNumber, 7, digits);
			c = a + 1;
			r = p + 1;
			grille->Cells[c][r] = s;
		}
		if (total == 0)
			continue;

		s = FloatToStrF((double) total, ffNumber, 7, digits);
		grille->Cells[c][rTot] = s;
	}
	grille->Cells[0][rTot] = "   Total Annuel";
}

