//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>

#pragma hdrstop

#include "CL_Matrice.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
CL_Matrice::CL_Matrice(int i, int j) {
	iX = i;
	jX = j;
	X = new float[iX * jX];
	for (i = 0; i < iX * jX; i++)
		X[i] = 0;
	/*
	 X=new float*[iX];
	 for(i=0;i<iX;i++)
	 X[i]=new float[jX];
	 for(i=0;i<iX;i++)
	 for(j=0;j<jX;j++)
	 X[i][j]=0;
	 */
}
//---------------------------------------------------------------------------
CL_Matrice::CL_Matrice(CL_Matrice *origine) {
	int i;
	iX = origine->iX;
	jX = origine->jX;
	X = new float[iX * jX];
	for (i = 0; i < iX * jX; i++)
		X[i] = origine->X[i];
	/*
	 X=new float*[jX];
	 for(j=0;j<jX;j++)
	 X[j]=new float[iX];
	 for(i=0;i<iX;i++)
	 for(j=0;j<jX;j++)
	 X[i][j]=origine->X[i][j];
	 */
}
//---------------------------------------------------------------------------
CL_Matrice::~CL_Matrice() {
//int i,j;
//    for(i=0;i<iX;i++)
//        delete [] X[i];

	iX = 0;
	jX = 0;
	delete[] X;

}
//---------------------------------------------------------------------------
void CL_Matrice::ecrireFichier(FILE *fichier) {
	int i, j, k;
	fwrite(&iX, sizeof(int), 1, fichier);
	fwrite(&jX, sizeof(int), 1, fichier);
	/*
	 for(i=0;i<iX*jX;i++)                        //201204
	 {
	 fwrite(&X[i],sizeof(float),1,fichier);
	 }
	 */
	for (i = 0; i < iX; i++) {
		for (j = 0; j < jX; j++) {
			k = i + j * iX;
			fwrite(&X[k], sizeof(float), 1, fichier);
		}
	}
}
//---------------------------------------------------------------------------
void CL_Matrice::lireFichier(FILE *fichier) {
	float *m;
	int i, j, k;
	int n;
	float x; //050908
	fread(&iX, sizeof(int), 1, fichier);
	fread(&jX, sizeof(int), 1, fichier);
	X = new float[iX * jX];
	//a remettre c'est bon
	for (i = 0; i < iX; i++) {
		for (j = 0; j < jX; j++) {
			k = i + j * iX;
			fread(&X[k], sizeof(float), 1, fichier);
//            fread(&x,sizeof(float),1,fichier);
		}
	}
	/*
	 //pour corriger des fichiers mal ecrits
	 m=new float[iX*jX];
	 for(i=0;i<iX*jX;i++)                        //201204
	 {
	 fread(&m[i],sizeof(float),1,fichier);
	 }
	 n=0;                   // trouver comment passer de m à X
	 for(j=0;j<jX;j++)
	 {
	 for(i=0;i<iX;i++)
	 {
	 X[n]=m[j+i*jX];
	 n++;
	 }
	 }
	 delete []m;
	 */
	/*------------------------------ essai
	 float val;
	 int n,m;
	 //
	 n=0;
	 for(i=0;i<iX;i++)
	 {
	 for(j=0;j<jX;j++)
	 {
	 k=j+i*jX;//i+j*iX;

	 val=i+j*100;
	 this->vaut(i,j,val);  //c'est bon
	 m[n]=val;
	 n++;
	 }
	 }
	 n=0;                   // trouver comment passer de m à X
	 for(i=0;i<iX;i++)
	 {
	 for(j=0;j<jX;j++)
	 {
	 X[n]=-1;
	 n++;
	 }
	 }
	 n=0;                   // trouver comment passer de m à X
	 for(j=0;j<jX;j++)
	 {
	 for(i=0;i<iX;i++)
	 {
	 X[n]=m[j+i*jX];
	 n++;
	 }
	 }
	 ---------fin essai------------*/

}
//---------------------------------------------------------------------------
float CL_Matrice::val(int i, int j) {
	int k;
	k = i + j * iX;
	return X[k];
}
//---------------------------------------------------------------------------
void CL_Matrice::vaut(int i, int j, float val) {
	int k;
	/*
	 if(X==NULL)
	 ShowMessage("X==NULL");
	 */
	k = i + j * iX;
	X[k] = val;
	;
}
//---------------------------------------------------------------------------
bool CL_Matrice::EstVide(void) {
	int i, j, k;
	for (i = 0; i < iX; i++) {
		for (j = 0; j < jX; j++) {
			k = i + j * iX;
			if (X[k] != 0)
				return false;
		}
	}
	return true;
}
/*
 template <typename T>
 Matrice<T>::Matrice(int i,int j)
 {
 iX=i;
 jX=j;
 X=new T*[jX];
 for(j=0;j<jX;j++)
 X[j]=new T[iX];
 }
 template <class T>Matrice<T>::~Matrice()
 {
 int i,j;
 for(j=0;j<jX;j++)
 delete [] X[j];
 delete []X;
 }
 */

/*
 Matrice<int> *matent;
 matent= new Matrice<int> (3,5);
 */

