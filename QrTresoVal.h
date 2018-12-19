//---------------------------------------------------------------------------

#ifndef QrTresoValH
#define QrTresoValH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Grids.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TQRTresoValFrm: public TForm {
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
protected: // Déclarations de l'utilisateur
	TObjectList *LstMois;
	TObjectList *LstVal;
	bool __fastcall CompleteDonnees(void);
	void __fastcall AffRow(void);

public:// Déclarations de l'utilisateur
	int NLigne;
	int MoisDeb;
	TStringGrid *LaGrille;

	void __fastcall Initialise(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_IntituleP;
	AnsiString LC_LabM0;
	AnsiString LC_LabM1;
	AnsiString LC_LabM10;
	AnsiString LC_LabM11;
	AnsiString LC_LabM2;
	AnsiString LC_LabM3;
	AnsiString LC_LabM4;
	AnsiString LC_LabM5;
	AnsiString LC_LabM6;
	AnsiString LC_LabM7;
	AnsiString LC_LabM8;
	AnsiString LC_LabM9;
	AnsiString LC_NomAgri;
	AnsiString LC_QRTresoValFrm;
	AnsiString LC_TitreEtat;
	AnsiString LC_UniteMonnaie;
	AnsiString LC_Val0;
	AnsiString LC_Val1;
	AnsiString LC_Val10;
	AnsiString LC_Val11;
	AnsiString LC_Val2;
	AnsiString LC_Val3;
	AnsiString LC_Val4;
	AnsiString LC_Val5;
	AnsiString LC_Val6;
	AnsiString LC_Val7;
	AnsiString LC_Val8;
	AnsiString LC_Val9;
	AnsiString LC_ValeurEn;

	__fastcall TQRTresoValFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRTresoValFrm *QRTresoValFrm;
//---------------------------------------------------------------------------
#endif
