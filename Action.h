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
	__published: // Composants g�r�s par l'EDI
private:// D�clarations de l'utilisateur
public:// D�clarations de l'utilisateur
	__fastcall TActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TActionFrm *ActionFrm;
//---------------------------------------------------------------------------
#endif
