//---------------------------------------------------------------------------

#ifndef TVVarianteEnsH
#define TVVarianteEnsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVVarianteAgri.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVVarianteEnsFrm: public TTVVarianteAgriFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall TVDblClick(TObject *Sender);void __fastcall TVClick(TObject *Sender);
private:
	// Déclarations utilisateur
public:
	// Déclarations utilisateur
	CL_Ensemble *Ensemble;
	__fastcall TTVVarianteEnsFrm(TComponent* Owner);void __fastcall trouveRow(CL_Ensemble *ens);
	//???

};
//---------------------------------------------------------------------------
extern PACKAGE TTVVarianteEnsFrm *TVVarianteEnsFrm;
//---------------------------------------------------------------------------
#endif
