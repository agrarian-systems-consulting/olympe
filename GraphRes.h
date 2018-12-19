//---------------------------------------------------------------------------

#ifndef GraphResH
#define GraphResH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TResGraphFrm: public TForm {
	__published: // Composants gérés par l'EDI
private:// Déclarations utilisateur
public:// Déclarations utilisateur
	__fastcall TResGraphFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TResGraphFrm *ResGraphFrm;
//---------------------------------------------------------------------------
#endif
