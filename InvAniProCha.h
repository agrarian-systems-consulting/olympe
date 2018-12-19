//---------------------------------------------------------------------------

#ifndef InvAniProChaH
#define InvAniProChaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "InvAniMax.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
class TInvAniProChaFrm: public TInvAniMaxFrm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnProcha;
	void __fastcall BtBnProchaClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private: // Déclarations de l'utilisateur
	void __fastcall DefinirLesGrilles(void);
	void __fastcall IniGrille(TStringGrid *grille);
	void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall DeGrille(TStringGrid *grille);

public:// Déclarations de l'utilisateur
	__fastcall TInvAniProChaFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInvAniProChaFrm *InvAniProChaFrm;
//---------------------------------------------------------------------------
#endif
