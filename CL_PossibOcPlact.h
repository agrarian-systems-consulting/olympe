//---------------------------------------------------------------------------

#ifndef Cl_PossibOcPlactH
#define Cl_PossibOcPlactH

#include "Olympedec.h"
#include "LesClassesApp.h"

//---------------------------------------------------------------------------
class CL_PossibOcPlact {
public:
	CL_PossibOcPlact();
	CL_PossibOcPlact(CL_PossibOcPlact *source);
	float Max[2][N_X];
	float Taux[2][N_X];
	float PlactMax[N_X];
	float PlactTaux[N_X];

	void Maz(void);
	void EcrireFichier(FILE *fichier);
	void LireFichier(FILE *fichier);

private:
};
#endif
