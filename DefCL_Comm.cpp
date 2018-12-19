//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"

#include "DefCL_Comm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CL_Comm::CL_Comm(int noItem) {
	NoItem = noItem;
	memset(Production, 0, sizeof(Production));
	memset(QVente, 0, sizeof(QVente));
	memset(VVente, 0, sizeof(VVente));
	memset(PrixRevient, 0, sizeof(PrixRevient));
	memset(Stock, 0, sizeof(Stock));
}
//---------------------------------------------------------------------------
void CL_Comm::InsereProdAvant(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++)
		Production[i] = quantite[i];
}

//---------------------------------------------------------------------------
void CL_Comm::InsereProdApres(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++)
		Production[i + N_X] = quantite[i];
}
//---------------------------------------------------------------------------
void CL_Comm::InserePrixRevientAvant(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++)
		PrixRevient[i] = quantite[i];
}

//---------------------------------------------------------------------------
void CL_Comm::InserePrixRevientApres(float *quantite) {
	int i;
	for (i = 0; i < N_X; i++)
		PrixRevient[i + N_X] = quantite[i];
}
//---------------------------------------------------------------------------
void CL_Comm::CalculStock(void) {
	int i;
	Stock[0] = Production[0];
	for (i = 1; i < N_X; i++)
		Stock[i] = Stock[0] + Production[i];
	for (i = 0; i < N_X; i++)
		Stock[i + N_X] = Stock[i - 1 + N_X] + Production[i] - QVente[i];

}

