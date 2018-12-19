//---------------------------------------------------------------------------
#ifndef TVChoixH
#define TVChoixH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "Forme00.h"
//---------------------------------------------------------------------------
class TTVChoixFrm: public TForm {
	__published: // Composants gérés par l'EDI
TTreeView	*TV;
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
protected: // Déclarations de l'utilisateur
	TMemo *Memo;
	TRadioGroup *RGModifiable;
	//cf "AgriSaisieEnum.h"
	void __fastcall TVDblClickAssol(void);
	void __fastcall TVDblClickVariable(void);
	void __fastcall TVDblClickVerger(void);
	void __fastcall TVDblClickVivrier(void);
	void __fastcall TVDblClickFormule(void);
	void __fastcall TVDblClickCreanceDette(void);
	void __fastcall TVDblClickStockIni(void);
	void __fastcall TVDblClickPolStock(void);

private:
	int __fastcall trouveFamille(CL_Item *item);

public:// Déclarations de l'utilisateur
	TStringGrid *LaGrille;
	int Origine;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_TVChoixFrm;

	__fastcall TTVChoixFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVChoixFrm *TVChoixFrm;
//---------------------------------------------------------------------------
#endif
