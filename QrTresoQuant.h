//---------------------------------------------------------------------------

#ifndef QrTresoQuantH
#define QrTresoQuantH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Grids.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "QrTresoVal.h"
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TQRTresoQuantFrm: public TQRTresoValFrm {
	__published: // Composants g�r�s par l'EDI
TQRLabel	*LabUnite;
	TQRLabel *QRLabUnite;
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender, bool &PrintReport);
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
protected: // D�clarations de l'utilisateur
	bool __fastcall CompleteDonnees(void);
	void __fastcall AffRow(void);

public:// D�clarations de l'utilisateur
	int NLigne;
	int MoisDeb;
	TStringGrid *LaGrille;
	void __fastcall Initialise(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_QRTresoQuantFrm;
	AnsiString LC_LabUnite;
	AnsiString LC_Unite;

	__fastcall TQRTresoQuantFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRTresoQuantFrm *QRTresoQuantFrm;
//---------------------------------------------------------------------------
#endif
