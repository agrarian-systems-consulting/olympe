//---------------------------------------------------------------------------
#ifndef ReclasseGH
#define ReclasseGH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TReclasseGFrm: public TForm {
	__published: // Composants gérés par l'EDI
TButton	*BtOK;
	TButton *BtAnnule;
	TBitBtn *BtHaut;
	TBitBtn *BtBas;
	void __fastcall BtHautClick(TObject *Sender);
	void __fastcall BtBasClick(TObject *Sender);
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private: // Déclarations de l'utilisateur
//	TStringGrid *LaGrille;
public:// Déclarations de l'utilisateur
	__fastcall TReclasseGFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TReclasseGFrm *ReclasseGFrm;
//---------------------------------------------------------------------------
#endif
