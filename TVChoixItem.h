//---------------------------------------------------------------------------
#ifndef TVChoixItemH
#define TVChoixItemH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TVChoix.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVChoixItemFrm: public TTVChoixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
	//ne pas modifier sans regarder Atelier.h TVChoixItem.h
	enum {
		GProduit, GCharge, GChProp, GExter
	};

	void __fastcall CompleteGrille(CL_Item *item,CL_Categorie *categorie,
			CL_SystemeUnite *sysUnit );
public:
	// Déclarations de l'utilisateur
	__fastcall TTVChoixItemFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixItemFrm *TVChoixItemFrm;
//---------------------------------------------------------------------------
#endif
