//---------------------------------------------------------------------------

#ifndef LesStocksH
#define LesStocksH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Assol.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TLesStocksFrm: public TAssolFrm {
	__published: // Composants gérés par l'EDI
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations de l'utilisateur
	virtual void __fastcall VersGrille(TStringGrid *grille);bool __fastcall ilYAStock(CL_QuanVal *quanval);

public:
	// Déclarations de l'utilisateur
	CL_Agriculteur *Agri;
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LesStocksFrm;
	__fastcall TLesStocksFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLesStocksFrm *LesStocksFrm;
//---------------------------------------------------------------------------
#endif
