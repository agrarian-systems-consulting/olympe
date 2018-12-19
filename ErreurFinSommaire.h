//---------------------------------------------------------------------------

#ifndef ErreurFinSommaireH
#define ErreurFinSommaireH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ErreurImmoSommaire.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TErreurFinSommaireFrm: public TErreurImmoSommaireFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall BtBnCalculerClick(TObject *Sender);
private:
	// Déclarations de l'utilisateur
public:
	// Déclarations de l'utilisateur
	float detteLT[N_X + 1];
	float rembLT[N_X];
	float nouvLT[N_X];

	float detteCT[N_X + 1];
	float rembCT[N_X];
	float nouvCT[N_X];
	void TexteCaption(void);
	void IniCaption(void);
	void TexteChaine(void);
	AnsiString LC_ErreurFinSommaireFrm;

	AnsiString L_LaFormule;
	AnsiString L_DetteN;
	AnsiString L_DetteN1;
	AnsiString L_RembourN;
	AnsiString L_NouveauN;
	AnsiString L_NonVerif;

	AnsiString L_Dette;
	AnsiString L_Rembour;
	AnsiString L_NeRienFaire;

	__fastcall TErreurFinSommaireFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TErreurFinSommaireFrm *ErreurFinSommaireFrm;
//---------------------------------------------------------------------------
#endif
