#include <vcl.h>
#include <stdio.h>
#include <Grids.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"

//---------------------------------------------------------------------------

#ifndef CL_RepartH
#define CL_RepartH
//---------------------------------------------------------------------------
class CL_Repart {
public:
	CL_Repart();
	CL_Repart(CL_Repart *source);
	AnsiString Nom;
	int No;
	int NoCategorie;
	CL_Categorie *Categorie;
	bool Supprimable;
	int Cmp(CL_Repart *source);

	float Pcent[36];
	float Total(void);
	void FichierEcrire(void);
	void FichierLire(void);
	void GrilleEcrire(TStringGrid* sg, float valTot);
	void GrilleLire(TStringGrid* SG);
	float LireCell(TStringGrid* SG, int col, int row);
	// il faut creer une classe ES cf Mangalere
	AnsiString Aff(float x);
	AnsiString Aff(float x, int digits);
	//CL_Outil
	float as2float(AnsiString as);
};
#endif
