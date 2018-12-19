//---------------------------------------------------------------------------

#ifndef AtelH
#define AtelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAtelFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TPageControl	*PC;
	TTabSheet *TSProduit;
	TTabSheet *TSCharge;
	TTabSheet *TSVolume;
	TTabSheet *TSExternalite;
	TStringGrid *SGProduit;
	TStringGrid *SGCharge;
	TStringGrid *SGVolume;
	TStringGrid *SGExternalite;
	TLabel *LabAtelier;
	TEdit *EdAtelier;
	TLabel *LabUtilise;
	TBitBtn *BtBnMarge;
	TBitBtn *BtBnReportDroit;
	TBitBtn *BtBnSupprimer;
	TBitBtn *BtBnProduit;
	TListBox *LBProduction;
	void __fastcall PCChange(TObject *Sender);

private: // Déclarations utilisateur
public:// Déclarations utilisateur
	void __fastcall Demarrer(void);
	void __fastcall AffAtelier(void);
	void __fastcall VerifPage(void);

	__fastcall TAtelFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAtelFrm *AtelFrm;
//---------------------------------------------------------------------------
#endif
