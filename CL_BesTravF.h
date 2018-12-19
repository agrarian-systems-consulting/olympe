//---------------------------------------------------------------------------

#ifndef CL_BesTravFH
#define CL_BesTravFH
//---------------------------------------------------------------------------
class CL_BesTrav {
public:
	CL_BesTrav(int nbAnnee, CL_Calendrier *calendrier);
	int NoCal;
	int NbAnnee;
	int NbPeriodeCal; //pour verif eventuelle
	int iX, jX;
	CL_Matrice* Besoins;
};

#endif
