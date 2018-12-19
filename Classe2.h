//---------------------------------------------------------------------------

#ifndef Classe2H
#define Classe2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TClasse2Frm: public TFrame {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtHaut;
	TBitBtn *BtBas;
	TLabel *LabClasse;
	void __fastcall BtHautClick(TObject *Sender);
	void __fastcall BtBasClick(TObject *Sender);
private: // Déclarations utilisateur
	TStringGrid *LaGrille;
public:// Déclarations utilisateur
	__fastcall TClasse2Frm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClasse2Frm *Classe2Frm;
//---------------------------------------------------------------------------
#endif
