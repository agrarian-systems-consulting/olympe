//---------------------------------------------------------------------------

#ifndef ResGraphLegendeH
#define ResGraphLegendeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TResGraphLegendeFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panel1;
	TBitBtn *BitBtn1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	void __fastcall Legende(TListBox *lbG,TListBox *lbD);

	__fastcall TResGraphLegendeFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResGraphLegendeFrm *ResGraphLegendeFrm;
//---------------------------------------------------------------------------
#endif
