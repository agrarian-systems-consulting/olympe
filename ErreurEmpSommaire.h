//---------------------------------------------------------------------------

#ifndef ErreurEmpSommaireH
#define ErreurEmpSommaireH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ErreurImmoSommaire.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TErreurEmpSommaireFrm: public TErreurImmoSommaireFrm {
	__published: // Composants gérés par l'EDI
private:// Déclarations de l'utilisateur
public:// Déclarations de l'utilisateur
	__fastcall TErreurEmpSommaireFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TErreurEmpSommaireFrm *ErreurEmpSommaireFrm;
//---------------------------------------------------------------------------
#endif
