//---------------------------------------------------------------------------

#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"

#include "CL_PossibOcPlact.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CL_PossibOcPlact::CL_PossibOcPlact() {
	Maz();
}
//---------------------------------------------------------------------------
CL_PossibOcPlact::CL_PossibOcPlact(CL_PossibOcPlact *source) {
	memcpy(Max, source->Max, sizeof(Max));
	memcpy(Taux, source->Taux, sizeof(Taux));
	memcpy(PlactMax, source->PlactMax, sizeof(PlactMax));
	memcpy(PlactTaux, source->PlactTaux, sizeof(PlactTaux));
}
//------------------------------------------------------------------------------
void CL_PossibOcPlact::Maz(void) {
	memset(Max, 0, sizeof(Max));
	memset(Taux, 0, sizeof(Taux));
	memset(PlactMax, 0, sizeof(PlactMax));
	memset(PlactTaux, 0, sizeof(PlactTaux));
}
//------------------------------------------------------------------------------
//---------------------------------------------------------------------------
void CL_PossibOcPlact::EcrireFichier(FILE *fichier) {
	int n, i;
	for (n = 0; n < 2; n++) {
		for (i = 0; i < N_X; i++) {
			fwrite(&Max[n][i], sizeof(int), 1, fichier);
			fwrite(&Taux[n][i], sizeof(int), 1, fichier);
		}
	}
	for (i = 0; i < N_X; i++) {
		fwrite(&PlactMax[i], sizeof(int), 1, fichier);
		fwrite(&PlactTaux[i], sizeof(int), 1, fichier);
	}
}
//---------------------------------------------------------------------------
void CL_PossibOcPlact::LireFichier(FILE *fichier) {
	int n, i;
	for (n = 0; n < 2; n++) {
		for (i = 0; i < N_X; i++) {
			fread(&Max[n][i], sizeof(int), 1, fichier);
			fread(&Taux[n][i], sizeof(int), 1, fichier);
		}
	}
	for (i = 0; i < N_X; i++) {
		fread(&PlactMax[i], sizeof(int), 1, fichier);
		fread(&PlactTaux[i], sizeof(int), 1, fichier);
	}
}
//-----------------------------------------------------------

