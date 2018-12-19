//---------------------------------------------------------------------------
#include <values.h>

#ifndef CL_TresoMensH
#define CL_TresoMensH
#include "Olympedec.h"
#include "LesClassesApp.h"

//---------------------------------------------------------------------------
class CL_TresoMens {
public:
	CL_TresoMens();
	CL_TresoMens(CL_QuanVal *quanVal, int type, char *famille, int proOUcha);
	CL_TresoMens(char *titre, float valVente, int mVente, float valAchat,
			int mAchat, int proOUcha, int contient);
	CL_TresoMens(char *famille, float *recu, float *verse, int proOUcha,
			int contient); //total

	CL_TresoMens(char *titre, float *total, int proOUcha, int contient,
			bool avecListe = true); //total

	CL_TresoMens(char *titre, int proOUcha, int contient);
	~CL_TresoMens();
	int Contient;
	char AAfficher;
	CL_QuanVal *QuanVal;
	int QouV;
	char *Nom;
	char *Famille;
	int ProOuCha; //PRODUIT CHARGE SOLDE
	TList *LstMoisVal; //ou LstMoisVal ou Valeur;
	float *Valeur;
	void Calcul(float *ValTva);
	void AdditioneDans(float *total);
	void EtablitFlux(float *flux);
	void TrouveMinMax(float &vMin, float &vMax, int mMin, int mMax);
	void AffGrilleValeur(TStringGrid *SG, int r, int digits = 0);
	void AffGrilleQuantite(TStringGrid *SG, int r, int digits = 0);

private:
	bool repartExiste;
	void Maz(void);
};
#endif
