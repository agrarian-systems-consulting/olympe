//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"

#include "CL_SousPeriode.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
CL_SousPeriode::CL_SousPeriode(int borneD, int borneF,
		CL_Calendrier *calendrier) {
	int n;
	n = calendrier->V_Periode->Nbelt;
	JD = borneD;
	JF = borneF;
	LesPeriodes = new CL_Periode*[n];
	LesPcent = new float[n];
	for (int i = 0; i < n; i++)
		LesPeriodes[i] = NULL;
	NPeriode = 0;
}
CL_SousPeriode::~CL_SousPeriode() {
	delete[] LesPeriodes;
	delete[] LesPcent;
}

