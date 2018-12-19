//---------------------------------------------------------------------------

#ifndef Cl_OcccTresoH
#define Cl_OcccTresoH

#include "Olympedec.h"
#include "LesClassesApp.h"

//---------------------------------------------------------------------------
class CL_OcccTreso {
public:
	CL_OcccTreso();
	float Max[2][N_X];
	float Taux[2][N_X];
	float Plact[N_X];
	float TauxPlact[N_X];

	void Maz(void);
	void EcrireFichier(FILE *fichier);
	void LireFichier(FILE *fichier);

private:
};
#endif
