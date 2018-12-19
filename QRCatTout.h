//---------------------------------------------------------------------------

#ifndef QRCatToutH
#define QRCatToutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "QRCatNomUnite.h"
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TQRCatToutFrm: public TQRCatNomUniteFrm {
	__published: // Composants gérés par l'EDI
TQRLabel	*Prix;
	TQRLabel *Tva;
	TQRLabel *PrixPro;
	TQRLabel *UnPro;
	TQRLabel *TauxTva;
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
private: // Déclarations utilisateur
	void __fastcall AffBlanc(void);
	void __fastcall AffTitre(char *nom);
	void __fastcall AffItem(CL_Item *item);
	bool __fastcall CompleteDonnees(void);
public:// Déclarations utilisateur
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GBPrix;
	AnsiString LC_PrixPro;
	AnsiString LC_QRCatToutFrm;
	AnsiString LC_TauxTva;
	AnsiString LC_BtBnTva;
	AnsiString LC_UnPro;
	__fastcall TQRCatToutFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRCatToutFrm *QRCatToutFrm;
//---------------------------------------------------------------------------
#endif
