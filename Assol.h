//---------------------------------------------------------------------------

#ifndef AssolH
#define AssolH
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
class TAssolFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGPrecision;
	void __fastcall RGPrecisionClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur

//    AnsiString L_Culture;
	AnsiString L_TotCulture;
	AnsiString L_Derobee;
	AnsiString L_TotDerobee;
	AnsiString L_Perenne;
	AnsiString L_TotPerenne;
	AnsiString L_Pluri;
	AnsiString L_TotPluri;
//    AnsiString L_Total;

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
	void TexteChaine(void);

	void TexteCaption(void);
	AnsiString L_Assol;

	void IniCaption(void);

	AnsiString LC_Assolement;
	AnsiString LC_RGPrecision;

	__fastcall TAssolFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAssolFrm *AssolFrm;
//---------------------------------------------------------------------------
#endif
