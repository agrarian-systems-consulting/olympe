//---------------------------------------------------------------------------

#ifndef ClasserH
#define ClasserH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TClasserFrm: public TForm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtClHaut;
	TBitBtn *BtClBas;
	TLabel *LabClasse;
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
private: // Déclarations utilisateur
//    TStringGrid *LaGrille;
//    void __fastcall MarquerLigne(int row);
public:// Déclarations utilisateur
	__fastcall TClasserFrm(TComponent* Owner);
//    void Demarrer(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TClasserFrm *ClasserFrm;
//---------------------------------------------------------------------------
#endif
