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
	__published: // Composants g�r�s par l'EDI
TPanel	*PanB;
	TRichEdit *RE;
private: // D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	__fastcall TIndicCalcFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIndicCalcFrm *IndicCalcFrm;
//---------------------------------------------------------------------------
#endif
