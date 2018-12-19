//---------------------------------------------------------------------------

#ifndef GereRendementH
#define GereRendementH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereAlea.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereRendementFrm: public TGereAleaFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall BtBnQuitterClick(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);void __fastcall BtBnCreerClick(TObject *Sender);void __fastcall BtCopierClick(TObject *Sender);void __fastcall BtsupprimerClick(TObject *Sender);void __fastcall BtModifierClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:
	// Déclarations utilisateur
public:
	// Déclarations utilisateur
	__fastcall TGereRendementFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereRendementFrm *GereRendementFrm;
//---------------------------------------------------------------------------
#endif
