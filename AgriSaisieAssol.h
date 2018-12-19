//---------------------------------------------------------------------------

#ifndef AgriSaisieAssolH
#define AgriSaisieAssolH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAgriSaisieAssolFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGPrecision;
	void __fastcall RGPrecisionClick(TObject *Sender);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall EcrireVecteur(void);
	void __fastcall IniGrilleIndic(void);
	void __fastcall VergerSurface(CL_Verger *verger);

	CL_Agriculteur *Agri;
	int nature;
	AnsiString titre;
	float *vecteur;
	__fastcall TAgriSaisieAssolFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAgriSaisieAssolFrm *AgriSaisieAssolFrm;
//---------------------------------------------------------------------------
#endif
