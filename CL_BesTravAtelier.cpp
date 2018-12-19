//---------------------------------------------------------------------------

#pragma hdrstop

#include "CL_BesTravAtelier.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
CL_BesTravAtelier::CL_BesTravAtelier(CL_Atelier *atelier, int nbSousPeriode) {
	Atelier = atelier;
	besSousPeriode = new float[nbSousPeriode];
	memset(besSousPeriode, 0, sizeof(float) * nbSousPeriode);

}
CL_BesTravAtelier::~CL_BesTravAtelier() {
	delete[] besSousPeriode;
}

