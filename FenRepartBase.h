//---------------------------------------------------------------------------

#ifndef FenRepartBaseH
#define FenRepartBaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//---------------------------------------------------------------------------
class TFenRepartBaseFrm: public TForm {
	__published: // Composants gérés par l'EDI
TGroupBox	*GBCode;
	TEdit *EdCode;
	TLabel *LabPcent;
	TStringGrid *LaGrille;
	TLabel *LabTotPcent;
	TEdit *EdTotPcent;
	TPanel *Panell;
	TBitBtn *BoutFermer;
	TBitBtn *BtBnQuitter;
	TBitBtn *BtBn100;
	TBitBtn *BtBnEgal;
	TLabel *LabelModifie;
	TRadioGroup *RGModifCode;
	void __fastcall FormActivate(TObject *Sender);
private: // Déclarations de l'utilisateur
	void __fastcall Demarre(void);
public:// Déclarations de l'utilisateur
	CL_Repart *Repart,*Repart0;

	__fastcall TFenRepartBaseFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFenRepartBaseFrm *FenRepartBaseFrm;
//---------------------------------------------------------------------------
#endif
