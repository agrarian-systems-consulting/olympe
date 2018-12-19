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
	__fastcall TQRMemoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRMemoFrm *QRMemoFrm;
//---------------------------------------------------------------------------
#endif
