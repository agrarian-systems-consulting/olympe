//---------------------------------------------------------------------------

#ifndef QRCatNomUniteH
#define QRCatNomUniteH
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
class TQRCatNomUniteFrm: public TQRCatNomFrm {
	__published: // Composants gérés par l'EDI
TQRLabel	*Unite;
	TQRLabel *UUt;
	TQRLabel *UTrans;
	TQRLabel *UGlobal;
	TQRLabel *Atelier;
	TQRLabel *Expl;
	TQRLabel *Region;
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
private: // Déclarations utilisateur
	void __fastcall AffBlanc(void);
	void __fastcall AffTitre(char *nom);
	void __fastcall AffItem(CL_Item *item);
	bool __fastcall CompleteDonnees(void);
public:// Déclarations utilisateur

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_AtelierFrm;
	AnsiString LC_Expl;
	AnsiString LC_QRCatNomUniteFrm;
	AnsiString LC_Region;
	AnsiString LC_UGlobal;
	AnsiString LC_BtBnUnite;
	AnsiString LC_UTrans;
	AnsiString LC_UUt;
	__fastcall TQRCatNomUniteFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRCatNomUniteFrm *QRCatNomUniteFrm;
//---------------------------------------------------------------------------
#endif
