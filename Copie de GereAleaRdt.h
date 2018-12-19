//---------------------------------------------------------------------------

#ifndef GereAleaRdtH
#define GereAleaRdtH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereAleaPrix.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereAleaRdtFrm: public TGereAleaPrixFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall TVDblClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);void __fastcall BtsupprimerClick(TObject *Sender);void __fastcall BtBnCreerClick(TObject *Sender);void __fastcall BtCopierClick(TObject *Sender);void __fastcall BtModifierClick(TObject *Sender);
private:
	// Déclarations utilisateur
//	CL_Tendance *Tendance;
protected:
	virtual void __fastcall CreeTV(void);virtual void __fastcall AffTendance(void);
//	CL_Tendance *Tendance;

public:
	// Déclarations utilisateur
	__fastcall TGereAleaRdtFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereAleaRdtFrm *GereAleaRdtFrm;
//---------------------------------------------------------------------------
#endif
