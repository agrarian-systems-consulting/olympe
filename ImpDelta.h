//---------------------------------------------------------------------------

#ifndef ImpDeltaH
#define ImpDeltaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TImpDeltaFrm: public TForm {
	__published: // Composants gérés par l'EDI
TGroupBox	*GBFicCSV;
	TEdit *EdFicCsv;
	TRadioGroup *RGSeparateurCsv;
	TRadioGroup *RGSeparateurDecimal;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnPasOk;
	TOpenDialog *OpenDialogFicCsv;
	void __fastcall EdFicCsvClick(TObject *Sender);
	void __fastcall BtBnOKClick(TObject *Sender);
private: // Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TImpDeltaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TImpDeltaFrm *ImpDeltaFrm;
//---------------------------------------------------------------------------
#endif
