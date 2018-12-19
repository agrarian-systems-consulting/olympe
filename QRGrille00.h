//---------------------------------------------------------------------------

#ifndef QRGrille00H
#define QRGrille00H
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
class TQRGrille00Frm: public TForm {
	__published: // Composants gérés par l'EDI
TQuickRep	*QR;
	TQRBand *TitleBand1;
	TQRLabel *NomAgri;
	TQRSysData *QRSysData1;
	TQRLabel *TitreEtat;

	TQRBand *DetailBand1;

	TQRLabel *Val0;
	TQRLabel *Val1;
	TQRLabel *Val2;
	TQRLabel *Val3;
	TQRLabel *Val4;
	TQRLabel *Val5;
	TQRLabel *Val6;
	TQRLabel *Val7;
	TQRLabel *Val8;
	TQRLabel *Val9;
	TQRLabel *Val10;
	TQRLabel *Val11;
	TQRLabel *Val12;
	TQRLabel *Val13;
	TQRLabel *Val14;
	TQRLabel *Val15;
	TQRBand *PageFooterBand1;
	TQRSysData *QRSysData2;
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender,
			bool &PrintReport);
	void __fastcall FormClick(TObject *Sender);
private: // Déclarations utilisateur

	TObjectList *LstVal;
	bool __fastcall CompleteDonnees(void);

public:// Déclarations utilisateur
	TStringGrid *LaGrille;
	int NLigne;
	int ColCount;// ou LaGrille->ColCount ou LstValCount
	char *TypeCol;
	void __fastcall Initialise(void);
	CL_Agriculteur *Agri;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_NomAgri_A;
	AnsiString LC_QRGrille00Frm;
	AnsiString LC_TitreEtat;
	AnsiString LC_Val0;
	AnsiString LC_Val1;
	AnsiString LC_Val10;
	AnsiString LC_Val11;
	AnsiString LC_Val12;
	AnsiString LC_Val13;
	AnsiString LC_Val14;
	AnsiString LC_Val15;
	AnsiString LC_Val2;
	AnsiString LC_Val3;
	AnsiString LC_Val4;
	AnsiString LC_Val5;
	AnsiString LC_Val6;
	AnsiString LC_Val7;
	AnsiString LC_Val8;
	AnsiString LC_Val9;

	__fastcall TQRGrille00Frm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRGrille00Frm *QRGrille00Frm;
//---------------------------------------------------------------------------
#endif
