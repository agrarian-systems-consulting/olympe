//---------------------------------------------------------------------------

#ifndef TresoDefOcccH
#define TresoDefOcccH
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
class TTresoDefOcccFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtReportDroit;
	TButton *SansMaxi;
	TBitBtn *BtRepToutDroit;
	TBitBtn *BtBnCalcul;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SansMaxiClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtRepToutDroitClick(TObject *Sender);
	void __fastcall BtBnCalculClick(TObject *Sender);
	void __fastcall Grille0KeyPress(TObject *Sender, char &Key);
private: // Déclarations de l'utilisateur
	// copie de TresoRes à placer ailleurs
	CL_PossibOcPlact *PossibOcPlact;
	/*
	 float Occc1Max[N_X],Occc2Max[N_X];
	 float TauxOccc1[N_X],TauxOccc2[N_X];
	 float PlactMax[N_X];
	 float TauxPlact[N_X];
	 */
	void __fastcall VersGrille(TStringGrid *grille);
	AnsiString Aff(float x,int digits=0);
	void __fastcall DeGrille(TStringGrid *grille);
	float __fastcall GrilleFloat(int col,int row);

public: // Déclarations de l'utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBnResultat;
	AnsiString LC_SansMaxi;
	AnsiString LC_TresoDefOcccFrm;

	__fastcall TTresoDefOcccFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoDefOcccFrm *TresoDefOcccFrm;
//---------------------------------------------------------------------------
#endif
