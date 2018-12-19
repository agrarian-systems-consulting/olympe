//---------------------------------------------------------------------------

#ifndef InvAniMaxH
#define InvAniMaxH
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
class TInvAniMaxFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabEffMax;
	TBitBtn *BtReportDroit;
	TBitBtn *BtBnSansBorne;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall BtBnSansBorneClick(TObject *Sender);
private: // Déclarations utilisateur
protected:
	CL_Agriculteur *Agri;
	int An_0;
	TStringGrid *GrilleMax;
	void __fastcall Demarrer(void);
	void __fastcall Personnaliser(void);
	void __fastcall DefinirLesGrilles(void);
	void __fastcall IniGrille(TStringGrid *grille);
//    void __fastcall SaisirCell(int col,int row);
//    bool __fastcall ControleCell(int col,int row);
	void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall DeGrille(TStringGrid *grille);

public:// Déclarations utilisateur
	int Origine;
	__fastcall TInvAniMaxFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInvAniMaxFrm *InvAniMaxFrm;
//---------------------------------------------------------------------------
#endif
