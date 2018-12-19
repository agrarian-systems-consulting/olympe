//---------------------------------------------------------------------------

#ifndef CL_BesTravAtelierH
#define CL_BesTravAtelierH
#include "Olympedec.h"
#include "LesClassesApp.h"

//---------------------------------------------------------------------------

class CL_BesTravAtelier {
public:
	CL_BesTravAtelier(CL_Atelier *atelier, int nbSousPeriode);
	~CL_BesTravAtelier();
	CL_Atelier *Atelier;
	float *besSousPeriode; //besoin par sous periode
};
#endif
