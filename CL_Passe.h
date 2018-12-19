//---------------------------------------------------------------------------

#ifndef CL_PasseH
#define CL_PasseH
#include <vcl.h>

//---------------------------------------------------------------------------
class CL_Passe {
public:
	CL_Passe(int *arg);
	CL_Passe(CL_Passe *source);
	int noFam;
	int noCat;
	int noItem;
	float Valeur[5];
};
#endif
