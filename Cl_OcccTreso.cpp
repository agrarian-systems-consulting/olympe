//---------------------------------------------------------------------------

#pragma hdrstop

#include "Cl_OcccTreso.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CL_OcccTreso::CL_OcccTreso() {
}
void CL_OcccTreso::Maz(void) {
	memset(Max, 0, sizeof(Max));
	memset(Taux, 0, sizeof(Taux));
	memset(Plact, 0, sizeof(Plact));
	memset(TauxPlact, 0, sizeof(Plact));
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CL_OcccTreso::EcrireFichier(FILE *fichier) {
	int n, i;
	for (n = 0; n < 2; n++) {
		for (i = 0; i < N_X; i++) {
			fwrite(&Max[n][i], sizeof(int), 1, fichier);
			fwrite(&Taux[n][i], sizeof(int), 1, fichier);
		}
	}

}
//---------------------------------------------------------------------------
void CL_OcccTreso::LireFichier(FILE *fichier) {
	int n, i;
}

//-----------------------------------------------------------

