//---------------------------------------------------------------------------

#ifndef QRCatNomTvaH
#define QRCatNomTvaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "QRCatNom.h"
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TQRCatNomTvaFrm: public TQRCatNomFrm {
	__published: // Composants gérés par l'EDI
TQRLabel	*Tva;
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

	AnsiString LC_QRCatNomTvaFrm;
	AnsiString LC_TauxTva;
	AnsiString LC_BtBnTva;

	__fastcall TQRCatNomTvaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRCatNomTvaFrm *QRCatNomTvaFrm;
//---------------------------------------------------------------------------
#endif
