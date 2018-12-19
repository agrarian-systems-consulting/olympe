//---------------------------------------------------------------------------

#ifndef TarifH
#define TarifH
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
class TTarifFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabNom;
	TLabel *LabCondition;
	TRichEdit *RECondition;
	TPanel *PanPourRG;
	TRadioGroup *RGLimite;
	TRadioGroup *RGMultiple;
	TBitBtn *BtBnDico;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall RGLimiteClick(TObject *Sender);
	void __fastcall BtBnDicoClick(TObject *Sender);
private: // Déclarations utilisateur
public:// Déclarations utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GBCondition;
	AnsiString LC_BtBnDico;
	AnsiString LC_LabNom;
	AnsiString LC_RGLimite;
	AnsiString LC_RGMultiple;
	AnsiString LC_TarifFrm;

	__fastcall TTarifFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTarifFrm *TarifFrm;
//---------------------------------------------------------------------------
#endif
