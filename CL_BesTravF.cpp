//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>

#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"

#include "CL_Matrice.h"

#include "CL_BesTravF.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
class CL_BesTrav::CL_BesTrav(int nbAnnee,CL_Calendrier *calendrier)
{
	NbAnnee=nbAnnee;
	NoCal=calendrier->No;
	NbPeriodeCal=calendrier->V_Periode->NbElt; //pour verif eventuelle
	Besoins=new CL_Matrice(NbPeriodeCal,NbAnnee);
}

