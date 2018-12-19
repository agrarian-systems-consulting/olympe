//---------------------------------------------------------------------------

#ifndef TVRdtChoixH
#define TVRdtChoixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVPrixChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVRdtChoixFrm: public TTVPrixChoixFrm {
	__published: // Composants g�r�s par l'EDI
	void __fastcall TVDblClick(TObject *Sender);
private:
	// D�clarations utilisateur
	CL_Vecteur<CL_Delta> *V_Delta;

	CL_Delta* __fastcall deltaExiste(CL_Atelier *atelier,CL_Item *item);bool __fastcall insereDelta(CL_Item *item,CL_Vecteur<CL_Atelier> *v_Atelier,int nature);void __fastcall TTVRdtChoixFrm::classeDelta(void);void __fastcall classeDelta(int nature);void __fastcall classeDelta2(CL_Vecteur<CL_Atelier> *v_Atelier,
			CL_Item *item,TList *listDelta);

	float trouveRdtCulture(CL_ItemParAtelier *itemParAtelier, int nbPhase);
	float trouveRdtPerenne(CL_ItemParAtelier *itemParAtelier, int nbPhase);

public:
	// D�clarations utilisateur
	__fastcall TTVRdtChoixFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVRdtChoixFrm *TVRdtChoixFrm;
//---------------------------------------------------------------------------
#endif
