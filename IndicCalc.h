//---------------------------------------------------------------------------

#ifndef IndicCalcH
#define IndicCalcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TIndicCalcFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanB;
	TRichEdit *RE;
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TIndicCalcFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIndicCalcFrm *IndicCalcFrm;
//---------------------------------------------------------------------------
#endif
