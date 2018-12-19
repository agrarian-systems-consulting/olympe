//---------------------------------------------------------------------------

#ifndef LBSelectionH
#define LBSelectionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TLBSelectionFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnPasOK;
	void __fastcall LBDblClick(TObject *Sender);
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall BtBnPasOKClick(TObject *Sender);
private: // Déclarations utilisateur
public:// Déclarations utilisateur
	__fastcall TLBSelectionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLBSelectionFrm *LBSelectionFrm;
//---------------------------------------------------------------------------
#endif
