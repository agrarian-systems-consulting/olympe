//---------------------------------------------------------------------------

#ifndef LesDefSimH
#define LesDefSimH
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
class TLesDefSimFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabPrix;
	TLabel *LabQuantite;
	TBitBtn *BtBnReprendre;
	void __fastcall Grille0Click(TObject *Sender);
	void __fastcall BtBnReprendreClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	void __fastcall AffTouS(int no,int col,int row);
	void __fastcall AffTend(CL_Tendance *tend,int col,int row);
	bool AffEnch;
protected:
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
public:// Déclarations utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LesDefSimFrm;
	AnsiString LC_GBPrix;
	AnsiString LC_GBQuantite;
	AnsiString LC_BtBnReprendre;

	__fastcall TLesDefSimFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLesDefSimFrm *LesDefSimFrm;
//---------------------------------------------------------------------------
#endif
