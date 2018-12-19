//---------------------------------------------------------------------------

#pragma hdrstop

#include "CL_Passe.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CL_Passe::CL_Passe(int *arg) {
	noFam = arg[0];
	noCat = arg[1];
	noItem = arg[2];
	memset(Valeur, 0, sizeof(Valeur));
}
//---------------------------------------------------------------------------
CL_Passe::CL_Passe(CL_Passe *source) {
	noFam = source->noFam;
	noCat = source->noCat;
	noItem = source->noItem;
	memcpy(Valeur, source->Valeur, sizeof(Valeur));
}

