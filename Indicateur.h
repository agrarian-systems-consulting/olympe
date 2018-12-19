//---------------------------------------------------------------------------
#ifndef IndicateurH
#define IndicateurH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "Forme0.h"
//#include "Forme0.h"
//---------------------------------------------------------------------------
class TIndicateurFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TRichEdit	*Edit;
	TBitBtn *BtBnStocker;
	TBitBtn *BtBnResultat;
	TBitBtn *BtBnCourbe;
	TBitBtn *BtBnImp;
	TPanel *PanHaut;
	TLabel *LabIndicateur;
	TLabel *LabelModifie;
	TBitBtn *BitBtn1;
	TBitBtn *BtBnMotCle;
	TRadioGroup *RGModifiable;
	TLabel *LabSupprimable;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnNotes;
	TBitBtn *BtBnAide;
	void __fastcall EditChange(TObject *Sender);

	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall RGModifiableClick(TObject *Sender);

	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnDicoClick(TObject *Sender);

	void __fastcall BtBnMotCleClick(TObject *Sender);
	void __fastcall BtBnResultatClick(TObject *Sender);

	void __fastcall BtBnCourbeClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall EditMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
	void __fastcall EditEnter(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);

protected:

private: // Déclarations de l'utilisateur
	bool __fastcall Compiler(void);

	CL_Elt Elt;
public:
	CL_Indicateur *Indicateur;
	int Origine;
	void __fastcall AffIndicateur(void);
//	virtual void __fastcall Stocker(void);
	bool __fastcall Calculer(void);
	void __fastcall PossibleModifier(bool modifiable);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBnCourbe;
	AnsiString LC_BtDico;
	AnsiString LC_LabIndicateur;
	AnsiString LC_GBAtelier_A;
	AnsiString LC_RGModifiable;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtMotCle;
	AnsiString LC_BtBnResultat;
	AnsiString LC_LabUtilise;

	__fastcall TIndicateurFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIndicateurFrm *IndicateurFrm;
//---------------------------------------------------------------------------
#endif
