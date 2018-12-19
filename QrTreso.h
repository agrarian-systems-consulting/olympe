//---------------------------------------------------------------------------

#ifndef QrTresoH
#define QrTresoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TQRTresoFrm: public TForm {
	__published: // Composants gérés par l'EDI
TQuickRep	*QR;
	TQRBand *QRBand1;
	TQRSysData *QRSysData1;
	TQRLabel *NomAgri;
	TQRLabel *TitreEtat;
	TQRLabel *ValeurEn;
	TQRLabel *QRValeurEn;
	TQRLabel *UniteMonnaie;
	TQRBand *QRBTitreCol;
	TQRLabel *LabM0;
	TQRLabel *LabM1;
	TQRLabel *LabM2;
	TQRLabel *LabM3;
	TQRLabel *LabM4;
	TQRLabel *LabM5;
	TQRLabel *LabM6;
	TQRLabel *LabM7;
	TQRLabel *LabM8;
	TQRLabel *LabM9;
	TQRLabel *LabM10;
	TQRLabel *LabM11;
	TQRBand *QRBDon;
	TQRLabel *IntituleP;
	TQRLabel *Val1;
	TQRLabel *Val2;
	TQRLabel *Val3;
	TQRLabel *Val4;
	TQRLabel *Val5;
	TQRLabel *Val0;
	TQRLabel *Val6;
	TQRLabel *Val7;
	TQRLabel *Val8;
	TQRLabel *Val10;
	TQRLabel *Val9;
	TQRLabel *Val11;
	TQRBand *PageFooterBand1;
	TQRSysData *QRSysData2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender,
			bool &PrintReport);
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
private: // Déclarations de l'utilisateur
	TObjectList *LstMois;
	TObjectList *LstVal;
	bool __fastcall CompleteDonnees(void);
	void __fastcall AffRow(void);

public:// Déclarations de l'utilisateur
	int NLigne;
	int MoisDeb;
	TStringGrid *LaGrille;

	void __fastcall Initialise(void);

	__fastcall TQRTresoFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRTresoFrm *QRTresoFrm;
//---------------------------------------------------------------------------
#endif
