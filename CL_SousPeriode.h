//---------------------------------------------------------------------------

#ifndef CL_SousPeriodeH
#define CL_SousPeriodeH
//---------------------------------------------------------------------------
class CL_SousPeriode {
public:
	CL_SousPeriode(int borneD, int borneF, CL_Calendrier *calendrier);
	~CL_SousPeriode();
	int JD, JF; //exprimé par rapport au J0 de BorneDebut
	int JDeb, MDeb; //les dates du calendrier
	int JFin, MFin;
	int xG, xD; // coordonnees dans l'ecran
	CL_Periode** LesPeriodes;
	float* LesPcent;
	int NPeriode;
};
#endif
