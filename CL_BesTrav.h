//---------------------------------------------------------------------------

#ifndef CL_BesTravH
#define CL_BesTravH
class CL_Calendrier;
class CL_Matrice;
//---------------------------------------------------------------------------

class CL_BesTrav {
public:
	CL_BesTrav();
	CL_BesTrav(int nbPhase, CL_Calendrier *calendrier);
	CL_BesTrav(CL_BesTrav *origine);
	~CL_BesTrav();
	int No; //c'est n° du calendrier permet de trouver rapidt dans Atelier->V_BesTrav
//    int NoCal;
	int NbPhase;
	int NbPeriodeCal; //pour verif eventuelle
	CL_Calendrier *Calendrier;
//    int iX,jX;
	CL_Matrice* Besoins;
//    void Totalise(float &TotHeure,float *TotHeureAn,CL_Espece *espece);
	void Totalise(float &TotHeure, float *TotHeureAn);
	void CopieValeur(CL_BesTrav *Bes0);
	//palliatif
	bool trouveCalendrier(int NbPeriodeCal);
	void lireFichier(FILE *fichier);
	void ecrireFichier(FILE *fichier);

	void lireGrille(TStringGrid *grille);
	void ecrireGrille(TStringGrid *grille);
};

#endif
