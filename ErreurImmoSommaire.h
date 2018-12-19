//---------------------------------------------------------------------------

#ifndef ErreurImmoSommaireH
#define ErreurImmoSommaireH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdarg.h>
#include <Buttons.hpp>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "AgriSaisie.h"

//---------------------------------------------------------------------------
class TErreurImmoSommaireFrm: public TForm {
	__published: // Composants gérés par l'EDI
TGroupBox	*GB;
	TRichEdit *RE;
	TRadioGroup *RG;
	TBitBtn *BtBnCalculer;
	void __fastcall BtBnCalculerClick(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	float Resid[N_X+1];
	float Amor[N_X+1];
	float Achat[N_X+1];
	float Revente[N_X+1];
	float ProdImmo[N_X+1];
	TStringGrid *LaGrille;

	void TexteCaption(void);
	void IniCaption(void);
	void TexteChaine(void);

	AnsiString LC_RG;
	AnsiString LC_ErreurFrm;
	AnsiString LC_ErreurImmoSommaireFrm;

	AnsiString L_LaFormule;
	AnsiString L_ValResid;
	AnsiString L_ValResidN;
	AnsiString L_Amor;
	AnsiString L_Achat;
	AnsiString L_Revente;
	AnsiString L_ProdImmo;
	AnsiString L_NonVerif;

	AnsiString L_ValResiduelles;
	AnsiString L_Amors;
	AnsiString L_NeRienFaire;

	__fastcall TErreurImmoSommaireFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TErreurImmoSommaireFrm *ErreurImmoSommaireFrm;
//---------------------------------------------------------------------------
#endif
