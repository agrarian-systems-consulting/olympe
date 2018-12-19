//---------------------------------------------------------------------------
#ifndef ResAtelierH
#define ResAtelierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TResAtelierFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall BtBnStockerClick(TObject *Sender);void __fastcall BtBnImpClick(TObject *Sender);

private:
	// Déclarations de l'utilisateur
//	void  __fastcall BoutEditClick(TObject *Sender);
	void __fastcall ImpResAtelier(char *titre,CL_Vecteur<CL_Item> *vecteur);

public:
	// Déclarations de l'utilisateur
	__fastcall TResAtelierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResAtelierFrm *ResAtelierFrm;
//---------------------------------------------------------------------------
#endif
