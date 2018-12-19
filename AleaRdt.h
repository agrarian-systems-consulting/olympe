//---------------------------------------------------------------------------

#ifndef AleaRdtH
#define AleaRdtH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AleaPrix.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAleaRdtFrm: public TAleaPrixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall BtDonneesClick(TObject *Sender);void __fastcall BtBnNotesClick(TObject *Sender);void __fastcall RGPrecisionClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);void __fastcall BtReportDroitClick(TObject *Sender);
private:
	// Déclarations utilisateur
	void __fastcall trouveRdt(CL_Delta *delta);
protected:
	virtual void __fastcall VersGrille(TStringGrid *grille);virtual bool __fastcall Stocker(void);virtual void __fastcall DesGrilles(void);

public:
	// Déclarations utilisateur
//    void __fastcall Produit(int *nature);

	AnsiString LC_AleaRdtFrm;
	AnsiString LC_Pcent;
	AnsiString LC_Valeur;

	void __fastcall IniGrille0(void);void __fastcall AppelerVersGrille(void);
	void TexteCaption(void);
	void IniCaption(void);

	__fastcall TAleaRdtFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAleaRdtFrm *AleaRdtFrm;
//---------------------------------------------------------------------------
#endif
