//---------------------------------------------------------------------------

#ifndef CalendrierH
#define CalendrierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TCalendrierFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtSup;
	TBitBtn *BtRepBas;
	TBitBtn *BtRecopBas;
	TLabel *LabCalendrier;
	TRadioGroup *RGDef;
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall BtRecopBasClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall RGDefClick(TObject *Sender);
protected:
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall IniGrille(TStringGrid *grille);
	virtual void __fastcall VersGrille(TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);
	virtual bool __fastcall ControleLaGrille(TStringGrid *grille);
	virtual void __fastcall DeGrille(TStringGrid *grille);

private: // Déclarations utilisateur
	virtual void __fastcall SaisirCell (int col,int row);
	bool __fastcall DureePeriode(CL_Periode *periode);
	void __fastcall CompleteGrille(CL_Periode *periode,int row);
	bool __fastcall VerifCoherence(TStringGrid *grille);

public:// Déclarations utilisateur
	CL_Calendrier *Calendrier;
//    virtual bool  __fastcall Stocker(void);
	void __fastcall AffCalendrier(void);
	__fastcall TCalendrierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCalendrierFrm *CalendrierFrm;
//---------------------------------------------------------------------------
#endif
