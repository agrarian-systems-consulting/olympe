//---------------------------------------------------------------------------

#ifndef ActionH
#define ActionH
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
class TActionFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
private:// Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TActionFrm *ActionFrm;
//---------------------------------------------------------------------------
#endif
