//---------------------------------------------------------------------------

#ifndef ClasseH
#define ClasseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TClasseFrm: public TFrame {
	__published: // Composants g�r�s par l'EDI
TBitBtn	*BtHaut;
	TBitBtn *BtBas;
	TLabel *LabClasse;
	void __fastcall BtHautClick(TObject *Sender);
private: // D�clarations utilisateur
	TStringGrid *LaGrille;
public:// D�clarations utilisateur
	__fastcall TClasseFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClasseFrm *ClasseFrm;
//---------------------------------------------------------------------------
#endif
