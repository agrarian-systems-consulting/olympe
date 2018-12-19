//---------------------------------------------------------------------------

#ifndef AgriDefSerieH
#define AgriDefSerieH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TAgriDefSerieFrm: public TForm {
	__published: // Composants gérés par l'EDI
private:// Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	void DefSerie(CL_Agriculteur *agriDepart,int nbAnSim);
	void DefSeriePlus(CL_Agriculteur *agri, int nbAnSim);
	void DefSerieMoins(CL_Agriculteur *agri, int nbAnSim);
	void CopieCulture(CL_Agriculteur *agriBis, CL_Agriculteur *agriDepart); //culture animaux Bestiaux

	void DefAgriApres(CL_Agriculteur *agriPrec, ST_NoAgri *noAgri);

	__fastcall TAgriDefSerieFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAgriDefSerieFrm *AgriDefSerieFrm;
//---------------------------------------------------------------------------
#endif
