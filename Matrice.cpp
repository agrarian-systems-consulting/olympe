//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Matrice.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
template<typename T>
Matrice<T>::Matrice(int i, int j) {
	iX = i;
	jX = j;
	X = new T*[jX];
	for (j = 0; j < jX; j++)
		X[j] = new T[iX];
}
template<class T> Matrice<T>::~Matrice() {
	int i, j;
	for (j = 0; j < jX; j++)
		delete[] X[j];
	delete[] X;
}

/*
 Matrice<int> *matent;
 matent= new Matrice<int> (3,5);
 */

