//---------------------------------------------------------------------------

#ifndef QRMemoH
#define QRMemoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TQRMemoFrm: public TForm {
	__published: // Composants gérés par l'EDI
TQuickRep	*QR;
	TQRBand *TitleBand1;
	TQRSysData *QRSysData;
	TQRLabel *NomAgri;
	TQRLabel *TitreEtat;
	TQRRichText *RE;
private: // Déclarations utilisateur
public:// Déclarations utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_NomAgri_A;
	AnsiString LC_QRMemoFrm;
	AnsiString LC_TitreEtat;
	__fastcall TQRMemoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRMemoFrm *QRMemoFrm;
//---------------------------------------------------------------------------
#endif
