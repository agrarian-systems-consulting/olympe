//---------------------------------------------------------------------------
#ifndef AtelierMargeH
#define AtelierMargeH
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
class TAtelierMargeFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall BtBnStockerClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
//    void __fastcall BtBnImpClick(TObject *Sender);

private:
	// Déclarations de l'utilisateur
//	void  __fastcall BoutEditClick(TObject *Sender);
	void __fastcall ImpResAtelier(char *titre,CL_Vecteur<CL_Item> *vecteur);

//    AnsiString L_Marge;
	AnsiString L_Moy;
//    AnsiString L_Tot;
//    AnsiString L_Prod;
//    AnsiString L_Charge;
	AnsiString L_ChVol;
	AnsiString L_MargeCum;
//    AnsiString L_MargeHeure;

public:
	// Déclarations de l'utilisateur
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtBnMarge;

	__fastcall TAtelierMargeFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAtelierMargeFrm *AtelierMargeFrm;
//---------------------------------------------------------------------------
#endif
